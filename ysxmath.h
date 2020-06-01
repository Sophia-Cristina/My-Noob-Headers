#pragma once

#ifndef YSXMATH_H
#define YSXMATH_H
//#ifndef __CIMG_H_INCLUDED__   // if x.h hasn't been included yet...
//#define __CIMG_H_INCLUDED__

#include <string>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
// MATEMATICAS:
#include <math.h> // #include <cmath> // Anterior
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

// #####################################################################################################################################
// ############## FORWARD DECLARATIONS ##############
// Extern:
double SrfSphr(double);
double WaveLgh(double, double);
double MiniForm(double, double);
double Derivative(double, double); double Derivative(double, double, double);
double Derivative(double, double, double, double); double Derivative(double, double, double, double, double);
double d2xdt2(double, double);
double LawSinAngle(double, double, double);

// Intern:
int SumVec(vector<int>);
double SumVec(vector<double>);
int MultVec(vector<int>);
double MultVec(vector<double>);
vector<int> PowVec(vector<int>, int);
vector<double> PowVec(vector<double>, double);
// #####################################################################################################################################
// ############## TOOLS ##############
// DECLARE OBJECTOS QUE SERÃO USADOS EM TODOS OS HEADERS AQUI!
// ####### STRUCTS:
struct Point { int x, y; }; // Coordenadas em int | Era Point { int x, y; Point(int x, int y) : x(x), y(y) {} };, mas funcionou assim
struct PointFlt { double x, y; }; // Coordenadas em flt
struct Point3D { int x, y, z; }; // Coordenadas em int 3D
struct Point3DFlt { double x, y, z; }; // Coordenadas em flt 3D
struct CellBool { int i, j; bool b; }; // Matriz de Bool
struct CellBool3D { int i, j, k; bool b; }; // Matriz de Bool 3D
struct CellInt { int i, j; int n; }; // Matriz de integer
struct CellInt3D { int i, j, k; int n; }; // Matriz de integer
struct CellFlt { int i, j; float x; }; // Matriz de float
struct CellFlt3D { int i, j; float x; }; // Matriz de float
struct LinePoint { int x0, y0, x1, y1; }; // Para fazer linhas
struct LinePoint3D { int x0, y0, z0, x1, y1, z1; }; // Para fazer linhas

// ####### CLASSES COMO FERRAMENTA:
class MatrixFlt
{
public:
	int i, j;
	vector<double> Datas;
	MatrixFlt(int Matrixi, int Matrixj) { i = Matrixi; j = Matrixj; vector<double> V(i * j); Datas = V; }
};

// #####################################################################################################################################

#include "ysxplg\\ysxConst.h";
#include "ysxplg\\ysxPhis.h";
#include "ysxplg\\ysxGeo.h";
#include "ysxplg\\ysxCalc.h";
#include "ysxplg\\ysxFractal.h";

// #####################################################################################################################################

// ############## MATEMATICA ##############

// ####### MULTIPLOS OU DIVISORES:
// GCD (GREATEST COMMON DIVISOR):
int GCD(int a, int b)
{
	a = abs(a); b = abs(b);
	if (b == a) { return (a); } if (b > a) { int tmp = a; a = b; b = tmp; }
	int GDC;
	int Mod = a % b, ModDiv = b, ActualMod;
	if (b == 0) { return (a); } else { while (Mod != 0) { ActualMod = ModDiv % Mod; ModDiv = Mod; Mod = ActualMod; } return (ModDiv); }
}

// LCM (LEAST COMMON MULTUPLE):
int LCM(int a, int b) { a = abs(a); b = abs(b); return ((a * b) / GCD(a, b)); }

// FACTORS:
vector<int> Factors(int n) { vector<int> V; for (int m = 1; m <= n; ++m) { if (0 == n % m) { V.push_back(m); } } return (V); }

// DIVISOR FUNCTION (When x is 1, the function is called the sigma function or sum - of - divisors function)
int DivFunc(int n, int Power) { vector<int> Fac = PowVec(Factors(n), Power); int Sum = SumVec(Fac); return(Sum); }
// ####### MÉDIAS E RAZÕES:
// MÉDIA, ARITHMETIC MEAN:
double Average(vector<double> Vec) { double Soma = 0; if (Vec.size() != 0) { for (int n = 0; n < Vec.size(); ++n) { Soma += Vec[n]; } Soma /= Vec.size(); } return (Soma); }

// ROOT MEAN SQUARE:
double RMS(vector<double> Vec) { double Soma = 0; int n = Vec.size(); if (n != 0) { for (int i = 0; i < n; ++i) { Soma += Vec[i] * Vec[i]; } Soma /= n; } return (sqrt(Soma)); }

// HARMONIC MEAN:
double HarmMean(vector<double> Vec) { double Soma = 0; int n = Vec.size(); if (n != 0) { for (int i = 0; i < n; ++i) { Soma += 1.0 / Vec[i]; } n /= Soma; } return (n); }

// GEOMETRIC MEAN:
double GeoMean(vector<double> Vec)
{ double Mult = 0; if (Vec.size() != 0) { for (int n = 0; n < Vec.size(); ++n) { Mult *= Vec[n]; } Mult = pow(Mult, 1 / Vec.size()); } return (Mult); }

// ARITHMETIC-GEOMETRIC MEAN:
PointFlt ArithGeoMean(PointFlt Point, int Iter)
{
	PointFlt Pt; Pt.x = 0.5 * (Point.x + Point.y); Pt.y = sqrt(Point.x * Point.y);
	for (int n = 1; n < Iter; ++n) { double x = Pt.x, y = Pt.y; Pt.x = 0.5 * (x + y); Pt.y = sqrt(x * y); }
	return (Pt);
}

// GEOMETRIC-HARMONIC MEAN:
PointFlt GeoHarmMean(PointFlt Point, int Iter)
{
	PointFlt Pt; Pt.x = sqrt(Point.x * Point.y); Pt.y = 2.0 / ((1.0 / Point.x) + (1.0 / Point.y));
	for (int n = 1; n < Iter; ++n) { double x = Pt.x, y = Pt.y; Pt.x = sqrt(x * y); Pt.y = 2.0 / ((1.0 / x) + (1.0 / y)); }
	return (Pt);
}

// POWER MEAN OR GENERALIZED MEAN:
double PowerMean(vector<double> Vec, double p)
{ double Soma = 0; int n = Vec.size(); for (int i = 0; i < n; ++i) { Soma += pow(Vec[i], p); } Soma *= 1.0 / n; Soma = pow(Soma, 1 / p); return(Soma); }

// RAZÃO ENTRE DUAS RAZÕES: (Ex.: Cerveja, a = 365ml, Rta = 0.046; Cachaça, b = 50ml, Rtb = 0.39; Retorno = 0.86102564...
double MixRatio(int a, int Rta, int b, int Rtb) { return((a * Rta) / (b * Rtb)); }

