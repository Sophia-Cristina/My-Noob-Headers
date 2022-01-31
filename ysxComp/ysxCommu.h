#pragma once

#ifndef YSXCOMMU_H
#define YSXCOMMU_H

// #####################
// ####### By Sophia Cristina
// ####### Things related to communication...
// ####### Morse, braile, barcode, qr-code, protocols and etc...
// #####################

// #################################################
/* REFERENCES:
[1qr] https://en.wikipedia.org/wiki/QR_code
[2qr] https://www.thonky.com/qr-code-tutorial/data-encoding
	[2.1qr] https://www.thonky.com/qr-code-tutorial/module-placement-matrix
	[2.2qr] https://www.thonky.com/qr-code-tutorial/alignment-pattern-locations
	[2.3qr] https://www.thonky.com/qr-code-tutorial/error-correction-coding
		[2.3.1qr] https://www.thonky.com/qr-code-tutorial/error-correction-table
	[2.4qr] https://www.thonky.com/qr-code-tutorial/character-capacities
*/
// #################################################

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

class QRCode
{
public:
	const unsigned char MsnPads[2] = { 236, 17 }; // Pad if it doesn't fit the entire QR message space
	std::string MSN; // Message in BYTES to be added to QR image (you can do a little hacking to make it other modes)
	
	/* The different sizes of QR codes are called VERsions.There are *forty* versions available.
	The smallest version is version 1, and is 21 pixels by 21 pixels in size.
	Version 2 is 25 pixels by 25 pixels.
	The largest version is version 40, and is 177 by 177 pixels in size.
	Each version is 4 pixels larger than the previous version.
	USE: Version > 0 */
	unsigned char Ver;

	unsigned char* Color; // Be sure it is a memory used for 3 bytes
	unsigned char* ColorBG; // Be sure it is a memory used for 3 bytes
	CImg<unsigned char> I; // Main Image
	unsigned short W, H; // Width and Height

	// #####################

	/* FORMAT INFO:
	EC Levels and Mask Patterns.
	This was made by me and made for this class.
	FIRST BYTE:
	Model: 000 | Mask: 0 00 | EC: 00
	Ex.: EC: L | Mask: i % 2 = 0 | Model: FrameQR
	BYTE: 1011 0011 -> 101 . 1 00 . 11
					   Model Mask   EC
	ModMaskEC
	1011 0011 */
	enum FmtInf
	{
		EC_M, EC_L, EC_H, EC_Q,
		Mask0 = 4, Mask1 = 8, Mask2 = 12, Mask3 = 16, Mask4 = 20, Mask5 = 24, Mask6 = 28
	};

	unsigned char Format; // Use 'FmtInf' 'OR' or 'AND'

	/* MODE INDICATOR [1qr]:
	The general structure of a QR encoding is as a sequence of 4 bit indicators with payload length
	dependent on the indicator mode(e.g.byte encoding payload length is dependent on the first byte).
	Note:
		* Character Count Indicator depends on how many modules are in a QR code (Symbol Version).
		* ECI Assignment number Size:
			- 8 × 1 bits if ECI Assignment Bitstream starts with '0'
			- 8 × 2 bits if ECI Assignment Bitstream starts with '10'
			- 8 × 3 bits if ECI Assignment Bitstream starts with '110'
	Four-bit indicators are used to select the encoding mode and convey other information.
	*/
	enum Modes
	{
		MODNumeric = 512, // Numeric encoding (10 bits per 3 digits)   | 0001
		MODAlphanum = 1024, // Alphanumeric (11 bits per 2 characters) | 0010
		MODByte = 2048, // Byte (8 bits per character)				   | 0100
		MODKanji = 4096, // Kanji (13 bits per character)			   | 1000

		MODStrucApp = 1536, // Structured append (used to split a  | 0011
							// message across multiple QR symbols) | 
		MODECI = 3584, // Extended Channel Interpretation (select  | 0111
					   // alternate character set or encoding)	   | 
		MODFNC11st = 2560, // FNC1 in first position (see Code	   | 0101
						   // 128 for more information)			   | 
		MODFNC12nd = 4608, // FNC1 in second position			   | 1001

