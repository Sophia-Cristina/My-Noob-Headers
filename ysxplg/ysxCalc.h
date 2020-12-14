#pragma once

#ifndef YSXCALC_H
#define YSXCALC_H

#include "ysxConst.h";

using namespace std;

// #####################################################################################################################################
// ####### DECLARAÇÕES:
double Sum(double, double, double, int, int);
double Integral(double, double, int, double);
double MiniForm(double, double);
double Sigmoid(double);

// #####################
// ### MINHAS FORMULAS:
// #####################

// Faz circulos a cada iteração de um delta x:
double FxPi(double x, int Iter, double Pin)
{
	double d = Tau / Iter;
	double divx = x / d;
	int divxflr = floor(divx);
	double PiSin = Sum(1, (divx - divxflr) * (Pi * Pin), 1, 1, 7); // Lembrar que era sin((divx - divxflr) * (Pi * Pin))
	return(PiSin * Sum(1, x, 1, 1, 7));
	// return(PiSin * sin(x)); // Bem legal também
}

// Faz circulos a cada iteração de um delta x:
double FxPi0(double x, int Iter, double Pin)
{
	double d = Tau / Iter;
	double divx = x / d;
	int divxflr = floor(divx);
	double Form;
	double PiSin = 0;
	for (int n = 1; n <= 7; ++n)
	{
		double Form = Sum(1, ((divx - divxflr) + n * (Pi * 0.5)) * (Pi * Pin * n), 1, 1, 7);
		//double Form = sin(((divx - divxflr) + n * Pi) * (Pi * Pin * n));
		PiSin += Form; PiSin *= 0.5;
	}
	return(PiSin * Sum(1, x, 1, 1, 7));
}

// Faz circulos a cada iteração de um delta x:
double FxPi1(double x, int Iter, double Pin)
{
	double d;
	double divx;
	int divxflr;
	double Form;
	double PiSin = 0;
	for (int n = 1; n <= 7; ++n)
	{
		d = Tau / (Iter * (n * 0.5));
		divx = x / d;
		divxflr = floor(divx);
		double Form = Sum(1, ((divx - divxflr) + n * Pi) * (Pi * Pin * n), 1, 1, 7);
		//double Form = Sum(1, ((divx - divxflr) + n * (Pi * 0.5)) * (Pi * Pin * n), 1, 1, 7);
		//double Form = sin(((divx - divxflr) + n * Pi) * (Pi * Pin * n));
		PiSin += Form; PiSin *= 0.5;
	}
	return(PiSin * Sum(1, x, 1, 1, 7));
	//return(PiSin * sin(x));
}

// #####################
// ### FIM | MINHAS ###
// #####################

// ####### ####### #######
// ####### RELÓGIO:
double Time2ms(int Min, int Sec) { return((Sec + (Min * 60)) * 1000); }
double Time2ms(int Hr, int Min, int Sec) { return((Sec + ((Min * 60) + (Hr * 3600))) * 1000); }
double ms2Min(double ms) { return((ms / 1000.0) / 60); }
double Dec2Sec(double Dec) { return(Dec * 60); }

// ####### MUSICA:
double BPM2ms(double BPM) { return(60000.0 / BPM); } // Quantos 'ms' tem em cada beat
double ms2BPM(double ms) { return(60000.0 / ms); } // Qual seria o 'BPM' se o beat tivesse tantos 'ms'
double ms2Freq(double ms) { return(1.0 / (ms / 1000.0)); } // dado 'ms', retorna a frequencia que oscilaria no mesmo periodo
double Ptrn2ms(int PtrnSize, int Ptrnn, double BPM) { return((PtrnSize * Ptrnn) * BPM2ms(BPM)); } // no "Renoise" com "64" linhas seria "PtrnSize = 16", é em beats;
double Beatsinms(double ms, double BPM) { return(ms / BPM2ms(BPM)); } // Quantos 'beats' tem em tantos 'ms'
double msinBeats(double Beats, double BPM) { return( BPM2ms(BPM) * Beats); } // Quantos 'ms' tem em tantos beats
double BeatsinTime(int Min, int Sec, double BPM) { return(Time2ms(Min, Sec) / BPM2ms(BPM)); } // Dado minutos e segundos, retorna a quantia de 'beats' que caberiam nesse tempo
double samptoms(double samp, double samprate) { return((samp * 1000.0) / samprate); } // Dada quantia de samples que passaram, quanto isso significa em milissegundos
double mstosamp(double ms, double samprate) { return((ms / samprate) / 1000.0); } // Dada quantia de milissegundos que passaram, quanto isso significa em numero de samples
double SamplesinMS(double ms, int SampleRate) { return((ms * SampleRate) / 1000); } // How much samples have in x miliseconds
double Tau2Samples(int SampleRate) { return(SampleRate / Tau); } // SamplesRate divided by tal | 44100 / 6.2831 = 7018.7329903525843074077739647279
double Sample_n2Rad(int n, int SampleRate) { return(Tau * n / SampleRate); } // If the SampleRate was a table, 'n' would be the index, when 'n = TableSize', the function returns 2*PI
double Rad2Sample_n(double x, int SampleRate) { return((x / Tau) * SampleRate); } // If the SampleRate was a table, the return would be the index, when 'x = 2*PI', the function returns SampleRate (ex.: 2*PI / 2*PI) * 44100)

