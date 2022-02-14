#pragma once

#ifndef YSXFILEINSP_H
#define YSXFILEINSP_H

#include <vector>
#include <iostream>
//#include <fstream>
#include "ysxMath.h"
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
// #######  IN / OUT #######
// #######  VECTORS:
// SAVE IN A BINARY FILE OVERWRITTING IT:
void ofsVectorOut(std::vector<double>& V, std::string Path)
{ std::ofstream F(Path, std::ios::binary); if (F.is_open()) { uint8_t Bytes = sizeof(double); for (size_t n = 0; n < V.size(); ++n) { F.write((char*)&V[n], Bytes); } } F.close(); }

// GET ROM:
std::vector<uint8_t> GetROM(std::string Path)
{
	std::vector<uint8_t> B;
	std::ifstream F(Path, std::ios::binary);
	if (F.is_open())
	{
		F.seekg(0, std::ios::end); uint32_t s = F.tellg(); F.seekg(0, std::ios::beg);
		B = std::vector<uint8_t>::vector(s); F.read((char*)&B[0], s);
	}
	else { std::cout << "File error\n"; }
	F.close(); return(B);
}

// GET ROM:
std::vector<uint8_t> GetROMendian(std::string Path)
{
	std::vector<uint8_t> B;
	std::ifstream F(Path, std::ios::binary);
	if (F.is_open())
	{
		F.seekg(0, std::ios::end); uint32_t s = F.tellg(), n = 0; F.seekg(0, std::ios::beg);
		B = std::vector<uint8_t>::vector(s); while (F.tellg() < s) { F.read((char*)&B[n], 1); ++n; }
	}
	else { std::cout << "File error\n"; }
	F.close(); return(B);
}

// GET A VECTOR FROM OF A BINARY (WHICH CONSIST ENTIRELY OF THE SAME TYPE OBJECT):
// * Remover 
template <class T_> std::vector<T_> ifsVectorIn(std::string Path)
{
	std::vector<T_> Buf; uint8_t Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); size_t s = F.tellg(); F.seekg(0, std::ios::beg);
	while (F.tellg() < s) { T_ Compile; F.read((char*)&Compile, Bytes); Buf.push_back(Compile); }}
	else { std::cout << "File error\n"; }
	F.close(); return(Buf);
}
template <class T_> std::vector<T_> ifsVectorIn(std::string Path, size_t Index)
{
	std::vector<T_> Buf; uint8_t Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(0, std::ios::end); size_t s = F.tellg(); F.seekg(Index);
	while (F.tellg() < s) { T_ Compile; F.read((char*)&Compile, Bytes); Buf.push_back(Compile); }}
	else { std::cout << "File error\n"; }
	F.close(); return(Buf);
}
template <class T_> std::vector<double> ifsVectorIn(std::string Path, size_t Index, size_t End)
{
	std::vector<T_> Buf; uint8_t Bytes = sizeof(T_); std::ifstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekg(End); size_t s = F.tellg(); F.seekg(Index);
	while (F.tellg() < s) { T_ Compile; F.read((char*)&Compile, Bytes); Buf.push_back(Compile); }}
	else { std::cout << "File error\n"; }
	F.close(); return(Buf);
}

// APPEND TO THE END OF A BINARY FILE:
template <class T_> void fsVectorOutApp(std::vector<T_> V, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); uint8_t Bytes = sizeof(T_); for (size_t n = 0; n < V.size(); ++n) { F.write((uint8_t*)&V[n], Bytes); } }
	else { std::cout << "File error\n"; }
	F.close();
}

// !!!!!!! FAZER UMA FUNÇÃO AQUI QUE COPIA O FIM DE UM ARQUIVO DESDE UM INDEX E APPEND UM VECTOR ALI E COLA O INDEX NO FIM DO VECTOR = A, B, C | A, [D, E] | A, D, E, B, C !!!!!!!

// #######  REST:

// GET FROM OF A BINARY (you should know if index in input is possible):
template <class T_> T_ ifsIn(std::string Path, size_t Index)
{
	std::ifstream F(Path, std::ios::binary); T_ B;
	if (F.is_open()) { F.seekg(Index); F.read(&B, sizeof(T_)); } else { std::cout << "File error\n"; } F.close(); return(B);
}

