module HLSM (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, sa, avg);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input [31:0] a;
	input [31:0] b;
	input [31:0] c;
	input [31:0] d;
	input [31:0] e;
	input [31:0] f;
	input [31:0] g;
	input [31:0] h;
	input [31:0] sa;
	output reg [31:0] avg;
	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] t7div2;
	reg [31:0] t7div4;

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
			t1 = a + b;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			t2 = t1 + c ;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			t3 = t2 + d ;
			Case <= Case + 1;
		end
		else if (Case == 4) begin
			t4 = t3 + e ;
			Case <= Case + 1;
		end
		else if (Case == 5) begin
			t5 = t4 + f ;
			Case <= Case + 1;
		end
		else if (Case == 6) begin
			t6 = t5 + g ;
			Case <= Case + 1;
		end
		else if (Case == 7) begin
			t7 = t6 + h ;
			Case <= Case + 1;
		end
		else if (Case == 8) begin
			t7div2 = t7 >> sa;
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			t7div4 = t7div2 >> sa ;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			avg = t7div4 >> sa;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
