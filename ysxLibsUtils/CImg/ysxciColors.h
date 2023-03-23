#pragma once

#ifndef YSXCICOLORS_H
#define YSXCICOLORS_H

using namespace cimg_library;

// VERSIONS:
// 'ysxCIMG_CLR_InsideRGBGap' now uses pointers instead of values;

// ############## FORWARD DECLARATION:
//Point3D<uint8_t> BitmapRGB(CImg<uint8_t>&, uint32_t, uint32_t);

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## CORES:

// ####### HUE:

// LINEAR RGB:
// x = hue = '0 to 1';
// Preferable range for 'Lum' is '0 to 2', and for 'Cont' is '0 to 1'.
// You can use on 'CImg' colors with '(uint8_t*)&Some3DPoint'.
Point3D<uint8_t> ysxCIMG_CLR_LinearRGB(float x, float Lum, float Cont)
{
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x = x - floor(x); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	uint16_t R = 0, G = 0, B = 0; // 'short' in case of overflow
	float m;

	if (x >= 5.0 / 6) { m = (x - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }
	else if (x >= 4.0 / 6) { m = (x - (4.0 / 6)) * 6; R = round(255 * m); G = 0; B = 255; }
	else if (x >= 3.0 / 6) { m = (x - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	else if (x >= 2.0 / 6) { m = (x - (2.0 / 6)) * 6; R = 0; G = 255; B = round(255 * m); }
	else if (x >= 1.0 / 6) { m = (x - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	else { m = x * 6; R = 255; G = round(255 * m); B = 0; }

	// Contrast:
	if (Cont != 1)
	{
		if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
		if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
		if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }
	}

	// Luminosity:
	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	else
	{
		if (!R) { R = 1; } if (!G) { G = 1; } if (!B) { B = 1; }
		float L = 255 * (Lum - 1); R = R + L; G = G + L; B = B + L;
	}

	// Limit:
	R %= 256; G %= 256; B %= 256;
	Point3D<uint8_t> RGB; RGB.x = R; RGB.y = G; RGB.z = B;
	return(RGB);
}

// OVERWRITE POINTED 'uint8_t[3]':
void ysxCIMG_CLR_LinearRGBuc(float x, float Lum, float Cont, uint8_t* Color)
{
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x = x - floor(x); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	uint16_t R = 0, G = 0, B = 0;
	float m = 0;

	if (x >= 5.0 / 6) { m = (x - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }
	else if (x >= 4.0 / 6) { m = (x - (4.0 / 6)) * 6; R = round(255 * m); G = 0; B = 255; }
	else if (x >= 3.0 / 6) { m = (x - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	else if (x >= 2.0 / 6) { m = (x - (2.0 / 6)) * 6; R = 0; G = 255; B = round(255 * m); }
	else if (x >= 1.0 / 6) { m = (x - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	else { m = x * 6; R = 255; G = round(255 * m); B = 0; }

	/*if (x <= 6.0 / 6 && x > 5.0 / 6) { m = (x - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }
	else if (x <= 5.0 / 6 && x > 4.0 / 6) { m = (x - (4.0 / 6)) * 6; R = round(255 * m); G = 0; B = 255; }
	else if (x <= 4.0 / 6 && x > 3.0 / 6) { m = (x - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	else if (x <= 3.0 / 6 && x > 2.0 / 6) { m = (x - (2.0 / 6)) * 6; R = 0; G = 255; B = round(255 * m); }
	else if (x <= 2.0 / 6 && x > 1.0 / 6) { m = (x - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	else { m = x * 6; R = 255; G = round(255 * m); B = 0; }*/

	if (Cont != 1)
	{
		if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
		if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
		if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }
	}

	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	else
	{
		if (!R) { R = 1; } if (!G) { G = 1; } if (!B) { B = 1; }
		float L = 255 * (Lum - 1); R = R + L; G = G + L; B = B + L;
	}

	R %= 256; G %= 256; B %= 256;
	Color[0] = R; Color[1] = G; Color[2] = B;
}

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TECHNICAL:

// INSIDE A GAP OF RGB NUMBERS:
bool ysxCIMG_CLR_InsideRGBGap(uint8_t RGB[3], uint8_t* RGB0, uint8_t* RGB1)
{ if (RGB[0] >= RGB0[0] && RGB[0] <= RGB1[0] && RGB[1] >= RGB0[1] && RGB[1] <= RGB1[1] && RGB[2] >= RGB0[2] && RGB[2] <= RGB1[2]) { return(true); } else { return(false); } }
bool ysxCIMG_CLR_InsideRGBGap(Point3D<uint8_t> RGB, uint8_t* RGB0, uint8_t* RGB1)
{ if (RGB.x >= RGB0[0] && RGB.x <= RGB1[0] && RGB.y >= RGB0[1] && RGB.y <= RGB1[1] && RGB.z >= RGB0[2] && RGB.z <= RGB1[2]) { return(true); } else { return(false); } }
bool ysxCIMG_CLR_InsideRGBGapOR(uint8_t RGB[3], uint8_t* RGB0, uint8_t* RGB1)
{ if (RGB[0] >= RGB0[0] || RGB[0] <= RGB1[0] || RGB[1] >= RGB0[1] || RGB[1] <= RGB1[1] || RGB[2] >= RGB0[2] || RGB[2] <= RGB1[2]) { return(true); } else { return(false); } }
bool ysxCIMG_CLR_InsideRGBGapOR(Point3D<uint8_t> RGB, uint8_t* RGB0, uint8_t* RGB1)
{ if (RGB.x >= RGB0[0] || RGB.x <= RGB1[0] || RGB.y >= RGB0[1] || RGB.y <= RGB1[1] || RGB.z >= RGB0[2] || RGB.z <= RGB1[2]) { return(true); } else { return(false); } }


// ############################################################################################################################################
// ############## MAX / MIN:

// MAX / MIN OF PIXEL X AND Y:
Point<uint32_t> MaxxMinxPixel(std::vector<Pixel> VP)
{
	Point<uint32_t> MM;
	int Maxx = VP[0].x, Minx = VP[0].x;
	for (size_t n = 1; n < VP.size(); ++n)
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
	for (size_t n = 1; n < VP.size(); ++n)
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
	for (size_t n = 1; n < VP.size(); ++n)
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
Point3D<uint8_t> ysxCIMG_CLR_BitmapRGB(CImg<uint8_t>& BMP, uint32_t x, uint32_t y)
{
	Point3D<uint8_t> Ret;
	Ret.x = BMP(x, y, 0, 0); Ret.y = BMP(x, y, 0, 1); Ret.z = BMP(x, y, 0, 2);
	return(Ret);
}
void ysxCIMG_CLR_BitmapRGBuc(CImg<uint8_t>& BMP, uint32_t x, uint32_t y, uint8_t* Clr)
{
	Clr[0] = BMP(x, y, 0, 0); Clr[1] = BMP(x, y, 0, 1); Clr[2] = BMP(x, y, 0, 2);
}

// BITMAP PIXEL:
Pixel ysxCIMG_CLR_BitmapPixel(CImg<uint8_t>& BMP, uint32_t x, uint32_t y)
{
	Pixel Ret;
	Ret.RGB[0] = BMP(x, y, 0, 0); Ret.RGB[1] = BMP(x, y, 0, 1); Ret.RGB[2] = BMP(x, y, 0, 2);
	Ret.x = x; Ret.y = y;
	return(Ret);
}

// ALL RGBS FROM BITMAP:
std::vector<Point3D<uint8_t>> ysxCIMG_CLR_BitmapRGBMatrix(CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();
	std::vector<Point3D<uint8_t>> Ret(H * W);
	Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y) { for (uint16_t x = 0; x < W; ++x) { ysxCIMG_CLR_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB); Ret[y * W + x] = RGB; } }
	return(Ret);
}

// ALL PIXELS FROM BITMAP:
std::vector<Pixel> ysxCIMG_CLR_BitmapPixelMatrix(CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();
	std::vector<Pixel> Ret(H * W); Pixel Pix;
	for (uint16_t y = 0; y < H; ++y) { for (uint16_t x = 0; x < W; ++x) { Pix = ysxCIMG_CLR_BitmapPixel(BMP, x, y); Ret[y * W + x] = Pix; } }
	return(Ret);
}

// VECTOR WITH VALUE FROM '-1 TO 1' BY BITMAP VALUES (GRAYSCALE):
std::vector<double> ysxCIMG_CLR_BitmapVector(CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();	std::vector<double> V(H * W);
	double Val = 0; Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_CLR_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			Val = ((RGB.x + RGB.y + RGB.z) / 765.0); V[y * W + x] = Val;
		}
	}
	return (V);
}

// VECTOR WITH VALUE FROM '0 TO 255' (DOUBLE) BY BITMAP VALUES, CHANNEL BY INDEX (C) "R = 0, G = 1, B > 1":
std::vector<double> ysxCIMG_CLR_BitmapVector(CImg<uint8_t>& BMP, uint8_t C)
{
	uint16_t H = BMP.height(), W = BMP.width();	std::vector<double> V(H * W);
	double Val = 0; Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_CLR_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			if (!C) { Val = RGB.x; } else if (C == 1) { Val = RGB.y; } else { Val = RGB.z; }
			V[y * W + x] = Val;
		}
	}
	return (V);
}

// ALL RGBS FROM BITMAP (in float), IT GOES LIKE R, THEN G, THEN B, THEN NEXT PIXEL, SO THE VECTOR HAVE 3X THE SIZE OF THE IMAGE:
std::vector<double> ysxCIMG_CLR_BitmapRGBVector(CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width(); std::vector<double> Ret(H * W * 3);
	Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_CLR_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			Ret[y * W + x * 3] = RGB.x / 255.0; Ret[y * W + x * 3 + 1] = RGB.y = RGB.y / 255.0; Ret[y * W + x * 3 + 2] = RGB.z = RGB.z / 255.0;
		}
	}
	return(Ret);
}

// LIMITED PIXEL MATRIX:
std::vector<Pixel> ysxCIMG_CLR_BitmapPixelLimMatrix(CImg<uint8_t>& BMP, uint8_t* RGB0, uint8_t* RGB1)
{
	uint16_t H = BMP.height(), W = BMP.width(); std::vector<Pixel> Ret(H * W); Pixel Pix;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x) { Pix = ysxCIMG_CLR_BitmapPixel(BMP, x, y); if (ysxCIMG_CLR_InsideRGBGap(Pix.RGB, RGB0, RGB1)) { Ret[y * W + x] = Pix; } }
	}
	return(Ret);
}

