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

// PROCESSORS:
#include "ysxComp/Processors/ysxIntel4004.h"

// OLDSCHOOL EMU:
#include "ysxComp/ysxZXSpec.h"

// HISTORICAL OR BASIC COMPUTERS:
#include "ysxComp/ysxEMUHist.h"

// EDUCATIONAL STUFF:
#include "ysxComp/ysxEMUEdu.h"


// #####################
// ####### FORWARD DECLARATIONS:
// #####################

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

// SET-RESET NOR FLIP-FLOP:
struct SRNORFF
{
	Point<uint8_t> Q = { 0, 0 };
	void FF(uint8_t S, uint8_t R)
	{ Point<uint8_t> NOR = { ~(Q.y | S), ~(Q.x | R) }; Q.x = NOR.y; Q.y = NOR.x; }
};

// #################################################
// ############## COUNTERS ############## [D3]

// DECADE COUNTER:
class DecadeCnt
{
public:
	SRNORFF FF[4];
	uint8_t oQ[4];
	void Count(uint8_t S, uint8_t R)
	{
		Point<uint8_t> NOR = { ~(FF[0].Q.y | S), ~(FF[0].Q.x | R) };
		FF[0].Q.x = NOR.y; FF[0].Q.y = NOR.x; oQ[0] = FF[0].Q.x;
		NOR.x = ~(FF[1].Q.y | FF[0].Q.y); NOR.y = ~(FF[1].Q.x | 0); FF[1].Q.x = NOR.y; FF[1].Q.y = NOR.x; oQ[1] = FF[1].Q.x;
		NOR.x = ~(FF[2].Q.y | FF[1].Q.y); NOR.y = ~(FF[2].Q.x | 0); FF[2].Q.x = NOR.y; FF[2].Q.y = NOR.x; oQ[2] = FF[2].Q.x;
		NOR.x = ~(FF[3].Q.y | FF[2].Q.y); NOR.y = ~(FF[3].Q.x | 0); FF[3].Q.x = NOR.y; FF[3].Q.y = NOR.x; oQ[3] = FF[3].Q.x;
		uint8_t CLR = FF[1].Q.x & FF[3].Q.x;
		FF[0].Q.x &= CLR; FF[0].Q.y &= CLR; FF[1].Q.x &= CLR; FF[1].Q.y &= CLR;
		FF[2].Q.x &= CLR; FF[0].Q.y &= CLR; FF[1].Q.x &= CLR; FF[3].Q.y &= CLR;		
	}
};

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
	
	std::string GetOuts(std::string In) 
	{
		std::string O;
		for (int n = 0; n < In.size(); ++n)
		{
						  // unused 4321 Y
			uint8_t Y = 15;  //   0000 1111
					   // nB			   nA
			if ((In[n] & 0x2) && (In[n] & 0x1)) { Y -= 1; }   // Y = 0000 1110 = 14
			if ((In[n] & 0x8) && (In[n] & 0x4)) { Y -= 2; }   // Y = 0000 1101 = 13
			if ((In[n] & 0x20) && (In[n] & 0x10)) { Y -= 4; } // Y = 0000 1011 = 11
			if ((In[n] & 0x80) && (In[n] & 0x40)) { Y -= 8; } // Y = 0000 0111 = 7  // MAYBE I CAN USE A SINGLE CHAR WITH AND AND DELETE ALL THOSE IFS
			O.push_back(Y);
			// RESULTS (based on image):
			// { 3, 7, 11 } + 16 * (Row - 1) // 15 + 16 * (Row - 1)
			// Especial color each 4 Rows.
		}
		return(O);
	}

	// DUMP ALL POSSIBLE COMBINATIONS:
	void GetAllCombinations()
	{
		std::string s;
		for (int n = 0; n < 256; ++n) { s.push_back(n); }
		s = GetOuts(s);
		std::ofstream O("!TTLSN7400.bin", std::ios::binary);
		if (O.is_open()) { O.write((char*)&s[0], s.size()); }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}

	// DUMP A STRING RESULT (EACH CHAR BIT CORRESPONDS TO: B4A4B3A3B2A2B1A1):
	void GetSequence(std::string s)
	{
		s = GetOuts(s);
		std::ofstream O("!TTLSN7400.bin", std::ios::binary); // In fact, it could maybe be text-mode, since the string is in binary anyway
		if (O.is_open()) { O.write((char*)&s[0], s.size()); }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_