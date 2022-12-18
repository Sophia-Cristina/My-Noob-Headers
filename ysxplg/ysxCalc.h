#pragma once

#ifndef YSXCALC_H
#define YSXCALC_H

/*#####################
####### By Sophia Cristina
####### Header made to deal with calculus.
####### Functions, derivatives, integrals and etc.
#####################*/

// ############################################################################################################################################
// ################################################# NOTES #################################################
// !!!!!!!	
// !!!!!!!	CHANGES:
// !!!!!!!	* 'MiniForm(...)' is no longer available! Functions that used it are now receiving function as parameter;
// !!!!!!!	
// ################################################# NOTES #################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ATTENTION: double (*f)(double, double) MEANS "f(x, Omega)"!!!
// ############################################################################################################################################

	/* Cool functions:
	sin((Omega / 160) * pow(x, 3)) <------- Classic of my tests, since it changes freq by 'x' and change direction when negative.
	sin(x) ||| sin(x)+(tan(x*((sin((pow(x,3))/200)/4))))/4 ||| sin(x)+(cos(x*((sin((pow(x,3))/200)/4))))/4
	(sin(x) + A) / 2 ||| sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	(((cos(x) + (sin(x * 7))/4)/1.25) + A) / 2 ||| sin(pow(x,2)) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4 ||| (sin(x * 7) + ((cos(x * 14)) / 2) + (tan(x) / 7)) / 1.266666
	(sin(x * 28) + ((pow((cos(x * 12.5) / 2), (sin(x) / 2))) / 700)) / 1.166666 |||

	LOGISTIC FUNCTION:
	1 /(1 + pow(EXP, -2 * x))

	POLAR:
	https://en.wikipedia.org/wiki/File:Rose-rhodonea-curve-7x9-chart-improved.svg
	-- r = cos(7 * n) * Amp; // Rosa
	-- r = cos(0.8 * n) * (Amp * 0.97); // Rosa
	-- r = (Amp/8) * (n / (2 * PI));
	-- r = ((1/cos(n)) + Amp * cos(n)) / 3.5; // Conchoid of de Sluze
	-- r = pow(n, 0.5) * (Amp * 0.25); // Fermat's spiral
	-- r = Amp * ((Amp * sin(n)) / n); // Cochleoid
	-- r = (cos(n) * (pow(EXP, cos(n)) - (2 * cos(4 * n) - (pow(sin(n / 12), 5))))) * 0.125; // Butterfly
	-- r = (((sin((Amp* 5) * n) * (pow(EXP, sin(n)) / EXP)) - (2 * sin((Amp * 4) * n) - sin((Amp * 2) * n))) + Amp) * (Amp / 5); // My Butterfly
	*/

	/*Cool summantions:
	SawFourier: ((4 / (Step * PI))*sin((Step*PI*x) / ((n + n - 1)*PI))) / 2.333333
	SawFourier2: ((1 / (Step * PI))*sin((Step*PI*x) / ((n + n - 1)*PI))) / 2.333333 || - 0.5 no Sum antes do return, esse que esta "Sum = Sum * a;"
	SqrFourier: ((4 / ((2* Step - 1) * PI))*sin(((2 * Step - 1)*PI*x) / ((n + n - 1)*PI))) / 1.125 || Stp2 / 2
	TriFourier: ((8 / pow(PI,2)) * (pow(-1,((2 * Step - 1 - 1) / 2.0)) / (pow((2 * Step - 1), 2)) * sin(((2* Step - 1) * PI * x) / ((n + n - 1)*PI)))) / 2.333333
	Taylor Series of f(X): (n * ((a / Factorial(n)) * (x - a)) / Factorial(n)) * pow((x - a), n)
	Taylor Analytic: ((sin(n) * x) / Factorial(n)) * pow((x), n)
	Taylor exp func: pow(x, n) / Factorial(n)
	Maclaurin series: pow(x, n); || -((1 / n) * pow(x, n))
	*/

// #####################################################################################################################################
// ####### DECLARATIONS:

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// LOG2 POW (2^(log2(p) + log2(q))):
double ysxCALC_Log_2POW(double p, double q) { return(pow(2, log2(p) + log2(q))); }

