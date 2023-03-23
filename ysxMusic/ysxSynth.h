#pragma once

#ifndef YSXSYNTH_H
#define YSXSYNTH_H
// Time for some synths should be included from 'ysxSDLAudio.h'
// UNCOMMENT IF YOU NEED, BUT YOU SHOULD INCLUDE IT BY YOURSELF
// TO AVOID MISTAKES WITH OTHER HEADERS:
//#include "ysxplg/ysxSignal.h"

// #####################
// ####### By Sophia Cristina
// ####### Codes about synth and related, for SDL Audio
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* PAY ATTENTION to any change that may affect 'ysxElectr.h' classes, since electronic devices normally have alike terms to music devices;
// !!!!!!!	* HUGE: SOON TO ADD TEMPLATE TO LOT OF FUNCTIONS HERE! And it might break old codes!
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

/*
Glos.:
A = A.ttack; D = D.ecay; S = S.ustain; R = R.elease;
AD = A.ttack.D.ecay. A system where 'A' is a percentage of the playing time, and 'D' the end gain;
 ~ Ex.: to 15, A = 7; D = 7;
 ~ Until 0.467 seconds, there will happen the A.ttack.
 ~ After that, signal loses gain until D.ecay, the end gain would be 0.467;
F = F.loat, F.lag, F.requency; // Or something else if i miss
FFT = F.ast-F.ourier-T.ransform;
Flt32 = float; // If a float, *probably* something from -1 to 1, or 0 to 1
pSomething = probably 'the p.ower' or 'a p.ower' or 'iterator' or 'p.ointer' of 'Something';
PW = P.ulse-W.idth;
SRate = S.ample Rate;
BS = B.lock S.ize;
*/

// #################################################
// REFERENCES:
// [1] The Computer Music Tutorial - Curtis Roads
// #################################################

// #################################################
// ####### DRUM KIT #######

// KICK SAMPLE, Kick(x), HEHE:
// sin(x*Freq*TAU*((1 - x)^PF)) * (1 - x)^PA
// You can use bigger frequencies and changes in curves to make a hit or click sound.
double ysxSIG_KickSmpD(double x, double Freq, double pFreq, double pAmp, double Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
float ysxSIG_KickSmpF(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
uint8_t ysxSIG_KickSmpU8(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 127.5 * g);
}
uint16_t ysxSIG_KickSmpU16(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 32767.5 * g);
}
uint32_t ysxSIG_KickSmpU32(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 2147483647.5 * g);
}

// GENERATE A KICK BUFFER:
template <class T_> std::vector<uint8_t> ysxSIG_KickSmpBuf(uint32_t Size, uint32_t SRate, float Freq, float pFreq, float pAmp, float Atk)
{
	if (Atk > 1) { Atk = 1; } if (Atk < 0) { Atk = 0; }
	uint8_t Bytes = sizeof(T_);
	uint32_t BSize = Size * Bytes, ASize = BSize * Atk;
	std::vector<uint8_t> B(BSize);
	double x, y;
	size_t a;

	for (size_t n = 0; n < BSize; n += Bytes)
	{
		x = (double)n / SRate;
		y = sin(x * Freq * TAU * pow(1 - x, pFreq)) * pow(1 - x, pAmp);
		if (n < ASize) { y *= ((double)n / ASize); }
		if (Bytes == 1) { B[n] = (y + 1) * 127.5; }
		else { a = round((y + 1) * 0.5 * (pow(256, Bytes) - 1)); memcpy(&B[n], &a, Bytes); }
	}
	return(B);
}

// #################################################
// ####### INSTRUMENTS FOR 'SYNTH SIGNAL' INHERITANCE
// #################################################

/*ATTENTION: Take in mind that you might see some weird variables declared in strange ways, i'm doing
that to make it "compatible" (not sure if the right word) to what would be if that was emulating a
fantasy-hardware!
If there is a soldered memory device on a hardware which carries the variables, i wouldn't be able to
take it off and on whenever a function is used, the memory (as some sort of ROM, if not a ROM) in a
hardware would be fixed in place!*/

