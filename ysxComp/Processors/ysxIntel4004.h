#pragma once

#ifndef YSXINTEL4004_H
#define YSXINTEL4004_H

// #####################
// ####### By Sophia Cristina
// #######
// ####### Intel 4004 processor emulator.
// ####### The processor is not fidel emulation, check reference [1] for it.
// #######
// #####################

// #################################################
/* REFERENCES:
[1] http://e4004.szyc.org/emu/varia/4004cpu.js
 [1.1] https://jsfiddle.net/SophiaCristina/91omxuew
 [1.2] https://www.onlinegdb.com/J496vXa5U
[2] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
*/
// #################################################

// #################################################
// ############## MAIN CLASS ##############
/*
          ______                   ______                   ______
D0      -| INTL |- IO0   D0      -| INTL |- O0    D0      -| INTL |- CM-RAM0
D1      -| 4001 |- IO1   D1      -| 4002 |- O1    D1      -| 4004 |- CM-RAM1
D2      -| ROM  |- IO2   D2      -| RAM  |- O2    D2      -| CPU  |- CM-RAM2
D3      -|      |- IO3   D3      -|      |- O3    D3      -|      |- CM-RAM3
GND     -|      |- VDD   GND     -|      |- VDD   GND     -|      |- VDD
CLKPHS1 -|      |- CM    CLKPHS1 -|      |- CM    CLKPHS1 -|      |- CM-ROM
CLKPHS2 -|      |- CL    CLKPHS2 -|      |- P0    CLKPHS2 -|      |- TEST
SYNC    -|______|- RESET SYNC    -|______|- RESET SYNC    -|______|- RESET

4004:
Clock = 740khz;
 Drive: 4KB ROM and 640B
*/

struct Intel4002
{
    uint8_t RAM[16][4][16]; // Bank | CHIPS | Bytes !!! TO BE OUT OF HERE !!!
    uint8_t addr = 0, cm = 1;
    uint8_t stat[16][4][4];
    uint8_t out[16];
    uint8_t ph = 0, pm = 0, pl = 0;

    /* DECODE 'addr':
    0xAC: ph|pm|pl|
    cm 1:  2| 2|12|
       2:  6| 2|12|
       4: 10| 2|12|
       8: 14| 2|12|*/
    void ramAdrDecoder()
    {
        switch (cm)
        {
        case 1:		// RAM bank 0         2; addr >> 6
            ph = addr >> 6; // Ex.: AC = 10;10.11.00
            break;
        case 2:		// RAM bank 1
            ph = 0x4 | addr >> 6;
            break;
        case 4:		// RAM bank 2
            ph = 0x8 | addr >> 6;
            break;
        case 8:		// RAM bank 3
            ph = 0xC | addr >> 6;
            break;
        }
        //if (PROG & testFlag) { ph &= 0x1; }
        pm = (addr & 48) >> 4; // 10_10_1100 & 48 = 32; >>= 4; = 2;
        pl = addr & 0xf; // AC -> C
    }
};

class Intel4004
{
public:
    /* ############## SYSTEM REGS & MEMORY ##############
    A  | 4bits  | Accumulator
    PC | 12bits | 1 of 4 Stack Pointer Registers (Stack)
    R  | 16bits | 1 of 16 Scratchpad Registers
    C  | 1bit   | Carry
    T  | 1bit   | Test pin
    */
    
    /* ### ROM:
    divided by 16 pages of 256 bytes, totalling 4096 bytes
    !!! MAKE SURE TO HAVE 4096 BYTES !!!*/
    uint8_t* ROM;
    
    enum ePRG { stepFlag = 0, runFlag = 1, animFlag = 2, testFlag = 4 };
    /* PROG BITMAP *
    Think that it is a debugger, there are 5 bits free
           testFlag (use CT[] instead / for now)
           | ePRG
     00000 1 11
           4 21*/
    uint8_t PROG = 0;
    uint8_t sp = 0; // Stack
    uint8_t Regs[8]; // 16 4-bit index regs. R0R1... [2] P. 11

    /* ACCUMULATOR * [2] P. 49
    00 00 0000
    00 nn reg.
    ACC & 48 = OP | ACC & 15 = Registers*/
    uint8_t ACC = 0;
    
