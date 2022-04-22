#pragma once

#ifndef YSXYSPHAX_H
#define YSXYSPHAX_H
// DEFINE it after every other header!

// #####################
// ####### By Sophia Cristina
// ####### Keep private, however, nothing importat (maybe yet).
// #####################

// #################################################
// REFERENCES:
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// STAMP FOR MY PRODUCTS:
class YSX_Stamp
{
public:
	// #################################################
	
	// COORDENADES:
	const unsigned char Coords = 24;
	const LinePoint<unsigned char> CoordStamp[24] =
	{
		{{0, 0}, {2, 2}}, {{0, 2}, {1, 1}}, // 'y'SPHAx
		{{3, 1}, {4, 0}}, {{4, 0}, {6, 2}}, {{6, 2}, {3, 4}}, {{3, 4}, {5, 6}}, {{5, 6}, {6, 5}}, // y'S'PHAx
		{{7, 0}, {7, 6}}, {{7, 6}, {9, 6}}, {{9, 6}, {10, 5}}, {{10, 5}, {10, 4}}, {{10, 4}, {9, 3}}, {{7, 3}, {9, 3}}, // yS'P'HAx
		{{11, 0}, {11, 6}}, {{14, 0}, {14, 6}}, {{11, 3}, {14, 3}}, // ySP'H'Ax
		{{15, 0}, {15, 5}}, {{15, 5}, {16, 6}}, {{16, 6}, {17, 6}}, {{17, 6}, {18, 5}}, {{18, 0}, {18, 5}}, {{15, 3}, {18, 3}}, // ySPH'A'x
		{{19, 4}, {21, 6}}, {{19, 6}, {21, 4}} // ySPHA'x'
	};

	// COLOR GRADIENTS (! USE 3 CHANNELS ONLY !):
	enum Gradients { G2Pink, B2Pink };
	void Green2Pink(unsigned char* C, unsigned char Coord)
	{
		C[0] = 255.0 * ((double)Coord / Coords);
		C[1] = 255.0 * (1 - ((double)Coord / Coords));
		C[2] = 127.0 * ((double)Coord / Coords);
	}

	void Blue2Pink(unsigned char* C, unsigned char Coord)
	{
		C[0] = 255.0 * ((double)Coord / Coords);
		C[1] = 0;
		C[2] = 255.0 - 128 * (1 - ((double)Coord / Coords));
	}
	
	// #################################################
	
	YSX_Stamp()
	{
	}

	~YSX_Stamp()
	{
	}

	// #################################################

	CImg<unsigned char> StampImg(int x, int y, unsigned char ColorGrad)
	{
		CImg<unsigned char> I(x, y, 1, 3, 0); 
		double dx = x / 21.0, dy = y / 6.0;
		for (char n = 0; n < Coords; ++n)
		{
			// 127 -> 255 (128), 255 -> 0 (255), 0 -> 127 (127):
			unsigned char C[3]; if (ColorGrad == G2Pink) { Green2Pink(C, n); } else { Blue2Pink(C, n); }
			Linexy(I, CoordStamp[n].P0.x * dx, y - CoordStamp[n].P0.y * dy, CoordStamp[n].P1.x * dx, y - CoordStamp[n].P1.y * dy, C, false);
		}
		return(I);
	}

	void Print(CImg<unsigned char>& In, unsigned short Offx, unsigned short Offy, unsigned char ColorGrad)
	{
		double x = In.width(), y = In.height();
		double dx = x / 21.0, dy = y / 6.0;
		for (char n = 0; n < Coords; ++n)
		{
			unsigned short cx0 = Offx + CoordStamp[n].P0.x * dx;
			unsigned short cy0 = Offy + CoordStamp[n].P0.y * dy;
			unsigned short cx1 = Offx + CoordStamp[n].P1.x * dx;
			unsigned short cy1 = Offy + CoordStamp[n].P1.y * dy;
			if (InImg(In, cy0, cx0) && InImg(In, cy1, cx1))
			{
				unsigned char C[3];
				if (ColorGrad == G2Pink) { Green2Pink(C, n); } else { Blue2Pink(C, n); }

				C[0] = (C[0] * 0.5) + In(cx0, cy0, 0, 0) * 0.5;
				C[1] = (C[1] * 0.5) + In(cx0, cy1, 0, 1) * 0.5;
				C[2] = (C[2] * 0.5) + In(cx1, cy1, 0, 2) * 0.5;
				Linexy (In,	cx0, cy0, cx1, cy1, C, false);
			}
		}
	}

