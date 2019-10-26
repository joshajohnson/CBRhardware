// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : clkDivHz.v
// Description : Divides 12 MHz system clock outputs divided and single pulse
// Created     : 2019-09-06 19:17:20
// Revised     : 2019-09-06 19:17:20
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------

`default_nettype none

`ifndef _clkDivHz_v_
`define _clkDivHz_v_

module clkDivHz #(
	parameter integer FREQUENCY = 1
	)(
	input clk,
	input rst,
	input enable,
	output reg dividedClk = 0,
	output reg dividedPulse = 0
);	

	// calculate threshold value from frequency
	localparam CLK_FREQ = 32'd12_000_000;
	localparam THRESHOLD = CLK_FREQ / FREQUENCY / 2;
	
	reg [31:0] counter = 0;

	// accumulator counting up / resetting
	always @(posedge clk) begin
		if (rst || (counter >= THRESHOLD - 1)) begin
			counter <= 0;
			// give a pulse for one clock cycle only
			dividedPulse <= (1 & dividedClk);
		end
		else if (enable) begin
			counter <= counter + 1;
			dividedPulse <= 0;
		end
	end

	// generate divided down clock
	always @(posedge clk) begin
		if (rst) begin
			dividedClk <= 0;
		end
		else if (counter >= THRESHOLD - 1) begin
			dividedClk <= ~dividedClk;
		end
	end
endmodule

`endif