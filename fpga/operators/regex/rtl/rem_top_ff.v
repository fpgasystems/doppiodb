`default_nettype none

module rem_top_ff #(parameter CHAR_COUNT=16, DELIMITER=0, STATE_COUNT=8, INPUT_WIDTH=512, ENABLE_CIS=0)
    (
    input wire				clk,
    input wire				rst, //active high
	 //control
	 input wire				go,
	 output reg				done,
	 
	 input wire				regexConfig_valid,
	 input wire[511:0]	regexConfig_data,
  
    input wire				s_axis_valid,
	 output reg				s_axis_ready,
    input wire[INPUT_WIDTH-1:0]	s_axis_data,
	 input wire				s_axis_last,


    output wire			m_axis_valid,
	 input wire				m_axis_ready,
	 output wire[15:0]	m_axis_data
    );

	 localparam IDLE           = 0;
	 localparam GET_CONFIG		= 1;
	 localparam WAIT_NEW_STR	= 2;
	 localparam PROCESS_STR		= 3;
	 localparam WRITE_RESULT	= 4;
	 localparam PURGE				= 5;
	 localparam DONE				= 6;
	 reg [3:0]				state;
	 
  reg				input_hasdata;
  reg [INPUT_WIDTH-1:0]	input_datareg;
  reg input_waslast;
  reg				output_valid;
  wire			output_ready;
  reg				output_match;
  reg [15:0]	output_index;

  reg config_valid; 
  reg [CHAR_COUNT*8-1:0] config_chars;
  reg [CHAR_COUNT/2-1:0] config_ranges;
  reg [CHAR_COUNT-1:0] config_conds;
  reg [CHAR_COUNT-1:0] config_cis;

  reg [STATE_COUNT*(CHAR_COUNT)-1:0] config_state_pred;
  reg [STATE_COUNT*STATE_COUNT-1:0] config_state_act;  
  
  wire pred_valid;
  wire [CHAR_COUNT-1:0] pred_bits;
  wire [15:0] pred_index;
  wire pred_last;

  reg pred_valid_D;
  reg pred_last_D;
  reg [15:0] pred_index_D;

  reg [STATE_COUNT*(CHAR_COUNT)-1:0] state_pred_masks;
  reg [STATE_COUNT*STATE_COUNT-1:0] state_act_masks;

  wire [STATE_COUNT-1:0] state_match_bits;
  wire [STATE_COUNT-1:0] state_inact_bits;
  wire [STATE_COUNT-1:0] state_outact_bits;

  reg [STATE_COUNT*4-1:0] state_inact_delays;

  reg [STATE_COUNT-1:0] always_activated;
  reg [STATE_COUNT-1:0] state_act_sticky;

  reg [7:0] byte_addr;

  reg 		dec_valid;
  reg [7:0] dec_char;
  reg [1:0] wait_time;
  
  wire new_string;
  assign new_string = (WAIT_NEW_STR == state);
  
  // map ouputs
  assign m_axis_valid	= output_valid;
  assign output_ready	= m_axis_ready;
  assign m_axis_data		= (output_match == 1) ? output_index : 16'h00;


  rem_decoder  #(
  		.CHAR_COUNT(CHAR_COUNT),
  		.DELIMITER(DELIMITER)
  	) decoder_inst (
  		.clk(clk),
        .rst(rst),
        .config_valid(config_valid),
        .config_chars(config_chars),
        .config_ranges(config_ranges),
        .config_conds(config_conds),
        .config_cis(ENABLE_CIS==1 ? config_cis : 0),
        .input_valid(dec_valid),
        .input_char(dec_char),
        .index_rewind(new_string),
		.output_valid(pred_valid),
		.output_data(pred_bits),
		.output_index(pred_index),
		.output_last(pred_last)
  	);


  	genvar X;
  	generate
  		for (X=0; X<STATE_COUNT; X=X+1)
  		begin: gen_states
  			rem_onestate onestate_inst (	
				.clk(clk),
				.rst(rst || new_string),        

        .is_sticky(state_act_sticky),

        .delay_valid(config_valid),
        .delay_cycles(state_inact_delays[X*4 +: 4]),

				.pred_valid(pred_valid),
				.pred_match(state_match_bits[X]),

				.act_input(state_inact_bits[X]),
				.act_output(state_outact_bits[X])
			);

  			assign state_match_bits[X] = ((state_pred_masks[(X+1)*(CHAR_COUNT)-1:X*(CHAR_COUNT)] & pred_bits) == 0 && state_pred_masks[(X+1)*(CHAR_COUNT)-1:X*(CHAR_COUNT)]!=0) ? 0 : 1;

  			assign state_inact_bits[X] = ((state_act_masks[(X+1)*STATE_COUNT-1:X*STATE_COUNT] & state_outact_bits) != 0) ? 1 : always_activated[X];
  		end  		
  	endgenerate

    integer ind;

  	always @(posedge clk) begin

  		pred_valid_D <= pred_valid;
  		pred_last_D <= pred_last;
      pred_index_D <= pred_index;

  		if (rst) begin
			state <= IDLE;
  			output_valid <= 0;
			always_activated <= 0;
			s_axis_ready <= 0;

			config_valid <= 0;
			dec_valid <= 0;
			wait_time <= 0;


        input_hasdata <= 0;
		  input_datareg <= 0;
		  input_waslast <= 0;

        state_inact_delays <= 0;
		  done <= 0;

  		end
		else begin

			output_valid <= 0;
			config_valid <= 0;
			dec_valid <= 0;
			
			case(state)
				IDLE: begin
					if (go & ~done) begin
						input_hasdata <= 0;
						input_waslast <= 0;
						state <= GET_CONFIG;
					end
				end //IDLE
				GET_CONFIG: begin
					if (regexConfig_valid) begin
					 config_valid <= 1;
					 config_chars <= regexConfig_data[CHAR_COUNT*8-1:0];
					 config_ranges <= regexConfig_data[CHAR_COUNT/2 + CHAR_COUNT*8-1 : CHAR_COUNT*8];
					 config_conds <= regexConfig_data[CHAR_COUNT-1+CHAR_COUNT/2 + CHAR_COUNT*8:CHAR_COUNT/2 + CHAR_COUNT*8];
					 config_state_pred <= regexConfig_data[STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8-1:CHAR_COUNT/2 + CHAR_COUNT*8+CHAR_COUNT];
					 config_state_act <= regexConfig_data[STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8-1:STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8];

					 state_pred_masks <= regexConfig_data[STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8-1:CHAR_COUNT/2 + CHAR_COUNT*8+CHAR_COUNT];
					 state_act_masks <= regexConfig_data[STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8-1:STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8];

					 state_inact_delays <= regexConfig_data[STATE_COUNT*4-1+STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8 : STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8];
					 state_act_sticky <= regexConfig_data[STATE_COUNT-1+STATE_COUNT*4+STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8 : STATE_COUNT*4+STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8];

					 if (ENABLE_CIS==1) begin
					 	config_cis <= regexConfig_data[STATE_COUNT+STATE_COUNT*4+STATE_COUNT*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8 +: CHAR_COUNT];
					 end

			
					 for (ind=0; ind<STATE_COUNT; ind=ind+1) begin
						if (regexConfig_data[(ind)*STATE_COUNT+STATE_COUNT*CHAR_COUNT+CHAR_COUNT+CHAR_COUNT/2 + CHAR_COUNT*8 +: STATE_COUNT]==0) always_activated[ind]=1;
					 end
					 
					 s_axis_ready <= 0;
					 state <= WAIT_NEW_STR;
				  end
				end //GET_CONFIG
				WAIT_NEW_STR: begin
					byte_addr <= 0;
					if (wait_time != 0) begin
						wait_time <= wait_time - 1;
					end
					else begin
						byte_addr <= 0;
						input_hasdata <= 0;
						input_waslast <= 0;
						s_axis_ready <= 1;
						state <= PROCESS_STR;
					end
				end // WAIT_NEW_STR
				PROCESS_STR: begin
					//Check if we received a new word
					if (s_axis_valid && s_axis_ready) begin
						s_axis_ready <= 0;
						input_hasdata <= 1;
						input_datareg <= s_axis_data;
						input_waslast <= s_axis_last;
					end
					//Check if we have a word to process
					if (input_hasdata==1) begin
						// Process cache line byte 0..63
						if (byte_addr<=(INPUT_WIDTH/8)-1) begin
						  dec_valid <= 1;
						  dec_char <= input_datareg[byte_addr[5:0]*8 +: 8];
						  byte_addr <= byte_addr+1;            
						  
						end 
						// Check if there is another cache line to be processed
						if (byte_addr==((INPUT_WIDTH/8)-1) && input_waslast == 0) begin
						  byte_addr <= 0;
						  s_axis_ready <= 1;
						  input_hasdata <= 0;
						end
						else if (byte_addr==((INPUT_WIDTH/8)-1) && input_waslast==1) begin
						  byte_addr <= 0;
						  input_hasdata <= 0; //this kills this condition and waits for pred_valid_D
						end //byte_addr
					end //hasdata
					
					// Check for a match or last from the remdecoder
					if (pred_valid_D==1 && (state_outact_bits[STATE_COUNT-1]==1 || pred_last_D==1)) begin            
						output_valid <= 1;
						output_match <= state_outact_bits[STATE_COUNT-1]==1;
						output_index <= pred_index_D;
						s_axis_ready <= 0; // is already 0
						state <= WRITE_RESULT;
					end //pred_valid_D						
				end //PROCESS_DATA

				WRITE_RESULT: begin
					// Check if output got accepted
					output_valid <= 1;
					output_match <= output_match;
					output_index <= output_index;
					if (output_valid==1 && output_ready==1) begin
						output_valid <= 0;
						if (input_waslast) begin
							s_axis_ready <= 0; // is already 0
							wait_time <= 2'b11;
							state <= WAIT_NEW_STR;
						end
						else begin
							s_axis_ready <= 1;
							state <= PURGE;
						end
					end
				end //WRITE_RESULT
				PURGE: begin
					s_axis_ready <= 1;
					if (s_axis_valid && s_axis_ready && s_axis_last) begin
						s_axis_ready <= 0;
						wait_time <= 2'b11;
						state <= WAIT_NEW_STR;
					end
				end //PURGE
				DONE: begin // WAIT HERE UNTIL RESET
					s_axis_ready <= 0;
					state <= IDLE;
					done <= 1;
				end
			endcase
  		end //else reset
  	end //posedge
	
	//for debug
	reg[15:0] out_coutner;
	always @(posedge clk) begin
		if (rst == 1) begin
			out_coutner <= 0;
		end
		else begin
			if (m_axis_valid && m_axis_ready) begin
				out_coutner <= out_coutner + 1;
			end
		end
	end


endmodule

`default_nettype wire