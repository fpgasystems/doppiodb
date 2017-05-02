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


//`include "../../framework_defines.vh"


module SkylineInputFIFO_wide_full #( parameter NUM_DIMENSIONS  = 2,
						        parameter MAX_DIM_BITS    = 8,
	                            parameter DIMENSION_WIDTH = 32) 
(
	input   wire                                       clk,               
    input   wire                                       rst_n, 

    input   wire  [NUM_DIMENSIONS-1:0]                 DimsMask,
    input   wire  [MAX_DIM_BITS-1:0]                   NumDimsMinusOne,

	output  wire                                       s_axis_ready,              
	input   wire                                       s_axis_valid,
	input   wire  [511:0]                              s_axis_data, 

	input   wire                                       m_axis_ready,
	output  reg                                        m_axis_valid, 
	output  reg   [DIMENSION_WIDTH-1:0]                m_axis_data[NUM_DIMENSIONS-1:0]
);


localparam DIMS_PER_CL = 64 / (DIMENSION_WIDTH/8);

localparam PATCH_SIZE = 16;

wire  [DIMS_PER_CL-1:0]         tuple_fifo_re;
wire  [DIMS_PER_CL-1:0]         tuple_fifo_valid[NUM_DIMENSIONS-1:0];
wire  [DIMS_PER_CL-1:0]         tuple_fifo_full[NUM_DIMENSIONS-1:0];
wire  [DIMENSION_WIDTH-1:0]     tuple_fifo_data[NUM_DIMENSIONS-1:0][DIMS_PER_CL-1:0];
wire  [8:0]                     tuple_fifo_count[NUM_DIMENSIONS-1:0][DIMS_PER_CL-1:0];

wire                            valid_fifo;

reg   [MAX_DIM_BITS-1:0]        DimCnt;
reg   [3:0]                     fifo_index;
reg   [5:0]                     patch_index;

wire  [31:0]                    s_axis_data_arr[DIMS_PER_CL-1:0];

wire  [31:0]                    fifo_data_out[NUM_DIMENSIONS-1:0];
wire  [NUM_DIMENSIONS-1:0]      fifo_we;
wire  [NUM_DIMENSIONS-1:0]      fifo_valid_t;

reg   [31:0]                    clsCount = 0;

reg   [NUM_DIMENSIONS-1:0]      DimsMaskReg;
reg   [MAX_DIM_BITS-1:0]        NumDimsMinusOneReg;

//wire  [DIMENSION_WIDTH-1:0]     fifo_data_out[NUM_DIMENSIONS-1:0];

genvar i, c;
integer j;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

generate for (i = 0; i < NUM_DIMENSIONS; i=i+1) begin: fifos_all

	for (c = 0; c < DIMS_PER_CL; c=c+1) begin: fifos_dim

	quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
                  .FIFO_DEPTH_BITS(9),
                  .FIFO_ALMOSTFULL_THRESHOLD(32)
                 ) fifo_xy (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (s_axis_data_arr[c]),
        .we                 (fifo_we[i]),

        .re                 (tuple_fifo_re[c]),
        .dout               (tuple_fifo_data[i][c]),
        .empty              (),
        .valid              (tuple_fifo_valid[i][c]),
        .full               (tuple_fifo_full[i][c]),
        .count              (tuple_fifo_count[i][c]),
        .almostfull         ()
    );
	//



end // fifos_dim
 
assign fifo_we[i]       = DimCnt == i;
assign fifo_data_out[i] = tuple_fifo_data[i][fifo_index];
assign fifo_valid_t[i]  = tuple_fifo_valid[i][fifo_index];

end //fifos_all

//
for (c = 0; c < DIMS_PER_CL; c=c+1) begin: fifos_re

	assign tuple_fifo_re[c]   = (fifo_index == c) & valid_fifo & m_axis_ready;

	assign s_axis_data_arr[c] = s_axis_data[32*c+31:c*32];
end


 
endgenerate

assign s_axis_ready  = ~(|tuple_fifo_full[DimCnt]);
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
assign valid_fifo = (& (fifo_valid_t | DimsMaskReg) );

always @(posedge clk) begin
	if(~rst_n) begin
		DimCnt       <= 0;

		for(j=0; j < NUM_DIMENSIONS; j=j+1) begin 
            m_axis_data[j]     <= 0;
        end

		m_axis_valid <= 0;

		clsCount     <= 0;

		fifo_index   <= 0;

		DimsMaskReg        <= 0;
		NumDimsMinusOneReg <= 0;

		patch_index        <= 0;
	end 
	else begin 
		DimsMaskReg        <= ~DimsMask;
		NumDimsMinusOneReg <= NumDimsMinusOne;

		if(s_axis_valid & s_axis_ready) begin
			clsCount <= clsCount + 1'b1;
		end 
		if(m_axis_ready) begin
			m_axis_data  <= fifo_data_out;
			m_axis_valid <= valid_fifo;

			if(valid_fifo) begin
				if(fifo_index == DIMS_PER_CL-1) begin
					fifo_index <= 0;
				end
				else begin
					fifo_index <= fifo_index + 1'b1;
				end
			end
		end
		if( s_axis_valid & s_axis_ready ) begin 
			if(patch_index == PATCH_SIZE-1) begin
				if( DimCnt == NumDimsMinusOneReg ) begin
					DimCnt <= 0;
				end 
				else begin 
					DimCnt <= DimCnt + 1;
				end

				patch_index <= 0;
			end
			else begin
				patch_index <= patch_index + 1'b1;
			end
		end
    end 
end

endmodule // SkylineInputFIFO