		MODEnd = 0 // End of message (Terminator)
	};


	/* CONFIG MESSAGE PREFIX BY FLAGS [2qr]:
	[Mode + Char_Count], which is going to be the prefix of [Message]
	Ex.: 'HELLO WORLD' (count: 11) encoded on the alphanumeric mode:
	MODE_ | COUNT INDC.
	0 010 | 0 0000 1011 = 1035
	0 0100 0000 1011 = 1035 | 1011 = 11 | 0010 = 2 | 0 0100 0000 0000 = 1024 = 2 * 512
	MODByte + Count("HELLO WORLD") = 1024 + 11 = 1035
	Or: 0010 0000 0101 1 MSN ...
	*/
	unsigned short MsnPrefix;

	// #####################

	// ###############################################################

	// GET SQUARE SIDE FOR CERTAIN VERSION:
	unsigned char VerSize(unsigned char V) { return((((V - 1) * 4) + 21)); }

	// NEW IMAGE (CHANGE COLOR MANUALLY):
	void NewImage(unsigned char Version)
	{
		Ver = Version;  unsigned char S = VerSize(Version);
		I = CImg<unsigned char>::CImg(S, S, 1, 3, 255);
		FillAll(I, ColorBG);
		W = I.width(); H = I.height();
	}

	unsigned short GetFormat(unsigned char EC, unsigned char Mask, unsigned char Model, unsigned char Mode)
	{ return(EC + Mask + Model + Mode); }

	// #####################

	// PRINT FINDER PATTERNS TO REFERENCE IMAGE [2.1qr]:
	void PrintFinders()
	{
		if (W >= 14 && H >= 14) // Make sure it fits
		{
			I.draw_line(0, 0, 6, 0, Color); I.draw_line(W - 7, 0, W - 1, 0, Color); I.draw_line(0, H - 7, 6, H - 7, Color); // TOPs
			I.draw_line(0, 6, 6, 6, Color); I.draw_line(W - 7, 6, W - 1, 6, Color); I.draw_line(0, H - 1, 6, H - 1, Color); // BOTTOMs
			I.draw_line(0, 1, 0, 5, Color); I.draw_line(W - 7, 1, W - 7, 5, Color); I.draw_line(0, H - 6, 0, H - 2, Color); // LEFTs
			I.draw_line(6, 1, 6, 5, Color); I.draw_line(W - 1, 1, W - 1, 5, Color); I.draw_line(6, H - 6, 6, H - 2, Color); // RIGHTs
			for (char c = 0; c < 3; ++c) // CENTERs
			{
				I.draw_line(2 + c, 2, 2 + c, 4, Color);
				I.draw_line(W - 5 + c, 2, W - 5 + c, 4, Color);
				I.draw_line(2 + c, H - 5, 2 + c, H - 3, Color);
			}
		}
	}

	/* TIMING PATTERNS:
	x = 6, y = 6;
	Always start and end with a dark module. Alignment patterns may overlap timing patterns
	because their light and dark modules always coincide with the light and dark modules of
	the timing patterns */

	void PrintTimingPat()
	{
		for (short n = 8; n < W - 8; ++n)
		{
			if (n % 2 == 0)	{ I.draw_point(n, 6, Color); I.draw_point(6, n, Color); }
		}
	}

	// #####################

