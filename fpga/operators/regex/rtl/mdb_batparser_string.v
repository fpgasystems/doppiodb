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

`default_nettype none

module mdb_batparser_string 
(
       input wire		clk,
       input wire		Clk_400,
       input wire		rst,

		 input wire						go,
		 output reg						done,
		 // WRITE
       output reg						m_axis_write_req_valid,                     //                       arb:               write enable
       input wire						m_axis_write_req_ready,                //                       arb:               write fifo almost full
       output reg[57:0]				m_axis_write_req_addr,                   // [ADDR_LMT-1:0]        arb:               write address
       output reg[511:0]			m_axis_write_req_data,                    // [511:0]               arb:               Cache line data
		 
		 // READ
		 output reg						m_axis_read_req_valid,
		 input wire						m_axis_read_req_ready,
		 output reg[57:0]				m_axis_read_req_addr,
		 output reg						m_axis_read_req_tag,
		 
		 input wire						s_axis_read_rsp_valid,
		 output reg						s_axis_read_rsp_ready,
		 input wire[511:0]			s_axis_read_rsp_data,
		 input wire						s_axis_read_rsp_tag,

       input wire[31:0]				re2xy_BatCount,                 // [31:0]                requestor:         number of cache lines
		 input wire[57:0]				re2xy_BaseAddr,
		 input wire[57:0]				re2xy_VBaseAddr,
		 input wire[7:0]				re2xy_TailWidth,

       output reg[255:0]			l12ab_ErrorInfo,                // [255:0]               arb:               error information
       output reg						l12ab_ErrorValid,               //                       arb:               test has detected an error
		 
		 input wire						regexConfig_valid,
		 input wire[511:0]			regexConfig_data,
		 
		 //stats
		 output wire[319:0] stats_counter
);
    
	 reg					wrDupTagValid;
	 reg					wrDupTagData;
	 
	 reg					readDupTagReady;
	 wire					readDupTagValid;
	 wire					readDupTagData;
	 reg					readDupTagDataReg;
	 
	//state machine for deduplication
	reg[2:0] readOutState;
	localparam GET_META = 0;
	localparam WAIT_DATA = 1;
	
	reg 				axis_read_rsp_valid_delay;
	reg[511:0]		axis_read_rsp_data_delay;
	reg				axis_read_rsp_tag_delay;
	reg[511:0]					readRspDataNext;
	reg							readRspTagNext;
	reg[511:0]					readRspDataPrev;
	reg							readRspTagPrev;

	// to be able to duplicate cache lines
	nlb_axififo #(
	 	.BUS_SIZE_ADDR(10),
	 	.BUS_SIZE_DATA(1)
	) 
 	axififo_readtag_inst (
	 	.rst(rst),
      .clk(clk),
		
		.s_axis_valid(wrDupTagValid),
		.s_axis_ready(),
		.s_axis_data(wrDupTagData),
		.s_axis_last(1'b0),
		
		.m_axis_valid(readDupTagValid),
		.m_axis_ready(readDupTagReady),
		.m_axis_data(readDupTagData),
		.m_axis_last()
	);
	
	reg hasRspData;
	always @(posedge clk) begin
		if (rst) begin
			readDupTagReady <= 0;
			s_axis_read_rsp_ready <= 0;
			axis_read_rsp_valid_delay <= 0;
			axis_read_rsp_data_delay <= 0;
			axis_read_rsp_tag_delay <= 0;
			hasRspData <= 0;
			readOutState <= GET_META;
		end
		else begin
			readDupTagReady <= 1;
			s_axis_read_rsp_ready <= ~hasRspData;
			axis_read_rsp_valid_delay <= 0;
			
			//DATA PRE_FETCHER
			if (s_axis_read_rsp_valid && s_axis_read_rsp_ready) begin
				readRspDataNext <= s_axis_read_rsp_data;
				readRspTagNext	 <= s_axis_read_rsp_tag;
				hasRspData <= 1;
				s_axis_read_rsp_ready <= 0;
			end
			
			
			case (readOutState)
				GET_META: begin
					if (readDupTagReady && readDupTagValid) begin
						readDupTagDataReg <= readDupTagData;
						//fetch data
						if (readDupTagData == 0) begin
							//Check if we already prefetched data
							if (hasRspData || (s_axis_read_rsp_valid && s_axis_read_rsp_ready )) begin
								hasRspData <= 0;
								s_axis_read_rsp_ready <= 1;
								axis_read_rsp_valid_delay <= 1;
								if (hasRspData) begin
									axis_read_rsp_data_delay <= readRspDataNext;
									axis_read_rsp_tag_delay <= readRspTagNext;
									readRspDataPrev <= readRspDataNext;
									readRspTagPrev <= readRspTagNext;
								end
								else begin
									axis_read_rsp_data_delay <= s_axis_read_rsp_data;
									axis_read_rsp_tag_delay <= s_axis_read_rsp_tag;
									readRspDataPrev <= s_axis_read_rsp_data;
									readRspTagPrev <= s_axis_read_rsp_tag;
								end
								//axis_read_rsp_tag_delay <= readTagData;
							end
							else begin
								readDupTagReady <= 0;
								readOutState <= WAIT_DATA;
							end
						end
						// duplicate
						else begin
							axis_read_rsp_valid_delay <= 1;
							axis_read_rsp_data_delay <= readRspDataPrev;
							axis_read_rsp_tag_delay <= readRspTagPrev;
						end
					end
				end //GET_META
				
				WAIT_DATA: begin
					readDupTagReady <= 0;
					//s_axis_read_rsp_ready <= 1;
					if (s_axis_read_rsp_valid && s_axis_read_rsp_ready) begin
						readDupTagReady <= 1;
						hasRspData <= 0;
						s_axis_read_rsp_ready <= 1;
						
						axis_read_rsp_valid_delay	<= 1;
						axis_read_rsp_data_delay	<= s_axis_read_rsp_data;
						axis_read_rsp_tag_delay		<= s_axis_read_rsp_tag;
						readRspDataPrev <= s_axis_read_rsp_data;
						readRspTagPrev  <= s_axis_read_rsp_tag;
						
						readOutState <= GET_META;
					end
				end //GET_DATA
				
			endcase
		end
	end //always
	
	


    wire parseDone;
	 wire regexDone;
	 
	 wire           parser2fifo_valid;
	 wire           parser2fifo_ready;
    wire[511:0]    parser2fifo_data; //TODO change
    wire           parser2fifo_last;
	 
	 wire           parser2regex_valid;
	 wire           parser2regex_ready;
    wire[511:0]    parser2regex_data; //TODO change
    wire           parser2regex_last;
	 
	 wire			mdb_axis_read_req_valid;
	 reg			mdb_axis_read_req_ready;
	 wire[57:0] mdb_axis_read_req_addr;
	 wire 		mdb_axis_read_req_tag;
	 reg			haveReq;
	 reg			pendingReq;
	 
	 //reg[511:0] regData; 
	 reg[57:0] regPrevAddress;
	 reg regTag;
	 
	 
	//check for duplicate address requestor
	always @(posedge clk) begin
		if (rst) begin
			m_axis_read_req_valid <= 0;
			mdb_axis_read_req_ready <= 0;
			regPrevAddress <= 0;
			wrDupTagValid <= 0;
			wrDupTagData <= 0;
			haveReq <= 0;
			pendingReq <= 0;
		end
		else begin
			mdb_axis_read_req_ready <= ~pendingReq; //(~haveReq | ~pendingReq);
			//rd_mdata <= rd_mdata;
			wrDupTagValid <= 0; //meta write
			
			//Check if we got new data
			if (mdb_axis_read_req_valid && mdb_axis_read_req_ready) begin
				regPrevAddress <= mdb_axis_read_req_addr;
				regTag <= mdb_axis_read_req_tag;
				//rd_mdata[0] <= mdb_axis_read_req_tag;
				//haveReq <= 1;
				
				//Check for Duplicate request
				if (regPrevAddress == mdb_axis_read_req_addr) begin
					wrDupTagValid <= 1;
					wrDupTagData <= 1;
				end
				else begin
					haveReq <= 1;
					wrDupTagValid <= 1;
					wrDupTagData  <= 0;
					// Check if potential output was consumed
					if (m_axis_read_req_ready) begin
						m_axis_read_req_valid <= 1;
						m_axis_read_req_addr <= mdb_axis_read_req_addr;
						m_axis_read_req_tag <= mdb_axis_read_req_tag;
					end
					else begin
						mdb_axis_read_req_ready <= 0;
						pendingReq <= 1;
					end
				end
			end
			
			//Check if output was consumed
			if (m_axis_read_req_valid && m_axis_read_req_ready) begin
				//pendingReq <= 0;
				m_axis_read_req_valid <= (mdb_axis_read_req_valid & mdb_axis_read_req_ready) & (regPrevAddress != mdb_axis_read_req_addr);
				//haveReq <= (pendingReq | (mdb_axis_read_req_valid & mdb_axis_read_req_ready & (regPrevAddress != mdb_axis_read_req_addr)));
				if (pendingReq) begin
					pendingReq <= 0;
					mdb_axis_read_req_ready <= 1;
					
					m_axis_read_req_valid <= 1;
					m_axis_read_req_addr <= regPrevAddress;
					m_axis_read_req_tag <= regTag;
				end
			end
			
		end //rst
	end
	
	wire[31:0] string_stall_counter;
	wire[31:0] meta_stall_counter;

	reg[31:0] counter_for_pushes;
	 
    mdb_stringreader string_reader
    (
      .clk(clk),
      .rst(rst),
		//control
      .go(go), //in
      .done(parseDone), //out

		//parameter inputs
		.baseAddr(re2xy_BaseAddr),
		.vbaseAddr(re2xy_VBaseAddr),
		.batCount(re2xy_BatCount),
		.tailWidth(re2xy_TailWidth),
		
		
		// read requests
      .m_axis_read_req_valid(mdb_axis_read_req_valid),
		.m_axis_read_req_ready(mdb_axis_read_req_ready),
      .m_axis_read_req_addr(mdb_axis_read_req_addr),
		.m_axis_read_req_tag(mdb_axis_read_req_tag),
		
		// read responses
      .inValid(axis_read_rsp_valid_delay),
      .inData(axis_read_rsp_data_delay),
		.inTag(axis_read_rsp_tag_delay),
		
		// aligned string output
		.stringValid(parser2fifo_valid),
		.stringReady(parser2fifo_ready),
		.stringData(parser2fifo_data),
		.stringLast(parser2fifo_last),
		
		.string_stall_counter(string_stall_counter),
		.meta_stall_counter(meta_stall_counter)
    );
	 
	 //
	 nlb_axififo #(
	 	.BUS_SIZE_ADDR(9),
	 	.BUS_SIZE_DATA(512)
	) 
 	stringreader_out_fifo (
	 	.rst(rst),
      .clk(clk),
		
		.s_axis_valid(parser2fifo_valid),
		.s_axis_ready(parser2fifo_ready),
		.s_axis_data(parser2fifo_data),
		.s_axis_last(parser2fifo_last),
		
		.m_axis_valid(parser2regex_valid),
		.m_axis_ready(parser2regex_ready),
		.m_axis_data(parser2regex_data),
		.m_axis_last(parser2regex_last)
	);
	 
	 /*axis_x_to_halfx_register
	 #(
		.DATA_WIDTH(512)
	 )
	 axis_x_to_halfx_register_inst
	 (
		.clk(clk),
		.rst(rst),
		
		.s_axis_valid(parser2fifo_valid),
		.s_axis_ready(parser2fifo_ready),
		.s_axis_data(parser2fifo_data), //512bit
		.s_axis_last(parser2fifo_last),
		
		.m_axis_valid(parser2regex_valid),
		.m_axis_ready(parser2regex_ready),
		.m_axis_data(parser2regex_data), //256bit
		.m_axis_last(parser2regex_last)
	 );*/
	 
	 //FIFO in between, part of stringreader
	 
	 wire							regex_match_valid;
	 wire							regex_match_ready;
	 wire[511:0]				regex_match_data;
	 wire							regex_match_last;
	 
	 assign regex_match_ready = m_axis_write_req_ready;
	 
	 
	 reg				regexConfigD_valid;
	 reg[511:0]		regexConfigD_data;
	 
	always @(posedge clk) begin
		if (rst) begin
			regexConfigD_valid <= 0;
		end
		else begin
			regexConfigD_valid <= regexConfig_valid;
			regexConfigD_data <= regexConfig_data;
		end
	end
	 
	 rem_engines_async
	 #(
		.INPUT_WIDTH(512)
	 )
	 rem_engines_inst
	 (
		.clk(clk),
		.Clk_400(Clk_400),
		.rst(rst), //active high
		.go(go),
		.done(regexDone),
		
		//config
		.regexConfig_valid(regexConfigD_valid),
		.regexConfig_data(regexConfigD_data),
		
		.batCount(re2xy_BatCount),
		
		//input
		.s_axis_valid(parser2regex_valid),
		.s_axis_ready(parser2regex_ready),
		.s_axis_data(parser2regex_data), //INPUT_WIDTH
		.s_axis_last(parser2regex_last),
		
		//output
		.m_axis_valid(regex_match_valid),
		.m_axis_ready(regex_match_ready),
		.m_axis_data(regex_match_data), //512bit
		.m_axis_last(regex_match_last)
		
	 );
	 
	 // Increment write address
    always @(posedge clk) begin
      done <= 0;
      m_axis_write_req_valid <= 0;

      if (rst) begin
			m_axis_write_req_addr            <= 0;
			done           <= 0;
		   l12ab_ErrorInfo         <= 0;
		   l12ab_ErrorValid        <= 0;
		end else begin
		  
        m_axis_write_req_valid <= 0;
		  //increment if we did a write, maybe check if succesful, see code above
		  if (m_axis_write_req_valid && m_axis_write_req_ready) begin
				m_axis_write_req_addr <= m_axis_write_req_addr + 1;
		  end
		  
			//fwd new output
        if (regex_match_valid && regex_match_ready) begin
           m_axis_write_req_valid <= 1;
           m_axis_write_req_data <= regex_match_data;
			  if (regex_match_last == 1) begin //TODO
					done <=1;
			  end
        end

      end //else
    end //always
	 
	 
	 //some stats
	 reg prevGo;
	 reg[31:0] input_counter;
	 reg[31:0] input_string_counter;
	 reg[31:0] input_offset_counter;
	 reg[31:0] offset_req_counter;
	 reg[31:0] string_req_counter;
	 reg[31:0] read_stall_counter;
	 reg[31:0] pipe_stall_counter;
	 reg[31:0] input_stall_counter;
	 reg[31:0] output_stall_counter;
	 reg[31:0] fifo_stall_counter;
	 
	 reg[31:0] ext_input_counter;
	 reg[31:0] ext_string_counter;
	 reg[31:0] ext_offset_counter;
	 reg[31:0] ext_req_counter;
	 reg[31:0] ext_str_req_counter;
	 reg[31:0] ext_off_req_counter;
	 reg[31:0] dup_wr_counter;
	 reg[31:0] dup_rd_counter;
	 
	 //assign stats_counter = {string_req_counter, offset_req_counter, input_offset_counter, (dup_rd_counter & dup_wr_counter), ext_off_req_counter, ext_str_req_counter, ext_offset_counter, ext_string_counter, input_string_counter, input_counter};
	 assign stats_counter = {{64{1'b0}}, meta_stall_counter, string_stall_counter,fifo_stall_counter, read_stall_counter, pipe_stall_counter, input_stall_counter, output_stall_counter, 32'hdeadface};
	 
	 always @(posedge clk) begin
		prevGo <= go;
		if (!prevGo && go) begin
			input_counter <= 0;
			input_string_counter <= 0;
			input_offset_counter <= 0;
			offset_req_counter <= 0;
			string_req_counter <= 0;
			read_stall_counter <= 0;
			pipe_stall_counter <= 0;
			input_stall_counter <= 0;
			output_stall_counter <= 0;
			fifo_stall_counter <= 0;
			
			
			ext_input_counter <= 0;
			ext_string_counter <= 0;
			ext_offset_counter <= 0;
			ext_req_counter <= 0;
			ext_str_req_counter <= 0;
			ext_off_req_counter <= 0;
			dup_wr_counter <= 0;
			dup_rd_counter <= 0;

			counter_for_pushes <= 0;
		end
		else begin
			if (parser2fifo_last && parser2fifo_valid && parser2fifo_ready) begin
				counter_for_pushes <= counter_for_pushes + 1;
			end

		//internal
			if (axis_read_rsp_valid_delay) begin
					input_counter <= input_counter + 1;
				if (axis_read_rsp_tag_delay) begin
					input_string_counter <= input_string_counter + 1;
				end
				else begin
					input_offset_counter <= input_offset_counter + 1;
				end
			end
			if (mdb_axis_read_req_valid && mdb_axis_read_req_ready) begin
				if (mdb_axis_read_req_tag) begin
					string_req_counter <= string_req_counter + 1;
				end
				else begin
					offset_req_counter <= offset_req_counter + 1;
				end
			end
			//external
			if (s_axis_read_rsp_valid && s_axis_read_rsp_ready) begin
				ext_input_counter <= ext_input_counter + 1;
				if (s_axis_read_rsp_tag) begin
					ext_string_counter <= ext_string_counter + 1;
				end
				else begin
					ext_offset_counter <= ext_offset_counter + 1;
				end
			end
			if (m_axis_read_req_valid && m_axis_read_req_ready) begin
				ext_req_counter <= ext_req_counter + 1;
				if (m_axis_read_req_tag) begin
					ext_str_req_counter <= ext_str_req_counter + 1;
				end
				else begin
					ext_off_req_counter <= ext_off_req_counter + 1;
				end
			end
			//tag fifo
			if (wrDupTagValid) begin
				dup_wr_counter <= dup_wr_counter + 1;
			end
			if (readDupTagValid && readDupTagReady) begin
				dup_rd_counter <= dup_rd_counter + 1;
			end
			//other
			if (~m_axis_read_req_ready && go) begin
				read_stall_counter <= read_stall_counter + 1;
			end
			/*if (~parser2regex_ready && parser2regex_valid  && go) begin
				pipe_stall_counter <= pipe_stall_counter + 1;
			end*/
			if (s_axis_read_rsp_valid && ~s_axis_read_rsp_ready) begin
				input_stall_counter <= input_stall_counter + 1;
			end
			if (m_axis_write_req_valid && ~m_axis_write_req_ready) begin
				output_stall_counter <= output_stall_counter + 1;
			end
			if (parser2fifo_valid && ~parser2fifo_ready) begin
				fifo_stall_counter <= fifo_stall_counter;
			end
		end
	 end
	 
    
endmodule

`default_nettype wire