// APPEND TO THE END OF A BINARY FILE:
template <class T_> void fsOutApp(T_ B, std::string Path)
{
	std::fstream F(Path, std::ios::binary);
	if (F.is_open()) { F.seekp(0, std::ios::end); F.write(&B, sizeof(T_)); } else { std::cout << "File error\n"; } F.close();
}

// #####################################################################################################################################
// #####################
// #######  CLASSES #######
// #####################

class GetFileInfo
{	
public:
	std::ifstream File;
	std::string Path;
	size_t FileSize;

	GetFileInfo(std::string InputPath)
	{
		File.open(InputPath, std::ios::binary);
		Path = InputPath;
		FileSize = GetSize();
	}

	~GetFileInfo() { File.close(); }

	// #####################
	// NUMBERS:

	size_t GetSize()
	{
		File.seekg(0, std::ios::end);
		size_t Return = File.tellg();
		File.seekg(0, std::ios::beg);
		return (Return);
	}

	// #################################################
	
	// PRINT CHAR BUFFER IN A ".txt" FILE:
	void PrintBufferChar(size_t Size, size_t Index)
	{
		File.seekg(0, std::ios::end);
		size_t Total, End = Index + Size;
		std::vector<uint8_t> Buf;

		if (File.is_open())
		{
			File.seekg(0, std::ios::end); Total = File.tellg();
			if (End > Total) { Size -= End - Total; } File.seekg(Index);
			Buf = std::vector<uint8_t>::vector(Size); uint8_t* bp = &Buf[0];
			File.read((char*)bp, Size); File.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }
		std::ofstream O ("PrintBufferChar.txt");
		O << Buf.data() << std::endl;
		O.close();
	}

	// PRINT ENTIRE FILE AS CHAR IN A ".txt" FILE:
	void PrintFileChar()
	{
		size_t s;
		std::vector<uint8_t> Buf;

		if (File.is_open())
		{
			File.seekg(0, std::ios::end);
			s = File.tellg();
			Buf = std::vector<uint8_t>::vector(s); uint8_t* bp = &Buf[0];
			File.seekg(0, std::ios::beg); File.read((char*)bp, s); File.seekg(0, std::ios::beg);
		}
		else { std::cout << "Unable to open file"; }

		std::ofstream O("PrintFileChar.txt");
		O.write((char*)&Buf[0], s);
		O.close();
	}

	// #################################################

	// COUT INFORMATION:
	void CoutFileInfo(size_t BufSize)
	{
		std::cout << "#####################\n\n";
		std::vector<uint8_t> EntireFile; GetROMendian(Path);
		std::vector<uint8_t> Buf = ifsVectorIn<uint8_t>(Path, BufSize);
		std::vector<uint32_t> BufInt = ifsVectorIn<uint32_t>(Path, BufSize);
		std::cout << "####### FILE:\n(string size: " << EntireFile.size() << ")\n";
		std::cout << EntireFile.data() + '\0' << "\n\n";
		std::cout << "\n#####################\n\n";
		std::cout << "####### BUFFER:\n(string size: " << Buf.size() << ", int size: " << BufInt.size() << ")\n";
		std::cout << Buf.data() + '\0' << "\n\n";
		CoutVector(BufInt);
		std::cout << "\n#####################\n\n";
	}

	// PRINT INFORMATION:
	void PrintFileInfo(size_t BufSize)
	{
		std::ofstream O("PrintFileInfo.txt");
		O << "#####################\n\n";
		std::vector<uint8_t> EntireFile; GetROMendian(Path);
		std::vector<uint8_t> Buf = ifsVectorIn<uint8_t>(Path, BufSize);
		std::vector<uint32_t> BufInt = ifsVectorIn<uint32_t>(Path, BufSize);
		O << "####### FILE:\n(File size: " << FileSize << "string size: " << EntireFile.size() << ")\n";
		O << EntireFile.data() + '\0' << "\n\n";
		O << "\n#####################\n\n";
		O << "####### BUFFER:\n(string size: " << Buf.size() << ", int size: " << BufInt.size() << ")\n";
		O << Buf.data() + '\0' << "\n\n";
		CoutVector(BufInt);
		O << "\n#####################\n\n";
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