#pragma once

#ifndef YSXCIFRACTALS_H
#define YSXCIFRACTALS_H

using namespace cimg_library;

// #####################
// ####### By Sophia Cristina
// ####### Plot fractals!
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ######################################################################

// ############## FRACTALS:


// ######################################################################

// ###################################
// ############## CLASSES ##############
// ###################################

// MANDELBROT:
class ysxCIMG_DRAW_Mandelbrot
{
public:
	double Zoom = 0.007042; // 1 / 142;
	double Panx = 0, Pany = 0;
	uint32_t Iter = 42;

	// #################################################

	// '0 to 1' SCALED TO MANDEL SET:
	void SetScaledPan(double px, double py)
	{
		if (px < 0) { px = 0; }	if (py < 0) { py = 0; }
		if (px > 1) { px = 1; }	if (py > 1) { py = 1; }
		Panx = 2.47 * px - 2; Pany = 2.24 * py - 1.12;
	}
	void SetSclPanx(double px) { if (px < 0) { px = 0; } if (px > 1) { px = 1; } Panx = 2.47 * px - 2; }
	void SetSclPany(double py) { if (py < 0) { py = 0; } if (py > 1) { py = 1; } Pany = 2.24 * py - 1.12; }

	// #################################################

	// CHECK IF INSIDE SET, RETURN A VALUE BASED ON THE ITERATION:
	double CheckInSet(double x, double y)
	{
		double Real = x, Img = y;
		double tReal, tImg;
		for (uint32_t i = 0; i < Iter; i++)
		{
			tReal = Real * Real - Img * Img + x;
			tImg = 2 * Real * Img + y;
			Real = tReal; Img = tImg;
			if (Real * Img > 5) { return ((double)i / Iter); } // Return a number as a multiplier:
		}
		return (0); // Return zero if in set
	}

	// #################################################
	// #################################################
	// #################################################

	// DRAW FRACTAL:
	void Draw(CImg<uint8_t>& Canvas)
	{
		uint32_t W = Canvas.width(), H = Canvas.height();
		Point<double> SclCanv = { 2.47 / W, 2.24 / H };
		double InSet, Mod; uint8_t c[3];
		for (uint32_t x = 0; x < W; x++)
		{
			for (uint32_t y = 0; y < H; y++)
			{
				Point<double> Scaled = { (x * SclCanv.x) - 2, (y * SclCanv.y) - 1.12 }; // x and y scaled to set size

				InSet = CheckInSet(Scaled.x / Zoom + Panx, Scaled.y / Zoom + Pany);
				if (InSet != 0)
				{
					Mod = InSet * ((double)(x + y) / (W + H));
					ysxCOLOR_LinearRGB(Mod, 1, 1, c); // Canvas.fillStyle = 'hsl(' + Mod * 360 * 15 + ', 100%, 50%)';
					Canvas.draw_point(x, y, c); // Draw a colorful pixel
				}
			}
		}
	}

	// #################################################

	// DRAW FRACTAL ANIMATION:
	// Prefer to use vectors of same size!
	// Use 'SaveInstead' if the memory of vector is too high, this is going to return an empty vector,
	// but, instead, it is going to save on the 'Path'.
	std::vector<CImg<uint8_t>> DrawAnimation
	(
		CImg<uint8_t>& Canvas, bool SaveInstead, std::string Path = "",
		std::vector<double>* ColorMod = NULL, std::vector<double>* ZoomMod = NULL,
		std::vector<double>* PanxMod = NULL, std::vector<double>* PanyMod = NULL,
		std::vector<double>* xMod = NULL, std::vector<double>* yMod = NULL
	)
	{
		uint32_t W = Canvas.width(), H = Canvas.height(); Point<double> SclCanv = { 2.47 / W, 2.24 / H };
		CImg<uint8_t> Frame;
		double tZoom = Zoom, tpx = Panx, tpy = Pany;
		double InSet, Mod;		
		uint32_t modsz = 0, magsz = 0, pxsz = 0, pysz = 0, xsz = 0, ysz = 0;
		if (ColorMod != NULL) { modsz = ColorMod->size(); } if (ZoomMod != NULL) { magsz = ZoomMod->size(); }
		if (PanxMod != NULL) { pxsz = PanxMod->size(); } if (PanyMod != NULL) { pysz = PanyMod->size(); }
		if (xMod != NULL) { xsz = xMod->size(); } if (yMod != NULL) { ysz = yMod->size(); }
		uint32_t sx, sy; Point<double> Scaled;
		uint8_t c[3]; std::string s;

		uint32_t Frames = 1;
		{
			uint32_t tF;
			pysz > pxsz ? tF = pysz : tF = pxsz;
			if (modsz > tF) { tF = modsz; }	if (magsz > tF) { tF = magsz; }
			Frames = tF;
		}

		std::vector<CImg<uint8_t>> Film; // <------- THE ANIMATION

		for (uint32_t n = 0; n < Frames; ++n)
		{
			Frame = Canvas;
			if (pxsz > 0 && n < pxsz) { Panx *= PanxMod->at(n); }
			if (pysz > 0 && n < pysz) { Pany *= PanyMod->at(n); }
			if (magsz > 0 && n < magsz) { Zoom *= ZoomMod->at(n); }

			for (uint32_t x = 0; x < W; x++)
			{
				for (uint32_t y = 0; y < H; y++)
				{
					sx = x, sy = y;
					if (xsz > 0 && n < xsz) { sx *= xMod->at(n); }
					if (ysz > 0 && n < ysz) { sy *= yMod->at(n); }

					Scaled = { (x * SclCanv.x) - 2, (y * SclCanv.y) - 1.12 }; // x and y scaled to set size
					InSet = CheckInSet(Scaled.x / Zoom + Panx, Scaled.y / Zoom + Pany);
					if (InSet != 0)
					{
						Mod = InSet * ((double)(sx + sy) / (W + H));
						if (modsz > 0 && n < modsz) { Mod += ColorMod->at(n); }
						ysxCOLOR_LinearRGB(Mod, 1, 1, c);
						Frame.draw_point(x, y, c); // Draw a colorful pixel // Maybe sx and sy instead
					}
				}
			}
			if (SaveInstead)
			{
				if (Path.size() > 0)
				{
					s = Path;
					s += " - f[" + std::to_string(n) + "]";
					if (ZoomMod != NULL) { s += " - Zoom[" + std::to_string(ZoomMod->at(n)) + "]"; }
					s += ".bmp";
					Frame.save_bmp(s.data());
				}
			}
			else { Film.push_back(Frame); }
			Zoom = tZoom, Panx = tpx, Pany = tpy;
		}
		return(Film);
	}
};

// ######################################################################
// ######################################################################
// ######################################################################

#endif // SCPARSE_
