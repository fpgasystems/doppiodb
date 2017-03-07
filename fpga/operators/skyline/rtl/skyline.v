
//`include "../../framework_defines.vh"

module skyline #(parameter NUM_DIMENSIONS  = 16,
                 parameter DIMENSION_WIDTH = 32,
                 //parameter MAX_DIM_BITS    = 8,
                 parameter NUM_CORES       = 128)(
    input   wire                        clk,
    input   wire                        rst_n,
    //-------------------------------------------------//
	input   wire 					    start_um,
    input   wire [1535:0]               um_params,
    output  reg                         um_done,

    output  wire [`NUM_USER_STATE_COUNTERS*32-1:0] um_state_counters,
    output  wire                                   um_state_counters_valid,
    // TX RD
    output  reg  [57:0]                 um_tx_rd_addr,
    output  reg  [7:0]                  um_tx_rd_tag,
    output  reg  						um_tx_rd_valid,
    input   wire                        um_tx_rd_ready,
    // TX WR
    output  reg  [57:0]                 um_tx_wr_addr,
    output  reg  [7:0]                  um_tx_wr_tag,
    output  reg 						um_tx_wr_valid,
    output  reg  [511:0]			    um_tx_data,
    input   wire                        um_tx_wr_ready,
    // RX RD
    input   wire [7:0]                  um_rx_rd_tag,
    input   wire [511:0]                um_rx_data,
    input   wire                        um_rx_rd_valid,
    output  wire                        um_rx_rd_ready,
    // RX WR 
    input   wire                        um_rx_wr_valid,
    input   wire [7:0]                  um_rx_wr_tag
);

//////////////////////////////////////////////////////////////////////////////////

localparam [2:0] 
         SKYLINE_IDLE       = 3'b000,
         SKYLINE_0          = 3'b001,
         SKYLINE_1          = 3'b010,
         SKYLINE_FLUSH      = 3'b011,
         SKYLINE_TERMINATE  = 3'b100;

localparam 
         REQUEUE_TUPLE  = 1'b0,
         SKYLINE_TUPLE  = 1'b1;

//localparam NUM_CORES = 256;

localparam MAX_DIM_BITS = (NUM_DIMENSIONS <= 8)? 4 : 5;

localparam BACKPRESSURE_THRESHOLD_REQUEUE_FIFO = NUM_CORES/4;

localparam NUM_DIMENSIONS_WITH_INDEX = NUM_DIMENSIONS + 1;
//////////////////////////////////////////////////////////////////////////////////
reg   [2:0]                      skyline_state_fsm = 0;


reg   [MAX_DIM_BITS-1:0]         PipeInDimCnt      = 0;    // Counts dimensions inserted in the pipeline            
reg   [MAX_DIM_BITS-1:0]         PipeOutDimCnt     = 0;    // Counts dimensions read out of the pipeline
reg   [MAX_DIM_BITS-1:0]         TupleRdTXDimCnt   = 0;    // Iterates over the dimensions when generating read requests
reg   [MAX_DIM_BITS-1:0]         TupleWrTXDimCnt   = 0;    // Iterates over the dimensions when requeueing the tuples
reg   [MAX_DIM_BITS-1:0]         SkylineWrTXDimCnt = 0;    // Iterates over the dimensions when writing skyline tuples
reg   [MAX_DIM_BITS-1:0]         FlushDimCnt       = 0;    // Counts dummy dimensions inserted in the pipeline            

reg   [31:0]                     ReadTuplesCount   = 0;    // Counts number of tuples we read from the input fifo and insert in the pipeline
reg   [31:0]                     WriteTuplesCount  = 0;    // Counts the number of valid tuples we get from the pipeline and requeue them

reg   [31:0]                     TuplesInMemory    = 0;    // Number of Tuples in the Main memory for the current iteration
reg   [31:0]                     IterationCounter  = 0;    // Current Iteration counter
reg   [31:0]                     NumberOfTuples    = 0;    // Initial number of tuples in main memory
reg   [NUM_DIMENSIONS-1:0]       TupleDimsComparisons = 0;
reg   [MAX_DIM_BITS-1:0]         TupleNumDimsMinusOne   = 0;
reg   [MAX_DIM_BITS-1:0]         TupleNumDimsPlusOne   = 0;
reg   [MAX_DIM_BITS-1:0]         TupleNumDims          = 0;

reg                              TupleValidIReg    = 0;    // Register input tuple (1 dimension) before entering the pipeline (Valid bit)
reg   [DIMENSION_WIDTH-1:0]      TupleDataIReg     = 0;    // Register input tuple (1 dimension) before entering the pipeline (Data word)
reg                              TupleDimsCmpsIReg = 0;

reg                              TupleValidOReg    = 0;    // Register output tuple (1 dimension) coming out of the pipeline (Valid bit)  
reg   [DIMENSION_WIDTH-1:0]      TupleDataOReg     = 0;    // Register output tuple (1 dimension) coming out of the pipeline (Data word)  

wire                             TupleValidO;              // Output tuple (1 dimension) coming out of the pipeline (Valid bit)  
wire  [DIMENSION_WIDTH-1:0]      TupleDataO;               // Output tuple (1 dimension) coming out of the pipeline (Data word)  

reg                              iteration_rd_done;        // Flag indicating if reading tuples from main memory is done for current iteration
reg                              EmptyingCorePipe;         // Flag indicating if we waiting for the pipeline process all in fly tuples (set after last tuple enter the pipeline)
reg   [31:0]                     WaitCorePipeCycles;       // A predefined number of cycles waiting for the pipeline to become empty of in fly tuples
reg                              flush_out_fifo;           // Flush all tuples still in the output fifo
reg                              flush_skyline_fifo;       // Flush all tuples still in the skyline tuples fifo


reg   [57:0]                     dim_base[NUM_DIMENSIONS-1:0];          // Base address for every input dimension (set from um_params)
reg   [31:0]                     dim_rd_offset[NUM_DIMENSIONS-1:0];     // offsets incremented while reading dimensions from main memory (in cacheline increments)
reg   [31:0]                     requeue_wr_offset;                     // offsets incremented while writing (requeuing) dimensions to main memory (in cacheline increments)
reg   [31:0]                     requeue_rd_offset;                     // offsets incremented while writing (requeuing) dimensions to main memory (in cacheline increments)
reg   [57:0]                     requeue_base;  

reg   [57:0]                     skyline_base;                          // Base address for every skyline dimension (set from um_params)
reg   [31:0]                     skyline_wr_offset;                     // offsets incremented while writing skyline dimensions from main memory (in cacheline increments)
reg   [31:0]                     rd_offset_limit;                       // Upper limit for offset increments (in cacheline increments)

//- TX WR channel for requeueing tuples
reg                              requeue_tx_wr_valid;
wire                             requeue_tx_wr_ready;
reg   [57:0]                     requeue_tx_wr_addr;
reg   [511:0]                    requeue_tx_data;

// TX WR channel for writing skyline tuples 
reg                              skyline_tx_wr_valid;
wire                             skyline_tx_wr_ready;
reg   [57:0]                     skyline_tx_wr_addr;
reg   [511:0]                    skyline_tx_data;

// Input FIFO output signals
wire                             in_fifo_ready;
wire                             in_fifo_valid;
wire  [DIMENSION_WIDTH-1:0]      in_fifo_dout;

// Skyline Tuple coming out of the pipeline
wire  [DIMENSION_WIDTH-1:0]      SkylineTupleData;
wire                             SkylineTupleValid;
wire                             PipelineEmpty;          // The pipeline is flushed of all skyline tuples

// Command to invalidate (or validate) a tuple coming out of the pipeline
reg                              FlushTuple;
reg                              FlushTupleASValid;

wire                             FilteredTupleValid;
wire  [DIMENSION_WIDTH-1:0]      FilteredTupleData;

// Output FIFO signals
wire                             out_fifo_empty;
wire                             out_fifo_ready;
wire                             out_fifo_valid;
wire  [511:0]                    out_fifo_dout;

wire                             skyline_fifo_empty;
wire                             skyline_fifo_ready;
wire                             skyline_fifo_valid;
wire  [511:0]                    skyline_fifo_dout;

reg                              writer_state = 0;
reg                              Activated    = 0;
reg                              clearInputFIFO = 0;
reg                              clearOutputFIFO = 0;

//- Statistics Counters
wire  [31:0]                     NumberOfSkylineTuples_t;
reg   [31:0]                     NumberOfSkylineTuples = 0;
reg   [31:0]                     NumberOfIterations    = 0;
reg   [31:0]                     requeue_requests      = 0;
reg   [31:0]                     requeue_responses     = 0;


wire  [11:0]                     RequeueFIFOSpace;
wire                             waitForSpaceInRequeueFIFO;

reg   [31:0]                     StalledInputCounter    = 0;
reg   [31:0]                     RequeueFIFOFullCounter = 0;
reg   [31:0]                     ActiveCycles           = 0;
reg   [31:0]                     ReadingDimsCycles      = 0;
reg   [31:0]                     starvingCycles         = 0;
reg   [31:0]                     SKTuplesViolations     = 0;
reg   [31:0]                     RequeueViolations      = 0;

wire                             RequeueTuplesFIFOReady;
wire                             SkylineTuplesFIFOReady;

reg                              firstTime;
reg   [31:0]                     PrevRequeuedLines;

genvar j;
integer i;


////////////////////////////////////////////////////////////////////////////////////////////////////
assign um_state_counters_valid = 1'b0;
assign um_state_counters       = {//{((`NUM_USER_STATE_COUNTERS-3)*32){1'b0}},
                                  StalledInputCounter,
                                  RequeueFIFOFullCounter,
                                  SKTuplesViolations,
                                  RequeueViolations, 
                                  starvingCycles,
                                  requeue_requests, 
                                  NumberOfIterations, 
                                  NumberOfSkylineTuples};

