#pragma once

#ifndef YSXWAVE_H
#define YSXWAVE_H

#include <vector>
#include <iostream>

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// !!!!!!!	
// !!!!!!!	CHANGES (KEEP ORDER):
// !!!!!!!	* ATTENTION: I'm going to delete different functions for different data types soon, since it was just just noobness of my part;
// !!!!!!!	Removed "FileName += ".wav";" from constructor!
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #####################################################################################################################################
/*
// http://soundfile.sapp.org/doc/WaveFormat/

Notes:
 * The default byte ordering assumed for WAVE data files is little-endian. Files written using the big-endian byte ordering scheme have the identifier RIFX instead of RIFF.
 * The sample data must end on an even byte boundary. Whatever that means.
 * 8-bit samples are stored as unsigned bytes, ranging from 0 to 255. 16-bit samples are stored as 2's-complement signed integers, ranging from -32768 to 32767.
 * There may be additional subchunks in a Wave data stream. If so, each will have a uint8_t[4] SubChunkID, and unsigned long SubChunkSize, and SubChunkSize amount of data.
 * RIFF stands for Resource Interchange File Format.
*/
/*
General discussion of RIFF files:
Multimedia applications require the storageand management of a wide variety of data, including bitmaps, audio data, video data, and peripheral device control information.
RIFF provides a way to store all these varied types of data.The type of data a RIFF file contains is indicated by the file extension.Examples of data that may be stored in RIFF files are:
* Audio / visual interleaved data(.AVI)
* Waveform data(.WAV)
* Bitmapped data(.RDI)
* MIDI information(.RMI)
* Color palette(.PAL)
* Multimedia movie(.RMN)
* Animated cursor(.ANI)
* A bundle of other RIFF files(.BND)

NOTE: At this point, AVI files are the only type of RIFF files that have been fully implemented using the current RIFF specification.
Although WAV files have been implemented, these files are very simple, and their developers typically use an older specification in constructing them.
*/

/*
The canonical WAVE format starts with the RIFF header:
| Offset | Size | Name        | Description

0         4   ChunkID          Contains the letters "RIFF" in ASCII form
							   (0x52494646 big-endian form).
4         4   ChunkSize        36 + SubChunk2Size, or more precisely:
							   4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
							   This is the size of the rest of the chunk
							   following this number.  This is the size of the
							   entire file in bytes minus 8 bytes for the
							   two fields not included in this count:
							   ChunkID and ChunkSize.
8         4   Format           Contains the letters "WAVE"
							   (0x57415645 big-endian form).

The "WAVE" format consists of two subchunks: "fmt " and "data":
The "fmt " subchunk describes the sound data's format:

12        4   Subchunk1ID      Contains the letters "fmt "
							   (0x666d7420 big-endian form).
16        4   Subchunk1Size    16 for PCM.  This is the size of the
							   rest of the Subchunk which follows this number.
20        2   AudioFormat      PCM = 1 (i.e. Linear quantization)
							   Values other than 1 indicate some
							   form of compression.
22        2   Channels      Mono = 1, Stereo = 2, etc.
24        4   SampleRate       8000, 44100, etc.
28        4   ByteRate         = SampleRate * Channels * BitsPerSample/8
32        2   BlockAlign       = Channels * BitsPerSample/8
							   The number of bytes for one sample including
							   all channels. I wonder what happens when
							   this number isn't an integer?
34        2   BitsPerSample    8 bits = 8, 16 bits = 16, etc.
		  2   ExtraParamSize   if PCM, then doesn't exist
		  X   ExtraParams      space for extra parameters

The "data" subchunk contains the size of the data and the actual sound:

36        4   Subchunk2ID      Contains the letters "data"
							   (0x64617461 big-endian form).
40        4   Subchunk2Size    = NumSamples * Channels * BitsPerSample/8
							   This is the number of bytes in the data.
							   You can also think of this as the size
							   of the read of the subchunk following this
							   number.
44        *   Data             The actual sound data.


As an example, here are the opening 72 bytes of a WAVE file with bytes shown as hexadecimal numbers:
*/
// RIFF:
// 52 49 46 46 24 08 00 00 57 41 56 45
// R  I  F  F  |ChunkSize| W  A  V  E
struct wavRIFF
{
	uint8_t RIFF[4]; // 4 _ 'RIFF' | Resource Interchange File Format
	uint32_t ChunkSize; // 4 _ make sure to read only 4 bits | I think it works like this: (4 + (8 + Subchunk1Size) + (8 + Subchunk2Size))
	uint8_t WAVE[4]; // 4 _ 'WAVE'
	// TOTAL: 12
};

