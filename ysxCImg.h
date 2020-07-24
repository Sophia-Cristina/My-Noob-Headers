#pragma once

#ifndef YSXCIMG_H
#define YSXCIMG_H
//#ifndef __CIMG_H_INCLUDED__   // if x.h hasn't been included yet...
//#define __CIMG_H_INCLUDED__

#include "CImg.h"
#include "ysxmath.h"
#include <vector>
#include <string>
#include <string.h>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cimg_library;

// ###################################
// ############## FUNÇÕES #######
// ###################################
// ############## DECLARAÇÕES:
Point3D BitmapRGB(CImg<unsigned char>, int, int);
Point3D LinearRGB(double, double, double);
CImg<unsigned char> DrawImageIgnClr(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
CImg<unsigned char> DrawImageIgnClrCout(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
// ###################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TÉCNICOS:
// ABRIR:
CImg<unsigned char> OpenImg(string FileName) { CImg<unsigned char> Open(Str2Char(FileName).data()); return(Open); }

// SALVAR (Com uso de 'string to char', minha função que cria um vetor de char com um string, acho que cimg aceita só um 'char array'):
void SaveBmp(CImg<unsigned char> Image, string FileName) { Image.save_bmp(Str2Char(FileName).data()); }
void SavePng(CImg<unsigned char> Image, string FileName) { Image.save_png(Str2Char(FileName).data()); }
void SavePng(CImg<unsigned char> Image, string FileName, int BytesPerPixel) { Image.save_png(Str2Char(FileName).data(), BytesPerPixel); }
void SaveJpg(CImg<unsigned char> Image, string FileName) { Image.save_jpeg(Str2Char(FileName).data(), 100); } // 100% quality
void SaveJpg(CImg<unsigned char> Image, string FileName, int QualityPercent) { Image.save_jpeg(Str2Char(FileName).data(), QualityPercent); }

// VERIFICA SE VALOR ESTA DENTRO DA IMAGEM:
bool InImg(CImg<unsigned char> Img, int y, int x)
{
	if (y < Img.height()) { if (x < Img.width()) { return (true); } else { return (false); } }
	else { return (false); }
}

// VER IMAGEM SALVA:
void CIMG(string Nome)
{
	CImg<unsigned char> ImagemAbrir(Str2Char(Nome).data()), Grafico(100, 100, 1, 3, 0);
	const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };

	CImgDisplay main_disp(ImagemAbrir, "Bela Arte:"), draw_disp(Grafico, "Perfil de Intensidade");
	while (!main_disp.is_closed() && !draw_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {
			int y = 0;
			const int ycimg = main_disp.mouse_y();
			Grafico.fill(0).draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 0, ImagemAbrir.width() - 1, y, 0, 0), red, 1, 1, 0, 255, 0);
			Grafico.draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 1, ImagemAbrir.width() - 1, y, 0, 1), green, 1, 1, 0, 255, 0);
			Grafico.draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 2, ImagemAbrir.width() - 1, y, 0, 2), blue, 1, 1, 0, 255, 0).display(draw_disp);
		}
	}
}

// VER IMAGEM MEMORIA:
void VerImg(CImg<unsigned char> Img) { CImgDisplay Disp(Img, "Imagem porreta, seria porreta uma pequena porra?"); while (!Disp.is_closed()) { Disp.wait(); } }
void VerImg(CImg<unsigned char> Img, string Title) { CImgDisplay Disp(Img, Str2Char(Title).data()); while (!Disp.is_closed()) { Disp.wait(); } }

// BITMAPRGB:
Point3D BitmapRGB(CImg<unsigned char> BMP, int x, int y)
{
	Point3D Ret;
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (x < 0) { x = 0; }
	if (y > BMP.height() - 1) { y = BMP.height() - 1; } if (y < 0) { y = 0; }
	Ret.x = BMP(x, y, 0, 0); Ret.y = BMP(x, y, 0, 1); Ret.z = BMP(x, y, 0, 2);
	return(Ret);
}

// ALL RGBS FROM BITMAP (in float):
vector<Point3DFlt> BitmapRGBMatrix(CImg<unsigned char> BMP)
{
	vector<Point3DFlt> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{ Point3D RGB = BitmapRGB(BMP, n, m); Point3DFlt RGBFlt; RGBFlt.x = RGB.x / 255.0; RGBFlt.y = RGB.y / 255.0; RGBFlt.z = RGB.z / 255.0; Ret.push_back(RGBFlt); }
	}
	return(Ret);
}

// ALL RGBS FROM BITMAP (in float), IT GOES LIKE R, THEN G, THEN B, THEN NEXT PIXEL, SO THE VECTOR HAVE 3X THE SIZE OF THE IMAGE:
vector<double> BitmapRGBVector(CImg<unsigned char> BMP)
{
	vector<double> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{
			Point3D RGB = BitmapRGB(BMP, n, m);  Ret.push_back(RGB.x / 255.0);  Ret.push_back(RGB.y = RGB.y / 255.0);  Ret.push_back(RGB.z = RGB.z / 255.0);
		}
	}
	return(Ret);
}

// POEM DADOS NA MATRIZ ATRAVEZ DE UM BITMAP (GRAYSCALE):
vector<double> BitmapMatrix(CImg<unsigned char> BMP)
{
	vector<double> NewMatrix;
	Point3D RGB;
	for (int ny = 0; ny < BMP.height(); ++ny)
	{
		for (int nx = 0; nx < BMP.width(); ++nx) { RGB = BitmapRGB(BMP, nx, ny); double Valor = ((RGB.x + RGB.y + RGB.z) / 765.0); NewMatrix.push_back(Valor); }
	}
	return (NewMatrix);
}
// POEM DADOS NA MATRIZ ATRAVEZ DE UM BITMAP (R = 0, G = 1, B = 2):
vector<double> BitmapMatrix(CImg<unsigned char> BMP, int R0orG1orB2)
{
	vector<double> NewMatrix;
	Point3D RGB;
	for (int ny = 0; ny < BMP.height(); ++ny)
	{
		for (int nx = 0; nx < BMP.width(); ++nx)
		{
			RGB = BitmapRGB(BMP, nx, ny);
			double Value = 0; if (R0orG1orB2 == 0) { Value = RGB.x; } if (R0orG1orB2 == 1) { Value = RGB.y; } if (R0orG1orB2 == 2) { Value = RGB.z; }
			Value /= 255.0;
			NewMatrix.push_back(Value);
		}
	}
	return (NewMatrix);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TEXTOS:
// ADC TEXTO:
void AdcTexto(CImg<unsigned char>& Img, int x, int y, string String, int R, int G, int B)
{
	// www.cplusplus.com/reference/string/string/at/
	int TxtLim = String.length() + 1;
	vector<char> Texto(TxtLim);
	for (int chr = 0; chr < String.length(); ++chr)
	{
		Texto[chr] = String.at(chr);
		if (chr == String.length() - 1) { Texto[chr + 1] = '\0'; }
	}
	//unsigned char color[] = { R, G, B };
	unsigned char color[] = { R, G, B };
	CImgList<unsigned char> font(const unsigned int font_height = 19, const bool variable_size = true);
	Img.draw_text(x, y, Texto.data(), color);
}
void AdcTextoCirc(CImg<unsigned char>& Img, double r, int x, int y, vector<string> Strings, int R, int G, int B) // Adiciona em direções de um circulo, como raios, como numeros num relógio
{
	double Div = Tau / Strings.size() * 1.0; int Count = 0;
	for (double rad = 0; rad <= Tau; rad += Div) { AdcTexto(Img, x + round(cos(rad) * (r - 8)), y + round(sin(rad) * (r - 8)), Strings[Count], R, G, B); ++Count; }
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GRAFICOS:

// ### LINEARRGB:
// PALETAS DO LINEAR RGB:
// LINEAR RGB:
Point3D LinearRGB(double n, double Lum, double Cont)
{
	//cout << "####### LINEAR RGB #######\n";
	//cout << "### Numero: " << n << "\n\n";

	//cout << "Estapas:\n" << 1.0 / 6 << " | " << 2.0 / 6 << " | " << 3.0 / 6 << " | " << 4.0 / 6 << endl << 5.0 / 6 << " | " << 6.0 / 6 << "\n\n";
	if (n > 1.0) { while (n > 1.0) { n -= 1; } } if (n < 0.0) { while (n < 0.0) { n += 1; } }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	int R, G, B;
	Point3D RGB;
	double m, delta;

	if (n <= 1.0 / 6)
	{
		m = n * 6;
		R = 255;
		G = round(255 * m);
		B = 0;
	}
	if (n <= 2.0 / 6 && n > 1.0 / 6)
	{
		m = (n - (1.0 / 6)) * 6;
		R = round(255 - (255 * m));
		G = 255;
		B = 0;
	}
	if (n <= 3.0 / 6 && n > 2.0 / 6)
	{
		m = (n - (2.0 / 6)) * 6;
		R = 0;
		G = 255;
		B = round(255 * m);
	}
	if (n <= 4.0 / 6 && n > 3.0 / 6)
	{
		m = (n - (3.0 / 6)) * 6;
		R = 0;
		G = round(255 - (255 * m));
		B = 255;
	}
	if (n <= 5.0 / 6 && n > 4.0 / 6)
	{
		m = (n - (4.0 / 6)) * 6;
		R = round(255 * m);
		G = 0;
		B = 255;
	}
	if (n <= 6.0 / 6 && n > 5.0 / 6)
	{
		m = (n - (5.0 / 6)) * 6;
		R = 255;
		G = 0;
		B = round(255 - (255 * m));
	}

	// Contraste:
	if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
	if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
	if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }

	// Luminosidade:
	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	if (Lum > 1.0) { if (R == 0) { R = 1; } if (G == 0) { G = 1; } if (B == 0) { B = 1; } double LumMath = 255 * (Lum - 1); R = R + LumMath; G = G + LumMath; B = B + LumMath; }

	// Limite:
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	RGB.x = R; RGB.y = G; RGB.z = B;
	return(RGB);
}

// Brilho:
void PaletaLinRGBLum(int sx, int sy, double div)
{
	CImg<unsigned char> Paleta(sx, sy, 1, 3, 0);

	for (double ny = 0; ny < sy + 1; ++ny)
	{
		for (double nx = 0; nx < sx + 1; ++nx)
		{
			//cout << "nx/sx: " << nx / sx << " | (sy - ny) / sy: " << (sy - ny) / sy << endl;
			Point3D RGB = LinearRGB(nx / sx, (sy - ny) / (sy / div), 1);
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Paleta.draw_point(nx, ny, color);
		}
	}

	Paleta.save_bmp("PaletaLum.bmp");
	CImgDisplay Display(Paleta, "Paleta:");
	while (!Display.is_closed()) { Display.wait(); }
}

// Contraste:
void PaletaLinRGBCont(int sx, int sy, double div)
{
	CImg<unsigned char> Paleta(sx, sy, 1, 3, 0);

	for (double ny = 0; ny < sy + 1; ++ny)
	{
		for (double nx = 0; nx < sx + 1; ++nx)
		{
			Point3D RGB = LinearRGB(nx / sx, 1, (sy - ny) / (sy / div));
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Paleta.draw_point(nx, ny, color);
		}
	}

	Paleta.save_bmp("PaletaCont.bmp");
	CImgDisplay Display(Paleta, "Paleta:");
	while (!Display.is_closed()) { Display.wait(); }
}

// Só uma linha de cor:
void PaletaLinRGB(int sx, int sy)
{
	CImg<unsigned char> Paleta(sx, sy, 1, 3, 0);

	for (double ny = 0; ny < sy + 1; ++ny)
	{
		for (double nx = 0; nx < sx + 1; ++nx)
		{
			Point3D RGB = LinearRGB(nx / sx, 1, 1);
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Paleta.draw_point(nx, ny, color);
		}
	}
	Paleta.save_bmp("Paleta.bmp");
	CImgDisplay Display(Paleta, "Paleta:");
	while (!Display.is_closed()) { Display.wait(); }
}
// ###

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

// REFAZ IMAGEM COM CERTA COR:
void FillAll(CImg<unsigned char>& Img)
{
	CImg<unsigned char> FilledImg(Img.width(), Img.height(), 1, 3, 0);
	unsigned char color[] = { 0, 0, 0 };
	FilledImg.draw_fill(1, 1, color, 1, 1, false);
	Img = FilledImg;
}
CImg<unsigned char> FillAll(int Width, int Height)
{
	CImg<unsigned char> FilledImg(Width, Height, 1, 3, 0);
	unsigned char color[] = { 0, 0, 0 };
	FilledImg.draw_fill(1, 1, color, 1, 1, false);
	return(FilledImg);
}

// FILL CERTO LUGAR:
void FillArea(CImg<unsigned char>& Img, int x, int y, int R, int G, int B)
{ unsigned char color[] = { R, G, B }; Img.draw_fill(x, y, color, 1, 1, false); }

// BARRAS:
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

// CRIA IMAGEM DE UMS BARRA BASEADO NUM VALOR (ABOSLUTO):
CImg<unsigned char> ValueBarAbs(int Width, double Value, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> Bar;
	Value = abs(Value * Ratio);
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
	Value = abs(Value * Ratio);
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

// PLOTAR CIRCULO EM DIFERENTE XY:
void Circuloxy(CImg<unsigned char>& Img, double r, int tx, int ty, int R, int G, int B)
{
	double y, x;
	int xzero = tx, yzero = ty;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= Tau; Rad += Step) // MUDAR SE NESCESSARIO
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		
		if (InImg(Img, y + yzero, x + xzero))
		{
			unsigned char color[] = { R, G, B };
			Img.draw_point(x + xzero, y + yzero, color);
		}
	}
}
void Circuloxy(CImg<unsigned char>& Img, double r, int tx, int ty)
{
	double y, x;
	int xzero = tx, yzero = ty;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= Tau; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		double Progresso = Rad / Tau;

		if (InImg(Img, y + yzero, x + xzero))
		{
			Point3D RGB = LinearRGB(Progresso, 1, 1);
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(x + xzero, y + yzero, color);
		}
	}
}

