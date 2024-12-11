#pragma once

#ifndef YSXBYTE_H
#define YSXBYTE_H

#include <vector>
#include "ysxMath/ysxReedSolo.h"

/*
Buf = Buffer = Buff;
*/

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
#define DIV255 0.003921568627451 // 0.0039215686274509803921568627451
#define DIV65535 (1.0 / 65535) // 1.5259021896696421759365224689097e-5

#define HEXCHARS { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' }

// Pointer mapping, tricks, hacks:
template <class T_> struct ysxBYTE_PointAndValue { void* p = nullptr; T_ v = 0; }; // A pointer and a value
template <class T_> struct ysxBYTE_PointAndVector { void* p = nullptr; std::vector<T_> Vec; }; // A pointer and multiple values
template <class T_, size_t N> struct ysxBYTE_PointAndArray { void* p = nullptr; T_ Array[N]; }; // A pointer and multiple values

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// STRINGS:
std::string ysxBYTE_ANDstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] &= B[n]; } } return(A); }
std::string ysxBYTE_ORstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] |= B[n]; } } return(A); }
std::string ysxBYTE_XORstr(std::string A, std::string B) { for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] ^= B[n]; } } return(A); }
std::string ysxBYTE_NOTstr(std::string A) { for (size_t n = 0; n < A.size(); ++n) { A[n] = ~A[n]; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
std::string ysxBYTE_RSHFstr(std::string A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] >>= i; } return(A); }
// CHANGE LATER THAT ONE BYTE CARRIES TO ANOTHER:
std::string ysxBYTE_LSHFstr(std::string A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] <<= i; } return(A); }

// VECTORS:
template <class T_> std::vector<T_> ysxBYTE_AND(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] &= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_OR(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] |= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_XOR(std::vector<T_> A, std::vector<T_> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] ^= B[n]; } } return(A); }
template <class T_> std::vector<T_> ysxBYTE_NOT(std::vector<T_> A)
{ for (size_t n = 0; n < A.size(); ++n) { A[n] = ~A[n]; } return(A); }
template <class T_> std::vector<T_> ysxBYTE_RSHF(std::vector<T_> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] >>= i; } return(A); }
template <class T_> std::vector<T_> ysxBYTE_LSHF(std::vector<T_> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] <<= i; } return(A); }

// ARRAYS:
template <class T_, size_t size> std::array<T_, size> ysxBYTE_AND(std::array<T_, size> A, std::array<T_, size> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] &= B[n]; } } return(A); }
template <class T_, size_t size> std::array<T_, size> ysxBYTE_OR(std::array<T_, size> A, std::array<T_, size> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] |= B[n]; } } return(A); }
template <class T_, size_t size> std::array<T_, size> ysxBYTE_XOR(std::array<T_, size> A, std::array<T_, size> B)
{ for (size_t n = 0; n < A.size(); ++n) { if (n < B.size()) { A[n] ^= B[n]; } } return(A); }
template <class T_, size_t size> std::array<T_, size> ysxBYTE_NOT(std::array<T_, size> A)
{ for (size_t n = 0; n < A.size(); ++n) { A[n] = ~A[n]; } return(A); }
template <class T_, size_t size> std::array<T_, size> ysxBYTE_RSHF(std::array<T_, size> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] >>= i; } return(A); }
template <class T_, size_t size> std::array<T_, size> ysxBYTE_LSHF(std::array<T_, size> A, uint8_t i) { for (size_t n = 0; n < A.size(); ++n) { A[n] <<= i; } return(A); }

// 'A' is going to be the return:
void ysxBYTE_ANDuc(uint8_t* A, uint8_t* B,const size_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] &= B[n]; } }
void ysxBYTE_ORuc(uint8_t* A, uint8_t* B,const size_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] |= B[n]; } }
void ysxBYTE_XORuc(uint8_t* A, uint8_t* B,const size_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] ^= B[n]; } }
void ysxBYTE_NOTuc(uint8_t* A, uint16_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] = ~A[n]; } }
void ysxBYTE_RSHFuc(uint8_t* A, uint8_t i,const size_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] >>= i; } }
void ysxBYTE_LSHFuc(uint8_t* A, uint8_t i,const size_t Size) { for (size_t n = 0; n < Size; ++n) { A[n] <<= i; } }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################################################################################################################################
// ####### TEXT CONVERTERS #######

// HEX NUMBERS (AS std::string) TO A STRING OF ASCII (char, byte):
std::string ysxBYTE_Hex2ASCII(std::string hex)
{ std::string ASCII = ""; for (size_t i = 0; i < hex.length(); i += 2) { ASCII += stoul(hex.substr(i, 2), nullptr, 16); } return ASCII; }

std::string ysxBYTE_Bin2ASCII(std::string Bin)
{ std::string ASCII = ""; for (size_t i = 0; i < Bin.length(); i += 2) { ASCII += stoul(Bin.substr(i, 2), nullptr, 2); } return ASCII; }

