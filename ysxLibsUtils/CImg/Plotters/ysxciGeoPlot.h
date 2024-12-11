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
void ysxCIMG_DRAW_Circlexy(CImg<uint8_t>& Img, double r, uint16_t x, uint16_t y, uint8_t* C = nullptr)
{
	uint16_t yc, xc;
	double dt = 1.0 / r; bool LC = false;
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
void ysxCIMG_DRAW_Turn(CImg<uint8_t>& I, double r, uint16_t x, int16_t y, double Ini, double Turn, uint8_t* C = nullptr)
{
	uint16_t yc, xc;
	double rad, dt = (Turn - Ini) / (TAU * r);
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	uint8_t c[3];

	for (rad = Ini; rad <= Turn; rad += dt)
	{
		yc = y + round(sin(TAU - rad) * r); xc = x + round(cos(rad) * r);
		if (ysxCIMG_InImg(I, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB((rad - Ini) / (Turn - Ini), 1, 1, c); I.draw_point(xc, yc, c); }
			else { I.draw_point(xc, yc, C); }
		}
	}
}

// ######################################################################

// ############## RADIUS:

// PLOT RADIUS:
void ysxCIMG_DRAW_Radius(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double rad, bool Triangle, bool Border, uint8_t* C = nullptr)
{
	uint16_t xc, yc, rn;
	double Sin = sin(TAU - rad), Cos = cos(rad);
	int xend = round(Cos * r);
	uint8_t IC[3]; uint8_t c[3];

	for (rn = 0; rn <= r; ++rn)
	{
		yc = y + round(Sin * rn);
		xc = x + round(Cos * rn);
		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C) 
			{
				ysxCOLOR_LinearRGB(rn / r, 1, 1, c);
				Img.draw_point(xc, yc, c);
			}
			else { Img.draw_point(xc, yc, C); }
			if (Triangle)
			{
				if (!C) { IC[0] = 255 - c[0]; IC[1] = 255 - c[1]; IC[2] = 255 - c[2]; }
				else { IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2]; }
				Img.draw_point(xc, y, IC);
				Img.draw_point(x + xend, yc, IC);
			}
		}
	}	
	if (Border) { if (!C) { ysxCIMG_DRAW_Circlexy(Img, r, x, y, c); } else { ysxCIMG_DRAW_Circlexy(Img, r, x, y, C); } }
}
void ysxCIMG_DRAW_RadiusQuick(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double rad, bool Triangle, bool Border, uint8_t* C)
{
	uint16_t xc, yc;
	double Sin = sin(TAU - rad), Cos = cos(rad);
	int xend = round(Cos * r), yend = round(Sin * r);
	uint8_t IC[3];

	if (ysxCIMG_InImg(Img, y, x) && ysxCIMG_InImg(Img, yend, xend))
	{
		Img.draw_line(x, y, x + xend, y + yend, C);
		if (Triangle)
		{
			IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2];
			Img.draw_line(x, y, x + xend, y, IC);
			Img.draw_line(x + xend, y, x + xend, y + yend, IC);
		}
	}
	if (Border) { ysxCIMG_DRAW_Circlexy(Img, r, x, y, C); }
}

void ysxCIMG_DRAW_RadiusPolygon(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double OffSet, int Divisions, bool Triangle, bool Border, uint8_t* C = nullptr)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		if (!C) { ysxCIMG_DRAW_Radius(Img, r, x, y, n, Triangle, Border); }
		else { ysxCIMG_DRAW_Radius(Img, r, x, y, n, Triangle, Border, C); }		
	}
}
void ysxCIMG_DRAW_RadiusPolygonQuick(CImg<uint8_t>& Img, double r, uint16_t x, int16_t y, double OffSet, int Divisions, uint8_t* C, bool Triangle, bool Border)
{
	double Div = TAU / Divisions;
	for (double n = OffSet; n < TAU + OffSet; n += Div)
	{
		ysxCIMG_DRAW_RadiusQuick(Img, r, x, y, n, Triangle, Border, C);
	}
}

// ######################################################################

// ############## CYCLOIDS:

// HYPOCYCLOID (FIX PERIMETER OR MAYBE THE PROBLEM IS ON THE COORDS):
void ysxCIMG_DRAW_HypoCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2, uint8_t* C = nullptr)
{
	double Arc = (r * 8 * ((R / r) - 1)), dt = (t2 - t1) / Arc;
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		xc = x + ((R - r) * cos(t) + r * cos(t * (R - r) / r));
		yc = y + ((R - r) * sin(t) - r * sin(t * (R - r) / r));
		if (!C) { ysxCOLOR_LinearRGB((t - t1) / (t2 - t1), 1, 1, c); I.draw_point(xc, yc, c); }
		else { I.draw_point(xc, yc, C); }
	}
}

