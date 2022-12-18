#pragma once

//#include <time.h>
//#include "ysxCImg.h" // To create terminal user interfaces

#ifndef YSXEMU_H
#define YSXEMU_H

// #####################
// ####### By Sophia Cristina
// ####### I'm trying to study some computer stuffs...
// #######
// ####### Everything related to emulating some kind of computer
// ####### or electronic devide akin to it.
// #####################

// UTILS:
#include "ysxCImg.h"

// PROCESSORS:
#include "ysxComp/Processors/ysxIntel4004.h"
//#include "ysxComp/NES/ysxRP2A03.h"
//#include "ysxComp/NES/ysxNESAPU.h"
//#include "ysxComp/NES/ysxNESPPU.h"

// OLDSCHOOL EMU:
#include "ysxComp/ysxZXSpec.h"

// HISTORICAL OR BASIC COMPUTERS:
#include "ysxComp/ysxEMUHist.h"

// EDUCATIONAL STUFF:
#include "ysxComp/ysxEMUEdu.h"

// EDUCATIONAL STUFF:
#include "ysxComp/ysxEMUEsoLang.h"

// #################################################
/* REFERENCES:
DECADE COUNTER:
 [D1] https://teachics.org/computer-organization-and-architecture/decade-counter-bcd-counter/
 [D2] https://www.electronics-tutorial.net/Mini-Projects/DECADE-COUNTER/
 [D3] https://www.electronicsforu.com/technology-trends/learn-electronics/decade-counter-circuit-basics
  [D3.1] https://www.slideshare.net/slideshow/embed_code/key/pFFctjyDmwMMGw
EPROM DESIGN:
 [E1] https://pdf1.alldatasheet.com/datasheet-pdf/view/27266/TI/PAL16L8.html
7400-SERIES:
 [T1] https://www.ti.com/lit/ds/symlink/sn74ls00.pdf?ts=1627944918289
ROM / RAM, MICRO-CONTROLLER:
 [M1] https://pdf1.alldatasheet.com/datasheet-pdf/download/519427/STMICROELECTRONICS/STM8S003F3P6TR.html
*/

 // #################################################
 // ############## ELEC. COMPONENTS ##############

 // ####### BASIC CIRCUIT:

/* TRANSFER DATA WITH AN EMULATED BUS :
!!! ATTENTION, UNSAFE CODE !!!
This code assumes you know what memory you are accessing!
It constructs with 'BusOffSet' as the initial position of an array of 'T_' with constant size:
		uint8_t ARRAY[SIZE]; DataBus<uint_8, SIZE> DB(ARRAY) { p = ARRAY; }
WRITE or READ assumes that 'ARRAY[addr % Size]' is accessible and doesn't mind if your computer explodes!
		 W(addr, 123) = p[addr % Size]     = 123;
SAME AS: W(addr, 123) = ARRAY[addr % Size] = 123;
SO YOU MUST be sure the address you are using inside the bus is inside the array size!
*/
template <class T_, size_t Size>
class DataBus
{
public:
	T_* p = nullptr;
	DataBus(T_* BusOffSet) { p = BusOffSet; }
	// Write; Read:
	void W(size_t addr, T_ data) { if (p) { p[addr] = data; } };
	T_ R(size_t addr, bool bReadOnly = false) { if (p) { return(p[addr]); } return(0); };
};

/* BIPOLAR TRANSISTOR (NPN AND PNP):
NPN: iC--v->oE | PNP: oC--v-<iE
		iB	   |		 oB
Same as an 'AND'*/
//uint8_t TrnsBip(uint8_t In, uint8_t B) { return(In & B); }
 
// ####### FLIP-FLOPS: [FF1]

// SET-RESET FLIP-FLOP, RET. Q0 AND Q1:
// (S) | (Q & (~(R)))
//uint8_t SRFF(uint8_t S, uint8_t R, uint8_t Q) { return (S | (Q & (~R))); }

/* SET-RESET NOR FLIP-FLOP:
   NOR.x , NOR.y
	 Q.y , Q.x
	y | S, x | R = x, y
Hold:
	0 | 0, 0 | 0 = 1, 1:<-| Loop
	1 | 0, 1 | 0 = 0, 0:>-|
Reset:
	0 | 0, 0 | 1 = 0, 1:<-| Loop
	1 | 0, 1 | 1 = 0, 0:  |
	0 | 0, 1 | 1 = 0, 1:  |
	1 | 0, 1 | 1 = 0, 0:>-|
Set:
	0 | 1, 0 | 0 = 1, 0:<-| Loop
	0 | 1, 1 | 0 = 0, 0:  |
	0 | 1, 0 | 0 = 1, 0:  |
	0 | 1, 1 | 0 = 0, 0:>-|
Not allowed:
    0 | 1, 0 | 1 = 0, 0:<-| Loop
	S  = 0101 1110
	R  = 0110 0010
	X  = 0011 1100
	S&X= 0001 1100
	R&X= 0010 0000
*/
struct SRNORFF
{
	Point<uint8_t>* Q = nullptr;
	Point<uint8_t> NOR;	uint8_t X;
	void FF(uint8_t S, uint8_t R = 0)
	{
		if (Q)
		{
			X = S ^ R; S &= X; R &= X;
			NOR.x = ~(Q->y | S); NOR.y = ~(Q->x | R);
			Q->x = NOR.y; Q->y = NOR.x;
		}
	}
};

