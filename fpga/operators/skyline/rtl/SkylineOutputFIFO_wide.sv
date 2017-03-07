
//`include "../../framework_defines.vh"


module SkylineOutputFIFO_wide #( parameter NUM_DIMENSIONS  = 2,
							     parameter MAX_DIM_BITS    = 8,
	                             parameter DIMENSION_WIDTH = 32 ) 
(
	input   wire                                       clk,               
    input   wire                                       rst_n, 

    output  wire                                       empty,
    input   wire                                       flush,

    input   wire  [MAX_DIM_BITS-1:0]                   NumDimsMinusOne,

	output  wire                                       s_axis_ready,              
	input   wire                                       s_axis_valid,
	input   wire  [DIMENSION_WIDTH-1:0]                s_axis_data[NUM_DIMENSIONS-1:0], 
	output  reg   [31:0]                               TuplesCount,
	output  reg   [11:0]                               available_space,

	input   wire                                       m_axis_ready,
	output  reg                                        m_axis_valid, 
	output  reg   [511:0]                              m_axis_data
);

localparam DIMS_PER_CL = 64 / (DIMENSION_WIDTH/8);

wire                            tuple_fifo_we[DIMS_PER_CL-1:0];
wire  [DIMS_PER_CL-1:0]         tuple_fifo_valid;
wire  [DIMS_PER_CL-1:0]         tuple_fifo_empty;
wire  [DIMENSION_WIDTH-1:0]     tuple_fifo_data[DIMS_PER_CL-1:0];
wire  [8:0]                     tuple_fifo_count[DIMS_PER_CL-1:0];

wire                            read_line;

wire  [511:0]                   fifo_data_out;
wire                            fifo_valid_out;
wire                            fifos_empty;

reg   [3:0]                     fifo_index;  // NOTE: Assuming Minimum dimension width 32-bit and maximum cacheline width 512
reg                             flush_fifo;

reg   [3:0]                     countIn[15:0];  
reg   [31:0]                    line_data[15:0][NUM_DIMENSIONS-1:0];
wire  [31:0]                    line_data_t[15:0][NUM_DIMENSIONS-1:0];
wire  [31:0]                    fifo_in[15:0];
reg   [15:0]                    line_valid;

reg   [MAX_DIM_BITS-1:0]        NumDimsMinusOneReg;


genvar i, k;
integer j;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

assign s_axis_ready = ~line_valid[fifo_index];

generate for (i = 0; i < DIMS_PER_CL; i=i+1) begin: inData
	for(k=0; k < NUM_DIMENSIONS; k=k+1) begin: lineData 
		assign line_data_t[i][k]  = s_axis_data[k];
	end
        assign fifo_in[i] = line_data[i][countIn[i]];
end 
endgenerate

generate for (i = 0; i < DIMS_PER_CL; i=i+1) begin: fifos

	// Serializing the feed to every fifo
	always @(posedge clk) begin
		if(~rst_n) begin
			line_valid[i] <= 0;
			countIn[i]    <= 0;

			for(j=0; j < NUM_DIMENSIONS; j=j+1) begin 
				line_data[i][j]  <= 0;
			end
		end 
		else begin
			if(s_axis_valid & (fifo_index == i) & ~line_valid[i]) begin 
				line_valid[i] <= 1'b1;
				countIn[i]    <= 0;

				for(j=0; j < NUM_DIMENSIONS; j=j+1) begin 
					line_data[i][j]  <= line_data_t[i][j];
				end
			end

			if(line_valid[i]) begin 
				countIn[i] <= countIn[i] + 1'b1;
			end

			if(countIn[i] == NumDimsMinusOneReg) begin 
				line_valid[i] <= 1'b0;
				countIn[i]    <= 0;
			end
		end
	end
	
	quick_fifo  #(.FIFO_WIDTH(DIMENSION_WIDTH),        
                  .FIFO_DEPTH_BITS(9),
                  .FIFO_ALMOSTFULL_THRESHOLD(32)
                 ) fifo_x (
        .clk                (clk),
        .reset_n            (rst_n),
        .din                (fifo_in[i]),
        .we                 (line_valid[i]),

        .re                 (read_line),
        .dout               (tuple_fifo_data[i]),
        .empty              (tuple_fifo_empty[i]),
        .valid              (tuple_fifo_valid[i]),
        .full               (),
        .count              (tuple_fifo_count[i]),
        .almostfull         ()
    );


assign fifo_data_out[i*32+31:i*32] = (tuple_fifo_valid[i])? tuple_fifo_data[i] : `INT_MAX;

end


endgenerate


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

assign fifo_valid_out  = (&tuple_fifo_valid) | (flush_fifo & (|tuple_fifo_valid) & ~(|line_valid));
assign read_line       = m_axis_ready & fifo_valid_out;

assign fifos_empty     = &tuple_fifo_empty;
assign empty           = fifos_empty & ~m_axis_valid;

always @(posedge clk) begin
	if(~rst_n) begin
		fifo_index   <= 0;
		flush_fifo   <= 0;

		m_axis_data  <= 0;
		m_axis_valid <= 0;

		TuplesCount  <= 0;

		available_space <= 512;
	end 
	else begin

		NumDimsMinusOneReg <= NumDimsMinusOne;

		if( m_axis_ready ) begin 
			m_axis_data  <= fifo_data_out;
			m_axis_valid <= fifo_valid_out;
		end
		//
		if( fifos_empty ) begin 
			flush_fifo <= 1'b0;
		end
		else if( flush ) begin
			flush_fifo <= 1'b1;
		end 
		
        // 
        available_space <= 512 - tuple_fifo_count[0];

		if( s_axis_valid ) begin 
			TuplesCount <= TuplesCount + 1'b1;
				
			if( fifo_index == DIMS_PER_CL-1 ) begin
					fifo_index <= 0;
			end 
			else begin 
				fifo_index <= fifo_index + 1;
			end
		end
	end
end


endmodule // SkylineOutputFIFO
