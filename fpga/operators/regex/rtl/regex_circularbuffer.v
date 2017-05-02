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

//`default_nettype none

module regex_circularbuffer(
    input   wire                        clk,
    input   wire                        reset_n,
    //-------------------------------------------------//
	input   wire 					    start_um,
    input   wire [511:0]                um_params,
    output  wire                        um_rd_done,
    output  wire                        um_wr_done,
    // TX RD
    output  wire [57:0]                 um_tx_rd_addr,
    output  wire [8:0]                  um_tx_rd_tag,
    output  wire 						um_tx_rd_valid,
    input   wire                        um_tx_rd_free,
    // TX WR
    output  wire [57:0]                 um_tx_wr_addr,
    output  wire [8:0]                  um_tx_wr_tag,
    output  wire						um_tx_wr_valid,
    output  wire [511:0]			    um_tx_data,
    input   wire                        um_tx_wr_free,
    // RX RD
    input   wire [8:0]                  um_rx_rd_tag,
    input   wire [511:0]                um_rx_rd_data,
    input   wire                        um_rx_rd_valid,
    // RX WR 
    input   wire                        um_rx_wr_valid,
    input   wire [8:0]                  um_rx_wr_tag
);

wire [15:0]                 usr_dout;
wire                        usr_dout_valid;
wire                        usr_dout_last;
wire                        usr_dout_flush;
wire                        usr_dout_ready;

wire [511:0]                usr_din;
wire                        usr_din_valid;
wire                        usr_din_last;
wire                        usr_din_empty;
wire                        usr_din_ready;

wire                        producer_done;
wire                        consumer_done;


// TX RD
wire  [57:0]                 ocrb_tx_rd_addr;
wire  [7:0]                  ocrb_tx_rd_tag;
wire                         ocrb_tx_rd_valid;
wire                         ocrb_tx_rd_free;
// TX WR
wire  [57:0]                 ocrb_tx_wr_addr;
wire  [7:0]                  ocrb_tx_wr_tag;
wire                         ocrb_tx_wr_valid;
wire  [511:0]                ocrb_tx_data;
wire                         ocrb_tx_wr_free;
// RX RD
wire  [7:0]                  ocrb_rx_rd_tag;
wire  [511:0]                ocrb_rx_rd_data;
wire                         ocrb_rx_rd_valid;
// RX WR 
wire                         ocrb_rx_wr_valid;
wire  [7:0]                  ocrb_rx_wr_tag;

// TX RD
wire  [57:0]                 icrb_tx_rd_addr;
wire  [7:0]                  icrb_tx_rd_tag;
wire                         icrb_tx_rd_valid;
wire                         icrb_tx_rd_free;
// TX WR
wire  [57:0]                 icrb_tx_wr_addr;
wire  [7:0]                  icrb_tx_wr_tag;
wire                         icrb_tx_wr_valid;
wire  [511:0]                icrb_tx_data;
wire                         icrb_tx_wr_free;
// RX RD
wire  [7:0]                  icrb_rx_rd_tag;
wire  [511:0]                icrb_rx_rd_data;
wire                         icrb_rx_rd_valid;
// RX WR 
wire                         icrb_rx_wr_valid;
wire  [7:0]                  icrb_rx_wr_tag;

wire   [15:0]      producer_din;
wire               producer_last;
wire               producer_flush;
wire               producer_ready;
wire               user_to_producer_full;
wire               user_to_producer_valid;
////

////
assign um_rd_done = consumer_done;
assign um_wr_done = producer_done;

//////////////////////////// TX_RD Selector

assign um_tx_rd_addr   = (ocrb_tx_rd_valid)? {ocrb_tx_rd_addr} : {icrb_tx_rd_addr};
assign um_tx_rd_tag    = (ocrb_tx_rd_valid)? {1'b1, ocrb_tx_rd_tag}  : {1'b0, icrb_tx_rd_tag};
assign um_tx_rd_valid  = ocrb_tx_rd_valid | icrb_tx_rd_valid;

assign ocrb_tx_rd_free = um_tx_rd_free;
assign icrb_tx_rd_free = um_tx_rd_free & ~ocrb_tx_rd_valid;

///////////////////////////// TX_WR Selector

