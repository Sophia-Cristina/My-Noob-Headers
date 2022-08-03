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
"Set of five commands is small but 'Turing complete' and therefore enough to represent
all mathematical functions: incrementing ("inc") or decrementing ("dec") a register,
unconditional jump ("jmp"), conditional jump ("isz", skips next instruction if a register
is zero), and stopping program execution ("stp")".

*/
class WDRPaperCPU
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

	// IF YOU USE THIS METHOD:
	//		void INC() { ++PC; if (R[*(uint32_t*)&ROM[PC]] == 255) { R[*(uint32_t*)&ROM[PC]] = 0; } else { ++R[*(uint32_t*)&ROM[PC]]; } PC += 4; }
	// YOU CAN HAVE 4GB OF MEMORY ONLY WITH REGISTERS!

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
	p is 'long long'; So we have to add and sub.
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

	WDRPaperCPU(uint8_t* ROM16b, uint16_t ROM_Size) { ROM = ROM16b; ROMSize = ROM_Size; }
	WDRPaperCPU(uint8_t* ROM16b, uint16_t ROM_Size, uint32_t Registers) // Careful with the amount of registers!
	{
		ROM = ROM16b; ROMSize = ROM_Size;
		R = std::vector<uint8_t>::vector(Registers);
	}

	~WDRPaperCPU() { }

	// #################################################

	void RST() { p = 0; PC = 0; memset(&R[0], 0, R.size()); } // Clean registers

	// Be sure of how much memory you use for ROM!!!
	void Run(uint32_t Steps)
	{
		RST(); for (uint32_t n = 0; n < Steps; ++n) { if (bLOG) { LOG += LogState(); } OpC(ROM[PC]); }
	}

	// #################################################

	std::string LOG = "LOG BEG:\nOpCuctions:\nSTP = 000; INC = 001; DEC = 010;\nJMP = 011; ISZ = 100; WRM = 101;\nRRM = 110; SRM = 111;\nFIM = 10RR;\n";
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

	INC 1  ; OpCuctions lines begin with a space
		   ; spaces are ignored between instruction and variable
	INC12   ; OK!
	INC 12  ; OK!
	INC  12 ; OK!
	INC 1 2 ; NOT OK!
	IN C 12 ; NOT OK!

	FIM 1,2 ; *NO* space between comma
	*/
	enum eFlag
	{
		fLab = 1, fIns = 2, fVal = 4, // ON
		fCom = 8, fJMP = 128, fNum = 48,
		fnLab = 0xfe, fnIns = 0xfd, fnVal = 0xfb, // OFF
		fnCom = 0xf7, fnJMP = 127, fnNum = 0xcf
	};
	void Assembler(uint8_t* Asm, uint32_t End, uint8_t* Out, std::string Sav = " ")
	{
		std::string GetInst[9] = { "STP", "INC", "DEC", "JMP", "ISZ", "WRM", "RRM", "SRM", "FIM" };
		std::map<std::string, uint32_t> Labels;
		uint32_t Line = 0, O_n = 0; // OpCuction 'Line', Out writting position 'O_n'
		//std::vector<char> Buf(End);
		std::string s, WrgI = "WRONG INSTRUCTION AT 'n: ";
		uint8_t Byte = 0;

		/*
			  Comment
			  |W Val
			  ||W OpC
			  |||W label
		 1011 0110 = B6 Possible flags
		 ||0 - 3 numbers
		 |Nothing yet, use for anything
		 JMP Num or Label
		 */
		uint8_t F = 0, I = 0;

		std::ofstream O; if (Sav != " ") { O.open(Sav, std::ios::binary); if (!O.is_open()) { std::cout << "Could not create output file!\n"; } }
		for (size_t n = 0; n < End; ++n)
		{
			if (Asm[n] == ';' && !(F & fCom)) { F |= fCom; } //  <------- GOT COMMENT!
			if (F & fCom)
			{
				if (F & 7) { std::cout << "Found comment, but assembler is in 'writting mode'!\n"; break; }
				if (Asm[n] == '\n') { F &= fnCom; }
			}
			else
			{
				if (!(F & fIns)) // <------- IF NOT WRITTING INSTRUCTION, CHECK IF LABEL!
				{   // If there is no ' ', means a label if it is NOT writting a label already!
					if (Asm[n] != ' ' && Asm[n] != '\n' && !(F & fLab)) { F |= fLab; } // GOT LABEL, SET FLAG
				}
				if (F & fLab) // <------- WRITE LABEL!
				{
					if (Asm[n] == ':') // If at the end of a label
					{
						if (n < End - 1) // Finish writting
						{
							++n; if (Asm[n] == '\n') { F &= fnLab; Labels.insert({ s, Line }); s.clear(); } // Flag &= 1111 1110, Add Labels 
						}
						else { std::cout << "Incomplete code!\n"; break; } // Code is too short!
					}
					else // Or else, keep writting
					{
						if (Asm[n] != ' ') { s.push_back(Asm[n]); }
					}
				}
				else // <------- GOT INSTRUCTION! <------- <------- <------- <------- <------- <-------
				{
					if (F & fVal)
					{
						if (Asm[n] != ' ') // <------- GOT VALUE!
						{
							if (I != 3) // FIM and JMP
							{
								if (IsNumber(Asm[n]))
								{
									if (I != 8)
									{
										if (n < End - 3) // Biggest: INC 255
										{
											while (IsNumber(Asm[n]) && ((F >> 4) & 3) < 3)
											{
												s.push_back(Asm[n]);
												++n; // Since we are sure there is size for it!
												F = (F & fnNum) + ((((F >> 4) + 1) & 3) << 4); // Increase number count
											}
											if (Asm[n] == ',') { std::cout << "OpCuction should have only one value!\n"; s.clear(); break; }
											Byte = Str2Int(s);
											Out[O_n] = Byte; ++O_n;
											if (O.is_open()) { O << Byte; }
											s.clear(); F = 0; Byte = 0; Line += 2; I = 0; // Correct variables!
										}
										else { std::cout << "Incomplete code!\n"; break; }
									}
									else
									{
										if (n < End - 5) // Biggest: FIM 3,255
										{
											Out[O_n] = 8 + (Chr2Int(Asm[n]) & 3); if (O.is_open()) { O << Out[O_n]; }
											++O_n; ++n;
											if (Asm[n] == ',')
											{
												++n;
												while (IsNumber(Asm[n]) && ((F >> 4) & 3) < 3)
												{
													s.push_back(Asm[n]);
													++n; // Since we are sure there is size for it!
													F = (F & fnNum) + ((((F >> 4) + 1) & 3) << 4); // Increase number count
												}
												Byte = Str2Int(s);
												Out[O_n] = Byte; ++O_n;
												if (O.is_open()) { O << Byte; }
												s.clear(); F = 0; Byte = 0; Line += 2; I = 0; // Correct variables!
											}
											else { std::cout << "Expected ','!\n"; break; }
										}
										else { std::cout << "Incomplete code!\n"; break; }
									}
								}
								else { std::cout << "Expected a number!\n"; break; }
							}
							else
							{
								if (IsNumber(Asm[n]) && IsLetter(Asm[n]))
								{
									while (IsNumber(Asm[n]) && IsLetter(Asm[n]) && ((F >> 4) & 3) < 3 && n < End)
									{
										if (IsLetter(Asm[n])) { F |= fJMP; }
										s.push_back(Asm[n]);
										++n; // Since we are sure there is size for it!
										if (!(F & fJMP)) { F = (F & fnNum) + ((((F >> 4) + 1) & 3) << 4); } // Increase number count
									}
									if (F & fJMP) { Byte = Labels[s] & 255; } else { Byte = Str2Int(s); }
									Out[O_n] = Byte; ++O_n;
									if (O.is_open()) { O << Byte; }
									s.clear(); F = 0; Byte = 0; Line += 2; I = 0; F &= fnJMP; // Correct variables!
								}
								else { std::cout << "Expected a number or a char!\n"; break; }
							}
						}
					}
					else // <------- FINDING INSTRUCTION! <------- <------- <------- <------- <------- <------- 
					{
						F |= fIns; // Set flag to writting instruction mode!
						// { "STP", "INC", "DEC", "JMP", "ISZ", "WRM", "RRM", "SRM", "FIM" };
						if (!I)
						{
							if (Asm[n] == 'D' || Asm[n] == 'd') { I = 2; }
							if (Asm[n] == 'F' || Asm[n] == 'f') { I = 8; } // Don't increment 'O_n'!
							if (Asm[n] == 'I' || Asm[n] == 'i') { I = 1; }
							if (Asm[n] == 'J' || Asm[n] == 'j') { I = 3; }
							if (Asm[n] == 'R' || Asm[n] == 'r') { I = 6; }
							if (Asm[n] == 'S' || Asm[n] == 's') { I = 255; } // 0 is reserved for writting
							if (Asm[n] == 'W' || Asm[n] == 'w') { I = 5; }
						}
						else if (I == 255 || I == 7) // <------- STP();
						{
							if (Asm[n] != 'T' || Asm[n] != 't' || Asm[n] != 'R' || Asm[n] != 'r') { std::cout << WrgI << n << "'!\n"; I = 0; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n] == 'T' || Asm[n] == 't') // Got STP();
									{
										// Flag, inc. 'n' (we know we can), set byte to memory, Save on binary.
										if (Asm[n + 1] == 'P' || Asm[n + 1] == 'p') { F = 0;  I = 0; ++n; Out[O_n] = 0; ++O_n; if (O.is_open()) { O << 0; } }
										else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
									}
									else // Got SRM();
									{
										if (Asm[n + 1] == 'M' || Asm[n + 1] == 'm') { F |= fVal; ++n; Out[O_n] = 7; ++O_n; if (O.is_open()) { O << 7; } }
										else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
									}
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 1 || I == 4) // <------- INC() or ISZ();
						{
							if (Asm[n] != 'N' || Asm[n] != 'n' || Asm[n] != 'S' || Asm[n] != 's') { std::cout << WrgI << n << "'!\n"; I = 0; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n] == 'N' || Asm[n] == 'n') // Got INC();
									{
										if (Asm[n + 1] == 'C' || Asm[n + 1] == 'c') { F |= fVal; ++n; Out[O_n] = 1; ++O_n; if (O.is_open()) { O << 1; } }
										else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
									}
									else
									{
										I = 4; // Got ISZ();
										if (Asm[n + 1] == 'Z' || Asm[n + 1] == 'z') { F |= fVal; ++n; Out[O_n] = 4; ++O_n; if (O.is_open()) { O << 4; } }
										else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
									}
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 2) // <------- DEC();
						{
							if (Asm[n] != 'E' || Asm[n] != 'e') { std::cout << WrgI << n << "'!\n"; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n + 1] == 'C' || Asm[n + 1] == 'c') { F |= fVal; ++n; Out[O_n] = 2; ++O_n; if (O.is_open()) { O << 2; } }
									else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 3) // <------- JMP();
						{
							if (Asm[n] != 'M' || Asm[n] != 'm') { std::cout << WrgI << n << "'!\n"; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n + 1] == 'P' || Asm[n + 1] == 'p') { F |= fVal; ++n; Out[O_n] = 3; ++O_n; if (O.is_open()) { O << 3; } }
									else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 5) // <------- WRM();
						{
							if (Asm[n] != 'R' || Asm[n] != 'r') { std::cout << WrgI << n << "'!\n"; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n + 1] == 'C' || Asm[n + 1] == 'c') { F |= fVal; ++n; Out[O_n] = 5; ++O_n; if (O.is_open()) { O << 5; } }
									else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 6) // <------- RRM();
						{
							if (Asm[n] != 'R' || Asm[n] != 'r') { std::cout << WrgI << n << "'!\n"; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n + 1] == 'C' || Asm[n + 1] == 'c') { F |= fVal; ++n; Out[O_n] = 6; ++O_n; if (O.is_open()) { O << 6; } }
									else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
						else if (I == 8) // <------- FIM();
						{
							if (Asm[n] != 'E' || Asm[n] != 'e') { std::cout << WrgI << n << "'!\n"; break; }
							else
							{
								if (n < End - 1) // Check code integrity
								{
									if (Asm[n + 1] == 'C' || Asm[n + 1] == 'c') { F |= fVal; ++n; } // FIM manages 'Out' by value
									else { std::cout << WrgI << n + 1 << "'!\n"; I = 0; break; }
								}
								else { std::cout << "Incomplete code!\n"; break; }
							}
						}
					}
				}
			}
		}
		if (O.is_open()) { O.close(); }
	}
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