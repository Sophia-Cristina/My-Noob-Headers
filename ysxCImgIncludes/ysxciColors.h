#pragma once

#ifndef YSXCICOLORS_H
#define YSXCICOLORS_H

using namespace cimg_library;

// ###################################
// ############## FUNÇÕES #######
// ###################################
// ############## DECLARAÇÕES:
Point3D BitmapRGB(CImg<unsigned char>, int, int);
Point3D LinearRGB(double, double, double);
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
bool InsideRGBGap(unsigned char RGB[3], int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB[0] >= R0 && RGB[0] <= R1 && RGB[1] >= G0 && RGB[1] <= G1 && RGB[2] >= B0 && RGB[2] <= B1) { return(true); } else { return(false); } }
bool InsideRGBGap(Point3D RGB, int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB.x >= R0 && RGB.x <= R1 && RGB.y >= G0 && RGB.y <= G1 && RGB.z >= B0 && RGB.z <= B1) { return(true); } else { return(false); } }
bool InsideRGBGapOR(unsigned char RGB[3], int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB[0] >= R0 || RGB[0] <= R1 || RGB[1] >= G0 || RGB[1] <= G1 || RGB[2] >= B0 || RGB[2] <= B1) { return(true); } else { return(false); } }
bool InsideRGBGapOR(Point3D RGB, int R0, int R1, int G0, int G1, int B0, int B1)
{ if (RGB.x >= R0 || RGB.x <= R1 || RGB.y >= G0 || RGB.y <= G1 || RGB.z >= B0 || RGB.z <= B1) { return(true); } else { return(false); } }