// EPICYCLOID (WIP, PERIMETER AND MORE):
void ysxCIMG_DRAW_EpiCicl(CImg<uint8_t>& I, double R, double r, double x, double y, double t1, double t2, uint8_t* C = nullptr)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double dt = (t2 - t1) / (TAU * (R + r)); // Não lembro, mudar depois
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		yc = y + ((R + r) * sin(t) - r * sin(t * (R + r) / r));
		xc = x + ((R + r) * cos(t) - r * cos(t * (R + r) / r));
		if (ysxCIMG_InImg(I, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB((t - t1) / (t2 - t1), 1, 1, c); I.draw_point(xc, yc, c); }
			else { I.draw_point(xc, yc, C); }
		}
	}
}

// ############################################################################################################################################

// ############## POLYGONAL:

// PLOT POLYGON:
void ysxCIMG_DRAW_Polygon(CImg<uint8_t>& Img, int Sides, double r, uint16_t x, uint16_t y, bool Vertex, uint8_t* C = nullptr)
{
	uint16_t xc, yc, Count = 0;
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
	for (uint16_t ns = 1; ns < Sides; ++ns)
	{
		if (ysxCIMG_InImg(Img, Coord[ns].y, Coord[ns].x) && ysxCIMG_InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			if (!C) { ysxCOLOR_LinearRGB(ns - 1 / Sides, 1, 1, c); ysxCIMG_DRAW_Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, c); }
			else { ysxCIMG_DRAW_Linexy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, C); }
			if (ns == Sides - 1) { ysxCIMG_DRAW_Linexy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, c); }
		}
	}

}


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## CLASSES ##############
// ###################################

// ############## PRINT TRIANGLE:
class ysxCIMG_DRAW_Tri
{
public:
	// CONFIG:
	uint16_t Border = 25; // Distancia da margem
	size_t Width, Heigth; // Medidas da imagem
	int Offy; // Offset para resumir texto dos calculos
	int x[3], y[3]; // Coordenadas de acordo com escalas, bordas, altura e largura
	Point<int> Coord[3], SclCrd[3], Midpoint[3], Circumcenter; // Cordenada dos triangulos, Cordenada com Scale, Coordenada dos midpoints e do Circumcentro
	uint8_t Color[3];
	uint8_t ClrBiLine[3], ClrhLine[3], ClrIncirc[3]; // Bisector line, Heigth line, Incircle line
	double Scale;
	bool LRGB = false;
	double a, b, c, h, base, base0, gamma, beta, alpha, area, perimetro, bisa, bisb, bisc, inradius, IA, IB, IC;

	// OUTPUT:
	CImg<uint8_t> TriOut;

	// ##################### ##################### #####################

