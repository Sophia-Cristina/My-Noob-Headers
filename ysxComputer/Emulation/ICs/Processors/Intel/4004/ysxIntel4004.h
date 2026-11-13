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
[3] https://smithsonianchips.si.edu/ice/4004thb.htm
*/
// #################################################


// #################################################


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
	enum Pinning { CM_RAM0 = 1, CM_RAM1 = 2, CM_RAM2 = 4, CM_RAM3 = 8, CM = 16, TEST = 32, RESET = 64 };
	uint8_t* Pins;

	// ####### SYSTEM:
	uint8_t Count = 0; // 4-bit timing counter

	// ACCUMULATOR:
	uint8_t ACC = 0;

	uint8_t StackP = 0;
	uint8_t Regs[8];
	uint8_t CMReg = 0;	   // Index register pair selector
	uint8_t CMRAMReg = 0;	// 3-bit command-control register
	uint8_t Temp = 0;

	// INSTRUCTION REGISTERS:
	uint8_t Instr = 0;	   // OPR: currently executing instruction
	uint8_t OPR_OPA = 0;	 // OPR / OPA data buffer

	uint8_t Cycle = 0;	   // Double Cycle flip-flop

	// CONDITION:
	uint8_t ConditionFF = 0; // Condition flip-flop (JCN / ISZ)

	// MEMORY LATCHES:
	uint8_t SRCRegPair = 0;  // SRC address latch: chip / register / character

	// ADDRESS REGISTERS:
	uint16_t PCs[4] = { 0, 0, 0, 0 }; // Four 12-bit address registers

	// CARRY:
	uint8_t C = 0;

	// SPECIAL:
	uint8_t FINFetch = 0; // FIN indirect-fetch control state


	// #################################################

	ysxEMU_Intel4004CPU() {}
	~ysxEMU_Intel4004CPU() {}

	void ResetCPU()
	{
		ACC = 0; C = 0;
		memset(PCs, 0, sizeof(PCs));
		memset(Regs, 0, sizeof(Regs));
		StackP = 0;
		CMReg = 0;
		CMRAMReg = 0;
		Temp = 0;
		Instr = 0;
		OPR_OPA = 0;
		Cycle = 0;
		ConditionFF = 0;
		SRCRegPair = 0;
		FINFetch = 0;
		Count = 0;
		if (Pins) { *Pins &= 0x60; }
		if (Bus) { Bus->SYNC = false; }
	}

	// #################################################
	// UTILS:
	std::string* LOG = nullptr; // = "LOG BEG:\n";
	void LogState()
	{
		if (LOG)
		{
			*LOG += "\n### Intel 4004 CPU:\n# Registers:\n";
			*LOG += std::to_string((uint16_t)Regs[0]) + " " + std::to_string((uint16_t)Regs[1]) + " " + std::to_string((uint16_t)Regs[2]) + " " + std::to_string((uint16_t)Regs[3]) + '\n';
			*LOG += std::to_string((uint16_t)Regs[4]) + " " + std::to_string((uint16_t)Regs[5]) + " " + std::to_string((uint16_t)Regs[6]) + " " + std::to_string((uint16_t)Regs[7]) + '\n';
			*LOG += "# Data: " + std::to_string((uint16_t)Bus->Data) + '\n';
			*LOG += "# SYNC: " + std::to_string((uint16_t)Bus->SYNC) + " | CLK1: " + std::to_string((uint16_t)Bus->CLK1) + " | CLK2: " + std::to_string((uint16_t)Bus->CLK2);
			*LOG += "# CM: " + std::to_string((uint16_t)(*Pins & CM)) + " | CM_RAM: " + std::to_string((uint16_t)*Pins & 0xf) + " | STACK PT.: " + std::to_string((uint16_t)StackP) + '\n';
			*LOG += "# ACC: " + std::to_string((uint16_t)ACC) + " | Carry: " + std::to_string((uint16_t)C) + " | T: " + std::to_string((uint16_t)*Pins & TEST) + '\n';
			*LOG += "# PCs: " + std::to_string((uint16_t)PCs[0]) + " " + std::to_string((uint16_t)PCs[1]) + " " + std::to_string((uint16_t)PCs[2]) + " " + std::to_string((uint16_t)PCs[3]) + "\n\n";
		}
	}

	// #################################################
	// ### SYSTEM:

	void Fetch()
	{
		if (Count == 0) // A1: Send lowest address nibble
		{
			Bus->SYNC = true;
			if (FINFetch) { Bus->Data = GetRegPair() & 0x0f; } // FIN: Use R0 / R1 as the indirect address.
			else { Bus->Data = PCs[0] & 0x0f; }
			if (!Cycle && !FINFetch) { Instr = 0; }
		}
		else if (Count == 2) // A2: Send middle address nibble
		{
			if (FINFetch) { Bus->Data = (GetRegPair() >> 4) & 0x0f; }
			else { Bus->Data = (PCs[0] >> 4) & 0x0f; }
		}
		else if (Count == 4) // A3: Send highest address nibble
		{
			// The page address always comes from the PC.
			Bus->Data = (PCs[0] >> 8) & 0x0f;

			// Activate ROM and selected RAM command lines.
			*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);
			*Pins |= CM | (1 << (CMRAMReg & 0x03));

			// Normal fetches advance the PC after sending A3.
			// FIN's indirect fetch does not consume another PC address.
			if (!FINFetch) { IncPC(); }
		}
		else if (Count == 6) // M1: Read OPR
		{
			*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);

			OPR_OPA = (Bus->Data & 0x0f) << 4;
		}
		else if (Count == 8) // M2: Read OPA
		{
			OPR_OPA |= Bus->Data & 0x0f;

			// Only load the instruction register during a normal fetch.
			// During a second-word fetch, Instr must retain the original OPR.
			if (!Cycle && !FINFetch)
			{
				Instr = OPR_OPA;

				// Activate command lines for I/O and RAM instructions.
				if ((Instr & 0xf0) == 0xe0)
				{
					*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);
					*Pins |= CM | (1 << (CMRAMReg & 0x03));
				}
			}
		}
	}


	void Tick() override
	{
		if (Pins && Bus)
		{
			if (Count < 9) { Fetch(); }
			else if (Count == 10) // X1: Execute instruction
			{
				*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);

				// Capture the states before executing the instruction.
				// An instruction may activate its own state during execution.
				uint8_t WasCycle = Cycle;
				uint8_t WasFINFetch = FINFetch;
				InstrDecoder(Instr);

				// The second word of a double-length instruction has now been processed.
				if (WasCycle) { Cycle = 0; }
                if (WasFINFetch) { FINFetch = 0; }
			}
			else if (Count == 12) // X2: SRC address / I/O data transfer
			{
				if ((Instr & 0xf1) == 0x21) // SRC
				{
					*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);
					*Pins |= CM | (1 << (CMRAMReg & 0x03));

					Bus->Data = (SRCRegPair >> 4) & 0x0f;
				}
				else if (Instr == 0xE0 || Instr == 0xE1 || Instr == 0xE2 || Instr == 0xE3 || (Instr >= 0xE4 && Instr <= 0xE7))
				{
					Bus->Data = ACC & 0x0f;
				}
			}
			else if (Count == 13) // X2: Second phase
			{
				if ((Instr & 0xf1) == 0x21) // SRC
				{
					Bus->Data = (SRCRegPair >> 4) & 0x0f;
				}
				else if ( Instr == 0xE0 || Instr == 0xE1 || Instr == 0xE2 || Instr == 0xE3 || (Instr >= 0xE4 && Instr <= 0xE7))
				{
					Bus->Data = ACC & 0x0f;
				}
				else if (Instr == 0xE8 || Instr == 0xE9 || Instr == 0xEA || Instr == 0xEB || (Instr >= 0xEC && Instr <= 0xEF))
				{
					uint8_t M = Bus->Data & 0x0f;

					if (Instr == 0xE8) // SBM
					{
                        uint8_t Result = (ACC & 0x0f) + ((~M) & 0x0f) + (C & 1);
						ACC = Result & 0x0f;
						C = (Result >> 4) & 1;
					}
					else if (Instr == 0xEB) // ADM
					{
						uint8_t Result = (ACC & 0x0f) + M + (C & 1);
						ACC = Result & 0x0f;
						C = (Result >> 4) & 1;
					}
					else { ACC = M; }
				}
			}
			else if (Count == 14) // X3: SRC character address
			{
				Bus->SYNC = false;
				*Pins &= ~(CM | CM_RAM0 | CM_RAM1 | CM_RAM2 | CM_RAM3);
				if ((Instr & 0xf1) == 0x21) { Bus->Data = SRCRegPair & 0x0f; }
			}
			++Count;
			Count &= 0x0f;
		}
		else
		{
			std::cerr << "ERROR: 'if (Pins && Bus)' failed / nullptr! Before running 4004, you should connect the pins and the bus!\n";
			if (LOG) { *LOG += "ERROR: 'if (Pins && Bus)' failed / nullptr! Before running 4004, you should connect the pins and the bus!\n"; }
		}
	}


	void IncPC() { PCs[0] = (PCs[0] + 1) & 0x0fff; }
	//uint8_t activeCode() { if (PCs[0] < 4096) { return(ROM[PCs[0]] & 255); } return(0); }
	void SetRegPair() { if (CMReg < 8) { Regs[CMReg] = OPR_OPA & 255; } } // Set Register Pair value
	uint8_t GetRegPair() { return(((Regs[CMReg] << 4) & 0xf0) | ((Regs[CMReg] >> 4) & 0xf)); } // Get Register Pair as one number

	// #################################################
	// ####### 4004 FUNCTIONS:
	// TEMPLATE:
	// if (reg % 2) { reg >>= 1; }
	// else { reg >>= 1; }


	// No operation:
	void NOP() {}

	// JCN - Jump Conditional
	void JCN(uint8_t cond)
	{
		bool Condition = false;

		// C2: Accumulator is zero.
		if (cond & 0x04)
		{
			Condition |= ((ACC & 0x0f) == 0);
		}

		// C3: Carry is set.
		if (cond & 0x02)
		{
			Condition |= (C & 1);
		}

		// C4: TEST input is LOW (active-low).
		if (cond & 0x01)
		{
			Condition |= ((*Pins & TEST) == 0);
		}

		// C1: Invert the complete condition.
		if (cond & 0x08)
		{
			Condition = !Condition;
		}

		if (Condition)
		{
			PCs[0] = (PCs[0] & 0xf00) | OPR_OPA;
		}
	}

	// FIM - Fetch Immediate
	void FIM(uint8_t rpar)
	{
		if (!Cycle)
		{
			CMReg = rpar & 0x07;
			Cycle = 1;
		}
		else
		{
			SetRegPair();
		}
	}

	// SRC - Send Register Control
	void SRC(uint8_t rpar)
	{
		CMReg = rpar & 0x07;
		SRCRegPair = GetRegPair();
	}

	// FIN - Fetch Indirect
	void FIN(uint8_t rpar)
	{
		if (!FINFetch) { CMReg = 0; FINFetch = 1; }
		else { CMReg = rpar & 0x07; SetRegPair(); }
	}

	// JIN - Jump Indirect
	void JIN(uint8_t rpar)
	{
		CMReg = rpar & 0x07;
		PCs[0] = (PCs[0] & 0xf00) | GetRegPair();
	}

	// JUN - Jump Unconditional
	void JUN(uint8_t addr)
	{
		if (!Cycle) { Cycle = 1; }
		else { PCs[0] = ((static_cast<uint16_t>(addr & 0x0f) << 8) | OPR_OPA) & 0x0fff; }
	}

	// JMS - Jump to Subroutine:
	void JMS(uint8_t addr)
	{
		if (!Cycle) { Cycle = 1; }
		else
		{
			// Preserve the return address.
			// PCs[1..3] represent saved return addresses in this existing emulator storage convention.
			if (StackP < 3) { ++StackP; }
			for (uint8_t i = StackP; i > 1; --i) { PCs[i] = PCs[i - 1]; }
			PCs[1] = PCs[0];
			PCs[0] = ((static_cast<uint16_t>(addr & 0x0f) << 8) | OPR_OPA) & 0x0fff;
		}
	}

	// INC - Increment Register; modern computer char is 8-bits, so this may not be loyal to the system (i don't own a 4004 to know):
	void INC(uint8_t reg)
	{
		reg &= 0x0f;
		uint8_t Index = reg >> 1;
		if (reg & 1) { Regs[Index] = (Regs[Index] & 0xf0) | ((Regs[Index] + 1) & 0x0f); } // Odd register: low nibble
		else { Regs[Index] = ((Regs[Index] + 0x10) & 0xf0) | (Regs[Index] & 0x0f); } // Even register: high nibble
	}

	// ISZ - Increment and Skip:
	void ISZ(uint8_t reg)
	{
		if (!Cycle) { Cycle = 1; }
		else
		{
			reg &= 0x0f;
			uint8_t Index = reg >> 1;
			uint8_t Value = 0;
			if (reg & 1)
			{
				Value = (Regs[Index] & 0x0f) + 1;
				Regs[Index] = (Regs[Index] & 0xf0) | (Value & 0x0f);
			}
			else
			{
				Value = ((Regs[Index] >> 4) & 0x0f) + 1;
				Regs[Index] = (Regs[Index] & 0x0f) | ((Value & 0x0f) << 4);
			}
			// Skip if the incremented nibble is zero.
			if ((Value & 0x0f) != 0) { PCs[0] = (PCs[0] & 0xf00) | OPR_OPA; }
		}
	}

	// ADD - Add Register:
	void ADD(uint8_t reg)
	{
		reg &= 0x0f;
		uint8_t Index = reg >> 1;
		uint8_t Value = (reg & 1) ? (Regs[Index] & 0x0f) : ((Regs[Index] >> 4) & 0x0f);
		uint8_t Result = (ACC & 0x0f) + Value + (C & 1);
		ACC = Result & 0x0f;
		C = (Result >> 4) & 1;
	}

	// SUB - Subtract Register:
	void SUB(uint8_t reg)
	{
		reg &= 0x0f;
		uint8_t Index = reg >> 1;
		uint8_t Value = (reg & 1) ? (Regs[Index] & 0x0f) : ((Regs[Index] >> 4) & 0x0f);
		// Two's-complement subtraction using the 4004 carry convention:
		// C = 1 means no borrow.
		uint8_t Result = (ACC & 0x0f) + ((~Value) & 0x0f) + (C & 1);
		ACC = Result & 0x0f;
		C = (Result >> 4) & 1;
	}

	// LD - Load Register:
	void LD(uint8_t reg)
	{
		reg &= 0x0f;
		uint8_t Index = reg >> 1;
		if (reg & 1) { ACC = Regs[Index] & 0x0f; }
		else { ACC = (Regs[Index] >> 4) & 0x0f; }
	}

	// XCH - Exchange Register:
	void XCH(uint8_t reg)
	{
		reg &= 0x0f;
		uint8_t Index = reg >> 1;
		Temp = ACC & 0x0f;
		if (reg & 1)
		{
			ACC = Regs[Index] & 0x0f;
			Regs[Index] = (Regs[Index] & 0xf0) | Temp;
		}
		else
		{
			ACC = (Regs[Index] >> 4) & 0x0f;
			Regs[Index] = (Regs[Index] & 0x0f) | (Temp << 4);
		}
	}

	// BBL - Branch Back and Load:
	void BBL(uint8_t data)
	{
		if (StackP > 0)
		{
			PCs[0] = PCs[1];
			for (uint8_t i = 1; i < StackP; ++i) { PCs[i] = PCs[i + 1]; }
			PCs[StackP] = 0;
			--StackP;
		}
		else
		{
			if (LOG) { *LOG += "BBL: Return stack underflow\n"; }
		}
		ACC = data & 0x0f;
	}

	// LDM - Load Immediate:
	void LDM(uint8_t data) { ACC = data & 0x0f; }

	// CLB - Clear Both:
	void CLB() { ACC = 0; C = 0; }

	// CLC - Clear Carry;
	void CLC() { C = 0; }

	// IAC - Increment Accumulator:
	void IAC()
	{
		uint8_t Result = (ACC & 0x0f) + 1;
		ACC = Result & 0x0f;
		C = (Result >> 4) & 1;
	}

	// CMC - Complement Carry:
	void CMC() { C = !(C & 1); }

	// CMA - Complement Accumulator:
	void CMA() { ACC = (~ACC) & 0x0f; }

	// RAL - Rotate Accumulator Left through Carry:
	void RAL()
	{
		uint8_t OldCarry = C & 1;
		C = (ACC >> 3) & 1;
		ACC = ((ACC << 1) | OldCarry) & 0x0f;
	}

	// RAR - Rotate Accumulator Right through Carry:
	void RAR()
	{
		uint8_t OldCarry = C & 1;
		C = ACC & 1;
		ACC = ((ACC >> 1) | (OldCarry << 3)) & 0x0f;
	}

	// TCC - Transfer Carry and Clear:
	void TCC() { ACC = C & 1; C = 0; }

	// DAC - Decrement Accumulator:
	void DAC()
	{
		uint8_t Result = (ACC & 0x0f) + 0x0f;
		ACC = Result & 0x0f;
		C = (Result >> 4) & 1;
	}

	// TCS - Transfer Carry Subtract:
	void TCS() { ACC = 9 + (C & 1); C = 0; }

	// STC - Set Carry:
	void STC() { C = 1; }

	// DAA - Decimal Adjust Accumulator:
	void DAA()
	{
		if ((ACC & 0x0f) > 9 || (C & 1))
		{
			uint8_t Result = (ACC & 0x0f) + 6;
			ACC = Result & 0x0f;
			C = ((Result >> 4) & 1) | (C & 1);
		}
	}

	// KBP - Keyboard Process:
	void KBP()
	{
		switch (ACC & 0x0f)
		{
			case 0x0: ACC = 0x0; break;
			case 0x1: ACC = 0x1; break;
			case 0x2: ACC = 0x2; break;
			case 0x4: ACC = 0x3; break;
			case 0x8: ACC = 0x4; break;
			default: ACC = 0x0f; break;
		}
	}

	// DCL - Designate Command Line:
	void DCL()
	{
		CMRAMReg = ACC & 0x07;
	}


	// #################################################

	// OPCODES:
	void InstrDecoder(uint8_t H)
	{
		if (!Bus->RESET)
		{
			if (LOG) { *LOG += "RESET = ON; Reseting...\n"; }
			ResetCPU();
		}
		else
		{
			if (LOG) { *LOG += "Instr.: " + std::to_string((uint16_t)H) + '\n'; }
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
			if (LOG) { LogState(); }
		}
	}
};


// #################################################


#endif
