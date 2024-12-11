#pragma once

#ifndef YSXSYNTHKICK_H
#define YSXSYNTHKICK_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Kick synths or alike...
// #####################

// #################################################

// KICK SINE SYNTH:
class ysxSIG_KickSine : public ysxSIG_Synth<float>
{
public:
	float y = 0, g = 1, pFreq = 0.75, pAmp = 0.33, Atk = 0.05;

	float IO(float x) override
	{
		if ((float)(Size - C[V]) / Size < Atk && Atk != 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / (Atk * Size); }
		else { g = ysxSIG_MIDI_V; }
		y = sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * g;
		return(y);
	}
};

// KICK THAT USES FEW BYTES:
class ysxSIG_KickMini : public ysxSIG_Synth<float>
{
private:
	float y = 0, g = 0;
public:
	uint8_t PFPA = 8; // 15 levels of power, 0xF0 = pFreq; 0x0F = pAmp
	uint8_t AtkSec = 1; // 15 levels of: 0xF0 = Attack; 0x0F = sec / 3; 5 seconds max

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((AtkSec & 15) == 0) { ++AtkSec; } if (x < 0) { x *= -1; }
		if (x > (AtkSec & 15) / 45.0) { x = (x - floor(x)) - ((AtkSec & 15) / 45.0 - floor((AtkSec & 15) / 45.0)); }
		if (x < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / ((AtkSec >> 4) / 15.0); }
		y = sin(x * Freq * TAU * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0)) * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * g;

		return(y);
	}
};

// KICK THAT USES EVEN FEWER BYTES (WORK IN PROGRESS):
// 'x' = '0 to 255' is '0 to 2*PI'.
// 'g'ain '0 to 255' is as '0 to 1'.
class ysxSIG_KickMicro : public ysxSIG_Stream<uint8_t> // !!! WIP !!!
{
private:
	uint8_t y = 0, g = 0;
public:
	// MIDI note | 15 levels of power, 0xF0 = pFreq; 0x0F = pAmp | 15 levels of: F0 = Atk; 0F = sec / 3; 5 sec max
	uint8_t MIDI = 1, PFPA = 8, AtkSec = 1;

	// USE TURNS! Preferably 32b:
	uint8_t IO(uint8_t ui8) override
	{
		if ((AtkSec & 15) == 0) { ++AtkSec; }
		//if ((ui8 / 255.0) > (AtkSec & 15) / 45.0) { ui8 = ((ui8 / 255.0) - floor((ui8 / 255.0))) - ((AtkSec & 15) / 45.0 - floor((AtkSec & 15) / 45.0)); }
		//if (ui8 < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g = ui8 / ((AtkSec >> 4) / 15.0); }
		if (ui8 > (AtkSec & 15) * 17) { ui8 %= (AtkSec & 15) * 17; }
		if (ui8 < (AtkSec >> 4) * 17 && AtkSec >> 4 != 0) { g = (AtkSec >> 4) * 17; }
		//ui8 = sin((ui8 / 255.0) * MtoFMini(MIDI) * TAU * pow(1 - (ui8 / 255.0) / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0))
		//	* pow(1 - (ui8 / 255.0) / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * (g / 255.0);
		y = sin(0.0246399 * ysxMUS_MtoFMini(MIDI) * ui8 * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA >> 4))) // WOLFRAM ALPHA
			* 0.00392157 * g * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA & 15));
		return(y);
	}
};

// KICK INSTRUMENT, SIN-TRI-RECT:
class ysxSIG_KickSTR : public ysxSIG_Synth<float>
{
private:
	float y = 0, g = 0;
public:
	float RatioT = 1, RatioR = 1, pFreq = 1, pAmp = 1, Atk = 0.05;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((float)(Size - C[V]) < Atk * Size && Atk > 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / (Atk * Size); }
		else { g = ysxSIG_MIDI_V; }
		y = (sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			tri(x * Freq * RatioT * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			rect(x * Freq * RatioR * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3) * g;
		//std::cout << "Y: " << y << '\n';
		//std::cout << "PFREQ: " << pow(1 - (float)(Size - C[V]) / Size, pFreq) << '\n';
		return(y);
	}
};

#endif
