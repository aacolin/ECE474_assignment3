module HLSM (Clk, Rst, Start, Done, a, b, c, d, e, i);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] Case;

	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;
	output reg signed [15:0] i;
	reg signed [15:0] f;
	reg signed [15:0] g;
	reg signed [15:0] h;

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
			f = a + b;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			g = f + c;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			h = g + d;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			i = h + e;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
