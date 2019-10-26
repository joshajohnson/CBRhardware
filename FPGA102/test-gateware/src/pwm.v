// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : pwm.v
// Description : Generates PWM signal with frequency and duty cycle control
// 				 Input dutyCycle is a 8 bit var
// Created     : 2019-09-26 16:37:33
// Revised     : 2019-09-26 16:37:33
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------
`ifndef _pwm_v_
`define _pwm_v_

`default_nettype none
`include "../src/clkDivHz.v"

module pwm #(
	parameter integer FREQUENCY = 1000
	)(
    input clk,
    input rst,
    input enable,
    input [7:0] dutyCycle,
    output out,
    output nOut
);

	wire dividedPulse;
	reg [0:7] counter = 0;
	reg out;
	wire nOut;

	// accumulator for ramp function
	always @(posedge clk) begin
		if (rst) begin
			counter <= 0;
		end
		else if (dividedPulse && enable) begin
			counter <= counter + 1;
		end
	end

	// flip flop output upon comparison
	always @(posedge clk) begin
		if (rst) begin
			out <= 0;
		end
		else if ((counter < dutyCycle) && enable) begin
			out <= 1;
		end
		else if ((counter >= dutyCycle) && enable) begin
			out <= 0;
		end
	end

	assign nOut = ~out;
	
	// divided down clock as required		
	clkDivHz #(
			.FREQUENCY(FREQUENCY * 256)
		) inst_clockDividerHz (
			.clk        	(clk),
			.rst        	(rst),
			.enable     	(enable),
			.dividedClk 	(),
			.dividedPulse	(dividedPulse)
		);
endmodule

`endif