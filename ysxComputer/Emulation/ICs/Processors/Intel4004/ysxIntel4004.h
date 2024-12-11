#pragma once

#ifndef YSXINTEL4004_H
#define YSXINTEL4004_H

// #####################
// ####### By Sophia Cristina
// ####### Intel 400x emulator.
// #####################

// #################################################
/* REFERENCES:
[1] http://e4004.szyc.org/emu/varia/4004cpu.js
 [1.1] https://jsfiddle.net/SophiaCristina/91omxuew
 [1.2] https://www.onlinegdb.com/J496vXa5U
[2] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
[3] http://www.cpu-zone.com/4002.htm
[4] https://smithsonianchips.si.edu/ice/4004thb.htm
*/
// #################################################

/*#################################################
ATTENTION: These are not accurate emulations of MSC-4!!!
There are schemes online, but i'm not willing to read these schemes.
So i'm going to emulate just enough that it looks like is working equaly externaly.
#################################################*/
 
/*Doc is low resolution, seems like the CLK works by these steps:
A1,A2,A3,M1,M2,X1,X2,X3;*/

/*#################################################
############## CLASSES / STRUCTS ##############*/

struct ysxEMU_MSC_4_Bus
{   
    uint8_t Data;
    uint8_t CLK1;
    uint8_t CLK2;
    uint8_t SYNC;
    uint8_t RESET;
    uint8_t VDD;
};

class ysxEMU_MSC_4 : public ysxEMU_Component<uint8_t>
{
public:
    ysxEMU_MSC_4_Bus* Bus = nullptr;
    virtual void Tick() {}
};


/*####### 4003 #######

#################################################*/

/*####### 4001 #######
          ______
D0      -| INTL |- IO0
D1      -| 4001 |- IO1
D2      -| ROM  |- IO2
D3      -|      |- IO3
GND     -|      |- VDD
CLKPHS1 -|      |- CM
CLKPHS2 -|      |- CL
SYNC    -|______|- RESET

2048 bits (256B);
Addresses are received from CPU on three time periods following SYNC, and select 1 out of 16 ROM's;
Information is tranfered from the ROM to the data bus lines;
!!! This class is going to 'ICs/ROMs' directory !!!
*/
class ysxEMU_Intel4001ROM : public ysxEMU_MSC_4
{
public:
    // ####### PINS:
    enum Pinning { IO0 = 1, IO1 = 2, IO2 = 4, IO3 = 8, CM = 16, CL = 32 };
    uint8_t* Pins;
    
    //ysxEMU_DataBus<uint8_t, 4>* DataBus;

    // ####### SYSTEM:
    uint8_t Buf = 0;
    uint8_t O_Regs; // Output register, use CL to clean.
    uint8_t FF = 0;
    uint8_t ROM[256];
    uint8_t IOPorts; // &= 0xF = I; &= 0xF0 = O;
    uint8_t Count = 0;

    bool CheckFuncPins() { return(Bus->VDD && Bus->SYNC && *Pins & CM); }

    void Tick() override
    {
        if (Bus)
        {
            if (CheckFuncPins())
            {
                if (Count == 1) // Send the the 1st ROM opcode nibble
                {
                    Buf = (Bus->Data & 0xf) << 4;
                }
                else if (Count == 2) // Send the the 2nd ROM opcode nibble
                {
                    Buf |= Bus->Data & 0xf;
                    Bus->Data = Buf;
                }
            }
        }
        if (LOG_On) { LogState(); }
        ++Count;
        Count &= 7;
    }

    // Check out later what activates Control and add function to "Process"():
    void Control() { }

    void Process() override { }

    // ####### UTILS:
    std::string* LOG;
    bool LOG_On = false;
    bool LOG_PlotMemASCII = false;

    void LogState()
    {
	if (LOG)
	{
            *LOG += "\n### ROM 4001:\n";
            *LOG += "# PINS:\nIO: " + std::to_string((short)(*Pins & 0xf)) + " | CM: " + std::to_string((short)(*Pins & CM)) + " | CL: " + std::to_string((short)(*Pins & CL) ) + '\n';
            *LOG += "# SYSTEM:\nReg: " + std::to_string((short)O_Regs) + " | FF: " + std::to_string((short)FF) + " | O Port: " + std::to_string((short)IOPorts) + '\n';
            *LOG += "# CLOCK:\nSYNC: " + std::to_string((short)Bus->SYNC) + " | CLK1: " + std::to_string((short)Bus->CLK1) + " | CLK2: " + std::to_string((short)Bus->CLK2) + '\n';
            *LOG += "# DATA '" + std::to_string((short)Bus->Data) + "':\n";
            *LOG += "BUF: " + std::to_string((short)Buf) + ":\n";
            if (LOG_PlotMemASCII) { for (uint16_t n = 0; n < 256; ++n) { if (!(n % 16)) { *LOG += '\n'; } *LOG += ROM[n]; } }
            *LOG += "\n\n";
	}
    }
};

