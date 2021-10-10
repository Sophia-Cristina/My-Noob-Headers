#pragma once

#ifndef YSXCIPLOTTER_H
#define YSXCIPLOTTER_H

using namespace cimg_library;

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	FAZER TODOS POSSIVEIS PLOTTERS ESCREVEREM NUMA IMAGEM DE INPUT;
// !!!!!!!	FAZER TODOS POSSIVEIS PLOTTERS ACEITAREM VECTORS COMO INPUT, E ASSIM ACABAR COM REDUNDANCIAS DE FUNÇÕES, TIPO "POLAR", "CIRCULO" E "TURN";
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* Funções com nome 'SaveVector...' agora são 'PrintVector...';
// !!!!!!!	* 'yrto *= 2' removed from lot of functions;
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## CIRCULARES:

// PLOTAR CIRCULO EM DIFERENTE XY:
void Circlexy(CImg<unsigned char>& Img, double r, int Imgx, int Imgy, unsigned char Color[3])
{
	double y, x;
	int xzero = Imgx, yzero = Imgy;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= TAU; Rad += Step) // MUDAR SE NESCESSARIO
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		
		if (InImg(Img, y + yzero, x + xzero))
		{
			Img.draw_point(x + xzero, y + yzero, Color);
		}
	}
}
void Circlexy(CImg<unsigned char>& Img, double r, int Imgx, int Imgy)
{
	double y, x;
	int xzero = Imgx, yzero = Imgy;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= TAU; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		double Progresso = Rad / TAU;

		if (InImg(Img, y + yzero, x + xzero))
		{
			Point3D<unsigned char> RGB = LinearRGB(Progresso, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(x + xzero, y + yzero, Color);
		}
	}
}

// PLOTAR CIRCULO:
void Circle(CImg<unsigned char>& Img, unsigned char Color[3])
{
	double y, x;
	double r = Img.height(); if (Img.width() <= Img.height()) { r = Img.width(); } r -= 1; r *= 0.5;
	double Step = 1.0 / r;
	int xzero = floor(Img.width() * 0.5), yzero = Img.height() - floor(Img.height() * 0.5);

	for (double Rad = 0; Rad <= TAU; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);

		if (InImg(Img, y, x))
		{
			Img.draw_point(x + xzero, y + yzero, Color);
		}
	}
}
void Circle(CImg<unsigned char>& Img)
{
	double y, x;
	double r = Img.height(); if (Img.width() <= Img.height()) { r = Img.width(); } r -= 2; r *= 0.5;
	double Step = 1.0 / r;
	int xzero = floor(Img.width() * 0.5), yzero = Img.height() - floor(Img.height() * 0.5);

	for (double Rad = 0; Rad <= TAU; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		double Progresso = Rad / TAU;

		if (InImg(Img, y, x))
		{
			Point3D<unsigned char> RGB = LinearRGB(Progresso, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(x + xzero, y + yzero, Color);
		}
	}
}

// ######################################################################

// Metric lines (vertical OR horizontal divisions):
// Make your changes based on the idea that the metric is scaled on the entire image.
void MetricLines(CImg<unsigned char>& I, double a1, double a2, double Div, bool VertHori, bool Text, unsigned char Color[3]) // REFAZER, e adicionar polar
{
	if (a1 > a2) { double T = a1; a1 = a2; a2 = T; }
	double sx = I.width(), sy = I.height(); // size x and y
	double Delta = a2 - a1;
	if (Delta > 0)
	{
		Div = Delta / Div;
		double Ratio = 1;
		double Mid = 1;

		if (VertHori) { Ratio = sx / Delta;	Mid = sy * 0.5; }
		else { Ratio = sy / Delta; Mid = sx * 0.5; }


		int C = 0;
		for (double a = a1; a <= a2; a += Div)
		{
			if (VertHori)
			{
				int x = C * Div * Ratio; ++C;
				for (int y = 0; y < sy; ++y)
				{
					I.draw_point(x, y, Color);
				}
				if (Text)
				{
					Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
					AddText(I, x, Mid, std::to_string(a), Color);
				}
			}
			else
			{
				int y = sy - (C * Div * Ratio); ++C;
				for (int x = 0; x < sx; ++x)
				{
					I.draw_point(x, y, Color);
				}
				if (Text)
				{
					Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
					AddText(I, Mid, y, std::to_string(a), Color);
				}
			}
		}
	}
}

// ######################################################################

// POLAR (arrumar, roubei da classe, colocar x e y), fazer um com raio:
// FAZER UMA VERSÃO COM VECTOR, SEM SER POLIGONAL COMO AQUELE QUE JÁ TEM.
void Polar(CImg<unsigned char>& I, double r, int x, int y, double t1, double t2, double Omega)
{
	if (t1 < 0) { t1 =  TAU + t1; }
	if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	while (t2 > TAU) { t2 -= TAU; } while (t1 > TAU) { t1 -= TAU; }
	double Step = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	// Plotadora
	for (double t = t1; t <= t2; t = t + Step)
	{
		// ### ESCREVA AQUI A SUA FORMULA:
		double Amp = r * MiniForm(t, Omega);
		// #######

		int iy = y + round(Amp * sin(t));
		int ix = x + round(Amp * cos(t));

		// Plota Polar:
		if (InImg(I, y, x))
		{
			double Progresso = ((t - t1) / (t2 - t1));
			Point3D<unsigned char> RGB = LinearRGB(Progresso, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			I.draw_point(ix, iy, Color);
		}
	}
}
void Polar(CImg<unsigned char>& I, double r, double x, double y, double t1, double t2, double Omega, unsigned char Color[3])
{
	if (t1 < 0) { t1 = TAU + t1; }
	if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	while (t2 > TAU) { t2 -= TAU; } while (t1 > TAU) { t1 -= TAU; }
	double Step = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	// Plotadora
	for (double t = t1; t <= t2; t = t + Step)
	{
		// ### ESCREVA AQUI A SUA FORMULA:
		double Amp = r * MiniForm(t, Omega);
		// #######

		y = round(Amp * sin(t));
		x = round(Amp * cos(t));

		// Plota Polar:
		if (InImg(I, y, x))
		{
			I.draw_point(x, y, Color);
		}
	}
}

// TURN:
void Turn(CImg<unsigned char>& Img, double r, int Imgx, int Imgy, double Ini, double Turn, unsigned char Color[3])
{
	double y, x;
	double Rad;
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	double Step = (Turn - Ini) / (TAU * r);

	for (Rad = Ini; Rad <= Turn; Rad += Step)
	{
		y = round(sin(TAU - Rad) * r);
		x = round(cos(Rad) * r);
		//x = round(cos(TAU - Rad) * r); // ???

		if (InImg(Img, y + Imgy, x + Imgx))
		{
			Img.draw_point(x + Imgx, y + Imgy, Color);
		}
	}
}
void Turn(CImg<unsigned char>& Img, double r, int Imgx, int Imgy, double Ini, double Turn)
{
	double y, x;
	double Rad;
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	double Step = (Turn - Ini) / (TAU * r);

	for (Rad = Ini; Rad <= Turn; Rad += Step)
	{
		y = round(sin(TAU - Rad) * r);
		x = round(cos(Rad) * r);

		if (InImg(Img, y + Imgy, x + Imgx))
		{
			double Val = (Rad - Ini) / (Turn - Ini); Point3D<unsigned char> RGB = LinearRGB(Val, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(x + Imgx, y + Imgy, Color);
		}
	}
}

// PLOTAR RAIO:
void Ray(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Border)
{
	int Pixy, Pixx;
	double rn, Sin = sin(TAU - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);

	for (rn = 0; rn <= r; ++rn)
	{
		Pixy = round(Sin * rn);
		Pixx = round(Cos * rn);
		double Prog = rn / r;
		if (InImg(Img, Pixy + y, Pixx + x))
		{
			Point3D<unsigned char> RGB = LinearRGB(Prog, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(Pixx + x, Pixy + y, Color);
			if (Triangle)
			{
				unsigned char InvColor[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z };
				Img.draw_point(Pixx + x, y, InvColor);
				Img.draw_point(x + xend, Pixy + y, InvColor);
			}
		}
	}
	if (Border) { Circlexy(Img, r, x, y); }
}
void Ray(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Border, unsigned char Color[3])
{
	int Pixy, Pixx;
	double rn, Sin = sin(TAU - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);

	for (rn = 0; rn <= r; ++rn)
	{
		Pixy = round(Sin * rn);
		Pixx = round(Cos * rn);
		if (InImg(Img, Pixy + y, Pixx + x))
		{
			Img.draw_point(Pixx + x, Pixy + y, Color);
			if (Triangle)
			{
				unsigned char InvColor[] = { 255 - Color[0], 255 - Color[1], 255 - Color[2] };
				Img.draw_point(Pixx + x, y, InvColor);
				Img.draw_point(x + xend, Pixy + y, InvColor);
			}
		}
	}	
	if (Border) { Circlexy(Img, r, x, y, Color); }
}
void RayQuick(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Border, unsigned char Color[3])
{
	int Pixy, Pixx;
	double Sin = sin(TAU - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);

	if (InImg(Img, y, x) && InImg(Img, yend, xend))
	{
		//Img.draw_line(x, y, xend, yend, Color);
		Img.draw_line(x, y, x + xend, y + yend, Color);
		if (Triangle)
		{
			unsigned char InvColor[] = { 255 - Color[0], 255 - Color[1], 255 - Color[2] };
			Img.draw_line(x, y, x + xend, y, InvColor);
			Img.draw_line(x + xend, y, x + xend, y + yend, InvColor);
		}
	}
	if (Border) { Circlexy(Img, r, x, y, Color); }
}
void RayPolygon(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, bool Triangle, bool Border)
{ double Div = TAU / Divisions; for (double n = OffSet; n < TAU + OffSet; n += Div) { Ray(Img, r, x, y, n, Triangle, Border); } }
void RayPolygon(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, unsigned char Color[3], bool Triangle, bool Border)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		//std::cout << "n / TAU: " << n / (TAU + OffSet) << "!\n";
		Ray(Img, r, x, y, n, Triangle, Border, Color);
	}
}
void RayPolygonQuick(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, unsigned char Color[3], bool Triangle, bool Border)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		//std::cout << "n / TAU: " << n / (TAU + OffSet) << "!\n";
		RayQuick(Img, r, x, y, n, Triangle, Border, Color);
	}
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## COM LINES:

// PLOT LINE:
void Line(CImg<unsigned char>& Img, double r, double Rad, int xpix, int ypix, bool Triangle, unsigned char Color[3], bool LRGB)
{
	double y, x;
	double rn;
	int xend = round(cos(Rad) * r), yend = round(sin(Rad) * r);

	for (rn = 0; rn <= r; rn = ++rn)
	{
		y = round(sin(Rad) * rn);
		x = round(cos(Rad) * rn);
		double Progresso = (rn / r) * 100;

		if (InImg(Img, y + ypix, x + xpix))
		{
			if (LRGB) { Point3D<unsigned char> RGB = LinearRGB(Progresso / 100, 1, 1); Color[0] = RGB.x; Color[1] = RGB.y; Color[2] = RGB.z; }
				Img.draw_point(x + xpix, y + ypix, Color);
				if (Triangle)
				{
					unsigned char InvColor[] = { 255 - Color[0], 255 - Color[1], 255 - Color[2] };
					Img.draw_point(xpix + x, ypix, InvColor);
					Img.draw_point(xpix + xend, y + ypix, InvColor);
				}
		}
	}
}

// BRESENHAM LINE:
void Linexy(CImg<unsigned char>& Img, int x1, int y1, int x2, int y2, unsigned char Color[3], bool LRGB)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	unsigned char First[] = { Color[0], Color[1], Color[2] };
	if (dy1 <= dx1)
	{
		if (dx >= 0) { x = x1; y = y1; xe = x2; }
		else { x = x2; y = y2; xe = x1; }
		Img.draw_point(x, y, First);
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0) { px = px + 2 * dy1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { y = y + 1; } else { y = y - 1; } px = px + 2 * (dy1 - dx1); }
			if (LRGB) { Point3D<unsigned char> RGB = LinearRGB(1.0 * x / (xe - 1), 1, 1); Color[0] = RGB.x; Color[1] = RGB.y; Color[2] = RGB.z; }
			Img.draw_point(x, y, Color);
		}
	}
	else
	{
		if (dy >= 0) { x = x1; y = y1; ye = y2; }
		else { x = x2; y = y2; ye = y1; }
		Img.draw_point(x, y, First);
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0) { py = py + 2 * dx1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { x = x + 1; } else { x = x - 1; }	py = py + 2 * (dx1 - dy1); }
			if (LRGB) { Point3D<unsigned char> RGB = LinearRGB(1.0 * y / (ye - 1), 1, 1); Color[0] = RGB.x; Color[1] = RGB.y; Color[2] = RGB.z; }
			Img.draw_point(x, y, Color);
		}
	}
}


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GEOMETRICOS:

// PLOTAR POLIGONO:
void Polygon(CImg<unsigned char>& Img, int Lados, double r, int Imgx, int Imgy, bool Vertex, unsigned char Color[3])
{
	double x, y;
	if (Lados < 3) { Lados = 3; }
	std::vector<Point<int>> Coord(Lados);
	double Div = TAU / Lados;
	int Count = 0;

	for (double n = 0.0; n <= TAU; n = n + Div)
	{
		x = round(cos(n) * r);
		y = round(sin(n) * r);
		//std::cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / TAU) * 360 << std::endl;
		if (Count < Lados) { Coord[Count].x = x + Imgx; Coord[Count].y = y + Imgy; }
		double Progresso = (n / TAU) * 100;
		++Count;
		if (Vertex)
		{
			AddVert(Img, x + Imgx, y + Imgy, 3, Color);
		}
	}
	for (int ns = 1; ns < Lados; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, Color, false);
			if (ns == Lados - 1) { Linexy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, Color, false); }
		}
	}
}
void Polygon(CImg<unsigned char>& Img, int Lados, double r, int Imgx, int Imgy, bool Vertex)
{
	double x, y;
	Point3D<unsigned char> RGB = { 255, 0, 127 };
	if (Lados < 3) { Lados = 3; }
	std::vector<Point<int>> Coord(Lados);
	double Div = TAU / Lados;
	int Count = 0;

	for (double n = 0.0; n <= TAU; n = n + Div)
	{
		x = round(cos(n) * r);
		y = round(sin(n) * r);
		//std::cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / TAU) * 360 << std::endl;
		if (Count < Lados) { Coord[Count].x = x + Imgx; Coord[Count].y = y + Imgy; }
		double Progresso = n / TAU;
		++Count;
		if (Vertex)
		{
			RGB = LinearRGB(Progresso, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			AddVert(Img, x + Imgx, y + Imgy, 3, Color);
		}
	}
	unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
	for (int ns = 1; ns < Lados; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, Color, true);
			if (ns == Lados - 1) { Linexy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, Color, true); }
		}
	}

}



// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## EUCLIDEAN VETORES:

// Print vector line in a cartesian plane:
void PrintEucVec(CImg<unsigned char>& Img, Point<double> Vector, int x, int y, double Scale, bool Arrow, bool DrawAngle, bool CartesianLines, bool Text, Point3D<unsigned char> RGB)
{
	Vector.x *= Scale; Vector.y *= Scale;
	int xend = x + round(Vector.x), yend =Img.height() - (y + round(Vector.y));
	if (xend < 0) { xend = 0; } if (yend < 0) { yend = 0; }
	if (xend > Img.width()) { xend = Img.width(); } if (yend > Img.height()) { yend = Img.height(); }
	unsigned char Color[] = { 127, 127, 127 };
	if (CartesianLines) { Img.draw_line(0, y, Img.width(), y, Color); Img.draw_line(x, 0, x, Img.height(), Color); }
	Color[0] = RGB.x; Color[1] = RGB.y; Color[2] = RGB.z;
	if (Arrow) { Img.draw_arrow(x, y, xend, yend, Color); } else { Img.draw_line(x, y, xend, yend, Color); }
	if (DrawAngle) { Turn(Img, GetMag(Vector) * 0.2, x, y, 0, GetVecRad(Vector), Color); }
	if (Text)
	{
		std::string Txt = "[" + std::to_string(Vector.x) + ", " + std::to_string(Vector.y) + "]";
		int Size = Txt.size() * 6;
		int xtxt = xend - Size * 0.5, ytxt = yend - 10;
		if (xtxt + Txt.size() * 3.75 > Img.width()) { xtxt = xend - Size * 0.5 - Txt.size() * 3.75; } if (xtxt < 0) { xtxt = xend + Size * 0.5; }
		if (ytxt < 0) { ytxt = yend + 10; }
		AddText(Img, xtxt, ytxt, Txt, Color);
	}
}

// Print vector line joining tail to tail:
void PrintEucVecTail(CImg<unsigned char>& Img, std::vector<Point<double>> Vectors, int x, int y, double Scale, bool Arrow, bool DrawAngle, bool CartesianLines, bool Text, bool LRGB, Point3D<unsigned char> RGB)
{
	if (LRGB) { RGB = { 255, 0, 0 }; }
	PrintEucVec(Img, Vectors[0], x, y, Scale, Arrow, DrawAngle, CartesianLines, Text, RGB);
	double sumx = Vectors[0].x, sumy = Vectors[0].y;
	for (int n = 1; n < Vectors.size(); ++n)
	{
		std::cout << "sumx: " << sumx << " | sumy: " << sumy << " | V.x: " << Vectors[n].x << " | V.y: " << Vectors[n].y << std::endl;
		if (LRGB) { RGB = LinearRGB(1.0 * n / Vectors.size(), 1, 1); }
		int xend = x + sumx, yend = y + sumy;
		if (xend < 0) { xend = 0; } if (Img.height() - yend < 0) { yend = Img.height(); } if (xend > Img.width()) { xend = Img.width(); } if (Img.height() - yend > Img.height()) { yend = 0; }
		PrintEucVec(Img, Vectors[n], xend, Img.height() - yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		//PrintEucVec(Img, Vectors[n], xend, yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		std::cout << "xend: " << xend << " | Img.height() - yend: " << Img.height() - yend << "\nV.x + xend: " << Vectors[n].x + xend
				  << " | Img.height() - (yend + V.y): " << Img.height() - (yend + Vectors[n].y) << std::endl;
		sumx += Vectors[n].x; sumy += Vectors[n].y;
	}
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## VETORES:
// THREE VECTORS TO RGB:
std::vector<Point3D<double>> Vectors2RGB(std::vector<double> VecR, std::vector<double> VecG, std::vector<double> VecB)
{
	std::vector<Point3D<double>> RGBs;
	if (VecR.size() == VecG.size() && VecG.size() == VecB.size())
	{
		int Size = VecR.size(); for (int n = 0; n < Size; ++n) { Point3D<double> RGB; RGB.x = VecR[n] * 255; RGB.y = VecG[n] * 255; RGB.z = VecB[n] * 255; RGBs.push_back(RGB); }
	}
	return(RGBs);
}

// ######################################################################

// PLOTAR VETOR (LINE):
// Esses fazem uma linha de um ponto ao outro, o tamanho do segmento é multiplicado por cada célula do vetor:
CImg<unsigned char> PrintVectorLine(std::vector<double> Vec, int SegmentSize, int BackGround, unsigned char Color[3])
{
	double Max, Min;
	MaxMinVec(Vec, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil((Max + Min) * SegmentSize);
	
	CImg<unsigned char> Print(Vec.size() * SegmentSize, MaxMin, 1, 3, BackGround);

	for (int n = 1; n < Vec.size(); ++n)
	{ Linexy(Print, (n - 1)  * SegmentSize, MaxMin - ((Vec[n - 1] + Absmn) * SegmentSize), n * SegmentSize, MaxMin - ((Vec[n] + Absmn) * SegmentSize), Color, false); }

	return(Print);
}

CImg<unsigned char> PrintVectorPoint(std::vector<double> Vec, int BackGround, unsigned char Color[3])
{
	double Max, Min;
	MaxMinVec(Vec, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil(Max + Min); // Pixels
	
	CImg<unsigned char> Print(Vec.size(), MaxMin, 1, 3, BackGround);

	for (int n = 0; n < Vec.size(); ++n)
	{
		Print.draw_point(n, MaxMin - (Vec[n] + Absmn), Color);
	}

	return(Print);
}

// ######################################################################

// Esse assume que o valor do vetor é a amplitude, então, faz uma linha em cada divisão de um circulo pelo size() de acordo com a amplitude:
CImg<unsigned char> PrintVectorPolygn(std::vector<double> Vec, int BackGround, unsigned char Color[3], bool LRGB, bool Vertex)
{
	double x, y;
	int Lados = Vec.size();
	std::vector<Point<int>> xy(Lados); // Coordinates for image
	double Div = TAU / Lados;
	int m = 0; // Counter

	double Max, Min; // Pixels
	MaxMinVec(Vec, Max, Min);
	double Abs = 0;
	if (Max < 0) { Abs = abs(Max); Max += Abs; Min += Abs; }
	else if (Min < 0) { Abs = abs(Min); Max += Abs; Min += Abs; }
	int MaxMin = ceil(Max + Min);
	if (Min > 0) { MaxMin -= Min; }
	if (Abs > 0) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Abs; } } // #######

	for (int n = 0; n < Lados; ++n) // ####### COORDINATES:
	{
		double Rad = n * Div, Cos = (cos(Rad) + 1) * 0.5, Sin = (sin(Rad) + 1) * 0.5;
		x = Cos * Vec[n];
		y = Sin * Vec[n];
		if (m < Lados) { xy[m].x = round(x); xy[m].y = MaxMin - round(y); } // Poem na matriz de coordenada
		++m;
	}
	CImg<unsigned char> Ret(MaxMin, MaxMin, 1, 3, BackGround); // IMAGEM
	for (int ns = 1; ns < Lados; ++ns) // ####### PRINT
	{
		Linexy(Ret, xy[ns - 1].x, xy[ns - 1].y, xy[ns].x, xy[ns].y, Color, LRGB); // LINES
		if (ns == Lados - 1) { Linexy(Ret, xy[0].x, xy[0].y, xy[ns].x, xy[ns].y, Color, LRGB); } // LAST LINE
		if (Vertex) // VERTEXES
		{
			if (LRGB) { double Val = ns / Lados; Point3D<unsigned char> RGB = LinearRGB(Val, 1, 1); Color[0] = RGB.x; Color[1] = RGB.y; Color[2] = RGB.z; }
			AddVert(Ret, xy[ns].x, xy[ns].y, 3, Color);
			if (ns == 1) { unsigned char Color[] = { 255, 0, 0 }; AddVert(Ret, xy[0].x, xy[0].y, 3, Color); }
		}
	}
	return(Ret);
}

// ######################################################################

// IMPRIME DADOS DE UM VETOR POR COLUNA:
// Esse assume que cada pixel de uma imagem corresponde a um dx (PROVAVELMENTE IGUAL O SEM "Norm"):
// f[n] = y = V[n] * (sy / 255) | V[n] is based in '0 to 255':
// Ex.: f(x) = sin(x) * (512 / 255) = sin(x) * 2.007843 -> y;
CImg<unsigned char> PrintVectorPointNorm(std::vector<unsigned char> V, int sy, double yrto)
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	float syd = sy / 255.0;
	for (int n = 0; n < V.size(); ++n)
	{
		float ndiv = (float)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n] / 255.0, 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(sy - V[n] * syd * yrto), Color);
	}
	return (R);
}
CImg<unsigned char> PrintVectorPointNorm(std::vector<float> V)
{
	float Min = 0, Max = 0, Total;
	for (int n = 0; n < V.size(); ++n)
	{
		if (V[n] > Max) { Max = V[n]; }
		if (V[n] < Min) { Min = V[n]; }
	}
	Total = fabs(Max) + fabs(Min);
	CImg<unsigned char> R(V.size(), ceil(Total), 1, 3, 0);
	for (int n = 0; n < V.size(); ++n)
	{
		float ndiv = (float)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(Total - (V[n] - Min)), Color);
	}
	return (R);
}
CImg<unsigned char> PrintVectorPointNorm(std::vector<float> V, int sy, float yrto)
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	float Max, Min; MaxMinVecAbs(V, Max, Min);
	for (int n = 0; n < V.size(); ++n)
	{
		float ndiv = (float)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(sy - (((V[n] / Max) * sy * 0.5 * yrto) + sy * 0.5)), Color);
	}
	return (R);
}
CImg<unsigned char> PrintVectorPointNorm(std::vector<double> V)
{
	double Min = 0, Max = 0, Total;
	for (int n = 0; n < V.size(); ++n)
	{
		if (V[n] > Max) { Max = V[n]; }
		if (V[n] < Min) { Min = V[n]; }
	}
	Total = fabs(Max) + fabs(Min);
	CImg<unsigned char> R(V.size(), ceil(Total), 1, 3, 0);
	for (int n = 0; n < V.size(); ++n)
	{
		double ndiv = (double)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(Total - (V[n] - Min)), Color);
	}
	return (R);
}
// f[n] = y = (V[n] * (sy / 2) * yrto) + (sy / 2) | V[n] is normalized to '-1 to 1':
// Ex.: f(x) = sin(x) * 32 * 1 + 32 = sin(x) * 32 + 32 -> y;
CImg<unsigned char> PrintVectorPointNorm(std::vector<double> V, int sy, double yrto)
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	for (int n = 0; n < V.size(); ++n)
	{
		double ndiv = (double)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(sy - (((V[n] / Max) * sy * 0.5 * yrto) + sy * 0.5)), Color);
	}
	return (R);
}
CImg<unsigned char> PrintVectorPointNorm(std::vector<double> V, int sy, double yrto, unsigned char Color[3])
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	for (int n = 0; n < V.size(); ++n)
	{
		R.draw_point(n, round(sy - (((V[n] / Max) * sy * 0.5 * yrto) + sy * 0.5)), Color);
	}
	return (R);
}

