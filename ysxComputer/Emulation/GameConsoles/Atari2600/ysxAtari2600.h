#pragma once

//#include <time.h>

#ifndef YSXATARI2600_H
#define YSXATARI2600_H

// Useful codes to mess with machine code stuffs:
#include ../../../../ysxCode/ysxOpCodeUtils.h

// Useful classes and functions to facilitate 6502 programming:
#include ../../ICs/Processors/6502/ysxM6502OPCode.h

// #####################
// ####### By Sophia Cristina
// ####### Main header for Atari 2k6 hardware, software, algos and etc.
// ####### Take in mind that the CPU is going to be on the '../../ICs/Processors' directory.
// #####################

// #################################################
/* REFERENCES:
 [1] https://cdn.hackaday.io/files/1646277043401568/Atari_2600_Programming_for_Newbies_Revised_Edition.pdf
  [1.1] https://www.randomterrain.com/atari-2600-memories-tutorial-andrew-davie-01.html // Same as above, but in HTML
  [1.2] https://www.randomterrain.com/atari-2600-memories-tutorial-andrew-davie-08.html // Screen code sample
  [1.3] https://www.randomterrain.com/atari-2600-memories-tutorial-andrew-davie-12.html // Memory and TIA initialization
  [1.4] https://www.randomterrain.com/atari-2600-memories-tutorial-andrew-davie-25.html // Time tips
 [2]https://www.randomterrain.com/atari-2600-lets-make-a-game-spiceware-00.html
 [3] https://en.wikipedia.org/wiki/Atari_2600_hardware
 [4] https://github.com/stella-emu/stella
  [4.1] https://github.com/stella-emu/stella/tree/master/src/emucore
 [5] https://en.wikibooks.org/wiki/6502_Assembly
  [5.1]https://www.chibiakumas.com/6502/
  [5.2] https://www.masswerk.at/6502/ // Online 6502 emulator
 [6] https://archive.org/details/Atari_2600_TIA_Technical_Manual
*/


/*NOTES:
* Takes 228 clocks for a scanline.
* CPU uses 3 clocks for a cycle, so, 76 machine cycles per scanline.
* 38 NOP (0xEA) instructions would sync to a scanline time.
* It is possible for 228 instructions in the 3 vertical sync scanlines (3 * 76).
* It is possible for 2812 instructions in the 37 vertical blank scanlines (37 * 76).
* It is possible for 2280 instructions in the 30 overscan scanlines (30 * 76).
*/
// #################################################

// #################################################
// ############## MAPPING ##############

struct ysxATARI2k6_Mapping
{
 uint32_t TIAEnd = 0x7F; // 0 to 127
 uint32_t RAMStart = 0x80, RAMEnd = 0xFF // 128 to 255
 // Space of 257 bytes here!
 uint32_t RIOTStart = 0x200, RIOTEnd = 0x2FF // 512 to 767
 uint32_t ROMStart = 0x1000, ROMEnd = 0x1FFF // 4096 to 8191
};

// #################################################
// ##############  ##############

// Reset TIA and RAM:
ysxCODE_CodeSet ysxATARI2k6_GetResetCodeSet()
{
 //     		       ldx #0,  lda #0, sta 0,x,  inx,        bne
 std::vector<uint8_t> Set = { 0xA2, 0, 0xA9, 0, 0x95, 0, 0xE8, 0xD0, 0xFB };
2+2+4+2+3
 return({"Reset TIA and RAM", 0, 13, Set});
}

// Start VBLANK and VSYNC:
ysxCODE_CodeSet ysxATARI2k6_GetStrtVBAndVSYNCCodeSet()
{
 //			       lda #0,   sta 1,  lda #2,   sta 0
 std::vector<uint8_t> Set = { 0xA9, 0, 0x85, 1, 0xA9, 2, 0x85, 0 };
 return({"Start VBLANK and VSYNC", 1, 10, Set});
}

// Get a bunch of WSYNC:
ysxCODE_CodeSet ysxATARI2k6_GetNumerousWSYNC(uint32_t n)
{
 ysxCODE_CodeSet WS;
 WS.Name = "WSYNC Fill";
 WS.ID = 3;
 WS.CodeCycle = n * 3;
 for (uint32_t m = 0; m < n; ++n) { WS.OpCodeSet.push_back(0x85); WS.OpCodeSet.push_back(2); }
}

/*This class can be filled with Code Sets that will be run in moments of:
Vertical sync, Vertical blank and Overscan
Objects here are separeted between: 'V' and 'OS', that means, respectively, Vertical Space and Overscan.
Vertical Space = Vertical sync + Vertical Blank;
This does not consider Horizontal Blank, since Horizontal Blank have a space that draws screen.*/
class ysxATARI2k6_BlankSpace
{
private:
 uint16_t MachineCyclesV = 0; // This should not trepass '2812 + 228 = 3040' instructions in NTSC
 uint16_t MachineCyclesOS = 0; // This should not trepass '2280' instructions in NTSC

 // This is private because if the sum of 'CodeCycles' trepass 3040, then, the programmer should not mess with it:
 std::vector<ysxCODE_CodeSet> CodesV; 
 std::vector<ysxCODE_CodeSet> CodesOS;

public:

 // #####################

 // Add the typicall VBLANK and VSYNC start, this should be one of the first things in your code, if not possible, return '0':
 uint8_t CodeSetAddVBAndVSYNC()
 {
  ysxCODE_CodeSet Add = ysxATARI2k6_GetStrtVBAndVSYNCCodeSet();
  if (MachineCyclesV + Add.CodeCycles < 3040)
  { Codes.push_back(Add); MachineCyclesV += Add.CodeCycles; return(1); } else { return(0); }
 }

 uint8_t CodeSetAddEndVSYNC()
 {
  std::vector<uint8_t> Set = { 0xA9, 0, 0x85, 0 }; // lda #0, sta 0
  ysxCODE_CodeSet Add;
  Add.Name = "EndVSYNC"; Add.ID = 2; Add.CodeCycles = 5; Add.OpCodeSet = Set;
  if (MachineCyclesV + Add.CodeCycles < 3040)
  { Codes.push_back(Add); MachineCyclesV += Add.CodeCycles; return(1); } else { return(0); }
 }

 // #####################

 // Tries to add a code set in the vector of Vertical Space Codes, if not possible, return '0':
 // Take in mind that you may have to do a 'CodeSetAddEndVSYNC' in-between VSYNC and VBLANK.
 // I could make it a template, but that would remove programmer's freedom.
 uint8_t CodeSetVAddNew(ysxCODE_CodeSet Add)
 {
  if (MachineCyclesV + Add.CodeCycles < 3040)
  { Codes.push_back(Add); MachineCyclesV += Add.CodeCycles; return(1); } else { return(0); }
 }

 // Tries to add a code set in the vector of OverScan, if not possible, return '0':
 uint8_t CodeSetOSAddNew(ysxCODE_CodeSet Add)
 {
  if (MachineCyclesOS + Add.CodeCycles < 2390)
  { Codes.push_back(Add); MachineCyclesOS += Add.CodeCycles; return(1); } else { return(0); }
 }

};

// #################################################
// #################################################
// #################################################
#endif


























