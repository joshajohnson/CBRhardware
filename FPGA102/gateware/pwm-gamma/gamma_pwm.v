/*
 *  icebreaker examples - gamma pwm demo 
 *
 *  Copyright (C) 2018 Piotr Esden-Tempski <piotr@esden.net>
 *  Modified to suit the iCE40-feather by Josh Johnson <josh@joshajohnson.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

// This example generates PWM with gamma correction
// The intended result is a pulsating LED whih does not stay at a perceptable 
// brightness level longer than others.
//
// For more information about gamma correction:
// https://en.wikipedia.org/wiki/Gamma_correction

module top (
	input clk,
	output nLED_RED
);

// Gamma value lookup table parameters
parameter G_PW = 8; // Number of input bits
parameter G_OW = 16; // Number of output bits

// Load the gamma value lookup table
reg [(G_OW-1):0] gamma_lut [0:((1<<(G_PW))-1)];
initial $readmemh("gamma_table.hex", gamma_lut);

// Very simple PWM generator
reg [15:0] pwm_counter = 0;
reg [15:0] pwm_compare_0;
reg pwm_out;
always @(posedge clk) begin
	pwm_counter <= pwm_counter + 1;

	if (pwm_counter < pwm_compare_0) begin
		pwm_out <= 1;
	end else begin
		pwm_out <= 0;
	end
end

// PWM compare value generator
// Fade through the values using the gamma correction
reg [17:0] pwm_inc_counter = 0;
reg [G_PW:0] pwm_value = 0;
always @(posedge clk) begin
	// Divide clock by 131071
	pwm_inc_counter <= pwm_inc_counter + 1;

	// increment/decrement the index
	if (pwm_inc_counter[17]) begin
		pwm_inc_counter <= 0;
		pwm_value <= pwm_value + 1;
	end

	// Assign the compare value
	// The MSB bit of pwm_value determines the direction of the count
	// It is less expensive on an FPGA than doing an up down counter with dir variable
	pwm_compare_0 <= gamma_lut[pwm_value[G_PW] ?  pwm_value[G_PW-1:0] : ~pwm_value[G_PW-1:0]];
end

assign nLED_RED = ~pwm_out;

endmodule