assign um_tx_wr_addr   = (icrb_tx_wr_valid)? icrb_tx_wr_addr : ocrb_tx_wr_addr;
assign um_tx_wr_tag    = (icrb_tx_wr_valid)? {1'b1, icrb_tx_wr_tag}  : {1'b0, ocrb_tx_wr_tag};
assign um_tx_data      = (icrb_tx_wr_valid)? icrb_tx_data    : ocrb_tx_data;
assign um_tx_wr_valid  = ocrb_tx_wr_valid | icrb_tx_wr_valid;

assign icrb_tx_wr_free = um_tx_wr_free;
assign ocrb_tx_wr_free = um_tx_wr_free & ~icrb_tx_wr_valid;

//////////////////////////// RX_RD Distributor
assign ocrb_rx_rd_tag   = um_rx_rd_tag[7:0];
assign ocrb_rx_rd_data  = um_rx_rd_data;
assign ocrb_rx_rd_valid = um_rx_rd_valid & um_rx_rd_tag[8];

assign icrb_rx_rd_tag   = um_rx_rd_tag[7:0];
assign icrb_rx_rd_data  = um_rx_rd_data;
assign icrb_rx_rd_valid = um_rx_rd_valid & ~um_rx_rd_tag[8];

//////////////////////////// RX_WR Distributor
assign ocrb_rx_wr_tag   = um_rx_wr_tag[7:0];
assign ocrb_rx_wr_valid = um_rx_wr_valid & ~um_rx_wr_tag[8];

assign icrb_rx_wr_tag   = um_rx_wr_tag[7:0];
assign icrb_rx_wr_valid = um_rx_wr_valid & um_rx_wr_tag[8];

/////////////// Producer CRB End
wire             producer_valid;
reg              output_done;
wire             producer_last_t;
wire             user_to_producer_empty;
reg              terminate_cond_wr_set;
wire             consumer_fifo_terminate;	

assign usr_dout_ready = ~user_to_producer_full;

crb_producer #(.TYPE_SIZE_IN_BYTES(2)) crb_producer (
    .clk                                (clk),
    .reset_n                            (reset_n),
    //-------------------------------------------------//
    .start_crb                          (start_um),
    .crb_struct_addr                    (um_params[127:70]),
    //.dst_size                           (um_params[159:128]),
    .crb_done                           (producer_done),
    // TX RD
    .crb_tx_rd_addr                     (ocrb_tx_rd_addr),
    .crb_tx_rd_tag                      (ocrb_tx_rd_tag),
    .crb_tx_rd_valid                    (ocrb_tx_rd_valid),
    .crb_tx_rd_free                     (ocrb_tx_rd_free),
    // TX WR
    .crb_tx_wr_addr                     (ocrb_tx_wr_addr),
    .crb_tx_wr_tag                      (ocrb_tx_wr_tag),
    .crb_tx_wr_valid                    (ocrb_tx_wr_valid),
    .crb_tx_data                        (ocrb_tx_data),
    .crb_tx_wr_free                     (ocrb_tx_wr_free),
    // RX RD
    .crb_rx_rd_tag                      (ocrb_rx_rd_tag),
    .crb_rx_rd_data                     (ocrb_rx_rd_data),
    .crb_rx_rd_valid                    (ocrb_rx_rd_valid),
    // RX WR 
    .crb_rx_wr_valid                    (ocrb_rx_wr_valid),
    .crb_rx_wr_tag                      (ocrb_rx_wr_tag),
    //
    .crb_din                            (producer_din),
    .crb_din_we                         (user_to_producer_valid),
    .crb_din_last                       (producer_last),
    .crb_flush                          (producer_flush),
    .crb_ready                          (producer_ready)
);

quick_fifo  #(.FIFO_WIDTH(16 + 1 + 1 + 1),        
            .FIFO_DEPTH_BITS(9),
            .FIFO_ALMOSTFULL_THRESHOLD(32)
            ) user_to_producer(
        .clk                (clk),
        .reset_n            (reset_n),
        .din                ({usr_dout_valid, usr_dout_flush, usr_dout_last, usr_dout}),
        .we                 (usr_dout_valid),
        .re                 (producer_ready),
        .dout               ({producer_valid, producer_flush, producer_last_t, producer_din}),
        .empty              (user_to_producer_empty),
        .valid              (user_to_producer_valid),
        .full               (user_to_producer_full),
        .count              (),
        .almostfull         ()
    );

always @(posedge clk) begin
    if(~reset_n) begin
        terminate_cond_wr_set <= 0;
    end 
    else begin
        terminate_cond_wr_set <= (producer_done)? 1'b0 :  (usr_dout_last | terminate_cond_wr_set);
    end
