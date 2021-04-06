#pragma once

#ifndef YSXBMP_H
#define YSXBMP_H

#include <vector>

using namespace std;

// #####################################################################################################################################
// ####### STRUCTS #######

// HEADER:
typedef struct BMP_HDR {
	// File Header
	// * Tentar unsigned int se os int não funcionarem
	char bfType[2]; // The characters "BM"
	short int bfSize; // The size of the file in bytes
	short int bfReserved1; // Unused - must be zero
	short int bfReserved2; // Unused - must be zero
	short int DUMP;
	short int bfOffBits; // Offset to start of Pixel Data
	short int DUMP2;
	// Image Header:
	short int biSize; // Header Size - Must be at least 40
	short int DUMP3;
	short int biWidth; // Image width in pixels
	short int DUMP4;
	short int biHeight; // Image height in pixels
	short int DUMP5;
	short int biPlanes; // Must be 1
	short int biBitCount; // Bits per pixel - 1, 4, 8, 16, 24, or 32
	short int biCompression; // Compression type(0 = uncompressed)
	short int DUMP6;
	short int biSizeImage; // Image Size - may be zero for uncompressed images
	short int DUMP7;
	short int biXPelsPerMeter; //	Preferred resolution in pixels per meter
	short int DUMP8;
	short int biYPelsPerMeter; // Preferred resolution in pixels per meter
	short int DUMP9;
	short int biClrUsed; // Number Color Map entries that are actually used
	short int DUMP10;
	short int biClrImportant; // Number of significant colors
	short int DUMP11;
};

// #####################################################################################################################################
// ####### FUNCTIONS #######

// #####################################################################################################################################

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_