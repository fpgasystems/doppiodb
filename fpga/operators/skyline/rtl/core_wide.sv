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


module core_wide #(parameter DIMENSION_WIDTH    = 32,
	          parameter MAX_NUM_DIMENSIONS = 16,
	          parameter IS_PHYSICALLY_LAST = 1'b1) (
	input  wire                                          clk,    
	input  wire 							             rst_n,  
    
    // Input tuple data
	input  wire [DIMENSION_WIDTH-1:0]                    TupleDataI[MAX_NUM_DIMENSIONS-1:0],
	input  wire [31:0]                                   TupleIndexI,
	input  wire [15:0]                                   TupleRoundI,
	input  wire [MAX_NUM_DIMENSIONS-1:0]                 TupleDimMaskI,
	input  wire [MAX_NUM_DIMENSIONS-1:0]                 TupleDimComparisonI,
	input  wire                                          TupleValidI,

	// Output tuple Data
	output reg  [DIMENSION_WIDTH-1:0]                    TupleDataO[MAX_NUM_DIMENSIONS-1:0],
	output reg  [31:0]                                   TupleIndexO,
	output reg  [15:0]                                   TupleRoundO,
	output reg  [MAX_NUM_DIMENSIONS-1:0]                 TupleDimMaskO,
	output reg  [MAX_NUM_DIMENSIONS-1:0]                 TupleDimComparisonO,
	output reg                                           TupleValidO,

	// Successor Copy
	input  wire [DIMENSION_WIDTH-1:0]                    SuccCopyDataI[MAX_NUM_DIMENSIONS-1:0],
	input  wire [31:0]                                   SuccCopyIndexI,
	input  wire                                          SuccCopyValidI,
	input  wire [15:0]                                   SuccCopyTupleRoundI,
	input  wire [1:0]                                    SuccCoreState,
	output reg                                           AcceptSuccCopy,

	// Copy to predecessor
	output wire [DIMENSION_WIDTH-1:0]                    CopyToPredDataO[MAX_NUM_DIMENSIONS-1:0],
	output wire [31:0]                                   CopyToPredIndexO,
	output wire                                          CopyToPredValidO,
	output wire [15:0]                                   CopyToPredRoundO,
	output wire [1:0]                                    CoreState,
	input  wire                                          PredAcceptingCopy
);


/*
*/

localparam [1:0]
		L_FREE = 2'b00,
		N_FREE = 2'b01,
		P_OCC  = 2'b10,
		S_OCC  = 2'b11;



reg  [DIMENSION_WIDTH-1:0]                    CoreTupleData[MAX_NUM_DIMENSIONS-1:0];
reg  [31:0]                                   CoreTupleIndex;
reg  [15:0]                                   CoreTupleRound;
reg  [MAX_NUM_DIMENSIONS-1:0]                 CoreTupleDimMask;
reg  [MAX_NUM_DIMENSIONS-1:0]                 CoreTupleDimComparison;

reg  [1:0]                                    CoreStateX;

wire [MAX_NUM_DIMENSIONS-1:0]                 smaller;
wire [MAX_NUM_DIMENSIONS-1:0]                 greater;
wire [MAX_NUM_DIMENSIONS-1:0]                 windowBetter;
wire [MAX_NUM_DIMENSIONS-1:0]                 tupleBetter;

wire                                          windowHasBetterDim;
wire                                          tupleHasBetterDim;
wire                                          windowDominates;
wire                                          tupleDominates;

reg  [DIMENSION_WIDTH-1:0]                    CmpTupleData[MAX_NUM_DIMENSIONS-1:0];

genvar i;
integer j;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
assign CopyToPredValidO         = ((CoreStateX == P_OCC) & (~TupleValidI | ~(tupleDominates))) | (CoreStateX == S_OCC);
assign CopyToPredDataO          = CoreTupleData;
assign CopyToPredIndexO         = CoreTupleIndex;
assign CopyToPredRoundO         = CoreTupleRound;
assign CoreState                = CoreStateX;

assign CoreTupleOlder = ((TupleRoundI - CoreTupleRound) >= 2) | (((TupleRoundI - CoreTupleRound) == 1) & (CoreTupleIndex < TupleIndexI) );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

