#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces. Assuming you have not included it by yourself!

#ifndef YSXEMUESOLANG_H
#define YSXEMUESOLANG_H

// #####################
// ####### By Sophia Cristina
// ####### Well... Esolang...
// #####################

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
/* REFERENCES:
[1] https://en.wikipedia.org/wiki/One-instruction_set_computer
*/
// #################################################

// #################################################
/* ############## FLIP JUMP 8 BITS ############## [1]
!!! NOT TESTED !!!
https://esolangs.org/wiki/FlipJump
*/
class ysxEMUESO_FlipJumpCPU8b
{
private:
	uint32_t ROMSize = 0;
	uint8_t ip = 0, f = 0, j = 0;
public:
	uint8_t* mem; // Take care with memory size!

	// #######
	ysxEMUESO_FlipJumpCPU8b(uint8_t* ROM, uint32_t ROM_Size) { mem = ROM; ROMSize = ROM_Size; }
	~ysxEMUESO_FlipJumpCPU8b() {}
	// #######

	std::string Run(size_t Steps)
	{
		if (ROMSize)
		{
			for (size_t n = 0; n < Steps; ++n)
			{
				f = mem[ip / 8]; j = mem[ip / 8 + 1];
				if (ip % 8) { return("BAD_ALIGNMENT"); }
				if (f >= ip && f < ip + 16) { return("SELF_FLIP"); }
				//if (...) { } // handle IO  (will be explained next).
				if (ip == j) { return("SUCCESS_FINISH"); }
				mem[f / 8] ^= 1 << (f % 8); // Flip
				ip = j; // Jump
				if (bLOG) { LOG += LogState(n); }
			}
		}
		return("NO_MEMORY"); // Please, point to a valid memory!
	}

	// #######

	std::string LOG = "LOG BEG:\n";
	bool bLOG = false;
	std::string LogState(size_t n)
	{
		std::string L = "\nRegisters:\n";
		L += "ip: " + std::to_string((short)ip) + " | f: " + std::to_string((short)f) + " | j: " + std::to_string((short)j);
		L += "\nSTEP: " + std::to_string(n) + '\n';
		return(L);
	}
};

// #################################################
/* ############## TOGA COMPUTER ############## [1]
!!! NOT TESTED !!!
https://esolangs.org/wiki/TOGA_computer
*/
class ysxEMUESO_TOGAComputer
{
private:
	const uint8_t PC_SIZE = 12; //#define PC_SIZE 12
	const uint8_t W_SIZE = 10; //#define W_SIZE 10

	uint32_t pc = 0;
	Point<uint32_t>* pm; //Point<uint16_t> pm[1 << PC_SIZE] = { {0,0},{1,0},{1,0} }; // x = a, y = b
	bool dm[1024]; //bool dm[1 << W_SIZE];
public:

	// #######
	// USE CORRECT RAM SIZE, WHICH IS 4096 POINTS, TAKE THAT IN MIND!
	ysxEMUESO_TOGAComputer(Point<uint32_t>* RAM4096) { pm = RAM4096; pm[0] = { 0, 0 }; pm[1] = { 1, 0 }; pm[2] = { 1, 0 }; }
	~ysxEMUESO_TOGAComputer() {}
	// #######

	int Run(size_t Steps)
	{
		if (pm)
		{			
			pc = 0;
			for (size_t n = 0; n < Steps; ++n)
			{
				pc &= (1 << PC_SIZE) - 1;
				pm[pc].x &= (1 << W_SIZE) - 1;
				pm[pc].y &= (1 << PC_SIZE) - 1;
				dm[pm[pc].x] = !dm[pm[pc].x];
				if (dm[pm[pc].x]) pc = pm[pc].y; else pc++;
				if (bLOG) { LOG += LogState(n); }
			}
			return(0);
		}
		return(-1); // Please, point to a valid memory!
	}

	// #######

