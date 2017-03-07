module rem_onestate
	(
		clk,
		rst,

		is_sticky,

		delay_valid,
		delay_cycles,

		pred_valid,
		pred_match,
		pred_index,

		act_input,
		act_output,
		act_index
	);

	input clk;
	input rst;

	input is_sticky;

	input pred_valid;
	input pred_match;
	input [15:0] pred_index;

	input delay_valid;
	input [3:0] delay_cycles;

	input act_input;
	output reg act_output;
	output reg [15:0] act_index;

	reg activated;

	reg [3:0] delay_cycles_reg;

	reg [2+15:0] delay_shift;

	always @(posedge clk ) begin

		if (delay_valid==1) delay_cycles_reg <= delay_cycles;

		if (rst) begin
			act_output <= 0;					
			activated <= 0;
		end			
		else 
		begin 

			delay_shift <= {delay_shift[14:2],act_input,2'b00};

			activated <= (delay_cycles_reg>1) ? delay_shift[delay_cycles_reg] : act_input;

			if (pred_valid) begin

				if ((delay_cycles_reg==0 && act_input==1) || (delay_cycles_reg!=0 && activated==1) && pred_match==1) begin			
					act_output <= pred_match;	

					if (act_output==0) act_index <= pred_index;
				end
				else begin
					if (is_sticky) begin
						act_output <= act_output;
					end else begin
						act_output <= 0;
					end
				end
			end

		end
	end

endmodule