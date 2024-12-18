#pragma once

#ifndef YSXSDLAUDIO_H
#define YSXSDLAUDIO_H

#include <time.h>
#include "include/SDL3/SDL_audio.h"

// #####################
// ####### By Sophia Cristina
// ####### Audio programming using SDL2
// #####################

// #################################################
// REFERENCES:
// [1] https://www.youtube.com/watch?v=P7lzXavDZ7g | #1 Audio Programming Tutorial: Project Setup
// [2] https://github.com/BennyQBD/AudioTutorial/tree/e7246ae739f8897e8e356d8e0f0c9d1eda81cc4e | From [1]
// [3] https://wiki.libsdl.org/SDL_AudioStream
// [4] https://wiki.libsdl.org/Tutorials-AudioStream
// [5] https://wiki.libsdl.org/SDL_OpenAudioDevice
// [6] https://wiki.libsdl.org/SDL_OpenAudio
// [7] https://wiki.libsdl.org/SDL_AudioSpec
// #################################################

// #################################################

// #################################################
// ############## AUDIO FORMAT ##############
// #################################################
/*
BIT MEANING OF 'SDL_AudioFormat':
(Unspecified bits are always zero).

++-----------------------sample is signed if set
||       ++-----------sample is bigendian if set
||       ||          ++---sample is float if set
||       ||          || +---sample bit size---+
15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
 |		  |			  |128 64 32 16 08 04 02 00
 1	0  0  1	 0	0  0  0  0  0  1  0  0  0  0  0 = AUDIO_S16MSB = 0x9010 = 36880 <- Example
 
 * NOTE: You can use 'AND' to '255' and get only the bit size.
		 Ex.: F = 0x9020 = 36896 = %1001 0000 0010 0000
			  F = Signed, BigEndian, 32 bit
			  F &= 255
			  F = 32
*/

/* FORMAT MACROS:
AUDIO_U8     0x0008 | Unsigned 8-bit samples
AUDIO_S8     0x8008 | Signed 8-bit samples
AUDIO_U16LSB 0x0010 | Unsigned 16-bit samples
AUDIO_S16LSB 0x8010 | Signed 16-bit samples
AUDIO_U16MSB 0x1010 | As above, but big-endian byte order
AUDIO_S16MSB 0x9010 | As above, but big-endian byte order
AUDIO_U16    AUDIO_U16LSB
AUDIO_S16    UDIO_S16LSB
*/

// ###############################################################################################################################################################################

// ###############################################################################################################################################################################
// ####### STRUCTS #######

// ###############################################################################################################################################################################
// ####### CALLBACK #######

// POISTION AND LENGHT LEFT TO BE READ:
// Audio->Pos += Samples; Audio->Samples -= Samples;
struct ysxSDL_AU_AudioData { uint8_t* Pos; uint32_t Samples; };
// With 'SDL >= 2.0.4' you can choose to avoid callbacks and use 'SDL_QueueAudio()' instead, if you like.
// Just open your audio device with a NULL callback.
void ysxSDL_AU_AudioCall(void* Data, uint8_t* Stream, int StreamSamples)
{
	ysxSDL_AU_AudioData* Audio = (ysxSDL_AU_AudioData*)Data;

	if (Audio->Samples == 0) { return; } uint32_t Samples = (uint32_t)StreamSamples;
	Samples = Samples > Audio->Samples ? Audio->Samples : Samples;

	SDL_memcpy(Stream, Audio->Pos, Samples);
	Audio->Pos += Samples; Audio->Samples -= Samples;
}

