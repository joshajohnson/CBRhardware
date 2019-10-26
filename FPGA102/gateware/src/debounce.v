// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : debounce.v
// Description : Debounces button, outputting debounced button, and single
//               clock pulses on rising and falling edges of debounced signal
// Created     : 2019-09-06 19:13:56
// Revised     : 2019-09-06 19:13:56
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------

`ifndef _debounce_v_
`define _debounce_v_

`default_nettype none
`include "../src/clkDivHz.v"

module debounce(
    input clk,
    input button,
    output button_db,
    output reg button_rising,
    output reg button_falling
);

	wire dbPulse;
	reg [7:0] shiftReg = 0;
	reg [1:0] shiftRegDb = 0;
	reg [1:0] inputShift = 0;

	// dual dff to prevent metastablilty
	always @(posedge clk) begin
		inputShift[0] <= button;
		inputShift[1] <= inputShift[0];	
	end

	// generate shift reg to compare 
	always @(posedge clk) begin
		if (dbPulse) begin
			shiftReg[7:0] <= {shiftReg[6:0], inputShift[1]};
		end
	end

	// set output only if all shift reg is ones
	assign button_db = &shiftReg[7:0];
	
	// one clock pulse for rising and falling button_db
	always @(posedge clk) begin
		shiftRegDb[1:0] <= {shiftRegDb[0], button_db};

		if (shiftRegDb == 2'b01) begin
			button_rising <= 1'b1;
		end else begin
			button_rising <= 1'b0;
		end

		if (shiftRegDb == 2'b10) begin
			button_falling <= 1'b1;
		end else begin
			button_falling <= 1'b0;
		end
	end

	// clock for input sampling
	clkDivHz #(
			.FREQUENCY(200)
		) inst_clockDividerHz (
			.clk        	(clk),
			.rst        	(1'b0),
			.enable     	(1'b1),
			.dividedClk 	(),
			.dividedPulse	(dbPulse)
		);

endmodule

`endif