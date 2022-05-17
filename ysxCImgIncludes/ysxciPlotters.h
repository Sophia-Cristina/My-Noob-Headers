#pragma once

#ifndef YSXCIPLOTTER_H
#define YSXCIPLOTTER_H

using namespace cimg_library;

// ############################################################################################################################################
// ################################################# ANOTA��ES E ATEN��ES #################################################
// !!!!!!!	
// !!!!!!!	MAKE ALL POSSIBLE PLOTTERS TO WRITE ON AN INPUT IMAGE;
// !!!!!!!	MAKE ALL POSSIBLE PLOTTERS TO ACCEPT VECTORS AS INPUTS TO STOP REDUNDANCY OF FUNCTIONS, LIKE "POLAR", "CIRCLE" AND "TURN";
// !!!!!!!	
// !!!!!!!	LOG (TRY TO MANTAIN ORDER):
// !!!!!!!	* Functions that had the name 'SaveVector...' are now 'PrintVector...';
// !!!!!!!	* 'yrto *= 2' removed from lot of functions;
// !!!!!!!	* Huge changes, take care;
// !!!!!!!	
// ################################################# ANOTA��ES E ATEN��ES #################################################
// ############################################################################################################################################

// ###################################

// ############################################################################################################################################
// ############## CIRCULARES:

// PLOT CIRCLE WITH ORIGIN AT X AND Y:
void Circlexy(CImg<uint8_t>& Img, double r, uint16_t x, uint16_t y, uint8_t* C)
{
	uint16_t yc, xc;
	double dt = 1.0 / r;
	if (!C) { C = new uint8_t[3]; }

	for (double rad = 0; rad <= TAU; rad += dt) // MUDAR SE NESCESSARIO
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, yc, xc)) { Img.draw_point(xc, yc, C); }
	}
}
void Circlexy(CImg<uint8_t>& Img, double r, uint16_t x, uint16_t y)
{
	uint16_t yc, xc;
	double dt = 1.0 / r;
	uint8_t C[3];

	for (double rad = 0; rad <= TAU; rad += dt) // MUDAR SE NESCESSARIO
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, yc, xc))
		{
			LinearRGBuc(rad / TAU, 1, 1, C);
			Img.draw_point(xc, yc, C);
		}
	}
}

// PLOT CIRCLE THAT FITS AN IMAGE:
void Circle(CImg<uint8_t>& Img, uint8_t* C)
{
	double r; Img.width() <= Img.height() ? r = Img.width() : r = Img.height(); r -= 1; r *= 0.5;
	double dt = 1.0 / r;
	uint16_t yc, xc, x = floor(Img.width() * 0.5), y = Img.height() - floor(Img.height() * 0.5);

	for (double rad = 0; rad <= TAU; rad = rad + dt)
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, yc, xc)) { Img.draw_point(xc, yc, C); }
	}
}
void Circle(CImg<uint8_t>& Img)
{
	double r; Img.width() <= Img.height() ? r = Img.width() : r = Img.height(); r -= 1; r *= 0.5;
	double dt = 1.0 / r;
	uint16_t yc, xc, x = floor(Img.width() * 0.5), y = Img.height() - floor(Img.height() * 0.5);
	uint8_t C[3];

	for (double rad = 0; rad <= TAU; rad = rad + dt)
	{
		yc = y + round(sin(rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, y, x)) { LinearRGBuc(rad / TAU, 1, 1, C); Img.draw_point(x + xc, y + yc, C); }
	}
}

// ######################################################################

/*METRIC LINES:
Vertical OR horizontal divisions.
Make your changes based on the idea that the metric is scaled by image size.*/
void MetricLines(CImg<uint8_t>& I, double a1, double a2, double Div, bool VertHori, bool Text, uint8_t* Clr) // REFAZER, e adicionar polar
{
	if (a1 > a2) { double T = a1; a1 = a2; a2 = T; }
	double sx = I.width(), sy = I.height(); // size x and y
	double Ratio = 1, Mid = 1, Delta = a2 - a1;
	uint16_t C = 0, x, y;
	if (Delta > 0)
	{
		Div = Delta / Div;

		if (VertHori) { Ratio = sx / Delta;	Mid = sy * 0.5; }
		else { Ratio = sy / Delta; Mid = sx * 0.5; }

		for (double a = a1; a <= a2; a += Div)
		{
			if (VertHori)
			{
				x = C * Div * Ratio; ++C;
				for (y = 0; y < sy; ++y) { I.draw_point(x, y, Clr); }
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					AddText(I, x, Mid, std::to_string(a), Clr);
				}
			}
			else
			{
				y = sy - (C * Div * Ratio); ++C;
				for (x = 0; x < sx; ++x) { I.draw_point(x, y, Clr); }
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					AddText(I, Mid, y, std::to_string(a), Clr);
				}
			}
		}
	}
}

// ######################################################################

// POLAR (arrumar, roubei da classe, colocar x e y), fazer um com raio:
// FAZER UMA VERS�O COM VECTOR, SEM SER POLIGONAL COMO AQUELE QUE J� TEM.
void Polar(CImg<uint8_t>& I, double r, double x, double y, double t1, double t2, double Omega)
{
	if (t1 < 0) { t1 =  TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double Amp, dt = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		Amp = r * MiniForm(t, Omega); // FORMULA
		yc = y + round(Amp * sin(t)); xc = x + round(Amp * cos(t));
		if (InImg(I, yc, xc))
		{
			LinearRGBuc((t - t1) / (t2 - t1), 1, 1, c);
			I.draw_point(xc, yc, c);
		}
	}
}
void Polar(CImg<uint8_t>& I, double r, double x, double y, double t1, double t2, double Omega, uint8_t* C)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double Amp, dt = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	uint16_t yc, xc;
	for (double t = t1; t <= t2; t += dt)
	{
		Amp = r * MiniForm(t, Omega); // FORMULA
		yc = y + round(Amp * sin(t)); xc = x + round(Amp * cos(t));
		if (InImg(I, yc, xc)) { I.draw_point(xc, yc, C); }
	}
}

// HYPOCYCLOID (FIX PERIMETER OR MAYBE THE PROBLEM IS ON THE COORDS):
void HypoCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2)
{
	double Arc = (r * 8 * ((R / r) - 1)), dt = (t2 - t1) / Arc;
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		xc = x + ((R - r) * cos(t) + r * cos(t * (R - r) / r));
		yc = y + ((R - r) * sin(t) - r * sin(t * (R - r) / r));
		if (InImg(I, yc, xc))
		{
			LinearRGBuc((t - t1) / (t2 - t1), 1, 1, c);
			I.draw_point(xc, yc, c);
		}
	}
}
void HypoCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2, uint8_t* C)
{
	double Arc = (r * 8 * ((R / r) - 1)), dt = (t2 - t1) / Arc;
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	uint16_t yc, xc;
	for (double t = t1; t <= t2; t += dt)
	{
		xc = x + ((R - r) * cos(t) + r * cos(t * (R - r) / r));
		yc = y + ((R - r) * sin(t) - r * sin(t * (R - r) / r));
		if (InImg(I, yc, xc))	{ I.draw_point(xc, yc, C); }
	}
}

// EPICYCLOID (WIP, PERIMETER AND MORE):
void EpiCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double dt = (t2 - t1) / (TAU * (R + r)); // N�o lembro, mudar depois
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		yc = y + ((R + r) * sin(t) - r * sin(t * (R + r) / r));
		xc = x + ((R + r) * cos(t) - r * cos(t * (R + r) / r));
		if (InImg(I, yc, xc))
		{
			LinearRGBuc((t - t1) / (t2 - t1), 1, 1, c);
			I.draw_point(x, y, c);
		}
	}
}
void EpiCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2, uint8_t* C)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double dt = (t2 - t1) / (TAU * (R + r));
	uint16_t yc, xc;
	for (double t = t1; t <= t2; t += dt)
	{
		yc = y + ((R + r) * sin(t) - r * sin(t * (R + r) / r));
		xc = x + ((R + r) * cos(t) - r * cos(t * (R + r) / r));
		if (InImg(I, yc, xc)) { I.draw_point(xc, yc, C); }
	}
}

// TURN:
void Turn(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double Ini, double Turn, uint8_t* C)
{
	uint16_t yc, xc;
	double rad, dt = (Turn - Ini) / (TAU * r);
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }

	for (rad = Ini; rad <= Turn; rad += dt)
	{
		yc = y + round(sin(TAU - rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, yc, xc)) { Img.draw_point(xc, yc, C); }
	}
}
void Turn(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double Ini, double Turn)
{
	uint16_t yc, xc;
	double rad, dt = (Turn - Ini) / (TAU * r);
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	uint8_t C[3];

	for (rad = Ini; rad <= Turn; rad += dt)
	{
		yc = y + round(sin(TAU - rad) * r); xc = x + round(cos(rad) * r);
		if (InImg(Img, yc, xc))
		{
			LinearRGBuc((rad - Ini) / (Turn - Ini), 1, 1, C);
			Img.draw_point(xc, yc, C);
		}
	}
}

