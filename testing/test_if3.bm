module HLSM (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, sa, one, two, four, avg);

	input Clk, Rst, Start;
	output reg Done;
	reg [4:0] Case;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] d;
	input signed [31:0] e;
	input signed [31:0] f;
	input signed [31:0] g;
	input signed [31:0] h;
	input signed [31:0] sa;
	input signed [31:0] one;
	input signed [31:0] two;
	input signed [31:0] four;
	output reg signed [31:0] avg;
	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] t4;
	reg signed [31:0] t5;
	reg signed [31:0] t6;
	reg signed [31:0] t7;
	reg signed [31:0] t7div2;
	reg signed [31:0] t7div4;
	reg signed  csa1;
	reg signed  csa2;
	reg signed  csa3;
	reg signed [31:0] t7div4_True;
	reg signed [31:0] t7div4_False;

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
			csa1 = sa > one;
			Case <= Case + 1;
		end
		else if (Case == 2) begin
			t2 = t1 + c ;
			csa3 = sa > four;
			Case <= Case + 1;
		end
		else if (Case == 3) begin
			t3 = t2 + d ;
			csa2 = sa > two;
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
			      t7div4_False = t7 >> one;
			   t7div2 = t7 >> one;
			Case <= Case + 1;
		end
		else if (Case == 9) begin
			      t7div4_True = t7div2 >> one;
			Case <= Case + 1;
		end
		else if (Case == 10) begin
			t7div4 = csa2 ? t7div4_True : t7div4_False;
			Case <= Case + 1;
		end
		else if (Case == 11) begin
			         avg = t7div4 >> one;
			Case <= Case + 1;
		end
		else if (Case == 12) begin
			Done <= 1;
			Case <= 0;
		end
	end

endmodule
