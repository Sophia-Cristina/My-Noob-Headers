#pragma once

#ifndef YSXMATH_H
#define YSXMATH_H

// #####################
// ####### By Sophia Cristina
// ####### Header made to deal with technical aspects of math stuffs.
// ####### It also contain some math formulaes...
// ####### But you should check below some internal includes.
// #####################

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

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// !!!!!!!	
// !!!!!!!	CHANGES (KEEP ORDER):
// !!!!!!!	* Function 'IsNumber' was called 'IsNmbr';
// !!!!!!!	* 'Str2cArray' is now 'Str2cPt' and 'Str2ucPt' in 'ysxBytes.h';
// !!!!!!!	
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #####################################################################################################################################
// ############## FORWARD DECLARATIONS ##############
// Extern:
double SphereSurf(double);
double WaveLgh(double, double);
double MiniForm(double, double);
double Derivative(double, double); double Derivative(double, double, double);
double Derivative(double, double, double, double); double Derivative(double, double, double, double, double);
double d2xdt2(double, double);
double LawSinAngle(double, double, double);

// Intern:
int SumVec(std::vector<int>);
double SumVec(std::vector<double>);
int MultVec(std::vector<int>);
double MultVec(std::vector<double>);
std::vector<int> PowVec(std::vector<int>, int);
std::vector<double> PowVec(std::vector<double>, double);
double Average(std::vector<double>);

// #####################################################################################################################################
// ############## TOOLS ##############

// DECLARE OBJECTOS QUE SER�O USADOS EM TODOS OS HEADERS AQUI!

// ####### STRUCTS:
struct Point { int x, y; }; // Coordinates in int
struct PointB { unsigned char x, y; }; // Coordinates in bytes
struct PointFlt { double x, y; }; // Coordinates in flt
struct Point3D { int x, y, z; }; // Coordinates in int 3D
struct Point3DB { unsigned char x, y, z; }; // Coordinates in bytes 3D
struct Point3DFlt { double x, y, z; }; // Coordinates in flt 3D
struct CellBool { int i, j; bool b; }; // Matriz de Bool
struct CellBool3D { int i, j, k; bool b; }; // Matriz de Bool 3D
struct CellInt { int i, j; int n; }; // Matriz de integer
struct CellInt3D { int i, j, k; int n; }; // Matriz de integer
struct CellFlt { int i, j; float x; }; // Matriz de float
struct CellFlt3D { int i, j; float x; }; // Matriz de float
struct LinePoint { Point P0, P1; }; // Para fazer linhas
struct LinePoint3D { Point3D P0, P1; }; // Para fazer linhas

// ####### ABREVIATIONS:
/*
typedef vector<vector<char>>		   Matrix2Dc; // char
typedef vector<vector<int>>			   Matrix2Di; // int
typedef vector<vector<double>>		   Matrix2Df; // float
typedef vector<vector<double>>		   Matrix2Dd; // double
typedef vector<vector<vector<char>>>   Matrix3Dc; // char
typedef vector<vector<vector<int>>>	   Matrix3Di; // int
typedef vector<vector<vector<double>>> Matrix3Df; // float
typedef vector<vector<vector<double>>> Matrix3Dd; // double

unsigned char* Matrix2Dtochar(Matrix2Dc M)
{
	//int Sizex = M.size();
	//int Sizey = M[0].size();
	//unsigned char* m 
}
*/

// #####################################################################################################################################

#include "ysxplg\\ysxConst.h";
#include "ysxplg\\ysxConv.h"
#include "ysxplg\\ysxVector.h";
#include "ysxplg\\ysxPhys.h";
#include "ysxplg\\ysxGeo.h";
#include "ysxplg\\ysxCalc.h";
#include "ysxplg\\ysxElectr.h" // There is signals too, but there is trigonomotry in 'ysxGeo.h'. Also #include 'ysxBytes.h'.
#include "ysxplg\\ysxMusic.h"
#include "ysxplg\\ysxMoney.h"; // Things about money and related to economy and etc...
#include "ysxplg\\ysxFractal.h";

// #####################################################################################################################################

// ############################
// ############################
// ############################

// ############## MATHEMATICS ##############

// ############################
// ####### MULTIPLES OR DIVISORS:
// GCD (GREATEST COMMON DIVISOR):
int GCD(int a, int b)
{
	a = abs(a); b = abs(b);
	if (b == a) { return (a); } if (b > a) { int tmp = a; a = b; b = tmp; }
	int Mod = a % b, ModDiv = b, ActualMod;
	if (b == 0) { return (a); } else { while (Mod != 0) { ActualMod = ModDiv % Mod; ModDiv = Mod; Mod = ActualMod; } return (ModDiv); }
}

