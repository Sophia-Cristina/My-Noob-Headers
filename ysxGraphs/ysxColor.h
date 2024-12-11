#pragma once

#ifndef YSXCOLOR_H
#define YSXCOLOR_H

// #####################
// ####### By Sophia Cristina
// ####### Headers for things related to colors in general.
// #####################

#include "../ysxMath/ysxMath.h"

/*#################################################
/* REFERENCES:
 [1] 
*/


/*NOTES:

*/
// #################################################


// #################################################

// ###################################
// ############## TOOLS:
struct Pixel { unsigned int x; unsigned int y; uint8_t RGB[3]; };
// ###################################


// #################################################
// ############## TECHNICAL ##############

// MAX / MIN OF PIXEL X AND Y:
Point<uint32_t> ysxCOLOR_MaxxMinxPixel(std::vector<Pixel> VP)
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
Point<uint32_t> ysxCOLOR_MaxyMinyPixel(std::vector<Pixel> VP)
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
void ysxCOLOR_MaxMinPixel(std::vector<Pixel> VP, Point<uint32_t>& MaxxMinx, Point<uint32_t>& MaxyMiny)
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

// #################################################
// ############## COLOR / PALLETES ##############

// CHANGE CONSTRAST FROM COLOR INSIDE A RGB POINTER:
void ysxCOLOR_ChangeContrast(float Cont, uint8_t* Color)
{
	if (Cont > 1.0) { Cont -= floor(Cont); } if (Cont < 0.0) { Cont *= -1; }
	if (Cont != 1)
	{
		if (Color[0] > 127) { Color[0] = Color[0] - ((Color[0] - 127) * (1 - Cont)); }
		if (Color[0] < 127) { Color[0] = Color[0] + ((127 - Color[0]) * (1 - Cont)); }
		if (Color[1] > 127) { Color[1] = Color[1] - ((Color[1] - 127) * (1 - Cont)); }
		if (Color[1] < 127) { Color[1] = Color[1] + ((127 - Color[1]) * (1 - Cont)); }
		if (Color[2] > 127) { Color[2] = Color[2] - ((Color[2] - 127) * (1 - Cont)); }
		if (Color[2] < 127) { Color[2] = Color[2] + ((127 - Color[2]) * (1 - Cont)); }
	}
}

// CHANGE BRIGHTNESS FROM COLOR INSIDE A RGB POINTER:
void ysxCOLOR_ChangeBrightness(float Bright, uint8_t* Color)
{
	if (Bright > 2.0) { Bright -= floor(Bright); } if (Bright < 0.0) { Bright *= -1; }
	uint16_t R = 0, G = 0, B = 0;
	float L = 0;

	if (Bright <= 1.0) { R = round(R * Bright); G = round(G * Bright); B = round(B * Bright); }
	else { L = 255 * (Bright - 1); R = R + L; G = G + L; B = B + L; }
	if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }
	Color[0] = R; Color[1] = G; Color[2] = B;
}

// RETURN A RGB COLOR BY LINEAR HUE AND OVERWRITE POINTED 'uint8_t[3]':
void ysxCOLOR_LinearRGB(float x, float Bright, float Cont, uint8_t* Color)
{
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x -= floor(x); }
	if (Bright > 2.0) { Bright = 2.0; } if (Bright < 0.0) { Bright = 0.0; }
	float m = 0;

	if (x >= 5.0 / 6) { m = (x - (5.0 / 6)) * 6; Color[0] = 255; Color[1] = 0; Color[2] = round(255 - (255 * m)); }
	else if (x >= 4.0 / 6) { m = (x - (4.0 / 6)) * 6; Color[0] = round(255 * m); Color[1] = 0; Color[2] = 255; }
	else if (x >= 3.0 / 6) { m = (x - (3.0 / 6)) * 6; Color[0] = 0; Color[1] = round(255 - (255 * m)); Color[2] = 255; }
	else if (x >= 2.0 / 6) { m = (x - (2.0 / 6)) * 6; Color[0] = 0; Color[1] = 255; Color[2] = round(255 * m); }
	else if (x >= 1.0 / 6) { m = (x - (1.0 / 6)) * 6; Color[0] = round(255 - (255 * m)); Color[1] = 255; Color[2] = 0; }
	else { m = x * 6; Color[0] = 255; Color[1] = round(255 * m); Color[2] = 0; }

	ysxCOLOR_ChangeContrast(Cont, Color);
	ysxCOLOR_ChangeBrightness(Bright, Color);
}


// INSIDE A GAP OF RGB NUMBERS:
bool ysxCOLOR_InsideRGBGap(const uint8_t RGB[3], const uint8_t* RGB0, const uint8_t* RGB1)
{ if (RGB[0] >= RGB0[0] && RGB[0] <= RGB1[0] && RGB[1] >= RGB0[1] && RGB[1] <= RGB1[1] && RGB[2] >= RGB0[2] && RGB[2] <= RGB1[2]) { return(true); } else { return(false); } }
bool ysxCOLOR_InsideRGBGapOR(const uint8_t RGB[3], const uint8_t* RGB0, const uint8_t* RGB1)
{ if (RGB[0] >= RGB0[0] || RGB[0] <= RGB1[0] || RGB[1] >= RGB0[1] || RGB[1] <= RGB1[1] || RGB[2] >= RGB0[2] || RGB[2] <= RGB1[2]) { return(true); } else { return(false); } }

// #################################################

#endif