// RAZÃO DA RAZÃO:
double RatioRatio(int a, int Rto) { return((a * Rto) / a); }

// SOMA DE POTENCIA: (Vai somando desde o 'm' até 'n' elevado por 'p' ou vai somando n de 'p0 a p1')
double SumIniEndtoPow(int Ini, int End, int p) { double Soma = 0; for (int m = Ini; m <= End; ++m) { Soma += pow(m, p); } return (Soma); }
double SumntoPowIniEnd(int n, int Ini, int End) { double Soma = 0; for (int m = Ini; m <= End; ++m) { Soma += pow(n, m); } return (Soma); }

double CubeofTwoCubes(double x, double y) { return(pow((x * x * x) + (y * y * y), 1.0 / 3)); }

// ####### ALGEBRA:
// FATORIAL:
long Fact(int a) { int Fact = 1; if (a > 0) { for (int n = 1; n <= a; ++n) { Fact *= n; } return (Fact); } else { return (1); } }

// QUADRATIC EQUATION:
PointFlt QuadraticEq(double a, double b, double c)
{
	PointFlt Root;
	double Delta = b * b - 4 * a * c;
	if (Delta == 0) { Root.x = -b / (2 * a); Root.y = -b / (2 * a);	return(Root); }
	Root.x = (-b + sqrt(Delta)) / (2 * a); Root.y = (-b - sqrt(Delta)) / (2 * a);
	return(Root);
}

// ####### NUMEROS:
// É PRIMO?:
bool IsPrime(long n) { n = abs(n); for (int m = 2; m < n - 1; ++m) { if (0 == n % m) { return(false); } } return(true); }

// NUMERO TRIANGULAR:
int TriNmbr(int n) { return ((n * (n + 1)) / 2); }

// ####### COMBINATÓRIA:
// PERMUTATIONS WITHOUT REPETITION:
long BinomialCoff(int n, int k) { n = abs(n); k = abs(k); long Fct = (n - k) + 1; for (int a = Fct + 1; a <= n; ++a) { Fct *= a; } return(Fct / Fact(k)); }

// COMBINATION:

// PERMUTATIONS WITHOUT REPETITION:
//long PermNoRep(int n, int r) { n = abs(n); r = abs(r); long fn = Fact(n), fnr = Fact(n - r), Ret = fn / fnr; cout << "fn: " << fn << " | fnr: " << fnr << endl;
//cout << "Ret: " << Ret << endl; return(Ret); }

// FIBO NUMBER:
int GetaFibonmbr(int Fn)
{
	if (Fn < 1) { return(1); }
	if (Fn == 2) { return(1); }
	int One = 1, Two = 1;
	int Actual;
	for (int n = 3; n <= Fn; ++n)
	{
		Actual = One + Two;
		One = Two;
		Two = Actual;
	}
	return(Actual);
}
vector<int> GetaFiboVec(int Fn) // VEJA SE TA CERTO, VEJA SE n NÃO DEVERIA SER 2
{
	if (Fn < 1) { vector<int> A; A.push_back(1); return(A); }
	if (Fn == 2) { vector<int> A; A.push_back(1); A.push_back(1); return(A); }
	int One = 1, Two = 1;
	vector<int> Actual{1, 1};
	for (int n = 3; n <= Fn; ++n)
	{
		Actual.push_back(One + Two);
		One = Two;
		Two = Actual[n - 1];
	}
	return(Actual);
}

// LUCAS NUMBER:
int GetaLucasnmbr(int Ln)
{
	if (Ln < 1) { return(2); }
	if (Ln == 2) { return(1); }
	int One = 2, Two = 1;
	int Actual;
	for (int n = 3; n <= Ln; ++n)
	{
		Actual = One + Two;
		One = Two;
		Two = Actual;
	}
	return(Actual);
}
vector<int> GetaLucasVec(int Ln) // VEJA SE TA CERTO, VEJA SE n NÃO DEVERIA SER 2
{
	if (Ln < 1) { vector<int> A; A.push_back(2); return(A); }
	if (Ln == 2) { vector<int> A; A.push_back(2); A.push_back(1); return(A); }
	int One = 2, Two = 1;
	vector<int> Actual{ 2, 1 };
	for (int n = 3; n <= Ln; ++n)
	{
		Actual.push_back(One + Two);
		One = Two;
		Two = Actual[n - 1];
	}
	return(Actual);
}

// ################################################# FIM ####################################################################################

// ############## TECNICOS  ##############
// STR2CHAR:
vector<char> Str2Char(string ThisStr)
{
	// char * ThisChr; | Estilo antigo, tinha que usar delete[] ThisChr, mas o return não permitia
	int TxtLim = ThisStr.length() + 1;
	// ThisChr = new char[TxtLim];
	vector<char> ThisChr(TxtLim);
	for (int chr = 0; chr < ThisStr.length(); ++chr)
	{
		ThisChr[chr] = ThisStr.at(chr);
		if (chr == ThisStr.length() - 1) { ThisChr[chr + 1] = '\0'; }
	}
	return(ThisChr);
}

string Char2Str(char C) { string Str = { C }; return (Str); }

// IS NUMBER?:
bool IsNmbr(char C)
{
	{
		if (C == '1') { return(true); }
		else if (C == '2') { return(true); }
		else if (C == '3') { return(true); }
		else if (C == '4') { return(true); }
		else if (C == '5') { return(true); }
		else if (C == '6') { return(true); }
		else if (C == '7') { return(true); }
		else if (C == '8') { return(true); }
		else if (C == '9') { return(true); }
		else if (C == '0') { return(true); }
		else { return (false); }
	}
}

// CHAR2INT:
int Chr2Int(char C)
{
	int a;
	if (C == '1') { return(1); } if (C == '2') { return(2); } if (C == '3') { return(3); } if (C == '4') { return(4); } if (C == '5') { return(5); }
	if (C == '6') { return(6); } if (C == '7') { return(7); } if (C == '8') { return(8); } if (C == '9') { return(9); } if (C == '0') { return(0); }
}