	void PrintMatrix(CImg<unsigned char>& In, unsigned int i, unsigned int j, unsigned short Offx, unsigned short Offy, unsigned char ColorGrad)
	{
		double x = In.width(), y = In.height();
		double dx = (x / 21.0) / (double)i, dy = (y / 6.0) / (double)j;
		double dj = x / (double)j, di = y / (double)i;
		for (size_t ii = 0; ii < i; ++ii)
		{
			for (size_t jj = 0; jj < j; ++jj)
			{
				for (char n = 0; n < Coords; ++n)
				{
					unsigned short cx0 = round((jj * dj) + Offx + CoordStamp[n].P0.x * dx);
					unsigned short cy0 = y - round(Offy + ((ii * di) + CoordStamp[n].P0.y * dy));
					unsigned short cx1 = round((jj * dj) + Offx + CoordStamp[n].P1.x * dx);
					unsigned short cy1 = y - round(Offy + ((ii * di) + CoordStamp[n].P1.y * dy));
					if (InImg(In, cy0, cx0) && InImg(In, cy1, cx1))
					{
						unsigned char C[3];
						if (ColorGrad == G2Pink) { Green2Pink(C, n); }
						else { Blue2Pink(C, n); }

						C[0] = (C[0] * 0.5) + In(cx0, cy0, 0, 0) * 0.5;
						C[1] = (C[1] * 0.5) + In(cx1, cy0, 0, 1) * 0.5;
						C[2] = (C[2] * 0.5) + In(cx1, cy1, 0, 2) * 0.5;
						Linexy(In, cx0, cy0, cx1, cy1, C, false);
					}
				}
			}
		}
	}
};

// ###################################################################################################################################################
// ###################################################################################################################################################
// ###################################################################################################################################################

class YSX_ImgManip
{
public:
	double Perc0 = 0.125, Perc1 = 0.875; // Porcentages
	enum Colors
	{
		Pink7, Pink6, Pink5, Pink4, Pink3, Pink2, Pink1, Pink0,
		PinkD7, PinkD6, PinkD5, PinkD4, PinkD3, PinkD2, PinkD1, PinkD0,
	};
	const unsigned char ColorTab[14][3] = // Color Table, check 'enum'
	{
		{ 255, 163, 228 }, { 255, 140, 214 }, { 255, 116, 199 },
		{ 255, 93, 185 }, { 255, 70, 170 }, { 255, 47, 156 },
		{ 255, 23, 141 }, { 255, 0, 127 },
		{ 219, 0, 109 }, { 182, 0, 91 }, { 146, 0, 73 },
		{ 109, 0, 54 }, { 73, 0, 36 }, { 36, 0, 18 }
	};
	const unsigned short cSize = 14; // ColorTab.size()

	// DESIGN BG LIMITS, USE '7 * n' SIDE SIZES (2:1):
	bool BGLimit(double WIn, double HIn, int x, int y)
	{	//   _a___b
		// H |\AS\*|-- ATri
		//   |_\_h\|
		//	    W
		// Every division of 56, '7 * 8':
		double a = 0.625, b = 0.375;// , h = 0.625; // 7 * 5, 7 * 3, 7 * 5
		double H = 0.5;//, W = 1; // 7 / 14 | 7 * 4
		double t = LawSinRad(H, b, HPI);
		//double ATri = (H * b) / 2, AStamp = a * H, A = H * W;
		double dx = (y / cos(t)) * sin(t);
		if (x <= (WIn * a) + dx && x >= dx)
		{ return(true); } else { return(false); }
	}

	// #################################################

	void MyColors(CImg<unsigned char>& In)
	{
		unsigned short H = In.height(), W = In.width();
		unsigned char C[3];
		for (size_t y = 0; y < H; ++y)
		{
			for (size_t x = 0; x < W; ++x)
			{
				C[0] = 127.5 + In(x, y, 0, 0) * 0.5;
				C[1] = 0;
				C[2] = 63.75 + In(x, y, 0, 2) * 0.5;
				In.draw_point(x, y, C);
			}
		}
	}

