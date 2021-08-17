#pragma once

#ifndef YSXBYTE_H
#define YSXBYTE_H

#include <vector>

// #####################################################################################################################################

#define LOOP8 for(char n = 0; n < 8; ++n)

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

std::string ANDstr(std::string A, std::string B) { std::string C; for (int n = 0; n < A.size(); ++n) { if (n < B.size()) { C.push_back(A[n] & B[n]); } } }
std::string ORstr(std::string A, std::string B) { std::string C; for (int n = 0; n < A.size(); ++n) { if (n < B.size()) { C.push_back(A[n] | B[n]); } } }
std::string XORstr(std::string A, std::string B) { std::string C; for (int n = 0; n < A.size(); ++n) { if (n < B.size()) { C.push_back(A[n] ^ B[n]); } } }
std::string NOTstr(std::string A) { std::string B; for (int n = 0; n < A.size(); ++n) { B.push_back(~A[n]); } }
std::string RSHFstr(std::string A, unsigned char i) { std::string B; for (int n = 0; n < A.size(); ++n) { B.push_back(A[n] >> i); } }
std::string LSHFstr(std::string A, unsigned char i) { std::string B; for (int n = 0; n < A.size(); ++n) { B.push_back(A[n] << i); } }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// ####### UNIVERSAL CONSTANTS #######

// Numeric way to use Hexadecimals:
#define HEXCHARS const char HexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' }

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

std::string Bin2ASCII(std::string BIN) // Geeksforgeeks functions to convert Hex to ASCII
{
	std::string ASCII = "";
	for (size_t i = 0; i < BIN.length(); i += 2)
	{
		std::string part = BIN.substr(i, 2);
		char ch = stoul(part, nullptr, 2);
		ASCII += ch;
	}
	return ASCII;
}

// CHAR TO HEX STRING:
std::string ASCII2Hex(char c[])
{
	int Size = sizeof(c);
	std::string Hex;
	HEXCHARS;

	for (int n = 0; n < Size; ++n)
	{
		float d = c[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]);
	}
	return(Hex);
}
std::string ASCII2Hex(std::string s)
{
	std::string Hex;
	HEXCHARS;

	for (int n = 0; n < s.size(); ++n)
	{
		float d = s[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]); // Remember that it is always double the size
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

// GET AN UCHAR ARRAY AND ADDS STRING BYTES ON IT:
// USE CORRECT ARRAY SIZE, IT USES POINTER AND MODULO,
// BIGGER VALUES OVERFLOW AND OVERWRITE THE FIRST AND MORE INDEXES.
//		Array[n % Size]
void StrInUChar(std::string s, unsigned char* Array, unsigned int Size) { for (int n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void StrInChar(std::string s, char* Array, unsigned int Size) { for (int n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void StrInwChar(std::string s, wchar_t* Array, unsigned int Size) { for (int n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }  // Never tested
unsigned char* Str2ucPt(std::string Str) { return((unsigned char*)&Str[0]); }
char* Str2cPt(std::string Str) { return((char*)&Str[0]); }
wchar_t* Str2wcPt(std::string Str) { return((wchar_t*)&Str[0]); } // Never tested

// GET AN UCHAR ARRAY AND ADD BYTES TO A NEW STRING, PLEASE, USE CORRECT ARRAY SIZE, IT USES POINTER:
std::string uchar2str(unsigned char* Array, unsigned int Size) { std::string s; for (int n = 0; n < Size; ++n) { s.push_back(Array[n]); } return(s); }
std::string char2str(char* Array, unsigned int Size) { std::string s; for (int n = 0; n < Size; ++n) { s.push_back(Array[n]); } return(s); }

// #####################################################################################################################################

// #####################################################################################################################################
// ####### STRINGS #######

// TURN STRING TO ARRAY OF DOUBLES (IGNORE LAST BYTES IF < SIZEOF(DOUBLE)):
std::vector<double> str2vdouble(std::string s) // NOT TESTED YET
{
	char Size = sizeof(double);
	std::vector<double> v(floor(s.size() / 8.0));
	for (unsigned int n = 0; n < s.size() - Size; n += Size) { memcpy(&v[n], &s[n], Size); }
}
std::vector<float> str2vfloat(std::string s) // NOT TESTED YET
{
	char Size = sizeof(float);
	std::vector<float> v(floor(s.size() / 8.0));
	for (unsigned int n = 0; n < s.size() - Size; n += Size) { memcpy(&v[n], &s[n], Size); }
}
std::vector<int> str2vint(std::string s) // NOT TESTED YET
{
	char Size = sizeof(int);
	std::vector<int> v(floor(s.size() / 8.0));
	for (unsigned int n = 0; n < s.size() - Size; n += Size) { memcpy(&v[n], &s[n], Size); }
}
std::vector<short> str2vshort(std::string s) // NOT TESTED YET
{
	char Size = sizeof(short);
	std::vector<short> v(floor(s.size() / 8.0));
	for (unsigned int n = 0; n < s.size() - Size; n += Size) { memcpy(&v[n], &s[n], Size); }
}

// #####################################################################################################################################
// ####### ARRAYS #######

// INVERT
void InvertArray(char c[], char* pt)
{
	const int Size = sizeof c; char t[Size];
	for (int n = 0; n < Size; ++n) { t[Size - 1 - n] = c[n]; }
	memcpy(c, t, Size); //for (int n = 0; n < Size; ++n) { *(pt + n) = t[n]; }
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