// SYNTH SIGNAL CLASS, CHECK 'ysxSIG_Stream' FOR MORE INFORMATION:
template<class T_> class ysxSIG_Synth : public ysxSIG_Stream<T_>
{
public:
	// It is public, so you can do crazy tricks with this, BUT this might be dangerous if you don't reset every place that uses 'Voices'!
	// x = note; y = velocity
	std::vector<Point<uint8_t>> MIDI;
	uint8_t V = 0; // Voice for the counter, ex.: C[V]; MIDI[V].x;
	float Freq = 1;
	//ysxSIG_Synth() { }
	//~ysxSIG_Synth() { }
};

template<class T_> void ysxSIG_SynthSetVoices(ysxSIG_Synth<T_>& Synth, uint8_t Voices)
{
	Synth.MIDI = std::vector<Point<uint8_t>>::vector(Voices);
	Synth.C = std::vector<uint32_t>::vector(Voices);
}
template<class T_> void ysxSIG_SynthSetVoices(ysxSIG_Synth<T_>& Synth, uint8_t Voices, uint8_t Note, uint8_t Vel)
{
	Synth.MIDI = std::vector<Point<uint8_t>>::vector(Voices);
	Synth.C = std::vector<uint32_t>::vector(Voices);
	for (uint8_t n = 0; n < Voices; ++n) { Synth.MIDI[n].x = Note; Synth.MIDI[n].y = Vel; }
}

// PROMPT FOR INSTRUMENT:
// POINTS TO A 'ysxSIG_Synth<Stream>' AND CREATES A BITWISE MUSIC PATTERN (MUSIC BAR):
template<class SigType, class PatSize>
struct ysxSIG_Instr { ysxSIG_Synth<SigType>* S; PatSize Ptrn; };

// EASY VELOCITY FORMULA (VEL_VOICE / 127):
#define ysxSIG_MIDI_V (MIDI[V].y * 0.007874015748031496)

// #################################################

// VST UTILS:
#ifdef YSXVST2_H

// LINK EFFECT VST TO AN INSTRUMENT:
template<const uint32_t SRATE, const uint32_t BUFSIZE, const uint8_t CHANNELS>
class ysxSIG_SynthVSTefx : public ysxSIG_Synth<float>
{
private:
	float y; // If "Music(x) = f(x)", then "Music(x) = y"
	uint32_t Count = 0; // Count until it fills the input signal buffer for the VST
	uint8_t TVSTs, TInstrs; // Total VSTs / Instruments. Shouldn't mess with it
	uint8_t n = 0, p = 0, I = 0;
	uint32_t m = 0;

public:
	// Add all instruments which you want to receive all efxs here!
	std::vector<ysxSIG_Synth<float>*> Instrs;
	std::vector<ysxVST2_Plugin<SRATE, BUFSIZE, CHANNELS>*> VST2s;
		
	// Point to main buffer used in the sound engine:
	// !!! This is for all kind of engines, i don't think i would make
	// possible to hack the buffer by the hardware i would use for 'MSEA1' !!!
	uint8_t* Buf;
	
	// Use the same you would use in "RAM->Gg":
	float* Gain = 0;

	float IO(float x) override
	{
		// At end of the buffer...
		if (Count >= BUFSIZE)
		{
			TVSTs = VST2s.size();
			for (p = 0; p < TVSTs; ++p) { VST2s[p]->ProcessAudio(); }
			for (p = 0; p < TVSTs; ++p)
			{
				for (n = 0; n < CHANNELS; ++n)
				{
					for (m = 0; m < BUFSIZE; ++m)
					{
						y = VST2s[p]->Outs[n][m] / ((float)CHANNELS == 0 ? 1 : CHANNELS);
						if (y > 1) { y = 1; } if (y < -1) { y = -1; } // Clip
						Buf[m] += round((y + 1) * 127.5);
					}
				}
			}
			Count = 0;
		}
		for (n = 0; n < CHANNELS; ++n)
		{
			for (I = 0; I < Instrs.size(); ++I)
			{
				y += Instrs[I]->IO(x) / (*Gain == 0 ? 1 : *Gain);
			}
			for (p = 0; p < TVSTs; ++p) { VST2s[p]->Ins[n][Count] = y; }
			y = 0;
		}
		++Count;
		return(0);
	}

