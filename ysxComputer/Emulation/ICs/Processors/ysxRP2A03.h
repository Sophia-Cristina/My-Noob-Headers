#pragma once

#ifndef YSXRP2A03_H
#define YSXRP2A03_H

// #####################
// ####### By Sophia Cristina
// ####### RP2A03 processor emulator. Used on NES.
// #####################

//#include "ysxComp/NES/ysxNESAPU.h" // TAKE CARE, THE NAMES MAY CHANGE!
//#include "ysxComp/NES/ysxNESPPU.h"

// #################################################
/* REFERENCES:
[1] https://bisqwit.iki.fi/jutut/kuvat/programming_examples/nesemu1/nesemu1.cc
[2] https://www.youtube.com/watch?v=y71lli8MS8s
[3] https://en.wikipedia.org/wiki/Ricoh_2A03
[4] https://en.wikipedia.org/wiki/MOS_Technology_6502
[5] https://www.nesdev.org/wiki/2A03
[5.1] https://www.nesdev.org/wiki/CPU
[5.2] https://www.nesdev.org/wiki/CPU_pinout
[6] https://www.nesdev.org/wiki/APU // Audio Processing Unit
[7] https://github.com/OneLoneCoder/olcNES // Everything, but mainly: olc6502.h, olc6502.cpp*/
// #################################################

// ###################################################################################################################################################
// ############## MAIN CLASS ##############
/*      _____
AD0  <-|  U  |-- +5V
AD2  <-|     |-> OUT0
/RST >-|  @  |-> OUT1
A00  <-|     |-> OUT2
A01  <-|   R |-> /OE1
A02  <-| 6 P |-> /OE2
A03  <-| 0 2 |-> R/W
A04  <-| 3 A |-< /NMI
A05  <-| 8 0 |-< /IRQ
A06  <-| 3 3 |-> M2
A07  <-|   E |-< TST
A08  <-|     |-< CLK
to   <+|  @  |<> D0
A15  <-|     |<> to
GND  --|_____|<> D7
1 to 20:     :40 to 21

RP2A03:
Based on MOS6502.

Clock = 740khz;
Drive: 4KB ROM and 640B
*/

class RicohRP2A03
{
public:
    // ####### REGISTERS:
    uint8_t RB, WB;
    uint16_t PC = 0; // NES = 0xC000;
    // Accum., Index X, Y, Stack Pointer
    uint8_t A = 0, X = 0, Y = 0, S = 0;
    
    enum StatusFlags { sfC = 1, sfZ = 2, sfI = 4, sfD = 8, sfB = 16, sfU = 32, sfV = 64, sfN = 128 };
    /* Status Register
    10101010
    Negative
     Overflow
      Break
       No CPU effect, see: "The B Flag"
        Decimal: unsupported on NES
         Interrupt disable
          Zero
           Carry
    RegBit<n> for Biskwit.
    */
    uint8_t P = 0;
    
    /* ### ROM:
    Make it like my 4004!
    uint8_t* ROM;*/
    
    // #################################################

    void resetCPU()
    {
        /* Get address to set program counter to:
        lo = read(0xfffc); hi = read(0xfffd);
        Set it:*/
        PC = Bus->R((0xfffd << 8)) | Bus->R(0xfffc);

        // Reset internal registers
        A = 0; X = 0; Y = 0;
        S = 0xFD; P = 0x00 | sfU;

        // Clear internal helper variables
        //addr_rel = 0x0000;
        //addr_abs = 0x0000;
        //fetched = 0x00;

        // Reset takes time
        //cycles = 8;
    }

    void clearRAM()
    {

    }

    void clearROM() {  }

    //void reset() { resetCPU(); clearRAM(); clearROM(); } // changeAll();   
    // #################################################

    // #################################################
    // ##################### HARDWARE:
    
    // ####### BUS CONNECTIVITY:
    // Data bus that sends and receive 8-bits data from 0x0 to 0xffff.
    // It needs to be connected by means of poiting:
    DataBus<uint8_t, 0x10000> * Bus = nullptr;
    
    // Reads an 8-bit byte from the bus, located at the specified 16-bit address [7]
    //uint8_t R(uint16_t a)
    //{
        // In normal operation "read only" is set to false. This may seem odd. Some
        // devices on the bus may change state when they are read from, and this 
        // is intentional under normal circumstances. However the disassembler will
        // want to read the data at an address without changing the state of the
        // devices on the bus
        //return(Bus->R(&a, false));
    //}

