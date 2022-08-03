#pragma once

#ifndef YSXCIMG_H
#define YSXCIMG_H

#pragma comment (lib, "zlib.lib")
#pragma comment (lib, "zlibstatic.lib")
//#pragma comment (lib, "zlibd.lib") // DEBUG
//#pragma comment (lib, "zlibstaticd.lib")
#pragma comment (lib, "libpng.lib")
//#pragma comment (lib, "libpngd.lib") // DEBUG

//#define cimg_use_png // unresolved external symbol png_ something something
//#define cimg_use_zlib // unresolved external symbol uncompress
//#define cimg_use_jpeg // lot of errors, not even intellisense can deal with

#include "png.h"
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

using namespace cimg_library; // COMMENT IF YOU ARE HAVING A PROBLEM

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!	* Functions with names like 'SaveBmp' are now 'SaveBMP';
// !!!	* 'VerImg(...)' is 'CIMG(...)' now;
// !!!	* 'AdcTexto' is 'AddText' now, and 'AdcBarras' i think is called 'DrawBars' now; ! Everything that is in portuguese is going to be changed !
// !!!	* Function 'FillAll' is now called 'CleanImg';
// !!!	* 'OpenImg' removed;
// !!!	* BIG CHANGES, TAKE CARE! Templates, references and more! 21/07/22;
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// ###################################
// ############## FORWARD DECLARATIONS:
CImg<uint8_t> DrawImageIgnClr(CImg<uint8_t>&, CImg<uint8_t>&, uint32_t, uint32_t, uint8_t[3]);
CImg<uint8_t> JoinImg(CImg<uint8_t>&, CImg<uint8_t>&, bool);
// Fractal stuffs:
std::vector<std::string> BinaryWordsSeq(int);
std::vector<long> BinaryWordSeqArean(int);
double AOScore(double);
// 'ysxMath.h' stuffs:
double GetMag(Point<double>); // ysxciPlotters.h
double GetVecRad(Point<double>); // ysxciPlotters.h
double SumntoPowIniEnd(int, int, int);

/*bool InImg(CImg<uint8_t>&, size_t, size_t);
void AddVert(CImg<uint8_t>&, unsigned short, unsigned short, unsigned short, uint8_t*);
void AddText(CImg<uint8_t>&, uint32_t , uint32_t , std::string, uint8_t[3]);
CImg<uint8_t> ValueBarAbs(uint16_t, double, double, uint16_t, uint16_t, bool);
void Resize(CImg<uint8_t>&, uint16_t, uint16_t, uint8_t);
void FillArea(CImg<uint8_t>&, uint16_t, uint16_t, uint8_t[3]);
void CleanImg(CImg<uint8_t>&, uint8_t[3]);
CImg<uint8_t> ExpandImg(CImg<uint8_t>, uint16_t, char);*/
// ###################################

// ###################################
// ############## TOOLS:
struct Pixel { unsigned int x; unsigned int y; uint8_t RGB[3]; };
// ###################################

// ############## GENERALLY USEFUL:
// CHECK IF PIXEL IS INSIDE IMAGE (MAYBE SOON TO BE OBSOLETE):
bool InImg(CImg<uint8_t>& Img, size_t y, size_t x) { if (y < Img.height()) { if (x < Img.width()) { return (true); } return (false); } return (false); }

// ADD TEXT ON IMAGE:
void AddText(CImg<uint8_t>& Img, uint32_t x, uint32_t y, std::string String, uint8_t C[3])
{
	Img.draw_text(x, y, String.data(), C);// , 19);
}

// SAME AS 'AddText', BUT PRINT IN CIRCLE DIVISION WITH A VECTOR OF STRINGS:
void AddTextCirc(CImg<uint8_t>& Img, double r, uint32_t x, uint32_t y, std::vector<std::string> Strings, uint8_t C[3])
{
	double Div = TAU / Strings.size(); uint32_t Count = 0;
	for (double rad = 0; rad <= TAU; rad += Div) { AddText(Img, x + round(cos(rad) * (r - 8)), y + round(sin(rad) * (r - 8)), Strings[Count], C); ++Count; }
}

void CleanImg(CImg<uint8_t>& Img, uint8_t* C = nullptr)
{
	Img = CImg<uint8_t>::CImg(Img.width(), Img.height(), 1, 3, 0);
	if (C) { Img.draw_fill(1, 1, C, 1, 1, false); }
}

