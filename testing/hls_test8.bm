module HLSM (Clk, Rst, Start, Done, x0, x1, x2, x3, y0, c0, five, ten, d1, d2, e, f, g, h);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] x0;
	input signed [31:0] x1;
	input signed [31:0] x2;
	input signed [31:0] x3;
	input signed [31:0] y0;
	input signed [31:0] c0;
	input signed [31:0] five;
	input signed [31:0] ten;
	output reg signed [31:0] d1;
	output reg signed [31:0] d2;
	output reg signed [31:0] e;
	output reg signed [31:0] f;
	output reg signed [31:0] g;
	output reg signed [31:0] h;
	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] vd1;
	reg signed [31:0] ve;
	reg signed [31:0] vf;
	reg signed [31:0] vg;

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
			t1 = x0 + x1;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			d1 = t1 * c0;
			t3 = x3 + c0;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			vd1 = t1 * c0;
			t2 = x1 + x2;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			ve = t2 * t3;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			d2 = vd1 * five;
			vg = x0 - ten;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			f = ve * y0;
			g = x0 - ten;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			vf = ve * y0;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			e = t2 * t3;
			h = vf + vg;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