	void EmptyImg() { CImg<uint8_t> T; TriOut = T; } // CLEAN
	// Fills the image with a single color, but do not clean height and width like the function above
	void PaintScreen(uint8_t* Color) { ysxCIMG_CleanImg(TriOut, Color); }
	void ChangeBorder(uint16_t New)
	{
		if (New < 0) { New = 0; } Border = New;
		Width = ceil(Scale * (base + base0)) + (Border * 2); Heigth = ceil(h * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (Scale * Coord[0].x); x[1] = Border + (Scale * Coord[1].x); x[2] = Border + (Scale * Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * Coord[0].y); y[1] = Offy - (Scale * Coord[1].y); y[2] = Offy - (Scale * Coord[2].y); // CORDENADAS Y
	}

	// ##################### CONSTRUTORES #####################
	ysxCIMG_DRAW_Tri(ysxTRI_Triangle TriInput, double ScaleRto, int BorderImg, uint8_t* inColor = nullptr)
	{
		Border = BorderImg; base = TriInput.Base; base0 = TriInput.Base0;
		Width = ceil(ScaleRto * (base + base0)) + (Border * 2); Heigth = ceil(TriInput.Height * ScaleRto) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (ScaleRto * TriInput.Coord[0].x); x[1] = Border + (ScaleRto * TriInput.Coord[1].x); x[2] = Border + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		CImg<uint8_t> TO(Width, Heigth, 1, 3, 0); TriOut = TO; // Output

		LRGB = false; Scale = ScaleRto; // Graph
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Height; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
		area = TriInput.A; perimetro = TriInput.P;
		bisa = TriInput.BisA; bisb = TriInput.BisB; bisc = TriInput.BisC; inradius = TriInput.Inradius; IA = TriInput.IA; IB = TriInput.IB; IC = TriInput.IC;

		Coord[0].x = TriInput.Coord[0].x; Coord[1].x = TriInput.Coord[1].x; Coord[2].x = TriInput.Coord[2].x;
		Coord[0].y = TriInput.Coord[0].y; Coord[1].y = TriInput.Coord[1].y; Coord[2].y = TriInput.Coord[2].y;
		
		SclCrd[0].x = Scale * Coord[0].x; SclCrd[1].x = Scale * Coord[1].x; SclCrd[2].x = Scale * Coord[2].x;
		SclCrd[0].y = Scale * Coord[0].y; SclCrd[1].y = Scale * Coord[1].y; SclCrd[2].y = Scale * Coord[2].y;
		
		Midpoint[0] = TriInput.Midpts[0]; Midpoint[1] = TriInput.Midpts[1]; Midpoint[2] = TriInput.Midpts[2];
		Circumcenter.x = TriInput.Circumcenter.x; Circumcenter.y = TriInput.Circumcenter.y;
		
		// CORES:
		if (inColor)
		{
			Color[0] = inColor[0]; Color[1] = inColor[1]; Color[2] = inColor[2];
			ClrBiLine[0] = inColor[0] / 2; ClrBiLine[1] = inColor[1] / 2; ClrBiLine[2] = inColor[2];
			ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
			ClrIncirc[0] = (255 - inColor[0]) / 2; ClrIncirc[1] = (255 - inColor[1]) / 2; ClrIncirc[2] = (255 - inColor[2]) / 2;
		}
		else
		{
			Color[0] = 191; Color[1] = 127; Color[2] = 159;
			ClrBiLine[0] = Color[0] / 2; ClrBiLine[1] = Color[1] / 2; ClrBiLine[2] = Color[2];
			ClrhLine[0] = 127; ClrhLine[1] = 127; ClrhLine[2] = 127;
			ClrIncirc[0] = (255 - Color[0]) / 2; ClrIncirc[1] = (255 - Color[1]) / 2; ClrIncirc[2] = (255 - Color[2]) / 2;
		}
	}
	
	void NewTri(ysxTRI_Triangle TriInput) // RE-DO THIS!!!
	{
		Width = ceil(Scale * (TriInput.Base + TriInput.Base0)) + (Border * 2); Heigth = ceil(TriInput.Height * Scale) + (Border * 2);
		Offy = Heigth - Border; // O fim vertical da imagem se não contar a borda
		x[0] = Border + (Scale * TriInput.Coord[0].x); x[1] = Border + (Scale * TriInput.Coord[1].x); x[2] = Border + (Scale * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (Scale * TriInput.Coord[0].y); y[1] = Offy - (Scale * TriInput.Coord[1].y); y[2] = Offy - (Scale * TriInput.Coord[2].y); // CORDENADAS Y
		bool Lb = false, Ab = false, LbAb = false; // Width Bigger, Heigth bigger, Width Or Heigth bigger
		if (Width > TriOut.width()) { Lb = true; } // Do we need to expand the image because the width?
		if (Heigth > TriOut.height()) { Ab = true; } // Do we need to expand the image because the height?
		if (Lb && Ab) { if (Width < Heigth) { LbAb = true; } } // 'LbAb' can only be true if we need to expand BOTH width and height
		if (LbAb || Ab) { TriOut = ysxCIMG_ExpandImgBorders(TriOut, (Heigth - TriOut.height()) * 0.5, 0); } // Expand image in accord to height
		else if (Lb) { TriOut = ysxCIMG_ExpandImgBorders(TriOut, (Width - TriOut.height()) * 0.5, 0); }
		a = TriInput.a; b = TriInput.b; c = TriInput.c; h = TriInput.Height; gamma = TriInput.Gamma; beta = TriInput.Beta; alpha = TriInput.Alpha; // GET CLASS INFO
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
	void TriPeriPrint(bool AddVertex, bool Text, bool AddHeight, bool ChangeSidesColor)
	{
		ysxCIMG_DRAW_Linexy(TriOut, x[0], y[0], x[1], y[1], Color); // a -> "_"
		if (!ChangeSidesColor) { ysxCIMG_DRAW_Linexy(TriOut, x[1], y[1], x[2], y[2], Color); }
		else
		{
			uint8_t nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			ysxCIMG_DRAW_Linexy(TriOut, x[1], y[1], x[2], y[2], nc);
		} // c -> "\"
		if (!ChangeSidesColor) { ysxCIMG_DRAW_Linexy(TriOut, x[2], y[2], x[0], y[0], Color); }
		else
		{
			uint8_t nc[] = { (Color[0] + 85) % 256, (Color[1] + 85) % 256, (Color[2] + 85) % 256 };
			ysxCIMG_DRAW_Linexy(TriOut, x[2], y[2], x[0], y[0], nc);
		}	// b -> "/"
		if (Text)
		{
			ysxCIMG_AddText(TriOut, 16, y[0] - 8, "a: " + std::to_string(a), Color); // A
			uint8_t nc[] = { (255 - Color[0]) * 0.75, (255 - Color[1]) * 0.75, (255 - Color[2]) * 0.75 };
			ysxCIMG_AddText(TriOut, 16, y[0], "Gamma: " + std::to_string(gamma), nc); // GAMMA
			ysxCIMG_AddText(TriOut, round(Width * 0.75), y[1] - 8, "c: " + std::to_string(c), Color); // C, Algo misteriosamente deu errado
			ysxCIMG_AddText(TriOut, round(Width * 0.75), y[1], "Beta: " + std::to_string(beta), nc); // BETA
			ysxCIMG_AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 8), "b: " + std::to_string(b), Color); // B
			ysxCIMG_AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 16), "Alpha: " + std::to_string(alpha), nc); // ALPHA
			nc[0] = 255; nc[1] = 127; nc[2] = 127;
			ysxCIMG_AddText(TriOut, round(Width * 0.5), Heigth * 0.5, "Area: " + std::to_string(area), nc); // AREA
			nc[0] = 127; nc[1] = 255; nc[2] = 127;
			ysxCIMG_AddText(TriOut, round(Width * 0.5), (Heigth * 0.5) + 8, "Peri.: " + std::to_string(perimetro), nc); // PERIMETER
		}
		if (AddVertex)
		{
			uint8_t nc[] = { 255, 0, 0 };
			ysxCIMG_AddVert(TriOut, x[0], y[0], 3, nc);
			nc[0] = 0; nc[1] = 255;
			ysxCIMG_AddVert(TriOut, x[1], y[1], 3, nc);
			nc[1] = 0; nc[2] = 255;
			ysxCIMG_AddVert(TriOut, x[2], y[2], 3, nc);
		}
		if (AddHeight)
		{
			ysxCIMG_DRAW_Linexy(TriOut, (SclCrd[2].x) + Border, Offy, (SclCrd[2].x) + Border, Offy - round(Scale * h), ClrhLine);
			if (Text)
			{ int px = x[2] - 64; if (px < Width * 0.33) { px += 80; } ysxCIMG_AddText(TriOut, px, Offy - round(Scale * h * 0.5) - 8, "Height: " + std::to_string(h), ClrhLine); }
			if (AddVertex) { uint8_t Color[] = { 127, 127, 127 }; ysxCIMG_AddVert(TriOut, (SclCrd[2].x) + Border, Offy, 3, Color); }
		}
	}

	// PRINT BISECTOR LINES:
	void TriBisectorPrint(bool Text)
	{
		double Angle = 0;
		if (gamma <= 90) { Angle = Ang2Rad(beta + (alpha * 0.5)); }	else { Angle = Ang2Rad(beta + (alpha * 0.5)); }
		ysxCIMG_DRAW_Line(TriOut, bisa * Scale, Angle, x[2], y[2], false, ClrBiLine);
		if (gamma <= 90) { Angle = Ang2Rad(180 + (beta * 0.5)); } else { Angle = Ang2Rad(180 + (beta * 0.5)); }
		ysxCIMG_DRAW_Line(TriOut, bisb * Scale, Angle, x[1], y[1], false, ClrBiLine);
		if (gamma <= 90) { Angle = Ang2Rad(360 - (gamma * 0.5)); } else { Angle = Ang2Rad(360 - (gamma * 0.5)); }
		ysxCIMG_DRAW_Line(TriOut, bisc * Scale, Angle, x[0], y[0], false, ClrBiLine);
		if (Text)
		{
			ysxCIMG_AddText(TriOut, round(Width * 0.5), Offy - ((SclCrd[2].y) - 24), "BisA: " + std::to_string(bisa), ClrBiLine);
			ysxCIMG_AddText(TriOut, round(Width * 0.75), y[1] - 16, "BisB: " + std::to_string(bisb), ClrBiLine);
			ysxCIMG_AddText(TriOut, 16, y[0] - 16, "BisC: " + std::to_string(bisc), ClrBiLine);
		}
	}

	// IMPRIME INCIRCLE:
	void TriIncirclePrint(bool AddVertex)
	{
		int xc = x[1] - (Scale * IB * cos(Ang2Rad(beta) * 0.5)), yc = y[0] - (Scale * IB * sin(Ang2Rad(beta) * 0.5));
		if (AddVertex) { ysxCIMG_AddVert(TriOut, xc, yc, 3, Color); } // Incenter
		if (LRGB) { ysxCIMG_DRAW_Circlexy(TriOut, inradius * Scale, xc, yc); } else { ysxCIMG_DRAW_Circlexy(TriOut, inradius * Scale, xc, yc, ClrIncirc); }
	}

	// IMPRIME MIDPOINTS DO TRIANGULO (Algumas vezes fica zuado):
	void TriMidpointPrint()
	{
		ysxCIMG_AddVert(TriOut, Border + (Scale * Midpoint[0].x), Offy - (Scale * Midpoint[0].y), 3, Color);
		ysxCIMG_AddVert(TriOut, Border + (Scale * Midpoint[1].x), Offy - (Scale * Midpoint[1].y), 3, Color);
		ysxCIMG_AddVert(TriOut, Border + (Scale * Midpoint[2].x), Offy - (Scale * Midpoint[2].y), 3, Color);
	}

	// IMPRIME INFORMAÇÕES TRIGONOMETRICAS DOS ANGULOS:
	void TriTrigPrint()
	{
		double ralpha = Ang2Rad(alpha), rbeta = Ang2Rad(beta), rgamma = Ang2Rad(gamma);
		CImg<uint8_t> StringComp(Width, (8 * 3) + 4, 1, 3, 255);
		std::string S0 = "# sin abc: " + std::to_string(sin(ralpha)) + " | " + std::to_string(sin(rbeta)) + " | " + std::to_string(sin(rgamma));
		std::string S1 = "# cos abc: " + std::to_string(cos(ralpha)) + " | " + std::to_string(cos(rbeta)) + " | " + std::to_string(cos(rgamma));
		std::string S2 = "# tan abc: " + std::to_string(tan(ralpha)) + " | " + std::to_string(tan(rbeta)) + " | " + std::to_string(tan(rgamma));
		uint8_t nc[] = { 0, 0, 0 };
		ysxCIMG_AddText(StringComp, 4, 1, S0, nc);
		ysxCIMG_AddText(StringComp, 4, 9, S1, nc);
		ysxCIMG_AddText(StringComp, 4, 17, S2, nc);
		TriOut = ysxCIMG_JoinImg(TriOut, StringComp, 1); // Não vamos modificar altura, pois a variavel de Offset de Heigth (Offy) se mantém igual a quando a classe foi construida
	}

	// ##################### ##################### #####################

	/*PRINT TRIANGLE WITH FLAG OPTIONS:
	 Flags:
	 AddVertPeri 128
	 |AddVertBis 64
	 ||AddVertInCirc 32
	 1111 1111
	    | |||Print Perimeter 1
	    | ||Print Bisector Lines 2
	    | |Print Incircle 4
	    | Print Midpoints 8
	    Print Trig. functions info 16*/
	void TriPrintByFlags(bool AddText, bool ChangeSidesColor, uint8_t Flags = 255)
	{
		//int R = Color[0], G = Color[1], B = Color[1];
		if (Flags & 1) { TriPeriPrint(Flags & 32, AddText, true, ChangeSidesColor); }
		if (Flags & 2) { TriBisectorPrint(Flags & 64); }
		if (Flags & 4) { TriIncirclePrint(Flags & 128); }
		if (Flags & 8) { TriMidpointPrint(); }
		if (Flags & 16) { TriTrigPrint(); } // (MANTENHA POR ULTIMO)
		//uint8_t CC[] = { 255, 0, 255 }; // I forgot why i wrote this... ???
		ysxCIMG_AddVert(TriOut, (Scale * Circumcenter.x) + Border, Offy - (Scale * Circumcenter.y), 3, Color); // Circumcentro
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
