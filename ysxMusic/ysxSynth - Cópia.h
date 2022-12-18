#pragma once

#ifndef YSXSYNTH_H
#define YSXSYNTH_H
// Time for some synths should be included from 'ysxSDLAudio.h'
// UNCOMMENT IF YOU NEED, BUT YOU SHOULD INCLUDE IT BY YOURSELF
// TO AVOID MISTAKES WITH OTHER HEADERS:
 #include "ysxplg/ysxSignal.h"

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
double KickSmpD(double x, double Freq, double pFreq, double pAmp, double Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
float KickSmpF(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp) * g);
}
uint8_t KickSmpU8(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 127.5 * g);
}
uint16_t KickSmpU16(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 32767.5 * g);
}
uint32_t KickSmpU32(float x, float Freq, float pFreq, float pAmp, float Atk, double sec = 1)
{
	if (sec <= 0) { sec = 1; } if (x < 0) { x *= -1; }
	if (x > sec) { x = (x - floor(x)) - (sec - floor(sec)); }
	float g = x < Atk ? x / Atk : 1;
	return(((sin(x * (Freq * TAU * pow(1 - x / sec, pFreq))) * pow(1 - x / sec, pAmp)) + 1) * 2147483647.5 * g);
}

// GENERATE A KICK BUFFER, USE BYTES 1, 2 OR 4:
std::vector<uint8_t> KickSmpBuf(uint32_t Size, uint32_t SRate, uint8_t Bytes, float Freq, float pFreq, float pAmp, float Atk)
{
	if (Atk > 1) { Atk = 1; } if (Atk < 0) { Atk = 0; }
	uint32_t BSize = Size * Bytes, ASize = BSize * Atk;
	std::vector<uint8_t> B(BSize);
	
	if (Bytes == 4 || Bytes == 2 || Bytes == 1)
	{
		for (int n = 0; n < BSize; n += Bytes)
		{
			double x = (double)n / SRate;
			double b = sin(x * Freq * TAU * pow(1 - x, pFreq)) * pow(1 - x, pAmp);
			if (n < ASize) { b *= ((double)n / ASize); }
			if (Bytes == 4)	{ uint32_t a = (b + 1) * 2147483647.5; memcpy(&B[0], &a, Bytes); }
			else if (Bytes == 2) { uint16_t a = (b + 1) * 32767.5; memcpy(&B[0], &a, Bytes); }
			else { B[n] = (b + 1) * 127.5; }
		}
	}
	else { std::cout << "Sorry, for now, this only supports '1', '2' and '4' bytes format!\n"; }
	return(B);
}

// #################################################
// ####### INSTRUMENTS FOR 'SYNTH SIGNAL' INHERITANCE
// #################################################

// SYNTH SIGNAL CLASS, CHECK 'SigStream' FOR MORE INFORMATION:
template<class T_, uint8_t Voices> class SigSynth : public SigStream<T_, Voices>
{
public:
	// It is public, so you can do crazy tricks with this, BUT this might be dangerous if you don't reset every place that uses 'Voices'!
	// x = note; y = velocity
	std::vector<Point<uint8_t>> MIDI = std::vector<Point<uint8_t>>::vector(Voices);
	uint8_t V = 0; // Voice for the counter, ex.: C[V]; MIDI[V].x;
	float Freq = 1;
	//SigSynth() { }
	//~SigSynth() { }
};

// EASY VELOCITY FORMULA (VEL_VOICE / 127):
#define IO_MIDI_V (MIDI[V].y * 0.007874015748031496)

// #################################################

// KICK IO:
template<uint8_t Voices> class IO_Kick : public SigSynth<float, Voices>
{
public:
	float g = 1, pFreq = 0.75, pAmp = 0.33, Atk = 0.05;

	float IO(float x) override
	{
		//if (std::is_floating_point<T_>::value)
		//{
			if (x < Atk && Atk != 0) { g = (MIDI[V].y * 0.007874015748031496) * x / Atk; }
			x = sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * g;
		//}
		
		return(x);
	}
};

