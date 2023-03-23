#pragma once

#ifndef YSXARITH_H
#define YSXARITH_H

// #####################
// ####### By Sophia Cristina
// #######
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ############## MULT. AND DIVISIONS ##############

// FACTORIAL:
size_t ysxARITH_Fact(size_t a) { size_t Fact = 1; if (a > 0) { for (size_t n = 1; n <= a; ++n) { Fact *= n; } return (Fact); } else { return (1); } }

// FACTORS:
std::vector<int> ysxARITH_Factors(int n) { std::vector<int> V; for (size_t m = 1; m <= n; ++m) { if (0 == n % m) { V.push_back(m); } } return (V); }

// GCD (GREATEST COMMON DIVISOR):
int ysxARITH_GCD(int a, int b)
{
	a = abs(a); b = abs(b);
	if (b == a) { return (a); } if (b > a) { int tmp = a; a = b; b = tmp; }
	int Mod = a % b, Div = b, Actual;
	if (!b) { return (a); }
	else { while (Mod != 0) { Actual = Div % Mod; Div = Mod; Mod = Actual; } return (Div); }
}

// LCM (LEAST COMMON MULTIPLE):
int ysxARITH_LCM(int a, int b) { a = abs(a); b = abs(b); return (a * b / ysxARITH_GCD(a, b)); }

// DIVISOR FUNCTION (When x is 1, the function is called the sigma function or sum-of-divisors function)
int ysxARITH_DivFunc(int n, int Power) { std::vector<int> Fac = ysxVEC_PowVec(ysxARITH_Factors(n), Power); int Sum = ysxVEC_SumVec(Fac); return(Sum); }

// ####### AVERAGES AND RATIOS:
// ARITHMETIC MEAN:
double ysxARITH_Average(std::vector<double> Vec)
{ double Sum = 0; if (Vec.size() != 0) { for (size_t n = 0; n < Vec.size(); ++n) { Sum += Vec[n]; } Sum /= Vec.size(); } return (Sum); }

// ROOT MEAN SQUARE:
double ysxARITH_RMS(std::vector<double> Vec)
{ double Sum = 0; size_t n = Vec.size(); if (n != 0) { for (size_t i = 0; i < n; ++i) { Sum += Vec[i] * Vec[i]; } Sum /= n; } return (sqrt(Sum)); }

// HARMONIC MEAN:
double ysxARITH_HarmMean(std::vector<double> Vec)
{ double Sum = 0; size_t n = Vec.size(); if (n != 0) { for (size_t i = 0; i < n; ++i) { Sum += 1.0 / Vec[i]; } n /= Sum; } return (n); }

// GEOMETRIC MEAN:
double ysxARITH_GeoMean(std::vector<double> Vec)
{ double Mul = 0; if (Vec.size() != 0) { for (size_t n = 0; n < Vec.size(); ++n) { Mul *= Vec[n]; } Mul = pow(Mul, 1 / Vec.size()); } return (Mul); }

// ARITHMETIC-GEOMETRIC MEAN:
Point<double> ysxARITH_ArithGeoMean(Point<double> P, size_t Iter)
{
	Point<double> Pt; Pt.x = 0.5 * (P.x + P.y); Pt.y = sqrt(P.x * P.y);
	double x, y;
	for (size_t n = 1; n < Iter; ++n) { x = Pt.x, y = Pt.y; Pt.x = 0.5 * (x + y); Pt.y = sqrt(x * y); }
	return (Pt);
}

// GEOMETRIC-HARMONIC MEAN:
Point<double> ysxARITH_GeoHarmMean(Point<double> P, size_t Iter)
{
	Point<double> Pt; Pt.x = sqrt(P.x * P.y); Pt.y = 2.0 / ((1.0 / P.x) + (1.0 / P.y));
	double x, y;
	for (size_t n = 1; n < Iter; ++n) { x = Pt.x, y = Pt.y; Pt.x = sqrt(x * y); Pt.y = 2.0 / ((1.0 / x) + (1.0 / y)); }
	return (Pt);
}

