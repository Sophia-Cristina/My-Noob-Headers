#pragma once

#ifndef YSXCIUTILS_H
#define YSXCIUTILS_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### CImg for utils, like GUI, interfaces, human-readable stuffs..
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################

// ############################################################################################################################################
// ############## TRANSFORMERS / MODIFICATORS:

// JOIN IMAGES (APPEND):
CImg<uint8_t> JoinImg(CImg<uint8_t> I1, CImg<uint8_t> I2, bool RightOrDown)
{
	int W = 1, H = 1;
	if (!RightOrDown) { W = I1.width() + I2.width(); if (I1.height() >= I2.height()) { H = I1.height(); } else { H = I2.height(); } }
	else { H = I1.height() + I2.height(); if (I1.width() >= I2.width()) { W = I1.width(); } else { W = I2.width(); } }
	CImg<uint8_t> I3(W, H, 1, 3, 0);
	if (!RightOrDown) { I3.draw_image(0, 0, I1); I3.draw_image(I1.width(), 0, I2); }
	else { I3.draw_image(0, 0, I1); I3.draw_image(0, I1.height(), I2); }
	return(I3);
}

// RESIZE:
void Resize(CImg<uint8_t>& Img, uint16_t xrs, uint16_t yrs, uint8_t Interpolation)
{
	if (Interpolation < 1) { Interpolation = 1; } if (Interpolation > 6) { Interpolation = 6; }
	Img.resize(xrs, yrs, 3, 3, Interpolation, 0, 0, 0, 0, 0);
}

// INVERT:
void Invert(CImg<uint8_t>& Img)
{
	uint16_t H = Img.height(), W = Img.width();
	for (uint16_t n = 0; n < H; ++n)
	{
		for (uint16_t m = 0; m < W; ++m)
		{
			Point3D<uint8_t> RGB = BitmapRGB(Img, m, n);
			uint8_t C[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z }; Img.draw_point(m, n, C);
		}
	}
}

// FILL SOME PLACE:
void FillArea(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint8_t* Color) { Img.draw_fill(x, y, Color, 1, 1, false); }

// EXPAND IMAGE BORDERS:
// (char as byte, '0' to '8', '0 = center', imagine an octagon, '1 = top side', clock-wise, '2 = top-right side', and that is how it goes)
CImg<uint8_t> ExpandImg(CImg<uint8_t> Img, uint16_t Size, char Side)
{
	// W = Width | H = height | e = Ex | i = Img | m = mid
	int Wi = Img.width(), Hi = Img.height(), Wim = Wi * 0.5, Him = Hi * 0.5;
	CImg<uint8_t> Ex(Wi + Size * 2, Hi + Size * 2, 1, 3, 0);
	int We = Ex.width(), He = Ex.height(), Wem = We * 0.5, Hem = He * 0.5;
	
	if (Side == 0) { Ex.draw_image(Wem - Wim, Hem - Him, Img); }  // Center
	else if (Side == 1) { Ex.draw_image(Wem - Wim, 0, Img); } // Top
	else if (Side == 2) { Ex.draw_image(We - Wi, 0, Img); } // Top-Right
	else if (Side == 3) { Ex.draw_image(We - Wi, Hem - Him, Img); } // Right
	else if (Side == 4) { Ex.draw_image(We - Wi, He - Hi, Img); } // Bottom-Right
	else if (Side == 5) { Ex.draw_image(Wem - Wim, He - Hi, Img); } // Bottom
	else if (Side == 6) { Ex.draw_image(0, He - Hi, Img); } // Bottom-Left
	else if (Side == 7) { Ex.draw_image(0, Hem - Him, Img); } // Left
	else { Ex.draw_image(0, 0, Img); } // Top-Left

	return(Ex);
}

// ############################################################################################################################################
// ############## TEXTOS:

// ############################################################################################################################################
// ############## GRAFICOS:

// BARS:
// If xAxis, then 'a = x0', 'b = x1', and 'Axis = y'
// If !xAxis, then 'a = y0', 'b = y1', and 'Axis = x'
void DrawBar(CImg<uint8_t>& Img, bool xAxis, uint16_t a, uint16_t b, uint16_t Thickness, uint16_t Axis, uint8_t* Color)
{
	if (Thickness < 1) { Thickness = 1; }
	if (xAxis) { for (short C = 0; C < Thickness; ++C) { Img.draw_line(a, Axis + C, b, Axis + C, Color); } }
	else { for (short C = 0; C < Thickness; ++C) { Img.draw_line(Axis + C, a, Axis + C, b, Color); } }
}

