#pragma once

#ifndef YSXCIPLOTTER_H
#define YSXCIPLOTTER_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Anything related to plotting!
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ############################################################################################################################################

/*METRIC LINES:
Vertical OR horizontal divisions.
Make your changes based on the idea that the metric is scaled by image size.*/
void ysxCIMG_DRAW_MetricLines(CImg<uint8_t>&I, double a1, double a2, double Div, bool VertHori, bool Text, uint8_t * Clr) // REFAZER, e adicionar polar
{
	if (a1 > a2) { double T = a1; a1 = a2; a2 = T; }
	double sx = I.width(), sy = I.height(); // size x and y
	double Ratio = 1, Mid = 1, Delta = a2 - a1;
	uint16_t C = 0, x, y;
	if (Delta > 0)
	{
		Div = Delta / Div;

		if (VertHori) { Ratio = sx / Delta;	Mid = sy * 0.5; }
		else { Ratio = sy / Delta; Mid = sx * 0.5; }

		for (double a = a1; a <= a2; a += Div)
		{
			if (VertHori)
			{
				x = C * Div * Ratio; ++C;
				I.draw_line(x, 0, x, sy, Clr);
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					ysxCIMG_AddText(I, x, Mid, std::to_string(a), Clr);
				}
			}
			else
			{
				y = sy - (C * Div * Ratio); ++C;
				I.draw_line(0, y, sx, y, Clr);
				if (Text)
				{
					Clr[0] = 255 - Clr[0]; Clr[1] = 255 - Clr[1]; Clr[2] = 255 - Clr[2];
					ysxCIMG_AddText(I, Mid, y, std::to_string(a), Clr);
				}
			}
		}
	}
}

// ######################################################################

// POLAR (arrumar, roubei da classe, colocar x e y), fazer um com raio:
// FAZER UMA VERSÃO COM VECTOR, SEM SER POLIGONAL COMO AQUELE QUE JÁ TEM.
void ysxCIMG_DRAW_Polar(CImg<uint8_t>& I, double r, double x, double y, double t1, double t2, double Omega, double (*f)(double, double), uint8_t* C = nullptr)
{
	if (t1 < 0) { t1 = TAU + t1; } if (t2 < t1) { double T = t1; t1 = t2; t2 = T; }
	double Amp, dt = (t2 - t1) / (TAU * r); // Ver se no polar vale a pena
	uint16_t yc, xc; uint8_t c[3];
	for (double t = t1; t <= t2; t += dt)
	{
		Amp = r * f(t, Omega); // FORMULA
		yc = y + round(Amp * sin(t)); xc = x + round(Amp * cos(t));
		if (!C) { ysxCOLOR_LinearRGB((t - t1) / (t2 - t1), 1, 1, c); I.draw_point(xc, yc, c); }
		else { I.draw_point(xc, yc, C); }
	}
}

// ######################################################################

// DRAW IMAGE OVER ANOTHER IMAGE, BUT IGNORE SPECIFIC COLOR:
// Change this function to another header! Add an 'if' to avoid 'nullptr'.
CImg<uint8_t> ysxCIMG_DRAW_ImageIgnClr(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
{
	if (x < 0) { x = 0; } if (y < 0) { y = 0; }
	uint32_t  Width = Img1.width(), Height = Img1.height();
	CImg<uint8_t> Ret = Img0;
	Point3D<uint8_t> RGB;
	uint8_t Clr[3];
	for (uint32_t i = 0; i < Height; ++i)
	{
		for (uint32_t j = 0; j < Width; ++j)
		{
			if (j + x >= Img0.width() - 1) { break; }
			RGB = ysxCIMG_BitmapRGB(Img1, j, i);
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

// ######################################################################

// ############## INCLUDES:

#include "ysxciDraw.h"
#include "ysxciDrawVectors.h"
#include "ysxciGeoPlot.h"
#include "ysxciEucVec.h"
#include "ysxciSigProc.h"
#include "ysxciFractals.h"

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ###################################
// ############## CLASSES ##############
// ###################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
