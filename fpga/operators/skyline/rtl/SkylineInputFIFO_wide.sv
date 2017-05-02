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


module SkylineInputFIFO_wide #( parameter NUM_DIMENSIONS  = 2,
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

wire                            tuple_fifo_re;
wire  [NUM_DIMENSIONS-1:0]      tuple_fifo_valid;
wire  [NUM_DIMENSIONS-1:0]      tuple_fifo_full;
wire  [DIMENSION_WIDTH-1:0]     tuple_fifo_data[NUM_DIMENSIONS-1:0];
wire  [8:0]                     tuple_fifo_count[NUM_DIMENSIONS-1:0];

wire                            valid_fifo;

reg   [MAX_DIM_BITS-1:0]        DimCnt;
reg   [3:0]                     countIn[NUM_DIMENSIONS-1:0];  
reg   [511:0]                   line_data[NUM_DIMENSIONS-1:0];
reg   [31:0]                    fifo_in[NUM_DIMENSIONS-1:0];
reg   [NUM_DIMENSIONS-1:0]      line_valid;

reg   [31:0]                    clsCount = 0;

reg   [NUM_DIMENSIONS-1:0]      DimsMaskReg;
reg   [MAX_DIM_BITS-1:0]        NumDimsMinusOneReg;

//wire  [DIMENSION_WIDTH-1:0]     fifo_data_out[NUM_DIMENSIONS-1:0];

genvar i;
integer j;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

generate for (i = 0; i < NUM_DIMENSIONS; i=i+1) begin: fifos

	// Serializing the feed to every fifo
	always @(posedge clk) begin
		if(~rst_n) begin
			line_valid[i] <= 0;
			countIn[i]    <= 0;
			line_data[i]  <= 0;
		end 
		else begin
			if(s_axis_valid & (DimCnt == i) & ~line_valid[i]) begin 
				line_valid[i] <= 1'b1;
				countIn[i]    <= 0;
				line_data[i]  <= s_axis_data;
			end

			if(line_valid[i] & ~tuple_fifo_full[i]) begin 
				countIn[i] <= countIn[i] + 1'b1;
			end

			if((countIn[i] == DIMS_PER_CL-1) & ~tuple_fifo_full[i]) begin 
				line_valid[i] <= 1'b0;
				countIn[i]    <= 0;
			end
		end 
	end
	//
	always @(*) begin
		case(countIn[i])
			4'h0: begin  fifo_in[i] = line_data[i][31:0]; end 
			4'h1: begin  fifo_in[i] = line_data[i][63:32]; end 
			4'h2: begin  fifo_in[i] = line_data[i][95:64]; end 
			4'h3: begin  fifo_in[i] = line_data[i][127:96]; end 
			4'h4: begin  fifo_in[i] = line_data[i][159:128]; end 
			4'h5: begin  fifo_in[i] = line_data[i][191:160]; end 
			4'h6: begin  fifo_in[i] = line_data[i][223:192]; end 
			4'h7: begin  fifo_in[i] = line_data[i][255:224]; end 
			4'h8: begin  fifo_in[i] = line_data[i][287:256]; end 
			4'h9: begin  fifo_in[i] = line_data[i][319:288]; end
			4'ha: begin  fifo_in[i] = line_data[i][351:320]; end 
			4'hb: begin  fifo_in[i] = line_data[i][383:352]; end 
			4'hc: begin  fifo_in[i] = line_data[i][415:384]; end 
			4'hd: begin  fifo_in[i] = line_data[i][447:416]; end 
			4'he: begin  fifo_in[i] = line_data[i][479:448]; end 
			4'hf: begin  fifo_in[i] = line_data[i][511:480]; end
			default: begin  fifo_in[i] = 0; end
		endcase // countIn[i]
	end
	
	quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
                  .FIFO_DEPTH_BITS(9),
                  .FIFO_ALMOSTFULL_THRESHOLD(32)
                 ) fifo_x (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (fifo_in[i]),
        .we                 (line_valid[i]),

        .re                 (tuple_fifo_re),
        .dout               (tuple_fifo_data[i]),
        .empty              (),
        .valid              (tuple_fifo_valid[i]),
        .full               (tuple_fifo_full[i]),
        .count              (tuple_fifo_count[i]),
        .almostfull         ()
    );


//assign fifo_data_out[i] = tuple_fifo_data[i];

end

endgenerate

assign tuple_fifo_re = valid_fifo & m_axis_ready;
assign s_axis_ready  = ~line_valid[DimCnt];
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
assign valid_fifo = (& (tuple_fifo_valid | DimsMaskReg) );

always @(posedge clk) begin
	if(~rst_n) begin
		DimCnt       <= 0;

		for(j=0; j < NUM_DIMENSIONS; j=j+1) begin 
            m_axis_data[j]     <= 0;
        end

		m_axis_valid <= 0;

		clsCount     <= 0;

		DimsMaskReg        <= 0;
		NumDimsMinusOneReg <= 0;
	end 
	else begin 
		DimsMaskReg        <= ~DimsMask;
		NumDimsMinusOneReg <= NumDimsMinusOne;

		if(s_axis_valid & s_axis_ready) begin
			clsCount <= clsCount + 1'b1;
		end 
		if(m_axis_ready) begin
			m_axis_data  <= tuple_fifo_data;
			m_axis_valid <= valid_fifo;
		end
		if( s_axis_valid & s_axis_ready ) begin 
			if( DimCnt == NumDimsMinusOneReg ) begin
				DimCnt <= 0;
			end 
			else begin 
				DimCnt <= DimCnt + 1;
			end
		end
    end 
end

endmodule // SkylineInputFIFO