	void PinkGrad(CImg<unsigned char>& In)
	{
		unsigned short H = In.height(), W = In.width();
		unsigned char C[3];
		for (size_t y = 0; y < H; ++y)
		{
			for (size_t x = 0; x < W; ++x)
			{
				double v = (double)(x * y) / (H * W);
				C[0] = 36 + 219.0 * v + In(x, y, 0, 0) * 0.5;
				C[1] = 163 * v + In(x, y, 0, 1) * 0.5 * pow(v, 7.77);
				C[2] = 18 + 210.0 * v + In(x, y, 0, 2) * 0.5;
				In.draw_point(x, y, C);
			}
		}
	}

	// #################################################

	void MyTurn(CImg<unsigned char>& In)
	{
		unsigned short W = In.width(), H = In.height();
		double y0, x0, y1, x1, y2, x2, y3, x3;
		double Rad, a, r, k = 7 / 9.0;
		double Step = PI / (9 * TAU * (W * 0.5));
		short n = 0;
		double Div = PI / 48.0;
		unsigned char C[4][3];
		for (char cn = 0; cn < 4; ++cn)
		{
			C[n][0] = ((cn * 3) / 12.0) * 255.0;
			C[n][1] = 0;
			C[n][2] = 255 - 128.0 * (((cn * 3) + 2) / 12.0);
		}
		
		for (Rad = 0; Rad <= PI; Rad += Step)
		{
			n = round(Rad / Div);
			for (short Curve = 0; Curve < 7; ++Curve)
			{
				//std::cout << "CURVE " << Curve << std::endl;
				for (short m = 0; m < 7 * 2; ++m)
				{
					//std::cout << "m " << m << std::endl;
					unsigned char CC[3];
					
					r = ((W * 0.5) - m - Curve * 7 * 3);
					a = r * sin(k * (TAU - Rad) * 9); // BOTTOM
					y0 = round(((double)H / W) * a * sin(9 * (TAU - Rad))) + H - 1;
					x0 = round(a * cos(9 * Rad)) + (W * 0.5);
					if (x0 < W && x0 > 0 && y0 < H && y0 > 0)
					{
						CC[0] = C[(Curve + n) % 4][0] * Perc0 + In(x0, y0, 0, 0) * Perc1;
						CC[1] = C[(Curve + n) % 4][1] * Perc0 + In(x0, y0, 0, 1) * Perc1;
						CC[2] = C[(Curve + n) % 4][2] * Perc0 + In(x0, y0, 0, 2) * Perc1;
						In.draw_point(x0, y0, CC);
					}
					
					a = r * sin(k * (HPI + TAU - Rad) * 9); // LEFT
					y1 = round(((double)H / W) * a * sin(9 * (HPI + TAU - Rad))) + (H * 0.5);
					x1 = round(a * cos(9 * (Rad - HPI)));
					if (x1 < W && x1 > 0 && y1 < H && y1 > 0)
					{
						CC[0] = C[(Curve + n + 1) % 4][0] * Perc0 + In(x1, y1, 0, 0) * Perc1;
						CC[1] = C[(Curve + n + 1) % 4][1] * Perc0 + In(x1, y1, 0, 1) * Perc1;
						CC[2] = C[(Curve + n + 1) % 4][2] * Perc0 + In(x1, y1, 0, 2) * Perc1;
						In.draw_point(x1, y1, CC);
					}
					
					a = r * sin(k * Rad * 9); // TOP
					y2 = round(((double)H / W) * a * sin(9 * Rad));
					x2 = round(a * cos(9 * Rad)) + (W * 0.5);
					if (x2 < W && x2 > 0 && y2 < H && y2 > 0)
					{
						CC[0] = C[(Curve + n + 2) % 4][0] * Perc0 + In(x2, y2, 0, 0) * Perc1;
						CC[1] = C[(Curve + n + 2) % 4][1] * Perc0 + In(x2, y2, 0, 1) * Perc1;
						CC[2] = C[(Curve + n + 2) % 4][2] * Perc0 + In(x2, y2, 0, 2) * Perc1;
						In.draw_point(x2, y2, CC);
					}

					a = r * sin(k * (TAU - Rad - HPI) * 9); // RIGHT
					y3 = round(((double)H / W) * a * sin(9 * (TAU - Rad - HPI))) + (H * 0.5);
					x3 = round(a * cos(9 * (HPI + Rad))) + W - 1;
					if (x3 < W && x3 > 0 && y3 < H && y3 > 0)
					{
						CC[0] = C[(Curve + n + 3) % 4][0] * Perc0 + In(x3, y3, 0, 0) * Perc1;
						CC[1] = C[(Curve + n + 3) % 4][1] * Perc0 + In(x3, y3, 0, 1) * Perc1;
						CC[2] = C[(Curve + n + 3) % 4][2] * Perc0 + In(x3, y3, 0, 2) * Perc1;
						In.draw_point(x3, y3, CC);
					}
				}
			}
		}
	}