// PLOTAR CIRCULO:
void Circulo(CImg<unsigned char>& Img, int R, int G, int B)
{
	double y, x;
	double r = Img.height(); if (Img.width() <= Img.height()) { r = Img.width(); } r -= 1; r *= 0.5;
	double Step = 1.0 / r;
	int xzero = floor(Img.width() * 0.5), yzero = Img.height() - floor(Img.height() * 0.5);

	for (double Rad = 0; Rad <= Tau; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);

		if (InImg(Img, y, x))
		{
			unsigned char color[] = { R, G, B };
			Img.draw_point(x + xzero, y + yzero, color);
		}
	}
}
void Circulo(CImg<unsigned char>& Img)
{
	double y, x;
	double r = Img.height(); if (Img.width() <= Img.height()) { r = Img.width(); } r -= 2; r *= 0.5;
	double Step = 1.0 / r;
	int xzero = floor(Img.width() * 0.5), yzero = Img.height() - floor(Img.height() * 0.5);

	for (double Rad = 0; Rad <= Tau; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		double Progresso = Rad / Tau;

		if (InImg(Img, y, x))
		{
			int R, G, B;
			Point3D RGB = LinearRGB(Progresso, 1, 1); R = RGB.x; G = RGB.y; B = RGB.z;
			unsigned char color[] = { R, G, B };
			Img.draw_point(x + xzero, y + yzero, color);
		}
	}
}

// TURN:
void Turn(CImg<unsigned char>& Img, double r, int tx, int ty, double Ini, double Turn, int R, int G, int B)
{
	double y, x;
	double Rad;
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	double Step = (Turn - Ini) * (1.0 / Circumf(r));

	for (Rad = Ini; Rad <= Turn; Rad += Step)
	{
		y = round(sin(Tau - Rad) * r);
		x = round(cos(Tau - Rad) * r);

		if (InImg(Img, y + ty, x + tx))
		{
			unsigned char color[] = { R, G, B };
			Img.draw_point(x + tx, y + ty, color);
		}
	}
}
void Turn(CImg<unsigned char>& Img, double r, int tx, int ty, double Ini, double Turn)
{
	double y, x;
	double Rad;
	if (Ini > Turn) { double Tmp; Tmp = Ini; Ini = Turn; Turn = Tmp; }
	double Step = (Turn - Ini) * (1.0 / Circumf(r));

	for (Rad = Ini; Rad <= Turn; Rad += Step)
	{
		y = round(sin(Tau - Rad) * r);
		x = round(cos(Tau - Rad) * r);

		if (InImg(Img, y + ty, x + tx))
		{
			double Val = (Rad - Ini) / (Turn - Ini); Point3D RGB = LinearRGB(Val, 1, 1);
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(x + tx, y + ty, color);
		}
	}
}

// PLOTAR RAIO:
void Raio(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Borda)
{
	int Pixy, Pixx;
	double rn, Sin = sin(Tau - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);

	for (rn = 0; rn <= r; rn = ++rn)
	{
		Pixy = round(Sin * rn);
		Pixx = round(Cos * rn);
		double Prog = rn / r;
		if (InImg(Img, Pixy + y, Pixx + x))
		{
			Point3D RGB = LinearRGB(Prog, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			Img.draw_point(Pixx + x, Pixy + y, Color);
			if (Triangle == true)
			{
				unsigned char InvColor[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z };
				Img.draw_point(Pixx + x, y, InvColor);
				Img.draw_point(x + xend, Pixy + y, InvColor);
			}
		}
	}
	if (Borda) { Circuloxy(Img, r, x, y); }
}
void Raio(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Borda, int R, int G, int B)
{
	int Pixy, Pixx;
	double rn, Sin = sin(Tau - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);
	unsigned char Color[] = { R, G, B };

	for (rn = 0; rn <= r; rn = ++rn)
	{
		Pixy = round(Sin * rn);
		Pixx = round(Cos * rn);
		if (InImg(Img, Pixy + y, Pixx + x))
		{
			Img.draw_point(Pixx + x, Pixy + y, Color);
			if (Triangle)
			{
				unsigned char InvColor[] = { 255 - R, 255 - G, 255 - B };
				Img.draw_point(Pixx + x, y, InvColor);
				Img.draw_point(x + xend, Pixy + y, InvColor);
			}
		}
	}	
	if (Borda) { Circuloxy(Img, r, x, y, R, G, B); }
}
void RaioQuick(CImg<unsigned char>& Img, double r, int x, int y, double Rad, bool Triangle, bool Borda, int R, int G, int B)
{
	int Pixy, Pixx;
	double Sin = sin(Tau - Rad), Cos = cos(Rad);
	int xend = round(Cos * r), yend = round(Sin * r);
	unsigned char Color[] = { R, G, B };

	if (InImg(Img, y, x) && InImg(Img, yend, xend))
	{
		//Img.draw_line(x, y, xend, yend, Color);
		Img.draw_line(x, y, x + xend, y + yend, Color);
		if (Triangle)
		{
			unsigned char InvColor[] = { 255 - R, 255 - G, 255 - B };
			Img.draw_line(x, y, x + xend, y, InvColor);
			Img.draw_line(x + xend, y, x + xend, y + yend, InvColor);
		}
	}
	if (Borda) { Circuloxy(Img, r, x, y, R, G, B); }
}
void RaioPoligono(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, bool Triangle, bool Borda)
{ double Div = Tau / Divisions; for (double n = OffSet; n < Tau + OffSet; n += Div) { Raio(Img, r, x, y, n, Triangle, Borda); } }
void RaioPoligono(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, int R, int G, int B, bool Triangle, bool Borda)
{
	double Div = Tau / Divisions;
	for (double n = OffSet; n < Tau + OffSet; n += Div)
	{
		//cout << "n / Tau: " << n / (Tau + OffSet) << "!\n";
		Raio(Img, r, x, y, n, Triangle, Borda, R, G, B);
	}
}
void RaioPoligonoQuick(CImg<unsigned char>& Img, double r, int x, int y, double OffSet, int Divisions, int R, int G, int B, bool Triangle, bool Borda)
{
	double Div = Tau / Divisions;
	for (double n = OffSet; n < Tau + OffSet; n += Div)
	{
		//cout << "n / Tau: " << n / (Tau + OffSet) << "!\n";
		RaioQuick(Img, r, x, y, n, Triangle, Borda, R, G, B);
	}
}

// PLOTAR LINHA:
void Linha(CImg<unsigned char>& Img, double r, double Rad, int xpix, int ypix, bool Triangle, int R, int G, int B, bool LRGB)
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
				if (LRGB == true) { Point3D RGB = LinearRGB(Progresso / 100, 1, 1); R = RGB.x; G = RGB.y; B = RGB.z; }
				unsigned char Color[] = { R, G, B };
				Img.draw_point(x + xpix, y + ypix, Color);
				if (Triangle == true)
				{
					unsigned char InvColor[] = { 255 - R, 255 - G, 255 - B };
					Img.draw_point(xpix + x, ypix, InvColor);
					Img.draw_point(xpix + xend, y + ypix, InvColor);
				}
		}
	}
}

// PLOTAR LINHAS BRESENHAM:
void Linhaxy(CImg<unsigned char>& Img, int x1, int y1, int x2, int y2, int R, int G, int B, bool LRGB)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	unsigned char First[] = { R, G, B };
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
			if (LRGB == true) { Point3D RGB = LinearRGB(1.0 * x / (xe - 1), 1, 1); R = RGB.x; G = RGB.y; B = RGB.z; }
			unsigned char Color[] = { R, G, B };
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
			if (LRGB == true) { Point3D RGB = LinearRGB(1.0 * y / (ye - 1), 1, 1); R = RGB.x; G = RGB.y; B = RGB.z; }
			unsigned char Color[] = { R, G, B };
			Img.draw_point(x, y, Color);
		}
	}
}

// PLOTAR POLIGONO:
void Poligono(CImg<unsigned char>& Img, int Lados, double r, int x, int y, bool Vertex, int R, int G, int B)
{
	double tx, ty;
	if (Lados < 3) { Lados = 3; }
	vector<Point> Coord(Lados);
	double Div = Tau / Lados;
	int Count = 0;

	for (double n = 0.0; n <= Tau; n = n + Div)
	{
		tx = round(cos(n) * r);
		ty = round(sin(n) * r);
		//cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / Tau) * 360 << endl;
		if (Count < Lados) { Coord[Count].x = tx + x; Coord[Count].y = ty + y; }
		double Progresso = (n / Tau) * 100;
		++Count;
		if (Vertex == true)
		{
			unsigned char Color[] = { R, G, B };
			AdcVert(Img, tx + x, ty + y, 3, Color);
		}
	}
	for (int ns = 1; ns < Lados; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linhaxy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, R, G, B, false);
			if (ns == Lados - 1) { Linhaxy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, R, G, B, false); }
		}
	}
}
void Poligono(CImg<unsigned char>& Img, int Lados, double r, int x, int y, bool Vertex)
{
	double tx, ty;
	Point3D RGB = { 255, 0, 127 };
	if (Lados < 3) { Lados = 3; }
	vector<Point> Coord(Lados);
	double Div = Tau / Lados;
	int Count = 0;

	for (double n = 0.0; n <= Tau; n = n + Div)
	{
		tx = round(cos(n) * r);
		ty = round(sin(n) * r);
		//cout << "cosine: " << cos(n) << " | sine: " << sin(n) << " | Angle radians: " << n << " | Degress: " << (n / Tau) * 360 << endl;
		if (Count < Lados) { Coord[Count].x = tx + x; Coord[Count].y = ty + y; }
		double Progresso = n / Tau;
		++Count;
		if (Vertex == true)
		{
			RGB = LinearRGB(Progresso, 1, 1);
			unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
			AdcVert(Img, tx + x, ty + y, 3, Color);
		}
	}
	for (int ns = 1; ns < Lados; ++ns)
	{
		if (InImg(Img, Coord[ns].y, Coord[ns].x) && InImg(Img, Coord[ns - 1].y, Coord[ns - 1].x))
		{
			Linhaxy(Img, Coord[ns - 1].x, Coord[ns - 1].y, Coord[ns].x, Coord[ns].y, RGB.x, RGB.y, RGB.z, true);
			if (ns == Lados - 1) { Linhaxy(Img, Coord[ns].x, Coord[ns].y, Coord[0].x, Coord[0].y, RGB.x, RGB.y, RGB.z, true); }
		}
	}

}


