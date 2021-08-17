#pragma once

#ifndef YSXCALC_H
#define YSXCALC_H

#include "ysxConst.h";

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* Usar classe 'Function' do std;
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// #####################################################################################################################################
// ####### DECLARAÇÕES:
double Sum(double, double, double, int, int);
double Integral(double, double, int, double);
double MiniForm(double, double);
double Sigmoid(double);


// #################################################
// ####### MINHAS FORMULAS #######
// #################################################

// Faz circulos a cada iteração de um delta x:
double FxPI(double x, int Iter, double PIn)
{
	double d = TAU / Iter;
	double divx = x / d;
	int divxflr = floor(divx);
	double PISin = Sum(1, (divx - divxflr) * (PI * PIn), 1, 1, 7); // Lembrar que era sin((divx - divxflr) * (PI * PIn))
	return(PISin * Sum(1, x, 1, 1, 7));
	// return(PISin * sin(x)); // Bem legal também
}

// Faz circulos a cada iteração de um delta x:
double FxPI0(double x, int Iter, double PIn)
{
	double d = TAU / Iter;
	double divx = x / d;
	int divxflr = floor(divx);
	double Form;
	double PISin = 0;
	for (int n = 1; n <= 7; ++n)
	{
		double Form = Sum(1, ((divx - divxflr) + n * (PI * 0.5)) * (PI * PIn * n), 1, 1, 7);
		//double Form = sin(((divx - divxflr) + n * PI) * (PI * PIn * n));
		PISin += Form; PISin *= 0.5;
	}
	return(PISin * Sum(1, x, 1, 1, 7));
}

// Faz circulos a cada iteração de um delta x:
double FxPI1(double x, int Iter, double PIn)
{
	double d;
	double divx;
	int divxflr;
	double Form;
	double PISin = 0;
	for (int n = 1; n <= 7; ++n)
	{
		d = TAU / (Iter * (n * 0.5));
		divx = x / d;
		divxflr = floor(divx);
		double Form = Sum(1, ((divx - divxflr) + n * PI) * (PI * PIn * n), 1, 1, 7);
		//double Form = Sum(1, ((divx - divxflr) + n * (PI * 0.5)) * (PI * PIn * n), 1, 1, 7);
		//double Form = sin(((divx - divxflr) + n * PI) * (PI * PIn * n));
		PISin += Form; PISin *= 0.5;
	}
	return(PISin * Sum(1, x, 1, 1, 7));
	//return(PISin * sin(x));
}

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### RELÓGIO #######
// #################################################

double Time2ms(int Min, int Sec) { return((Sec + (Min * 60)) * 1000); }
double Time2ms(int Hr, int Min, int Sec) { return((Sec + ((Min * 60) + (Hr * 3600))) * 1000); }
double ms2Min(double ms) { return(ms / 60000.0); }
double Dec2Sec(double Dec) { return(Dec * 60); }

// #################################################
// ####### CALCULOS #######
// #################################################

// LINHA (y = a + x * b):
double Linex(double x, double a, double b) { return(a + x * b); }

// FORMULA COMPLEXA ((a * Seno(x^b)) + c) / d | LEMBRAR DE FAZER UMA FUNÇÃO QUE LEIA QUALQUER FORMULA:
double Formula(double a, double Omega, double x, double b, double c, double d)
{
	double Seno = sin((Omega / 160) * pow(x, b));
	// #######
	double ThisFormula = a * Seno; // FORMULA AQUI!!!!!!!
	// #######
	if (d == 0) { d = 0.000000001; } // Divisão por 0
	double Retorno = (ThisFormula + c) / d;
	return (Retorno);
}