// LCM (LEAST COMMON MULTIPLE):
int LCM(int a, int b) { a = abs(a); b = abs(b); return ((a * b) / GCD(a, b)); }

// FACTORS:
std::vector<int> Factors(int n) { std::vector<int> V; for (int m = 1; m <= n; ++m) { if (0 == n % m) { V.push_back(m); } } return (V); }

// DIVISOR FUNCTION (When x is 1, the function is called the sigma function or sum - of - divisors function)
int DivFunc(int n, int Power) { std::vector<int> Fac = PowVec(Factors(n), Power); int Sum = SumVec(Fac); return(Sum); }

// ####### AVERAGES AND RATIOS:
// M�DIA, ARITHMETIC MEAN:
double Average(std::vector<double> Vec) { double Sum = 0; if (Vec.size() != 0) { for (int n = 0; n < Vec.size(); ++n) { Sum += Vec[n]; } Sum /= Vec.size(); } return (Sum); }

// ROOT MEAN SQUARE:
double RMS(std::vector<double> Vec) { double Sum = 0; int n = Vec.size(); if (n != 0) { for (int i = 0; i < n; ++i) { Sum += Vec[i] * Vec[i]; } Sum /= n; } return (sqrt(Sum)); }

// HARMONIC MEAN:
double HarmMean(std::vector<double> Vec) { double Sum = 0; int n = Vec.size(); if (n != 0) { for (int i = 0; i < n; ++i) { Sum += 1.0 / Vec[i]; } n /= Sum; } return (n); }

// GEOMETRIC MEAN:
double GeoMean(std::vector<double> Vec)
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
double PowerMean(std::vector<double> Vec, double p)
{ double Sum = 0; int n = Vec.size(); for (int i = 0; i < n; ++i) { Sum += pow(Vec[i], p); } Sum *= 1.0 / n; Sum = pow(Sum, 1 / p); return(Sum); }

// RATIO BETWEEN TWO RATIOS '(a * Rta) / (b * Rtb)' : (Ex.: Beer, a = 350ml, Rta = 0.046; Spirit, b = 50ml, Rtb = 0.39; Return = 0.825641...
double RatioofRatios(double a, double Rta, double b, double Rtb) { return((a * Rta) / (b * Rtb)); }

// RATIO OF THE RATIO '(a * Rto) / a)':
double RatioofRatio(double a, double Rto) { return((a * Rto) / a); }

// SUM OF POWERS (It keeps summing from 'm' to 'n' to the power of 'p' or  it will be summing 'n' from 'p0' to 'p1'):
double SumIniEndtoPow(int Ini, int End, int p) { double Sum = 0; for (int m = Ini; m <= End; ++m) { Sum += pow(m, p); } return (Sum); }
double SumntoPowIniEnd(int n, int Ini, int End) { double Sum = 0; for (int m = Ini; m <= End; ++m) { Sum += pow(n, m); } return (Sum); }

// Take the cube root of 'x^3 + y^3', also remember about integers and 'x^3 + y^3 = z^3':
double CubeofTwoCubes(double x, double y) { return(pow((x * x * x) + (y * y * y), 1.0 / 3)); }

// ############################
// ####### ALGEBRA:
// FACTORIAL:
long long Fact(int a) { int Fact = 1; if (a > 0) { for (int n = 1; n <= a; ++n) { Fact *= n; } return (Fact); } else { return (1); } }

// QUADRATIC EQUATION:
PointFlt QuadraticEq(double a, double b, double c)
{
	PointFlt Root;
	double Delta = b * b - 4 * a * c;
	if (Delta == 0) { Root.x = -b / (2 * a); Root.y = -b / (2 * a);	return(Root); }
	Root.x = (-b + sqrt(Delta)) / (2 * a); Root.y = (-b - sqrt(Delta)) / (2 * a);
	return(Root);
}

// COLLATZ CONJECTURE:
// Creates a vector with each iteration process until the number reaches 1
std::vector<int> CollatzConj(int n)
{
	std::vector<int> V;
	if (n < 1) { V.push_back(1); return(V); }
	else
	{
		int v = n;
		while (v != 1)
		{
			if (v % 2 == 0) { v /= 2; V.push_back(v); }
			else { v = v * 3 + 1; V.push_back(v); }
		}
	}
	return(V);
}

