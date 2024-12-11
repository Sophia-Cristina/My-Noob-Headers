#pragma once

//#include <time.h>

#ifndef YSXATARI2600GFX_H
#define YSXATARI2600GFX_H

// Useful codes to mess with machine code stuffs:
//#include ../../../../ysxCode/ysxOpCodeUtils.h

// Useful classes and functions to facilitate 6502 programming:
//#include ../../ICs/Processors/6502/ysxM6502OPCode.h

Those are commented because i expect that you include 'ysxAtari2600.h' that includes
both headers already.

// #####################
// ####### By Sophia Cristina
// ####### Main header for Atari 2k6 graphics program.
// #####################

// #################################################
/* REFERENCES:
 [1] https://archive.org/details/Atari_2600_TIA_Technical_Manual
*/


/*NOTES:

*/
// #################################################

// #################################################
// ############## MAPPING ##############


// #################################################
// ############## COLOR / PALLETES ##############

// CHANGE CONSTRAST FROM COLOR INSIDE A RGB POINTER:
/*void ysxATARI2k6_CLR_ChangeContrastNTSC(float Cont, uint8_t* Color)
{
	if (Cont > 1.0) { Cont -= floor(Cont); } if (Cont < 0.0) { Cont *= -1; }
	if (Cont != 1)
	{
		if (Color[0] > 127) { Color[0] = Color[0] - ((Color[0] - 127) * (1 - Cont)); }
		if (Color[0] < 127) { Color[0] = Color[0] + ((127 - Color[0]) * (1 - Cont)); }
		if (Color[1] > 127) { Color[1] = Color[1] - ((Color[1] - 127) * (1 - Cont)); }
		if (Color[1] < 127) { Color[1] = Color[1] + ((127 - Color[1]) * (1 - Cont)); }
		if (Color[2] > 127) { Color[2] = Color[2] - ((Color[2] - 127) * (1 - Cont)); }
		if (Color[2] < 127) { Color[2] = Color[2] + ((127 - Color[2]) * (1 - Cont)); }
	}
}*/

// CHANGE BRIGHTNESS:
// Brightness wrap around '0' to '1'.
uint8_t ysxATARI2k6_CLR_ChangeBrightnessNTSCPAL(float Bright, uint8_t Color)
{
	if (Bright > 1.0) { Bright -= floor(Bright); } if (Bright < 0.0) { Bright *= -1; }
	uint8_t C = (uint8_t)(Bright * 7) * 2; Color &= 0xF0;
	return(C | Color);
}

// RETURN A RGB COLOR BY HUE:
uint8_t ysxATARI2k6_CLR_LinearRGBNTSC(float x, float Bright)
{

	uint8_t ClrTable[14] = { 0x38, 0xFA, 0x2A, 0x1E, 0xDC, 0xCC, 0xBC, 0xAE, 0x9C, 0x86, 0x76, 0x68, 0x5A, 0x4A };
	if (x < 0.0) { x *= -1; } if (x > 1.0) { x -= floor(x); }
	uint8_t C = (uint8_t)(x * 13);
	C = ClrTable[C];
	C = ysxATARI2k6_CLR_ChangeBrightnessNTSCPAL(Bright, C);
	return(C);
}

// #################################################
// #################################################
// #################################################
#endif