// MINI FORMULA | LEMBRAR DE FAZER UMA FUNÇÃO QUE LEIA QUALQUER FORMULA:
double MiniForm(double n, double Omega) // n = discrete time, akin to typicall 'x' in a 'f(x)' -> f[n]
{
	//double x = (TAU * Omega) * n; // Dependendo da formula, não é nescessario.
	// TIPO SINAIS:
	//return(/*Formula: */sin(n * Omega)/**/);
	//return(/*Formula: */sin(n * Omega) * 0.75 + sin(n * n * Omega) * 0.25/**/);
	//return(rect(n * Omega));
	//return(saw(n * Omega));
	//return(phasor(n * Omega));
	//return(tri(n * Omega));

	// MEUS:
	//return(Formula(1, Omega, n, 3, 0, 1));
	//return(FxPI(n, 7, 1));
	//return(FxPI1(n, 7, 0.0714285);)

	// FISICA:
	//return(NonStatWaveFunc(1.0 / (n + 1), 6.2831, n, 1, Omega, 0));
	//return(SimpleHarmOsc(90, 220, n, 0));

	// SOMATÓRIA:
	return(Sum(Omega, n, 1, 1, 7));

	// !!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!!

	/* Formulas interessantes:
	sin((Omega / 160) * pow(n, 3)) <------- Classico dos meus testes, muda a frequencia com x e muda direção em negativo.
	sin(x) ||| sin(x)+(tan(x*((sin((pow(x,3))/200)/4))))/4 ||| sin(x)+(cos(x*((sin((pow(x,3))/200)/4))))/4
	(sin(x) + ASerModulado) / 2 ||| sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	(((cos(x) + (sin(x * 7))/4)/1.25) + ASerModulado) / 2 ||| sin(pow(x,2)) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4 ||| (sin(x * 7) + ((cos(x * 14)) / 2) + (tan(x) / 7)) / 1.266666
	(sin(x * 28) + ((pow((cos(x * 12.5) / 2), (sin(x) / 2))) / 700)) / 1.166666 |||

	LOGISTIC FUNCTION:
	1 /(1 + pow(EXP, -2 * n))

	FOURIER:
	Sum(1, n, 1, 1, 77) || VERIFICAR SE ESTA A FORMULA FOURIER NA SOMATÓRIA

	// !!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!! !!!!!!!!!!!!!!!!!!!!!

	POLAR:
	en.wikipedia.org/wiki/File:Rose-rhodonea-curve-7x9-chart-improved.svg
	-- r = cos(7 * n) * Amp; // Rosa
	-- r = cos(0.8 * n) * (Amp * 0.97); // Rosa
	-- r = (Amp/8) * (n / (2 * PI)); // Acho que espiral
	-- r = ((1/cos(n)) + Amp * cos(n)) / 3.5; // Conchoid of de Sluze
	-- r = pow(n, 0.5) * (Amp * 0.25); // Fermat's spiral
	-- r = Amp * ((Amp * sin(n)) / n); // Cochleoid
	-- r = (cos(n) * (pow(EXP, cos(n)) - (2 * cos(4 * n) - (pow(sin(n / 12), 5))))) * 0.125; // Butterfly
	-- r = (((sin((Amp* 5) * n) * (pow(EXP, sin(n)) / EXP)) - (2 * sin((Amp * 4) * n) - sin((Amp * 2) * n))) + Amp) * (Amp / 5); // Meu Butterfly
	-- r = Amp * (sin(14 + cos(n) * 7)); // Minha Rosa;
	*/
}

// MINI FORMULA DA MODULAÇÃO:
double ModForm(double n, double Omega) { return((MiniForm(n, Omega) + 1) * 0.5); }
double ModForm(double n, double Rto, double Omega) { return((MiniForm(n, Omega) + 1) * Rto); }
double ModForm(double n, double Sum, double Rto, double Omega) { return((MiniForm(n, Omega) + Sum) * Rto); }

// NUMERICAL INTEGRATION: MID-ORDINATE RULE:
double Integral(double a, double b, int n, double Omega)
{
	if (n < 1) { n = 1; }
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += MiniForm(a + (i - 0.5) * dt, Omega) * dt;
	return sum;
}

// INTEGRAL ABSOLUTO:
double IntgrlAbs(double a, double b, int n, double Omega)
{
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += fabs(MiniForm(a + (i - 0.5) * dt, Omega)) * dt;
	return sum;
}

// ARC LENGTH:
double ArcLength(double a, double b, int n, double Omega)
{
	double dt = (b - a) / n; double sum = 0;
	for (int i = 1; i <= n; i++) sum += sqrt(1 + pow(Derivative(a + (i - 0.5) * dt, Omega), 2)) * dt;
	return sum;
}

