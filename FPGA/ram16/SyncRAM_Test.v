`timescale 1ns / 1ps

module SyncRAM_Test;

	// Inputs
	reg clk;
	reg we;
	reg [3:0] address;
	reg [3:0] data_in;

	// Outputs
	wire [3:0] data_out;

	// Instantiate the Unit Under Test (UUT)
	SyncRAM uut (
		.clk(clk), 
		.we(we), 
		.address(address), 
		.data_in(data_in), 
		.data_out(data_out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		we = 0;
		address = 0;
		data_in = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		address = 8;
		we = 1;
		data_in = 10;
		#100
		we = 0;
		address = 0;
		data_in = 0;
		#100
		address = 8;
		#100
		address = 0;

	end
	
	always
	begin
		#100
		clk = !clk;
	end
      
endmodule