// LIMPAR:
void LimparImagem(CImg<unsigned char>& Img) { CImg<unsigned char> ImagemLimpa(Img.width(), Img.height(), 1, 3, 0); Img = ImagemLimpa; }

// GRADUAÇÃO:
CImg<unsigned char> GraduaçãoRGB(CImg<unsigned char> Img, bool Inv) // Talvez fazer um struct RGB
{
	CImg<unsigned char> ImgRet(Img.width(), Img.height(), 1, 3, 0);
	Point3D RGB;
	for (int nfy = 0; nfy < Img.height(); ++nfy)
	{
		for (int nfx = 0; nfx < Img.width(); ++nfx)
		{
			double Multi = (Img.width() * nfy + nfx * 1.0) / (Img.width() * (Img.height() + 1)); // Ver no Wolfram Alpha se não lembrar da onde veio essa expressão.
			if (Inv == true) { Multi = 1 - Multi; }
			RGB = BitmapRGB(Img, nfx, nfy);
			RGB.x = round(RGB.x * Multi); RGB.y = round(RGB.y * Multi); RGB.z = round(RGB.z * Multi);
			unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
			ImgRet.draw_point(nfx, nfy, Clr);
		}
	}
	return (ImgRet);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## FRACTAIS:
// PLOTAR PONTOS (STRUCT):
CImg<unsigned char> PrintPoints(vector<Point> Coord, int SegmentSize, int BackGround, bool Abs)
{
	Point max, min;
	MaxMinVecPoint(Coord, max, min, Abs);

	int sx = (max.x - min.x + 1) * SegmentSize,	sy = (max.y - min.y + 1) * SegmentSize;
	CImg<unsigned char> Print(sx, sy, 1, 3, BackGround);

	for (size_t n = 1; n < Coord.size(); ++n)
		Linhaxy(Print, (Coord[n - 1].x - min.x) * SegmentSize, (Coord[n - 1].y - min.y) * SegmentSize,
		(Coord[n].x - min.x) * SegmentSize, (Coord[n].y - min.y) * SegmentSize,	255, 0, 127, false);

	return Print;
}
CImg<unsigned char> PrintLinePoints(vector<LinePoint> Coord, int SegmentSize, int BackGround, bool Abs) // Testar para ver se esta tudo certo
{
	LinePoint max, min;
	MaxMinVecLinePoint(Coord, max, min, Abs);

	int sx = 0;
	if (max.x0 > max.x1) { sx = (max.x0 + 1) * SegmentSize; }
	else { sx = (max.x0 + 1) * SegmentSize; }
	int sy = 0;
	if (max.y0 > max.y1) { sy = (max.y0 + 1) * SegmentSize; }
	else { sy = (max.y0 + 1) * SegmentSize; }

	CImg<unsigned char> Print(sx, sy, 1, 3, BackGround);

	for (size_t n = 0; n < Coord.size(); ++n)
	{
		Linhaxy(Print, Coord[n].x0 * SegmentSize, Coord[n].y0 * SegmentSize, Coord[n].x1 * SegmentSize, Coord[n].y1 * SegmentSize, 255, 0, 127, false);
	}
	return Print;
}
CImg<unsigned char> PrintBinaryWordCircle(int Size, int r, int Iter, bool GeoAri, bool RandomColor, bool LRGB, Point3D RGB, bool Cout)
{
	CImg<unsigned char> MainImg(Size, Size, 1, 3, 0);
	double rRatio = 1.0 * r / Size;	int Mid = floor(Size * 0.5);
	vector<string> BinWords = BinaryWordsSeq(Iter);	vector<long> BinArea = BinaryWordSeqArean(Iter);
	for (int c = Iter; c > 0; --c)
	{
		int Invc = (Iter - c) + 1;
		int cSize = 0; if (GeoAri) { cSize = (Size / Iter) * c; } else { cSize = Size / Invc; }
		int MidS = cSize * 0.5;	int cr = rRatio * cSize; int s = BinArea[c - 1]; int s2 = pow(2, c);
		CImg<unsigned char> CircleImg(cSize, cSize, 1, 3, 127);	unsigned char cclr[] = { 255, 0, 0 }; CircleImg.draw_circle(MidS, MidS, cr, cclr, 1, 1);
		if (c > 1) { RaioPoligonoQuick(CircleImg, cr, MidS, MidS, 0, s, 255, 255, 0, 0, 0); } RaioPoligonoQuick(CircleImg, cr, MidS, MidS, 0, s2, 255, 0, 127, 0, 0);
		double Div = Tau / s2; int Count = 0; vector<PointFlt> Scores; for (double rad =  0; Count < s2; ++Count) { Scores.push_back({ rad, AOScore(rad) }); rad += Div; } QuickSortPty(Scores, 0, Scores.size() - 1);
		int Wordset = SumntoPowIniEnd(2, 1, c - 1);
		for (int Word = Wordset; Word < Wordset + s2; ++Word)
		{
			if (RandomColor) { RGB.x = rand() % 256; RGB.y = rand() % 256; RGB.z = rand() % 256; }
			if (LRGB) { double Line = 1.0 * (Word - Wordset) / s2; if (BinWords[Word][0] == '0') { RGB = LinearRGB(0.5 + Line, 1, 1); } else { RGB = LinearRGB(Line, 1, 1); } }
			int WordSize = BinWords[Word].size();
			for (int Char = 0; Char < WordSize; ++Char)
			{
				Point3D NewRGB = RGB; if (BinWords[Word][WordSize - 1 - Char] == '0') { NewRGB.x = 255 - NewRGB.x; NewRGB.y = 255 - NewRGB.y; NewRGB.z = 255 - NewRGB.z; }
				double SubDiv = Div / WordSize; double Rad = Scores[Word - Wordset].x - (SubDiv * (WordSize - 1)) + (SubDiv * Char); Rad -= (Tau / s) * 0.5; Rad = Tau - Rad;
				if (c > 1) { FillArea(CircleImg, MidS + cos(Rad) * cr * 0.85, MidS + sin(Rad) * cr * 0.85, NewRGB.x, NewRGB.y, NewRGB.z); }
				else { FillArea(CircleImg, MidS, MidS + sin(Rad + Tau * 0.5) * cr * 0.75, NewRGB.x, NewRGB.y, NewRGB.z); }
				//AdcTexto(CircleImg, MidS + cos(Rad) * cr * 0.90, MidS + sin(Rad) * cr * 0.90, to_string(BinWords[Word][Char]) + "\n" + BinWords[Word], 255, 0, 0);
			}
		}
		unsigned char IgnoreColor[] = { 127, 127, 127 };
		if (Cout) { MainImg = DrawImageIgnClrCout(MainImg, CircleImg, Mid - MidS, Mid - MidS, IgnoreColor); } else { MainImg = DrawImageIgnClr(MainImg, CircleImg, Mid - MidS, Mid - MidS, IgnoreColor); }
	}
	return (MainImg);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## EUCLIDEAN VETORES:

// Print vector line in a cartesian plane:
void PrintEucVec(CImg<unsigned char>& Img, PointFlt Vector, int x, int y, double Scale, bool Arrow, bool DrawAngle, bool CartesianLines, bool Text, Point3D RGB)
{
	Vector.x *= Scale; Vector.y *= Scale;
	int xend = x + round(Vector.x), yend =Img.height() - (y + round(Vector.y));
	if (xend < 0) { xend = 0; } if (yend < 0) { yend = 0; }
	if (xend > Img.width()) { xend = Img.width(); } if (yend > Img.height()) { yend = Img.height(); }
	unsigned char clr[] = { 127, 127, 127 };
	if (CartesianLines) { Img.draw_line(0, y, Img.width(), y, clr); Img.draw_line(x, 0, x, Img.height(), clr); }
	clr[0] = RGB.x; clr[1] = RGB.y; clr[2] = RGB.z;
	if (Arrow) { Img.draw_arrow(x, y, xend, yend, clr); } else { Img.draw_line(x, y, xend, yend, clr); }
	if (DrawAngle) { Turn(Img, GetMag(Vector) * 0.2, x, y, 0, GetVecRad(Vector), RGB.x, RGB.y, RGB.z); }
	if (Text)
	{
		string Txt = "[" + to_string(Vector.x) + ", " + to_string(Vector.y) + "]";
		int Size = Txt.size() * 6;
		int xtxt = xend - Size * 0.5, ytxt = yend - 10;
		if (xtxt + Txt.size() * 3.75 > Img.width()) { xtxt = xend - Size * 0.5 - Txt.size() * 3.75; } if (xtxt < 0) { xtxt = xend + Size * 0.5; }
		if (ytxt < 0) { ytxt = yend + 10; }
		AdcTexto(Img, xtxt, ytxt, Txt, RGB.x, RGB.y, RGB.z);
	}
}

// Print vector line joining tail to tail:

void PrintEucVecTail(CImg<unsigned char>& Img, vector<PointFlt> Vectors, int x, int y, double Scale, bool Arrow, bool DrawAngle, bool CartesianLines, bool Text, bool LRGB, Point3D RGB)
{
	if (LRGB) { RGB = { 255, 0, 0 }; }
	PrintEucVec(Img, Vectors[0], x, y, Scale, Arrow, DrawAngle, CartesianLines, Text, RGB);
	double sumx = Vectors[0].x, sumy = Vectors[0].y;
	for (int n = 1; n < Vectors.size(); ++n)
	{
		cout << "sumx: " << sumx << " | sumy: " << sumy << " | V.x: " << Vectors[n].x << " | V.y: " << Vectors[n].y << endl;
		if (LRGB) { RGB = LinearRGB(1.0 * n / Vectors.size(), 1, 1); }
		int xend = x + sumx, yend = y + sumy;
		if (xend < 0) { xend = 0; } if (Img.height() - yend < 0) { yend = Img.height(); } if (xend > Img.width()) { xend = Img.width(); } if (Img.height() - yend > Img.height()) { yend = 0; }
		PrintEucVec(Img, Vectors[n], xend, Img.height() - yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		//PrintEucVec(Img, Vectors[n], xend, yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		cout << "xend: " << xend << " | Img.height() - yend: " << Img.height() - yend << "\nV.x + xend: " << Vectors[n].x + xend << " | Img.height() - (yend + V.y): " << Img.height() - (yend + Vectors[n].y) << endl;
		sumx += Vectors[n].x; sumy += Vectors[n].y;
	}
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## VETORES:
// THREE VECTORS TO RGB:
vector<Point3DFlt> Vectors2RGB(vector<double> VecR, vector<double> VecG, vector<double> VecB)
{
	vector<Point3DFlt> RGBs;
	if (VecR.size() == VecG.size() && VecG.size() == VecB.size())
	{
		int Size = VecR.size(); for (int n = 0; n < Size; ++n) { Point3DFlt RGB; RGB.x = VecR[n]; RGB.y = VecG[n]; RGB.z = VecB[n]; RGBs.push_back(RGB); }
	}
	return(RGBs);
}

// PLOTAR VETOR (LINHA):
// Esses fazem uma linha de um ponto ao outro, o tamanho do segmento é multiplicado por cada célula do vetor:
CImg<unsigned char> PrintVectorLine(vector<double> Vec, int SegmentSize, int BackGround, int R, int G, int B)
{
	double Max, Min;
	MaxMinVec(Vec, Max, Min);
	double Absmx = 0, Absmn = 0;
	if (Max < 0) { Absmx = abs(Max); Max += Absmx; Min += Absmx; }
	if (Min < 0) { Absmn = abs(Min); Max += Absmn; Min += Absmn; }
	int MaxMin = ceil((Max + Min) * SegmentSize);
	
	CImg<unsigned char> Print(Vec.size() * SegmentSize, MaxMin, 1, 3, BackGround);

	for (int n = 1; n < Vec.size(); ++n)
	{ Linhaxy(Print, (n - 1)  * SegmentSize, MaxMin - ((Vec[n - 1] + Absmn) * SegmentSize), n * SegmentSize, MaxMin - ((Vec[n] + Absmn) * SegmentSize), R, G, B, false); }

	return Print;
}
CImg<unsigned char> PrintVectorPoint(vector<double> Vec, int BackGround, int R, int G, int B)
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
		unsigned char Clr[] = { R, G, B };
		Print.draw_point(n, MaxMin - (Vec[n] + Absmn), Clr);
	}

	return Print;
}

// Esse assume que o valor do vetor é a amplitude, então, faz uma linha em cada divisão de um circulo pelo size() de acordo com a amplitude:
CImg<unsigned char> PrintVectorPolygn(vector<double> Vec, int BackGround, int R, int G, int B, bool LRGB, bool Vertex)
{
	double x, y;
	int Lados = Vec.size();
	vector<Point> xy(Lados); // Coordinates for image
	double Div = Tau / Lados;
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
		Linhaxy(Ret, xy[ns - 1].x, xy[ns - 1].y, xy[ns].x, xy[ns].y, R, G, B, LRGB); // LINHAS
		if (ns == Lados - 1) { Linhaxy(Ret, xy[0].x, xy[0].y, xy[ns].x, xy[ns].y, R, G, B, LRGB); } // ULTIMA LINHA
		if (Vertex == true) // VERTICES
		{
			if (LRGB == true) { double Val = ns / Lados; Point3D RGB = LinearRGB(Val, 1, 1); R = RGB.x; G = RGB.y; B = RGB.z; }
			unsigned char Color[] = { R, G, B };
			AdcVert(Ret, xy[ns].x, xy[ns].y, 3, Color);
			if (ns == 1) { unsigned char Clr[] = { 255, 0, 0 }; AdcVert(Ret, xy[0].x, xy[0].y, 3, Clr); }
		}
	}
	return(Ret);
}

// IMPRIME DADOS DE UM VETOR POR COLUNA:
// Esse assume que cada pixel de uma imagem corresponde a um dx (PROVAVELMENTE IGUAL O SEM "Norm"):
CImg<unsigned char> PrintVectorPointNorm(vector<double> Vector)
{
	double Min = 0, Max = 0, Total;
	for (int n = 0; n < Vector.size(); ++n)
	{
		if (Vector[n] > Max) { Max = Vector[n]; }
		if (Vector[n] < Min) { Min = Vector[n]; }
	}
	Total = fabs(Max) + fabs(Min);
	CImg<unsigned char> WavePrint(Vector.size(), ceil(Total), 1, 3, 0);
	for (int n = 0; n < Vector.size(); ++n)
	{
		double ndiv = (1.0 * n) / (Vector.size() - 1);
		Point3D RGB = LinearRGB(ndiv, 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		WavePrint.draw_point(n, round(Total - (Vector[n] - Min)), Color);
	}
	return (WavePrint);
}

// Esse o "sy" (Size y) é o tamanho "y" da imagem, "syrto" vai ser multiplicado pelo valor do vetor:
CImg<unsigned char> PrintVectorPointNorm(vector<double> Vector, int sy, double syrto)
{
	CImg<unsigned char> WavePrint(Vector.size(), sy, 1, 3, 0);
	double Max, Min; MaxMinVecAbs(Vector, Max, Min);
	for (int n = 0; n < Vector.size(); ++n)
	{
		double ndiv = (1.0 * n) / (Vector.size() - 1);
		Point3D RGB = LinearRGB(ndiv, 1, 1);
		unsigned char Color[] = { RGB.x, RGB.y, RGB.z };
		WavePrint.draw_point(n, round(sy - (((Vector[n] / Max) * (sy * 0.5) * syrto) + (sy * 0.5))), Color);
	}
	return (WavePrint);
}

// Imprime vetor como barras, tipo grafico estastistico: (LEMBRAR DE FAZER COM QUE SE NÃO TIVER VALOR NEGATIVO, USAR METADE DA IMAGEM!)
CImg<unsigned char> PrintVectorBars(vector<double> Vector, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	double Max, Min; bool Neg = false; MaxMinVec(Vector, Max, Min); if (Min < 0) { Neg = true; } MaxMinVecAbs(Vector, Max, Min); Max *= Ratio; Min *= Ratio;
	CImg<unsigned char> VecPrint; //vector<CImg<unsigned char>> Prints;
	if (Neg)
	{
		if (xAxis) { CImg<unsigned char> I(Max + Min + 2 + Borderx * 2, Width * Vector.size(), 1, 3, 0); VecPrint = I; } else { CImg<unsigned char> I(Width * Vector.size(), Max + Min + 2 + Bordery * 2, 1, 3, 0); VecPrint = I; }
	}
	else { if (xAxis) { CImg<unsigned char> I(Max + 2 + Borderx * 2 , Width * Vector.size(), 1, 3, 0); VecPrint = I; } else { CImg<unsigned char> I(Width * Vector.size(), Max + 2 + Bordery * 2, 1, 3, 0); VecPrint = I; } }
	int Mid = 0;
	if (Neg) { double NewMax, NewMin; MaxMinVec(Vector, NewMax, NewMin); NewMin *= Ratio; if (xAxis) { Mid = round((NewMin * -1) + Borderx); } else { Mid = round((NewMin * -1) + Bordery); } }
	//else { if (xAxis) { Mid = VecPrint.width(); } else { Mid = VecPrint.height(); } }
	for (int n = 0; n < Vector.size(); ++n)
	{
		if (Vector[n] != 0)
		{
			if (xAxis)
			{
				if (Vector[n] >= 0) { VecPrint.draw_image(Mid, n * Width, ValueBarAbs(Width, Vector[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(Mid + (Vector[n] * Ratio), n * Width, ValueBarAbs(Width, Vector[n], Ratio, Borderx, Bordery, xAxis)); } // + porque é "+ -", o que torna "-"
			}
			else
			{
				if (Vector[n] >= 0) { VecPrint.draw_image(n * Width, VecPrint.height() - (Mid + (Vector[n] * Ratio)), ValueBarAbs(Width, Vector[n], Ratio, Borderx, Bordery, xAxis)); }
				else { VecPrint.draw_image(n * Width, VecPrint.height() - Mid, ValueBarAbs(Width, Vector[n], Ratio, Borderx, Bordery, xAxis)); }
			}
		}
	}
	return (VecPrint);
}
CImg<unsigned char> PrintVectorBars(vector<double> Vector, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}
CImg<unsigned char> PrintVectorBarsAbs(vector<double> Vector, int Width, double Ratio, int Borderx, int Bordery, bool xAxis)
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}
CImg<unsigned char> PrintVectorBarsAbs(vector<double> Vector, int Width, double Ratio, int Borderx, int Bordery, bool xAxis, unsigned char Color[3])
{
	CImg<unsigned char> VecPrint;
	return (VecPrint);
}

// PLOTAR LISTA DE MEDIDAS DE MECANICA CLASSICA: // Parou de funcionar depois que mechi em algo
CImg<unsigned char> PrintVelAclNtnMntJlWt(VelAclNtnMntJlWt Class, double Scale)
{
	CImg<unsigned char> ImgVel = PrintVectorLine(Class.Vel, Scale, 127, 255, 0, 0); // GRÁFICOS:
	AdcTexto(ImgVel, round(ImgVel.width() * 0.5), round(ImgVel.height() * 0.5), to_string(Class.Vel.back()), 255, 0, 0);
	CImg<unsigned char> ImgAcl = PrintVectorLine(Class.Acell, Scale, 64, 0, 255, 0);
	AdcTexto(ImgAcl, round(ImgAcl.width() * 0.5), round(ImgAcl.height() * 0.5), to_string(Class.Acell.back()), 0, 255, 0);
	CImg<unsigned char> ImgNew = PrintVectorLine(Class.Newton, Scale, 0, 0, 0, 255);
	AdcTexto(ImgNew, round(ImgNew.width() * 0.5), round(ImgNew.height() * 0.5), to_string(Class.Newton.back()), 0, 0, 255);
	CImg<unsigned char> ImgMnt = PrintVectorLine(Class.Moment, Scale, 0, 255, 255, 0);
	AdcTexto(ImgMnt, round(ImgMnt.width() * 0.5), round(ImgMnt.height() * 0.5), to_string(Class.Moment.back()), 255, 255, 0);
	CImg<unsigned char> ImgJl = PrintVectorLine(Class.Joule, Scale, 127, 0, 255, 255);
	AdcTexto(ImgJl, round(ImgJl.width() * 0.5), round(ImgJl.height() * 0.5), to_string(Class.Joule.back()), 0, 255, 255);
	CImg<unsigned char> ImgWt = PrintVectorLine(Class.Watt, Scale, 64, 255, 0, 255);
	AdcTexto(ImgWt, round(ImgWt.width() * 0.5), round(ImgWt.height() * 0.5), to_string(Class.Watt.back()), 255, 0, 255);
	int h1 = ImgVel.height() + ImgAcl.height() + ImgNew.height(); // MEDIDAS
	int h2 = ImgMnt.height() + ImgJl.height() + ImgWt.height();
	int Heights = 0;
	if (h1 > h2) { Heights = h1; }
	else { Heights = h2; }
	int Widht = ImgVel.width() * 2;
	CImg<unsigned char> ImgAll(Widht, Heights, 1, 3, 0); // DESENHA
	ImgAll.draw_image(0, 0, ImgVel);
	ImgAll.draw_image(0, ImgVel.height(), ImgAcl);
	ImgAll.draw_image(0, ImgVel.height() + ImgAcl.height(), ImgNew);
	ImgAll.draw_image(Widht, 0, ImgMnt);
	ImgAll.draw_image(Widht, ImgMnt.height(), ImgJl);
	ImgAll.draw_image(Widht, ImgMnt.height() + ImgJl.height(), ImgWt);
	return(ImgAll); // RETURN
}

// VER DADOS NA MATRIZ (COUT):
void VerMatriz(vector<double> Matrix, int i, int j)
{
	cout << "Matriz[nij]:\n";
	for (int ni = 0; ni < i; ++ni) { for (int nj = 0; nj < j; ++nj) { int nij = nj + (ni * j); { cout << " | " << Matrix[nij]; if (nj == j - 1) { cout << endl; } } } }
}

// IMAGENS DA MATRIZ DOS VETORES:
// Salva uma imagem 'x' por 'y' baseado nos dados de um vetor:
CImg<unsigned char> SaveVectorImg(vector<Point3DFlt> Vector, int x, int y, double Rsize)
{
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		int R = Vector[n].x * 255; if (R > 255) { R = 255; } if (R < 0) { R = 0; }
		int G = Vector[n].y * 255; if (G > 255) { G = 255; } if (G < 0) { G = 0; }
		int B = Vector[n].z * 255; if (B > 255) { B = 255; } if (B < 0) { B = 0; }
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}
CImg<unsigned char> SaveVectorImg(vector<Point3DFlt> Vector, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		int R = Vector[n].x * 255;
		int G = Vector[n].y * 255;
		int B = Vector[n].z * 255;
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}

// Salva uma Imagem com a cor sendo função de 'x' e 'y':
CImg<unsigned char> SaveVectorInfoLRGB(vector<double> Vector, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		Point3D RGB = LinearRGB(Vector[n], 1.0, 1.0);
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}

	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}
CImg<unsigned char> SaveVectorInfoLRGB(vector<double> Vector, int x, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	if (x > Vector.size()) { x = Vector.size(); }
	if (x < 1) { x = 1; }
	int y = ceil(Vector.size() / (x * 1.0));
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		Point3D RGB = LinearRGB(Vector[n], 1.0, 1.0);
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}

	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}

// Salva uma Imagem com a cor sendo grayscale de '0' a '127':
CImg<unsigned char> SaveVectorInfo(vector<double> Vector, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		Point3D RGB; RGB.x = Vector[n] * 255; RGB.y = Vector[n] * 255; RGB.z = Vector[n] * 255;
		if (RGB.x > 255) { RGB.x = 255; } if (RGB.y > 255) { RGB.y = 255; } if (RGB.z > 255) { RGB.z = 255; }
		if (RGB.x < 0) { RGB.x = 0; } if (RGB.y < 0) { RGB.y = 0; } if (RGB.z < 0) { RGB.z = 0; }
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}

	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}
CImg<unsigned char> SaveVectorInfo(vector<double> Vector, int x, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	if (x > Vector.size()) { x = Vector.size(); }
	if (x < 1) { x = 1; }
	int y = ceil(Vector.size() / (x * 1.0));
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		Point3D RGB; RGB.x = Vector[n] * 255; RGB.y = Vector[n] * 255; RGB.z = Vector[n] * 255;
		if (RGB.x > 255) { RGB.x = 255; } if (RGB.y > 255) { RGB.y = 255; } if (RGB.z > 255) { RGB.z = 255; }
		if (RGB.x < 0) { RGB.x = 0; } if (RGB.y < 0) { RGB.y = 0; } if (RGB.z < 0) { RGB.z = 0; }
		unsigned char Clr[] = { RGB.x, RGB.y, RGB.z };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}

	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
}

