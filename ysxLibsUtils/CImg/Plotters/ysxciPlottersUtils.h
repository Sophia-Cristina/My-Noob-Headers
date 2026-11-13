#pragma once

#ifndef YSXCIPLOTTERUTILS_H
#define YSXCIPLOTTERUTILS_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Useful tools that may be used in a plot.
// #####################


// #################################################

// #################################################


// #################################################
// ####### MEASURES:

/*METRIC LINES:
Vertical OR horizontal divisions.
Make your changes based on the idea that the metric is scaled by image size.*/
void ysxCIMG_DRAW_MetricLines(CImg<uint8_t>&I, double a1, double a2, double Div, bool VertHori, bool Text, uint8_t * Clr) // REFAZER, e adicionar polar
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
				I.draw_line(x, 0, x, sy, Clr);
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					ysxCIMG_AddText(I, x, Mid, std::to_string(a), Clr);
				}
			}
			else
			{
				y = sy - (C * Div * Ratio); ++C;
				I.draw_line(0, y, sx, y, Clr);
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					ysxCIMG_AddText(I, Mid, y, std::to_string(a), Clr);
				}
			}
		}
	}
}


// POLAR (arrumar, roubei da classe, colocar x e y), fazer um com raio:
// FAZER UMA VERSÃO COM VECTOR, SEM SER POLIGONAL COMO AQUELE QUE JÁ TEM.
void ysxCIMG_DRAW_Polar(CImg<uint8_t>& I, double r, double x, double y, double t1, double t2, double Omega, double (*f)(double, double), uint8_t* C = nullptr)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double Amp, dt = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		Amp = r * f(t, Omega); // FORMULA
		yc = y + round(Amp * sin(t)); xc = x + round(Amp * cos(t));
		if (!C) { ysxCOLOR_LinearRGB((t - t1) / (t2 - t1), 1, 1, c); I.draw_point(xc, yc, c); }
		else { I.draw_point(xc, yc, C); }
	}
}


// #################################################


// ########################################################
// ############## GRAPHICS:
// !!! ATTENTION: Most functions here are very old and i'm not sure if these still works or if these are optmized or not a complete mess !!!

// BARS:
// If '!x_or_y_axis', then 'xory0 = x0', and 'pos = y'.
void ysxCIMG_DrawBar(CImg<uint8_t>& Img, bool x_or_y_axis, uint16_t xory0, uint16_t xory1, uint16_t Thick, uint16_t pos, uint8_t* Color)
{
	if (!Thick) { Thick = 1; }
	if (Color)
	{
		if (!x_or_y_axis) { for (size_t C = 0; C < Thick; ++C) { Img.draw_line(xory0, pos + C, xory1, pos + C, Color); } }
		else { for (size_t C = 0; C < Thick; ++C) { Img.draw_line(pos + C, xory0, pos + C, xory1, Color); } }
	}
}

// ADD BORDERS:
CImg<uint8_t> ysxCIMG_AddBorder(CImg<uint8_t>& Img, uint16_t BorderXThick, uint16_t BorderYThick, uint8_t* C)
{
	uint16_t x = Img.width() + (BorderYThick * 2), y = Img.height() + (BorderXThick * 2);
	CImg<uint8_t> R(x, y, 1, 3, 0);
	R.draw_image(BorderXThick, BorderYThick, Img);
	ysxCIMG_DrawBar(R, false, 0, y, BorderYThick, 0, C);
	ysxCIMG_DrawBar(R, false, 0, y, BorderYThick, x - BorderYThick, C);
	ysxCIMG_DrawBar(R, true, BorderYThick, x - (BorderYThick + 1), BorderXThick, 0, C);
	ysxCIMG_DrawBar(R, true, BorderYThick, x - (BorderYThick + 1), BorderXThick, y - BorderXThick, C);
	return(R);
}

// DRAW BOX, RECTANGLE (NOT FILLED):
void ysxCIMG_Box(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t* C)
{
	//Img.draw_rectangle(x, y, sizex, sizey, C); // <-- USAR ESSE!
	ysxCIMG_DrawBar(Img, false, y, y + sizey, 1, x, C);
	ysxCIMG_DrawBar(Img, false, y, y + sizey, 1, x + sizex, C);
	ysxCIMG_DrawBar(Img, true, x, x + sizex, 1, y, C);
	ysxCIMG_DrawBar(Img, true, x, x + sizex, 1, y + sizey, C);
}

