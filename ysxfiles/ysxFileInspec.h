#pragma once

#ifndef YSXFILEINSP_H
#define YSXFILEINSP_H

#include <vector>
#include <iostream>
//#include <fstream>
#include "ysxmath.h"

using namespace std;

// #####################################################################################################################################
// ####### STRUCTS #######

// #####################################################################################################################################
// #######  FUNCTIONS #######

// #####################################################################################################################################
// #####################
// #######  CLASSES #######
// #####################

class GetFileInfo
{	
public:
	ifstream FileIn;
	string Path;

	GetFileInfo(string InputPath)
	{
		FileIn.open(InputPath, ios::binary);
		Path = InputPath;
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
		else cout << "Unable to open file";
		
		return (Buffer);
	}
	vector<int> GetBufferInt(int Size, int Index, bool LittleBig) // I modified this and i have not tested
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
					FileIn.seekg(Begin + (n * IntSize)); FileIn.read(Byte, IntSize);
					int CompileInt = 0;
					if (LittleBig) { InvertArray(Bytes, Byte); }
					memcpy(&CompileInt, Bytes, IntSize);
					Buffer.push_back(CompileInt);
				}
			}
			else { cout << "Size is out of file bounds!\n\n"; }
			FileIn.seekg(0, ios::beg);
		}
		else cout << "Unable to open file";

    FileIn.seekg(0, ios::beg);
		return (Buffer);
	}
	// #################################################

	void CoutInfo() { cout << NumberOfBytes() / 1000.0 << "KB" << endl; }
};

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_