// Salva uma Imagem com a cor sendo função de 'y' dividido em 3 partes, de vermelho a azul:
CImg<unsigned char> SaveVectorInfoTriClr(vector<double> Vector, double Rsize)
{
	double SqrtVec = sqrt(Vector.size());
	int x = round(SqrtVec);
	int y;
	if (SqrtVec / round(SqrtVec) == 1) { y = round(SqrtVec); }
	else { y = ceil(sqrt(Vector.size())); }
	CImg<unsigned char> ResultImg(x, y, 1, 3, 0);
	int Countx = 0, County = 0;
	for (int n = 0; n < Vector.size(); ++n)
	{
		int R, G, B;
		if (abs(Vector[n]) < 0.333333333) { R = 255; G = round((abs(Vector[n]) * 3) * 160); B = round((abs(Vector[n]) * 3) * 160); }
		else if (abs(Vector[n]) > 0.666666667) { R = round(((abs(Vector[n]) - 0.666666667) * 3) * 160); G = round(((abs(Vector[n]) - 0.666666667) * 3) * 160); B = 255; }
		else { R = round(((abs(Vector[n]) - 0.33333333) * 3) * 160); G = 255; B = round(((abs(Vector[n]) - 0.33333333) * 3) * 160); }
		unsigned char Clr[] = { R, G, B };
		ResultImg.draw_point(Countx, County, Clr);
		++Countx;
		if (Countx == x) { Countx = 0; ++County; }
	}
	if (Rsize != 1.0) { Resize(ResultImg, round(x * Rsize), round(y * Rsize), 6); }
	return(ResultImg);
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
	int Borda; // Distancia da margem
	int Largura, Altura; // Medidas da imagem
	int Offy; // Offset para resumir texto dos calculos
	int x[3], y[3]; // Coordenadas de acordo com escalas, bordas, altura e largura
	Point Coord[3], SclCrd[3], Midpoint[3], Circumcenter; // Cordenada dos triangulos, Cordenada com Scale, Coordenada dos midpoints e do Circumcentro
	unsigned char Clr[3]; // Cor
	double Scale;
	bool LRGB;
	double a, b, c, h, gamma, beta, alpha, area, perimetro, bisa, bisb, bisc, inradius, IA, IB, IC;

	// OUTPUT:
	CImg<unsigned char> TriOut;
	void CleanImg() { CImg<unsigned char> T; TriOut = T; } // CLEAN

	// ##################### CONSTRUTORES #####################
	TriPrint(Triangulo TriInput, double ScaleRto, int R, int G, int B)
	{
		Borda = 25; Largura = ceil(ScaleRto * (TriInput.Base + TriInput.Base0)) + (Borda * 2); Altura = ceil(TriInput.Alt * ScaleRto) + (Borda * 2);
		Offy = Altura - Borda; // O fim vertical da imagem se não contar a borda
		x[0] = Borda + (ScaleRto * TriInput.Coord[0].x); x[1] = Borda + (ScaleRto * TriInput.Coord[1].x); x[2] = Borda + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		Clr[0] = R; Clr[1] = G; Clr[2] = B;
		CImg<unsigned char> TO(Largura, Altura, 1, 3, 0); TriOut = TO; // Output
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
	}	
	TriPrint(Triangulo TriInput, double ScaleRto)
	{
		Borda = 25; Largura = ceil(ScaleRto * (TriInput.Base + TriInput.Base0)) + (Borda * 2); Altura = ceil(TriInput.Alt * ScaleRto) + (Borda * 2);
		Offy = Altura - Borda; // O fim vertical da imagem se não contar a borda
		x[0] = Borda + (ScaleRto * TriInput.Coord[0].x); x[1] = Borda + (ScaleRto * TriInput.Coord[1].x); x[2] = Borda + (ScaleRto * TriInput.Coord[2].x); // CORDENADAS X
		y[0] = Offy - (ScaleRto * TriInput.Coord[0].y); y[1] = Offy - (ScaleRto * TriInput.Coord[1].y); y[2] = Offy - (ScaleRto * TriInput.Coord[2].y); // CORDENADAS Y
		Clr[0] = 191; Clr[1] = 127; Clr[2] = 159;
		CImg<unsigned char> TO(Largura, Altura, 1, 3, 0); TriOut = TO; // Output
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
	}
	// ##################### ##################### #####################

	// IMPRIME PERIMETRO DO TRIANGULO:
	void TriPeriPrint(bool AddVert, bool AddText, bool AddAlt)
	{
		Linhaxy(TriOut, x[0], y[0], x[1], y[1], 255, 0, 127, LRGB); // a -> "_"
		Linhaxy(TriOut, x[1], y[1], x[2], y[2], 255, 0, 127, LRGB); // c -> "\"
		Linhaxy(TriOut, x[2], y[2], x[0], y[0], 255, 0, 127, LRGB); // b -> "/"
		int R = Clr[0], G = Clr[1], B = Clr[1];
		if (AddText)
		{
			AdcTexto(TriOut, 16, y[0] - 8, "a: " + to_string(a), R, G, B); // A
			AdcTexto(TriOut, 16, y[0], "Gamma: " + to_string(gamma), 255 - R, 255 - G, 255 - B); // GAMMA
			AdcTexto(TriOut, round(Largura * 0.75), y[1] - 8, "c: " + to_string(c), R, G, B); // C, Algo misteriosamente deu errado
			AdcTexto(TriOut, round(Largura * 0.75), y[1], "Beta: " + to_string(beta), 255 - R, 255 - G, 255 - B); // BETA
			AdcTexto(TriOut, round(Largura * 0.5), Offy - ((SclCrd[2].y) - 8), "b: " + to_string(b), R, G, B); // B
			AdcTexto(TriOut, round(Largura * 0.5), Offy - ((SclCrd[2].y) - 16), "Alpha: " + to_string(alpha), 255 - R, 255 - G, 255 - B); // ALPHA
			AdcTexto(TriOut, round(Largura * 0.5), Altura * 0.5, "Area: " + to_string(area), 255, 127, 127); // AREA
			AdcTexto(TriOut, round(Largura * 0.5), (Altura * 0.5) + 8, "Peri.: " + to_string(perimetro), 127, 255, 127); // PERIMETRO
		}
		if (AddVert)
		{
			Clr[0] = 255; Clr[1] = 0; Clr[2] = 0; // Adicionando vértices
			AdcVert(TriOut, x[0], y[0], 3, Clr);
			Clr[0] = 0; Clr[1] = 255; Clr[2] = 0;
			AdcVert(TriOut, x[1], y[1], 3, Clr);
			Clr[0] = 0; Clr[1] = 0; Clr[2] = 255;
			AdcVert(TriOut, x[2], y[2], 3, Clr);
			Clr[0] = R; Clr[1] = G; Clr[2] = B; // Volta a cor normal
		}
		if (AddAlt)
		{
			Linhaxy(TriOut, (SclCrd[2].x) + Borda, Offy, (SclCrd[2].x) + Borda, Offy - round(Scale * h), 127, 127, 127, false);
			if (AddText)
			{ int px = x[2] - 64; if (px < Largura * 0.33) { px += 80; } AdcTexto(TriOut, px, Offy - round(Scale * h * 0.5) - 8, "Height: " + to_string(h), 127, 127, 127); }
			if (AddVert) { unsigned char Color[] = { 127, 127, 127 }; AdcVert(TriOut, (SclCrd[2].x) + Borda, Offy, 3, Color); }
		}
	}

	// IMPRIME LINHAS BISETORAS:
	void TriBisectorPrint(bool AddText)
	{
		// ####### Imprime Linha Bisetora #######
		double Angle = 0;
		if (gamma <= 90) { Angle = Ang2Rad(beta + (alpha * 0.5)); }
		else { Angle = Ang2Rad(beta + (alpha * 0.5)); }
		Linha(TriOut, bisa * Scale, Angle, x[2], y[2], false, 0, 0, 255, false);
		if (gamma <= 90) { Angle = Ang2Rad(180 + (beta * 0.5)); }
		else { Angle = Ang2Rad(180 + (beta * 0.5)); }
		Linha(TriOut, bisb * Scale, Angle, x[1], y[1], false, 0, 0, 255, false);
		if (gamma <= 90) { Angle = Ang2Rad(360 - (gamma * 0.5)); }
		else { Angle = Ang2Rad(360 - (gamma * 0.5)); }
		Linha(TriOut, bisc * Scale, Angle, x[0], y[0], false, 0, 0, 255, false);
		if (AddText)
		{
			AdcTexto(TriOut, round(Largura * 0.5), Offy - ((SclCrd[2].y) - 24), "BisA: " + to_string(bisa), 0, 0, 255);
			AdcTexto(TriOut, round(Largura * 0.75), y[1] - 16, "BisB: " + to_string(bisb), 0, 0, 255);
			AdcTexto(TriOut, 16, y[0] - 16, "BisC: " + to_string(bisc), 0, 0, 255);
		}
	}

	// IMPRIME INCIRCLE:
	void TriIncirclePrint(bool AddVert)
	{
		int Pixx = x[1] - (Scale * IB * cos(Ang2Rad(beta) * 0.5)), Pixy = y[0] - (Scale * IB * sin(Ang2Rad(beta) * 0.5));
		if (AddVert) { AdcVert(TriOut, Pixx, Pixy, 3, Clr); } // Incenter
		Circuloxy(TriOut, inradius * Scale, Pixx, Pixy);
	}

	// IMPRIME MIDPOINTS DO TRIANGULO (NÃO FUNCIONA, ARRUMAR, provavelmente pois o scale * midpoint fode tudo, tipo, se mid point for 1, o scale vai jogar o primeiro midpoint longe):
	void TriMidpointPrint()
	{
		AdcVert(TriOut, Borda + (Scale * Midpoint[0].x), Offy - (Scale * Midpoint[0].y), 3, Clr);
		AdcVert(TriOut, Borda + (Scale * Midpoint[1].x), Offy - (Scale * Midpoint[1].y), 3, Clr);
		AdcVert(TriOut, Borda + (Scale * Midpoint[2].x), Offy - (Scale * Midpoint[2].y), 3, Clr);
	}

	// IMPRIME TRIÂNGULO COM TODAS FUNÇÕES:
	void TriAllPrint(bool AddVert, bool AddText)
	{
		int R = Clr[0], G = Clr[1], B = Clr[1];
		TriPeriPrint(AddVert, AddText, true);
		TriBisectorPrint(AddText);
		TriIncirclePrint(AddVert);
		TriMidpointPrint();
		// ####### Imprime Linhas Medians #######		
		// ####### Circumcentro #######
		Clr[0] = 255; Clr[1] = 0; Clr[2] = 255;
		AdcVert(TriOut, (Scale * Circumcenter.x) + Borda, Offy - (Scale * Circumcenter.y), 3, Clr); // Circumcentro
		// ###################################
	}
};

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## IMAGENS ##############
// ###################################