/*####### 4002 #######
          ______
D0      -| INTL |- O0
D1      -| 4002 |- O1
D2      -| RAM  |- O2
D3      -|      |- O3
GND     -|      |- VDD
CLKPHS1 -|      |- CM
CLKPHS2 -|      |- P0
SYNC    -|______|- RESET
4 registers, each with 16 4-bit chars and 4 4-bit status;
TOTAL: 4*10 = 40 bytes;
You can have 4 banks with 4 chips each:
40b*4*4 = 640b;

The chip was available in two different metal options 4002-1 and 4002-2 this was to make it possible to extend
the chip selection. So chips could be connected to the 4004 CPU without any external chip selection logic [3].
Use 'Op = 0' for 4002-1;

Chip|Op|D3|D2| at X2
   0| 0| 0| 0|
   1| 0| 0| 1|
   2| 1| 1| 0|
   3| 1| 1| 1|

!!! This class is going to 'ICs/RAMs' directory !!!
*/
template <const bool Op = 0>
class ysxEMU_Intel4002RAM : public ysxEMU_MSC_4
{
public:
    // ####### PINS:
    enum Pinning { O0 = 1, O1 = 2, O2 = 4, O3 = 8, CM = 16, P = 32 };
    uint8_t* Pins;

    // ####### SYSTEM:
    uint8_t Reg = 0, Addr = 0;
    uint8_t FF = 0;
    uint8_t RAM[4][20]; // Registers, 16 4-bit chars and 4 4-bit status
    uint8_t OPort = 0;
    uint8_t Count = 0;
    
    void Tick() override
    {
        if (Bus)
        {
            //if (Count == 3)
            //{
            //}
            if (Count == 4 && Bus->SYNC && *Pins & CM)
            {
                //RAM[Reg][Addr] = Bus->Data & 0xf;
            }
            else if (Count == 5 && Bus->SYNC && *Pins & CM)
            {
                Reg = Bus->Data & 3;
            }
            else if (Count == 6 && Bus->SYNC && *Pins & CM) // Send the the 2nd ROM opcode nibble
            {
                Addr = Bus->Data & 0xf;
            }
        }
        ++Count;
        Count &= 7;
    }

    void Process() override { }

    void clearRAM() { for (uint8_t n = 0; n < 4; ++n) { for (uint8_t m = 0; m < 20; ++m) { RAM[n][m] = 0; } } }

    // ####### UTILS:
    std::string* LOG;
    bool LOG_On = false;
    void LogState()
    {
	if (LOG)
	{
            *LOG += "\n### RAM 4002:\n";
            *LOG += "# PINS:\nO: " + std::to_string((short)*Pins & 0xf) + " | CM: " + std::to_string((short)*CM) + " | P: " + std::to_string((short)*P) + '\n';
            *LOG += "# SYSTEM:\nReg: " + std::to_string((short)Reg) + " | FF: " + std::to_string((short)FF) + " | O Port: " + std::to_string((short)OPort) + '\n';
            *LOG += "# CLOCK:\nSYNC: " + std::to_string((short)Bus->SYNC) + " | CLK1: " + std::to_string((short)Bus->CLK1) + " | CLK2: " + std::to_string((short)Bus->CLK2) + '\n';
            *LOG += "# DATA '" + std::to_string((short)Bus->Data) + "':\n";
            *LOG += "UI4: " + std::to_string((short)RAM[Reg][Bus->Data > 19 ? Bus->Data % 20 : Bus->Data]) + "';\n\n";
	}
    }
};

