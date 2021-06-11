#pragma once

#ifndef YSXDVGA_H
#define YSXDVGA_H

#include "DOS.H"
#include "YSXDOS/YSXDIMG.HPP"

// #####################
// ####### By Sophia Cristina
// ####### VGA utils for DOS
// #####################

// #################################################
// #####################
// #######
// REFERENCES:
// [1] https://www.youtube.com/watch?v=6C0ch7kV7B4 // Let's Code MS DOS 0x03: The VGA Card
// [2] https://stanislavs.org/helppc/idx_interrupt.html
// [3] https://stanislavs.org/helppc/int_10.html // BIOS video services
// [4] http://www.brackeen.com/vga/index.html

// Check in the folder '!UTILS' the file 'pixelVGA.c' to understand how to plot // http://www.brackeen.com/vga/source/djgpp20/pixel.c.html

// #################################################
// ############## BIOS VIDEO SERVICES ##############
// ####### INT 10,0 - Set video mode
/*
AH = 00
	AL = 00  

	   = 01  40x25 16 color text (CGA,EGA,MCGA,VGA)

	   = 02  80x25 16 shades of gray text (CGA,EGA,MCGA,VGA)

	   = 03  80x25 16 color text (CGA,EGA,MCGA,VGA)

	   = 04  320x200 4 color graphics (CGA,EGA,MCGA,VGA)

	   = 05  320x200 4 color graphics (CGA,EGA,MCGA,VGA)

	   = 06  640x200 B/W graphics (CGA,EGA,MCGA,VGA)

	   = 07  80x25 Monochrome text (MDA,HERC,EGA,VGA)

	   = 08  160x200 16 color graphics (PCjr)

	   = 09  320x200 16 color graphics (PCjr)

	   = 0A  640x200 4 color graphics (PCjr)

	   = 0B  Reserved (EGA BIOS function 11)

	   = 0C  Reserved (EGA BIOS function 11)

	   = 0D  320x200 16 color graphics (EGA,VGA)

	   = 0E  640x200 16 color graphics (EGA,VGA)

	   = 0F  640x350 Monochrome graphics (EGA,VGA)

	   = 10  640x350 16 color graphics (EGA or VGA with 128K)
		 640x350 4 color graphics (64K EGA)

	   = 11  640x480 B/W graphics (MCGA,VGA)

	   = 12  640x480 16 color graphics (VGA)

	   = 13  320x200 256 color graphics (MCGA,VGA)
			-> Structure of mode 0x13
			-  In mode 0x13, the screen dimensions are 320 pixels in width and 200 pixels in height.
			-  This is mapped 0 to 319 on the x axis and 0 to 199 on the y axis, with the origin (0,0)
			-  at the top-left corner (Figure 1). Since this is a 256-color mode, each pixel represents
			-  8 bits (28=256) or one byte, so the memory needed is 320*200 or 64,000 bytes.

	   = 8x  EGA, MCGA or VGA ignore bit 7, see below

	   = 9x  EGA, MCGA or VGA ignore bit 7, see below


	- if AL bit 7=1, prevents EGA,MCGA & VGA from clearing display
	- function updates byte at 40:49;  bit 7 of byte 40:87
	  (EGA/VGA Display Data Area) is set to the value of AL bit 7
*/

// #######

const unsigned char ModeSetVGA = 0x00; // Use this to change modes
const unsigned char VideoIntVGA = 0x10; // Video Interruptor

// #################################################
// ####### FUNÇÕES #######
// #################################################

// SET VIDEO MODE:
// https://stanislavs.org/helppc/int_10-0.html [3]


// #################################################
// ####### CLASSES #######
// #################################################

class VGAScreen
{
public:
	unsigned char Mode;
	//unsigned short int Width = 320, Heigth = 200; // No c++ do DOS, não pode se inicializar um objeto
	unsigned short int Width, Heigth;
	