always @(posedge clk) begin
    if (~rst_n) begin
        StalledInputCounter    <= 0;
        RequeueFIFOFullCounter <= 0;
        ActiveCycles           <= 0;
        ReadingDimsCycles      <= 0;
        starvingCycles         <= 0;
        SKTuplesViolations     <= 0;
        RequeueViolations      <= 0;
    end
    else begin 
        if (um_rx_rd_valid & ~um_rx_rd_ready) begin
            StalledInputCounter <= StalledInputCounter + 1'b1;
        end 
        if (waitForSpaceInRequeueFIFO) begin
            RequeueFIFOFullCounter <= RequeueFIFOFullCounter + 1'b1;
        end

        if(skyline_state_fsm == SKYLINE_0) begin
            ActiveCycles <= ActiveCycles + 1'b1;
        end

        if(~iteration_rd_done & (skyline_state_fsm == SKYLINE_0)) begin
            ReadingDimsCycles <= ReadingDimsCycles + 1'b1;
        end

        if(~in_fifo_valid & (skyline_state_fsm == SKYLINE_0)) begin
            starvingCycles <= starvingCycles + 1'b1;
        end

        if(SkylineTupleValid & ~SkylineTuplesFIFOReady) begin 
            SKTuplesViolations <= SKTuplesViolations + 1'b1;
        end

        if(FilteredTupleValid & ~RequeueTuplesFIFOReady) begin 
            RequeueViolations <= RequeueViolations + 1'b1;
        end
    end
