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
`include "nlb_cfg_pkg.vh"

module nlb_axififo
	#(
		parameter BUS_SIZE_ADDR=5,
		parameter BUS_SIZE_DATA=16,
		parameter GRAM_STYLE=`GRAM_AUTO,
		parameter PROG_FULL_THRESH=0
		
	)
	(
		input wire								clk,
		input wire								rst,
		
		input wire								s_axis_valid,
		output wire								s_axis_ready,
		input wire[BUS_SIZE_DATA-1:0]		s_axis_data,
		input wire								s_axis_last,
		
		output wire								m_axis_valid,
		input wire								m_axis_ready,
		output wire[BUS_SIZE_DATA-1:0]	m_axis_data,
		output wire								m_axis_last,
		
		output reg [BUS_SIZE_ADDR-1: 0] data_count
	);
	
	
	// Convert FIFO to AxiStream
	wire readEn;
	wire readValid;
	wire[BUS_SIZE_DATA-1:0] readData;
	reg[BUS_SIZE_DATA-1:0] readDataDelayed;
	wire readLast;
	reg readLastDelayed;
 	wire readEmpty;
	wire writeFull;
	reg outputPending;
	
	assign s_axis_ready = ~writeFull;
	assign m_axis_data = (readValid) ? readData : readDataDelayed;
	assign m_axis_last = (readValid) ? readLast : readLastDelayed;
	assign m_axis_valid = (readValid | outputPending);
	assign readEn = (~readEmpty & m_axis_ready);

	//TODO check for overflow
 	nlb_gfifo_v #(
	 	.BUS_SIZE_ADDR(BUS_SIZE_ADDR),
	 	.BUS_SIZE_DATA(BUS_SIZE_DATA+1),
		.GRAM_STYLE(GRAM_STYLE),
		.PROG_FULL_THRESH(PROG_FULL_THRESH)
	 	)
 	gfifo_outputPrep_i (
	 	.rst_x(~rst),       // input   reset, reset polarity defined by SYNC_RESET_POLARITY
      .clk(clk),         // input   clock
		  //WRITE
		.wr_data({s_axis_last, s_axis_data}),
		.wr_en(s_axis_valid),
		.overflow(),     // input   write data with configurable width
		//READ
 	   .rd_en(readEn),       // input   read enable
		.rd_data({readLast,readData}),
		.valid(readValid), //TODO
      .underflow(),   // output  underflow being asserted indicates one unsuccessfully read
      .empty(readEmpty),       // output  FIFO empty
      
		.full(writeFull),        // output  FIFO full
      .count(),       // output  FIFOcount
      .prog_full()
	);
	
	always @(posedge clk) begin
		if (rst == 1) begin
			outputPending <= 0;
			readDataDelayed <= 0;
			readLastDelayed <= 0;
		end
		else begin
			outputPending <= outputPending;
			//Check if there is data available and ready is high
			/*if (readEmpty == 0 && m_axis_ready) begin
				readEn <= 1;
			end*/
			//Chech if new string got accepted
			if (readValid && ~m_axis_ready) begin
				outputPending <= 1;
				readDataDelayed <= readData;
				readLastDelayed <= readLast;
			end
			if (m_axis_ready && outputPending && ~readValid) begin
				outputPending <= 0;
			end
		end
	end
	
	always @(posedge clk) begin
		if (rst == 1) begin
			data_count <= 0;
		end
		else begin
			if (m_axis_valid && m_axis_ready && !(s_axis_valid && s_axis_ready)) begin
				data_count <= data_count - 1;
			end
			
			if (s_axis_valid && s_axis_ready && !(m_axis_valid && m_axis_ready)) begin
				data_count <= data_count + 1;
			end
		end
	end
	

endmodule

`default_nettype wire