// ADD BORDERS (TALVEZ FILL ARRUMARIA TUDO ISSO BEM FÁCIL):
CImg<uint8_t> AddBorder(CImg<uint8_t> Img, uint16_t BorderX, uint16_t BorderY, uint8_t* Color)
{
	uint16_t x = Img.width() + (BorderY * 2), y = Img.height() + (BorderX * 2);
	CImg<uint8_t> R(x, y, 1, 3, 0);
	R.draw_image(BorderX, BorderY, Img);
	DrawBar(R, false, 0, y, BorderY, 0, Color);
	DrawBar(R, false, 0, y, BorderY, x - BorderY, Color);
	DrawBar(R, true, BorderY, x - (BorderY + 1), BorderX, 0, Color);
	DrawBar(R, true, BorderY, x - (BorderY + 1), BorderX, y - BorderX, Color);
	return (R);
}

// ENCAIXOTAR:
void Box(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t* Color)
{
	DrawBar(Img, false, y, y + sizey, 1, x, Color);
	DrawBar(Img, false, y, y + sizey, 1, x + sizex, Color);
	DrawBar(Img, true, x, x + sizex, 1, y, Color);
	DrawBar(Img, true, x, x + sizex, 1, y + sizey, Color);
}

// BOX MATRIX:
void BoxMatrix(CImg<uint8_t>& Img, uint16_t Border, uint16_t Divx, uint16_t Divy, uint8_t* Color)
{
	uint16_t Height = Img.height(), Width = Img.width();
	DrawBar(Img, false, Border, Height - Border, Border, 0, Color);
	DrawBar(Img, false, Border, Height - Border, Border, Width - Border, Color);
	DrawBar(Img, true, 0, Width, Border, 0, Color);
	DrawBar(Img, true, 0, Width, Border, Height - Border, Color);
	if (Divx == 0) { Divx = 1; } if (Divy == 0) { Divy = 1; } // No division by zero!
	double HD = (double)Height / Divy, WD = (double)Width / Divx;
	for (int n = 1; n < Divx; ++n) { DrawBar(Img, false, Border, Height - Border, Border, n * WD - Border * 0.5, Color); }
	for (int n = 1; n < Divy; ++n) { DrawBar(Img, true, Border, Width - Border, Border, n * HD - Border * 0.5, Color); }
}

// CRIA IMAGEM DE UM RETANGULO ENCAIXOTADO E COM TEXTO (OBS.: A DUAS BORDAS DEVEM SER MAIOR QUE ZERO PARA TER BORDAS, PREGUIÇA DE FAZER UM FUNÇÃO SÓ PARA DESENHAR ISSO):
CImg<uint8_t> RetCell(uint16_t x, uint16_t y, uint16_t Borderx, uint16_t Bordery, std::string Text, uint8_t* Color)
{
	if (x <= Borderx) { x = Borderx + 1; } if (y <= Bordery) { y = Bordery + 1; }
	CImg<uint8_t> Cell(x - Bordery, y - Borderx, 1, 3, 0);
	FillArea(Cell, x * 0.5, y * 0.5, Color);
	Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
	if (Borderx > 0 && Bordery > 0) { Cell = AddBorder(Cell, Borderx, Bordery, Color); }
	Color[0] = 255 - Color[0];
	AddText(Cell, x * 0.25, y * 0.25, Text, Color);
	return(Cell);
}

// CRIA IMAGEM DE UMA BARRA BASEADO NUM VALOR (ABOSLUTO):
CImg<uint8_t> ValueBarAbs(int Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* Color)
{
	CImg<uint8_t> Bar;
	Value = fabs(Value * Ratio);
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<uint8_t> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		else { CImg<uint8_t> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		FillArea(Bar, Bar.width() * 0.5, Bar.height() * 0.5, Color);
		Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
		if (Borderx > 0 && Bordery > 0) { Bar = AddBorder(Bar, Borderx, Bordery, Color); }
	}
	return(Bar);
}
CImg<uint8_t> ValueBarAbs(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis)
{
	CImg<uint8_t> Bar;
	Value = fabs(Value * Ratio);
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<uint8_t> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		else { CImg<uint8_t> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		 uint8_t C[3]; LinearRGBuc(Value / Ratio, 1, 1, C);
		FillArea(Bar, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { Bar = AddBorder(Bar, Borderx, Bordery, C); }		
	}
	return(Bar);
}
CImg<uint8_t> ValueBar(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis)
{
	CImg<uint8_t> Bar;
	Value = Value * Ratio;
	uint16_t Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<uint8_t> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		else { CImg<uint8_t> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		uint8_t C[3]; LinearRGBuc(Value / Ratio, 1, 1, C);
		CImg<uint8_t> BarFill = Bar;
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = AddBorder(Bar, Borderx, Bordery, C); }
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}
CImg<uint8_t> ValueBar(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* Color)
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
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, Color);
		Color[0] = 255 - Color[0]; Color[1] = 255 - Color[1]; Color[2] = 255 - Color[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = AddBorder(Bar, Borderx, Bordery, Color); }
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}

