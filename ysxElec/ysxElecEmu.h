#pragma once

#ifndef YSXELECEMU_H
#define YSXELECEMU_H

#include "ysxElectr.h"

// #####################
// ####### By Sophia Cristina
// ####### Electrical components emulation, like IC
// #####################

// #################################################
// REFERENCES:
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################
// ##############  ##############

// #################################################
/* ############## SN7400 FOUR NAND ############## // [T1]
https://en.wikipedia.org/wiki/7400-series_integrated_circuits
	      __________
	1A  -|1 #     14|- 4Y
	1B  -|2       13|- 4B
	1Y  -|3  SN   12|- 4A
	Vcc -|4	7400  11|- GND
	2Y  -|5	      10|- 3B = 3 In
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
class ysxELEC_TTL_SN7400 : public ysxELEC_Component
{
public:

	ysxELEC_CompConfig* Config;
	enum Pins { A1, B1, A2, B2, A3, B3, A4, B4, Vcc }; // Work on Vcc yet to be done!
	ysxELEC_Wire* Y; // Outputs are in numerical order. IDEAL that you add 4 signals!
	ysxELEC_Wire* GND; // You can point GND wire signal to its own input

	ysxELEC_TTL_SN7400(ysxELEC_CompConfig& InConfig)
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
				if ((Signals[A1][n] > 2) && (Signals[B1][n] > 2)) { Y->Signals[0][n] = ysxSIG_NoiseSample(0.016, 0.006); }
				else { Y->Signals[0][n] = ysxSIG_NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 1)
			{
				if ((Signals[A2][n] > 2) && (Signals[B2][n] > 2)) { Y->Signals[1][n] = ysxSIG_NoiseSample(0.016, 0.006); }
				else { Y->Signals[1][n] = ysxSIG_NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 2)
			{
				if ((Signals[A3][n] > 2) && (Signals[B3][n] > 2)) { Y->Signals[2][n] = ysxSIG_NoiseSample(0.016, 0.006); }
				else { Y->Signals[2][n] = ysxSIG_NoiseSample(5.125, Config->NoiseGain); }
			}
			if (Sigs > 3)
			{
				if ((Signals[A4][n] > 2) && (Signals[B4][n] > 2)) { Y->Signals[3][n] = ysxSIG_NoiseSample(0.016, 0.006); }
				else { Y->Signals[3][n] = ysxSIG_NoiseSample(5.125, Config->NoiseGain); }
			}
		}
		Y->ProcessSignal();
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_

/*
class A
{
public:

// #################################################

	A()
	{
	}

	~A()
	{
	}
};
*/