// #################################################
// ####### CALCULOS #######
// #################################################

// LINE (y = a + x * b):
double ysxCALC_Linex(double x, double a, double b) { return(a + x * b); }

// #################################################
 
// NUMERICAL INTEGRATION: MID-ORDINATE RULE:
double ysxCALC_Integral(double a, double b, int n, double Omega, double (*f)(double, double))
{
	if (n < 1) { n = 1; }
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += f(a + (i - 0.5) * dt, Omega) * dt;
	return sum;
}

// INTEGRAL ABSOLUTE:
double ysxCALC_IntgrlAbs(double a, double b, int n, double Omega, double (*f)(double, double))
{
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += fabs(f(a + (i - 0.5) * dt, Omega)) * dt;
	return sum;
}

// #################################################

// DERIVATIVE:
double ysxCALC_Deriv(double x, double Omega, double (*f)(double, double))
{
	double Lim = 1.0e-9; return((f(x + 0.5 * Lim, Omega) - f(x - 0.5 * Lim, Omega)) / Lim);
}
double ysxCALC_Deriv(double x, double Delta, double Omega, double (*f)(double, double))
{
	return((f(x + 0.5 * Delta, Omega) - f(x - 0.5 * Delta, Omega)) / Delta);
}
double ysxCALC_Deriv(double x1, double x2, double t1, double t2) { return((x2 - x1) / (t2 - t1)); }
double ysxCALC_Deriv(double x1, double x2, double t1, double t2, double Omega, double (*f)(double, double))
{
	return((f(x2 - x1, Omega) - f(x1, Omega)) / (t2 - t1));
}

// SECOND ORDER DIFFERENTIAL EQ.:
// Second-Order Central | Finite Difference:
double ysxCALC_d2xdt2(double x, double Omega, double (*f)(double, double))
{
	double Lim = 1.0e-6; return((f(x + Lim, Omega) - 2 * f(x, Omega) + f(x - Lim, Omega)) / (Lim * Lim));
}
double ysxCALC_d2xdt2(double x0, double x1, double dt) { double dx = x1 - x0; return((x1 - (2 * x0) + (x0 - dx)) / (dt * dt)); }
double ysxCALC_d2xdt2(double x, double dx, double dt, double Omega, double (*f)(double, double))
{
	return((f(x + dx, Omega) - 2 * f(x, Omega) + f(x - dx, Omega)) / dt);
}
double ysxCALC_d2xdt2(double x0, double x1, double x2, double t0, double t1) { double dx1 = x2 - x1, dx0 = x1 - x0, dt = t1 - t0; return((x2 - (2 * x1) + dx0) / (dt * dt)); }

// #################################################
 
// SUMMATION:
double ysxCALC_Sum(double x, double Omega, double Amp, int n0, int n1, double (*f)(double, double, int))
{ double S = 0; for (int n = n0; n <= n1; ++n) { S += f(x, Omega, n); } S *= Amp; return(S); }

// (f(x) + 1) * 0.5:
// Good to normalize functions like sin(x).
double ysxCALC_ModForm(double n, double Omega, double (*f)(double, double)) { return((f(n, Omega) + 1) * 0.5); }
double ysxCALC_ModForm(double n, double Rto, double Omega, double (*f)(double, double)) { return((f(n, Omega) + 1) * Rto); }
double ysxCALC_ModForm(double n, double Sum, double Rto, double Omega, double (*f)(double, double)) { return((f(n, Omega) + Sum) * Rto); }

// #################################################