// ######################################################################

CImg<unsigned char> PrintVectorPointNormFill(std::vector<unsigned char> V, int sy, double yrto)
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	double syd = sy / 255.0;
	for (int n = 0; n < V.size(); ++n)
	{
		double ndiv = (double)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n] / 255.0, 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_line(n, sy, n, round(sy - V[n] * syd * yrto), Color);
	}
	return (R);
}
CImg<unsigned char> PrintVectorPointNormFill(std::vector<double> V, int sy, double yrto)
{
	CImg<unsigned char> R(V.size(), sy, 1, 3, 0);
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	for (int n = 0; n < V.size(); ++n)
	{
		double ndiv = (double)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_line(n, sy * 0.5, n, round(sy - (((V[n] / Max) * sy * 0.5 * yrto) + sy * 0.5)), Color);
	}
	return (R);
}

// ######################################################################

void PrintVectorLineOnImg(CImg<unsigned char>& Img, std::vector<double> V, double yrto)
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double ReciRatio = 1.0 / ((double)V.size() / sx);

	for (int n = 1; n < V.size(); ++n)
	{
		double sig0 = (V[n - 1] / Max) * (sy * 0.5) * yrto; // SCALE
		double sig1 = (V[n] / Max) * (sy * 0.5) * yrto;
		
		int xi0 = round((n - 1) * ReciRatio); // COORDINATES
		int yi0 = round(sy - (sig0 + sy * 0.5));
		int xi1 = round(n * ReciRatio);
		int yi1 = round(sy - (sig1 + sy * 0.5));

		if (yi0 > sy) { yi0 = sy; } if (yi0 < 0) { yi0 = 0; } if (yi1 > sy) { yi1 = sy; } if (yi1 < 0) { yi1 = 0; }
		if (xi0 > sx) { xi0 = sx; } if (xi0 < 0) { xi0 = 0; } if (xi1 > sx) { xi1 = sx; } if (xi1 < 0) { xi1 = 0; }
		
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		Linexy(Img, xi0, yi0, xi1, yi1, Color, false);
	}
}
void PrintVectorLineOnImg(CImg<unsigned char>& Img, std::vector<double> V, double yrto, unsigned char Color[3])
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double ReciRatio = 1.0 / ((double)V.size() / sx);

	for (int n = 1; n < V.size(); ++n)
	{
		double sig0 = (V[n - 1] / Max) * (sy * 0.5) * yrto; // SCALE
		double sig1 = (V[n] / Max) * (sy * 0.5) * yrto;
		double y0 = (sig0 + sy * 0.5);
		double y1 = (sig1 + sy * 0.5);

		int xi0 = round((n - 1) * ReciRatio); // COORDINATES
		int yi0 = round(sy - y0);
		int xi1 = round(n * ReciRatio);
		int yi1 = round(sy - y1);

		if (yi0 > sy) { yi0 = sy; } if (yi0 < 0) { yi0 = 0; } if (yi1 > sy) { yi1 = sy; } if (yi1 < 0) { yi1 = 0; }
		if (xi0 > sx) { xi0 = sx; } if (xi0 < 0) { xi0 = 0; } if (xi1 > sx) { xi1 = sx; } if (xi1 < 0) { xi1 = 0; }

		Linexy(Img, xi0, yi0, xi1, yi1, Color, false);
	}
}