// ############## MIX COLORS:

// MIX IMAGES AND CAN ALSO IGNORE COLORS:
CImg<uint8_t> ysxCIMG_CLR_MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1)
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
			RGB0 = ysxCIMG_CLR_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_CLR_BitmapRGB(Img1, m, n);
			Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
			Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
			Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<uint8_t> ysxCIMG_CLR_MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, bool IgnoreBlack, bool IgnoreWhite)
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
			RGB0 = ysxCIMG_CLR_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_CLR_BitmapRGB(Img1, m, n); // PEGA PIXEL
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
CImg<uint8_t> ysxCIMG_CLR_MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint8_t IgnoreColor[3])
{
	uint16_t Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, n�o vai pedir mem�ria aonde n�o tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			RGB0 = ysxCIMG_CLR_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_CLR_BitmapRGB(Img1, m, n);
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
	return (Ret);
}
CImg<uint8_t> ysxCIMG_CLR_MixRGB(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	uint16_t Width = 1, Height = 1;
	if (Img0.width() > Img1.width()) { Width = Img1.width(); }
	else { Width = Img0.width(); } // Maior que (>), pois, ao passar pelo pixel, n�o vai pedir mem�ria aonde n�o tem
	if (Img0.height() > Img1.height()) { Height = Img1.height(); }
	else { Height = Img0.height(); }
	CImg<uint8_t> Ret(Width, Height, 1, 3, 0);
	Point3D<uint8_t> RGB0, RGB1;
	uint8_t Clr[3];
	for (uint16_t n = 0; n < Height; ++n)
	{
		for (uint16_t m = 0; m < Width; ++m)
		{
			if (ysxCIMG_InImg(Img0, n + y, m + x))
			{
				RGB0 = ysxCIMG_CLR_BitmapRGB(Img0, m + x, n + y), RGB1 = ysxCIMG_CLR_BitmapRGB(Img1, m, n);
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

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############## TEXTOS:

// ################################################# FIM ####################################################################################

#endif // SCPARSE_