#pragma once

#ifndef YSXCIUTILS_H
#define YSXCIUTILS_H

using namespace cimg_library;

// ###################################
// ############## FUNÇÕES #######
// ###################################
// ############## DECLARAÇÕES:



// ###################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## TRANSFORMADORES / MODIFICADORES:

// UNE IMAGEM:
CImg<unsigned char> JoinImg(CImg<unsigned char> I1, CImg<unsigned char> I2, bool RightOrDown)
{
	int W = 1, H = 1;
	if (!RightOrDown) { W = I1.width() + I2.width(); if (I1.height() >= I2.height()) { H = I1.height(); } else { H = I2.height(); } }
	else { H = I1.height() + I2.height(); if (I1.width() >= I2.width()) { W = I1.width(); } else { W = I2.width(); } }
	CImg<unsigned char> I3(W, H, 1, 3, 0);
	if (!RightOrDown) { I3.draw_image(0, 0, I1); I3.draw_image(I1.width(), 0, I2); }
	else { I3.draw_image(0, 0, I1); I3.draw_image(0, I1.height(), I2); }
	return(I3);
}

// RESIZE:
void Resize(CImg<unsigned char>& Img, int xrs, int yrs, int Interpolation)
{
	if (Interpolation < 1) { Interpolation = 1; } if (Interpolation > 6) { Interpolation = 6; }
	Img.resize(xrs, yrs, 3, 3, Interpolation, 0, 0, 0, 0, 0);
}

// INVERT:
void Invert(CImg<unsigned char>& Img)
{
	for (int n = 0; n < Img.height(); ++n)
	{
		for (int m = 0; m < Img.width(); ++m) { Point3D RGB = BitmapRGB(Img, m, n); unsigned char Color[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z }; Img.draw_point(m, n, Color); }
	}
}

// FILL CERTO LUGAR:
void FillArea(CImg<unsigned char>& Img, int x, int y, int R, int G, int B)
{ unsigned char color[] = { R, G, B }; Img.draw_fill(x, y, color, 1, 1, false); }

