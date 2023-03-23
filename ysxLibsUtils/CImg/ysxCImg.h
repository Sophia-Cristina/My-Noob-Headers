#pragma once

#ifndef YSXCIMG_H
#define YSXCIMG_H

#pragma comment (lib, "zlib.lib")
#pragma comment (lib, "zlibstatic.lib")
//#pragma comment (lib, "zlibd.lib") // DEBUG
//#pragma comment (lib, "zlibstaticd.lib")
#pragma comment (lib, "libpng.lib")
//#pragma comment (lib, "libpngd.lib") // DEBUG

//#define cimg_use_png // unresolved external symbol png_ something something
//#define cimg_use_zlib // unresolved external symbol uncompress
//#define cimg_use_jpeg // lot of errors, not even intellisense can deal with

#include "png.h"
#include "CImg.h"
#include "ysxMath/ysxMath.h"

/*#####################
####### By Sophia Cristina
####### Personal header made do some useful stuffs with 'CImg.h'.
####### The namespace of this library is giant, so i'll keep it here.
####### This header is basically a trash thing i did so i could have graphical references
####### for my programs. It was never intended to be pro, and i did as one of the first
####### header i made in my C++ journey. So there is a lot to fix and i'm too lazy for that.
#####################*/

using namespace cimg_library; // COMMENT IF YOU ARE HAVING A PROBLEM
	// ############################################################################################################################################
	// ################################################# NOTES AND ATTENTIONS #################################################
	// !!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
	// !!!	* Lot of name changes! Prefix added to lot of things!
	// !!!	* BIG CHANGES, TAKE CARE! Templates, references and more! 21/07/22;
	// ################################################# NOTES AND ATTENTIONS #################################################
	// ############################################################################################################################################

	// ###################################
	// ############## FORWARD DECLARATIONS:
	CImg<uint8_t> ysxCIMG_DRAW_ImageIgnClr(CImg<uint8_t>&, CImg<uint8_t>&, uint32_t, uint32_t, uint8_t[3]);
	CImg<uint8_t> ysxCIMG_JoinImg(CImg<uint8_t>&, CImg<uint8_t>&, bool);
	// ###################################

	// ###################################
	// ############## TOOLS:
	struct Pixel { unsigned int x; unsigned int y; uint8_t RGB[3]; };
	// ###################################

	// ############## GENERALLY USEFUL:
	
	// POINT3D TO UI8[3]:
	void ysxCIMG_Point3D2uchar3(const Point3D<uint8_t> P, uint8_t* c) { c[0] = P.x; c[1] = P.y; c[2] = P.z; }

	// CHECK IF PIXEL IS INSIDE IMAGE (MAYBE SOON TO BE OBSOLETE):
	bool ysxCIMG_InImg(CImg<uint8_t>& Img, size_t y, size_t x) { if (y < Img.height()) { if (x < Img.width()) { return (true); } return (false); } return (false); }

	// ADD TEXT ON IMAGE:
	void ysxCIMG_AddText(CImg<uint8_t>& Img, uint32_t x, uint32_t y, std::string String, uint8_t C[3])
	{
		Img.draw_text(x, y, String.data(), C);// , 19);
	}

	// SAME AS 'AddText', BUT PRINT IN CIRCLE DIVISION WITH A VECTOR OF STRINGS:
	void ysxCIMG_AddTextCirc(CImg<uint8_t>& Img, double r, uint32_t x, uint32_t y, std::vector<std::string> Strings, uint8_t C[3])
	{
		const double Div = TAU / Strings.size(); uint32_t Count = 0;
		for (double rad = 0; rad <= TAU; rad += Div) { ysxCIMG_AddText(Img, x + round(cos(rad) * (r - 8)), y + round(sin(rad) * (r - 8)), Strings[Count], C); ++Count; }
	}

	void ysxCIMG_CleanImg(CImg<uint8_t>& Img, uint8_t* C = nullptr)
	{
		Img = CImg<uint8_t>::CImg(Img.width(), Img.height(), 1, 3, 0);
		if (C) { Img.draw_fill(1, 1, C, 1, 1, false); }
	}

// ###################################
// EXTRA:
#include "ysxLibsUtils/CImg/ysxciColors.h"
#include "ysxLibsUtils/CImg/ysxciUtils.h"
#include "ysxLibsUtils/CImg/ysxciPlotters.h"
#include "ysxLibsUtils/CImg/ysxciElecPlotters.h" // For class 'Component' of 'ysxElec.h'
#include "ysxLibsUtils/CImg/ysxciMisc.h"
// ###################################


// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############## TECHNICAL:

// SAVE:
	void ysxCIMG_SaveBMP(CImg<uint8_t> Image, std::string FileName) { Image.save_bmp(FileName.data()); }
	void ysxCIMG_SavePNG(CImg<uint8_t> Image, std::string FileName) { Image.save_png(FileName.data()); }
	void ysxCIMG_SavePNG(CImg<uint8_t> Image, std::string FileName, int BytesPerPixel) { Image.save_png(FileName.data(), BytesPerPixel); } // needs 'libpng' defined
	void ysxCIMG_SaveJPG(CImg<uint8_t> Image, std::string FileName) { Image.save_jpeg(FileName.data(), 100); } // 100% quality
	void ysxCIMG_SaveJPG(CImg<uint8_t> Image, std::string FileName, int QualityPercent) { Image.save_jpeg(FileName.data(), QualityPercent); }

	// SEE IMG, LIKE, CIMG, GOTCHA?:
	void ysxCIMG_CIMG(std::string File, std::string Title = "CIMG:") { CImg<uint8_t> Img(File.data()); CImgDisplay d(Img, Title.data()); while (!d.is_closed()) { d.wait(); } }
	void ysxCIMG_CIMG(CImg<uint8_t>& Img, std::string Title = "CIMG:") { CImgDisplay d(Img, Title.data()); while (!d.is_closed()) { d.wait(); } }

	// ############################################################################################################################################
	// ############################################################################################################################################
	// ############################################################################################################################################

	// ############## GRAPHICS:

	// EZ CREATE NEW IMAGE WITH COLORED BACKGROUND:
	CImg<uint8_t> ysxCIMG_NewImgBGColor(int Width, int Height, uint8_t C[3])
	{
		CImg<uint8_t> FilledImg(Width, Height, 1, 3, 0);
		FilledImg.draw_fill(1, 1, C, 1, 1, false);
		return(FilledImg);
	}

	// ###################################
	// ############## CLASSES ##############
	// ###################################


	/*
	#define cimg_use_png
	#include "CImg.h"
	using namespace cimg_library;

	int main(int argc, char **argv) {

	  const CImg<> bg("background.png"); // RGB image
	  const CImg<> fg("foreground.png"); // RGBA image.

	  const CImg<> fg_rgb = fg.get_shared_channels(0,2); // Only RGB part of the foreground.
	  const CImg<> fg_a = fg.get_shared_channel(3); // Only Alpha part of the foreground.

	  CImg<> result(bg);
	  result.draw_image(30,30,fg_rgb,fg_a,1,255);

	  (bg,fg,result).display();
	}
	*/

	// ############################################################################################################################################
	// ############################################################################################################################################
	// ############################################################################################################################################	
#endif // SCPARSE_
