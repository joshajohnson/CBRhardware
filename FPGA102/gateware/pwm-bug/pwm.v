// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : pwm.v
// Description : iCE40-feather implementation of a pulsing LED
//               This has a few bugs added to demo debugging 
// Created     : 2019-09-26 17:45:42
// Revised     : 2019-09-26 17:45:42
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------

`default_nettype none
`include "../src/pwm.v"
`include "../src/clkDivHz.v"

module top(
    input clk,
    output nLED_GRN
);

	reg dutyCycle = 0;
	reg countUp = 1;
	wire dividedPulse;

	always @(posedge clk) begin
		if (dividedPulse) begin
			if (dutyCycle == 0) begin
				countUp <= 1;
			end else if (dutyCycle == 255) begin
				countUp <= 0;
			end

			if (countUp) begin
				dutyCycle <= dutyCycle + 1;
			end else begin
				dutyCycle <= dutyCycle - 1;
			end
		end
	end

	clkDivHz #(
		.FREQUENCY(50)
	) inst_clkDivHz (
		.clk          (clk),
		.rst          (1'b0),
		.enable       (1'b1),
		.dividedClk   (),
		.dividedPulse (dividedPulse)
	);

	pwm #(
		.FREQUENCY(1_000)
	) inst_pwm (
		.clk       (clk),
		.rst       (1'b0),
		.enable    (1'b1),
		.dutyCycle (dutyCycle),
		.out       (),
		.nOut      (nLED_GRN)
	);

endmodule

