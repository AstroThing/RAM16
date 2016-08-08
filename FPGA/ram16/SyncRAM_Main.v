`timescale 1ns / 1ps

module SyncRAM_Main(
	input clk,
	input we,
	input [3:0] address,
	input [3:0] data_in,
	output [3:0] data_out
   );
	 
	SyncRAM ram(clk, we, address, data_in, data_out);

endmodule
