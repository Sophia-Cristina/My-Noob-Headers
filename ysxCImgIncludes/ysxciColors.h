#pragma once

#ifndef YSXCICOLORS_H
#define YSXCICOLORS_H

using namespace cimg_library;

// ###################################
// ############## FUNÇÕES #######
// ###################################
// ############## DECLARAÇÕES:
Point3D<uint8_t> BitmapRGB(CImg<uint8_t>, uint32_t, uint32_t);
Point3D<uint8_t> LinearRGB(double, double, double);
// ###################################
// ############## TYPEDEFS:
//typedef std::vector<std::vector<Point3DFlt>> IMGDataSet; // !!!!!!! !!!!!!! !!!!!!! PAY ATTENTION TO THIS TYPEDEF !!!!!!! !!!!!!! !!!!!!!
// ###################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## TÉCNICOS:

// INSIDE A GAP OF RGB NUMBERS:
bool InsideRGBGap(uint8_t RGB[3], int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB[0] >= R0 && RGB[0] <= R1 && RGB[1] >= G0 && RGB[1] <= G1 && RGB[2] >= B0 && RGB[2] <= B1) { return(true); } else { return(false); } }
bool InsideRGBGap(Point3D<uint8_t> RGB, int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB.x >= R0 && RGB.x <= R1 && RGB.y >= G0 && RGB.y <= G1 && RGB.z >= B0 && RGB.z <= B1) { return(true); } else { return(false); } }
bool InsideRGBGapOR(uint8_t RGB[3], int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB[0] >= R0 || RGB[0] <= R1 || RGB[1] >= G0 || RGB[1] <= G1 || RGB[2] >= B0 || RGB[2] <= B1) { return(true); } else { return(false); } }
bool InsideRGBGapOR(Point3D<uint8_t> RGB, int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB.x >= R0 || RGB.x <= R1 || RGB.y >= G0 || RGB.y <= G1 || RGB.z >= B0 || RGB.z <= B1) { return(true); } else { return(false); } }


