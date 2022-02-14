#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXEMUEDU_H
#define YSXEMUEDU_H

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// #######
// ####### Everything related to understanding computer science
// #######
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
set of five commands is small but 'Turing complete' and therefore enough to represent
all mathematical functions: incrementing ("inc") or decrementing ("dec") a register,
unconditional jump ("jmp"), conditional jump ("isz", skips next instruction if a register
is zero), and stopping program execution ("stp").

*/
class WDRPaperCPU
{
public:
	uint8_t* ROM;
	uint8_t* RAM;
	uint64_t p; // RAM Pointer, make sure that it is inside RAM limits
	std::vector<uint8_t> R; // Registers
	uint64_t PC = 0; // Counter

	uint8_t Step() { return(ROM[PC] & 255); } // Get Instruction
	uint32_t Value()
	{
		uint32_t n;
		++PC; n += ROM[PC];
		++PC; n += ROM[PC] * 256;
		++PC; n += ROM[PC] * 65536;
		++PC; n += ROM[PC] * 16777216;
		return(n);
	}

	void STP() { ++PC; }
	void INC(uint32_t Reg) { if (R[Reg] == 255) { R[Reg] = 0; } else { ++R[Reg]; } ++PC; }
	void DEC(uint32_t Reg) { if (!R[Reg]) { R[Reg] = 255; } else { --R[Reg]; } ++PC; }
	void JMP(uint32_t Prog) { PC = Prog; ++PC; }
	void ISZ(uint32_t Reg) { if (!R[Reg]) { ++PC; } ++PC; }

	// BONUS:
	// Write in RAM:
	void WRM(uint32_t Reg) { RAM[p] = R[Reg]; ++PC; }
	// Read in RAM:
	uint8_t RRM(uint32_t Reg) { R[Reg] = RAM[p]; ++PC; }
	/* Set RAM pointer:
	p is 'long long'; So we have to add and sub.
	R = snnn nnnn;
	s = signal, 0 = add, 1 = sub; n_m = amount to add or sub;
	Ex.: p = 0; SRM(0100 1101) -> p += 77; SRM(1100 1101) -> p -= 77; p = 0;
	*/ 
	uint8_t SRM(uint32_t Reg) { if (R[Reg] & 128) { p -= R[Reg] & 127; } else { p += R[Reg] & 127; } ++PC; }

	// Fetch imediate, limited:
	// Bytes: RRRS; Data: Register >> 8, Set & 0xff;
	void FIM(uint32_t Data) { R[(Data & 0xffffff00) >> 8] = Data & 0xff; ++PC; }

	/* Instructions:
	STP = 000; INC = 001; DEC = 010;
	JMP = 011; ISZ = 100;
	WRM = 101; RRM = 110;
	SRM = 111; FIM = 1000;*/
	void Instr(uint8_t I, uint32_t N)
	{
		if (I == 0) { STP(); }
		else if (I == 1) { INC(N); }
		else if (I == 2) { DEC(N); }
		else if (I == 3) { JMP(N); }
		else if (I == 4) { ISZ(N); }
		else if (I == 5) { WRM(N); }
		else if (I == 6) { RRM(N); }
		else if (I == 7) { SRM(N); }
		else if (I == 8) { FIM(N); }

	}

	// #################################################

	WDRPaperCPU(uint8_t* ROM16b, unsigned short ROMsize) { ROM = ROM16b; }

	~WDRPaperCPU() { }
};

// #################################################
// ############## YSX TEST COMPUTER ##############

// TEST 1, GNOSISCOMP:
class GnsCPU
{
public:

	std::vector<uint8_t*> ROMs;
	std::vector<uint8_t*> RAMs;
	// #################################################

	GnsCPU(uint8_t* ROM16b, unsigned short ROMsize) { }

	~GnsCPU() { }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_