// https://www.onlinegdb.com/HyavW4JBD
#include <iostream>
using namespace std; 

struct RIFFChunk
	{
		char RIFF[4]; // 4 - 'RIFF' | Resource Interchange File Format
		unsigned int ChunkSize; // 4 - make sure to read only 4 bits | (4 + (8 + Subchunk1Size) + (8 + Subchunk2Size))
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
		short int BlockAlingn; // 2 - == NumChannels * BitsPerSample / 8 | The number of bytes for one sample including all channels. I wonder what happens when this number isn't an integer?
		short int BitsPerSample; // 2 - 8 bits = 8, 16 bits = 16, etc.
		// TOTAL: 24 + 12 = 36
	};

struct DataChunk
	{
		char ID[4]; // 4 - Subchunk2ID
		unsigned int Size; // 4 - Subchunk2Size
		// TOTAL: 8 + 24 + 12 = 44
	};

// #################################################

string WAVEHeader()
{
    // A WAVE FILE HEADER IN HEXADECIMAL:
    return("52494646ce00000057415645666d7420100000000100020044ac000010b10200040010006461746104000000");
}
  
string Hex2ASCII(string hex) // Geeksforgeeks functions to convert Hex to ASCII
{ 
    string ascii = ""; 
    for (size_t i = 0; i < hex.length(); i += 2) 
    { 
        string part = hex.substr(i, 2); 
        char ch = stoul(part, nullptr, 16); 
        ascii += ch; 
    } 
    return ascii; 
} 
  
int main() 
{ 
    RIFFChunk RIFF; FMTChunk FMT; DataChunk DATAC;
    string Header = Hex2ASCII(WAVEHeader());
    char * p = &Header.at(0);
    
    // WRITE RIFF CHUNK:
    char * q = (char *)&RIFF; // Points to RIFF's first byte
    for (int n = 0; n < 12; ++n)
    {
        *q = *p; // Copy byte from string
        ++p; ++q; // Advance pointer position
    }
    // WRITE FMT CHUNK:
    q = (char *)&FMT; // Points to FMT's first byte
    for (int n = 0; n < 24; ++n)
    {
        *q = *p;
        ++p; ++q; // q is in a new position, however p is still advancing
    }
    // WRITE DATA CHUNK:
    q = (char *)&DATAC; // Points to DATAC's first byte
    for (int n = 0; n < 8; ++n)
    {
        *q = *p;
        ++p; ++q;
    }
    
    // COUT EVERYTHING:
    
    std::cout << "#####################\nPath: " << "c:/Somewhere.wav" << "\n#####################\n\n";
	std::cout << "RIFF[4]: " << RIFF.RIFF << endl;
	std::cout << "ChunkSize: " << RIFF.ChunkSize << endl;
	std::cout << "Wave[4]: " << RIFF.WAVE << "\n\n";

	std::cout << "fmt[4]: " << FMT.fmt << endl;
	std::cout << "Subchunk1Size: " << FMT.Size << endl;
	std::cout << "AudioFormat: " << FMT.AudioFormat << endl;
	std::cout << "NumChannels: " << FMT.NumChannels << endl;
	std::cout << "SampleRate: " << FMT.SampleRate << endl;
	std::cout << "ByteRate: " << FMT.ByteRate << endl;
	std::cout << "BlockAlingn: " << FMT.BlockAlingn << "\n\n";

	std::cout << "Subchunk2ID: " << DATAC.ID << endl;
	std::cout << "Subchunk2Size: " << DATAC.Size << "\nNOTE: 'short int' size is '2 bytes', Fixed size to 'short int': " << DATAC.Size / 2 << "\n\n";
	std::cout << "#####################\n\n";
    
  
    return 0; 
}