void PrintVectorPointOnImg(CImg<unsigned char>& Img, std::vector<double> V, double yrto)
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	//double ReciRatio = 1.0 / ((double)V.size() / sx);
	double ReciRatio = 1.0 / ((double)V.size() / sx);
	for (int n = 0; n < V.size(); ++n)
	{
		double sig = (V[n] / Max) * (sy * 0.5) * yrto;
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		int xi = round(n * ReciRatio); // 'x' coordinate from 'i'mage
		int yi = round(sy - (sig + sy * 0.5));
		if (yi > sy) { yi = sy; } if (yi < 0) { yi = 0; }
		if (xi > sx) { xi = sx; } if (xi < 0) { xi = 0; }
		Img.draw_point(xi, yi, Color); // Read comment from function above
	}
}
void PrintVectorPointOnImg(CImg<unsigned char>& Img, std::vector<double> V, double yrto, unsigned char Color[3])
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	//double ReciRatio = 1.0 / ((double)V.size() / sx);
	double ReciRatio = 1.0 / ((double)V.size() / sx);
	for (int n = 0; n < V.size(); ++n)
	{
		double sig = (V[n] / Max) * (sy * 0.5) * yrto;
		int xi = round(n * ReciRatio); // 'x' coordinate from 'i'mage
		int yi = round(sy - (sig + sy * 0.5));
		if (yi > sy) { yi = sy; } if (yi < 0) { yi = 0; }
		if (xi > sx) { xi = sx; } if (xi < 0) { xi = 0; }
		Img.draw_point(xi, yi, Color); // Read comment from function above
	}
}
void PrintVectorPtOnImgPolar(CImg<unsigned char>& Img, std::vector<double> V, double Ratio)
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double ReciRatio = 1.0 / ((double)V.size() / sx);
	for (int n = 0; n < V.size(); ++n)
	{
		double Theta(n / (V.size() * TAU)); double Cos = cos(Theta * V[n]), Sin = sin(Theta * V[n]); // Trigonometries
		double xr = (sx * 0.5), yr = (sy * 0.5); // Radius and Mid screen
		Point3D<unsigned char> RGB = LinearRGB((float)n / V.size(), 1, 1); unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		int xi = round(Cos * xr * Ratio + xr); // 'x' coordinate from 'i'mage
		int yi = round(sy - (Sin * yr * Ratio + yr));
		if (yi > sy) { yi = sy; } if (yi < 0) { yi = 0; }
		if (xi > sx) { xi = sx; } if (xi < 0) { xi = 0; }
		Img.draw_point(xi, yi, Color); // Read comment from function above
	}
}
void PrintVectorPtOnImgPolar(CImg<unsigned char>& Img, std::vector<double> V, double Ratio, unsigned char Color[3])
{
	int sy = Img.height(), sx = Img.width();
	double Max, Min; MaxMinVecAbs(V, Max, Min);
	double ReciRatio = 1.0 / ((double)V.size() / sx);
	for (int n = 0; n < V.size(); ++n)
	{
		double Theta(n / (V.size() * TAU)); double Cos = cos(Theta * V[n]), Sin = sin(Theta * V[n]); // Trigonometries
		double xr = (sx * 0.5), yr = (sy * 0.5); // Radius and Mid screen
		int xi = round(Cos * xr * Ratio + xr); // 'x' coordinate from 'i'mage
		int yi = round(sy - (Sin * yr * Ratio + yr));
		if (yi > sy) { yi = sy; } if (yi < 0) { yi = 0; }
		if (xi > sx) { xi = sx; } if (xi < 0) { xi = 0; }
		Img.draw_point(xi, yi, Color); // Read comment from function above
	}
}

// ######################################################################

