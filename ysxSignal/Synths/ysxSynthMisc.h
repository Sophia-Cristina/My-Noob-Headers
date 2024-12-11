#pragma once

#ifndef YSXSYNTHMISC_H
#define YSXSYNTHMISC_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Things like noise or some other exotic type of signal.
// #####################

// #################################################

// #####################
// NOISE:
// #####################

// WHITE NOISE
class ysxSIG_WhiteNoise : public ysxSIG_Synth<float>
{
private:
    std::default_random_engine RndGen;
    std::uniform_real_distribution<double> RandDist{0.0, 22000.0};
    double GetRand = 0;
    float y = 0;
public:
    uint8_t AD = 0; // AD >> 4 = Attack; AD & 15 = Decay;

    float IO(float x) override
    {
        GetRand = RandDist(RndGen);
        y = sin(GetRand * x * 6.283185);
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

#endif
