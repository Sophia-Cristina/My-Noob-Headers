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
class ysxSIG_EFX_DelayFB : public ysxSIG_Synth<float>
{
private:

    std::vector<std::vector<float>> DelayBuf;

    std::vector<size_t> Play;
    std::vector<size_t> Write;

public:

    ysxSIG_Stream<float>* Sig = nullptr;

    size_t DelaySize = 0;
    size_t Samples = 0;

    float FB = 0.75f;

    void InitVoices(size_t voices)
    {
        DelayBuf.resize(voices);
        Play.resize(voices);
        Write.resize(voices);

        for(size_t v = 0; v < voices; ++v)
        {
            DelayBuf[v].assign(DelaySize, 0.0f);
            Play[v] = 0;
            Write[v] = 0;
        }
    }

    void NewDelayLine(uint32_t SRate, double ms)
    {
        DelaySize = (size_t)(SRate * ms / 1000.0);
        Size = DelaySize; // delay lifetime
    }

    void ChangeDelayTime(uint32_t SRate, double ms)
    {
        Samples = (size_t)(SRate * ms / 1000.0);

        if(Samples >= DelaySize)
        {
            Samples = DelaySize - 1;
        }
    }

    float IO(float x) override
    {
        float in = 0.0f;

        if(Sig)
        {
            Sig->V = V;

            if(Sig->C[V] > 0)
            {
                in = Sig->IO(x);
            }
        }

        float delayed = DelayBuf[V][Play[V]];

        float out = in + delayed;

        Write[V] = (Play[V] + Samples) % DelaySize;

        DelayBuf[V][Write[V]] = in + delayed * FB;

        Play[V]++;
        if(Play[V] >= DelaySize)
        {
            Play[V] = 0;
        }

        return out;
    }
};


// #################################################
// #################################################
// #################################################


#endif
