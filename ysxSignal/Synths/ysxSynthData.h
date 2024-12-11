#pragma once

#ifndef YSXSYNTHDATA_H
#define YSXSYNTHDATA_H

// This is included by 'ysxSynth.h'.
// And mostly likely shouldn't be included by you.

// #####################
// ####### By Sophia Cristina
// ####### Files, datas and protocols.
// #####################

// #################################################

// #####################
// FILES:
// #####################

/*PLAY RAW DATA FROM FILE:
Only PCM and integer types!
Using different SampleRate may make it sound weirdt but it works.
Set 'Freq' to '1' for 1x playback speed.
This class ignores 'MIDI[n].x' from 'ysxSIG_Synth'.
'Ini' and 'End', are the initial and final byte of the file.
Use 'Size' for the final byte of playback (there is a function that will align it for it to match the channels and bitdepth.
There is also the use of the function 'ysxSIG_ByteAlign' when buffering (which you should do to play, it doesn't play without the buffer)!
My engine for now works only on mono, i'll change in the future,
so this is going to mix all channels into one;*/
template<uint32_t SRATE>
class ysxSIG_PlayRAW : public ysxSIG_Synth<float>
{
private:
	uint32_t EoF = 0;
	uint32_t Ini = 0, End = 1;
	float y = 0;
	
	union Data
	{
		uint64_t ui64;
		uint32_t ui32[2];
		uint16_t ui16[4];
		uint8_t ui8[8];
	};
	Data Get;

	std::vector<float> Buffer;

public:
	// File stuffs:
	uint32_t FileSRate = 44100;
	uint8_t Chans = 1, Bitdepth = 8;
	std::string Path;
	std::ifstream F;

	// #####################
	ysxSIG_PlayRAW(std::string OpenFile)
	{
		F.open(OpenFile, std::ios::binary);
		if (F.is_open())
		{
				//std::cout << "FILE (PlayRAW): " << OpenFile << " is open!\n";
		}
		else {std::cerr << "ERROR (PlayRAW): Could not open file!\n"; }
		F.seekg(0, F.end); EoF = F.tellg();
		F.seekg(0, F.beg);
	}
	// #####################

	// Get EoF:
	void GetEoF() { F.seekg(0, F.end); EoF = F.tellg(); F.seekg(0, F.beg); }
	
	// Fix 'Ini' and 'End' and set value of 'Size':
	void SetSize()
	{
		if (Ini == End) { Ini > 0 ? --Ini : ++End; }
		if (End > EoF) { End = EoF; }
		if (Ini > End) { Get.ui64 = Ini; Ini = End; End = Get.ui64; Get.ui64 = 0; }
		if (!Chans) { Chans = 1; } if (!Bitdepth) { Bitdepth = 8; }
		Size = End - Ini; Size /= Chans * (Bitdepth / 8);
	}
	
	// Set End equal to EoF:
	void SetEndtoEoF() { GetEoF(); End = EoF; SetSize(); }
	
	// Set playback sizes (in bytes):
	void SetIniEndByte(uint32_t SetIni, uint32_t SetEnd) { Ini = SetIni; End = SetEnd; SetSize(); }
	// Set 'Ini' manually and 'End' will be 'Samp' samples away from 'Ini':
	void SetIniEndSamples(uint32_t SetIni, uint32_t Samp) { Ini = SetIni; End = Ini + (Samp * Chans * (Bitdepth / 8)); SetSize(); }
	// Set 'Ini' manually and 'End' will be 'Sec' in samples away from 'Ini':
	void SetIniEndSec(uint32_t SetIni, float Sec) { Ini = SetIni; End = Ini + Sec * SRATE * Chans * (Bitdepth / 8); SetSize(); }
	
	// Set basic must-have parameters:
	void SetAudioSpec(uint32_t SetFileSRate, uint8_t SetChans, uint8_t SetBitdepth)
	{ FileSRate = SetFileSRate; Chans = SetChans; Bitdepth = SetBitdepth; }

