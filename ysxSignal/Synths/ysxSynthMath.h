#pragma once

#ifndef YSXSYNTHMATH_H
#define YSXSYNTHMATH_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Signal maths.
// #####################

// #################################################

// !!! ATTENTION: Be sure that the size of these objects are the same as the size of the bigger signal.

// #####################
// ARITHMETIC:
// #####################

// ADD MULTIPLE SIGNALS:

class ysxSIG_MATH_Add : public ysxSIG_Synth<float>
{
public:
	std::vector<ysxSIG_Synth<float>*> Sigs;
	float y = 0;

	float IO(float x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n) { Sigs[n]->V = V; y += Sigs[n]->IO(x); --Sigs[n]->C[V]; }
		}
	}
};


// SUB MULTIPLE SIGNALS:
class ysxSIG_MATH_Sub : public ysxSIG_Synth<float>
{
public:
	std::vector<ysxSIG_Synth<float>*> Sigs;
	float y = 0;

	float IO(float x) override
	{
		if (Sigs.size() > 0)
		{
			for (size_t n = 0; n < Sigs.size(); ++n) { Sigs[n]->V = V; y -= Sigs[n]->IO(x); --Sigs[n]->C[V]; }
		}
	}
};


#endif
