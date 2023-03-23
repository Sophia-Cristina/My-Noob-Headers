#pragma once

#ifndef YSXEMUICS_H
#define YSXEMUICS_H

// #####################
// ####### By Sophia Cristina
// ####### Emulating small electronic Integrated Circuits.
// ####### However, big ICs, like, processors, have their own header.
// #####################


// #################################################
/* REFERENCES:
EPROM DESIGN:
 [E1] https://pdf1.alldatasheet.com/datasheet-pdf/view/27266/TI/PAL16L8.html
7400-SERIES:
 [T1] https://www.ti.com/lit/ds/symlink/sn74ls00.pdf?ts=1627944918289
ROM / RAM, MICRO-CONTROLLER:
 [M1] https://pdf1.alldatasheet.com/datasheet-pdf/download/519427/STMICROELECTRONICS/STM8S003F3P6TR.html
*/

 // #################################################
 // ############## ABC ##############


// #################################################
// ############## IC ##############

// Here you add random small ICs that are in no other catheogory.

/* ####### SN7400 FOUR NAND: [T1]
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
class ysxEMU_TTL_SN7400
{
public:

	union DATA { uint32_t I; uint8_t C[4]; };

	// return is ui32, but that is an array of 4 bytes, ui8[4]:
	uint32_t Out(Point<DATA> In) { return(~(In.x.I & In.y.I)); }
	std::vector<uint32_t> Outs(std::vector<Point<DATA>> In)
	{
		std::vector<uint32_t> O(In.size());
		for (size_t i = 0; i < In.size(); ++i) { uint32_t d = ~(In[i].x.I & In[i].y.I); O.push_back(d); }
		return(O);
	}

	// SAVE BINARY FILE WITH OUTPUTS:
	void GetSequence(std::vector<Point<DATA>> s, std::string Path = "!TTLSN7400.bin")
	{
		std::vector<uint32_t> o = Outs(s);
		std::ofstream O(Path, std::ios::binary);
		if (O.is_open()) { for (size_t n = 0; n < o.size(); ++n) { O << o[n]; } }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}
};

// #################################################
// ############## ROM ##############

// ####### PAL16L8 EPROM: [E1]
class ysxEMU_PAL16L8
{
public:

};


// #################################################
// ############## RAM ##############

// ####### :

// #################################################
// ############## MICROCONTROLLERS ##############

/*####### STM8S003F3P6TR: [M1]
The STM8S003x value line 8-bit microcontrollers feature 8 Kbytes Flash program memory,
plus integrated true data EEPROM.*/
class ysxEMU_STM8S003F3P6TR
{
public:

};

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_