// wavFMT:
// 66 6d 74 20 10 00 00 00 01 00 02 00
// F  M  T     |SubChunk1S|AuFor|Channels
// 22 56 00 00 88 58 01 00 04 00 10 00
// SampleRate | ByteRate |BlkAlig|BPS|
struct wavFMT
{
	uint8_t fmt[4]; // 4 _ 'fmt ' | Subchunk1ID
	uint32_t Size; // 4 _ Subchunk1Size
	uint16_t AudioFormat; // 2 _ PCM = 1 (i.e. Linear quantization). Values other than 1 indicate some form of compression.
	uint16_t Channels; // 2 _ Mono = 1, Stereo = 2, etc.
	uint32_t SRate; // 4
	uint32_t ByteRate; // 4 _ == SampleRate * Channels * BitsPerSample / 8
	uint16_t BlockAlign; // 2 _ == Channels * BitsPerSample / 8 | The number of bytes for one sample including all channels. I wonder what happens when this number isn't an integer?
	uint16_t BitsPerSample; // 2 _ 8 bits = 1 byte, 16 bits = 2 bytes, etc.
	// TOTAL: 24 + 12 = 36
};

// wavDATA:
// 64 61 74 61 00 08 00 00
// d  a  t  a |SubChunk2S|
struct wavDATA
{
	uint8_t ID[4]; // 4 _ 'data' | Subchunk2ID
	uint32_t Size; // 4 _ Subchunk2Size | Count all data per bits-per-sample
	// TOTAL: 8 + 24 + 12 = 44
};

/*Samples 16-bits:
00 00.00 00    24 17.1e f3	  3c 13.3c 14	 16 f9.18 f9...
LEFT | RIGHT | LEFT | RIGHT | LEFT | RIGHT | LEFT | RIGHT
Sample 1	   Sample 2		  Sample 3		 Sample 4...

SHORT INT Max and Min values (2 bytes):
signed: 32767 & -32768 | unsigned: 65535*/

// #####################################################################################################################################

// RETURN AN EMPTY HEADER TEMPLATE:
std::string WAVEHeaderHex()
{
	// decimal: 2948802364898608268190755917197372413344555719335282424875914519085364177445035852103193336182040757796864
	return("52494646a400000057415645666d7420100000000100010044ac000088580100020010006461746180000000"); // A WAVE FILE HEADER IN HEXADECIMAL:
}

// #####################################################################################################################################
// ####### CLASSES #######

class WAVEFile
{
public:
	enum ByteMapping
	{
		bRIFF = 0, bChunkSize = 4, bFormat = 8, bSubChunk1ID = 12, bSubChunk1Size = 16, bAudioFormat = 20, bChannels = 22, bSRate = 24,
		bByteRate = 28, bBlockAlign = 32, bBitsPetSample = 34, bSubChunk2ID = 36, bSubchunk2Size = 40, bDataBeg = 44
	};
	std::string Path; std::fstream wavFile; uint32_t FileSize; // File stuffs
	wavRIFF RIFF; wavFMT FMT; wavDATA DATA; // Header chunks

	// #################################################
	// #################################################
	// #################################################

	WAVEFile(std::string OpenFile)
	{
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(OpenFile, std::ios::in | std::ios::out | std::ios::binary);
		Path = OpenFile;
		ReadHeader();
		// NUMBER OF BYTES:
		wavFile.seekg(0, std::ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, std::ios::beg);
	}