// STR2INT:
int Str2Int(string S)
{
	int a = 0, Count = 0;
	char C; bool Oktogo = false, Neg = false;
	vector<int> Array;
	for (int n = 0; n < S.length(); ++n)
	{
		if (S[n] == '1' || S[n] == '2' || S[n] == '3' || S[n] == '4' || S[n] == '5' || S[n] == '6' || S[n] == '7' || S[n] == '8' || S[n] == '9' || S[n] == '-')
		{ Oktogo = true; } // se não for ok antes, e for depois, retornara true
	}
	if (Oktogo == true)
	{
		for (int n = 0; n < S.length(); ++n)
		{
			if (S[0] == '-') { Neg = true; }
			if (S[n] == '1') { Array.push_back(1); ++Count; } if (S[n] == '2') { Array.push_back(2); ++Count; } if (S[n] == '3') { Array.push_back(3); ++Count; }
			if (S[n] == '4') { Array.push_back(4); ++Count; } if (S[n] == '5') { Array.push_back(5); ++Count; } if (S[n] == '6') { Array.push_back(6); ++Count; }
			if (S[n] == '7') { Array.push_back(7); ++Count; } if (S[n] == '8') { Array.push_back(8); ++Count; } if (S[n] == '9') { Array.push_back(9); ++Count; }
			if (S[n] == '0' && n != 0) { Array.push_back(0); ++Count; }
		}
		for (int n = 0; n < Count; ++n)
		{
			if (Array[n] != 0) { a = a + (Array[n] * (pow(10, (Count - n - 1)))); }
			else { for (int m = 1; m <= Count - n; m = m * 10) { a = a * 1; } }
		}
	}
	else { a = 0; }
	if (Neg) { a *= - 1; }
	return(a);
}

// STR2DEC:
double Str2Dec(string S)
{
	int n = 0;
	string Str, Str0;
	while (S[n] != '.' && n < S.length()) { Str.push_back(S[n]); ++n; }
	if (n + 1 < S.length()) { for (int m = n + 1; m < S.length(); ++m) { Str0.push_back(S[m]); } } else { Str0 = "0"; }
	int Int = Str2Int(Str), Int2 = Str2Int(Str0);
	return (Int + (Int2 * (1.0 / pow(10, Str0.length()))));
}

// IS DECIMAL?:
bool IsDec(string S) { double n = Str2Dec(S); if (1.0 == n / round(n)) { return (false); } else { return (true); } }

// DEC2FRAC:
Point Dec2Frac(double n)
{
	Point ab;
	int m = 0;
	bool Got = false;
	while (!Got)
	{
		double Div = (1.0 * m) / n; if (n == m / round(Div)) { ab.x = m; ab.y = round(Div); Got = true; } ++m;
		if (m > 999999999) { cout << "Numero muito grande!\n"; ab.x = 1; ab.y = 1; Got = true; }
	}
	return(ab);
}

// INDICE DAS LETRAS:
int LetterIndex(char C)
{
	if (IsNmbr(C)) { return(Chr2Int(C)); }	if (C == 'a' || C == 'A') { return(1); }
	else if (C == 'b' || C == 'B') { return(2); } else if (C == 'c' || C == 'C') { return(3); }
	else if (C == 'd' || C == 'D') { return(4); } else if (C == 'e' || C == 'E') { return(5); }
	else if (C == 'f' || C == 'F') { return(6); } else if (C == 'g' || C == 'G') { return(7); }
	else if (C == 'h' || C == 'H') { return(8); } else if (C == 'i' || C == 'I') { return(9); }
	else if (C == 'j' || C == 'J') { return(10); } else if (C == 'k' || C == 'K') { return(11); }
	else if (C == 'l' || C == 'L') { return(12); } else if (C == 'm' || C == 'M') { return(13); }
	else if (C == 'n' || C == 'N') { return(14); } else if (C == 'o' || C == 'O') { return(15); }
	else if (C == 'p' || C == 'P') { return(16); } else if (C == 'q' || C == 'Q') { return(17); }
	else if (C == 'r' || C == 'R') { return(18); } else if (C == 's' || C == 'S') { return(19); }
	else if (C == 't' || C == 'T') { return(20); } else if (C == 'u' || C == 'U') { return(21); }
	else if (C == 'v' || C == 'V') { return(22); } else if (C == 'w' || C == 'W') { return(23); }
	else if (C == 'x' || C == 'X') { return(24); } else if (C == 'y' || C == 'Y') { return(25); }
	else if (C == 'z' || C == 'Z') { return(26); }
}
char LetterIndex(int Index, bool Capital)
{
	if (Index > 26) { return('Z'); } if (Index < 1) { return('A'); }
	if (Index == 1) { if (!Capital) { return('a'); } else { return('A'); } }
	else if (Index == 2) { if (!Capital) { return('b'); } else { return('B'); } } else if (Index == 3) { if (!Capital) { return('c'); } else { return('C'); } }
	else if (Index == 4) { if (!Capital) { return('d'); } else { return('D'); } } else if (Index == 5) { if (!Capital) { return('e'); } else { return('E'); } }
	else if (Index == 6) { if (!Capital) { return('f'); } else { return('F'); } } else if (Index == 7) { if (!Capital) { return('g'); } else { return('G'); } }
	else if (Index == 8) { if (!Capital) { return('h'); } else { return('H'); } } else if (Index == 9) { if (!Capital) { return('i'); } else { return('I'); } }
	else if (Index == 10) { if (!Capital) { return('j'); } else { return('J'); } } else if (Index == 11) { if (!Capital) { return('k'); } else { return('K'); } }
	else if (Index == 12) { if (!Capital) { return('l'); } else { return('L'); } } else if (Index == 13) { if (!Capital) { return('m'); } else { return('M'); } }
	else if (Index == 14) { if (!Capital) { return('n'); } else { return('N'); } } else if (Index == 15) { if (!Capital) { return('o'); } else { return('O'); } }
	else if (Index == 16) { if (!Capital) { return('p'); } else { return('P'); } } else if (Index == 17) { if (!Capital) { return('q'); } else { return('Q'); } }
	else if (Index == 18) { if (!Capital) { return('r'); } else { return('R'); } } else if (Index == 19) { if (!Capital) { return('s'); } else { return('S'); } }
	else if (Index == 20) { if (!Capital) { return('t'); } else { return('T'); } } else if (Index == 21) { if (!Capital) { return('u'); } else { return('U'); } }
	else if (Index == 22) { if (!Capital) { return('v'); } else { return('V'); } } else if (Index == 23) { if (!Capital) { return('w'); } else { return('W'); } }
	else if (Index == 24) { if (!Capital) { return('x'); } else { return('X'); } } else if (Index == 25) { if (!Capital) { return('y'); } else { return('Y'); } }
	else if (Index == 26) { if (!Capital) { return('z'); } else { return('Z'); } }
}

// PEGA CASAS DECIMAIS:
double GetDec(double x) { return(x - floor(x)); }

