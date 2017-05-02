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

`default_nettype none


module regex_mdb(
    input   wire                                   clk,
    input   wire                                   Clk_400,
    input   wire                                   rst_n,
    //-------------------------------------------------//
	input   wire 					               start_um,
    input   wire [1023:0]                          um_params,
    output  wire                                   um_done,
    output  wire [10*32-1:0]                     um_state_counters,
    output  wire                                   um_state_counters_valid,
    // TX RD
    output  reg  [57:0]                            um_tx_rd_addr,
    output  reg  [7:0]                             um_tx_rd_tag,
    output  reg  						           um_tx_rd_valid,
    input   wire                                   um_tx_rd_ready,
    // TX WR
    output  reg  [57:0]                            um_tx_wr_addr,
    output  reg  [7:0]                             um_tx_wr_tag,
    output  reg 						           um_tx_wr_valid,
    output  reg  [511:0]			               um_tx_data,
    input   wire                                   um_tx_wr_ready,
    // RX RD
    input   wire [7:0]                             um_rx_rd_tag,
    input   wire [511:0]                           um_rx_data,
    input   wire                                   um_rx_rd_valid,
    output  wire                                   um_rx_rd_ready,
    // RX WR 
    input   wire                                   um_rx_wr_valid,
    input   wire [7:0]                             um_rx_wr_tag
);

// TX RD
wire  [57:0]                 tx_rd_addr;
wire                         tx_rd_tag;
wire                         tx_rd_valid;

// TX WR
wire  [57:0]                 tx_wr_addr;
wire  [511:0]                tx_data;
wire                         tx_wr_valid;

reg   [1023:0]               um_params_reg = 0;
reg                          regex_done_d1 = 0;
reg                          um_activated = 0;
wire                         regex_done;


///////////////////////////////////////////////////////////////////////////////
//////////////////////////// Module Control Logic  ////////////////////////////
// Register afu parameters
always @(posedge clk) begin
    if(~rst_n) begin
        um_params_reg <= 0;
    end 
    else if (start_um) begin
        um_params_reg <= um_params;
    end
    else if(regex_done) begin
        um_params_reg <=  0;
    end
end
// module done, activation logic
always@(posedge clk) begin
    if(~rst_n) begin
        regex_done_d1  <= 0;
        um_activated   <= 0;
    end
    else begin
        if(regex_done) begin
            regex_done_d1 <= 1'b1;
        end 
        
        if(regex_done) begin
            um_activated <= 1'b0;
        end
        else if (start_um ) begin
            um_activated <= 1'b1;
        end
    end 
end 

assign um_done = regex_done_d1 & ~um_tx_wr_valid;
////////////////////////////////////////////////// Writing Interface ///////////////////////////////////
// valid 
always@(posedge clk) begin 
    if(~rst_n) begin
        um_tx_wr_valid <= 0;
    end 
    else if(um_tx_wr_ready) begin
        um_tx_wr_valid <= tx_wr_valid;
    end 
end 

// data, addr, tag
always@(posedge clk) begin 
    if(um_tx_wr_ready) begin
        um_tx_wr_addr  <= tx_wr_addr + um_params_reg[191:134];
        um_tx_wr_tag   <= 9'b0;
        um_tx_data     <= tx_data;
    end 
end 
////////////////////////////////////////////////// Reading Interface ///////////////////////////////////
// valid
always@(posedge clk) begin 
    if(~rst_n) begin
        um_tx_rd_valid  <= 0;
    end 
    else if(um_tx_rd_ready) begin
        um_tx_rd_valid <= tx_rd_valid;
    end 
end 
// addr, tag
always@(posedge clk) begin 
    if(um_tx_rd_ready) begin
        um_tx_rd_addr  <= tx_rd_addr;
        um_tx_rd_tag   <= {7'b0, tx_rd_tag};
    end 
end 
////////////////////////////////////////////////////////////////////////////////////////////
mdb_batparser_string myafu (
        .clk                      (clk),
        .Clk_400                  (Clk_400),
        .rst                      (~rst_n),
        //control
	    .go                       (um_activated),
        .done                     (regex_done),
	    //writes
		.m_axis_write_req_valid   (tx_wr_valid),
		.m_axis_write_req_ready   (um_tx_wr_ready),
		.m_axis_write_req_addr    (tx_wr_addr),
		.m_axis_write_req_data    (tx_data),
		//read requests
		.m_axis_read_req_valid    (tx_rd_valid),
		.m_axis_read_req_ready    (um_tx_rd_ready),
		.m_axis_read_req_addr     (tx_rd_addr),
		.m_axis_read_req_tag      (tx_rd_tag),
		//read responses
		.s_axis_read_rsp_valid    (um_rx_rd_valid),
		.s_axis_read_rsp_ready    (um_rx_rd_ready),
		.s_axis_read_rsp_data     (um_rx_data),
		.s_axis_read_rsp_tag      (um_rx_rd_tag[0]),
		//parameters
        .re2xy_BatCount           (um_params_reg[223:192]),   // num_cl
        .re2xy_BaseAddr           (um_params_reg[57:0]),      // pSource
        .re2xy_VBaseAddr          (um_params_reg[121:64]),    // vpSource
        .re2xy_TailWidth          (um_params_reg[231:224]),   // param2
		//regex config
        .regexConfig_valid        (um_activated),
        .regexConfig_data         (um_params_reg[1023:512]),
        .stats_counter            (um_state_counters)
    );

assign um_state_counters_valid    = 1'b0;

endmodule

`default_nettype wire