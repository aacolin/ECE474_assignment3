module HLSM (Clk, Rst, Start, Done, a, b, c, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	output reg signed [31:0] z;
	output reg signed [31:0] x;
	reg signed [31:0] d;
	reg signed [31:0] e;
	reg signed [31:0] f;
	reg signed [31:0] g;
	reg signed [31:0] h;
	reg  dLTe;
	reg  dEQe;

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
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			e = a + c;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			d = a + b;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			f = a - b  ;
			dEQe = d == e;
			dLTe = d < e;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			g = dLTe ? d : e ;
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			h = dEQe ? g : f ;
			x = g << dLTe;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			z = h >> dEQe;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
