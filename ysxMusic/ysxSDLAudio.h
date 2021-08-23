#pragma once

#ifndef YSXSDLAUDIO_H
#define YSXSDLAUDIO_H
#include <time.h>

#include "SDL_Audio.h"

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
 1	0  0  1	 0	0  0  0  0  0  0  1  0  0  0  0 = AUDIO_S16MSB = 0x9010 = 36880 <- Example
 
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
// ###############################################################################################################################################################################
// ####### STRUCTS #######

// POISTION AND LENGHT LEFT TO BE READ:
// Audio->Pos += Samples; Audio->Samples -= Samples;
struct AudioData { Uint8* Pos; Uint32 Samples; };

// SET 'Pos' TO FIRST SAMPLE WHILE 'Loops' IS NOT '0':
// ! 'SamplesStart' *MUST* BE *EQUAL* TO SamplesLeft' WHEN 'LoopData' IS CONFIGURED !
// ! THE FORMULA TO SET POSITION BACK TO THE START AFTER A LOOP IS:
// ! if (Audio->Loops > 0) { Audio->Pos -= Audio->SamplesStart; --Audio->Loops; }
// ! BUT WHILE THE LOOP IS NOT FINISHED, IT IS:
// ! Audio->Pos += Samples; Audio->SamplesLeft -= Samples;
struct LoopData { Uint8* Pos; Uint32 SamplesStart; Uint32 SamplesLeft; Uint16 Loops; };

// THIS DATA LOOPS THE BUFFER WITH A MODULO:
// Check the callback function!
struct SignalData { Uint8* Pos; Uint32 Count; Uint32 Samples; };

// ###############################################################################################################################################################################
// ####### CALLBACK #######
// With 'SDL >= 2.0.4' you can choose to avoid callbacks and use 'SDL_QueueAudio()' instead, if you like.
// Just open your audio device with a NULL callback.
void AudioCall(void* UserData, Uint8* Stream, int StreamSamples)
{
	AudioData* Audio = (AudioData*)UserData;

	if (Audio->Samples == 0) { return; } Uint32 Samples = (Uint32)StreamSamples;
	Samples = Samples > Audio->Samples ? Audio->Samples : Samples;

	SDL_memcpy(Stream, Audio->Pos, Samples);
	Audio->Pos += Samples; Audio->Samples -= Samples;
}

// CALLBACK WHICH LOOPS UNTIL YOU STOP THE AUDIO:
void LoopCall(void* UserData, Uint8* Stream, int StreamSamples)
{
	LoopData* Audio = (LoopData*)UserData;

	if (Audio->SamplesLeft == 0)
	{
		if (Audio->Loops > 0) { Audio->Pos -= Audio->SamplesStart; Audio->SamplesLeft = Audio->SamplesStart; --Audio->Loops; }
		else { return; }
	}
	Uint32 Samples = (Uint32)StreamSamples;
	Samples = Samples > Audio->SamplesLeft ? Audio->SamplesLeft : Samples;

	SDL_memcpy(Stream, Audio->Pos, Samples);
	Audio->Pos += Samples; Audio->SamplesLeft -= Samples;
}

// CALLBACK FOR A SIGNAL BUFFER LOOPED BY A MODULO:
// Changes are to be done in the buffer index which is going to be played!
// ~| 0 | 1 | 2 | 3 || 4 | 5 | 6 | 7 |~ BYTES
//  |Pos| .	| .	| .	|| . |B.S|Set| % |~ SIZE // B.S = Block Size = 6 samples (example)
//	| _	| _ | _	|B.S||Set| _ | _ | % |
void SignalCall(void* UserData, Uint8* Stream, int StreamSamples)
{
	SignalData* Audio = (SignalData*)UserData;
	unsigned int SamplesLeft = Audio->Samples - Audio->Count;
	Uint32 Samples = (Uint32)StreamSamples; // Buffer Size
	// If stream size is bigger than the space left. For now we operate with only what is left:
	Samples = Samples > SamplesLeft ? SamplesLeft : Samples;
	SDL_memcpy(Stream, &Audio->Pos[Audio->Count], Samples);
	// Now, we get back to position '0' and add what is left to add in it (B.S - SamplesLeft):
	if (Samples < (Uint32)StreamSamples) { SDL_memcpy(Stream, &Audio->Pos[0], (Uint32)StreamSamples - Samples);	}
	Audio->Count %= Audio->Samples;
}