// POWER MEAN OR GENERALIZED MEAN:
double ysxARITH_PowerMean(std::vector<double> Vec, double p)
{
	double Sum = 0; size_t n = Vec.size(); for (size_t i = 0; i < n; ++i) { Sum += pow(Vec[i], p); } Sum *= 1.0 / n; Sum = pow(Sum, 1 / p); return(Sum);
}

// RATIO BETWEEN TWO RATIOS '(a * Rta) / (b * Rtb)' : (Ex.: Beer, a = 350ml, Rta = 0.046; Spirit, b = 50ml, Rtb = 0.39; Return = 0.825641...
double ysxARITH_RatioofRatios(double a, double Rta, double b, double Rtb) { return((a * Rta) / (b * Rtb)); }

// SUM OF POWERS (It keeps summing from 'm' to 'n' to the power of 'p' or  it will be summing 'n' from 'p0' to 'p1'):
double ysxARITH_SumIniEndtoPow(int Ini, int End, int p) { double Sum = 0; for (size_t m = Ini; m <= End; ++m) { Sum += pow(m, p); } return (Sum); }
double ysxARITH_SumntoPowIniEnd(int n, int Ini, int End) { double Sum = 0; for (size_t m = Ini; m <= End; ++m) { Sum += pow(n, m); } return (Sum); }

// Take the cube root of 'x^3 + y^3', also remember about integers and 'x^3 + y^3 = z^3':
double ysxARITH_CubeofTwoCubes(double x, double y) { return(pow((x * x * x) + (y * y * y), 1.0 / 3)); }

// ###################################################################################################################################################

// #################################################
// ############## CLASSES ##############
// #################################################

