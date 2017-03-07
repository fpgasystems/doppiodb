`default_nettype none

module async_axififo
	#(
		parameter BUS_SIZE_DATA=16,
		parameter LAST_EN=0
	 )
	(
		input  wire								s_axis_clk,
		input  wire								m_axis_clk,
		input  wire								rst,
		
		input  wire								s_axis_valid,
		output wire								s_axis_ready,
		input  wire[BUS_SIZE_DATA-1:0]		    s_axis_data,
		input  wire								s_axis_last,
		
		output wire  							m_axis_valid,
		input  wire								m_axis_ready,
		output wire[BUS_SIZE_DATA-1:0]	        m_axis_data,
		output wire 							m_axis_last
	);
	
	

	wire  ren, wen, full, full2, full_last, empty, empty2, empty_last;

generate
   if (BUS_SIZE_DATA == 512) begin
		fifo_async_256 fifo_async_256_inst1 (
			.aclr(rst),
			.wrclk(s_axis_clk),
			.wrreq(wen),
			.data(s_axis_data[255:0]),
			.wrfull(full),
			
			.rdclk(m_axis_clk),
			.rdreq(ren),
			.q(m_axis_data[255:0]),
			.rdempty(empty)
		);
		fifo_async_256 fifo_async_256_inst2 (
			.aclr(rst),
			.wrclk(s_axis_clk),
			.wrreq(wen),
			.data(s_axis_data[511:256]),
			.wrfull(full2),
			
			.rdclk(m_axis_clk),
			.rdreq(ren),
			.q(m_axis_data[511:256]),
			.rdempty(empty2)
		);
	end
	else if(BUS_SIZE_DATA == 256) begin
	
	fifo_async_256 fifo_async_256_inst (
			.aclr(rst),
			.wrclk(s_axis_clk),
			.wrreq(wen),
			.data(s_axis_data),
			.wrfull(full),
			
			.rdclk(m_axis_clk),
			.rdreq(ren),
			.q(m_axis_data),
			.rdempty(empty)
		);
		assign full2 = 0;
		assign empty2 = 0;
	end 
	else begin
		fifo_async_16 fifo_async_16_inst (
			.aclr(rst),
			.wrclk(s_axis_clk),
			.wrreq(wen),
			.data(s_axis_data),
			.wrfull(full),
			
			.rdclk(m_axis_clk),
			.rdreq(ren),
			.q(m_axis_data),
			.rdempty(empty)
		);
		assign full2 = 0;
		assign empty2 = 0;
	end
	if (LAST_EN) begin
	fifo_async_1 fifo_async_last_inst (
			.aclr(rst),
			.wrclk(s_axis_clk),
			.wrreq(wen),
			.data(s_axis_last),
			.wrfull(full_last),
			
			.rdclk(m_axis_clk),
			.rdreq(ren),
			.q(m_axis_last),
			.rdempty(empty_last)
		);
	end
	else begin
	assign full_last = 0;
	assign empty_last = 0;
	assign m_axis_last = 0;
	end
endgenerate

   
    assign ren = m_axis_ready & ~empty & ~empty2 & ~empty_last;
    assign wen = s_axis_valid & ~full & ~full2 & ~full_last;


    assign s_axis_ready = ~full & ~full2 & ~full_last;

    assign m_axis_valid = ~empty & ~empty2 & ~empty_last;
	

endmodule

`default_nettype wire