	/*VST MAIN FORMULA: y += Instruments[I]->IO(x) / (*Gain == 0 ? 1 : *Gain);
	* VST BUFFER FORMULA: Buf[m] += round((y + 1) * 127.5);
	! IF YOU DON'T WANT TO OVERFLOW, BE SURE TO SET A CORRECT "Gain" !
	VST2s.push_back(SetVST2);
	Buffer = SetBuffer;
	Gain = SetGain;
	
	'Gain' is a pointer because it would be easier to automate if you operate outside of the class in my opinion:*/
	ysxSIG_SynthVSTefx(ysxVST2_Plugin<SRATE, BUFSIZE, CHANNELS>* SetVST2, uint8_t* SetBuffer, float* SetGain)
	{
		VST2s.push_back(SetVST2);
		Buf = SetBuffer;
		Gain = SetGain;
	}

};

// USE VST INSTRUMENT:
template<class T_, const uint32_t SRATE, const uint32_t BUFSIZE, const uint8_t CHANNELS>
class ysxSIG_SynthVSTi : public ysxSIG_Stream<T_>
{
public:
	
	ysxVST2_Plugin<SRATE, BUFSIZE, CHANNELS>* VST2;

	ysxSIG_SynthVSTi(ysxVST2_Plugin<SRATE, BUFSIZE, CHANNELS>* SetVST2)
	{
	}
};
#endif

// #################################################

// KICK IO:
class ysxSIG_Kick : public ysxSIG_Synth<float>
{
public:
	float g = 1, pFreq = 0.75, pAmp = 0.33, Atk = 0.05;

	float IO(float x) override
	{
		//if (std::is_floating_point<T_>::value)
		//{
		if ((float)(Size - C[V]) / Size < Atk && Atk != 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / (Atk * Size); }
		else { g = ysxSIG_MIDI_V; }
		x = sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * g;
		//}
		return(x);
	}
};

// KICK THAT USES FEW BYTES:
class ysxSIG_KickMini : public ysxSIG_Synth<float>
{
private:
	float g = 0;
public:
	uint8_t PFPA = 8; // 15 levels of power, 0xF0 = pFreq; 0x0F = pAmp
	uint8_t AtkSec = 1; // 15 levels of: 0xF0 = Attack; 0x0F = sec / 3; 5 seconds max

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((AtkSec & 15) == 0) { ++AtkSec; } if (x < 0) { x *= -1; }
		if (x > (AtkSec & 15) / 45.0) { x = (x - floor(x)) - ((AtkSec & 15) / 45.0 - floor((AtkSec & 15) / 45.0)); }
		if (x < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / ((AtkSec >> 4) / 15.0); }
		x = sin(x * Freq * TAU * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0)) * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * g;

		return(x);
	}
};

// KICK THAT USES EVEN FEWER BYTES (WORK IN PROGRESS):
// 'x' = '0 to 255' is '0 to 2*PI'.
// 'g'ain '0 to 255' is as '0 to 1'.
class ysxSIG_KickMicro : public ysxSIG_Stream<uint8_t> // !!! WIP !!!
{
private:
	uint8_t g = 0;
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
		ui8 = sin(0.0246399 * ysxMUS_MtoFMini(MIDI) * ui8 * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA >> 4))) // WOLFRAM ALPHA
			* 0.00392157 * g * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA & 15));
		return(ui8);
	}
};

