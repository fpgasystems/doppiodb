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

module test_count(
    input   wire                        clk,
    input   wire                        rst_n,
    //-------------------------------------------------//
	input   wire 					    start_um,
    input   wire [511:0]                um_params,
    output  reg                         um_done,
    // TX RD
    output  reg  [57:0]                 um_tx_rd_addr,
    output  reg  [7:0]                  um_tx_rd_tag,
    output  reg  						um_tx_rd_valid,
    input   wire                        um_tx_rd_ready,
    // TX WR
    output  reg  [57:0]                 um_tx_wr_addr,
    output  reg  [7:0]                  um_tx_wr_tag,
    output  reg 						um_tx_wr_valid,
    output  reg  [511:0]			    um_tx_data,
    input   wire                        um_tx_wr_ready,
    // RX RD
    input   wire [7:0]                  um_rx_rd_tag,
    input   wire [511:0]                um_rx_data,
    input   wire                        um_rx_rd_valid,
    output  wire                        um_rx_rd_ready,
    // RX WR 
    input   wire                        um_rx_wr_valid,
    input   wire [7:0]                  um_rx_wr_tag
);

wire [31:0]                 usr_dout;
wire                        usr_dout_valid;
wire                        usr_dout_last;
wire                        usr_dout_ready;

reg                         um_activated;
reg                         rd_done;
reg  [31:0]                 rd_cnt;
reg  [31:0]                 rx_rd_cnt;

wire [31:0]                 rd_cnt_inc;
wire [31:0]                 rx_rd_cnt_inc;

reg  [511:0]                um_params_reg;

reg                         ret_set;

assign um_rx_rd_ready = 1'b1;
///////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
    if (~rst_n) begin
        // reset
        um_activated <= 1'b0;
    end
    else if(um_done) begin
        um_activated <= 1'b0;
    end
    else if (start_um ) begin
        um_activated <= 1'b1;

    end
end

always @(posedge clk) begin
    if (start_um) begin
        um_params_reg <= um_params;
    end
end
/////////////////////// Write Result Back /////////////////////////////////////////
always @(posedge clk) begin
    if(~rst_n) begin
        um_tx_wr_valid <= 0;
        ret_set        <= 0;
        um_done        <= 0;
    end
    else if(~ret_set) begin
        um_tx_wr_valid <= usr_dout_valid;
        ret_set        <= usr_dout_valid;
        um_done        <= 0; 
    end 
    else if(um_tx_wr_ready) begin
        um_tx_wr_valid <= 0;
        //ret_set        <= 0;
        um_done        <= 1'b1;
    end 
end

always @(posedge clk) begin
    um_tx_wr_addr       <= um_params_reg[127:70];
    um_tx_wr_tag        <= 0;
    um_tx_data[511: 32] <= 0;
    if(~ret_set) begin
       um_tx_data[31:0] <= usr_dout;
    end 
end

/////////////////////// read data in /////////////////////////////////////////
// TX RD
always @(posedge clk) begin
    if (~rst_n) begin
        // reset
        um_tx_rd_addr  <= 0;
        um_tx_rd_valid <= 0;
        rd_cnt         <= 0;
        um_tx_rd_tag   <= 0;

        rd_done        <= 0;
    end
    else if (um_tx_rd_ready & um_activated) begin
        if( ~rd_done) begin
            um_tx_rd_addr  <= um_params_reg[63:6] + rd_cnt;
            um_tx_rd_valid <= rd_cnt != um_params_reg[159:128];
            rd_cnt         <= rd_cnt_inc;
            um_tx_rd_tag   <= 0;
            rd_done        <= 0;

            if(rd_cnt_inc == um_params[159:128]) begin 
                um_tx_rd_tag   <= 1;
                rd_done        <= 1'b1;
            end
        end
        else begin 
            um_tx_rd_valid <= 0;
        end   
    end
end

assign rd_cnt_inc = rd_cnt + 1'b1;
///////////////////////////////////////////////////////////////////////////////////
always @(posedge clk) begin
    if(~rst_n) begin
        rx_rd_cnt <= 0;
    end 
    else if(um_rx_rd_valid) begin
        rx_rd_cnt <= rx_rd_cnt_inc;
    end
end

assign rx_rd_cnt_inc = rx_rd_cnt + 1'b1;
///////////////////////////////////////////////////////////////////////////////////
/////////////////////// Instantiate User Logic Here ///////////////////////////////
test_and_count #(.ELEMENT_WIDTH(16))

test_and_count(
    .clk                                (clk),
    .rst_n                              (rst_n),

    .data_pack_in                       (um_rx_data),
    .data_in_valid                      (um_rx_rd_valid),
    .data_in_last                       ((rx_rd_cnt_inc == um_params_reg[159:128]) & um_rx_rd_valid),
    .in_ready                           (),
    .test_type                          (um_params_reg[163:160]),
    .test_condition                     (um_params_reg[207:192]),

    .result_count                       (usr_dout),
    .result_valid                       (usr_dout_valid),
    .out_ready                          (1'b1)
    );


endmodule
