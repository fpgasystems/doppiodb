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

module test_and_count #(parameter ELEMENT_WIDTH=32)(


	input  wire                        clk,
	input  wire                        rst_n, 

	input  wire   [511:0]  			   data_pack_in,
	input  wire                        data_in_valid, 
	input  wire   [3:0]                test_type,
	input  wire   [ELEMENT_WIDTH-1:0]  test_condition, 
	input  wire                        data_in_last, 
	output wire                        in_ready, 

	output reg    [31:0]               result_count, 
	output reg                         result_valid,
	input  wire                        out_ready
	);


parameter NUM_ELEMENTS = 512 / ELEMENT_WIDTH;

wire  less_w[NUM_ELEMENTS-1:0];
wire  equal_w[NUM_ELEMENTS-1:0];

reg   less[NUM_ELEMENTS-1:0];
reg   equal[NUM_ELEMENTS-1:0];
reg   notEqual[NUM_ELEMENTS-1:0];
reg   greater[NUM_ELEMENTS-1:0];
reg   greaterEqual[NUM_ELEMENTS-1:0];
reg   lessEqual[NUM_ELEMENTS-1:0];

reg  [NUM_ELEMENTS-1:0]  condition_test_result;

reg   [31:0]                          temp_count;

reg                                   data_in_valid_d1;
reg                                   data_in_valid_d2;

reg                                   data_in_last_d1;
reg                                   data_in_last_d2;
reg                                   data_in_last_d3;
reg                                   data_in_last_d4;
reg                                   data_in_last_d5;

wire 								  matches_valid;
wire  [5:0] 						  matches_count;

reg   [3:0]                           test_type_d1;
reg                                   data_valid;
reg                                   data_last;


localparam [2:0] 
			EQUAL           = 3'b000,
			NOT_EQUAL       = 3'b001,
			LESS_THAN       = 3'b010, 
			LESS_EQUAL      = 3'b011, 
			GREATER_THAN    = 3'b100,
			GREATER_EQUAL   = 3'b101;



/////////////////////////////////// cycle 0: buffer input signals /////////////////////////////////

assign in_ready = out_ready | ~result_valid;

always@(posedge clk) begin
	if(~rst_n) begin
		data_in_valid_d1 <= 0;
		data_in_valid_d2 <= 0;
		data_in_last_d1  <= 0;
		data_in_last_d2  <= 0;
		data_in_last_d3  <= 0;
		data_in_last_d4  <= 0;
		data_in_last_d5  <= 0;


		test_type_d1     <= 0;

		data_valid       <= 0;
		data_last        <= 0;
	end
	else begin 
		data_in_valid_d1 <= data_in_valid;
		data_in_valid_d2 <= data_in_valid_d1;

		data_in_last_d1  <= data_in_last;
		data_in_last_d2  <= data_in_last_d1;
		data_in_last_d3  <= data_in_last_d2;
		data_in_last_d4  <= data_in_last_d3;
		data_in_last_d5  <= data_in_last_d4;

		test_type_d1     <= test_type;

		if(matches_valid) begin 
			data_valid       <= 1'b1;
		end
		if(data_in_last_d5) begin
			data_last        <= 1'b1;
		end 
	end
end 

/////////////////////////////////// cycle 1: evaluate conditions /////////////////////////////////
// test for == and less than

generate
	genvar i;
	for(i = 0; i < NUM_ELEMENTS; i = i + 1) begin: l_e_cmp
		
assign less_w[i]  = (data_pack_in[(i+1)*ELEMENT_WIDTH-1 : i*ELEMENT_WIDTH] < test_condition);
assign equal_w[i] = (data_pack_in[(i+1)*ELEMENT_WIDTH-1 : i*ELEMENT_WIDTH] == test_condition);
 

// produce the rest of all other condition tests
always@(posedge clk) begin 
	if( ~ rst_n ) begin 
		greater[i]      <= 0;
		greaterEqual[i] <= 0;
		lessEqual[i]    <= 0;
		notEqual[i]     <= 0;
		less[i]         <= 0;
		equal[i]        <= 0;
	end 
	else if(data_in_valid) begin 
		greater[i]      <= ~less_w[i] & ~equal_w[i];
		greaterEqual[i] <= ~less_w[i];
		lessEqual[i]    <= less_w[i] | equal_w[i];
		notEqual[i]     <= ~equal_w[i];
		less[i]         <= less_w[i];
		equal[i]        <= equal_w[i];			
	end 
	else begin
		greater[i]      <= 0;
		greaterEqual[i] <= 0;
		lessEqual[i]    <= 0;
		notEqual[i]     <= 0;
		less[i]         <= 0;
		equal[i]        <= 0;
	end
end 

/////////////////////////////////// cycle 1: get the right condition test /////////////////////////////////

always@(posedge clk) begin
	case(test_type_d1)
		LESS_THAN:       condition_test_result[i] <= less[i];
		LESS_EQUAL:		 condition_test_result[i] <= lessEqual[i];
		GREATER_THAN:    condition_test_result[i] <= greater[i];
		GREATER_EQUAL:   condition_test_result[i] <= greaterEqual[i];
		EQUAL:           condition_test_result[i] <= equal[i];
		NOT_EQUAL:       condition_test_result[i] <= notEqual[i];
		default:         condition_test_result[i] <= 0;
	endcase 
end
	end
endgenerate


onesCounter onesCounter
(
	.clk            (clk),
	.rst_n          (rst_n),

	.data_in_valid  (data_in_valid_d2),
	.data_in        (condition_test_result),

	.count_valid    (matches_valid),
	.count          (matches_count)
	);


always@(posedge clk) begin
	if(~rst_n) begin
		temp_count <= 0;
	end
	else if(matches_valid) begin
		temp_count <= temp_count + matches_count;
	end
end

/////////////////////////////////// cycle 2: Assign output signals /////////////////////////////////
always @(posedge clk) begin
	if (~rst_n) begin
		// reset
		result_count <= 0;
		result_valid <= 0;
	end
	else begin
		result_count <= temp_count;
		result_valid <= data_last & data_valid;
	end
end 

endmodule