// KICK INSTRUMENT, SIN-TRI-RECT:
class ysxSIG_KickSTR : public ysxSIG_Synth<float>
{
private:
	float g = 0;
public:
	float RatioT = 1, RatioR = 1, pFreq = 1, pAmp = 1, Atk = 0.05;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((float)(Size - C[V]) < Atk * Size && Atk > 0) { g = ysxSIG_MIDI_V * (float)(Size - C[V]) / (Atk * Size); }
		else { g = ysxSIG_MIDI_V; }
		x = (sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			tri(x * Freq * RatioT * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			rect(x * Freq * RatioR * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3) * g;
		//if (C[V] <= 0) { x = 0; } // Ok, time to cheat! // Old code, i think there is no need to that now...
		return(x);
	}
};

// #################################################
// ####### OSCILLATORS #######

// #####################
// SIMPLE OSCS:
// #####################

// SIMPLE OSCILLATOR:
class ysxSIG_SimpleOSC : public ysxSIG_Synth<float>
{
public:
	float y = 0;
	uint8_t n = 0;
	uint8_t F = 1; // Flags, 1111 15-levels PW, or phase for others than rect | 1111 saw, rect, tri, sine

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (F == 0) { F = 1; }
		x *= 6.283185; y = 0; n = 0;
		if (F & 1) { y += sin(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(Freq * x, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(Freq * x + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (n == 0) { n = 1; } // Just for safety
		y /= n;
		return(y * ysxSIG_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY:
class ysxSIG_OSC_AD : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0; //At = (AD >> 4) / 15.0; //std::cout << "At: " << At << '\n';
		if (F & 1) { y += sin(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(Freq * x * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (n == 0) { ++n; } // Just for safety
		y /= n;
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				/* Wolfram in:
				(d * y * ((s * 0.039216 - a * s / 3825.0 - (x - a * s / 3825.0)) / (s * 0.039216 - a * s / 3825.0))) + y * (1 - d);*/
				//y = (y * (AD & 15) / 15.0) * (((x - sec * 0.039216) / ((Size * (AD >> 4) / 15.0) - sec * 0.039216)) - 1) + y;
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

class ysxSIG_OSC_PULSE_AD : public ysxSIG_Synth<float>
{
private:
	float y = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	float pFreq = 0.75, pAmp = 0.33;
	float FloorFreq = 110;

	float IO(float x) override
	{
		y = 0;
		y = sin(x * Freq * TAU - ((Freq - FloorFreq) * pow(1 - (float)(Size - C[V]) / Size, pFreq))) * pow(1 - (float)(Size - C[V]) / Size, pAmp);
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);		
	}
};

// #####################
// AM OSCS:
// #####################

// #####################
// FM OSCS:
// #####################

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, USING GENERAL FM FORMULA (WHICH IS IN FACT A PHASE MODULATOR):
// FORM.: signal(sin(freq_m * x) + freq_c * x)
class ysxSIG_OSC_AD_PhaseFM : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	float FMFreq = 1, FMAmp = 1;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0;
		if (F & 1) { y += sin(sin(x * 6.283185 * FMFreq) * FMAmp + Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(sin(x * 6.283185 * FMFreq) * FMAmp + Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(sin(x * 6.283185 * FMFreq) * FMAmp + Freq * x * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(sin(x * 6.283185 * FMFreq) * FMAmp + Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (!n) { ++n; } y /= n;
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY:
// FORM.: sin(sin(freq_m * x) * freq_c * 2 * PI)
class ysxSIG_OSC_AD_FM_Mult : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	float FMFreq = 1, FMAmp = 1;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0;
		if (F & 1) { y += sin(sin(x * 6.283185 * FMFreq) * FMAmp * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(sin(x * 6.283185 * FMFreq) * FMAmp * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(sin(x * 6.283185 * FMFreq) * FMAmp * Freq * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(sin(x * 6.283185 * FMFreq) * FMAmp * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (!n) { ++n; } y /= n;
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, AND A FM INCREASES FREQ. BY TIME:
// FORM.: sin(sin(freq_m * x) * x * 2 * PI)
class ysxSIG_OSC_AD_Mult_FMMult : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	float FMFreq = 1;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0; //At = (AD >> 4) / 15.0; //std::cout << "At: " << At << '\n';
		if (F & 1) { y += sin(sin(x * 6.283185 * FMFreq) * Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri(sin(x * 6.283185 * FMFreq) * Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect(sin(x * 6.283185 * FMFreq) * Freq * x * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw(sin(x * 6.283185 * FMFreq) * Freq * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (n == 0) { ++n; } // Just for safety
		y /= n;
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, AND A FM THAT SUMS WITH THE FREQUENCY:
class ysxSIG_OSC_AD_Mult_FMSum : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	float FMFreq = 1, FMAmp = 1;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0;
		if (F & 1) { y += sin((sin(x * 6.283185 * FMFreq) * FMAmp + Freq) * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 2) { y += tri((sin(x * 6.283185 * FMFreq) * FMAmp + Freq) * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (F & 4) { y += rect((sin(x * 6.283185 * FMFreq) * FMAmp + Freq) * x * 6.283185, (F >> 4) / 15.0); ++n; }
		if (F & 8) { y += saw((sin(x * 6.283185 * FMFreq) * FMAmp + Freq) * x * 6.283185 + 6.283185 * (F >> 4) / 15.0); ++n; }
		if (!n) { ++n; } y /= n;
		if (Size)
		{
			if ((float)(Size - C[V]) < Size * (AD >> 4) / 15.0 && Size * (AD >> 4) / 15.0 != 0)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) / 15.0);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// #####################
// SPECIAL OSCS:
// Special experimentations with signals!
// #####################

// CIRCLES BY CHORD SYNTH:
// 'D' (diameter of the first circle) should be the MIDI note.
// 'Cs' means "Circles", and it should have at least 1, which in fact means three circles,
// it is the amount of circles that will create the chord circle, and it is an 'ui8'.
class ysxSIG_CCRDSYNTH : public ysxSIG_Synth<float>
{
private:
	float D1 = 1, D2 = 1;
	float y = 0, h = 1; // By cord: h = (8 * r - (c * c) / h) * 0.25
public:
	uint8_t Cs = 1; bool Type = false;
	float Ratio = 0.9;
	uint8_t AD = 0;

	ysxSIG_CCRDSYNTH(uint8_t SetCs = 1, bool SetType = false, float SetRatio = 0.9, uint8_t SetAD = 0)
	{
		Cs = SetCs; Type = SetType; Ratio = SetRatio; AD = SetAD;
	}

	float IO(float x) override
	{
		y = 0;
		if (Freq == 0) { Freq = 1; } if (Cs == 0) { Cs = 1; }
		D1 = Freq;
		// Sample:
		for (uint8_t n = 0; n < Cs; ++n)
		{
			D2 = D1 * Ratio; h = D2 * 0.5;
			y += sin(D1 * TAU * x);	y += sin(D2 * TAU * x);
			if (Type) { y *= sin(((D1 - D2) * sin(TAU * x) - D2 * sin(TAU * x * ((D1 - D2) / D2))) * TAU * x); }
			else { y *= sin((D1 - D2) * sin(TAU * x) - D2 * sin(TAU * x * ((D1 - D2) / D2))); }
			D1 = 2 * sqrt(h * (D1 - h));
		}
		//y /= (Cs + 1) * 0.5;// * 2.0;

		// Envelope:
		if (Size)
		{
			if ((Size - C[V]) < Size * (AD >> 4) * 0.066667 && AD >> 4)
			{
				y *= (float)(Size - C[V]) / (Size * (AD >> 4) * 0.066667);
			}
			else
			{
				y = (y * (AD & 15) * 0.066667) * (((float)(Size - C[V]) - Size * (AD >> 4) * 0.066667) / (Size - (Size * (AD >> 4) * 0.066667))) + y;
				y *= 0.5;
			}
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// #####################
// COMPLETE OSCS:
// What i mean with complete? Is that those are oscs trying to be alike one you would buy.
// Like a music equip or a VSTi.
// #####################

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_