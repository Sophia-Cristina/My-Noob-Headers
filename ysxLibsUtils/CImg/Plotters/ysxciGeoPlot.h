#pragma once

#ifndef YSXCIGEOPLOT_H
#define YSXCIGEOPLOT_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Plotting things related to geometry!
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ######################################################################

// ############## TRIGONOMETRIC:

// PLOT CIRCLE WITH ORIGIN AT X AND Y:
void ysxCIMG_DRAW_Circle(CImg<uint8_t>& Img, double r, size_t x, size_t y, uint8_t* C = nullptr)
{
	size_t yc, xc;
	double dt = 1.0 / r;
	uint8_t Cc[3];

	for (double rad = 0; rad <= TAU; rad += dt) // MUDAR SE NESCESSARIO
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C)	{ ysxCOLOR_LinearRGB(rad / TAU, 1, 1, Cc); Img.draw_point(xc, yc, Cc);	}
			else { Img.draw_point(xc, yc, C); }
		}
	}
}
// PLOT CIRCLE THAT FITS AN IMAGE:
void ysxCIMG_DRAW_Circle(CImg<uint8_t>& Img, uint8_t* C = nullptr)
{
	double r; Img.width() < Img.height() ? r = Img.width() : r = Img.height(); r -= 1; r *= 0.5;
	double dt = 1.0 / r;
	size_t yc, xc, x = (size_t)floor(Img.width() * 0.5), y = (size_t)floor(Img.height() * 0.5);
	uint8_t Cc[3];

	for (double rad = 0; rad <= TAU; rad = rad + dt)
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (!C) { ysxCOLOR_LinearRGB(rad / TAU, 1, 1, Cc); Img.draw_point(xc, yc, Cc); }
		else { Img.draw_point(xc, yc, C); }
	}
}

// TURN, DRAWS A CIRCULAR CURVE BASED ON TURN NUMBER:
void ysxCIMG_DRAW_Arc(CImg<uint8_t>& Img, double r, size_t x, size_t y, double Ini, double Turn, uint8_t* C = nullptr)
{
	size_t yc, xc;
	double rad, dt = (Turn - Ini) / (TAU * r);
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	uint8_t c[3];

	for (rad = Ini; rad <= Turn; rad += dt)
	{
		yc = y + round(sin(TAU - rad) * r); xc = x + round(cos(rad) * r);
		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB((rad - Ini) / (Turn - Ini), 1, 1, c); Img.draw_point(xc, yc, c); }
			else { Img.draw_point(xc, yc, C); }
		}
	}
}

// ######################################################################

// ############## RADIUS:

// PLOT RADIUS:
void ysxCIMG_DRAW_Radius(CImg<uint8_t>& Img, double r, size_t x, size_t y, double rad, bool Triangle, bool Border, uint8_t* C = nullptr)
{
	size_t yc, xc, rn, xend = (size_t)round(cos(rad) * r), yend = (size_t)round(sin(rad) * r);
	uint8_t c[3], IC[3];

	for (rn = 0; rn <= r; rn = ++rn)
	{
		yc = y + round(sin(rad) * rn); xc = x + round(cos(rad) * rn);

		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB(rn / r, 1, 1, c); Img.draw_point(xc, yc, c); }
			else { Img.draw_point(xc, yc, C); }
			if (Triangle)
			{
				if (!C) { IC[0] = 255 - c[0]; IC[1] = 255 - c[1]; IC[2] = 255 - c[2]; }
				else { IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2]; }
				Img.draw_point(xc, y, IC); Img.draw_point(x + xend, yc, IC);
			}
		}
	}
	if (Border) { if (!C) { ysxCIMG_DRAW_Circle(Img, r, x, y, c); } else { ysxCIMG_DRAW_Circle(Img, r, x, y, C); } }
}


void ysxCIMG_DRAW_RadiusPolygon(CImg<uint8_t>& Img, double r, size_t x, size_t y, double OffSet, int Divisions, bool Triangle, bool Border, uint8_t* C = nullptr)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		if (!C) { ysxCIMG_DRAW_Radius(Img, r, x, y, n, Triangle, Border); } // Make 'Border' to be painted only once
		else { ysxCIMG_DRAW_Radius(Img, r, x, y, n, Triangle, Border, C); }		
	}
}