// ############################
// ####### NUMEROS:
// IS IT PRIME?:
bool IsPrime(long n) { n = abs(n); for (int m = 2; m < n - 1; ++m) { if (0 == n % m) { return(false); } } return(true); }

// TRIANGULAR NUMBER:
int TriNmbr(int n) { return ((n * (n + 1)) / 2); }

// FIBO NUMBER:
int GetaFiboNmbr(int Fn)
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
std::vector<int> GetaFiboVec(int Fn) // VEJA SE TA CERTO, VEJA SE n N�O DEVERIA SER 2
{
	if (Fn < 1) { std::vector<int> A; A.push_back(1); return(A); }
	if (Fn == 2) { std::vector<int> A; A.push_back(1); A.push_back(1); return(A); }
	int One = 1, Two = 1;
	std::vector<int> Actual{1, 1};
	for (int n = 3; n <= Fn; ++n)
	{
		Actual.push_back(One + Two);
		One = Two;
		Two = Actual[n - 1];
	}
	return(Actual);
}

// LUCAS NUMBER:
int GetaLucasNmbr(int Ln)
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
std::vector<int> GetaLucasVec(int Ln) // VEJA SE TA CERTO, VEJA SE n N�O DEVERIA SER 2
{
	if (Ln < 1) { std::vector<int> A; A.push_back(2); return(A); }
	if (Ln == 2) { std::vector<int> A; A.push_back(2); A.push_back(1); return(A); }
	int One = 2, Two = 1;
	std::vector<int> Actual{ 2, 1 };
	for (int n = 3; n <= Ln; ++n)
	{
		Actual.push_back(One + Two);
		One = Two;
		Two = Actual[n - 1];
	}
	return(Actual);
}

// ############################
// ####### COMBINATORICS:
// PERMUTATIONS WITHOUT REPETITION:
long long BinomialCoff(int n, int k) { n = abs(n); k = abs(k); long Fct = (n - k) + 1; for (int a = Fct + 1; a <= n; ++a) { Fct *= a; } return(Fct / Fact(k)); }

// COMBINATION:

// PERMUTATIONS WITHOUT REPETITION:
//long long PermNoRep(int n, int r) { n = abs(n); r = abs(r); long fn = Fact(n), fnr = Fact(n - r), Ret = fn / fnr; cout << "fn: " << fn << " | fnr: " << fnr << std::endl;
//cout << "Ret: " << Ret << std::endl; return(Ret); }

// ############################
// ####### EUCLIDEAN VECTOR:
// GET MAGNITUDE:
double GetMag(PointFlt Vector) { return(hipo(fabs(Vector.x), fabs(Vector.y))); }

// GET RADIAN:
double GetVecRad(PointFlt Vector)
{
	double ax = fabs(Vector.x), ay = fabs(Vector.y); double Rad = asin(ay / hipo(ax, ay));
	if (Vector.x >= 0 && Vector.y >= 0) { return (Rad); }
	else if (Vector.x < 0 && Vector.y >= 0) { return (PI - Rad); }
	else if (Vector.x < 0 && Vector.y < 0) { return (PI + Rad); }
	return ((PI * 1.5) + ((0.5 * PI) - Rad));
}

// GET RADIAN BETWEEN TWO VECTORS:
double GetRadBetween(PointFlt A, PointFlt B) { double RadA = GetVecRad(A), RadB = GetVecRad(B); if (RadA > RadB) { return(RadA - RadB); } return(RadB - RadA); }

// SUBTRACT, ADD OR MULTIPLY EUC. VECTOR:
PointFlt SubEucVector(PointFlt A, PointFlt B) { PointFlt C = { A.x - B.x, A.y - B.y }; return(C); }
PointFlt AddEucVector(PointFlt A, PointFlt B) { PointFlt C = { A.x + B.x, A.y + B.y }; return(C); }
PointFlt SclrMultEucVec(PointFlt A, double ScalarMultiplier) { PointFlt B = { A.x * ScalarMultiplier, A.y * ScalarMultiplier }; return(B); }

// DOT PRODUCT:
double DotProd(double AMag, double BMag, double Rad) { return(AMag * BMag * cos(Rad)); }
double DotProd(PointFlt A, PointFlt B) { return((A.x * B.x) + (A.y * B.y)); }

// ################################################# FIM ####################################################################################

// ############################
// ############################
// ############################

// ############################
// ############## TECHNICALS  ##############

