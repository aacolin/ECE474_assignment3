module HLSM (Clk, Rst, Start, Done, a, b, c, d, e, f, g, k, l);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;
	input signed [15:0] f;
	input signed [15:0] g;
	output reg signed [15:0] k;
	output reg signed [15:0] l;
	reg signed [15:0] h;
	reg signed [15:0] i;
	reg signed [15:0] j;

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
			h = a * b;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			i = c * d;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			l = f / g;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			j = h + i;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			k = j / e;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