// ### Notas e Patterns:
// # Frequencias:
//double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, (MIDI - (Temperament * 5.75)) / Temperament) * BaseFreq); } // A3 = 57; C3 = 48;
double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, ((double)MIDI / Temperament)) * BaseFreq * 0.0185814); } // Modo Reduzido, mas fixo em 'A3 = 57'
double FreqtoMIDI(double Freq, int Temperament, double BaseFreq) { return(69 + 12 * log2(Freq / BaseFreq)); }

// ####### ####### #######
// ####### CALCULOS:
// LINHA (y = b + x * a):
double Linex(double x, double a, double b) { return(b + x * a); }

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
double MiniForm(double n, double Omega)
{
	//double x = (Tau * Omega) * n; // Dependendo da formula, não é nescessario.
	//return (/*Formula: */sin(n * Omega)/**/);
	return Formula(1, Omega, n, 3, 0, 1);
	//return (NonStatWaveFunc(1.0 / (n + 1), 6.2831, n, 1, Omega, 0));
	//return (SimpleHarmOsc(90, 220, n, 0));
	//return (Sum(Omega, n, 1, 1, 21));
	/* Formulas interessantes:
	sin((Omega / 160) * pow(n, 3)) <------- Classico dos meus testes, muda a frequencia com x e muda direção em negativo.
	sin(x) ||| sin(x)+(tan(x*((sin((pow(x,3))/200)/4))))/4 ||| sin(x)+(cos(x*((sin((pow(x,3))/200)/4))))/4
	(sin(x) + ASerModulado) / 2 ||| sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	(((cos(x) + (sin(x * 7))/4)/1.25) + ASerModulado) / 2 ||| sin(pow(x,2)) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4
	sin(x) + (cos(x*((sin((pow(x, 3)) / 200) / 4)))) / 4 ||| (sin(x * 7) + ((cos(x * 14)) / 2) + (tan(x) / 7)) / 1.266666
	(sin(x * 28) + ((pow((cos(x * 12.5) / 2), (sin(x) / 2))) / 700)) / 1.166666 |||

	LOGISTIC FUNCTION:
	1/(1+pow(Exp, - 2 * n))

	FOURIER:
	Sum(1, n, 1, 1, 77) || VERIFICAR SE ESTA A FORMULA FOURIER NA SOMATÓRIA

	POLAR:
	en.wikipedia.org/wiki/File:Rose-rhodonea-curve-7x9-chart-improved.svg
	-- r = cos(7 * n) * Amp; // Rosa
	-- r = cos(0.8 * n) * (Amp * 0.97); // Rosa
	-- r = (Amp/8) * (n / (2 * Pi)); // Acho que espiral
	-- r = ((1/cos(n)) + Amp * cos(n)) / 3.5; // Conchoid of de Sluze
	-- r = pow(n, 0.5) * (Amp * 0.25); // Fermat's spiral
	-- r = Amp * ((Amp * sin(n)) / n); // Cochleoid
	-- r = (cos(n) * (pow(Exp, cos(n)) - (2 * cos(4 * n) - (pow(sin(n / 12), 5))))) * 0.125; // Butterfly
	-- r = (((sin((Amp* 5) * n) * (pow(Exp, sin(n)) / Exp)) - (2 * sin((Amp * 4) * n) - sin((Amp * 2) * n))) + Amp) * (Amp / 5); // Meu Butterfly
	-- r = Amp * (sin(14 + cos(n) * 7)); // Minha Rosa;
	
	PHISICA:
	NonStatWaveFunc(1.0 / (n + 1), 6.2831, n, 1, Omega, 0);

	MINHAS:
	FxPi(n, 7, 1)
	FxPi1(n, 7, 0.0714285)

	*/
}

