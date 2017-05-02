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

module fifo_to_axis #(
    parameter Width = 174
) (
    input  wire             clk,
    input  wire             rst,

    input  wire [Width-1:0] input_data,
    input  wire             input_empty,
    //input  wire             input_almost_empty,
    output wire             input_read,

    output wire [Width-1:0] M_AXIS_TDATA,
    output wire             M_AXIS_TVALID,
    input  wire             M_AXIS_TREADY
);

// Dataflow
reg             input_data_valid;
reg [Width-1:0] out_data;
reg             out_valid;
wire            out_ready;
wire            output_processed;

// In case a word was read, but output is not ready, the word
// needs to be buffered. in_valid/data makes this transparent.
wire             stall;
reg              stalled;
reg              input_data_valid_buf;
reg  [Width-1:0] input_data_buf;
wire             in_valid;
wire [Width-1:0] in_data;

// State Logic
assign output_processed = (~out_valid | out_ready);
assign stall            = ~output_processed & in_valid;
assign input_read       = ~(rst | input_empty | stall);

assign in_valid = stalled ? input_data_valid_buf : input_data_valid;
assign in_data  = stalled ? input_data_buf       : input_data;

always @ (posedge clk)
    if(rst) begin
        out_valid            <= 0;
        out_data             <= 0;
        input_data_valid     <= 0;
        input_data_valid_buf <= 0;
        input_data_buf       <= 0;
        stalled              <= 0;
    end else begin
        out_valid            <= output_processed ? in_valid : out_valid;
        out_data             <= output_processed ? in_data  : out_data;
        input_data_valid     <= input_read;
        stalled              <= stall;
        input_data_valid_buf <= stalled ? input_data_valid_buf : input_data_valid;
        input_data_buf       <= stalled ? input_data_buf       : input_data;
    end

	 
	 assign out_ready = M_AXIS_TREADY;
	 assign M_AXIS_TVALID = out_valid;
	 assign M_AXIS_TDATA = out_data;
	 
/*kvs_AXIBuffer #(
    .Width(Width)
) output_buffer (
    .clk(clk),
    .rst(rst),
    .S_AXIS_TVALID(out_valid),
    .S_AXIS_TREADY(out_ready),
    .S_AXIS_TDATA(out_data),
    .M_AXIS_TVALID(M_AXIS_TVALID),
    .M_AXIS_TREADY(M_AXIS_TREADY),
    .M_AXIS_TDATA(M_AXIS_TDATA)
);*/

endmodule 

`default_nettype wire