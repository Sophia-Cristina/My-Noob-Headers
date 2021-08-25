#pragma once

#ifndef YSXMUSIC_H
#define YSXMUSIC_H

#include "ysxConst.h";

// #####################
// ####### By Sophia Cristina
// ####### Functions normally used in music and related
// #####################

// #####################################################################################################################################

// ############################
// ####### CLOCK / TIME:

double BPM2ms(double BPM) { return(60000.0 / BPM); } // Quantos 'ms' tem em cada beat
double ms2BPM(double ms) { return(60000.0 / ms); } // Qual seria o 'BPM' se o beat tivesse tantos 'ms'
double ms2Freq(double ms) { return(1.0 / (ms / 1000.0)); } // dado 'ms', retorna a frequencia que oscilaria no mesmo periodo
double Ptrn2ms(int PtrnSize, int Ptrnn, double BPM) { return((PtrnSize * Ptrnn) * BPM2ms(BPM)); } // no "Renoise" com "64" linhas seria "PtrnSize = 16", é em beats;
double ms2beat(double ms, double BPM) { return(ms / (60000.0 / BPM)); } // Beats per ms | f(1000ms, 120bpm) = 2 beats
double beat2ms(double Beats, double BPM) { return((60000.0 / BPM) * Beats); } // ms per beats | f(2Beats, 120bpm) = 500ms
double BeatsinTime(int Min, int Sec, double BPM) { return((Min * 60 + Sec) / (60.0 / BPM)); } // Minutes and seconds to Beats (ms) | '6m30s' / (60s / 120bpm) = 390s / 0.5s = 780 beats
double samptoms(double samp, double SampleRate) { return((samp * 1000.0) / SampleRate); } // samples to ms by sample rate | (22050n * 1000) / 44100hz = 500ms
double mstosamp(double ms, double SampleRate) { return((ms / 1000.0) * SampleRate); } // ms to samples by sample rate | (500ms / 1000.0) * 44100hz = 22050 samples
double TAU2Samples(int SampleRate) { return(SampleRate / TAU); } // SamplesRate divided by tau | 44100 / 6.2831 = 7018.7329903525843074077739647279
double Samplen2Rad(int n, int SampleRate) { return(TAU * (n / SampleRate)); } // Sample 'n' in '44100hz' to '2 * PI' | TAU * (22050 / 44100)  = TAU * 0.5 = PI radians
double Rad2Samplen(double theta, int SampleRate) { return((theta / TAU) * SampleRate); } // Sample position based on a sine wave of 1hz | (PI / TAU) * 44100 = 0.5 * 44100 = 22050 samples

// TIME IN SECONDS MEASURES EITHER BY CONVERTING UCHAR SAMPLES OR BY SAMPLES COUNT:
double Samples2Sec(unsigned int nSamplesbyUCHAR, unsigned int SampRate, unsigned char BitsPerSamp) { return((double)nSamplesbyUCHAR / ((long long)SampRate * (0.125 * BitsPerSamp))); }
double Samples2Sec(unsigned int nSamplesbyUCHAR, unsigned int SampRate, unsigned char BitsPerSamp, unsigned char Channels)
{
	return((double)nSamplesbyUCHAR / ((long long)(SampRate * (0.125 * BitsPerSamp) * Channels)));
}
double Samples2Sec(unsigned int Samples, unsigned int SampRate) { return((double)Samples / SampRate); }

// ############################
// ####### NOTES AND PATTERNS:
// # FREQUENCIES:
//double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, (MIDI - (Temperament * 5.75)) / Temperament) * BaseFreq); } // A3 = 57; C3 = 48;
double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, ((double)MIDI / Temperament)) * BaseFreq * 0.0185814); } // Modo Reduzido, mas fixo em 'A3 = 57'
double FreqtoMIDI(double Freq, int Temperament, double BaseFreq) { return(69 + 12 * log2(Freq / BaseFreq)); }

// ############################
// ####### SPECIAL:

// Find a periodic value from 'sine' through a 'margin_b' of 'frequencies' multiplied by 'a' on the line of specific 'Radian'; (use 'Value' in set { -1 <= Value <= 1) }:
// The math is just 'if (sin(Radian * a * b) == Value)'
std::vector<int> FindValueInSine(double a, int b0, int b1, double Value, double Radian)
{ std::vector<int> Return; for (int b = b0; b < b1; ++b) { if (sin(Radian * a * b) == Value) { Return.push_back(b); } } return(Return); }

// The same, but based on a music scale (MIDI):
std::vector<int> FindValueInSineinMIDI(double a, int MIDIini, int MIDIend, double Value, double Radian, int Temperament, double BaseFreq)
{ std::vector<int> Return; for (int M = MIDIini; M < MIDIend; ++M) { if (sin(Radian * a * MIDItoFreq(M, Temperament, BaseFreq)) == Value) { Return.push_back(M); } } return(Return); }

// The same, but based on a music scale (Frequency):
std::vector<double> FindValueInSineinFreq(double a, int FreqIni, int FreqEnd, double Increment, double Value, double Radian, int Temperament, double BaseFreq)
{ std::vector<double> Return; for (int f = FreqIni; f < FreqEnd; f += Increment) { if (sin(Radian * a * f) == Value) { Return.push_back(FreqtoMIDI(f, Temperament, BaseFreq)); } } return(Return); }

// ################################################# FIM ####################################################################################

#endif // SCPARSE_