// MIXA IMAGENS E PODE REMOVER FUNDO (Não esta ignorando cor, esta ignorando uma só variavel de cor, arrumar depois):
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1)
{
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, não vai pedir memória aonde não tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<unsigned char> Ret(Width, Height, 1, 3, 0);
	for (int n = 0; n < Height; ++n)
	{
		int Prog = round((n / Height) * 100.0);
		for (int m = 0; m < Width; ++m)
		{
			Point3D RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n);
			unsigned char Clr[3];
			Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
			Clr[0] = round((RGB0.y + RGB1.y) * 0.5);
			Clr[0] = round((RGB0.z + RGB1.z) * 0.5);
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1, bool IgnoreBlack, bool IgnoreWhite)
{
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); } else { Width = Img0.width(); }
	if (Img0.height() > Img1.height()) { Height = Img1.height(); } else { Height = Img0.height(); }
	CImg<unsigned char> Ret(Width, Height, 1, 3, 0);
	for (int n = 0; n < Height; ++n)
	{
		int Prog = round((n / Height) * 100.0);
		for (int m = 0; m < Width; ++m)
		{
			Point3D RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n); // PEGA PIXEL
			unsigned char Clr[3];
			if (!IgnoreBlack && !IgnoreWhite) { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); Clr[1] = round((RGB0.y + RGB1.y) * 0.5); Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			else if (IgnoreBlack && !IgnoreWhite)
			{
				if (RGB0.x == 0) { Clr[0] = RGB1.x; }
				else { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); }
				if (RGB0.y == 0) { Clr[1] = RGB1.y; }
				else { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); }
				if (RGB0.z == 0) { Clr[2] = RGB1.z; }
				else { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			}
			else if (IgnoreWhite && !IgnoreBlack)
			{
				if (RGB0.x == 255) { Clr[0] = RGB1.x; }
				else { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); }
				if (RGB0.y == 255) { Clr[1] = RGB1.y; }
				else { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); }
				if (RGB0.z == 255) { Clr[2] = RGB1.z; }
				else { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			}
			else if (IgnoreWhite && IgnoreBlack)
			{
				if (RGB0.x == 0) { Clr[0] = RGB1.x; }
				else if (RGB0.x == 255) { Clr[0] = RGB1.x; }
				else { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); }
				if (RGB0.y == 0) { Clr[1] = RGB1.y; }
				else if (RGB0.y == 255) { Clr[1] = RGB1.y; }
				else { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); }
				if (RGB0.z == 0) { Clr[2] = RGB1.z; }
				else if (RGB0.z == 255) { Clr[2] = RGB1.z; }
				else { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			}
			//cout << "ClrR: " << Clr[0] << " | ClrG: " << Clr[1] << " | ClrB: " << Clr[2] << endl;
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1, unsigned char IgnoreColor[3])
{
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); } else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, não vai pedir memória aonde não tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); } else { Height = Img0.height(); }
	CImg<unsigned char> Ret(Width, Height, 1, 3, 0);
	for (int n = 0; n < Height; ++n)
	{
		int Prog = round((n / Height) * 100.0);
		for (int m = 0; m < Width; ++m)
		{
			Point3D RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n);
			unsigned char Clr[3];
			if (IgnoreColor[0] != RGB0.x) { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); } else { Clr[0] = RGB1.x; }
			if (IgnoreColor[1] != RGB0.y) { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); } else { Clr[1] = RGB1.y; }
			if (IgnoreColor[2] != RGB0.z) { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); } else { Clr[2] = RGB1.z; }
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1, int x, int y, unsigned char IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, não vai pedir memória aonde não tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<unsigned char> Ret(Width, Height, 1, 3, 0);
	for (int n = 0; n < Height; ++n)
	{
		for (int m = 0; m < Width; ++m)
		{
			if (InImg(Img0, n + y, m + x))
			{
				Point3D RGB0 = BitmapRGB(Img0, m + x, n + y), RGB1 = BitmapRGB(Img1, m, n);
				unsigned char Clr[3];
				if (IgnoreColor[0] != RGB0.x) { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); }
				else { Clr[0] = RGB1.x; }
				if (IgnoreColor[1] != RGB0.y) { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); }
				else { Clr[1] = RGB1.y; }
				if (IgnoreColor[2] != RGB0.z) { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
				else { Clr[2] = RGB1.z; }
				Ret.draw_point(m, n, Clr);
			}
		}
	}
	return (Ret);
}
CImg<unsigned char> DrawImageIgnClr(CImg<unsigned char> Img0, CImg<unsigned char> Img1, int x, int y, unsigned char IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	int Width = Img1.width(), Height = Img1.height();
	CImg<unsigned char> Ret = Img0;
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j + x >= Img0.width() - 1) { break; }
			Point3D RGB = BitmapRGB(Img1, j, i); if (IgnoreColor[0] != RGB.x || IgnoreColor[1] != RGB.y || IgnoreColor[2] != RGB.z)	{ unsigned char Clr[] = { RGB.x, RGB.y, RGB.z }; Ret.draw_point(j + x, i + y, Clr); }
		}
		if (i + y >= Img0.height() - 1) { break; }
	}
	return (Ret);
}
CImg<unsigned char> DrawImageIgnClrCout(CImg<unsigned char> Img0, CImg<unsigned char> Img1, int x, int y, unsigned char IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	int Width = Img1.width(), Height = Img1.height();
	CImg<unsigned char> Ret = Img0;
	cout << "i:\n";
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j + x >= Img0.width() - 1) { break; }
			Point3D RGB = BitmapRGB(Img1, j, i); if (IgnoreColor[0] != RGB.x || IgnoreColor[1] != RGB.y || IgnoreColor[2] != RGB.z) { unsigned char Clr[] = { RGB.x, RGB.y, RGB.z }; Ret.draw_point(j + x, i + y, Clr); }
		}
		if (i + y >= Img0.height() - 1) { break; }
		cout << " | " << i;
	}
	cout << endl;
	return (Ret);
}
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## MISC:
// SIEVE OF ERATOSTHENES:
CImg<unsigned char> SieveEratosthenes(int n)
{
	if (n < 10) { n = 10; }
	vector<CImg<unsigned char>> Squares;
	vector<Point3D> RGBs;
	int Lines = ceil(n / 10.0);
	CImg<unsigned char> Ret(10 * 32, Lines * 32, 1, 3, 0);
	for (int m = 0; m < 4; ++m)
	{
		Point3D RGB = LinearRGB(m / 4.0, 1, 1);
		RGBs.push_back(RGB);
	}
	for (int m = 1; m <= n; ++m)
	{
		// Cores:
		unsigned char Color[] = { 0, 0, 0 };
		if (0 == m % 2) { Color[0] = RGBs[0].x; Color[1] = RGBs[0].y; Color[2] = RGBs[0].z;	}
		if (0 == m % 3) { Color[0] = RGBs[1].x; Color[1] = RGBs[1].y; Color[2] = RGBs[1].z; }
		if (0 == m % 5) { Color[0] = RGBs[2].x; Color[1] = RGBs[2].y; Color[2] = RGBs[2].z; }
		if (0 == m % 7) { Color[0] = RGBs[3].x; Color[1] = RGBs[3].y; Color[2] = RGBs[3].z; }
		CImg<unsigned char> Square(31, 31, 1, 3, 0);
		Square = AdcBorda(Square, 1, 1, 255 - Color[0], 255 - Color[1], 255 - Color[2]);
		// Fill:
		FillArea(Square, 15, 15, Color[0], Color[1], Color[2]);
		// Texto:
		AdcTexto(Square, 7, 15, to_string(m), 255 - Color[0], 255 - Color[1], 255 - Color[2]);
		Squares.push_back(Square);
	}
	for (int m = 0; m < Lines; ++m) { for (int k = 0; k < 10; ++k) { if (k + (m * 10) < Squares.size()) { Ret.draw_image(k * 32, m * 32, Squares[k + (m * 10)]); } } }
	return(Ret);
}

