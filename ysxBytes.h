#pragma once

#ifndef YSXBYTE_H
#define YSXBYTE_H

#include <vector>
#include "ysxplg\\ysxReedSolo.h"

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
//
// CHANGES (KEEP ORDER):
//
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #####################################################################################################################################

#define LOOP4 for(uint8_t n = 0; n < 4; ++n)
#define LOOP5 for(uint8_t n = 0; n < 5; ++n)
#define LOOP6 for(uint8_t n = 0; n < 6; ++n)
#define LOOP7 for(uint8_t n = 0; n < 7; ++n)
#define LOOP8 for(uint8_t n = 0; n < 8; ++n)
#define LOOP9 for(uint8_t n = 0; n < 9; ++n)
#define LOOP10 for(uint8_t n = 0; n < 10; ++n)
#define LOOP12 for(uint8_t n = 0; n < 12; ++n)
#define LOOP16 for(uint8_t n = 0; n < 16; ++n)
#define LOOP24 for(uint8_t n = 0; n < 24; ++n)
#define LOOP32 for(uint8_t n = 0; n < 32; ++n)
#define LOOP48 for(uint8_t n = 0; n < 48; ++n)
#define LOOP64 for(uint8_t n = 0; n < 64; ++n)
#define LOOP128 for(uint8_t n = 0; n < 128; ++n)
#define LOOP256 for(uint16_t n = 0; n < 256; ++n)

#define DIV31 0.032258064516129 // 0.03225806451612903225806451612903
#define DIV47 0.0212765957446808 // 0.02127659574468085106382978723404
#define DIV63 0.0158730158730159 // 0.01587301587301587301587301587302
#define DIV95 0.0105263157894737 // 0.01052631578947368421052631578947
#define DIV127 0.0078740157480315 // 0.00787401574803149606299212598425
#define DIV190 0.0052631578947368 // 0.00526315789473684210526315789474
#define DIV256 0.00390625 // 0.00390625
#define DIV65535 1.0 / 65535 // 1.5259021896696421759365224689097e-5

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################


std::string ysxBYTE_ANDstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] &= B[n]; } } return(A); }
std::string ysxBYTE_ORstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] |= B[n]; } } return(A); }
std::string ysxBYTE_XORstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] ^= B[n]; } } return(A); }
std::string ysxBYTE_NOTstr(std::string A) { for (size_t n = 0; n < A.size(); ++n) { A[n] = ~A[n]; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
std::string ysxBYTE_RSHFstr(std::string A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] >>= i; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
std::string ysxBYTE_LSHFstr(std::string A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] <<= i; } return(A); }

template <class T_> std::vector<T_> ysxBYTE_ANDv(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] &= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_ORv(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] |= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_XORv(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] ^= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_NOTv(std::vector<T_> A)
{ for (size_t n = 0; n < A.size(); ++n) { A[n] = ~A[n]; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
template <class T_> std::vector<T_> ysxBYTE_RSHFstr(std::vector<T_> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] >>= i; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
template <class T_> std::vector<T_> ysxBYTE_LSHFstr(std::vector<T_> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] <<= i; } return(A); }

// A is going to be the return:
void ysxBYTE_ANDuc(uint8_t* A, uint8_t* B, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] &= B[n]; } }
void ysxBYTE_ORuc(uint8_t* A, uint8_t* B, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] |= B[n]; } }
void ysxBYTE_XORuc(uint8_t* A, uint8_t* B, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] ^= B[n]; } }
void ysxBYTE_NOTuc(uint8_t* A, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] = ~A[n]; } }
void ysxBYTE_RSHFuc(uint8_t* A, uint8_t i, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] >>= i; } }
void ysxBYTE_LSHFuc(uint8_t* A, uint8_t i, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] <<= i; } }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// ####### UNIVERSAL CONSTANTS #######

// Numeric way to use Hexadecimals:
#define HEXCHARS { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' }

// ####### CONVERTERS #######

// HEX NUMBERS (AS std::string) TO A STRING OF ASCII (char, byte):
std::string ysxBYTE_Hex2ASCII(std::string hex) // Geeksforgeeks functions to convert Hex to ASCII
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

std::string ysxBYTE_Bin2ASCII(std::string Bin)
{
	std::string ASCII = "";
	for (size_t i = 0; i < Bin.length(); i += 2)
	{
		std::string part = Bin.substr(i, 2);
		char ch = stoul(part, nullptr, 2);
		ASCII += ch;
	}
	return ASCII;
}

// CHAR TO HEX STRING:
std::string ysxBYTE_ASCII2Hex(uint8_t* c, uint16_t Size)
{
	std::string Hex;
	const char HexChars[16] = HEXCHARS;

	for (size_t n = 0; n < Size; ++n)
	{
		float d = c[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]);
	}
	return(Hex);
}
std::string ysxBYTE_ASCII2Hex(std::string s)
{
	std::string Hex;
	const char HexChars[16] = HEXCHARS;

	for (size_t n = 0; n < s.size(); ++n)
	{
		float d = s[n] / 16.0; int h2 = floor(d); int h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]); // Remember that it is always double the size
	}
	return(Hex);
}

// Write byte as text and convert to int:
/*std::vector<uint8_t> ASCII2Int(std::string s)
{
	std::vector<uint8_t> O;
	std::vector<std::vector<uint8_t>> Oo;
	for (size_t n = 0; n < s.size(); ++n)
	{
		std::vector<uint16_t> O;
		if (IsNumber(s[n]))
		{
			O.push_back(Chr2Int(s[n]));
		}
		uint8_t i = 0;
		for (uint8_t o = 0; o < O.size(); ++o)
		{
			i += O[o] * pow(10, O.size() - o - 1);
		}
	}
	return(O);
}*/

