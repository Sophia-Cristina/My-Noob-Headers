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
// #######
// #####################

// UTILS:
#include "ysxCImg.h"

// PROCESSORS:
#include "ysxComp/Processors/ysxIntel4004.h"

// OLDSCHOOL EMU:
#include "ysxComp/ysxZXSpec.h"

// HISTORICAL OR BASIC COMPUTERS:
#include "ysxComp/ysxEMUHist.h"

// EDUCATIONAL STUFF:
#include "ysxComp/ysxEMUEdu.h"

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
 [T1] https://www.ti.com/lit/ds/symlink/sn74ls00.pdf?ts=1627944918289*/
// #################################################
// ############## FLIP-FLOPS ############## [FF1]

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

	^  = 0011 1100
	S&^= 0001 1100
	R&^= 0010 0000
*/
struct SRNORFF
{
	Point<uint8_t> Q = { 0, 0 };
	void FF(uint8_t S, uint8_t R)
	{
		uint8_t X = S ^ R; S &= X; R &= X;
		Point<uint8_t> NOR = { ~(Q.y | S), ~(Q.x | R) };
		Q.x = NOR.y; Q.y = NOR.x;
	}
	
};

/* JK Flip-Flop:
       PR,    CLR,    CLK
   110011, 001111, 010101
*/
class JKFF
{
public:
	uint8_t PR = 0, CLR = 0, CLK = 0;
	uint8_t J = 0, K = 0;
	Point<uint8_t> Q = { 0, 0 };
	void FF()
	{
		Point<uint8_t> AND = { ((J & CLK) | Q.y) & PR, ((K & CLK) | Q.x) & CLR };
		Q.x = AND.y; Q.y = AND.x;
		//J = Q.y; K = Q.x;
	}

};

// #################################################
// ############## COUNTERS ############## [D3]

// DECADE COUNTER:
class DecadeCnt
{
public:
	Point<uint8_t> Q = { 0, 0 };
	void FF(uint8_t S, uint8_t R)
	{
		uint8_t X = S ^ R; S &= X; R &= X;
		Point<uint8_t> NOR = { ~(Q.y | S), ~(Q.x | R) };
		Q.x = NOR.y; Q.y = NOR.x;
	}
};

// #################################################
// ############## PORTS ##############

struct USB_C { uint8_t CC, D1, D2, RX1, RX2, TX1, TX2; };

// #################################################
// ############## PAL16L8 EPROM ##############

// #################################################
/* ############## SN7400 FOUR NAND ############## // [T1]
https://en.wikipedia.org/wiki/7400-series_integrated_circuits
	  __________
1A  -|1 #	  14|- 4Y
1B  -|2       13|- 4B
1Y  -|3  SN   12|- 4A
Vcc -|4	7400  11|- GND
2Y  -|5		  10|- 3B = 3 In
2A  -|6        9|- 3A = 3 In
2B  -|7________8|- 3Y = 3 Out

GATE LOGIC:
.A.B..Y.
|H|H||L|
|L|x||H|
|x|L||H|

MY TEMPLATE, U8 ADDRESS:
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

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_