// RAY INFO:
CImg<unsigned char> RayInfo(double Degrees, int ImgSize)
{
	if (ImgSize < 192) { ImgSize = 192; }
	CImg<unsigned char> I(ImgSize, ImgSize, 1, 3, 0);
	double Rad = Ang2Rad(Degrees);
	int r = round(0.5 * ImgSize);
	Linhaxy(I, r, 0, r, ImgSize, 64, 64, 64, false); Linhaxy(I, 0, r, ImgSize, r, 64, 64, 64, false); // Cruz
	Circuloxy(I, r, r, r);
	Raio(I, r, r, r, Rad, true, false);
	Linhaxy(I, r, r, ceil(cos(Rad) * r) + r, r, 255, 0, 0, false);
	Linhaxy(I, r, r, r, r - ceil(sin(Rad) * r), 0, 255, 0, false);
	Linhaxy(I, r, r - ceil(sin(Rad) * r), ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), 255, 0, 0, false);
	Linhaxy(I, ceil(cos(Rad) * r) + r, r, ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), 0, 255, 0, false);
	string Sin = "Sin: " + to_string(sin(Rad)), Cos = "Cos: " + to_string(cos(Rad)), Tan = "Tan: " + to_string(tan(Rad)),
		Cot = "Cot: " + to_string(cot(Rad)), Sec = "Sec: " + to_string(sec(Rad)), Csc = "Csc: " + to_string(csc(Rad)),
		Ver = "Versin: " + to_string(versin(Rad)), Exsec = "ExSec: " + to_string(exsec(Rad)), Excsc = "ExCsc: " + to_string(excsc(Rad)), Crd = "Cord: " + to_string(crd(Rad));
	int Line = 8, Txtpx = r - 24;
	AdcTexto(I, Txtpx, r + Line, Sin, 0, 255, 0); AdcTexto(I, Txtpx, r + Line * 2, Cos, 255, 0, 0);	AdcTexto(I, Txtpx, r + Line * 3, Tan, 0, 0, 255);
	AdcTexto(I, Txtpx, r + Line * 4, Cot, 255, 255, 0);	AdcTexto(I, Txtpx, r + Line * 5, Sec, 0, 255, 255);	AdcTexto(I, Txtpx, r + Line * 6, Csc, 255, 0, 255);
	AdcTexto(I, Txtpx, r + Line * 7, Ver, 127, 255, 127); AdcTexto(I, Txtpx, r + Line * 8, Exsec, 255, 127, 127); AdcTexto(I, Txtpx, r + Line * 9, Excsc, 127, 127, 255);
	AdcTexto(I, Txtpx, r + Line * 10, Crd, 255, 255, 127);
	AdcTexto(I, r + 24, r - Line * 2, "ANGLE: " + to_string(Degrees), 255, 255, 255);
	return(I);
}

// ################################################# FIM ####################################################################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

class Standard
{
public:
	int GUIGridx = 800, GUIGridy = 640;
	void GetStandardImage(CImg<unsigned char>& Img) { CImg<unsigned char> Standard(GUIGridx, GUIGridy, 1, 3, 0); Img = Standard; }

	// Colors:
	int BCCR = 277, BCCG = 0, BCCB = 127; // BCC = Button Countour Color.
	int BICR = 32, BICG = 32, BICB = 32; // BIC = Button Inside Color.
	int TXTR = 255, TXTG = 0, TXTB = 127; // Text Color.
};
// Fonte:
//CImgList<unsigned char> font(const unsigned int font_height = 19, const bool variable_size = true);

// ################################################# FIM ####################################################################################

