#pragma once

#ifndef YSXSYNTHOSC_H
#define YSXSYNTHOSC_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Oscillators or alike...
// #####################

// #################################################


// !!! ATTENTION: Soon to change 'Freq' to MtoF.


// #####################
// SIMPLE OSCS:
// #####################

// SIMPLE OSCILLATOR:
class ysxSIG_OSC : public ysxSIG_Synth<float>
{
public:
	float y = 0;
	uint8_t n = 0;
	uint8_t F = 1; // Flags, 1111 15-levels PW, or phase for others than rect | 1111 saw, rect, tri, sine

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

class ysxSIG_OSC_SINEPULSE_AD : public ysxSIG_Synth<float>
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


// OSCILLATOR WITH 15 LEVELS OF ATTACK AND DECAY, USING GENERAL FM FORMULA (WHICH IS IN FACT A PHASE MODULATOR):
// FORM.: signal(sin(freq_m * x) + freq_c * x)
class ysxSIG_OSC_AD_AM : public ysxSIG_Synth<float>
{
private:
	float y = 0; uint8_t n = 0;
	float AM = 1;
public:
	uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;
	uint8_t F = 1; // Flags, 1111 15-levels PW or phase for non-rect | 1111 saw, rect, tri, sine
	float AMFreq = 1, AMAmp = 1;

	float IO(float x) override
	{
		if ((F & 15) == 0) { F += 1; }
		y = 0; n = 0;
		fabs(AMAmp) < 1 ? AM = sin(x * 6.283185 * AMFreq) * AMAmp + (1 - AMAmp) : AM = sin(x * 6.283185 * AMFreq) * AMAmp;
		
		if (F & 1) { y += sin(x * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0) * AM; ++n; }
		if (F & 2) { y += tri(x * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0) * AM; ++n; }
		if (F & 4) { y += rect(x * Freq * 6.283185, (F >> 4) / 15.0) * AM; ++n; }
		if (F & 8) { y += saw(x * Freq * 6.283185 + 6.283185 * (F >> 4) / 15.0) * AM; ++n; }
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

#endif
