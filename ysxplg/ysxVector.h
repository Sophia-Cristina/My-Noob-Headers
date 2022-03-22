#pragma once

#ifndef YSXVECTOR_H
#define YSXVECTOR_H

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
//
// CHANGES (KEEP ORDER):
// * Function 'ExpSignalVec' is now 'ExponentVec'. I don't remember why it was 'Signal';
// * Functions of trigonometric vectors and signals are now on 'ysxElectr.h';
// * Older versions don't use template, you may fix if your code used the older version. W.I.P!
// * 'SumVecIndex' and any fucntion '-VecIndex' were removed, because the older version was dumb, they are easy to code in hand and in function would not be optmal;
// * Trying to work out 'for' loops which call '.size()' in every loop to one that calls 'size_t Size = .size()'. W.I.P;
//
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################

// ############################
// ####### TÉCNICOS
// ############################

// CONVERTERS:
std::vector<float> SInt2Float(std::vector<uint16_t> SInt) { std::vector<float> V; for (size_t n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<double> SInt2double(std::vector<uint16_t> SInt) { std::vector<double> V; for (size_t n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<float> Int2Float(std::vector<int> Int) { std::vector<float> V; for (size_t n = 0; n < Int.size(); ++n) { V.push_back(Int[n]); } return(V); }
std::vector<int> Float2Int(std::vector<float> Float) { std::vector<int> V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<int> SInt2Int(std::vector<uint16_t> SInt) { std::vector<int> V; for (size_t n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<double> Float2Double(std::vector<float> Float) { std::vector<double> V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<float> Double2Float(std::vector<double> Double) { std::vector<float> V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
std::vector<uint16_t> Double2SInt(std::vector<double> Double) { std::vector<uint16_t> V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
std::vector<uint16_t> Float2SInt(std::vector<float> Float) { std::vector<uint16_t> V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<uint8_t> Double2uChar(std::vector<double> Double) { std::vector<uint8_t> V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255)); } return(V); }
std::vector<char> Double2Char(std::vector<double> Double) { std::vector<char> V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 127)); } return(V); }
std::vector<uint8_t> Float2uChar(std::vector<float> Float) { std::vector<uint8_t> V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(round(Float[n] * 255)); } return(V); }
std::vector<char> Float2Char(std::vector<float> Float) { std::vector<char> V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(round(Float[n] * 127)); } return(V); }
std::vector<double> String2double(std::string S) { std::vector<double> V; for (size_t n = 0; n < S.size(); ++n) { V.push_back((int)S[n] / 255.0); } return(V); }
// Use values from '0' to '1.0', it multiplies by '255.0'
std::string Double2String(std::vector<double> Double) { std::string V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255.0)); } return(V); }
std::vector<double> String2Double(std::string S) { std::vector<double> V; for (size_t n = 0; n < S.size(); ++n) { V.push_back((int)S[n] / 255.0); } return(V); }
std::vector<float> String2Float(std::string S) { std::vector<float> V; for (size_t n = 0; n < S.size(); ++n) { V.push_back((int)S[n] / 255.0); } return(V); }
// (Int[n] / 4294967295) * 255 = Int[n] / 16843099:
std::string UInt2String(std::vector<unsigned long> Int) { std::string V; for (size_t n = 0; n < Int.size(); ++n) { V.push_back(round(Int[n] / 16843099.0)); } return(V); }
// (Int[n] / 65535) * 255 = Int[n] / 257:
std::string UShort2String(std::vector<unsigned short> Int) { std::string V; for (size_t n = 0; n < Int.size(); ++n) { V.push_back(round(Int[n] / 257.0)); } return(V); }

// JOIN VECTORS:
template <class T_>
std::vector<T_> JoinVectors(std::vector<T_> VecPre, std::vector<T_> VecSuf) { for (size_t n = 0; n < VecSuf.size(); ++n) { VecPre.push_back(VecSuf[n]); } return(VecPre); }