/*#################################################
####### 4004 #######
          ______
D0      -| INTL |- CM-RAM0
D1      -| 4004 |- CM-RAM1
D2      -| CPU  |- CM-RAM2
D3      -|      |- CM-RAM3
GND     -|      |- VDD
CLKPHS1 -|      |- CM-ROM
CLKPHS2 -|      |- TEST
SYNC    -|______|- RESET

Clock = 740khz;
Drive: 4KB ROM and 640B;
Instruction cycle time: minimum 10.8us (8 clock cycles per machine cycle);
46250 instructions per second;

Adding two 8-digit decimal numbers (32 bits each, assuming 4-bit BCD digits) takes a claimed 850us, or
approximately 79 machine cycles (632 clock ticks), for an average of just under 10 cycles (80 ticks) per digit
pair and an operating speed of 1176 × 8-digit additions per second;

Separate program and data storage. Contrary to Harvard architecture designs, however, which use separate buses,
the 4004, with its need to keep pin count down, uses a single multiplexed 4-bit bus for transferring:
* 12-bit addresses,
* 8-bit instructions,
* 4-bit data words;

Able to directly address 5120 bits (equivalent to 640 bytes) of RAM, stored as 1280 4-bit "characters" and
organised into groups representing 1024 "data" and 256 "status" characters (512 and 128 bytes);

Able to directly address 32768 bits of ROM, equivalent to and arranged as 4096 8-bit bytes;

Instruction set contained 46 instructions (of which 41 were 8 bits wide and 5 were 16 bits wide);

Register set contains 16 registers of 4 bits each;

Internal subroutine stack, 3 levels deep;

CONSIDER 'BusSize' as the amount of components connected to the data bus, but not the amount of lines in the data bus.
'17' is the standard ROM bus, because 1 is the CPU and 16 are the ROMs IC;
The same for the RAM bus;
*/
class ysxEMU_Intel4004CPU : public ysxEMU_MSC_4
{
public:
    // ####### PINS:
    // ####### PINS:
    enum Pinning { CM_RAM0 = 1, CM_RAM1 = 2, CM_RAM2 = 4, CM_RAM3 = 8, CM = 16, TEST = 32, RESET = 64 };
    uint8_t* Pins;
    // ####### SYSTEM:
    uint8_t Count = 0;

    /* ACCUMULATOR * [2] P. 49
    00 00 0000
    00 nn reg.
    ACC & 48 = OP | ACC & 15 = Registers*/
    uint8_t ACC = 0;
    
    uint8_t Temp = 0;
    uint8_t Instr = 0; // Instruction
    uint8_t OPR_OPA = 0; // 0xf0 = OPR; oxf = OPA;
    uint8_t BufAddr = 0; // CM Logic buffer
    uint8_t Cycle = 0; // If an opcode needs two cycles, it activates this

    uint8_t sp = 0; // Stack pointer
    uint8_t Regs[8]; // 16 4-bit index regs. R0R1... [2] P. 11
    uint8_t RegSel = 0; // Register Selector
    
    // Consists of three 12-bit registers used to hold addresses of program instructions.
    // Since programs are always run in ROM or program RAM, the stack registers will always refer to ROM locations
    // or program RAM locations:
    uint16_t PCs[4] = { 0, 0, 0, 0 }; // 16 bits, but only 12 bits used; T: 6B

    // Carry flag:
    uint8_t C = 0;

    // ####### SPECIAL:
    uint8_t FINFetch = 0; // When using opcode FIN, it may need to send another address to the ROM
    
    // #################################################

    ysxEMU_Intel4004CPU() { }
    ~ysxEMU_Intel4004CPU() {}

    void ResetCPU()
    {
        ACC = 0; C = 0;
        memset(PCs, 0, sizeof(uint16_t) * 4); // PCs must always be declared with 4 "size", else, change it here
        sp = 0;
        memset(Regs, 0, 8); // Regs have 8 bytes as size
        *Pins &= 0x60;
        Count = 0; Temp = 0; Instr = 0;
    }
    
