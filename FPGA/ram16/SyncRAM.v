`timescale 1ns / 1ps

module SyncRAM(
	input clk,
	input we,
	input [3:0] address,
	input [3:0] data_in,
	output [3:0] data_out
   );
	 
	reg [3:0] read_data;
	reg [3:0] mem [0:15];
	assign data_out = read_data;
	
	always @ (posedge clk)
	if (we)
		mem[address] <= data_in;
	else
		read_data <= mem[address];
		
endmodule
