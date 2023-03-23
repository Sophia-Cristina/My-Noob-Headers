#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXEMUEDU_H
#define YSXEMUEDU_H

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// ####### This headers are for educational computers (or related systems)
// ####### or random experiements based on computer concepts!
// #####################

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
/* REFERENCES:
*/
// #################################################

// #################################################
/* ############## WDR PAPER COMPUTER ##############
https://en.wikipedia.org/wiki/WDR_paper_computer
"Set of five commands is small but 'Turing complete' and therefore enough to represent
all mathematical functions: incrementing ("inc") or decrementing ("dec") a register,
unconditional jump ("jmp"), conditional jump ("isz", skips next instruction if a register
is zero), and stopping program execution ("stp")".*/
class ysxEMU_WDRPaperCPU
{
public:
	uint8_t* ROM; uint8_t ROMSize = 0;
	uint8_t* RAM; // To be safer, use at least 128 bytes
	uint64_t p = 0; // RAM Pointer, make sure that it is inside RAM limits
	std::vector<uint8_t> R = std::vector<uint8_t>::vector(4); // 8-bits registers
	uint64_t PC = 0; // Counter

	uint8_t Step() { return(ROM[PC] & 255); } // Peek at byte in ROM at actual step
	uint32_t Value() // Ignore, special function
	{
		uint32_t n = 0;
		++PC; n += ROM[PC];
		++PC; n += ROM[PC] * 0x100; // 256
		++PC; n += ROM[PC] * 0x10000; // 65536
		++PC; n += ROM[PC] * 0x1000000; // 16777216
		return(n);
	}

	void STP() { }
	void INC() { ++PC; if (R[ROM[PC]] == 255) { R[ROM[PC]] = 0; } else { ++R[ROM[PC]]; } ++PC; }
	void DEC() { ++PC; if (!R[ROM[PC]]) { R[ROM[PC]] = 255; } else { --R[ROM[PC]]; } ++PC; }
	void JMP() { ++PC; PC = ROM[PC]; }
	void ISZ() { ++PC; if (!R[ROM[PC]]) { PC += 2; } ++PC; }

	/* ### BONUS ###
	Functions here are not from WDR, since it is a paper computer.
	So i decided that i could add some extra functions to render it possible
	as a real computer!*/

	// WRITE IN RAM:
	void WRM() { ++PC; RAM[p] = R[ROM[PC]]; ++PC; }
	// READ IN RAM:
	void RRM() { ++PC; R[ROM[PC]] = RAM[p]; ++PC; }
	/* SET RAM POINTER:
	p is 'ui64'; So we have to add and sub.
	R = snnn nnnn;
	s = signal, 0 = add, 1 = sub; n_m = amount to add or sub;
	Ex.: p = 0; SRM(0100 1101) -> p += 77; SRM(1100 1101) -> p -= 77; p = 0;
	*/
	void SRM()
	{
		++PC;
		if (R[ROM[PC]] & 128) { p -= R[ROM[PC]] & 127; }
		else { p += R[ROM[PC]] & 127; }
		++PC;
	}

	// FETCH IMEDIATE (LIMITED RANGE OF FOUR REGISTERS):
	void FIM(uint8_t Reg) { ++PC; R[Reg] = ROM[PC]; ++PC; }

	// Read ports:
	//void RDP(uint32_t Data)
	//{

	//}

	// #################################################
	/* Opcodes:
	STP = 000, 0x0; INC = 001, 0x1; DEC = 010, 0x2;
	JMP = 011, 0x3; ISZ = 100, 0x4; WRM = 101, 0x5;
	RRM = 110, 0x6; SRM = 111, 0x7;

	FIM = 10RR, 0x8 -> 0xB; RDP = 11PP, 0xC -> 0xF;

	XYZ = 1 0000, 0x10 // TEMP
	*/
	void OpC(uint8_t I)
	{
		if (PC >= ROMSize) { PC %= ROMSize; }
		if (I == 0) { STP(); }
		else if (I == 1) { INC(); }
		else if (I == 2) { DEC(); }
		else if (I == 3) { JMP(); }
		else if (I == 4) { ISZ(); }
		else if (I == 5) { WRM(); }
		else if (I == 6) { RRM(); }
		else if (I == 7) { SRM(); }
		else if ((I & 12) == 8) { FIM(I & 3); }
		//else if ((I & 12) == 12) { RDP(I & 3); }
	}

