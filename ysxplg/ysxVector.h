#pragma once

#ifndef YSXVECTOR_H
#define YSXVECTOR_H

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* FUNÇÃO 'ExpSignalVec' AGORA É 'ExponentVec'. E EU NÃO LEMBRO O PORQUE ERA 'Signal';
// !!!!!!!	* Funões de vetores trigonométricos e sinais agora está em 'ysxElectr.h'
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################
// ####### TÉCNICOS
// ############################

// CONVERSORES:
std::vector<float> SInt2Float(std::vector<short int> SInt) { std::vector<float> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<double> SInt2double(std::vector<short int> SInt) { std::vector<double> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<float> Int2Float(std::vector<int> Int) { std::vector<float> V; for (int n = 0; n < Int.size(); ++n) { V.push_back(Int[n]); } return(V); }
std::vector<int> Float2Int(std::vector<float> Float) { std::vector<int> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<int> SInt2Int(std::vector<short int> SInt) { std::vector<int> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
std::vector<double> Float2Double(std::vector<float> Float) { std::vector<double> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<float> Double2Float(std::vector<double> Double) { std::vector<float> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
std::vector<short int> Double2SInt(std::vector<double> Double) { std::vector<short int> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
std::vector<short int> Float2SInt(std::vector<float> Float) { std::vector<short int> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
std::vector<unsigned char> Double2uChar(std::vector<double> Double) { std::vector<unsigned char> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255)); } return(V); }
std::vector<char> Double2Char(std::vector<double> Double) { std::vector<char> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 127)); } return(V); }
std::vector<unsigned char> Float2uChar(std::vector<float> Float) { std::vector<unsigned char> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(round(Float[n] * 255)); } return(V); }
std::vector<char> Float2Char(std::vector<float> Float) { std::vector<char> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(round(Float[n] * 127)); } return(V); }
std::vector<double> String2double(std::string S) { std::vector<double> V; for (int n = 0; n < S.size(); ++n) { V.push_back((int)S[n] / 255.0); } return(V); }
// Use values from '0' to '1.0', it multiplies by '255.0'
std::string Double2String(std::vector<double> Double) { std::string V; for (int n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255.0)); } return(V); }
std::vector<double> String2Int(std::string S) { std::vector<double> V; for (int n = 0; n < S.size(); ++n) { V.push_back((int)S[n] / 255.0); } return(V); }
std::string Int2String(std::vector<double> Double) { std::string V; for (int n = 0; n < Double.size(); ++n) { V.push_back(round(Double[n] * 255.0)); } return(V); }

// UNE VETORES:
std::vector<int> JoinVectors(std::vector<int> VecPre, std::vector<int> VecSuf) { for (int n = 0; n < VecSuf.size(); ++n) { VecPre.push_back(VecSuf[n]); } return(VecPre); }
std::vector<float> JoinVectors(std::vector<float> VecPre, std::vector<float> VecSuf) { std::vector<float> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
std::vector<double> JoinVectors(std::vector<double> VecPre, std::vector<double> VecSuf)
{ std::vector<double> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
std::vector<char> JoinVectors(std::vector<char> VecPre, std::vector<char> VecSuf) { std::vector<char> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
std::vector<std::string> JoinVectors(std::vector<std::string> VecPre, std::vector<std::string> VecSuf)
{ std::vector<std::string> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
std::vector<bool> JoinVectors(std::vector<bool> VecPre, std::vector<bool> VecSuf) { std::vector<bool> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }

// POR INDICES:
std::vector<double> SumVecIndex(std::vector<double> V, int Index0, int Index1, bool Average)
{
	std::vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { if (Average) { Vec.push_back((V[n] + V[Last]) * 0.5); } else { Vec.push_back(V[n] + V[Last]); } } }
	return(Vec);
}
std::vector<double> SubVecIndex(std::vector<double> V, int Index0, int Index1)
{
	std::vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { Vec.push_back(V[n] - V[Last]); } }
	return(Vec);
}
std::vector<double> MultVecIndex(std::vector<double> V, int Index0, int Index1, bool Sqrt)
{
	std::vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { if (Sqrt) { Vec.push_back(sqrt(V[n] * V[Last])); } else { Vec.push_back(V[n] * V[Last]); } } }
	return(Vec);
}
std::vector<double> DivVecIndex(std::vector<double> V, int Index0, int Index1)
{
	std::vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { Vec.push_back(V[n] / V[Last]); } }
	return(Vec);
}