// CHAR TO HEX STRING:
std::string ysxBYTE_ASCII2Hex(uint8_t* c, uint16_t Size)
{
	std::string Hex;
	const uint8_t HexChars[16] = HEXCHARS;
	float d = 0; uint8_t h2 = 0; uint8_t h1 = 0;
	for (size_t n = 0; n < Size; ++n)
	{
		d = c[n] / 16.0; h2 = floor(d); h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]);
	}
	return(Hex);
}
std::string ysxBYTE_ASCII2Hex(std::string s)
{
	std::string Hex;
	const uint8_t HexChars[16] = HEXCHARS;
	float d = 0; uint8_t h2 = 0; uint8_t h1 = 0;
	for (size_t n = 0; n < s.size(); ++n)
	{
		d = s[n] / 16.0; h2 = floor(d); h1 = round((d - h2) * 16);
		Hex.push_back(HexChars[h2]); Hex.push_back(HexChars[h1]);
	}
	return(Hex);
}

// STRING OF CHARS TO A STRING OF BINARY NUMBER:
std::string ysxBYTE_ASCII2Bin(uint8_t c)
{
	std::string Bin;
	LOOP8 { if (c & 1 << (7 - n)) { Bin.push_back('1'); } else { Bin.push_back('0'); } }
	return(Bin);
}

std::string ysxBYTE_ASCII2Bin(std::string s)
{
	std::string Bin;
	for (size_t c = 0; c < s.size(); ++c)
	{
		LOOP8 { if (s[c] & 1 << (7 - n)) { Bin.push_back('1'); } else { Bin.push_back('0'); } }
	}
	return(Bin);
}

// HEX string to Decimal (uses full string as one number):
uint64_t ysxBYTE_Hex2Dec(std::string Hex)
{
	uint64_t Sum = 0; size_t N = Hex.size();
	for (size_t n = 0; n < N; ++n)
	{
		std::string s; s.push_back(Hex[n]);
		Sum += stoul(s, nullptr, 16) * pow(16, n);
	}
	return(Sum);
}

// GET AN UCHAR ARRAY AND ADD STRING BYTES ON IT:
//		Array[n % Size] = s[n];
// Anyway, those functions are pretty useless...
void ysxBYTE_StrInUChar(std::string s, uint8_t* Array, const size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void ysxBYTE_StrInChar(std::string s, char* Array, const size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }
void ysxBYTE_StrInwChar(std::string s, wchar_t* Array, const size_t Size) { for (size_t n = 0; n < s.size(); ++n) { Array[n % Size] = s[n]; } }  // Never tested

// GET AN UCHAR ARRAY AND ADD BYTES TO A NEW STRING:
std::string ysxBYTE_uchar2str(uint8_t* Array,const size_t Size) { std::string s; for (size_t n = 0; n < Size; ++n) { s.push_back(Array[n]); } return(s); }

// INSERT WHATEVER IS IN A STRING TO WHATEVER DATA IS THE OUTPUT, BE SURE TO CHECK SIZES:
// 'Size' of the 'O' array; Input wont copy if it have more elements than Size;
void ysxBYTE_StringOut(const std::string& I, uint8_t* O, const size_t Size) { I.size() < Size ? memcpy(O, &I[0], I.size()) : memcpy(O, &I[0], Size); }

// #####################################################################################################################################
// ####### VECTOR CONVERTERS #######

// NORMALIZE FLOAT VALUES TO INTEGER (RANGE: '-1 TO 1'; GOING TO FIX THIS LATER):
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
std::vector<uint16_t> ysxBYTE_ScaleUI16(std::vector<double> V)
{
	std::vector<uint16_t> ui16(V.size());
	for (size_t n = 0; n < V.size(); ++n) { ui16[n] = round((V[n] + 1) * 32767.5); }
	return(ui16);
}
std::vector<uint8_t> ysxBYTE_ScaleUI8(std::vector<double> V)
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
	uint8_t sSize = s.size();
	std::vector<T_> v(ceil(sSize / (double)sizeof(T_)));
	memcpy(&v[0], &s[0], sSize);
	return(v);
}
template <class T_> std::vector<T_> ysxBYTE_str2Vec(uint8_t* s, uint32_t Size)
{
	std::vector<T_> v(ceil(Size / (double)sizeof(T_)));
	memcpy(&v[0], s, Size);
	return(v);
}

// SCALES FLOAT VALUES TO STRING, PLEASE, USE VALUES BETWEEN '-1' AND '1':
// Also check the function 'ScaleFloat2UI8':
std::string ysxBYTE_ScaleFloat2String(std::vector<float> V)
{
	std::string ui8;
	for (size_t n = 0; n < V.size(); ++n) { ui8 += (uint8_t)((V[n] + 1) * 127.5); }
	return(ui8);
}

// RETURN STRING THAT IS THE BASE_10 INT OF EACH BYTE:
std::string ysxBYTE_Bytes2Text(uint8_t* p, const size_t Size)
{
	std::string txt;
	for (size_t n = 0; n < Size; ++n) { txt += std::to_string(p[n]) + " "; }
	return(txt);
}
// RETURN STRING THAT IS THE BASE_10 INT OF EACH BYTE:
template <class T_> std::string ysxBYTE_Array2Text(T_* p, const size_t Size)
{
	std::string txt;
	for (size_t n = 0; n < Size; ++n) { txt += std::to_string((uint64_t)p[n]) + " "; }
	return(txt);
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
template<class T_> T_ ysxBYTE_Buffer2Type(void* p) { return(*(T_*)p); }
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