// SET 'Pos' TO FIRST SAMPLE WHILE 'Loops' IS NOT '0':
// ! 'Start' *MUST* BE *EQUAL* TO SmpLeft' WHEN 'LoopData' IS CONFIGURED !
// ! THE FORMULA TO SET POSITION BACK TO THE START AFTER A LOOP IS:
// ! if (Audio->Loops > 0) { Audio->Pos -= Audio->Start; --Audio->Loops; }
// ! BUT WHILE THE LOOP IS NOT FINISHED, IT IS:
// ! Audio->Pos += Samples; Audio->SmpLeft -= Samples;
struct ysxSDL_AU_LoopData { uint8_t* Pos; uint32_t Size; uint32_t SmpLeft; uint16_t Loops; };
// CALLBACK WHICH LOOPS UNTIL YOU STOP THE AUDIO:
void ysxSDL_AU_LoopCall(void* Data, uint8_t* Stream, int StreamSamples)
{
	ysxSDL_AU_LoopData* S = (ysxSDL_AU_LoopData*)Data;

	if (S->SmpLeft == 0)
	{
		if (S->Loops > 0) { S->Pos -= S->Size; S->SmpLeft = S->Size; --S->Loops; }
		else { return; }
	}
	uint32_t Samples = (uint32_t)StreamSamples;
	Samples = Samples > S->SmpLeft ? S->SmpLeft : Samples;

	SDL_memcpy(Stream, S->Pos, Samples);
	S->Pos += Samples; S->SmpLeft -= Samples;
}

// THIS DATA LOOPS THE BUFFER WITH A MODULO :
// Check the callback function! Pos = &array[0], Samples = array.size();
struct ysxSDL_AU_SignalData { uint8_t* Pos; uint32_t Count; size_t Samples; };
/*CALLBACK FOR A SIGNAL BUFFER LOOPED BY A MODULO:
I named "Signal" because it is a buffer that constantly outputs itself, like a signal cable connection.
But it is just a call that goes to the first sample position after it reaches the last sample.
I have not named "loop" because the "LoopCall" is based on looping the buffer after reaching the end,
but it does it abruptly and not by a modulo!
Changes are to be done in the buffer index which is going to be played or before playing!
~| 0 | 1 | 2 | 3 || 4 | 5 | 6 | 7 |~ BYTES
 |Pos| . | . | . || . |B.S|Set| % |~ SIZE // B.S = Block Size = 6 samples (example)
 | _ | _ | _ |B.S||Set| _ | _ | % |*/
void ysxSDL_AU_SignalCall(void* Data, uint8_t* Stream, int BufSamples)
{
	ysxSDL_AU_SignalData* S = (ysxSDL_AU_SignalData*)Data;
	uint32_t Left = S->Samples - S->Count;
	uint32_t Samples = BufSamples > Left ? Left : BufSamples; // If 'Block Size' is bigger than the space left...
	SDL_memcpy(Stream, &S->Pos[S->Count], Samples); // ... For now we add every sample possible.
	if (Samples < BufSamples) { SDL_memcpy(Stream, &S->Pos[0], BufSamples - Samples); } // And now we add the rest.
	S->Count += BufSamples; S->Count %= S->Samples; // Loop if needed! Pos. should be seem as a constant, however, you can change.
}

// CALLBACK FOR WAV FILES:
void ysxSDL_AU_WavCall(void* Data, uint8_t* Stream, int StreamSamples)
{
	ysxSDL_AU_AudioData* S = (ysxSDL_AU_AudioData*)Data;

	if (S->Samples == 0) { return; } uint32_t length = (uint32_t)StreamSamples;
	length = (length > S->Samples ? S->Samples : length);

	SDL_memcpy(Stream, S->Pos, length);
	S->Pos += length; S->Samples -= length;
}
// ###############################################################################################################################################################################
// ####### OBJECTS #######

// SDL_AudioFormat::format = NewSpecFormat(...);
uint16_t ysxSDL_AU_NewSpecFormat(uint8_t Bytes, bool Signed, bool BigEndian)
{
	if (Bytes > 31) { Bytes = 31; } uint16_t f = Bytes * 8;
	if (Signed) { f += 0x8000; } if (BigEndian) { f += 0x1000; }
	return(f);
}

