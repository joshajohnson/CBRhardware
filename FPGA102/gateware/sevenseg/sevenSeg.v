// Seven segment decoder from binary to hex and dec 
// Can be configured for common anode or cathode display by adjusting COM_ANODE to 1 or 0
// @input sw: 8 dip switches on FeatherWing
// @input switch: slide switch on side of FeatherWing
// @output seg: pins for seven segment A:G connections
// @output com: common (anode / cathode) pins for each seven segment display

`default_nettype none
`include "../src/clkDivHz.v"
`include "nibbleDecode.v"
`include "displaySelect.v"

module top(
    input clk,
    input [7:0] sw,
    input switch,
    output reg [6:0] seg,
    output reg [1:0] com
	);

	// params / wires
	localparam COM_ANODE = 1;
	wire dividedClk;
	wire [6:0] disp0, disp1;
	wire [3:0] nibbleMS, nibbleLS;

	// mux displays together
	always @(posedge clk) begin
		case (dividedClk)
			0:begin
				seg <= disp1;
				if (COM_ANODE) begin
					com <= 2'b01;
				end else begin
					com <= 2'b10;
				end
			end
			1:begin
				seg <= disp0;
				if (COM_ANODE) begin
					com <= 2'b10;
				end else begin
					com <= 2'b01;
				end
			end
		endcase
	end

	// choose what number to show on display
	displaySelect inst_displaySelect (
		.clk 		(clk), 
		.sw 		(sw), 
		.switch 	(switch), 
		.nibbleMS 	(nibbleMS), 
		.nibbleLS 	(nibbleLS)
	);

	// decodes nibble to 7 segment display
	nibbleDecode #(
			.COM_ANODE 	(COM_ANODE)
		) nibbleDecodeMSD (
			.clk 		(clk), 
		 	.nibblein 	(nibbleMS), 
			.segout 	(disp0)
	);

	nibbleDecode #(
			.COM_ANODE 	(COM_ANODE)
		) nibbleDecodeLSD (
			.clk 		(clk), 
		 	.nibblein 	(nibbleLS), 
			.segout 	(disp1)
	);
	
	// generate clock for switching displays
	clkDivHz #(
			.FREQUENCY(100)
		) inst_clkDivHz (
			.clk        	(clk),
			.rst        	(1'b0),
			.enable     	(1'b1),
			.dividedClk 	(dividedClk),
			.dividedPulse	()
	);

endmodule

