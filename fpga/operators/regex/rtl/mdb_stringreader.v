`default_nettype none

module mdb_stringreader  
		#(
		parameter GDK_VAROFFSET=8192, // page size in cache lines
		parameter MAX_OFFSET_CLS = 512
		)
    (
    input wire            clk,
    input wire            rst,

	//control
   input wire					go,
   output reg					done,
	//parameters
	input wire[57:0]			baseAddr, //TODO 48 should be enough
	input wire[57:0]			vbaseAddr,
	input wire[3:0]			tailWidth, //TODO make size consistent
	input wire[31:0]			batCount, //we support up to tailWidth of 4
	 
    output reg           	m_axis_read_req_valid,
	 input wire            	m_axis_read_req_ready,
    output wire[57:0]      m_axis_read_req_addr,
	 output reg					m_axis_read_req_tag, // 0: offset, 1: string

    input wire            	inValid,
    input wire[511:0]     	inData,
	 input wire					inTag, // 0: offset, 1: string

	 
	 output wire			  stringValid, //TODO rename axis style
	 input wire					stringReady,
    output wire[511:0]    stringData,
    output wire 		     stringLast,
	 
	 output reg[31:0]			string_stall_counter,
	 output reg[31:0]			meta_stall_counter
    );    

	localparam IDLE = 0;
	localparam READ_OFFSETS = 1;
	localparam DEQUEUE_OFFSET_LINE	= 2;
	localparam READ_STRINGS = 3;
	localparam GET_STRING	= 4;
	localparam WAIT_DONE		= 5;
	
	reg [3:0]									regState;
	reg [15:0]									remainingWords;
	
	reg [57:0]							regBaseAddr;
	reg [57:0]							regVBaseAddr;
	reg [64:0]							regReadAddr;
	wire[57:0]							regPrevAddr; //TODO rename
	reg [7:0]							regOffsPerCl;
	
	reg [31:0]							offsetCounter;
	reg [31:0]							offsetReqCounter;
	reg [10:0]							fifoInCounter;
	reg [10:0]							fifoOutCounter;
	reg [10:0]							curReqCounter;
	reg [5:0]							offset_jdx;
	reg [511:0]							curStrOffset;
	reg [511:0]							nextStrOffset; //TODO rename heapOffset
	reg [31:0]							strCount;
	reg									regReadStrigsDone;
	reg [1:0]							offsetLines;


	reg									writeMetaEn;
	reg									pushIsFirstLine;
	reg [3:0]								pushOffset;
	reg [7:0]								pushLength;

	wire									readMetaEn;
	wire									popValid;
	wire 									popIsFirst;
	wire [3:0]								popOffset;
	wire [7:0]								popLength;	

	reg [3:0]								curOffset;
	reg [7:0]								curLength;
	reg 									curIsFirst;	

	reg										regShiftIt;
	reg 						            regValid;
   reg[1023:0]   							regData;
	reg [3:0]								regOffsetD;
	reg [3:0]								regOffsetD2;
	//reg [7:0]								regLengthD;
	reg										regLast;


   wire			  						smartshiftOutValid;
   wire[511:0]    					smartshiftOutData;
   wire 		  							smartshiftOutLast;

   reg			  							inValidReg;
   reg[511:0]    							inDataReg;

	 
	reg								axis_wr_offset_valid;
	wire								axis_wr_offset_ready;
	reg[511:0]						axis_wr_offset_data;
	
	reg								fifoReload;

	wire  [8:0]                       gfifo_string_metadata_count;
	reg                               gfifo_string_metadata_almostfull;
	reg  [9:0]                      gfifo_outputPrep_i_count;
	reg										gfifo_outputPrep_i_almostfull;
	
	wire 								axis_rd_offset_valid;
	reg								axis_rd_offset_ready;
	wire[511:0]						axis_rd_offset_data;
    wire  gfifo_outputPrep_i_full;
    wire  gfifo_string_metadata_full;

	 
	assign regPrevAddr = (m_axis_read_req_valid && m_axis_read_req_ready) ? regReadAddr : regPrevAddr;
	assign m_axis_read_req_addr = regReadAddr / 64;
	
	// FIFO to store offsets
	nlb_axififo #(
		.BUS_SIZE_ADDR(9), //TODO maybe use 8
		.BUS_SIZE_DATA(512) //TODO make last optional
	)
	offset_fifo_inst (
		.clk(clk),
		.rst(rst),
		
		.s_axis_valid(axis_wr_offset_valid),
		.s_axis_ready(axis_wr_offset_ready),
		.s_axis_data(axis_wr_offset_data),
		.s_axis_last(1'b0),
		
		.m_axis_valid(axis_rd_offset_valid),
		.m_axis_ready(axis_rd_offset_ready),
		.m_axis_data(axis_rd_offset_data),
		.m_axis_last()
	);


	always @(posedge clk) begin


		if (rst==1) begin
			m_axis_read_req_valid <= 0;
			m_axis_read_req_tag <= 0;
			regState <= IDLE;
			
			regBaseAddr <= 0;
			regVBaseAddr <= 0;
			
			//offsetCounter		<= 0;
			offsetReqCounter	<= 0;
			fifoOutCounter 		<= 0;
			curReqCounter		<= 0;
			offset_jdx <= 0;
			curStrOffset <= 0;
			nextStrOffset <= 0;
			strCount <= 0;
			remainingWords <= 0;
			offsetLines <= 0;
			
			regReadStrigsDone <= 0;	
			
			writeMetaEn <= 0;
			pushIsFirstLine <= 0;
			pushOffset <= 0;
			pushLength <= 0;
			
			//axis_wr_offset_valid <= 0;
			axis_rd_offset_ready <= 0;

		end else begin

			inValidReg <= inValid; //TODO rename Delay
			inDataReg <= inData;
			
			m_axis_read_req_valid <= 0;
			writeMetaEn <= 0; //TODO remove

			//REQUESTING
			case(regState)
				IDLE: begin
					if (go == 1) begin
						regReadStrigsDone <= 0;
						regBaseAddr		<= baseAddr;
						case (tailWidth)
							1: begin
								regVBaseAddr	<= vbaseAddr + GDK_VAROFFSET;
								regOffsPerCl	<= 64;
							end
							2: begin
								regVBaseAddr	<= vbaseAddr + GDK_VAROFFSET;
								regOffsPerCl	<= 32;
							end
							4: begin
								regVBaseAddr	<= vbaseAddr;
								regOffsPerCl	<= 16;
							end
						endcase
						/*if (tailWidth == 1 || tailWidth == 2) begin
							regVBaseAddr	<= vbaseAddr + GDK_VAROFFSET;
						end
						else begin
							regVBaseAddr	<= vbaseAddr;
						end*/
						strCount <= batCount;
						regState <= READ_OFFSETS;			
					end
				end //IDLE
				
				READ_OFFSETS: begin
					//axis_wr_offset_valid <= 0;
					// Check if we read all offsets
					/*if (offsetCounter >= batCount || fifoCounter >= MAX_OFFSET_CLS-1) begin
						offsetLines <= 0;
						
						//insert dummy CL
						axis_wr_offset_valid <= 1;
						axis_wr_offset_data <= 0;
						fifoCounter <= fifoCounter + 1;
						regState <= DEQUEUE_OFFSET_LINE;
					end*/
					
					// Check if we can request more data
					if (offsetReqCounter < (batCount) && curReqCounter < MAX_OFFSET_CLS-1) begin //TODO cleanup
						m_axis_read_req_valid <= 1;
						regReadAddr <= regBaseAddr;
						m_axis_read_req_tag <= 0;
					end
					else begin
						offsetLines <= 0;
						fifoOutCounter <= 0;
						regState <= DEQUEUE_OFFSET_LINE;
					end
					//Check if read request was accepted
					if (m_axis_read_req_valid && m_axis_read_req_ready) begin
						regReadAddr	<= regBaseAddr + 64;
						regBaseAddr <= regBaseAddr + 64;
						offsetReqCounter <= offsetReqCounter + regOffsPerCl; //TODO better implementation
						curReqCounter <= curReqCounter + 1;
						if ((offsetReqCounter + regOffsPerCl) >= (batCount) || (curReqCounter+1) >= MAX_OFFSET_CLS-1) begin
							m_axis_read_req_valid <= 0;
						end
					end
					
					/*if (rdStall==0) begin
						// Check if we have more offsets to read
						if (offsetReqCounter < (batCount) && curReqCounter < MAX_OFFSET_CLS-1) begin //TODO cleanup
							rdEn <= 1;
							rdTag <= 0;
							regReadAddr	<= regBaseAddr;
							regBaseAddr <= regBaseAddr + 64;
							offsetReqCounter <= offsetReqCounter + (64/tailWidth); //TODO better implementation
							curReqCounter <= curReqCounter + 1;
						end
					end //rdStall*/
					
					// Process incoming offsets
					/*if (inValid==1 && inTag==0) begin
						offsetCounter	<= offsetCounter + regOffsPerCl;
						fifoCounter		<= fifoCounter + 1;
						
						// Since we know the capacity of the FIFO we can ignore the ready
						axis_wr_offset_valid <= 1;
						axis_wr_offset_data <= inData;
					end //inValid*/
				end //READ_OFFSETS
				
				DEQUEUE_OFFSET_LINE: begin
					//axis_wr_offset_valid <= 0;
					axis_rd_offset_ready <= 1;
					
					if (axis_rd_offset_valid && axis_rd_offset_ready) begin
						fifoOutCounter <= fifoOutCounter + 1;
						nextStrOffset <= axis_rd_offset_data;
						curStrOffset <= nextStrOffset;
						offsetLines <= offsetLines + 1;
						if (offsetLines == 1) begin
							axis_rd_offset_ready <= 0;
							case (tailWidth)
								2: regReadAddr <= regVBaseAddr + nextStrOffset[15:0];
								4: regReadAddr <= regVBaseAddr + nextStrOffset[31:0];
							endcase
							if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin
								m_axis_read_req_valid <= 1;
								m_axis_read_req_tag <= 1;
							end
							regState <= READ_STRINGS;
						end
					end
					else if (fifoReload) begin
						// GET more offsets
						fifoOutCounter <= 0;
						curReqCounter <= 0;
						axis_rd_offset_ready <= 0;
						regState <= READ_OFFSETS;
					end					
				end //DEQUEUE_OFFSET_LINE	
				READ_STRINGS: begin //TODO rename NEW_STRING
					writeMetaEn <= 0;
					m_axis_read_req_valid <= 0;
					
					// Check if we can request more data
					if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin
						m_axis_read_req_valid <= 1;
						m_axis_read_req_tag <= 1;
						/*case (tailWidth) //TODO maybe remove
							2: regReadAddr <= regVBaseAddr + curStrOffset[15:0];
							4: regReadAddr <= regVBaseAddr + curStrOffset[31:0];
						endcase*/
					end
					
					// Check if request got accepted
					if (m_axis_read_req_valid && m_axis_read_req_ready) begin
						// Depending on the tail width (pointer width) a different case is executed
						case (tailWidth)
							2: begin
								//regReadAddr <= regVBaseAddr + curStrOffset[15:0]; //TODO check SW
								// push meta
								writeMetaEn <= 1; //Write only once
								pushIsFirstLine <= 1;
								pushOffset <= curStrOffset[5:2]; //ignoring lowest 2 bits, because we shift at granularity of 32bits/4bytes
								//TODO maybe make it 0-based, optimize this??
								remainingWords <= (curStrOffset[31:22] - curStrOffset[15:6]);
								pushLength <= (curStrOffset[31:22] - curStrOffset[15:6]) + 1; //ingore lowest 6bits, because we want length in CLs
								offset_jdx <= offset_jdx + 1;
								
								//shift to new offset
								curStrOffset <= {16'h0000,curStrOffset[511:16]};
								regReadAddr <= regVBaseAddr + curStrOffset[31:16];
								// Check if end of cache line or last offset
								if (offset_jdx == 31) begin
									//if at end of CL we need to compute length differently
									remainingWords <= (nextStrOffset[15:6] - curStrOffset[15:6]);
									pushLength <= nextStrOffset[15:6] - curStrOffset[15:6] + 1;
									if (fifoReload == 1) begin
										remainingWords <= 1;
										pushLength <= 2; //TODO these are some assumptions
									end
									offset_jdx <= 0;
									strCount <= strCount - 32;
									//Request new offsetlines
									offsetLines <= 1;
									m_axis_read_req_valid <= 0;
									regState <= DEQUEUE_OFFSET_LINE;
									//TODO move GET_STRING here
								end
								// Check if we requested all strings
								if (offset_jdx == strCount-1) begin
									//set a flag that we are done
									regReadStrigsDone <= 1;
									remainingWords <= 1; //TODO compute this by using the vheap->free pointer
									pushLength <= 2;
									m_axis_read_req_valid <= 0;
									regState <= WAIT_DONE;
								end
								
								// Check if remainingWords, TODO what about last one??
								if (((curStrOffset[31:22] != curStrOffset[15:6]) && offset_jdx != 31) || (offset_jdx == 31 && (nextStrOffset[15:6] != curStrOffset[15:6]))) begin
									//m_axis_read_req_valid <= 0; //TODO improve, req next cache line
									/*if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin //TODO only need address
										m_axis_read_req_valid <= 1;
										m_axis_read_req_tag <= 1;*/
										regReadAddr <= regPrevAddr + 64;
									//end
									regState <= GET_STRING;
								end
							end //case 2
							4: begin
								//regReadAddr <= regVBaseAddr + curStrOffset[31:0]; //TODO check SW
								// push meta
								writeMetaEn <= 1; //Write only once
								pushIsFirstLine <= 1;
								pushOffset <= curStrOffset[5:2]; //ignoring lowest 2 bits, because we shift at granularity of 32bits/4bytes
								//TODO maybe make it 0, optimize this??
								pushLength <= (curStrOffset[63:38] - curStrOffset[31:6]) + 1; //ingore lowest 6bits, because we want length in CLs
								//pushLength <= curStrOffset[31:16] - curStrOffset[15:0];// + 1; //ingore lowest 6bits, because we want length in CLs
								remainingWords <= (curStrOffset[63:38] - curStrOffset[31:6]);
								offset_jdx <= offset_jdx + 1;
								
								//shift to new offset
								curStrOffset <= {32'h0000_0000,curStrOffset[511:32]};
								regReadAddr <= regVBaseAddr + curStrOffset[63:32];
								// Check if end of cache line or last offset
								if (offset_jdx == 15) begin
									//if at end of CL we need to compute length differently
									pushLength <= nextStrOffset[31:6] - curStrOffset[31:6] + 1;
									remainingWords <= (nextStrOffset[31:6] - curStrOffset[31:6]);
									if (fifoReload == 1) begin
										remainingWords <= 1;
										pushLength <= 2; //TODO these are some assumptions
									end
									offset_jdx <= 0;
									strCount <= strCount - 16;
									//Request new offsetlines
									offsetLines <= 1;
									m_axis_read_req_valid <= 0;
									regState <= DEQUEUE_OFFSET_LINE;
									//TODO move GET_STRING here
								end
								// Check if we requested all strings
								if (offset_jdx == strCount-1) begin
									//set a flag that we are done
									regReadStrigsDone <= 1;
									remainingWords <= 1; //TODO compute this by using the vheap->free pointer
									pushLength <= 2;
									m_axis_read_req_valid <= 0;
									regState <= WAIT_DONE;
								end
								
								// Check if remainingWords, TODO what about last one??
								if (((curStrOffset[63:38] != curStrOffset[31:6]) && offset_jdx != 15) || (offset_jdx == 15 && (nextStrOffset[31:6] != curStrOffset[31:6]))) begin
									/*m_axis_read_req_valid <= 0; //TODO improve, req next cache line
									if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin
										m_axis_read_req_valid <= 1;
										m_axis_read_req_tag <= 1;*/
										regReadAddr <= regPrevAddr + 64;
									//end
									regState <= GET_STRING;
								end
							end //case 4
							//TODO
							//2: rdAddr <= vbaseAddr + offsets[offset_idx][15:0];
							//4: rdAddr <= vbaseAddr + offsets[offset_idx][31:0];
							//8: rdAddr <= vbaseAddr + offsets[offset_idx][63:0];
						endcase
					end
				end //READ_STRINGS
				
				GET_STRING: begin
					m_axis_read_req_valid <= 0;
					writeMetaEn <= 0;
					
					//Check if we can make a read request
					if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin
						m_axis_read_req_valid <= 1;
						m_axis_read_req_tag <= 1;
						//regReadAddr <= regPrevAddr + 64;
					end
					
					//Check if read request got accepted
					if (m_axis_read_req_valid && m_axis_read_req_ready) begin
						regReadAddr <= regPrevAddr + 64;
						writeMetaEn <= 1;
						pushIsFirstLine <= 0;
						pushOffset <= pushOffset;
						pushLength <= remainingWords;
						remainingWords <= remainingWords -1;
						if (remainingWords == 1) begin
							//m_axis_read_req_valid <= 0;
							//regState <= READ_STRINGS;
							//Check if this was the last string
							if (regReadStrigsDone == 1) begin
								m_axis_read_req_valid <= 0;
								regState <= WAIT_DONE;
							end
							//Check if we need another offset line
							else if (offsetLines == 1) begin
								m_axis_read_req_valid <= 0;
								regState <= DEQUEUE_OFFSET_LINE;
							end
							// Read more Strings
							else begin
								/*if (~gfifo_outputPrep_i_almostfull && ~gfifo_string_metadata_almostfull) begin
									m_axis_read_req_valid <= 1;
									m_axis_read_req_tag <= 1;*/
									case (tailWidth) //TODO maybe remove
										2: regReadAddr <= regVBaseAddr + curStrOffset[15:0];
										4: regReadAddr <= regVBaseAddr + curStrOffset[31:0];
									endcase
								//end
								regState <= READ_STRINGS;
							end
						end
					end //check accept
				end //GET_STRING
				WAIT_DONE: begin
					m_axis_read_req_valid <= 0;
					writeMetaEn <= 0;
					if (done == 1) begin
						//regState <= IDLE;
					end
				end
			endcase
		end
	end
	
	//localparam IDLE = 0; //already defined
	localparam LOAD = 1;
	reg fifoFsmState;
	
	always @(posedge clk) begin
		if (rst == 1) begin
			fifoReload <= 0;
			fifoFsmState <= 0;
			offsetCounter <= 0;
			fifoInCounter <= 0;
			axis_wr_offset_valid <= 0;
			axis_wr_offset_data <= 0;
		end
		else begin
			//Counter
			/*if (inValid==1 && inTag==0 && axis_rd_offset_valid && axis_rd_offset_ready) begin
				fifoCounter <= fifoCounter;
			end
			else*/ /*if (inValid==1 && inTag==0) begin
				fifoInCounter <= fifoInCounter + 1;
			end*/
			/*else if (axis_rd_offset_valid && axis_rd_offset_ready) begin
				fifoCounter <= fifoCounter - 1;
			end*/
			axis_wr_offset_valid <= 0;
			
			case(fifoFsmState)
				IDLE: begin
					fifoReload <= (fifoInCounter == fifoOutCounter);
					if (regState == READ_OFFSETS) begin
						fifoReload <= 0;
						fifoInCounter <= 0;
						fifoFsmState <= LOAD;
					end
				end//IDLE
				LOAD: begin
					if (offsetCounter >= batCount || fifoInCounter >= MAX_OFFSET_CLS-1) begin
						//offsetLines <= 0;
						
						//insert dummy CL
						axis_wr_offset_valid <= 1;
						axis_wr_offset_data <= 0;
						fifoInCounter <= fifoInCounter + 1;
						//fifoLoaded <= 1;
						fifoFsmState <= IDLE;
						//regState <= DEQUEUE_OFFSET_LINE;
					end
					
					//Check if we got a new offset cache line
					if (inValid==1 && inTag==0) begin
						offsetCounter	<= offsetCounter + regOffsPerCl;
						fifoInCounter		<= fifoInCounter + 1;
						
						// Since we know the capacity of the FIFO we can ignore the ready
						axis_wr_offset_valid <= 1;
						axis_wr_offset_data <= inData;
					end //inValid
				end//LOAD
			endcase
		end
	end //always
	
	//circuit to count when output items and indicate when we are done
	/*reg [15:0] outputCount;
	always @(posedge clk) begin
		if (rst == 1 || regState == IDLE) begin
			done <= 0;
			outputCount <= 0;
		end
		else begin
			if (stringValid == 1 && stringReady == 1) begin
				outputCount <= outputCount+1;
				//check if we wrote all results out, 32 results per CL
				if (outputCount == (batCount/32)) begin
					done <= 1;
				end
			end
		end
	end //end always*/
	
	//logic to read out meta data when strings are coming in
	assign readMetaEn = inValid & inTag;
	
	always @(posedge clk) begin
		if (rst == 1) begin
			regValid <= 0;
			regData <= 0;
			regShiftIt <= 0;

			gfifo_string_metadata_almostfull <= 0;
		end
		else begin
			regValid <= 0;
			regShiftIt <= 0;

			gfifo_string_metadata_almostfull <= ({1'b0, gfifo_string_metadata_count} >= (10'd508));
			
			//metadata, offsetD2 shift by 1 since we're now smartshifting by 64
			regOffsetD2 <= {1'b0, regOffsetD[3:1]};
			regLast <= regShiftIt;
			
			if (inValidReg == 1 && popValid == 1) begin
				regValid <= (popIsFirst == 0 || regShiftIt);
				regShiftIt <= (popLength == 1);
				regData <= {inDataReg,regData[1023:512]};
				regOffsetD <= popOffset;
			end
			else if (regShiftIt == 1) begin
				regValid <= 1;
				regData <= {inDataReg,regData[1023:512]};
			end
		end
	end //always

	// can align at 32bit granularity
	// always have to insert current and next cache line
	pg_smartshifter shifter_i (
		.clk(clk),
		.rst(rst),

		.inValid(regValid),
		.inLast(regLast),
		//TODO what if a word has no real value, only garbage, we have to purge it in the rem module!!
		.inOffs(regOffsetD2),
		.inData(regData),

		.outValid(smartshiftOutValid),   
		.outLast(smartshiftOutLast),  
		.outData(smartshiftOutData)    
	);

	// Store meta data while waiting for data to come back
	wire metaEmpty; //for debug
	//TODO meta full
	nlb_gfifo_v #(
	 	.BUS_SIZE_ADDR(9), //TODO
	 	.BUS_SIZE_DATA(13)
	 	) 
 	gfifo_string_metadata (
	 	.rst_x(!rst),       // input   reset, reset polarity defined by SYNC_RESET_POLARITY
      .clk(clk),         // input   clock
		//meta input
		.wr_data({pushOffset,pushLength,pushIsFirstLine}),
		.wr_en(writeMetaEn),
		.overflow(),     // input   write data with configurable width
		//meta output
 	    .rd_en(readMetaEn),       // input   read enable
       .rd_data({popOffset,popLength,popIsFirst}),     // output  read data with configurable width
       .valid(popValid),       // output  active valid indicate valid read data
       .underflow(),   // output  underflow being asserted indicates one unsuccessfully read
       
		 .empty(metaEmpty),       // output  FIFO empty
       .full(gfifo_string_metadata_full),        // output  FIFO full
       .count(gfifo_string_metadata_count),       // output  FIFOcount
       .prog_full()
   );

	// Convert FIFO to AxiStream
	// TODO use axi_fifo
	wire						readStringEn;
	wire						readStringValid;
	wire[511:0]				readStringData;
	//reg[511:0]				readStringDataReg;
	wire						readStringLast;
	//reg						readStringLastReg;
 	wire						readStringEmpty;
	//reg						stringPending;
	
	/*assign stringData = (readStringValid) ? readStringData : readStringDataReg;
	assign stringLast = (readStringValid) ? readStringLast : readStringLastReg;
	assign stringValid = (readStringValid | stringPending);
	assign readStringEn = (~readStringEmpty & stringReady);*/

	
	
	/*wire fifo2register_valid;
	wire fifo2register_ready;
	wire[511:0] fifo2register_data;
	wire fifo2register_last;
	
	nlb_axififo #(
		.BUS_SIZE_ADDR(9), //TODO maybe use 8
		.BUS_SIZE_DATA(512) //TODO make last optional
	)
	string_fifo_inst (
		.clk(clk),
		.rst(rst),
		
		.s_axis_valid(smartshiftOutValid),
		.s_axis_ready(),
		.s_axis_data(smartshiftOutData),
		.s_axis_last(smartshiftOutLast),
		
		.m_axis_valid(fifo2register_valid),
		.m_axis_ready(fifo2register_ready),
		.m_axis_data(fifo2register_data),
		.m_axis_last(fifo2register_last),
		
		.data_count(gfifo_outputPrep_i_count)
	);
	
	
	axis_register #(
		.DATA_WIDTH(513)
	) axis_register_inst (
		.clk(clk),
		.rst(rst),
		
		.input_axis_tvalid(fifo2register_valid),
		.input_axis_tready(fifo2register_ready),
		.input_axis_tdata({fifo2register_data,fifo2register_last}),
		//.s_axis_last(), //TODO
		
		.output_axis_tvalid(stringValid),
		.output_axis_tready(stringReady),
		.output_axis_tdata({stringData,stringLast})
		//.m_axis_last() //TODO
	);*/

	//TODO check for overflow
 	nlb_gfifo_v #(
	 	.BUS_SIZE_ADDR(9), //TODO how many can be in flight??
	 	.BUS_SIZE_DATA(512+1)
	 	) 
 	gfifo_outputPrep_i (
	 	.rst_x(!rst),       // input   reset, reset polarity defined by SYNC_RESET_POLARITY
      .clk(clk),         // input   clock
		  //WRITE
		.wr_data({smartshiftOutLast,smartshiftOutData}),
		.wr_en(smartshiftOutValid),
		.overflow(),     // input   write data with configurable width
		//READ
 	   .rd_en(readStringEn),       // input   read enable
		.rd_data({readStringLast,readStringData}),
		.valid(readStringValid), //TODO
      .underflow(),   // output  underflow being asserted indicates one unsuccessfully read
      .empty(readStringEmpty),       // output  FIFO empty
      
		.full(gfifo_outputPrep_i_full),        // output  FIFO full
      .count(),       // output  FIFOcount
      .prog_full()
	);
	
	fifo_to_axis #(
		.Width(513) //TODO make uppercase
	) axis_register_inst (
		.clk(clk),
		.rst(rst),
		
		.input_read(readStringEn),
		.input_empty(readStringEmpty),
		.input_data({readStringData,readStringLast}),
		
		.M_AXIS_TVALID(stringValid),
		.M_AXIS_TREADY(stringReady),
		.M_AXIS_TDATA({stringData,stringLast})
	);
	
	/*always @(posedge clk) begin
		if (rst == 1) begin
			stringPending <= 0;
			readStringDataReg <= 0;
			readStringLastReg <= 0;
		end
		else begin
			stringPending <= stringPending;
			//Chech if new string got accepted
			if (readStringValid && ~stringReady) begin
				stringPending <= 1;
				readStringDataReg <= readStringData;
				readStringLastReg <= readStringLast;
			end
			if (stringReady && stringPending && ~readStringValid) begin
				stringPending <= 0;
			end
		end
	end*/
	
	always @(posedge clk) begin
		if (rst == 1) begin
			gfifo_outputPrep_i_almostfull <= 0;
			gfifo_outputPrep_i_count <= 0;
		end
		else begin
			gfifo_outputPrep_i_almostfull <= (gfifo_outputPrep_i_count > 10'd128);
			
			if (stringValid && stringReady && smartshiftOutValid) begin
				gfifo_outputPrep_i_count <= gfifo_outputPrep_i_count;
			end
			else if (stringValid && stringReady) begin //COUld use readStringValid
				gfifo_outputPrep_i_count <= gfifo_outputPrep_i_count - 1;
			end
			else if (smartshiftOutValid) begin
				gfifo_outputPrep_i_count <= gfifo_outputPrep_i_count + 1;
			end
		end
	end
	
	reg prevGo;
	always @(posedge clk) begin
		prevGo <= go;
		if (!prevGo && go) begin
			meta_stall_counter <= 0;
			string_stall_counter <= 0;
		end
		else begin
			if (gfifo_string_metadata_almostfull) begin
				meta_stall_counter <= meta_stall_counter + 1;
			end
			if (gfifo_outputPrep_i_almostfull) begin
				string_stall_counter <= string_stall_counter + 1;
			end
		end
	end
	
endmodule

`default_nettype wire
