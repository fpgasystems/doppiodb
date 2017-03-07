`default_nettype none

//achieves 64bit alignment

module pg_smartshifter
	#(
	SHIFT_BITS=8, //was16
	SHIFT_WIDTH=64 //was32
	)
    (
    input wire            clk,
    input wire            rst,

    input wire 			 inValid,
    input wire           inLast,
    input wire[3:0]      inOffs,    
    input wire[1023:0] 	 inData,

    output reg           outValid,   
    output reg           outLast,  
    output reg[511:0]    outData    

    );    

    reg[1023:0] shData [SHIFT_BITS-1:0];
    reg[8:0]   shOffs [SHIFT_BITS-1:0];
	 integer i;

    always @(posedge clk) begin

        if (rst==1) begin
            outValid <= 0;

            for (i = 0; i <SHIFT_BITS; i = i+1)
            begin
                shOffs[i] <= 0;
            end

        end
        else begin
            
            shData[0] <= inData;
            shOffs[0][3:0] <= {3'b0, inOffs[3:0]};
            shOffs[0][7] <= inValid;
            shOffs[0][8] <= inLast;

            for (i = 0; i <SHIFT_BITS-1; i = i+1)
            begin
                if (shOffs[i][6:0]!=0) begin
                    shData[i+1] <= {64'b0, shData[i][1023:64]};
                    shOffs[i+1][8:7] <= shOffs[i][8:7];
                    shOffs[i+1][6:0] <= shOffs[i][6:0]-1;
                end else begin
                    shData[i+1] <= shData[i][1023:0];
                    shOffs[i+1][8:7] <= shOffs[i][8:7];
                    shOffs[i+1][6:0] <= shOffs[i][6:0];
                end
            end

            outValid <= shOffs[SHIFT_BITS-1][7];
            outLast <= shOffs[SHIFT_BITS-1][8];
            outData <= shData[SHIFT_BITS-1][511:0];

        end
    end


endmodule

`default_nettype wire