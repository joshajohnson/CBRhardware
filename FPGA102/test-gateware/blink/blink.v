// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : blink.v
// Description : Blinking a LED using the clkDivHz.v module
// Created     : 2019-09-26 22:46:11
// Revised     : 2019-09-26 22:46:11
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------

`default_nettype none
`include "../src/clkDivHz.v"

module top(
    input clk,
    output nLED
);

	wire dividedClk;
		
	clkDivHz #(
			.FREQUENCY(15)
		) inst_clockDividerHz (
			.clk        	(clk),
			.rst        	(1'b0),
			.enable     	(1'b1),
			.dividedClk 	(dividedClk),
			.dividedPulse	()
		);

	assign nLED = dividedClk;
endmodule

