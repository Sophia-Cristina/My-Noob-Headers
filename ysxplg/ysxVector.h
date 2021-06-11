#pragma once

#ifndef YSXVECTOR_H
#define YSXVECTOR_H

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	FUNÇÃO 'ExpSignalVec' AGORA É 'ExponentVec'. E EU NÃO LEMBRO O PORQUE ERA 'Signal';
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################
// ####### TÉCNICOS
// ############################

// CONVERSORES:
vector<float> SInt2Float(vector<short int> SInt) { vector<float> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
vector<double> SInt2double(vector<short int> SInt) { vector<double> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
vector<float> Int2Float(vector<int> Int) { vector<float> V; for (int n = 0; n < Int.size(); ++n) { V.push_back(Int[n]); } return(V); }
vector<int> Float2Int(vector<float> Float) { vector<int> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
vector<int> SInt2Int(vector<short int> SInt) { vector<int> V; for (int n = 0; n < SInt.size(); ++n) { V.push_back(SInt[n]); } return(V); }
vector<double> Float2Double(vector<float> Float) { vector<double> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
vector<float> Double2Float(vector<double> Double) { vector<float> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
vector<short int> Double2SInt(vector<double> Double) { vector<short int> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }
vector<short int> Float2SInt(vector<float> Float) { vector<short int> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }

// UNE VETORES:
vector<int> JoinVectors(vector<int> VecPre, vector<int> VecSuf) { for (int n = 0; n < VecSuf.size(); ++n) { VecPre.push_back(VecSuf[n]); } return(VecPre); }
vector<float> JoinVectors(vector<float> VecPre, vector<float> VecSuf) { vector<float> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<double> JoinVectors(vector<double> VecPre, vector<double> VecSuf)
{ vector<double> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<char> JoinVectors(vector<char> VecPre, vector<char> VecSuf) { vector<char> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<string> JoinVectors(vector<string> VecPre, vector<string> VecSuf)
{ vector<string> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<bool> JoinVectors(vector<bool> VecPre, vector<bool> VecSuf) { vector<bool> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }

// POR INDICES:
vector<double> SumVecIndex(vector<double> V, int Index0, int Index1, bool Average)
{
	vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { if (Average) { Vec.push_back((V[n] + V[Last]) * 0.5); } else { Vec.push_back(V[n] + V[Last]); } } }
	return(Vec);
}
vector<double> SubVecIndex(vector<double> V, int Index0, int Index1)
{
	vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { Vec.push_back(V[n] - V[Last]); } }
	return(Vec);
}
vector<double> MultVecIndex(vector<double> V, int Index0, int Index1, bool Sqrt)
{
	vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { if (Sqrt) { Vec.push_back(sqrt(V[n] * V[Last])); } else { Vec.push_back(V[n] * V[Last]); } } }
	return(Vec);
}
vector<double> DivVecIndex(vector<double> V, int Index0, int Index1)
{
	vector<double> Vec;
	if (Index0 < 0) { Index0 = 0; } if (Index1 < 1) { Index1 = 1; } if (Index0 == Index1) { ++Index1; }
	int First = Index0, Last = Index1; if (Index0 > Index1) { First = Index1; Last = Index0; }
	for (int n = 0; n < V.size(); ++n) { if (n != First) { if (n != Last) { Vec.push_back(V[n]); } } else { Vec.push_back(V[n] / V[Last]); } }
	return(Vec);
}

// CHANGE VALUE IN INDEX AND DELETE THE VALUE THAT GOT IN:
vector<double> SubstituteVecIndex(vector<double> V, int TargetIndex, int SubIndex)
{
	vector<double> Vec;
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
vector<double> ReplaceeVecIndex(vector<double> V, int TargetIndex, int SubIndex)
{
	vector<double> Vec;
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
vector<vector<double>> VectorSubBlocks(vector<double> In, int Div)
{
	vector<double> v;
	vector<vector<double>> V;
	int Fraction = In.size() / Div;

	for (int n = 0; n < In.size(); ++n)
	{
		v.push_back(In[n]);
		int Mod = n % Fraction;
		if (Mod == Fraction - 1) { V.push_back(v); v = vector<double>::vector(); }
		else if (n == In.size() - 1) { V.push_back(v); }
	}

	return(V);
}

// ############################
// ####### OPERAÇÕES COM ZEROS
// ############################

// Se o segundo vetor tiver um numero no mesmo indice que o primeiro vetor tem um zero, ele substitui o zero pelo valor do indice:
vector<int> SubstituteZero(vector<int> Vec0, vector<int> Vec1)
{
	vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<float> SubstituteZero(vector<float> Vec0, vector<float> Vec1)
{
	vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<double> SubstituteZero(vector<double> Vec0, vector<double> Vec1)
{
	vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// Insert zeros in random positions into a vector:
vector<double> InsertRandomZeros(vector<double> Vector, int Zeros)
{
	if (Zeros < 1) { Zeros = 1; }
	vector<double> V;
	for (int Z = 0; Z < Zeros; ++Z)
	{
		vector<double> v;
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
vector<double> InsertZerosBeginorEnd(vector<double> Vector, int Zeros, bool BeginEnd)
{
	vector<double> V;
	if (!BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	for (int n = 0; n < Vector.size(); ++n) { V.push_back(Vector[n]); }
	if (BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	return (V);
}

// Insert zeros between each term:
vector<double> InsertZerosBetweenTerms(vector<double> Vector, int Zeros, bool BeforeAfter, bool BeforeAndAfter)
{
	vector<double > V;
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
vector<double> InsertZerosBetweenTermsExpo(vector<double> Vector, int Zeros, double InitialPower, bool BeforeAfter, bool BeforeAndAfter)
{
	vector<double> V;
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
vector<double> InsertZerosatTerm(vector<double> Vector, int Zeros, int at, bool BeforeAfter)
{
	vector<double> V;
	for (int n = 0; n < Vector.size(); ++n)
	{
		if (!BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
		V.push_back(Vector[n]);
		if (BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { V.push_back(0); } }
	}
	return (V);
}

// Delete zeros:
vector<double> DeleteZeros(vector<double> Vector)
{
	vector<double> V;
	for (int n = 0; n < Vector.size(); ++n) { if (Vector[n] != 0) { V.push_back(Vector[n]); } }
	return (V);
}

// ############################
// ####### OPERAÇÕES COM NUMEROS
// ############################

// Insert copy of an indexed value at random positions into a vector:
vector<double> InsertRandomCopies(vector<double> Vector, int Copies)
{
	if (Copies < 1) { Copies = 1; }
	vector<double> V;
	for (int c = 0; c < Copies; ++c)
	{
		vector<double> v;
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

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SORTS
// ############################

// ### QUICKSORT:
void QuickSort(vector<int>& V, int l, int r)
{
	if (l >= r) { return; } int pivot = V[r]; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSort(vector<double>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r]; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSortPtx(vector<PointFlt>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r].x; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i].x <= pivot) { swap(V[cnt].x, V[i].x); swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPtx(V, l, cnt - 2); QuickSortPtx(V, cnt, r);
}
void QuickSortPty(vector<PointFlt>& V, int l, int r)
{
	if (l >= r) { return; } double pivot = V[r].y; int cnt = l;
	for (int i = l; i <= r; ++i) { if (V[i].y <= pivot) { swap(V[cnt].x, V[i].x); swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPty(V, l, cnt - 2); QuickSortPty(V, cnt, r);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### TRIGONEMETRICOS E SINAIS
// ############################

// Seno (phase in radians):
vector<double> SineWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * sin(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Coseno (phase in radians):
vector<double> CosineWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * cos(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Tangente (phase in radians):
vector<double> TangentWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * tan(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// Cotangente (phase in radians):
vector<double> CotangentWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * cot(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SquareWave (phase in radians):
vector<double> SquareWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * rect(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SawWave (phase in radians):
vector<double> SawWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * saw(Phase + (x0 + (Delta * n * Freq)))); } return(R);
}

// SawWave (phase in radians):
vector<double> TriWaveVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * tri(Phase + (x0 + (Delta * n) * Freq))); } return(R);
}

// Miniform vector (phase in radians):
vector<double> MiniFormVec(int Size, double x0, double x1, double Amp, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(Amp * MiniForm(Phase + x0 + (Delta * n), Freq)); } return(R);
}

// Linha:
vector<double> LineVec(int Size, double x0, double x1, double Sum, double Mult)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R.push_back(Sum + x * Mult); } return(R);
}

// Linha curva por exponente | 'x^Pow / Div^Pow':
vector<double> ExpCurveVec(int Size, double x0, double x1, double Pow, double Div)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size;
	for (int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R.push_back(pow(x, Pow) / pow(Div, Pow)); }
	return(R);
}

// Vetor Exponencial 'a^n'':
vector<double> ExponentVec(int Size, double x0, double x1, double a)
{
	vector<double> V;
	for (int n = 0; n < Size; ++n)
	{
		V.push_back(pow(a, n));
	}
	return(V);
}

// Vetor Exponencial 'B * (r^n)':
vector<double> ExponentVec(int Size, double x0, double x1, double B, double r)
{
	vector<double> V;

	for (int n = 0; n < Size; ++n)
	{
		V.push_back(B * pow(r, n));
	}
	return(V);
}

// Sinal Degrau:
vector<double> StepSigVec(int n0, int n1) { vector<double> V; for (int n = n0; n < n1; ++n) { V.push_back(StepSig(n)); } return(V); }

// ### COM TEMPO:

// Seno com mudança de frequencia por tempo:
vector<double> SineWaveVecTimeFreq(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
	double Delta = (x1 - x0) / Size;
	for (int n = 0; n < Size; ++n) { R.push_back(Gain * sin(Phase + x0 + Freq * pow(TimeRatio, n) * Delta * n)); } return(R);
}
// Seno com mudança de fase por tempo:
vector<double> SineWaveVecTimePhase(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
	double Delta = (x1 - x0) / Size;
	for (int n = 0; n < Size; ++n) { R.push_back(Gain * sin((pow(TimeRatio, n) * Phase) + (x0 + (Delta * n * Freq)))); } return(R);
}
// Seno com mudança de ganho por tempo:
vector<double> SineWaveVecTimeGain(int Size, double x0, double x1, double TimeRatio, double Gain, double Freq, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
	double Delta = (x1 - x0) / Size;
	for (int n = 0; n < Size; ++n) { R.push_back((pow(TimeRatio, n) * Gain) * sin(Phase + x0 + (Delta * n * Freq))); } return(R);
}
// Seno com mudança de frequencia por modulação (FM):
vector<double> SineWaveVecFM(int Size, double x0, double x1, double Gain, double Freq, double FreqFM, double Phase)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; }
	double Delta = (x1 - x0) / Size;
	for (int n = 0; n < Size; ++n)
	{
		double x = Phase + (x0 + Freq * Delta * n);
		double xm = Phase + (x0 + FreqFM * Delta * n);
		R.push_back(Gain * sin(sin(x) * FreqFM));
	}
	return(R);
}

// ### NOISE:

// White noise:
vector<double> WhiteNoise(int Size)
{ vector<double> WN; for (int n = 0; n < Size; ++n) { int Random = rand() % 20001; double RealVal = (Random - 10000) / 10000.0; WN.push_back(RealVal); } return(WN); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### MÁXIMO E MINIMO DE VETOR
// ############################

int MaxVec(vector<int> Vec) { int Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }
float MaxVec(vector<float> Vec) { float Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }
double MaxVec(vector<double> Vec) { double Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }

int MinVec(vector<int> Vec) { int Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }
float MinVec(vector<float> Vec) { float Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }
double MinVec(vector<double> Vec) { double Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] < Min) Min = Vec[n]; } return(Min); }

int MaxVecAbs(vector<int> Vec) { int Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) > Max) Max = abs(Vec[n]); } return(Max); }
float MaxVecAbs(vector<float> Vec) { float Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }
double MaxVecAbs(vector<double> Vec) { double Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) > Max) Max = fabs(Vec[n]); } return(Max); }

int MinVecAbs(vector<int> Vec) { int Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (abs(Vec[n]) < Min) Min = abs(Vec[n]); } return(Min); }
float MinVecAbs(vector<float> Vec) { float Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }
double MinVecAbs(vector<double> Vec) { double Min = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (fabs(Vec[n]) < Min) Min = fabs(Vec[n]); } return(Min); }

// #######

void MaxMinVec(vector<int> Vec, int& Max, int& Min)
{
	int max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	Max = max; Min = min;
}
void MaxMinVecAbs(vector<int> Vec, int& Max, int& Min) // Soma com ABS, não ABS de apenas ABS.
{
	int max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}
	int Absmx = 0, Absmn = 0;
	if (max < 0) { Absmx = abs(max); max += Absmx; min += Absmx; }
	if (min < 0) { Absmn = abs(min); max += Absmn; min += Absmn; }
	Max = max; Min = min;
}
void MaxMinVec(vector<double> Vec, double& Max, double& Min)
{
	double max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}

	Max = max; Min = min;
}
void MaxMinVecAbs(vector<double> Vec, double& Max, double& Min) // Soma com ABS, não ABS de apenas ABS.
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
	Max = max; Min = min;
}
void MaxMinVec(vector<float> Vec, float& Max, float& Min)
{
	float max = Vec[0], min = Vec[0];
	for (int n = 1; n < Vec.size(); ++n)
	{
		if (Vec[n] > max) max = Vec[n];
		if (Vec[n] < min) min = Vec[n];
	}

	Max = max; Min = min;
}
void MaxMinVecAbs(vector<float> Vec, float& Max, float& Min) // Soma com ABS, não ABS de apenas ABS.
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
	Max = max; Min = min;
}

// ####### ESPECIAIS:

// O minimo sempre vai ser zero, basicamente o delta entre o maximo e o minimo de um vector:
float MaxVecMin0(vector<float> Vec)
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
double MaxVecMin0(vector<double> Vec)
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
void MaxSizeBoolMatrix(vector<CellBool> Vec, int& Maxi, int& Maxj)
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
void MaxMinVecPoint(vector<Point>& VecPoint, Point& Max, Point& Min, bool Abs)
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
void MaxMinVecLinePoint(vector<LinePoint>& VecLinePoint, LinePoint& Max, LinePoint& Min, bool Abs)
{
	LinePoint oMax(VecLinePoint[0]), oMin(VecLinePoint[0]);
	for (size_t n = 1; n < VecLinePoint.size(); ++n)
	{
		if (VecLinePoint[n].x0 > oMax.x0) oMax.x0 = VecLinePoint[n].x0; else if (VecLinePoint[n].x0 < oMin.x0) oMin.x0 = VecLinePoint[n].x0;
		if (VecLinePoint[n].y0 > oMax.y0) oMax.y0 = VecLinePoint[n].y0; else if (VecLinePoint[n].y0 < oMin.y0) oMin.y0 = VecLinePoint[n].y0;
		if (VecLinePoint[n].x1 > oMax.x1) oMax.x1 = VecLinePoint[n].x1; else if (VecLinePoint[n].x1 < oMin.x1) oMin.x1 = VecLinePoint[n].x1;
		if (VecLinePoint[n].y1 > oMax.y1) oMax.y1 = VecLinePoint[n].y1; else if (VecLinePoint[n].y1 < oMin.y1) oMin.y1 = VecLinePoint[n].y1;
	}
	if (Abs) // Construção
	{
		int absx, absy;
		bool absxb0 = false, absyb0 = false, absxb1 = false, absyb1 = false;
		if (Abs)
		{
			if (oMin.x0 < 0) { absx = abs(oMin.x0); oMax.x0 += absx; oMin.x0 = 0; absxb0 = true; }
			if (oMin.y0 < 0) { absy = abs(oMin.y0); oMax.y0 += absy; oMin.y0 = 0; absyb0 = true; }
			if (oMin.x0 < 0) { absx = abs(oMin.x0); oMax.x0 += absx; oMin.x0 = 0; absxb1 = true; }
			if (oMin.y0 < 0) { absy = abs(oMin.y0); oMax.y0 += absy; oMin.y0 = 0; absyb1 = true; }
		}
		if (absxb0 || absyb0 || absxb1 || absyb1)
		{
			for (size_t n = 0; n < VecLinePoint.size(); ++n)
			{
				if (absxb0) { VecLinePoint[n].x0 += absx; }
				if (absyb0) { VecLinePoint[n].y0 += absy; }
				if (absxb1) { VecLinePoint[n].x1 += absx; }
				if (absyb1) { VecLinePoint[n].y1 += absy; }
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
int SumVec(vector<int> Vec) { int Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
double SumVec(vector<double> Vec) { double Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
int MultVec(vector<int> Vec) { int Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); } // Procure não ter zeros
double MultVec(vector<double> Vec) { double Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); }

// POWER VECTOR TERMS:
vector<int> PowVec(vector<int> Vec, int Pow) { vector<int> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }
vector<double> PowVec(vector<double> Vec, double Pow) { vector<double> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }

// Two vectors and vector return:
vector<int> SumTwoVec(vector<int> Vec0, vector<int> Vec1)
{
	vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<float> SumTwoVec(vector<float> Vec0, vector<float> Vec1)
{
	vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<double> SumTwoVec(vector<double> Vec0, vector<double> Vec1)
{
	vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] + Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<int> MultiTwoVec(vector<int> Vec0, vector<int> Vec1)
{
	vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<float> MultiTwoVec(vector<float> Vec0, vector<float> Vec1)
{
	vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<double> MultiTwoVec(vector<double> Vec0, vector<double> Vec1)
{
	vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); }
	else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { V.push_back(Vec0[n] * Vec1[n]); }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}

// PEGA MARGEM DE EXPONENTE:
vector<long> PowerOfn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(n, a)); } return(Vec); }
vector<long> PowerByn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(a, n)); } return(Vec); }
vector<double> nRootOfm(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(m, 1.0 / n)); }	return(Vec); }
vector<double> mRootOfn(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(n, 1.0 / m)); } return(Vec); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### SELF
// ############################

