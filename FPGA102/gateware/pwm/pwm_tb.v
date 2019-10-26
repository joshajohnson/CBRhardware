// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : pwm_tb.v
// Description : Test bench for pulsing PWM
// Created     : 2019-09-26 17:48:02
// Revised     : 2019-09-26 17:48:02
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------


`timescale 1ns/1ps
`include "pwm.v"

module pwm_tb();

	logic clk;
	wire nLED_GRN;

	// Clock
	initial begin
		clk = 0;
		forever #(42) clk = ~clk;
	end

	top inst_top (.clk(clk), .nLED_GRN(nLED_GRN));

	// Dump wave
	initial begin
		$dumpfile("pwm_tb.lxt");
		$dumpvars(0,pwm_tb);
	end
	
	// Count in 10% increments and finish sim when time is up
	localparam SIM_TIME_MS = 100;
	localparam SIM_TIME = SIM_TIME_MS * 1000_000; // @ 1 ns / unit
	initial begin
		$display("Simulation Started");
		#(SIM_TIME/10);
		$display("10%");
		#(SIM_TIME/10);
		$display("20%");
		#(SIM_TIME/10);
		$display("30%");
		#(SIM_TIME/10);
		$display("40%");
		#(SIM_TIME/10);
		$display("50%");
		#(SIM_TIME/10);
		$display("60%");
		#(SIM_TIME/10);
		$display("70%");
		#(SIM_TIME/10);
		$display("80%");
		#(SIM_TIME/10);
		$display("90%");
		#(SIM_TIME/10);
		$display("Finished");
		$finish;
	end

endmodule
