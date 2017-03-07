
//`include "../../framework_defines.vh"


module SkylineInputFIFO #( parameter NUM_DIMENSIONS  = 2,
						   parameter MAX_DIM_BITS    = 8,
	                       parameter DIMENSION_WIDTH = 32) 
(
	input   wire                        clk,               
    input   wire                        rst_n, 

    input   wire  [MAX_DIM_BITS-1:0]    NumDimsMinusOne,
    input   wire                        firstTime,

	output  wire                        s_axis_ready,              
	input   wire                        s_axis_valid,
	input   wire  [511:0]               s_axis_data, 

	input   wire                        m_axis_ready,
	output  reg                         m_axis_valid, 
	output  reg   [DIMENSION_WIDTH-1:0] m_axis_data
);


localparam DIMS_PER_CL = 64 / (DIMENSION_WIDTH/8);

wire                            tuple_fifo_re[DIMS_PER_CL-1:0];
wire                            tuple_fifo_valid[DIMS_PER_CL-1:0];
wire  [DIMS_PER_CL-1:0]         tuple_fifo_full;
wire  [DIMENSION_WIDTH-1:0]     tuple_fifo_data[DIMS_PER_CL-1:0];

wire                            valid_fifo;

reg   [MAX_DIM_BITS-1:0]        DimCnt;
reg   [3:0]                     fifo_index;  // NOTE: Assuming Minimum dimension width 32-bit and maximum cacheline width 512

reg   [31:0]                    clsCount = 0;
reg 							firstTimeReg;

genvar i;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

generate for (i = 0; i < DIMS_PER_CL; i=i+1) begin: fifos
	
	quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
                  .FIFO_DEPTH_BITS(9),
                  .FIFO_ALMOSTFULL_THRESHOLD(32)
                 ) fifo_x (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (s_axis_data[DIMENSION_WIDTH*(i+1)-1 : DIMENSION_WIDTH*i]),
        .we                 (s_axis_valid & s_axis_ready),

        .re                 (tuple_fifo_re[i]),
        .dout               (tuple_fifo_data[i]),
        .empty              (),
        .valid              (tuple_fifo_valid[i]),
        .full               (tuple_fifo_full[i]),
        .count              (),
        .almostfull         ()
    );



assign tuple_fifo_re[i] = (fifo_index == i) & m_axis_ready;

end

endgenerate

assign s_axis_ready = ~(|tuple_fifo_full);
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
assign valid_fifo = tuple_fifo_valid[ fifo_index ];

always @(posedge clk) begin
	if(~rst_n) begin
		DimCnt       <= 0;
		fifo_index   <= 0;

		m_axis_data  <= 0;
		m_axis_valid <= 0;
		firstTimeReg <= 0;

		clsCount <= 0;
	end 
	else begin 

		firstTimeReg <= firstTime;

		if(s_axis_valid & s_axis_ready) begin
			clsCount <= clsCount + 1'b1;
		end 

		if(m_axis_ready) begin
			m_axis_data  <= tuple_fifo_data[ fifo_index ];
			m_axis_valid <= valid_fifo;

			if( valid_fifo ) begin 
				if( (DimCnt == NumDimsMinusOne) | ~firstTimeReg ) begin
					DimCnt <= 0;

					if( fifo_index == DIMS_PER_CL-1 ) begin
						fifo_index <= 0;
					end 
					else begin 
						fifo_index <= fifo_index + 1;
					end
				end 
				else begin 
					DimCnt <= DimCnt + 1;
				end
			end
		end
    end 
end

endmodule // SkylineInputFIFO