class YSXCIMAIN
{
public:
	// #################################################
	// #################################################
	YSXCIMAIN(int Grdx, int Grdy)
	{
		cout << "YSXCIMAIN CARREGANDO!\n";
		GradeX = Grdx; GradeY = Grdy;
		Sizex = GradeX + (BordaY * 2), Sizey = GradeY + (BordaX * 2);
		CImg<unsigned char> Img(Sizex, Sizey, 1, 3, 0); Imagem = Img;
		CImg<unsigned char> CB(64, 64, 1, 3, 0); Bitmap = CB;
		cout << "YSXCIMAIN CRIADO!\n";
	}
	YSXCIMAIN(CImg<unsigned char> Img, CImg<unsigned char> Bmp)
	{
		cout << "YSXCIMAIN CARREGANDO!\n";
		Imagem = Img; Bitmap = Bmp;
		GradeX = Img.width(); GradeY = Img.height();
		Sizex = GradeX + (BordaY * 2), Sizey = GradeY + (BordaX * 2);
		cout << "YSXCIMAIN CRIADO!\n";
	}
	~YSXCIMAIN() { cout << "YSXCIMAIN FOI DELETADO!\n"; }
	// #################################################
	// #################################################
	// Gráfico:
	int BordaX = 1, BordaY = 1; // Deixar um espaço de 175 pixeis.
	int GradeX, GradeY; // Grade da plotagem, numero para dividirr a dimensão da função.
	int R = 255, G = 0, B = 127; // Cor da linha da função.
	int Rbrd = 255, Gbrd = 255, Bbrd = 255; // RGBborda.
	int Rbrr = 77, Gbrr = 77, Bbrr = 77; // RGBbarra.
	int Rbkg = 200, Gbkg = 200, Bbkg = 200; // RGBbackground.
	int Sizex, Sizey; // Sizex = GradeX + (BordaY * 2), Sizey = GradeY + (BordaX * 2);

	// Matematica:
	int AreaImg = ((BordaX + BordaY) * 2) + (GradeX*GradeY); // Area da Imagem (Pixeis)
	int AreaPlot = GradeX * GradeY; // Area da Plotagem (Pixeis)
	double xDiv; // Passos das funções.
	double Random = (rand() % 1000001) / 1000000;
	double Omega = 1; // Frequencia angular, sin(x * Omega)
	vector<string> ParseExp; // Expressões que passarão por uma classe que traduz algebraicamente retornando um valor.
	vector<int> PlyCoord; // Ainda pensando em/como colocar, salva um poligono.
	
	// Imagens:
	CImg<unsigned char> Imagem; // Imagem principal para modificações
	CImg<unsigned char> Bitmap;
	
	// #####################
	// ####### FUNÇÕES #######
	// #####################
	
	// ####### Funções Técnicas #######
	// VARIAVEIS:
	// Refaz variaveis de tamanho e não salva
	void RedoVar() { Sizex = GradeX + (BordaY * 2); Sizey = GradeY + (BordaX * 2); AreaImg = ((BordaX + BordaY) * 2) + (GradeX*GradeY); AreaPlot = GradeX * GradeY; }
	// Refaz variaveis de tamnho baseado em inputs:
	void NewVar(int NewX, int NewY)	{ GradeX = NewX; GradeY = NewY; RedoVar(); }
	// Refaz variaveis de tamnho baseado em uma imagem:
	void ImgVar(CImg<unsigned char> Reference) { GradeX = Reference.width(); GradeY = Reference.height(); RedoVar(); }
	// Refaz variaveis de tamanho e salva nova imagem:
	void RedoImg() { RedoVar(); CImg<unsigned char> ImagemConfig(Sizex, Sizey, 1, 3, 0); Imagem = ImagemConfig; }
	
	// CONFIGURAR:
	void Configurar(int Opção)
{
	cout << "####### CONFIGURAÇÕES #######\n";
	cout << "* Todo numero negativo será multiplicado por '-1'.\n\n";
	if (Opção == 0)
	{
		cout << "Padrão da grade é 350 x 350.\nAtual é " << GradeX << " x " << GradeY << ".\n";
		cout << "Você pode deixar 'y' ou 'x' igual a '0' se quiser fazer da imagem apenas barras de suas bordas.\n";
		cout << "Defina valor da GradeX:\n"; cin >> GradeX;	if (GradeX < 0) { GradeX = GradeX * -1; } Sizex = GradeX + (BordaY * 2); //Sizex = GradeX + (BordaX * 2);
		cout << "Defina valor da GradeY:\n"; cin >> GradeY;	if (GradeY < 0) { GradeY = GradeY * -1; } Sizey = GradeY + (BordaX * 2); //Sizey = GradeY + (BordaY * 2);
		cout << "Imagem(" << Sizex << ", " << Sizey << ", 1, 3, 0)\n";
	}
	if (Opção == 1)
	{
		cout << "Padrão das bordas são 'x = 1' e 'y = 1'.\nAtual é 'x = " << BordaX << "' e 'y = " << BordaY << "'.\n";
		cout << "Você pode deixar 'y' ou 'x' igual a '0' se quiser fazer da imagem apenas barras de suas bordas.\n";
		cout << "X: "; cin >> BordaX; if (BordaX < 0) { BordaX = BordaX * -1; }	Sizey = GradeY + (BordaX * 2); //Sizey = GradeY + (BordaY * 2);
		cout << "Y: "; cin >> BordaY; if (BordaY < 0) { BordaY = BordaY * -1; } Sizex = GradeX + (BordaY * 2); //Sizex = GradeX + (BordaX * 2);
		cout << "Imagem(" << Sizex << ", " << Sizey << ", 1, 3, 0)\n";
	}
	if (Opção == 2)
	{
		cout << "Defina R, G, B da plotadora respectivamente:\nR: "; cin >> R; if (R < 0) { R = R * -1; } cout << "G: "; cin >> G; if (G < 0) { G = G * -1; }
		cout << "B: "; cin >> B; if (B < 0) { B = B * -1; }
		cout << "Defina R, G, B das bordas respectivamente:\nR: "; cin >> Rbrd;	if (Rbrd < 0) { Rbrd = Rbrd * -1; }	cout << "G: "; cin >> Gbrd;	if (Gbrd < 0) { Gbrd = Gbrd * -1; }
		cout << "B: "; cin >> Bbrd;	if (Bbrd < 0) { Bbrd = Bbrd * -1; }
		cout << "Defina R, G, B das barras respectivamente:\nR: "; cin >> Rbrr;	if (Rbrr < 0) { Rbrr = Rbrr * -1; }	cout << "G: "; cin >> Gbrr;	if (Gbrr < 0) { Gbrr = Gbrr * -1; }
		cout << "B: "; cin >> Bbrr;	if (Bbrr < 0) { Bbrr = Bbrr * -1; }
		cout << "Defina R, G, B do plano de fundo respectivamente:\nR: "; cin >> Rbkg; if (Rbkg < 0) { Rbkg = Rbkg * -1; } cout << "G: "; cin >> Gbkg;
		if (Gbkg < 0) { Gbkg = Gbkg * -1; }	cout << "B: "; cin >> Bbkg;	if (Bbkg < 0) { Bbkg = Bbkg * -1; }
	}

	// Sobreescreve "Imagem":
	CImg<unsigned char> ImagemConfig(Sizex, Sizey, 1, 3, 0);
	Imagem = ImagemConfig;
}

	// VERIFICA GRADE:
	bool InGrid(int y, int x) // Verifica se os pixels estão dentro da parte utilizavel da imagem.
	{ if (y > BordaX && y < GradeY + BordaX) { if (x > BordaY && x < GradeX + BordaY) { return (true); } else { return (false); } } else { return (false); } }
	bool InGridy(int y) { if (y > BordaX && y < GradeY + BordaX) { return (true); } else { return (false); } }
	bool InGridx(int x) { if (x > BordaY && x < GradeX + BordaY) { return (true); } else { return (false); }	}

	// ####### Funções Graficas #######

	// #################################################
	// ####### DECLARAÇÕES:
	// #################################################
	// #####################
	// ####### FUNÇÕES MATEMATICAS:
	// #####################
	// FUNÇÃO DE LINHA:
	void FuncLinx(double a, double b, double x1, double x2, int EspessuraFx, bool LRGB)
	{
		// Input:
		double x, y;
		if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.
		int TR = R, TG = G, TB = B;


		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		// PLOTADORA:
		for (double xn = BordaY; xn < GradeX + BordaY; ++xn)
		{
			double xdiv = (xn - (BordaY)) / (GradeX - 1);
			x = x1 + ((x2 - x1) * xdiv);

			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
			y = Linex(x, a, b); // ESCREVA AQUI SUA FUNÇÃO.

			// Y e GradeY:
			double yg = BordaX + ((GradeY - 2) - (((y + 1) * 0.5) * (GradeY - 3))); // GRADEY
			int ygRound = round(yg);

			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
			// Adiciona coluna de espessura:
			if (EspessuraFx != 0)
			{
				for (int yEspsr = 1; yEspsr <= EspessuraFx; ++yEspsr)
				{
					if (InGridy(ygRound + yEspsr))
					{
						unsigned char clrdrv[] = { round(255 - TR) / (yEspsr + 1), round((255 - TG) / 1.5) / (yEspsr + 1), round((255 - TB) / 1.5) / (yEspsr + 1) };
						unsigned char color[] = { round(TR / (yEspsr + 1)), round(TG / (yEspsr + 1)), round(TB / (yEspsr + 1)) };
						Imagem.draw_point(xn, ygRound + yEspsr, color);
						if (InGridy(ygRound - yEspsr))
						{
							Imagem.draw_point(xn, ygRound - yEspsr, color);
						}
					}
				}
			}

			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
			// Plotagem:
			if (LRGB == true) { Point3D RGB = LinearRGB(xdiv, 1, 1); TR = RGB.x; TG = RGB.y; TB = RGB.z; }

			if (ygRound < Sizey - BordaX)
			{
				if (ygRound > BordaX)
				{
					unsigned char color[] = { TR, TG, TB }; // Cor do gráfico.
					Imagem.draw_point(xn, ygRound, color);
				}
			}
			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		}
	}

