#pragma once

//#include <time.h>
#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXZXSPEC_H
#define YSXZXSPEC_H

// #####################
// ####### By Sophia Cristina
// #######
// ####### Let's try to build a ZX Spectrum
// #######
// #####################

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
// REFERENCES:
// [1] https://spectrumforeveryone.com/technical/zx-spectrum-pcb-schematics-layout/
// [2] https://en.wikipedia.org/wiki/ZX_Spectrum
// [1z] http://www.zxdesign.info/goals.shtml
/* [2z] http://www.zxdesign.info/vidresearch.shtml
Video summary:
The ZX Spectrum has a display of 192 lines by 256 pixels (or 32 bytes). To the left and right of this
displaty rectangle is a border 48 pixels wide.

The number of border lines before and after the display rectangle can be calculated by knowing that the
PAL video display is based on a 625 line at 50 fields / 25 frames a second(50HZ). For television
transmissions the signal contains two interlaced frames composed of 312 lines each. Computer display does
not use interlaced frames because you get a visible vertical judder everytime the frames swap. Thus a single
frame PAL picture contains 312 lines.

It is a well documented fact that the ZX Spectrum CPU Interrupt is generated when the TV electron beam is in
vertical fly-back. Knowing this and timing the number of CPU T-States that have elapsed between the interrupt
and the electron beam scan of the first video display line reveals 64 lines have passed. The number of lines
used for the lower border are therefore 312 - 192 - 64 = 56.

A time taken for a single display row has been measured at 224 T-States by the above analysis.
Thus a complete frame takes 312 x 224 T-States = 69,888 T per frame. At 3.5MHz, 1 frame will take 0.019968 seconds.
50 frames takes 0.019968 x 50 = 0.9984 seconds. This is a little under the expected 1 second for 50 frames due to the
fact that each frame should really be 625 / 2 = 312.5 lines (the half line allows each frame to be offset from the
other when interlacing), and explains why a clock program running on a ZX Spectrum will run a little fast.*/

// #################################################

// #################################################
// ############## ZX MAIN CLASS ##############

class ZXSpectrum
{
	ZXSpectrum();
	~ZXSpectrum();

};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_