    // Writes a byte to the bus at the specified address
    //void W(uint16_t a, uint8_t d) { Bus->W(&a, &d); }

    // #################################################
        // Assisstive variables to facilitate emulation
    //uint8_t  fetched = 0x00;   // Represents the working input value to the ALU
    //uint16_t temp = 0x0000; // A convenience variable used everywhere
    uint16_t addr_abs = 0x0000; // All used memory addresses end up in here
    //uint16_t addr_rel = 0x00;   // Represents absolute address following a branch
    ////uint8_t  opcode = 0x00;   // Is the instruction byte
    //uint8_t  cycles = 0;	   // Counts how many cycles the instruction has remaining
    //uint32_t clock_count = 0;	   // A global accumulation of the number of clocks

    //void incPC() { PC++; PC &= 0xfff; if (PROG & testFlag) PC &= 255; }
    /*
    Faze um BUS no lugar do ROM, fica mais realista. E pode usar outras fontes de BUS.

    */
    //uint8_t nextCode() { incPC(); if (PC < 4096) { return(ROM[PC] & 255); } return(0); }
    //uint8_t activeCode() { if (PC < 4096) { return(ROM[PC] & 255); } return(0); }
    //void setRpar(uint8_t rpar, uint8_t pset) { if (rpar < 8) { Regs[rpar] = pset & 255; } } // Set Register Pair
    //uint8_t getRpar(uint8_t rpar) { return(((Regs[rpar] << 4) & 0xf0) | ((Regs[rpar] >> 4) & 0xf)); } // Get Register Pair

    /* This function sources the data used by the instruction into
    a convenient numeric variable. Some instructions dont have to
    fetch data as the source is implied by the instruction. For example
    "INX" increments the X register. There is no additional data
    required. For all other addressing modes, the data resides at
    the location held within addr_abs, so it is read from there.
    Immediate adress mode exploits this slightly, as that has
    set addr_abs = pc + 1, so it fetches the data from the
    n ext byte for example "LDA $FF" just loads the accumulator with
    256, i.e. no far reaching memory fetch is required. "fetched"
    is a variable global to the CPU, and is set by calling this
    function. It also returns it for convenience.*/
    /*uint8_t olc6502::fetch()
    {
        if (!(lookup[opcode].addrmode == &olc6502::IMP))
        fetched = read(addr_abs);
        return fetched;
    }
    */

    // #################################################
#include "ysxComp/NES/ysxRP2A03Instr.h" // <------- INSTRUCTIONS!!!
    // #################################################
       
    // BYTE TO MACHINE INSTRUCTIONS:
    void Instrc(uint8_t H)
    {
        if (bLOG) { LOG += "Instr.: " + std::to_string((short)H) + '\n'; }
        uint8_t n = H & 0xf, m = H & 0xf0;
        /*if (H == 0) { NOP(); }
        else if (m == 0x10) { JCN(n); }
        else if (((H & 0xf1) ^ 0x21) == 1) { FIM(n >> 1); }
        else if (((H & 0xf1) ^ 0x21) == 0) { SRC(n >> 1); }
        else if (((H & 0xf1) ^ 0x31) == 1) { FIN(n >> 1); }
        else if (((H & 0xf1) ^ 0x31) == 0) { JIN(n >> 1); }
        else if (m == 0x40) { JUN(n); }*/
        if (bLOG) { LOG += LogState(); }
    }

    // #################################################

    RicohRP2A03() {} //uint8_t* ROM4096) { ROM = ROM4096; }
    ~RicohRP2A03(){}

    // #################################################
    // UTILS:
    std::string LOG = "LOG BEG:\n"; bool bLOG = false;
    std::string LogState()
    {
        std::string L;
        L += "\nA: " + std::to_string((short)A) + " | X: " + std::to_string((short)X) + " | Y: " + std::to_string((short)Y) + '\n';
        L += "S: " + std::to_string((short)S) + " | P (status): " + std::to_string((short)P) + '\n';
        //L += "RAM.addr: " + std::to_string((short)RAM.addr) + '\n';
        //L += "ph: " + std::to_string((short)RAM.ph) + " | pm: " + std::to_string((short)RAM.pm) + " | pl: " + std::to_string((short)RAM.pl);
        //L += " | RAM: " + std::to_string((short)RAM.RAM[RAM.ph][RAM.pm][RAM.pl]) + '\n';
        L += "PC: " + std::to_string((short)PC) + '\n';
        return(L);
    }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_