	// If your file is a '.wav', use this to set it up:
	void OpenAsWav()
	{
		std::cout << "### Opening as '.wav' ###\n";
		Ini = 44;
		SetEndtoEoF(); SetSize();
		std::cout << "BYTES: " << EoF << " | Size: " << Size << '\n';
		F.seekg(22); // Get channels
		F.read((char*)&Get.ui16[0], 2);
		Chans = Get.ui16[0];
		std::cout << "Ch: " << Get.ui16[0] << '\n';
		F.read((char*)&Get.ui32[0], 4);
		FileSRate = Get.ui32[0];
		std::cout << "S. Rate: " << Get.ui32[0] << '\n';
		F.seekg(34);
		F.read((char*)&Get.ui16[0], 2);
		Bitdepth = Get.ui16[0];
		std::cout << "Bits: " << Get.ui16[0] << "\n####### ### #######\n\n";
		Get.ui64 = 0;
	}

	// Add data to buffer:
	void AddDataToBuffer()
	{
		if (Bitdepth > 64) { std::cerr << "Bitdepth must be from '1 to 64'!\n"; }
		else
		{
			std::cout << "### Adding data to Buffer ###\n";
			Buffer = std::vector<float>::vector(Size);
			for (uint64_t smp = 0; smp < Size; ++smp) // Maybe i'll have to multiply by channels
			{
				Get.ui64 = Ini + ysxSIG_ByteAlign((float)smp / FileSRate, Freq, FileSRate, Chans, Bitdepth); // Get aligned position
				if (Get.ui64 < Ini) { Get.ui64 = Ini; }
				if (Get.ui64 >= End) { Get.ui64 = Ini + (Get.ui64 - End); } // Modulo
				//std::cout << "####### INDEX: " << Get.ui64 << " | x: " << (float)smp / FileSRate << " | x_end: " << (float)Size / FileSRate << '\n';
				F.seekg(Get.ui64);
				//F.seekg(smp + 44);
				Get.ui64 = 0; // CLEAN

				if (Bitdepth == 64)
				{
					for (uint8_t n = 0; n < Chans; ++n)
					{
						F.read((char*)&Get.ui64, 8);
						Buffer[smp] = (Get.ui64 / ((float)pow(256, 8) - 1));// / Chans;
					}
				}
				else if (Bitdepth == 32)
				{
					for (uint8_t n = 0; n < Chans; ++n)
					{
						F.read((char*)&Get.ui32[0], 4);
						Buffer[smp] = (Get.ui32[0] / ((float)pow(256, 4) - 1));// / Chans;
					}
				}
				else if (Bitdepth == 16)
				{
					for (uint8_t n = 0; n < Chans; ++n)
					{
						F.read((char*)&Get.ui16[0], 2);
						Buffer[smp] = (Get.ui16[0] / ((float)pow(256, 2) - 1));// / Chans;
					}
				}
				else if (Bitdepth == 8)
				{
					for (uint8_t n = 0; n < Chans; ++n)
					{
						F.read((char*)&Get.ui8[0], 1);
						Buffer[smp] = (Get.ui8[0] / 255.0);// / Chans;
					}
				}
				else
				{
				   	std::cerr << "In the future i'll try to make it compatible to any bit depth!\nBut for now, only multiples of '8' <= 64!\n";
					break;
			   	}
				Buffer[smp] = (Buffer[smp] * 2) - 1;
				//std::cout << "BUFFER: " << Buffer[smp] << '\n';
			}
		std::cout << "Done!\n####### ### #######\n\n";
		}
	}

	// #####################

	float IO(float x) override
	{
		//std::cout << "### PlayRAW: x: " << x << " |  Buffer index: " << round(Freq * FileSRate * x * FileSRate / SRATE) << " ###\n";
		return(Buffer[uint64_t(round(Freq * FileSRate * x * FileSRate / SRATE)) % Size]) * ysxSIG_MIDI_V;
	}
};

#endif