// ####### OBJETOS #######

// Checkered block:
vector<double> CheckeredBlock(int Size, double a, double b)
{ vector<double> R; bool Switch = false;  for (int n = 0; n < Size; ++n) { if (!Switch) { R.push_back(a); Switch = true; } else { R.push_back(b); Switch = false; } } return(R); }

// ####### ARI. E GEO. #######

// TERMS:
void SumVecTerms(vector<short int>& Vec, short int Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(vector<int>& Vec, int Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(vector<float>& Vec, float Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(vector<double>& Vec, double Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void MultVecTerms(vector<int>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Procure não ter zeros
void MultVecTerms(vector<short int>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Procure não ter zeros
void MultVecTerms(vector<float>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } }
void MultVecTerms(vector<double>& Vec, double Mult) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult; } }

// Seq. & Series:
void SumVecTermsArith(vector<int>& Vec, int Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } } // Da para fazer linhas com isso
void SumVecTermsArith(vector<double>& Vec, double Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } }
void MultVecTermsArith(vector<int>& Vec, double Mult, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } } // Procure não ter zeros
void MultVecTermsArith(vector<double>& Vec, double Mult, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } }
void SumVecTermsGeo(vector<int>& Vec, int Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * pow(Ratio, n); } }
void SumVecTermsGeo(vector<double>& Vec, double Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * pow(Ratio, n); } }
void MultVecTermsGeo(vector<int>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * pow(Ratio, n); } } // Procure não ter zeros
void MultVecTermsGeo(vector<double>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * pow(Ratio, n); } }

