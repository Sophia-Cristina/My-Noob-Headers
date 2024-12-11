#pragma once

#ifndef YSXSYNTHSPECIAL_H
#define YSXSYNTHSPECIAL_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Signal processors for multiple functions.
// #####################

// #################################################

// #####################
// COMPOSITE SYNTHS:
// Re-trigger the same synth multiple times, then sum and normalize the result.
// Be sure that the size of these objects are the same as the size of the bigger signal.
// #####################

// COMPOSITE SYNTH FREQ:
// Sum all the outputs of the same synth for each item in the 'Freqs' vector index.
class ysxSIG_SPCL_CompositeFreq : public ysxSIG_Synth<float>
{
public:
	std::vector<float> Freqs = std::vector<float>::vector(1);
	ysxSIG_Synth<float>* Synth = nullptr;
	float y = 0;
	size_t n = 0;

	void FreqReGenVector(uint16_t TotalFreqs) { Freqs = std::vector<float>::vector(TotalFreqs); } // New clean array

	float IO(float x) override
	{
		Synth->V = V;
		if (Synth && Freqs.size())
		{
			for (n = 0; n < Freqs.size(); ++n)
			{
				Synth->Freq = Freqs[n];
				y += Synth->IO(x);
			}
			y /= Freqs.size();
		}
		--Synth->C[V];
		return(y);
	}
};

// COMPOSITE SYNTH FREQ:
// Sum all the outputs of the same synth for each item in the 'Configs' vector index.
template <class T_> class ysxSIG_SPCL_CompositeConfig : public ysxSIG_Synth<float>
{
	uint32_t Bigger = 0, Sum = 0;
public:
	std::vector<float> Freqs;
	std::vector<ysxBYTE_PointAndVector<T_>> Configs;
	ysxSIG_Synth<float>* Synth = nullptr;
	float y = 0;
	size_t n = 0, m = 0;

	void FreqReGenVector(uint16_t TotalFreqs) { Freqs = std::vector<float>::vector(TotalFreqs); } // New clean array

	float IO(float x) override
	{
		Synth->V = V;
		if (Synth && Configs.size())
		{
			Bigger = Freqs.size();
			for (n = 0; n < Configs.size(); ++n)
			{
				if (Bigger < Configs[n].Vec.size()) { Bigger = Configs[n].Vec.size(); }
				Sum += Configs[n].Vec.size();
			}
			Sum += Freqs.size();

			for (n = 0; n < Bigger; ++n)
			{
				for (m = 0; m < Configs.size(); ++m)
				{
					if (n < Configs[m].Vec.size())
					{
						*(T_*)Configs[m].p = Configs[m].Vec[n];
					}
					if (n < Freqs.size())
					{
						Synth->Freq = Freqs[n];
					}
					y += Synth->IO(x);
				}
			}
			if (Sum) { y /= Sum; }
		}
		Bigger = 0; Sum = 0; n = 0;
		--Synth->C[V];
		return(y);
	}
};


// #####################
// AAA OSCS:
// Aaaaaaa!
// #####################


#endif