	WAVEFile(std::string FileName, uint32_t SampleRate, uint16_t Channels = 1, uint8_t BitsPerSample = 8)
	{
		std::ofstream CREATE(FileName, std::ios::binary); CREATE.close();
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(FileName, std::ios::in | std::ios::out | std::ios::binary);
		Path = FileName;
		RIFF.RIFF[0] = 'R'; RIFF.RIFF[1] = 'I'; RIFF.RIFF[2] = 'F'; RIFF.RIFF[3] = 'F';
		RIFF.ChunkSize = 36;
		RIFF.WAVE[0] = 'W'; RIFF.WAVE[1] = 'A'; RIFF.WAVE[2] = 'V'; RIFF.WAVE[3] = 'E';

		FMT.fmt[0] = 'f'; FMT.fmt[1] = 'm'; FMT.fmt[2] = 't'; FMT.fmt[3] = ' ';
		FMT.Size = 16;
		FMT.AudioFormat = 1;
		FMT.BitsPerSample = BitsPerSample;
		FMT.Channels = Channels;
		FMT.SRate = SampleRate;
		FMT.BlockAlign = FMT.Channels * (FMT.BitsPerSample / 8);
		FMT.ByteRate = FMT.SRate * FMT.BlockAlign;
		
		DATA.ID[0] = 'd'; DATA.ID[1] = 'a'; DATA.ID[2] = 't'; DATA.ID[3] = 'a';
		DATA.Size = 0;
		
		//WAVEHeaderHexWriteIt();
		WriteHeader();
		ReadHeader();
		
		// NUMBER OF BYTES:
		wavFile.seekg(0, std::ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, std::ios::beg);
	}

	~WAVEFile() { wavFile.close(); }

	void ReOpenFile()
	{
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(Path, std::ios::in | std::ios::out | std::ios::binary);
		ReadHeader();
		// NUMBER OF BYTES:
		wavFile.seekg(0, std::ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, std::ios::beg);
		wavFile.seekp(0, std::ios::beg);
	}


	// #################################################
	// #################################################
	// #################################################
	
	// TOOLS:
	// GET CHUNK SIZE:
	//int GetChunkSize() { return(36 + DATA.Size); }
	uint32_t GetChunkSize() { return(20 + FMT.Size + DATA.Size); }
	void SetChunkSize() { RIFF.ChunkSize = 20 + FMT.Size + DATA.Size; }

	// CHECK IF THE CHUNK IS SIZED CORRECTLY:
	bool IsSizeCorrect() { if (RIFF.ChunkSize == 20 + FMT.Size + DATA.Size) { return(true); } return(false); }

	// #################################################
	// #################################################
	// #################################################

	// GET NUMBER OF BYTES:
	void RefreshFileSize() { wavFile.seekg(0, std::ios::end); FileSize = wavFile.tellg(); wavFile.seekg(0, std::ios::beg); }

	// PREPARE CHUNK STRUCTURES:
	void ReadHeader()
	{
		wavFile.read((char*)&RIFF, sizeof(wavRIFF));
		wavFile.read((char*)&FMT, sizeof(wavFMT));
		wavFile.read((char*)&DATA, sizeof(wavDATA));
		wavFile.seekg(0, std::ios::beg);
	}

	// REFRESH HEADER VALUES:
	void RefreshHeader()
	{
		FileSize < 45 ? DATA.Size = 0 : DATA.Size = FileSize - 44;
		SetChunkSize();
		FMT.BlockAlign = FMT.Channels * (FMT.BitsPerSample / 8);
		FMT.ByteRate = FMT.SRate * FMT.BlockAlign;		
	}

	// CHANGE SAMPLE RATE IN HEADER FILE AND THE OBJECTS THAT DEPENDS OF IT:
	void ChangeSRate(uint32_t NewSRate)
	{
		FMT.SRate = NewSRate;
		FMT.BlockAlign = FMT.Channels * (FMT.BitsPerSample / 8);
		FMT.ByteRate = FMT.SRate * FMT.BlockAlign;
	}

	// CHANGE NUMBER OF CHANNELS IN HEADER FILE AND THE OBJECTS THAT DEPENDS OF IT:
	void ChangeChannels(uint32_t NumChannels)
	{
		FMT.Channels = NumChannels;
		FMT.BlockAlign = FMT.Channels * (FMT.BitsPerSample / 8);
		FMT.ByteRate = FMT.SRate * FMT.BlockAlign;
	}