// ####### CONVERTERS:
// STRING TO CHAR (should use std::string.data() instead):
std::vector<char> Str2Char(std::string Str)
{
	// char * C; // Oldschool
	int TxtLim = Str.length() + 1;
	// C = new char[TxtLim];
	std::vector<char> C(TxtLim);
	for (int chr = 0; chr < Str.length(); ++chr)
	{
		C[chr] = Str.at(chr);
		if (chr == Str.length() - 1) { C[chr + 1] = '\0'; }
	}
	return(C);
}

std::vector<wchar_t> Str2wChart(std::string Str)
{
	int TxtLim = Str.length() + 1;
	std::vector<wchar_t> C(TxtLim);
	for (int chr = 0; chr < Str.length(); ++chr)
	{
		C[chr] = Str.at(chr);
		if (chr == Str.length() - 1) { C[chr + 1] = '\0'; }
	}
	return(C);
}

// STRING TO CHAR ARRAY:
// * Now on 'ysxBytes.h'

// CHAR VECTOR TO A STRING:
std::string Char2Str(std::vector<char> C) { std::string Str; for (int n = 0; n < C.size(); ++n) { Str.push_back(C[n]); } return (Str); }

// GET A CHAR AS TEXT AND READ AS INTEGER:
int Chr2Int(char C)
{
	int a;
	if (C == '1') { return(1); } if (C == '2') { return(2); } if (C == '3') { return(3); } if (C == '4') { return(4); } if (C == '5') { return(5); }
	if (C == '6') { return(6); } if (C == '7') { return(7); } if (C == '8') { return(8); } if (C == '9') { return(9); } if (C == '0') { return(0); }
}