// EZ SPEC MAKER:
SDL_AudioSpec ysxSDL_AU_NewAuSpec(uint32_t SampleRate, uint16_t BlockSize, uint8_t BytesPerSample, uint8_t Channels, bool Signed, bool BigEndian)
{
	SDL_AudioSpec S; SDL_zero(S);
	S.freq = SampleRate; S.samples = BlockSize; S.channels = Channels;
	S.format = ysxSDL_AU_NewSpecFormat(BytesPerSample, Signed, BigEndian);
	return(S);
}

// INTERLACE BUFFERS:
// asdasdasdasd

// ####### INFOS #######

// COUT SPEC FORMAT:
std::string ysxSDL_AU_GetFormatInfo(uint16_t Format)
{
	std::string s = "# Format #\n"; s += "Value: " + std::to_string(Format) + '\n';
	Format & 0x8000 ? s += "* Signed\n" : s += "* Unsigned\n";
	Format & 0x1000 ? s += "* Big Endian\n" : s += "* Little Endian\n";
	s += "* Bits: " + std::to_string(Format & 255) + '\n';
	return(s);
}

// COUT SPECT:
std::string ysxSDL_AU_GetSpecInfo(SDL_AudioSpec& Spec)
{
	std::string s = "Sample Rate: ";
	s += std::to_string(Spec.freq) + '\n' + "Channels: " + std::to_string((int)Spec.channels) + '\n';
	s += "Samples: " + std::to_string(Spec.samples) + '\n' + "Size: " + std::to_string(Spec.size) + '\n';
	ysxSDL_AU_GetFormatInfo(Spec.format);
	return(s);
}

// COUT DATA:
std::string ysxSDL_AU_GetDataInfo(ysxSDL_AU_AudioData& D)
{ std::string s = "Pos.: "; s += std::to_string((uint32_t)D.Pos) + " | Samples: " + std::to_string(D.Samples) + '\n'; return(s); }
std::string ysxSDL_AU_GetDataInfo(ysxSDL_AU_LoopData& D)
{
	std::string s = "Pos.: "; s += std::to_string((uint32_t)D.Pos) + " | Smp. Left: " + std::to_string(D.SmpLeft)
		+ " | Loop Samples: " + std::to_string(D.Size) + '\n';
	return(s);
}
std::string ysxSDL_AU_GetDataInfo(ysxSDL_AU_SignalData& D)
{
	std::string s = "Ini. Pos.: "; s += std::to_string((uint32_t)D.Pos) + " | Total Samples: " + std::to_string(D.Samples)
		+ " | Current pos.: " + std::to_string(D.Count) + '\n';
	return(s);
}

// ###############################################################################################################################################################################

// #################################################
// ####### CLASSES #######

/* [5]
	THIS IS THE CLASS TO OUTPUT SOUNDS!

	* To load any file:
	SDL_LoadFile(File, DataSize);
	
	* Also, any 'uint8_t' buffer can be used to play a sound:
	Data.Pos = &vector<uint8_t> AnyBuffer[0];

	* 'Signal' vector is aimed to be used with 'SignalData' and 'SignalCall'.
	  Advised to not touch this buffer if using 'SignalData'! But you may use
	  it as the main buffer if using other kind of data structure.

	* 'Block' vector is to be used to inject values in the position being read
	  in 'Signal' vector. This is also to be used with 'SignalData'.
*/
class ysxSDL_AU_Device
{
public:
	SDL_AudioSpec* Spec;
	//SDL_AudioSpec OutSpec; // [6][7]
	std::vector<std::vector<uint8_t>> Buffers; // Add your audios here
	std::vector<uint8_t> Signal; // !!! FOR CALLBACK LOOP, CAUTION WHEN TOUCHING IT !!!
	std::vector<uint8_t> Block; // You may modify this to be read by the signal block
	uint8_t Bytes = 2; // Bytes per sample. (Spec.format & 255) / 8
	bool IsOpen = false; // To make sure that the audio is closed when this class is destroyed
	SDL_AudioDeviceID Device;
	// #################################################
	ysxSDL_AU_Device(SDL_AudioSpec& InSpec, uint32_t SigSize)
	{
		InSpec.callback = ysxSDL_AU_AudioCall;
		Bytes = (InSpec.format & 255) / 8;
		if (SigSize < InSpec.samples) { Signal = std::vector<uint8_t>::vector(InSpec.samples); }
		else { Signal = std::vector<uint8_t>::vector(SigSize); }
		Block = std::vector<uint8_t>::vector(InSpec.samples);
		Spec = &InSpec;
		for (uint32_t n = 0; n < Signal.size(); ++n) { Signal[n] = 127; } // Need to change based on bits later
	}
	~ysxSDL_AU_Device()
	{
		if (IsOpen) { SDL_CloseAudioDevice(Device); }
		//delete(Start);
	}
	
