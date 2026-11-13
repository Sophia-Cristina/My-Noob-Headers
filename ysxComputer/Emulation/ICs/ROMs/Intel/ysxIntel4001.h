#pragma once

#ifndef YSXINTEL4001_H
#define YSXINTEL4001_H

// #####################
// ####### By Sophia Cristina
// ####### Intel 400x emulator.
// #####################

// #################################################
/* REFERENCES:
[1] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
*/
// #################################################


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

	// ####### UTILS:

	std::string* LOG = nullptr;
	bool LOG_Mem = false;

	void LogState()
	{
		if (!LOG || !Pins || !Bus) { return; }
		*LOG += "\n### ROM 4001:\n";
		*LOG += "# PINS:\n";
		*LOG += "IO: " + std::to_string((uint16_t)(*Pins & 0x0f)) + " | CM: " + std::to_string((uint16_t)((*Pins & CM) != 0)) + " | CL: " + std::to_string((uint16_t)((*Pins & CL) != 0)) + '\n';
		*LOG += "# SYSTEM:\n";
		*LOG += "Chip: " + std::to_string((uint16_t)ChipNumber) + " | Address: " + std::to_string((uint16_t)Buf) + " | MTCFF: " + std::to_string((uint16_t)MTCFF)
		+ " | SRCFF: " + std::to_string((uint16_t)SRCFF) + " | IOP: " + std::to_string((uint16_t)IOP)+ '\n';
		*LOG += "O Reg: " + std::to_string((uint16_t)O_Regs) + " | ReadFF: " + std::to_string((uint16_t)ReadFF) + " | WriteFF: " + std::to_string((uint16_t)WriteFF) + " | I/O Input: " + std::to_string((uint16_t)IOPorts) + '\n';
		*LOG += "# CLOCK:\n";
		*LOG += "SYNC: " + std::to_string((uint16_t)Bus->SYNC) + " | CLK1: " + std::to_string((uint16_t)Bus->CLK1) + " | CLK2: " + std::to_string((uint16_t)Bus->CLK2) + " | RESET: " + std::to_string((uint16_t)Bus->RESET) + '\n';
		*LOG += "# DATA: " + std::to_string((uint16_t)(Bus->Data & 0x0f)) + '\n';
		if (LOG_Mem)
		{
			*LOG += "\n### ROM MEMORY ###\n";
			for (uint16_t n = 0; n < 256; ++n)
			{
				if (!(n % 16)) { *LOG += '\n'; } *LOG += std::to_string((uint16_t)ROM[n]) + " | ";
			}
		}

		*LOG += "\n\n";
	}
};


// #################################################

#endif