// PLOT RADIUS:
void Radius(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double rad, bool Triangle, bool Border)
{
	uint16_t xc, yc, rn;
	double Sin = sin(TAU - rad), Cos = cos(rad);
	int xend = round(Cos * r);
	uint8_t C[3], IC[3];

	for (rn = 0; rn <= r; ++rn)
	{
		yc = y + round(Sin * rn); xc = x + round(Cos * rn);
		if (InImg(Img, yc, xc))
		{
			LinearRGBuc(rn / r, 1, 1, C); Img.draw_point(xc, yc, C);
			if (Triangle)
			{
				IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
				Img.draw_point(xc, y, IC); Img.draw_point(x + xend, yc, IC);
			}
		}
	}
	if (Border) { Circlexy(Img, r, x, y); }
}
void Radius(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double rad, bool Triangle, bool Border, uint8_t* C)
{
	uint16_t xc, yc, rn;
	double Sin = sin(TAU - rad), Cos = cos(rad);
	int xend = round(Cos * r);
	uint8_t IC[3];

	for (rn = 0; rn <= r; ++rn)
	{
		yc = y + round(Sin * rn);
		xc = x + round(Cos * rn);
		if (InImg(Img, yc, xc))
		{
			Img.draw_point(xc, yc, C);
			if (Triangle)
			{
				IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
				Img.draw_point(xc, y, IC);
				Img.draw_point(x + xend, yc, IC);
			}
		}
	}	
	if (Border) { Circlexy(Img, r, x, y, C); }
}
void RadiusQuick(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double rad, bool Triangle, bool Border, uint8_t* C)
{
	uint16_t xc, yc;
	double Sin = sin(TAU - rad), Cos = cos(rad);
	int xend = round(Cos * r), yend = round(Sin * r);
	uint8_t IC[3];

	if (InImg(Img, y, x) && InImg(Img, yend, xend))
	{
		//Img.draw_line(x, y, xend, yend, C);
		Img.draw_line(x, y, x + xend, y + yend, C);
		if (Triangle)
		{
			IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
			Img.draw_line(x, y, x + xend, y, IC);
			Img.draw_line(x + xend, y, x + xend, y + yend, IC);
		}
	}
	if (Border) { Circlexy(Img, r, x, y, C); }
}
void RadiusPolygon(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double OffSet, int Divisions, bool Triangle, bool Border)
{ double Div = TAU / Divisions; for (double n = OffSet; n < TAU + OffSet; n += Div) { Radius(Img, r, x, y, n, Triangle, Border); } }
void RadiusPolygon(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double OffSet, int Divisions, uint8_t* C, bool Triangle, bool Border)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		//std::cout << "n / TAU: " << n / (TAU + OffSet) << "!\n";
		Radius(Img, r, x, y, n, Triangle, Border, C);
	}
}
void RadiusPolygonQuick(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double OffSet, int Divisions, uint8_t* C, bool Triangle, bool Border)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		//std::cout << "n / TAU: " << n / (TAU + OffSet) << "!\n";
		RadiusQuick(Img, r, x, y, n, Triangle, Border, C);
	}
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## COM LINES:

// PLOT LINE:
void Line(CImg<uint8_t>& Img, double r, double rad, uint16_t x, uint16_t y, bool Triangle)
{
	uint16_t yc, xc, rn, xend = round(cos(rad) * r), yend = round(sin(rad) * r);
	uint8_t C[3], IC[3];

	for (rn = 0; rn <= r; rn = ++rn)
	{
		yc = y + round(sin(rad) * rn); xc = x + round(cos(rad) * rn);

		if (InImg(Img, yc, xc))
		{
			LinearRGBuc(rn / r, 1, 1, C);
			Img.draw_point(xc, yc, C);
			if (Triangle)
			{
				IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
				Img.draw_point(xc, y, IC); Img.draw_point(x + xend, yc, IC);
			}
		}
	}
}
void Line(CImg<uint8_t>& Img, double r, double rad, uint16_t x, uint16_t y, bool Triangle, uint8_t* C)
{
	uint16_t yc, xc, rn, xend = round(cos(rad) * r), yend = round(sin(rad) * r);
	uint8_t IC[3];

	for (rn = 0; rn <= r; rn = ++rn)
	{
		yc = y + round(sin(rad) * rn); xc = x + round(cos(rad) * rn);

		if (InImg(Img, yc, xc))
		{
			Img.draw_point(xc, yc, C);
			if (Triangle)
			{ 
				IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
				Img.draw_point(xc, y, IC);
				Img.draw_point(x + xend, yc, IC);
			}
		}
	}
}

// BRESENHAM LINE:
void Linexy(CImg<uint8_t>& Img, int x1, int y1, int x2, int y2, uint8_t* C, bool LRGB)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1, dy = y2 - y1;
	dx1 = fabs(dx), dy1 = fabs(dy);
	px = 2 * dy1 - dx1, py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0) { x = x1; y = y1; xe = x2; }
		else { x = x2; y = y2; xe = x1; }
		Img.draw_point(x, y, C);
		for (i = 0; x < xe; i++)
		{
			x += 1;	if (px < 0) { px = px + 2 * dy1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { y = y + 1; } else { y = y - 1; } px = px + 2 * (dy1 - dx1); }
			if (LRGB) { LinearRGBuc(x / (xe - 1.0), 1, 1, C); } // RE-TEST LRGB!!!
			Img.draw_point(x, y, C);
		}
	}
	else
	{
		if (dy >= 0) { x = x1; y = y1; ye = y2; }
		else { x = x2; y = y2; ye = y1; }
		Img.draw_point(x, y, C);
		for (i = 0; y < ye; i++)
		{
			y += 1; if (py <= 0) { py = py + 2 * dx1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { x = x + 1; } else { x = x - 1; }	py = py + 2 * (dx1 - dy1); }
			if (LRGB) { LinearRGBuc(y / (ye - 1.0), 1, 1, C); }
			Img.draw_point(x, y, C);
		}
	}
}


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GEOMETRICOS:

// PLOT POLYGON:
void Polygon(CImg<uint8_t>& Img, int Sides, double r, uint16_t x, uint16_t y, bool Vertex, uint8_t* C)
{
	uint16_t xc, yc, Count = 0;
	if (Sides < 3) { Sides = 3; }
	std::vector<Point<int>> Coord(Sides);
	double Div = TAU / Sides;

	for (double n = 0.0; n <= TAU; n = n + Div)
	{
		xc = x + round(cos(n) * r);
		yc = y + round(sin(n) * r);
		//std::cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / TAU) * 360 << std::endl;
		if (Count < Sides) { Coord[Count].x = xc; Coord[Count].y = yc; }
		++Count;
		if (Vertex)	{ AddVert(Img, xc, yc, 3, C); }
	}
	for (size_t ns = 1; ns < Sides; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, C, false);
			if (ns == Sides - 1) { Linexy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, C, false); }
		}
	}
}
void Polygon(CImg<uint8_t>& Img, int Sides, double r, uint16_t x, uint16_t y, bool Vertex)
{
	uint16_t xc, yc, Count = 0;
	Point3D<uint8_t> RGB = { 255, 0, 127 };
	if (Sides < 3) { Sides = 3; }
	std::vector<Point<int>> Coord(Sides);
	double Div = TAU / Sides;
	uint8_t C[3];

	for (double n = 0.0; n <= TAU; n = n + Div)
	{
		xc = x + round(cos(n) * r);
		yc = y + round(sin(n) * r);
		//std::cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / TAU) * 360 << std::endl;
		if (Count < Sides) { Coord[Count].x = xc; Coord[Count].y = yc; }
		++Count;

		if (Vertex)
		{
			LinearRGBuc(n / TAU, 1, 1, C);
			AddVert(Img, xc, yc, 3, C);
		}
	}
	for (int ns = 1; ns < Sides; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, C, true);
			if (ns == Sides - 1) { Linexy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, C, true); }
		}
	}

}



// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## EUCLIDEAN VECTORS:

// PRINT EUC. VECTOR LINE:
void PrintEucVec(CImg<uint8_t>& Img, Point<double> V, uint16_t x, int16_t y, double Scale, bool Arrow, bool DrawAngle, bool CartLines, bool Text, uint8_t* RGB)
{
	V.x *= Scale; V.y *= Scale;
	int xend = x + round(V.x), yend =Img.height() - (y + round(V.y));
	if (xend < 0) { xend = 0; } if (yend < 0) { yend = 0; }
	if (xend > Img.width()) { xend = Img.width(); } if (yend > Img.height()) { yend = Img.height(); }
	uint8_t C[] = { 127, 127, 127 };
	if (CartLines) { Img.draw_line(0, y, Img.width(), y, C); Img.draw_line(x, 0, x, Img.height(), C); }
	if (Arrow) { Img.draw_arrow(x, y, xend, yend, C); } else { Img.draw_line(x, y, xend, yend, RGB); }
	if (DrawAngle) { Turn(Img, GetMag(V) * 0.2, x, y, 0, GetVecRad(V), RGB); }
	if (Text)
	{
		std::string Txt = "[" + std::to_string(V.x) + ", " + std::to_string(V.y) + "]";
		uint16_t Size = Txt.size() * 6, xtxt = xend - Size * 0.5, ytxt = yend - 10;
		if (xtxt + Txt.size() * 3.75 > Img.width()) { xtxt = xend - Size * 0.5 - Txt.size() * 3.75; } if (xtxt < 0) { xtxt = xend + Size * 0.5; }
		if (ytxt < 0) { ytxt = yend + 10; }
		AddText(Img, xtxt, ytxt, Txt, C);
	}
}