	// CONFIG SIGNAL DATA:
	void ConfigSigData(ysxSDL_AU_SignalData& SigD)
	{
		SigD.Pos = &Signal[0]; SigD.Samples = Signal.size();
		SigD.Count = 0; Spec->userdata = &SigD;
	}
	
	// #################################################

	// MAKE SURE THE BUFFER IS NOT EMPTY!
	void PlayBuffer(uint32_t nBuffer, bool COut)
	{
		if (nBuffer < Buffers.size())
		{
			ysxSDL_AU_AudioData Au; Au.Pos = &Buffers[nBuffer][0]; Au.Samples = Buffers[nBuffer].size();
			Spec->userdata = &Au; Spec->callback = ysxSDL_AU_AudioCall;
			uint32_t Time = (uint32_t)round((double)Au.Samples / (Spec->freq / 1000.0)); // Time to end a playback
			if (SDL_OpenAudioDevice(NULL, 0, Spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE) < 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
			else
			{
				#ifdef USE_SDL3
				SDL_PlayAudioDevice(Device);
				#endif
				#ifdef USE_SDL2
				SDL_PauseAudioDevice(Device, 0);
				#endif
				while (Au.Samples > 0)
				{
					if (COut)
					{ std::cout << "(Synth) Seconds: " << Samples2Sec(Au.Samples, Spec->freq, Spec->format & 255, Spec->channels) << std::endl; }
					SDL_Delay(Time);
				}
				SDL_CloseAudioDevice(Device);
			}
		}
		else { std::cout << "!!! No Buffer !!!\n"; }
	}

	// PLAY '.wav' FILE:
	// Stopped working after SDL3, so i'll have to fix it somehow.
	/*void PlayWAV(std::string Filename, bool COut)
	{
		SDL_AudioSpec wSpec; uint8_t* wStart; uint32_t wSamples;
		if (SDL_LoadWAV(Filename.data(), &wSpec, &wStart, &wSamples) == NULL)
		{ std::cerr << "ERROR: '" << Filename << "' could not be loaded!" << std::endl; }
		else
		{
			ysxSDL_AU_AudioData Au; Au.Pos = wStart; Au.Samples = wSamples;
			wSpec.callback = ysxSDL_AU_WavCall; wSpec.userdata = &Au;
			uint32_t Time = (uint32_t)round((double)Spec->samples / (Spec->freq / 1000.0));
			time_t t = time(&t);
			Uint64 Ts = t;
			Uint64 Te = (Time / 1000) + t;
			Device = SDL_OpenAudioDevice(NULL, 0, &wSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
			if (Device == 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
			else
			{
				SDL_PlayAudioDevice(Device);
				while (Au.Samples > 0)
				{
					while (time(&t) < Te) {  } // Do nothing
					if (COut)
					{ std::cout << "(Synth) Seconds: " << Samples2Sec(Au.Samples, wSpec.freq, wSpec.format & 255, wSpec.channels) << " | Time: " << time(&t) << std::endl; }
				}
				SDL_CloseAudioDevice(Device); SDL_FreeWAV(wStart);
			}
		}
	}*/

	// #################################################

	// OPEN:
	void Open()
	{
		Device = SDL_OpenAudioDevice(NULL, 0, Spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
		if (Device < 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
		else { IsOpen = true; }
	}

	// CLOSE:
	void Close() { SDL_CloseAudioDevice(Device); IsOpen = false; }
};

#endif // SCPARSE_