// CHANGE VALUE IN INDEX AND DELETE THE VALUE THAT GOT IN:
std::vector<double> SubstituteVecIndex(std::vector<double> V, int TargetIndex, int SubIndex)
{
	std::vector<double> Vec;
	if (TargetIndex < 0) { TargetIndex = 0; } if (SubIndex < 0) { SubIndex = 0; } if (TargetIndex >= V.size() - 1) { TargetIndex = V.size() - 1; } if (SubIndex >= V.size() - 1) { SubIndex = V.size() - 1; }
	if (TargetIndex == SubIndex)
	{
		if (TargetIndex > 0 && TargetIndex - 1 != SubIndex) { --TargetIndex; } else if (SubIndex > 0 && SubIndex - 1 != TargetIndex) { --SubIndex; }
		else if (TargetIndex + 1 != V.size() && TargetIndex + 1 != SubIndex) { ++TargetIndex; } else if (SubIndex + 1 != V.size() && SubIndex + 1 != SubIndex) { ++SubIndex; }
		else { TargetIndex = 0; SubIndex = 1; }
	}
	for (int n = 0; n < V.size(); ++n) { if (n != TargetIndex) { if (n != SubIndex) { Vec.push_back(V[n]); } } else { Vec.push_back(V[SubIndex]); } }
	return(Vec);
}

// CHANGE VALUE OF ONE INDEX TO ANOTHER, AND THE VALUE OF THIS ANOTHER TO THE INDEX ONE:
std::vector<double> ReplaceeVecIndex(std::vector<double> V, int TargetIndex, int SubIndex)
{
	std::vector<double> Vec;
	if (TargetIndex < 0) { TargetIndex = 0; } if (SubIndex < 0) { SubIndex = 0; } if (TargetIndex >= V.size() - 1) { TargetIndex = V.size() - 1; } if (SubIndex >= V.size() - 1) { SubIndex = V.size() - 1; }
	if (TargetIndex == SubIndex)
	{
		if (TargetIndex > 0 && TargetIndex - 1 != SubIndex) { --TargetIndex; } else if (SubIndex > 0 && SubIndex - 1 != TargetIndex) { --SubIndex; }
		else if (TargetIndex + 1 != V.size() && TargetIndex + 1 != SubIndex) { ++TargetIndex; } else if (SubIndex + 1 != V.size() && SubIndex + 1 != SubIndex) { ++SubIndex; }
		else { TargetIndex = 0; SubIndex = 1; }
	}
	for (int n = 0; n < V.size(); ++n) { if (n != TargetIndex) { if (n != SubIndex) { Vec.push_back(V[n]); } else { Vec.push_back(V[TargetIndex]); } } else { Vec.push_back(V[SubIndex]); } }
	return(Vec);
}

// BREAK VECTOR INTO SUB-BLOCK:
std::vector<std::vector<double>> VectorSubBlocks(std::vector<double> In, int Div)
{
	std::vector<double> v;
	std::vector<std::vector<double>> V;
	int Fraction = In.size() / Div;

	for (int n = 0; n < In.size(); ++n)
	{
		v.push_back(In[n]);
		int Mod = n % Fraction;
		if (Mod == Fraction - 1) { V.push_back(v); v = std::vector<double>::vector(); }
		else if (n == In.size() - 1) { V.push_back(v); }
	}

	return(V);
}

// ############################
// ####### OPERAÇÕES COM ZEROS
// ############################