	std::string LOG = "LOG BEG:\n";
	bool bLOG = false;
	std::string LogState(size_t n)
	{
		std::string L = "\nRegisters:\n";
		L += "pc: " + std::to_string(pc) + " | pm[pc].x: " + std::to_string(pm[pc].x) + " | pm[pc].y: " + std::to_string(pm[pc].y);
		L += "\ndm[pm[pc].x]: " + std::to_string(dm[pm[pc].x]) + "\nSTEP: " + std::to_string(n) + '\n';
		return(L);
	}
};

// #################################################
/* ############## Brainfuck compiler ##############
https://
*/
class ysxEMUESO_BrainFuckCompiler
{

};

// #################################################
// MY MACHINES:
// #################################################

// #################################################
/* ############## LRONETWO FLIP MACHINE V1 ##############
My machine is based on this concept:
MEM is a circular buffer;
Each two bits consist of the parameters for an instruction;
There is only one instruction;
A pair of bits is checked:
[a,b]
[0,0]
[1,0]
[0,1]
[1,1]
if (a), then move left, else, move right;
if (b), then move two bits, else, one bit.
That is it! Enjoy!*/
template <const uint64_t MemSize>
class ysxEMUESO_LRONETWOMachineV1
{
private:
	uint8_t* MEM = nullptr;
	uint64_t Byte = 0;
	int8_t Bit = 0;

public:
	ysxEMUESO_LRONETWOMachineV1(uint8_t* InsertMem) { MEM = InsertMem; }
	~ysxEMUESO_LRONETWOMachineV1() {}

	int Run(size_t Steps)
	{
		if (bLOG) { LOG += LogState(0); }
		for (uint64_t n = 0; n < Steps; ++n)
		{
			if (!MEM) { return(-1); }
			if (MEM[Byte] & 1 << (7 - Bit))
			{
				++Bit;
				if (MEM[Byte] & 1 << (7 - Bit)) { MEM[Byte] ^= 1 << (7 - Bit); Bit -= 5; }
				else { MEM[Byte] ^= 1 << (7 - Bit); Bit -= 3; }
			}
			else
			{
				++Bit;
				if (MEM[Byte] & 1 << (7 - Bit)) { MEM[Byte] ^= 1 << (7 - Bit); Bit += 3; }
				else { MEM[Byte] ^= 1 << (7 - Bit); ++Bit; }
			}
			if (Bit > 7) { ++Byte; Byte %= MemSize; Bit %= 8; }
			else if (Bit < 0) { --Byte; if (Byte >= MemSize) { Byte = MemSize - 1; } Bit += 8; }
			if (bLOG) { LOG += LogState(n); }
		}
		Byte = 0; Bit = 0;
		return(0);
	}

	// #######

	std::string LOG = "LOG BEG:\n";
	bool bLOG = false;
	std::string LogState(size_t n)
	{
		std::string L = "MEM ADDR: ";
		L += std::to_string((uint64_t)&MEM[Byte]) + '\n';
		L += "Byte: " + std::to_string(Byte) + " | Bit: " + std::to_string(Bit) + '\n';
		L += "Byte value at addr: " + std::to_string(MEM[Byte]) + '\n';
		L += "Bitset: " + ysxBYTE_ASCII2Bin(MEM[Byte]) + '\n';
		L += "Step: " + std::to_string(n) + "\n\n";
		return(L);
	}
};

/*LRONETWO FLIP MACHINE V2
The logic is the same of V1, but:
ROM:
[0, 1, 0, 1]
MEM:
[0, 1, 1, 0]
The ROM is what would be 'a'.
If ROM[0], then flip MEM[n] and move left;
If ROM[1], then flip MEM[n] and move right twice;*/
template <const uint64_t MemSize, const uint64_t ROMSize>
class ysxEMUESO_LRONETWOMachineV2
{
private:
	uint8_t* MEM = nullptr;
	uint8_t* ROM = nullptr;
	uint64_t MEMByte = 0, ROMByte = 0;
	int8_t MEMBit = 0; uint8_t ROMBit = 0;

public:
	ysxEMUESO_LRONETWOMachineV2(uint8_t* InsertMem, uint8_t* InsertROM) { MEM = InsertMem; ROM = InsertROM; }
	~ysxEMUESO_LRONETWOMachineV2() {}

