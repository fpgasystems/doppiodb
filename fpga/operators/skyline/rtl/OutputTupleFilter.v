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


module OutputTupleFilter  #(parameter NUM_DIMENSIONS  = 2,
							parameter MAX_DIM_BITS    = 8,
	                        parameter DIMENSION_WIDTH = 32) 
  (
    input   wire                        clk,               
    input   wire                        rst_n,     

    input   wire  [MAX_DIM_BITS-1:0]    NumDimsMinusOne,
         
    input   wire                        TupleValid, 
    input   wire  [DIMENSION_WIDTH-1:0] TupleData,     
    input   wire                        FlushTuple,      
    input   wire                        FlushTupleASValid,  

    output  reg                         FilteredTupleValid,
    output  reg   [DIMENSION_WIDTH-1:0] FilteredTupleData 
    );


reg   [MAX_DIM_BITS-1:0]    DimCnt;
reg                         flush;
reg                         flush_valid;

wire  [DIMENSION_WIDTH-1:0] tuple_data;
wire                        tuple_valid;

//////////////////////////////////////////////////

quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
              .FIFO_DEPTH_BITS(9),
              .FIFO_ALMOSTFULL_THRESHOLD(32)
             ) temp_tuple_fifo (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (TupleData),
        .we                 (TupleValid),

        .re                 (flush),
        .dout               (tuple_data),
        .empty              (),
        .valid              (tuple_valid),
        .full               (),
        .count              (),
        .almostfull         ()
    );

always @(posedge clk) begin
	if(~rst_n) begin
		DimCnt      <= 0;
		flush       <= 0;
		flush_valid <= 0;

		FilteredTupleData  <= 0;
		FilteredTupleValid <= 0;
	end 
	else begin

		FilteredTupleData  <= tuple_data;
		FilteredTupleValid <= flush_valid & tuple_valid;

		if(DimCnt == NumDimsMinusOne) begin
			flush       <= 0;
			flush_valid <= 0;
			DimCnt      <= 0;
		end 
		else if( flush ) begin 
			DimCnt <= DimCnt  +1;
		end

		if( FlushTuple ) begin 
			flush_valid <= FlushTupleASValid;
			flush       <= 1'b1;
			DimCnt      <= 0;
		end
	end
end


endmodule // OutputTupleFilter 