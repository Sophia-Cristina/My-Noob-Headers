#pragma once

#ifndef YSXCIDRAW_H
#define YSXCIDRAW_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Things to draw basic graphs!
// #####################

// WARNING: THINGS HERE ARE LATER GOING TO BE FOR MULTIPLE LIBS AND CONTROLLED BY PRE-COMPILER CODES!

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ######################################################################

// ############## LINES:

// PLOT LINE:
void ysxCIMG_DRAW_Line(CImg<uint8_t>& Img, double r, double rad, uint16_t x, uint16_t y, bool Triangle, uint8_t* C = nullptr)
{
	size_t yc, xc, rn, xend = (size_t)round(cos(rad) * r), yend = (size_t)round(sin(rad) * r);
	uint8_t c[3], IC[3];

	for (rn = 0; rn <= r; rn = ++rn)
	{
		yc = y + round(sin(rad) * rn); xc = x + round(cos(rad) * rn);

		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB(rn / r, 1, 1, c);	Img.draw_point(xc, yc, c); }
			else { Img.draw_point(xc, yc, C); }
			if (Triangle)
			{
				if (!C) { IC[0] = 255 - c[0]; IC[1] = 255 - c[1]; IC[2] = 255 - c[2]; }
				else { IC[0] = 255 - C[0]; IC[1] = 255 - C[1]; IC[2] = 255 - C[2]; }
				Img.draw_point(xc, y, IC); Img.draw_point(x + xend, yc, IC);
			}
		}
	}
}

// BRESENHAM LINE:
void ysxCIMG_DRAW_Linexy(CImg<uint8_t>& Img, int x1, int y1, int x2, int y2, uint8_t* C = nullptr)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1, dy = y2 - y1;
	dx1 = fabs(dx), dy1 = fabs(dy);
	px = 2 * dy1 - dx1, py = 2 * dx1 - dy1;
	uint8_t c[] = { 255, 0 , 0 };
	if (dy1 <= dx1)
	{
		if (dx >= 0) { x = x1; y = y1; xe = x2; }
		else { x = x2; y = y2; xe = x1; }
		if (!C) { Img.draw_point(x, y, c); } else { Img.draw_point(x, y, C); }
		for (i = 0; x < xe; i++)
		{
			x += 1;	if (px < 0) { px = px + 2 * dy1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { y = y + 1; } else { y = y - 1; } px = px + 2 * (dy1 - dx1); }
			if (!C) { ysxCOLOR_LinearRGB(x / (xe - 1.0), 1, 1, c); Img.draw_point(x, y, c); }
			else { Img.draw_point(x, y, C); }
		}
	}
	else
	{
		if (dy >= 0) { x = x1; y = y1; ye = y2; }
		else { x = x2; y = y2; ye = y1; }
		if (!C) { Img.draw_point(x, y, c); } else { Img.draw_point(x, y, C); }
		for (i = 0; y < ye; i++)
		{
			y += 1; if (py <= 0) { py = py + 2 * dx1; }
			else { if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) { x = x + 1; } else { x = x - 1; }	py = py + 2 * (dx1 - dy1); }
			if (!C) { ysxCOLOR_LinearRGB(y / (ye - 1.0), 1, 1, c); Img.draw_point(x, y, c); }
			else { Img.draw_point(x, y, C); }
		}
	}
}

// ######################################################################
// ######################################################################
// ######################################################################

#endif // SCPARSE_
