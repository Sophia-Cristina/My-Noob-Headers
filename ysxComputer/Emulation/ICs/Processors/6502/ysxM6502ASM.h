#pragma once

#ifndef YSXM6502ASM_H
#define YSXM6502ASM_H

// #####################
// ####### By Sophia Cristina
// ####### MOS 6502 CPU stuffs for assembly.
// #####################

// #################################################
/* REFERENCES:
 [1] https://en.wikibooks.org/wiki/6502_Assembly
  [1.1]https://www.chibiakumas.com/6502/
  [1.2] https://www.masswerk.at/6502/ // Online 6502 emulator
*/
// #################################################

/*#################################################
##############  ##############*/

std::string ysxM6502_TableSineASM(uint16_t Size, uint8_t Min, uint8_t Max, float x0, float x1, float Freq = 1, float Phase = 0)
{
 std::string S = "SineTable:\n .byte ";
 float Val;
 if (x0 > x1) { float t = x0; x0 = x1; x1 = t; } float Delta = (x1 - x0) / Size;
 if (Min > Max) { T_ t = Min; Min = Max; Max = t; } uint8_t MinMaxDelta = Max - Min;
 for (uint32_t n = 0; n < Size; ++n)
 {
  Val = sin(Phase + x0 + Delta * n * Freq);
  S.push_back(std::to_string((uint8_t)(((Val + 1) * MinMaxDelta * 0.5) + Min)));
  S += ", ";
 }
 return(S);
}



/*#################################################
##############  ##############*/


// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_