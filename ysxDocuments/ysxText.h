#pragma once

#ifndef YSXTEXT_H
#define YSXTEXT_H

// #####################
// ####### By Sophia Cristina
// ####### Header made to handle text, not binary.
// ####### It also deals with 'strings'.
// ####### This file is included in 'ysxPrintTxt.h'.
// #####################


// #####################################################################################################################################

// IS NUMBER?:
bool ysxTEXT_IsNumber(char C) { if (C > 47 && C < 58) { return(true); } return (false); }

// IS LETTER?:
bool ysxTEXT_IsLetter(char C) { if ((C > 64 && C < 91) || (C > 96 && C < 123)) { return(true); } return (false); }

// ###################################
// ####### CONVERTERS #######
// ###################################

// STRING TO WCHAR_T
wchar_t* ysxTEXT_Str2wChart(std::string Str)
{
	Str += '\0';
	int TxtLim = Str.length();
	wchar_t* C = new wchar_t[TxtLim];
	memcpy(C, &Str[0], TxtLim);
	return(C);
}

// STRING TO CHAR ARRAY:
// * Now on 'ysxBytes.h'

// CHAR VECTOR TO A STRING:
std::string ysxTEXT_Char2Str(std::vector<uint8_t> C) { std::string Str; for (size_t n = 0; n < C.size(); ++n) { Str.push_back(C[n]); } return (Str); }
// CHAR TO STRING:
std::string ysxTEXT_Char2Str(uint8_t* C, int Size) { std::string Str; for (size_t n = 0; n < Size; ++n) { Str.push_back(C[n]); } return (Str); }

// GET A NUMBER CHAR (48 TO 57) AND RETURN AN INTEGER CHAR:
uint8_t ysxTEXT_Chr2Int(uint8_t C) { if (C > 47 && C < 58) { return(C - 48); } return(0); }

// GET STRING AS TEXT AND READ AS AN INTEGER:
int64_t ysxTEXT_Str2Int(std::string S)
{
	if (S.size() > 1)
	{
		int64_t a = 0, Count = 0;
		bool Ok = false, Neg = false; if (S[0] == '-') { Neg = true; }
		std::vector<uint8_t> Array;
		for (size_t n = 0; n < S.length(); ++n) { if (S[n] > 47 && S[n] < 58 || S[n] == '-') { Ok = true; break; } }
		if (Ok)
		{
			for (size_t n = 0; n < S.length(); ++n)
			{
				if (S[n] > 48 && S[n] < 58) { Array.push_back(S[n] - 48); ++Count; }
				else if (S[n] == '0' && n != 0) { Array.push_back(0); ++Count; }
			}
			for (size_t n = 0; n < Count; ++n) { if (Array[n] != 0) { a += Array[n] * (pow(10, Count - n - 1)); } else { a *= 10; } }
		}
		else { return(0); }
		if (Neg) { a *= -1; }
		return(a);
	}
	return(0);
}

// GET STRING AS TEXT AND READ AS A DOUBLE:
double ysxTEXT_Str2Double(std::string S)
{
	size_t n = 0;
	std::string Str, Str0;
	while (S[n] != '.' && n < S.size()) { Str.push_back(S[n]); ++n; }
	if (n + 1 < S.size()) { for (size_t m = n + 1; m < S.size(); ++m) { Str0.push_back(S[m]); } }
	else { Str0 = "0"; }
	int Int = ysxTEXT_Str2Int(Str), Int2 = ysxTEXT_Str2Int(Str0);
	return (Int + (Int2 * (1.0 / pow(10, Str0.size()))));
}

// ###################################
// ####### CONVERTERS #######
// ###################################

// LETTER INDEX:
uint8_t ysxTEXT_LetterIndex(uint8_t C)
{
	if (ysxTEXT_IsNumber(C)) { return(ysxTEXT_Chr2Int(C)); }
	if (C > 96 && C < 123) { return(C - 96); }
	else if (C > 64 && C < 91) { return(C - 64); }
	return(0);
}
uint8_t ysxTEXT_LetterIndex(uint8_t n, bool Capital)
{
	uint8_t c;
	if (n > 26 || n < 1) { return(0); }
	else { if (Capital) { return(n + 64); } else { return(n + 96); } }
}

// It means 'String to Int/Double, Clean Char', get a string with chars and number,
// filter out the chars, return it as a int or double:
int ysxTEXT_Str2IntClnChr(std::string s)
{
	std::string t;
	for (size_t n = 0; n < s.size(); ++n)
	{
		if (ysxTEXT_IsNumber(s[n])) { t.push_back(s[n]); }
	}
	return(ysxTEXT_Str2Int(t));
}
double ysxTEXT_Str2DblClnChr(std::string s)
{
	std::string t; bool FirstDot = false;
	for (size_t n = 0; n < s.size(); ++n)
	{
		if (ysxTEXT_IsNumber(s[n])) { t.push_back(s[n]); }
		else if (!FirstDot && s[n] == '.') { t.push_back(s[n]); FirstDot = true; }
	}
	return(ysxTEXT_Str2Double(t));
}

// ################################################# END ####################################################################################

#endif // SCPARSE_