// MINI FORMULA DA MODULAÇÃO:
double ModForm(double n, double Omega) { return((MiniForm(n, Omega) + 1) * 0.5); }
double ModForm(double n, double Rto, double Omega) { return((MiniForm(n, Omega) + 1) * Rto); }
double ModForm(double n, double Sum, double Rto, double Omega) { return((MiniForm(n, Omega) + Sum) * Rto); }

// Numerical integration: mid-ordinate rule:
double Integral(double a, double b, int n, double Omega)
{
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

// DERIVA:
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
		Form = ((4 / (Step * Pi))*sin((Step * Pi * x * m) / ((n + n - 1) * Pi))) / 2.333333;
		Sm += Form;

		//Formulas de interesse:
		/*
		SawFourier: ((4 / (Step * Pi))*sin((Step*Pi*x) / ((n + n - 1)*Pi))) / 2.333333
		SawFourier2: ((1 / (Step * Pi))*sin((Step*Pi*x) / ((n + n - 1)*Pi))) / 2.333333 || - 0.5 no Sum antes do return, esse que esta "Sum = Sum * a;"
		SqrFourier: ((4 / ((2* Step - 1) * Pi))*sin(((2 * Step - 1)*Pi*x) / ((n + n - 1)*Pi))) / 1.125 || Stp2 / 2
		TriFourier: ((8 / pow(Pi,2)) * (pow(-1,((2 * Step - 1 - 1) / 2.0)) / (pow((2 * Step - 1), 2)) * sin(((2* Step - 1) * Pi * x) / ((n + n - 1)*Pi)))) / 2.333333
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

double FourierSeries(double x, int Harmonics, double P, double Omega, double Integr, int IntIter)
{
	if (P == 0) { P = 0.000001; }
	double Cos, Sin;
	double Sum = 0, Form, an, bn, a0 = 0, b0 = 0;
	double IntSuma = 0, IntSumb = 0, dt = (1.0 * Integr - P) / IntIter;
	for (int i = 1; i <= IntIter; i++) { a0 += MiniForm(P + (i - 0.5) * dt, Omega) * dt; }
	a0 = (1.0 / P) * a0;
	for (int n = 0; n <= Harmonics; ++n) // LEMBRAR DE VERIFICAR SE STP2 NÃO ESTA MODIFICADO
	{
		// Integrais:
		for (int i = 1; i <= IntIter; i++)
		{
			Cos = cos(2 * Pi * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			Sin = sin(2 * Pi * (P + (i - 0.5) * dt) * ((n * 1.0) / P));
			IntSuma += (Cos * MiniForm(P + (i - 0.5) * dt, Omega)) * dt; // Ve se precisa do '* dt'
			IntSumb += (Sin * MiniForm(P + (i - 0.5) * dt, Omega)) * dt;
		}
		an = (2.0 / P) * IntSuma; bn = (2.0 / P) * IntSumb;
		if (n > 0) { Form = an * cos((2 * Pi * n * x) / P) + bn * sin((2 * Pi * n * x) / P); }
		else { Form = a0 * cos((2 * Pi * n * x) / P); }
		Sum += Form;
	}
	return((a0 / 2.0) + Sum);
}

// ### SEQUENCIAS:
// Aritimética:
vector<double> ArithSequence(double a, double d, int n) { vector<double> S{ a }; for (int k = 1; k < n; ++k) { S.push_back(S[0] + (d * k)); } return (S); }
double ArithSeqnth(double a, double d, int n) { return(a + d * (n - 1)); }
double ArithSeqSum(double a, double d, int n) { return(n * 0.5 * (2 * a + d * (n - 1))); }
//double ArithSeqProduct() {}

// Geométrica:
vector<double> GeoSequence(double a, double r, int n) { vector<double> S{ a }; for (int k = 1; k < n; ++k) { S.push_back(S[0] * pow(r, k)); } return (S); }
double GeoSeqnth(double a, double r, int n) { return(a * pow(3, n - 1)); }
double GeoSeqSum(double a, double r, int n) { return(a * ((1 - pow(r, n))/(1 - r))); }
double GeoSeqProduct(double a, double r, int n) { return(pow(sqrt(a*a*pow(r, n)), n + 1)); } // https://en.wikipedia.org/wiki/Geometric_progression#Product

// ### SERIES:
double Serie(int a1, int an)
{
	return (0);
}

// ### I THINK IT IS CALLED SIG FUNCTIONS:
// SIGMOID (ver variavel)
double Sigmoid(double x) { return (1 / (1 + (pow(Exp, -x)))); }

// RECTIFIER:
double Softplus(double x) { return(log(1 + pow(Exp, x))); }
double ReLU(double x) { if (x < 0) { return(0); } else return(x); }

// ### ESPECIAL:

// Find a periodic value from 'sine' through a 'margin_b' of 'frequencies' multiplied by 'a' on the line of specific 'Radian'; (use 'Value' in set { -1 <= Value <= 1) }:
// The math is just 'if (sin(Radian * a * b) == Value)'
vector<int> FindValueInSine(double a, int b0, int b1, double Value, double Radian)
{ vector<int> Return; for (int b = b0; b < b1; ++b) { if (sin(Radian * a * b) == Value) { Return.push_back(b); } } return(Return); }

// The same, but based on a music scale (MIDI):
vector<int> FindValueInSineinMIDI(double a, int MIDIini, int MIDIend, double Value, double Radian, int Temperament, double BaseFreq)
{ vector<int> Return; for (int M = MIDIini; M < MIDIend; ++M) { if (sin(Radian * a * MIDItoFreq(M, Temperament, BaseFreq)) == Value) { Return.push_back(M); } } return(Return); }

// The same, but based on a music scale (Frequency):
vector<double> FindValueInSineinFreq(double a, int FreqIni, int FreqEnd, double Increment, double Value, double Radian, int Temperament, double BaseFreq)
{ vector<double> Return; for (int f = FreqIni; f < FreqEnd; f += Increment) { if (sin(Radian * a * f) == Value) { Return.push_back(FreqtoMIDI(f, Temperament, BaseFreq)); } } return(Return); }

// ### MISC:
double EzSeqForm(double a, double b, double c, double d, double e) { return(pow(pow(a, b + c), d) / e); }

// ####### ####### ####### ####### ####### #######


class TestCalc
{
public:
	void Test()
	{
		cout << "Digite qual função:\n";
		cout << "| 1 = Formula | 2 = ModForm | 3 = MiniForm | 4 = Somação |\n";
		cout << "| 5 = Integral M-L-RRAM | 6 = IntegralAbs| 7 = Derivativos |\n";
		cout << "| 8 = Diff. Eq. 2nd Order |\n";
		cout << "#######\n MISC:\n";
		cout << "770 = BPM2ms | 771 = ms2BPM | 772 = ms2Freq | 773 = Ptrn2ms |\n";
		cout << "774 = Beats in ms | 775 = ms in Beats | 776 = Beats in Time |\n";
		cout << "880(m, s)/881(h, m, s) = Time in ms |\n";
		int Op; cin >> Op;

		if (Op == 1)
		{
			cout << "Formula(a, Frequencia, x, b, c, d);\n";
			double Opa, Opf, Opx, Opb, Opc, Opd;
			cout << "a: "; cin >> Opa; cout << "Omega: "; cin >> Opf;
			cout << "x: "; cin >> Opx; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc; cout << "d: "; cin >> Opd;
			cout << "RETORNO: " << Formula(Opa, Opf, Opx, Opb, Opc, Opd) << endl;
		}
		if (Op == 2)
		{
			cout << "ModForm(n, Omega);\n"; float Opn, Opf; cout << "n: "; cin >> Opn; cout << "Omega: "; cin >> Opf; cout << "RETORNO: " << ModForm(Opn, Opf) << endl;
		}
		if (Op == 3)
		{
			cout << "MiniForm(n, Omega);\n"; float Opn, Opf; cout << "n: "; cin >> Opn; cout << "Omega: "; cin >> Opf; cout << "RETORNO: " << MiniForm(Opn, Opf) << endl;
		}
		if (Op == 4)
		{
			cout << "Sum(n, x, a, Inicio, Fim);\n"; double Opn, Opx, Opa; int Opi, Opf;
			cout << "n: "; cin >> Opn; cout << "x: "; cin >> Opx; cout << "a: "; cin >> Opa; cout << "Inicio: "; cin >> Opi; cout << "Fim: "; cin >> Opf;
			cout << "RETORNO: " << Sum(Opn, Opx, Opa, Opi, Opf);
		}
		if (Op == 5)
		{
			cout << "IntgrlRAM(a, b, Iteracao, 1-2-3 OpRet);\n";
			double Opa, Opb; int Opi, Opo; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "Iterações: "; cin >> Opi; cout << "Omega: "; cin >> Opo;
			cout << "RETORNO: " << Integral(Opa, Opb, Opi, Opo) << endl;
		}
		if (Op == 6)
		{
			cout << "IntgrlAbs(a, b, Iteracao);\n";
			double Opa, Opb; int Opi; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "Iterações: "; cin >> Opi;
			cout << "RETORNO: " << IntgrlAbs(Opa, Opb, 0, Opi) << endl;
		}
		if (Op == 7)
		{
			cout << "double Derivative(x);\n"; double Opx, Opf; cout << "x: "; cin >> Opx; cout << "Omega.: "; cin >> Opf;
			cout << "RETORNO: " << Derivative(Opx, Opf) << endl;
		}
		if (Op == 8)
		{
			cout << "d2tdt2(x, Omega);\n"; double Opx, OpF; cout << "x: "; cin >> Opx; cout << "Omega.: "; cin >> OpF;
			cout << "RETORNO: " << d2xdt2(Opx, OpF) << endl;
		}

		// ####### MISC:

		if (Op == 770) { cout << "double BPM2ms(BPM);\n"; double Opb; cout << "BPM: "; cin >> Opb; cout << "RETORNO: " << BPM2ms(Opb) << endl; }
		if (Op == 771) { cout << "double ms2BPM(ms);\n"; double Opms; cout << "ms: "; cin >> Opms; cout << "RETORNO: " << ms2BPM(Opms) << endl; }
		if (Op == 772) { cout << "double ms2Freq(ms);\n"; double Opms; cout << "ms: "; cin >> Opms; cout << "RETORNO: " << ms2Freq(Opms) << endl; }
		if (Op == 773)
		{
			cout << "double Ptrn2ms(PSiz, Pn, BPM);\n"; double Ops, Opn, Opb; cout << "PSize: "; cin >> Ops; cout << "Pnum: "; cin >> Opn; cout << "BPM: "; cin >> Opb;
			cout << "RETORNO: " << Ptrn2ms(Ops, Opn, Opb) << endl;
		}
		if (Op == 774)
		{ cout << "double Beatsinms(ms, BPM);\n"; double Opms, Opb; cout << "ms: "; cin >> Opms; cout << "BPM: "; cin >> Opb; cout << "RETORNO: " << Beatsinms(Opms, Opb) << endl; }
		if (Op == 775)
		{ cout << "double msinBeats(n, BPM);\n"; double Opn, Opb; cout << "n: "; cin >> Opn; cout << "BPM: "; cin >> Opb; cout << "RETORNO: " << msinBeats(Opn, Opb) << endl; }
		if (Op == 776)
		{
			cout << "double BeatsinTime(Min, Sec, BPM);\n"; double Opm, Ops, Opb;
			cout << "m: "; cin >> Opm; cout << "s: "; cin >> Ops; cout << "BPM: "; cin >> Opb; cout << "RETORNO: " << BeatsinTime(Opm, Ops, Opb) << endl;
		}
		// #######
		if (Op == 880)
		{ cout << "double Time2ms(min, sec);\n"; double Opm, Ops; cout << "m: "; cin >> Opm; cout << "s: "; cin >> Ops; cout << "RETORNO: " << Time2ms(Opm, Ops) << endl; }
		if (Op == 881)
		{
			cout << "double Time2ms(Hr, Min, Sec);\n"; double Opm, Ops, Oph;
			cout << "m: "; cin >> Opm; cout << "s: "; cin >> Ops; cout << "h: "; cin >> Oph; cout << "RETORNO: " << Time2ms(Oph, Opm, Ops) << endl;
		}
		
	}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_