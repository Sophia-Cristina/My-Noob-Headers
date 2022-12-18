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

// #####################
// ####### By Sophia Cristina
// ####### Header made do some useful stuffs with 'CImg.h'
// #####################

using namespace cimg_library; // COMMENT IF YOU ARE HAVING A PROBLEM

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!	* Lot of name changes! Prefix added to lot of things!
// !!!	* BIG CHANGES, TAKE CARE! Templates, references and more! 21/07/22;
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// ###################################
// ############## FORWARD DECLARATIONS:
CImg<uint8_t> ysxCIMG_DRAW_ImageIgnClr(CImg<uint8_t>&, CImg<uint8_t>&, uint32_t, uint32_t, uint8_t[3]);
CImg<uint8_t> JoinImg(CImg<uint8_t>&, CImg<uint8_t>&, bool);
// Fractal stuffs: // IF EVERYtHING WORKS WHILE COMMENTED, DELETE LATER!
//std::vector<std::string> BinaryWordsSeq(int);
//std::vector<long> BinaryWordSeqArean(int);
//double AOScore(double);
// 'ysxMath.h' stuffs:
//double GetMag(Point<double>); // ysxciPlotters.h
//double GetVecRad(Point<double>); // ysxciPlotters.h
//double SumntoPowIniEnd(int, int, int);

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
#include "ysxCImgIncludes/ysxciElecPlotters.h" // For class 'Component' of 'ysxElec.h'
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

// ############## GRAPHICS:

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