    // #################################################
    // UTILS:
    std::string* LOG; // = "LOG BEG:\n";
    bool LOG_On = false;
    void LogState()
    {
        if (LOG)
	{
            *LOG += "\n### Intel 4004 CPU:\n# Registers:\n";
            *LOG += std::to_string((short)Regs[0]) + " " + std::to_string((short)Regs[1]) + " " + std::to_string((short)Regs[2]) + " " + std::to_string((short)Regs[3]) + '\n';
            *LOG += std::to_string((short)Regs[4]) + " " + std::to_string((short)Regs[5]) + " " + std::to_string((short)Regs[6]) + " " + std::to_string((short)Regs[7]) + '\n';
            *LOG += "# Data: " + std::to_string((short)Bus->Data) + '\n';
            *LOG += "# SYNC: " + std::to_string((short)Bus->SYNC) + " | CLK1: " + std::to_string((short)Bus->CLK1) + " | CLK2: " + std::to_string((short)Bus->CLK2);
            *LOG += "# CM: " + std::to_string((short)(*Pins & CM)) + " | CM_RAM: " + std::to_string((short)*Pins & 0xf) + " | STACK PT.: " + std::to_string((short)sp) + '\n';
            *LOG += "# ACC: " + std::to_string((short)ACC) + " | Carry: " + std::to_string((short)C) + " | T: " + std::to_string((short)*Pins & TEST) + '\n';        
            *LOG += "# PCs: " + std::to_string((short)PCs[0]) + " " + std::to_string((short)PCs[1]) + " " + std::to_string((short)PCs[2]) + " " + std::to_string((short)PCs[3]) + "\n\n";
	}
    }

    // #################################################
    // ### SYSTEM:
    
    // This function called in a loop makes the CPU run the instructions:
    //uint8_t nextCode() { IncPC(); PCs[0] &= 0xfff; { return(ROM[PCs[0]] & 255); } return(0); }

    void Tick() override
    {
        //if () // Flipflop
        if (Count == 0)      // A1: Turn SYNC low; Select ROM IC
        {
            Bus->SYNC = true;
            Bus->Data = (PCs[0] >> 8) & 0xf;
            Instr = 0;
        }
        else if (Count == 1) // A2: Send the 1st ROM address nibble
        {
            if (FINFetch && Cycle) { Bus->Data = (GetRegPair() >> 4) & 0xf; }
            else
            {
                Bus->Data = (PCs[0] >> 4) & 0xf;
            }
            
        }
        else if (Count == 2) // A3: Send the 2nd ROM address nibble
        {
            if (FINFetch && Cycle) { Bus->Data = GetRegPair() & 0xf; }
            else
            {
                Bus->Data = PCs[0] & 0xf;
            }
        }
        else if (Count == 3) // M1: Read instruction
        {
            OPR_OPA = Bus->Data & 0xf0;
        }
        else if (Count == 4) // M2: Send instruction
        {
            OPR_OPA |= Bus->Data & 0xf;
            if (!Cycle) { Instr = OPR_OPA; }
            InstrDecoder(Instr);
        }
        else if (Count == 5) // X1: Select RAM
        {
            // CM Pins:
            *Pins = (Regs[BufAddr] >> 6) | (*Pins & 0xf0);

            // RAM Register:
            Bus->Data = (Regs[BufAddr] >> 4) & 3;
        }
        else if (Count == 6) // X2: Use RAM
        {
            Bus->Data = Regs[BufAddr] & 0xf;
        }
        else if (Count == 7) // X3
        {
            if (Cycle) { Cycle = 0; }
            Bus->SYNC = false;
        }
        ++Count; // One day to be substituted by flip-flop counters
        Count &= 7;
    }

    void IncPC() { ++PCs[0]; PCs[0] &= 0xfff; if (*Pins & TEST) PCs[0] &= 255; }
    //uint8_t activeCode() { if (PCs[0] < 4096) { return(ROM[PCs[0]] & 255); } return(0); }
    void SetRegPair() { if (RegSel < 8) { Regs[RegSel] = OPR_OPA & 255; } } // Set Register Pair value
    uint8_t GetRegPair() { return(((Regs[RegSel] << 4) & 0xf0) | ((Regs[RegSel] >> 4) & 0xf)); } // Get Register Pair as one number

    // #################################################
    // ####### 4004 FUNCTIONS:
    // TEMPLATE:
    // if (reg % 2) { reg >>= 1; }
    // else { reg >>= 1; }

    // No operation:
    void NOP() { IncPC(); }
    
    //JCN jump conditionally [1]
    void JCN(uint8_t cond)
    {
        uint8_t F = 0;
        if (cond & 0x8) { F = 1; } // AD & 8 = 8 -> F = 1
        Temp = PCs[0] & 0xf00;
        //Temp |= nextCode(); IncPC();
        if (cond & 0x4) { if ((!ACC) ^ F) PCs[0] = Temp; } // if accu is zero
        if (cond & 0x2) { if (C) PCs[0] = Temp; } // if carry
        if (cond & 0x1) { if (*Pins & TEST) PCs[0] = Temp; } // if test
    }

