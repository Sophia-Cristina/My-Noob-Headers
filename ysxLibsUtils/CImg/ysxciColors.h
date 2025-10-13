#pragma once

#ifndef YSXCICOLORS_H
#define YSXCICOLORS_H

using namespace cimg_library;

// ############## FORWARD DECLARATION:
//Point3D<uint8_t> BitmapRGB(CImg<uint8_t>&, uint32_t, uint32_t);

// ############################################################################################################################################

// ############## TECHNICAL:

// ############################################################################################################################################

// ############## MAX / MIN:

// ############################################################################################################################################
// ############## BITMAP:

// BITMAP RGB:
Point3D<uint8_t> ysxCIMG_BitmapRGB(const CImg<uint8_t>& BMP, uint32_t x, uint32_t y)
{
	Point3D<uint8_t> Ret;
	Ret.x = BMP(x, y, 0, 0); Ret.y = BMP(x, y, 0, 1); Ret.z = BMP(x, y, 0, 2);
	return(Ret);
}
void ysxCIMG_BitmapRGBuc(const CImg<uint8_t>& BMP, uint32_t x, uint32_t y, uint8_t* Clr)
{
	Clr[0] = BMP(x, y, 0, 0); Clr[1] = BMP(x, y, 0, 1); Clr[2] = BMP(x, y, 0, 2);
}

// BITMAP PIXEL:
Pixel ysxCIMG_BitmapPixel(const CImg<uint8_t>& BMP, uint32_t x, uint32_t y)
{
	Pixel Ret;
	Ret.RGB[0] = BMP(x, y, 0, 0); Ret.RGB[1] = BMP(x, y, 0, 1); Ret.RGB[2] = BMP(x, y, 0, 2);
	Ret.x = x; Ret.y = y;
	return(Ret);
}

// ALL RGBS FROM BITMAP:
std::vector<Point3D<uint8_t>> ysxCIMG_BitmapRGBMatrix(const CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();
	std::vector<Point3D<uint8_t>> Ret(H * W);
	Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y) { for (uint16_t x = 0; x < W; ++x) { ysxCIMG_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB); Ret[y * W + x] = RGB; } }
	return(Ret);
}

// ALL PIXELS FROM BITMAP:
std::vector<Pixel> ysxCIMG_BitmapPixelMatrix(const CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();
	std::vector<Pixel> Ret(H * W); Pixel Pix;
	for (uint16_t y = 0; y < H; ++y) { for (uint16_t x = 0; x < W; ++x) { Pix = ysxCIMG_BitmapPixel(BMP, x, y); Ret[y * W + x] = Pix; } }
	return(Ret);
}

// VECTOR WITH VALUE FROM '-1 TO 1' BY BITMAP VALUES (GRAYSCALE):
std::vector<double> ysxCIMG_BitmapVector(const CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width();	std::vector<double> V(H * W);
	double Val = 0; Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			Val = ((RGB.x + RGB.y + RGB.z) / 765.0); V[y * W + x] = Val;
		}
	}
	return (V);
}

// VECTOR WITH VALUE FROM '0 TO 255' (DOUBLE) BY BITMAP VALUES, CHANNEL BY INDEX (C) "R = 0, G = 1, B > 1":
std::vector<double> ysxCIMG_BitmapVector(const CImg<uint8_t>& BMP, uint8_t C)
{
	uint16_t H = BMP.height(), W = BMP.width(); std::vector<double> V(H * W);
	double Val = 0; Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			if (!C) { Val = RGB.x; } else if (C == 1) { Val = RGB.y; } else { Val = RGB.z; }
			V[y * W + x] = Val;
		}
	}
	return (V);
}

// ALL RGBS FROM BITMAP (in float), IT GOES LIKE R, THEN G, THEN B, THEN NEXT PIXEL, SO THE VECTOR HAVE 3X THE SIZE OF THE IMAGE:
std::vector<double> ysxCIMG_BitmapRGBVector(const CImg<uint8_t>& BMP)
{
	uint16_t H = BMP.height(), W = BMP.width(); std::vector<double> Ret(H * W * 3);
	Point3D<uint8_t> RGB;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x)
		{
			ysxCIMG_BitmapRGBuc(BMP, x, y, (uint8_t*)&RGB);
			Ret[y * W + x * 3] = RGB.x / 255.0; Ret[y * W + x * 3 + 1] = RGB.y = RGB.y / 255.0; Ret[y * W + x * 3 + 2] = RGB.z = RGB.z / 255.0;
		}
	}
	return(Ret);
}

// LIMITED PIXEL MATRIX:
std::vector<Pixel> ysxCIMG_BitmapPixelLimMatrix(const CImg<uint8_t>& BMP, uint8_t* RGB0, uint8_t* RGB1)
{
	uint16_t H = BMP.height(), W = BMP.width(); std::vector<Pixel> Ret(H * W); Pixel Pix;
	for (uint16_t y = 0; y < H; ++y)
	{
		for (uint16_t x = 0; x < W; ++x) { Pix = ysxCIMG_BitmapPixel(BMP, x, y); if (ysxCOLOR_InsideRGBGap(Pix.RGB, RGB0, RGB1)) { Ret[y * W + x] = Pix; } }
	}
	return(Ret);
}

// ############## MIX COLORS:

// MIX IMAGES AND CAN ALSO IGNORE COLORS:
CImg<uint8_t> ysxCIMG_MixRGB(const CImg<uint8_t>& Img0, const CImg<uint8_t>& Img1)
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
			RGB0 = ysxCIMG_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_BitmapRGB(Img1, m, n);
			Clr[0] = round((RGB0.x + RGB1.x) * 0.5);
			Clr[1] = round((RGB0.y + RGB1.y) * 0.5);
			Clr[2] = round((RGB0.z + RGB1.z) * 0.5);
			Ret.draw_point(m, n, Clr);
		}
	}
	return (Ret);
}
CImg<uint8_t> ysxCIMG_MixRGB(const CImg<uint8_t>& Img0, const CImg<uint8_t>& Img1, bool IgnoreBlack, bool IgnoreWhite)
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
			RGB0 = ysxCIMG_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_BitmapRGB(Img1, m, n); // PEGA PIXEL
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
CImg<uint8_t> ysxCIMG_MixRGB(const CImg<uint8_t>& Img0, const CImg<uint8_t>& Img1, uint8_t IgnoreColor[3])
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
			RGB0 = ysxCIMG_BitmapRGB(Img0, m, n), RGB1 = ysxCIMG_BitmapRGB(Img1, m, n);
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
CImg<uint8_t> ysxCIMG_MixRGB(const CImg<uint8_t>& Img0, const CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
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
			if (ysxCIMG_InImg(Img0, n + y, m + x))
			{
				RGB0 = ysxCIMG_BitmapRGB(Img0, m + x, n + y), RGB1 = ysxCIMG_BitmapRGB(Img1, m, n);
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