// GET STRING AS TEXT AND READ AS AN INTEGER:
int Str2Int(std::string S)
{
	int a = 0, Count = 0;
	char C; bool Oktogo = false, Neg = false;
	std::vector<int> Array;
	for (int n = 0; n < S.length(); ++n)
	{
		if (S[n] == '1' || S[n] == '2' || S[n] == '3' || S[n] == '4' || S[n] == '5' || S[n] == '6' || S[n] == '7' || S[n] == '8' || S[n] == '9' || S[n] == '-')
		{
			Oktogo = true;
		} // se n�o for ok antes, e for depois, retornara true
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
	if (Neg) { a *= -1; }
	return(a);
}

// GET STRING AS TEXT AND READ AS A DOUBLE:
double Str2Double(std::string S)
{
	int n = 0;
	std::string Str, Str0;
	while (S[n] != '.' && n < S.length()) { Str.push_back(S[n]); ++n; }
	if (n + 1 < S.length()) { for (int m = n + 1; m < S.length(); ++m) { Str0.push_back(S[m]); } }
	else { Str0 = "0"; }
	int Int = Str2Int(Str), Int2 = Str2Int(Str0);
	return (Int + (Int2 * (1.0 / pow(10, Str0.length()))));
}

// IS DECIMAL?:
bool IsDec(std::string S) { double x = Str2Double(S); if (1.0 == x / round(x)) { return (false); } else { return (true); } }

// DEC2FRAC:
Point Dec2Frac(double n)
{
	Point ab;
	int m = 0;
	bool Got = false;
	while (!Got)
	{
		double Div = (1.0 * m) / n; if (n == m / round(Div)) { ab.x = m; ab.y = round(Div); Got = true; } ++m;
		if (m > 999999999) { break; }
	}
	return(ab);
}

// #####################
// ####### PROPRIEDADES DOS NUMEROS:

// IS NUMBER?:
bool IsNumber(char C) { if (C > 47 && C < 58) { return(true); } return (false); }

// IS LETTER?:
bool IsLetter(char C) { if (C > 64 && C < 91) { std::cout << "C = " << (int)C << std::endl; return(true); } else if (C > 96 && C < 123) { std::cout << "C = " << (int)C << std::endl; return(true); }  return (false); }

// LETTER INDEX:
int LetterIndex(char C)
{
	if (IsNumber(C)) { return(Chr2Int(C)); }	if (C == 'a' || C == 'A') { return(1); }
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

// It means 'String to Int / Double Clean Char', get a string with chars and number,
// filter only the numbers, return it as a int or double:
int Str2IntClnChr(std::string s)
{
	std::string t;
	for (int n = 0; n < s.size(); ++n)
	{
		if (IsNumber(s[n])) { t.push_back(s[n]); }
	}
	return(Str2Int(t));
}
double Str2DblClnChr(std::string s)
{
	std::string t; bool FirstDot = false;
	for (int n = 0; n < s.size(); ++n)
	{
		if (IsNumber(s[n])) { t.push_back(s[n]); }
		else if (!FirstDot && s[n] == '.') { t.push_back(s[n]); FirstDot = true; }
	}
	return(Str2Double(t));
}

// GET DECIMALS:
double GetDec(double x) { return(x - floor(x)); }

// #####################################################################################################################################

// ############################
// ############################
// ############################

// ############## DATAS  ##############
// GET LINES FROM A .TXT AND RETURN AS VECTOR:
std::vector<double> DataTextLine(std::string File)
{
	std::vector<double> Ret;
	std::string Line;
	std::ifstream Data(File); if (!Data.is_open()) { std::cout << "! NOT OPEN !\n"; }
	else { while (getline(Data, Line)) { Ret.push_back(Str2Double(Line)); } } Data.close();
	return(Ret);
}

// GET ITEM (A DOUBLE) FROM A .TXT AND RETURN AS VECTOR:
std::vector<double> DataTextItem(std::string File)
{
	std::vector<double> Ret;
	std::ifstream Data(File); if (!Data.is_open()) { std::cout << "! NOT OPEN !\n"; }
	else { while (!Data.eof()) { double Db; Data >> Db; Ret.push_back(Db); } } Data.close();
	return(Ret);
}

// COUT TEXT:
void CoutText(std::string Filename)
{
	std::string Line; std::ifstream Data(Filename); if (!Data.is_open()) { std::cout << "! NOT OPEN !\n"; }
	else { while (getline(Data, Line)) { std::cout << Line << std::endl; } } Data.close();
}

// COUT VECTOR:
void CoutVector(std::vector<short int> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<int> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<long> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<float> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<double> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<bool> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<std::string> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<char> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; } }
void CoutVector(std::vector<Point> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << std::endl; } }
void CoutVector(std::vector<PointFlt> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << std::endl; } }
void CoutVector(std::vector<Point3D> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << std::endl; } }
void CoutVector(std::vector<Point3DFlt> Vec) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << std::endl; } }
// COUT VECTOR WITH COLLUMS:
void CoutVector(std::vector<short int> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | "; if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<int> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<long> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<float> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<double> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<bool> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<std::string> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<char> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | ";  if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<Point> Vec, int Cols) { for (int n = 0; n < Vec.size(); ++n)
{ std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " "; if (n % Cols == Cols - 1) { std::cout << std::endl; } } }
void CoutVector(std::vector<PointFlt> Vec, int Cols)
{
	int c = 0; for (int n = 0; n < Vec.size(); ++n)
	{
		std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " ";
		++c; if (c == Cols) { std::cout << std::endl; c = 0; }
	}
}
void CoutVector(std::vector<Point3D> Vec, int Cols)
{
	int c = 0; for (int n = 0; n < Vec.size(); ++n)
	{
		std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << " ";
		++c; if (c == Cols) { std::cout << std::endl; c = 0; }
	}
}
void CoutVector(std::vector<Point3DFlt> Vec, int Cols)
{
	int c = 0; for (int n = 0; n < Vec.size(); ++n)
	{
		std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << " ";
		++c; if (c == Cols) { std::cout << std::endl; c = 0; }
	}
}
// COUT STRING AS INT:
void CoutStringInt(std::string Str) { int i; for (int n = 0; n < Str.size(); ++n) { i = Str[n]; std::cout << n << ": " << i << std::endl; } }
void CoutStringInt(std::string Str, int Cols)
{ int i; int c = 0; for (int n = 0; n < Str.size(); ++n) { i = Str[n]; std::cout << n << ": " << i << " "; ++c; if (c == Cols) { std::cout << std::endl; c = 0; } } }

// ################################################# FIM ####################################################################################

// ############################
// ############################
// ############################

// ############## CLASSES ##############
// KERNEL FOR MATRIX CONVOLUTION:
class MatrixKernel
{
public:
	int i, j; // Begins on '1'
	Point Mid = { 1, 1 };
	std::vector<double> Datas;
	std::vector<double> Output;

	// CREATES EMPTY KERNEL:
	MatrixKernel(int Matrixi, int Matrixj)
	{
		if (Matrixi < 1) { Matrixi = 1; } if (Matrixj < 1) { Matrixj = 1; }
		i = Matrixi; j = Matrixj; Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		std::vector<double> V(i * j); Datas = V;
		for (int n = 0; n < (i * j) - 1; ++n) { Datas[n] = 1; }
	}