// MAX / MIN OF PIXEL X AND Y:
Point MaxxMinxPixel(std::vector<Pixel> VP)
{
	Point MM;
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
Point MaxyMinyPixel(std::vector<Pixel> VP)
{
	Point MM;
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
void MaxMinPixel(std::vector<Pixel> VP, Point& MaxxMinx, Point& MaxyMiny)
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
Point3D BitmapRGB(CImg<unsigned char> BMP, int x, int y)
{
	Point3D Ret;
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (x < 0) { x = 0; }
	if (y > BMP.height() - 1) { y = BMP.height() - 1; } if (y < 0) { y = 0; }
	Ret.x = BMP(x, y, 0, 0); Ret.y = BMP(x, y, 0, 1); Ret.z = BMP(x, y, 0, 2);
	return(Ret);
}
// BITMAP PIXEL:
Pixel BitmapPixel(CImg<unsigned char> BMP, int x, int y)
{
	Pixel Ret;
	if (x > BMP.width() - 1) { x = BMP.width() - 1; } if (x < 0) { x = 0; }
	if (y > BMP.height() - 1) { y = BMP.height() - 1; } if (y < 0) { y = 0; }
	Ret.RGB[0] = BMP(x, y, 0, 0); Ret.RGB[1] = BMP(x, y, 0, 1); Ret.RGB[2] = BMP(x, y, 0, 2);
	Ret.x = x; Ret.y = y;
	return(Ret);
}

// ALL RGBS FROM BITMAP:
std::vector<Point3D> BitmapRGBMatrix(CImg<unsigned char> BMP)
{
	std::vector<Point3D> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{ Point3D RGB = BitmapRGB(BMP, n, m); Ret.push_back(RGB); }
	}
	return(Ret);
}
// ALL PIXELS FROM BITMAP:
std::vector<Pixel> BitmapPixelMatrix(CImg<unsigned char> BMP)
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
std::vector<double> BitmapRGBVector(CImg<unsigned char> BMP)
{
	std::vector<double> Ret;
	for (int m = 0; m < BMP.height(); ++m)
	{
		for (int n = 0; n < BMP.width(); ++n)
		{
			Point3D RGB = BitmapRGB(BMP, n, m);  Ret.push_back(RGB.x / 255.0);  Ret.push_back(RGB.y = RGB.y / 255.0);  Ret.push_back(RGB.z = RGB.z / 255.0);
		}
	}
	return(Ret);
}

// LIMITED PIXEL MATRIX:
std::vector<Pixel> BitmapPixelLimMatrix(CImg<unsigned char> BMP, int R0, int R1, int G0, int G1, int B0, int B1)
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
		CImg<unsigned char> BMP;
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
Point3D LinearRGB(double n, double Lum, double Cont)
{
	if (n < 0.0) { n *= -1; } if (n > 1.0) { n = n - floor(n); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	int R = 0, G = 0, B = 0;
	double m;

	if (n <= 1.0 / 6) {	m = n * 6; R = 255; G = round(255 * m); B = 0; }
	if (n <= 2.0 / 6 && n > 1.0 / 6) { m = (n - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0;	}
	if (n <= 3.0 / 6 && n > 2.0 / 6) { m = (n - (2.0 / 6)) * 6; R = 0; G = 255;	B = round(255 * m); }
	if (n <= 4.0 / 6 && n > 3.0 / 6) { m = (n - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	if (n <= 5.0 / 6 && n > 4.0 / 6) { m = (n - (4.0 / 6)) * 6;	R = round(255 * m); G = 0; B = 255;	}
	if (n <= 6.0 / 6 && n > 5.0 / 6) { m = (n - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m));	}

	// Contraste:
	if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
	if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
	if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }

	// Luminosidade:
	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	if (Lum > 1.0) { if (R == 0) { R = 1; } if (G == 0) { G = 1; } if (B == 0) { B = 1; } double LumMath = 255 * (Lum - 1); R = R + LumMath; G = G + LumMath; B = B + LumMath; }

	// Limite:
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	Point3D RGB; RGB.x = R; RGB.y = G; RGB.z = B;
	return(RGB);
}

// Returns unsignec char[3]:
unsigned char* LinearRGBuc(double n, double Lum, double Cont)
{
	if (n < 0.0) { n *= -1; } if (n > 1.0) { n = n - floor(n); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	int R = 0, G = 0, B = 0;
	double m;

	if (n <= 1.0 / 6) { m = n * 6; R = 255; G = round(255 * m); B = 0; }
	if (n <= 2.0 / 6 && n > 1.0 / 6) { m = (n - (1.0 / 6)) * 6; R = round(255 - (255 * m)); G = 255; B = 0; }
	if (n <= 3.0 / 6 && n > 2.0 / 6) { m = (n - (2.0 / 6)) * 6; R = 0; G = 255;	B = round(255 * m); }
	if (n <= 4.0 / 6 && n > 3.0 / 6) { m = (n - (3.0 / 6)) * 6; R = 0; G = round(255 - (255 * m)); B = 255; }
	if (n <= 5.0 / 6 && n > 4.0 / 6) { m = (n - (4.0 / 6)) * 6;	R = round(255 * m); G = 0; B = 255; }
	if (n <= 6.0 / 6 && n > 5.0 / 6) { m = (n - (5.0 / 6)) * 6; R = 255; G = 0; B = round(255 - (255 * m)); }

	// Contraste:
	if (R > 127) { R = R - ((R - 127) * (1 - Cont)); } if (R < 127) { R = R + ((127 - R) * (1 - Cont)); }
	if (G > 127) { G = G - ((G - 127) * (1 - Cont)); } if (G < 127) { G = G + ((127 - G) * (1 - Cont)); }
	if (B > 127) { B = B - ((B - 127) * (1 - Cont)); } if (B < 127) { B = B + ((127 - B) * (1 - Cont)); }

	// Luminosidade:
	if (Lum <= 1.0) { R = round(R * Lum); G = round(G * Lum); B = round(B * Lum); }
	if (Lum > 1.0) { if (R == 0) { R = 1; } if (G == 0) { G = 1; } if (B == 0) { B = 1; } double LumMath = 255 * (Lum - 1); R = R + LumMath; G = G + LumMath; B = B + LumMath; }

	// Limite:
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	unsigned char RGB[] = { R, G, B };
	return(RGB);
}

// ####### PRINTS:

// Brilho:
CImg<unsigned char> PaletaLinRGBLum(int sx, int sy, double div)
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

	return(Paleta);
}

// Contraste:
CImg<unsigned char> PaletaLinRGBCont(int sx, int sy, double div)
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

	return(Paleta);
}

// Só uma linha de cor:
CImg<unsigned char> PaletaLinRGB(int sx, int sy)
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
	return(Paleta);
}

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

// ################################################# FIM ####################################################################################

#endif // SCPARSE_