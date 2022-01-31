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
	unsigned char* ROM; // Please, know how much bytes you are using
	unsigned char* RAM; // Please, know how much bytes you are using. If you need more RAM, just change, it is public
	unsigned long long p; // RAM Pointer, make sure that it is inside RAM limits
	std::vector<unsigned char> R; // Registers
	unsigned long long PC = 0; // Counter

	unsigned char Step() { return(ROM[PC] & 255); } // Get Instruction
	unsigned int Value()
	{
		// Big endian, fu, my computer, my rules!
		unsigned int n;
		++PC; n += ROM[PC];
		++PC; n += ROM[PC] * 256;
		++PC; n += ROM[PC] * 65536;
		++PC; n += ROM[PC] * 16777216;
		return(n);
	}

	void STP() { ++PC; }
	void INC(unsigned int Reg) { if (R[Reg] == 255) { R[Reg] = 0; } else { ++R[Reg]; } ++PC; }
	void DEC(unsigned int Reg) { if (!R[Reg]) { R[Reg] = 255; } else { --R[Reg]; } ++PC; }
	void JMP(unsigned int Prog) { PC = Prog; ++PC; }
	void ISZ(unsigned int Reg) { if (!R[Reg]) { ++PC; } ++PC; }

	// BONUS:
	// Write in RAM:
	void WRM(unsigned int Reg) { RAM[p] = R[Reg]; ++PC; }
	// Read in RAM:
	unsigned char RRM(unsigned int Reg) { R[Reg] = RAM[p]; ++PC; }
	/* Set RAM pointer:
	p is 'long long'; So we have to add and sub.
	R = snnn nnnn;
	s = signal, 0 = add, 1 = sub; n_m = amount to add or sub;
	Ex.: p = 0; SRM(0100 1101) -> p += 77; SRM(1100 1101) -> p -= 77; p = 0;
	*/ 
	unsigned char SRM(unsigned int Reg) { if (R[Reg] & 128) { p -= R[Reg] & 127; } else { p += R[Reg] & 127; } ++PC; }

	// Fetch imediate, limited:
	// Bytes: RRRS; Data: Register >> 8, Set & 0xff;
	void FIM(unsigned int Data) { R[(Data & 0xffffff00) >> 8] = Data & 0xff; ++PC; }

	/* Instructions:
	STP = 000; INC = 001; DEC = 010;
	JMP = 011; ISZ = 100;
	WRM = 101; RRM = 110;
	SRM = 111; FIM = 1000;*/
	void Instr(unsigned char I, unsigned int N)
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

	WDRPaperCPU(unsigned char* ROM16b, unsigned short ROMsize) { ROM = ROM16b; }

	~WDRPaperCPU() { }
};

// #################################################
// ############## YSX TEST COMPUTER ##############

// TEST 1, GNOSISCOMP:
class GnsCPU
{
public:

	std::vector<unsigned char*> ROMs;
	std::vector<unsigned char*> RAMs;
	// #################################################

	GnsCPU(unsigned char* ROM16b, unsigned short ROMsize) { }

	~GnsCPU() { }
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_