// CONVERSORES:
vector<float> Int2Float(vector<int> Int) { vector<float> V; for (int n = 0; n < Int.size(); ++n) { V.push_back(Int[n]); } return(V); }
vector<int> Float2Int(vector<float> Float) { vector<int> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
vector<double> Float2Double(vector<float> Float) { vector<double> V; for (int n = 0; n < Float.size(); ++n) { V.push_back(Float[n]); } return(V); }
vector<float> Double2Float(vector<double> Double) { vector<float> V; for (int n = 0; n < Double.size(); ++n) { V.push_back(Double[n]); } return(V); }

// ################################################# FIM ####################################################################################

// ############## VETORES  ##############
// QUICKSORT:
void QuickSort(vector<int>& V, int l, int r)
{ if (l >= r) { return; } int pivot = V[r]; int cnt = l; for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { swap(V[cnt], V[i]); ++cnt; } } QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r); }
void QuickSort(vector<double>& V, int l, int r)
{ if (l >= r) { return; } double pivot = V[r]; int cnt = l; for (int i = l; i <= r; ++i) { if (V[i] <= pivot) { swap(V[cnt], V[i]); ++cnt; } } QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r); }
void QuickSortPtx(vector<PointFlt>& V, int l, int r)
{ if (l >= r) { return; } double pivot = V[r].x; int cnt = l; for (int i = l; i <= r; ++i) { if (V[i].x <= pivot) { swap(V[cnt].x, V[i].x); swap(V[cnt].y, V[i].y); ++cnt; } } QuickSortPtx(V, l, cnt - 2); QuickSortPtx(V, cnt, r); }
void QuickSortPty(vector<PointFlt>& V, int l, int r)
{ if (l >= r) { return; } double pivot = V[r].y; int cnt = l; for (int i = l; i <= r; ++i) { if (V[i].y <= pivot) { swap(V[cnt].x, V[i].x); swap(V[cnt].y, V[i].y); ++cnt; } } QuickSortPty(V, l, cnt - 2); QuickSortPty(V, cnt, r); }

// UNE VETORES:
vector<int> JoinVectors(vector<int> VecPre, vector<int> VecSuf) { vector<int> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<float> JoinVectors(vector<float> VecPre, vector<float> VecSuf) { vector<float> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<double> JoinVectors(vector<double> VecPre, vector<double> VecSuf)
{ vector<double> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<char> JoinVectors(vector<char> VecPre, vector<char> VecSuf) { vector<char> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<string> JoinVectors(vector<string> VecPre, vector<string> VecSuf)
{ vector<string> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }
vector<bool> JoinVectors(vector<bool> VecPre, vector<bool> VecSuf) { vector<bool> Vec = VecPre; for (int n = 0; n < VecSuf.size(); ++n) { Vec.push_back(VecSuf[n]); } return(Vec); }

// MÁXIMO E MINIMO DE VETOR:
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
	Point max(VecPoint[0]), min(VecPoint[0]);
	for (size_t n = 1; n < VecPoint.size(); ++n)
	{
		if (VecPoint[n].x > max.x) max.x = VecPoint[n].x; else if (VecPoint[n].x < min.x) min.x = VecPoint[n].x;
		if (VecPoint[n].y > max.y) max.y = VecPoint[n].y; else if (VecPoint[n].y < min.y) min.y = VecPoint[n].y;
	}
	if (Abs) // Construção
	{
		int absx, absy;
		bool absxb = false, absyb = false;
		if (Abs)
		{
			if (min.x < 0) { absx = abs(min.x); max.x += absx; min.x = 0; absxb = true; }
			if (min.y < 0) { absy = abs(min.y); max.y += absy; min.y = 0; absyb = true; }
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
	Max = max; Min = min;
}
void MaxMinVecLinePoint(vector<LinePoint>& VecLinePoint, LinePoint& Max, LinePoint& Min, bool Abs)
{
	LinePoint max(VecLinePoint[0]), min(VecLinePoint[0]);
	for (size_t n = 1; n < VecLinePoint.size(); ++n)
	{
		if (VecLinePoint[n].x0 > max.x0) max.x0 = VecLinePoint[n].x0; else if (VecLinePoint[n].x0 < min.x0) min.x0 = VecLinePoint[n].x0;
		if (VecLinePoint[n].y0 > max.y0) max.y0 = VecLinePoint[n].y0; else if (VecLinePoint[n].y0 < min.y0) min.y0 = VecLinePoint[n].y0;
		if (VecLinePoint[n].x1 > max.x1) max.x1 = VecLinePoint[n].x1; else if (VecLinePoint[n].x1 < min.x1) min.x1 = VecLinePoint[n].x1;
		if (VecLinePoint[n].y1 > max.y1) max.y1 = VecLinePoint[n].y1; else if (VecLinePoint[n].y1 < min.y1) min.y1 = VecLinePoint[n].y1;
	}
	if (Abs) // Construção
	{
		int absx, absy;
		bool absxb0 = false, absyb0 = false, absxb1 = false, absyb1 = false;
		if (Abs)
		{
			if (min.x0 < 0) { absx = abs(min.x0); max.x0 += absx; min.x0 = 0; absxb0 = true; }
			if (min.y0 < 0) { absy = abs(min.y0); max.y0 += absy; min.y0 = 0; absyb0 = true; }
			if (min.x0 < 0) { absx = abs(min.x0); max.x0 += absx; min.x0 = 0; absxb1 = true; }
			if (min.y0 < 0) { absy = abs(min.y0); max.y0 += absy; min.y0 = 0; absyb1 = true; }
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
	Max = max; Min = min;
}

// SOMA/MULTIPLICA DADOS:
int SumVec(vector<int> Vec) { int Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
double SumVec(vector<double> Vec) { double Sum = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Sum += Vec[n]; } return(Sum); }
int MultVec(vector<int> Vec) { int Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); } // Procure não ter zeros
double MultVec(vector<double> Vec) { double Mult = Vec[0]; for (int n = 1; n < Vec.size(); ++n) { Mult *= Vec[n]; } return(Mult); }

// POWER VECOTR TERMS:
vector<int> PowVec(vector<int> Vec, int Pow) { vector<int> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }
vector<double> PowVec(vector<double> Vec, double Pow) { vector<double> V; for (int n = 0; n < Vec.size(); ++n) { V.push_back(pow(Vec[n], Pow)); } return(V); }

// Two vectors:
void SumVecTerms(vector<int>& Vec, int Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void SumVecTerms(vector<double>& Vec, double Sum) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum; } }
void MultVecTerms(vector<int>& Vec, double Mult) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult; } } // Procure não ter zeros
void MultVecTerms(vector<double>& Vec, double Mult) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult; } }

// Seq. & Series:
void SumVecTermsArith(vector<int>& Vec, int Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } }
void SumVecTermsArith(vector<double>& Vec, double Sum, double Diff) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum + (n * Diff); } }
void MultVecTermsArith(vector<int>& Vec, double Mult, double Diff) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } } // Procure não ter zeros
void MultVecTermsArith(vector<double>& Vec, double Mult, double Diff) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult + (n * Diff); } }
void SumVecTermsGeo(vector<int>& Vec, int Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * (n * Ratio); } }
void SumVecTermsGeo(vector<double>& Vec, double Sum, double Ratio) { for (int n = 0; n < Vec.size(); ++n) { Vec[n] += Sum * (n * Ratio); } }
void MultVecTermsGeo(vector<int>& Vec, double Mult, double Ratio) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult * (n * Ratio); } } // Procure não ter zeros
void MultVecTermsGeo(vector<double>& Vec, double Mult, double Ratio) { for (int n = 1; n < Vec.size(); ++n) { Vec[n] *= Mult * (n * Ratio); } }