	// WRITE HEADER:
	void WriteHeader() // 12 24 8
	{
		wavFile.seekp(0, std::ios::beg);
		char Buf[44]; char* p = Buf;
		RefreshFileSize(); RefreshHeader();
		wavFile.write((char*)&RIFF, sizeof(wavRIFF));
		wavFile.write((char*)&FMT, sizeof(wavFMT));
		wavFile.write((char*)&DATA, sizeof(wavDATA));
		wavFile.seekp(0, std::ios::beg);
	}

	// WRITE NEW HEADER:
	void WriteNewHeader() // 12 24 8
	{
		
	}

	// CLEAR DATA, MAINTAIN HEADER:
	void ClearData() // Not sure what happens if you save like that.
	{
		wavFile.close();
		std::ofstream CLEAN(Path); // Open and close to clean
		CLEAN.close(); // Clean!
		wavFile.open(Path, std::ios::in | std::ios::out | std::ios::binary);
		RefreshFileSize(); // So the writter will set Data size to '0';
		WriteHeader();
		// NUMBER OF BYTES:
		RefreshFileSize(); // Re-writes FileSize
	}

	void ReWriteSizes()
	{
		wavFile.seekg(0, std::ios::end);
		FileSize = wavFile.tellg();
		DATA.Size = (FileSize - 44) / (FMT.BitsPerSample / 8);
		SetChunkSize();
		wavFile.seekp(4); wavFile.write((char*)&RIFF.ChunkSize, sizeof(uint32_t));
		wavFile.seekp(40); wavFile.write((char*)&DATA.Size, sizeof(uint32_t));
		wavFile.seekp(0, std::ios::beg); wavFile.seekg(0, std::ios::beg);
	}

	// #################################################

	void CoutHeaderInfo()
	{
		std::cout << "#####################\nPath: " << Path << "\n#####################\n\n";
		std::cout << "RIFF[4]: " << RIFF.RIFF << '\n';
		std::cout << "ChunkSize: " << RIFF.ChunkSize << " = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size) =\n               | 4 + (8 + " << FMT.Size << ") + (8 + " << DATA.Size << ") =\n";
		std::cout << "               | 4 + (" << 8 + FMT.Size << ") + (" << 8 + DATA.Size << ") = 4 + (" << 8 + FMT.Size + 8 + DATA.Size << ")\n\n";
		std::cout << "Wave[4]: " << RIFF.WAVE << "\n\n";

		std::cout << "fmt[4]: " << FMT.fmt << '\n';
		std::cout << "Subchunk1Size: " << FMT.Size << '\n';
		std::cout << "AudioFormat: " << FMT.AudioFormat << '\n';
		std::cout << "Channels: " << FMT.Channels << '\n';
		std::cout << "SampleRate: " << FMT.SRate << '\n';
		std::cout << "ByteRate: " << FMT.ByteRate << " = SampleRate * BlockAlign = " << FMT.SRate << " * " << FMT.BlockAlign << '\n';
		std::cout << "BlockAlign: " << FMT.BlockAlign << " = Channels * BitsPerSample / 8 = " << FMT.Channels << " * " << FMT.BitsPerSample / 8 << '\n';
		std::cout << "BitsPerSample: " << FMT.BitsPerSample << "\n\n";

		std::cout << "Subchunk2ID: " << DATA.ID << '\n';
		std::cout << "Subchunk2Size: " << DATA.Size << "\nNOTE: 'uint16_t' size is '2 bytes', Fixed size to 'uint16_t': " << DATA.Size / 2 << "\n\n";
		std::cout << "#####################\n\n";

		std::cout << "CLASS INFO:\n";
		std::cout << "FileSize: " << FileSize << '\n';
		std::cout << "sizeof(WAVEFile): " << sizeof(WAVEFile) << '\n';

		std::cout << "#####################\n" << std::endl;
	}