// ###################################
// EXTRA:
#include "ysxCImgIncludes/ysxciColors.h"
#include "ysxCImgIncludes/ysxciUtils.h"
#include "ysxCImgIncludes/ysxciPlotters.h"
#include "ysxCImgIncludes/ysxciMisc.h"
// ###################################


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## TECHNICAL:

// SAVE:
void SaveBMP(CImg<uint8_t> Image, std::string FileName) { Image.save_bmp(FileName.data()); }
void SavePNG(CImg<uint8_t> Image, std::string FileName) { Image.save_png(FileName.data()); }
void SavePNG(CImg<uint8_t> Image, std::string FileName, int BytesPerPixel) { Image.save_png(FileName.data(), BytesPerPixel); } // needs 'libpng' defined
void SaveJPG(CImg<uint8_t> Image, std::string FileName) { Image.save_jpeg(FileName.data(), 100); } // 100% quality
void SaveJPG(CImg<uint8_t> Image, std::string FileName, int QualityPercent) { Image.save_jpeg(FileName.data(), QualityPercent); }

// SEE IMG, LIKE, CIMG, GOTCHA?:
void CIMG(std::string File, std::string Title = "Art! :3") { CImg<uint8_t> Img(File.data()); CImgDisplay d(Img, Title.data()); while (!d.is_closed()) { d.wait(); } }
void CIMG(CImg<uint8_t>& Img, std::string Title = "Img") { CImgDisplay d(Img, Title.data()); while (!d.is_closed()) { d.wait(); } }

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## GRAFICOS:

// REDO IMAGE WITH SPECIFIC COLOR (OR ELSE, IT IS BLACK):
void FillAlpha(CImg<uint8_t>& Img) { Img = CImg<uint8_t>::CImg(Img.width(), Img.height(), 1, 4, 0); uint8_t C[] = { 0, 0, 0, 0 }; Img.draw_fill(1, 1, C, 1, 1); } // Maybe it is already black

// Fill / clean entire image, but by drawing a rectangle over it:
void FillRect(CImg<uint8_t>& Img) { uint8_t c[] = { 0, 0, 0 }; Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, c); }
void FillRect(CImg<uint8_t>& Img, uint8_t C[3]) { Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, C); }

// EZ CREATE NEW IMAGE WITH COLORED BACKGROUND:
CImg<uint8_t> NewImgBGColor(int Width, int Height, uint8_t C[3])
{
	CImg<uint8_t> FilledImg(Width, Height, 1, 3, 0);
	FilledImg.draw_fill(1, 1, C, 1, 1, false);
	return(FilledImg);
}

// ###################################
// ############## CLASSES ##############
// ###################################

// ###################################
// ############## IMAGENS ##############
// ###################################

