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



module precentage_um(
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

wire   [39:0]              total_sum;
wire   [39:0]              selected_sum;
wire   [31:0]              selected_count; 
wire                       output_valid;

reg                         um_activated;
reg                         data_rd_done;
reg                         pred_rd_done;

reg  [31:0]                 data_rd_cnt;
reg  [31:0]                 pred_rd_cnt;

reg  [31:0]                 rx_rd_cnt;

wire [31:0]                 pred_rd_cnt_inc;
wire [31:0]                 data_rd_cnt_inc;

reg  [511:0]                um_params_reg;

reg                         ret_set;
reg                         read_fsm;
reg                         data_read;

wire  [511:0]               predicates_line;
wire                        predicates_valid;
wire                        predicates_last;
wire                        predicates_in_ready;

wire  [511:0]               data_line;
wire                        data_valid;
wire                        data_last;

reg  [31:0]                 data_rd_numcls;
reg  [31:0]                 pred_rd_numcls;   

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

        data_rd_numcls <= um_params[223:192];
        pred_rd_numcls <= {1'b0, um_params[223:193]} + um_params[192];
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
        um_tx_wr_valid <= output_valid;
        ret_set        <= output_valid;
        um_done        <= 0; 
    end 
    else if(um_tx_wr_ready) begin
        um_tx_wr_valid <= 0;
        //ret_set        <= 0;
        um_done        <= 1'b1;
    end 
end

always @(posedge clk) begin
    um_tx_wr_addr       <= um_params_reg[191:134];
    um_tx_wr_tag        <= 0;
    um_tx_data[511: 160] <= 0;
    if(~ret_set) begin
       um_tx_data[159:0] <= { selected_count, 24'b0, selected_sum, 24'b0, total_sum};
    end 
end

/////////////////////// read data in /////////////////////////////////////////
// TX RD
always @(posedge clk) begin
    if (~rst_n) begin
        // reset
        um_tx_rd_addr  <= 0;
        um_tx_rd_valid <= 0;
        data_rd_cnt    <= 0;
        pred_rd_cnt    <= 0;
        um_tx_rd_tag   <= 0;

        data_rd_done   <= 0;
        pred_rd_done   <= 0;

        read_fsm       <= 0;
        data_read      <= 0;
    end
    else if (um_tx_rd_ready & um_activated) begin
        if(read_fsm & ~data_rd_done) begin 
            um_tx_rd_addr  <= um_params_reg[63:6] + data_rd_cnt;
            um_tx_rd_valid <= data_rd_cnt != um_params_reg[223:192];
            data_rd_cnt    <= data_rd_cnt_inc;
            um_tx_rd_tag   <= {1'b1, 7'b0};
            data_rd_done   <= 0;

            if(data_rd_cnt_inc == data_rd_numcls) begin 
                um_tx_rd_tag   <= {1'b1, 7'b0000001};
                data_rd_done   <= 1'b1;
            end

            data_read <= 1'b1;

            if(data_read) begin
                read_fsm  <= 1'b0;
                data_read <= 1'b0;
            end
        end
        else if(~pred_rd_done) begin
            um_tx_rd_addr     <= um_params_reg[127:70] + pred_rd_cnt;
            um_tx_rd_valid    <= pred_rd_cnt != {1'b0, um_params_reg[223:193]};
            pred_rd_cnt       <= pred_rd_cnt_inc;
            um_tx_rd_tag      <= {1'b0, 7'b0};
            pred_rd_done      <= 0;

            if(pred_rd_cnt_inc == pred_rd_numcls) begin 
                um_tx_rd_tag      <= {1'b0, 7'b0000001};
                pred_rd_done      <= 1'b1;
            end
            read_fsm  <= 1'b1;
        end
        else begin 
            um_tx_rd_valid <= 0;
            read_fsm       <= 1'b1;
        end     
    end
end

assign data_rd_cnt_inc = data_rd_cnt + 1'b1;
assign pred_rd_cnt_inc = pred_rd_cnt + 1'b1;
///////////////////////////////////////////////////////////////////////////////////

assign data_line  = um_rx_data;
assign data_valid = um_rx_rd_valid & um_rx_rd_tag[7];
assign data_last  = um_rx_rd_tag[0]; 

assign predicates_line  = um_rx_data;
assign predicates_valid = um_rx_rd_valid & ~um_rx_rd_tag[7];
assign predicates_last  = um_rx_rd_tag[0]; 
///////////////////////////////////////////////////////////////////////////////////
/////////////////////// Instantiate User Logic Here ///////////////////////////////
percentage percentage(
    .clk                                (clk),
    .rst_n                              (rst_n),

    .predicates_line                    (predicates_line),
    .predicates_valid                   (predicates_valid),
    .predicates_last                    (predicates_last),
    .predicates_in_ready                (),

    .data_line                          (data_line),
    .data_valid                         (data_valid),
    .data_last                          (data_last),
    .data_in_ready                      (),
    
    .total_sum                          (total_sum),
    .selected_sum                       (selected_sum),
    .selected_count                     (selected_count), 
    .output_valid                       (output_valid)
    );


endmodule
