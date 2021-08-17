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
// ################################################# ANOTA��ES E ATEN��ES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDAN�AS (MANTENHA EM ORDEM):
// !!!!!!!	* Fun��es com nomes tipo 'SaveBmp' agora s�o 'SaveBMP';
// !!!!!!!	* 'VerImg(...)' � agora 'CIMG(...)';
// !!!!!!!	* 'AdcTexto' � agora 'AddText', e 'AdcBarras' eu acho que agora � 'DrawBars';
// !!!!!!!	
// ################################################# ANOTA��ES E ATEN��ES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## FORWARD DECLARATIONS:
CImg<unsigned char> DrawImageIgnClr(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
CImg<unsigned char> DrawImageIgnClrCout(CImg<unsigned char>, CImg<unsigned char>, int, int, unsigned char[3]);
bool InImg(CImg<unsigned char>, int, int);
void AdcVert(CImg<unsigned char>&, int, int, int, unsigned char[3]);
void AddText(CImg<unsigned char>&, int, int, std::string, int, int, int);
CImg<unsigned char> ValueBarAbs(int, double, double, int, int, bool);
void Resize(CImg<unsigned char>&, int, int, int);
void FillArea(CImg<unsigned char>&, int, int, int, int, int);
void FillAll(CImg<unsigned char>&, int, int, int);
CImg<unsigned char> ExpandImg(CImg<unsigned char>, int, char);
CImg<unsigned char> JoinImg(CImg<unsigned char>, CImg<unsigned char>, bool);
std::vector<char> Str2Char(std::string);
double GetMag(PointFlt);
double GetVecRad(PointFlt);
double SumntoPowIniEnd(int, int, int);
std::vector<std::string> BinaryWordsSeq(int);
std::vector<long> BinaryWordSeqArean(int);
double AOScore(double);
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
// ############## T�CNICOS:
// ABRIR (acho que apenas 'Open(FileName.data())' basta):
CImg<unsigned char> OpenImg(std::string FileName) { CImg<unsigned char> Open(Str2Char(FileName).data()); return(Open); }

// SALVAR (Com uso de 'string to char', minha fun��o que cria um vetor de char com um string, acho que cimg aceita s� um 'char array'):
void SaveBMP(CImg<unsigned char> Image, std::string FileName) { Image.save_bmp(Str2Char(FileName).data()); }
void SavePNG(CImg<unsigned char> Image, std::string FileName) { Image.save_png(Str2Char(FileName).data()); }
void SavePNG(CImg<unsigned char> Image, std::string FileName, int BytesPerPixel) { Image.save_png(Str2Char(FileName).data(), BytesPerPixel); }
void SaveJPG(CImg<unsigned char> Image, std::string FileName) { Image.save_jpeg(Str2Char(FileName).data(), 100); } // 100% quality
void SaveJPG(CImg<unsigned char> Image, std::string FileName, int QualityPercent) { Image.save_jpeg(Str2Char(FileName).data(), QualityPercent); }

// VERIFICA SE VALOR ESTA DENTRO DA IMAGEM:
bool InImg(CImg<unsigned char> Img, int y, int x)
{
	if (y < Img.height()) { if (x < Img.width()) { return (true); } else { return (false); } }
	else { return (false); }
}

// VER IMAGEM SALVA:
void CIMG(std::string Nome)
{
	CImg<unsigned char> ImagemAbrir(Str2Char(Nome).data());// , Grafico(100, 100, 1, 3, 0);
	CImgDisplay main_disp(ImagemAbrir, "Bela Arte:");// , draw_disp(Grafico, "Perfil de Intensidade");

	//const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 }, blue[] = { 0, 0, 255 };
	while (!main_disp.is_closed())// && !draw_disp.is_closed())
	{
		main_disp.wait();
		/*if (main_disp.button() && main_disp.mouse_y() >= 0)
		{
			int y = 0;
			const int ycimg = main_disp.mouse_y();
			Grafico.fill(0).draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 0, ImagemAbrir.width() - 1, y, 0, 0), red, 1, 1, 0, 255, 0);
			Grafico.draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 1, ImagemAbrir.width() - 1, y, 0, 1), green, 1, 1, 0, 255, 0);
			Grafico.draw_graph(ImagemAbrir.get_crop(0, ycimg, 0, 2, ImagemAbrir.width() - 1, y, 0, 2), blue, 1, 1, 0, 255, 0).display(draw_disp);
		}*/
	}
}

// VER IMAGEM MEMORIA:
void CIMG(CImg<unsigned char> Img) { CImgDisplay Disp(Img, "Image"); while (!Disp.is_closed()) { Disp.wait(); } }
void CIMG(CImg<unsigned char> Img, std::string Title) { CImgDisplay Disp(Img, Str2Char(Title).data()); while (!Disp.is_closed()) { Disp.wait(); } }

// POEM DADOS NO VETOR ATRAVEZ DE UM BITMAP (GRAYSCALE):
std::vector<double> BitmapVector(CImg<unsigned char> BMP)
{
	std::vector<double> NewMatrix;
	Point3D RGB;
	for (int ny = 0; ny < BMP.height(); ++ny)
	{
		for (int nx = 0; nx < BMP.width(); ++nx) { RGB = BitmapRGB(BMP, nx, ny); double Valor = ((RGB.x + RGB.y + RGB.z) / 765.0); NewMatrix.push_back(Valor); }
	}
	return (NewMatrix);
}
// POEM DADOS NO VETOR ATRAVEZ DE UM BITMAP (R = 0, G = 1, B = 2):
std::vector<double> BitmapVector(CImg<unsigned char> BMP, int R0orG1orB2)
{
	std::vector<double> NewMatrix;
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
// ADC TEXTO (PODE SE USAR A FUN��O .DATA() DO STRING MESMO):
void AddText(CImg<unsigned char>& Img, int x, int y, std::string String, int R, int G, int B)
{
	int TxtLim = String.length() + 1;
	std::vector<char> Texto(TxtLim);
	for (int chr = 0; chr < String.length(); ++chr)
	{
		Texto[chr] = String[chr];
		if (chr == String.length() - 1) { Texto[chr + 1] = '\0'; }
	}
	unsigned char color[] = { R, G, B };
	CImgList<unsigned char> font(const unsigned int font_height = 19, const bool variable_size = true);
	Img.draw_text(x, y, Texto.data(), color);
}
void AddTextCirc(CImg<unsigned char>& Img, double r, int x, int y, std::vector<std::string> Strings, int R, int G, int B) // Adiciona em dire��es de um circulo, como raios, como numeros num rel�gio
{
	double Div = TAU / Strings.size() * 1.0; int Count = 0;
	for (double rad = 0; rad <= TAU; rad += Div) { AddText(Img, x + round(cos(rad) * (r - 8)), y + round(sin(rad) * (r - 8)), Strings[Count], R, G, B); ++Count; }
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GRAFICOS:

// REFAZ IMAGEM COM CERTA COR (PRETA SE N�O TIVER RGB):
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

// MIXA IMAGENS E PODE REMOVER FUNDO (N�o esta ignorando cor, esta ignorando uma s� variavel de cor, arrumar depois):
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1)
{
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, n�o vai pedir mem�ria aonde n�o tem
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
			//std::cout << "ClrR: " << Clr[0] << " | ClrG: " << Clr[1] << " | ClrB: " << Clr[2] << std::endl;
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<unsigned char> MixRGB(CImg<unsigned char> Img0, CImg<unsigned char> Img1, unsigned char IgnoreColor[3])
{
	int Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, n�o vai pedir mem�ria aonde n�o tem
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
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, n�o vai pedir mem�ria aonde n�o tem
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
	std::cout << "i:\n";
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j + x >= Img0.width() - 1) { break; }
			Point3D RGB = BitmapRGB(Img1, j, i); if (IgnoreColor[0] != RGB.x || IgnoreColor[1] != RGB.y || IgnoreColor[2] != RGB.z) { unsigned char Clr[] = { RGB.x, RGB.y, RGB.z }; Ret.draw_point(j + x, i + y, Clr); }
		}
		if (i + y >= Img0.height() - 1) { break; }
		std::cout << " | " << i;
	}
	std::cout << std::endl;
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
	std::vector<CImg<unsigned char>> Squares;
	std::vector<Point3D> RGBs;
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
		AddText(Square, 7, 15, std::to_string(m), 255 - Color[0], 255 - Color[1], 255 - Color[2]);
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
	std::string Sin = "Sin: " + std::to_string(sin(Rad)), Cos = "Cos: " + std::to_string(cos(Rad)), Tan = "Tan: " + std::to_string(tan(Rad)),
		Cot = "Cot: " + std::to_string(cot(Rad)), Sec = "Sec: " + std::to_string(sec(Rad)), Csc = "Csc: " + std::to_string(csc(Rad)),
		Ver = "Versin: " + std::to_string(versin(Rad)), Exsec = "ExSec: " + std::to_string(exsec(Rad)),
		Excsc = "ExCsc: " + std::to_string(excsc(Rad)), Crd = "Cord: " + std::to_string(crd(Rad));
	int Line = 8, Txtpx = r - 24;
	AddText(I, Txtpx, r + Line, Sin, 0, 255, 0); AddText(I, Txtpx, r + Line * 2, Cos, 255, 0, 0);	AddText(I, Txtpx, r + Line * 3, Tan, 0, 0, 255);
	AddText(I, Txtpx, r + Line * 4, Cot, 255, 255, 0);	AddText(I, Txtpx, r + Line * 5, Sec, 0, 255, 255);	AddText(I, Txtpx, r + Line * 6, Csc, 255, 0, 255);
	AddText(I, Txtpx, r + Line * 7, Ver, 127, 255, 127); AddText(I, Txtpx, r + Line * 8, Exsec, 255, 127, 127); AddText(I, Txtpx, r + Line * 9, Excsc, 127, 127, 255);
	AddText(I, Txtpx, r + Line * 10, Crd, 255, 255, 127);
	AddText(I, r + 24, r - Line * 2, "ANGLE: " + std::to_string(Degrees), 255, 255, 255);
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

// VER O QUE PODE TIRAR DAQUI:
// PLOTAR F(X, Y): // Lembrar de modificar essa fun��o para 'z' ser cor;
/*void Funcxy(double a, double x1, double x2, double y1, double y2, int PlotDrv)
{
	// Input:
	double x, y, z;
	int TR = R, TG = G, TB = B;

	int zdrv, zgdrv = 0;
	// MUDE SEMPRE QUE ADICIONAR OUTRAS FORMULAS:
	if (PlotDrv > 2) { PlotDrv = 2; }

	if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.

	// ##### Come�a aqui #####

	// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
	// PLOTADORA:
	//for (double yn = GradeY + BordaX; yn > BordaX; --yn)
	for (double yn = BordaX; yn < GradeY + BordaX; ++yn)
	{
		double ydiv = (yn - (BordaX)) / (GradeY - 1);
		y = y1 + ((y2 - y1) * ydiv);
		std::cout << "y = " << y << " | yn = " << yn << std::endl;
		for (double xn = BordaY; xn < GradeX + BordaY; ++xn)
		{
			double xdiv = (xn - (BordaY)) / (GradeX - 1);
			x = x1 + ((x2 - x1) * xdiv);
			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
			// ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA ####### FORMULA #######
			z = NonStatWaveFunc(a / (x + 1), x2, x, y, Omega, ((x + y) * 0.125)); // ESCREVA AQUI SUA FUN��O.
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
}*/

// ################################################# FIM ####################################################################################
#endif // SCPARSE_