end
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////             Register Parameters             /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
generate for(j=0; j < NUM_DIMENSIONS; j= j+1) begin: configPtrs

always @(posedge clk) begin
    if(~rst_n) begin
        dim_base[j]     <= 0;
    end 
    else begin 
        if(start_um) begin
            dim_base[j]     <= um_params[j*64+63 +512 : j*64 + 6 + 512];
        end
    end
end
end 
endgenerate

always @(posedge clk) begin
    if(~rst_n) begin
        NumberOfTuples         <= 0;
        Activated              <= 0;
        
        skyline_base           <= 0;
        requeue_base           <= 0;

        TupleNumDimsMinusOne   <= 0;
        TupleNumDims           <= 0;
        TupleNumDimsPlusOne    <= 0;
        TupleDimsComparisons   <= 0;
    end 
    else begin 
        Activated       <= 1'b0;
        if(start_um) begin
            skyline_base           <= um_params[63: 6];
            requeue_base           <= um_params[127: 70];

            NumberOfTuples         <= um_params[159: 128];
            TupleNumDimsMinusOne   <= um_params[159+MAX_DIM_BITS   : 160] - 1'b1;
            TupleNumDims           <= um_params[159+MAX_DIM_BITS   : 160];
            TupleNumDimsPlusOne    <= um_params[159+MAX_DIM_BITS   : 160] + 1'b1;
            TupleDimsComparisons   <= um_params[191+NUM_DIMENSIONS : 192];

            Activated              <= 1'b1;
        end
    end
end

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////               Skyline FSM                   /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   SKYLINE FSM:

      SKYLINE_IDLE: When the Operator is triggered, we record the initial number of tuples in Main memory
                    and initialize other variables properly then move SKYLINE_0 state.

      SKYLINE_0: In this state the skyline operator is active, reading tuples from memory, requeuing tuples 
                 and writing skyline tuple back to main memory. 
                 Reading tuples terminates when all tuples of the current iteration are fetched.
                 When the core pipeline is empty of tuples and all tuples in the output buffer are sent to 
                 main memory we change state to SKYLINE_1.
                 NOTE: WE DO NOT CHECK RESPONSES OF ALL WRITES, THIS MIGHT LEAD TO READ-AFTER-WRITE DATA 
                 HAZARD.

      SKYLINE_1: This state checks if we need more iterations or not. If we requeue some tuples back to 
                 main memory, we need another iteration, otherwise we move to SKYLINE_FLUSH.
    
      SKYLINE_FLUSH: Here we flush all skyline tuples in the corepipe, untill there is no more tuples 
                     in the pipeline, then we terminate the operator.