// EXPAND IMAGE BORDERS:
// (char as byte, '0' to '8', '0 = center', imagine an octagon, '1 = top side', clock-wise, '2 = top-right side', and that is how it goes)
CImg<unsigned char> ExpandImg(CImg<unsigned char> Img, int Size, char Side)
{
	// W = Width | H = height | e = Ex | i = Img | m = mid
	int Wi = Img.width(), Hi = Img.height(), Wim = Wi * 0.5, Him = Hi * 0.5;
	CImg<unsigned char> Ex(Wi + Size * 2, Hi + Size * 2, 1, 3, 0);
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
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TEXTOS:

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GRAFICOS:

// BARRAS (MODIFIQUE PELA LINE DO CIMG PARA FICAR MAIS RAPIDO):
void AdcBarra(CImg<unsigned char>& Img, bool Eixox, int a, int b, int Espsr, int Eixo, int R, int G, int B) // bool Eixox, int a, int b, int Espessura, int Eixo, int Transparencia (%), int R, int G, int B (R)
{
	if (Espsr < 1) { Espsr = 1; }
	int Espessura = Espsr, EspCount = 0;
	if (Eixox == true)
	{
		for (EspCount = 1; EspCount <= Espessura; ++EspCount)
		{
			for (int x = a; x < b + 1; ++x)
			{
				unsigned char color[] = { R, G, B };
				Img.draw_point(x, Eixo + EspCount - 1, color);
			}
		}
	}
	else
	{
		for (EspCount = 1; EspCount <= Espessura; ++EspCount)
		{
			for (int y = a; y < b + 1; ++y)
			{
				unsigned char color[] = { R, G, B };
				Img.draw_point(Eixo + EspCount - 1, y, color);
			}
		}
	}
}

// ADICIONAR BORDAS:
CImg<unsigned char> AdcBorda(CImg<unsigned char> Img, int BordaX, int BordaY, int R, int G, int B)
{
	int GradeX = Img.width(), GradeY = Img.height();
	int Sizex = GradeX + (BordaY * 2), Sizey = GradeY + (BordaX * 2);
	CImg<unsigned char> ThisImg(Sizex, Sizey, 1, 3, 0);
	ThisImg.draw_image(BordaX, BordaY, Img);
	AdcBarra(ThisImg, false, 0, Sizey, BordaY, 0, R, G, B);
	AdcBarra(ThisImg, false, 0, Sizey, BordaY, Sizex - BordaY, R, G, B);
	AdcBarra(ThisImg, true, BordaY, Sizex - (BordaY + 1), BordaX, 0, R, G, B);
	AdcBarra(ThisImg, true, BordaY, Sizex - (BordaY + 1), BordaX, Sizey - BordaX, R, G, B);
	return (ThisImg);
}

// ENCAIXOTAR:
void Box(CImg<unsigned char>& Img, int x1, int y1, int sizex, int sizey, int R, int G, int B)
{
	AdcBarra(Img, false, y1, y1 + sizey, 1, x1, R, G, B);
	AdcBarra(Img, false, y1, y1 + sizey, 1, x1 + sizex, R, G, B);
	AdcBarra(Img, true, x1, x1 + sizex, 1, y1, R, G, B);
	AdcBarra(Img, true, x1, x1 + sizex, 1, y1 + sizey, R, G, B);
}

// CRIA IMAGEM DE UM RETANGULO ENCAIXOTADO E COM TEXTO (OBS.: A DUAS BORDAS DEVEM SER MAIOR QUE ZERO PARA TER BORDAS, PREGUIÇA DE FAZER UM FUNÇÃO SÓ PARA DESENHAR ISSO):
CImg<unsigned char> RetCell(int Sizex, int Sizey, int Borderx, int Bordery, string Text, unsigned char Color[3])
{
	if (Sizex <= Borderx) { Sizex = Borderx + 1; } if (Sizey <= Bordery) { Sizey = Bordery + 1; }
	CImg<unsigned char> Cell(Sizex - Bordery, Sizey - Borderx, 1, 3, 0);
	if (Borderx > 0 && Bordery > 0) { Cell = AdcBorda(Cell, Borderx, Bordery, 255 - Color[0], 255 - Color[1], 255 - Color[2]); }
	FillArea(Cell, Sizex * 0.5, Sizey * 0.5, Color[0], Color[1], Color[2]);
	AdcTexto(Cell, Sizex * 0.25, Sizey * 0.25, Text, 255 - Color[0], 255 - Color[1], 255 - Color[2]);
	return(Cell);
}

// CRIA IMAGEM DE UMA BARRA BASEADO NUM VALOR (ABOSLUTO):
CImg<unsigned char> ValueBarAbs(int Width, double Value, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> Bar;
	Value = fabs(Value * Ratio);
	int Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<unsigned char> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		if (!xAxis) { CImg<unsigned char> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		if (Borderx > 0 && Bordery > 0) { Bar = AdcBorda(Bar, Borderx, Bordery, 255 - Color[0], 255 - Color[1], 255 - Color[2]); }
		FillArea(Bar, Bar.width() * 0.5, Bar.height() * 0.5, Color[0], Color[1], Color[2]);
	}
	return(Bar);
}
CImg<unsigned char> ValueBarAbs(int Width, double Value, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<unsigned char> Bar;
	Value = fabs(Value * Ratio);
	int Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<unsigned char> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		if (!xAxis) { CImg<unsigned char> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		Point3D Color = LinearRGB(Value / Ratio, 1, 1);
		if (Borderx > 0 && Bordery > 0) { Bar = AdcBorda(Bar, Borderx, Bordery, 255 - Color.x, 255 - Color.y, 255 - Color.z); }
		FillArea(Bar, Bar.width() * 0.5, Bar.height() * 0.5, Color.x, Color.y, Color.z);
	}
	return(Bar);
}
CImg<unsigned char> ValueBar(int Width, double Value, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<unsigned char> Bar;
	Value = Value * Ratio;
	int Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<unsigned char> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		if (!xAxis) { CImg<unsigned char> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		Point3D Color = LinearRGB(Value / Ratio, 1, 1);
		CImg<unsigned char> BarFill = Bar;
		if (Borderx > 0 && Bordery > 0) { BarFill = AdcBorda(Bar, Borderx, Bordery, 255 - Color.x, 255 - Color.y, 255 - Color.z); }
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, Color.x, Color.y, Color.z);
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		if (!xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}
CImg<unsigned char> ValueBar(int Width, double Value, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> Bar;
	Value = Value * Ratio;
	int Border = 0; if (xAxis) { Border = Borderx; } else { Border = Bordery; }
	if (Value >= 1 + 2 * Border)
	{
		if (Width <= Borderx) { Width = Borderx + 1; } if (Value <= Bordery) { Value = Bordery + 1; }
		if (xAxis) { CImg<unsigned char> XIMG(Value - Bordery, Width - Borderx, 1, 3, 0); Bar = XIMG; }
		if (!xAxis) { CImg<unsigned char> YIMG(Width - Bordery, Value - Borderx, 1, 3, 0); Bar = YIMG; }
		CImg<unsigned char> BarFill = Bar;
		if (Borderx > 0 && Bordery > 0) { BarFill = AdcBorda(Bar, Borderx, Bordery, 255 - Color[0], 255 - Color[1], 255 - Color[2]); }
		FillArea(BarFill, Bar.width() * 0.5, Bar.height() * 0.5, Color[0], Color[1], Color[2]);
		if (xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 0); } if (Value >= 0) { JoinImg(BarFill, Bar, 0); } }
		if (!xAxis) { if (Value < 0) { JoinImg(Bar, BarFill, 1); } if (Value >= 0) { JoinImg(BarFill, Bar, 1); } }
	}
	return(Bar);
}

