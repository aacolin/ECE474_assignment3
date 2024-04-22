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
	reg signed [31:0] f;
	reg signed [31:0] g;
	reg signed [31:0] zrin;
	reg signed [31:0] zrin_False;
	reg signed [31:0] zrin_True;

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
			g = a < b;
			zrin_False = a + c;
			f = a * c;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
				zrin_True = a + b;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			zrin = g ? zrin_True : zrin_False;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			z = zrin + f;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			d = a + b;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			x = f - d  ;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
