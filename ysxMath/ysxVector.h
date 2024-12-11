#pragma once

#ifndef YSXVECTOR_H
#define YSXVECTOR_H

/*############################################################################################################################################
  ################################################# ANOTATIONS AND ALTERATIONS #################################################

CHANGES (KEEP ORDER):
* Function 'ExpSignalVec' is now 'ExponentVec'. I don't remember why it was 'Signal';
* Functions of trigonometric vectors and signals are now on 'ysxElectr.h' and 'ysxSignal.h';
* Older versions don't use template, you may fix if your code used the older version.
* 'SumVecIndex' and any function '-VecIndex' were removed, because the older version was dumb, they are easy to code by hand and in function would not be optmal;
* Trying to work out 'for' loops which call '.size()' in every loop to one that calls 'size_t Size = .size()'. Also use a variable instead of calling functions W.I.P;
* 'Sort' and 'Search' functions are now o 'ysxDoc.h', which in fact was made with a place intended for it, but i forgot;

  ################################################# ANOTATIONS AND ALTERATIONS #################################################
  ############################################################################################################################################*/

// ############################
// ####### TECHNICAL
// ############################

// CONVERTERS:
template <class _T1, class _T2>
std::vector<float> ysxVEC_Convert(std::vector<_T1> T1) { std::vector<_T2> V(T1.size()); for (size_t n = 0; n < T1.size(); ++n) { V[n] = T1[n]; } return(V); }
std::vector<uint8_t> ysxVEC_Double2uChar(std::vector<double> Double)
{ std::vector<uint8_t> V(Double.size()); for (size_t n = 0; n < Double.size(); ++n) { V[n] = round(Double[n] * 255); } return(V); }
std::vector<uint8_t> ysxVEC_Float2uChar(std::vector<float> Float)
{ std::vector<uint8_t> V(Float.size()); for (size_t n = 0; n < Float.size(); ++n) { V[n] = round(Float[n] * 255); } return(V); }
std::vector<double> ysxVEC_String2double(std::string S)
{ std::vector<double> V(S.size()); for (size_t n = 0; n < S.size(); ++n) { V[n] = S[n] / 255.0; } return(V); }
// Use values from '0' to '1.0', it multiplies by '255.0'
std::string ysxVEC_Double2String(std::vector<double> Double)
{ std::string V; for (size_t n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255.0)); } return(V); }
std::string ysxVEC_Float2String(std::vector<double> Float)
{ std::string V; for (size_t n = 0; n < Float.size(); ++n) { V.push_back(round(Float[n] * 255.0)); } return(V); }
std::vector<float> ysxVEC_String2Float(std::string S)
{ std::vector<float> V(S.size()); for (size_t n = 0; n < S.size(); ++n) { V[n] = S[n] / 255.0; } return(V); }
// (Int[n] / 4294967295) * 255 = Int[n] / 16843099:
std::string ysxVEC_UI322String(std::vector<uint32_t> Int)
{ std::string V; for (size_t n = 0; n < Int.size(); ++n) { V.push_back(round(Int[n] / 16843099.0)); } return(V); }
// (Int[n] / 65535) * 255 = Int[n] / 257:
std::string ysxVEC_UI162String(std::vector<uint16_t> Int)
{ std::string V; for (size_t n = 0; n < Int.size(); ++n) { V.push_back(round(Int[n] / 257.0)); } return(V); }

// JOIN VECTORS:
// At the end of VPre, it will be pushed back VSuf
template <class T_>
std::vector<T_> ysxVEC_JoinVecs(std::vector<T_> VPre, std::vector<T_> VSuf) { for (size_t n = 0; n < VSuf.size(); ++n) { VPre.push_back(VSuf[n]); } return(VPre); }

// MERGE VECTORS:
template <class T_>
std::vector<T_> ysxVEC_MergeVecs(std::vector<T_> a, std::vector<T_> b)
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
std::vector<std::vector<double>> ysxVEC_VecSubBlocks(std::vector<double> In, uint32_t Div)
{
	std::vector<double> v;
	std::vector<std::vector<double>> V;
	uint32_t Fraction = In.size() / Div;
	uint32_t Mod;
	size_t Size = In.size();

	for (size_t n = 0; n < Size; ++n)
	{
		v.push_back(In[n]);
		Mod = n % Fraction;
		if (Mod == Fraction - 1) { V.push_back(v); v = std::vector<double>::vector(); }
		else if (n == Size - 1) { V.push_back(v); }
	}
	return(V);
}

