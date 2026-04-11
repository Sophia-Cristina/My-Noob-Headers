// #####################
// ####### By Sophia Cristina
// ####### Fractal plotter in MS-DOS
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################


class ysxCIMG_DRAW_Mandelbrot
{
public:
	double Zoom = 0.007042; // 1 / 142;
	double Panx = 0, Pany = 0;
	long long Iter = 42;
	

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
};
