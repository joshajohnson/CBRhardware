// -----------------------------------------------------------------------------
// Copyright (c) 2019 All rights reserved
// -----------------------------------------------------------------------------
// Author      : Josh Johnson <josh@joshajohnson.com>
// File        : disp_rx.v
// Description : Displays UART chars on matrix display
// Created     : 2019-10-25 13:19:55
// Revised     : 2019-10-25 13:19:55
// Editor      : sublime text3, tab size (4)
// -----------------------------------------------------------------------------

`default_nettype none
`include "../src/ledMatrix.v"
`include "../src/uart_rx.v"
`include "../src/char_disp.v"

module top(
    input clk,
    input wire UART_RX,
    output wire [5:0] row,
    output wire [5:0] col
);

	wire [35:0] img;
	reg [35:0] img_show;

	// Display whatever char recently arrived
	always @(posedge clk) begin
		if (ready) begin
			img_show <= img;
		end
	end
	
	// Uart RX 
	wire ready;
	wire [7:0] data;
	uart_rx inst_uart_rx (
		.clk(clk), 
		.rst(1'b0), 
		.uart_rx(UART_RX), 
		.ready(ready), 
		.data(data)
	);

	// Display lookup table
	char_disp inst_char_disp (
		.clk(clk), 
		.data(data), 
		.img(img)
	);

	// Drive matrix
	ledMatrix inst_ledMatrix (
		.clk	(clk), 
		.img	(img_show), 
		.row 	(row), 
		.col 	(col)
	);

endmodule