// ######################################################################

// ############## CYCLOIDS:

// HYPOCYCLOID / HYPOTROCHOID:
// Hypocycloid if 'd = r'.
void ysxDRAW_HypoCycl(CImg<uint8_t>& Img, double R, double r, size_t x, size_t y, double t0, double t1, double d = 1, uint8_t* C = nullptr)
{
	double Arc = (r * 8 * ((R / r) - 1)), dt = ((t1 - t0) / Arc) / (PI * 4);
	if (t0 < 0) { t0 = TAU + t0; } if (t1 < t0) { double T = t0; t0 = t1; t1 = T; }
	size_t yc, xc;
	uint8_t c[] = { 0, 0, 0 };
	for (double t = t0; t <= t1; t += dt)
	{
		xc = x + ((R - r) * cos(t) + d * cos(t * (R - r) / r));
		yc = y + ((R - r) * sin(t) - d * sin(t * (R - r) / r));
		if (!C) { ysxCOLOR_LinearRGB((t - t0) / (t1 - t0), 1, 1, c); Img.draw_point(xc, yc, c); }
		else { Img.draw_point(xc, yc, C); }
	}
}

// EPICYCLOID / EPITROCHOID:
// Epicycloid if 'd = r'.
void ysxDRAW_EpiCycl(CImg<uint8_t>& Img, double R, double r, size_t x, size_t y, double t0, double t1, double d = 1, uint8_t* C = nullptr)
{
	if (t0 < 0) { t0 = TAU + t0; } if (t1 < t0) { double T = t0; t0 = t1; t1 = T; }
	double dt = ((t1 - t0) / (TAU * (R + r))) / (PI * 4);
	size_t yc, xc;
	uint8_t c[] = { 0, 0, 0 };
	for (double t = t0; t <= t1; t += dt)
	{
		yc = y + ((R + r) * sin(t) - d * sin(t * (R + r) / r));
		xc = x + ((R + r) * cos(t) - d * cos(t * (R + r) / r));
		if (!C) { ysxCOLOR_LinearRGB((t - t0) / (t1 - t0), 1, 1, c); Img.draw_point(xc, yc, c); }
		else { Img.draw_point(xc, yc, C); }
	}
}

// ############################################################################################################################################

// ############## POLYGONAL:

// PLOT POLYGON:
void ysxCIMG_DRAW_Polygon(CImg<uint8_t>& Img, int Sides, double r, size_t x, size_t y, bool Vertex, uint8_t* C = nullptr)
{
	size_t xc, yc, Count = 0;
	Point3D<uint8_t> RGB = { 255, 0, 127 };
	if (Sides < 3) { Sides = 3; }
	std::vector<Point<int>> Coord(Sides);
	double Div = TAU / Sides;
	uint8_t c[] = { 255, 0, 0 };

	for (double n = 0.0; n <= TAU; n = n + Div)
	{
		xc = x + round(cos(n) * r);
		yc = y + round(sin(n) * r);
		//std::cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / TAU) * 360 << std::endl;
		if (Count < Sides) { Coord[Count].x = xc; Coord[Count].y = yc; }
		++Count;

		if (Vertex)
		{
			if (!C) { ysxCOLOR_LinearRGB(n / TAU, 1, 1, c); ysxCIMG_AddVert(Img, xc, yc, 3, c); }
			else { ysxCIMG_AddVert(Img, xc, yc, 3, C); }
		}
	}
	for (size_t ns = 1; ns < Sides; ++ns)
	{
		if (ysxCIMG_InImg(Img, Coord[ns].y, Coord[ns].x) && ysxCIMG_InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			if (!C) { ysxCOLOR_LinearRGB(ns - 1 / Sides, 1, 1, c); ysxCIMG_DRAW_Line(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, c); }
			else { ysxCIMG_DRAW_Line(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, C); }
			if (ns == Sides - 1) { ysxCIMG_DRAW_Line(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, c); }
		}
	}

}


// #################################################
// #################################################
// #################################################


// ###################################
// ############## CLASSES ##############
// ###################################

