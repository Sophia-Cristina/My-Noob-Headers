#pragma once

#ifndef YSXINTEL4003_H
#define YSXINTEL4003_H

// #####################
// ####### By Sophia Cristina
// ####### Intel 400x emulator.
// #####################

// #################################################
/* REFERENCES:
[1] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
*/
// #################################################


/*#################################################
############## CLASSES / STRUCTS ##############*/


/*####### 4003 #######
          ______
CP      -|      |- E
DATA_IN -| 4003 |- SO
Q0      -|      |- VDD
Q1      -|      |- Q9
VSS     -|      |- Q8
Q2      -|      |- Q7
Q3      -|      |- Q6
Q4      -|______|- Q5
10-BIT SERIAL-IN / PARALLEL-OUT SHIFT REGISTER
*/

class ysxEMU_Intel4003 : public ysxEMU_MSC_4
{
public:

	// PINS:
	enum Pinning
	{
		CP = 1, DATA_IN = 1 << 1, Q0 = 1 << 2, Q1 = 1 << 3, VSS << 4, Q2 = 1 << 5, Q3 = 1 << 6, Q4 = 1 << 7,
		Q5 = 1 << 8, Q6 = 1 << 9, Q7 = 1 << 10, Q8 = 1 << 11, Q9 = 1 << 12, VDD = 1 << 13, SO = 1 << 14, E = 1 << 15
	};
	uint16_t* Pins = nullptr;

	// SHIFT REGISTER:
	uint16_t ShiftReg = 0;

	// CLOCK STATE:
	uint8_t PrevCP = 0;

	// OUTPUT:
	void UpdateOutputs()
	{
		if (!Pins) { return; }
		*Pins &= ~(Q0 | Q1 | Q2 | Q3 | Q4 | Q5 | Q6 | Q7 | Q8 | Q9 | SO); // Clear the output pins first.
		if (*Pins & E) { *Pins |= (ShiftReg & 0x03FF) << 2; } // Parallel outputs are enabled when E is HIGH.
		if (ShiftReg & 0x0200) { *Pins |= SO; } // Serial output is independent of E.
	}

	// SYSTEM:
	void Process() override
	{
		if (!Pins) { return; }
		uint8_t CurrentCP = (*Pins & CP) != 0;
		// Shift on the rising edge of CP:
		if (CurrentCP && !PrevCP) { uint8_t Data = (*Pins & DATA_IN) != 0; ShiftReg = ((ShiftReg << 1) | Data) & 0x03FF; }
		PrevCP = CurrentCP;
		UpdateOutputs();
	}
};


// #################################################

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

256 x 8-bit ROM = 2048 bits.
4-bit bidirectional I/O port.
The ROM has a metal-option chip number from 0 to 15.
*/

class ysxEMU_Intel4001ROM : public ysxEMU_MSC_4
{
public:

	// PINS:
	enum Pinning { IO0 = 1, IO1 = 2, IO2 = 4, IO3 = 8, CM = 16, CL = 32 };
	uint8_t* Pins = nullptr;

	// SYSTEM:
	uint8_t ChipNumber = 0; // Metal-option ROM chip number: 0-15.
	uint8_t Buf = 0; // Address buffer.
	uint8_t O_Regs = 0; // Output register.
	uint8_t MTCFF = 0; // ROM mode: Memory Timing Control flip-flop.
	uint8_t SRCFF = 0; // I/O mode: SRC selection flip-flop.
	uint8_t IOP = 0; // I/O instruction register.
	uint8_t ReadFF = 0; // I/O control flip-flops.
	uint8_t WriteFF = 0;
	uint8_t ROM[256] = {}; // 256 bytes of ROM.
	uint8_t IOPorts = 0; // External I/O input state. The lower four bits represent IO0-IO3
	uint8_t Count = 0; // Timing counter.

	// ####### CHIP SELECTION:
	bool CheckFuncPins() { return( Bus && Pins && Bus->VDD && ((*Pins & CM) != 0)); }
	bool CheckChip(uint8_t Address) { return((Address & 0x0f) == (ChipNumber & 0x0f)); }

	// ####### ROM:
	uint8_t ReadROM() { return(ROM[Buf] & 0xff); }
	void LoadROM(const uint8_t* Data, uint16_t Size)
	{
		if (!Data) { return; }
		if (Size > 256) { Size = 256; }
		for (uint16_t i = 0; i < Size; ++i) { ROM[i] = Data[i]; }
	}