	int Run()
	{
		if (bLOG) { LOG += LogState(0); }
		for (uint64_t n = 0; n < ROMSize * 8; ++n)
		{
			if (!MEM || !ROM) { return(-1); }
			if (ROM[ROMByte] & 1 << (7 - ROMBit))
			{
				if (MEM[MEMByte] & 1 << (7 - MEMBit)) { MEM[MEMByte] ^= 1 << (7 - MEMBit); MEMBit -= 2; }
				else { MEM[MEMByte] ^= 1 << (7 - MEMBit); --MEMBit; }
				++ROMBit;
			}
			else
			{
				if (MEM[MEMByte] & 1 << (7 - MEMBit)) { MEM[MEMByte] ^= 1 << (7 - MEMBit); MEMBit += 2; }
				else { MEM[MEMByte] ^= 1 << (7 - MEMBit); ++MEMBit; }
				++ROMBit;
			}
			if (MEMBit > 7) { ++MEMByte; MEMByte %= MemSize; MEMBit %= 8; }
			else if (MEMBit < 0) { --MEMByte; if (MEMByte >= MemSize) { MEMByte = MemSize - 1; } MEMBit += 8; }
			if (ROMBit > 7) { ++ROMByte; ROMByte %= ROMSize; ROMBit %= 8; }
			if (bLOG) { LOG += LogState(n); }
		}
		ROMByte = 0; ROMBit = 0; MEMByte = 0; MEMBit = 0;
		return(0);
	}

	// #######

	std::string LOG = "LOG BEG:\n";
	bool bLOG = false;
	std::string LogState(size_t n)
	{
		std::string L = "MEM ADDR: ";
		L += std::to_string((uint64_t)&MEM[MEMByte]) + '\n';
		L += "MEM ADDR: " + std::to_string((uint64_t)&MEM[MEMByte]) + '\n';
		L += "MEM Byte: " + std::to_string(MEMByte) + " | MEMBit: " + std::to_string(MEMBit) + '\n';
		L += "MEM Byte value at addr: " + std::to_string(MEM[MEMByte]) + '\n';
		L += "MEM Bitset: " + ysxBYTE_ASCII2Bin(MEM[MEMByte]) + "\n\n";
		L += "ROM ADDR: ";
		L += std::to_string((uint64_t)&ROM[ROMByte]) + '\n';
		L += "ROM ADDR: " + std::to_string((uint64_t)&ROM[ROMByte]) + '\n';
		L += "ROM Byte: " + std::to_string(ROMByte) + " | ROMBit: " + std::to_string(ROMBit) + '\n';
		L += "ROM Byte value at addr: " + std::to_string(ROM[ROMByte]) + '\n';
		L += "ROM Bitset: " + ysxBYTE_ASCII2Bin(ROM[ROMByte]) + '\n';
		L += "Step: " + std::to_string(n) + "\n\n---------------------\n\n";
		return(L);
	}
};