// ############## PRINT TRIANGLE
// * NOTE: This code is old and badly made, so i'm going to optmize and reduce verbosity. This may change functions and other things and may lose compatibility.
class ysxCIMG_DRAW_Tri
{
public:
	// CONFIG:
	size_t Border = 25;
	size_t ImgWidth = 0;
	size_t ImgHeight = 0;
	size_t Offy = 0;

	size_t x[3] = { 0, 0, 0 };
	size_t y[3] = { 0, 0, 0 };

	Point<size_t> Coord[3] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
	Point<size_t> SclCrd[3] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
	Point<size_t> Midpoint[3] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
	Point<size_t> Circumcenter = { 0, 0 };

	uint8_t ColorSides[3] = { 255, 0, 0 };
	uint8_t ColorBisectors[3] = { 191, 191, 255 };
	uint8_t ColorHeightLine[3] = { 127, 127, 127 };
	uint8_t ColorIncircle[3] = { 255, 191, 223 };
	bool LRGB = false;
	
	double Scale = 1.0;

	// Triangle information:
	double a = 0, b = 0, c = 0;
	double h = 0;
	double gamma = 0, beta = 0, alpha = 0;
	double area = 0, perimeter = 0;
	double BisA = 0, BisB = 0, BisC = 0;
	double inradius = 0;
	double IA = 0, IB = 0, IC = 0;

	// OUTPUT:
	CImg<uint8_t> TriOut;


	// ####### INTERNAL #######


	size_t GetHorizontalExtent()
	{
		size_t X0 = Coord[0].x;
		size_t X1 = Coord[1].x;
		size_t X2 = Coord[2].x;
		size_t MinX = X0 < X1 ? X0 : X1;
		MinX = MinX < X2 ? MinX : X2;
		size_t MaxX = X0 > X1 ? X0 : X1;
		MaxX = MaxX > X2 ? MaxX : X2;
		return(MaxX - MinX);
	}

	void EmptyImg() { TriOut = CImg<uint8_t>::CImg(); }

	/*void PaintScreen(uint8_t* Color)
	{
		if (!TriOut) { return; }
		TriOut.fillStyle = `rgb(${Color[0]}, ${Color[1]}, ${Color[2]})`;
		TriOut.fillRect(0, 0, ImgWidth, ImgHeight);
	}*/


	void ChangeBorder(size_t BorderNewSize)
	{
		if (BorderNewSize < 0) { BorderNewSize = 0; }
		Border = BorderNewSize;
		size_t HorizontalExtent = GetHorizontalExtent();
		ImgWidth = ceil(Scale * HorizontalExtent) + (Border * 2);
		ImgHeight = ceil(h * Scale) + (Border * 2);
		Offy = ImgHeight - Border;

		for (uint8_t i = 0; i < 3; ++i)
		{
			x[i] = Border + (Scale * Coord[i].x);
			y[i] = Offy - (Scale * Coord[i].y);
		}
	}
	
	
	// ####### NEW TRIANGLE #######


	void NewTri(ysxTRI_Triangle TriInput)
	{
		a = TriInput.a;
		b = TriInput.b;
		c = TriInput.c;

		h = TriInput.Height;

		gamma = TriInput.Gamma;
		beta = TriInput.Beta;
		alpha = TriInput.Alpha;

		area = TriInput.Area;
		perimeter = TriInput.Perimeter;

		BisA = TriInput.BisA;
		BisB = TriInput.BisB;
		BisC = TriInput.BisC;

		inradius = TriInput.Inradius;

		IA = TriInput.IA;
		IB = TriInput.IB;
		IC = TriInput.IC;

		ImgHeight = ceil(h * Scale) + (Border * 2);
		Offy = ImgHeight - Border;

		for (uint8_t i = 0; i < 3; ++i)
		{
		  Coord[i].x = TriInput.Coord[i].x; Coord[i].y = TriInput.Coord[i].y;
		  SclCrd[i].x = Scale * Coord[i].x; SclCrd[i].y = Scale * Coord[i].y;
		  Midpoint[i].x = TriInput.Mid[i].x; Midpoint[i].y = TriInput.Mid[i].y;
		  x[i] = Border + (Scale * Coord[i].x); y[i] = Offy - (Scale * Coord[i].y);
		}
		
		size_t HorizontalExtent = GetHorizontalExtent();
		ImgWidth = ceil(Scale * HorizontalExtent) + (Border * 2);

		Circumcenter.x = TriInput.Circumcenter.x;
		Circumcenter.y = TriInput.Circumcenter.y;
	}