always@(*) begin 
	if(IS_PHYSICALLY_LAST == 1'b1) begin 
		CmpTupleData = CoreTupleData;
	end
	else begin 
		if(CoreStateX == N_FREE) begin
			CmpTupleData = SuccCopyDataI;
		end
		else begin 
			CmpTupleData = CoreTupleData;
		end
	end
end 

generate for (i = 0; i < MAX_NUM_DIMENSIONS; i=i+1) begin: comparisons
	
	assign smaller[i]      = CmpTupleData[i] < TupleDataI[i];
	assign greater[i]      = CmpTupleData[i] > TupleDataI[i];
	assign windowBetter[i] = CoreTupleDimMask[i] & ((CoreTupleDimComparison[i])? greater[i] : smaller[i]);
	assign tupleBetter[i]  = CoreTupleDimMask[i] & ((CoreTupleDimComparison[i])? smaller[i] : greater[i]);
end
endgenerate

assign windowHasBetterDim = |windowBetter;
assign tupleHasBetterDim  = |tupleBetter;

assign windowDominates    =  windowHasBetterDim & ~tupleHasBetterDim;
assign tupleDominates     = ~windowHasBetterDim &  tupleHasBetterDim;

always @(posedge clk) begin
	if(~rst_n) begin
		for(j=0; j < MAX_NUM_DIMENSIONS; j=j+1) begin 
            TupleDataO[j]     <= 0;
            CoreTupleData[j]  <= 0;
        end

		TupleIndexO            <= 0;
		TupleDimComparisonO    <= 0;
		TupleDimMaskO          <= 0;
		TupleValidO            <= 0;
		TupleRoundO            <= 0;

		CoreTupleIndex         <= 0;
		CoreTupleDimComparison <= 0;
		CoreTupleDimMask       <= 0;
		CoreTupleRound         <= 0;

		CoreStateX             <= 0;

		AcceptSuccCopy         <= 0;
	end 
	else begin

		TupleDataO          <= TupleDataI;
		TupleIndexO         <= TupleIndexI;
		TupleDimComparisonO <= TupleDimComparisonI;
		TupleDimMaskO       <= TupleDimMaskI;
		TupleRoundO         <= TupleRoundI;
		TupleValidO         <= TupleValidI;

		
		case( CoreStateX )
			L_FREE: begin 

				CoreTupleData          <= TupleDataI;
				CoreTupleIndex         <= TupleIndexI;
				CoreTupleDimComparison <= TupleDimComparisonI;
				CoreTupleDimMask       <= TupleDimMaskI;
				CoreTupleRound         <= TupleRoundI;

				if(TupleValidI) begin 
					CoreStateX  <= P_OCC;

					TupleValidO <= 1'b0;
				end
			end
			N_FREE: begin 
				CoreTupleData          <= SuccCopyDataI;
				CoreTupleIndex         <= SuccCopyIndexI;
				CoreTupleRound         <= SuccCopyTupleRoundI;

				if(SuccCopyValidI) begin
					if(TupleValidI) begin
						if( windowDominates ) begin 
							TupleValidO    <= 1'b0;
						end 

						if(~tupleDominates) begin 
							CoreStateX     <= SuccCoreState;
							AcceptSuccCopy <= 1'b0;
						end
					end
					else begin 
						CoreStateX     <= SuccCoreState;
						AcceptSuccCopy <= 1'b0;
					end
				end
				else if((SuccCoreState == L_FREE) & ~TupleValidI & ~TupleValidO) begin 
					CoreStateX     <= L_FREE;
					AcceptSuccCopy <= 1'b0;
				end
			end
			P_OCC: begin 

				if(TupleValidI & windowDominates) begin
					TupleValidO <= 1'b0;
				end

				if(IS_PHYSICALLY_LAST) begin

					if(TupleValidI) begin 
						
						if(tupleDominates | (PredAcceptingCopy & ~windowDominates)) begin 
							TupleValidO        <= 1'b0;
							CoreTupleData      <= TupleDataI;
							CoreTupleIndex     <= TupleIndexI;
							CoreTupleRound     <= TupleRoundI;
						end
						else if(PredAcceptingCopy) begin 
							CoreStateX     <= L_FREE;
						end
						else if(CoreTupleOlder) begin 
							CoreStateX     <= S_OCC;
						end 
					end
					else if(PredAcceptingCopy) begin 
						CoreStateX     <= L_FREE;
					end
				end
				else begin 
					if(TupleValidI) begin 
						if(tupleDominates | PredAcceptingCopy) begin 
							CoreStateX     <= N_FREE;
							AcceptSuccCopy <= 1'b1;
						end
						else if(CoreTupleOlder) begin 
							CoreStateX     <= S_OCC;
						end 
					end
					else if(PredAcceptingCopy) begin 
						CoreStateX     <= N_FREE;
						AcceptSuccCopy <= 1'b1;
					end
				end
			end
			S_OCC: begin
				if (PredAcceptingCopy) begin
					if (IS_PHYSICALLY_LAST) begin
						CoreStateX <= L_FREE;
						/*
						if(prevTupleNotDominated & TupleValidI & windowDominates) begin
							TupleValidO    <= 1'b0;
						end

						if(prevTupleNotDominated & TupleValidI & tupleDominates) begin
							TupleValidO       <= 1'b0;
							CoreTupleData     <= TupleDataI;
							CoreTupleIndex    <= TupleIndexI;
							CoreTupleTimeFlag <= TupleTimeFlagI;
							CoreStateX        <= P_OCC;
						end 
						else begin 
							CoreTupleData          <= SuccCopyDataI;
							CoreTupleIndex         <= SuccCopyIndexI;
							CoreTupleTimeFlag      <= ~CoreTupleTimeFlag;

							if(prevTupleNotDominated) begin 
								CoreStateX <= P_OCC;
							end
						end*/
					end
					else begin
						CoreStateX     <= N_FREE;
						AcceptSuccCopy <= 1'b1;
					end
				end
			end
		endcase // CoreStateX
	end
end


endmodule
