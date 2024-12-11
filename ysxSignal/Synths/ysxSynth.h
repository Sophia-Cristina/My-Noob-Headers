#pragma once

#ifndef YSXSYNTH_H
#define YSXSYNTH_H

#include "ysxSignal/ysxSignal.h"
#include <random>

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
Glossary:
A = A.ttack; D = D.ecay; S = S.ustain; R = R.elease;
AD = A.ttack D.ecay. A system where 'A' is a percentage of the playing time, and 'D' the end gain;
 ~ Ex.: to 15, A = 7; D = 7;
 ~ Until 0.467 seconds, there will happen the A.ttack.
 ~ After that, signal loses gain until D.ecay, the end gain would be 0.467;
F = F.loat, F.lag, F.requency; // Or something else if i miss. 'Freq' is mostly used, as the main synth class have it for inheritance
FFT = F.ast-F.ourier-T.ransform;
Flt32 = float; // If a data type will be read as a 32-bit-float, *probably* something that will be scaled to a range from -1 to 1, or 0 to 1 (or 2)
pSomething = probably 'the p.ower' or 'a p.ower' or 'iterator' or 'p.ointer' of 'Something'; // Ex.: pAmp = Amplifaction controlled by an exponential expression
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
template <class SIGTYPE>
double ysxSIG_KickSmp(double x, double Freq, double pFreq, double pAmp, double Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	double g = x < Atk ? x / Atk : 1;
	double y = sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g;
	if (std::is_floating_point<SIGTYPE>::value) { return(y); }
	return((SIGTYPE)((y + 1) * (pow(256, sizeof(SIGTYPE)) - 1) * 0.5));
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

// ############################
// ####### SYNTHS #######
#include "ysxSynthMath.h"
#include "ysxSynthKicks.h"
#include "ysxSynthOSC.h"
#include "ysxSynthMisc.h"
#include "ysxSynthData.h"
#include "ysxSynthEmu.h"
#include "Projects/ysxSynthProjects.h"
#include "ysxSynthSpecial.h" // Should always be the last
// ############################

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_
