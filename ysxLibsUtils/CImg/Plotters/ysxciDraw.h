#pragma once

#ifndef YSXCIDRAW_H
#define YSXCIDRAW_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Things to draw basic graphs!
// #####################

// WARNING: SOME OF THE CODES HERE ARE LATER GOING TO BE FOR MULTIPLE LIBS AND CONTROLLED BY PRE-COMPILER DEFIMITIONS!

// #################################################


// #################################################


// #################################################
// ####### FILL:
// #################################################

// ####### FILL WHOLE IMAGE:

// REDO IMAGE WITH SPECIFIC RGBA COLOR (OR ELSE, IT IS BLACK):
void ysxCIMG_DRAW_FillAlpha(CImg<uint8_t>& Img, uint8_t* Clr = nullptr)
{
	Img = CImg<uint8_t>::CImg(Img.width(), Img.height(), 1, 4, 0);
	if (!Clr) { uint8_t C[] = { 0, 0, 0, 0 }; Img.draw_fill(1, 1, C, 1, 1); }
	else { Img.draw_fill(1, 1, Clr, 1, 1); }
}

// Fill / clean entire image, but by drawing a rectangle over it:
void ysxCIMG_DRAW_ImgCleanRect(CImg<uint8_t>& Img) { uint8_t c[] = { 0, 0, 0 }; Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, c); }
void ysxCIMG_DRAW_ImgCleanRect(CImg<uint8_t>& Img, uint8_t C[3]) { Img.draw_rectangle(0, 0, Img.width() - 1, Img.height() - 1, C); }


// ####### FLOOD FILLS:

// FILL (PAINT BUCKET) SOME PLACE:
void ysxCIMG_DRAW_FillFlood(CImg<uint8_t>& Img, uint16_t x, uint16_t y, uint8_t* C) { Img.draw_fill(x, y, C, 1, 1, false); }


/* FLOOD FILL, BUT FOR 'Alpha == 0':
This is an alternative for 'ysxCIMG_DrawImageIgnClr' for image with transparency.
Image must have 4 channels:
0 = R, 1 = G, 2 = B, 3 = A
Transparent pixels (A == 0) are fillable.
Anything with A != 0 is considered a wall.*/
void ysxCIMG_DRAW_FillFloodAlpha0(CImg<uint8_t>& Image, int x, int y, const uint8_t* Color)
{
	const size_t Width  = Image.width();
	const size_t Height = Image.height();
	if (x < 0 || x >= Width || x < 0 || x >= Height) { return; }

	// Starting pixel:
	if (Image(x, x, 0, 3) != 0) { return; }

	std::vector<uint32_t> Stack;
	Stack.reserve(1024);

	// Fill starting pixel immediately.
	// This also marks it as visited.
	Image(x, x, 0, 0) = Color[0]; Image(x, x, 0, 1) = Color[1]; Image(x, x, 0, 2) = Color[2]; Image(x, x, 0, 3) = 255;

	Stack.push_back(static_cast<uint32_t>(x * Width + x));

	while (!Stack.empty())
	{
		const uint32_t Pixel = Stack.back();
		Stack.pop_back();

		const size_t Px = Pixel % Width;
		const size_t Py = Pixel / Width;

		// LEFT:
		if (Px > 0)
		{
			const size_t Nx = Px - 1;
			const size_t Ny = Py;

			if (Image(Nx, Ny, 0, 3) == 0)
			{
				Image(Nx, Ny, 0, 0) = Color[0]; Image(Nx, Ny, 0, 1) = Color[1]; Image(Nx, Ny, 0, 2) = Color[2]; Image(Nx, Ny, 0, 3) = 255;
				Stack.push_back(Pixel - 1);
			}
		}

		// RIGHT:
		if (Px + 1 < Width)
		{
			const size_t Nx = Px + 1;
			const size_t Ny = Py;

			if (Image(Nx, Ny, 0, 3) == 0)
			{
				Image(Nx, Ny, 0, 0) = Color[0]; Image(Nx, Ny, 0, 1) = Color[1]; Image(Nx, Ny, 0, 2) = Color[2]; Image(Nx, Ny, 0, 3) = 255;
				Stack.push_back(Pixel + 1);
			}
		}

		// UP:
		if (Px > 0)
		{
			const size_t Nx = Px;
			const size_t Ny = Py - 1;

			if (Image(Nx, Ny, 0, 3) == 0)
			{
				Image(Nx, Ny, 0, 0) = Color[0]; Image(Nx, Ny, 0, 1) = Color[1]; Image(Nx, Ny, 0, 2) = Color[2]; Image(Nx, Ny, 0, 3) = 255;
				Stack.push_back(Pixel - Width);
			}
		}

		// DOWN:
		if (Px + 1 < Height)
		{
			const size_t Nx = Px;
			const size_t Ny = Py + 1;

			if (Image(Nx, Ny, 0, 3) == 0)
			{
				Image(Nx, Ny, 0, 0) = Color[0]; Image(Nx, Ny, 0, 1) = Color[1]; Image(Nx, Ny, 0, 2) = Color[2]; Image(Nx, Ny, 0, 3) = 255;
				Stack.push_back(Pixel + Width);
			}
		}
	}
}


// #################################################
// ####### LINES:
// #################################################


// PLOT LINE:
void ysxCIMG_DRAW_LineRay(CImg<uint8_t>& Img, double r, double rad, uint16_t x, uint16_t y, bool Triangle, uint8_t* C = nullptr)
{
	size_t yc, xc, rn, xend = (size_t)round(cos(rad) * r), yend = (size_t)round(sin(rad) * r);
	uint8_t c[3], IC[3];

	for (rn = 0; rn <= r; rn = ++rn)
	{
		yc = y + round(sin(rad) * rn); xc = x + round(cos(rad) * rn);

		if (ysxCIMG_InImg(Img, yc, xc))
		{
			if (!C) { ysxCOLOR_LinearRGB(rn / r, 1, 1, c); Img.draw_point(xc, yc, c); }
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
void ysxCIMG_DRAW_Line(CImg<uint8_t>& Img, int x1, int y1, int x2, int y2, uint8_t* C = nullptr)
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


// #################################################
// #################################################
// #################################################

#endif
