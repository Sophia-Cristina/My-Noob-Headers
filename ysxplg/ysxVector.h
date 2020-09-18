#pragma once

#ifndef YSXVECTOR_H
#define YSXVECTOR_H

// #####################################################################################################################################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

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
vector<int> JoinVectors(vector<int> VecPre, vector<int> VecSuf) { vector<int> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<float> JoinVectors(vector<float> VecPre, vector<float> VecSuf) { vector<float> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<double> JoinVectors(vector<double> VecPre, vector<double> VecSuf)
{ vector<double> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<char> JoinVectors(vector<char> VecPre, vector<char> VecSuf) { vector<char> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<string> JoinVectors(vector<string> VecPre, vector<string> VecSuf)
{ vector<string> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<bool> JoinVectors(vector<bool> VecPre, vector<bool> VecSuf) { vector<bool> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }

// ############################
// ####### ARRAYS:

void InvertArray(char c[], char* pt)
{
	const int Size = sizeof c; char t[Size];
	for (int n = 0; n < Size; ++n) { t[Size - 1 - n] = c[n]; }
	for (int n = 0; n < Size; ++n) { *(pt + n) = t[n]; }
}

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

// ############################
// ####### TRIGONEMETRICOS E SINAIS
// ############################

// Seno:
vector<double> SineVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(sin(x0 + (Delta * n))); } return(R);
}

// Coseno:
vector<double> CosineVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(cos(x0 + (Delta * n))); } return(R);
}

// Tangente:
vector<double> TangentVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(tan(x0 + (Delta * n))); } return(R);
}

// Cotangente:
vector<double> CotangentVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(cot(x0 + (Delta * n))); } return(R);
}

// SquareWave:
vector<double> SquareWaveVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(rect(x0 + (Delta * n))); } return(R);
}

// SawWave:
vector<double> SawWaveVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(saw(x0 + (Delta * n))); } return(R);
}

// SawWave:
vector<double> TriWaveVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(tri(x0 + (Delta * n))); } return(R);
}

// Miniform vector:
vector<double> MiniFormVec(int Size, double x0, double x1)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { R.push_back(MiniForm(x0 + (Delta * n), 1)); } return(R);
}

// Linha:
vector<double> LineVec(int Size, double x0, double x1, double Sum, double Mult)
{
	vector<double> R; if (x0 > x1) { double t = x0; x0 = x1; x1 = t; } double Delta = (x1 - x0) / Size; for (int n = 0; n < Size; ++n) { double x = x0 + (Delta * n); R.push_back(Sum + x * Mult); } return(R);
}

// ############################
// ####### MÁXIMO E MINIMO DE VETOR
// ############################

int MaxVec(vector<int> Vec) { int Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }

double MaxVec(vector<double> Vec) { double Max = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { if (Vec[n] > Max) Max = Vec[n]; } return(Max); }

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
void MaxMinVecAbs(vector<int> Vec, int& Max, int& Min)
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
void MaxMinVecAbs(vector<double> Vec, double& Max, double& Min)
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

// PONTO MÁXIMO E MINIMO DE VETORES:
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

// PEGA MARGEM DE EXPONENTE:
vector<long> PowerOfn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(n, a)); } return(Vec); }
vector<long> PowerByn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(a, n)); } return(Vec); }
vector<double> nRootOfm(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(m, 1.0 / n)); }	return(Vec); }
vector<double> mRootOfn(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(n, 1.0 / m)); } return(Vec); }

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
void SumVecTermsGeo(vector<int>& Vec, int Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * (n * Ratio); } }
void SumVecTermsGeo(vector<double>& Vec, double Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * (n * Ratio); } }
void MultVecTermsGeo(vector<int>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * (n * Ratio); } } // Procure não ter zeros
void MultVecTermsGeo(vector<double>& Vec, double Mult, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] *= Mult * (n * Ratio); } }

// ####### ENVELOPES #######

// Attack Decay, considerando o numero de dados num 'vector' (.size()):
vector<double> AttackDecay(vector<double> Input, double A, double D )
{
	vector<double> R;
	double Sum = A + D, RatioA = A / Sum, RatioD = D / Sum;
	int Size = Input.size(); int SizeA = floor(Size * RatioA), SizeD = Size - SizeA;
	double DeltaA = 1.0 / SizeA, DeltaD = 1.0 / SizeD;
	for (int n = 0; n < SizeA; ++n) { double x = (DeltaA * n); R.push_back(x * Input[n]); }
	for (int n = SizeA; n < Size; ++n) { double x = (DeltaD * (n - SizeA)); R.push_back((1 - x) * Input[n]); }	
	return(R);
}

// vector<double> ADSR

// ############################
// ####### OPERAÇOES COM ZEROS
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
		int Rand = rand() % Vector.size();
		for (int n = 0; n < Vector.size(); ++n)
		{
			V.push_back(Vector[n]); if (n == Rand) { V.push_back(0); }
		}
		Vector = V;
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

// ############################

// ############################

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