// CALLBACK FOR WAV FILES:
void WavCall(void* UserData, Uint8* Stream, int StreamSamples)
{
	AudioData* Audio = (AudioData*)UserData;

	if (Audio->Samples == 0) { return; } Uint32 length = (Uint32)StreamSamples;
	length = (length > Audio->Samples ? Audio->Samples : length);

	SDL_memcpy(Stream, Audio->Pos, length);
	Audio->Pos += length; Audio->Samples -= length;
}
// ###############################################################################################################################################################################
// ####### FUNCTIONS #######
// FORMAT VIEWER:
void FormatViewer(unsigned short Format)
{
	std::cout << "# Format #\n";
	std::cout << "Value: " << Format << std::endl;
	if (Format & 0x8000) { std::cout << "* Signed\n"; }
	else { std::cout << "* Unsigned\n"; }
	if (Format & 0x1000) { std::cout << "* Big Endian\n"; }
	else { std::cout << "* Little Endian\n"; }
	Format = Format & 255;
	std::cout << "* Bits: " << Format << std::endl;
}

// COUT SPECT:
void CoutSpec(SDL_AudioSpec Spec)
{
	std::cout << "Sample Rate: " << Spec.freq << std::endl;
	std::cout << "Channels: " << (int)Spec.channels << std::endl;
	std::cout << "Samples: " << Spec.samples << std::endl;
	std::cout << "Size: " << Spec.size << std::endl;
	FormatViewer(Spec.format);

}

// SDL_AudioFormat::format = GetSpecFormat(...);
unsigned short NewSpecFormat(unsigned char Bytes, bool Signed, bool BigEndian)
{
	if (Bytes > 31) { Bytes = 31; } unsigned short f = Bytes * 8;
	if (Signed) { f += 0x8000; } if (BigEndian) { f += 0x1000; }
	return(f);
}

// EZ SPEC MAKER:
SDL_AudioSpec NewAudioSpec(unsigned int SampleRate, unsigned short BlockSize, unsigned char BytesPerSample, unsigned char Channels, bool Signed, bool BigEndian)
{
	SDL_AudioSpec S; SDL_zero(S);
	S.freq = SampleRate; S.samples = BlockSize; S.channels = Channels;
	S.format = NewSpecFormat(BytesPerSample, Signed, BigEndian);
	return(S);
}

// INTERLACE BUFFERS:
// asdasdasdasd

// ###############################################################################################################################################################################

// #################################################
// ####### CLASSES #######

/*
	This is the class to output sounds!

	* You may load a '.wav' file using the macro below:
				File	 , Spec    , Buffer   , Buf. Size
	SDL_LoadWAV(FILE_PATH, &wavSpec, &wavStart, &wavSamples);

	* You can also load any file:
	SDL_LoadFile(File, DataSize);
	
	* Also, any 'Uint8' buffer can be used to play a sound:
*/
class SDLAudioDevice // [5]
{
public:
	SDL_AudioSpec* InSpec;
	//SDL_AudioSpec OutSpec; // [6][7]
	std::vector<std::vector<Uint8>> Buffers;
	unsigned char Bytes = 2; // Bytes per sample. Spec.format
	Uint8 BufTest[262144];
	bool IsOpen = false;
	SDL_AudioDeviceID Device;
	// #################################################
	// CALLBACK IS ALWAYS EQUAL TO TE FUNCTION 'AudioCall' INSIDE THIS HEADER!
	SDLAudioDevice(SDL_AudioSpec& Spec)
	{
		Spec.callback = AudioCall;
		Bytes = (Spec.format & 255) / 8;
		InSpec = &Spec;
	}
	~SDLAudioDevice()
	{
		if (IsOpen) { SDL_CloseAudio(); }
		//delete(Start);
	}
	// #################################################
	