// PRINT EUC. VECTOR, TAIL BY TAIL (NOT WORKING):
void PrintEucVecTail(CImg<uint8_t>& Img, std::vector<Point<double>> Vs, uint16_t x, int16_t y, double Scale, bool Arrow, bool DrawAngle, bool CartLines, bool Text, bool LRGB, uint8_t* RGB)
{
	if (LRGB) { RGB[0] = 255; RGB[1] = 0; RGB[2] = 0; }
	PrintEucVec(Img, Vs[0], x, y, Scale, Arrow, DrawAngle, CartLines, Text, RGB);
	double sumx = Vs[0].x, sumy = Vs[0].y;
	for (int n = 1; n < Vs.size(); ++n)
	{
		std::cout << "sumx: " << sumx << " | sumy: " << sumy << " | V.x: " << Vs[n].x << " | V.y: " << Vs[n].y << std::endl;
		if (LRGB) { LinearRGBuc(1.0 * n / Vs.size(), 1, 1, RGB); }
		int xend = x + sumx, yend = y + sumy;
		if (xend < 0) { xend = 0; } if (Img.height() - yend < 0) { yend = Img.height(); } if (xend > Img.width()) { xend = Img.width(); } if (Img.height() - yend > Img.height()) { yend = 0; }
		PrintEucVec(Img, Vs[n], xend, Img.height() - yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		//PrintEucVec(Img, Vs[n], xend, yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		std::cout << "xend: " << xend << " | Img.height() - yend: " << Img.height() - yend << "\nV.x + xend: " << Vs[n].x + xend
				  << " | Img.height() - (yend + V.y): " << Img.height() - (yend + Vs[n].y) << std::endl;
		sumx += Vs[n].x; sumy += Vs[n].y;
	}
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## VETORES:
// THREE VECTORS TO RGB:
std::vector<Point3D<double>> Vectors2RGB(std::vector<double> VecR, std::vector<double> VecG, std::vector<double> VecB)
{
	uint32_t Size = VecR.size(); std::vector<Point3D<double>> RGBs(Size); Point3D<double> RGB;
	if (VecR.size() == VecG.size() && VecG.size() == VecB.size())
	{
		for (size_t n = 0; n < Size; ++n)
		{ RGB.x = VecR[n] * 255; RGB.y = VecG[n] * 255; RGB.z = VecB[n] * 255; RGBs[n] = RGB; }
	}
	return(RGBs);
}

// ######################################################################

// PLOTAR VETOR (LINE):
// Esses fazem uma linha de um ponto ao outro, o tamanho do segmento � multiplicado por cada c�lula do vetor:
CImg<uint8_t> PrintVectorLine(std::vector<double> V, int SegSize, uint8_t BG, uint8_t* C)
{
	uint32_t Size = V.size();
	double Max, Min; MaxMinVec(V, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil((Max + Min) * SegSize);
	
	CImg<uint8_t> Print(Size * SegSize, MaxMin, 1, 3, BG);

	for (size_t n = 1; n < Size; ++n)
	{ Linexy(Print, (n - 1)  * SegSize, MaxMin - ((V[n - 1] + Absmn) * SegSize), n * SegSize, MaxMin - ((V[n] + Absmn) * SegSize), C, false); }

	return(Print);
}

CImg<uint8_t> PrintVectorPoint(std::vector<double> V, uint8_t BG, uint8_t* C)
{
	uint32_t Size = V.size();
	double Max, Min; MaxMinVec(V, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil(Max + Min); // Pixels
	
	CImg<uint8_t> Print(Size, MaxMin, 1, 3, BG);

	for (size_t n = 0; n < Size; ++n)
	{
		Print.draw_point(n, MaxMin - (V[n] + Absmn), C);
	}

	return(Print);
}

// ######################################################################

// Esse assume que o valor do vetor � a amplitude, ent�o, faz uma linha em cada divis�o de um circulo pelo size() de acordo com a amplitude:
// REDO IT!!!
CImg<uint8_t> PrintVectorPolygn(std::vector<double> V, uint8_t BG, uint8_t* C, bool LRGB, bool Vertex)
{
	uint32_t Sides = V.size();
	double x, y;	
	std::vector<Point<int>> xy(Sides); // Coordinates for image
	double rad, Cos, Sin, Div = TAU / Sides;
	int m = 0; // Counter

	double Max, Min; MaxMinVec(V, Max, Min); // Pixels
	double Abs = 0;
	if (Max < 0) { Abs = abs(Max); Max += Abs; Min += Abs; }
	else if (Min < 0) { Abs = abs(Min); Max += Abs; Min += Abs; }
	int MaxMin = ceil(Max + Min);
	if (Min > 0) { MaxMin -= Min; }	if (Abs > 0) { for (int n = 0; n < Sides; ++n) { V[n] += Abs; } }

	// ####### COORDINATES:
	for (size_t n = 0; n < Sides; ++n)
	{
		rad = n * Div; Cos = (cos(rad) + 1) * 0.5; Sin = (sin(rad) + 1) * 0.5;
		x = Cos * V[n]; y = Sin * V[n];
		if (m < Sides) { xy[m].x = round(x); xy[m].y = MaxMin - round(y); } // Poem na matriz de coordenada
		++m;
	}
	CImg<uint8_t> Ret(MaxMin, MaxMin, 1, 3, BG); // IMAGE

	 // ####### PRINT:
	for (size_t ns = 1; ns < Sides; ++ns)
	{
		Linexy(Ret, xy[ns - 1].x, xy[ns - 1].y, xy[ns].x, xy[ns].y, C, LRGB); // LINES
		if (ns == Sides - 1) { Linexy(Ret, xy[0].x, xy[0].y, xy[ns].x, xy[ns].y, C, LRGB); } // LAST LINE
		if (Vertex) // VERTEXES
		{
			if (LRGB) { double Val = ns / Sides; LinearRGBuc(Val, 1, 1, C); }
			AddVert(Ret, xy[ns].x, xy[ns].y, 3, C);
			if (ns == 1) { uint8_t C[] = { 255, 0, 0 }; AddVert(Ret, xy[0].x, xy[0].y, 3, C); }
		}
	}
	return(Ret);
}

// ######################################################################

// IMPRIME DADOS DE UM VETOR POR COLUNA:
// Soon to be obsolete, changed to the one with the img as input.
// Esse assume que cada pixel de uma imagem corresponde a um dx (PROVAVELMENTE IGUAL O SEM "Norm"):
// f[n] = y = V[n] * (sy / 255) | V[n] is based in '0 to 255':
// Ex.: f(x) = sin(x) * (512 / 255) = sin(x) * 2.007843 -> y;
CImg<uint8_t> PrintVectorPointNorm(std::vector<uint8_t> V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	float ndiv, syd = sy / 255.0;
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (float)n / (Size - 1);
		LinearRGBuc(V[n] / 255.0, 1, 1, C);
		R.draw_point(n, round(sy - V[n] * syd * yrto), C);
	}
	return (R);
}
CImg<uint8_t> PrintVectorPointNorm(std::vector<float> V)
{
	uint32_t Size = V.size(); float Min = 0, Max = 0, Total, ndiv;
	for (size_t n = 0; n < Size; ++n) { if (V[n] > Max) { Max = V[n]; } if (V[n] < Min) { Min = V[n]; } }
	Total = fabs(Max) + fabs(Min);
	CImg<uint8_t> R(Size, ceil(Total), 1, 3, 0);
	uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (float)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);
		R.draw_point(n, round(Total - (V[n] - Min)), C);
	}
	return (R);
}
CImg<uint8_t> PrintVectorPointNorm(std::vector<float> V, uint32_t sy, float yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	float Max, Min, ndiv; uint8_t C[3];
	MaxMinVecAbs(V, Max, Min);

	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (float)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);
		R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C);
	}
	return (R);
}
CImg<uint8_t> PrintVectorPointNorm(std::vector<double> V)
{
	uint32_t Size = V.size();
	double Min = 0, Max = 0, Total, ndiv;
	for (size_t n = 0; n < Size; ++n) { if (V[n] > Max) { Max = V[n]; } if (V[n] < Min) { Min = V[n]; } }
	Total = fabs(Max) + fabs(Min);
	CImg<uint8_t> R(Size, ceil(Total), 1, 3, 0); uint8_t C[3];
	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (double)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);
		R.draw_point(n, round(Total - (V[n] - Min)), C);
	}
	return (R);
}
// f[n] = y = (V[n] * (sy / 2) * yrto) + (sy / 2) | V[n] is normalized to '-1 to 1':
// Ex.: f(x) = sin(x) * 32 * 1 + 32 = sin(x) * 32 + 32 -> y;
CImg<uint8_t> PrintVectorPointNorm(std::vector<double> V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0); uint8_t C[3];
	double Max, Min, ndiv; MaxMinVecAbs(V, Max, Min);
	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (double)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);		
		R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C);
	}
	return (R);
}
CImg<uint8_t> PrintVectorPointNorm(std::vector<double> V, uint32_t sy, uint8_t* C, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0);
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	// OLD (Wolfram): round(sy - (((V[n] / Max) * sy * 0.5 * yrto) + sy * 0.5));
	for (size_t n = 0; n < Size; ++n) { R.draw_point(n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C); }
	return (R);
}