*/
assign in_fifo_ready = (firstTime)? (skyline_state_fsm == SKYLINE_0) & (PipeInDimCnt < TupleNumDims)        & ~waitForSpaceInRequeueFIFO :
                                    (skyline_state_fsm == SKYLINE_0) & (PipeInDimCnt < TupleNumDimsPlusOne) & ~waitForSpaceInRequeueFIFO;

assign waitForSpaceInRequeueFIFO = RequeueFIFOSpace < BACKPRESSURE_THRESHOLD_REQUEUE_FIFO;

always @(posedge clk) begin
	if(~rst_n) begin
        skyline_state_fsm  <= 0;

        ReadTuplesCount    <= 0;
        WriteTuplesCount   <= 0;

        TupleValidIReg     <= 1'b0;
        TupleDataIReg      <= 0;

        EmptyingCorePipe   <= 1'b0;
        WaitCorePipeCycles <= 0;

        TupleDataOReg      <= 0;
        TupleValidOReg     <= 1'b0;

        FlushTupleASValid  <= 1'b0;
        FlushTuple         <= 1'b0;
                
        PipeOutDimCnt      <= 0;
        PipeInDimCnt       <= 0;
        TupleRdTXDimCnt    <= 0;
        FlushDimCnt        <= 0;

        TuplesInMemory     <= 0;
        IterationCounter   <= 1;

        um_tx_rd_valid     <= 0;
        um_tx_rd_addr      <= 0;
        um_tx_rd_tag       <= 0;
        iteration_rd_done  <= 0;

        requeue_tx_wr_valid    <= 1'b0;
        requeue_tx_data        <= 0;
        requeue_tx_wr_addr     <= 0;

        skyline_tx_wr_valid    <= 1'b0;
        skyline_tx_data        <= 0;
        skyline_tx_wr_addr     <= 0;

        for(i=0; i < NUM_DIMENSIONS; i=i+1) begin 
            dim_rd_offset[i]   <= 0;
        end

        requeue_wr_offset     <= 0;
        skyline_wr_offset     <= 0;
        requeue_rd_offset     <= 0;

        flush_out_fifo     <= 0;
        flush_skyline_fifo <= 0;
        
        um_done            <= 1'b0;

        clearInputFIFO     <= 1'b0;
        clearOutputFIFO    <= 1'b0;

        NumberOfIterations    <= 0;
        NumberOfSkylineTuples <= 0;

        firstTime             <= 1'b1;
        PrevRequeuedLines     <= 0;

	end 
	else begin
		
		case (skyline_state_fsm)

            SKYLINE_IDLE: begin
                if(Activated) begin 
                    skyline_state_fsm <= SKYLINE_0;

                    um_done            <= 1'b0;
                    firstTime          <= 1'b1;
                    PrevRequeuedLines  <= 0;
                    //------------------- Reset FSM Variables ---------------------//
                    ReadTuplesCount    <= 0;
                    WriteTuplesCount   <= 0;

                    TupleValidIReg     <= 1'b0;
                    TupleDataIReg      <= 0;

                    EmptyingCorePipe   <= 1'b0;
                    WaitCorePipeCycles <= 0;

                    TupleDataOReg      <= 0;
                    TupleValidOReg     <= 1'b0;

                    FlushTupleASValid  <= 1'b0;
                    FlushTuple         <= 1'b0;
                
                    PipeOutDimCnt      <= 0;
                    PipeInDimCnt       <= 0;
                    TupleRdTXDimCnt    <= 0;
                    FlushDimCnt        <= 0;

                    TuplesInMemory     <= NumberOfTuples;

                    if( NumberOfTuples[3:0] > 0 ) begin
                        rd_offset_limit  <= NumberOfTuples[31:4];
                    end 
                    else begin 
                        rd_offset_limit  <= NumberOfTuples[31:4] - 1;
                    end

                    IterationCounter     <= 1;

                    NumberOfIterations    <= 0;
                    NumberOfSkylineTuples <= 0;
                end
            end

          /*  SKYLINE_INIT: begin
                skyline_state_fsm <= SKYLINE_0;
            end */

            //- SKYLINE_0: Read tuples from the input fifo and pass to the core pipe, once all the tuples
            // in memory are read, we change to state SKYLINE_1


            //#############################################################################################//
			SKYLINE_0: begin 
            
                clearOutputFIFO <= 1'b0;
            //---------------------------------------------------------------------------------------------//
            //----------------------------- Reading Tuples from Main Memory -------------------------------//
            //---------------------------------------------------------------------------------------------//
                if( um_tx_rd_ready ) begin
                    um_tx_rd_valid <= 1'b0;
                    if( ~iteration_rd_done ) begin 
                        um_tx_rd_valid <= 1'b1;
                        um_tx_rd_tag   <= 0;

                        if( firstTime ) begin
                            um_tx_rd_addr  <= dim_base[ TupleRdTXDimCnt ] + dim_rd_offset[TupleRdTXDimCnt];
                            

                            for(i = 0; i < NUM_DIMENSIONS; i=i+1) begin 
                                if(TupleRdTXDimCnt == i) begin 
                                    if( dim_rd_offset[i] == rd_offset_limit ) begin 
                                        dim_rd_offset[i] <= 0;
                                    end
                                    else begin 
                                        dim_rd_offset[i] <= dim_rd_offset[i] + 1;
                                    end
                                end
                            end

                            if(TupleRdTXDimCnt == TupleNumDimsMinusOne) begin 
                                TupleRdTXDimCnt <= 0;

                                if( dim_rd_offset[TupleNumDimsMinusOne] == rd_offset_limit ) begin 
                                    iteration_rd_done <= 1'b1;
                                end
                            end
                            else begin 
                                TupleRdTXDimCnt <= TupleRdTXDimCnt + 1'b1;
                            end
                        end
                        else begin
                            um_tx_rd_addr      <= requeue_base + requeue_rd_offset;
                            requeue_rd_offset  <= requeue_rd_offset + 1'b1;
                            
                            if( requeue_rd_offset == rd_offset_limit ) begin
                                iteration_rd_done <= 1'b1;
                                requeue_rd_offset <= 0;
                            end
                        end 
                    end
                end
            //---------------------------------------------------------------------------------------------//
			//----------------------------------- Input FIFO to core pipe ---------------------------------//
            //---------------------------------------------------------------------------------------------//
				TupleValidIReg    <= 1'b0;
                clearInputFIFO    <= 1'b0;
                TupleDimsCmpsIReg <= 1'b0;
                
                //- When we push the last tuple dim in the core pipeline, we start waiting 
                // for the pipeline to empty.
                if(ReadTuplesCount == TuplesInMemory) begin 
                    EmptyingCorePipe   <= 1'b1;
                    WaitCorePipeCycles <= 1;
                    ReadTuplesCount    <= 0;
                end

				if (PipeInDimCnt == TupleNumDimsPlusOne) begin
					TupleDataIReg     <= IterationCounter;
					PipeInDimCnt      <= 0;
                    TupleValidIReg    <= 1'b1;
                    ReadTuplesCount   <= ReadTuplesCount + 1;
				end
                else if (PipeInDimCnt == TupleNumDims) begin
                    if((in_fifo_valid & ~waitForSpaceInRequeueFIFO) | firstTime ) begin
                        TupleValidIReg  <= 1'b1;
                        if(firstTime) begin
                            TupleDataIReg   <= ReadTuplesCount;
                        end
                        else begin
                            TupleDataIReg   <= in_fifo_dout;
                        end
                        PipeInDimCnt    <= PipeInDimCnt + 1;

                        if( ReadTuplesCount == (TuplesInMemory-1) ) begin 
                            clearInputFIFO <= 1'b1;
                        end
                    end
                end
				else if(in_fifo_valid & ~waitForSpaceInRequeueFIFO) begin
                    TupleValidIReg    <= 1'b1;
                    TupleDataIReg     <= in_fifo_dout;
                    TupleDimsCmpsIReg <= TupleDimsComparisons[PipeInDimCnt];
                    PipeInDimCnt      <= PipeInDimCnt + 1;
                end
            //---------------------------------------------------------------------------------------------//
            //--------------------------------- Core pipe to Output FIFO ----------------------------------//
            //---------------------------------------------------------------------------------------------//
                TupleDataOReg     <= TupleDataO;
                FlushTupleASValid <= 1'b0;
                FlushTuple        <= 1'b0;
                TupleValidOReg    <= 1'b0;

                if( TupleValidO ) begin 
                    if (PipeOutDimCnt == TupleNumDimsPlusOne) begin
                        if( TupleDataO[0] ) begin 
                            WriteTuplesCount  <= WriteTuplesCount + 1;
                            FlushTupleASValid <= 1'b1;
                        end
                        PipeOutDimCnt    <= 0;
                        FlushTuple       <= 1'b1;
                    end
                    else begin 
                        PipeOutDimCnt    <= PipeOutDimCnt + 1;