// MIX IMAGES AND CAN ALSO IGNORE COLORS:
CImg<uint8_t> MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1)
{
	uint16_t Width = 1, Height = 1;
	Img0.width() > Img1.width() ? Width = Img1.width() : Width = Img0.width();
	Img0.height() > Img1.height() ? Height = Img1.height() : Height = Img0.height();
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n);
			Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
			Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
			Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<uint8_t> MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, bool IgnoreBlack, bool IgnoreWhite)
{
	uint16_t Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); }
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n); // PEGA PIXEL
			if (!IgnoreBlack && !IgnoreWhite) { Clr[0] = round((RGB0.x + RGB1.x) * 0.5); Clr[1] = round((RGB0.y + RGB1.y) * 0.5); Clr[2] = round((RGB0.z + RGB1.z) * 0.5); }
			else if (IgnoreBlack && !IgnoreWhite)
			{
				if (RGB0.x == 0 && RGB0.y == 0 && RGB0.z == 0) { Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z; }
				else
				{
					Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
					Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
					Clr[2] = round((RGB0.z + RGB1.z) * 0.5);					
				}
			}
			else if (IgnoreWhite && !IgnoreBlack)
			{
				if (RGB0.x == 255 && RGB0.y == 255 && RGB0.z == 255) { Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z; }
				else
				{
					Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
					Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
					Clr[2] = round((RGB0.z + RGB1.z) * 0.5);					
				}
			}
			else if (IgnoreWhite && IgnoreBlack)
			{
				if (RGB0.x == 0 && RGB0.y == 0 && RGB0.z == 0) { Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z; }
				else if (RGB0.x == 255 && RGB0.y == 255 && RGB0.z == 255) { Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z; }
				else
				{
					Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
					Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
					Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
				}
			}
			//std::cout << "ClrR: " << Clr[0] << " | ClrG: " << Clr[1] << " | ClrB: " << Clr[2] << std::endl;
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<uint8_t> MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint8_t IgnoreColor[3])
{
	uint16_t Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, não vai pedir memória aonde não tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			RGB0 = BitmapRGB(Img0, m, n), RGB1 = BitmapRGB(Img1, m, n);
			if (RGB0.x == IgnoreColor[0] && RGB0.y == IgnoreColor[1] && RGB0.z == IgnoreColor[2])
			{ Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z; }
			else
			{
				Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
				Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
				Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
			}
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<uint8_t> MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	uint16_t Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, não vai pedir memória aonde não tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			if (InImg(Img0, n + y, m + x))
			{
				RGB0 = BitmapRGB(Img0, m + x, n + y), RGB1 = BitmapRGB(Img1, m, n);
				if (RGB0.x == IgnoreColor[0] && RGB0.y == IgnoreColor[1] && RGB0.z == IgnoreColor[2])
				{
					Clr[0] = RGB1.x; Clr[1] = RGB1.y; Clr[2] = RGB1.z;
				}
				else
				{
					Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
					Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
					Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
				}
				Ret.draw_point(m, n, Clr);
			}
		}
	}
	return (Ret);
}

// DRAW IMAGE OVER ANOTHER IMAGE, BUT IGNORE SPECIFIC COLOR:
CImg<uint8_t> DrawImageIgnClr(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	uint32_t  Width = Img1.width(), Height = Img1.height();
	CImg<uint8_t> Ret = Img0;
	Point3D<uint8_t> RGB;
	uint8_t Clr[3];
	for (uint32_t  i = 0; i < Height; ++i)
	{
		for (uint32_t  j = 0; j < Width; ++j)
		{
			if (j + x >= Img0.width() - 1) { break; }
			RGB = BitmapRGB(Img1, j, i);
			if (IgnoreColor[0] != RGB.x || IgnoreColor[1] != RGB.y || IgnoreColor[2] != RGB.z)
			{
				Clr[0] = RGB.x; Clr[1] = RGB.y; Clr[2] = RGB.z;
				Ret.draw_point(j + x, i + y, Clr);
			}
		}
		if (i + y >= Img0.height() - 1) { break; }
	}
	return (Ret);
}

/*
#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;

int main(int argc, char **argv) {

  const CImg<> bg("background.png"); // RGB image
  const CImg<> fg("foreground.png"); // RGBA image.

  const CImg<> fg_rgb = fg.get_shared_channels(0,2); // Only RGB part of the foreground.
  const CImg<> fg_a = fg.get_shared_channel(3); // Only Alpha part of the foreground.

  CImg<> result(bg);
  result.draw_image(30,30,fg_rgb,fg_a,1,255);

  (bg,fg,result).display();
}
*/

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## MISC:
// SIEVE OF ERATOSTHENES (Modified and not tested):
CImg<uint8_t> SieveEratosthenes(uint32_t  n)
{
	if (n < 10) { n = 10; }
	CImg<uint8_t> Ret(320, ceil(n / 10.0) * 32, 1, 3, 0);
	CImg<uint8_t> Square;
	std::vector<Point3D<uint8_t>> RGBs(4);
	for (uint8_t m = 0; m < 4; ++m) { RGBs[m] = LinearRGB(m / 4.0, 1, 1); }
	uint8_t C[] = { 0, 0, 0 };

	for (uint8_t m = 0; m < n; ++m)
	{
		// Colors:
		if (!((m + 1) % 2)) { C[0] = RGBs[0].x; C[1] = RGBs[0].y; C[2] = RGBs[0].z; }
		else if (!((m + 1) % 3)) { C[0] = RGBs[1].x; C[1] = RGBs[1].y; C[2] = RGBs[1].z; }
		else if (!((m + 1) % 5)) { C[0] = RGBs[2].x; C[1] = RGBs[2].y; C[2] = RGBs[2].z; }
		else if (!((m + 1) % 7)) { C[0] = RGBs[3].x; C[1] = RGBs[3].y; C[2] = RGBs[3].z; }

		Square = CImg<uint8_t>::CImg(31, 31, 1, 3, 0);
		FillArea(Square, 15, 15, C);
		C[0] = 255 - C[0], C[1] = 255 - C[1], C[2] = 255 - C[2];
		Square = AddBorder(Square, 1, 1, C);
		AddText(Square, 7, 15, std::to_string(m + 1), C);
		Ret.draw_image((n % 10) * 32, floor(n / 10) * 32, Square);
	}
	return(Ret);
}