// ############################
// ####### OPERATIONS WITH ZEROS
// ############################

// IF VALUE IN 'V0[n]' IS EQUAL TO '0', IT WILL CHANGE TO THE VALUE IN 'V1[n]', EVEN IF THAT IS ANOTHER '0':
template <class T_>
std::vector<T_> ysxVEC_SubstituteZero(std::vector<T_> V0, std::vector<T_> V1)
{
	std::vector<T_> V; bool v0v1 = false;
	uint32_t Size = 0;
	if (V0.size() <= V1.size()) { Size = V0.size(); } else { Size = V1.size(); v0v1 = true; }
	for (size_t n = 0; n < Size; ++n) { if (V0[n] != 0) { V.push_back(V0[n]); } else { V.push_back(V1[n]); } }
	if (!v0v1) { if (V1.size() - Size > 0) { for (size_t n = Size; n < V1.size(); ++n) { V.push_back(V1[n]); } } }
	else { if (V0.size() - Size > 0) { for (size_t n = Size; n < V0.size(); ++n) { V.push_back(V0[n]); } } }
	return(V);
}

// INSERT ZEROS IN RANDOM POSITIONS INTO A VECTOR:
template <class T_>
std::vector<T_> ysxVEC_InsertRandomZeros(std::vector<T_> Vec, size_t Zeros)
{
	if (Zeros < 1) { Zeros = 1; }
	std::vector<T_> V; size_t Size = Vec.size();
	uint32_t Rand;
	for (size_t Z = 0; Z < Zeros; ++Z)
	{
		std::vector<T_> v;
		Rand = rand() % Size;
		for (size_t n = 0; n < Size; ++n)
		{
			v.push_back(Vec[n]); if (n == Rand) { v.push_back(0); }
		}
		Vec = v;
		V = v;
	}
	return (V);
}

// INSERT ZEROS AT THE BEGINNING OR THE END OF A VECTOR:
template <class T_>
std::vector<T_> ysxVEC_InsertZerosBeginorEnd(std::vector<T_> Vec, size_t Zeros, bool BeginEnd = false)
{
	std::vector<T_> V; size_t Size = Vec.size();
	if (!BeginEnd) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	for (size_t n = 0; n < Size; ++n) { V.push_back(Vec[n]); }
	if (BeginEnd) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	return (V);
}

