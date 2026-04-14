#pragma once

#ifndef YSXSIGEFX_H
#define YSXSIGEFX_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Signal effects, like, delay, reverb and etc.
// #####################

// #################################################

// #####################
// BASIC ONES:
// #####################


// ####### MATH BETWEEN SIGNALS #######

// DELAY A SIGNAL WITH FEEDBACK:
#include "Synths/ysxSynth.h"
//template<class T_>
class ysxSIG_EFX_DelayFB : public ysxSIG_Synth<float> //public ysxSIG_Stream<float> //public ysxSIG_Stream<T_>
{
private:
	//T_ y = 0;
	float y = 0;
	size_t Play = 0, Write = 0; // Actual sample to play or write

public:
	//ysxSIG_Stream<T_>* Sig;
	//std::vector<T_> DelayBuf; // Aka 'delay line'
	ysxSIG_Stream<float>* Sig;
	std::vector<float> DelayBuf; // Aka 'delay line'
	size_t DelaySize = 0; size_t Samples = 0; // Samples to delay, like 'ms' for delay time: float ms = 100
	size_t Bigger = 0;
	float FB = 0.75; // Feedback

	// #####################

	/* CREATE NEW DELAY LINE:
	Re-create 'DelayBuf' with samples based on 'SRate' (Sample Rate) and
	'DelayLinems', which is the amount of ms the 'DelayBuf' will be able to carry.*/
	void NewDelayLine(uint32_t SRate, double DelayLinems)
	{
		DelaySize = SRate * DelayLinems / 1000; // Ex.: 44100, 5000; 'DelaySize = 44100 * 5000 / 1000 = 220500'
		//std::vector<T_> New(DelaySize);
		std::vector<float> New(DelaySize);
		DelayBuf = New;
		//DelayBuf = std::vector<T_>::vector(DelaySize);
		for (size_t n = 0; n < DelaySize; ++n) { DelayBuf[n] = 0; } // Change when fixing it to accept 'T_'
		Size = DelaySize - 1;
	}

	void ChangeDelayTime(uint32_t SRate, double ms)
	{
		Samples = SRate * ms / 1000;
		if (Samples > DelayBuf.size() - 1) { Samples = DelayBuf.size() - 1; }
	}

	// #####################

	//T_ IO(T_ x) override
	float IO(float x) override
	{
		if (Sig && DelayBuf.size() > 0 && Samples > 0)
		{
			Sig->V = V;
			Write = Play + Samples; Write %= DelaySize;
			if (C[V] == DelaySize - 1) { Sig->C[V] = Sig->Size; }

			// There is no need for multiple voices in delay, and long delays will take all the voice's buffer.
			// Delay just read from the Delay Line / Buffer, and so it needs only one voice, and this is better to avoid problems with a big buffer size.
			for (size_t n = 0; n < C.size(); ++n)
			{
				std::cout << "C[" << n << "] = " << C[n] << " | ";
				if (n == 0 || C[n] > Bigger) { Bigger = C[n]; }
				if (!Sig->C[n]) { C[n] = 0; }
				std::cout << "NEW: " << C[n] << "\n";
			}
			C[V] = Bigger;

			if (Sig->C[V] > 0) // If there is samples in the instrument to play, so play the instrument
			{
				if (C[V] < 1) {	C[V] = Sig->C[V]; } // Avoid halting instrument by using instrument's samples left in case the delay's samples are over
				Sig->C[V] = Sig->Size - (DelaySize - 1 - C[V]); // Set instrument counter, since delay line very likely will have a different time
				y = Sig->IO(x); DelayBuf[Write] = y; // Copy signal sample to delay line
				//y = Sig->IO(x);
				y = y + DelayBuf[Play]; // Play sample togheter with delay (if there is any)
				DelayBuf[Write] += DelayBuf[Play] * FB; // Feedback line
			}
			else // If the instrument played all its 'Size', then it only plays the delay feedback
			{
				DelayBuf[Write] = 0;
				y = DelayBuf[Play];
				DelayBuf[Write] += DelayBuf[Play] * FB;
			}
			++Play; Play %= DelaySize;
		}
		return(y);
	}
};


// #################################################
// #################################################
// #################################################


#endif
