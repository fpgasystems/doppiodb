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

module rem_engines_async
#(
		REGEX_COUNT_BITS=4,
		INPUT_WIDTH=512
)
(
       input wire				clk,
       input wire				Clk_400,
       input wire				rst,
		 
		 input wire				go,
		 output wire			done,
		 
		 input wire				regexConfig_valid,
		 input wire[511:0]	regexConfig_data,
		 
		 input wire[31:0]		batCount,
		 
		 input wire				s_axis_valid,
		 output wire			s_axis_ready,
		 input wire[INPUT_WIDTH-1:0]	s_axis_data,
		 input wire				s_axis_last,
		 
		 output wire 			m_axis_valid,
		 input wire				m_axis_ready, //TODO connect this better
		 output wire[511:0]	m_axis_data,
		 output wire				m_axis_last
);

	reg[(REGEX_COUNT_BITS)-1:0]			engine_idx;
	wire[(2**REGEX_COUNT_BITS)-1:0]		axis_input_valid;
	wire[(2**REGEX_COUNT_BITS)-1:0]		axis_input_ready;
	
	reg				regConfigValid;
	reg[511:0]		regConfigData;
	
	/* wires between FIFOs */
	//engines inputs
	wire [2**REGEX_COUNT_BITS-1:0]	regex_string_valid;
	wire [2**REGEX_COUNT_BITS-1:0]	regex_string_ready;
	wire [INPUT_WIDTH-1:0]							regex_string_data [2**REGEX_COUNT_BITS-1:0];
	wire [2**REGEX_COUNT_BITS-1:0]	regex_string_last;
	
	//engines outputs
	wire [2**REGEX_COUNT_BITS-1:0]	regex_match_valid;
	wire [2**REGEX_COUNT_BITS-1:0]	regex_match_ready;
	wire [15:0] 							regex_match_data [2**REGEX_COUNT_BITS-1:0];

	wire[2**REGEX_COUNT_BITS-1:0]		match_collect_any_valid;
	wire[2**REGEX_COUNT_BITS-1:0]		match_collect_any_ready;
	wire[((2**REGEX_COUNT_BITS)*16)-1:0]	match_collect_any_data;
	wire										match_collect_valid;
	reg										match_collect_ready;
	wire[15:0]								match_collect_data;
	
	reg											m_axis_valid_prelay;
	reg[(REGEX_COUNT_BITS)-1:0]			fifo_idx;
	reg[31:0]									outCount;
	reg[4:0]										shiftCount;
	reg[511:0]									resultVec;
	
	reg                             collect2output_valid;
	wire                             collect2output_ready;
	reg[511:0]								collect2output_data;
	reg                             collect2output_last;

	
	// Delay config signal by 1 cycle
	always @(posedge Clk_400) begin
		if (rst == 1)begin
			regConfigValid <= 0;
			//regConfigData <= 0;
		end
		else begin
			regConfigValid <= regexConfig_valid;
			regConfigData <= regexConfig_data;
		end
	end //always
	
	// Input distribution logic
	assign s_axis_ready = axis_input_ready[engine_idx];

	always @(posedge clk) begin
		if (rst == 1 || go == 0)begin
			engine_idx <=  1'b0;
		end
		else begin
			if (s_axis_valid == 1 && s_axis_ready == 1 && s_axis_last == 1) begin
				engine_idx <= engine_idx + 1;
			end
		end //else
	end //always
	
    //
   reg reset;
	reg rem_reset;
	reg rem_reset_delay;
	reg rem_reset_fast;
	reg rem_reset_fast_delay;

	always @(posedge clk) begin
		reset <= rst;
		rem_reset <= reset;
		rem_reset_delay <= rem_reset;
	end	
	always @(posedge Clk_400) begin
		rem_reset_fast <= reset;
		rem_reset_fast_delay <= rem_reset_fast;
	end
	// Generate multiple regex engines
	genvar X;  
  	generate  
    for (X=0; X < 2**REGEX_COUNT_BITS; X=X+1)  
	begin: generateloop
	
		assign axis_input_valid[X] = (engine_idx == X) ? s_axis_valid : 1'b0;

		// input string fifo
		async_axififo #(
		 	.BUS_SIZE_DATA(INPUT_WIDTH),
			.LAST_EN(1)
		)
		axi_string_fifo_inst (
			.s_axis_clk(clk),
			.m_axis_clk(Clk_400),
			.rst(rem_reset_delay),
			
			.s_axis_valid(axis_input_valid[X]),
			.s_axis_ready(axis_input_ready[X]),
			.s_axis_data(s_axis_data),
			.s_axis_last(s_axis_last),
			
			.m_axis_valid(regex_string_valid[X]),
			.m_axis_ready(regex_string_ready[X]),
			.m_axis_data(regex_string_data[X]),
			.m_axis_last(regex_string_last[X])
		);
		
		// regex engines
		rem_top_ff
		#(
			.INPUT_WIDTH(INPUT_WIDTH)
		)
		regex_top_inst
		(
			.clk(Clk_400),
			.rst(rem_reset_fast_delay), //active high
			.go(go),
			.done(), //TODO remove
			
			//config
			.regexConfig_valid(regConfigValid),
			.regexConfig_data(regConfigData),
			
			//input
			.s_axis_valid(regex_string_valid[X]),
			.s_axis_ready(regex_string_ready[X]),
			.s_axis_data(regex_string_data[X]), //INPUT_WIDTH
			.s_axis_last(regex_string_last[X]),
			
			//output
			.m_axis_valid(regex_match_valid[X]),
			.m_axis_ready(regex_match_ready[X]),
			.m_axis_data(regex_match_data[X]) //16bit
		 );
		 
		assign match_collect_any_ready[X] = (fifo_idx == X) ? match_collect_ready : 1'b0;
		
		// output match fifo
		async_axififo #(
		 	.BUS_SIZE_DATA(16)
		) axi_match_fifo_inst (
			.s_axis_clk(Clk_400),
			.m_axis_clk(clk),
			.rst(rem_reset_delay),
			
			.s_axis_valid(regex_match_valid[X]),
			.s_axis_ready(regex_match_ready[X]),
			.s_axis_data(regex_match_data[X]),
			.s_axis_last(1'b0), //TODO
			
			.m_axis_valid(match_collect_any_valid[X]),
			.m_axis_ready(match_collect_any_ready[X]),
			.m_axis_data(match_collect_any_data[X*16 +: 16]),
			.m_axis_last()
		);

	end  
	endgenerate
	
	//logic to read out
	assign match_collect_valid = match_collect_any_valid[fifo_idx];
	assign match_collect_data = match_collect_any_data[fifo_idx*16 +: 16];
	
	always @(posedge clk) begin
		if (rst == 1 || go == 0) begin
			collect2output_valid <= 0;
			m_axis_valid_prelay <= 0;
			//m_axis_data <= 0;
			match_collect_ready <= 0;
			fifo_idx <= 0;
			resultVec <= 0;
			outCount <= 0;
			shiftCount <= 0;
		end
		else begin
			match_collect_ready <= collect2output_ready; //TODO be smarter about this			
			m_axis_valid_prelay <= 0;
			collect2output_last <= 0;
			
			//Check if we have to write out resultVec
			if (m_axis_valid_prelay) begin
				collect2output_valid <= 1;
				collect2output_data <= resultVec;
			end
			
			//Check if successfully writen out
			if (m_axis_valid && collect2output_ready) begin
				collect2output_valid <= 0;
			end
			
			//Check if a new match value is coming from regex engines
			if (match_collect_valid == 1 && match_collect_ready == 1) begin
				resultVec[511:496] <= match_collect_data;
				resultVec[495:0] <= resultVec[511:16];
				outCount <= outCount + 1;
				shiftCount <= shiftCount + 1;
				fifo_idx <= fifo_idx + 1;
				// if lowest 5bits == 0x1F, then we collected 32 values
				if (outCount[4:0] == 5'h1F) begin
					//write out 512bit words
					m_axis_valid_prelay <= 1;
				end
			end //popValid
			else if (outCount == batCount) begin
				if (shiftCount[4:0] != 5'h00) begin
					shiftCount <= shiftCount + 1;
					resultVec[495:0] <= resultVec[511:16];
				end
				else begin
					collect2output_valid <= 1;
					collect2output_data <= resultVec;
					outCount <= 0;
					collect2output_last <= 1;
				end
			end
		end
	end //always
	
	axis_register #(
		.WIDTH(513)
	) axis_register_inst (
		.clk(clk),
		.rst(rst),
		
		.s_axis_valid(collect2output_valid),
		.s_axis_ready(collect2output_ready),
		.s_axis_data({collect2output_data,collect2output_last}),
		//.s_axis_last(), //TODO
		
		.m_axis_valid(m_axis_valid),
		.m_axis_ready(m_axis_ready),
		.m_axis_data({m_axis_data,m_axis_last})
		//.m_axis_last() //TODO
	);
	
endmodule

`default_nettype wire