    // FIM Fetch Immediate
    void FIM(uint8_t rpar) { if (!Cycle) { RegSel = rpar; Cycle = 1; } else { SetRegPair(); IncPC(); } }
    
    // SRC Send Register Control
    void SRC(uint8_t rpar) { RegSel = rpar; BufAddr = GetRegPair(); IncPC(); }
        
    // FIN Fetch Indirect
    // Not sure if this uses 'Temp' reg, i'll do it anyway.
    //FORMER: void FIN(uint8_t rpar) { SetRegPair(rpar, ROM[(PCs[0] & 0xf00) | GetRegPair(0)]); IncPC(); }
    void FIN(uint8_t rpar) { if (!Cycle) { RegSel = 0; FINFetch = 1; Cycle = 1; } else { RegSel = rpar; SetRegPair(); IncPC(); } }

    // JIN Jump Indirect
    void JIN(uint8_t rpar) { RegSel = rpar; PCs[0] = (PCs[0] & 0xf00) | GetRegPair(); if (*Pins & TEST) PCs[0] &= 255; }

    // JUN Jump Uncoditional
    //FORMER: void JUN(uint8_t addr) { PCs[0] = addr | nextCode(); if (*Pins & TEST) { PCs[0] &= 255; } }
    void JUN(uint8_t addr) { if (!Cycle) { Cycle = 1; } else { PCs[0] = addr | OPR_OPA; } if (*Pins & TEST) { PCs[0] &= 255; } }

    //JMS Jump to Subroutine
    //FORMER: void JMS(uint8_t addr)
    //{ Temp = addr | nextCode(); if (sp < 3) { sp++; for (char i = sp; i > 0; i--) { PCs[i] = PCs[i - 1]; } PCs[0] = Temp; if (*Pins & TEST) PCs[0] &= 255; } }
    //  else { IncPC(); if (LOG_On && LOG) { *LOG += "PCs overflow\n"; } }
    void JMS(uint8_t addr)
    {
        if (!Cycle) { Cycle = 1; }
        else
        {
            if (sp < 3)
            {
                sp++; for (char i = sp; i > 0; i--) { PCs[i] = PCs[i - 1]; }
                PCs[0] = addr | OPR_OPA; if (*Pins & TEST) PCs[0] &= 255;
            }
            else { IncPC(); if (LOG_On && LOG) { *LOG += "Stack overflow\n"; } }
        } 
    }

    //INC Increment:
    void INC(uint8_t reg)
    {
         if (reg % 2) { reg >>= 1; if ((Regs[reg] & 0xf) == 0xf) { Regs[reg] &= 0xf0; } else { ++Regs[reg]; } }
         else { reg >>= 1; if ((Regs[reg] & 0xf0) == 0xf0) { Regs[reg] &= 0xf; } else { Regs[reg] += 16; } }
        IncPC();
    }

    // ISZ Increment and Skip:
    void ISZ(uint8_t reg)
    {
        if (!Cycle)
        {
            Cycle = 1;
        }
        else
        {
            Temp = OPR_OPA;
            if (reg % 2)
            {
                reg >>= 1; if ((Regs[reg] & 0xf) == 0xf) { Regs[reg] &= 0xf0; }
                else { ++Regs[reg]; }
                if (Regs[reg] & 0xf) { PCs[0] = (PCs[0] & 0xf00) | Temp; }
                else IncPC();
            }
            else
            {
                reg >>= 1; if ((Regs[reg] & 0xf0) == 0xf0) { Regs[reg] &= 0xf; }
                else { Regs[reg] += 16; }
                if (Regs[reg] & 0xf0) { PCs[0] = (PCs[0] & 0xf00) | Temp; }
                else IncPC();
            }
        }
    }

