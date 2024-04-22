module HLSM (Clk, Rst, Start, Done, a, b, c, zero, one, t, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] zero;
	input signed [31:0] one;
	input signed  t;
	output reg signed [31:0] z;
	output reg signed [31:0] x;
	reg signed [31:0] e;
	reg signed [31:0] g;
	reg signed [31:0] d;
	reg signed [31:0] f;
	reg signed [31:0] d_False;
	reg signed [31:0] d_True;
	reg signed [31:0] f_True;
	reg signed [31:0] f_False;
	reg signed [31:0] x_True;
	reg signed [31:0] x_False;

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
			d_False = a + b;
			   d_True = a - one;
				f_False = a * c;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			d = t ? d_True : d_False;
			   f_True = a + c;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			f = t ? f_True : f_False;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			   x_True = f - d;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
				x_False = f - d  ;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			x = t ? x_True : x_False;
				e = a + c;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
				g = d > e;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
				z = g ? d : e;
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
