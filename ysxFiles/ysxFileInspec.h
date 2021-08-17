#pragma once

#ifndef YSXFILEINSP_H
#define YSXFILEINSP_H

#include <vector>
#include <iostream>
//#include <fstream>
#include "ysxmath.h"
#include "ysxBytes.h"

// #####################################################################################################################################
// ####### STRUCTS #######
// INDEX:


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// #######  IN / OUT #######
// #######  VECTORS:
// SAVE IN A BINARY FILE OVERWRITTING IT:
void ofsVectorOut(std::vector<double> V, std::string Path)
{ std::ofstream F(Path, std::ios::binary); if (F.is_open()) { char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } } F.close(); }

// GET A VECTOR FROM OF A BINARY (WHICH CONSIST ENTIRELY OF THE SAME TYPE OBJECT):
std::vector<double> ifsVectorDblIn(std::string Path)
{
	std::vector<double> Buffer; char Bytes = sizeof(double); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
std::vector<double> ifsVectorDblIn(std::string Path, int Index)
{
	std::vector<double> Buffer; char Bytes = sizeof(double); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
std::vector<double> ifsVectorDblIn(std::string Path, int Index, int End)
{
	std::vector<double> Buffer; char Bytes = sizeof(double); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
std::vector<int> ifsVectorIntIn(std::string Path)
{
	std::vector<int> Buffer; char Bytes = sizeof(int); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
std::vector<int> ifsVectorIntIn(std::string Path, int Index)
{
	std::vector<int> Buffer; char Bytes = sizeof(int); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
std::vector<int> ifsVectorIntIn(std::string Path, int Index, int End)
{
	std::vector<int> Buffer; char Bytes = sizeof(int); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}

// APPEND TO THE END OF A BINARY FILE:
void fsVectorOutApp(std::vector<double> V, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close();
}

// !!!!!!! FAZER UMA FUNÇÃO AQUI QUE COPIA O FIM DE UM ARQUIVO DESFE UM INDEX E APPEND UM VECTOR ALI E COLA O INDEX NO FIM DO VECTOR = A, B, C | A, [D, E] | A, D, E, B, C !!!!!!!
// #######  REST:

// GET FROM OF A BINARY (you should know if index on input is possible):
char ifsInChar(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); char c;
	if (F.is_open()) { F.seekg(Index); F.read(&c, sizeof(char)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(c);
}
short int ifsInSInt(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); short int Compile;
	if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(short int)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
int ifsInInt(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); int Compile;
	if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(int)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
float ifsInFlt(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); float Compile;
	if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(float)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
double ifsInDbl(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); double Compile;
	if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(double)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}

/*// GET FROM OF A BINARY (you should know if index on input is possible), FROM ONE INDEX TO ANOTHER:
std::string ifsInChar(std::string Path, int Index, int LastIndex)
{
	std::string Buffer;
	std::ifstream F(Path, std::ios::binary); char c; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read(&c, sizeof(char)); Buffer.push_back(c); } }
	else { std::cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
std::vector<short int> ifsInSInt(std::string Path, int Index, int LastIndex)
{
	std::vector<short int> Buffer;
	std::ifstream F(Path, std::ios::binary); short int Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(short int)); Buffer.push_back(Compile); } }
	else { std::cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
std::vector<int> ifsInInt(std::string Path, int Index, int LastIndex)
{
	std::vector<int> Buffer;
	std::ifstream F(Path, std::ios::binary); int Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(int)); Buffer.push_back(Compile); } }
	else { std::cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
std::vector<float> ifsInFlt(std::string Path, int Index, int LastIndex)
{
	std::vector<float> Buffer;
	std::ifstream F(Path, std::ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(float)); Buffer.push_back(Compile); } }
	else { std::cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
std::vector<double> ifsInDbl(std::string Path, int Index, int LastIndex)
{
	std::vector<double> Buffer;
	std::ifstream F(Path, std::ios::binary); double Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(double)); Buffer.push_back(Compile); } }
	else { std::cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}*/

// APPEND TO THE END OF A BINARY FILE:
void fsOutApp(char C, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write(&C, sizeof(char)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
}
void fsOutApp(short int si, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write((char*)&si, sizeof(short int)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
}
void fsOutApp(int i, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write((char*)i, sizeof(int)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
}
void fsOutApp(float f, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write((char*)&f, sizeof(float)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
}
void fsOutApp(double d, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write((char*)&d, sizeof(double)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
}

// #####################################################################################################################################
// #####################
// #######  CLASSES #######
// #####################

class GetFileInfo
{	
public:
	std::ifstream FileIn;
	std::string Path;
	unsigned int FileSize;

	GetFileInfo(std::string InputPath)
	{
		FileIn.open(InputPath, std::ios::binary);
		Path = InputPath;
		FileSize = NumberOfBytes();
	}

	~GetFileInfo() { FileIn.close(); }

	// #####################
	// NUMBERS:

	int NumberOfBytes()
	{
		FileIn.seekg(0, std::ios::end);
		int Return = FileIn.tellg();
		FileIn.seekg(0, std::ios::beg);
		return (Return);
	}

	// #####################
	// BUFFERS:

	// CHAR CHUNK:
	std::vector<char> GetBufferChar(int Size, int Index)
	{
		int SizeTotal; int Begin = Index * Size; int End = Begin + Size;
		std::vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			SizeTotal = FileIn.tellg(); if (End > SizeTotal) { Size -= End - SizeTotal; }
			Buffer = std::vector<char>::vector(Size); char* BufferPointer = &Buffer.at(0);
			FileIn.seekg(Begin); FileIn.read(BufferPointer, Size); FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }
		
		return (Buffer);
	}

	// INT CHUNK:
	std::vector<int> GetBufferInt(int Size, int Index, bool LittleBig)
	{
		int SizeTotal;
		const int IntSize = sizeof (int);
		//Size *= IntSize;
		int SizeinBytes = Size * IntSize;
		int Begin = Index * SizeinBytes; int End = Begin + SizeinBytes;
		std::vector<int> Buffer;
		char Bytes[IntSize];

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			SizeTotal = FileIn.tellg();
			if (End <= SizeTotal)
			{
				//Buffer = std::vector<int>::vector(Size); int* BufferPointer = &Buffer.at(0);
				char* Byte = Bytes;
				for (int n = 0; n < Size; ++n)
				{
					FileIn.seekg(Begin + (n * SizeinBytes)); FileIn.read(Byte, IntSize);
					int CompileInt = 0;
					if (LittleBig) { InvertArray(Bytes, Byte); }
					memcpy(&CompileInt, Bytes, IntSize);
					Buffer.push_back(CompileInt);
				}
			}
			else { std::cout << "Size is out of file bounds!\n\n"; }
			FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }

		return (Buffer);
	}

	// #################################################

	// ENTIRE FILE IN CHAR:
	std::vector<char> GetFileChar()
	{
		int Size;
		std::vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			Size = FileIn.tellg(); 
			Buffer = std::vector<char>::vector(Size); char* bp = &Buffer.at(0);
			FileIn.seekg(0, std::ios::beg); FileIn.read(bp, Size); FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }

		return (Buffer);
	}

	// #################################################
	
	// PRINT CHAR BUFFER IN A ".txt" FILE:
	void PrintBufferChar(int Size, int Index)
	{
		FileIn.seekg(0, std::ios::end);
		int SizeTotal; int Begin = Index * Size; int End = Begin + Size;
		std::vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			SizeTotal = FileIn.tellg(); if (End > SizeTotal) { Size -= End - SizeTotal; } FileIn.seekg(Begin);
			Buffer = std::vector<char>::vector(Size); char* BufferPointer = &Buffer.at(0);
			FileIn.read(BufferPointer, Size); FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }
		std::ofstream Out ("PrintBufferChar.txt");
		Out << Buffer.data() << std::endl;
		Out.close();
	}

	// PRINT ENTIRE FILE AS CHAR IN A ".txt" FILE:
	void PrintFileChar()
	{
		int Size;
		std::vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			Size = FileIn.tellg();
			Buffer = std::vector<char>::vector(Size); char* bp = &Buffer.at(0);
			FileIn.seekg(0, std::ios::beg); FileIn.read(bp, Size); FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }

		std::ofstream Out("PrintFileChar.txt");
		Out.write(Buffer.data(), Size);
		Out.close();
	}

	// #################################################

	// COUT INFORMATION:
	void CoutFileInfo(int BufferSize)
	{
		std::cout << "#####################\n\n";
		std::string EntireFile = GetFileChar().data();
		std::string Buffer = GetBufferChar(BufferSize, 0).data();
		std::vector<int> BufferInt = GetBufferInt(BufferSize / 4, 0, 0);
		std::cout << "####### FILE:\n(string size: " << EntireFile.size() << ")\n";
		std::cout << EntireFile << "\n\n";
		std::cout << "\n#####################\n\n";
		std::cout << "####### BUFFER:\n(string size: " << Buffer.size() << ", int size: " << BufferInt.size() << ")\n";
		std::cout << Buffer << "\n\n";
		CoutVector(BufferInt);
		std::cout << "\n#####################\n\n";
	}

	// PRINT INFORMATION:
	void PrintFileInfo(int BufferSize)
	{
		std::ofstream PrintOut("PrintFileInfo.txt");
		PrintOut << "#####################\n\n";
		std::string EntireFile = GetFileChar().data();
		std::string Buffer = GetBufferChar(BufferSize, 0).data();
		std::vector<int> BufferInt = GetBufferInt(BufferSize / 4, 0, 0);
		PrintOut << "####### FILE:\n(File size: " << FileSize << "string size: " << EntireFile.size() << ")\n";
		PrintOut << EntireFile << "\n\n";
		PrintOut << "\n#####################\n\n";
		PrintOut << "####### BUFFER:\n(string size: " << Buffer.size() << ", int size: " << BufferInt.size() << ")\n";
		PrintOut << Buffer << "\n\n";
		CoutVector(BufferInt);
		PrintOut << "\n#####################\n\n";
	}

	// #################################################
	
	// #################################################
	// #################################################
	// #################################################

	void CoutInfo() { std::cout << NumberOfBytes() / 1000.0 << "KB" << std::endl; }
};

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_