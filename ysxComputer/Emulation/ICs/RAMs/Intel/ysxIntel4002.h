#pragma once

#ifndef YSXINTEL4002_H
#define YSXINTEL4002_H

// #####################
// ####### By Sophia Cristina
// ####### Intel 400x emulator.
// #####################

// #################################################
/* REFERENCES:
[1] https://codeabbey.github.io/heavy-data-1/msc-4-asm-manual-1973.pdf
[2] http://www.cpu-zone.com/4002.htm
*/
// #################################################


// #################################################


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


// #################################################


#endif