// CRIA MATRIZ COM A FUNÇÃO DE CRIAR QUADRADOS:
CImg<uint8_t> SqrMatrix(std::vector<double> V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size(); double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i; (Sqrt / j) == 1 ? i = j : i = ceil(sqrt(S)); // SQUARE SIDE SIZE
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	uint16_t cj = 0, ci = 0; // Count i or j
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); } else { Txt = " "; }
		LinearRGBuc((V[m] * 1.0) / MaxVec(V), 1, 1, C);
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj; if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrix(std::vector<double> V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	if (j > S) { j = S; } if (j < 1) { j = 1; }
	uint16_t i = ceil(S / (j * 1.0));
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0); // VER SE O (+1) NÃO DA ERRO!
	uint16_t cj = 0, ci = 0;
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (int m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); } else { Txt = " "; }
		LinearRGBuc((V[m] * 1.0) / MaxVec(V), 1, 1, C);
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj;
		if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrix(std::vector<uint8_t> V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i;
	(Sqrt / j) == 1 ? i = j : i = ceil(sqrt(S));
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	uint16_t cj = 0, ci = 0;
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); } else { Txt = " "; }
		LinearRGBuc(V[m] / 255.0, 1, 1, C);
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj; if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrix(std::vector<uint8_t> V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	if (j > S) { j = S; } if (j < 1) { j = 1; }
	uint16_t i = ceil(S / (j * 1.0));
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	int cj = 0, ci = 0;
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); } else { Txt = " "; }
		LinearRGBuc(V[m] / 255.0, 1, 1, C);
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj; if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrixGray(std::vector<uint8_t> V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i;
	(Sqrt / j) == 1 ? i = j : i = ceil(sqrt(S));
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	uint16_t cj = 0, ci = 0;
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); } else { Txt = " "; }
		C[0] = V[m]; C[1] = V[m]; C[2] = V[m];
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj; if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrixGray(std::vector<uint8_t> V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint32_t S = V.size();
	if (j > S) { j = S; } if (j < 1) { j = 1; }
	uint16_t i = ceil(S / (j * 1.0));
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	uint16_t cj = 0, ci = 0;
	std::string Txt; uint8_t C[3];
	uint16_t Cellj = 0, Celli = 0;
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		else { Txt = " "; }
		C[0] = V[m]; C[1] = V[m]; C[2] = V[m];
		Cellj = cj * x, Celli = ci * y;
		Squares.draw_image(Cellj, Celli, RetCell(x, y, 1, 1, Txt, C));
		++cj; if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<uint8_t> SqrMatrix(CImg<uint8_t> V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint16_t j = V.width(), i = V.height();
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt; uint8_t C[3];
	uint16_t cj = 0, ci = 0;
	for (uint32_t m = 0; m < j; ++m)
	{
		for (uint32_t n = 0; n < i; ++n)
		{
			BitmapRGBuc(V, n, m, C);
			if (Text) { Txt = std::to_string(n + (j * m)) + ":\n" + std::to_string((C[0] + C[1] + C[2]) / 3.0); } else { Txt = " "; }
			cj = n * x, ci = m * y;
			Squares.draw_image(cj, ci, RetCell(x, y, 1, 1, Txt, C));
		}
	}
	return(Squares);
}

// ADD VERTICE:
void AddVert(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t Size, uint8_t* Color)
{
	for (uint16_t DrawLine = 0; DrawLine <= Size; ++DrawLine)
	{
		for (int Draw = floor((Size * 0.5) - Size); Draw < floor(Size - (Size * 0.5)); ++Draw)
		{
			int Drawx = Draw + x, Drawy = DrawLine + y;
			if (InImg(Img, Drawx, Drawy)) { Img.draw_point(Drawx, Drawy, Color); }
		}
	}
}

// ################################################# FIM ####################################################################################

#endif // SCPARSE_