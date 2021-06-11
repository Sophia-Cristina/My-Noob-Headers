#pragma once

#ifndef YSXWAVE_H
#define YSXWAVE_H

#include <vector>
#include <iostream>

// #####################################################################################################################################
/*
// http://soundfile.sapp.org/doc/WaveFormat/

Notes:
 * The default byte ordering assumed for WAVE data files is little-endian. Files written using the big-endian byte ordering scheme have the identifier RIFX instead of RIFF.
 * The sample data must end on an even byte boundary. Whatever that means.
 * 8-bit samples are stored as unsigned bytes, ranging from 0 to 255. 16-bit samples are stored as 2's-complement signed integers, ranging from -32768 to 32767.
 * There may be additional subchunks in a Wave data stream. If so, each will have a char[4] SubChunkID, and unsigned long SubChunkSize, and SubChunkSize amount of data.
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
22        2   NumChannels      Mono = 1, Stereo = 2, etc.
24        4   SampleRate       8000, 44100, etc.
28        4   ByteRate         == SampleRate * NumChannels * BitsPerSample/8
32        2   BlockAlign       == NumChannels * BitsPerSample/8
							   The number of bytes for one sample including
							   all channels. I wonder what happens when
							   this number isn't an integer?
34        2   BitsPerSample    8 bits = 8, 16 bits = 16, etc.
		  2   ExtraParamSize   if PCM, then doesn't exist
		  X   ExtraParams      space for extra parameters

The "data" subchunk contains the size of the data and the actual sound:

36        4   Subchunk2ID      Contains the letters "data"
							   (0x64617461 big-endian form).
40        4   Subchunk2Size    == NumSamples * NumChannels * BitsPerSample/8
							   This is the number of bytes in the data.
							   You can also think of this as the size
							   of the read of the subchunk following this
							   number.
44        *   Data             The actual sound data.


As an example, here are the opening 72 bytes of a WAVE file with bytes shown as hexadecimal numbers:

RIFFChunk:
52 49 46 46 24 08 00 00 57 41 56 45
R  I  F  F  |ChunkSize| W  A  V  E

FMTChunk:
66 6d 74 20 10 00 00 00 01 00 02 00
F  M  T     |SubChunk1S|AuFor|NumChannels
22 56 00 00 88 58 01 00 04 00 10 00
SampleRate | ByteRate |BlkAlig|BPS|

DataChunk:
64 61 74 61 00 08 00 00
d  a  t  a |SubChunk2S|

Samples:
00 00 00 00
LEFT | RIGHT
Sample 1

24 17 1e f3
LEFT | RIGHT
Sample 2

3c 13 3c 14
LEFT | RIGHT
Sample 3

16 f9 18 f9
LEFT | RIGHT
Sample 4

34 e7 23 a6
LEFT | RIGHT
Sample 5

3c f2 24 f2
LEFT | RIGHT
Sample 6

11 ce 1a 0d
LEFT | RIGHT
Sample 7

SHORT INT Max and Min values (2 bytes):
signed: 32767 & -32768 | unsigned: 65535

*/
// #####################################################################################################################################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// ####### STRUCTS #######
// INDEX:


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// ####### OBJECTS #######


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// ####### FUNCTIONS #######

std::string WAVEHeaderHex()
{
	return("52494646a400000057415645666d7420100000000100010044ac000088580100020010006461746180000000"); // A WAVE FILE HEADER IN HEXADECIMAL:
}

