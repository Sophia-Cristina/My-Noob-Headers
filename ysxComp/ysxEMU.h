#pragma once

//#include <time.h>
#include "ysxCImg.h" // To create terminal user interfaces

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

// #####################
// ####### FORWARD DECLARATIONS:
// #####################

// #################################################
// #####################
// #######
// REFERENCES:
// EPROM DESIGN:
//  [E1] https://pdf1.alldatasheet.com/datasheet-pdf/view/27266/TI/PAL16L8.html
// 7400-SERIES:
//  [T1] https://www.ti.com/lit/ds/symlink/sn74ls00.pdf?ts=1627944918289

// #################################################
// ############## PAL16L8 EPROM ##############

// #################################################
// ############## SN7400 FOUR NAND ############## // [T1]
// https://en.wikipedia.org/wiki/7400-series_integrated_circuits

/*
		  __________
	1A  -|1 #	  14|- 4Y
	1B  -|2       13|- 4B
	1Y  -|3  SN   12|- 4A
	Vcc -|4	7400  11|- GND
	2Y  -|5		  10|- 3B = 3 In
	2A  -|6        9|- 3A = 3 In
	2B  -|7________8|- 3Y = 3 Out
	
	// VOLTAGES:
	// Supply: MAX 7v
	// In: MIM: 4.75v | NOM : 5v | MAX 5.5v;
	// V_IH MIN: 2v;
	// V_IL MAX: 0.8v;
	// I_OL MAX: 16mA;

	GATE LOGIC:
	|A|B||Y|

	|H|H||L|
	|L|x||H|
	|x|L||H|

	// MY TEMPLATE, U8 ADDRESS:
	//  1   1   0   1 |  1   0   0   1 = 217
	// 4B, 4A, 3B, 3A | 2B, 2A, 1B, 1A
*/

class TTL_SN7400_FourNAND_Chip : public Component
{
public:

	CompConfig* Config;
	enum Pins { A1, B1, A2, B2, A3, B3, A4, B4, Vcc }; // Work on Vcc yet to be done!
	Wire* Y; // Outputs are in numerial order. IDEAL that you add 4 signals!
	Wire* GND; // You can point GND wire signal to its own input

	TTL_SN7400_FourNAND_Chip(CompConfig& InConfig)
	{
		Config = &InConfig;
		if (Config->Volts > 5.5) { Config->Volts = 5.5; } // !!! THIS IS THE INPUT VOLT, MAX IS 5.5v !!!
		Signals = std::vector<std::vector<double>>::vector(9); // 8 Inputs + Vcc
		std::vector<double> s(Config->Samples);
		for (int n = 0; n < 9; ++n) { Signals[n] = s; }
	}

	void ProcessSignal() override
	{
		unsigned int Sigs = Y->Signals.size();
		for (unsigned int n = 0; n < Config->Samples; ++n) // !!! SIGNAL SIZES MUST BE THE SAME AS CONFIG SAMPLES | ALWAYS USE THE SAME CONFIG !!!
		{
			if (Sigs > 0)
			{
				//  		 nA						 nB											    16mA
				if ((Signals[A1][n] > 2) && (Signals[B1][n] > 2)) { Y->Signals[0][n] = NoiseSample(0.016, 0.006); }
				else { Y->Signals[0][n] = NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 1)
			{
				if ((Signals[A2][n] > 2) && (Signals[B2][n] > 2)) { Y->Signals[1][n] = NoiseSample(0.016, 0.006); }
				else { Y->Signals[1][n] = NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 2)
			{
				if ((Signals[A3][n] > 2) && (Signals[B3][n] > 2)) { Y->Signals[2][n] = NoiseSample(0.016, 0.006); }
				else { Y->Signals[2][n] = NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 3)
			{
				if ((Signals[A4][n] > 2) && (Signals[B4][n] > 2)) { Y->Signals[3][n] = NoiseSample(0.016, 0.006); }
				else { Y->Signals[3][n] = NoiseSample(5.125, Config->NoiseGain); }
			}
		}
		Y->ProcessSignal();
	}
};

class TTL_SN7400_FourNAND
{
public:
	
	std::string GetOuts(std::string In) 
	{
		std::string O;
		for (int n = 0; n < In.size(); ++n)
		{
						  // unused 4321 Y
			char Y = 15;  //   0000 1111
					   // nB			   nA
			if ((In[n] & 0x2) && (In[n] & 0x1)) { Y -= 1; }   // Y = 0000 1110 = 14
			if ((In[n] & 0x8) && (In[n] & 0x4)) { Y -= 2; }   // Y = 0000 1101 = 13
			if ((In[n] & 0x20) && (In[n] & 0x10)) { Y -= 4; } // Y = 0000 1011 = 11
			if ((In[n] & 0x80) && (In[n] & 0x40)) { Y -= 8; } // Y = 0000 0111 = 7  // MAYBE I CAN USE A SINGLE CHAR WITH AND AND DELETE ALL THOSE IFS
			O.push_back(Y);
			// RESULTS (based on image):
			// (3 | 7 | 11) + 16 * (Row - 1) // 15 + 16 * (Row - 1)
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
		ofstream O("!TTLSN7400.bin", ios::binary);
		if (O.is_open()) { O.write((char*)&s[0], s.size()); }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}

	// DUMP A STRING RESULT (EACH CHAR BIT CORRESPONDS TO: B4A4B3A3B2A2B1A1):
	void GetSequence(std::string s)
	{
		s = GetOuts(s);
		ofstream O("!TTLSN7400.bin", ios::binary); // In fact, it could maybe be text-mode, since the string is in binary anyway
		if (O.is_open()) { O.write((char*)&s[0], s.size()); }
		else { std::cout << "\nCouldn't open file!\n"; }
		O.close();
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_