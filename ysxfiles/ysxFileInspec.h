#pragma once

#ifndef YSXFILEINSP_H
#define YSXFILEINSP_H

#include <vector>
#include <iostream>
//#include <fstream>
#include "ysxmath.h"
#include "ysxBytes.h"

using namespace std;

// TAKE CARE WITH THIS FILE, IT IS SOMEWHAT NEW AND I'M NOT SURE IF EVERYTHING IS WORKING CORRECTLY

// #####################################################################################################################################
// ####### STRUCTS #######
// INDEX:


// #####################################################################################################################################
// #######  IN / OUT #######
// #######  VECTORS:
// SAVE IN A BINARY FILE OVERWRITTING IT:
void ofsVectorOut(vector<double> V, string Path) { ofstream F(Path, ios::binary); if (F.is_open()) { char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } } F.close(); }

// GET A VECTOR FROM OF A BINARY:
vector<double> ifsVectorIn(string Path)
{
	vector<double> Buffer; char Bytes = sizeof(double);
	ifstream F(Path, ios::binary);
	if (F.is_open())
	{
		while (!F.eof()) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); }
	}
	else { cout << "Something went wrong while loading file.\n"; }
	F.close();
	return(Buffer);
}

// APPEND TO THE END OF A BINARY FILE:
void fsVectorOutApp(vector<double> V, string Path)
{
	fstream F(Path, ios::binary);
	if (F.is_open()) { F.seekp(0, ios::end); char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close();
}

// !!!!!!! FAZER UMA FUNÇÃO AQUI QUE COPIA O FIM DE UM ARQUIVO DESFE UM INDEX E APPEND UM VECTOR ALI E COLA O INDEX NO FIM DO VECTOR = A, B, C | A, [D, E] | A, D, E, B, C !!!!!!!
// #######  REST:

// GET FROM OF A BINARY (you should know if index on input is possible):
double ifsInChar(string Path, int Index)
{
	ifstream F(Path, ios::binary); char c; if (F.is_open()) { F.seekg(Index); F.read(&c, sizeof(char)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(c);
}
double ifsInSInt(string Path, int Index)
{
	ifstream F(Path, ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(float)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
double ifsInInt(string Path, int Index)
{
	ifstream F(Path, ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(float)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
double ifsInFlt(string Path, int Index)
{
	ifstream F(Path, ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(float)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
double ifsInDbl(string Path, int Index)
{
	ifstream F(Path, ios::binary); double Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(double)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}

// APPEND TO THE END OF A BINARY FILE:
void fsOutApp(char C, string Path) { fstream F(Path, ios::binary); if (F.is_open()) { F.seekp(0, ios::end); F.write(&C, sizeof(char)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); }
void fsOutApp(short int si, string Path) { fstream F(Path, ios::binary); if (F.is_open()) { F.seekp(0, ios::end); F.write((char*)&si, sizeof(short int)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); }
void fsOutApp(int i, string Path) { fstream F(Path, ios::binary); if (F.is_open()) { F.seekp(0, ios::end); F.write((char*)i, sizeof(int)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); }
void fsOutApp(float f, string Path) { fstream F(Path, ios::binary); if (F.is_open()) { F.seekp(0, ios::end); F.write((char*)&f, sizeof(float)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); }
void fsOutApp(double d, string Path) { fstream F(Path, ios::binary); if (F.is_open()) { F.seekp(0, ios::end); F.write((char*)&d, sizeof(double)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); }

// #####################################################################################################################################
// #####################
// #######  CLASSES #######
// #####################

class GetFileInfo
{	
public:
	ifstream FileIn;
	string Path;
	unsigned int Bytes;

	GetFileInfo(string InputPath)
	{
		FileIn.open(InputPath, ios::binary);
		Path = InputPath;
		Bytes = NumberOfBytes();
	}

	~GetFileInfo() { FileIn.close(); }

	// #####################
	// NUMBERS:

	int NumberOfBytes()
	{
		FileIn.seekg(0, ios::end);
		int Return = FileIn.tellg();
		FileIn.seekg(0, ios::beg);
		return (Return);
	}

	// #####################
	// BUFFERS:

	// CHAR CHUNK:
	vector<char> GetBufferChar(int Size, int Index)
	{
		int SizeTotal; int Begin = Index; int End = Begin + Size;
		vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, ios::end);
			SizeTotal = FileIn.tellg(); if (End > SizeTotal) { Size -= End - SizeTotal; }
			Buffer = vector<char>::vector(Size); char* BufferPointer = &Buffer.at(0);
			FileIn.seekg(Begin); FileIn.read(BufferPointer, Size); FileIn.seekg(0, ios::beg);
		}
		else { cout << "Unable to open file"; }
		
		return (Buffer);
	}

	// INT CHUNK:
	vector<int> GetBufferInt(int Size, int Index, bool LittleBig)
	{
		int SizeTotal;
		const int IntSize = sizeof (int);
		int SizeinBytes = Size * IntSize;
		int Begin = Index * SizeinBytes; int End = Begin + SizeinBytes;
		vector<int> Buffer;
		char Bytes[IntSize];

		if (FileIn.is_open())
		{
			FileIn.seekg(0, ios::end);
			SizeTotal = FileIn.tellg();
			if (End <= SizeTotal)
			{
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
			else { cout << "Size is out of file bounds!\n\n"; }
			FileIn.seekg(0, ios::beg);
		}
		else { cout << "Unable to open file"; }

		return (Buffer);
	}

	// #################################################

	// ENTIRE FILE IN CHAR:
	vector<char> GetFileChar()
	{
		int Size;
		vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, ios::end);
			Size = FileIn.tellg(); 
			Buffer = vector<char>::vector(Size); char* bp = &Buffer.at(0);
			FileIn.seekg(0, ios::beg); FileIn.read(bp, Size); FileIn.seekg(0, ios::beg);
		}
		else { cout << "Unable to open file"; }

		return (Buffer);
	}

	// #################################################
	
	void PrintBufferChar(int Size, int Index)
	{
		FileIn.seekg(0, ios::end);
		int SizeTotal; int Begin = Index * Size; int End = Begin + Size;
		vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, ios::end);
			SizeTotal = FileIn.tellg(); if (End > SizeTotal) { Size -= End - SizeTotal; } FileIn.seekg(Begin);
			Buffer = vector<char>::vector(Size); char* BufferPointer = &Buffer.at(0);
			FileIn.read(BufferPointer, Size); FileIn.seekg(0, ios::beg);
		}
		else { cout << "Unable to open file"; }
		ofstream Out ("PrintBufferChar.txt");
		Out << Buffer.data() << endl;
		Out.close();
	}

	void PrintFileChar()
	{
		int Size;
		vector<char> Buffer;

		if (FileIn.is_open())
		{
			FileIn.seekg(0, ios::end);
			Size = FileIn.tellg();
			Buffer = vector<char>::vector(Size); char* bp = &Buffer.at(0);
			FileIn.seekg(0, ios::beg); FileIn.read(bp, Size); FileIn.seekg(0, ios::beg);
		}
		else { cout << "Unable to open file"; }

		ofstream Out("PrintFileChar.txt");
		Out.write(Buffer.data(), Size);
		Out.close();
	}

	// #################################################
	
	// #################################################
	// #################################################
	// #################################################

	void CoutInfo() { cout << NumberOfBytes() / 1000.0 << "KB" << endl; }
};

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_
