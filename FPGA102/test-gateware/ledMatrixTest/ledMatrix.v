// Example code for LED FeatherWing
// Currently scans through row / col, and lights up LEDs when buttons are pressed
// @input [3:0] btn: four buttons on FeatherWing
// @output nLEDx: RGB LED on FeatherWing + user led on Feather. 
// @output row, col: row and col of LED matrix

`default_nettype none
`include "../src/clkDivHz.v"

module top(
    input clk,
    input [3:0] btn,
    output [5:0] row,
    output [5:0] col,
    output nLED_RED_fw,
    output nLED_GRN_fw,
    output nLED_BLU_fw,
    output nLED
);
	wire dividedPulse;
	reg [2:0] rowPos = 0;
	reg [2:0] colPos = 0;

	always @(posedge clk) begin
		if (dividedPulse) begin
			if (rowPos < 6) begin
				rowPos = rowPos + 1;
			end
			if (rowPos == 6) begin
				rowPos = 0;
			end
			if (rowPos == 0) begin
				colPos = colPos + 1;
			end
			if (colPos == 6) begin
				colPos = 0;
			end
			
		end
	end

	assign row = (1 << rowPos);
	assign col = ~(1 << colPos);

	assign nLED = ~btn[0];
	assign nLED_RED_fw = ~btn[1];
	assign nLED_GRN_fw = ~btn[2];
	assign nLED_BLU_fw = ~btn[3];
		
	clkDivHz #(
			.FREQUENCY(36)
		) inst_clockDividerHz (
			.clk        	(clk),
			.rst        	(1'b0),
			.enable     	(1'b1),
			.dividedClk 	(),
			.dividedPulse	(dividedPulse)
		);

endmodule