	// DO KERNEL BY A VECTOR AND THE SIZE OF A LINE (j):
	MatrixKernel(std::vector<double> MatrixInput, int Matrixj)
	{
		if (Matrixj > MatrixInput.size()) { j = MatrixInput.size(); } if (Matrixj < 1) { j = 1; } else { j = Matrixj; }
		i = ceil(MatrixInput.size() / (j * 1.0));
		Datas = MatrixInput;
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
	}

	// MAKE THE SUM JOB:
	void Sum(std::vector<double> Input, int Inj, bool UseAreaRatio, bool SubArea, bool ReciprocalRatio, bool IgnoreNeg, bool InvertNegSub)
	{
		if (Inj > Input.size()) { Inj = Input.size(); }	if (Inj < 1) { Inj = 1; }
		int Ini = ceil(Input.size() / (Inj * 1.0));
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		//std::cout << "### Mid.x: " << Mid.x << " | Mid.y: " << Mid.y << std::endl;
		std::vector<double> Out;
		//std::cout << "####### i = " << i << " | j = " << j << "\nInput i = " << Ini << " | Input j = " << Inj << "\n#######\n";
		if (Input.size() >= Datas.size() && Inj >= j && Ini >= i)
		{
			for (int n = 0; n < Ini; ++n)
			{
				for (int m = 0; m < Inj; ++m)
				{
					//std::cout << "n: " << n << " | m: " << m << std::endl;
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
							//std::cout << "k: " << k << " | l: " << l;
							//std::cout << "k: " << k << " | l: " << l << " | Mi: " << Mi << " | Mj: " << Mj << " | Offi0: " << Offi0 << " | Offj0: " << Offj0;
							//std::cout << " | Offi: " << Offi << " | Offj: " << Offj << std::endl;
							//std::cout << "Posj + (Posi * Inj) = " << Posj << " + (" << Posi << " * " << Inj << ") = " << InMap << std::endl;
							++Mj;
							int KArea = (i - (Offi + Offi0)) * (j - (Offj + Offj0));
							double AreaRatio = (1.0 / KArea) / (1.0 / (i * j));
							//std::cout << "Size: " << Datas.size() - 1 << " | Kmap: " << KMap << " | Input Map: " << InMap;
							double Data = Datas[KMap];
							//std::cout << " | Data: " << Data;
							if (SubArea && !IgnoreNeg) { if (Data >= 0) { Data - ((i * j) - KArea); } }
							if (SubArea && IgnoreNeg) { if (InvertNegSub && Data < 0) { Data *= -1; } Data - ((i * j) - KArea); }
							double Val = Data * Input[InMap];
							//std::cout << " | Value: " << Val << std::endl;
							if (UseAreaRatio && !ReciprocalRatio) { Val *= AreaRatio; }
							if (UseAreaRatio && ReciprocalRatio) { Val *= 1.0 / AreaRatio; }
							Result += Val;
						}
						++Mi; //
					}
					//std::cout << "Result: " << Result << std::endl;
					Out.push_back(Result);
				}
			}
		}
		Output = Out;
	}

	// DO THE MULTIPLICATION JOB:
	void Multiply(std::vector<double> Input, int Inj, bool UseAreaRatio, bool SubArea, bool ReciprocalRatio, bool IgnoreNeg, bool InvertNegSub)
	{
		if (Inj > Input.size()) { Inj = Input.size(); }	if (Inj < 1) { Inj = 1; }
		int Ini = ceil(Input.size() / (Inj * 1.0));
		Point Pt = { ceil(i * 0.5), ceil(j * 0.5) }; Mid = Pt;
		//std::cout << "### Mid.x: " << Mid.x << " | Mid.y: " << Mid.y << std::endl;
		std::vector<double> Out;
		//std::cout << "####### i = " << i << " | j = " << j << "\nInput i = " << Ini << " | Input j = " << Inj << "\n#######\n";
		if (Input.size() >= Datas.size() && Inj >= j && Ini >= i)
		{
			for (int n = 0; n < Ini; ++n)
			{
				for (int m = 0; m < Inj; ++m)
				{
					//std::cout << "n: " << n << " | m: " << m << std::endl;
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
							//std::cout << "k: " << k << " | l: " << l;
							//std::cout << "k: " << k << " | l: " << l << " | Mi: " << Mi << " | Mj: " << Mj << " | Offi0: " << Offi0 << " | Offj0: " << Offj0;
							//std::cout << " | Offi: " << Offi << " | Offj: " << Offj << std::endl;
							//std::cout << "Posj + (Posi * Inj) = " << Posj << " + (" << Posi << " * " << Inj << ") = " << InMap << std::endl;
							++Mj;
							int KArea = (i - (Offi + Offi0)) * (j - (Offj + Offj0));
							double AreaRatio = (1.0 / KArea) / (1.0 / (i * j));
							//std::cout << "Size: " << Datas.size() - 1 << " | Kmap: " << KMap << " | Input Map: " << InMap;
							double Data = Datas[KMap];
							//std::cout << " | Data: " << Data;
							if (SubArea && !IgnoreNeg) { if (Data >= 0) { Data - ((i * j) - KArea); } }
							if (SubArea && IgnoreNeg) { if (InvertNegSub && Data < 0) { Data *= -1; } Data - ((i * j) - KArea); }
							double Val = Data * Input[InMap];
							//std::cout << " | " << Val;
							if (UseAreaRatio && !ReciprocalRatio) { Val *= AreaRatio; }
							if (UseAreaRatio && ReciprocalRatio) { Val *= 1.0 / AreaRatio; }
							Result *= Val; bool Neg = false; if (Val < 0) { Neg = true; }
							Result = sqrt(fabs(Result)); if (Neg) { Result *= -1;}
						}
						++Mi; //
					}
					//std::cout << std::endl;
					//std::cout << "Result: " << Result << std::endl;
					Out.push_back(Result);
				}
			}
		}
		Output = Out;
	}

};

