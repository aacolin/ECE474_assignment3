module HLSM (Clk, Rst, Start, Done, a, b, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] Case;

	input signed [15:0] a;
	input signed [15:0] b;
	output reg signed [7:0] z;
	output reg signed [15:0] x;
	reg signed [15:0] d;
	reg signed [15:0] e;
	reg signed [15:0] f;
	reg signed [15:0] g;

	initial begin
		Done <= 0;
		Case <= 0;
	end

	always @(posedge Clk) begin
		if (Rst) begin
			Done <= 0;
			Case <= 0;
		end

		if (Start && Case == 0) begin
			Case <= Case + 1;
			Done <= 0;
		end
		else if (Case == 1) begin
			d = a + b;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			g = d > e;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			x = f - d  ;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			z = g ? d : e;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