std::string MemoHeaderChar() // !!!!!!! NOT WORKING !!!!!!!
{
	std::string Return;
	char Buffer[44]; char* p = Buffer;
	char RIFF[4]; char * q = (char*)RIFF; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	unsigned int ChunkSize = 36; q = (char*)&ChunkSize; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	char WAVE[4]; q = (char*)WAVE; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	char fmt[4]; q = (char*)fmt; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	unsigned int Size = 16; q = (char*)&Size; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	short int AudioFormat = 1; q = (char*)&AudioFormat; for (int n = 0; n < 2; ++n) { *p = *q; ++p; ++q; }
	short int NumChannels = 1; q = (char*)&NumChannels; for (int n = 0; n < 2; ++n) { *p = *q; ++p; ++q; }
	unsigned int SampleRate = 44100; q = (char*)&SampleRate; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	unsigned int ByteRate = 88200; q = (char*)&ByteRate; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	short int BlockAlign = 2; q = (char*)&BlockAlign; for (int n = 0; n < 2; ++n) { *p = *q; ++p; ++q; }
	short int BitsPerSample = 16; q = (char*)&BitsPerSample; for (int n = 0; n < 2; ++n) { *p = *q; ++p; ++q; }
	char ID[4]; q = (char*)ID; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	unsigned int Size2 = 0; q = (char*)&Size2; for (int n = 0; n < 4; ++n) { *p = *q; ++p; ++q; }
	Return = Buffer;
	
	return(Return);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// ####### CLASSES #######

class WAVEFile
{
public:
	const int HeaderSize = 44;
	std::string Path;
	fstream wavFile;
	int FileSize;

	// #################################################
	// #################################################
	// #################################################

	WAVEFile(std::string InputPath)
	{
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(InputPath, ios::in | ios::out | ios::binary);
		Path = InputPath;
		ReadHeader();
		// NUMBER OF BYTES:
		wavFile.seekg(0, ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, ios::beg);
	}

	WAVEFile(std::string FileName, unsigned int SampleRate, short int Channels)
	{
		FileName += ".wav";
		ofstream CREATE(FileName, ios::binary);
		CREATE.close();
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(FileName, ios::in | ios::out | ios::binary);
		Path = FileName;
		RIFFChnk.RIFF[0] = 'R'; RIFFChnk.RIFF[1] = 'I'; RIFFChnk.RIFF[2] = 'F'; RIFFChnk.RIFF[3] = 'F';
		RIFFChnk.ChunkSize = 36;
		RIFFChnk.WAVE[0] = 'W'; RIFFChnk.WAVE[1] = 'A'; RIFFChnk.WAVE[2] = 'V'; RIFFChnk.WAVE[3] = 'E';

		FMTChnk.fmt[0] = 'f'; FMTChnk.fmt[1] = 'm'; FMTChnk.fmt[2] = 't'; FMTChnk.fmt[3] = ' ';
		FMTChnk.Size = 16;
		FMTChnk.AudioFormat = 1;
		FMTChnk.BitsPerSample = 16;
		FMTChnk.NumChannels = Channels;
		FMTChnk.SampleRate = SampleRate;
		FMTChnk.BlockAlign = FMTChnk.NumChannels * (FMTChnk.BitsPerSample / 8);
		FMTChnk.ByteRate = FMTChnk.SampleRate * FMTChnk.BlockAlign;
		
		DATAChnk.ID[0] = 'd'; DATAChnk.ID[1] = 'a'; DATAChnk.ID[2] = 't'; DATAChnk.ID[3] = 'a';
		DATAChnk.Size = 0;
		
		//WAVEHeaderHexWriteIt();
		WriteHeader();
		ReadHeader();
		
		// NUMBER OF BYTES:
		wavFile.seekg(0, ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, ios::beg);
	}

	~WAVEFile() { wavFile.close(); }

	void ReOpenFile()
	{
		if (wavFile.is_open()) { wavFile.close(); }
		wavFile.open(Path, ios::in | ios::out | ios::binary);
		Path = Path;
		ReadHeader();
		// NUMBER OF BYTES:
		wavFile.seekg(0, ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, ios::beg);
	}

	// #################################################
	// #################################################
	// #################################################
	enum ByteMapping
	{
		RIFF = 0, ChunkSize = 4, Format = 8, SubChunk1ID = 12, SubChunk1Size = 16, AudioFormat = 20, NumChannels = 22, SampleRate = 24,
		ByteRate = 28, BlockAlign = 32, BitsPetSample = 34, SubChunk2ID = 36, Subchunk2Size = 40, DataBegin = 44
	};

	struct RIFFChunk
	{
		char RIFF[4]; // 4 - 'RIFF' | Resource Interchange File Format
		unsigned int ChunkSize; // 4 - make sure to read only 4 bits | I think it works like this: (4 + (8 + Subchunk1Size) + (8 + Subchunk2Size))
		char WAVE[4]; // 4 - 'WAVE'
		// TOTAL: 12
	};

	struct FMTChunk
	{
		char fmt[4]; // 4 - 'fmt ' | Subchunk1ID
		unsigned int Size; // 4 - Subchunk1Size
		short int AudioFormat; // 2 - PCM = 1 (i.e. Linear quantization). Values other than 1 indicate some form of compression.
		short int NumChannels; // 2 - Mono = 1, Stereo = 2, etc.
		unsigned int SampleRate; // 4
		unsigned int ByteRate; // 4 - == SampleRate * NumChannels * BitsPerSample / 8
		short int BlockAlign; // 2 - == NumChannels * BitsPerSample / 8 | The number of bytes for one sample including all channels. I wonder what happens when this number isn't an integer?
		short int BitsPerSample; // 2 - 8 bits = 1 byte, 16 bits = 2 bytes, etc.
		// TOTAL: 24 + 12 = 36
	};

	struct DataChunk
	{
		char ID[4]; // 4 - 'data' | Subchunk2ID
		unsigned int Size; // 4 - Subchunk2Size | Count all data per bits-per-sample
		// TOTAL: 8 + 24 + 12 = 44
	};

	// #################################################

	RIFFChunk RIFFChnk; FMTChunk FMTChnk; DataChunk DATAChnk; // Chunks

	// #################################################
	// #################################################
	// #################################################
	
	// TOOLS:
	// GET CHUNK SIZE:
	//int GetChunkSize() { return(36 + DATAChnk.Size); }
	unsigned int GetChunkSize() { return(4 + (8 + FMTChnk.Size) + (8 + DATAChnk.Size)); }

	// GET DATA SIZE (Data Chunk):
	unsigned int GetDataSize() { RefreshFileSize(); return(FileSize - 44); }

	// CHECK IF THE CHUNK IS SIZED CORRECTLY:
	bool IsChunkSizeCorrect() { if (RIFFChnk.ChunkSize == (4 + (8 + FMTChnk.Size) + (8 + DATAChnk.Size))) { return(true); } else { return(false); } }

	// WRITE THE HEX STRING TO HEADER (STANDARD HEADER, WHEN YOU CREATE YOUR OWN WAV):
	/*void WAVEHeaderHexWriteIt()
	{
		std::string Buffer = Hex2ASCII(WAVEHeaderHex());
		char* p = (char*)&Buffer.at(0);

		char* q = (char*)&RIFFChnk; for (int n = 0; n < 12; ++n) { *q = *p; ++q; ++p; }
		q = (char*)&FMTChnk; for (int n = 0; n < 24; ++n) { *q = *p; ++q; ++p; }
		q = (char*)&DATAChnk; for (int n = 0; n < 8; ++n) { *q = *p; ++q; ++p; }
		GetDataSize(); GetChunkSize();
	}*/

	// #################################################
	// #################################################
	// #################################################

	typedef vector<int> DATAINT;
	typedef vector<float> DATAFLT;
	typedef vector<short int> DATASHINT;

	// #################################################
	// #################################################
	// #################################################

	// GET NUMBER OF BYTES:
	void RefreshFileSize()
	{
		wavFile.seekg(0, ios::end);
		FileSize = wavFile.tellg();
		wavFile.seekg(0, ios::beg);
	}

	// PREPARE CHUNK STRUCTURES:
	void ReadHeader()
	{
		wavFile.read((char*)&RIFFChnk, sizeof(RIFFChunk));
		wavFile.read((char*)&FMTChnk, sizeof(FMTChunk));
		wavFile.read((char*)&DATAChnk, sizeof(DataChunk));
		wavFile.seekg(0, ios::beg);
	}

	// REFRESH THE HEADER VALUES:
	void RefreshHeader()
	{
		if (FileSize <= 44) { DATAChnk.Size = 0; }	else { DATAChnk.Size = GetDataSize(); } RIFFChnk.ChunkSize = GetChunkSize();
		FMTChnk.BlockAlign = FMTChnk.NumChannels * (FMTChnk.BitsPerSample / 8);
		FMTChnk.ByteRate == FMTChnk.SampleRate * FMTChnk.BlockAlign;
		
	}

	// CHANGE SAMPLE RATE IN HEADER FILE AND THE OBJECTS THAT DEPENDS ON IT:
	void ChangeSampleRate(unsigned int NewSampleRate)
	{
		FMTChnk.SampleRate = NewSampleRate;
		FMTChnk.BlockAlign = FMTChnk.NumChannels * (FMTChnk.BitsPerSample / 8);
		FMTChnk.ByteRate = FMTChnk.SampleRate * FMTChnk.BlockAlign;
	}

	// CHANGE NUMBER OF CHANNELS IN HEADER FILE AND THE OBJECTS THAT DEPENDS ON IT:
	void ChangeNumChannels(unsigned int NewNumChannels)
	{
		FMTChnk.NumChannels = NewNumChannels;
		FMTChnk.BlockAlign = FMTChnk.NumChannels * (FMTChnk.BitsPerSample / 8);
		FMTChnk.ByteRate = FMTChnk.SampleRate * FMTChnk.BlockAlign;
	}

	// WRITE HEADER:
	void WriteHeader() // 12 24 8
	{
		wavFile.seekp(0, ios::beg);
		char Buffer[44]; char* p = Buffer;
		RefreshFileSize();
		RefreshHeader();

		// 12 + 24 + 8
		char* q = (char*)&RIFFChnk; for (int n = 0; n < 12; ++n) { *p = *q; ++p; ++q; }
		q = (char*)&FMTChnk; for (int n = 0; n < 24; ++n) { *p = *q; ++p; ++q; }
		q = (char*)&DATAChnk; for (int n = 0; n < 8; ++n) { *p = *q; ++p; ++q; }
		wavFile.write(Buffer, sizeof(Buffer));
		wavFile.seekp(0, ios::beg);
	}

	// WRITE NEW HEADER:
	void WriteNewHeader() // 12 24 8
	{
		
	}

	// CLEAR DATA, MAINTAIN HEADER:
	void ClearData() // Not sure what happens if you save like that.
	{
		wavFile.close();
		ofstream CLEAN(Path); // Open and close to clean
		CLEAN.close(); // Clean!
		wavFile.open(Path, ios::in | ios::out | ios::binary);
		RefreshFileSize(); // So the writter will set Data size to '0';
		WriteHeader();
		// NUMBER OF BYTES:
		RefreshFileSize(); // Re-writes FileSize
	}

	void ReWriteSizes()
	{
		wavFile.seekg(0, ios::end);
		int DataSize = wavFile.tellg(); DataSize -= 44;
		DATAChnk.Size = DataSize; RIFFChnk.ChunkSize = GetChunkSize();
		wavFile.seekp(4); wavFile.write((char*)&RIFFChnk.ChunkSize, sizeof(unsigned int));
		wavFile.seekp(40); wavFile.write((char*)&DATAChnk.Size, sizeof(unsigned int));
		wavFile.seekp(0, ios::beg); wavFile.seekg(0, ios::beg);
	}

	// #################################################

	void CoutHeaderInfo()
	{
		std::cout << "#####################\nPath: " << Path << "\n#####################\n\n";
		std::cout << "RIFF[4]: " << RIFFChnk.RIFF << endl;
		std::cout << "ChunkSize: " << RIFFChnk.ChunkSize << " = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size) =\n               | 4 + (8 + " << FMTChnk.Size << ") + (8 + " << DATAChnk.Size << ") =\n";
		std::cout << "               | 4 + (" << 8 + FMTChnk.Size << ") + (" << 8 + DATAChnk.Size << ") = 4 + (" << 8 + FMTChnk.Size + 8 + DATAChnk.Size << ")\n\n";
		std::cout << "Wave[4]: " << RIFFChnk.WAVE << "\n\n";

		std::cout << "fmt[4]: " << FMTChnk.fmt << endl;
		std::cout << "Subchunk1Size: " << FMTChnk.Size << endl;
		std::cout << "AudioFormat: " << FMTChnk.AudioFormat << endl;
		std::cout << "NumChannels: " << FMTChnk.NumChannels << endl;
		std::cout << "SampleRate: " << FMTChnk.SampleRate << endl;
		std::cout << "ByteRate: " << FMTChnk.ByteRate << " = SampleRate * BlockAlign = " << FMTChnk.SampleRate << " * " << FMTChnk.BlockAlign << endl;
		std::cout << "BlockAlign: " << FMTChnk.BlockAlign << " = NumChannels * BitsPerSample / 8 = " << FMTChnk.NumChannels << " * " << FMTChnk.BitsPerSample / 8 << endl;
		std::cout << "BitsPerSample: " << FMTChnk.BitsPerSample << "\n\n";

		std::cout << "Subchunk2ID: " << DATAChnk.ID << endl;
		std::cout << "Subchunk2Size: " << DATAChnk.Size << "\nNOTE: 'short int' size is '2 bytes', Fixed size to 'short int': " << DATAChnk.Size / 2 << "\n\n";
		std::cout << "#####################\n\n";

		std::cout << "CLASS INFO:\n";
		std::cout << "FileSize: " << FileSize << endl;
		std::cout << "sizeof(WAVEFile): " << sizeof(WAVEFile) << endl;

		std::cout << "#####################\n\n";
	}

	std::string StringHeaderInfo()
	{
		std::string s = "#####################\nPath: " + Path + "\n#####################\n\n";
		s += "ChunkSize: " + to_string(RIFFChnk.ChunkSize) + " = 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size) =\n               | 4 + (8 + " + to_string(FMTChnk.Size);
		s += ") + (8 + " + to_string(DATAChnk.Size) + ") =\n";
		s += "               | 4 + (" + to_string(8 + FMTChnk.Size) + ") + (" + to_string(8 + DATAChnk.Size) + ") = 4 + (" + to_string(8 + FMTChnk.Size + 8 + DATAChnk.Size) + ")\n\n";
		s += "Wave[4]: " + RIFFChnk.WAVE[0] + RIFFChnk.WAVE[1] + RIFFChnk.WAVE[2] + RIFFChnk.WAVE[3]; s += +"\n\n";

		s += "fmt[4]: " + FMTChnk.fmt[0] + FMTChnk.fmt[1] + FMTChnk.fmt[2] + FMTChnk.fmt[3]; s += "\n";
		s += "Subchunk1Size: " + to_string(FMTChnk.Size) + "\n";
		s += "AudioFormat: " + to_string(FMTChnk.AudioFormat) + "\n";
		s += "NumChannels: " + to_string(FMTChnk.NumChannels) + "\n";
		s += "SampleRate: " + to_string(FMTChnk.SampleRate) + "\n";
		s += "ByteRate: " + to_string(FMTChnk.ByteRate) + " = SampleRate * BlockAlign = " + to_string(FMTChnk.SampleRate) + " * " + to_string(FMTChnk.BlockAlign) + "\n";
		s += "BlockAlign: " + to_string(FMTChnk.BlockAlign) + " = NumChannels * BitsPerSample / 8 = " + to_string(FMTChnk.NumChannels) + " * " + to_string(FMTChnk.BitsPerSample / 8) + "\n";
		s += "BitsPerSample: " + to_string(FMTChnk.BitsPerSample) + "\n\n";

		s += "Subchunk2ID: " + DATAChnk.ID[0] + DATAChnk.ID[1] + DATAChnk.ID[2] + DATAChnk.ID[3]; s += "\n";
		s += "Subchunk2Size: " + to_string(DATAChnk.Size) + "\nNOTE: 'short int' size is '2 bytes', Fixed size to 'short int': " + to_string(DATAChnk.Size / 2) + "\n\n";
		s += "#####################\n\n";

		s += "CLASS INFO:\n";
		s += "FileSize: " + to_string(FileSize) + "\n";
		s += "sizeof(WAVEFile): " + to_string(sizeof(WAVEFile)) + "\n";

		s += "#####################\n\n";
		return(s);
	}

	// #################################################
	// #################################################
	// #################################################



	// #################################################

	DATASHINT GetAllDataSINT()
	{
		wavFile.seekg(0, ios::end);
		int End = wavFile.tellg();
		short int ReadSample;
		int pos = FileSize - DATAChnk.Size;
		wavFile.seekg(pos);

		DATASHINT GETDATA;
		for (int n = pos; n < End; )
		{
			wavFile.read((char*)&ReadSample, sizeof(ReadSample));
			GETDATA.push_back(ReadSample);
			n = wavFile.tellg();
		}
		wavFile.seekg(0, ios::beg);
		return(GETDATA);
	}

	// #################################################

	// GET INT DATA, THIS IS THE DOUBLE (4 BYTES) OF THE STANDARD SIZE OF DATA (2 BYTES, 16 BITSPERSAMPLE):
	DATAINT GetDataINT(int Index, int Size)
	{
		int Bytes = sizeof(int);
		Index *= Bytes; Size *= Bytes;
		wavFile.seekg(0, ios::end);
		int End = wavFile.tellg();
		int pos = End - DATAChnk.Size;
		int Begin = pos + Index;
		if (Index + Size > End) { Size -= Index + Size - End; End = Index + Size; }
		else { End = Index + Size + pos; }
		int ReadSample;

		wavFile.seekg(Begin);
		DATAINT GETDATA;
		for (int n = Begin; n < End; )
		{
			wavFile.read((char*)&ReadSample, Bytes);
			GETDATA.push_back(ReadSample);
			n = wavFile.tellg();
		}
		wavFile.seekg(0, ios::beg);
		return(GETDATA);
	}

	// GET FLOAT DATA, THIS IS THE DOUBLE (4 BYTES) OF THE STANDARD SIZE OF DATA (2 BYTES):
	DATAFLT GetDataFLT(int Index, int Size)
	{
		int Bytes = sizeof(float);
		Index *= Bytes; Size *= Bytes;
		wavFile.seekg(0, ios::end);
		int End = wavFile.tellg();
		int pos = End - DATAChnk.Size;
		int Begin = pos + Index;
		if (Index + Size > End) { Size -= Index + Size - End; End = Index + Size; }
		else { End = Index + Size + pos; }

		float ReadFloat;

		wavFile.seekg(Begin);
		DATAFLT GETDATA;
		for (int n = Begin; n < End; )
		{
			wavFile.read((char*)&ReadFloat, Bytes);
			GETDATA.push_back(ReadFloat);
			n = wavFile.tellg();
		}
		wavFile.seekg(0, ios::beg);
		return(GETDATA);
	}

	// GET SHORT INT DATA, THIS IS THE STANDARD SIZE OF DATA (2 BYTES):
	DATASHINT GetDataSHINT(int Index, int Size)
	{
		int Bytes = sizeof(short int);
		Index *= Bytes; Size *= Bytes;
		wavFile.seekg(0, ios::end);
		int End = wavFile.tellg();
		int pos = End - DATAChnk.Size;
		int Begin = pos + Index;
		if (Index + Size > End) { Size -= Index + Size - End; End = Index + Size; }
		else { End = Index + Size + pos; }

		short int ReadSample;

		wavFile.seekg(Begin);
		DATASHINT GETDATA;
		for (int n = Begin; n < End; )
		{
			wavFile.read((char*)&ReadSample, Bytes);
			GETDATA.push_back(ReadSample);
			n = wavFile.tellg();
		}
		wavFile.seekg(0, ios::beg);
		return(GETDATA);
	}

	// GET SHORT INT DATA FROM EITHER LEFT OR RIGHT CHANNEL:
	DATASHINT GetDataSHINTChannel(int Index, int Size, bool LeftRight)
	{
		int Bytes = sizeof(short int);
		Index *= Bytes; Size *= Bytes;
		wavFile.seekg(0, ios::end);
		int End = wavFile.tellg();
		int pos = End - DATAChnk.Size;
		int Begin = pos + Index;
		if (Index + Size > End) { Size -= Index + Size - End; End = Index + Size; }
		else { End = Index + Size + pos; }
		bool Switch = true;
		if (LeftRight) { Switch = false; }

		short int ReadSample;

		wavFile.seekg(Begin);
		DATASHINT GETDATA;
		for (int n = Begin; n < End; )
		{
			wavFile.read((char*)&ReadSample, Bytes);
			if (Switch) { GETDATA.push_back(ReadSample); Switch = false; }
			else { Switch = true; }
			n = wavFile.tellg();
		}
		wavFile.seekg(0, ios::beg);
		return(GETDATA);
	}

	// #################################################

	// GET DATA READY TO WORK AS A DOUBLE VECTOR (CONSIDERING THE SHORT INT MAX AT 32768), IGNORE LeftRight IF THERE IS ONLY ONE CHANNEL.
	// Use only multiples of '8' as 'FMTChnk.BitsPerSample', or else the vector returns with a single item of number '0':.
	// The function begins JUST AFTER the end of the '.wav' header, if you want 'Size' to reach the End of file, use the it equal as "DATAChnk.Size":
	vector<double> GetDataReadyToUse(int Index, int Size, bool LeftRight = false)
	{
		vector<double> GETDATA;
		int Bytes = FMTChnk.BitsPerSample / 8;
		if (FMTChnk.BitsPerSample % 8 == 0) // !!! PARA GARANTIR O NUMERO DE BYTES PARA OS COMPARADORES !!!
		{
			Index *= Bytes; Size *= Bytes;
			wavFile.seekg(0, ios::end);
			int End = wavFile.tellg();
			int pos = End - DATAChnk.Size;
			int Begin = pos + Index;
			if (Index + Size > End) { Size -= Index + Size - End; End = Index + Size; }
			else { End = Index + Size + pos; }

			bool Switch = true;
			if (LeftRight) { Switch = false; }

			wavFile.seekg(Begin);
			
			for (int n = Begin; n < End; )
			{
				double Push;
				short int Val; wavFile.read((char*)&Val, Bytes); Push = Val; // !!!!!!! POR ENQUANTO SÓ SHORT INT !!!!!!!
				//cout << "VAL: " << Push <<  " | ";
				if (Push > 0) { Push /= (pow(256, Bytes) / 2.0) - 1; } else { Push /= pow(256, Bytes) / 2.0; }
				if (FMTChnk.NumChannels == 1) { /*cout << "PUSH: " << Push << endl;*/ GETDATA.push_back(Push); }
				else { if (Switch) { /*cout << "PUSH: " << Push << endl;*/ GETDATA.push_back(Push); Switch = false; } else { Switch = true; } }

				n = wavFile.tellg();
			}
			wavFile.seekg(0, ios::beg);
		}
		else { GETDATA.push_back(0); }
		return(GETDATA);
	}

	// #################################################
	// #################################################
	// #################################################
		
	// PREPARE DATA TO OUTPUT: (!!! ATTENTION: This function Multiplies the data by 32767 !!!)
	DATASHINT PrepareData(vector<double> In)
	{ DATASHINT Buffer; for (int n = 0; n < In.size(); ++n) { if (In[n] > 0) { Buffer.push_back(round(In[n] * 32767)); } else { Buffer.push_back(round(In[n] * 32768)); } } return(Buffer);	}
	DATASHINT PrepareData(DATAFLT In)
	{ DATASHINT Buffer; for (int n = 0; n < In.size(); ++n) { if (In[n] > 0) { Buffer.push_back(round(In[n] * 32767)); } else { Buffer.push_back(round(In[n] * 32768)); } } return(Buffer);	}

	// #################################################

	// SAVE DATA FULL:
	void SaveDataSInt(vector<double> In)
	{
		DATASHINT Buffer = PrepareData(In); wavFile.seekp(44);
		for (int n = 0; n < Buffer.size(); ++n) { for (int Channel = 0; Channel < FMTChnk.NumChannels; ++Channel) { wavFile.write((char*)&Buffer[n], sizeof(short int)); } }
		ReWriteSizes();
		ReOpenFile();
	}
	void SaveDataSInt(vector<double> In, bool LeftRight)
	{
		DATASHINT Buffer = PrepareData(In); wavFile.seekp(44); short int Bytes = sizeof(short int);
		for (int n = 0; n < Buffer.size(); ++n)
		{
			//for (int Channel = 0; Channel < FMTChnk.NumChannels; ++Channel)
			//{
				if (LeftRight) { short int pos = wavFile.tellp(); pos += Bytes; wavFile.seekp(pos); }
				wavFile.write((char*)&Buffer[n], sizeof(short int));
				if (!LeftRight) { short int pos = wavFile.tellp(); pos += Bytes; wavFile.seekp(pos); }
			//}
		}
		ReWriteSizes();
		ReOpenFile();
	}
	void SaveDataSInt(DATAFLT In)
	{
		DATASHINT Buffer = PrepareData(In); wavFile.seekp(44);
		for (int n = 0; n < Buffer.size(); ++n) { wavFile.write((char*)&Buffer[n], sizeof(short int)); }
		ReWriteSizes();
		ReOpenFile();
	}
	void SaveDataSInt(DATASHINT In)
	{
		wavFile.seekp(44);
		for (int n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(short int)); }
		ReWriteSizes();
		ReOpenFile();
	}

	// #################################################
	
	// SAVE DATA INDEX:
	void SaveDataSInt(vector<double> In, int Index)
	{
		DATASHINT Buffer = PrepareData(In);
		int Begin = (Index * sizeof(short int)) + 44; wavFile.seekp(Begin); for (int n = 0; n < Buffer.size(); ++n) { wavFile.write((char*)&Buffer[n], sizeof(short int)); }
		ReWriteSizes();
		ReOpenFile();
	}
	void SaveDataSInt(DATAFLT In, int Index)
	{
		DATASHINT Buffer = PrepareData(In);
		int Begin = (Index * sizeof(short int)) + 44; wavFile.seekp(Begin); for (int n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(short int)); }
		ReWriteSizes();
		ReOpenFile();
	}
	void SaveDataSInt(DATASHINT In, int Index)
	{
		int Begin = (Index * sizeof(short int)) + 44; wavFile.seekp(Begin); for (int n = 0; n < In.size(); ++n) { wavFile.write((char*)&In[n], sizeof(short int)); }
		ReWriteSizes();
		ReOpenFile();
	}
};


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_