// ################################################# FIM ####################################################################################

// ############################
// ############################
// ############################

// ############## MISC. ##############
// GEMATRIA:
int Char2Gematria(char C)
{
	if (IsNumber(C)) { return(Chr2Int(C)); }	if (C == 'a' || C == 'A') { return(1); } else if (C == 'b' || C == 'B') { return(2); }
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
double Char2GemaPerCent(char C)
{
	if (IsNumber(C)) { return(Chr2Int(C) / 10.0); } if (C == 'a') { return(1 / 56.0); } else if (C == 'b') { return(2 / 56.0); }
	else if (C == 'c') { return(3 / 56.0); } else if (C == 'A') { return(0.5 + (1 / 56.0)); } else if (C == 'B') { return(0.5 + (2 / 56.0)); }
	else if (C == 'C') { return(0.5 + (3 / 56.0)); } if (C == 'd') { return(4 / 56.0); } else if (C == 'e') { return(5 / 56.0); }
	else if (C == 'f') { return(6 / 56.0); } else if (C == 'D') { return(0.5 + (4 / 56.0)); } else if (C == 'E') { return(0.5 + (5 / 56.0)); }
	else if (C == 'F') { return(0.5 + (6 / 56.0)); } if (C == 'g') { return(7 / 56.0); } else if (C == 'h') { return(8 / 56.0); }
	else if (C == 'i') { return(9 / 56.0); } else if (C == 'G') { return(0.5 + (7 / 56.0)); } else if (C == 'H') { return(0.5 + (8 / 56.0)); }
	else if (C == 'I') { return(0.5 + (9 / 56.0)); } if (C == 'j') { return(10 / 56.0); } else if (C == 'k') { return(11 / 56.0); }
	else if (C == 'l') { return(12 / 56.0); } else if (C == 'J') { return(0.5 + (10 / 56.0)); } else if (C == 'K') { return(0.5 + (11 / 56.0)); }
	else if (C == 'L') { return(0.5 + (12 / 56.0)); } if (C == 'm') { return(13 / 56.0); } else if (C == 'n') { return(14 / 56.0); }
	else if (C == 'o') { return(15 / 56.0); } else if (C == 'M') { return(0.5 + (13 / 56.0)); } else if (C == 'N') { return(0.5 + (14 / 56.0)); }
	else if (C == 'O') { return(0.5 + (15 / 56.0)); } if (C == 'p') { return(16 / 56.0); } else if (C == 'q') { return(17 / 56.0); }
	else if (C == 'r') { return(18 / 56.0); } else if (C == 'P') { return(0.5 + (16 / 56.0)); }	else if (C == 'Q') { return(0.5 + (17 / 56.0)); }
	else if (C == 'R') { return(0.5 + (18 / 56.0)); } if (C == 's') { return(19 / 56.0); } else if (C == 't') { return(20 / 52.02); }
	else if (C == 'u') { return(21 / 56.0); } else if (C == 'S') { return(0.5 + (19 / 56.0)); } else if (C == 'T') { return(0.5 + (20 / 56.0)); }
	else if (C == 'U') { return(0.5 + (21 / 56.0)); } if (C == 'v') { return(22 / 56.0); } else if (C == 'w') { return(23 / 52.05); }
	else if (C == 'x') { return(24 / 56.0); } else if (C == 'V') { return(0.5 + (22 / 56.0)); } else if (C == 'W') { return(0.5 + (23 / 56.0)); }
	else if (C == 'X') { return(0.5 + (24 / 56.0)); } if (C == 'y') { return(25 / 56.0); } else if (C == 'z') { return(26 / 56.0); }
	else if (C == 'Y') { return(0.5 + (25 / 56.0)); } else if (C == 'Z') { return(0.5 + (26 / 56.0)); }
	else { return(0); }
}

int Str2Gematria(std::string S) { int Ret = 0; for (int n = 0; n < S.size(); ++n) { Ret += Char2Gematria(S[n]); } return(Ret); }
double Str2GemaPerCent(std::string S) { double Ret = 0; for (int n = 0; n < S.size(); ++n) { Ret += Char2GemaPerCent(S[n]); } Ret /= S.size(); return(Ret); }

// ALPHA OMEGA POLAR SCORE (PERSONAL ART ITEM):
double AOScore(double Radian)
{
	double Score = 0;
	double Sin = sin(Radian), Cos = cos(Radian);
	Score += Sin; // Eixo Vertical recebe bonus alpha
	Score += Cos * 0.5; // Eixo Horizontal recebe bonus omega, mas menos bonus
	if (Sin > 0) { Sin *= 1.25; } if (Cos < 0) { Cos *= 1.25; } // Eixo "Vertical" � "Alpha", "Horizontal" � "Omega"
	Score += Sin; Score += Cos;
	return (Score / 2.704162); // Melhor aproxima��o que cheguei, n�o importa muito mesmo, o que importa � a raz�o perante outros, e esta confirmado que funciona
}

// PROGRESS BAR:
void CoutProgressBar(double ZeroToOne, int Size)
{
	if (ZeroToOne < 0) { ZeroToOne = 0; } if (ZeroToOne > 1) { ZeroToOne = 1; }
	std::cout << "PROGRESS: [";
	int Round = round(ZeroToOne * Size); for (int n = 0; n < Size; ++n) { if (n <= Round) { std::cout << "#"; } else { std::cout << "_"; } }
	std::cout << "];\n";
}
void CoutProgressBar(double ZeroToOne, int Size, std::string BarName)
{
	if (ZeroToOne < 0) { ZeroToOne = 0; } if (ZeroToOne > 1) { ZeroToOne = 1; }
	std::cout << BarName << ": [";
	int Round = round(ZeroToOne * Size); for (int n = 0; n < Size; ++n) { if (n <= Round) { std::cout << "#"; } else { std::cout << "_"; } }
	std::cout << "];\n";
}

// ################################################# FIM ####################################################################################

// ############################
// ############################
// ############################

// ############## RANDOM ##############
// RANDOM-N FOR M-TIMES:
std::vector<int> Randomnm(int n, int m) { std::vector<int> rndret; for (int a = 0; a < m; ++a) { rndret.push_back(rand() % n); } return(rndret); }

// RANDOM N TIMES:
std::vector<Point> RandomDominoes(int Tries) { std::vector<Point> Pts; for (int a = 0; a < Tries; ++a) { Point Pt; Pt.x = rand() % 7; Pt.y = rand() % 7; Pts.push_back(Pt); } return(Pts); }

// RANDOM CARD:
std::vector<NameValue> RandomCard(int Tries)
{
	std::vector<NameValue>Cards;
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
std::vector<NameValue> RandomTarot(int Tries)
{
	std::vector<NameValue>Cards;
	NameValue Card;
	std::vector<std::string> CardNames = TarotCards();
	for (int a = 0; a < Tries; ++a)
	{
		int Rnd = (rand() % 78) + 1;
		bool MinMaj = false; // Minor or Major Arcana?
		if (Rnd > 22) { MinMaj = false; }
		else { MinMaj = true; }
		if (MinMaj) { Card.Name = CardNames[Rnd - 1]; Card.Value = Rnd; Cards.push_back(Card); }
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
std::vector<int> RandomPSalm(int Tries) { std::vector<int> PSs; int PS; for (int a = 0; a < Tries; ++a) { PS = (rand() % 150) + 1; PSs.push_back(PS); } return(PSs); }

// RANDOM ICHING:
std::vector<int> RandomIChing(int Tries) { std::vector<int> ICs; int IC; for (int a = 0; a < Tries; ++a) { IC = (rand() % 64) + 1; ICs.push_back(IC); } return(ICs); }

// ################################################# FIM ####################################################################################

#endif // SCPARSE_