/*############################
####### FRACTION:
You should take care with division by zero, just like in anything related to math.
This class have a lot of operator overloads, enjoy:
	a/b
*/
template <class T_> class ysxARITH_Fraction
{
public:
	T_ a = 1, b = 1;

	// #################################################
	 
	ysxARITH_Fraction(const T_& set_a, const T_& set_b) { a = set_a; b = set_b; }
	ysxARITH_Fraction(const Point<T_>& q) { a = q.x; b = q.y; }
	ysxARITH_Fraction(const ysxARITH_Fraction<T_>& other) { a = other.a; b = other.b; }

	// #################################################
	// OVERLOAD:
		// Arithmethics overload:
	ysxARITH_Fraction<T_> operator + (const ysxARITH_Fraction<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.b + b * q.a; p.b = b * q.b; return(p); }
	ysxARITH_Fraction<T_> operator + (const Point<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.y + b * q.x; p.b = b * q.y; return(p); }
	ysxARITH_Fraction<T_> operator + (const T_& q) { ysxARITH_Fraction<T_> p; p.a = a + b * q; p.b = b; return(p); }
	void operator += (const ysxARITH_Fraction<T_>& q) { a = a * q.b + b * q.a; b = b * q.b; }
	void operator += (const T_& q) { a = a + b * q; }

	ysxARITH_Fraction<T_> operator - (const ysxARITH_Fraction<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.b - b * q.a; p.b = b * q.b; return(p); }
	ysxARITH_Fraction<T_> operator - (const Point<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.y - b * q.x; p.b = b * q.y; return(p); }
	ysxARITH_Fraction<T_> operator - (const T_& q) { ysxARITH_Fraction<T_> p; p.a = a - b * q; p.b = b; return(p); }
	void operator -= (const ysxARITH_Fraction<T_>& q) { a = a * q.b - b * q.a; b = b * q.b; }
	void operator -= (const T_& q) { a = a - b * q; }

	ysxARITH_Fraction<T_> operator * (const ysxARITH_Fraction<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.a; p.b = b * q.b; return(p); }
	ysxARITH_Fraction<T_> operator * (const Point<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.x; p.b = b * q.y; return(p); }
	ysxARITH_Fraction<T_> operator * (const T_& q) { ysxARITH_Fraction<T_> p; p.a = a * q; return(p); }
	void operator *= (const ysxARITH_Fraction<T_>& q) { a = a * q.a; b = b * q.b; }
	void operator *= (const T_& q) { a = a * q; }

	ysxARITH_Fraction<T_> operator / (const ysxARITH_Fraction<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.b; p.b = b * q.a; return(p); }
	ysxARITH_Fraction<T_> operator / (const Point<T_>& q) { ysxARITH_Fraction<T_> p; p.a = a * q.y; p.b = b * q.x; return(p); }
	ysxARITH_Fraction<T_> operator / (const T_& q) { ysxARITH_Fraction<T_> p; p.a = a; p.b = b * q; return(p); }
	void operator /= (const ysxARITH_Fraction<T_>& q) { a = a * q.b; b = b * q.a; }
	void operator /= (const T_& q) { b = b * q; }

	ysxARITH_Fraction<T_> operator = (const ysxARITH_Fraction<T_>& q) { ysxARITH_Fraction<T_> p; p.a = q.a; p.b = q.b; return(p); }
	ysxARITH_Fraction<T_> operator = (const T_& q) { ysxARITH_Fraction<T_> p; p.a = q; p.b = 1; return(p); }
	
	// Comparator overload:
	/*bool operator < (const ysxARITH_Fraction<T_>& q) { return((a / b) < (q.a / q.b)); }
	bool operator > (const ysxARITH_Fraction<T_>& q) { return((a / b) > (q.a / q.b)); }
	bool operator >= (const ysxARITH_Fraction<T_>& q) { return((a / b) >= (q.a / q.b)); }
	bool operator <= (const ysxARITH_Fraction<T_>& q) { return((a / b) <= (q.a / q.b)); }
	bool operator == (const ysxARITH_Fraction<T_>& q) { return((a / b) == (q.a / q.b)); }
	bool operator != (const ysxARITH_Fraction<T_>& q) { return((a / b) != (q.a / q.b)); }
	bool operator ! () { return(a == 0); }

	// Bitwise overload:
	void operator << (const ysxARITH_Fraction<T_>& q) { a = a << q.a; b = b << q.b; }
	void operator << (const T_& q) { a = a << q; b = b << 1; }
	void operator >> (const ysxARITH_Fraction<T_>& q) { a = a >> q.a; b = b >> q.b; }
	void operator >> (const T_& q) { a = a >> q; b = b >> 1; }
	void operator ~ () { a = ~a; b = ~b; }
	void operator & (const ysxARITH_Fraction<T_>& q) { a = a & q.a; b = b & q.b; }
	void operator & (const T_& q) { a = a & q; b = b & 1; }
	void operator | (const ysxARITH_Fraction<T_>& q) { a = a | q.a; b = b | q.b; }
	void operator | (const T_& q) { a = a | q; b = b | 1; }
	void operator ^ (const ysxARITH_Fraction<T_>& q) { a = a ^ q.a; b = b ^ q.b; }
	void operator ^ (const T_& q) { a = a ^ q; b = b ^ 1; }*/

	// COUT:
	//std::ostream& operator<<(std::ostream& COut, const ysxARITH_Fraction<T_>& q) { COut << (float)(q.a / q.b); return(COut); }
	// #################################################

	// Tries to reduce the value of 'a' and 'b', but maintaining ratio:
	void Simplify()
	{
		if (b == 0 || a == 0) { return; }
		for (size_t n = a > b ? a : b; n > 0; --n) 
		{ if (!(n % a) && !(n % b)) { a /= n; b /= n; } }
	}

	// Get Double:
	constexpr double GetDbl() { return(b == 0 ? 0 : (double)a / (double)b); }
	constexpr float GetFlt() { return(b == 0 ? 0 : (float)a / (float)b); }
	
	// Divide 'a/b', return 'T_':
	constexpr T_ GetDiv() { return(b == 0 ? 0 : a / b); }

	// #################################################
	ysxARITH_Fraction(T_ Set_a, T_ Set_b) { a = Set_a; b = Set_b; }
	//~ysxARITH_Fraction() {}
};




// #################################################
// ##############  



// #################################################
// #################################################
// #################################################

#endif // SCPARSE_
