#pragma once

#ifndef YSXCIEUCVEC_H
#define YSXCIEUCVEC_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Things to draw Eucliden Vector graphs!
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ######################################################################

// ############## EUCLIDEAN VECTORS:

// PLOT EUC. VECTOR LINE:
void ysxCIMG_DRAW_EucVec(CImg<uint8_t>& Img, Point<double> V, uint16_t x, int16_t y, double Scale, bool Arrow, bool DrawAngle, bool CartLines, bool Text, uint8_t* RGB)
{
	V.x *= Scale; V.y *= Scale;
	int xend = x + round(V.x), yend =Img.height() - (y + round(V.y));
	if (xend < 0) { xend = 0; } if (yend < 0) { yend = 0; }
	if (xend > Img.width()) { xend = Img.width(); } if (yend > Img.height()) { yend = Img.height(); }
	uint8_t C[] = { 127, 127, 127 };
	if (CartLines) { Img.draw_line(0, y, Img.width(), y, C); Img.draw_line(x, 0, x, Img.height(), C); }
	if (Arrow) { Img.draw_arrow(x, y, xend, yend, C); } else { Img.draw_line(x, y, xend, yend, RGB); }
	if (DrawAngle) { ysxCIMG_DRAW_Turn(Img, ysxEUCVEC_GetMag(V) * 0.2, x, y, 0, ysxEUCVEC_GetVecRad(V), RGB); }
	if (Text)
	{
		std::string Txt = "[" + std::to_string(V.x) + ", " + std::to_string(V.y) + "]";
		uint16_t Size = Txt.size() * 6, xtxt = (uint16_t)(xend - Size * 0.5), ytxt = (uint16_t)(yend - 10);
		if (xtxt + Txt.size() * 3.75 > Img.width()) { xtxt = xend - Size * 0.5 - Txt.size() * 3.75; } if (xtxt < 0) { xtxt = xend + Size * 0.5; }
		if (ytxt < 0) { ytxt = yend + 10; }
		ysxCIMG_AddText(Img, xtxt, ytxt, Txt, C);
	}
}

// PLOT EUC. VECTOR, TAIL BY TAIL (NOT WORKING):
void ysxCIMG_DRAW_EucVecTail
(
	CImg<uint8_t>& Img, std::vector<Point<double>> Vs, uint16_t x, int16_t y, double Scale,
	bool Arrow, bool DrawAngle, bool CartLines, bool Text, bool LRGB, uint8_t* RGB
)
{
	if (LRGB) { RGB[0] = 255; RGB[1] = 0; RGB[2] = 0; }
	ysxCIMG_DRAW_EucVec(Img, Vs[0], x, y, Scale, Arrow, DrawAngle, CartLines, Text, RGB);
	double sumx = Vs[0].x, sumy = Vs[0].y;
	for (int n = 1; n < Vs.size(); ++n)
	{
		std::cout << "sumx: " << sumx << " | sumy: " << sumy << " | V.x: " << Vs[n].x << " | V.y: " << Vs[n].y << std::endl;
		if (LRGB) { ysxCOLOR_LinearRGB(1.0 * n / Vs.size(), 1, 1, RGB); }
		int xend = x + sumx, yend = y + sumy;
		if (xend < 0) { xend = 0; } if (Img.height() - yend < 0) { yend = Img.height(); }
		if (xend > Img.width()) { xend = Img.width(); } if (Img.height() - yend > Img.height()) { yend = 0; }
		ysxCIMG_DRAW_EucVec(Img, Vs[n], xend, Img.height() - yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		//ysxCIMG_DRAW_EucVec(Img, Vs[n], xend, yend, Scale, Arrow, DrawAngle, true, Text, RGB); // depis muda para false
		std::cout << "xend: " << xend << " | Img.height() - yend: " << Img.height() - yend << "\nV.x + xend: " << Vs[n].x + xend
				  << " | Img.height() - (yend + V.y): " << Img.height() - (yend + Vs[n].y) << std::endl;
		sumx += Vs[n].x; sumy += Vs[n].y;
	}
}

// ######################################################################
// ######################################################################
// ######################################################################

#endif // SCPARSE_
