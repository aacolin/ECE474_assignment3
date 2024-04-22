module HLSM (Clk, Rst, Start, Done, u, x, y, dx, a, three, u1, x1, y1, c);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] u;
	input signed [31:0] x;
	input signed [31:0] y;
	input signed [31:0] dx;
	input signed [31:0] a;
	input signed [31:0] three;
	output reg signed [31:0] u1;
	output reg signed [31:0] x1;
	output reg signed [31:0] y1;
	output reg signed [31:0] c;
	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] t4;
	reg signed [31:0] t5;
	reg signed [31:0] t6;
	reg signed [31:0] t7;
	reg signed [31:0] vx1;

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
			t1 = three * x;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			t2 = u * dx;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			vx1 = x + dx;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			t3 = t1 * t2;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			t5 = three * y;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			t4 = u - t3;
			t7 = u * dx;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			x1 = x + dx;
			t6 = t5 * dx;
			c = vx1 < a;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			y1 = y + t7;
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			u1 = t4 - t6;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
