#pragma once

#ifndef YSXCICOLORS_H
#define YSXCICOLORS_H

using namespace std;
using namespace cimg_library;

// ###################################
// ############## FUNÇÕES #######
// ###################################
// ############## DECLARAÇÕES:
Point3D BitmapRGB(CImg<unsigned char>, int, int);
Point3D LinearRGB(double, double, double);
// ###################################
// ############## TYPEDEFS:
typedef vector<vector<Point3DFlt>> IMGDataSet; // !!!!!!! !!!!!!! !!!!!!! PAY ATTENTION TO THIS TYPEDEF !!!!!!! !!!!!!! !!!!!!!
// ###################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## BITMAP:

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
		vector<Point3DFlt> Frame;
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

// ####### PRINTS:

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