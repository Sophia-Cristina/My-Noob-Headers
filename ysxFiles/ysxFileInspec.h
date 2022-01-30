#pragma once

#ifndef YSXFILEINSP_H
#define YSXFILEINSP_H

#include <vector>
#include <iostream>
//#include <fstream>
#include "ysxmath.h"
#include "ysxBytes.h"

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
//
// CHANGES (KEEP ORDER):
// * Now using templates;
//
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// #######  IN / OUT #######
// #######  VECTORS:
// SAVE IN A BINARY FILE OVERWRITTING IT:
void ofsVectorOut(std::vector<double> V, std::string Path)
{ std::ofstream F(Path, std::ios::binary); if (F.is_open()) { char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } } F.close(); }

// GET ROM:
std::vector<unsigned char> GetROM(std::string Path)
{
	std::vector<unsigned char> B;
	std::ifstream F(Path, std::ios::binary);
	if (F.is_open())
	{
		F.seekg(0, std::ios::end); unsigned int Size = F.tellg(); F.seekg(0, std::ios::beg);
		B = std::vector<unsigned char>::vector(Size); F.read((char*)&B[0], Size);
	}
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(B);
}

// GET ROM:
std::vector<unsigned char> GetROMendian(std::string Path)
{
	std::vector<unsigned char> B;
	std::ifstream F(Path, std::ios::binary);
	if (F.is_open())
	{
		F.seekg(0, std::ios::end); unsigned int Size = F.tellg(), n = 0; F.seekg(0, std::ios::beg);
		B = std::vector<unsigned char>::vector(Size); while (F.tellg() < Size) { F.read((char*)&B[n], 1); ++n; }
	}
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(B);
}

// GET A VECTOR FROM OF A BINARY (WHICH CONSIST ENTIRELY OF THE SAME TYPE OBJECT):
// * Remover 
template <class T_> std::vector<T_> ifsVectorIn(std::string Path)
{
	std::vector<T_> Buffer; char Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < Size) { T_ Compile; F.read((char*)&Compile, Bytes); Buffer.push_back(Compile); }}
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
template <class T_> std::vector<T_> ifsVectorIn(std::string Path, int Index)
{
	std::vector<T_> Buffer; char Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); int Size = F.tellg(); F.seekg(Index);
	while (F.tellg() < Size) { T_ Compile; F.read((char*)&Compile, Bytes); Buffer.push_back(Compile); }}
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
template <class T_> std::vector<double> ifsVectorIn(std::string Path, int Index, int End)
{
	std::vector<T_> Buffer; char Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(End); int Size = F.tellg(); F.seekg(Index);
	while (F.tellg() < Size) { T_ Compile; F.read((char*)&Compile, Bytes); Buffer.push_back(Compile); }}
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}

// APPEND TO THE END OF A BINARY FILE:
template <class T_> void fsVectorOutApp(std::vector<T_> V, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); char Bytes = sizeof(T_); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } }
	else { std::cout << "Something went wrong while loading file.\n"; }
	F.close();
}

// !!!!!!! FAZER UMA FUNÇÃO AQUI QUE COPIA O FIM DE UM ARQUIVO DESDE UM INDEX E APPEND UM VECTOR ALI E COLA O INDEX NO FIM DO VECTOR = A, B, C | A, [D, E] | A, D, E, B, C !!!!!!!

// #######  REST:

// GET FROM OF A BINARY (you should know if index in input is possible):
template <class T_> T_ ifsIn(std::string Path, int Index)
{
	std::ifstream F(Path, std::ios::binary); T_ B;
	if (F.is_open()) { F.seekg(Index); F.read(&B, sizeof(T_)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close(); return(B);
}

// APPEND TO THE END OF A BINARY FILE:
template <class T_> void fsOutApp(T_ B, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write(&B, sizeof(T_)); } else { std::cout << "Something went wrong while loading file.\n"; } F.close();
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
		FileSize = GetSize();
	}

	~GetFileInfo() { FileIn.close(); }

	// #####################
	// NUMBERS:

	int GetSize()
	{
		FileIn.seekg(0, std::ios::end);
		int Return = FileIn.tellg();
		FileIn.seekg(0, std::ios::beg);
		return (Return);
	}

	// #####################
	// BUFFERS:
	// !!! Going to fix this entire section, probably everything is going to be remade !!!

	// CHAR CHUNK:
	std::vector<char> GetBufferChar(int Size, int Index)
	{
		int SizeTotal; int Begin = Index * Size; int End = Begin + Size;
		std::vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, std::ios::end);
			SizeTotal = FileIn.tellg(); if (End > SizeTotal) { Size -= End - SizeTotal; }
			Buffer = std::vector<char>::vector(Size); char* p = &Buffer[0];
			FileIn.seekg(Begin); FileIn.read(p, Size); FileIn.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }
		
		return (Buffer);
	}

	// INT CHUNK (do template out of it, later):
	std::vector<int> GetBufferInt(int Size, int Index, bool LittleBig)
	{
		int SizeTotal;
		const int IntSize = sizeof(int);
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
					if (LittleBig) { InvertArray((unsigned char*)Bytes, IntSize); }
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

	void CoutInfo() { std::cout << GetSize() / 1000.0 << "KB" << std::endl; }
};

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_