    //uint8_t ROM[4096];
    uint8_t ROMcm, ROMport;
    Intel4002 RAM;

    // Consists of three 12-bit registers used to hold addresses of program instructions.
    // Since programs are always run in ROM or program RAM, the stack registers will always refer to ROM locations
    // or program RAM locations:
    uint16_t PCs[4] = { 0, 0, 0, 0 }; // 16 bits, but only 12 bits used; T: 6B
    //uint8_t PCs[6]; // Tenta fazer com ponteiros depois

    // CT: "var C_flag, T_flag;" | Ref.: [1]
    uint8_t CT[2];
    uint8_t temp;

    // #################################################
    // ### SYSTEM:
    void incPC() { PCs[0]++; PCs[0] &= 0xfff; if (PROG & testFlag) PCs[0] &= 255; }
    /*
    Fazer um BUS no lugar do ROM, fica mais realista. E pode usar outras fontes de BUS.

    */
    uint8_t nextCode() { incPC(); if (PCs[0] < 4096) { return(ROM[PCs[0]] & 255); } return(0); }
    uint8_t activeCode() { if (PCs[0] < 4096) { return(ROM[PCs[0]] & 255); } return(0); }
    void setRpar(uint8_t rpar, uint8_t pset) { if (rpar < 8) { Regs[rpar] = pset & 255; } } // Set Register Pair
    uint8_t getRpar(uint8_t rpar) { return(((Regs[rpar] << 4) & 0xf0) | ((Regs[rpar] >> 4) & 0xf)); } // Get Register Pair

    // #################################################
    // ####### 4004 FUNCTIONS:

    // No operation:
    void NOP() { incPC(); }
    
    //JCN jump conditionally [1]
    void JCN(uint8_t cond)
    {
        uint8_t F = 0;
        if (cond & 0x8) { F = 1; } // AD & 8 = 8 -> F = 1
        temp = PCs[0] & 0xf00;
        temp |= nextCode(); incPC();
        if (cond & 0x4) { if ((!ACC) ^ F) PCs[0] = temp; } // if accu is zero
        if (cond & 0x2) { if ((CT[0]) ^ F) PCs[0] = temp; } // if carry
        if (cond & 0x1) { if ((CT[1]) ^ F) PCs[0] = temp; } // if test
    }

    // FIM Fetch Immediate
    void FIM(uint8_t rpar) { setRpar(rpar, nextCode()); incPC(); }
    
    // SRC Send Register Control
    void SRC(uint8_t rpar) { RAM.addr = getRpar(rpar); incPC(); }
    
    // FIN Fetch Indirect
    void FIN(uint8_t rpar) { setRpar(rpar, ROM[(PCs[0] & 0xf00) | getRpar(0)]); incPC(); }

    // JIN Jump Indirect
    void JIN(uint8_t rpar) { PCs[0] = (PCs[0] & 0xf00) | getRpar(rpar); if (PROG & testFlag) PCs[0] &= 255; }

    // JUN Jump Uncoditional
    void JUN(uint8_t addr) { PCs[0] = addr | nextCode(); if (PROG & testFlag) { PCs[0] &= 255; } }

    //JMS Jump to Subroutine
    void JMS(uint8_t addr)
    {
        temp = addr | nextCode();
        if (sp < 3)
        {
            sp++; for (char i = sp; i > 0; i--) { PCs[i] = PCs[i - 1]; }
            PCs[0] = temp; if (PROG & testFlag) PCs[0] &= 255;
        }
        else { incPC(); if (bLOG) { LOG += "PCs overflow\n"; } }
    }

    // ### REG 4-BIT FUNCTIONS:
    // TEMPLATE:
    // if (reg % 2) { reg >>= 1; }
    // else { reg >>= 1; }
    // reg should be 0 to 15. It will be '>>= 1' and access the correct pair.

    //INC Increment:
    void INC(uint8_t reg)
    {
        // 'Regs' are pairs: Regs[0] = R1R2;
        // reg = 13 -> reg % 2 = 1 -> Regs[6] | reg = 1 -> reg % 2 = 1 -> Regs[0]
        // Regs[reg] = AC -> 0C == 0xf -> R = D; AF -> 0F == 0xf -> R = 0
         if (reg % 2) { reg >>= 1; if ((Regs[reg] & 0xf) == 0xf) { Regs[reg] &= 0xf0; } else { ++Regs[reg]; } }
         else { reg >>= 1; if ((Regs[reg] & 0xf0) == 0xf0) { Regs[reg] &= 0xf; } else { Regs[reg] += 16; } }
        incPC();
    }