//                        if(PipeOutDimCnt < TupleNumDims) begin 
                            TupleValidOReg   <= 1'b1;
  //                      end 
                    end
                end
            //---------------------------------------------------------------------------------------------//
            //---------------------------------- Requeue Tuples to Main Memory ----------------------------//
            //---------------------------------------------------------------------------------------------//
                if( requeue_tx_wr_ready) begin 
                    requeue_tx_wr_valid <= 1'b0;
                    if(out_fifo_valid) begin
                        requeue_tx_wr_valid    <= 1'b1;
                        requeue_tx_data        <= out_fifo_dout;
                        requeue_tx_wr_addr     <= requeue_base + requeue_wr_offset;
                        requeue_wr_offset      <= requeue_wr_offset + 1; // CL increments

                        PrevRequeuedLines      <= requeue_wr_offset;
                    end
                end
            //---------------------------------------------------------------------------------------------//
            //------------------------------- Write Skyline Tuples to Main Memory -------------------------//
            //---------------------------------------------------------------------------------------------//
                if( skyline_tx_wr_ready) begin 
                    skyline_tx_wr_valid <= 1'b0;
                    if(skyline_fifo_valid) begin
                        skyline_tx_wr_valid   <= 1'b1;
                        skyline_tx_data       <= skyline_fifo_dout;
                        skyline_tx_wr_addr    <= skyline_base + skyline_wr_offset;
                        skyline_wr_offset     <= skyline_wr_offset + 1; // CL increments
                    end
                end
            //---------------------------------------------------------------------------------------------//
            //---------------------------------- Check if Pipeline Empty ----------------------------------//
            //---------------------------------------------------------------------------------------------//
                if(EmptyingCorePipe) begin 
                    WaitCorePipeCycles <= WaitCorePipeCycles + 1;
                end
                if(WaitCorePipeCycles == NUM_CORES*2) begin 
                    skyline_state_fsm <= SKYLINE_1;
                    flush_out_fifo    <= 1'b1;
                    firstTime         <= 1'b0;

                    NumberOfIterations <= NumberOfIterations + 1'b1;
                end
			end

            //#############################################################################################// 
            SKYLINE_1: begin 


            //---------------------------------------------------------------------------------------------//
            //---------------------------------- Requeue Tuples to Main Memory ----------------------------//
            //---------------------------------------------------------------------------------------------//
                if( requeue_tx_wr_ready) begin 
                    requeue_tx_wr_valid <= 1'b0;
                    if(out_fifo_valid) begin
                        requeue_tx_wr_valid    <= 1'b1;
                        requeue_tx_data        <= out_fifo_dout;
                        requeue_tx_wr_addr     <= requeue_base + requeue_wr_offset;
                        requeue_wr_offset      <= requeue_wr_offset + 1; // CL increments

                        PrevRequeuedLines      <= requeue_wr_offset;
                    end
                end
            //---------------------------------------------------------------------------------------------//
            //------------------------------- Write Skyline Tuples to Main Memory -------------------------//
            //---------------------------------------------------------------------------------------------//
                if( skyline_tx_wr_ready) begin 
                    skyline_tx_wr_valid <= 1'b0;
                    if(skyline_fifo_valid) begin
                        skyline_tx_wr_valid   <= 1'b1;
                        skyline_tx_data       <= skyline_fifo_dout;
                        skyline_tx_wr_addr    <= skyline_base + skyline_wr_offset;
                        skyline_wr_offset     <= skyline_wr_offset + 1; // CL increments
                    end
                end
            //---------------------------------------------------------------------------------------------//
            //------------------------------------ Reset FSM Variables ------------------------------------//
            //---------------------------------------------------------------------------------------------//
                firstTime         <= 1'b0;
                ReadTuplesCount   <= 0;

                TupleValidIReg    <= 1'b0;
                TupleDataIReg     <= 0;

                EmptyingCorePipe  <= 1'b0;

                TupleDataOReg     <= 0;
                TupleValidOReg    <= 1'b0;

                FlushTupleASValid <= 1'b0;
                FlushTuple        <= 1'b0;
                
                PipeOutDimCnt     <= 0;
                PipeInDimCnt      <= 0;
 
                iteration_rd_done <= 0;
                
                TuplesInMemory    <= WriteTuplesCount;

                rd_offset_limit   <= PrevRequeuedLines;
            
            //---------------------------------------------------------------------------------------------//
            //----------------------------- Change state when output fifo is empty ------------------------//
            //---------------------------------------------------------------------------------------------//
                if(out_fifo_empty) begin 
                    flush_out_fifo    <= 1'b0;
                    clearOutputFIFO   <= 1'b1;
                    requeue_wr_offset <= 0;

                    if( ~requeue_tx_wr_valid ) begin
                        if(requeue_requests == requeue_responses ) begin 
                            if( WriteTuplesCount > 0 ) begin 
                                skyline_state_fsm <= SKYLINE_0;
                                IterationCounter  <= IterationCounter + 2;
                                WriteTuplesCount  <= 0;
                            end
                            else begin 
                                skyline_state_fsm  <= SKYLINE_FLUSH;
                            end
                        end
                    end 
                end
            end

            //#############################################################################################// 
            SKYLINE_FLUSH: begin 

                clearOutputFIFO <= 1'b0;
            //---------------------------------------------------------------------------------------------//
            //------------------------------- Write Skyline Tuples to Main Memory -------------------------//
            //---------------------------------------------------------------------------------------------//
                if( skyline_tx_wr_ready) begin 
                    skyline_tx_wr_valid <= 1'b0;
                    if(skyline_fifo_valid) begin
                        skyline_tx_wr_valid   <= 1'b1;
                        skyline_tx_data       <= skyline_fifo_dout;
                        skyline_tx_wr_addr    <= skyline_base + skyline_wr_offset;
                        skyline_wr_offset     <= skyline_wr_offset + 1; // CL increments
                    end
                end

            //---------------------------------------------------------------------------------------------//
            //--------------------------- Send Dummy Tuples until pipeline is empty -----------------------//
            //---------------------------------------------------------------------------------------------//
                TupleValidIReg <= 1'b0;

                if( PipelineEmpty ) begin
                    if( ~skyline_tx_wr_valid ) begin 
                        skyline_state_fsm  <= SKYLINE_TERMINATE;
                        flush_skyline_fifo <= 1'b1;
                    end
                end 
                else begin
                    TupleValidIReg <= 1'b1;

                    // last tuple dim: send round counter
                    if (FlushDimCnt == TupleNumDimsPlusOne) begin
                        TupleDataIReg    <= IterationCounter + 1;
                        FlushDimCnt      <= 0;
                        IterationCounter     <= IterationCounter + 2;
                    end 
                    // second last tuple dim: send tuple counter
                    else if (FlushDimCnt == TupleNumDims) begin
                        TupleDataIReg    <= 0;
                        FlushDimCnt      <= FlushDimCnt + 1;
                    end 
                    // other tuple dims: send dummy value (Int.Max()) 
                    else begin 
                        TupleDataIReg    <= {32{~(TupleDimsComparisons[FlushDimCnt])}}; //`INT_MAX;
                        FlushDimCnt      <= FlushDimCnt + 1;
                    end;
                end 

            end
            //#############################################################################################// 
            SKYLINE_TERMINATE: begin 

                flush_skyline_fifo    <= 1'b0;
                NumberOfSkylineTuples <= NumberOfSkylineTuples_t;

            //---------------------------------------------------------------------------------------------//
            //------------------------------- Write Skyline Tuples to Main Memory -------------------------//
            //---------------------------------------------------------------------------------------------//
                if( skyline_tx_wr_ready) begin 
                    skyline_tx_wr_valid <= 1'b0;
                    if(skyline_fifo_valid) begin
                        skyline_tx_wr_valid   <= 1'b1;
                        skyline_tx_data       <= skyline_fifo_dout;
                        skyline_tx_wr_addr    <= skyline_base + skyline_wr_offset;
                        skyline_wr_offset     <= skyline_wr_offset + 1; // CL increments
                    end
                end
                //

                if( skyline_fifo_empty ) begin
                    skyline_state_fsm <= SKYLINE_IDLE;

                    um_done           <= 1'b1;
                end 
                
            end 
		endcase // skyline_state_fsm
	end