	// MAKE SURE THE BUFFER IS NOT EMPTY!
	void PlayBuffer(unsigned int nBuffer, bool COut)
	{
		if (nBuffer < Buffers.size())
		{
			AudioData Audio; Audio.Pos = &Buffers[nBuffer][0]; Audio.Samples = Buffers[nBuffer].size();
			InSpec->userdata = &Audio; InSpec->callback = AudioCall;
			unsigned int Time = round((double)InSpec->samples / (InSpec->freq / 1000.0)); // Time to end a playback
			time_t t = time(&t);
			long long Ts = t;
			long long Te = (Time / 1000) + t;
			if (SDL_OpenAudio(InSpec, NULL) < 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
			else
			{
				SDL_PauseAudio(0);
				while (Audio.Samples > 0)
				{
					while (time(&t) < Te) { /* Do nothing!*/ }
					if (COut)
					{ std::cout << "(Synth) Seconds: " << Samples2Sec(Audio.Samples, InSpec->freq, InSpec->format & 255, InSpec->channels) << " | Time: " << time(&t) << std::endl; }
				}
				SDL_CloseAudio();
			}
		}
		else { std::cout << "!!! No Buffer !!!\n"; }
	}

	// PLAY '.wav' FILE:
	void PlayWAV(std::string Filename, bool COut)
	{
		SDL_AudioSpec wSpec; Uint8* wStart; Uint32 wSamples;
		if (SDL_LoadWAV(Filename.data(), &wSpec, &wStart, &wSamples) == NULL)
		{
			std::cerr << "ERROR: '" << Filename << "' could not be loaded!" << std::endl;
		}
		else
		{
			AudioData Audio; Audio.Pos = wStart; Audio.Samples = wSamples;
			wSpec.callback = WavCall; wSpec.userdata = &Audio;
			unsigned int Time = round((double)InSpec->samples / (InSpec->freq / 1000.0));
			time_t t = time(&t);
			long long Ts = t;
			long long Te = (Time / 1000) + t;
			Device = SDL_OpenAudioDevice(NULL, 0, &wSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
			if (Device == 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
			else
			{
				SDL_PauseAudioDevice(Device, 0);
				while (Audio.Samples > 0)
				{
					while (time(&t) < Te) { /* Do nothing!*/ }
					if (COut)
					{ std::cout << "(Synth) Seconds: " << Samples2Sec(Audio.Samples, wSpec.freq, wSpec.format & 255, wSpec.channels) << " | Time: " << time(&t) << std::endl; }
				}
				SDL_CloseAudioDevice(Device); SDL_FreeWAV(wStart);
			}
		}
	}

	// OPEN:
	void OpenDevice()
	{
		Device = SDL_OpenAudio(InSpec, NULL); if (Device < 0) { std::cout << "!!! FAILED TO OPEN AUDIO: " << SDL_GetError() << " !!!\n"; }
	}

	// CLOSE:
	void CloseDevice() { SDL_CloseAudio(); }
};

// #################################################

class SDLAudioStream // [3]
{
public:

	// You put data at Sint16/mono/22050Hz, you get back data at Float32/stereo/48000Hz
	SDL_AudioStream* Stream;
	Sint16 *Samples;
	unsigned int BlockSize;

	// #################################################
	// 'pSamples', imagine as a sample block, please, use the correct size (SampleBlockSize) as the array (pSamples):
	SDLAudioStream(
					const SDL_AudioFormat src_format, const Uint8 src_channels,
					const int src_rate, const SDL_AudioFormat dst_format,
					const Uint8 dst_channels, const int dst_rate,
					Sint16* SamplesPointer, unsigned int SampleBlockSize
				  )
	{
		Stream = SDL_NewAudioStream(src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
		if (Stream == NULL) { std::cout << "Stream failed to create: \n" << SDL_GetError() << std::endl; }
		Samples = SamplesPointer; BlockSize = SampleBlockSize;
	}

	~SDLAudioStream()
	{
		//delete(Stream);
		// Destroy it:
		// *** This frees up internal state and buffers. You don't have to drain the Stream before freeing it.
		// The SDL_AudioStream pointer you've been using is invalid after this call. ***
		SDL_FreeAudioStream(Stream);
	}
	// #################################################

	void PutSamples()
	{
		// You tell it the number of 'bytes', not samples, you're putting!
		int rc = SDL_AudioStreamPut(Stream, Samples, BlockSize * sizeof(Sint16));
		if (rc == -1)
		{
			std::cout << "Uhoh, failed to put samples in Stream: " << SDL_GetError() << std::endl;
			return;
		}
	}

	// As you add data to the Stream, SDL will convert and resample it. You can ask how much converted data is available:
	int DataAvaible() { return(SDL_AudioStreamAvailable(Stream)); } // this is in bytes, not samples!

	// And when you have enough data to be useful, you can read out samples in the requested format:
	void Read()
	{
		short int converted[44100];
		int gotten = SDL_AudioStreamGet(Stream, converted, sizeof(converted)); // this is in bytes, not samples!
		if (gotten == -1) { std::cout << "Uhoh, failed to get converted data: " << SDL_GetError() << std::endl; }
		//write_more_samples_to_disk(converted, gotten); // whatever.
	}

	// If, for whatever reason, you want to throw a Stream's contents away without reading it, you can:
	// ***
	// This will remove any data you've put to the Stream without reading, and reset internal state
	// (so the resampler will be expecting a fresh buffer instead of resampling against data you
	// previously wrote to the Stream). This is useful if you plan to reuse a Stream for different source,
	// or just decided that the current source wasn't working out; maybe you're muting an offensive person
	// on a VoIP app
	// ***
	void Clear()
	{
		SDL_AudioStreamClear(Stream);
	}

	void ProcessAudio()
	{
		PutSamples();
		Read();
		// Tell the Stream that you're done sending data, and anything being buffered should be converted / resampled and made available immediately:
		SDL_AudioStreamFlush(Stream);
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_