// ####### ENVELOPES #######

// Attack Decay, considerando o numero de dados num 'vector',
// portanto A e D são razões:
vector<double> AttackDecay(vector<double> Input, double A, double D, double Gain)
{
	vector<double> R;
	double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
	int Size = Input.size(); int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
	double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
	cout << " Size: " << Size << " | SA: " << SizeA << " | SD: " << SizeD << " | DeltaA: " << DeltaA << " | DeltaD: " << DeltaD << endl;
	for (int n = 0; n < SizeA; ++n) { double x = DeltaA * n; R.push_back(x * Input[n] * Gain); }
	for (int n = SizeA; n < Size; ++n) { double x = DeltaD * (n - SizeA); R.push_back((1 - x) * Input[n] * Gain); }	
	return(R);
}

// Attack Envelope
vector<double> AttackVector(vector<double> Input, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	for (int n = 0; n < Size; ++n) { double x = n / (double)Size; R.push_back(x * Input[n] * Gain); }
	return(R);
}
// Attack Exponetial Envelope
vector<double> AttackExpVector(vector<double> Input, double Pow, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	for (int n = 0; n < Size; ++n) { double x = pow(n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
	return(R);
}

// Decay Envelope
vector<double> DecayVector(vector<double> Input, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	for (int n = 0; n < Size; ++n) { double x = (Size - n) / Size; R.push_back(x * Input[n] * Gain); }
	return(R);
}

// Decay Exponetial Envelope
vector<double> DecayExpVector(vector<double> Input, double Pow, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	for (int n = 0; n < Size; ++n) { double x = pow(Size - n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
	return(R);
}

// Change Input Vector by a graduation from L1 to L2, similar to an Attack, but with both sides:
vector<double> LineEnvelop(vector<double> Input, double L1, double L2, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
	//double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
	//double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
	double DeltaL = L2 - L1, Delta = DeltaL / Size;
	for (int n = 0; n < Size; ++n) { double x = L1 + Delta * n; R.push_back(x * Input[n] * Gain); }
	return(R);
}

// Change Input Vector by a exponential graduation from L1 to L2, similar to an Attack, but with both sides:
/*vector<double> LineExpEnvelop(vector<double> Input, double L1, double L2, double Pow, double Gain)
{
	vector<double> R;
	int Size = Input.size();
	if (L1 > 1) { L1 = 1; } if (L1 < 0) { L1 = 0; } if (L2 > 1) { L2 = 1; } if (L2 < 0) { L2 = 0; }
	//double BigL = L2; if (L1 > L2) { BigL = L1; } double SmallL = L1; if (L1 > L2) { SmallL = L2; }
	//double DeltaL = BigL - SmallL, Delta = DeltaL / Size;
	double Delta = L2 - L1;
	for (int n = 0; n < Size; ++n) { double x = L1 + pow(Delta * n, Pow) / pow(Size, Pow); R.push_back(x * Input[n] * Gain); }
	return(R);
}*/

// MODULATE VECTOR WITH ANOTHER VECTOR.
// Last index will be from input:
vector<double> VectorEnvelop(vector<double> Input, vector<double> Modulator, double Gain)
{
	vector<double> V; for (int n = 0; n < Input.size(); ++n) { if (n < Modulator.size()) { V.push_back(Input[n] * Modulator[n] * Gain); } else { V.push_back(Input[n] * Gain); } } return(V);
}

// vector<double> ADSR

// ####### NORMALIZERS #######

// IF BIGGER THAN Y THEN Y:
vector<double> LimitToptoY(vector<double> fx, double Y) { vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y) { gx[n] = Y; } } return(gx); }

// IF BIGGER THAN Y AND LOWER THAN -Y, THEN Y AND -Y:
vector<double> LimittoY(vector<double> fx, double Y) { vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y) { gx[n] = Y; } else if (gx[n] < -Y) { gx[n] = -Y; } } return(gx); }

