#pragma once

#ifndef YSXCIMISC_H
#define YSXCIMISC_H

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
// ############## MODULATIONS WITH HUE:
CImg<uint8_t> ysxCIMG_PaintHueRGBGapMod(CImg<uint8_t> I, double Phase, double Omega, double (*f)(double, double), uint8_t* RGB0, uint8_t* RGB1)
{
	std::vector<Pixel> VP = ysxCIMG_BitmapPixelMatrix(I);
	uint8_t C[3]; double Hue = 0;
	for (uint32_t n = 0; n < VP.size(); ++n)
	{
		if (ysxCOLOR_InsideRGBGap(VP[n].RGB, RGB0, RGB1))
		{
			Hue = ysxCALC_ModForm(((double)n / VP.size() * TAU) + Phase, Omega, f);
			ysxCOLOR_LinearRGB(Hue, 1, 1, C); I.draw_point(VP[n].x, VP[n].y, C);
		}
	}
	return(I);
}

// ###################################

// SIEVE OF ERATOSTHENES (Modified and not tested):
CImg<uint8_t> ysxCIMG_SieveEratosthenes(uint32_t  n)
{
	if (n < 10) { n = 10; }
	CImg<uint8_t> Ret(320, ceil(n / 10.0) * 32, 1, 3, 0);
	CImg<uint8_t> Square;
	std::vector<Point3D<uint8_t>> RGBs(4);
	for (uint8_t m = 0; m < 4; ++m) { ysxCOLOR_LinearRGB(m / 4.0, 1, 1, (uint8_t)&RGBs[m].x); }
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
		Square = ysxCIMG_AddBorder(Square, 1, 1, C);
		ysxCIMG_AddText(Square, 7, 15, std::to_string(m + 1), C);
		Ret.draw_image((n % 10) * 32, floor(n / 10) * 32, Square);
	}
	return(Ret);
}

// RAY INFO:
CImg<uint8_t> ysxCIMG_RayInfo(double Degrees, uint32_t  ImgSize)
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

	ysxCIMG_DRAW_Linexy(I, r, 0, r, ImgSize, C); ysxCIMG_DRAW_Linexy(I, 0, r, ImgSize, r, C); // Cruz
	ysxCIMG_DRAW_Circlexy(I, r, r, r);
	ysxCIMG_DRAW_Radius(I, r, r, r, Rad, true, false);
	C[0] = 255; C[1] = 0; C[2] = 0;
	ysxCIMG_DRAW_Linexy(I, r, r, ceil(cos(Rad) * r) + r, r, C);
	ysxCIMG_AddText(I, Txtpx, r + Line * 2, Cos, C);
	ysxCIMG_DRAW_Linexy(I, r, r - ceil(sin(Rad) * r), ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), C);
	C[0] = 0; C[1] = 255;
	ysxCIMG_DRAW_Linexy(I, r, r, r, r - ceil(sin(Rad) * r), C);
	ysxCIMG_AddText(I, Txtpx, r + Line, Sin, C);
	ysxCIMG_DRAW_Linexy(I, ceil(cos(Rad) * r) + r, r, ceil(cos(Rad) * r) + r, r - ceil(sin(Rad) * r), C);

	C[1] = 0; C[2] = 255; ysxCIMG_AddText(I, Txtpx, r + Line * 3, Tan, C);
	C[0] = 255; ysxCIMG_AddText(I, Txtpx, r + Line * 4, Cot, C);
	C[0] = 0; C[1] = 255; ysxCIMG_AddText(I, Txtpx, r + Line * 5, Sec, C);
	C[0] = 255; C[1] = 0; ysxCIMG_AddText(I, Txtpx, r + Line * 6, Csc, C);
	C[1] = 255;	ysxCIMG_AddText(I, r + 24, r - Line * 2, "ANGLE: " + std::to_string(Degrees), C);
	C[2] = 127;	ysxCIMG_AddText(I, Txtpx, r + Line * 10, Crd, C);
	C[0] = 127;	ysxCIMG_AddText(I, Txtpx, r + Line * 7, Ver, C);
	C[0] = 255; C[1] = 127;	ysxCIMG_AddText(I, Txtpx, r + Line * 8, Exsec, C);
	C[0] = 127; C[2] = 255; ysxCIMG_AddText(I, Txtpx, r + Line * 9, Excsc, C);

	return(I);
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################


// ################################################# FIM ####################################################################################

#endif // SCPARSE_