#pragma once

#ifndef YSXSDLSYNTH_H
#define YSXSDLSYNTH_H
// Time is included by 'ysxSDLAudio.h'

// #####################
// ####### By Sophia Cristina
// ####### Codes about synth and related, for SDL Audio
// #####################

// ############################################################################################################################################
// ################################################# NOTES AND ATTENTIONS #################################################
// !!!!!!!	
// !!!!!!!	CATALOGUE ANY CHANGE THAT CAN AFFECT CODE VERSIONS:
// !!!!!!!	* PAY ATTENTION to any change that may affect 'ysxElectr.h' classes, since electronic devices normally have alike terms to music devices;
// !!!!!!!	
// ################################################# NOTES AND ATTENTIONS #################################################
// ############################################################################################################################################

// #################################################
// REFERENCES:
// [1] The Computer Music Tutorial - Curtis Roads
// #################################################

// #################################################
// ####### DRUM KIT #######

// GENERATE A KICK BUFFER, USE BYTES 1, 2 OR 4:
std::vector<unsigned char> KickSimpleBuf(unsigned int Size, unsigned char Bytes, float Omega, float PowFreq, float PowAmp, float Attack)
{
	if (Attack > 1) { Attack = 1; } if (Attack < 0) { Attack = 0; }
	std::vector<unsigned char> B(Size * Bytes);
	unsigned int BSize = B.size(), ASize = BSize * Attack;
	if (Bytes == 4 || Bytes == 2 || Bytes == 1)
	{
		for (int n = 0; n < BSize; n += Bytes)
		{
			double x = (double)n / BSize;
			double b = sin(x * (Omega * TAU * pow(1 - x, PowFreq))) * pow(1 - x, PowAmp);
			if (n < ASize) { b *= ((double)n / ASize); }
			if (Bytes == 4)
			{
				unsigned int a = (b + 1) * 2147483647.5;
				memcpy(&B[0], &a, Bytes);
			}
			else if (Bytes == 2)
			{
				unsigned short a = (b + 1) * 32767.5;
				memcpy(&B[0], &a, Bytes);
			}
			else
			{
				unsigned char a = (b + 1) * 127.5;
				B[n] = a;
			}
		}
	}
	else { std::cout << "Sorry, for now, this only supports '1', '2' and '4' bytes format!\n"; }
	return(B);
}

// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

class AudioBuffer
{
public:
	std::vector<float> Buffer; // Oscillation is rendered here
	SDL_AudioSpec* Spec; // Configuration for SDL Audio
	unsigned short BlockSize = 512; // The wave in buffer is going to be based on the size of a block of samples
	
	// #################################################
	AudioBuffer(SDL_AudioSpec& AudioSpec) { Spec = &AudioSpec; BlockSize = Spec->samples; }
	~AudioBuffer() {}
	// #################################################

	// #################################################
	// PREPARE BUFFER:	
	// Transform 'Buffer' in this class to an usable 'Uint8' buffer for SDL.
	// New buffer is going to have the size in bytes as equal to 'Buffer.size() * Bytes_per_sample'.
	// Each float in the 'Buffer' in this class will be converted to specified format set in 'Spec'.
	// This means, even if float is four bytes, buffers with the format specified as UINT16 are going
	// to receive a value of a float normalized from '0' to '65535'. This logic applies to other formats.
	// Ex.: 128 values in 'Buffer' (from this class) is also 128 values in an 'UINT16 buffer',
	// but it renders to 'vector<Uint8> V(256)' or 'V(128 * (16 / 8))'.
	virtual std::vector<unsigned char> PrepareBuf()
	{
		unsigned char Bytes = Spec->format & 255; Bytes /= 8;
		std::vector<unsigned char> B(Buffer.size() * Bytes);
		if (Bytes == 4 || Bytes == 2 || Bytes == 1)
		{
			//unsigned char* c = new unsigned char[Bytes];
			for (int n = 0; n < B.size(); n += Bytes)
			{
				if (Bytes == 4)
				{
					unsigned int a = (Buffer[n / Bytes] + 1) * 2147483647.5;
					memcpy(&B[0], &a, Bytes);
				}
				else if (Bytes == 2)
				{
					unsigned short a = (Buffer[n / Bytes] + 1) * 32767.5;
					memcpy(&B[0], &a, Bytes);
				}
				else
				{
					unsigned char a = (Buffer[n / Bytes] + 1) * 127.5;
					B[n] = a;
				}
			}
			//delete[] c;
		}
		else { std::cout << "Sorry, for now, this only supports '1', '2' and '4' bytes format!\n"; }
		return(B);
	}
};


// SIMPLE OSCILLATOR, YOU MAY INHERIT IT WITH OTHER CLASSES:
class Oscillator : public AudioBuffer
{
public:
	enum Type { wSine, wTri, wRect, wSaw, wCustom };
	float Omega = 220, Phase = 0, Gain = 1; // Gain * f(Phase + x * Omega); Gain is normalized between '-1' and '1'
	float PW = 0.5; // Pulse Width, only for specific wave types
	// #################################################
	// 'tn' is the position in the 'x axis (time axis)', you may return to 0 if a wave-form is cyclical or if you want to set
	// a position in a function (or whatever reason).
	// !!! TREAT 'tn' AS SECONDS !!!
	// Consequently, imagine that 'tn = 2' and you want that at this point it have finished SIX cycles of a sine...
	// Using 't' from 'tn = 0' to 'tn = 2 seconds', you must do:
	//		---> sin(t * TAU * 3); <--- And '3' is the angular frequency
	// 't1' is always set as 'tn + (TotalSamples / SampleRate)'. And after finishing a function with it, then 'tn = t1'.
	int tn = 0;
	// #################################################
	Oscillator(SDL_AudioSpec& MainSpec) : AudioBuffer(MainSpec)
	{
	}

	~Oscillator()
	{
	}
	// #################################################
	// CREATES A WAVE (Type) AND *OVERWRITE* BUFFER OBJECT:
	void NewWave(unsigned char WaveType, unsigned int SizeAsSamples)
	{
		float t0 = tn, t1 = tn + (SizeAsSamples / Spec->freq);
		std::vector<float> R(SizeAsSamples);
		float Delta = (t1 - t0) / SizeAsSamples;
		for (int n = 0; n < SizeAsSamples; ++n)
		{
			float x = t0 + (Delta * n * Omega * TAU);
			if (WaveType == wSine) { R[n] = Gain * sin(Phase + x); }
			else if (WaveType == wTri) { R[n] = Gain * tri(Phase + x); }
			else if (WaveType == wRect) { R[n] = Gain * rect(Phase + x, PW); }
			else if (WaveType == wSaw) { R[n] = Gain * saw(Phase + x); }
			else { R[n] = Gain * MiniForm(Phase + (t0 + (Delta * n * TAU)), Omega); }
		}
		Buffer = R;
		tn = t1;
	}

	// PREFFER TO USE VALUES BETWEEN '-1' AND '1', THERE IS NO CODE TO HANDLE CLIPPING:
	void Modulate(std::vector<float> Modulator)
	{
		if (Modulator.size() > 0)
		{
			unsigned int Size = Buffer.size(), MSize = Modulator.size();
			for (unsigned int n = 0; n < Size; ++n) { Buffer[n] *= Modulator[n % MSize]; }
		}
	}
};

// #################################################

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_