// BOX MATRIX:
void ysxCIMG_BoxMatrix(CImg<uint8_t>& Img, uint16_t Border, uint16_t Divx, uint16_t Divy, uint8_t* C)
{
	uint16_t Height = Img.height(), Width = Img.width();
	ysxCIMG_DrawBar(Img, false, Border, Height - Border, Border, 0, C);
	ysxCIMG_DrawBar(Img, false, Border, Height - Border, Border, Width - Border, C);
	ysxCIMG_DrawBar(Img, true, 0, Width, Border, 0, C);
	ysxCIMG_DrawBar(Img, true, 0, Width, Border, Height - Border, C);
	if (Divx == 0) { Divx = 1; } if (Divy == 0) { Divy = 1; } // No division by zero!
	double HD = (double)Height / Divy, WD = (double)Width / Divx;
	for (int n = 1; n < Divx; ++n) { ysxCIMG_DrawBar(Img, false, Border, Height - Border, Border, n * WD - Border * 0.5, C); }
	for (int n = 1; n < Divy; ++n) { ysxCIMG_DrawBar(Img, true, Border, Width - Border, Border, n * HD - Border * 0.5, C); }
}

// DRAW A RECTANGLE CELL WITH TEXT:
CImg<uint8_t> ysxCIMG_RectCell(uint16_t x, uint16_t y, uint16_t Borderx, uint16_t Bordery, std::string Text, uint8_t* C)
{
	if (x <= Borderx) { x = Borderx + 1; } if (y <= Bordery) { y = Bordery + 1; }
	CImg<uint8_t> Cell(x - Bordery, y - Borderx, 1, 3, 0);
	ysxCIMG_DRAW_FillFlood(Cell, x * 0.5, y * 0.5, C);
	C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
	if (Borderx == 0) { ++Borderx; } if (Bordery == 0) { ++Bordery; }
	Cell = ysxCIMG_AddBorder(Cell, Borderx, Bordery, C);
	C[0] = 255 - C[0];
	ysxCIMG_AddText(Cell, x * 0.25, y * 0.25, Text, C);
	return(Cell);
}