// Two vectors and vector return:
vector<int> SumTwoVec(vector<int> Vec0, vector<int> Vec1)
{
	vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); } else { Size = Vec1.size(); v0v1 = true; }
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

// ### Operations with Zero:
// Se o segundo vetor tiver um numero no mesmo indice que o primeiro vetor tem um zero, ele substitui o zero pelo valor do indice:
vector<int> SubstituteZero(vector<int> Vec0, vector<int> Vec1)
{
	vector<int> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); } else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<float> SubstituteZero(vector<float> Vec0, vector<float> Vec1)
{
	vector<float> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); } else { Size = Vec1.size(); v0v1 = true; }
	for (int n = 0; n < Size; ++n) { if (Vec0[n] != 0) { V.push_back(Vec0[n]); } else { V.push_back(Vec1[n]); } }
	if (!v0v1) { if (Vec1.size() - Size > 0) { for (int n = Size; n < Vec1.size(); ++n) { V.push_back(Vec1[n]); } } }
	else { if (Vec0.size() - Size > 0) { for (int n = Size; n < Vec0.size(); ++n) { V.push_back(Vec0[n]); } } }
	return(V);
}
vector<double> SubstituteZero(vector<double> Vec0, vector<double> Vec1)
{
	vector<double> V; bool v0v1 = false;
	int Size = 0; if (Vec0.size() <= Vec1.size()) { Size = Vec0.size(); } else { Size = Vec1.size(); v0v1 = true; }
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

// PEGA MARGEM DE EXPONENTE:
vector<long> PowerOfn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(n, a)); } return(Vec); }
vector<long> PowerByn(double n, int From, int To) { vector<long> Vec; for (int a = From; a <= To; ++a) { Vec.push_back(pow(a, n)); } return(Vec); }
vector<double> nRootOfm(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(m, 1.0 / n)); }	return(Vec); }
vector<double> mRootOfn(double n, int m1, int m2) { vector<double> Vec; for (int m = m1; m <= m2; ++m) { Vec.push_back(pow(n, 1.0 / m)); } return(Vec); }

// ################################################# FIM ####################################################################################

// ############## DADOS  ##############
// PEGA LINHAS DE .TXT E RETORNA EM UM VETOR:
vector<double> DataTextLine(string File)
{
	vector<double> Ret;
	string Line;
	ifstream Data(File); if (!Data.is_open()) { cout << "! DADOS NÃO FORAM ABERTOS !\n"; }
	else { while (getline(Data, Line)) { Ret.push_back(Str2Dec(Line)); } } Data.close();
	return(Ret);
}

// PEGA ITEM (UM DOUBLE) DE .TXT E RETORNA EM UM VETOR:
vector<double> DataTextItem(string File)
{
	vector<double> Ret;
	ifstream Data(File); if (!Data.is_open()) { cout << "! DADOS NÃO FORAM ABERTOS !\n"; }
	else { while (!Data.eof()) { double Db; Data >> Db; Ret.push_back(Db); } } Data.close();
	return(Ret);
}

// COUT TEXTO:
void CoutText(string Filename)
{
	string Line; ifstream Data(Filename); if (!Data.is_open()) { cout << "! DADOS NÃO FORAM ABERTOS !\n"; }
	else { while (getline(Data, Line)) { cout << Line << endl; } } Data.close();
}

// COUT DE UM VETOR:
void CoutVector(vector<int> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<long> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<float> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<double> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<bool> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<string> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<char> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ": " << Vec[n] << endl; } }
void CoutVector(vector<Point> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << endl; } }
void CoutVector(vector<PointFlt> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << endl; } }
void CoutVector(vector<Point3D> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << endl; } }
void CoutVector(vector<Point3DFlt> Vec) { for (int n = 0; n < Vec.size(); ++n) { cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << endl; } }

// ################################################# FIM ####################################################################################

// ############## CLASSES ##############
// KERNEL PARA CONVOLUÇÃO DE MATRIZES:
class MatrixKernel
{
public:
	int i, j; // Begins on '1'
	Point Mid = { 1, 1 };
	vector<double> Datas;
	vector<double> Output;

	// FAZ KERNEL VAZIO:
	MatrixKernel(int Matrixi, int Matrixj)
	{
		if (Matrixi < 1) { Matrixi = 1; } if (Matrixj < 1) { Matrixj = 1; }
		i = Matrixi; j = Matrixj; Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		vector<double> V(i * j); Datas = V;
		for (int n = 0; n < (i * j) - 1; ++n) { Datas[n] = 1; }
	}

	// FAZ KERNEL ATRAVEZ DE UM VETOR E O TAMANHO DE UMA LINHA (j):
	MatrixKernel(vector<double> MatrixInput, int Matrixj)
	{
		if (Matrixj > MatrixInput.size()) { j = MatrixInput.size(); } if (Matrixj < 1) { j = 1; } else { j = Matrixj; }
		i = ceil(MatrixInput.size() / (j * 1.0));
		Datas = MatrixInput;
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
	}