// ######################################################################

CImg<uint8_t> PrintVectorPointNormFill(std::vector<uint8_t> V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0); uint8_t C[3];
	double ndiv, syd = sy / 255.0;
	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (double)n / (Size - 1);
		LinearRGBuc(V[n] / 255.0, 1, 1, C);
		R.draw_line(n, sy, n, round(sy - V[n] * syd * yrto), C);
	}
	return (R);
}
CImg<uint8_t> PrintVectorPointNormFill(std::vector<double> V, uint32_t sy, double yrto = 1)
{
	uint32_t Size = V.size(); CImg<uint8_t> R(Size, sy, 1, 3, 0); uint8_t C[3];
	double Max, Min, ndiv; MaxMinVecAbs(V, Max, Min);
	
	for (size_t n = 0; n < Size; ++n)
	{
		ndiv = (double)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);
		R.draw_line(n, sy * 0.5, n, round(0.5 * sy - ((0.5 * yrto * sy * V[n]) / Max)), C);
	}
	return (R);
}

// ######################################################################

void PrintVectorLineOnImg(CImg<uint8_t>& Img, std::vector<double> V, double yrto = 1)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double Max, Min, sig0, sig1; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	uint8_t C[3];
	uint16_t x0, y0, x1, y1;

	for (size_t n = 1; n < Size; ++n)
	{
		sig0 = (V[n - 1] / Max) * (sy * 0.5) * yrto; // SCALE
		sig1 = (V[n] / Max) * (sy * 0.5) * yrto;
		
		x0 = round((n - 1) * dx); // COORDINATES
		y0 = round(sy - (sig0 + sy * 0.5));
		x1 = round(n * dx);
		y1 = round(sy - (sig1 + sy * 0.5));

		if (y0 > sy) { y0 = sy; } if (y0 < 0) { y0 = 0; } if (y1 > sy) { y1 = sy; } if (y1 < 0) { y1 = 0; }
		if (x0 > sx) { x0 = sx; } if (x0 < 0) { x0 = 0; } if (x1 > sx) { x1 = sx; } if (x1 < 0) { x1 = 0; }
		
		LinearRGBuc(V[n], 1, 1, C);
		Linexy(Img, x0, y0, x1, y1, C, false);
	}
}
void PrintVectorLineOnImg(CImg<uint8_t>& Img, std::vector<double> V, uint8_t* C, double yrto = 1)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double Max, Min, sig0, sig1; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	uint16_t x0, y0, x1, y1;

	for (size_t n = 1; n < Size; ++n)
	{
		sig0 = (V[n - 1] / Max) * (sy * 0.5) * yrto; // SCALE
		sig1 = (V[n] / Max) * (sy * 0.5) * yrto;

		// COORDS:
		x0 = round((n - 1) * dx); y0 = round(sy - (sig0 + sy * 0.5));
		x1 = round(n * dx); y1 = round(sy - (sig1 + sy * 0.5));

		if (y0 > sy) { y0 = sy; } if (y0 < 0) { y0 = 0; } if (y1 > sy) { y1 = sy; } if (y1 < 0) { y1 = 0; }
		if (x0 > sx) { x0 = sx; } if (x0 < 0) { x0 = 0; } if (x1 > sx) { x1 = sx; } if (x1 < 0) { x1 = 0; }

		Linexy(Img, x0, y0, x1, y1, C, false);
	}
}

void PrintVectorPointOnImg(CImg<uint8_t>& Img, std::vector<double> V, double yrto = 1)
{

	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width(), x, y;
	uint8_t C[3];
	double Max, Min, Sig; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;

	for (size_t n = 0; n < Size; ++n)
	{
		Sig = (V[n] / Max) * (sy * 0.5) * yrto;
		LinearRGBuc(V[n], 1, 1, C);
		x = round(n * dx);
		y = round(sy - (Sig + sy * 0.5));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		Img.draw_point(x, y, C);
	}
}
void PrintVectorPointOnImg(CImg<uint8_t>& Img, std::vector<double> V, uint8_t* C, double yrto = 1)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width(), x, y;
	double Max, Min, Sig; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;

	for (size_t n = 0; n < Size; ++n)
	{
		Sig = (V[n] / Max) * (sy * 0.5) * yrto;
		x = round(n * dx);
		y = round(sy - (Sig + sy * 0.5));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		Img.draw_point(x, y, C);
	}
}
void PrintVectorPtOnImgPolar(CImg<uint8_t>& Img, std::vector<double> V, double Ratio)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	double t, Cos, Sin, xr = (sx * 0.5), yr = (sy * 0.5);
	uint8_t C[3]; uint16_t x, y;

	for (size_t n = 0; n < Size; ++n)
	{
		Cos = cos((n / (Size * TAU)) * V[n]); // Trigonometries
		Sin = sin((n / (Size * TAU)) * V[n]);
		
		LinearRGBuc((float)n / Size, 1, 1, C);
		x = round(Cos * xr * Ratio + xr); y = round(sy - (Sin * yr * Ratio + yr));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		Img.draw_point(x, y, C); // Read comment from function above
	}
}
void PrintVectorPtOnImgPolar(CImg<uint8_t>& Img, std::vector<double> V, double Ratio, uint8_t* C)
{
	uint32_t Size = V.size(), sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double dx = sx / (double)Size;
	double t, Cos, Sin, xr = (sx * 0.5), yr = (sy * 0.5);
	uint16_t x, y;

	for (size_t n = 0; n < Size; ++n)
	{
		Cos = cos((n / (Size * TAU)) * V[n]); // Trigonometries
		Sin = sin((n / (Size * TAU)) * V[n]);

		x = round(Cos * xr * Ratio + xr); y = round(sy - (Sin * yr * Ratio + yr));
		if (y > sy) { y = sy; } if (y < 0) { y = 0; }
		if (x > sx) { x = sx; } if (x < 0) { x = 0; }
		Img.draw_point(x, y, C); // Read comment from function above
	}
}

// PLOT LINE BETWEEN POINTS IN A COORDINATE VECTOR:
CImg<uint8_t> PrintPoints(std::vector<Point<int>> Coord, int SegSize, uint8_t BG, bool Abs)
{
	Point<int> max, min;
	MaxMinVecPoint(Coord, max, min, Abs);

	uint32_t sx = (max.x - min.x + 1) * SegSize, sy = (max.y - min.y + 1) * SegSize, Size = Coord.size();
	CImg<uint8_t> Print(sx, sy, 1, 3, BG);
	uint8_t C[] = { 255, 0, 0 };
	for (size_t n = 1; n < Size; ++n)
	{
		LinearRGBuc((float)n / Size, 1, 1, C);
		Linexy(Print, (Coord[n - 1].x - min.x) * SegSize, (Coord[n - 1].y - min.y) * SegSize,
			(Coord[n].x - min.x) * SegSize, (Coord[n].y - min.y) * SegSize, C, false);
	}

	return(Print);
}
CImg<uint8_t> PrintPoints(std::vector<Point<int>> Coord, int SegSize, uint8_t BG, bool Abs, uint8_t* C)
{
	Point<int> max, min;
	MaxMinVecPoint(Coord, max, min, Abs);

	uint32_t sx = (max.x - min.x + 1) * SegSize, sy = (max.y - min.y + 1) * SegSize;
	CImg<uint8_t> Print(sx, sy, 1, 3, BG);

	for (size_t n = 1; n < Coord.size(); ++n)
	{
		Linexy(Print, (Coord[n - 1].x - min.x) * SegSize, (Coord[n - 1].y - min.y) * SegSize,
			(Coord[n].x - min.x) * SegSize, (Coord[n].y - min.y) * SegSize, C, false);
	}

	return(Print);
}