// DERIVATIVE:
double Derivative(double x, double Omega) { double Limit = 1.0e-9; return((MiniForm(x + 0.5 * Limit, Omega) - MiniForm(x - 0.5 * Limit, Omega)) / Limit); }
double Derivative(double x, double Delta, double Omega) { return((MiniForm(x + 0.5 * Delta, Omega) - MiniForm(x - 0.5 * Delta, Omega)) / Delta); }
double Derivative(double x1, double x2, double t1, double t2) { return((x2 - x1) / (t2 - t1)); }
double Derivative(double x1, double x2, double t1, double t2, double Omega) { return((MiniForm(x2 - x1, Omega) - MiniForm(x1, Omega)) / (t2 - t1)); }

// EQ. DIFERENCIAL DE SEGUNDA ORDEM:
// Second-Order Central | Finite Difference:
double d2xdt2(double x, double Omega) { double Limit = 1.0e-6; double Eq = (MiniForm(x + Limit, Omega) - 2 * MiniForm(x, Omega) + MiniForm(x - Limit, Omega)) / (Limit * Limit); return(Eq); }
double d2xdt2(double x0, double x1, double dt) { double dx = x1 - x0; return((x1 - (2 * x0) + (x0 - dx)) / (dt * dt)); }
double d2xdt2(double x, double dx, double dt, double Omega) { double Eq = (MiniForm(x + dx, Omega) - 2 * MiniForm(x, Omega) + MiniForm(x - dx, Omega)) / dt; return(Eq); }
double d2xdt2(double x0, double x1, double x2, double t0, double t1) { double dx1 = x2 - x1, dx0 = x1 - x0, dt = t1 - t0; return((x2 - (2 * x1) + dx0) / (dt * dt)); }

// ####### SEQUENCIA E SERIES #######
// ### SOMAÇÃO:
double Sum(double m, double x, double Amp, int n, int n2)
{
	double Sm = 0, Form;
	for (int Step = n; Step <= n2; ++Step) // LEMBRAR DE VERIFICAR SE STP2 NÃO ESTA MODIFICADO
	{
		// FORMULA:
		//Form = ((4 / (Step * PI))*sin((Step * PI * x * m) / ((n + n - 1) * PI))) / 2.333333;
		Form = ((4 / ((2 * Step - 1) * PI)) * sin(((2 * Step - 1) * PI * x) / ((n + n - 1) * PI))) / 1.125;
		Sm += Form;

		//Formulas de interesse:
		/*
		SawFourier: ((4 / (Step * PI))*sin((Step*PI*x) / ((n + n - 1)*PI))) / 2.333333
		SawFourier2: ((1 / (Step * PI))*sin((Step*PI*x) / ((n + n - 1)*PI))) / 2.333333 || - 0.5 no Sum antes do return, esse que esta "Sum = Sum * a;"
		SqrFourier: ((4 / ((2* Step - 1) * PI))*sin(((2 * Step - 1)*PI*x) / ((n + n - 1)*PI))) / 1.125 || Stp2 / 2
		TriFourier: ((8 / pow(PI,2)) * (pow(-1,((2 * Step - 1 - 1) / 2.0)) / (pow((2 * Step - 1), 2)) * sin(((2* Step - 1) * PI * x) / ((n + n - 1)*PI)))) / 2.333333
		FS: 2 * IntgrlRAM(0, 1, 0, a, 1) + 2 * IntgrlRAM(0, 1, 0, a, 1)
		Taylor Series of f(X): (n * ((a / Factorial(n)) * (x - a)) / Factorial(n)) * pow((x - a), n)
		Taylor Analytic: ((sin(n) * x) / Factorial(n)) * pow((x), n)
		Taylor exp func: pow(x, n) / Factorial(n)
		Maclaurin series: pow(x, n); || -((1 / n) * pow(x, n))
		*/
	}
	Sm *= Amp; // LEMBRAR VER SE NÃO ESTA MODIFICADO ESSA TAMBÉM
	return(Sm);
}

