
module copy #(parameter DATA_WIDTH_IN  = 4,
              parameter DATA_WIDTH_OUT = 4 ) (
    input   wire                                   clk,
    input   wire                                   rst_n,
    //-------------------------------------------------//
    input   wire                                   start_um,
    input   wire [511:0]                           um_params,
    output  wire                                   um_done,
    // TX RD
    output  reg  [57:0]                            um_tx_rd_addr,
    output  reg  [7:0]                             um_tx_rd_tag,
    output  reg                                    um_tx_rd_valid,
    input   wire                                   um_tx_rd_ready,
    // TX WR
    output  reg  [57:0]                            um_tx_wr_addr,
    output  reg  [7:0]                             um_tx_wr_tag,
    output  reg                                    um_tx_wr_valid,
    output  reg  [511:0]                           um_tx_data,
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


reg                         um_activated;
reg                         rd_done;
reg  [31:0]                 rd_cnt;
reg  [31:0]                 wr_cnt;
reg  [31:0]                 rx_rd_cnt;

wire [31:0]                 rd_cnt_inc;
wire [31:0]                 wr_cnt_inc;
wire [31:0]                 rx_rd_cnt_inc;

reg  [511:0]                um_params_reg;
reg                         set_last;

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
/////////////////////// Write Data out ///////////////////////////////

assign um_rx_rd_ready = um_tx_wr_ready;

always@(posedge clk) begin
    if(~rst_n) begin
        um_tx_data        <= 0;
        um_tx_wr_valid    <= 0;
        um_tx_wr_addr     <= 0;
        um_tx_wr_tag      <= 0;
        set_last          <= 1'b0;
        wr_cnt            <= 0;
    end 
    else if( um_tx_wr_ready ) begin
        um_tx_data        <= um_rx_data;
        um_tx_wr_valid    <= um_rx_rd_valid;
        um_tx_wr_addr     <= um_params_reg[127:70] + wr_cnt;
        um_tx_wr_tag      <= um_rx_rd_tag;

        if( um_rx_rd_valid ) begin
            wr_cnt            <= wr_cnt_inc;
        end

        if( (wr_cnt_inc == um_params[159:128]) & um_rx_rd_valid) begin
            set_last <= 1'b1;
        end
    end 
end 

assign wr_cnt_inc = wr_cnt + 1'b1;

assign um_done  = (set_last & um_tx_wr_ready) | (um_activated & (um_params[159:128] == 0));


endmodule