    // ISZ Increment and Skip:
    void ISZ(uint8_t reg)
    {
        temp = nextCode();
        if (reg % 2)
        {
            reg >>= 1; if ((Regs[reg] & 0xf) == 0xf) { Regs[reg] &= 0xf0; }
            else { ++Regs[reg]; }
            if (Regs[reg] & 0xf) { PCs[0] = (PCs[0] & 0xf00) | temp; }
            else incPC();
        }
        else
        {
            reg >>= 1; if ((Regs[reg] & 0xf0) == 0xf0) { Regs[reg] &= 0xf; }
            else { Regs[reg] += 16; }
            if (Regs[reg] & 0xf0) { PCs[0] = (PCs[0] & 0xf00) | temp; }
            else incPC();
        }
    }

    // ADD Add:
    void ADD(uint8_t reg)
    {
        //ACC = ACC + Regs[reg] + CT[0];
        if (reg % 2) { reg >>= 1; ACC = ACC + (Regs[reg] & 0xf) + CT[0]; }
        else { reg >>= 1; ACC = ACC + (Regs[reg] >> 4) + CT[0]; } // & 0xf if you prefer
        CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; }
        incPC();
    }

    //SUB Subtract:
    void SUB(uint8_t reg)
    {
        if (reg % 2) { reg >>= 1; ACC = ACC + (~Regs[reg] & 0xf) + (~CT[0] & 1); }
        else { reg >>= 1; ACC = ACC + (~(Regs[reg] >> 4) & 0xf) + (~CT[0] & 1); }
        CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; }
        incPC();
    }

    // LD Load:
    void LD(uint8_t reg)
    {
        if (reg % 2) { reg >>= 1; ACC = Regs[reg] & 0xf; }
        else { reg >>= 1; ACC = Regs[reg] >> 4; }
        incPC();
    }

    // XCH Exchange:
    void XCH(uint8_t reg)
    {
        temp = ACC;
        if (reg % 2) { reg >>= 1; ACC = Regs[reg] & 0xf; Regs[reg] = (Regs[reg] & 0xf0) + temp; }
        else { reg >>= 1; ACC = Regs[reg] >> 4; Regs[reg] = (Regs[reg] & 0xf) + temp * 16; }
        incPC();
    }

    // BBL Branch Back and Load:
    void BBL(uint8_t data)
    {
        if (sp > 0)
        {
            for (uint8_t i = 0; i < sp; i++) { PCs[i] = PCs[i + 1]; }
            PCs[sp] = 0;
            sp--; ACC = data;
        }
        if (bLOG) { LOG += "! PCs error !\n"; }
        incPC();
    }

    // LDM Load Immediate
    void LDM(uint8_t data) { ACC = data; incPC(); }

    // ### MEMORY FUNCTIONS:

    // WRM Write Main Memory
    void WRM() { RAM.ramAdrDecoder(); RAM.RAM[RAM.ph][RAM.pm][RAM.pl] = ACC; incPC(); }

    // WMP Write RAM Port
    void WMP() { RAM.ramAdrDecoder(); RAM.out[RAM.ph] = ACC; if (PROG & testFlag) { CT[1] = RAM.out[0] & 1; } incPC(); }
    
    // WRR Write ROM Port
    void WRR() { ROMport = ACC; incPC(); }
    
    // WRx Write Status Char
    void WR(uint8_t status) { RAM.ramAdrDecoder(); RAM.stat[RAM.ph][RAM.pm][status] = ACC; incPC(); }
    
    // SBM Subtract Main Memory
    void SBM()
    {
        RAM.ramAdrDecoder();
        ACC = ACC + ((~RAM.RAM[RAM.ph][RAM.pm][RAM.pl]) & 0xf) + (~CT[0] & 1);
        CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; }
        incPC();
    }

    // RDM Read Main Memory
    void RDM() { RAM.ramAdrDecoder(); ACC = RAM.RAM[RAM.ph][RAM.pm][RAM.pl]; incPC(); }

    // RDR Read ROM Port
    void RDR() { if (PROG & testFlag) { ROMport = RAM.out[1]; } ACC = ROMport; incPC(); }

    // ADM Add Main Memory
    void ADM()
    {
        RAM.ramAdrDecoder();
        ACC = ACC + RAM.RAM[RAM.ph][RAM.pm][RAM.pl] + CT[0];
        CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; }
        incPC();
    }

    // RDx Read Status Char
    void RD(uint8_t status) { RAM.ramAdrDecoder(); ACC = RAM.stat[RAM.ph][RAM.pm][status]; incPC(); }

    // CLB Clear Both
    void CLB() { ACC = 0; CT[0] = 0; incPC(); }
    
    // CLC Clear Carry
    void CLC() { CT[0] = 0; incPC(); }

    // IAC Increment Accumulator
    void IAC() { ++ACC; CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; } incPC(); }

    // CMC Complement Carry
    void CMC() { CT[0] = (CT[0] == 1) ? 0 : 1; incPC(); }

    // CMA Complement
    void CMA() { ACC = (~ACC) & 0xf; incPC(); }

    // RAL Rotate Left
    void RAL() { ACC = (ACC << 1) | CT[0]; CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; } incPC(); }

    // RAR Rotate Right
    void RAR()
    {
        temp = ACC & 1;
        ACC = (ACC >> 1) | (CT[0] << 3);
        CT[0] = temp; incPC();
    }

    // TCC Transfer Carry and Clear
    void TCC() { ACC = CT[0]; CT[0] = 0; incPC(); }

    // DAC Decrement Accumulator
    void DAC() { ACC += 0xf; CT[0] = 0; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; } incPC(); }

    // TCS Transfer Carry Subtract
    void TCS() { ACC = 9 + CT[0]; CT[0] = 0; incPC(); }

    // STC Set Carry
    void STC() { CT[0] = 1; incPC(); }

    // DAA Decimal Adjust Accumulator
    void DAA() { if (ACC > 9 || CT[0] == 1) ACC += 6; if (ACC & 0xf0) { ACC &= 0xf; CT[0] = 1; } incPC(); }

    // KBP Keybord Process:
    void KBP()
    {
        switch (ACC)
        {
        case 0:
            ACC = 0;
            break;
        case 1:
            ACC = 1;
            break;
        case 2:
            ACC = 2;
            break;
        case 4:
            ACC = 3;
            break;
        case 8:
            ACC = 4;
            break;
        default:
            ACC = 15;
            break;
        }
        incPC();
    }

    // DCL Designate Command Line
    void DCL()
    {
        switch (ACC & 0x7)
        {
        case 0:
            RAM.cm = 1; break;
        case 1:
            RAM.cm = 2; break;
        case 2:
            RAM.cm = 4; break;
        case 3:
            RAM.cm = 3; break;
        case 4:
            RAM.cm = 8; break;
        case 5:
            RAM.cm = 10; break;
        case 6:
            RAM.cm = 12; break;
        case 7:
            RAM.cm = 14; break;
        }
        incPC();
    }

    // #################################################

    // BYTE TO MACHINE INSTRUCTIONS:
    void Instrc(uint8_t H)
    {
        if (bLOG) { LOG += "Instr.: " + std::to_string((short)H) + '\n'; }
        uint8_t n = H & 0xf, m = H & 0xf0;
        if (H == 0) { NOP(); }
        else if (m == 0x10) { JCN(n); }
        else if (((H & 0xf1) ^ 0x21) == 1) { FIM(n >> 1); }
        else if (((H & 0xf1) ^ 0x21) == 0) { SRC(n >> 1); }
        else if (((H & 0xf1) ^ 0x31) == 1) { FIN(n >> 1); }
        else if (((H & 0xf1) ^ 0x31) == 0) { JIN(n >> 1); }
        else if (m == 0x40) { JUN(n); }
        else if (m == 0x50) { JMS(n); }
        else if (m == 0x60) { INC(n); }
        else if (m == 0x70) { ISZ(n); }
        else if (m == 0x80) { ADD(n); }
        else if (m == 0x90) { SUB(n); }
        else if (m == 0xA0) { LD(n); }
        else if (m == 0xB0) { XCH(n); }
        else if (m == 0xC0) { BBL(n); }
        else if (m == 0xD0) { LDM(n); }
        else if (H == 0xE0) { WRM(); }
        else if (H == 0xE1) { WMP(); }
        else if (H == 0xE2) { WRR(); }
        else if ((H & 0xFC) == 0xE4) { WR(n - 4); }
        else if ((H & 0xFC) == 0xEC) { RD(n - 4); }
        else if (H == 0xE8) { SBM(); }
        else if (H == 0xE9) { RDM(); }
        else if (H == 0xEA) { RDR(); }
        else if (H == 0xEB) { ADM(); }
        else if (H == 0xF0) { CLB(); }
        else if (H == 0xF1) { CLC(); }
        else if (H == 0xF2) { IAC(); }
        else if (H == 0xF3) { CMC(); }
        else if (H == 0xF4) { CMA(); }
        else if (H == 0xF5) { RAL(); }
        else if (H == 0xF6) { RAR(); }
        else if (H == 0xF7) { TCC(); }
        else if (H == 0xF8) { DAC(); }
        else if (H == 0xF9) { TCS(); }
        else if (H == 0xFA) { STC(); }
        else if (H == 0xFB) { DAA(); }
        else if (H == 0xFC) { KBP(); }
        else if (H == 0xFD) { DCL(); }
        if (bLOG) { LOG += LogState(); }
    }

    // #################################################

    Intel4004(uint8_t* ROM4096) { ROM = ROM4096; }

	~Intel4004(){}

    void resetCPU()
    {
        ACC = CT[0] = CT[1] = 0;
        memset(PCs, 0, sizeof(short) * 4); // PCs must always be declared with 4 "size", else, change it here
        sp = 0;
        memset(Regs, 0, 8); // Regs have 8 bytes as size
        RAM.cm = 1; RAM.addr = 0;
        ROMcm = 0;
        PROG = 0;
        //cpuCycles = 0;
    }

    void clearRAM()
    {
        uint8_t i, j, k;
        for (i = 0; i < 16; i++) { for (j = 0; j < 4; j++) { for (k = 0; k < 16; k++) { RAM.RAM[i][j][k] = 0; } } }
        for (i = 0; i < 16; i++) { for (j = 0; j < 4; j++) { for (k = 0; k < 4; k++) { RAM.stat[i][j][k] = 0; } } }
        for (i = 0; i < 16; i++) { RAM.out[i] = 0; }
    }

    void clearROM() { for (uint8_t i = 0; i < 4096; ++i) { ROM[i] = 0; } ROMport = 0; }

    void reset() { resetCPU(); clearRAM(); clearROM(); } // changeAll();

    // #################################################
    // UTILS:
    std::string LOG = "LOG BEG:\n"; bool bLOG = false;
    std::string LogState()
    {
        std::string L = "\nRegisters:\n";
        L += std::to_string((short)Regs[0]) + " " + std::to_string((short)Regs[1]) + " " + std::to_string((short)Regs[2]) + " " + std::to_string((short)Regs[3]) + '\n';
        L += std::to_string((short)Regs[4]) + " " + std::to_string((short)Regs[5]) + " " + std::to_string((short)Regs[6]) + " " + std::to_string((short)Regs[7]) + '\n';
        L += "ACC: " + std::to_string((short)ACC) + " | Carry: " + std::to_string((short)CT[0]) + " | T: " + std::to_string((short)CT[1]) + '\n';
        L += "RAM.addr: " + std::to_string((short)RAM.addr) + " | cm: " + std::to_string((short)RAM.cm) + " | sp: " + std::to_string((short)sp) + '\n';
        L += "ph: " + std::to_string((short)RAM.ph) + " | pm: " + std::to_string((short)RAM.pm) + " | pl: " + std::to_string((short)RAM.pl);
        L += " | RAM: " + std::to_string((short)RAM.RAM[RAM.ph][RAM.pm][RAM.pl]) + '\n';
        L += "PCs: " + std::to_string((short)PCs[0]) + " " + std::to_string((short)PCs[1]) + " " + std::to_string((short)PCs[2]) + " " + std::to_string((short)PCs[3]) + '\n';
        return(L);
    }

};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_