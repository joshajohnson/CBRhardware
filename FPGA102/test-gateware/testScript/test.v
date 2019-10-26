// Test script used during assembly to confirm that all IO and UART are functioning correctly

`default_nettype none
`include "../src/clkDivHz.v"

module top(
    input clk,
    input UART_RX,
    output nLED,
    output nLED_RED,
    output nLED_GRN,
    output nLED_BLU,
    output IO_0,
    output IO_1,
    output IO_2,
    output IO_3,
    output IO_4,
    output IO_5,
    output IO_6,
    output IO_7,
    output IO_8,
    output IO_9,
    output IO_10,
    output IO_11,
    output IO_12,
    output IO_13,
    output IO_14,
    output IO_15,
    output IO_16,
    output IO_17,
    output IO_18,
    output IO_19,
    output UART_TX
);

	localparam NUM_PINS	= 8'd20;
	wire dividedClk;
	wire dividedPulse;
	reg [8:0] counter = 0;
	reg [1:0] rgbCounter = 0;
		
	clkDivHz #(
		.FREQUENCY(5)
	) inst_clockDividerHertz (
		.clk        	(clk),
		.rst        	(1'b0),
		.enable     	(1'b1),
		.dividedClk 	(dividedClk),
		.dividedPulse 	()
	);

	assign nLED = dividedClk;
	assign UART_TX = UART_RX;

	always @(posedge dividedClk) begin
		rgbCounter = rgbCounter + 1;
		if (counter >= NUM_PINS -1) begin
			counter = 0;
		end
		else if (counter < NUM_PINS -1) begin
			counter = counter + 1;
		end
	end

	assign nLED_RED = ~(rgbCounter == 1);
	assign nLED_GRN = ~(rgbCounter == 2);
	assign nLED_BLU = ~(rgbCounter == 3);

	assign IO_0 = (counter == 8'd0);
	assign IO_1 = (counter == 8'd1);
	assign IO_2 = (counter == 8'd2);
	assign IO_3 = (counter == 8'd3);
	assign IO_4 = (counter == 8'd4);
	assign IO_5 = (counter == 8'd5);
	assign IO_6 = (counter == 8'd6);
	assign IO_7 = (counter == 8'd7);
	assign IO_8 = (counter == 8'd8);
	assign IO_9 = (counter == 8'd9);
	assign IO_10 = (counter == 8'd10);
	assign IO_11 = (counter == 8'd11);
	assign IO_12 = (counter == 8'd12);
	assign IO_13 = (counter == 8'd13);
	assign IO_14 = (counter == 8'd14);		
	assign IO_15 = (counter == 8'd15);
	assign IO_16 = (counter == 8'd16);
	assign IO_17 = (counter == 8'd17);
	assign IO_18 = (counter == 8'd18);
	assign IO_19 = (counter == 8'd19);

endmodule

