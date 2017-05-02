/*
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 *
 * This hardware operator is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


`include "framework_defines.vh"

module skyline_wide #(parameter NUM_DIMENSIONS  = 7,
                      parameter DIMENSION_WIDTH = 32,
                      parameter MAX_DIM_BITS    = 3)(
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

localparam NUM_CORES = 128;

localparam BACKPRESSURE_THRESHOLD_REQUEUE_FIFO = 128;

localparam NUM_DIMENSIONS_WITH_INDEX = NUM_DIMENSIONS + 1;
//////////////////////////////////////////////////////////////////////////////////
reg   [2:0]                                     skyline_state_fsm      = 0;
     

reg   [31:0]                                    ReadTuplesCount        = 0;    // Counts number of tuples we read from the input fifo and insert in the pipeline
reg   [31:0]                                    WriteTuplesCount       = 0;    // Counts the number of valid tuples we get from the pipeline and requeue them

reg   [MAX_DIM_BITS-1:0]                        TupleRdTXDimCnt        = 0;    // Iterates over the dimensions when generating read requests
reg   [MAX_DIM_BITS-1:0]                        TupleWrTXDimCnt        = 0;    // Iterates over the dimensions when requeueing the tuples
reg   [MAX_DIM_BITS-1:0]                        SkylineWrTXDimCnt      = 0;    // Iterates over the dimensions when writing skyline tuples

reg   [31:0]                                    TuplesInMemory         = 0;    // Number of Tuples in the Main memory for the current iteration
reg   [31:0]                                    NumberOfTuples         = 0;    // Initial number of tuples in main memory
reg   [NUM_DIMENSIONS-1:0]                      TupleDimMaskIReg       = 0;
reg   [NUM_DIMENSIONS-1:0]                      TupleDimComparisonIReg = 0;
reg   [MAX_DIM_BITS-1:0]                        TupleNumDimsMinusOne   = 0;

reg   [DIMENSION_WIDTH-1:0]                     TupleDataIReg[NUM_DIMENSIONS-1:0];    // Register input tuple before entering the pipeline (Data word)
reg                                             TupleValidIReg         = 0;           // Register input tuple before entering the pipeline (Valid bit)
reg   [31:0]                                    TupleIndexIReg         = 0;
reg                                             TupleTimeFlagIReg      = 0;

reg                                             TupleValidOReg         = 0;           // Register output tuple coming out of the pipeline (Valid bit)  
reg   [DIMENSION_WIDTH-1:0]                     TupleDataOReg[NUM_DIMENSIONS_WITH_INDEX-1:0];    // Register output tuple coming out of the pipeline (Data word)  

wire                                            TupleValidO;                          // Output tuple coming out of the pipeline (Valid bit)  
wire  [DIMENSION_WIDTH-1:0]                     TupleDataO[NUM_DIMENSIONS-1:0];       // Output tuple coming out of the pipeline (Data word)  
wire  [31:0]                                    TupleIndexO;

// Skyline Tuple coming out of the pipeline
wire  [DIMENSION_WIDTH-1:0]                     SkylineTupleData[NUM_DIMENSIONS-1:0];
wire  [DIMENSION_WIDTH-1:0]                     SkylineTupleDataWithIndex[NUM_DIMENSIONS_WITH_INDEX-1:0];
wire                                            SkylineTupleValid;
wire  [31:0]                                    SkylineTupleIndex;
wire                                            PipelineEmpty;          // The pipeline is flushed of all skyline tuples

reg                                             ReadingSkylineTuples = 0;

reg                                             iteration_rd_done;        // Flag indicating if reading tuples from main memory is done for current iteration
reg                                             EmptyingCorePipe;         // Flag indicating if we waiting for the pipeline process all in fly tuples (set after last tuple enter the pipeline)
reg   [31:0]                                    WaitCorePipeCycles;       // A predefined number of cycles waiting for the pipeline to become empty of in fly tuples
reg                                             flush_out_fifo;           // Flush all tuples still in the output fifo
reg                                             flush_skyline_fifo;       // Flush all tuples still in the skyline tuples fifo


reg   [57:0]                                    dim_base[NUM_DIMENSIONS_WITH_INDEX-1:0];          // Base address for every input dimension (set from um_params)
reg   [31:0]                                    dim_rd_offset[NUM_DIMENSIONS_WITH_INDEX-1:0];     // offsets incremented while reading dimensions from main memory (in cacheline increments)
reg   [31:0]                                    dim_wr_offset[NUM_DIMENSIONS_WITH_INDEX-1:0];     // offsets incremented while writing (requeuing) dimensions to main memory (in cacheline increments)

reg   [57:0]                                    skyline_base[NUM_DIMENSIONS_WITH_INDEX-1:0];      // Base address for every skyline dimension (set from um_params)
reg   [31:0]                                    skyline_wr_offset[NUM_DIMENSIONS_WITH_INDEX-1:0]; // offsets incremented while writing skyline dimensions from main memory (in cacheline increments)
reg   [31:0]                                    rd_offset_limit;                       // Upper limit for offset increments (in cacheline increments)

//- TX WR channel for requeueing tuples
reg                                             requeue_tx_wr_valid;
wire                                            requeue_tx_wr_ready;
reg   [57:0]                                    requeue_tx_wr_addr;
reg   [511:0]                                   requeue_tx_data;

// TX WR channel for writing skyline tuples 
reg                                             skyline_tx_wr_valid;
wire                                            skyline_tx_wr_ready;
reg   [57:0]                                    skyline_tx_wr_addr;
reg   [511:0]                                   skyline_tx_data;

// Input FIFO output signals
wire                                            in_fifo_ready;
wire                                            in_fifo_valid;
wire  [DIMENSION_WIDTH-1:0]                     in_fifo_dout[NUM_DIMENSIONS_WITH_INDEX-1:0];

// Output FIFO signals
wire                                            out_fifo_empty;
wire                                            out_fifo_ready;
wire                                            out_fifo_valid;
wire  [511:0]                                   out_fifo_dout;

wire                                            skyline_fifo_empty;
wire                                            skyline_fifo_ready;
wire                                            skyline_fifo_valid;
wire  [511:0]                                   skyline_fifo_dout;

reg                                             writer_state = 0;
reg                                             Activated    = 0;
reg                                             clearInputFIFO = 0;
reg                                             clearOutputFIFO = 0;

//- Statistics Counters
wire  [31:0]                                    NumberOfSkylineTuples_t;
reg   [31:0]                                    NumberOfSkylineTuples = 0;
reg   [31:0]                                    NumberOfIterations    = 0;
reg   [31:0]                                    requeue_requests      = 0;
reg   [31:0]                                    requeue_responses     = 0;

reg   [15:0]                                    IterationCount;

reg   [31:0]                                    StalledInputCounter    = 0;
reg   [31:0]                                    RequeueFIFOFullCounter = 0;
reg   [31:0]                                    ActiveCycles           = 0;
reg   [31:0]                                    ReadingDimsCycles      = 0;
reg   [31:0]                                    starvingCycles         = 0;

wire  [11:0]                                    RequeueFIFOSpace;
wire                                            waitForSpaceInRequeueFIFO;


////////////////////////////////////////////////////////////////////////////////////////////////////
genvar j;
integer i;

////////////////////////////////////////////////////////////////////////////////////////////////////
assign um_state_counters_valid = 1'b0;
assign um_state_counters       = {//{((`NUM_USER_STATE_COUNTERS-3)*32){1'b0}},
                                  StalledInputCounter,
                                  RequeueFIFOFullCounter,
                                  ActiveCycles,
                                  ReadingDimsCycles, 
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
    end
end
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////             Register Parameters             /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
generate for(j=0; j < NUM_DIMENSIONS_WITH_INDEX; j= j+1) begin: configPtrs

always @(posedge clk) begin
    if(~rst_n) begin
        dim_base[j]     <= 0;
        skyline_base[j] <= 0;
    end 
    else begin 
        if(start_um) begin
            dim_base[j]     <= um_params[j*64+63 : j*64 + 6];
            skyline_base[j] <= um_params[j*64+63 + NUM_DIMENSIONS_WITH_INDEX*64: j*64 + NUM_DIMENSIONS_WITH_INDEX*64 + 6];
        end
    end
end
end 
endgenerate

always @(posedge clk) begin
    if(~rst_n) begin
        NumberOfTuples         <= 0;
        Activated              <= 0;

        TupleDimMaskIReg       <= 0;
        TupleNumDimsMinusOne   <= 0;
        TupleDimComparisonIReg <= 0;
    end 
    else begin 
        Activated       <= 1'b0;
        if(start_um) begin
            NumberOfTuples         <= um_params[1055: 1024];
            TupleDimMaskIReg       <= um_params[1055+NUM_DIMENSIONS : 1056];
            TupleNumDimsMinusOne   <= um_params[1087+MAX_DIM_BITS   : 1088];
            TupleDimComparisonIReg <= um_params[1119+NUM_DIMENSIONS : 1120];

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
assign in_fifo_ready = (skyline_state_fsm == SKYLINE_0) & ~waitForSpaceInRequeueFIFO;

assign waitForSpaceInRequeueFIFO = RequeueFIFOSpace < BACKPRESSURE_THRESHOLD_REQUEUE_FIFO;

always @(posedge clk) begin
	if(~rst_n) begin
        skyline_state_fsm  <= 0;

        ReadTuplesCount    <= 0;
        WriteTuplesCount   <= 0;
        TupleRdTXDimCnt    <= 0;

        TupleValidIReg     <= 1'b0;
        TupleTimeFlagIReg  <= 1'b0;

        EmptyingCorePipe   <= 1'b0;
        WaitCorePipeCycles <= 0;

        TupleValidOReg     <= 1'b0;
                
        TupleIndexIReg     <= 0;        

        TuplesInMemory     <= 0;

        um_tx_rd_valid     <= 0;
        um_tx_rd_addr      <= 0;
        um_tx_rd_tag       <= 0;
        iteration_rd_done  <= 0;

        for(i=0; i < NUM_DIMENSIONS; i=i+1) begin 
            TupleDataIReg[i]     <= 0;
        end

        for(i=0; i < NUM_DIMENSIONS_WITH_INDEX; i=i+1) begin 
            dim_rd_offset[i]     <= 0;
            TupleDataOReg[i]     <= 0;
        end

        flush_out_fifo     <= 0;
        flush_skyline_fifo <= 0;
        
        um_done            <= 1'b0;

        clearInputFIFO     <= 1'b0;
        clearOutputFIFO    <= 1'b0;

        NumberOfIterations    <= 0;
        NumberOfSkylineTuples <= 0;

        ReadingSkylineTuples  <= 0;

        IterationCount        <= 0;

	end 
	else begin
		
		case (skyline_state_fsm)

            SKYLINE_IDLE: begin

                if(Activated) begin 
                    skyline_state_fsm     <= SKYLINE_0;
                    NumberOfIterations    <= 0;
                    NumberOfSkylineTuples <= 0;
                end 
                    
                um_done            <= 1'b0;
                //------------------- Reset FSM Variables ---------------------//
                ReadTuplesCount    <= 0;
                WriteTuplesCount   <= 0;

                TupleValidIReg     <= 1'b0;
                TupleTimeFlagIReg  <= 1'b0;
                TupleIndexIReg     <= 0;

                for(i=0; i < NUM_DIMENSIONS; i=i+1) begin 
                    TupleDataIReg[i]     <= 0;
                    TupleDataOReg[i]     <= 0;
                end

                TupleRdTXDimCnt    <= 0;

                EmptyingCorePipe   <= 1'b0;
                WaitCorePipeCycles <= 0;

                TupleValidOReg     <= 1'b0;

                TuplesInMemory     <= NumberOfTuples;

                if( NumberOfTuples[3:0] > 0 ) begin
                    rd_offset_limit  <= NumberOfTuples[31:4];
                end 
                else begin 
                    rd_offset_limit  <= NumberOfTuples[31:4] - 1;
                end

                
                ReadingSkylineTuples  <= 0;

                IterationCount        <= 0;
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

                        um_tx_rd_addr  <= dim_base[ TupleRdTXDimCnt ] + dim_rd_offset[TupleRdTXDimCnt];
                        um_tx_rd_tag   <= 0;

                        for(i = 0; i < NUM_DIMENSIONS_WITH_INDEX; i=i+1) begin 
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
                end
            //---------------------------------------------------------------------------------------------//
			//----------------------------------- Input FIFO to core pipe ---------------------------------//
            //---------------------------------------------------------------------------------------------//
				TupleValidIReg   <= 1'b0;
                clearInputFIFO   <= 1'b0;
                
                //- When we push the last tuple dim in the core pipeline, we start waiting 
                // for the pipeline to empty.
                if(ReadTuplesCount == TuplesInMemory) begin 
                    EmptyingCorePipe   <= 1'b1;
                    WaitCorePipeCycles <= 1;
                    ReadTuplesCount    <= 0;
                    clearInputFIFO     <= 1'b1;
                end

				if(~waitForSpaceInRequeueFIFO) begin

                    if((ReadTuplesCount != TuplesInMemory) & ~EmptyingCorePipe) begin
                        if(in_fifo_valid) begin
                            ReadTuplesCount <= ReadTuplesCount + 1'b1;
                            TupleValidIReg  <= 1'b1;
                        end
                    end 
                    
                    TupleDataIReg   <= in_fifo_dout[NUM_DIMENSIONS_WITH_INDEX-1:1];
                    TupleIndexIReg  <= in_fifo_dout[0];
                end

                
            //---------------------------------------------------------------------------------------------//
            //--------------------------------- Core pipe to Output FIFO ----------------------------------//
            //---------------------------------------------------------------------------------------------//
                TupleValidOReg    <= TupleValidO;

                TupleDataOReg[NUM_DIMENSIONS_WITH_INDEX-1:1]  <= TupleDataO;
                TupleDataOReg[0]                              <= TupleIndexO;

                if( TupleValidO ) begin 
                    WriteTuplesCount  <= WriteTuplesCount + 1;
                end
            //---------------------------------------------------------------------------------------------//
            //---------------------------------- Check if Pipeline Empty ----------------------------------//
            //---------------------------------------------------------------------------------------------//
                if(EmptyingCorePipe) begin 
                    WaitCorePipeCycles <= WaitCorePipeCycles + 1;
                end
                if(WaitCorePipeCycles == NUM_CORES*2) begin 
                    skyline_state_fsm    <= SKYLINE_1;
                    flush_out_fifo       <= 1'b1;

                   // ReadingSkylineTuples <= 1'b1;

                    NumberOfIterations   <= NumberOfIterations + 1'b1;

                    IterationCount       <= IterationCount + 1'b1;
                end
			end

            //#############################################################################################// 
            SKYLINE_1: begin 

            //---------------------------------------------------------------------------------------------//
            //------------------------------------ Reset FSM Variables ------------------------------------//
            //---------------------------------------------------------------------------------------------//
                ReadTuplesCount  <= 0;

                TupleValidIReg   <= 1'b0;
                for(i=0; i < NUM_DIMENSIONS; i=i+1) begin 
                    TupleDataIReg[i]     <= 0;
                    TupleDataOReg[i]     <= 0;
                end

                EmptyingCorePipe <= 1'b0;

                TupleValidOReg   <= 1'b0;

                iteration_rd_done <= 0;

                if( WriteTuplesCount[3:0] > 0 ) begin
                    rd_offset_limit  <= WriteTuplesCount[31:4];
                end 
                else begin 
                    rd_offset_limit  <= WriteTuplesCount[31:4] - 1;
                end
                
                TuplesInMemory   <= WriteTuplesCount;
            
            //---------------------------------------------------------------------------------------------//
            //----------------------------- Change state when output fifo is empty ------------------------//
            //---------------------------------------------------------------------------------------------//
                if(out_fifo_empty) begin 
                    flush_out_fifo  <= 1'b0;
                    clearOutputFIFO <= 1'b1;
                    if( ~requeue_tx_wr_valid ) begin
                        if(requeue_requests == requeue_responses ) begin 
                            if( WriteTuplesCount > 0 ) begin 
                                skyline_state_fsm <= SKYLINE_0;
                                WriteTuplesCount  <= 0;
                                TupleTimeFlagIReg <= ~TupleTimeFlagIReg;
                            end
                            else begin 
                                skyline_state_fsm    <= SKYLINE_FLUSH;
                                ReadingSkylineTuples <= 1'b1;
                            end
                        end
                    end
                end
            end

            //#############################################################################################// 
            SKYLINE_FLUSH: begin 

                clearOutputFIFO <= 1'b0;

                if(PipelineEmpty) begin 

                    ReadingSkylineTuples <= 1'b0;

                    skyline_state_fsm    <= SKYLINE_TERMINATE;
                    flush_skyline_fifo   <= 1'b1;
                end
            end
            //#############################################################################################// 
            SKYLINE_TERMINATE: begin 

                NumberOfSkylineTuples <= NumberOfSkylineTuples_t;
                //
                if( skyline_fifo_empty ) begin
                    skyline_state_fsm    <= SKYLINE_IDLE;

                    um_done              <= 1'b1;
                    flush_skyline_fifo   <= 1'b0;
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
SkylineInputFIFO_wide_full  #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                         .DIMENSION_WIDTH(DIMENSION_WIDTH),
                         .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineInputFIFO_0(

	.clk                (clk),
	.rst_n              (rst_n & ~clearInputFIFO),

    .DimsMask           ({TupleDimMaskIReg,1'b1}),
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
  corepipe_wide #(.DIMENSION_WIDTH(DIMENSION_WIDTH),
                  .MAX_NUM_DIMENSIONS(NUM_DIMENSIONS),
                  .NUM_CORES(NUM_CORES) )
  corepipe_0(
    .clk                  (clk),
    .rst_n                (rst_n),

    .TupleDataI           (TupleDataIReg),
    .TupleIndexI          (TupleIndexIReg),
    .TupleRoundI          (IterationCount),
    .TupleDimMaskI        (TupleDimMaskIReg),
    .TupleDimComparisonI  (TupleDimComparisonIReg),
    .TupleValidI          (TupleValidIReg),

    .TupleDataO           (TupleDataO),
    .TupleIndexO          (TupleIndexO),
    .TupleValidO          (TupleValidO),

    .pipelineEmpty        (PipelineEmpty),

    .SkylineTupleDataO    (SkylineTupleData),
    .SkylineTupleIndexO   (SkylineTupleIndex),
    .SkylineTupleValidO   (SkylineTupleValid),

    .ReadingSkylineTuples (ReadingSkylineTuples)
  );

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////                            //////////////////////////////////
//////////////////////////////              Output Buffer                  /////////////////////////
//////////////////////////////////////                            //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


SkylineOutputFIFO_wide #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                         .DIMENSION_WIDTH(DIMENSION_WIDTH),
                         .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineOutputFIFO_0(

  .clk                (clk),
  .rst_n              (rst_n & ~clearOutputFIFO),
  .empty              (out_fifo_empty),
  .flush              (flush_out_fifo),

  .NumDimsMinusOne    (TupleNumDimsMinusOne),

  .s_axis_ready       (),              
  .s_axis_valid       (TupleValidOReg), 
  .s_axis_data        (TupleDataOReg), 
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

assign SkylineTupleDataWithIndex[0]                             = SkylineTupleIndex;
assign SkylineTupleDataWithIndex[NUM_DIMENSIONS_WITH_INDEX-1:1] = SkylineTupleData;

SkylineOutputFIFO_wide #(.NUM_DIMENSIONS(NUM_DIMENSIONS_WITH_INDEX),
                         .DIMENSION_WIDTH(DIMENSION_WIDTH),
                         .MAX_DIM_BITS(MAX_DIM_BITS) )
 SkylineOutputFIFO_1(

  .clk                (clk),
  .rst_n              (rst_n),
  .empty              (skyline_fifo_empty),
  .flush              (flush_skyline_fifo),

  .NumDimsMinusOne    (TupleNumDimsMinusOne),

  .s_axis_ready       (),              
  .s_axis_valid       (SkylineTupleValid), 
  .s_axis_data        (SkylineTupleDataWithIndex), 
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

always @(posedge clk) begin
    if(~rst_n) begin
        requeue_tx_wr_valid    <= 1'b0;
        requeue_tx_data        <= 0;
        requeue_tx_wr_addr     <= 0;

        skyline_tx_wr_valid    <= 1'b0;
        skyline_tx_data        <= 0;
        skyline_tx_wr_addr     <= 0;

        SkylineWrTXDimCnt      <= 0;
        TupleWrTXDimCnt        <= 0;

        for(i=0; i < NUM_DIMENSIONS_WITH_INDEX; i=i+1) begin 
            dim_wr_offset[i]     <= 0;
            skyline_wr_offset[i] <= 0;
        end
    end 
    else begin
        //---------------------------------------------------------------------------------------------//
        //---------------------------------- Requeue Tuples to Main Memory ----------------------------//
        //---------------------------------------------------------------------------------------------//
        if( requeue_tx_wr_ready) begin 
            requeue_tx_wr_valid <= 1'b0;
            if(out_fifo_valid) begin
                requeue_tx_wr_valid    <= 1'b1;
                requeue_tx_data       <= out_fifo_dout;
                requeue_tx_wr_addr     <= dim_base[ TupleWrTXDimCnt ] + dim_wr_offset[ TupleWrTXDimCnt ];

                        
                dim_wr_offset[ TupleWrTXDimCnt ] <= dim_wr_offset[ TupleWrTXDimCnt ] + 1; // CL increments

                if(TupleWrTXDimCnt == TupleNumDimsMinusOne) begin 
                    TupleWrTXDimCnt <= 0;
                end
                else begin 
                    TupleWrTXDimCnt <= TupleWrTXDimCnt + 1;
                end
            end
        end

        if(out_fifo_empty & (skyline_state_fsm == SKYLINE_1)) begin 
            for(i = 0; i < NUM_DIMENSIONS_WITH_INDEX; i=i+1) begin
                dim_wr_offset[i] <= 0;
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
                skyline_tx_wr_addr    <= skyline_base[ SkylineWrTXDimCnt ] + skyline_wr_offset[ SkylineWrTXDimCnt ];

                skyline_wr_offset[ SkylineWrTXDimCnt ] <= skyline_wr_offset[ SkylineWrTXDimCnt ] + 1; // CL increments

                if(SkylineWrTXDimCnt == TupleNumDimsMinusOne) begin 
                    SkylineWrTXDimCnt     <= 0;
                end
                else begin 
                    SkylineWrTXDimCnt <= SkylineWrTXDimCnt + 1;
                end
            end
        end

    end
end

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