// #################################################
/* ############## abc COMPUTER ##############
https://
*/
/*
class abcCPU
{
};

// #################################################
/* ############## abc COMPUTER ##############
https://
*/
/*
class abcCPU
{
public:
	uint8_t* ROM; uint8_t ROMSize = 0;
	uint8_t* RAM; // To be safer, use at least 128 bytes
	uint64_t p = 0; // RAM Pointer, make sure that it is inside RAM limits
	std::vector<uint8_t> R = std::vector<uint8_t>::vector(4); // Registers
	uint64_t PC = 0; // Counter

	uint8_t Step() { return(ROM[PC] & 255); } // Get Instruction

	void STP() { }
	void INC() { ++PC; if (R[ROM[PC]] == 255) { R[ROM[PC]] = 0; } else { ++R[ROM[PC]]; } ++PC; }
	void DEC() { ++PC; if (!R[ROM[PC]]) { R[ROM[PC]] = 255; } else { --R[ROM[PC]]; } ++PC; }
	void JMP() { ++PC; PC = ROM[PC]; }
	void ISZ() { ++PC; if (!R[ROM[PC]]) { PC += 2; } ++PC; }

	// ### BONUS ###
	// WRITE IN RAM:
	void WRM() { ++PC; RAM[p] = R[ROM[PC]]; ++PC; }
	// READ IN RAM:
	void RRM() { ++PC; R[ROM[PC]] = RAM[p]; ++PC; }*/
	/* SET RAM POINTER:
	p is 'long long'; So we have to add and sub.
	R = snnn nnnn;
	s = signal, 0 = add, 1 = sub; n_m = amount to add or sub;
	Ex.: p = 0; SRM(0100 1101) -> p += 77; SRM(1100 1101) -> p -= 77; p = 0;
	*/ 
	/*void SRM()
	{
		++PC;
		if (R[ROM[PC]] & 128) { p -= R[ROM[PC]] & 127; }
		else { p += R[ROM[PC]] & 127; }
		++PC;
	}

	// FETCH IMEDIATE (LIMITED RANGE OF REGISTERS):
	// Bits: SS SSSS;
	// 
	void FIM(uint8_t Reg) { std::cout << "FIM: R': " << R[Reg]; ++PC; R[Reg] = ROM[PC]; std::cout << " | R'': " << R[Reg] << " | ROM[" << PC << "]: " << ROM[PC] << '\n'; ++PC; }

	// Read ports:
	//void RDP(uint32_t Data)
	//{

	//}
	*/
	/* Instructions:
	STP = 000; INC = 001; DEC = 010;
	JMP = 011; ISZ = 100; WRM = 101;
	RRM = 110; SRM = 111;

	FIM = 10RR;	RDP = 11PP;

	XYZ = 0 0000 // TEMP
	*/
	/*void Instr(uint8_t I)
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

	abcCPU(uint8_t* ROM16b, uint16_t ROM_Size) { ROM = ROM16b; ROMSize = ROM_Size; }
	abcCPU(uint8_t* ROM16b, uint16_t ROM_Size, uint32_t Registers) // Careful with the amount of registers!
	{
		ROM = ROM16b; ROMSize = ROM_Size;
		R = std::vector<uint8_t>::vector(Registers);
	}

	~abcCPU() { }

	// #################################################

	void RST() { p = 0; PC = 0; memset(&R[0], 0, R.size()); } // Clean registers
	
	// Be sure of how much memory you use for ROM!!!
	void Run(uint32_t Steps)
	{
		RST(); for (uint32_t n = 0; n < Steps; ++n) { if (bLOG) { LOG += LogState(); } Instr(ROM[PC]); }
	}
	
	// #################################################

	std::string LOG = "LOG BEG:\nInstructions:\nSTP = 000; INC = 001; DEC = 010;\nJMP = 011; ISZ = 100; WRM = 101;\nRRM = 110; SRM = 111;\nFIM = 10RR;\n";
	bool bLOG = false;
	std::string LogState()
	{
		std::string L = "\nRegisters:\n";
		for (size_t n = 0; n < R.size(); ++n)
		{
			L += "R[" + std::to_string(n) + "]: " + std::to_string((short)R[n]);
			if (n % 8 == 7) { L += '\n'; } else { L += " | "; }
		}
		L += "RAM p: " + std::to_string(p) + " | RAM[p]: " + std::to_string((short)RAM[p]) + '\n';
		L += "PC: " + std::to_string(PC) + " | ROM[PC]: " + std::to_string((short)ROM[PC]) + '\n';
		return(L);
	}

};*/

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_