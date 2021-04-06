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
void ofsVectorOut(vector<double> V, string Path) { ofstream F(Path, ios::binary); if (F.is_open()) { char Bytes = sizeof(double); for (int n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } } F.close(); }

// GET A VECTOR FROM OF A BINARY (WHICH CONSIST ENTIRELY OF THE SAME TYPE OBJECT):
vector<double> ifsVectorDblIn(string Path)
{
	vector<double> Buffer; char Bytes = sizeof(double); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
vector<double> ifsVectorDblIn(string Path, int Index)
{
	vector<double> Buffer; char Bytes = sizeof(double); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
vector<double> ifsVectorDblIn(string Path, int Index, int End)
{
	vector<double> Buffer; char Bytes = sizeof(double); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { double Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
vector<int> ifsVectorIntIn(string Path)
{
	vector<int> Buffer; char Bytes = sizeof(int); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
vector<int> ifsVectorIntIn(string Path, int Index)
{
	vector<int> Buffer; char Bytes = sizeof(int); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
}
vector<int> ifsVectorIntIn(string Path, int Index, int End)
{
	vector<int> Buffer; char Bytes = sizeof(int); ifstream F(Path, ios::binary);
	if (F.is_open()) { F.seekg(0, ios::end); int Size = F.tellg(); F.seekg(0, ios::beg); while (F.tellg() < Size) { int Compile; char* p = (char*)&Compile; F.read(p, Bytes); Buffer.push_back(Compile); } }
	else { cout << "Something went wrong while loading file.\n"; }
	F.close(); return(Buffer);
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
char ifsInChar(string Path, int Index)
{
	ifstream F(Path, ios::binary); char c; if (F.is_open()) { F.seekg(Index); F.read(&c, sizeof(char)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(c);
}
short int ifsInSInt(string Path, int Index)
{
	ifstream F(Path, ios::binary); short int Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(short int)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
int ifsInInt(string Path, int Index)
{
	ifstream F(Path, ios::binary); int Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(int)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
float ifsInFlt(string Path, int Index)
{
	ifstream F(Path, ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(float)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}
double ifsInDbl(string Path, int Index)
{
	ifstream F(Path, ios::binary); double Compile; if (F.is_open()) { F.seekg(Index); F.read((char*)&Compile, sizeof(double)); } else { cout << "Something went wrong while loading file.\n"; } F.close(); return(Compile);
}

/*// GET FROM OF A BINARY (you should know if index on input is possible), FROM ONE INDEX TO ANOTHER:
string ifsInChar(string Path, int Index, int LastIndex)
{
	string Buffer;
	ifstream F(Path, ios::binary); char c; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read(&c, sizeof(char)); Buffer.push_back(c); } }
	else { cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
vector<short int> ifsInSInt(string Path, int Index, int LastIndex)
{
	vector<short int> Buffer;
	ifstream F(Path, ios::binary); short int Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(short int)); Buffer.push_back(Compile); } }
	else { cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
vector<int> ifsInInt(string Path, int Index, int LastIndex)
{
	vector<int> Buffer;
	ifstream F(Path, ios::binary); int Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(int)); Buffer.push_back(Compile); } }
	else { cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
vector<float> ifsInFlt(string Path, int Index, int LastIndex)
{
	vector<float> Buffer;
	ifstream F(Path, ios::binary); float Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(float)); Buffer.push_back(Compile); } }
	else { cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}
vector<double> ifsInDbl(string Path, int Index, int LastIndex)
{
	vector<double> Buffer;
	ifstream F(Path, ios::binary); double Compile; if (F.is_open()) { F.seekg(Index); while (F.tellg() < LastIndex) { F.read((char*)&Compile, sizeof(double)); Buffer.push_back(Compile); } }
	else { cout << "Couldn't open file.\n"; } F.close(); return(Buffer);
}*/

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
	unsigned int FileSize;

	GetFileInfo(string InputPath)
	{
		FileIn.open(InputPath, ios::binary);
		Path = InputPath;
		FileSize = NumberOfBytes();
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
		int SizeTotal; int Begin = Index * Size; int End = Begin + Size;
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
		//Size *= IntSize;
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
				//Buffer = vector<int>::vector(Size); int* BufferPointer = &Buffer.at(0);
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
	
	// PRINT CHAR BUFFER IN A ".txt" FILE:
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

	// PRINT ENTIRE FILE AS CHAR IN A ".txt" FILE:
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

	// COUT INFORMATION:
	void CoutFileInfo(int BufferSize)
	{
		cout << "#####################\n\n";
		string EntireFile = GetFileChar().data();
		string Buffer = GetBufferChar(BufferSize, 0).data();
		vector<int> BufferInt = GetBufferInt(BufferSize / 4, 0, 0);
		cout << "####### FILE:\n(string size: " << EntireFile.size() << ")\n";
		cout << EntireFile << "\n\n";
		cout << "\n#####################\n\n";
		cout << "####### BUFFER:\n(string size: " << Buffer.size() << ", int size: " << BufferInt.size() << ")\n";
		cout << Buffer << "\n\n";
		CoutVector(BufferInt);
		cout << "\n#####################\n\n";
	}

	// PRINT INFORMATION:
	void PrintFileInfo(int BufferSize)
	{
		ofstream PrintOut("PrintFileInfo.txt");
		PrintOut << "#####################\n\n";
		string EntireFile = GetFileChar().data();
		string Buffer = GetBufferChar(BufferSize, 0).data();
		vector<int> BufferInt = GetBufferInt(BufferSize / 4, 0, 0);
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

	void CoutInfo() { cout << NumberOfBytes() / 1000.0 << "KB" << endl; }
};

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_