// D-LATCH, USE CLOCK ON 'EN' TO FLIP-FLOP:
struct DLatch
{
	Point<uint8_t>* Q = nullptr;
	Point<uint8_t> AND, NOR; uint8_t iD, X;
	void FF(uint8_t D, uint8_t EN)
	{
		if (Q)
		{
			iD = ~D;
			AND.x = iD & EN; AND.y = D & EN;
			X = AND.x ^ AND.y; AND.x &= X; AND.y &= X;
			NOR.x = ~(Q->y | AND.x); NOR.y = ~(Q->x | AND.y);
			Q->x = NOR.y; Q->y = NOR.x;
		}
	}
};

// JK FLIP-FLOP:
struct JKFF
{
	uint8_t J = 0, K = 0;
	Point<uint8_t>* Q = nullptr;
	Point<uint8_t> AND, NOR;
	void FF(uint8_t CLK)
	{
		if (Q)
		{
			AND.x = Q->y & CLK & J; AND.y = Q->x & CLK & K;
			//uint8_t X = AND.x ^ AND.y; AND.x &= X; AND.y &= X; // Maybe i don't need that anymore, since it have the "toggle" option
			NOR.x = ~(Q->y | AND.x); NOR.y = ~(Q->x | AND.y);
			Q->x = NOR.y; Q->y = NOR.x;
		}
	}

};

// ####### COUNTERS:

// DECADE COUNTER: !!! WIP !!!
class DecadeCnt
{
public:
	SRNORFF FFs[4];
	Point<uint8_t> Qs[4];
	uint8_t Os[8]; // Parallel outs (overwrite by function)
	uint8_t cnt = 0;
	DecadeCnt()
	{
		FFs[0].Q = &Qs[0]; FFs[1].Q = &Qs[1];
		FFs[2].Q = &Qs[2]; FFs[3].Q = &Qs[3];
	}
	void FF(uint8_t CLK)
	{
		/*FFs[0].FF(CLK, CLK);
		FFs[1].FF(FFs[0].Q->x, ~FFs[0].Q->x);
		FFs[2].FF(FFs[1].Q->x, ~FFs[1].Q->x);
		FFs[3].FF(FFs[2].Q->x, ~FFs[2].Q->x);*/
		FFs[0].FF(CLK, 0);
		FFs[1].FF(FFs[0].Q->x, 0);
		FFs[2].FF(FFs[1].Q->x, 0);
		FFs[3].FF(FFs[2].Q->x, 0);
		GetPrllOut();
	}
	// GET PARALLEL OUT TO 'Os' ARRAY:
	void GetPrllOut()
	{
		LOOP8
		{
			Os[n] = 0; uint8_t tmp;
			for (uint8_t Q = 0; Q < 4; ++Q)
			{
				tmp = ((FFs[Q].Q->x >> n) & 1) * pow(2, Q);
				Os[n] |= tmp;
				//Os[n] |= FFs[Q].Q.x << bit;
				/*  [Q]|  >> n |&1|pow|Os
				    b6:|1011011| 0|1:0|0v
				    d2:|1101001| 0|2:0|0v
				    b1:|1011000| 1|4:4|1v
				    4d:|0100110| 1|8:8|1>> = C = 12 = 1100
				*/
			}
		}

	}
};

// #################################################
// ############## PORTS & PERIPHERALS ##############

// uint8_t data[7];
struct USB_C { uint8_t CC, D1, D2, RX1, RX2, TX1, TX2; };

// #################################################
// ############## IC ##############

// ####### PAL16L8 EPROM:

/* ####### SN7400 FOUR NAND: // [T1]
https://en.wikipedia.org/wiki/7400-series_integrated_circuits
	  _________
1A  -|1 #	 14|- 4Y
1B  -|2      13|- 4B
1Y  -|3  SN  12|- 4A
Vcc -|4	7400 11|- GND
2Y  -|5		 10|- 3B
2A  -|6       9|- 3A
2B  -|7_______8|- 3Y

GATE LOGIC:
.A.B..Y.
|H|H||L|
|L|x||H|
|x|L||H|

MY TEMPLATE, U8 ADDRESS (OBSOLETE):
1   1   0   1 |  1   0   0   1 = 217
4B, 4A, 3B, 3A | 2B, 2A, 1B, 1A
*/
class TTL_SN7400
{
public:

	struct DATA { uint8_t A[4], B[4]; };
	//DATA d;

	// return is ui32, but that is an array of 4 bytes, ui8[4]:
	uint32_t Out(DATA In) { return(~(*(uint32_t*)&In.A[0] & *(uint32_t*)&In.B[0])); }
	std::vector<uint32_t> Outs(std::vector<DATA> In)
	{
		std::vector<uint32_t> O(In.size());
		for (int i = 0; i < In.size(); ++i) { uint32_t d = ~(*(uint32_t*)&In[i].A[0] & *(uint32_t*)&In[i].B[0]); O.push_back(d); }
		return(O);
	}

	// SAVE BINARY FILE WITH OUTPUTS:
	void GetSequence(std::vector<DATA> s, std::string Path = "!TTLSN7400.bin")
	{
		std::vector<uint32_t> o = Outs(s);
		std::ofstream O(Path, std::ios::binary); // In fact, it could maybe be text-mode, since the string is in binary anyway
		if (O.is_open()) { for (size_t n = 0; n < o.size(); ++n) { O << o[n]; } }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}
};

/* ####### MICRO-CONTROLLER STM8S003F3P6TR: // [M1]
The STM8S003x value line 8-bit microcontrollers feature 8 Kbytes Flash program memory,
plus integrated true data EEPROM.*/

class STM8S003F3P6TR
{
public:

};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_