	std::string StringHeaderInfo()
	{
		std::string s = "#####################\nPath: " + Path + "\n#####################\n\n";
		s += "ChunkSize: " + std::to_string(RIFF.ChunkSize) + " = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size) =\n               | 4 + (8 + " + std::to_string(FMT.Size);
		s += ") + (8 + " + std::to_string(DATA.Size) + ") =\n";
		s += "               | 4 + (" + std::to_string(8 + FMT.Size) + ") + (" + std::to_string(8 + DATA.Size) + ") = 4 + (" + std::to_string(8 + FMT.Size + 8 + DATA.Size) + ")\n\n";
		s += "Wave[4]: " + RIFF.WAVE[0] + RIFF.WAVE[1] + RIFF.WAVE[2] + RIFF.WAVE[3]; s += +"\n\n";

		s += "fmt[4]: " + FMT.fmt[0] + FMT.fmt[1] + FMT.fmt[2] + FMT.fmt[3]; s += '\n';
		s += "Subchunk1Size: " + std::to_string(FMT.Size) + '\n';
		s += "AudioFormat: " + std::to_string(FMT.AudioFormat) + '\n';
		s += "Channels: " + std::to_string(FMT.Channels) + '\n';
		s += "SampleRate: " + std::to_string(FMT.SRate) + '\n';
		s += "ByteRate: " + std::to_string(FMT.ByteRate) + " = SampleRate * BlockAlign = " + std::to_string(FMT.SRate) + " * " + std::to_string(FMT.BlockAlign) + '\n';
		s += "BlockAlign: " + std::to_string(FMT.BlockAlign) + " = Channels * BitsPerSample / 8 = " + std::to_string(FMT.Channels) + " * " + std::to_string(FMT.BitsPerSample / 8) + '\n';
		s += "BitsPerSample: " + std::to_string(FMT.BitsPerSample) + "\n\n";

		s += "Subchunk2ID: " + DATA.ID[0] + DATA.ID[1] + DATA.ID[2] + DATA.ID[3]; s += '\n';
		s += "Subchunk2Size: " + std::to_string(DATA.Size) + "\nNOTE: 'uint16_t' size is '2 bytes', Fixed size to 'uint16_t': " + std::to_string(DATA.Size / 2) + "\n\n";
		s += "#####################\n\n";

		s += "CLASS INFO:\n";
		s += "FileSize: " + std::to_string(FileSize) + '\n';
		s += "sizeof(WAVEFile): " + std::to_string(sizeof(WAVEFile)) + '\n';

		s += "#####################\n\n";
		return(s);
	}

	// #################################################
	// #################################################
	// #################################################

	// #################################################

	template <class T_>
	std::vector<T_> GetAllData()
	{
		wavFile.seekg(0, std::ios::end);
		uint32_t End = wavFile.tellg();
		wavFile.seekg(FileSize - DATA.Size * (FMT.BitsPerSample / 8)); // First sample
		uint32_t Size = End - (FileSize - DATA.Size * (FMT.BitsPerSample / 8)); // Size by input type
		std::vector<T_> v(ceil(Size / (float)sizeof(T_)));
		wavFile.read((char*)&v[0], sizeof(T_) * v.size());
		wavFile.seekg(0, std::ios::beg);
		return(v);
	}

	// #################################################

	// GET DATA:
	template <class T_>
	std::vector<T_> GetData(size_t Index, size_t Size)
	{
		uint8_t B = sizeof(T_);
		std::vector<T_> GETDATA(Size);
		Index *= B; Size *= B;
		wavFile.seekg(0, std::ios::end);
		size_t End = wavFile.tellg();
		size_t pos = End - DATA.Size;
		size_t Beg = pos + Index;
		if (Beg + Size > End) { Size -= Beg + Size - End; End = Beg + Size; }
		else { End = Index + Size + pos; }
		wavFile.seekg(Beg);
		wavFile.read((char*)&GETDATA[0], Size);
		wavFile.seekg(0, std::ios::beg);
		return(GETDATA);
	}

	// GET DATA FROM EITHER LEFT OR RIGHT CHANNEL:
	template <class T_>
	std::vector<T_> GetDataByChannel(size_t Index, size_t Size, bool LeftRight = false)
	{
		uint8_t B = sizeof(T_);
		std::vector<T_> GETDATA;
		Index *= B; Size *= B;
		wavFile.seekg(0, std::ios::end);
		size_t End = wavFile.tellg();
		size_t pos = End - DATA.Size;
		size_t Beg = pos + Index;
		if (Beg + Size > End) { Size -= Beg + Size - End; End = Beg + Size; }
		else { End = Index + Size + pos; }
		uint16_t Read;

		wavFile.seekg(Beg);		
		for (size_t n = Beg; n < End; )
		{
			if (!LeftRight)
			{
				wavFile.read((char*)&Read, B);
				GETDATA.push_back(Read); LeftRight = true;
			}
			else { LeftRight = false; }
			n = wavFile.tellg();
		}
		wavFile.seekg(0, std::ios::beg);
		return(GETDATA);
	}

