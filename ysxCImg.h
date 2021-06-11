#pragma once

#ifndef YSXCIMG_H
#define YSXCIMG_H

#include "CImg.h"
#include "ysxMath.h"
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <complex>

// #####################
// ####### By Sophia Cristina
// ####### Header made do some useful stuffs with 'CImg.h'
// #####################

using namespace cimg_library; // UNCOMMENT IF YOU ARE HAVING A PROBLEM

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	FAZER TODOS POSSIVEIS PLOTTERS ESCREVEREM NUMA IMAGEM DE INPUT;
// !!!!!!!	FAZER TODOS POSSIVEIS PLOTTERS ACEITAREM VECTORS COMO INPUT, E ASSIM ACABAR COM RDUNDANCIAS DE FUNÇÕES, TIPO "POLAR", "CIRCULO" E "TURN";
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	FUNÇÕES COM NOMES TIPO 'SaveBmp' AGORA SÃO 'SaveBMP';
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## DECLARAÇÕES:
CImg<unsigned char> DrawImageIgnClr(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
CImg<unsigned char> DrawImageIgnClrCout(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
bool InImg(CImg<unsigned char>, int, int);
void AdcVert(CImg<unsigned char>&, int, int, int, unsigned char[3]);
void AdcTexto(CImg<unsigned char>&, int, int, string, int, int, int);
CImg<unsigned char> ValueBarAbs(int, double, double, int, int, bool);
void Resize(CImg<unsigned char>&, int, int, int);
void FillArea(CImg<unsigned char>&, int, int, int, int, int);
void FillAll(CImg<unsigned char>&, int, int, int);
CImg<unsigned char> ExpandImg(CImg<unsigned char>, int, char);
CImg<unsigned char> JoinImg(CImg<unsigned char>, CImg<unsigned char>, bool);
// ###################################
// ###################################
// ############## TOOLS:
struct Pixel { unsigned int x; unsigned int y; unsigned char RGB[3]; };
// ###################################

// ###################################
// EXTRA:
#include "ysxCImgIncludes/ysxciColors.h"
#include "ysxCImgIncludes/ysxciPlotters.h"
#include "ysxCImgIncludes/ysxciUtils.h"
#include "ysxCImgIncludes/ysxciMisc.h"
// ###################################


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## TÉCNICOS:
// ABRIR:
CImg<unsigned char> OpenImg(string FileName) { CImg<unsigned char> Open(Str2Char(FileName).data()); return(Open); }

// SALVAR (Com uso de 'string to char', minha função que cria um vetor de char com um string, acho que cimg aceita só um 'char array'):
void SaveBMP(CImg<unsigned char> Image, string FileName) { Image.save_bmp(Str2Char(FileName).data()); }
void SavePNG(CImg<unsigned char> Image, string FileName) { Image.save_png(Str2Char(FileName).data()); }
void SavePNG(CImg<unsigned char> Image, string FileName, int BytesPerPixel) { Image.save_png(Str2Char(FileName).data(), BytesPerPixel); }
void SaveJPG(CImg<unsigned char> Image, string FileName) { Image.save_jpeg(Str2Char(FileName).data(), 100); } // 100% quality
void SaveJPG(CImg<unsigned char> Image, string FileName, int QualityPercent) { Image.save_jpeg(Str2Char(FileName).data(), QualityPercent); }

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
	const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 }, blue[] = { 0, 0, 255 };

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
void VerImg(CImg<unsigned char> Img) { CImgDisplay Disp(Img, "Imagem"); while (!Disp.is_closed()) { Disp.wait(); } }
void VerImg(CImg<unsigned char> Img, string Title) { CImgDisplay Disp(Img, Str2Char(Title).data()); while (!Disp.is_closed()) { Disp.wait(); } }

// POEM DADOS NO VETOR ATRAVEZ DE UM BITMAP (GRAYSCALE):
vector<double> BitmapVector(CImg<unsigned char> BMP)
{
	vector<double> NewMatrix;
	Point3D RGB;
	for (int ny = 0; ny < BMP.height(); ++ny)
	{
		for (int nx = 0; nx < BMP.width(); ++nx) { RGB = BitmapRGB(BMP, nx, ny); double Valor = ((RGB.x + RGB.y + RGB.z) / 765.0); NewMatrix.push_back(Valor); }
	}
	return (NewMatrix);
}
// POEM DADOS NO VETOR ATRAVEZ DE UM BITMAP (R = 0, G = 1, B = 2):
vector<double> BitmapVector(CImg<unsigned char> BMP, int R0orG1orB2)
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
// ADC TEXTO (PODE SE USAR A FUNÇÃO .DATA() DO STRING MESMO):
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

// REFAZ IMAGEM COM CERTA COR (PRETA SE NÃO TIVER RGB):
void FillAlpha(CImg<unsigned char>& Img) { CImg<unsigned char> FilledImg(Img.width(), Img.height(), 1, 4, 0); unsigned char C[] = { 0, 0, 0, 0 }; Img.draw_fill(1, 1, C, 1, 1); Img = FilledImg; }
void FillAll(CImg<unsigned char>& Img) { CImg<unsigned char> FilledImg(Img.width(), Img.height(), 1, 3, 0); Img = FilledImg; }
void FillAll(CImg<unsigned char>& Img, int R, int G, int B)
{
	CImg<unsigned char> FilledImg(Img.width(), Img.height(), 1, 3, 0);
	unsigned char color[] = { R, G, B };
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
CImg<unsigned char> FillAll(int Width, int Height, int R, int G, int B)
{
	CImg<unsigned char> FilledImg(Width, Height, 1, 3, 0);
	unsigned char color[] = { R, G, B };
	FilledImg.draw_fill(1, 1, color, 1, 1, false);
	return(FilledImg);
}


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## CLASSES ##############
// ###################################

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
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); }
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
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
			if (IgnoreColor[0] != RGB0.x) { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); }
			else { Clr[0] = RGB1.x; }
			if (IgnoreColor[1] != RGB0.y) { Clr[1] = round((RGB0.y + RGB1.y) * 0.5); }
			else { Clr[1] = RGB1.y; }
			if (IgnoreColor[2] != RGB0.z) { Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			else { Clr[2] = RGB1.z; }
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
			Point3D RGB = BitmapRGB(Img1, j, i); if (IgnoreColor[0] != RGB.x || IgnoreColor[1] != RGB.y || IgnoreColor[2] != RGB.z) { unsigned char Clr[] = { RGB.x, RGB.y, RGB.z }; Ret.draw_point(j + x, i + y, Clr); }
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
		if (0 == m % 2) { Color[0] = RGBs[0].x; Color[1] = RGBs[0].y; Color[2] = RGBs[0].z; }
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

// !!!!!!! DELETAR EM  BREVE, NÃO ESTOU MAIS AFIM DISSO EM UMA CLASSE !!!!!!!
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
	~YSXCIMAIN() { }
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
	int AreaImg = ((BordaX + BordaY) * 2) + (GradeX * GradeY); // Area da Imagem (Pixeis)
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
	void RedoVar() { Sizex = GradeX + (BordaY * 2); Sizey = GradeY + (BordaX * 2); AreaImg = ((BordaX + BordaY) * 2) + (GradeX * GradeY); AreaPlot = GradeX * GradeY; }
	// Refaz variaveis de tamnho baseado em inputs:
	void NewVar(int NewX, int NewY) { GradeX = NewX; GradeY = NewY; RedoVar(); }
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
	{
		if (y > BordaX && y < GradeY + BordaX) { if (x > BordaY && x < GradeX + BordaY) { return (true); } else { return (false); } }
		else { return (false); }
	}
	bool InGridy(int y) { if (y > BordaX && y < GradeY + BordaX) { return (true); } else { return (false); } }
	bool InGridx(int x) { if (x > BordaY && x < GradeX + BordaY) { return (true); } else { return (false); } }

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

		// ##### Começa aqui #

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


	// #################################################

};


// ################################################# FIM ####################################################################################
#endif // SCPARSE_