// Imprime vetor como barras, tipo grafico estastistico: (LEMBRAR DE FAZER COM QUE SE NÃO TIVER VALOR NEGATIVO, USAR METADE DA IMAGEM!)
// Width é 'N * (Width + 2 * Border)'
CImg<unsigned char> PrintVectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	double Max, Min; bool Neg = false; MaxMinVec(V, Max, Min); if (Min < 0) { Neg = true; } MaxMinVecAbs(V, Max, Min); Max *= Ratio; Min *= Ratio;
	CImg<unsigned char> VecPrint; //std::vector<CImg<unsigned char>> Prints;
	if (Neg)
	{
		if (xAxis) { CImg<unsigned char> I(Max + Min + 2 + Borderx * 2, (Width + Bordery) * V.size(), 1, 3, 0); VecPrint = I; }
		else { CImg<unsigned char> I((Width + Bordery) * V.size(), Max + Min + 2 + Bordery * 2, 1, 3, 0); VecPrint = I; }
	}
	else
	{
		if (xAxis) { CImg<unsigned char> I(Max + 2 + Borderx * 2 , (Width + Borderx) * V.size(), 1, 3, 0); VecPrint = I; }
		else { CImg<unsigned char> I((Width + Borderx) * V.size(), Max + 2 + Bordery * 2, 1, 3, 0); VecPrint = I; }
	}
	int Mid = 0;
	if (Neg) { double NewMax, NewMin; MaxMinVec(V, NewMax, NewMin); NewMin *= Ratio; if (xAxis) { Mid = round((NewMin * -1) + Borderx); } else { Mid = round((NewMin * -1) + Bordery); } }
	//else { if (xAxis) { Mid = VecPrint.width(); } else { Mid = VecPrint.height(); } }
	for (int n = 0; n < V.size(); ++n)
	{
		if (V[n] != 0)
		{
			if (xAxis)
			{
				if (V[n] >= 0) { VecPrint.draw_image(Mid, n * (Width + Bordery), ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(Mid + (V[n] * Ratio), n * (Width + Bordery), ValueBarAbs(Width, V[n], Ratio, Borderx, Bordery, xAxis)); } // + porque é "+ -", o que torna "-"
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
CImg<unsigned char> PrintVectorBars(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}
CImg<unsigned char> PrintVectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}
CImg<unsigned char> PrintVectorBarsAbs(std::vector<double> V, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}

// ############## IMAGENS INFO:

// IMAGENS DA MATRIZ DOS VETORES:
// Salva uma imagem 'x' por 'y' usando um vetor com o RGB em double '0 a 1.0':
CImg<unsigned char> PrintVectorImg(std::vector<Point3D<double>> V, int x, int y, double Rsize)
{
	CImg<unsigned char> Ret(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		int R = V[n].x * 255; if (R > 255) { R = 255; } if (R < 0) { R = 0; }
		int G = V[n].y * 255; if (G > 255) { G = 255; } if (G < 0) { G = 0; }
		int B = V[n].z * 255; if (B > 255) { B = 255; } if (B < 0) { B = 0; }
		unsigned char Color[] = { R, G, B };
		Ret.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}
CImg<unsigned char> PrintVectorImg(std::vector<Point3D<double>> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / x == 1) { y = round(SqrtVec); } else { y = ceil(SqrtVec); }
	CImg<unsigned char> Ret(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		int R = V[n].x * 255;
		int G = V[n].y * 255;
		int B = V[n].z * 255;
		unsigned char Color[] = { R, G, B };
		Ret.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Salva uma Imagem com a cor sendo função de 'x' e 'y':
CImg<unsigned char> PrintVectorInfoLRGB(std::vector<double> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<unsigned char> PrintVectorInfoLRGB(std::vector<double> V, int x, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	if (x > V.size()) { x = V.size(); } if (x < 1) { x = 1; }
	int y = ceil(V.size() / (x * 1.0));
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

CImg<unsigned char> PrintVectorInfoLRGB(std::vector<unsigned short> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec), y;
	if (SqrtVec / x == 1) { y = x; }
	else { y = ceil(SqrtVec); }
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(V[n] / 65535.0, 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}


CImg<unsigned char> PrintVectorInfoLRGB(std::vector<char> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(V[n] / 255.0, 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<unsigned char> PrintVectorInfoLRGB(std::vector<char> V, int x, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	if (x > V.size()) { x = V.size(); } if (x < 1) { x = 1; }
	int y = ceil(V.size() / (x * 1.0));
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(V[n] / 255.0, 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<unsigned char> PrintVectorInfoLRGB(std::string String, double Rsize)
{
	double SqrtVec = sqrt(String.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / x == 1) { y = x; }
	else { y = ceil(SqrtVec); }
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < String.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(String[n] / 255.0, 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<unsigned char> PrintVectorInfoLRGB(std::string String, int x, double Rsize)
{
	double SqrtVec = sqrt(String.size());
	if (x > String.size()) { x = String.size(); } if (x < 1) { x = 1; }
	int y = ceil(String.size() / (x * 1.0));
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < String.size(); ++n)
	{
		Point3D<unsigned char> RGB = LinearRGB(String[n] / 255.0, 1.0, 1.0);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

// Salva uma Imagem com a cor sendo grayscale de '0' a '127':
CImg<unsigned char> PrintVectorInfo(std::vector<double> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(V.size())); }
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB; RGB.x = V[n] * 255; RGB.y = V[n] * 255; RGB.z = V[n] * 255;
		if (RGB.x > 255) { RGB.x = 255; } if (RGB.y > 255) { RGB.y = 255; } if (RGB.z > 255) { RGB.z = 255; }
		if (RGB.x < 0) { RGB.x = 0; } if (RGB.y < 0) { RGB.y = 0; } if (RGB.z < 0) { RGB.z = 0; }
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}
CImg<unsigned char> PrintVectorInfo(std::vector<double> V, int x, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	if (x > V.size()) { x = V.size(); }
	if (x < 1) { x = 1; }
	int y = ceil(V.size() / (x * 1.0));
	CImg<unsigned char> R(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		Point3D<unsigned char> RGB; RGB.x = V[n] * 255; RGB.y = V[n] * 255; RGB.z = V[n] * 255;
		if (RGB.x > 255) { RGB.x = 255; } if (RGB.y > 255) { RGB.y = 255; } if (RGB.z > 255) { RGB.z = 255; }
		if (RGB.x < 0) { RGB.x = 0; } if (RGB.y < 0) { RGB.y = 0; } if (RGB.z < 0) { RGB.z = 0; }
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n % x, C, Color);
		if (n % x == x - 1) { ++C; }
	}

	if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	return(R);
}

// Salva uma Imagem com a cor sendo função de 'y' dividido em 3 partes, de vermelho a azul:
CImg<unsigned char> PrintVectorInfoTriClr(std::vector<double> V, double Rsize)
{
	double SqrtVec = sqrt(V.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(V.size())); }
	CImg<unsigned char> Ret(x, y, 1, 3, 0);
	int C = 0;
	for (int n = 0; n < V.size(); ++n)
	{
		int R, G, B;
		if (abs(V[n]) < 0.333333333) { R = 255; G = round((abs(V[n]) * 3) * 160); B = round((abs(V[n]) * 3) * 160); }
		else if (abs(V[n]) > 0.666666667) { R = round(((abs(V[n]) - 0.666666667) * 3) * 160); G = round(((abs(V[n]) - 0.666666667) * 3) * 160); B = 255; }
		else { R = round(((abs(V[n]) - 0.33333333) * 3) * 160); G = 255; B = round(((abs(V[n]) - 0.33333333) * 3) * 160); }
		unsigned char Color[] = { R, G, B };
		Ret.draw_point(n % x, C, Color);
		if (n % x == x - 1) { ++C; }
	}
	if (Rsize != 1.0) { Resize(Ret, round(x * Rsize), round(y * Rsize), 6); }
	return(Ret);
}

// Save file bytes as linear RGB (HUE):
// Salva uma Imagem com a cor sendo função de 'x' e 'y', Rsize = Resize:
CImg<unsigned char> PrintFileAsBMP(std::string Path, double Multiplier, double Rsize)
{
	std::ifstream I(Path, std::ios::binary); // FILE
	I.seekg(0, std::ios::end); int End = I.tellg(); I.seekg(0, std::ios::beg);
	std::vector<char> V(End);
	if (I.is_open()) { I.read((char*)&V[0], End); } else { std::cout << "COULDN'T OPEN FILE!\n"; }
	//while (!I.eof()) { char c; I.read(&c, 1); V.push_back(c); std::cout << "CHAR: " << (int)c << " |\n"; } // Add this inside 'if' if you want to get char by char
	I.close();

	double SqrtVec = sqrt(V.size()); // IMAGE
	int x = round(SqrtVec);	int y;
	if (SqrtVec / x == 1) { y = x; } else { y = ceil(SqrtVec); }
	CImg<unsigned char> R(x, y, 1, 3, 0);

	if (V.size() > 0)
	{
		int C = 0;
		for (int n = 0; n < V.size(); ++n)
		{
			Point3D<unsigned char> RGB = LinearRGB(((unsigned char)V[n] / 256.0) * Multiplier, 1.0, 1.0);
			unsigned char c[] = { RGB.x, RGB.y, RGB.z };
			R.draw_point(n % x, C, c);
			if (n % x == x - 1) { ++C; }
		}
		if (Rsize != 1.0) { Resize(R, round(x * Rsize), round(y * Rsize), 6); }
	}
	return(R);
}

// ############################################################################################################################################

// ############## COMPLEX:

/*CImg<unsigned char> PrintVectorComplex(std::vector<complex<double>> V) // POR ENQUANTO É COPIA DO PRINT VECTOR NORM
{
	double Min = 0, Max = 0, Total;
	for (int n = 0; n < V.size(); ++n)
	{
		if (V[n] > Max) { Max = V[n]; }
		if (V[n] < Min) { Min = V[n]; }
	}
	Total = fabs(Max) + fabs(Min);
	CImg<unsigned char> R(V.size(), ceil(Total), 1, 3, 0);
	for (int n = 0; n < V.size(); ++n)
	{
		double ndiv = (double)n / (V.size() - 1);
		Point3D<unsigned char> RGB = LinearRGB(V[n], 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		R.draw_point(n, round(Total - (V[n] - Min)), Color);
	}
	return (R);
}*/

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## FRACTAIS:

// PLOTAR PONTOS (STRUCT), NEEDS LINEAR RGB:
CImg<unsigned char> PrintPoints(std::vector<Point<int>> Coord, int SegmentSize, int BackGround, bool Abs, unsigned char Color[3])
{
	Point<int> max, min;
	MaxMinVecPoint(Coord, max, min, Abs);

	int sx = (max.x - min.x + 1) * SegmentSize,	sy = (max.y - min.y + 1) * SegmentSize;
	CImg<unsigned char> Print(sx, sy, 1, 3, BackGround);

	for (size_t n = 1; n < Coord.size(); ++n)
		Linexy(Print, (Coord[n - 1].x - min.x) * SegmentSize, (Coord[n - 1].y - min.y) * SegmentSize,
		(Coord[n].x - min.x) * SegmentSize, (Coord[n].y - min.y) * SegmentSize,	Color, false);

	return(Print);
}
CImg<unsigned char> PrintLinePoints(std::vector<LinePoint<int>> Coord, int SegmentSize, int BackGround, bool Abs, unsigned char Color[3]) // Testar para ver se esta tudo certo
{
	LinePoint<int> max, min;
	MaxMinVecLinePoint(Coord, max, min, Abs);

	int sx = 0;
	if (max.P0.x > max.P1.x) { sx = (max.P0.x + 1) * SegmentSize; }
	else { sx = (max.P0.x + 1) * SegmentSize; }
	int sy = 0;
	if (max.P0.y > max.P1.y) { sy = (max.P0.y + 1) * SegmentSize; }
	else { sy = (max.P0.y + 1) * SegmentSize; }

	CImg<unsigned char> Print(sx, sy, 1, 3, BackGround);
	for (size_t n = 0; n < Coord.size(); ++n)
	{
		Linexy(Print, Coord[n].P0.x * SegmentSize, Coord[n].P0.y * SegmentSize, Coord[n].P1.x * SegmentSize, Coord[n].P1.y * SegmentSize, Color, false);
	}
	return(Print);
}

// PRINT MY FRACTAL:
CImg<unsigned char> PrintBinaryWordCircle(int Size, int r, int Iter, bool GeoAri, bool RandomColor, bool LRGB, Point3D<unsigned char> RGB)
{
	CImg<unsigned char> MainImg(Size, Size, 1, 3, 0);
	double rRatio = 1.0 * r / Size;	int Mid = floor(Size * 0.5);
	std::vector<std::string> BinWords = BinaryWordsSeq(Iter);	std::vector<long> BinArea = BinaryWordSeqArean(Iter);
	for (int c = Iter; c > 0; --c)
	{
		int Invc = (Iter - c) + 1;
		int cSize = 0; if (GeoAri) { cSize = (Size / Iter) * c; } else { cSize = Size / Invc; }
		int MidS = cSize * 0.5;	int cr = rRatio * cSize; int s = BinArea[c - 1]; int s2 = pow(2, c);
		CImg<unsigned char> CircleImg(cSize, cSize, 1, 3, 127);
		unsigned char cclr[] = { 255, 0, 0 }; CircleImg.draw_circle(MidS, MidS, cr, cclr, 1, 1);
		cclr[1] = 255; if (c > 1) { RayPolygonQuick(CircleImg, cr, MidS, MidS, 0, s, cclr, 0, 0); }
		cclr[1] = 0; cclr[2] = 127; RayPolygonQuick(CircleImg, cr, MidS, MidS, 0, s2, cclr, 0, 0);
		double Div = TAU / s2; int Count = 0; std::vector<Point<double>> Scores;
		for (double rad =  0; Count < s2; ++Count) { Scores.push_back({ rad, AOScore(rad) }); rad += Div; } QuickSortPty(Scores, 0, Scores.size() - 1);
		int Wordset = SumntoPowIniEnd(2, 1, c - 1);
		for (int Word = Wordset; Word < Wordset + s2; ++Word)
		{
			if (RandomColor) { RGB.x = rand() % 256; RGB.y = rand() % 256; RGB.z = rand() % 256; }
			if (LRGB) { double Line = 1.0 * (Word - Wordset) / s2; if (BinWords[Word][0] == '0') { RGB = LinearRGB(0.5 + Line, 1, 1); } else { RGB = LinearRGB(Line, 1, 1); } }
			int WordSize = BinWords[Word].size();
			for (int Char = 0; Char < WordSize; ++Char)
			{
				Point3D<unsigned char> NewRGB = RGB; if (BinWords[Word][WordSize - 1 - Char] == '0') { NewRGB.x = 255 - NewRGB.x; NewRGB.y = 255 - NewRGB.y; NewRGB.z = 255 - NewRGB.z; }
				double SubDiv = Div / WordSize; double Rad = Scores[Word - Wordset].x - (SubDiv * (WordSize - 1)) + (SubDiv * Char); Rad -= (TAU / s) * 0.5; Rad = TAU - Rad;
				unsigned char Color[] = { NewRGB.x, NewRGB.y, NewRGB.z };
				if (c > 1) { FillArea(CircleImg, MidS + cos(Rad) * cr * 0.85, MidS + sin(Rad) * cr * 0.85, Color); }
				else { FillArea(CircleImg, MidS, MidS + sin(Rad + TAU * 0.5) * cr * 0.75, Color); }
				//AddText(CircleImg, MidS + cos(Rad) * cr * 0.90, MidS + sin(Rad) * cr * 0.90, std::to_string(BinWords[Word][Char]) + "\n" + BinWords[Word], 255, 0, 0);
			}
		}
		unsigned char IgnoreColor[] = { 127, 127, 127 };
		MainImg = DrawImageIgnClr(MainImg, CircleImg, Mid - MidS, Mid - MidS, IgnoreColor);
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
	unsigned char Color[3]; // Cor
	unsigned char ClrBiLine[3], ClrhLine[3], ClrIncirc[3]; // Cores: Line Bisetora, Line da Heigth, Incircle
	double Scale;
	bool LRGB = false;
	double a, b, c, h, base, base0, gamma, beta, alpha, area, perimetro, bisa, bisb, bisc, inradius, IA, IB, IC;

	// OUTPUT:
	CImg<unsigned char> TriOut;

	// ##################### ##################### #####################

	void CleanImg() { CImg<unsigned char> T; TriOut = T; } // CLEAN
	// Fills the image with a single color, but do not clean height and width like the function above
	void PaintScreen(unsigned char Color[3]) { FillAll(TriOut, Color); }
	void ChangeBorder(int New)
	{
		if (New < 0) { New = 0; } Border = New;
		Width = ceil(Scale * (base + base0)) + (Border * 2); Heigth = ceil(h * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (Scale * Coord[0].x); x[1] = Border + (Scale * Coord[1].x); x[2] = Border + (Scale * Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * Coord[0].y); y[1] = Offy - (Scale * Coord[1].y); y[2] = Offy - (Scale * Coord[2].y); // CORDENADAS Y
	}

	// ##################### CONSTRUTORES #####################
	TriPrint(Triangulo TriInput, double ScaleRto, int BorderImg, unsigned char inColor[3])
	{
		Border = BorderImg; base = TriInput.Base; base0 = TriInput.Base0;
		Width = ceil(ScaleRto * (base + base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * ScaleRto) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (ScaleRto * TriInput.Coord[0].x); x[1] = Border + (ScaleRto * TriInput.Coord[1].x); x[2] = Border + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		CImg<unsigned char> TO(Width, Heigth, 1, 3, 0); TriOut = TO; // Output
		LRGB = false; Scale = ScaleRto; // Graph
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.Area; perimetro = TriInput.Perimetro;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * Coord[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpoints[0]; Midpoint[1] = TriInput.Midpoints[1]; Midpoint[2] = TriInput.Midpoints[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
		// CORES:
		Color[0] = inColor[0]; Color[1] = inColor[1]; Color[2] = inColor[2];
		ClrBiLine[0] = inColor[0] / 2; ClrBiLine[1] = inColor[1] / 2; ClrBiLine[2] = inColor[2];
		ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
		ClrIncirc[0] = (255 - inColor[0]) / 2; ClrIncirc[1] = (255 - inColor[1]) / 2; ClrIncirc[2] = (255 - inColor[2]) / 2;
	}
	TriPrint(Triangulo TriInput, double ScaleRto, int BorderImg)
	{
		Border = BorderImg; base = TriInput.Base; base0 = TriInput.Base0;
		Width = ceil(ScaleRto * (base + base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * ScaleRto) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (ScaleRto * TriInput.Coord[0].x); x[1] = Border + (ScaleRto * TriInput.Coord[1].x); x[2] = Border + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		CImg<unsigned char> TO(Width, Heigth, 1, 3, 0); TriOut = TO; // Output
		LRGB = true; Scale = ScaleRto; // Graph
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.Area; perimetro = TriInput.Perimetro;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * SclCrd[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpoints[0]; Midpoint[1] = TriInput.Midpoints[1]; Midpoint[2] = TriInput.Midpoints[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
		// CORES:
		Color[0] = 191; Color[1] = 127; Color[2] = 159;
		ClrBiLine[0] = Color[0] / 2; ClrBiLine[1] = Color[1] / 2; ClrBiLine[2] = Color[2];
		ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
		ClrIncirc[0] = (255 - Color[0]) / 2; ClrIncirc[1] = (255 - Color[1]) / 2; ClrIncirc[2] = (255 - Color[2]) / 2;
	}
	void NewTri(Triangulo TriInput)
	{
		Width = ceil(Scale * (TriInput.Base + TriInput.Base0)) + (Border * 2); Heigth = ceil(TriInput.Alt * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (Scale * TriInput.Coord[0].x); x[1] = Border + (Scale * TriInput.Coord[1].x); x[2] = Border + (Scale * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * TriInput.Coord[0].y); y[1] = Offy - (Scale * TriInput.Coord[1].y); y[2] = Offy - (Scale * TriInput.Coord[2].y); // CORDENADAS Y
		bool Lb = false, Ab = false, LbAb = false; // Width Bigger, Heigth bigger, Width Or Heigth bigger
		if (Width > TriOut.width()) { Lb = true; } // Do we need to expand the image because the width?
		if (Heigth > TriOut.height()) { Ab = true; } // Do we need to expand the image because the height?
		if (Lb && Ab) { if (Width < Heigth) { LbAb = true; } } // 'LbAb' can only be true if we need to expand BOTH width and height
		if (LbAb || Ab) { TriOut = ExpandImg(TriOut, (Heigth - TriOut.height()) * 0.5, 0); } // Expand image in accord to height
		else if (Lb) { TriOut = ExpandImg(TriOut, (Width - TriOut.height()) * 0.5, 0); }
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Alt; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.Area; perimetro = TriInput.Perimetro;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;
		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * Coord[1].y; SclCrd[2].y = Scale * Coord[2].y;
		Midpoint[0] = TriInput.Midpoints[0]; Midpoint[1] = TriInput.Midpoints[1]; Midpoint[2] = TriInput.Midpoints[2];
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
			unsigned char nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			Linexy(TriOut, x[1], y[1], x[2], y[2], nc, LRGB);
		} // c -> "\"
		if (!ChangeSidesColor) { Linexy(TriOut, x[2], y[2], x[0], y[0], Color, LRGB); }
		else
		{
			unsigned char nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			Linexy(TriOut, x[2], y[2], x[0], y[0], nc, LRGB);
		}	// b -> "/"
		if (Text)
		{
			AddText(TriOut, 16, y[0] - 8, "a: " + std::to_string(a), Color); // A
			unsigned char nc[] = { (255 - Color[0]) * 0.75, (255 - Color[1]) * 0.75, (255 - Color[2]) * 0.75 };
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
			unsigned char nc[] = { 255, 0, 0 };
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
			if (AddVert) { unsigned char Color[] = { 127, 127, 127 }; AddVert(TriOut, (SclCrd[2].x) + Border, Offy, 3, Color); }
		}
	}

	// PRINT BISECTOR LINES:
	void TriBisectorPrint(bool Text)
	{
		double Angle = 0;
		if (gamma <= 90) { Angle = Ang2Rad(beta + (alpha * 0.5)); }	else { Angle = Ang2Rad(beta + (alpha * 0.5)); }
		Line(TriOut, bisa * Scale, Angle, x[2], y[2], false, ClrBiLine, false);
		if (gamma <= 90) { Angle = Ang2Rad(180 + (beta * 0.5)); } else { Angle = Ang2Rad(180 + (beta * 0.5)); }
		Line(TriOut, bisb * Scale, Angle, x[1], y[1], false, ClrBiLine, false);
		if (gamma <= 90) { Angle = Ang2Rad(360 - (gamma * 0.5)); } else { Angle = Ang2Rad(360 - (gamma * 0.5)); }
		Line(TriOut, bisc * Scale, Angle, x[0], y[0], false, ClrBiLine, false);
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
		int Pixx = x[1] - (Scale * IB * cos(Ang2Rad(beta) * 0.5)), Pixy = y[0] - (Scale * IB * sin(Ang2Rad(beta) * 0.5));
		if (AddVertex) { AddVert(TriOut, Pixx, Pixy, 3, Color); } // Incenter
		if (LRGB) { Circlexy(TriOut, inradius * Scale, Pixx, Pixy); } else { Circlexy(TriOut, inradius * Scale, Pixx, Pixy, ClrIncirc); }
	}

	// IMPRIME MIDPOINTS DO TRIANGULO (Algumas vezes fica zuado):
	void TriMidpointPrint()
	{
		AddVert(TriOut, Border + (Scale * Midpoint[0].x), Offy - (Scale * Midpoint[0].y), 3, Color);
		AddVert(TriOut, Border + (Scale * Midpoint[1].x), Offy - (Scale * Midpoint[1].y), 3, Color);
		AddVert(TriOut, Border + (Scale * Midpoint[2].x), Offy - (Scale * Midpoint[2].y), 3, Color);
	}

	// IMPRIME INFORMAÇÕES TRIGONOMETRICAS DOS ANGULOS:
	void TriTrigPrint()
	{
		double ralpha = Ang2Rad(alpha), rbeta = Ang2Rad(beta), rgamma = Ang2Rad(gamma);
		CImg<unsigned char> StringComp(Width, (8 * 3) + 4, 1, 3, 255);
		std::string S0 = "# sin abc: " + std::to_string(sin(ralpha)) + " | " + std::to_string(sin(rbeta)) + " | " + std::to_string(sin(rgamma));
		std::string S1 = "# cos abc: " + std::to_string(cos(ralpha)) + " | " + std::to_string(cos(rbeta)) + " | " + std::to_string(cos(rgamma));
		std::string S2 = "# tan abc: " + std::to_string(tan(ralpha)) + " | " + std::to_string(tan(rbeta)) + " | " + std::to_string(tan(rgamma));
		unsigned char nc[] = { 0, 0, 0 };
		AddText(StringComp, 4, 1, S0, nc);
		AddText(StringComp, 4, 9, S1, nc);
		AddText(StringComp, 4, 17, S2, nc);
		TriOut = JoinImg(TriOut, StringComp, 1); // Não vamos modificar altura, pois a variavel de Offset de Heigth (Offy) se mantém igual a quando a classe foi construida
	}

	// ##################### ##################### #####################

	// IMPRIME TRIÂNGULO COM TODAS FUNÇÕES:
	void TriAllPrint(bool AddVertex, bool AddText, bool ChangeSidesColor)
	{
		//int R = Color[0], G = Color[1], B = Color[1]; // Caso um dia fazer um função que nescessite
		TriPeriPrint(AddVert, AddText, true, ChangeSidesColor);
		TriBisectorPrint(AddText);
		TriIncirclePrint(AddVertex);
		TriMidpointPrint();
		TriTrigPrint(); // (MANTENHA POR ULTIMO)
		// ####### Imprime Lines Medians #######		
		// ####### Circumcentro #######
		unsigned char CC[] = { 127, 127, 127 };
		AddVert(TriOut, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, Color); // Circumcentro
		// ###################################
	}

	/* IMPRIME TRIÂNGULO COM SELEÇÃO DE TODAS FUNÇÕES:
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
		unsigned char CC[] = { 255, 0, 255 };
		AddVert(TriOut, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, Color); // Circumcentro
		// ###################################
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_