// MERGE VECTORS:
template <class T_>
std::vector<T_> MergeVectors(std::vector<T_> a, std::vector<T_> b)
{
	//merge(int A[], int m, int B[], int n, int C[]) {
	uint32_t i = 0, j = 0, k = -1; // k will be incremented before storing a number in C[k]
	uint32_t as = a.size(), bs = b.size();
	std::vector<T_> c(as + bs);
	while (i < as && j < bs) { if (a[i] < b[j]) { c[++k] = a[i++]; } else { c[++k] = b[j++]; } }
	if (i == as) { for (; j < bs; j++) { c[++k] = b[j]; } }
	else { for (; i < as; i++) { c[++k] = a[i]; } } // j == n, copy A[i] to A[m-1] to C
	return(c);
}

// BREAK VECTOR INTO SUB-BLOCK:
std::vector<std::vector<double>> VectorSubBlocks(std::vector<double> In, uint32_t Div)
{
	std::vector<double> v;
	std::vector<std::vector<double>> V;
	uint32_t Fraction = In.size() / Div;
	size_t Size = In.size();

	for (size_t n = 0; n < Size; ++n)
	{
		v.push_back(In[n]);
		uint32_t Mod = n % Fraction;
		if (Mod == Fraction - 1) { V.push_back(v); v = std::vector<double>::vector(); }
		else if (n == Size - 1) { V.push_back(v); }
	}
	return(V);
}

// ############################
// ####### OPERATIONS WITH ZEROS
// ############################

