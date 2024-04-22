module HLSM (Clk, Rst, Start, Done, a, b, c, d, zero, z);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input [63:0] a;
	input [63:0] b;
	input [63:0] c;
	input [63:0] d;
	input [63:0] zero;
	output reg [63:0] z;
	reg [63:0] e;
	reg [63:0] f;
	reg [63:0] g;
	reg  gEQz;

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
			f = c / d;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			g = a % b  ;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			e = a / b;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			gEQz = g == zero;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			z = gEQz ? e : f ;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