	// FAZ O TRABALHO DE SOMAR:
	void Sum(vector<double> Input, int Inj, bool UseAreaRatio, bool SubArea, bool ReciprocalRatio, bool IgnoreNeg, bool InvertNegSub)
	{
		if (Inj > Input.size()) { Inj = Input.size(); }	if (Inj < 1) { Inj = 1; }
		int Ini = ceil(Input.size() / (Inj * 1.0));
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		//cout << "### Mid.x: " << Mid.x << " | Mid.y: " << Mid.y << endl;
		vector<double> Out;
		//cout << "####### i = " << i << " | j = " << j << "\nInput i = " << Ini << " | Input j = " << Inj << "\n#######\n";
		if (Input.size() >= Datas.size() && Inj >= j && Ini >= i)
		{
			for (int n = 0; n < Ini; ++n)
			{
				for (int m = 0; m < Inj; ++m)
				{
					//cout << "n: " << n << " | m: " << m << endl;
					int Map = m + (Inj * n);
					int Offi0 = 0, Offj0 = 0, Offi = 0, Offj = 0;
					if (n + 1 < i) { Offi0 = abs((n + 1) - i); }
					if (n + 1 > Ini - Mid.y) { Offi = abs((Ini - n) - i); }
					if (m + 1 < Mid.x) { Offj0 = Mid.x - (m + 1); }
					if (m + 1 > Inj - (j - Mid.x)) { Offj = abs((Inj - m) - Mid.x); }
					double Result = 0;
					int Mi = 0;
					for (int k = Offi0; k < i; ++k)
					{
						int Mj = 0; //
						for (int l = Offj0; l < j - Offj; ++l)
						{
							int Posi = Mi, Posj = Mj + m - Mid.x + 1 + Offj0;
							if (n >= i - 1) { Posi += n - (i - 1); }
							int KMap = l + (j * k), InMap = Posj + (Posi * Inj);
							//cout << "k: " << k << " | l: " << l;
							//cout << "k: " << k << " | l: " << l << " | Mi: " << Mi << " | Mj: " << Mj << " | Offi0: " << Offi0 << " | Offj0: " << Offj0;
							//cout << " | Offi: " << Offi << " | Offj: " << Offj << endl;
							//cout << "Posj + (Posi * Inj) = " << Posj << " + (" << Posi << " * " << Inj << ") = " << InMap << endl;
							++Mj;
							int KArea = (i - (Offi + Offi0)) * (j - (Offj + Offj0));
							double AreaRatio = (1.0 / KArea) / (1.0 / (i * j));
							//cout << "Size: " << Datas.size() - 1 << " | Kmap: " << KMap << " | Input Map: " << InMap;
							double Data = Datas[KMap];
							//cout << " | Data: " << Data;
							if (SubArea && !IgnoreNeg) { if (Data >= 0) { Data - ((i * j) - KArea); } }
							if (SubArea && IgnoreNeg) { if (InvertNegSub && Data < 0) { Data *= -1; } Data - ((i * j) - KArea); }
							double Val = Data * Input[InMap];
							//cout << " | Value: " << Val << endl;
							if (UseAreaRatio && !ReciprocalRatio) { Val *= AreaRatio; }
							if (UseAreaRatio && ReciprocalRatio) { Val *= 1.0 / AreaRatio; }
							Result += Val;
						}
						++Mi; //
					}
					//cout << "Result: " << Result << endl;
					Out.push_back(Result);
				}
			}
		}
		Output = Out;
	}

	// FAZ O TRABALHO DE MULTIPLICAR:
	void Multiply(vector<double> Input, int Inj, bool UseAreaRatio, bool SubArea, bool ReciprocalRatio, bool IgnoreNeg, bool InvertNegSub)
	{
		if (Inj > Input.size()) { Inj = Input.size(); }	if (Inj < 1) { Inj = 1; }
		int Ini = ceil(Input.size() / (Inj * 1.0));
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		//cout << "### Mid.x: " << Mid.x << " | Mid.y: " << Mid.y << endl;
		vector<double> Out;
		//cout << "####### i = " << i << " | j = " << j << "\nInput i = " << Ini << " | Input j = " << Inj << "\n#######\n";
		if (Input.size() >= Datas.size() && Inj >= j && Ini >= i)
		{
			for (int n = 0; n < Ini; ++n)
			{
				for (int m = 0; m < Inj; ++m)
				{
					//cout << "n: " << n << " | m: " << m << endl;
					int Map = m + (Inj * n);
					int Offi0 = 0, Offj0 = 0, Offi = 0, Offj = 0;
					if (n + 1 < i) { Offi0 = abs((n + 1) - i); }
					if (n + 1 > Ini - Mid.y) { Offi = abs((Ini - n) - i); }
					if (m + 1 < Mid.x) { Offj0 = Mid.x - (m + 1); }
					if (m + 1 > Inj - (j - Mid.x)) { Offj = abs((Inj - m) - Mid.x); }
					double Result = 1;
					int Mi = 0;
					for (int k = Offi0; k < i; ++k)
					{
						int Mj = 0; //
						for (int l = Offj0; l < j - Offj; ++l)
						{
							int Posi = Mi, Posj = Mj + m - Mid.x + 1 + Offj0;
							if (n >= i - 1) { Posi += n - (i - 1); }
							int KMap = l + (j * k), InMap = Posj + (Posi * Inj);
							//cout << "k: " << k << " | l: " << l;
							//cout << "k: " << k << " | l: " << l << " | Mi: " << Mi << " | Mj: " << Mj << " | Offi0: " << Offi0 << " | Offj0: " << Offj0;
							//cout << " | Offi: " << Offi << " | Offj: " << Offj << endl;
							//cout << "Posj + (Posi * Inj) = " << Posj << " + (" << Posi << " * " << Inj << ") = " << InMap << endl;
							++Mj;
							int KArea = (i - (Offi + Offi0)) * (j - (Offj + Offj0));
							double AreaRatio = (1.0 / KArea) / (1.0 / (i * j));
							//cout << "Size: " << Datas.size() - 1 << " | Kmap: " << KMap << " | Input Map: " << InMap;
							double Data = Datas[KMap];
							//cout << " | Data: " << Data;
							if (SubArea && !IgnoreNeg) { if (Data >= 0) { Data - ((i * j) - KArea); } }
							if (SubArea && IgnoreNeg) { if (InvertNegSub && Data < 0) { Data *= -1; } Data - ((i * j) - KArea); }
							double Val = Data * Input[InMap];
							//cout << " | " << Val;
							if (UseAreaRatio && !ReciprocalRatio) { Val *= AreaRatio; }
							if (UseAreaRatio && ReciprocalRatio) { Val *= 1.0 / AreaRatio; }
							Result *= Val; bool Neg = false; if (Val < 0) { Neg = true; }
							Result = sqrt(fabs(Result)); if (Neg) { Result *= -1;}
						}
						++Mi; //
					}
					//cout << endl;
					//cout << "Result: " << Result << endl;
					Out.push_back(Result);
				}
			}
		}
		Output = Out;
	}

};

// ################################################# FIM ####################################################################################

