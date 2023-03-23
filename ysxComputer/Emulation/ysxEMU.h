#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXEMU_H
#define YSXEMU_H

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// #######
// ####### Everything related to emulating some kind of computer
// ####### or electronic device.
// #####################

#include "ysxData/ysxData.h"
#include "ysxEMULowLevel.h"

// ICS, RAMs, ROMs, AND ALIKE:
#include "ysxEMUICs.h"
//#include "ysxComputer/GameConsoles/NES/ysxNESAPU.h"
//#include "ysxComputer/GameConsoles/NES/ysxNESPPU.h"

// PROCESSORS:
#include "ysxComputer/Emulation/ICs/Processors/Intel4004/ysxIntel4004.h"
//#include "ysxComputer/Emulation/ICs/Processors/ysxRP2A03.h"


// OLDSCHOOL EMU:
#include "ysxComputer/Emulation/Computers/ZX Spectrum/ysxZXSpec.h"

// MISC:
#include "ysxEMUHist.h" // Historical or basic computers
#include "ysxEMUEdu.h" // Educational stuffs
#include "ysxEMUEsoLang.h" // Esolang and their machines

// MY STUFFS:
#include "ysxComputer/Emulation/MyFantasies/4K4S/ysx4K4S.h" // Fantasy console with Intel 4004

// #################################################
/* REFERENCES:
 [1]
*/

// #################################################
// ############## ABC ##############



// #################################################
// #################################################
// #################################################

#endif // SCPARSE_