	// ADD ALIGMENT PATTERNS [2.2qr]:
	// QR codes that are version 2 and larger are required to have alignment patterns.
	// Every aligment coordinate is in this vector, the first coord to all versions is '6':
	const std::vector<std::vector<unsigned char>> QRAligCoord = 
	{
		{ 6, 18 }, { 6, 22 }, { 6, 26 }, { 6, 30 }, { 6, 34 }, // V1 to V6
		{ 6, 22, 38 }, { 6, 24, 42 }, { 6, 26, 46 }, { 6, 28, 50 }, { 6, 30, 54 },	{ 6, 32, 58 }, { 6, 34, 62 }, // V7 to 13
		{ 6, 26, 46, 66 }, { 6, 26, 48, 70}, { 6, 26, 50, 74 }, { 6, 30, 54, 78 }, { 6, 30, 56, 82 }, { 6, 30, 58, 86 }, { 6, 34, 62, 90 }, // V14 to 20
		{ 6, 28, 50, 72, 94 }, { 6, 26, 50, 74, 98 }, { 6, 30, 54, 78, 102 }, { 6, 28, 54, 80, 106}, // V21 to 24
		{ 6, 32, 58, 84, 110 }, { 6, 30, 58, 86, 114 }, { 6, 34, 62, 90, 118}, // V25 to 27
		{ 6, 26, 50, 74, 98, 122 }, { 6, 30, 54, 78, 102, 126 }, { 6, 26, 52, 78, 104, 130 }, { 6, 30, 56, 82, 108, 134 }, // V28 to 31
		{ 6, 34, 60, 86, 112, 138 }, { 6, 30, 58, 86, 114, 142 }, { 6, 34, 62, 90, 118, 146 }, // V32 to 34
		{ 6, 35, 6, 30, 54, 78, 102, 126, 150 }, { 6, 36, 6, 24, 50, 76, 102, 128, 154 }, { 6, 37, 6, 28, 54, 80, 106, 132, 158 }, // V35 to 37
		{ 6, 38, 6, 32, 58, 84, 110, 136, 162 }, { 6, 39, 6, 26, 54, 82, 110, 138, 166 }, { 6, 40, 6, 30, 58, 86, 114, 142, 170 } // V38 to 40
	};

	// PRINT THE SPOT:
	void PrintAligSpot(unsigned short x, unsigned short y)
	{
		if (x > 1 && y > 1)
		{
			I.draw_line(x - 2, y - 2, x + 2, y - 2, Color); I.draw_line(x - 2, y + 2, x + 2, y + 2, Color); // TOP; BOTTOM
			I.draw_line(x - 2, y - 1, x - 2, y + 1, Color); I.draw_line(x + 2, y - 1, x + 2, y + 1, Color); // LEFT; RIGTH
			I.draw_point(x, y, Color);
		}
	}

	// PRINT ALIGMENT MATRIX (USE 'Version' > 1):
	void PrintAligPat()
	{
		const unsigned char L = 6, R = W - 7, B = H - 7; // Position threshold
		unsigned short x, y;
		if (Ver > 1)
		{
			unsigned char Size = QRAligCoord[Ver - 2].size(); // // index '0' is 'version 2'
			for (char i = 0; i < Size; ++i)
			{
				y = QRAligCoord[Ver - 2][i];
				for (char j = 0; j < Size; ++j)
				{
					x = QRAligCoord[Ver - 2][j];
					if ((x > L && x < R) || y > L) { if (y < B || x > L) { PrintAligSpot(x, y);	} }					
				}
			}
		}
	}

	// ###############################################################

	// MODELS [1qr]:

	enum Models
	{
		MDLStandard, // Use 'Versions'.
		MDLModel1,   // An older version of the specification. Visually similar to the widely seen model 2
					 // codes, but lacks alignment patterns. Differences are in the bottom right corner and
				     // in the midsections of the bottom and right edges are additional functional regions.
		MDLMicroQR,  // A smaller version of the QR code standard for applications where symbol size is limited.
					 // There are four different versions (sizes) of Micro QR codes: the smallest is 11x11 modules;
					 // the largest can hold 35 numeric characters.
		MDLIQR,		 // IQR Code is an alternative to existing QR codes developed by Denso Wave. IQR codes can be
					 // created in square or rectangular formations; this is intended for situations where a rectangular
					 // barcode would otherwise be more appropriate, such as cylindrical objects.
					 // IQR codes can fit the same amount of information in 30% less space. There are 61 versions of
					 // square IQR codes, and 15 versions of rectangular codes. For squares, the minimum size is 9x9 modules;
					 // rectangles have a minimum of 19x5 modules. IQR codes add error correction level S, which allows for
					 // 50% error correction. IQR Codes have not yet been given an ISO specification, and only proprietary
					 // Denso Wave products can create or read IQR codes.
		MDLSecureQR, // Secure Quick Response (SQR) code is a QR code that contains a "private data" segment after
					 // the terminator instead of the specified filler bytes "ec 11". This private data segment must
					 // be deciphered with an encryption key. This can be used to store private information and to
					 // manage company's internal information.
		MDLFrameQR,  // Frame QR is a QR code with a "canvas area" that can be flexibly used. In the center of this
					 // code is the canvas area, where graphics, letters, and more can be flexibly arranged, making
					 // it possible to lay out the code without losing the design of illustrations, photos, etc.
		MDLHCC2D,    // High Capacity Colored 2-Dimensional (HCC2D) Code.
		MDLJABCode   // JAB code (Just Another Barcode) is a color 2D matrix symbology made of colorful square modules.
					 // arranged in either square or rectangle grids.
	};				 // !!! BITWISE the 'Format' object !!!