end

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////               Input Buffer                  /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
SkylineInputFIFO #(.NUM_DIMENSIONS(NUM_DIMENSIONS),
                   .DIMENSION_WIDTH(DIMENSION_WIDTH),
                   .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineInputFIFO_0(

	.clk                (clk),
	.rst_n              (rst_n & ~clearInputFIFO),
    .firstTime          (firstTime),

    .NumDimsMinusOne    (TupleNumDimsMinusOne),

	.s_axis_ready       (um_rx_rd_ready),              
	.s_axis_valid       (um_rx_rd_valid), 
	.s_axis_data        (um_rx_data), 

	.m_axis_ready       (in_fifo_ready), 
	.m_axis_valid       (in_fifo_valid), 
	.m_axis_data        (in_fifo_dout) 
	);

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////               Core Pipe                  ////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
  corepipe #(.NUM_CORES(NUM_CORES),
             .NumBitsDimCounterxK(MAX_DIM_BITS))
  corepipe_0(
    .ClkxCI               (clk),
    .RstxRI               (~rst_n),
    .TupleValidxEI        (TupleValidIReg),
    .TupleDataxDI         (TupleDataIReg),
    .TupleNumDimsI        (TupleNumDims[MAX_DIM_BITS-1:0]),
    .TupleDimsCmpsI       (TupleDimsCmpsIReg),
    .TupleValidxEO        (TupleValidO),
    .TupleDataxDO         (TupleDataO),
    .WinTupleValidxEO     (SkylineTupleValid),
    .WinTupleDataxDO      (SkylineTupleData),
    .EmptyxEO             (PipelineEmpty)
  );

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////              Output Buffer                  /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

