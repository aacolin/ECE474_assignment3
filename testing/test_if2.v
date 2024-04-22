module HLSM (Clk, Rst, Start, Done, a, b, c, one, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] one;
	output reg signed [31:0] z;
	output reg signed [31:0] x;
	reg signed [31:0] d;
	reg signed [31:0] e;
	reg signed [31:0] f;
	reg signed [31:0] g;
	reg signed [31:0] h;
	reg signed  dLTe;
	reg signed  dEQe;
	reg signed  dLTEe;
	reg signed [31:0] g_True;
	reg signed [31:0] g_False;
	reg signed [31:0] h_True;
	reg signed [31:0] h_False;

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
			e = a + c;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			d = a + b;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			dEQe = d == e;
					g_True = e + one;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			dLTe = d > e;
				g_False = d + e;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			f = a - b  ;
			g = dLTe ? g_True : g_False;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
					h_True = f + one;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
				h_False = f + e;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			dLTEe = dEQe + dLTe;
			h = dLTe ? h_True : h_False;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			x = h << one;
			z = h >> one;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