// Se o segundo vetor tiver um numero no mesmo indice que o primeiro vetor tem um zero, ele substitui o zero pelo valor do indice:
std::vector<int> SubstituteZero(std::vector<int> Vec0, std::vector<int> Vec1)
{
	std::vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<float> SubstituteZero(std::vector<float> Vec0, std::vector<float> Vec1)
{
	std::vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<double> SubstituteZero(std::vector<double> Vec0, std::vector<double> Vec1)
{
	std::vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// Insert zeros in random positions into a vector:
std::vector<double> InsertRandomZeros(std::vector<double> Vector, int Zeros)
{
	if (Zeros < 1) { Zeros = 1; }
	std::vector<double> V;
	for (int Z = 0; Z < Zeros; ++Z)
	{
		std::vector<double> v;
		int Rand = rand() % Vector.size();
		for (int n = 0; n < Vector.size(); ++n)
		{
			v.push_back(Vector[n]); if (n == Rand) { v.push_back(0); }
		}
		Vector = v;
		V = v;
	}
	return (V);
}

// Insert zeros at beginning or the end of a vector:
std::vector<double> InsertZerosBeginorEnd(std::vector<double> Vector, int Zeros, bool BeginEnd)
{
	std::vector<double> V;
	if (!BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	for (int n = 0; n < Vector.size(); ++n) { V.push_back(Vector[n]); }
	if (BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	return (V);
}

// Insert zeros between each term:
std::vector<double> InsertZerosBetweenTerms(std::vector<double> Vector, int Zeros, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<double > V;
	for (int n = 0; n < Vector.size(); ++n)
	{
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}
std::vector<double> InsertZerosBetweenTermsExpo(std::vector<double> Vector, int Zeros, double InitialPower, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<double> V;
	for (int n = 0; n < Vector.size(); ++n)
	{
		double Zr = pow(Zeros, (n + InitialPower));
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (int Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (int Z = 0; Z < Zr; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// Insert zeros at a term:
std::vector<double> InsertZerosatTerm(std::vector<double> Vector, int Zeros, int at, bool BeforeAfter)
{
	std::vector<double> V;
	for (int n = 0; n < Vector.size(); ++n)
	{
		if (!BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// Delete zeros:
std::vector<double> DeleteZeros(std::vector<double> Vector)
{
	std::vector<double> V;
	for (int n = 0; n < Vector.size(); ++n) { if (Vector[n] != 0) { V.push_back(Vector[n]); } }
	return (V);
}

// ############################
// ####### OPERAÇÕES COM NUMEROS
// ############################

// Insert copy of an indexed value at random positions into a vector:
std::vector<double> InsertRandomCopies(std::vector<double> Vector, int Copies)
{
	if (Copies < 1) { Copies = 1; }
	std::vector<double> V;
	for (int c = 0; c < Copies; ++c)
	{
		std::vector<double> v;
		int Rand = rand() % Vector.size();
		for (int n = 0; n < Vector.size(); ++n)
		{
			v.push_back(Vector[n]); if (n == Rand) { v.push_back(Vector[n]); }
		}
		Vector = v;
		V = v;
	}
	return (V);
}

// SUBSTITUTE VALUE (IF BIGGER THAN SIZE, THEN MODULO):
// Dest[(Index + n) % DSize] = In[n];
void SubstituteVals(std::vector<double>& Dest, std::vector<double> In, unsigned int Index)
{
	unsigned int Size = Dest.size();
	for (int n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n];	}
}
void SubstituteVals(std::vector<float>& Dest, std::vector<float> In, unsigned int Index)
{
	unsigned int Size = Dest.size();
	for (int n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}
void SubstituteVals(std::vector<unsigned char>& Dest, std::vector<unsigned char> In, unsigned int Index)
{
	unsigned int Size = Dest.size();
	for (int n = 0; n < In.size(); ++n) { Dest[(Index + n) % Size] = In[n]; }
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SORTS
// ############################

// QUICKSORT:
void QuickSort(std::vector<int>& V, int l, int r)
{
	if (l >= r) { return; } int pivot = V[r]; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { std::swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSort(std::vector<double>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r]; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { std::swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSortPtx(std::vector<PointFlt>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r].x; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i].x <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPtx(V, l, cnt - 2); QuickSortPtx(V, cnt, r);
}
void QuickSortPty(std::vector<PointFlt>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r].y; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i].y <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPty(V, l, cnt - 2); QuickSortPty(V, cnt, r);
}

// BUBBLE SORT:
void BubbleSort(std::vector<int>& V)
{
	unsigned int N = V.size();
	for (unsigned int i = 0; i < N; ++i)
	{
		int p = 0; while (p < N - 1 - i) { if (V[p] > V[p + 1]) { int t = V[p]; V[p] = V[p + 1]; V[p + 1] = t; } ++p; }
	}
}
void BubbleSort(std::vector<double>& V)
{
	unsigned int N = V.size();
	for (unsigned int i = 0; i < N; ++i)
	{
		int p = 0; while (p < N - 1 - i) { if (V[p] > V[p + 1]) { double t = V[p]; V[p] = V[p + 1]; V[p + 1] = t; } ++p; }
	}
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MAX AND MINIMUM OF A VECTOR
// ############################

int MaxVec(std::vector<int> Vec) { int Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }
float MaxVec(std::vector<float> Vec) { float Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }
double MaxVec(std::vector<double> Vec) { double Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }

int MinVec(std::vector<int> Vec) { int Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }
float MinVec(std::vector<float> Vec) { float Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }
double MinVec(std::vector<double> Vec) { double Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }

int MaxVecAbs(std::vector<int> Vec) { int Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) > Max) Max = abs(Vec[n]); } return(Max); }
float MaxVecAbs(std::vector<float> Vec) { float Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }
double MaxVecAbs(std::vector<double> Vec) { double Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }

int MinVecAbs(std::vector<int> Vec) { int Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) < Min) Min = abs(Vec[n]); } return(Min); }
float MinVecAbs(std::vector<float> Vec) { float Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }
double MinVecAbs(std::vector<double> Vec) { double Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }

// #######

void MaxMinVec(std::vector<int> Vec, int& Max, int& Min)
{
	int max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	Max = max; Min = min;
}
void MaxMinVec(std::vector<double> Vec, double& Max, double& Min)
{
	double max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}

	Max = max; Min = min;
}
void MaxMinVec(std::vector<float> Vec, float& Max, float& Min)
{
	float max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}

	Max = max; Min = min;
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
	for (int n = 1; n < Vec.size(); ++n)
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
	for (int n = 1; n < Vec.size(); ++n)
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
	for (int n = 1; n < Vec.size(); ++n)
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
float MaxVecMin0(std::vector<float> Vec)
{
	float max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
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
	for (int n = 1; n < Vec.size(); ++n)
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

// CellBool carrega numeros para o indice:
void MaxSizeBoolMatrix(std::vector<CellBool> Vec, int& Maxi, int& Maxj)
{
	int maxi = Vec[0].i, maxj = Vec[0].j;
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n].i > maxi) maxi = Vec[n].i;
		if (Vec[n].j > maxj) maxj = Vec[n].j;
	}
	Maxi = maxi; Maxj = maxj;
}

// Ponto y e x maximo do ponto:
void MaxMinVecPoint(std::vector<Point>& VecPoint, Point& Max, Point& Min, bool Abs)
{
	Point oMax(VecPoint[0]), oMin(VecPoint[0]);
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
void MaxMinVecLinePoint(std::vector<LinePoint>& VecLinePoint, LinePoint& Max, LinePoint& Min, bool Abs)
{
	LinePoint oMax(VecLinePoint[0]), oMin(VecLinePoint[0]);
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

// SOMA/MULTIPLICA DADOS:
int SumVec(std::vector<int> Vec) { int Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
double SumVec(std::vector<double> Vec) { double Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
int MultVec(std::vector<int> Vec) { int Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); } // Procure não ter zeros
double MultVec(std::vector<double> Vec) { double Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); }

// POWER VECTOR TERMS:
std::vector<int> PowVec(std::vector<int> Vec, int Pow) { std::vector<int> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }
std::vector<double> PowVec(std::vector<double> Vec, double Pow) { std::vector<double> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }

// Two vectors and vector return:
std::vector<int> SumTwoVec(std::vector<int> Vec0, std::vector<int> Vec1)
{
	std::vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<float> SumTwoVec(std::vector<float> Vec0, std::vector<float> Vec1)
{
	std::vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<double> SumTwoVec(std::vector<double> Vec0, std::vector<double> Vec1)
{
	std::vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<int> MultiTwoVec(std::vector<int> Vec0, std::vector<int> Vec1)
{
	std::vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<float> MultiTwoVec(std::vector<float> Vec0, std::vector<float> Vec1)
{
	std::vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
std::vector<double> MultiTwoVec(std::vector<double> Vec0, std::vector<double> Vec1)
{
	std::vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// PEGA MARGEM DE EXPONENTE:
std::vector<long> PowerOfn(double n, int From, int To) { std::vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(n, a)); } return(Vec); }
std::vector<long> PowerByn(double n, int From, int To) { std::vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(a, n)); } return(Vec); }
std::vector<double> nRootOfm(double n, int m1, int m2) { std::vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(m, 1.0 / n)); }	return(Vec); }
std::vector<double> mRootOfn(double n, int m1, int m2) { std::vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(n, 1.0 / m)); } return(Vec); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SELF
// ############################

// ####### OBJETOS #######

// Checkered block:
std::vector<double> CheckeredBlock(int Size, double a, double b)
{ std::vector<double> R; bool Switch = false;  for (int n = 0; n < Size; ++n) { if (!Switch) { R.push_back(a); Switch = true; } else { R.push_back(b); Switch = false; } } return(R); }

// ####### ARI. E GEO. #######

// TERMS:
void SumVecTerms(std::vector<short int>& Vec, short int Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(std::vector<int>& Vec, int Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(std::vector<float>& Vec, float Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(std::vector<double>& Vec, double Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void MultVecTerms(std::vector<int>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Procure não ter zeros
void MultVecTerms(std::vector<short int>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Procure não ter zeros
void MultVecTerms(std::vector<float>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } }
void MultVecTerms(std::vector<double>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } }

// Seq. & Series:
void SumVecTermsArith(std::vector<int>& Vec, int Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } } // Da para fazer linhas com isso
void SumVecTermsArith(std::vector<double>& Vec, double Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } }
void MultVecTermsArith(std::vector<int>& Vec, double Mult, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } } // Procure não ter zeros
void MultVecTermsArith(std::vector<double>& Vec, double Mult, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } }
void SumVecTermsGeo(std::vector<int>& Vec, int Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * pow(Ratio, n); } }
void SumVecTermsGeo(std::vector<double>& Vec, double Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * pow(Ratio, n); } }
void MultVecTermsGeo(std::vector<int>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * pow(Ratio, n); } } // Procure não ter zeros
void MultVecTermsGeo(std::vector<double>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * pow(Ratio, n); } }

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_