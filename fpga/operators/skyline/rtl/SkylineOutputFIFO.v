
`include "framework_defines.vh"


module SkylineOutputFIFO #( parameter NUM_DIMENSIONS  = 2,
							parameter MAX_DIM_BITS    = 8,
	                        parameter DIMENSION_WIDTH = 32 ) 
(
	input   wire                        clk,               
    input   wire                        rst_n, 

    output  wire                        empty,
    input   wire                        flush,

    input   wire  [MAX_DIM_BITS-1:0]    NumDimsMinusOne,

	output  wire                        s_axis_ready,              
	input   wire                        s_axis_valid,
	input   wire  [DIMENSION_WIDTH-1:0] s_axis_data, 
	output  reg   [31:0]                TuplesCount,
	output  reg   [11:0]                available_space,

	input   wire                        m_axis_ready,
	output  reg                         m_axis_valid, 
	output  reg   [511:0]               m_axis_data
);

localparam DIMS_PER_CL = 64 / (DIMENSION_WIDTH/8);

localparam FIFO_SIZE_BITS = 10;
localparam FIFO_SIZE      = 1024;

wire                            tuple_fifo_we[DIMS_PER_CL-1:0];
wire  [DIMS_PER_CL-1:0]         tuple_fifo_valid;
wire  [DIMS_PER_CL-1:0]         tuple_fifo_full;
wire  [DIMS_PER_CL-1:0]         tuple_fifo_empty;
wire  [DIMENSION_WIDTH-1:0]     tuple_fifo_data[DIMS_PER_CL-1:0];
wire  [9:0]                     tuple_fifo_count[DIMS_PER_CL-1:0];

wire                            read_line;

wire  [511:0]                   line_data;
wire                            line_valid;
wire                            fifos_empty;

reg   [MAX_DIM_BITS-1:0]        DimCnt;
reg   [3:0]                     fifo_index;  // NOTE: Assuming Minimum dimension width 32-bit and maximum cacheline width 512
reg                             flush_fifo;


genvar i;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

generate for (i = 0; i < DIMS_PER_CL; i=i+1) begin: fifos
	
	quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
                  .FIFO_DEPTH_BITS(FIFO_SIZE_BITS),
                  .FIFO_ALMOSTFULL_THRESHOLD(32)
                 ) fifo_x (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (s_axis_data),
        .we                 (tuple_fifo_we[i]),

        .re                 (read_line),
        .dout               (tuple_fifo_data[i]),
        .empty              (tuple_fifo_empty[i]),
        .valid              (tuple_fifo_valid[i]),
        .full               (tuple_fifo_full[i]),
        .count              (tuple_fifo_count[i]),
        .almostfull         ()
    );


assign tuple_fifo_we[i] = s_axis_valid & (fifo_index == i);

assign line_data[DIMENSION_WIDTH*(i+1)-1 : DIMENSION_WIDTH*i] = (tuple_fifo_valid[i])? tuple_fifo_data[i] : `INT_MAX;


end


endgenerate


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

assign s_axis_ready = ~tuple_fifo_full[fifo_index];

assign line_valid  = (&tuple_fifo_valid) | (flush_fifo & (|tuple_fifo_valid));
assign read_line   = m_axis_ready & line_valid;

assign fifos_empty = &tuple_fifo_empty;
assign empty       = fifos_empty & ~m_axis_valid;

always @(posedge clk) begin
	if(~rst_n) begin
		DimCnt       <= 0;
		fifo_index   <= 0;
		flush_fifo   <= 0;

		m_axis_data  <= 0;
		m_axis_valid <= 0;

		TuplesCount  <= 0;

		available_space <= FIFO_SIZE;
	end 
	else begin

		if( m_axis_ready ) begin 
			m_axis_data  <= line_data;
			m_axis_valid <= line_valid;
		end
		//
		if( fifos_empty ) begin 
			flush_fifo <= 1'b0;
		end
		else if( flush ) begin
			flush_fifo <= 1'b1;
		end 
		
        // 
        available_space <= FIFO_SIZE - tuple_fifo_count[0];
        
		if( s_axis_valid ) begin 
			if( fifo_index == DIMS_PER_CL-1 ) begin
				fifo_index <= 0;
			end 
			else begin 
				fifo_index <= fifo_index + 1;
			end

			if( DimCnt == NumDimsMinusOne ) begin
				DimCnt      <= 0;
				TuplesCount <= TuplesCount + 1'b1;
			end 
			else begin 
				DimCnt <= DimCnt + 1;
			end
		end
	end
end


endmodule // SkylineOutputFIFO