OutputTupleFilter  #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                     .DIMENSION_WIDTH(DIMENSION_WIDTH),
                     .MAX_DIM_BITS(MAX_DIM_BITS) ) 
  OutputTupleFilter_0(
    .clk                (clk),
    .rst_n              (rst_n & ~clearOutputFIFO),

    .NumDimsMinusOne    (TupleNumDims),
    
    .TupleValid         (TupleValidOReg),
    .TupleData          (TupleDataOReg),
    .FlushTuple         (FlushTuple),
    .FlushTupleASValid  (FlushTupleASValid),

    .FilteredTupleValid (FilteredTupleValid),
    .FilteredTupleData  (FilteredTupleData)
);

SkylineOutputFIFO #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                    .DIMENSION_WIDTH(DIMENSION_WIDTH),
                    .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineOutputFIFO_0(

  .clk                (clk),
  .rst_n              (rst_n & ~clearOutputFIFO),
  .empty              (out_fifo_empty),
  .flush              (flush_out_fifo),

  .NumDimsMinusOne    (TupleNumDims),

  .s_axis_ready       (RequeueTuplesFIFOReady),              
  .s_axis_valid       (FilteredTupleValid), 
  .s_axis_data        (FilteredTupleData), 
  .available_space    (RequeueFIFOSpace),

  .m_axis_ready       (out_fifo_ready), 
  .m_axis_valid       (out_fifo_valid), 
  .m_axis_data        (out_fifo_dout) 
  );

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////           Skyline Tuples Buffer             /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