// PLOT LINES IN A VECTOR BY USING THE 'ysxMath.h' OBJECT CALLED 'LinePoint':
CImg<uint8_t> PrintLinePoints(std::vector<LinePoint<int>> Coord, int SegSize, uint8_t BG, bool Abs, uint8_t* C) // Testar para ver se esta tudo certo
{
	LinePoint<int> max, min;
	MaxMinVecLinePoint(Coord, max, min, Abs);

	int sx = 0;
	if (max.P0.x > max.P1.x) { sx = (max.P0.x + 1) * SegSize; }
	else { sx = (max.P0.x + 1) * SegSize; }
	uint32_t sy = 0;
	if (max.P0.y > max.P1.y) { sy = (max.P0.y + 1) * SegSize; }
	else { sy = (max.P0.y + 1) * SegSize; }

	CImg<uint8_t> Print(sx, sy, 1, 3, BG);
	for (size_t n = 0; n < Coord.size(); ++n)
	{
		Linexy(Print, Coord[n].P0.x * SegSize, Coord[n].P0.y * SegSize, Coord[n].P1.x * SegSize, Coord[n].P1.y * SegSize, C, false);
	}
	return(Print);
}

// ######################################################################

// Imprime vetor como barras, tipo grafico estastistico: (LEMBRAR DE FAZER COM QUE SE N�O TIVER VALOR NEGATIVO, USAR METADE DA IMAGEM!)
// Width � 'N * (Width + 2 * Border)'
CImg<uint8_t> PrintVectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	double Max, Min; bool Neg = false;
	MaxMinVec(V, Max, Min); if (Min < 0) { Neg = true; } MaxMinVecAbs(V, Max, Min);
	Max *= Ratio; Min *= Ratio;
	uint32_t Size = V.size(), Mid = 0;

	CImg<uint8_t> VecPrint; //std::vector<CImg<uint8_t>> Prints;
	if (Neg)
	{
		if (xAxis) { VecPrint = CImg<uint8_t>::CImg(Max + Min + 2 + Borderx * 2, (Width + Bordery) * Size, 1, 3, 0); }
		else { VecPrint = CImg<uint8_t>::CImg((Width + Bordery) * Size, Max + Min + 2 + Bordery * 2, 1, 3, 0); }
	}
	else
	{
		if (xAxis) { VecPrint = CImg<uint8_t>::CImg(Max + 2 + Borderx * 2 , (Width + Borderx) * Size, 1, 3, 0); }
		else { VecPrint = CImg<uint8_t>::CImg((Width + Borderx) * Size, Max + 2 + Bordery * 2, 1, 3, 0); }
	}

	if (Neg) { double NewMax, NewMin; MaxMinVec(V, NewMax, NewMin); NewMin *= Ratio; if (xAxis) { Mid = round((NewMin * -1) + Borderx); } else { Mid = round((NewMin * -1) + Bordery); } }
	//else { if (xAxis) { Mid = VecPrint.width(); } else { Mid = VecPrint.height(); } }
	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] != 0)
		{
			if (xAxis)
			{
				if (V[n] >= 0) { VecPrint.draw_image(Mid, n * (Width + Bordery), ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(Mid + (V[n] * Ratio), n * (Width + Bordery), ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); } // + porque � "+ -", o que torna "-"
			}
			else
			{
				if (V[n] >= 0) { VecPrint.draw_image(n * (Width + Borderx), VecPrint.height() - (Mid + (V[n] * Ratio)), ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(n * (Width + Borderx), VecPrint.height() - Mid, ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
			}
		}
	}
	return (VecPrint);
}
CImg<uint8_t> PrintVectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}
CImg<uint8_t> PrintVectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}
CImg<uint8_t> PrintVectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> VecPrint;
	return (VecPrint);
}

// ############## IMAGENS INFO:

// IMAGENS DA MATRIZ DOS VETORES:
// Salva uma imagem 'x' por 'y' usando um vetor com o RGB em double '0 a 1.0':
CImg<uint8_t> PrintVectorImg(std::vector<Point3D<double>> V, uint16_t x, int16_t y, double Rsize = 1.0)
{
	uint32_t Size = V.size(); CImg<uint8_t> Ret(x, y, 1, 3, 0);
	uint8_t R, G, B, C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		R = (V[n].x + 1) * 127.5; G = (V[n].y + 1) * 127.5; B = (V[n].z  + 1) * 127.5;
		C[0] = R; C[1] = G; C[2] = B;
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}
CImg<uint8_t> PrintVectorImg(std::vector<Point3D<double>> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = round(SqrtVec); } else { y = ceil(SqrtVec); }
	CImg<uint8_t> Ret(x, y, 1, 3, 0); uint8_t R, G, B, C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		R = (V[n].x + 1) * 127.5; G = (V[n].y + 1) * 127.5; B = (V[n].z  + 1) * 127.5;
		C[0] = R; C[1] = G; C[2] = B;
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}
CImg<uint8_t> PrintVectorImg(std::vector<Point3D<uint8_t>> V, uint16_t x, int16_t y, double Rsize = 1.0)
{
	uint32_t Size = V.size(); CImg<uint8_t> Ret(x, y, 1, 3, 0);

	for (size_t n = 0; n < Size; ++n)
	{
		uint8_t C[] = { V[n].x, V[n].y, V[n].z };
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}
CImg<uint8_t> PrintVectorImg(std::vector<Point3D<uint8_t>> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = round(SqrtVec); } else { y = ceil(SqrtVec); }
	CImg<uint8_t> Ret(x, y, 1, 3, 0);
	
	for (size_t n = 0; n < Size; ++n)
	{
		uint8_t C[] = { V[n].x, V[n].y, V[n].z };
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Salva uma Imagem com a cor sendo fun��o de 'x' e 'y':
CImg<uint8_t> PrintVectorInfoLRGB(std::vector<double> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n], 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfoLRGB(std::vector<double> V, int x, double Rsize = 1.0)
{
	uint32_t Size = V.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n], 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

CImg<uint8_t> PrintVectorInfoLRGB(std::vector<uint16_t> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n] / 65535.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfoLRGB(std::vector<uint16_t> V, uint16_t x, double Rsize = 1.0)
{
	uint32_t Size = V.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n] / 65535.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}


CImg<uint8_t> PrintVectorInfoLRGB(std::vector<uint8_t> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfoLRGB(std::vector<uint8_t> V, uint16_t x, double Rsize = 1.0)
{
	uint32_t Size = V.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(V[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfoLRGB(std::string str, double Rsize = 1.0)
{
	uint32_t Size = str.size();
	double SqrtVec = sqrt(Size); uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(str[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfoLRGB(std::string str, int x, double Rsize = 1.0)
{
	uint32_t Size = str.size();
	if (x > Size) { x = Size; } if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		LinearRGBuc(str[n] / 255.0, 1.0, 1.0, C);
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}


// Salva uma Imagem com a cor sendo grayscale de '0' a '255':
CImg<uint8_t> PrintVectorInfo(std::vector<double> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = round(SqrtVec), y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Size)); }	
	
	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] > 1) { V[n] = 1; } if (V[n] < 0) { V[n] = 0; }
		C[0] = V[n] * 255; C[1] = V[n] * 255; C[2] = V[n] * 255;
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<uint8_t> PrintVectorInfo(std::vector<double> V, int x, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	if (x > Size) { x = Size; }	if (x < 1) { x = 1; }
	uint16_t y = ceil(Size / (x * 1.0));
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t C[3];

	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] > 1) { V[n] = 1; } if (V[n] < 0) { V[n] = 0; }
		C[0] = V[n] * 255; C[1] = V[n] * 255; C[2] = V[n] * 255;
		R.draw_point(n % x, floor((float)n / x), C);
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

// Salva uma Imagem com a cor sendo fun��o de 'y' dividido em 3 partes, de vermelho a azul:
CImg<uint8_t> PrintVectorInfoTriClr(std::vector<double> V, double Rsize = 1.0)
{
	uint32_t Size = V.size(); double SqrtVec = sqrt(Size);
	uint16_t x = round(SqrtVec), y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Size)); }
	CImg<uint8_t> Ret(x, y, 1, 3, 0); uint8_t C[3];
	
	for (size_t n = 0; n < Size; ++n)
	{
		uint8_t R, G, B;
		if (abs(V[n]) < 0.333333) { R = 255; G = round((abs(V[n]) * 3) * 160); B = round((abs(V[n]) * 3) * 160); }
		else if (abs(V[n]) > 0.666667) { R = round(((abs(V[n]) - 0.666667) * 3) * 160); G = round(((abs(V[n]) - 0.666667) * 3) * 160); B = 255; }
		else { R = round(((abs(V[n]) - 0.33333) * 3) * 160); G = 255; B = round(((abs(V[n]) - 0.33333) * 3) * 160); }
		C[0] = R; C[1] = G; C[2] = B;
		Ret.draw_point(n % x, floor((float)n / x), C);
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Save file bytes as linear RGB (HUE):
// Salva uma Imagem com a cor sendo fun��o de 'x' e 'y', Rsize = Resize:
CImg<uint8_t> PrintFileAsBMP(std::string Path, double Multiplier, double Rsize = 1.0)
{
	std::ifstream I(Path, std::ios::binary); // FILE
	I.seekg(0, std::ios::end); int End = I.tellg(); I.seekg(0, std::ios::beg);
	std::vector<uint8_t> V(End);
	if (I.is_open()) { I.read((char*)&V[0], End); } else { std::cout << "COULDN'T OPEN FILE!\n"; }
	//while (!I.eof()) { char c; I.read(&c, 1); V.push_back(c); std::cout << "CHAR: " << (int)c << " |\n"; } // Add this inside 'if' if you want to get char by char
	I.close();

	uint32_t Size = V.size(); double SqrtVec = sqrt(Size); // IMAGE
	uint16_t x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<uint8_t> R(x, y, 1, 3, 0); uint8_t c[3];

	if (Size > 0)
	{
		for (size_t n = 0; n < Size; ++n)
		{
			LinearRGBuc(((uint8_t)V[n] / 256.0) * Multiplier, 1.0, 1.0, c);
			R.draw_point(n % x, floor((float)n / x), c);
		}
		if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	}
	return(R);
}

// ############################################################################################################################################

// ############## COMPLEX:

/*CImg<uint8_t> PrintVectorComplex(std::vector<complex<double>> V) // POR ENQUANTO � COPIA DO PRINT VECTOR NORM
{
	double Min = 0, Max = 0, Total;
	for (size_t n = 0; n < Size; ++n)
	{
		if (V[n] > Max) { Max = V[n]; }
		if (V[n] < Min) { Min = V[n]; }
	}
	Total = fabs(Max) + fabs(Min);
	CImg<uint8_t> R(Size, ceil(Total), 1, 3, 0);
	for (size_t n = 0; n < Size; ++n)
	{
		double ndiv = (double)n / (Size - 1);
		LinearRGBuc(V[n], 1, 1, C);
		uint8_t C[3];
		R.draw_point(n, round(Total - (V[n] - Min)), C);
	}
	return (R);
}*/

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## FRACTAIS:

// MANDELBROT:
class Mandelbrot
{
public:
	double Zoom = 0.007042; // 1 / 142;
	double Panx = 0, Pany = 0;
	uint32_t Iter = 42;

	// #################################################

	// '0 to 1' SCALED TO MANDEL SET:
	void SetScaledPan(double px, double py)
	{
		if (px < 0) { px = 0; }	if (py < 0) { py = 0; }
		if (px > 1) { px = 1; }	if (py > 1) { py = 1; }
		Panx = 2.47 * px - 2; Pany = 2.24 * py - 1.12;
	}
	void SetSclPanx(double px) { if (px < 0) { px = 0; } if (px > 1) { px = 1; } Panx = 2.47 * px - 2; }
	void SetSclPany(double py) { if (py < 0) { py = 0; } if (py > 1) { py = 1; } Pany = 2.24 * py - 1.12; }

	// #################################################

	// CHECK IF INSIDE SET, RETURN A VALUE BASED ON THE ITERATION:
	double CheckInSet(double x, double y)
	{
		double Real = x, Img = y;
		double tReal, tImg;
		for (uint32_t i = 0; i < Iter; i++)
		{
			tReal = Real * Real - Img * Img + x;
			tImg = 2 * Real * Img + y;
			Real = tReal; Img = tImg;
			if (Real * Img > 5) { return ((double)i / Iter); } // Return a number as a multiplier:
		}
		return (0); // Return zero if in set
	}

	// #################################################
	// #################################################
	// #################################################

	// DRAW FRACTAL:
	void Draw(CImg<uint8_t>& Canvas)
	{
		uint32_t W = Canvas.width(), H = Canvas.height();
		Point<double> SclCanv = { 2.47 / W, 2.24 / H };
		double InSet, Mod; uint8_t c[3];
		for (uint32_t x = 0; x < W; x++)
		{
			for (uint32_t y = 0; y < H; y++)
			{
				Point<double> Scaled = { (x * SclCanv.x) - 2, (y * SclCanv.y) - 1.12 }; // x and y scaled to set size

				InSet = CheckInSet(Scaled.x / Zoom + Panx, Scaled.y / Zoom + Pany);
				if (InSet != 0)
				{
					Mod = InSet * ((double)(x + y) / (W + H));
					LinearRGBuc(Mod, 1, 1, c); // Canvas.fillStyle = 'hsl(' + Mod * 360 * 15 + ', 100%, 50%)';
					Canvas.draw_point(x, y, c); // Draw a colorful pixel
				}
			}
		}
	}

	// #################################################

	// DRAW FRACTAL ANIMATION:
	// Prefer to use vectors of same size!
	// Use 'SaveInstead' if the memory of vector is too high, this is going to return an empty vector,
	// but, instead, it is going to save on the 'Path'.
	std::vector<CImg<uint8_t>> DrawAnimation
	(
		CImg<uint8_t>& Canvas, bool SaveInstead, std::string Path = "",
		std::vector<double>* ColorMod = NULL, std::vector<double>* ZoomMod = NULL,
		std::vector<double>* PanxMod = NULL, std::vector<double>* PanyMod = NULL,
		std::vector<double>* xMod = NULL, std::vector<double>* yMod = NULL
	)
	{
		uint32_t W = Canvas.width(), H = Canvas.height(); Point<double> SclCanv = { 2.47 / W, 2.24 / H };
		CImg<uint8_t> Frame;
		double tZoom = Zoom, tpx = Panx, tpy = Pany;
		double InSet, Mod;		
		uint32_t modsz = 0, magsz = 0, pxsz = 0, pysz = 0, xsz = 0, ysz = 0;
		if (ColorMod != NULL) { modsz = ColorMod->size(); } if (ZoomMod != NULL) { magsz = ZoomMod->size(); }
		if (PanxMod != NULL) { pxsz = PanxMod->size(); } if (PanyMod != NULL) { pysz = PanyMod->size(); }
		if (xMod != NULL) { xsz = xMod->size(); } if (yMod != NULL) { ysz = yMod->size(); }
		uint32_t sx, sy; Point<double> Scaled;
		uint8_t c[3]; std::string s;

		uint32_t Frames = 1;
		{
			uint32_t tF;
			pysz > pxsz ? tF = pysz : tF = pxsz;
			if (modsz > tF) { tF = modsz; }	if (magsz > tF) { tF = magsz; }
			Frames = tF;
		}

		std::vector<CImg<uint8_t>> Film; // <------- THE ANIMATION

		for (uint32_t n = 0; n < Frames; ++n)
		{
			Frame = Canvas;
			if (pxsz > 0 && n < pxsz) { Panx *= PanxMod->at(n); }
			if (pysz > 0 && n < pysz) { Pany *= PanyMod->at(n); }
			if (magsz > 0 && n < magsz) { Zoom *= ZoomMod->at(n); }

			for (uint32_t x = 0; x < W; x++)
			{
				for (uint32_t y = 0; y < H; y++)
				{
					sx = x, sy = y;
					if (xsz > 0 && n < xsz) { sx *= xMod->at(n); }
					if (ysz > 0 && n < ysz) { sy *= yMod->at(n); }

					Scaled = { (x * SclCanv.x) - 2, (y * SclCanv.y) - 1.12 }; // x and y scaled to set size
					InSet = CheckInSet(Scaled.x / Zoom + Panx, Scaled.y / Zoom + Pany);
					if (InSet != 0)
					{
						Mod = InSet * ((double)(sx + sy) / (W + H));
						if (modsz > 0 && n < modsz) { Mod += ColorMod->at(n); }
						LinearRGBuc(Mod, 1, 1, c);
						Frame.draw_point(x, y, c); // Draw a colorful pixel // Maybe sx and sy instead
					}
				}
			}
			if (SaveInstead)
			{
				if (Path.size() > 0)
				{
					s = Path;
					s += " - f[" + std::to_string(n) + "]";
					if (ZoomMod != NULL) { s += " - Zoom[" + std::to_string(ZoomMod->at(n)) + "]"; }
					s += ".bmp";
					Frame.save_bmp(s.data());
				}
			}
			else { Film.push_back(Frame); }
			Zoom = tZoom, Panx = tpx, Pany = tpy;
		}
		return(Film);
	}
};

// #################################################

// PRINT MY FRACTAL:
CImg<uint8_t> PrintBinaryWordCircle(uint16_t Size, int r, int Iter, bool GeoAri, bool RandomColor, bool LRGB, Point3D<uint8_t> RGB)
{
	CImg<uint8_t> MainImg(Size, Size, 1, 3, 0), CircI;
	uint32_t Mid = floor(Size * 0.5);
	double Div, SubDiv, rad, Line, rRatio = 1.0 * r / Size;
	std::vector<std::string> BinWords = BinaryWordsSeq(Iter); std::vector<long> BinArea = BinaryWordSeqArean(Iter);
	Point3D<uint8_t> nRGB = RGB;

	uint32_t Invc, cSize = 0, MidS, cr, s, s2, Count = 0;
	uint32_t Wordset, WordSize;

	for (uint32_t c = Iter; c > 0; --c)
	{
		Invc = (Iter - c) + 1;
		GeoAri ? cSize = (Size / Iter) * c : cSize = Size / Invc;
		MidS = cSize * 0.5; cr = rRatio * cSize; s = BinArea[c - 1]; s2 = pow(2, c);
		CircI = CImg<uint8_t>::CImg(cSize, cSize, 1, 3, 127);
		uint8_t cclr[] = { 255, 0, 0 }; CircI.draw_circle(MidS, MidS, cr, cclr, 1, 1);
		cclr[1] = 255; if (c > 1) { RadiusPolygonQuick(CircI, cr, MidS, MidS, 0, s, cclr, 0, 0); }
		cclr[1] = 0; cclr[2] = 127; RadiusPolygonQuick(CircI, cr, MidS, MidS, 0, s2, cclr, 0, 0);

		Div = TAU / s2;
		rad = 0; std::vector<Point<double>> Scores;
		for (uint32_t n = 0; n < s2; ++n) { Scores.push_back({ rad, AOScore(rad) }); rad += Div; } QuickSortPty(Scores, 0, Scores.size() - 1);
		Wordset = SumntoPowIniEnd(2, 1, c - 1);
		for (uint32_t Word = Wordset; Word < Wordset + s2; ++Word)
		{
			if (RandomColor) { RGB.x = rand() % 256; RGB.y = rand() % 256; RGB.z = rand() % 256; }
			if (LRGB)
			{
				Line = 1.0 * (Word - Wordset) / s2;
				if (BinWords[Word][0] == '0') { LinearRGBuc(0.5 + Line, 1, 1, (uint8_t*)&RGB); }
				else { LinearRGBuc(Line, 1, 1, (uint8_t*)&RGB); }
			}
			WordSize = BinWords[Word].size();
			for (uint32_t Char = 0; Char < WordSize; ++Char)
			{
				if (BinWords[Word][WordSize - 1 - Char] == '0') { nRGB = RGB; nRGB.x = ~nRGB.x; nRGB.y = ~nRGB.y; nRGB.z = ~nRGB.z; }
				SubDiv = Div / WordSize;
				rad = Scores[Word - Wordset].x - (SubDiv * (WordSize - 1)) + (SubDiv * Char);
				rad -= (TAU / s) * 0.5; rad = TAU - rad;
				if (c > 1) { FillArea(CircI, MidS + cos(rad) * cr * 0.85, MidS + sin(rad) * cr * 0.85, (uint8_t*)&nRGB); }
				else { FillArea(CircI, MidS, MidS + sin(rad + TAU * 0.5) * cr * 0.75, (uint8_t*)&nRGB); }
				//AddText(CircI, MidS + cos(rad) * cr * 0.90, MidS + sin(rad) * cr * 0.90, std::to_string(BinWords[Word][Char]) + "\n" + BinWords[Word], 255, 0, 0);
			}
		}
		uint8_t IgnoreColor[] = { 127, 127, 127 };
		MainImg = DrawImageIgnClr(MainImg, CircI, Mid - MidS, Mid - MidS, IgnoreColor);
	}
	return (MainImg);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## CLASSES ##############
// ###################################

// ############## IMPRIME TRIANGULO:
class TriPrint
{
public:
	// CONFIG:
	int Border = 25; // Distancia da margem
	int Width, Heigth; // Medidas da imagem
	int Offy; // Offset para resumir texto dos calculos
	int x[3], y[3]; // Coordenadas de acordo com escalas, bordas, altura e largura
	Point<int> Coord[3], SclCrd[3], Midpoint[3], Circumcenter; // Cordenada dos triangulos, Cordenada com Scale, Coordenada dos midpoints e do Circumcentro
	uint8_t Color[3]; // Cor
	uint8_t ClrBiLine[3], ClrhLine[3], ClrIncirc[3]; // Cores: Line Bisetora, Line da Heigth, Incircle
	double Scale;
	bool LRGB = false;
	double a, b, c, h, base, base0, gamma, beta, alpha, area, perimetro, bisa, bisb, bisc, inradius, IA, IB, IC;

	// OUTPUT:
	CImg<uint8_t> TriOut;

	// ##################### ##################### #####################

	void EmptyImg() { CImg<uint8_t> T; TriOut = T; } // CLEAN
	// Fills the image with a single color, but do not clean height and width like the function above
	void PaintScreen(uint8_t* Color) { CleanImg(TriOut, Color); }
	void ChangeBorder(int New)
	{
		if (New < 0) { New = 0; } Border = New;
		Width = ceil(Scale * (base + base0)) + (Border * 2); Heigth = ceil(h * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se n�o contar a borda
		x[0] = Border + (Scale * Coord[0].x); x[1] = Border + (Scale * Coord[1].x); x[2] = Border + (Scale * Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * Coord[0].y); y[1] = Offy - (Scale * Coord[1].y); y[2] = Offy - (Scale * Coord[2].y); // CORDENADAS Y
	}

	// ##################### CONSTRUTORES #####################
	TriPrint(Triangle TriInput, double ScaleRto, int BorderImg, uint8_t inColor[3])
	{
		Border = BorderImg; base = TriInput.Base; base0 = TriInput.Base0;
		Width = ceil(ScaleRto * (base + base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * ScaleRto) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se n�o contar a borda
		x[0] = Border + (ScaleRto * TriInput.Coord[0].x); x[1] = Border + (ScaleRto * TriInput.Coord[1].x); x[2] = Border + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		CImg<uint8_t> TO(Width, Heigth, 1, 3, 0); TriOut = TO; // Output
		LRGB = false; Scale = ScaleRto; // Graph
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.A; perimetro = TriInput.P;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * Coord[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpts[0]; Midpoint[1] = TriInput.Midpts[1]; Midpoint[2] = TriInput.Midpts[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
		// CORES:
		Color[0] = inColor[0]; Color[1] = inColor[1]; Color[2] = inColor[2];
		ClrBiLine[0] = inColor[0] / 2; ClrBiLine[1] = inColor[1] / 2; ClrBiLine[2] = inColor[2];
		ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
		ClrIncirc[0] = (255 - inColor[0]) / 2; ClrIncirc[1] = (255 - inColor[1]) / 2; ClrIncirc[2] = (255 - inColor[2]) / 2;
	}
	TriPrint(Triangle TriInput, double ScaleRto, int BorderImg)
	{
		Border = BorderImg; base = TriInput.Base; base0 = TriInput.Base0;
		Width = ceil(ScaleRto * (base + base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * ScaleRto) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se n�o contar a borda
		x[0] = Border + (ScaleRto * TriInput.Coord[0].x); x[1] = Border + (ScaleRto * TriInput.Coord[1].x); x[2] = Border + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		CImg<uint8_t> TO(Width, Heigth, 1, 3, 0); TriOut = TO; // Output
		LRGB = true; Scale = ScaleRto; // Graph
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.A; perimetro = TriInput.P;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * SclCrd[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpts[0]; Midpoint[1] = TriInput.Midpts[1]; Midpoint[2] = TriInput.Midpts[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
		// CORES:
		Color[0] = 191; Color[1] = 127; Color[2] = 159;
		ClrBiLine[0] = Color[0] / 2; ClrBiLine[1] = Color[1] / 2; ClrBiLine[2] = Color[2];
		ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
		ClrIncirc[0] = (255 - Color[0]) / 2; ClrIncirc[1] = (255 - Color[1]) / 2; ClrIncirc[2] = (255 - Color[2]) / 2;
	}
	void NewTri(Triangle TriInput)
	{
		Width = ceil(Scale * (TriInput.Base + TriInput.Base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se n�o contar a borda
		x[0] = Border + (Scale * TriInput.Coord[0].x); x[1] = Border + (Scale * TriInput.Coord[1].x); x[2] = Border + (Scale * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * TriInput.Coord[0].y); y[1] = Offy - (Scale * TriInput.Coord[1].y); y[2] = Offy - (Scale * TriInput.Coord[2].y); // CORDENADAS Y
		bool Lb = false, Ab = false, LbAb = false; // Width Bigger, Heigth bigger, Width Or Heigth bigger
		if (Width > TriOut.width()) { Lb = true; } // Do we need to expand the image because the width?
		if (Heigth > TriOut.height()) { Ab = true; } // Do we need to expand the image because the height?
		if (Lb && Ab) { if (Width < Heigth) { LbAb = true; } } // 'LbAb' can only be true if we need to expand BOTH width and height
		if (LbAb || Ab) { TriOut = ExpandImg(TriOut, (Heigth - TriOut.height()) * 0.5, 0); } // Expand image in accord to height
		else if (Lb) { TriOut = ExpandImg(TriOut, (Width - TriOut.height()) * 0.5, 0); }
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.A; perimetro = TriInput.P;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * Coord[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpts[0]; Midpoint[1] = TriInput.Midpts[1]; Midpoint[2] = TriInput.Midpts[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
	}
	// ##################### ##################### #####################

	// IMPRIME PERIMETRO DO TRIANGULO:
	void TriPeriPrint(bool AddVertex, bool Text, bool AddAlt, bool ChangeSidesColor)
	{
		Linexy(TriOut, x[0], y[0], x[1], y[1], Color, LRGB); // a -> "_"
		if (!ChangeSidesColor) { Linexy(TriOut, x[1], y[1], x[2], y[2], Color, LRGB); }
		else
		{
			uint8_t nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			Linexy(TriOut, x[1], y[1], x[2], y[2], nc, LRGB);
		} // c -> "\"
		if (!ChangeSidesColor) { Linexy(TriOut, x[2], y[2], x[0], y[0], Color, LRGB); }
		else
		{
			uint8_t nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			Linexy(TriOut, x[2], y[2], x[0], y[0], nc, LRGB);
		}	// b -> "/"
		if (Text)
		{
			AddText(TriOut, 16, y[0] - 8, "a: " + std::to_string(a), Color); // A
			uint8_t nc[] = { (255 - Color[0]) * 0.75, (255 - Color[1]) * 0.75, (255 - Color[2]) * 0.75 };
			AddText(TriOut, 16, y[0], "Gamma: " + std::to_string(gamma), nc); // GAMMA
			AddText(TriOut, round(Width * 0.75), y[1] - 8, "c: " + std::to_string(c), Color); // C, Algo misteriosamente deu errado
			AddText(TriOut, round(Width * 0.75), y[1], "Beta: " + std::to_string(beta), nc); // BETA
			AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 8), "b: " + std::to_string(b), Color); // B
			AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 16), "Alpha: " + std::to_string(alpha), nc); // ALPHA
			nc[0] = 255; nc[1] = 127; nc[2] = 127;
			AddText(TriOut, round(Width * 0.5), Heigth * 0.5, "Area: " + std::to_string(area), nc); // AREA
			nc[0] = 127; nc[1] = 255; nc[2] = 127;
			AddText(TriOut, round(Width * 0.5), (Heigth * 0.5) + 8, "Peri.: " + std::to_string(perimetro), nc); // PERIMETER
		}
		if (AddVertex)
		{
			uint8_t nc[] = { 255, 0, 0 };
			AddVert(TriOut, x[0], y[0], 3, nc);
			nc[0] = 0; nc[1] = 255;
			AddVert(TriOut, x[1], y[1], 3, nc);
			nc[1] = 0; nc[2] = 255;
			AddVert(TriOut, x[2], y[2], 3, nc);
		}
		if (AddAlt)
		{
			Linexy(TriOut, (SclCrd[2].x) + Border, Offy, (SclCrd[2].x) + Border, Offy - round(Scale * h), ClrhLine, false);
			if (Text)
			{ int px = x[2] - 64; if (px < Width * 0.33) { px += 80; } AddText(TriOut, px, Offy - round(Scale * h * 0.5) - 8, "Height: " + std::to_string(h), ClrhLine); }
			if (AddVert) { uint8_t Color[] = { 127, 127, 127 }; AddVert(TriOut, (SclCrd[2].x) + Border, Offy, 3, Color); }
		}
	}

	// PRINT BISECTOR LINES:
	void TriBisectorPrint(bool Text)
	{
		double Angle = 0;
		if (gamma <= 90) { Angle = Ang2Rad(beta + (alpha * 0.5)); }	else { Angle = Ang2Rad(beta + (alpha * 0.5)); }
		Line(TriOut, bisa * Scale, Angle, x[2], y[2], false, ClrBiLine);
		if (gamma <= 90) { Angle = Ang2Rad(180 + (beta * 0.5)); } else { Angle = Ang2Rad(180 + (beta * 0.5)); }
		Line(TriOut, bisb * Scale, Angle, x[1], y[1], false, ClrBiLine);
		if (gamma <= 90) { Angle = Ang2Rad(360 - (gamma * 0.5)); } else { Angle = Ang2Rad(360 - (gamma * 0.5)); }
		Line(TriOut, bisc * Scale, Angle, x[0], y[0], false, ClrBiLine);
		if (Text)
		{
			AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 24), "BisA: " + std::to_string(bisa), ClrBiLine);
			AddText(TriOut, round(Width * 0.75), y[1] - 16, "BisB: " + std::to_string(bisb), ClrBiLine);
			AddText(TriOut, 16, y[0] - 16, "BisC: " + std::to_string(bisc), ClrBiLine);
		}
	}

	// IMPRIME INCIRCLE:
	void TriIncirclePrint(bool AddVertex)
	{
		int xc = x[1] - (Scale * IB * cos(Ang2Rad(beta) * 0.5)), yc = y[0] - (Scale * IB * sin(Ang2Rad(beta) * 0.5));
		if (AddVertex) { AddVert(TriOut, xc, yc, 3, Color); } // Incenter
		if (LRGB) { Circlexy(TriOut, inradius * Scale, xc, yc); } else { Circlexy(TriOut, inradius * Scale, xc, yc, ClrIncirc); }
	}

	// IMPRIME MIDPOINTS DO TRIANGULO (Algumas vezes fica zuado):
	void TriMidpointPrint()
	{
		AddVert(TriOut, Border + (Scale * Midpoint[0].x), Offy - (Scale * Midpoint[0].y), 3, Color);
		AddVert(TriOut, Border + (Scale * Midpoint[1].x), Offy - (Scale * Midpoint[1].y), 3, Color);
		AddVert(TriOut, Border + (Scale * Midpoint[2].x), Offy - (Scale * Midpoint[2].y), 3, Color);
	}

	// IMPRIME INFORMA��ES TRIGONOMETRICAS DOS ANGULOS:
	void TriTrigPrint()
	{
		double ralpha = Ang2Rad(alpha), rbeta = Ang2Rad(beta), rgamma = Ang2Rad(gamma);
		CImg<uint8_t> StringComp(Width, (8 * 3) + 4, 1, 3, 255);
		std::string S0 = "# sin abc: " + std::to_string(sin(ralpha)) + " | " + std::to_string(sin(rbeta)) + " | " + std::to_string(sin(rgamma));
		std::string S1 = "# cos abc: " + std::to_string(cos(ralpha)) + " | " + std::to_string(cos(rbeta)) + " | " + std::to_string(cos(rgamma));
		std::string S2 = "# tan abc: " + std::to_string(tan(ralpha)) + " | " + std::to_string(tan(rbeta)) + " | " + std::to_string(tan(rgamma));
		uint8_t nc[] = { 0, 0, 0 };
		AddText(StringComp, 4, 1, S0, nc);
		AddText(StringComp, 4, 9, S1, nc);
		AddText(StringComp, 4, 17, S2, nc);
		TriOut = JoinImg(TriOut, StringComp, 1); // N�o vamos modificar altura, pois a variavel de Offset de Heigth (Offy) se mant�m igual a quando a classe foi construida
	}

	// ##################### ##################### #####################

	// IMPRIME TRI�NGULO COM TODAS FUN��ES:
	void TriAllPrint(bool AddVertex, bool AddText, bool ChangeSidesColor)
	{
		//int R = Color[0], G = Color[1], B = Color[1]; // Caso um dia fazer um fun��o que nescessite
		TriPeriPrint(AddVert, AddText, true, ChangeSidesColor);
		TriBisectorPrint(AddText);
		TriIncirclePrint(AddVertex);
		TriMidpointPrint();
		TriTrigPrint(); // (MANTENHA POR ULTIMO)
		// ####### Imprime Lines Medians #######		
		// ####### Circumcentro #######
		uint8_t CC[] = { 127, 127, 127 };
		AddVert(TriOut, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, Color); // Circumcentro
		// ###################################
	}

	/* IMPRIME TRI�NGULO COM SELE��O DE TODAS FUN��ES:
	 * Use a 'bool Swtiches[5]' to turn on/off functions.
	 * Switches[0] = Print Perimeter;
	 * Switches[1] = Print Bisector Lines;
	 * Switches[2] = Print Incircle;
	 * Switches[3] = Print Midpoints;
	 * Switches[4] = Print Trig. functions info;
	*/
	void TriSwitchPrint(bool AddVertex, bool AddText, bool ChangeSidesColor, bool Switches[5]) // Make 'Switches' a single char and use AND as a way to operate
	{
		//int R = Color[0], G = Color[1], B = Color[1];
		if (Switches[0]) { TriPeriPrint(AddVertex, AddText, true, ChangeSidesColor); }
		if (Switches[1]) { TriBisectorPrint(AddVertex); }
		if (Switches[2]) { TriIncirclePrint(AddVertex); }
		if (Switches[3]) { TriMidpointPrint(); }
		if (Switches[4]) { TriTrigPrint(); } // (MANTENHA POR ULTIMO)
		// ####### Imprime Lines Medians #######
		// ####### Circumcentro #######
		uint8_t CC[] = { 255, 0, 255 };
		AddVert(TriOut, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, Color); // Circumcentro
		// ###################################
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_