#pragma once

#ifndef YSXBYTE_H
#define YSXBYTE_H

#include <vector>

// #####################################################################################################################################
// ####### CONSTANTES UNIVERSAIS #######

// Numeric way to use Hexadecimals:
const char HexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

// ####### CONVERSORES #######

// HEX NUMBERS (AS std::string) TO A STRING OF ASCII (char, byte):
std::string Hex2ASCII(std::string hex) // Geeksforgeeks functions to convert Hex to ASCII
{
	std::string ASCII = "";
	for (size_t i = 0; i < hex.length(); i += 2)
	{
		std::string part = hex.substr(i, 2);
		char ch = stoul(part, nullptr, 16);
		ASCII += ch;
	}
	return ASCII;
}

// CHAR TO HEX STRING:
std::string ASCII2Hex(char c[])
{
	int Size = sizeof(c);
	std::string Hex;
	
	for (int n = 0; n < Size; ++n)
	{
		float d = c[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]);
	}
	return(Hex);
}

// HEX string to Decimal (uses full string as one number):
long long Hex2Dec(std::string Hex)
{
	long long Sum = 0;
	for (int n = 0; n < Hex.size(); ++n)
	{
		std::string s; s.push_back(Hex[n]);
		char ch = stoul(s, nullptr, 16); // 15
		Sum += ch * pow(16, n);
	}
	return(Sum);
}

// #####################################################################################################################################

// #####################################################################################################################################
// ####### ARRAYS #######

// INVERT
void InvertArray(char c[], char* pt)
{
	const int Size = sizeof c; char t[Size];
	for (int n = 0; n < Size; ++n) { t[Size - 1 - n] = c[n]; }
	for (int n = 0; n < Size; ++n) { *(pt + n) = t[n]; }
}

// BUFFER TO DATA:
long long Buffer2long(char c[8], bool LittleBig)
{
	long long Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
int Buffer2int(char c[4], bool LittleBig)
{
	int Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
short int Buffer2sint(char c[2], bool LittleBig)
{ 
	short int Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
float Buffer2float(char c[4], bool LittleBig)
{ 
	float Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
double Buffer2double(char c[8], bool LittleBig)
{ 
	double Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
unsigned int Buffer2uint(char c[4], bool LittleBig)
{
	unsigned int Return;
	char* p = c; if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return; for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}
unsigned short int Buffer2usint(char c[2], bool LittleBig)
{
	unsigned short int Return; char* p = c;
	if (LittleBig) { p += sizeof(c); }
	char* q = (char*)&Return;
	for (int n = 0; n < sizeof(c); ++n) { *q = *p; ++q; if (!LittleBig) { ++p; } else { --p; } }
	return(Return);
}

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_