	// #################################################

	ysxEMU_WDRPaperCPU(uint8_t* ROM16b, uint16_t ROM_Size) { ROM = ROM16b; ROMSize = ROM_Size; }
	ysxEMU_WDRPaperCPU(uint8_t* ROM16b, uint16_t ROM_Size, uint32_t Registers) // Careful with the amount of registers!
	{
		ROM = ROM16b; ROMSize = ROM_Size;
		R = std::vector<uint8_t>::vector(Registers);
	}

	~ysxEMU_WDRPaperCPU() { }

	// #################################################

	void RST() { p = 0; PC = 0; memset(&R[0], 0, R.size()); } // Clean registers

	// Be sure of how much memory you use for ROM!!!
	void Run(uint32_t Steps)
	{
		RST(); for (uint32_t n = 0; n < Steps; ++n) { if (bLOG) { LOG += LogState(); } OpC(ROM[PC]); }
	}

	// #################################################

	std::string LOG = "LOG BEG:\nOpCodes:\nSTP = 000; INC = 001; DEC = 010;\nJMP = 011; ISZ = 100; WRM = 101;\nRRM = 110; SRM = 111;\nFIM = 10RR;\n";
	bool bLOG = false;
	std::string LogState()
	{
		std::string L = "\nRegisters:\n";
		for (size_t n = 0; n < R.size(); ++n)
		{
			L += "R[" + std::to_string(n) + "]: " + std::to_string((short)R[n]);
			if (n % 8 == 7) { L += '\n'; }
			else { L += " | "; }
		}
		L += "RAM p: " + std::to_string(p) + " | RAM[p]: " + std::to_string((short)RAM[p]) + '\n';
		L += "PC: " + std::to_string(PC) + " | ROM[PC]: " + std::to_string((short)ROM[PC]) + '\n';
		return(L);
	}

	// #####################
	// #####################
	// #####################

	/* ASSEMBLER:
	Point to the 'Beg'ginning of of a code text, and tell how many letters are in the text.
	Point to an output (can be the ROM or RAM).
	Ignore 'Sav' to NOT compile a binary file.
	!!! BE SURE TO HAVE ENOUGH ROM / RAM! IT DEALS WITH POINTERS !!!

	CODE STRUCTURE:
	* Codes uses TWO BYTES, make sure to jump to the right memory!
	* Only caps for now.
	* TO DO: Ignore first char as number, so you can enumerate your code!
	* $ = Hex; % = Bin; // NOT YET
	* LABELS AREN'T WORKING YET!

	!!! THIS ASSEMBLER IS NOT OPTIMIZED, IT MAY BUG OUT IF YOU WRITE CODE WRONGLY !!!

	; comment
	Label: ; Labels' lines begin without space and are identified by ending with ':\n'
		   ; Labels name ignores spaces, so "La bel:\n" would be registered as "Label:\n"

	INC 1  ; OpCodes lines begin with a space
		   ; spaces are ignored between instruction and variable
	INC12   ; OK!
	INC 12  ; OK!
	INC  12 ; OK!
	INC 1 2 ; NOT OK!
	IN C 12 ; NOT OK!

	FIM 1,2 ; *NO* space between comma
	*/
	

	// W.I.P
};

// #################################################
// ############## YSX TEST COMPUTER ##############

// TEST 1, GNOSISCOMP:
class ysxEMU_GnosisCPU
{
public:

	std::vector<uint8_t*> ROMs;
	std::vector<uint8_t*> RAMs;
	// #################################################

	ysxEMU_GnosisCPU(uint8_t* ROM16b, unsigned short ROMsize) { }

	~ysxEMU_GnosisCPU() { }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_