// ARC LENGTH:
double ysxCALC_ArcLength(double a, double b, int n, double Omega, double (*f)(double, double))
{
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += sqrt(1 + pow(ysxCALC_Deriv(a + (i - 0.5) * dt, Omega, f), 2)) * dt;
	return sum;
}
// ####### SEQUENCIA E SERIES #######
double ysxCALC_FourierSeries(double x, int Harmonics, double P, double Omega, double IntegrEnd, int IntIter, double (*f)(double, double))
{
	if (P == 0) { P = 0.000001; } if (IntIter < 1) { IntIter = 1; } if (Harmonics < 1) { Harmonics = 1; }
	double Cos, Sin;
	double Sum = 0, Form, an, bn, a0, b0 = 0;
	double IntSuma = 0, IntSumb = 0, dt = (1.0 * IntegrEnd - P) / IntIter; 
	for (int i = 1; i <= IntIter; i++) { a0 = f(P + (i - 0.5) * dt, Omega) * dt; } a0 = (2.0 / P) * a0; // <- computing a0
	// SUMMATION:
	for (int n = 1; n <= Harmonics; ++n) // LEMBRAR DE VERIFICAR SE STP2 NÃO ESTA MODIFICADO
	{
		// Integrais | WIKI EQ. 1:
		for (int i = 1; i <= IntIter; i++)
		{
			Cos = cos(2 * PI * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			Sin = sin(2 * PI * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			IntSuma += (Cos * f(P + (i - 0.5) * dt, Omega)) * dt; // Ve se precisa do '* dt'
			IntSumb += (Sin * f(P + (i - 0.5) * dt, Omega)) * dt;
		}
		an = (2.0 / P) * IntSuma; bn = (2.0 / P) * IntSumb; // END EQ. 1

		Form = an * cos((2 * PI * n * x) / P) + bn * sin((2 * PI * n * x) / P);
		Sum += Form;
	}
	return((a0 / 2.0) + Sum);
}

// ####### SEQUENCESS:
// ARITHMETIC SEQUENCE:
std::vector<double> ysxCALC_ArithSeq(double a, double d, size_t n)
{ std::vector<double> S{ a }; for (size_t k = 1; k < n; ++k) { S.push_back(S[0] + (d * k)); } return (S); }
double ysxCALC_ArithSeqnth(double a, double d, int n) { return(a + d * (n - 1.0)); }
double ysxCALC_ArithSeqSum(double a, double d, int n) { return(n * 0.5 * (2.0 * a + d * (n - 1.0))); }
// Get the difference from an arithmetic sequence which results as "1" at "n":
double ysxCALC_ArithSeqDiffAt1(double a, int n) { return((1 - a) / (n - 1.0)); }
double ysxCALC_ArithSeqDiffAtb(double a, double b, int n) { return((b - a) / (n - 1.0)); }

// GEOMETRIC SEQUENCE:
std::vector<double> ysxCALC_GeoSeq(double a, double r, int n)
{ std::vector<double> S{ a }; for (int k = 1; k < n; ++k) { S.push_back(S[0] * pow(r, k)); } return (S); }
double ysxCALC_GeoSeqnth(double a, double r, int n) { return(a * pow(r, n - 1.0)); }
double ysxCALC_GeoSeqSum(double a, double r, int n) { return(a * ((1.0 - pow(r, n)) / (1.0 - r))); }
double ysxCALC_GeoSeqProduct(double a, double r, int n) { return(pow(sqrt(a * a * pow(r, n)), n + 1.0)); } // https://en.wikipedia.org/wiki/Geometric_progression#Product
double ysxCALC_GeoSeqRatioAt1(double a, int n) { return(pow((1 / a), 1 / (n - 1.0))); }
double ysxCALC_GeoSeqRatioAtb(double a, double b, int n) { return(pow((b / a), 1 / (n - 1.0))); }

// EASY SEQUENCE FORMULA ((a^(b + c))^d) / e):
double ysxCALC_EzSeqForm(double a, double b, double c, double d, double e) { return(pow(pow(a, b + c), d) / e); }

// ### SERIES:
//double ysxCALC_Series(int a1, int an)
//{
//	return (0);
//}

// SIGMOID:
double ysxCALC_Sigmoid(double x) { return(1 / (1 + (pow(EXP, -x)))); }

// RECTIFIER:
double ysxCALC_Softplus(double x) { return(log(1 + pow(EXP, x))); }
double ysxCALC_ReLU(double x) { if (x < 0) { return(0); } else return(x); }

// #################################################
// ####### RANDOM FORMULAE #######
// #################################################

double ysxCALC_ElipticCurve(double x, double a, double b) { return(sqrt(x * x * x + a * x + b)); }

// ################################################# FIM ####################################################################################

#endif // SCPARSE_