	enum VideoModes
	{
		VGATextModeBWSmall = 0x00, // 40x25 B / W text (CGA, EGA, MCGA, VGA)
		VGATextMode16cSmall = 0x01, // 40x25 16 color text (CGA,EGA,MCGA,VGA)
		VGATextModeGray = 0x02, // 80x25 16 shades of gray text (CGA,EGA,MCGA,VGA)
		VGATextMode16c = 0x03, // 80x25 16 color text (CGA,EGA,MCGA,VGA) // STANDARD TEXT MODE
		VGAColors4Smalla = 0x04, // 320x200 4 color graphics (CGA,EGA,MCGA,VGA)
		VGAColors4Smallb = 0x05, // 320x200 4 color graphics (CGA,EGA,MCGA,VGA)
		VGABlackWhitea = 0x06, // 640x200 B/W graphics (CGA,EGA,MCGA,VGA)
		VGATextModeMono = 0x07, // 80x25 Monochrome text(MDA, HERC, EGA, VGA)
		VGAColors16ThinPCjr = 0x08, // 160x200 16 color graphics (PCjr)
		VGAColors16PCjr = 0x09, // 320x200 16 color graphics (PCjr)
		VGAColors4 = 0x0A, // 640x200 4 color graphics(PCjr)
		VGAReserved1 = 0x0B, // Reserved(EGA BIOS function 11)
		VGAReserved2 = 0x0C, // Reserved(EGA BIOS function 11)
		VGAColors16Small = 0x0D, // 320x200 16 color graphics(EGA, VGA)
		VGAColors16 = 0x0E, // 640x200 16 color graphics(EGA, VGA)
		VGAMonochrome = 0x0F, // 640x350 Monochrome graphics(EGA, VGA)
		VGAColors16Big = 0x10, // 640x350 16 color graphics(EGA or VGA with 128K) // 640x350 4 color graphics(64K EGA)
		VGABlackWhiteb = 0x11, // 640x480 B / W graphics(MCGA, VGA)
		VGAColors16Huge = 0x12, // 640x480 16 color graphics(VGA)
		VGAColors256 = 0x13 // 320x200 256 color graphics (MCGA,VGA)
	}; // VIDEO MODES

	

	// #################################################

	void RedefineSize()
	{
		if (Mode == 0x00 || Mode == 0x01) { Width = 40; Heigth = 25; }
		else if (Mode == 0x02 || Mode == 0x03 || Mode == 0x07) { Width = 80; Heigth = 25; }
		else if (Mode == 0x04 || Mode == 0x05 || Mode == 0x09 || Mode == 0x0D || Mode == 0x13) { Width = 320; Heigth = 200; }
		else if (Mode == 0x06 || Mode == 0x0A || Mode == 0x0E) { Width = 640; Heigth = 480; }
		else if (Mode == 0x08) { Width = 160; Heigth = 200; }
		else if (Mode == 0x0F || Mode == 0x10) { Width = 640; Heigth = 350; }
		else if (Mode == 0x11 || Mode == 0x12) { Width = 640; Heigth = 480; }
	}

	void SetMode(unsigned char NewMode) // Video uses 'void SetMode(byte Mode)' by 'typedef unsigned char byte;' [1]
	{
		if (NewMode < 19) { NewMode = 19; } if (NewMode < 0) { NewMode = 0; }
		union REGS regs;
		regs.h.ah = 0x00;
		regs.h.al = NewMode; Mode = NewMode;
		int86(VideoIntVGA, &regs, &regs);
		RedefineSize();
	}

	// #################################################
	// #################################################
	// #################################################

	VGAScreen(unsigned char InitialMode) { SetMode(InitialMode); }
	~VGAScreen()
	{
		union REGS regs;
		regs.h.ah = 0x00; // Mode Set
		regs.h.al = 0x03; // Text Mode
		int86(0x10, &regs, &regs); // Video interruptor
	}

	// #################################################
	// #################################################
	// #################################################

	void SetPixel(int x, int y, unsigned char ColorIndex) { PlotPixelVGA(x, y, Width, ColorIndex); }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_