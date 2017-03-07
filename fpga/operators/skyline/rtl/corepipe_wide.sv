
module corepipe_wide #(parameter DIMENSION_WIDTH    = 32,
	                   parameter MAX_NUM_DIMENSIONS = 16,
	                   parameter NUM_CORES          = 64) (
	input  wire                                          clk,    
	input  wire 							             rst_n,  
    
    // Input tuple data
	input  wire [DIMENSION_WIDTH-1:0]                    TupleDataI[MAX_NUM_DIMENSIONS-1:0],
	input  wire [31:0]                                   TupleIndexI,
	input  wire [MAX_NUM_DIMENSIONS-1:0]                 TupleDimMaskI,
	input  wire [15:0]                                   TupleRoundI,
	input  wire [MAX_NUM_DIMENSIONS-1:0]                 TupleDimComparisonI,
	input  wire                                          TupleValidI,

	// Output tuple Data
	output wire [DIMENSION_WIDTH-1:0]                    TupleDataO[MAX_NUM_DIMENSIONS-1:0],
	output wire [31:0]                                   TupleIndexO,
	output wire                                          TupleValidO,

	// 
	output wire                                          pipelineEmpty,


	// Copy to predecessor
	output wire [DIMENSION_WIDTH-1:0]                    SkylineTupleDataO[MAX_NUM_DIMENSIONS-1:0],
	output wire [31:0]                                   SkylineTupleIndexO,
	output wire                                          SkylineTupleValidO,
	input  wire                                          ReadingSkylineTuples
);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

wire  [DIMENSION_WIDTH-1:0]                    PipeTupleData[NUM_CORES:0][MAX_NUM_DIMENSIONS-1:0];
wire  [31:0]                                   PipeTupleIndex[NUM_CORES:0];
wire  [15:0]                                   PipeTupleRound[NUM_CORES:0];
wire  [MAX_NUM_DIMENSIONS-1:0]                 PipeTupleDimMask[NUM_CORES:0];
wire  [MAX_NUM_DIMENSIONS-1:0]                 PipeTupleDimComparison[NUM_CORES:0];
wire                                           PipeTupleValid[NUM_CORES:0];
wire                                           PipeTupleTimeFlag[NUM_CORES:0];

wire  [DIMENSION_WIDTH-1:0]                    PipeCopyData[NUM_CORES:0][MAX_NUM_DIMENSIONS-1:0];
wire  [31:0]                                   PipeCopyIndex[NUM_CORES:0];
wire  [15:0]                                   PipeCopyRound[NUM_CORES:0];
wire  [1:0]                                    PipeCoreState[NUM_CORES:0];
wire                                           PipeCopyAccept[NUM_CORES:0];
wire                                           PipeCopyTimeFlag[NUM_CORES:0];
wire                                           PipeCopyValid[NUM_CORES:0];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

assign PipeTupleData[0]          = TupleDataI;
assign PipeTupleDimComparison[0] = TupleDimComparisonI;
assign PipeTupleIndex[0]         = TupleIndexI;
assign PipeTupleRound[0]         = TupleRoundI;
assign PipeTupleDimMask[0]       = TupleDimMaskI;
assign PipeTupleValid[0]         = TupleValidI;

assign TupleDataO                = PipeTupleData[NUM_CORES];
assign TupleIndexO               = PipeTupleIndex[NUM_CORES];
assign TupleValidO               = PipeTupleValid[NUM_CORES];
 
assign pipelineEmpty             = PipeCoreState[0] == 2'b00;

assign SkylineTupleDataO         = PipeCopyData[0];
assign SkylineTupleIndexO        = PipeCopyIndex[0];
assign SkylineTupleValidO        = (PipeCopyValid[0] & ReadingSkylineTuples) | (PipeCoreState[0] == 2'b11);

assign PipeCoreState[NUM_CORES]  = 2'b00;
assign PipeCopyValid[NUM_CORES]  = 1'b0;

assign PipeCopyAccept[0]         = ReadingSkylineTuples | (PipeCoreState[0] == 2'b11);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
genvar i;

generate for (i = 0; i < NUM_CORES; i=i+1) begin: cores 

	core_wide #(.DIMENSION_WIDTH(DIMENSION_WIDTH),
	            .MAX_NUM_DIMENSIONS(MAX_NUM_DIMENSIONS),
	            .IS_PHYSICALLY_LAST(i == NUM_CORES-1)) 
	core_x(
	.clk                     (clk),    
	.rst_n                   (rst_n),  
    
    // Input tuple data
	.TupleDataI              (PipeTupleData[i]),
	.TupleIndexI             (PipeTupleIndex[i]),
	.TupleRoundI             (PipeTupleRound[i]),
	.TupleDimMaskI           (PipeTupleDimMask[i]),
	.TupleDimComparisonI     (PipeTupleDimComparison[i]),
	.TupleValidI			 (PipeTupleValid[i]),

	// Output tuple Data
	.TupleDataO              (PipeTupleData[i+1]),
	.TupleIndexO             (PipeTupleIndex[i+1]),
	.TupleRoundO             (PipeTupleRound[i+1]),
	.TupleDimMaskO           (PipeTupleDimMask[i+1]),
	.TupleDimComparisonO     (PipeTupleDimComparison[i+1]),
	.TupleValidO			 (PipeTupleValid[i+1]),

	// Successor Copy
	.SuccCopyDataI           (PipeCopyData[i+1]),
	.SuccCopyIndexI			 (PipeCopyIndex[i+1]),
	.SuccCopyValidI          (PipeCopyValid[i+1]),
	.SuccCopyTupleRoundI     (PipeCopyRound[i+1]),
	.SuccCoreState           (PipeCoreState[i+1]),
	.AcceptSuccCopy          (PipeCopyAccept[i+1]),

	// Copy to predecessor
	.CopyToPredDataO         (PipeCopyData[i]),
	.CopyToPredIndexO		 (PipeCopyIndex[i]),
	.CopyToPredValidO        (PipeCopyValid[i]),
	.CopyToPredRoundO        (PipeCopyRound[i]),
	.CoreState               (PipeCoreState[i]),
	.PredAcceptingCopy       (PipeCopyAccept[i])
	);

end
endgenerate

endmodule // corepipe_wide