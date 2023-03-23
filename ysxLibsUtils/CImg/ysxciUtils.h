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
// !!!	
// !!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################

// ############################################################################################################################################
// ############## TRANSFORMERS / MODIFICATORS:

// JOIN IMAGES (APPEND):
CImg<uint8_t> JoinImg(CImg<uint8_t>& I1, CImg<uint8_t>& I2, bool RightOrDown)
{
	uint16_t W = 1, H = 1;
	if (!RightOrDown) { W = I1.width() + I2.width(); I1.height() > I2.height() ? H = I1.height() : H = I2.height(); }
	else { H = I1.height() + I2.height(); I1.width() > I2.width() ? W = I1.width() : W = I2.width(); }
	CImg<uint8_t> I3(W, H, 1, 3, 0); I3.draw_image(0, 0, I1);
	RightOrDown ? I3.draw_image(0, I1.height(), I2) : I3.draw_image(I1.width(), 0, I2);	
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
			Point3D<uint8_t> RGB = ysxCIMG_CLR_BitmapRGB(Img, m, n);
			uint8_t C[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z }; Img.draw_point(m, n, C);
		}
	}
}

// REDO IMAGE WITH SPECIFIC COLOR (OR ELSE, IT IS BLACK):
void FillAlpha(CImg<uint8_t>& Img, uint8_t* Clr = nullptr)
{
	Img = CImg<uint8_t>::CImg(Img.width(), Img.height(), 1, 4, 0);
	if (!Clr) { uint8_t C[] = { 0, 0, 0, 0 }; Img.draw_fill(1, 1, C, 1, 1); }
	else { Img.draw_fill(1, 1, Clr, 1, 1); }
} // Maybe it is already black

// Fill / clean entire image, but by drawing a rectangle over it:
void FillRect(CImg<uint8_t>& Img) { uint8_t c[] = { 0, 0, 0 }; Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, c); }
void FillRect(CImg<uint8_t>& Img, uint8_t C[3]) { Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, C); }

// FILL (PAINT BUCKET) SOME PLACE:
void FillArea(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint8_t* C) { Img.draw_fill(x, y, C, 1, 1, false); }

// EXPAND IMAGE BORDERS:
// (char as byte, '0' to '8', '0 = center', imagine an octagon, '1 = top side', clock-wise, '2 = top-right side', and that is how it goes)
CImg<uint8_t> ExpandImg(CImg<uint8_t>& Img, uint8_t Size, uint8_t Side)
{
	// W = Width | H = height | e = Ex | i = Img | m = mid
	size_t Wi = Img.width(), Hi = Img.height(), Wim = (size_t)(Wi * 0.5), Him = (size_t)(Hi * 0.5);
	CImg<uint8_t> Ex(Wi + Size * 2, Hi + Size * 2, 1, 3, 0);
	size_t We = Ex.width(), He = Ex.height(), Wem = (size_t)(We * 0.5), Hem = (size_t)(He * 0.5);
	
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
// If 'xAxis', then 'a = x0', 'b = x1, Axis = y'
void DrawBar(CImg<uint8_t>& Img, bool xAxis, uint16_t a, uint16_t b, uint16_t Size, uint16_t Axis, uint8_t* Color)
{
	if (!Size) { Size = 1; }
	if (xAxis) { for (size_t C = 0; C < Size; ++C) { Img.draw_line(a, Axis + C, b, Axis + C, Color); } }
	else { for (size_t C = 0; C < Size; ++C) { Img.draw_line(Axis + C, a, Axis + C, b, Color); } }
}

// ADD BORDERS:
// !!! Mudar funções e usar as operações que tem dentro delas.
CImg<uint8_t> AddBorder(CImg<uint8_t>& Img, uint16_t BorderX, uint16_t BorderY, uint8_t* C)
{
	uint16_t x = Img.width() + (BorderY * 2), y = Img.height() + (BorderX * 2);
	CImg<uint8_t> R(x, y, 1, 3, 0);
	R.draw_image(BorderX, BorderY, Img);
	DrawBar(R, false, 0, y, BorderY, 0, C);
	DrawBar(R, false, 0, y, BorderY, x - BorderY, C);
	DrawBar(R, true, BorderY, x - (BorderY + 1), BorderX, 0, C);
	DrawBar(R, true, BorderY, x - (BorderY + 1), BorderX, y - BorderX, C);
	return (R);
}

// DRAW BOX, RECTANGLE (NOT FILLED):
void Box(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint8_t* C)
{
	//Img.draw_rectangle(x, y, sizex, sizey, C); // <-- USAR ESSE!
	DrawBar(Img, false, y, y + sizey, 1, x, C);
	DrawBar(Img, false, y, y + sizey, 1, x + sizex, C);
	DrawBar(Img, true, x, x + sizex, 1, y, C);
	DrawBar(Img, true, x, x + sizex, 1, y + sizey, C);
}

// BOX MATRIX:
void BoxMatrix(CImg<uint8_t>& Img, uint16_t Border, uint16_t Divx, uint16_t Divy, uint8_t* C)
{
	uint16_t Height = Img.height(), Width = Img.width();
	DrawBar(Img, false, Border, Height - Border, Border, 0, C);
	DrawBar(Img, false, Border, Height - Border, Border, Width - Border, C);
	DrawBar(Img, true, 0, Width, Border, 0, C);
	DrawBar(Img, true, 0, Width, Border, Height - Border, C);
	if (Divx == 0) { Divx = 1; } if (Divy == 0) { Divy = 1; } // No division by zero!
	double HD = (double)Height / Divy, WD = (double)Width / Divx;
	for (int n = 1; n < Divx; ++n) { DrawBar(Img, false, Border, Height - Border, Border, n * WD - Border * 0.5, C); }
	for (int n = 1; n < Divy; ++n) { DrawBar(Img, true, Border, Width - Border, Border, n * HD - Border * 0.5, C); }
}

// CRIA IMAGEM DE UM RETANGULO ENCAIXOTADO E COM TEXTO (OBS.: A DUAS BORDAS DEVEM SER MAIOR QUE ZERO PARA TER BORDAS, PREGUIÇA DE FAZER UM FUNÇÃO SÓ PARA DESENHAR ISSO):
CImg<uint8_t> RetCell(uint16_t x, uint16_t y, uint16_t Borderx, uint16_t Bordery, std::string Text, uint8_t* C)
{
	if (x <= Borderx) { x = Borderx + 1; } if (y <= Bordery) { y = Bordery + 1; }
	CImg<uint8_t> Cell(x - Bordery, y - Borderx, 1, 3, 0);
	FillArea(Cell, x * 0.5, y * 0.5, C);
	C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
	if (Borderx > 0 && Bordery > 0) { Cell = AddBorder(Cell, Borderx, Bordery, C); }
	C[0] = 255 - C[0];
	ysxCIMG_AddText(Cell, x * 0.25, y * 0.25, Text, C);
	return(Cell);
}

// CRIA IMAGEM DE UMA BARRA BASEADO NUM VALOR (ABOSLUTO):
CImg<uint8_t> ValueBarAbs(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* C)
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
		FillArea(Bar, Bar.width() * 0.5, Bar.height() * 0.5, C);
		if (Borderx > 0 && Bordery > 0) { Bar = AddBorder(Bar, Borderx, Bordery, InvC); }
	}
	return(Bar);
}
CImg<uint8_t> ValueBarAbs(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis)
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
		ysxCIMG_CLR_LinearRGBuc(Value / Ratio, 1, 1, C);
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
		if (xAxis) { Bar = CImg<uint8_t>::CImg(Value - Bordery, Width - Borderx, 1, 3, 0); }
		else { Bar = CImg<uint8_t>::CImg(Width - Bordery, Value - Borderx, 1, 3, 0); }
		uint8_t C[3]; ysxCIMG_CLR_LinearRGBuc(Value / Ratio, 1, 1, C);
		CImg<uint8_t> BarFill = Bar;
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = AddBorder(Bar, Borderx, Bordery, C); }
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}
CImg<uint8_t> ValueBar(uint16_t Width, double Value, double Ratio, uint16_t Borderx, uint16_t Bordery, bool xAxis, uint8_t* C)
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
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, C);
		C[0] = 255 - C[0]; C[1] = 255 - C[1]; C[2] = 255 - C[2];
		if (Borderx > 0 && Bordery > 0) { BarFill = AddBorder(Bar, Borderx, Bordery, C); }
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		else { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}