// STRING OF CHARS TO A STRING OF BINARY NUMBER ! NOT TESTED !:
std::string ysxBYTE_ASCII2Bin(std::string s)
{
	std::string Bin;
	const char HexChars[16] = HEXCHARS;

	for (size_t c = 0; c < s.size(); ++c)
	{
		LOOP8
		{
			uint8_t b = pow(2, n);
			if (s[c] & b) { Bin.push_back('1'); }
			else { Bin.push_back('0'); }
		}
	}
	return(Bin);
}

// HEX string to Decimal (uses full string as one number):
uint64_t ysxBYTE_Hex2Dec(std::string Hex)
{
	uint64_t Sum = 0;
	for (size_t n = 0; n < Hex.size(); ++n)
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
// Anyway, those functions are pretty useless...
void ysxBYTE_StrInUChar(std::string s, uint8_t* Array, size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void ysxBYTE_StrInChar(std::string s, char* Array, size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void ysxBYTE_StrInwChar(std::string s, wchar_t* Array, size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }  // Never tested

// GET AN UCHAR ARRAY AND ADD BYTES TO A NEW STRING:
std::string ysxBYTE_uchar2str(uint8_t* Array, size_t Size) { std::string s; for (size_t n = 0; n < Size; ++n) { s.push_back(Array[n]); } return(s); }

// INSERT WHATEVER IS ON A STRING TO WHATEVER DATA IS THE OUTPUT, BE SURE TO CHECK SIZES:
// 'Size' of the 'O' array; Input wont copy if it have more elements than Size;
void ysxBYTE_StringOut(std::string I, uint8_t* O, size_t Size) { I.size() < Size ? memcpy(O, &I[0], I.size()) : memcpy(O, &I[0], Size); }

// ####### VECTOR CONVERTERS #######

// NORMALIZE FLOAT VALUE TO '-1 TO 1':
// * In the future i'm going to use template *
std::vector<uint16_t> ysxBYTE_ScaleUI16(std::vector<float> V)
{
	std::vector<uint16_t> ui16(V.size());
	for (size_t n = 0; n < V.size(); ++n) { ui16[n] = round((V[n] + 1) * 32767.5); }
	return(ui16);
}
std::vector<uint8_t> ysxBYTE_ScaleUI8(std::vector<float> V)
{
	std::vector<uint8_t> ui8(V.size());
	for (size_t n = 0; n < V.size(); ++n) { ui8[n] = round((V[n] + 1) * 127.5); }
	return(ui8);
}

// #####################################################################################################################################
// ####### STRINGS #######

// TURN STRING TO VECTOR (IGNORE LAST BYTES IF < SIZEOF(T_)):
template <class T_> std::vector<T_> ysxBYTE_str2Vec(std::string s) // NOT TESTED YET
{
	uint8_t Size = sizeof(T_), sSize = s.size();
	std::vector<T_> v(ceil(sSize / (double)Size));
	memcpy(&v[0], &s[0], sSize);
	return(v);
}
template <class T_> std::vector<T_> ysxBYTE_str2Vec(uint8_t* s, uint32_t Size)
{
	uint8_t tSize = sizeof(T_);
	std::vector<T_> v(ceil(Size / (double)tSize));
	memcpy(&v[0], s, Size);
	return(v);
}

// SCALES FLOAT VALUES TO STRING, PLEASE, USE VALUES BETWEEN '-1' AND '1':
// Also check the function 'ScaleFloat2UI8':
std::string ysxBYTE_ScaleFloat2String(std::vector<float> V)
{
	std::string ui8;
	for (size_t n = 0; n < V.size(); ++n) { ui8 += round((V[n] + 1) * 127.5); }
	return(ui8);
}

// #####################################################################################################################################
// ####### ARRAYS #######

// INVERT
template <size_t Size> void ysxBYTE_InvertArray(uint8_t* c)
{
	std::array<uint8_t, Size> t;
	for (size_t n = 0; n < Size; ++n) { t[Size - 1 - n] = c[n]; }
	memcpy(c, &t[0], Size); //for (size_t n = 0; n < Size; ++n) { *(pt + n) = t[n]; }
}

// BUFFER TO DATA:
template<class T_>
T_ ysxBYTE_Buffer2Type(uint8_t* ui8, bool LittleBig)
{
	T_ R;
	if (LittleBig) { ui8 += sizeof(T_); }
	uint8_t* q = (uint8_t*)&R;
	for (uint8_t n = 0; n < sizeof(T_); ++n) { *q = *ui8; ++q; if (LittleBig) { --ui8; } else { ++ui8; } }
	return(R);
}

// #####################################################################################################################################
// ####### MATHS #######

// HAMMING DISTANCE (USE PROPER TYPES):
// https://en.wikipedia.org/wiki/Hamming_distance
template <class T_>
T_ ysxBYTE_HammingDist(T_ x, T_ y)
{
	int dist = 0;

	// The ^ operators sets to 1 only the bits that are different:
	for (size_t val = x ^ y; val > 0; ++dist)
	{
		// We then count the bit set to 1 using the Peter Wegner way:
		val &= val - 1; // Set to zero val's lowest-order 1
	}

	return(dist); // Number of differing bits
}

// HAMMING WEIGHT (CHECK BETTER SOMEWHERE ELSE LATER):
// https://en.wikiversity.org/wiki/Reed%E2%80%93Solomon_codes_for_coders
size_t ysxBYTE_HammingWeight(size_t x) { size_t weight = 0; while (x > 0) { weight += x & 1; x >>= 1; } return(weight); }

// #################################################
// #################################################
// #################################################

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_