	// #################################################

	// GET DATA READY TO WORK AS A DOUBLE VECTOR, IGNORE LeftRight IF THERE IS ONLY ONE CHANNEL.
	// 'FMT.BitsPerSample / 8' must be equal to 'sizeof(T_)'.
	// The function begins JUST AFTER the end of the '.wav' header, if you want 'Size' to reach the End of file, use it equal as "DATA.Size":
	template <class T_>
	std::vector<double> GetDataReadyToUse(uint32_t Index, uint32_t Size, bool LeftRight = false)
	{
		uint8_t B = sizeof(T_);
		wavFile.seekg(0, std::ios::end);
		uint32_t eof = wavFile.tellg();
		uint32_t Beg = (eof - (DATA.Size * B)) + Index; if (Beg >= eof) { Beg = eof - B; Size = B; }
		wavFile.seekg(Beg);
		uint32_t End = Beg + Size; if (End > eof) { End = eof; }
		std::vector<double> GETDATA(End - Beg);
		
		if (B == FMT.BitsPerSample / 8)
		{
			if (B == 0) { B = 1; } //if (B > 2) { B = 2; }
			if (!(FMT.BitsPerSample % 8)) // !!! PARA GARANTIR O NUMERO DE BYTES PARA OS COMPARADORES !!!
			{
				Index *= B; Size *= B;
				for (uint32_t n = Beg; n < End; )
				{
					double Push;
					T_ Val; wavFile.read((char*)&Val, B);
					Push = (2 * Val / (pow(256, B) - 1)) - 1;
					if (FMT.Channels == 1) { GETDATA[n - Beg] = Push; }
					else { if (!LeftRight) { GETDATA[n - Beg] = Push; LeftRight = true; } else { LeftRight = false; } }
					n = wavFile.tellg();
				}
				wavFile.seekg(0, std::ios::beg);
			}
			else { std::cerr << "Bits per sample needs to be equal to 2^n!"; }
		}
		else { std::cerr << "size of 'Type' (T_) is different than 'FMT.BitPerSample / 8'!"; }
		return(GETDATA);
	}

	// #################################################
	// #################################################
	// #################################################
		
