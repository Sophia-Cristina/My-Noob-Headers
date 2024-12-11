#pragma once

#ifndef YSXM6502_H
#define YSXM6502_H

// #####################
// ####### By Sophia Cristina
// ####### MOS 6502 CPU.
// #####################

// #################################################
/* REFERENCES:
 [1] https://en.wikibooks.org/wiki/6502_Assembly
  [1.1]https://www.chibiakumas.com/6502/
  [1.2] https://www.masswerk.at/6502/ // Online 6502 emulator
*/
// #################################################

/*#################################################
############## CLASSES / STRUCTS ##############*/


/*#################################################
####### M6502 #######
          ______
D0      -| INTL |- CM-RAM0
D1      -| 4004 |- CM-RAM1
D2      -| CPU  |- CM-RAM2
D3      -|      |- CM-RAM3
GND     -|      |- VDD
CLKPHS1 -|      |- CM-ROM
CLKPHS2 -|      |- TEST
SYNC    -|______|- RESET


Write useful info here.
*/

class ysxEMU_M6502
{
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_