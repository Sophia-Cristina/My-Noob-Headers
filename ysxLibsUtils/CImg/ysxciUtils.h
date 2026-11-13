#pragma once

#ifndef YSXCIUTILS_H
#define YSXCIUTILS_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### CImg for utils, like GUI, interfaces, human-readable stuffs..
// #####################


// #################################################

// #################################################
// ####### IMAGE CANVAS OPERATIONS:

// JOIN IMAGES (APPEND):
CImg<uint8_t> ysxCIMG_JoinImg(CImg<uint8_t>& I1, CImg<uint8_t>& I2, bool RightOrDown)
{
	uint16_t W = 1, H = 1;
	if (!RightOrDown) { W = I1.width() + I2.width(); I1.height() > I2.height() ? H = I1.height() : H = I2.height(); }
	else { H = I1.height() + I2.height(); I1.width() > I2.width() ? W = I1.width() : W = I2.width(); }
	CImg<uint8_t> I3(W, H, 1, 3, 0); I3.draw_image(0, 0, I1);
	RightOrDown ? I3.draw_image(0, I1.height(), I2) : I3.draw_image(I1.width(), 0, I2);	
	return(I3);
}

// RESIZE:
void ysxCIMG_Resize(CImg<uint8_t>& Img, uint16_t xrs, uint16_t yrs, uint8_t Interpolation)
{
	if (Interpolation < 1) { Interpolation = 1; } if (Interpolation > 6) { Interpolation = 6; }
	Img.resize(xrs, yrs, 3, 3, Interpolation, 0, 0, 0, 0, 0);
}

// INVERT:
void ysxCIMG_Invert(CImg<uint8_t>& Img)
{
	uint16_t H = Img.height(), W = Img.width();
	for (uint16_t n = 0; n < H; ++n)
	{
		for (uint16_t m = 0; m < W; ++m)
		{
			Point3D<uint8_t> RGB = ysxCIMG_BitmapRGB(Img, m, n);
			uint8_t C[] = { 255 - RGB.x, 255 - RGB.y, 255 - RGB.z }; Img.draw_point(m, n, C);
		}
	}
}


// EXPAND IMAGE BORDERS:
// (char as byte, '0' to '8', '0 = center', imagine an octagon, '1 = top side', clock-wise, '2 = top-right side', and that is how it goes)
CImg<uint8_t> ysxCIMG_ExpandImgBorders(CImg<uint8_t>& Img, uint8_t Size, uint8_t Side)
{
	// W = Width | H = height | e = Ex | i = Img | m = mid
	size_t Wi = Img.width(), Hi = Img.height(), Wim = (size_t)(Wi * 0.5), Him = (size_t)(Hi * 0.5);
	CImg<uint8_t> Ex(Wi + Size * 2, Hi + Size * 2, 1, 3, 0);
	size_t We = Ex.width(), He = Ex.height(), Wem = (size_t)(We * 0.5), Hem = (size_t)(He * 0.5);
	
	if (Side == 0) { Ex.draw_image(Wem - Wim, Hem - Him, Img); }  // Center
	else if (Side == 1) { Ex.draw_image(Wem - Wim, 0, Img); } // Top
	else if (Side == 2) { Ex.draw_image(We - Wi, 0, Img); } // Top-Right
	else if (Side == 3) { Ex.draw_image(We - Wi, Hem - Him, Img); } // Right
	else if (Side == 4) { Ex.draw_image(We - Wi, He - Hi, Img); } // Bottom-Right
	else if (Side == 5) { Ex.draw_image(Wem - Wim, He - Hi, Img); } // Bottom
	else if (Side == 6) { Ex.draw_image(0, He - Hi, Img); } // Bottom-Left
	else if (Side == 7) { Ex.draw_image(0, Hem - Him, Img); } // Left
	else { Ex.draw_image(0, 0, Img); } // Top-Left

	return(Ex);
}

// DRAW IMAGE OVER ANOTHER IMAGE, BUT IGNORE SPECIFIC COLOR:
// Change this function to another header! Add an 'if' to avoid 'nullptr'.
CImg<uint8_t> ysxCIMG_DrawImageIgnClr(CImg<uint8_t>& Img0, CImg<uint8_t>& Img1, uint32_t x, uint32_t y, uint8_t IgnoreColor[3])
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


// #################################################
// #################################################
// #################################################

#endif
