#pragma once

#ifndef YSXTABLE_H
#define YSXTABLE_H

// #####################
// ####### By Sophia Cristina
// ####### Math table macros or functions.
// #####################

// #################################################
/* REFERENCES:
 [1]
*/
// #################################################


// #################################################
// ############## MACROS ##############

// POWERS OF TWO THAT FITS 2 BYTES:
#define YSXTABLE_TWOPOWERS16B { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 }

// POPULAR SAMPLE-RATES TABLE:
// https://en.wikipedia.org/wiki/Sampling_(signal_processing)#Sampling_rate
#define YSXTABLE_SAMPLERATES { 8000, 11025, 16000, 22050, 32000, 44056, 44100, 47250, 48000, 50000, 50400, 64000, 88200, 96000, 176400, 192000, 352800, 2822400, 5644800, 11289600, 22579200 }

// HIGH COMPOSITE NUMBERS:
// https://oeis.org/A002182
#define YSXTABLE_HIGHCOMPNUMS { 1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, \
45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160 }


// #################################################
// ############## LISTS ##############


// #################################################
// ############## FUNCTIONS ##############

// RETURN A SINE WAVE TABLE:
// ATTENTION: This function does not prevent overflow and neither check if 'T_' is unsigned or not!
template<class T_> std::vector<T_> ysxTABLE_SineWave(uint32_t Size, T_ Min, T_ Max, double x0, double x1, double Freq = 1, double Phase = 0)
{
    std::vector<T_> V(Size);
    double Val;
    if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
    if (Min > Max) { T_ t = Min; Min = Max; Max = t; } T_ MinMaxDelta = Max - Min;
    for (uint32_t n = 0; n < Size; ++n)
    {
     Val = sin(Phase + x0 + Delta * n * Freq);
     V[n] = (T_)(((Val + 1) * MinMaxDelta * 0.5) + Min);
    }
    return(V);
}

// ################################################# FIM ####################################################################################

#endif