// CRIA IMAGEM DE UMA BARRA BASEADO NUM VALOR (ABOSLUTO):
CImg<uint8_t> ysxCIMG_ValueBarAbs(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> Bar;
	uint8_t InvC[] = { C[0] = 255 - C[0], C[1] = 255 - C[1], C[2] = 255 - C[2], };
	Value = fabs(Value * Ratio);
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { Bar = CImg<uint8_t>::CImg(Value - Bordery, Width - Borderx, 1, 3, 0); }
		else { Bar = CImg<uint8_t>::CImg(Width - Bordery, Value - Borderx, 1, 3, 0); }
		ysxCIMG_DRAW_FillFlood(Bar, Bar.width() * 0.5, Bar.height() * 0.5, C);
		if (Borderx > 0 && Bordery > 0) { Bar = ysxCIMG_AddBorder(Bar, Borderx, Bordery, InvC); }
	}
	return(Bar);
}
CImg<uint8_t> ysxCIMG_ValueBarAbs(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis)
{
	CImg<uint8_t> Bar;
	uint8_t C[3];
	Value = fabs(Value * Ratio);
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { Bar = CImg<uint8_t>::CImg(Value - Bordery, Width - Borderx, 1, 3, 0); }
		else { Bar = CImg<uint8_t>::CImg(Width - Bordery, Value - Borderx, 1, 3, 0); }
		ysxCOLOR_LinearRGB(Value / Ratio, 1, 1, C);
		ysxCIMG_DRAW_FillFlood(Bar, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { Bar = ysxCIMG_AddBorder(Bar, Borderx, Bordery, C); }		
	}
	return(Bar);
}
CImg<uint8_t> ysxCIMG_ValueBar(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis)
{
	CImg<uint8_t> Bar;
	Value = Value * Ratio;
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { Bar = CImg<uint8_t>::CImg(Value - Bordery, Width - Borderx, 1, 3, 0); }
		else { Bar = CImg<uint8_t>::CImg(Width - Bordery, Value - Borderx, 1, 3, 0); }
		uint8_t C[3]; ysxCOLOR_LinearRGB(Value / Ratio, 1, 1, C);
		CImg<uint8_t> BarFill = Bar;
		ysxCIMG_DRAW_FillFlood(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = ysxCIMG_AddBorder(Bar, Borderx, Bordery, C); }
		if (xAxis) { if (Value < 0) { ysxCIMG_JoinImg(Bar, BarFill, 0); } if (Value >= 0) { ysxCIMG_JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { ysxCIMG_JoinImg(Bar, BarFill, 1); } if (Value >= 0) { ysxCIMG_JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}
CImg<uint8_t> ysxCIMG_ValueBar(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* C)
{
	CImg<uint8_t> Bar;
	Value = Value * Ratio;
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<uint8_t> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		else { CImg<uint8_t> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		CImg<uint8_t> BarFill = Bar;
		ysxCIMG_DRAW_FillFlood(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = ysxCIMG_AddBorder(Bar, Borderx, Bordery, C); }
		if (xAxis) { if (Value < 0) { ysxCIMG_JoinImg(Bar, BarFill, 0); } if (Value >= 0) { ysxCIMG_JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { ysxCIMG_JoinImg(Bar, BarFill, 1); } if (Value >= 0) { ysxCIMG_JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}

// CREATE A SQUARE MOSAIC:
template <class T_>
CImg<uint8_t> ysxCIMG_SqrMatrix(std::vector<T_>& V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	const uint32_t S = V.size(); const double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i; (Sqrt / j) == 1 ? i = j : i = ceil(Sqrt); // SQUARE SIDE SIZE
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3];
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		if (std::is_floating_point<T_>::value) { ysxCOLOR_LinearRGB(V[m], 1, 1, C); }
		else { ysxCOLOR_LinearRGB(V[m] / (float)(pow(256, sizeof(T_)) - 1), 1, 1, C);	}
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
template <class T_>
CImg<uint8_t> ysxCIMG_SqrMatrix(std::vector<T_>& V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	if (j > S) { j = S; } if (j < 1) { j = 1; }
	uint16_t i = ceil(S / (float)j);
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3];
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		if (std::is_floating_point<T_>::value) { ysxCOLOR_LinearRGB(V[m], 1, 1, C); }
		else { ysxCOLOR_LinearRGB(V[m] / (float)(pow(256, sizeof(T_)) - 1), 1, 1, C); }
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
template <class T_>
CImg<uint8_t> ysxCIMG_SqrMatrixGray(std::vector<T_>& V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i; (Sqrt / j) == 1 ? i = j : i = ceil(Sqrt);
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3]; uint8_t Byte;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		if (std::is_floating_point<T_>::value) { C[0] = V[m] * 255; C[1] = V[m] * 255; C[2] = V[m] * 255; }
		else { Byte = (V[m] / (float)(pow(256, sizeof(T_)) - 1)) * 255; C[0] = Byte; C[1] = Byte; C[2] = Byte; }
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
template <class T_>
CImg<uint8_t> ysxCIMG_SqrMatrixGray(std::vector<uint8_t>& V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	if (j > S) { j = S; } if (j < 1) { j = 1; }
	uint16_t i = ceil(S / (float)j);
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3]; uint8_t Byte;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		else { Txt = " "; }

		if (std::is_floating_point<T_>::value) { C[0] = V[m] * 255; C[1] = V[m] * 255; C[2] = V[m] * 255; }
		else { Byte = (V[m] / (float)(pow(256, sizeof(T_)) - 1)) * 255; C[0] = Byte; C[1] = Byte; C[2] = Byte; }
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
CImg<uint8_t> ysxCIMG_SqrMatrix(CImg<uint8_t>& V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint16_t j = V.width(), i = V.height();
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3];
	for (uint32_t m = 0; m < j; ++m)
	{
		for (uint32_t n = 0; n < i; ++n)
		{
			ysxCIMG_BitmapRGBuc(V, n, m, C);
			if (Text) { Txt = std::to_string(n + (j * m)) + ":\n" + std::to_string((C[0] + C[1] + C[2]) / 3.0); }
			Squares.draw_image(n * x, m * y, ysxCIMG_RectCell(x, y, 1, 1, Txt, C));
		}
	}
	return(Squares);
}

// ADD VERTEX:
void ysxCIMG_AddVert(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t Size, uint8_t* C)
{
	uint16_t px, py;
	for (uint16_t Row = 0; Row <= Size; ++Row)
	{
		for (int Col = floor((Size * 0.5) - Size); Col < Size * 0.5; ++Col)
		{
			px = Col + x, py = Row + y;
			Img.draw_point(px, py, C);
		}
	}
}


// #################################################


// ###################################
// ############## CLASSES ##############
// ###################################


// #################################################


#endif