	// PLOTAR F(X):
	void Funcx(double Métrica, bool UsarMétrica, double a, double x1, double x2, int EspessuraFx, int PlotDrv, bool LRGB)
{
	// Input:
	double x, y, ydrv;

	int TR = R, TG = G, TB = B;
		
	int ygdrv = 0;
	// MUDE SEMPRE QUE ADICIONAR OUTRAS FORMULAS:
	if (PlotDrv > 2) { PlotDrv = 2; }

	if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.

	// ##### Começa aqui #####

	// Marca Métrica:
	if (UsarMétrica == true)
	{
		double BarraN;
		for (BarraN = -a; BarraN <= a; BarraN = BarraN + Métrica)
		{
			int ygBarra = round(BordaX + ((GradeY - 2) - ((((BarraN + a) * 0.5) / a) * (GradeY - 3))));
			if (BarraN != 0.0 || BarraN != -a || BarraN != a)
			{
				if (BarraN >= 0) { AdcTexto(Imagem, round(Sizex * 0.5), ygBarra + 4, to_string(BarraN), Rbrr, Gbrr, Bbrr); }
				else { AdcTexto(Imagem, round(Sizex * 0.5), ygBarra - 16, to_string(BarraN), Rbrr, Gbrr, Bbrr); }
				if (ygBarra < Sizey - BordaX && ygBarra > BordaX) { AdcBarra(Imagem, true, BordaY, GradeX + BordaY - 1, 1, ygBarra, Rbrr, Gbrr, Bbrr); }
			}
			if (BarraN == 0.0 || BarraN == -a || BarraN == a)
			{
				if (BarraN >= 0) { AdcTexto(Imagem, round(Sizex * 0.5), ygBarra + 4, to_string(BarraN), 255, 127, 127); }
				else { AdcTexto(Imagem, round(Sizex * 0.5), ygBarra - 16, to_string(BarraN), 255, 127, 127); }
				if (ygBarra < Sizey - BordaX && ygBarra > BordaX) { AdcBarra(Imagem, true, BordaY, GradeX + BordaY - 1, 1, ygBarra, 255, 127, 127); }
			}
		}
	}

	// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
	// PLOTADORA:
	for (double xn = BordaY; xn < GradeX + BordaY; ++xn)
	{
		double xdiv = (xn - (BordaY)) / (GradeX - 1);
		x = x1 + ((x2 - x1) * xdiv);

		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		// ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA #######
		y = MiniForm(x, Omega); // ESCREVA AQUI SUA FUNÇÃO.
		// ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA #######
		if (PlotDrv == 1) { ydrv = (1 / a) * Derivative(x, Omega); /*FuncLinx(ydrv, y - (x * ydrv), x1, x2, round(EspessuraFx * 0.25), LRGB);*/ } // Derivativo
		if (PlotDrv == 2) { ydrv = (1 / a) * d2xdt2(x, Omega); } // Second-order derivative

		if (PlotDrv > 0) { ygdrv = BordaX + ((GradeY - 2) - ((((ydrv + a) * 0.5) / a) * (GradeY - 3))); } // GRADEY
		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		cout << "!!! f(" << x << ") = " << y << endl;
		if (PlotDrv > 0) { cout << "ydrv: " << ydrv << " | ygdrv: " << ygdrv << endl; }

		// Y e GradeY:
		y *= 1.0 / a;
		double yg = BordaX + ((GradeY - 2) - (((y + 1) * 0.5) * (GradeY - 3))); // GRADEY | Formula pode ser: "(((y + a) * 0.5) / a)"
		int ygRound = round(yg);

		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		if (LRGB == true) { Point3D RGB = LinearRGB(xdiv, 1, 1); TR = RGB.x; TG = RGB.y; TB = RGB.z; }
		// Adiciona coluna de espessura:
		if (EspessuraFx != 0)
		{
			for (int yEspsr = 1; yEspsr <= EspessuraFx; ++yEspsr)
			{
				if (InGridy(ygRound + yEspsr))
				{
					unsigned char clrdrv[] = { round(255 - TR) / (yEspsr + 1), round((255 - TG) / 1.5) / (yEspsr + 1), round((255 - TB) / 1.5) / (yEspsr + 1) };
					if (InGridy(ygdrv + yEspsr) && PlotDrv > 0)
					{
						Imagem.draw_point(xn, ygdrv + yEspsr, clrdrv);
						if (InGridy(ygdrv - yEspsr))
						{
							Imagem.draw_point(xn, ygdrv - yEspsr, clrdrv);
						}
					}
					unsigned char color[] = { round(TR / (yEspsr + 1)), round(TG / (yEspsr + 1)), round(TB / (yEspsr + 1)) };
					Imagem.draw_point(xn, ygRound + yEspsr, color);
					if (InGridy(ygRound - yEspsr))
					{
						Imagem.draw_point(xn, ygRound - yEspsr, color);
					}
				}
			}
		}

		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		// Plotagem:

		if (ygRound < Sizey - BordaX)
		{
			if (ygRound > BordaX)
			{
				if (InGridy(ygdrv) && PlotDrv > 0)
				{
					unsigned char clrdrv[] = { round(255 - TR), round((255 - TG) / 1.5), round((255 - TB) / 1.5) }; // Cor do derivativo
					Imagem.draw_point(xn, ygdrv, clrdrv);
				}
				unsigned char color[] = { TR, TG, TB }; // Cor do gráfico.
				Imagem.draw_point(xn, ygRound, color);
				
				cout << "PLOTTED: xn: " << xn << ", ygRound: " << ygRound << endl;
			}
		}
		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
	}

	// #######

	cout << "####### Fim! #######\n\n";
}
	
	// PLOTAR F(X, Y): // Lembrar de modificar essa função para 'z' ser cor;
	void Funcxy(double a, double x1, double x2, double y1, double y2, int PlotDrv)
	{
		// Input:
		double x, y, z;
		int TR = R, TG = G, TB = B;

		int zdrv, zgdrv = 0;
		// MUDE SEMPRE QUE ADICIONAR OUTRAS FORMULAS:
		if (PlotDrv > 2) { PlotDrv = 2; }

		if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.

		// ##### Começa aqui #####
			
		// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		// PLOTADORA:
		//for (double yn = GradeY + BordaX; yn > BordaX; --yn)
		for (double yn = BordaX; yn < GradeY + BordaX; ++yn)
		{
			double ydiv = (yn - (BordaX)) / (GradeY - 1);
			y = y1 + ((y2 - y1) * ydiv);
			cout << "y = " << y << " | yn = " << yn << endl;
			for (double xn = BordaY; xn < GradeX + BordaY; ++xn)
			{
				double xdiv = (xn - (BordaY)) / (GradeX - 1);
				x = x1 + ((x2 - x1) * xdiv);

				// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
				// ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA #######
				z = NonStatWaveFunc(a / (x + 1), x2, x, y, Omega, ((x + y) * 0.125)); // ESCREVA AQUI SUA FUNÇÃO.
				z *= 1.0 / a;
				// ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA #######
				if (PlotDrv == 1) { zdrv = ((1 / a) * Derivative(x, Omega * 7 * (y / 3))) * ((1 / a) * ((cos((y + 0.000000001) * 0.5) - cos(y * 0.5)) / 0.000000001)); } // Derivativo
				if (PlotDrv == 2) { zdrv = (1 / a) * WaveEq(x, Omega); } // Wave Equation.

				if (PlotDrv > 0) { zgdrv = BordaX + ((GradeY - 2) - ((((zdrv + a) * 0.5) / a) * (GradeY - 3))); } // GRADEY
				// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
								
				// Plotagem:
				Point3D RGB = LinearRGB((z + 1) * 0.5, 1.0, 1.0); TR = RGB.x; TG = RGB.y; TB = RGB.z;
				unsigned char Clr[] = { TR, TG, TB };
				Imagem.draw_point(xn, yn, Clr);

				// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
			}
		}

		// #######

		cout << "####### Fim! #######\n\n";
	}

	// PLOTAR POLAR:
	void Polar(double Amp, double Tht1, double Tht2, int div, bool Deriv, bool Comraio, bool Tri, bool Borda, bool LRGB)
{
	int TR = R, TG = G, TB = B;
	double y, x;
	double r, Theta;
	int xzero = floor((GradeX / 2) + (BordaY / 1.33333)), yzero = Sizey - (floor((GradeY / 2) + (BordaX)));
	int Step = 0;
	double tttmp; if (Tht1 < 0) { tttmp = (Tht1 * -1) + Tht2; } else { tttmp = Tht2 - Tht1; } tttmp = tttmp / div;
	vector<double> DIVS(div);
	for (int n = 0; n < div; ++n) { DIVS[n] = (tttmp * n) + Tht1; }
	if (Comraio) // Adiciona raios
	{
		for (int n = 0; n < div; ++n)
		{
			double r = Amp * (sin(DIVS[n] * 7)); if (r < 0) { r *= -1; }
			if (LRGB) { Raio(Imagem, r, xzero, yzero, DIVS[n], Tri, Borda); }
			else { Raio(Imagem, r, xzero, yzero, DIVS[n], Tri, Borda, TR, TG, TB); }
		}
	}
	AdcBarra(Imagem, false, BordaX, GradeY - 1, 1, xzero, 127, 127, 127);
	AdcBarra(Imagem, true, BordaY, GradeX - 1, 1, yzero, 127, 127, 127);
	// Plotadora
	for (Theta = Tht1; Theta <= Tht2; Theta = Theta + 0.0001)
	{
		double Progresso = (Theta / Tht2);
		// ### ESCREVA AQUI A SUA FORMULA:
		r = Amp * MiniForm(Theta, 1);
		// ### Eq. Diferencial:
		double rdrv;
		if (Deriv == 1) { rdrv = Amp * Derivative(Theta, Omega); } // Derivativo
		if (Deriv == 2) { rdrv = Amp * WaveEq(Theta, Omega); } // Wave Equation.
		// #######

		y = round(r * sin(Theta));
		x = round(r * cos(Theta));
		int CorrectX = x + xzero;
		int CorrectY = Sizey - (y + yzero);

		// Plota Derivativo:
		if (Deriv > 0)
		{
			double Thisyd = round(rdrv * sin(Theta)); double Thisxd = round(rdrv * cos(Theta));
			int CorrectXd = Thisxd + xzero; int CorrectYd = Sizey - (Thisyd + yzero);
			if (InGrid(CorrectYd, CorrectXd))
			{
				if (LRGB == true) { Point3D RGB = LinearRGB(Progresso, 1, 1); TR = RGB.x; TG = RGB.y; TB = RGB.z; }
				unsigned char color[] = { round((255 - TR) * 0.5), round((255 - TG) * 0.5), round((255 - TB) * 0.5) }; Imagem.draw_point(CorrectXd, CorrectYd, color);
			}
		}

		// Plota Polar:
		if (InGrid(CorrectY, CorrectX))
		{
			if (LRGB == true) { Point3D RGB = LinearRGB(Progresso, 1, 1); TR = RGB.x; TG = RGB.y; TB = RGB.z; }
			unsigned char color[] = { TR, TG, TB };
			Imagem.draw_point(CorrectX, CorrectY, color);
		}
	}
}
	
	// #################################################

		// PLOTAR PARAMETRICO:
	void Parametrico(double r, double Ini, double ThisTau, bool LRGB)
{
	int TR = R, TG = G, TB = B;
	double y, x;
	double Rad;
	int xzero = floor((GradeX / 2) + BordaY), yzero = Sizey - (floor((GradeY / 2) + BordaX));
	if (ThisTau < Ini) { double temp = ThisTau; ThisTau = Ini; Ini = temp; }

	for (Rad = Ini; Rad <= ThisTau; Rad = Rad + 0.00001)
	{
		// Formulas para brincar...
		/* x = round(((cos(Rad) + cos(6.28318 - 3 * Rad + (6.058785))) / 2) * r);
		-- x = ((((r * 3) - r) * cos(Rad)) + (r * cos((((r * 3) - r) / r) * Rad)));
		-- x = (sin(Rad) * (pow(Exp, cos(Rad)) - (2 * cos(4 * Rad) - (pow(sin(Rad / 12), 5))))) * r; // Butterfly
		-- x = r * (2.1 + 1) * cos(Rad) - (r * cos((2.1 + 1) * Rad)); // Epicycloid
		*/
		x = r * (2.1 + 1) * cos(Rad) - (r * cos((2.1 + 1) * Rad));
		/* y = round(((sin(6.28318 - Rad) + sin (3 * Rad + (4.0 / 7))) / 2) * r);
		-- y = round(((sin(Rad) + sin(3 * Rad + (6.058785))) / 2) * r);
		-- y = round(((sin(Rad) + tan(3 * Rad + 6.283185)) / 2) * r);
		-- y = round(((tan(Rad) + cos(3 * Rad + 6.283185)) / 2) * r);
		-- y = ((((r * 3) - r) * sin(Rad)) - (r * sin((((r * 3) - r) / r) * Rad)));
		-- y = (cos(Rad) * (pow(Exp, cos(Rad)) - (2 * cos(4*Rad) - (pow(sin(Rad/12), 5))))) * r; // Butterfly
		-- y = r * (2.1 + 1) * sin(Rad) - (r * sin((2.1 + 1) * Rad)); // Epicycloid
		*/
		y = r * (2.1 + 1) * sin(Rad) - (r * sin((2.1 + 1) * Rad));

		y = round(y);
		x = round(x);
		double Progresso = Rad / ThisTau;
		int CorrectX = x + xzero;
		int CorrectY = Sizey - (y + yzero);

		if (CorrectY >= BordaX && CorrectY < GradeY + BordaX)
		{
			if (CorrectX >= BordaY && CorrectX < GradeX + BordaY)
			{
				if (LRGB == true) { Point3D RGB = LinearRGB(Progresso, 1, 1); TR = RGB.x; TG = RGB.y; TB = RGB.z; }
				unsigned char color[] = { TR, TG, TB };
				Imagem.draw_point(CorrectX, CorrectY, color);
			}
		}
	}
}

	// PLOTAR POLIGRAMA:
	// void Poligrama(){}

};


// ################################################# FIM ####################################################################################
#endif // SCPARSE_