// IF VALUE IN 'Vec0[n]' IS EQUAL TO '0', IT WILL CHANGE TO THE VALUE IN 'Vec1[n]', EVEN IF THAT IS ANOTHER '0':
template <class T_>
std::vector<T_> SubstituteZero(std::vector<T_> Vec0, std::vector<T_> Vec1)
{
	std::vector<T_> V; bool v0v1 = false;
	uint32_t Size = 0;
	if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }	else { Size = Vec1.size(); v0v1 = true; }
	for (size_t n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (size_t n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (size_t n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// INSERT ZEROS IN RANDOM POSITIONS INTO A VECTOR:
template <class T_>
std::vector<T_> InsertRandomZeros(std::vector<T_> Vector, size_t Zeros)
{
	if (Zeros < 1) { Zeros = 1; }
	std::vector<T_> V; size_t Size = Vector.size();
	for (size_t Z = 0; Z < Zeros; ++Z)
	{
		std::vector<T_> v;
		uint32_t Rand = rand() % Size;
		for (size_t n = 0; n < Size; ++n)
		{
			v.push_back(Vector[n]); if (n == Rand) { v.push_back(0); }
		}
		Vector = v;
		V = v;
	}
	return (V);
}

// INSERT ZEROS AT THE BEGINNING OR THE END OF A VECTOR:
template <class T_>
std::vector<T_> InsertZerosBeginorEnd(std::vector<T_> Vector, size_t Zeros, bool BeginEnd)
{
	std::vector<T_> V; size_t Size = Vector.size();
	if (!BeginEnd) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	for (size_t n = 0; n < Size; ++n) { V.push_back(Vector[n]); }
	if (BeginEnd) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	return (V);
}

// INSERT ZEROS BETWEEN EACH TERM:
template <class T_>
std::vector<T_> InsertZerosBetweenTerms(std::vector<T_> Vector, size_t Zeros, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<T_> V; size_t Size = Vector.size();
	for (size_t n = 0; n < Size; ++n)
	{
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}
template <class T_>
std::vector<T_> InsertZerosBetweenTermsExpo(std::vector<T_> Vector, size_t Zeros, double InitialPower, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<T_> V; size_t Size = Vector.size();
	for (size_t n = 0; n < Size; ++n)
	{
		double Zr = pow(Zeros, (n + InitialPower));
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (size_t Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (size_t Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// INSERT ZEROS AT A INDEX:
template <class T_>
std::vector<T_> InsertZerosatTerm(std::vector<T_> Vector, size_t Zeros, uint32_t at, bool BeforeAfter)
{
	std::vector<T_> V; size_t Size = Vector.size();
	for (size_t n = 0; n < Size; ++n)
	{
		if (!BeforeAfter && n == at) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAfter && n == at) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// DELETE ZEROS:
template <class T_>
std::vector<T_> DeleteZeros(std::vector<T_> Vector)
{
	std::vector<T_> V; size_t Size = Vector.size();
	for (size_t n = 0; n < Size; ++n) { if (Vector[n] != 0) { V.push_back(Vector[n]); } }
	return (V);
}

// ############################
// ####### OPERATIONS WITH NUMBERS
// ############################

// Insert copy of an indexed value at random positions into a vector:
std::vector<double> InsertRandomCopies(std::vector<double> Vector, uint32_t Copies)
{
	if (Copies < 1) { Copies = 1; }
	std::vector<double> V;
	for (size_t c = 0; c < Copies; ++c)
	{
		std::vector<double> v;
		uint32_t Rand = rand() % Vector.size();
		for (size_t n = 0; n < Vector.size(); ++n)
		{
			v.push_back(Vector[n]); if (n == Rand) { v.push_back(Vector[n]); }
		}
		Vector = v;
		V = v;
	}
	return (V);
}

// if (Index + n < DSize) { Dest[Index + n] = In[n]; }:
void SubstituteVals(std::vector<double>& Dest, std::vector<double> In, uint32_t Index)
{
	uint32_t Size = (Index + In.size()) > Dest.size() ? Dest.size() : In.size();
	for (size_t n = 0; n < Size; ++n) { Dest[Index + n] = In[n]; }
}
void SubstituteVals(std::vector<float>& Dest, std::vector<float> In, uint32_t Index)
{
	uint32_t Size = (Index + In.size()) > Dest.size() ? Dest.size() : In.size();
	for (size_t n = 0; n < Size; ++n) { Dest[Index + n] = In[n]; }
}
void SubstituteVals(std::vector<uint8_t>& Dest, std::vector<uint8_t> In, uint32_t Index)
{
	uint32_t Size = (Index + In.size()) > Dest.size() ? Dest.size() : In.size();
	for (size_t n = 0; n < Size; ++n) { Dest[Index + n] = In[n]; }
}
// Dest[(Index + n) % DSize] = In[n];
void SubstituteValsMod(std::vector<double>& Dest, std::vector<double> In, uint32_t Index)
{
	uint32_t Size = Dest.size();
	for (size_t n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}
void SubstituteValsMod(std::vector<float>& Dest, std::vector<float> In, uint32_t Index)
{
	uint32_t Size = Dest.size();
	for (size_t n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}
void SubstituteValsMod(std::vector<uint8_t>& Dest, std::vector<uint8_t> In, uint32_t Index)
{
	uint32_t Size = Dest.size();
	for (size_t n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SORTS
// ############################

// QUICKSORT:
template <class T_>
void QuickSort(std::vector<T_>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } size_t pivot = V[r]; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i] <= pivot) { std::swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSortPtx(std::vector<Point<double>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } double pivot = V[r].x; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].x <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPtx(V, l, cnt - 2); QuickSortPtx(V, cnt, r);
}
void QuickSortPty(std::vector<Point<double>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } double pivot = V[r].y; uint32_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].y <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPty(V, l, cnt - 2); QuickSortPty(V, cnt, r);
}

// BUBBLE SORT:
template <class T_>
void BubbleSort(std::vector<T_>& V)
{
	uint32_t N = V.size();
	for (uint32_t i = 0; i < N; ++i)
	{ uint32_t p = 0; while (p < N - 1 - i) { if (V[p] > V[p + 1]) { T_ t = V[p]; V[p] = V[p + 1]; V[p + 1] = t; } ++p; } }
}

// INSERTION SORT:
template <class T_>
void InsertionSort(std::vector<T_>& V)
{
	uint32_t n = V.size(), K, k;
	if (n > 1)
	{
		for (uint32_t h = 1; h < n; ++h)
		{
			K = V[h]; k = h - 1;
			while (k >= 0 && K < V[k]) { V[k + 1] = V[k]; --k; }
			V[k + 1] = K;
		}
	}
}

// ############################
// ####### SEARCH
// ############################

// BINARY SEARCH (-1 = NOT FOUND):
// Vector should be sorted already!
/*template <class T_>
uint32_t BinSearch(uint32_t Val, std::vector<T_> V)
{
	uint32_t n = 0, m = V.size();
	while (lo <= hi)
	{
		uint32_t mid = (n + m) / 2;	if (Val == V[mid]) { return(mid); } // found
		if (Val < V[mid]) { m = mid - 1; } else { n = mid + 1; }
	}
	return(-1); // n and m have crossed; key not found
}*/

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MAX AND MINIMUM OF A VECTOR
// ############################

template <class T_>
T_ MaxVec(std::vector<T_> Vec) { T_ Max = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }

template <class T_>
T_ MinVec(std::vector<T_> Vec) { T_ Min = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }

int MaxVecAbs(std::vector<int> Vec) { int Max = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) > Max) Max = abs(Vec[n]); } return(Max); }
float MaxVecAbs(std::vector<float> Vec) { float Max = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }
double MaxVecAbs(std::vector<double> Vec) { double Max = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }

int MinVecAbs(std::vector<int> Vec) { int Min = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) < Min) Min = abs(Vec[n]); } return(Min); }
float MinVecAbs(std::vector<float> Vec) { float Min = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }
double MinVecAbs(std::vector<double> Vec) { double Min = Vec[0]; for (size_t n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }

// #######

// MAXIMUM AND MINUMUM VALUE INSIDE A VECTOR:
template <class T_>
void MaxMinVec(std::vector<T_> Vec, T_& Max, T_& Min)
{
	Max = Vec[0], Min = Vec[0]; size_t Size = Vec.size();
	for (size_t n = 1; n < Size; ++n)
	{
		if (Vec[n] > Max) Max = Vec[n];
		if (Vec[n] < Min) Min = Vec[n];
	}
}

// MAX AND MIN CAN'T BE LOWER THAN '0':
// * Abs is not only about abs(), it is a sum to the negative value
// ** Ex 1: sin(x) results in 'min = -1', but 'min' is '< 0', so:
//		    min += abs(min); max += abs(min) -> Result: min = 0; max = 2;
// ** Ex 2: f(x) results in 'min = 0.0001' and 'max = 1'. 'min > 0', so:
//			Result: min = 0.0001; max = 1;
// * If a number goes '< 0', you can normalize to '1' if you divide any index of input vector by 'max'
void MaxMinVecAbs(std::vector<int> Vec, int& Max, int& Min)
{
	int max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	if (max < 0) { max += abs(max); min += abs(max); }
	if (min < 0) { max += abs(min); min += abs(min); }
	Max = max; Min = min;
}
void MaxMinVecAbs(std::vector<double> Vec, double& Max, double& Min)
{
	double max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	if (max < 0) { max += fabs(max); min += fabs(max); }
	if (min < 0) { max += fabs(min); min += fabs(min); }
	Max = max; Min = min;
}
void MaxMinVecAbs(std::vector<float> Vec, float& Max, float& Min) // Soma com ABS, não ABS de apenas ABS.
{
	float max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	if (max < 0) { max += fabs(max); min += fabs(max); }
	if (min < 0) { max += fabs(min); min += fabs(min); }
	Max = max; Min = min;
}

// ####### ESPECIAIS:

// O minimo sempre vai ser zero, basicamente o delta entre o maximo e o minimo de um vector:
int MaxVecMin0(std::vector<int> Vec)
{
	int max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	int Absmx = 0, Absmn = 0;
	if (max < 0) { Absmx = abs(max); max += Absmx; min += Absmx; }
	if (min < 0) { Absmn = abs(min); max += Absmn; min += Absmn; }
	if (min > 0) { max -= min; }
	return(max);
}
float MaxVecMin0(std::vector<float> Vec)
{
	float max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	float Absmx = 0, Absmn = 0;
	if (max < 0) { Absmx = abs(max); max += Absmx; min += Absmx; }
	if (min < 0) { Absmn = abs(min); max += Absmn; min += Absmn; }
	if (min > 0) { max -= min; }
	return(max);
}
double MaxVecMin0(std::vector<double> Vec)
{
	double max = Vec[0], min = Vec[0];
	for (size_t n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	double Absmx = 0, Absmn = 0;
	if (max < 0) { Absmx = abs(max); max += Absmx; min += Absmx; }
	if (min < 0) { Absmn = abs(min); max += Absmn; min += Absmn; }
	if (min > 0) { max -= min; }
	return(max);
}

// Ponto y e x maximo do ponto:
void MaxMinVecPoint(std::vector<Point<int>>& VecPoint, Point<int>& Max, Point<int>& Min, bool Abs)
{
	Point<int> oMax(VecPoint[0]), oMin(VecPoint[0]);
	for (size_t n = 1; n < VecPoint.size(); ++n)
	{
		if (VecPoint[n].x > oMax.x) oMax.x = VecPoint[n].x; else if (VecPoint[n].x < oMin.x) oMin.x = VecPoint[n].x;
		if (VecPoint[n].y > oMax.y) oMax.y = VecPoint[n].y; else if (VecPoint[n].y < oMin.y) oMin.y = VecPoint[n].y;
	}
	if (Abs) // Construção
	{
		int absx, absy;
		bool absxb = false, absyb = false;
		if (Abs)
		{
			if (oMin.x < 0) { absx = abs(oMin.x); oMax.x += absx; oMin.x = 0; absxb = true; }
			if (oMin.y < 0) { absy = abs(oMin.y); oMax.y += absy; oMin.y = 0; absyb = true; }
		}
		if (absxb || absyb)
		{
			for (size_t n = 0; n < VecPoint.size(); ++n)
			{
				if (absxb) { VecPoint[n].x += absx; }
				if (absyb) { VecPoint[n].y += absy; }
			}
		}
	}
	Max = oMax; Min = oMin;
}

// O mesmo que acima, ma para linha:
void MaxMinVecLinePoint(std::vector<LinePoint<int>>& VecLinePoint, LinePoint<int>& Max, LinePoint<int>& Min, bool Abs)
{
	LinePoint<int> oMax(VecLinePoint[0]), oMin(VecLinePoint[0]);
	for (size_t n = 1; n < VecLinePoint.size(); ++n)
	{
		if (VecLinePoint[n].P0.x > oMax.P0.x) oMax.P0.x = VecLinePoint[n].P0.x; else if (VecLinePoint[n].P0.x < oMin.P0.x) oMin.P0.x = VecLinePoint[n].P0.x;
		if (VecLinePoint[n].P0.y > oMax.P0.y) oMax.P0.y = VecLinePoint[n].P0.y; else if (VecLinePoint[n].P0.y < oMin.P0.y) oMin.P0.y = VecLinePoint[n].P0.y;
		if (VecLinePoint[n].P1.x > oMax.P1.x) oMax.P1.x = VecLinePoint[n].P1.x; else if (VecLinePoint[n].P1.x < oMin.P1.x) oMin.P1.x = VecLinePoint[n].P1.x;
		if (VecLinePoint[n].P1.y > oMax.P1.y) oMax.P1.y = VecLinePoint[n].P1.y; else if (VecLinePoint[n].P1.y < oMin.P1.y) oMin.P1.y = VecLinePoint[n].P1.y;
	}
	if (Abs) // Construção
	{
		int absx, absy;
		bool absxb0 = false, absyb0 = false, absxb1 = false, absyb1 = false;
		if (Abs)
		{
			if (oMin.P0.x < 0) { absx = abs(oMin.P0.x); oMax.P0.x += absx; oMin.P0.x = 0; absxb0 = true; }
			if (oMin.P0.y < 0) { absy = abs(oMin.P0.y); oMax.P0.y += absy; oMin.P0.y = 0; absyb0 = true; }
			if (oMin.P0.x < 0) { absx = abs(oMin.P0.x); oMax.P0.x += absx; oMin.P0.x = 0; absxb1 = true; }
			if (oMin.P0.y < 0) { absy = abs(oMin.P0.y); oMax.P0.y += absy; oMin.P0.y = 0; absyb1 = true; }
		}
		if (absxb0 || absyb0 || absxb1 || absyb1)
		{
			for (size_t n = 0; n < VecLinePoint.size(); ++n)
			{
				if (absxb0) { VecLinePoint[n].P0.x += absx; }
				if (absyb0) { VecLinePoint[n].P0.y += absy; }
				if (absxb1) { VecLinePoint[n].P1.x += absx; }
				if (absyb1) { VecLinePoint[n].P1.y += absy; }
			}
		}
	}
	Max = oMax; Min = oMin;
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MATEMATICAS
// ############################

// SUM DATA:
template <class T_>
T_ SumVec(std::vector<T_> Vec) { size_t Size = Vec.size(); T_ Sum = Vec[0]; for (size_t n = 1; n < Size; ++n) { Sum += Vec[n]; } return(Sum); }
// MULTIPLY DATA, ANY '0' RETURN IN '0':
template <class T_>
T_ MultVec(std::vector<T_> Vec) { size_t Size = Vec.size(); T_ Mult = Vec[0]; for (size_t n = 1; n < Size; ++n) { Mult *= Vec[n]; } return(Mult); }

// POWER VECTOR TERMS:
template <class T_>
std::vector<T_> PowVec(std::vector<T_> Vec, T_ Pow) { size_t Size = Vec.size(); std::vector<T_> V(Size); for (size_t n = 0; n < Size; ++n) { V[n] = pow(Vec[n], Pow); } return(V); }

// SUM / MULTIPLY TWO VECTORS VALUES:
template <class T_>
std::vector<T_> SumTwoVec(std::vector<T_> Vec0, std::vector<T_> Vec1)
{
	std::vector<T_> V; bool v0v1 = false;
	size_t Size = 0;
	if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }	else { Size = Vec1.size(); v0v1 = true; }
	for (size_t n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (size_t n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (size_t n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
template <class T_>
std::vector<T_> MultiTwoVec(std::vector<T_> Vec0, std::vector<T_> Vec1)
{
	std::vector<T_> V; bool v0v1 = false;
	size_t Size = 0;
	if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }	else { Size = Vec1.size(); v0v1 = true; }
	for (size_t n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (size_t n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (size_t n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// GET A EXPONENT MARGIN:
template <class T_> std::vector<T_> PowerOfn(double n, int From, int To) { std::vector<T_> Vec; for (size_t a = From; a <= To; ++a) { Vec.push_back(pow(n, a)); } return(Vec); }
template <class T_> std::vector<T_> PowerByn(double n, int From, int To) { std::vector<T_> Vec; for (size_t a = From; a <= To; ++a) { Vec.push_back(pow(a, n)); } return(Vec); }
template <class T_> std::vector<T_> nRootOfm(double n, int m1, int m2) { std::vector<T_> Vec; for (size_t m = m1; m <= m2; ++m) { Vec.push_back(pow(m, 1.0 / n)); }	return(Vec); }
template <class T_> std::vector<T_> mRootOfn(double n, int m1, int m2) { std::vector<T_> Vec; for (size_t m = m1; m <= m2; ++m) { Vec.push_back(pow(n, 1.0 / m)); } return(Vec); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SELF
// ############################

// ####### OBJETOS #######

// CHECKERED BLOCK:
template <class T_> std::vector<T_> CheckeredBlock(uint32_t Size, double a, double b)
{ std::vector<double> R(Size); for (size_t n = 0; n < Size; ++n) { if (!(n % 2)) { R[n] = a; } else { R[n] = b; } } return(R); }

// ####### ARI. E GEO. #######

// SUM / MULT. TERMS:
template <class T_> void SumVecTerms(std::vector<T_>& Vec, T_ Sum) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
template <class T_> void MultVecTerms(std::vector<T_>& Vec, T_ Mult) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Avoid zeros

// SEQ. & SERIES:
template <class T_> void SumVecTermsArith(std::vector<T_>& Vec, T_ Sum, double Diff) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } } // Da para fazer linhas com isso
template <class T_> void MultVecTermsArith(std::vector<T_>& Vec, T_ Mult, double Diff) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } } // Avoid zeros
template <class T_> void SumVecTermsGeo(std::vector<T_>& Vec, T_ Sum, double Ratio) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * pow(Ratio, n); } }
template <class T_> void MultVecTermsGeo(std::vector<T_>& Vec, T_ Mult, double Ratio) { for (size_t n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * pow(Ratio, n); } } // Procure não ter zeros

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_