	// #################################################

	// SHADOWS BY LINE DENSITY:
	CImg<unsigned char> LineShadowBG(CImg<unsigned char> In, bool Sine)
	{
		unsigned short W = In.width(), H = In.height();
		CImg<unsigned char> Ret(W, H, 1, 3, 0);
		FillArea(Ret, 1, 1, (unsigned char*)&ColorTab[Pink7]);
		const double dc = 1.0 / cSize; // Delta Color

		for (unsigned short n = 0; n < H; ++n)
		{
			std::cout << "H: " << n << std::endl;
			for (unsigned short m = 0; m < W; ++m)
			{
				if (BGLimit(W, H, m, n))
				{
					unsigned char C[] = { In(m, n, 0, 0), In(m, n, 0, 1), In(m, n, 0, 2) };
					double CAvg = (C[0] + C[1] + C[2]) / 765.0;
					for (int c = 0; c < cSize; ++c)
					{
						if (CAvg < dc * (c + 1))
						{
							if (n % (c + 2) == 0)
							{
								unsigned short nn = n + sin(((double)m / W) * 1554) * 14;
								Ret.draw_point(m, nn, (unsigned char*)&ColorTab[c]);
							}
						}
					}
				}
			}
		}
		return(Ret);
	}

	// #################################################

	void MainPrint(CImg<unsigned char>& In)
	{
		// QUALITY:
		In.resize((In.width() * 7), (In.height() * 7), 3, 3, 6, 0, 0, 0, 0, 0);
		std::cout << "RESIZED!\n";
		// BACKGROUND:
		unsigned short W = In.width(), H = In.height();
		CImg<unsigned char> I = In; // MAIN IMAGE
		/*{
			YSX_Stamp S; for (char n = 0; n < 7; ++n) { S.PrintMatrix(I, 2, 4, n, n, S.B2Pink); S.Print(I, n, n, S.B2Pink); }
			std::cout << "STAMPED!\n";
			for (short y = 0; y < In.height(); ++y)
			{
				for (short x = 0; x < In.width(); ++x)
				{
					unsigned char C[] =
					{
						(I(x, y, 0, 0) + In(x, y, 0, 0)) * 0.5,
						(I(x, y, 0, 1) + In(x, y, 0, 1)) * 0.5,
						(I(x, y, 0, 2) + In(x, y, 0, 2)) * 0.5
					};
					In.draw_point(x, y, C);
				}
			}
		}*/
		std::cout << "LAYER!\n";
		CImg<unsigned char> BG(W, H, 1, 3, 255); // BG IMG
		MyTurn(BG);
		std::cout << "BG DONE!\n";
		MyColors(BG); PinkGrad(BG);
		BG = LineShadowBG(BG, false); // Make it look like bank note printed lines
		std::cout << "LINES!\n";
		for (short y = 0; y < In.height(); ++y)
		{
			for (short x = 0; x < In.width(); ++x)
			{
				unsigned char C[] =
				{
					(I(x, y, 0, 0) * 0.33 + In(x, y, 0, 0)) * 0.67,
					0,
					(I(x, y, 0, 2) * 0.33 + In(x, y, 0, 2)) * 0.67
				};
				In.draw_point(x, y, C);
			}
		}
		std::cout << "RE-LAYER!\n";

		// ### END ###
		In = LineShadowBG(In, true);
		In.resize(1120, 560, 3, 3, 6, 0, 0, 0, 0, 0); // Ratio is always 2:1. Make it better quality later.
		In.save_bmp("!IMAGE_MANIP_OVER.bmp");
		BG.save_bmp("!IMAGE_MANIP_OVER_BG.bmp");
	}

	// #################################################

	YSX_ImgManip() {}
	~YSX_ImgManip() {}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_