	// ####### I/O:
	uint8_t ReadIO() { return(IOPorts & 0x0f); }
	void WriteIO(uint8_t Data) // Reflect the output latch on the four I/O pins.
	{
		O_Regs = Data & 0x0f;
		if (Pins) { *Pins = (*Pins & 0xf0) | O_Regs; }
	}

	void ClearIO() { O_Regs = 0; if (Pins) { *Pins &= 0xf0; } }

	// ####### RESET:
	void Reset()
	{
		Buf = 0;
		MTCFF = 0;
		SRCFF = 0;
		IOP = 0;
		ReadFF = 0;
		WriteFF = 0;
		ClearIO();
		Count = 0;
	}

	// ####### CLOCK:
	void Tick() override
	{
		if (!Bus || !Pins) { return; }
 		if (!Bus->RESET) { Reset(); return; } // RESET is active-low in the logical bus model.
		if (*Pins & CL) { ClearIO(); } // CL asynchronously clears the output flip-flops.

		if (Bus->VDD)
		{
			switch (Count)
			{
				// A1: Receive low address nibble.
				case 0:
				{
					Buf = Bus->Data & 0x0f;
					break;
				}

				// A2: Receive high address nibble.
				case 2:
				{
					Buf |= (Bus->Data & 0x0f) << 4;
					break;
				}

				// A3: Decode ROM chip number.
				case 4:
				{
					MTCFF = 0;
					if (CheckFuncPins() && CheckChip(Bus->Data)) { MTCFF = 1; }
					break;
				}

				// M1: Send first instruction nibble.
				case 6:
				{
					if (MTCFF) { Bus->Data = (ReadROM() >> 4) & 0x0f; }

					break;
				}

				// M2: Send second instruction nibble.
				case 8:
				{
					if (MTCFF) { Bus->Data = ReadROM() & 0x0f; }
					MTCFF = 0;
					break;
				}

				// M2: Receive I/O instruction modifier.
				case 9:
				{
					if (CheckFuncPins() && SRCFF)
					{
						IOP = Bus->Data & 0x0f;
						ReadFF = (IOP == 0x0a);
						WriteFF = (IOP == 0x02);
					}

					break;
				}

				// X2: Receive SRC ROM chip selection.
				case 12:
				{
					if (CheckFuncPins()) { SRCFF = CheckChip(Bus->Data); }
					// RDR: Place the four input lines on the bus.
					if (SRCFF && ReadFF) { Bus->Data = ReadIO(); }
					break;
				}

				// X2: WRR data latch.
				case 13:
				{
					if (SRCFF && WriteFF) { WriteIO(Bus->Data); }
					break;
				}

				// X3: End I/O operation.
				case 14:
				{
					ReadFF = 0;
					WriteFF = 0;
					break;
				}
			}
		}

		if (LOG_On) { LogState(); }
		++Count;
		Count &= 0x0f;
	}


	// ####### CONTROL:

	void Control()
	{
	}

	void Process() override
	{
	}


	// ####### UTILS:

	std::string* LOG = nullptr;
	bool LOG_Mem = false;