// MAX / MIN OF PIXEL X AND Y:
Point<uint32_t> MaxxMinxPixel(std::vector<Pixel> VP)
{
	Point<uint32_t> MM;
	int Maxx = VP[0].x, Minx = VP[0].x;
	for (int n = 1; n < VP.size(); ++n)
	{
		if (VP[n].x > Maxx) { Maxx = VP[n].x; }
		if (VP[n].x < Minx) { Minx = VP[n].x; }
	}
	float Absmx = 0, Absmn = 0;
	if (Maxx < 0) { Absmx = abs(Maxx); Maxx += Absmx; Minx += Absmx; }
	if (Minx < 0) { Absmn = abs(Minx); Maxx += Absmn; Minx += Absmn; }

	MM.x = Maxx; MM.y = Minx;
	return(MM);
}
Point<uint32_t> MaxyMinyPixel(std::vector<Pixel> VP)
{
	Point<uint32_t> MM;
	int Maxy = VP[0].x, Miny = VP[0].x;
	for (int n = 1; n < VP.size(); ++n)
	{
		if (VP[n].y > Maxy) { Maxy = VP[n].y; }
		if (VP[n].y < Miny) { Miny = VP[n].y; }
	}
	float Absmx = 0, Absmn = 0;
	if (Maxy < 0) { Absmx = abs(Maxy); Maxy += Absmx; Miny += Absmx; }
	if (Miny < 0) { Absmn = abs(Miny); Maxy += Absmn; Miny += Absmn; }

	MM.x = Maxy; MM.y = Miny;
	return(MM);
}
void MaxMinPixel(std::vector<Pixel> VP, Point<uint32_t>& MaxxMinx, Point<uint32_t>& MaxyMiny)
{
	int Maxx = VP[0].x, Minx = VP[0].x;
	int Maxy = VP[0].y, Miny = VP[0].y;
	for (int n = 1; n < VP.size(); ++n)
	{
		if (VP[n].x > Maxx) { Maxx = VP[n].x; }
		if (VP[n].x < Minx) { Minx = VP[n].x; }
		if (VP[n].y > Maxy) { Maxy = VP[n].y; }
		if (VP[n].y < Miny) { Miny = VP[n].y; }
	}
	float Absmx = 0, Absmn = 0;
	if (Maxx < 0) { Absmx = abs(Maxx); Maxx += Absmx; Minx += Absmx; }
	if (Minx < 0) { Absmn = abs(Minx); Maxx += Absmn; Minx += Absmn; }

	if (Maxy < 0) { Absmx = abs(Maxy); Maxy += Absmx; Miny += Absmx; }
	if (Miny < 0) { Absmn = abs(Miny); Maxy += Absmn; Miny += Absmn; }

	MaxxMinx.x = Maxx; MaxxMinx.y = Minx;
	MaxyMiny.x = Maxx; MaxyMiny.y = Miny;
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## BITMAP:

// BITMAP RGB:
Point3D<uint8_t> BitmapRGB(CImg<uint8_t> BMP, uint32_t x, uint32_t y)
{
	Point3D<uint8_t> Ret;
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (y > BMP.height() - 1) { y = BMP.height() - 1; }
	Ret.x = BMP(x, y, 0, 0); Ret.y = BMP(x, y, 0, 1); Ret.z = BMP(x, y, 0, 2);
	return(Ret);
}
void BitmapRGBuc(CImg<uint8_t> BMP, uint32_t x, uint32_t y, uint8_t* Clr)
{
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (y > BMP.height() - 1) { y = BMP.height() - 1; }
	Clr[0] = BMP(x, y, 0, 0); Clr[1] = BMP(x, y, 0, 1); Clr[2] = BMP(x, y, 0, 2);
}
// BITMAP PIXEL:
Pixel BitmapPixel(CImg<uint8_t> BMP, uint32_t x, uint32_t y)
{
	Pixel Ret;
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (y > BMP.height() - 1) { y = BMP.height() - 1; }
	Ret.RGB[0] = BMP(x, y, 0, 0); Ret.RGB[1] = BMP(x, y, 0, 1); Ret.RGB[2] = BMP(x, y, 0, 2);
	Ret.x = x; Ret.y = y;
	return(Ret);
}

// ALL RGBS FROM BITMAP:
std::vector<Point3D<uint8_t>> BitmapRGBMatrix(CImg<uint8_t> BMP)
{
	std::vector<Point3D<uint8_t>> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{ Point3D<uint8_t> RGB = BitmapRGB(BMP, n, m); Ret.push_back(RGB); }
	}
	return(Ret);
}
// ALL PIXELS FROM BITMAP:
std::vector<Pixel> BitmapPixelMatrix(CImg<uint8_t> BMP)
{
	std::vector<Pixel> Ret;
	for (int y = 0; y < BMP.height(); ++y)
	{
		for (int x = 0; x < BMP.width(); ++x)
		{
			Pixel Pix = BitmapPixel(BMP, x, y); Ret.push_back(Pix);
		}
	}
	return(Ret);
}

// ALL RGBS FROM BITMAP (in float), IT GOES LIKE R, THEN G, THEN B, THEN NEXT PIXEL, SO THE VECTOR HAVE 3X THE SIZE OF THE IMAGE:
std::vector<double> BitmapRGBVector(CImg<uint8_t> BMP)
{
	std::vector<double> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{
			Point3D<uint8_t> RGB = BitmapRGB(BMP, n, m);  Ret.push_back(RGB.x / 255.0);  Ret.push_back(RGB.y = RGB.y / 255.0);  Ret.push_back(RGB.z = RGB.z / 255.0);
		}
	}
	return(Ret);
}

// LIMITED PIXEL MATRIX:
std::vector<Pixel> BitmapPixelLimMatrix(CImg<uint8_t> BMP, int R0, int R1, int G0, int G1, int B0, int B1)
{
	std::vector<Pixel> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{
			Pixel Pix = BitmapPixel(BMP, n, m);
			if (InsideRGBGap(Pix.RGB, R0, R1, G0, G1, B0, B1)) { Ret.push_back(Pix); }
		}
	}
	return(Ret);
}

