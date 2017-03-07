module rem_halfrange 
    #(
      parameter HIGH_HALF = 0, 
      parameter ENABLE_CIS = 0
      )
    (
    clk,
    rst,
    config_valid,
    config_char,
    config_chained,
    config_range_en,
    config_cis_en,
    input_valid,
    input_char,
    prev_matched,    
    this_matched,

    low_smaller,
    this_smaller
    );


  input clk;
  input rst;

  input config_valid;
  input [7:0] config_char;
  input       config_chained;
  input       config_range_en; // only relevant if LOW_PART=0
  input       config_cis_en;

  input       input_valid;
  input [7:0] input_char;

  input       prev_matched;
  input       low_smaller; // only relevant if LOW_PART=0
  output      this_matched;
  output      this_smaller; // only relevant if LOW_PART=1

  reg         char_match;
  reg [7:0]   char_data;
  reg [7:0]   char_data_lowerc;
  reg 	      is_chained;
  reg         is_ranged;
         

  assign this_matched = char_match;

  assign this_smaller = (HIGH_HALF==0 && input_valid==1) ? input_char>char_data-1 : 0;  
  
  always @(posedge clk)
  begin
    
    if(rst) begin
      char_data <= 0;
      char_match <= 0;
    end    
    else begin      
      
      if (input_valid==1) begin

        if (char_data==input_char || (ENABLE_CIS==1 && char_data_lowerc==input_char)) begin
          char_match <= is_chained ? prev_matched : 1;
        end
        else begin
          if (HIGH_HALF==1 && is_ranged==1 && char_data>input_char && low_smaller==1) begin
            char_match <= 1;
          end 
          else begin
            char_match <= 0;               
          end
        end 
      end
      
      if (config_valid==1) begin
        char_data <= config_char;
        if (ENABLE_CIS==1) begin
          char_data_lowerc <= config_char + 32;
        end
        is_chained <= config_chained;
        is_ranged <= config_range_en;
        char_match <= 0;
      end
      

    end              	     
  end

endmodule