// ############## MISC. ##############
// GEMATRIA:
int Char2Gematria(char C)
{
	if (IsNmbr(C)) { return(Chr2Int(C)); }	if (C == 'a' || C == 'A') { return(1); } else if (C == 'b' || C == 'B') { return(2); }
	else if (C == 'c' || C == 'C') { return(3); } else if (C == 'd' || C == 'D') { return(4); } else if (C == 'e' || C == 'E') { return(5); }
	else if (C == 'f' || C == 'F') { return(6); } else if (C == 'g' || C == 'G') { return(7); } else if (C == 'h' || C == 'H') { return(8); }
	else if (C == 'i' || C == 'I') { return(9); } else if (C == 'j' || C == 'J') { return(1); } else if (C == 'k' || C == 'K') { return(2); }
	else if (C == 'l' || C == 'L') { return(3); } else if (C == 'm' || C == 'M') { return(4); } else if (C == 'n' || C == 'N') { return(5); }
	else if (C == 'o' || C == 'O') { return(6); } else if (C == 'p' || C == 'P') { return(7); } else if (C == 'q' || C == 'Q') { return(8); }
	else if (C == 'r' || C == 'R') { return(9); } else if (C == 's' || C == 'S') { return(1); } else if (C == 't' || C == 'T') { return(2); }
	else if (C == 'u' || C == 'U') { return(3); } else if (C == 'v' || C == 'V') { return(4); } else if (C == 'w' || C == 'W') { return(5); }
	else if (C == 'x' || C == 'X') { return(6); } else if (C == 'y' || C == 'Y') { return(7); } else if (C == 'z' || C == 'Z') { return(8); }
	else { return(0); }
}
double Char2GemaPerCent(char C) // VEJA, DEPOIS DE L 12, M É 15
{
	if (IsNmbr(C)) { return(Chr2Int(C) / 10.0); } if (C == 'a') { return(1 / 56.0); } else if (C == 'b') { return(2 / 56.0); }
	else if (C == 'c') { return(3 / 56.0); } else if (C == 'A') { return(0.5 + (1 / 56.0)); } else if (C == 'B') { return(0.5 + (2 / 56.0)); }
	else if (C == 'C') { return(0.5 + (3 / 56.0)); } if (C == 'd') { return(4 / 56.0); } else if (C == 'e') { return(5 / 56.0); }
	else if (C == 'f') { return(6 / 56.0); } else if (C == 'D') { return(0.5 + (4 / 56.0)); } else if (C == 'E') { return(0.5 + (5 / 56.0)); }
	else if (C == 'F') { return(0.5 + (6 / 56.0)); } if (C == 'g') { return(7 / 56.0); } else if (C == 'h') { return(8 / 56.0); }
	else if (C == 'i') { return(9 / 56.0); } else if (C == 'G') { return(0.5 + (7 / 56.0)); } else if (C == 'H') { return(0.5 + (8 / 56.0)); }
	else if (C == 'I') { return(0.5 + (9 / 56.0)); } if (C == 'j') { return(10 / 56.0); } else if (C == 'k') { return(11 / 56.0); }
	else if (C == 'l') { return(12 / 56.0); } else if (C == 'J') { return(0.5 + (10 / 56.0)); } else if (C == 'K') { return(0.5 + (11 / 56.0)); }
	else if (C == 'L') { return(0.5 + (12 / 56.0)); } if (C == 'm') { return(15 / 56.0); } else if (C == 'n') { return(16 / 56.0); }
	else if (C == 'o') { return(17 / 56.0); } else if (C == 'M') { return(0.5 + (15 / 56.0)); } else if (C == 'N') { return(0.5 + (16 / 56.0)); }
	else if (C == 'O') { return(0.5 + (17 / 56.0)); } if (C == 'p') { return(18 / 56.0); } else if (C == 'q') { return(19 / 56.0); }
	else if (C == 'r') { return(20 / 56.0); } else if (C == 'P') { return(0.5 + (18 / 56.0)); }
	else if (C == 'Q') { return(0.5 + (19 / 56.0)); }
	else if (C == 'r') { return(20 / 56.0); } else if (C == 'P') { return(0.5 + (18 / 56.0)); } else if (C == 'Q') { return(0.5 + (19 / 56.0)); }
	else if (C == 'R') { return(0.5 + (20 / 56.0)); } if (C == 's') { return(21 / 56.0); } else if (C == 't') { return(22 / 52.02); }
	else if (C == 'u') { return(23 / 56.0); } else if (C == 'S') { return(0.5 + (21 / 56.0)); } else if (C == 'T') { return(0.5 + (22 / 56.0)); }
	else if (C == 'U') { return(0.5 + (23 / 56.0)); } if (C == 'v') { return(24 / 56.0); } else if (C == 'w') { return(25 / 52.05); }
	else if (C == 'x') { return(26 / 56.0); } else if (C == 'V') { return(0.5 + (24 / 56.0)); } else if (C == 'W') { return(0.5 + (25 / 56.0)); }
	else if (C == 'X') { return(0.5 + (26 / 56.0)); } if (C == 'y') { return(27 / 56.0); } else if (C == 'z') { return(28 / 56.0); }
	if (C == 'Y') { return(0.5 + (27 / 56.0)); } else if (C == 'Z') { return(0.5 + (28 / 56.0)); }
	else { return(0); }
}

int Str2Gematria(string S) { int Ret = 0; for (int n = 0; n < S.size(); ++n) { Ret += Char2Gematria(S[n]); } return(Ret); }
double Str2GemaPerCent(string S) { double Ret = 0; for (int n = 0; n < S.size(); ++n) { Ret += Char2GemaPerCent(S[n]); } Ret /= S.size(); return(Ret); }

// ALPHA OMEGA POLAR SSCORE:
double AOScore(double Radian)
{
	double Score = 0;
	double Sin = sin(Radian), Cos = cos(Radian);
	Score += Sin; // Eixo Vertical recebe bonus alpha
	Score += Cos * 0.5; // Eixo Horizontal recebe bonus omega, mas menos bonus
	if (Sin > 0) { Sin *= 1.25; } if (Cos < 0) { Cos *= 1.25; } // Eixo "Vertical" é "Alpha", "Horizontal" é "Omega"
	Score += Sin; Score += Cos;
	return (Score / 2.704162); // Melhor aproximação que cheguei, não importa muito mesmo, o que importa é a razão perante outros, e esta confirmado que funciona
}

// ################################################# FIM ####################################################################################

// ############## RANDOM ##############
// RANDOM-N FOR M-TIMES:
vector<int> Randomnm(int n, int m) { vector<int> rndret; for (int a = 0; a < m; ++a) { rndret.push_back(rand() % n); } return(rndret); }

// RANDOM N TIMES:
vector<Point> RandomDominoes(int Tries) { vector<Point> Pts; for (int a = 0; a < Tries; ++a) { Point Pt; Pt.x = rand() % 7; Pt.y = rand() % 7; Pts.push_back(Pt); } return(Pts); }

// RANDOM CARD:
vector<NameValue> RandomCard(int Tries)
{
	vector<NameValue>Cards;
	NameValue Card;
	for (int a = 0; a < Tries; ++a)
	{
		Card.Value = (rand() % 13) + 1;
		int Naipe = rand() % 4; if (Naipe == 0) { Card.Name = "Hearts"; } else if (Naipe == 1) { Card.Name = "Diamonds"; }
		else if (Naipe == 2) { Card.Name = "Spades"; } else { Card.Name = "Clubs"; }
		if (Card.Value == 13) { Card.Name += " - King"; } if (Card.Value == 12) { Card.Name += " - Queen"; } if (Card.Value == 11) { Card.Name += " - Jack"; }
		Cards.push_back(Card);
	}
	return(Cards);
}