// FLATTEN A BUNCH OF IMAGE INTO A DATASET (in float; function aimed for OpenNN):
// Create a bunch of images like 'image0.bmp', write 'Preffix = image', and 'Last = 'Last number of image sequence'';
// It always begins at '0', if you want a single image, use 'Last = 0';

// !!!!!!! I CHANGED IDEA AND THIS MAY BECOME OBSOLETE !!!!!!! CHECK 'ysxPrint.h' at 'MakeDataSetRGBLine' !!!!!!!
/*IMGDataSet BitmapRGBMatrix(string Preffix, int Last)
{
	IMGDataSet Ret;
	for (int Index = 0; Index < Last; ++Index)
	{
		CImg<uint8_t> BMP;
		std::vector<Point3DFlt> Frame;
		for (int m = 0; m < BMP.height(); ++m)
		{
			for (int n = 0; n < BMP.width(); ++n)
			{
				Point3D RGB = BitmapRGB(BMP, n, m); Point3DFlt RGBFlt; RGBFlt.x = RGB.x / 255.0; RGBFlt.y = RGB.y / 255.0; RGBFlt.z = RGB.z / 255.0; Ret.push_back(RGBFlt);
			}
		}
	}
	return(Ret);
}*/


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TEXTOS:


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## CORES:

// ####### HUE:

// LINEAR RGB:
// Preferable range for 'Lum' is '0 to 2', and for 'Cont' is '0 to 1'.
// You can use on 'CImg' colors with '(uint8_t*)&Some3DPoint<uint8_t>'.
Point3D<uint8_t> LinearRGB(double x, double Lum, double Cont)
{
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x = x - floor(x); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	unsigned short R = 0, G = 0, B = 0; // 'short' in case of overflow
	double m;

	if (x > 5.0 / 6) { m = (x - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }
	else if (x <= 5.0 / 6 && x > 4.0 / 6) { m = (x - (4.0 / 6)) * 6;	R = round(255 * m); G = 0; B = 255; }
	else if (x <= 4.0 / 6 && x > 3.0 / 6) { m = (x - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	else if (x <= 3.0 / 6 && x > 2.0 / 6) { m = (x - (2.0 / 6)) * 6; R = 0; G = 255;	B = round(255 * m); }
	else if (x <= 2.0 / 6 && x > 1.0 / 6) { m = (x - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	else {	m = x * 6; R = 255; G = round(255 * m); B = 0; }	

	// Contrast:
	if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
	if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
	if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }

	// Luminosity:
	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	else
	{
		if (R == 0) { R = 1; } if (G == 0) { G = 1; } if (B == 0) { B = 1; }
		double LumMath = 255 * (Lum - 1); R = R + LumMath; G = G + LumMath; B = B + LumMath;
	}

	// Limit:
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	Point3D<uint8_t> RGB; RGB.x = R; RGB.y = G; RGB.z = B;
	return(RGB);
}

// OVERWRITE POINTED 'uint8_t[3]':
void LinearRGBuc(double x, double Lum, double Cont, uint8_t* Color)
{
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x = x - floor(x); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	unsigned short R = 0, G = 0, B = 0;
	double m;

	if (x <= 6.0 / 6 && x > 5.0 / 6) { m = (x - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }
	else if (x <= 5.0 / 6 && x > 4.0 / 6) { m = (x - (4.0 / 6)) * 6;	R = round(255 * m); G = 0; B = 255; }
	else if (x <= 4.0 / 6 && x > 3.0 / 6) { m = (x - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	else if (x <= 3.0 / 6 && x > 2.0 / 6) { m = (x - (2.0 / 6)) * 6; R = 0; G = 255;	B = round(255 * m); }
	else if (x <= 2.0 / 6 && x > 1.0 / 6) { m = (x - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	else { m = x * 6; R = 255; G = round(255 * m); B = 0; }

	if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
	if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
	if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }

	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	else
	{
		if (R == 0) { R = 1; } if (G == 0) { G = 1; } if (B == 0) { B = 1; }
		double LumMath = 255 * (Lum - 1); R = R + LumMath; G = G + LumMath; B = B + LumMath;
	}

	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	Color[0] = R; Color[1] = G; Color[2] = B;
}

// ################################################# FIM ####################################################################################

#endif // SCPARSE_