// RAY INFO:
CImg<uint8_t> RayInfo(double Degrees, uint32_t  ImgSize)
{
	if (ImgSize < 192) { ImgSize = 192; }
	CImg<uint8_t> I(ImgSize, ImgSize, 1, 3, 0);
	double Rad = Ang2Rad(Degrees);
	uint32_t  r = round(0.5 * ImgSize);
	uint8_t C[] = { 64, 64, 64 };
	uint32_t  Line = 8, Txtpx = r - 24;
	std::string Sin = "Sin: " + std::to_string(sin(Rad)), Cos = "Cos: " + std::to_string(cos(Rad)), Tan = "Tan: " + std::to_string(tan(Rad)),
		Cot = "Cot: " + std::to_string(cot(Rad)), Sec = "Sec: " + std::to_string(sec(Rad)), Csc = "Csc: " + std::to_string(csc(Rad)),
		Ver = "Versin: " + std::to_string(versin(Rad)), Exsec = "ExSec: " + std::to_string(exsec(Rad)),
		Excsc = "ExCsc: " + std::to_string(excsc(Rad)), Crd = "Cord: " + std::to_string(crd(Rad));

	Linexy(I, r, 0, r, ImgSize, C); Linexy(I, 0, r, ImgSize, r, C); // Cruz
	Circlexy(I, r, r, r);
	Radius(I, r, r, r, Rad, true, false);
	C[0] = 255; C[1] = 0; C[2] = 0;
	Linexy(I, r, r, ceil(cos(Rad) * r) + r, r, C);
	AddText(I, Txtpx, r + Line * 2, Cos, C);
	Linexy(I, r, r - ceil(sin(Rad) * r), ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), C);
	C[0] = 0; C[1] = 255;
	Linexy(I, r, r, r, r - ceil(sin(Rad) * r), C);
	AddText(I, Txtpx, r + Line, Sin, C);
	Linexy(I, ceil(cos(Rad) * r) + r, r, ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), C);
		
	C[1] = 0; C[2] = 255; AddText(I, Txtpx, r + Line * 3, Tan, C);
	C[0] = 255; AddText(I, Txtpx, r + Line * 4, Cot, C);
	C[0] = 0; C[1] = 255; AddText(I, Txtpx, r + Line * 5, Sec, C);
	C[0] = 255; C[1] = 0; AddText(I, Txtpx, r + Line * 6, Csc, C);
	C[1] = 255;	AddText(I, r + 24, r - Line * 2, "ANGLE: " + std::to_string(Degrees), C);
	C[2] = 127;	AddText(I, Txtpx, r + Line * 10, Crd, C);
	C[0] = 127;	AddText(I, Txtpx, r + Line * 7, Ver, C);
	C[0] = 255; C[1] = 127;	AddText(I, Txtpx, r + Line * 8, Exsec, C);
	C[0] = 127; C[2] = 255; AddText(I, Txtpx, r + Line * 9, Excsc, C);
	
	return(I);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################



// VER O QUE PODE TIRAR DAQUI:
// PLOTAR F(X, Y): // Lembrar de modificar essa função para 'z' ser cor;
/*void Funcxy(double a, double x1, double x2, double y1, double y2, int PlotDrv)
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
		std::cout << "y = " << y << " | yn = " << yn << std::endl;
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
			Point3D<uint8_t> RGB = LinearRGB((z + 1) * 0.5, 1.0, 1.0); TR = RGB.x; TG = RGB.y; TB = RGB.z;
			uint8_t Clr[] = { TR, TG, TB };
			Imagem.draw_point(xn, yn, Clr);
			// ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### ####### #######
		}
	}
}*/

// ################################################# FIM ####################################################################################
#endif // SCPARSE_