// CRIA MATRIZ COM A FUNÇÃO DE CRIAR QUADRADOS:
CImg<unsigned char> SqrMatrix(vector<CellBool> Matrix, int Sizex, int Sizey, bool Text, bool CleanFalse, unsigned char Color[3])
{
	if (Sizex < 3) { Sizex = 3; } if (Sizey < 3) { Sizey = 3; }
	int i, j; MaxSizeBoolMatrix(Matrix, i, j);
	CImg<unsigned char> Squares((j + 1) * Sizex, (i + 1) * Sizey, 1, 3, 0);
	for (int m = 0; m < Matrix.size(); ++m)
	{
		string Txt; if (Text) { Txt = to_string(m); } else { Txt = " "; }
		unsigned char Clr[] = { Color[0], Color[1], Color[2] };
		if (!Matrix[m].b) { Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2]; }
		if (Matrix[m].b || (!Matrix[m].b && !CleanFalse))
		{
			CImg<unsigned char> Square = RetCell(Sizex, Sizey, 1, 1, Txt, Clr);
			int Cellj = Matrix[m].j * Sizex, Celli = Matrix[m].i * Sizey;
			Squares.draw_image(Cellj, Celli, Square);
		}
	}

	return(Squares);
}
CImg<unsigned char> SqrMatrix(vector<double> Matrix, int Sizex, int Sizey, bool Text)
{
	if (Sizex < 3) { Sizex = 3; } if (Sizey < 3) { Sizey = 3; }
	double SqrtVec = sqrt(Matrix.size());
	int j = round(SqrtVec);	int i; if (SqrtVec / round(SqrtVec) == 1) { i = round(SqrtVec); } else { i = ceil(sqrt(Matrix.size())); } // SQUARE SIDE SIZE
	CImg<unsigned char> Squares(j * Sizex, i * Sizey, 1, 3, 0);
	int cj = 0, ci = 0; // Count i or j
	for (int m = 0; m < Matrix.size(); ++m)
	{
		string Txt; if (Text) { Txt = to_string(m) + ":\n" + to_string(Matrix[m]); } else { Txt = " "; }
		Point3D RGB = LinearRGB((Matrix[m] * 1.0) / MaxVec(Matrix), 1, 1);
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		CImg<unsigned char> Square = RetCell(Sizex, Sizey, 1, 1, Txt, Clr);
		int Cellj = cj * Sizex, Celli = ci * Sizey;
		Squares.draw_image(Cellj, Celli, Square);
		++cj;
		if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<unsigned char> SqrMatrix(vector<double> Matrix, int Sizex, int Sizey, int j, bool Text)
{
	if (Sizex < 3) { Sizex = 3; } if (Sizey < 3) { Sizey = 3; }
	if (j > Matrix.size()) { j = Matrix.size(); }
	if (j < 1) { j = 1; }
	int i = ceil(Matrix.size() / (j * 1.0));
	CImg<unsigned char> Squares(j * Sizex, i * Sizey, 1, 3, 0); // VER SE O (+1) NÃO DA ERRO!
	int cj = 0, ci = 0; // Count i or j
	for (int m = 0; m < Matrix.size(); ++m)
	{
		string Txt; if (Text) { Txt = to_string(m) + ":\n" + to_string(Matrix[m]); }
		else { Txt = " "; }

		Point3D RGB = LinearRGB((Matrix[m] * 1.0) / MaxVec(Matrix), 1, 1);
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		CImg<unsigned char> Square = RetCell(Sizex, Sizey, 1, 1, Txt, Clr);
		int Cellj = cj * Sizex, Celli = ci * Sizey;
		Squares.draw_image(Cellj, Celli, Square);
		++cj;
		if (cj == j) { cj = 0; ++ci; }
	}
	return(Squares);
}
CImg<unsigned char> SqrMatrix(CImg<unsigned char> Matrix, int Sizex, int Sizey, bool Text)
{
	if (Sizex < 3) { Sizex = 3; } if (Sizey < 3) { Sizey = 3; }
	int j = Matrix.width(), i = Matrix.height();
	CImg<unsigned char> Squares(j * Sizex, i * Sizey, 1, 3, 0); // VER SE O (+1) NÃO DA ERRO!
	for (int m = 0; m < Matrix.width(); ++m)
	{
		for (int n = 0; n < Matrix.height(); ++n)
		{
			Point3D RGB = BitmapRGB(Matrix, n, m);
			string Txt; if (Text) { Txt = to_string(n + (j * m)) + ":\n" + to_string((RGB.x + RGB.y + RGB.z) / 3.0); }
			else { Txt = " "; }
			unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
			CImg<unsigned char> Square = RetCell(Sizex, Sizey, 1, 1, Txt, Clr);
			int Cellj = n * Sizex, Celli = m * Sizey;
			Squares.draw_image(Cellj, Celli, Square);
		}
	}
	return(Squares);
}

// ADICIONA VERTICE:
void AdcVert(CImg<unsigned char>& Img, int x, int y, int Size, unsigned char Color[3])
{
	for (int DrawLine = 0; DrawLine <= Size; ++DrawLine)
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