// IF BIGGER THAN Y1 AND LOWER THAN Y0, THEN Y1 AND Y0:
vector<double> LimittoY1Y0(vector<double> fx, double Y1, double Y0)
{
	if (Y0 == Y1) { Y0 += 1.0e-9; } if (Y1 < Y0) { double T = Y1; Y1 = Y0; Y0 = T; }
	vector<double> gx = fx; for (int n = 0; n < gx.size(); ++n) { if (gx[n] > Y1) { gx[n] = Y1; } else if (gx[n] < Y0) { gx[n] = Y0; } } return(gx);
}

// MAX (TOP OF VECTOR) IS DIVIDED BY MAX:
vector<int> NormalizeTopto1(vector<int> fx) { vector<int> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }
vector<double> NormalizeTopto1(vector<double> fx) { vector<double> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }

// IF MAX AND MIN IS BIGGER THAN 1 AND LOWER THAN -1, DIVIDE BY THE BIGGER ABSOLUTE:
vector<int> Normalize(vector<int> fx) { vector<int> gx = fx; int Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }
vector<double> Normalize(vector<double> fx) { vector<double> gx = fx; double Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; } return(gx); }

// MOD NORMALIZE, (f(x) + 1) * 0.5:
vector<int> NormalizeModTopto1(vector<int> fx)
{ vector<int> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx); }
vector<double> NormalizeModTopto1(vector<double> fx)
{ vector<double> gx = fx; double Max = MaxVec(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx); }
vector<int> NormalizeMod(vector<int> fx) { vector<int> gx = fx; int Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx); }
vector<double> NormalizeMod(vector<double> fx)
{ vector<double> gx = fx; double Max = MaxVecAbs(gx); if (Max == 0) { Max = 1.0e-9; } for (int n = 0; n < gx.size(); ++n) { gx[n] /= Max; gx[n] += 1; gx[n] *= 0.5; } return(gx); }

// ############################

// ############################


// ############################




// #####################################################################################################################################



// ################################################# FIM ####################################################################################

#endif // SCPARSE_