// KICK THAT USES FEW BYTES:
template<uint8_t Voices> class IO_KickMini : public SigSynth<float, Voices>
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
		if (x < (AtkSec >> 4) / 15.0 && (AtkSec >> 4) / 15.0 != 0) { g =  IO_MIDI_V * x / ((AtkSec >> 4) / 15.0); }
		x = sin(x * Freq * TAU * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA >> 4) / 15.0)) * pow(1 - x / ((AtkSec & 15) / 45.0), (PFPA & 15) / 15.0) * g;
		
		return(x);
	}
};

// KICK THAT USES EVEN FEWER BYTES (WORK IN PROGRESS):
// 'x' = '0 to 255' is '0 to 2*PI'.
// 'g'ain '0 to 255' is as '0 to 1'.
template<uint8_t Voices> class IO_KickMicro : public SigStream<uint8_t, Voices> // !!! WIP !!!
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
		ui8 = sin(0.0246399 * MtoFMini(MIDI) * ui8 * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA >> 4))) // WOLFRAM ALPHA
			* 0.00392157 * g * pow(1 - 0.176471 * ui8 / (AtkSec & 15), 0.0666667 * (PFPA & 15));
		return(ui8);
	}
};


// KICK INSTRUMENT, SIN-TRI-RECT:
template<uint8_t Voices> class IO_KickSTR : public SigSynth<float, Voices>// : public iopSec
{
private:
	float g = 0;
public:
	float RatioT = 1, RatioR = 1, pFreq = 1, pAmp = 1, Atk = 0.05;

	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if ((float)(Size - C[V]) < Atk * Size && Atk > 0) { g = IO_MIDI_V * (float)(Size - C[V]) / (Atk * Size); } else { g = IO_MIDI_V; }
		x = (sin(x * Freq * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			tri(x * Freq * RatioT * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3 +
			rect(x * Freq * RatioR * TAU * pow(1 - (float)(Size - C[V]) / Size, pFreq)) * pow(1 - (float)(Size - C[V]) / Size, pAmp) * 0.3) * g;
		//std::cout << "x: " << x << '\n';
		if (C[V] <= 0) { x = 0; } // Ok, time to cheat!
		return(x);
	}
};

// #################################################
// ####### OSCILLATORS #######

// SIMPLE OSCILLATOR:
template<uint8_t Voices> class IO_SimpleOSC : public SigSynth<float, Voices>
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
		return(y * IO_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY:
template<uint8_t Voices> class IO_OSC_AD : public SigSynth<float, Voices>
{
private:
	float y = 0; uint8_t n = 0;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	
	// USE TURNS! Preferably 32b:
	float IO(float x) override
	{
		if (F & 15 == 0) { F += 1; }
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
		return(y * IO_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, AND A FM THAT MULTIPLIES THE FREQUENCY:
template<uint8_t Voices> class IO_OSC_AD_FMMult : public SigSynth<float, Voices>
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
		if (F & 15 == 0) { F += 1; }
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
		return(y * IO_MIDI_V);
	}
};

// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, AND A FM THAT SUMS WITH THE FREQUENCY:
template<uint8_t Voices> class IO_OSC_AD_FMSum : public SigSynth<float, Voices>
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
		if (F & 15 == 0) { F += 1; }
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
		return(y * IO_MIDI_V);
	}
};

// CIRCLES BY CHORD SYNTH:
// 'D' (diameter of the first circle) should be the MIDI note.
// 'Cs' means "Circles", and it should have at least 1, which in fact means three circles,
// it is the amount of circles that will create the chord circle, and it is an 'ui8'.
template<uint8_t Voices> class IO_CCRDSYNTH : public SigSynth<float, Voices>
{
private:
	float D1 = 1, D2 = 1;
	float y = 0, h = 1; // By cord: h = (8 * r - (c * c) / h) * 0.25
public:
	uint8_t Cs = 1; bool Type = false;
	float Ratio = 0.9;
	uint8_t AD = 0;

	IO_CCRDSYNTH(uint8_t SetCs = 1, bool SetType = false, float SetRatio = 0.9, uint8_t SetAD = 0)
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
		y /= (Cs + 1) * 0.5;// * 2.0;

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
		return(y * IO_MIDI_V);
	}
};

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_