// INSERT ZEROS BETWEEN EACH TERM:
template <class T_>
std::vector<T_> ysxVEC_InsertZerosBetweenTerms(std::vector<T_> Vec, size_t Zeros, bool BeforeAfter = false, bool BeforeAndAfter = false)
{
	std::vector<T_> V; size_t Size = Vec.size();
	for (size_t n = 0; n < Size; ++n)
	{
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vec[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}
template <class T_>
std::vector<T_> ysxVEC_InsertZerosBetweenTermsExpo(std::vector<T_> Vec, size_t Zeros, double InitialPower, bool BeforeAfter = false, bool BeforeAndAfter = false)
{
	std::vector<T_> V; size_t Size = Vec.size();
	double Zr;
	for (size_t n = 0; n < Size; ++n)
	{
		Zr = pow(Zeros, (n + InitialPower));
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (size_t Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
		V.push_back(Vec[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (size_t Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// INSERT ZEROS AT A INDEX:
template <class T_>
std::vector<T_> ysxVEC_InsertZerosatTerm(std::vector<T_> Vec, size_t Zeros, uint32_t at, bool BeforeAfter = false)
{
	std::vector<T_> V; size_t Size = Vec.size();
	for (size_t n = 0; n < Size; ++n)
	{
		if (!BeforeAfter && n == at) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vec[n]);
		if (BeforeAfter && n == at) { for (size_t Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// DELETE ZEROS:
template <class T_>
std::vector<T_> ysxVEC_DeleteZeros(std::vector<T_> Vec)
{
	std::vector<T_> V; size_t Size = Vec.size();
	for (size_t n = 0; n < Size; ++n) { if (Vec[n] != 0) { V.push_back(Vec[n]); } }
	return (V);
}

// ############################
// ####### OPERATIONS WITH NUMBERS
// ############################

// Insert copy of an indexed value at random positions into a vector:
template <class T_> std::vector<T_> ysxVEC_InsertRandomCopies(std::vector<T_> Vec, uint32_t Copies)
{
	if (Copies < 1) { Copies = 1; }
	std::vector<T_> V;
	for (size_t c = 0; c < Copies; ++c)
	{
		std::vector<T_> v;
		uint32_t Rand = rand() % Vec.size();
		for (size_t n = 0; n < Vec.size(); ++n)
		{
			v.push_back(Vec[n]); if (n == Rand) { v.push_back(Vec[n]); }
		}
		Vec = v;
		V = v;
	}
	return (V);
}

// if (Size > 0) { Dest[Index + n] = In[n]; }; Take cara between 'Dest' and 'In' size:
template <class T_> void ysxVEC_SubstituteVals(std::vector<T_>& Dest, const std::vector<T_>& In, uint32_t Index)
{
	int64_t Size = (Index + In.size()) > Dest.size() ? Dest.size() - Index : In.size();
	if (Size > 0) { for (size_t n = 0; n < Size; ++n) { Dest[Index + n] = In[n]; } }
}

// Dest[(Index + n) % DSize] = In[n];
template <class T_> void ysxVEC_SubstituteValsMod(std::vector<T_>& Dest, std::vector<T_> In, uint32_t Index)
{
	uint32_t Size = Dest.size();
	for (size_t n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MAX AND MINIMUM OF A VECTOR
// ############################

template <class T_>
T_ ysxVEC_MaxVec(std::vector<T_> V) { T_ Max = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (V[n] > Max) Max = V[n]; } return(Max); }

template <class T_>
T_ ysxVEC_MinVec(std::vector<T_> V) { T_ Min = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (V[n] < Min) Min = V[n]; } return(Min); }

int ysxVEC_MaxVecAbs(std::vector<int> V) { int Max = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (abs(V[n]) > Max) Max = abs(V[n]); } return(Max); }
float ysxVEC_MaxVecAbs(std::vector<float> V) { float Max = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (fabs(V[n]) > Max) Max = fabs(V[n]); } return(Max); }
double ysxVEC_MaxVecAbs(std::vector<double> V)
{ double Max = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (fabs(V[n]) > Max) Max = fabs(V[n]); } return(Max); }

int ysxVEC_MinVecAbs(std::vector<int> V) { int Min = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (abs(V[n]) < Min) Min = abs(V[n]); } return(Min); }
float ysxVEC_MinVecAbs(std::vector<float> V) { float Min = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (fabs(V[n]) < Min) Min = fabs(V[n]); } return(Min); }
double ysxVEC_MinVecAbs(std::vector<double> V)
{ double Min = V[0]; for (size_t n = 1; n < V.size(); ++n) { if (fabs(V[n]) < Min) Min = fabs(V[n]); } return(Min); }

// #######

// MAXIMUM AND MINUMUM VALUE INSIDE A VECTOR:
template <class T_>
void ysxVEC_MaxMinVec(std::vector<T_> V, T_& Max, T_& Min)
{
	Max = V[0], Min = V[0]; size_t Size = V.size();
	for (size_t n = 1; n < Size; ++n)
	{
		if (V[n] > Max) Max = V[n];
		if (V[n] < Min) Min = V[n];
	}
}

// MAX OR MIN CAN'T BE LOWER THAN '0':
// * Abs is not only about abs(), it is a sum to the negative value
// ** Ex 1: sin(x) results in 'min = -1', but 'min' is '< 0', so:
//		    max += abs(min); min += abs(min) -> Result: min = 0; max = 2;
// ** Ex 2: f(x) results in 'min = 0.0001' and 'max = 1'. 'min > 0', so:
//			Result: min = 0.0001; max = 1;
// * If a number goes '< 0', you can normalize to '1' if you divide any index of input vector by 'max'
void ysxVEC_MaxMinVecAbs(std::vector<int>& V, int& Max, int& Min)
{
	int max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	if (max < 0) { min += abs(max); max = 0; }
	if (min < 0) { max += abs(min); min = 0; }
	Max = max; Min = min;
}
void ysxVEC_MaxMinVecAbs(std::vector<double>& V, double& Max, double& Min)
{
	double max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	if (max < 0) { min += fabs(max); max = 0; }
	if (min < 0) { max += fabs(min); min = 0; }
	Max = max; Min = min;
}
void ysxVEC_MaxMinVecAbs(std::vector<float>& V, float& Max, float& Min)
{
	float max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	if (max < 0) { min += fabs(max); max = 0; }
	if (min < 0) { max += fabs(min); min = 0; }
	Max = max; Min = min;
}

// ####### SPECIAL:

// Delta between max and min. The minimum will always be at ZERO (that means if 'min > 0', then 'max -= min'):
int ysxVEC_VecDelta(std::vector<int> V)
{
	int max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	int Absmx = 0, Absmn = 0;
	if (max < 0) { min += abs(max); max = 0; }
	if (min < 0) { max += abs(min); min = 0; }
	if (min > 0) { max -= min; }//min = 0; }
	return(max);
}
float ysxVEC_VecDelta(std::vector<float> V)
{
	float max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	float Absmx = 0, Absmn = 0;
	if (max < 0) { min += fabs(max); max = 0; }
	if (min < 0) { max += fabs(min); min = 0; }
	if (min > 0) { max -= min; }
	return(max);
}
double ysxVEC_VecDelta(std::vector<double> V)
{
	double max = V[0], min = V[0];
	for (size_t n = 1; n < V.size(); ++n)
	{
		if (V[n] > max) max = V[n];
		if (V[n] < min) min = V[n];
	}
	double Absmx = 0, Absmn = 0;
	if (max < 0) { min += fabs(max); max = 0; }
	if (min < 0) { max += fabs(min); min = 0; }
	if (min > 0) { max -= min; }
	return(max);
}

// MAX OF BOTH 'y' AND 'x':
// 'bool Abs'modifies VPoint! For now, i'm going to modify this later, since it was a noobish from me to do that!
void ysxVEC_MaxMinVecPoint(std::vector<Point<int>>& VPoint, Point<int>& Max, Point<int>& Min, bool Abs)
{
	Point<int> oMax(VPoint[0]), oMin(VPoint[0]);
	for (size_t n = 1; n < VPoint.size(); ++n)
	{
		if (VPoint[n].x > oMax.x) oMax.x = VPoint[n].x; if (VPoint[n].x < oMin.x) oMin.x = VPoint[n].x;
		if (VPoint[n].y > oMax.y) oMax.y = VPoint[n].y; if (VPoint[n].y < oMin.y) oMin.y = VPoint[n].y;
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
			for (size_t n = 0; n < VPoint.size(); ++n)
			{
				if (absxb) { VPoint[n].x += absx; }
				if (absyb) { VPoint[n].y += absy; }
			}
		}
	}
	Max = oMax; Min = oMin;
}

// MAX OF 'x', 'y' AND 'z':
void ysxVEC_MaxMinVecPoint3D(std::vector<Point3D<int>>& VPoint, Point3D<int>& Max, Point3D<int>& Min, bool Abs)
{
	Point3D<int> oMax(VPoint[0]), oMin(VPoint[0]);
	for (size_t n = 1; n < VPoint.size(); ++n)
	{
		if (VPoint[n].x > oMax.x) oMax.x = VPoint[n].x; if (VPoint[n].x < oMin.x) oMin.x = VPoint[n].x;
		if (VPoint[n].y > oMax.y) oMax.y = VPoint[n].y; if (VPoint[n].y < oMin.y) oMin.y = VPoint[n].y;
		if (VPoint[n].z > oMax.z) oMax.z = VPoint[n].z; if (VPoint[n].z < oMin.z) oMin.z = VPoint[n].z;
	}
	if (Abs) // Construção
	{
		int absx, absy, absz;
		bool absxb = false, absyb = false, abszb = false;
		if (Abs)
		{
			if (oMin.x < 0) { absx = abs(oMin.x); oMax.x += absx; oMin.x = 0; absxb = true; }
			if (oMin.y < 0) { absy = abs(oMin.y); oMax.y += absy; oMin.y = 0; absyb = true; }
			if (oMin.z < 0) { absz = abs(oMin.z); oMax.z += absz; oMin.z = 0; abszb = true; }
		}
		if (absxb || absyb || abszb)
		{
			for (size_t n = 0; n < VPoint.size(); ++n)
			{
				if (absxb) { VPoint[n].x += absx; }
				if (absyb) { VPoint[n].y += absy; }
				if (abszb) { VPoint[n].z += absz; }
			}
		}
	}
	Max = oMax; Min = oMin;
}

// MAX COORD FROM A LINE STRUCT:
void ysxVEC_MaxMinVecLinePoint(std::vector<LinePoint<int>>& VLinePoint, LinePoint<int>& Max, LinePoint<int>& Min, bool Abs)
{
	LinePoint<int> oMax(VLinePoint[0]), oMin(VLinePoint[0]);
	for (size_t n = 1; n < VLinePoint.size(); ++n)
	{
		if (VLinePoint[n].P0.x > oMax.P0.x) oMax.P0.x = VLinePoint[n].P0.x; else if (VLinePoint[n].P0.x < oMin.P0.x) oMin.P0.x = VLinePoint[n].P0.x;
		if (VLinePoint[n].P0.y > oMax.P0.y) oMax.P0.y = VLinePoint[n].P0.y; else if (VLinePoint[n].P0.y < oMin.P0.y) oMin.P0.y = VLinePoint[n].P0.y;
		if (VLinePoint[n].P1.x > oMax.P1.x) oMax.P1.x = VLinePoint[n].P1.x; else if (VLinePoint[n].P1.x < oMin.P1.x) oMin.P1.x = VLinePoint[n].P1.x;
		if (VLinePoint[n].P1.y > oMax.P1.y) oMax.P1.y = VLinePoint[n].P1.y; else if (VLinePoint[n].P1.y < oMin.P1.y) oMin.P1.y = VLinePoint[n].P1.y;
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
			for (size_t n = 0; n < VLinePoint.size(); ++n)
			{
				if (absxb0) { VLinePoint[n].P0.x += absx; }
				if (absyb0) { VLinePoint[n].P0.y += absy; }
				if (absxb1) { VLinePoint[n].P1.x += absx; }
				if (absyb1) { VLinePoint[n].P1.y += absy; }
			}
		}
	}
	Max = oMax; Min = oMin;
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MATHEMATICS
// ############################

// SUM DATA:
template <class T_>
T_ ysxVEC_SumVec(std::vector<T_> V) { size_t Size = V.size(); T_ Sum = V[0]; for (size_t n = 1; n < Size; ++n) { Sum += V[n]; } return(Sum); }
// MULTIPLY DATA, ANY '0' RETURN IN '0':
template <class T_>
T_ ysxVEC_MultVec(std::vector<T_> V) { size_t Size = V.size(); T_ Mult = V[0]; for (size_t n = 1; n < Size; ++n) { Mult *= V[n]; } return(Mult); }

// POWER VECTOR TERMS:
template <class T_>
std::vector<T_> ysxVEC_PowVec(std::vector<T_> V, T_ Pow)
{ size_t Size = V.size(); std::vector<T_> R(Size); for (size_t n = 0; n < Size; ++n) { R[n] = pow(V[n], Pow); } return(R); }

// N-ROOT VECTOR TERMS:
template <class T_>
std::vector<T_> ysxVEC_nRootVec(std::vector<T_> V, T_ nRoot)
{ size_t Size = V.size(); std::vector<T_> R(Size); for (size_t n = 0; n < Size; ++n) { R[n] = pow(V[n], 1 / nRoot); } return(R); }

// SUM / MULTIPLY TWO VECTORS VALUES:
template <class T_>
std::vector<T_> ysxVEC_SumTwoVec(std::vector<T_>& V0, std::vector<T_>& V1)
{
	bool v0v1 = false;
	std::vector<T_> V;
	V0.size() < V1.size() ? v0v1 = true : v0v1 = false;
	v0v1 ? V = V0 : V = V1;
	size_t Size = V.size();
	for (size_t n = 0; n < Size; ++n) { V[n] = V0[n] + V1[n]; }
	if (v0v1) { for (size_t n = Size; n < V1.size(); ++n) { V.push_back(V1[n]); } }
	else { if (V0.size() - Size > 0) { for (size_t n = Size; n < V0.size(); ++n) { V.push_back(V0[n]); } } }
	return(V);
}
template <class T_>
std::vector<T_> ysxVEC_MultiTwoVec(std::vector<T_>& V0, std::vector<T_>& V1)
{
	bool v0v1 = false;
	std::vector<T_> V;
	V0.size() < V1.size() ? v0v1 = true : v0v1 = false;
	v0v1 ? V = V0 : V = V1;
	size_t Size = V.size();
	if (V0.size() <= V1.size()) { Size = V0.size(); }	else { Size = V1.size(); v0v1 = true; }
	for (size_t n = 0; n < Size; ++n) { V[n] = V0[n] * V1[n]; }
	if (v0v1) { for (size_t n = Size; n < V1.size(); ++n) { V.push_back(V1[n]); } }
	else { if (V0.size() - Size > 0) { for (size_t n = Size; n < V0.size(); ++n) { V.push_back(V0[n]); } } }
	return(V);
}

// GET A EXPONENT MARGIN:
template <class T_> std::vector<T_> ysxVEC_PowerOfn(double n, int m1, int m2)
{ std::vector<T_> V(m2 - m1); for (size_t m = m1; m <= m2; ++m) { V[m - m1] = pow(n, m); } return(V); }
template <class T_> std::vector<T_> ysxVEC_PowerByn(double n, int m1, int m2)
{ std::vector<T_> V(m2 - m1); for (size_t m = m1; m <= m2; ++m) { V[m - m1] = pow(m, n); } return(V); }
template <class T_> std::vector<T_> ysxVEC_nRootOfm(double n, int m1, int m2)
{ std::vector<T_> V(m2 - m1); for (size_t m = m1; m <= m2; ++m) { V[m - m1] = pow(m, 1.0 / n); }	return(V); }
template <class T_> std::vector<T_> ysxVEC_mRootOfn(double n, int m1, int m2)
{ std::vector<T_> V(m2 - m1); for (size_t m = m1; m <= m2; ++m) { V[n - m1] = pow(n, 1.0 / m); } return(V); }

// CREATE VECTOR THAT IS DERIVATIVE OF ANOTHER VECTOR:
std::vector<double> ysxVEC_VecDeriv(std::vector<double> VecData, double dt)
{
	std::vector<double> Derivs(VecData.size()); for (size_t n = 1; n < VecData.size(); ++n) { Derivs[n] = ((VecData[n] - VecData[n - 1]) / dt); } return(Derivs);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SELF
// ############################

// ####### OBJETOS #######

// CHECKERED BLOCK:
template <class T_> std::vector<T_> ysxVEC_CheckeredBlock(uint32_t Size, double a, double b)
{ std::vector<double> R(Size); for (size_t n = 0; n < Size; ++n) { if (!(n % 2)) { R[n] = a; } else { R[n] = b; } } return(R); }

// ####### ARI. E GEO. #######

// SUM / MULT. TERMS:
template <class T_> void ysxVEC_SumVecTerms(std::vector<T_>& V, T_ Sum) { for (size_t n = 0; n < V.size(); ++n) { V[n] += Sum; } }
template <class T_> void ysxVEC_MultVecTerms(std::vector<T_>& V, T_ Mult) { for (size_t n = 0; n < V.size(); ++n) { V[n] *= Mult; } } // Avoid zeros

// SEQ. & SERIES:
template <class T_> void ysxVEC_SumVecTermsArith(std::vector<T_>& V, T_ Sum, double Diff)
{ for (size_t n = 0; n < V.size(); ++n) { V[n] += Sum + (n * Diff); } } // You can make lines with that
template <class T_> void ysxVEC_MultVecTermsArith(std::vector<T_>& V, T_ Mult, double Diff)
{ for (size_t n = 0; n < V.size(); ++n) { V[n] *= Mult + (n * Diff); } } // Avoid zeros
template <class T_> void ysxVEC_SumVecTermsGeo(std::vector<T_>& V, T_ Sum, double Ratio)
{ for (size_t n = 0; n < V.size(); ++n) { V[n] += Sum * pow(Ratio, n); } }
template <class T_> void ysxVEC_MultVecTermsGeo(std::vector<T_>& V, T_ Mult, double Ratio)
{ for (size_t n = 0; n < V.size(); ++n) { V[n] *= Mult * pow(Ratio, n); } } // Avoid zeros

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