end

assign producer_last = (producer_last_t & user_to_producer_valid) | (terminate_cond_wr_set & user_to_producer_empty);
/////////////// Consumer CRB End

wire  [511:0]    consumer_fifo_dout;
wire             consumer_fifo_valid;
wire             consumer_fifo_last;
wire             consumer_fifo_empty;
wire             consumer_to_user_full;
wire             consumer_to_user_valid;

reg              terminate_cond_rd_set;
wire             usr_din_last_t;
wire             consumer_to_user_empty;
wire             consumer_finished;

crb_consumer #(.TYPE_SIZE_IN_BYTES(64)) crb_consumer (
    .clk                                (clk),
    .reset_n                            (reset_n),
    //-------------------------------------------------//
    .start_crb                          (start_um),
    .crb_struct_addr                    (um_params[63:6]),
    //.src_size                           (um_params[159:128]),
    .crb_done                           (consumer_done),
    // TX RD
    .crb_tx_rd_addr                     (icrb_tx_rd_addr),
    .crb_tx_rd_tag                      (icrb_tx_rd_tag),
    .crb_tx_rd_valid                    (icrb_tx_rd_valid),
    .crb_tx_rd_free                     (icrb_tx_rd_free),
    // TX WR
    .crb_tx_wr_addr                     (icrb_tx_wr_addr),
    .crb_tx_wr_tag                      (icrb_tx_wr_tag),
    .crb_tx_wr_valid                    (icrb_tx_wr_valid),
    .crb_tx_data                        (icrb_tx_data),
    .crb_tx_wr_free                     (icrb_tx_wr_free),
    // RX RD
    .crb_rx_rd_tag                      (icrb_rx_rd_tag),
    .crb_rx_rd_data                     (icrb_rx_rd_data),
    .crb_rx_rd_valid                    (icrb_rx_rd_valid),
    // RX WR 
    .crb_rx_wr_valid                    (icrb_rx_wr_valid),
    .crb_rx_wr_tag                      (icrb_rx_wr_tag),
    //
    .crb_dout                           (consumer_fifo_dout),
    .crb_dout_valid                     (consumer_fifo_valid),
    .crb_dout_last                      (consumer_fifo_last),
    .crb_dout_terminate                 (consumer_fifo_terminate),
    .crb_empty                          (consumer_fifo_empty),
    .crb_dout_ready                     (~consumer_to_user_full)
);

quick_fifo  #(.FIFO_WIDTH(512 + 1 + 1),        
            .FIFO_DEPTH_BITS(9),
            .FIFO_ALMOSTFULL_THRESHOLD(32)
            ) consumer_to_user(
        .clk                (clk),
        .reset_n            (reset_n),
        .din                ({consumer_fifo_valid, consumer_fifo_last, consumer_fifo_dout}),
        .we                 (consumer_fifo_valid),
        .re                 (usr_din_ready),
        .dout               ({usr_din_valid, usr_din_last_t, usr_din}),
        .empty              (consumer_to_user_empty),
        .valid              (consumer_to_user_valid),
        .full               (consumer_to_user_full),
        .count              (),
        .almostfull         ()
    );

always @(posedge clk) begin
    if(~reset_n) begin
        terminate_cond_rd_set <= 0;
    end 
    else begin
        terminate_cond_rd_set <= (consumer_finished & usr_din_ready)? 1'b0 :  (consumer_fifo_terminate | terminate_cond_rd_set);
    end
end

assign consumer_finished = consumer_fifo_empty & consumer_to_user_empty & terminate_cond_rd_set;
assign usr_din_last      = consumer_finished | (usr_din_last_t & consumer_to_user_valid);
/////////////////////// Instantiate User Logic Here ///////////////////////////////
assign usr_dout_ready  = ~user_to_producer_full;


rem_top_ff rem_top_ff(
    .clk                                (clk),
    .rst                                (~reset_n),
    .done                               (usr_dout_flush),

    .s_axis_data                        (usr_din),
    .s_axis_valid                       (consumer_to_user_valid),
    .s_axis_done                        (usr_din_last),
    .s_axis_ready                       (usr_din_ready),

    .m_axis_data                        (usr_dout),
    .m_axis_valid                       (usr_dout_valid),
    .m_axis_done                        (usr_dout_last),
    .m_axis_ready                       (usr_dout_ready)
    );


endmodule

//`default_nettype wire
