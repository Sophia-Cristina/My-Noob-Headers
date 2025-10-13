#pragma once

#ifndef YSXSYNTHMOD_H
#define YSXSYNTHMOD_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Signal Modulators.
// #####################

// #################################################

// #####################
// MODULATIONS:
// #####################


// SIMPLE OSCILLATOR MADE FOR MODULATIONS:
class ysxSIG_OSCMod : public ysxSIG_Synth<float>
{
private:
	float y = 0;
	uint8_t n = 0;
public:
	uint8_t OSCs = 255; // 0000 1111 saw, rect, tri, sine
	float Phase[4] = { 0, 0, 0, 0 };

	float IO(float x) override
	{
		if (OSCs == 0) { OSCs = 1; }
		x *= 6.283185; y = 0; n = 0;
		if (OSCs & 1) { y += (sin(Freq * x + 6.283185 * Phase[0]) + 1) * 0.5; ++n; }
		if (OSCs & 2) { y += (tri(Freq * x + 6.283185 * Phase[1]) + 1) * 0.5; ++n; }
		if (OSCs & 4) { y += (rect(Freq * x, Phase[2]) + 1) * 0.5; ++n; }
		if (OSCs & 8) { y += (saw(Freq * x + 6.283185 * Phase[3]) + 1) * 0.5; ++n; }
		if (n == 0) { n = 1; } // Just for safety
		y /= n;
		return(y * ysxSIG_MIDI_V);
	}
};


// AM A SYNTH WITH ANOTHER SYNTH:
// Soon to change to 'ysxSIG_Stream'.
class ysxSIG_MOD_AMSynth : public ysxSIG_Synth<float>
{
private:
	float y = 0, AM = 0, z = 0;
public:
	ysxSIG_Stream<float>* SigMod; // Cast from a 'ysxSIG_Synth' if it is a Synth
	ysxSIG_Synth<float>* SigCarry;
	float Floor = 0;
	/* FLAGS:
	 The signal engine works with a 'V'oice and a 'C[V]' counter. Since this is a modulator, you may not desire
	 to change 'V' or to use a counter. If you don't know what to do, just leave it this way.
	 Map:
	 mmmm cccc = 0xF0, 0x0F;
	 And also:
	 vvcc vvcc = 0xC0, 0x30, 0x0C, 0x03;
	 & 0xC0 -> Change 'V': 'SigMod->V = V'; & 0x30 -> Hit 'SigMod''s counter: 'SigMod->C[V] = C[V]';
	 & 0x0C -> Change 'V': 'SigCarry->V = V'; & 0x03 -> Hit 'SigCarry''s counter: 'SigCarry->C[V] = C[V]';*/
	uint8_t Flags = 0xff;

	float IO(float x) override
	{
		if (SigMod && SigCarry)
		{
			if (Flags & 0xC0) { SigMod->V = V; } if (Flags & 0x0C) { SigCarry->V = V; }
			if (Flags & 0x30) { SigMod->C[V] = C[V]; } if (Flags & 0x03) { SigCarry->C[V] = C[V]; }
			AM = SigMod->IO(x);
			y = SigCarry->IO(x);
			y = (Floor * y) + (y - Floor * y) * AM;
		}
		return(y * ysxSIG_MIDI_V);
	}
};

// FM A SYNTH WITH ANOTHER SYNTH:
class ysxSIG_MOD_FMSynth : public ysxSIG_Synth<float>
{
private:
	float y = 0, FM = 0;
public:
	ysxSIG_Synth<float>* SigMod;
	ysxSIG_Synth<float>* SigCarry;
	float Floor = 0;
	uint8_t Flags = 0xff; // Check 'AMSynth'

	float IO(float x) override
	{
		if (SigMod && SigCarry)
		{
			if (Flags & 0xC0) { SigMod->V = V; } if (Flags & 0x0C) { SigCarry->V = V; }
			if (Flags & 0x30) { SigMod->C[V] = C[V]; } if (Flags & 0x03) { SigCarry->C[V] = C[V]; }
			FM = SigMod->IO(x); Freq = SigCarry->Freq;
			SigCarry->Freq = (Floor * SigCarry->Freq) + (SigCarry->Freq - Floor * SigCarry->Freq) * FM;
			y = SigCarry->IO(x);
			SigCarry->Freq = Freq;
		}
		return(y * ysxSIG_MIDI_V);
	}
};

#endif
