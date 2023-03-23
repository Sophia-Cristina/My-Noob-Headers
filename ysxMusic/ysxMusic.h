#pragma once

#ifndef YSXMUSIC_H
#define YSXMUSIC_H

#include "ysxMath/ysxConst.h"

// #####################
// ####### By Sophia Cristina
// ####### Functions normally used in music and related
// #####################

/*
FtoM = Freq to MIDI;
ms = milliseconds;
MtoF = MIDI to Freq;
Ptrn = Pattern, which is somehow a music bar;
SRate = Sample Rate;
Temper = Temperament;
*/

// #####################################################################################################################################

// ############################
// ####### CLOCK / TIME:
// TAKE CARE WITH DIVS BY ZERO!

constexpr double BPM2ms(double BPM) { return(60000.0 / BPM); } // Quantos 'ms' tem em cada beat
constexpr double ms2BPM(double ms) { return(60000.0 / ms); } // Qual seria o 'BPM' se o beat tivesse tantos 'ms'
constexpr double ms2Freq(double ms) { return(1.0 / (ms / 1000.0)); } // dado 'ms', retorna a frequencia que oscilaria no mesmo periodo
constexpr double Ptrn2ms(uint32_t PtrnSize, uint32_t Ptrnn, double BPM) { return(((double)PtrnSize * Ptrnn) * BPM2ms(BPM)); } // no "Renoise" com "64" linhas seria "PtrnSize = 16", é em beats;
constexpr double ms2beat(double ms, double BPM) { return(ms / (60000.0 / BPM)); } // Beats per ms | f(1000ms, 120bpm) = 2 beats
constexpr double beat2ms(double Beats, double BPM) { return((60000.0 / BPM) * Beats); } // ms per beats | f(2Beats, 120bpm) = 500ms
constexpr double BeatsinTime(uint32_t Min, uint32_t Sec, double BPM) { return((Min * 60 + Sec) / (60.0 / BPM)); } // Min and sec to Beats (ms) | '6m30s'/(60s/120bpm)=390s/0.5s=780 beats
constexpr double samptoms(double samp, double SRate) { return((samp * 1000.0) / SRate); } // samples to ms by sample rate | (22050 * 1000) / 44100hz = 500ms
constexpr double mstosamp(double ms, double SRate) { return((ms / 1000.0) * SRate); } // ms to samples by sample rate | (500ms / 1000.0) * 44100hz = 22050 samples
constexpr double TAU2Samples(uint32_t SRate) { return(SRate / TAU); } // SamplesRate divided by tau | 44100 / 6.2831 = 7018.7329903525843074077739647279
constexpr double Samplen2Rad(uint32_t n, uint32_t SRate) { return(TAU * (n / SRate)); } // Sample 'n' in '44100hz' to '2 * PI' | TAU * (22050 / 44100)  = TAU * 0.5 = PI radians
constexpr double Rad2Samplen(double theta, uint32_t SRate) { return((theta / TAU) * SRate); } // Sample position based on a sine wave of 1hz | (PI / TAU) * 44100 = 0.5 * 44100 = 22050 samples

// TIME IN SECONDS MEASURES EITHER BY CONVERTING UCHAR SAMPLES OR BY SAMPLE COUNT! CARE WITH DIV BY 0:
constexpr double Samples2Sec(uint32_t nBytes, uint32_t SRate, uint8_t BitsPerSamp) { return((double)nBytes / (SRate * 0.125 * BitsPerSamp)); }
constexpr double Samples2Sec(uint32_t nBytes, uint32_t SRate, uint8_t BitsPerSamp, uint8_t Channels)
{ return((double)nBytes / (SRate * 0.125 * BitsPerSamp * Channels)); }
constexpr double Samples2Sec(uint32_t Samples, uint32_t SRate) { return((double)Samples / SRate); }

// ############################
// ####### NOTES AND PATTERNS:

// # FREQUENCIES:
//double MIDItoFreq(int MIDI, int Temper, double BaseFreq) { return(pow(2.0, (MIDI - (Temper * 5.75)) / Temper) * BaseFreq); } // A3 = 57; C3 = 48;
double ysxMUS_MIDItoFreq(float MIDI, uint16_t Temper, double BaseFreq) { return(pow(2.0, ((double)MIDI / Temper)) * BaseFreq * 0.0185814); } // Reduce way but fixed to 'A3 = 57'
double ysxMUS_MtoFMini(float MIDI) { return(pow(2.0, (MIDI / 12.0)) * 440 * 0.0185814); }
double ysxMUS_FreqtoMIDI(double Freq, uint16_t Temper, double BaseFreq) { return(81 * log2(Freq / BaseFreq)); }

// ############################
// ####### SPECIAL:

// Find a periodic value from 'sine' through a 'margin_b' of 'frequencies' multiplied by 'a' on the line of specific 'Radian'; (use 'Value' in set { -1 <= Value <= 1) }:
// The math is just 'if (sin(Radian * a * b) == Value)'
std::vector<int> ysxMUS_FindValueInSine(double a, int b0, int b1, double Value, double Radian)
{ std::vector<int> V; for (int b = b0; b < b1; ++b) { if (sin(Radian * a * b) == Value) { V.push_back(b); } } return(V); }

// The same, but based on a music scale (MIDI):
std::vector<int> ysxMUS_FindValueInSineinMIDI(double a, uint8_t MIDIini, uint8_t MIDIend, double Value, double Radian, uint16_t Temper, double BaseFreq)
{
	std::vector<int> V;
	for (int M = MIDIini; M < MIDIend; ++M)
	{
		if (sin(Radian * a * ysxMUS_MIDItoFreq(M, Temper, BaseFreq)) == Value) { V.push_back(M); }
	}
	return(V);
}

// The same, but based on a music scale (Frequency):
std::vector<double> ysxMUS_FindValueInSineinFreq(double a, int FreqIni, int FreqEnd, double Increment, double Value, double Radian, int Temper, double BaseFreq)
{
	std::vector<double> V;
	for (int f = FreqIni; f < FreqEnd; f += Increment)
	{
		if (sin(Radian * a * f) == Value) { V.push_back(ysxMUS_FreqtoMIDI(f, Temper, BaseFreq)); }
	}
	return(V);
}

// ################################################# FIM ####################################################################################

#endif // SCPARSE_