double FourierSeries(double x, int Harmonics, double P, double Omega, double IntegrEnd, int IntIter)
{
	if (P == 0) { P = 0.000001; } if (IntIter < 1) { IntIter = 1; } if (Harmonics < 1) { Harmonics = 1; }
	double Cos, Sin;
	double Sum = 0, Form, an, bn, a0, b0 = 0;
	double IntSuma = 0, IntSumb = 0, dt = (1.0 * IntegrEnd - P) / IntIter; 
	for (int i = 1; i <= IntIter; i++) { a0 = MiniForm(P + (i - 0.5) * dt, Omega) * dt; } a0 = (2.0 / P) * a0; // <- computing a0
	// SUMMATION:
	for (int n = 1; n <= Harmonics; ++n) // LEMBRAR DE VERIFICAR SE STP2 NÃO ESTA MODIFICADO
	{
		// Integrais | WIKI EQ. 1:
		for (int i = 1; i <= IntIter; i++)
		{
			Cos = cos(2 * PI * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			Sin = sin(2 * PI * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			IntSuma += (Cos * MiniForm(P + (i - 0.5) * dt, Omega)) * dt; // Ve se precisa do '* dt'
			IntSumb += (Sin * MiniForm(P + (i - 0.5) * dt, Omega)) * dt;
		}
		an = (2.0 / P) * IntSuma; bn = (2.0 / P) * IntSumb; // END EQ. 1

		Form = an * cos((2 * PI * n * x) / P) + bn * sin((2 * PI * n * x) / P);
		Sum += Form;
	}
	return((a0 / 2.0) + Sum);
}

// ### SEQUENCIAS:
// Aritimética:
std::vector<double> ArithSequence(double a, double d, int n) { std::vector<double> S{ a }; for (int k = 1; k < n; ++k) { S.push_back(S[0] + (d * k)); } return (S); }
double ArithSeqnth(double a, double d, int n) { return(a + d * (n - 1.0)); }
double ArithSeqSum(double a, double d, int n) { return(n * 0.5 * (2.0 * a + d * (n - 1.0))); }
// Get the difference from an arithmetic sequence which results as "1" at "n":
double ArithSeqDiffAt1(double a, int n) { return((1 - a) / (n - 1.0)); }
double ArithSeqDiffAtb(double a, double b, int n) { return((b - a) / (n - 1.0)); }
//double ArithSeqProduct() {}

// Geométrica:
std::vector<double> GeoSequence(double a, double r, int n) { std::vector<double> S{ a }; for (int k = 1; k < n; ++k) { S.push_back(S[0] * pow(r, k)); } return (S); }
double GeoSeqnth(double a, double r, int n) { return(a * pow(r, n - 1.0)); }
double GeoSeqSum(double a, double r, int n) { return(a * ((1.0 - pow(r, n)) / (1.0 - r))); }
double GeoSeqProduct(double a, double r, int n) { return(pow(sqrt(a * a * pow(r, n)), n + 1.0)); } // https://en.wikipedia.org/wiki/Geometric_progression#Product
double GeoSeqRatioAt1(double a, int n) { return(pow((1 / a), 1 / (n - 1.0))); }
double GeoSeqRatioAtb(double a, double b, int n) { return(pow((b / a), 1 / (n - 1.0))); }

// Easy sequence formula:
double EzSeqForm(double a, double b, double c, double d, double e) { return(pow(pow(a, b + c), d) / e); }

// ### SERIES:
double Serie(int a1, int an)
{
	return (0);
}

// ### I THINK IT IS CALLED SIG FUNCTIONS:
// SIGMOID (ver variavel)
double Sigmoid(double x) { return(1 / (1 + (pow(EXP, -x)))); }

// RECTIFIER:
double Softplus(double x) { return(log(1 + pow(EXP, x))); }
double ReLU(double x) { if (x < 0) { return(0); } else return(x); }

// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################
// ####################################################################################################################################################################################################

// #################################################
// ####### RANDOM FORMULAES: #######
// #################################################

double ElipticCurve(double x, double a, double b) { return(sqrt(x * x * x + a * x + b)); }

// ################################################# FIM ####################################################################################

#endif // SCPARSE_