	// PREPARE DATA TO OUTPUT: (!!! ATTENTION: This function Multiplies the data by 32767 !!!)
	template <class T_>
	std::vector<T_> PrepareData(std::vector<double> In)
	{
		std::vector<T_> Buf(In.size());
		for (size_t n = 0; n < In.size(); ++n)	{ Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1)); }
		return(Buf);
	}
	template <class T_>
	std::vector<T_> PrepareData(std::vector<float> In)
	{
		std::vector<T_> Buf(In.size());
		for (size_t n = 0; n < In.size(); ++n) { Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1)); }
		return(Buf);
	}

	// #################################################

	// SAVE DATA FULL:
	template <class T_>	void SaveData(std::vector<double> In)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		wavFile.seekp(44);
		for (size_t n = 0; n < Is; ++n)
		{
			for (uint8_t Channel = 0; Channel < FMT.Channels; ++Channel)
			{
				if (In[n] > 1) { In[n] = 1; } if (In[n] < -1) { In[n] = -1; }
				Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
				wavFile.write((char*)&Buf[n], sizeof(T_));
			}
		}
		ReWriteSizes(); ReOpenFile();
	}

	template <class T_>	void SaveData(std::vector<double> In, bool LeftRight)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		wavFile.seekp(44); uint16_t Bs = sizeof(T_);
		for (size_t n = 0; n < Buf.size(); ++n)
		{
			//for (size_t Channel = 0; Channel < FMT.Channels; ++Channel)
			//{
				if (LeftRight) { wavFile.seekp(wavFile.tellp() + Bs); }
				Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
				wavFile.write((char*)&Buf[n], sizeof(T_));
				if (!LeftRight) { wavFile.seekp(wavFile.tellp() + Bs); }
			//}
		}
		ReWriteSizes(); ReOpenFile();
	}

	template <class T_>	void SaveDataT_(std::vector<T_> In)
	{ wavFile.seekp(44); for (size_t n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(T_)); } ReWriteSizes(); ReOpenFile(); }
	template <class T_>	void SaveDataT_(T_* In, uint32_t Size)
	{ wavFile.seekp(44); for (size_t n = 0; n < Size; ++n) { wavFile.write((char*)&In[n], sizeof(T_)); } ReWriteSizes(); ReOpenFile(); }

	// #################################################
	
	// SAVE DATA INDEX:
	template <class T_> void SaveDataIndex(std::vector<double> In, uint32_t Index)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		size_t Beg = (Index * sizeof(T_)) + 44; wavFile.seekp(Beg);
		for (size_t n = 0; n < Is; ++n)
		{
			for (uint8_t Channel = 0; Channel < FMT.Channels; ++Channel)
			{
				if (In[n] > 1) { In[n] = 1; } if (In[n] < -1) { In[n] = -1; }
				Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
				wavFile.write((char*)&Buf[n], sizeof(T_));
			}
		}
		ReWriteSizes(); ReOpenFile();
	}

	template <class T_> void SaveDataIndex(std::vector<float> In, uint32_t Index)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		size_t Beg = (Index * sizeof(T_)) + 44; wavFile.seekp(Beg);
		for (size_t n = 0; n < Is; ++n)
		{
			for (uint8_t Channel = 0; Channel < FMT.Channels; ++Channel)
			{
				if (In[n] > 1) { In[n] = 1; } if (In[n] < -1) { In[n] = -1; }
				Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
				wavFile.write((char*)&Buf[n], sizeof(T_));
			}
		}
		ReWriteSizes(); ReOpenFile();
	}

	template <class T_> void SaveDataT_Index(std::vector<T_> In, uint32_t Index)
	{
		size_t Beg = (Index * sizeof(T_)) + 44; wavFile.seekp(Beg);
		for (size_t n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(T_)); }
		ReWriteSizes();	ReOpenFile();
	}
	template <class T_> void SaveDataT_Index(T_* In, uint32_t Size, uint32_t Index)
	{
		size_t Beg = (Index * sizeof(T_)) + 44; wavFile.seekp(Beg);
		for (size_t n = 0; n < Size; ++n) { wavFile.write((char*)&In[n], sizeof(T_)); }
		ReWriteSizes();	ReOpenFile();
	}

	// #################################################

	// APPEND DATA:
	template <class T_>	void AppData(std::vector<double> In)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		wavFile.seekp(0, std::ios::end);
		for (size_t n = 0; n < Is; ++n)
		{
			for (uint8_t Channel = 0; Channel < FMT.Channels; ++Channel)
			{
				if (In[n] > 1) { In[n] = 1; } if (In[n] < -1) { In[n] = -1; }
				Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
				wavFile.write((char*)&Buf[n], sizeof(T_));
			}
		}
		ReWriteSizes(); ReOpenFile();
	}
	template <class T_>	void AppData(std::vector<double> In, bool LeftRight)
	{
		size_t Is = In.size();
		std::array<T_, Is> Buf;
		wavFile.seekp(0, std::ios::end); uint16_t Bs = sizeof(T_);
		for (size_t n = 0; n < Buf.size(); ++n)
		{
			if (LeftRight) { wavFile.seekp(wavFile.tellp() + Bs); }
			Buf[n] = round((In[n] + 1) * 0.5 * (pow(256, sizeof(T_)) - 1));
			wavFile.write((char*)&Buf[n], sizeof(T_));
			if (!LeftRight) { wavFile.seekp(wavFile.tellp() + Bs); }
		}
		ReWriteSizes(); ReOpenFile();
	}

	template <class T_>	void AppDataT_(std::vector<T_> In)
	{ wavFile.seekp(0, std::ios::end); for (size_t n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(T_)); } ReWriteSizes(); ReOpenFile(); }
	template <class T_>	void AppDataT_(T_* In, uint32_t Size)
	{ wavFile.seekp(0, std::ios::end); for (size_t n = 0; n < Size; ++n) { wavFile.write((char*)&In[n], sizeof(T_)); } ReWriteSizes(); ReOpenFile(); }
};

#endif // SCPARSE_