// CREATE A SQUARE MOSAIC:
template <class T_>
CImg<uint8_t> SqrMatrix(std::vector<T_>& V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	const uint32_t S = V.size(); const double Sqrt = sqrt(S);
	uint16_t j = round(Sqrt), i; (Sqrt / j) == 1 ? i = j : i = ceil(Sqrt); // SQUARE SIDE SIZE
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3];
	for (uint32_t m = 0; m < S; ++m)
	{
		if (Text) { Txt = std::to_string(m) + ":\n" + std::to_string(V[m]); }
		if (std::is_floating_point<T_>::value) { ysxCIMG_CLR_LinearRGBuc(V[m], 1, 1, C); }
		else { ysxCIMG_CLR_LinearRGBuc(V[m] / (float)(pow(256, sizeof(T_)) - 1), 1, 1, C);	}
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
template <class T_>
CImg<uint8_t> SqrMatrix(std::vector<T_>& V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
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
		if (std::is_floating_point<T_>::value) { ysxCIMG_CLR_LinearRGBuc(V[m], 1, 1, C); }
		else { ysxCIMG_CLR_LinearRGBuc(V[m] / (float)(pow(256, sizeof(T_)) - 1), 1, 1, C); }
		Squares.draw_image((m % j) * x, floor((float)m / j) * y, RetCell(x, y, 1, 1, Txt, C));
	}
	return(Squares);
}
template <class T_>
CImg<uint8_t> SqrMatrixGray(std::vector<T_>& V, uint16_t x, uint16_t y, bool Text = 0)
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
CImg<uint8_t> SqrMatrixGray(std::vector<uint8_t>& V, uint16_t x, uint16_t y, uint16_t j, bool Text = 0)
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
CImg<uint8_t> SqrMatrix(CImg<uint8_t>& V, uint16_t x, uint16_t y, bool Text = 0)
{
	if (x < 3) { x = 3; } if (y < 3) { y = 3; }
	uint16_t j = V.width(), i = V.height();
	CImg<uint8_t> Squares(j * x, i * y, 1, 3, 0);
	std::string Txt = " "; uint8_t C[3];
	for (uint32_t m = 0; m < j; ++m)
	{
		for (uint32_t n = 0; n < i; ++n)
		{
			ysxCIMG_CLR_BitmapRGBuc(V, n, m, C);
			if (Text) { Txt = std::to_string(n + (j * m)) + ":\n" + std::to_string((C[0] + C[1] + C[2]) / 3.0); }
			Squares.draw_image(n * x, m * y, RetCell(x, y, 1, 1, Txt, C));
		}
	}
	return(Squares);
}

// ADD VERTEX:
void AddVert(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint16_t Size, uint8_t* C)
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

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