	// ###############################################################
	// ###############################################################
	// ###############################################################

	/*  BCH QR CHECK FORMAT:
	The process for checking the encoded information is similar to long division, but uses exclusive-or
	instead of subtraction. The format code should produce a remainder of zero when it is "divided" by
	the so-called generator of the code. QR format codes use the generator 10100110111. This process is
	demonstrated for the format information in the example code (000111101011001) below:
							00011
				-----------------
	10100110111 ) 000111101011001
				   ^ 10100110111
					 ------------
					 010100110111
					^ 10100110111
					  -----------
					  00000000000
	Here is a Python function which implements this calculation:*/
	unsigned long long QRCheckFormat(unsigned long long fmt)
	{
		unsigned short g = 0x537; // = 0b10100110111 in python 2.6 +
		for (char i = 4; i > -1; --i) { if (fmt & (1 << (i + 10))) { fmt ^= g << i; } }
		return(fmt);
	}

	// ###############################################################

	// QR DECODE FORMAT:
	/* Although sophisticated algorithms for decoding BCH codes exist, they are probably overkill in this case.
	Since there are only 32 possible format codes, it's much easier to simply try each one and pick the one that
	has the smallest number of bits different from the code in question (the number of different bits is known as
	the Hamming distance). This method of finding the closest code is known as exhaustive search, and is possible
	only because we have very few codes (a code is a valid message, and here there are only 32, all other binary
	numbers aren't correct).

	(Note that Reed–Solomon is also based on this principle, but since the number of possible codewords is simply
	too big, we can't afford to do an exhaustive search, and that's why clever but complicated algorithms have been
	devised, such as Berlekamp-Massey.)
	*/
	unsigned long long QRDecodeFormat(unsigned long long fmt)
	{
		unsigned long best_fmt = -1;
		unsigned long best_dist = 15;
		for (unsigned long test_fmt = 0; test_fmt < 32; ++test_fmt)
		{
			unsigned long test_code = (test_fmt << 10) + QRCheckFormat(test_fmt << 10);
			unsigned long test_dist = HammingWeight(fmt ^ test_code);
			if (test_dist < best_dist) { best_dist = test_dist; best_fmt = test_fmt; }
			else if (test_dist == best_dist) { best_fmt = -1; }
		}
		return(best_fmt);
	}

	// ###############################################################

	// ##############################################################################################################################
	// ##############################################################################################################################
	// ##############################################################################################################################

	// GENERATE ERROR-CORRECT WORDS:
	void ErrorCrctWords()
	{

	}

	// #####################

	// PRINT THE ENTIRE CODE:
	void PrintQR(/*std::string Msn*/)
	{
		PrintFinders(); PrintTimingPat(); PrintAligPat();
	}

	// ###############################################################
	// ###############################################################
	// ###############################################################

	QRCode(unsigned char Version, unsigned char QRColor[3], unsigned char BGColor[3])
	{
		Ver = Version;
		unsigned char S = VerSize(Ver);
		Color = QRColor; ColorBG = BGColor;
		I = CImg<unsigned char>::CImg(S, S, 1, 3, 255);
		FillAll(I, ColorBG);
		W = I.width(); H = I.height();
	}

	~QRCode()
	{
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_