    // ADD Add:
    void ADD(uint8_t reg)
    {
        //ACC = ACC + Regs[reg] + C & 1;
        if (reg % 2) { reg >>= 1; ACC = ACC + (Regs[reg] & 0xf) + (C & 1); }
        else { reg >>= 1; ACC = ACC + (Regs[reg] >> 4) + (C & 1); } // & 0xf if you prefer
        C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; }
        IncPC();
    }

    //SUB Subtract:
    void SUB(uint8_t reg)
    {
        if (reg % 2) { reg >>= 1; ACC = ACC + (~Regs[reg] & 0xf) + (~(C & 1) & 1); }
        else { reg >>= 1; ACC = ACC + (~(Regs[reg] >> 4) & 0xf) + (~(C & 1) & 1); }
        C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; }
        IncPC();
    }

    // LD Load:
    void LD(uint8_t reg)
    {
        if (reg % 2) { reg >>= 1; ACC = Regs[reg] & 0xf; }
        else { reg >>= 1; ACC = Regs[reg] >> 4; }
        IncPC();
    }

    // XCH Exchange:
    void XCH(uint8_t reg)
    {
        Temp = ACC;
        if (reg % 2) { reg >>= 1; ACC = Regs[reg] & 0xf; Regs[reg] = (Regs[reg] & 0xf0) + Temp; }
        else { reg >>= 1; ACC = Regs[reg] >> 4; Regs[reg] = (Regs[reg] & 0xf) + Temp * 16; }
        IncPC();
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
        if (LOG_On && LOG) { *LOG += "! PCs error !\n"; }
        IncPC();
    }

    // LDM Load Immediate
    void LDM(uint8_t data) { ACC = data; IncPC(); }

    // ### MEMORY FUNCTIONS:

    // WRM Write Main Memory
    // FORMER: void WRM() { RAM.ramAdrDecoder(addr); RAM.RAM[RAM.pm][RAM.pl] = ACC; IncPC(); }
    /*
    void WRM() { Bus->Data = ACC; IncPC(); }

    // WMP Write RAM Port
    // FORMER: void WMP() { RAM.ramAdrDecoder(addr); RAM.O[RAM.ph] = ACC; if (*Pins & TEST) { if (!(RAM.O[0] & 1)) { *Pins |= TEST; } } IncPC(); }
    void WMP() { RAM.O[RAM.ph] = ACC; if (*Pins & TEST) { if (!(RAM.O[0] & 1)) { *Pins |= TEST; } } IncPC(); }
    
    // WRR Write ROM Port
    void WRR() { ROMport = ACC; IncPC(); }
    
    // WRx Write Status Char
    // FORMER: void WR(uint8_t status) { RAM.ramAdrDecoder(addr); RAM.RAM[RAM.ph][status + 16] = ACC; IncPC(); }
    void WR(uint8_t status) { RAM.ramAdrDecoder(addr); RAM.RAM[RAM.ph][status + 16] = ACC; IncPC(); }
    
    // SBM Subtract Main Memory
    void SBM()
    {
        RAM.ramAdrDecoder(addr);
        ACC = ACC + ((~RAM.RAM[RAM.pm][RAM.pl]) & 0xf) + (~(C & 1) & 1);
        C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; }
        IncPC();
    }

    // RDM Read Main Memory
    void RDM() { RAM.ramAdrDecoder(addr); ACC = RAM.RAM[RAM.ph][RAM.pm][RAM.pl]; IncPC(); }

    // RDR Read ROM Port
    void RDR() { if (*Pins & TEST) { ROMport = RAM.O[1]; } ACC = ROMport; IncPC(); }

    // ADM Add Main Memory
    void ADM()
    {
        RAM.ramAdrDecoder(addr);
        ACC = ACC + RAM.RAM[RAM.pm][RAM.pl] + (C & 1);
        C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; }
        IncPC();
    }

    // RDx Read Status Char
    void RD(uint8_t status) { RAM.ramAdrDecoder(addr); ACC = RAM.RAM[RAM.ph][status + 16]; IncPC(); }
    */

    // CLB Clear Both
    void CLB() { ACC = 0; C = 0; IncPC(); }
    
    // CLC Clear Carry
    void CLC() { C = 0; IncPC(); }

    // IAC Increment Accumulator
    void IAC() { ++ACC; C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; } IncPC(); }

    // CMC Complement Carry
    void CMC() { C = (C & 1) ? 0 : 1; IncPC(); }

    // CMA Complement
    void CMA() { ACC = (~ACC) & 0xf; IncPC(); }

    // RAL Rotate Left
    void RAL() { ACC = (ACC << 1) | (C & 1); C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; } IncPC(); }

    // RAR Rotate Right
    void RAR()
    {
        Temp = ACC & 1;
        ACC = (ACC >> 1) | ((C & 1) << 3);
        C = 0 + Temp; IncPC();
    }

    // TCC Transfer Carry and Clear
    void TCC() { ACC = C & 1; C = 0; IncPC(); }

    // DAC Decrement Accumulator
    void DAC() { ACC += 0xf; C = 0; if (ACC & 0xf0) { ACC &= 0xf; C = 1; } IncPC(); }

    // TCS Transfer Carry Subtract
    void TCS() { ACC = 9 + (C & 1); C = 0; IncPC(); }

    // STC Set Carry
    void STC() { C = 1; IncPC(); }

    // DAA Decimal Adjust Accumulator
    void DAA() { if (ACC > 9 || C & 1) { ACC += 6; } if (ACC & 0xf0) { ACC &= 0xf; C = 1; } IncPC(); }

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
        IncPC();
    }

    // DCL Designate Command Line
    void DCL()
    {
        switch (ACC & 0x7)
        {
        case 0:
            *Pins = *Pins & 0xf1; break;
        case 1:
            *Pins = *Pins & 0xf2; break;
        case 2:
            *Pins = *Pins & 0xf4; break;
        case 3:
            *Pins = *Pins & 0xf3; break;
        case 4:
            *Pins = *Pins & 0xf8; break;
        case 5:
            *Pins = *Pins & 0xfa; break;
        case 6:
            *Pins = *Pins & 0xfc; break;
        case 7:
            *Pins = *Pins & 0xfe; break;
        }
        IncPC();
    }

    // #################################################

    // OPCODES:
    void InstrDecoder(uint8_t H)
    {
        if (Bus->RESET)
        {
            *LOG += "RESET = ON; Reseting...\n";
            ResetCPU();
        }
        else
        {
            if (LOG_On && LOG) { *LOG += "Instr.: " + std::to_string((short)H) + '\n'; }
            if (H == 0) { NOP(); }
            else if ((H & 0xf0) == 0x10) { JCN((H & 0xf)); }
            else if (((H & 0xf1) ^ 0x21) == 1) { FIM((H & 0xf) >> 1); }
            else if (((H & 0xf1) ^ 0x21) == 0) { SRC((H & 0xf) >> 1); }
            else if (((H & 0xf1) ^ 0x31) == 1) { FIN((H & 0xf) >> 1); }
            else if (((H & 0xf1) ^ 0x31) == 0) { JIN((H & 0xf) >> 1); }
            else if ((H & 0xf0) == 0x40) { JUN((H & 0xf)); }
            else if ((H & 0xf0) == 0x50) { JMS((H & 0xf)); }
            else if ((H & 0xf0) == 0x60) { INC((H & 0xf)); }
            else if ((H & 0xf0) == 0x70) { ISZ((H & 0xf)); }
            else if ((H & 0xf0) == 0x80) { ADD((H & 0xf)); }
            else if ((H & 0xf0) == 0x90) { SUB((H & 0xf)); }
            else if ((H & 0xf0) == 0xA0) { LD((H & 0xf)); }
            else if ((H & 0xf0) == 0xB0) { XCH((H & 0xf)); }
            else if ((H & 0xf0) == 0xC0) { BBL((H & 0xf)); }
            else if ((H & 0xf0) == 0xD0) { LDM((H & 0xf)); }
            else if (H == 0xE0) { std::cout << "WRM to be fixed!\n"; } // WRM(); }
            else if (H == 0xE1) { std::cout << "WMP to be fixed!\n"; } // WMP(); }
            else if (H == 0xE2) { std::cout << "WRR to be fixed!\n"; } // WRR(); }
            else if ((H & 0xFC) == 0xE4) { std::cout << "WR to be fixed!\n"; } // WR((H & 0xf) - 4); }
            else if ((H & 0xFC) == 0xEC) { std::cout << "RD to be fixed!\n"; } // RD((H & 0xf) - 4); }
            else if (H == 0xE8) { std::cout << "SBM to be fixed!\n"; } // SBM(); }
            else if (H == 0xE9) { std::cout << "RDM to be fixed!\n"; } // RDM(); }
            else if (H == 0xEA) { std::cout << "RDR to be fixed!\n"; } // RDR(); }
            else if (H == 0xEB) { std::cout << "ADM to be fixed!\n"; } // ADM(); }
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
            if (LOG_On && LOG) { LogState(); }
        }
    }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_