	void LogState()
	{
		if (!LOG || !Pins || !Bus)
		{
			return;
		}

		*LOG += "\n### ROM 4001:\n";

		*LOG += "# PINS:\n";

		*LOG +=
		"IO: " + std::to_string((uint16_t)(*Pins & 0x0f)) +
		" | CM: " + std::to_string((uint16_t)((*Pins & CM) != 0)) +
		" | CL: " + std::to_string((uint16_t)((*Pins & CL) != 0)) +
		'\n';

		*LOG += "# SYSTEM:\n";

		*LOG +=
		"Chip: " + std::to_string((uint16_t)ChipNumber) +
		" | Address: " + std::to_string((uint16_t)Buf) +
		" | MTCFF: " + std::to_string((uint16_t)MTCFF) +
		" | SRCFF: " + std::to_string((uint16_t)SRCFF) +
		" | IOP: " + std::to_string((uint16_t)IOP) +
		'\n';

		*LOG +=
		"O Reg: " + std::to_string((uint16_t)O_Regs) +
		" | ReadFF: " + std::to_string((uint16_t)ReadFF) +
		" | WriteFF: " + std::to_string((uint16_t)WriteFF) +
		" | I/O Input: " + std::to_string((uint16_t)IOPorts) +
		'\n';

		*LOG += "# CLOCK:\n";

		*LOG +=
		"SYNC: " + std::to_string((uint16_t)Bus->SYNC) +
		" | CLK1: " + std::to_string((uint16_t)Bus->CLK1) +
		" | CLK2: " + std::to_string((uint16_t)Bus->CLK2) +
		" | RESET: " + std::to_string((uint16_t)Bus->RESET) +
		'\n';

		*LOG +=
		"# DATA: " + std::to_string((uint16_t)(Bus->Data & 0x0f)) +
		'\n';

		if (LOG_Mem)
		{
			*LOG += "\n### ROM MEMORY ###\n";

			for (uint16_t n = 0; n < 256; ++n)
			{
				if (!(n % 16))
				{
					*LOG += '\n';
				}

				*LOG +=
				std::to_string((uint16_t)ROM[n]) + " | ";
			}
		}

		*LOG += "\n\n";
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
4 registers, each with:
* 16 main-memory characters
* 4 status characters
Total: 4 * 20 * 4 = 320 bits.
*/

template <const bool Op = 0>
class ysxEMU_Intel4002RAM : public ysxEMU_MSC_4
{
public:

	// PINS:
	enum Pinning { O0 = 1, O1 = 2, O2 = 4, O3 = 8, CM = 16, P = 32 };
	uint8_t* Pins = nullptr;

	// SYSTEM:
	uint8_t Reg = 0;
	uint8_t Addr = 0;

	// SRC selection flip-flop.
	uint8_t SRCFF = 0;

	// OPA instruction register.
	uint8_t IOP = 0;

	// Indicates that an SRC high nibble was received
	// and the low nibble is still pending.
	uint8_t AddressFF = 0;

	// 4 registers * 20 characters * 4 bits.
	uint8_t RAM[4][20] = {};

	// Four-bit output port.
	uint8_t OPort = 0;

	// Timing counter.
	uint8_t Count = 0;


	// MEMORY:
	void ClearRAM() { for (uint8_t n = 0; n < 4; ++n) { for (uint8_t m = 0; m < 20; ++m) { RAM[n][m] = 0; } } }

	// RESET:
	void Reset()
	{
		Reg = 0;
		Addr = 0;
		SRCFF = 0;
		IOP = 0;
		AddressFF = 0;
		OPort = 0;
		Count = 0;
		ClearRAM();
		if (Pins) { *Pins &= 0xf0; }
	}

	/* CHIP SELECTION:
	D3:D2 select the physical 4002 chip.
	Op = 0: 4002-1
	Op = 1: 4002-2
	P0 distinguishes the two chips
	of the same metal option.*/
	bool IsSelected(uint8_t Address)
	{
		uint8_t Chip = (Address >> 2) & 0x03;
		uint8_t ChipID = (Op ? 0x02 : 0x00) | ((*Pins & P) ? 0x01 : 0x00);
		return(Chip == ChipID);
	}

	// MEMORY ACCESS:
	uint8_t ReadMain() { return(RAM[Reg][Addr] & 0x0f); }
	uint8_t ReadStatus(uint8_t Status) { return(RAM[Reg][16 + (Status & 0x03)] & 0x0f); }
	void WriteMain(uint8_t Data) { RAM[Reg][Addr] = Data & 0x0f; }
	void WriteStatus(uint8_t Status, uint8_t Data) { RAM[Reg][16 + (Status & 0x03)] = Data & 0x0f; }

	// OUTPUT PORT:
	void SetOPort(uint8_t Data) { OPort = Data & 0x0f; if (Pins) { *Pins = (*Pins & 0xf0) | OPort; } }


	// ####### INSTRUCTION DECODER:
	void ExecuteWrite(uint8_t Data)
	{
		switch (IOP & 0x0f)
		{
			case 0x0: // WRM
				WriteMain(Data);
				break;

			case 0x1: // WMP
				SetOPort(Data);
				break;

			case 0x4: // WR0
			case 0x5: // WR1
			case 0x6: // WR2
			case 0x7: // WR3
				WriteStatus(IOP & 0x03, Data);
				break;

			default:
				break;
		}
	}

	uint8_t ExecuteRead()
	{
		switch (IOP & 0x0f)
		{
			case 0x8: // SBM
			case 0x9: // RDM
			case 0xB: // ADM
				return(ReadMain());

			case 0xC: // RD0
			case 0xD: // RD1
			case 0xE: // RD2
			case 0xF: // RD3
				return(ReadStatus(IOP & 0x03));

			default:
				return(0);
		}
	}


	// ####### CLOCK:
	void Tick() override
	{
		if (!Bus || !Pins) { return; }
		if (!Bus->RESET) { Reset(); return; } // RESET is active-low in the logical bus model.

		// X2: Receive the OPA instruction nibble.
		// The CPU activates CM for the OPA phase.
		// Only a chip previously selected by SRC accepts the instruction.
		if (Count == 9) { if ((*Pins & CM) && SRCFF) { IOP = Bus->Data & 0x0f; } }

		// X2: Receive the high address nibble of SRC.
		// D3:D2 = chip number
		// D1:D0 = register number
		else if (Count == 13)
		{
			if (*Pins & CM)
			{
				AddressFF = 1;
				SRCFF = IsSelected(Bus->Data);
				if (SRCFF) { Reg = Bus->Data & 0x03; }
			}
			else if (SRCFF) { ExecuteWrite(Bus->Data); } // Write operations. The CPU supplies ACC on the data bus
		}

		// X3: Receive the main-memory character address.
		else if (Count == 15)
		{
			if (AddressFF)
			{
				if (SRCFF) { Addr = Bus->Data & 0x0f; }
				AddressFF = 0;
			}
		}

		// Read operations.
		// The RAM supplies its selected character to
		// the data bus before the CPU samples it.
		else if (Count == 12)
		{
			if (SRCFF)
			{
				switch (IOP & 0x0f)
				{
					case 0x8: // SBM
					case 0x9: // RDM
					case 0xB: // ADM
					case 0xC: // RD0
					case 0xD: // RD1
					case 0xE: // RD2
					case 0xF: // RD3
						Bus->Data = ExecuteRead();
						break;

					default:
						break;
				}
			}
		}

		++Count;
		Count &= 0x0f;
	}

	// ####### UTILS:

	std::string* LOG = nullptr;

	void LogState()
	{
		if (!LOG || !Pins || !Bus) { return; }
		*LOG += "\n### RAM 4002:\n";
		*LOG += "# PINS:\n";
		*LOG += "O: " + std::to_string((uint16_t)(*Pins & 0x0f)) + " | CM: " + std::to_string((uint16_t)((*Pins & CM) != 0)) + " | P0: " + std::to_string((uint16_t)((*Pins & P) != 0)) + '\n';
		*LOG += "# SYSTEM:\n";
		*LOG += "Reg: " + std::to_string((uint16_t)Reg) + " | Addr: " + std::to_string((uint16_t)Addr) + " | SRCFF: " + std::to_string((uint16_t)SRCFF) + " | IOP: " + std::to_string((uint16_t)IOP) + " | OPort: " + std::to_string((uint16_t)OPort) + '\n';
		*LOG += "# CLOCK:\n";
		*LOG += "SYNC: " + std::to_string((uint16_t)Bus->SYNC) + " | CLK1: " + std::to_string((uint16_t)Bus->CLK1) + " | CLK2: " + std::to_string((uint16_t)Bus->CLK2) + '\n';
		*LOG += "# DATA: " + std::to_string((uint16_t)(Bus->Data & 0x0f)) + '\n';
		*LOG += "Main: " + std::to_string((uint16_t)ReadMain()) + " | Status 0: " + std::to_string((uint16_t)ReadStatus(0)) + " | Status 1: " + std::to_string((uint16_t)ReadStatus(1)) +
		" | Status 2: " + std::to_string((uint16_t)ReadStatus(2)) + " | Status 3: " + std::to_string((uint16_t)ReadStatus(3)) + "\n\n";
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
			else if (H == 0xE0) { WRM(); }
			else if (H == 0xE1) { WMP(); }
			else if (H == 0xE2) { std::cout << "WRR to be fixed!\n"; } // WRR(); }
			else if ((H & 0xFC) == 0xE4) { WR(H & 0x3); }
			else if (H == 0xE8) { std::cout << "SBM to be fixed!\n"; } // SBM(); }
			else if (H == 0xE9) { RDM(); }
			else if (H == 0xEA) { std::cout << "RDR to be fixed!\n"; } // RDR(); }
			else if (H == 0xEB) { std::cout << "ADM to be fixed!\n"; } // ADM(); }
			else if ((H & 0xFC) == 0xEC) { RD(H & 0x3); }
			else if (H == 0xE9) { RDM(); }
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
// #################################################
// #################################################


#endif