	// ####### CONSTRUCTOR #######


	ysxCIMG_DRAW_Tri(ysxTRI_Triangle TriInput, double ScaleIn, size_t BorderSize, uint8_t* ColorIn = nullptr)
	{
		Scale = ScaleIn;
		NewTri(TriInput);
		TriOut = CImg<uint8_t>::CImg(ImgWidth, ImgHeight, 1, 3, 0);
		Border = BorderSize;

		if (ColorIn)
		{
			ColorSides[0] = ColorIn[0]; ColorSides[1] = ColorIn[1]; ColorSides[2] = ColorIn[2];
			ColorIncircle[0] = floor((255 - ColorSides[0]) * 0.5);
			ColorIncircle[1] = floor((255 - ColorSides[1]) * 0.5);
			ColorIncircle[2] = floor((255 - ColorSides[2]) * 0.5);
			ColorHeightLine[0] = 127; ColorHeightLine[1] = 127; ColorHeightLine[2] = 127;
			ColorBisectors[0] = floor(ColorSides[0] * 0.5);
			ColorBisectors[1] = floor(ColorSides[1] * 0.5);
			ColorBisectors[2] = ColorSides[2];
		}
		else
		{
			ColorIncircle[0] = 255; ColorIncircle[1] = 255; ColorIncircle[2] = 255;
			ColorHeightLine[0] = 127; ColorHeightLine[1] = 127; ColorHeightLine[2] = 127;
			ColorBisectors[0] = 191; ColorBisectors[1] = 191; ColorBisectors[2] = 255;
		}
	}

	ysxCIMG_DRAW_Tri(ysxTRI_Triangle TriInput, double ScaleIn, uint8_t* ColorIn = nullptr)
	{
		Scale = ScaleIn;
		NewTri(TriInput);
		TriOut = CImg<uint8_t>::CImg(ImgWidth, ImgHeight, 1, 3, 0);

		if (ColorIn)
		{
			ColorSides[0] = ColorIn[0]; ColorSides[1] = ColorIn[1]; ColorSides[2] = ColorIn[2];
			ColorIncircle[0] = floor((255 - ColorSides[0]) * 0.5);
			ColorIncircle[1] = floor((255 - ColorSides[1]) * 0.5);
			ColorIncircle[2] = floor((255 - ColorSides[2]) * 0.5);
			ColorHeightLine[0] = 127; ColorHeightLine[1] = 127; ColorHeightLine[2] = 127;
			ColorBisectors[0] = floor(ColorSides[0] * 0.5);
			ColorBisectors[1] = floor(ColorSides[1] * 0.5);
			ColorBisectors[2] = ColorSides[2];
		}
		else
		{
			ColorIncircle[0] = 255; ColorIncircle[1] = 255; ColorIncircle[2] = 255;
			ColorHeightLine[0] = 127; ColorHeightLine[1] = 127; ColorHeightLine[2] = 127;
			ColorBisectors[0] = 191; ColorBisectors[1] = 191; ColorBisectors[2] = 255;
		}
	}

	// ####### TRIANGLE PERIMETER #######