// RANDOM TAROT:
vector<NameValue> RandomTarot(int Tries)
{
	vector<NameValue>Cards;
	NameValue Card;
	for (int a = 0; a < Tries; ++a)
	{
		int Rnd = (rand() % 78) + 1;
		bool MinMaj = false; // Minor or Major Arcana?
		if (Rnd > 22) { MinMaj = false; }
		else { MinMaj = true; }
		if (MinMaj) { Card.Name = TarotCards[Rnd - 1]; Card.Value = Rnd; Cards.push_back(Card); }
		else
		{
			Card.Value = (rand() % 14) + 1;
			int Naipe = rand() % 4; if (Naipe == 0) { Card.Name = "Cups"; }
			else if (Naipe == 1) { Card.Name = "Pentacles"; }
			else if (Naipe == 2) { Card.Name = "Spades"; }
			else { Card.Name = "Wand"; }
			if (Card.Value == 14) { Card.Name += " - King"; }
			if (Card.Value == 13) { Card.Name += " - Queen"; }
			if (Card.Value == 12) { Card.Name += " - Knight"; }
			if (Card.Value == 11) { Card.Name += " - Page"; }
			Cards.push_back(Card);
		}
	}
	return(Cards);
}

// RANDOM PSALM:
vector<int> RandomPSalm(int Tries) { vector<int> PSs; int PS; for (int a = 0; a < Tries; ++a) { PS = (rand() % 150) + 1; PSs.push_back(PS); } return(PSs); }

// RANDOM ICHING:
vector<int> RandomIChing(int Tries) { vector<int> ICs; int IC; for (int a = 0; a < Tries; ++a) { IC = (rand() % 64) + 1; ICs.push_back(IC); } return(ICs); }

// ################################################# FIM ####################################################################################

class TestIt
{
	public: 
		void TestMath()
		{
			cout << "0 = Aqui | 1 = Geo | 2 = Calculus | 3 = Fisica\n";
			int Choice = 0; cin >> Choice;
			if (Choice == 1) { TestGeo tst; tst.Test(); } if (Choice == 2) { TestCalc tst; tst.Test(); } if (Choice == 3) { TestPhis tst; tst.Test(); }
			if (Choice == 0)
			{
				cout << "Digite qual função:\n";
				cout << "| 1 = Testa primo | 2 = Char to integer | 3 = String to integer |\n";
				cout << "| 4 = Str2Dec | 5 = IsDec? | 6 = Dec2Frac |\n";
				cout << "| 7 = BinomialCoff | 8 = Perm. no rep.\n";
				cout << "| 9 = Quadratic Eq. | 10 = GDC | 11 = LCM | 12 Tri. Number |\n";
				int Op; cin >> Op;

				if (Op == 1) { cout << "IsPrime(n);\n"; long Opn; cout << "n: "; cin >> Opn; cout << "RETORNO: " << IsPrime(Opn) << endl; }
				if (Op == 2) { cout << "Chr2Int(C);\n"; char Opc; cout << "Char: "; cin >> Opc; cout << "RETORNO: " << Chr2Int(Opc) << endl; }
				if (Op == 3) { cout << "Str2Int(S);\n"; string Ops; cout << "String: "; cin >> Ops; cout << "RETORNO: " << Str2Int(Ops) << endl; }
				if (Op == 4) { cout << "Str2Dec(S);\n"; string Ops; cout << "String: "; cin >> Ops; cout << "RETORNO: " << Str2Dec(Ops) << endl; }
				if (Op == 5) { cout << "IsDec(S);\n"; string Ops; cout << "String: "; cin >> Ops; cout << "RETORNO: " << IsDec(Ops) << endl; }
				if (Op == 6)
				{
					cout << "Dec2Frac(n, &a, &b);\n"; double Opn; cout << "n: "; cin >> Opn; int Opa = Dec2Frac(Opn).x, Opb = Dec2Frac(Opn).y;
					cout << "RETORNO: " << Opa << " / " << Opb << endl;
				}
				if (Op == 7)
				{ cout << "BinomialCoff(n, k);\n"; int Opn, Opk; cout << "n: "; cin >> Opn; cout << "k: "; cin >> Opk; cout << "RETORNO: " << BinomialCoff(Opn, Opk) << endl; }
				//if (Op == 8)
				//{
				//	cout << "PermNoRep(n, r);\n"; int Opn, Opr; cout << "n: "; cin >> Opn; cout << "r: "; cin >> Opr; cout << "RETORNO: " << PermNoRep(Opn, Opr) << endl;
				//}
				if (Op == 9)
				{
					cout << "QuadraticEq(a, b, c);\n"; int Opa, Opb, Opc; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
					cout << "RETORNO: x1 = " << QuadraticEq(Opa, Opb, Opc).x << " | x2 = " << QuadraticEq(Opa, Opb, Opc).y << endl;
				}
				if (Op == 10)
				{
					cout << "GCD(n, k);\n"; int Opa, Opb; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << GCD(Opa, Opb) << endl;
				}
				if (Op == 11)
				{
					cout << "LCM(n, k);\n"; int Opa, Opb; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << LCM(Opa, Opb) << endl;
				}
				if (Op == 12)
				{
					cout << "TriNmbr(n, k);\n"; int Op; cout << "n: "; cin >> Op; cout << "RETORNO: " << TriNmbr(Op) << endl;
				}
			}
		}
		void TestRandom(int Rnd, int Tries)
		{
			vector<int> RandomVec = Randomnm(Rnd, Tries);
			for (int n = 0; n < RandomVec.size(); ++n) { cout << "Random[" << n << "] + 1: " << RandomVec[n] + 1 << endl; }

			int Resto; cout << "Ver outros randoms? "; cin >> Resto;
			if (Resto != 0)
			{
				vector<NameValue> Cards = RandomCard(Tries);
				for (int n = 0; n < Cards.size(); ++n) { cout << "Cards[" << n << "].Name: " << Cards[n].Name << " | Cards[" << n << "].Value: " << Cards[n].Value << endl; }
				vector<Point> Dominoes = RandomDominoes(Tries);
				for (int n = 0; n < Dominoes.size(); ++n) { cout << "Dominoes[" << n << "].x: " << Dominoes[n].x << " | Dominoes[" << n << "].y: " << Dominoes[n].y << endl; }
				vector<NameValue> Tarots = RandomTarot(Tries);
				for (int n = 0; n < Tarots.size(); ++n) { cout << "Tarots[" << n << "].Name: " << Tarots[n].Name << " | Tarots[" << n << "].Value: " << Tarots[n].Value << endl; }
				vector<int> Ichings = RandomIChing(Tries);
				for (int n = 0; n < Ichings.size(); ++n) { cout << "Ichings[" << n << "]: " << Ichings[n] << endl; }
				vector<int> PSalms = RandomPSalm(Tries);
				for (int n = 0; n < PSalms.size(); ++n) { cout << "PSalms[" << n << "]: " << PSalms[n] << endl; }
			}
		}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