SkylineOutputFIFO #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                    .DIMENSION_WIDTH(DIMENSION_WIDTH),
                    .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineOutputFIFO_1(

  .clk                (clk),
  .rst_n              (rst_n),
  .empty              (skyline_fifo_empty),
  .flush              (flush_skyline_fifo),

  .NumDimsMinusOne    (TupleNumDims),

  .s_axis_ready       (SkylineTuplesFIFOReady),              
  .s_axis_valid       (SkylineTupleValid), 
  .s_axis_data        (SkylineTupleData), 
  .TuplesCount        (NumberOfSkylineTuples_t),

  .m_axis_ready       (skyline_fifo_ready), 
  .m_axis_valid       (skyline_fifo_valid), 
  .m_axis_data        (skyline_fifo_dout) 
  );
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////               WR TX, RX                  ////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

assign out_fifo_ready      = (skyline_state_fsm != SKYLINE_IDLE) & requeue_tx_wr_ready;
assign skyline_fifo_ready  = (skyline_state_fsm != SKYLINE_IDLE) & skyline_tx_wr_ready;

assign requeue_tx_wr_ready = (~requeue_tx_wr_valid)? 1'b1 : um_tx_wr_ready & ((writer_state == REQUEUE_TUPLE) | ~skyline_tx_wr_valid);
assign skyline_tx_wr_ready = (~skyline_tx_wr_valid)? 1'b1 : um_tx_wr_ready & ((writer_state == SKYLINE_TUPLE) | ~requeue_tx_wr_valid);

always @(posedge clk) begin
    if(~rst_n) begin
        um_tx_wr_addr  <= 0;
        um_tx_data     <= 0;
        um_tx_wr_valid <= 0;
        um_tx_wr_tag   <= 0;

        writer_state   <= REQUEUE_TUPLE;

        requeue_requests  <= 0;
        requeue_responses <= 0;
    end 
    else begin 
    if(um_rx_wr_valid & um_rx_wr_tag[0]) begin
        requeue_responses <= requeue_responses + 1'b1;
    end 
    if( um_tx_wr_ready ) begin
        um_tx_wr_valid <= requeue_tx_wr_valid | skyline_tx_wr_valid;
        um_tx_wr_tag   <= 0;
        if( ((writer_state == REQUEUE_TUPLE) & requeue_tx_wr_valid) | ~skyline_tx_wr_valid  ) begin
            um_tx_wr_addr <= requeue_tx_wr_addr;
            um_tx_data    <= requeue_tx_data;
            um_tx_wr_tag  <= 1;
            writer_state  <= SKYLINE_TUPLE;

            if(requeue_tx_wr_valid) begin
                requeue_requests <= requeue_requests + 1'b1;
            end
        end 
        else begin 
            um_tx_wr_addr <= skyline_tx_wr_addr;
            um_tx_data    <= skyline_tx_data;
            um_tx_wr_tag  <= 2;

            writer_state  <= REQUEUE_TUPLE;
        end
    end 
    end 
end


endmodule //skyline
