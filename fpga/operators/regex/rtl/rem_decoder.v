`default_nettype none

module rem_decoder #(parameter CHAR_COUNT=16, DELIMITER=0, ENABLE_CIS=0)
    (
    input wire								clk,
    input wire								rst, //active high
    
	 input wire								config_valid,
    input wire[CHAR_COUNT*8-1:0]		config_chars, // an eight bit character for each checker
    input wire[(CHAR_COUNT/2)-1:0]	config_ranges, // two eight bit characters for each range checker (>=LOW, <LARGE)
    input wire[CHAR_COUNT-1:0]		config_conds, // one bit to indicate whether the checker should only match if the previous one in line matched
    input wire[CHAR_COUNT-1:0]    config_cis, // one bit to indicate whether the checker should match lower case ASCII characters if the input is an upper case one
    
	 input wire								input_valid,
    input wire[7:0]						input_char,
    input wire								index_rewind,
	 
    output reg								output_valid, 
    output reg[CHAR_COUNT-1:0]		output_data, // bitmask for each char and range matcher  
    output reg[15:0]						output_index, // the sequence number of the character in the string 
    output reg								output_last // high for the last character (delimiter)
    );
  
  reg [15:0] index;

  reg in_reg_valid;
  reg [7:0] in_reg_char;

  wire [CHAR_COUNT:0] match_bits;

  wire [CHAR_COUNT-1:0] intermediary;

  assign match_bits[0] = 0;

  genvar X;  
  generate  
    for (X=0; X < CHAR_COUNT; X=X+2)  
    begin: gen_charmatch  
      rem_halfrange #(
        .HIGH_HALF(0),
        .ENABLE_CIS(ENABLE_CIS)
        ) match_low (
        .clk(clk),
        .rst(rst),
        .config_valid(config_valid),
        .config_char(config_chars[X*8+7:X*8]),
        .config_chained(config_conds[X]),
        .config_range_en(1'b0),
        .config_cis_en(ENABLE_CIS==1 ? config_cis : 0),
        .input_valid(input_valid),
        .input_char(input_char),        
        .prev_matched(match_bits[X]),
        .this_matched(match_bits[X+1]),

        .low_smaller(),
        .this_smaller(intermediary[X])
    );

      rem_halfrange #(
        .HIGH_HALF(1),
        .ENABLE_CIS(ENABLE_CIS)
        ) match_high (
        .clk(clk),
        .rst(rst),
        .config_valid(config_valid),
        .config_char(config_chars[(X+1)*8+7:(X+1)*8]),
        .config_chained(config_conds[(X+1)]),
        .config_range_en(config_ranges[(X+1)/2]),
        .config_cis_en(ENABLE_CIS==1 ? config_cis : 0),
        .input_valid(input_valid),
        .input_char(input_char),
        .prev_matched(match_bits[(X+1)]),
        .this_matched(match_bits[(X+1)+1]),

        .low_smaller(intermediary[X]),
        .this_smaller()
    );
    end  
  endgenerate  
  

  
  always @(posedge clk) begin
    if (rst) begin
      output_valid <= 0;
      in_reg_valid <= 0;   
      index <= 0;
    end
    else begin
      in_reg_valid <= input_valid;
      in_reg_char <= input_char;

      if (in_reg_valid) begin
        index <= index+1;      
        if (in_reg_char==DELIMITER) index <= 0;
      end

      output_valid <= in_reg_valid;
      output_data <= match_bits[CHAR_COUNT:1];
      output_last <= (in_reg_char==DELIMITER) ? 1 : 0;
      output_index <= index;

      if (index_rewind==1) begin
        index <= 0;
      end
    end
  end //always
  
endmodule

`default_nettype wire

  
