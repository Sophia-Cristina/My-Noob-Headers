#pragma once

// #################################################
// #################################################
// #################################################
// #####################
// ##################### !!!!!!!! ATTENTION !!!!!!!
// ##################### Include this header after
// ##################### other headers which import
// ##################### the JUCE library, or else
// ##################### the functions here will
// ##################### fail.
// #####################
// #################################################
// #################################################
// #################################################

#ifndef YSXJUCE_H
#define YSXJUCE_H

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

juce::Colour jLinearRGB(double n, double Lum, double Cont)
{
	if (n < 0.0) { n *= -1; } if (n > 1.0) { n = n - floor(n); }
	if (Lum > 2.0) { Lum = 2.0; } if (Lum < 0.0) { Lum = 0.0; }
	if (Cont > 1.0) { Cont = 1.0; } if (Cont < 0.0) { Cont = 0.0; }
	int R = 0, G = 0, B = 0;
	double m;

	if (n <= 1.0 / 6)
	{
		m = n * 6;
		R = 255; G = round(255 * m); B = 0;
	}
	if (n <= 2.0 / 6 && n > 1.0 / 6)
	{
		m = (n - (1.0 / 6)) * 6;
		R = round(255 - (255 * m)); G = 255; B = 0;
	}
	if (n <= 3.0 / 6 && n > 2.0 / 6)
	{
		m = (n - (2.0 / 6)) * 6;
		R = 0; G = 255;	B = round(255 * m);
	}
	if (n <= 4.0 / 6 && n > 3.0 / 6)
	{
		m = (n - (3.0 / 6)) * 6;
		R = 0; G = round(255 - (255 * m)); B = 255;
	}
	if (n <= 5.0 / 6 && n > 4.0 / 6)
	{
		m = (n - (4.0 / 6)) * 6;
		R = round(255 * m); G = 0; B = 255;
	}
	if (n <= 6.0 / 6 && n > 5.0 / 6)
	{
		m = (n - (5.0 / 6)) * 6;
		R = 255; G = 0; B = round(255 - (255 * m));
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
	unsigned char uc[] = { R, G, B };
	juce::Colour RGB = { uc[0], uc[1], uc[2] };
	return(RGB);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################           #####################
// ##################### FUNCTIONS #####################
// #####################           #####################

// 'juce::String' to 'std::string':
std::string jStr2cstr(juce::String s) { string t; for (int n = 0; n < s.length(); ++n) { t.push_back(s[n]); } return(t); }

// #####################
// #####################
// ############## ysxCImg.h:

// BITMAP PIXEL:
Pixel BitmapPixel(juce::Image I, int x, int y)
{
	Pixel Ret;
	if (x > I.getWidth() - 1) { x = I.getWidth() - 1; } if (x < 0) { x = 0; }
	if (y > I.getHeight() - 1) { y = I.getHeight() - 1; } if (y < 0) { y = 0; }
	Ret.RGB[0] = I.getPixelAt(x, y).getRed(); Ret.RGB[1] = I.getPixelAt(x, y).getGreen(); Ret.RGB[2] = I.getPixelAt(x, y).getBlue();
	Ret.x = x; Ret.y = y;
	return(Ret);
}

// ALL PIXELS FROM BITMAP:
vector<Pixel> BitmapPixelMatrix(juce::Image I)
{
	vector<Pixel> Ret;
	for (int y = 0; y < I.getHeight(); ++y)
	{
		for (int x = 0; x < I.getWidth(); ++x)
		{
			Pixel Pix = BitmapPixel(I, x, y);
			Ret.push_back(Pix);
		}
	}
	return(Ret);
}

// #####################
// #####################
// ############## ysxCImg.h/ysxciPlottlers.h:

void Circuloxy(juce::Image& Img, double r, int Imgx, int Imgy, int R, int G, int B)
{
	double y, x;
	int xzero = Imgx, yzero = Imgy;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= Tau; Rad += Step) // MUDAR SE NESCESSARIO
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);

		if (y + yzero < Img.getHeight() && y + yzero >= 0 && x + xzero < Img.getWidth() && x + xzero >= 0) // if 'InImg' from my header
		{
			unsigned char color[] = { R, G, B };
			Img.setPixelAt(x + xzero, y + yzero, { color[0], color[1], color[2] });
		}
	}
}
void Circuloxy(juce::Image& Img, double r, int Imgx, int Imgy)
{
	double y, x;
	int xzero = Imgx, yzero = Imgy;
	double Step = 1.0 / r;

	for (double Rad = 0; Rad <= Tau; Rad = Rad + Step)
	{
		y = round(sin(Rad) * r);
		x = round(cos(Rad) * r);
		double Progresso = Rad / Tau;

		if (y + yzero < Img.getHeight() && y + yzero >= 0 && x + xzero < Img.getWidth() && x + xzero >= 0) // if 'InImg' from my header
		{
			Point3D RGB = LinearRGB(Progresso, 1, 1);
			unsigned char color[] = { RGB.x, RGB.y, RGB.z };
			Img.setPixelAt(x + xzero, y + yzero, { color[0], color[1], color[2] });
		}
	}
}

// #####################################################################################################################################
// #####################  #####################

// #####################################################################################################################################

// #####################################################################################################################################
// #####################  #####################

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_