	void TriPeriPrint(bool DrawVertex, bool DrawText, bool DrawHeightLine)
	{
		// A -> B = side b
		if (LRGB) { ysxCIMG_DRAW_Line(TriOut, x[0], y[0], x[1], y[1]); }
		ysxCIMG_DRAW_Line(TriOut, x[0], y[0], x[1], y[1], ColorSides);

		uint8_t nc[3], tc[3];
		// B -> C = side c
		if (LRGB) { ysxCIMG_DRAW_Line(TriOut, x[1], y[1], x[2], y[2]); }
		else
		{
			nc[0] = (ColorSides[0] + 85) % 256;
			nc[1] = (ColorSides[1] + 85) % 256;
			nc[2] = (ColorSides[2] + 85) % 256;
			ysxCIMG_DRAW_Line(TriOut,x[1], y[1], x[2], y[2], nc);
		}
		
		// C -> A = side a
		if (LRGB) { ysxCIMG_DRAW_Line(TriOut, x[2], y[2], x[0], y[0]); }
		else
		{
			nc[0] = (ColorSides[0] + 170) % 256;
			nc[1] = (ColorSides[1] + 170) % 256;
			nc[2] = (ColorSides[2] + 170) % 256;
			ysxCIMG_DRAW_Line(TriOut, x[2], y[2], x[0], y[0], nc);
		}

		if (DrawText)
		{
			nc[0] = (255 - ColorSides[0]) * 0.75; nc[1] = (255 - ColorSides[1]) * 0.75; nc[2] = (255 - ColorSides[2]) * 0.75;
			tc[0] = ColorSides[0]; tc[1] = ColorSides[1]; tc[2] = ColorSides[2];

			ysxCIMG_AddText(TriOut, 16, y[0] - 18, "a: " + std::to_string(a), tc);
			ysxCIMG_AddText(TriOut, 16, y[0] - 10, "Gamma: " + std::to_string(gamma), nc);

			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.5), y[1] - 16, "b: " + std::to_string(b), tc);
			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.5), y[1] - 8, "Alpha: " + std::to_string(alpha), nc);

			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.75), y[2] - 18, "c: " + std::to_string(c), tc);
			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.75), y[2] - 10,  "Beta: " + std::to_string(beta), nc);

			nc[0] = 255; nc[1] = 127; nc[2] = 127;
			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.5), ImgHeight * 0.5, "Area: " + std::to_string(area), nc);
			nc[0] = 127; nc[1] = 255; nc[2] = 127;
			ysxCIMG_AddText(TriOut, round(ImgWidth * 0.5), (ImgHeight * 0.5) + 8, "Peri.: " + std::to_string(perimeter), nc);
		}

		if (DrawVertex)
		{
			nc[0] = 255; nc[1] = 0; nc[2] = 0;
			ysxCIMG_AddVert(TriOut, x[0], y[0], 3, nc);
			nc[0] = 0; nc[1] = 255; nc[2] = 0;
			ysxCIMG_AddVert(TriOut, x[1], y[1], 3, nc);
			nc[0] = 0; nc[1] = 0; nc[2] = 255;
			ysxCIMG_AddVert(TriOut, x[2], y[2], 3, nc);
		}

		if (DrawHeightLine)
		{
			size_t HeightX = SclCrd[1].x + Border;
			ysxCIMG_DRAW_Line(TriOut, HeightX, Offy, HeightX, Offy - round(Scale * h), ColorHeightLine);
			ysxCIMG_DRAW_Line(TriOut, HeightX, Offy - 5, HeightX + 5, Offy - 5, ColorHeightLine); // Right angle square
			ysxCIMG_DRAW_Line(TriOut, HeightX + 5, Offy - 5, HeightX + 5, Offy, ColorHeightLine);
			if (DrawText) { ysxCIMG_AddText(TriOut, HeightX + 16, Offy - round(Scale * h * 0.5) - 8, "Height: " + std::to_string(h), ColorHeightLine); }
			if (DrawVertex)
			{
				nc[0] = 127; nc[1] = 127; nc[2] = 127;
				ysxCIMG_AddVert(TriOut, HeightX, Offy, 3, nc);
			}
		}
	}


	// ####### BISECTORS #######


	void TriBisectorPrint(bool DrawText)
	{
		double AngleA = beta + alpha * 0.5;
		ysxCIMG_DRAW_LineRay(TriOut, BisA * Scale, AngleA,  x[1], y[1], false, ColorBisectors);
		double AngleB = PI + beta * 0.5;
		ysxCIMG_DRAW_LineRay(TriOut, BisB * Scale, AngleB, x[2], y[2], false, ColorBisectors);
		double AngleC = (PI * 2.0) - gamma * 0.5;
		ysxCIMG_DRAW_LineRay(TriOut, BisC * Scale, AngleC, x[0], y[0], false, ColorBisectors);

	  if (DrawText)
	  {
		ysxCIMG_AddText(TriOut, 16, y[0], "BisA: " + std::to_string(BisA), ColorBisectors);
		ysxCIMG_AddText(TriOut, round(ImgWidth * 0.5), y[1], "BisB: " + std::to_string(BisB), ColorBisectors);
		ysxCIMG_AddText(TriOut, round(ImgWidth * 0.75), y[2], "BisC: " + std::to_string(BisC), ColorBisectors);
	  }
	}


	// ####### INCIRCLE #######
	

	void TriIncirclePrint(bool DrawVertex)
	{
	  double Angle = gamma * 0.5;

	  size_t xc = x[0] + Scale * IA * cos(Angle);
	  size_t yc = y[0] - Scale * IA * sin(Angle);

	  if (DrawVertex) { ysxCIMG_AddVert(TriOut, xc, yc, 3, ColorIncircle); }
	  if (LRGB) { ysxCIMG_DRAW_Circle(TriOut, inradius * Scale, xc, yc); }
	  else { ysxCIMG_DRAW_Circle(TriOut, inradius * Scale, xc, yc, ColorIncircle); }
	}


	// ####### MIDPOINTS #######
  

	void TriMidpointPrint()
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
		  if (LRGB)
		  {
			uint8_t vc[3]; ysxCOLOR_LinearRGB(i / 3.0, 1, 1, vc);
			ysxCIMG_AddVert(TriOut, Border + (Scale * Midpoint[i].x), Offy - (Scale * Midpoint[i].y), 3, vc);
		  }
		  else { ysxCIMG_AddVert(TriOut, Border + (Scale * Midpoint[i].x), Offy - (Scale * Midpoint[i].y), 3, ColorSides); }
		}
	}


	// ####### TRIGONOMETRY #######


	void TriTrigPrint()
	{
		CImg<uint8_t> StringComp(ImgWidth, (8 * 3) + 4, 1, 3, 255);
		std::string S0 = "# sin abc: " + std::to_string(sin(alpha)) + " | " + std::to_string(sin(beta)) + " | " + std::to_string(sin(gamma));
		std::string S1 = "# cos abc: " + std::to_string(cos(alpha)) + " | " + std::to_string(cos(beta)) + " | " + std::to_string(cos(gamma));
		std::string S2 = "# tan abc: " + std::to_string(tan(alpha)) + " | " + std::to_string(tan(beta)) + " | " + std::to_string(tan(gamma));
		uint8_t nc[3] = { 0, 0, 0 };
		ysxCIMG_AddText(StringComp, 4, 1, S0, nc);
		ysxCIMG_AddText(StringComp, 4, 9, S1, nc);
		ysxCIMG_AddText(StringComp, 4, 17, S2, nc);
		TriOut = ysxCIMG_JoinImg(TriOut, StringComp, 1);
	}


	// ####### FLAGS #######
	/* Flags:
		128 = Add vertex to incircle
		 64 = Add text to bisectors
		 32 = Add vertex to perimeter
		 16 = Trigonometric functions
		  8 = Midpoints
		  4 = Incircle
		  2 = Bisectors
		  1 = Perimeter*/
	void TriPrintByFlags(bool DrawText, uint8_t Flags = 255)
	{
		if (Flags & 1) { TriPeriPrint(Flags & 32, DrawText, true); std::cout << "TriPeriPrint();\n"; }
		if (Flags & 2) { TriBisectorPrint(Flags & 64); std::cout << "TriBisectorPrint();\n"; }
		if (Flags & 4) { TriIncirclePrint(Flags & 128); std::cout << "TriIncirclePrint();\n"; }
		if (Flags & 8) { TriMidpointPrint(); std::cout << "TriMidpointPrint();\n"; }
		if (Flags & 16) { TriTrigPrint(); std::cout << "TriTrigPrint();\n"; }
		/*const Context = TriOut.getContext("2d");
		if (LRGB)
		{
		  ysxCIMG_AddVert(Context, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, [255, 255, 255]);
		}
		else { ysxCIMG_AddVert(Context, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, ColorSides); }*/
	}
};


// #################################################
// #################################################
// #################################################

#endif
