#pragma once

#ifndef YSXPRINT_H
#define YSXPRINT_H

#include "ysxmath.h"

using namespace std;

// #####################################################################################################################################
// ####### VARIAVEIS:
ifstream iPrint;
//ofstream oPrint;
int Begin, End;

// #####################################################################################################################################
// ####### FUNÇÔES:
void BegEnd()
{
	iPrint.open("Print.txt", ios::ate);
	End = iPrint.tellg();
	iPrint.seekg(0, ios::beg);
	Begin = iPrint.tellg();
	iPrint.close();
}

// #####################################################################################################################################
// ####### MÉTRICA:
// Print.open("Print.txt");
// if (!Print.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
void PrintMeterSecConvesor(double ms)
{
	ofstream oPrint("PrintMeterSecConvesor.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else {
		oPrint << "ms to kmh: " << ms * 3.6 << " | "; oPrint << "ms to mile: " << ms / 0.44704 << " | ";
		oPrint << "ms to feet per sec: " << ms * 3.28084 << " | "; oPrint << "ms to knot: " << ms * 1.9438444924 << " | ";
	}
	oPrint.close();
}

// ####### MUSICA:
// "Prt" significa "Print"
// Imprime Informações que possam ser adiquiridas atravéz de um BPM:
void PrtBPMInfo(double BPM, int Div, int Div0)
{
	ofstream oPrint("PrtBPMInfo.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		double Beatms = BPM2ms(BPM);
		BegEnd(); oPrint.seekp(End);
		oPrint << "\nBPM: " << BPM << " | Beat ms: " << Beatms << " | 4/4: " << Beatms * 4 << " | 16 * 4/4: " << 16 * (Beatms * 4) << endl;
		oPrint << "Time, minute: 4/4: " << ms2Min(Beatms) * 4 << "| Time, minute: 16 * 4/4: " << 16 * (ms2Min(Beatms) * 4) << endl;
		oPrint << "Dec2Sec: " << Dec2Sec(ms2Min(Beatms) - floor(ms2Min(Beatms))) << " | Dec2Sec (4/4): " << Dec2Sec(ms2Min(Beatms * 4) - floor(ms2Min(Beatms * 5)));
		oPrint << " | Dec2Sec (16 * 4/4): " << Dec2Sec(ms2Min((Beatms * 4) * 16) - floor(ms2Min((Beatms * 4) * 16))) << endl;
		oPrint << "Freq.:" << ms2Freq(Beatms) << endl;
		oPrint << "-------\nDivisões:\n";
		for (int n = 1; n <= Div; ++n) { oPrint << "Beat: " << Beatms << " / " << n << " = " << Beatms / n * 1.0 << endl; }
		for (int m = 1; m < Div0; ++m)
		{
			for (int n = 1; n <= 10; ++n) { oPrint << "(" << Beatms << " / " << n << ") + (Beat * 1 / " << m << ") = " << (Beatms / n * 1.0) + (Beatms * (1.0 / m)) << endl; }
		}
	}
	oPrint.close();
}

// Imprime Informações que possam ser adiquiridas atravéz de milisegundos:
void PrtmsInfo(double ms, int Div)
{
	ofstream oPrint("PrtmsInfo.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "ms em minutos: " << ms2Min(ms) << " | ms em BPM: " << ms2BPM(ms) << " | ms em freq.: " << ms2Freq(ms) << endl;
	}
	oPrint.close();
}

// Imprime informações sobre sample rate:
void SampleRateInfo()
{
	ofstream oPrint("SampleRateInfo.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		int Count = 0;
		for (int n = 0; n < SampleRateList.size(); ++n) { int Rate = SampleRateList[n]; oPrint << "hz: " << Rate; ++Count; if (Count >= 5) { oPrint << endl; Count = 0; } }
		for (int n = 0; n < SampleRateList.size(); ++n)	{ int Rate = SampleRateList[n]; oPrint << "ms per sample: " << 1000.0 / Rate; ++Count; if (Count >= 5) { oPrint << endl; Count = 0; } }
		for (int n = 0; n < SampleRateList.size(); ++n) { int Rate = SampleRateList[n]; oPrint << "2 * Pi per sample: " << Tau / Rate; ++Count; if (Count >= 5) { oPrint << endl; Count = 0; } }
	}
	oPrint.close();
}

void MtoFPrint(int MIDImin, int MIDImax, int Temperament, double BaseFreq)
{
	ofstream oPrint("MtoFPrint.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "####### MIDI to Frequency #######\n\n";
		oPrint << "Temperament: " << Temperament << " | Base Freq.: " << BaseFreq << "\n\n";
		int CountOctave = 0;
		for (int MIDI = MIDImin; MIDI <= MIDImax; ++MIDI)
		{
			oPrint << "MIDI: " << MIDI << " | FREQ.: " << MIDItoFreq(MIDI, Temperament, BaseFreq);
			if (MIDI == Temperament * CountOctave) { oPrint << " <- NOTE 'A'!\n"; ++CountOctave; } else { oPrint << endl; }
		}
		oPrint << "\n####### FIM! #######";
	}
	oPrint.close();
}

// #####################################################################################################################################
// ####### MATEMÁTICAS:
// Imprime numero elevado a 'n':
void PrintPowerandRoot(double n, int From, int To)
{
	if (From > To) { int Tmp = From; From = To; To = Tmp; }
	ofstream oPrint("PowerRoot.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		vector<long> pn = PowerOfn(n, From, To);
		oPrint << "#####################\n";
		for (int m = 0; m < pn.size(); ++m)
		{
			oPrint << n << "^" << From + m << " = " << pn[m] << endl;
		}
		pn = PowerByn(n, From, To);
		oPrint << "#####################\n";
		for (int m = 0; m < pn.size(); ++m)
		{
			oPrint << From + m << "^" << n << " = " << pn[m] << endl;
		}
		vector<double> rn = nRootOfm(n, From, To);
		oPrint << "#####################\n";
		for (int m = 0; m < pn.size(); ++m)
		{
			oPrint << n << "root(" << From + m << ") = " << rn[m] << endl;
		}
		rn = mRootOfn(n, From, To);
		oPrint << "#####################\n";
		for (int m = 0; m < pn.size(); ++m)
		{
			oPrint << From + m << "root(" << n << ") = " << rn[m] << endl;
		}
	}
	oPrint.close();
}

// Imprime multiplos e divisões:
void PrintMult(double x, double Ini, double End, double Div)
{
	ofstream oPrint("PrintMult.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "####### MULTIPLICAÇÕES:\n\n";
		for (double a = Ini; a <= End; a += 1.0 / Div)
		{
			oPrint << x << " * " << a << " = " << x * a << endl;
		}
		oPrint << "####### FIM!\n";
	}
	oPrint.close();
}
void PrintDiv(double x, double Ini, double End, double Div)
{
	ofstream oPrint("PrintDiv.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "####### DIVIÕES:\n\n";
		for (double a = Ini; a <= End; a += 1.0 / Div)
		{
			oPrint << x << " / " << a << " = " << x / a << endl;
		}
		oPrint << "####### FIM!\n";
	}
	oPrint.close();
}

// #####################################################################################################################################
// ####### GEOMETRIA:
// Imprime Informações que possam ser adiquiridas atravéz de um lado 'a' e outro 'b', e com o 'c' baseado na hipotenusa destes:
void PrtTriInfo(double a, double b, double ang)
{
	ofstream oPrint("Print.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		BegEnd(); oPrint.seekp(End);
		Triangulo Tri(a, b, ang);
		cout << "0: NoTypeLgt; 1: Equilateral; 2: Isoceles; 3: Scalene;\n";
		cout << "0: NoTypeAng; 1: Right; 2: Acute; 3: Obtuse;\n";
		cout << "Tipo triangulo = " << (int)Tri.LnghtType << " & " << (int)Tri.AngType << endl;
		cout << "a: " << Tri.a << " | Alpha: " << Tri.Alpha << " | BisA: " << Tri.BisA << endl;
		cout << "b: " << Tri.b << " | Beta: " << Tri.Beta << " | BisB: " << Tri.BisB << endl;
		cout << "c: " << Tri.c << " | Gamma: " << Tri.Gamma << " | BisC: " << Tri.BisC << endl;
		cout << "Alt: " << Tri.Alt << " | Base: " << Tri.Base << " | Base0: " << Tri.Base0 << endl;
		cout << "Circumcentro: x: " << Tri.Circumcenter.x << " | y: " << Tri.Circumcenter.y << endl;
		oPrint << "0: NoTypeLgt; 1: Equilateral; 2: Isoceles; 3: Scalene;\n";
		oPrint << "0: NoTypeAng; 1: Right; 2: Acute; 3: Obtuse;\n";
	}
	oPrint.close();
}

// #####################################################################################################################################
// ####### VETORES:
// ### PRINT VECTORS:
void PrintVector(vector<int> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<long> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<float> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<double> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<bool> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<string> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
void PrintVector(vector<char> Vec)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { oPrint << n << ": " << Vec[n] << endl; } } oPrint.close();
}
// ###

// #####################################################################################################################################
// ####### FRACTAIS:

// #####################################################################################################################################
// ####### COLL:
void FiboWord2Coll(int Iter, bool CollMsn, int Line)
{
	ofstream oPrint("FiboWord.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		string Word = FiboWord(Iter);
		if (!CollMsn) { oPrint << Line << ","; }
		for (int n = 0; n < Word.size(); ++n)
		{
			if (!CollMsn) { oPrint << " " << Word[n]; } else { oPrint << Word[n] << " "; }
		}
		if (!CollMsn) { oPrint << ";"; }
	}
	oPrint.close();
}

void FiboWordFrac2Coll(int Iter, bool CollMsn, int Line)
{
	ofstream oPrint("FiboFrac.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		enum { Up, Down, Left, Right };
		static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
		int dir = Up;
		string Word = FiboWord(Iter);
		if (!CollMsn) { oPrint << Line << ","; }
		for (size_t n = 1; n < Word.size(); ++n)
		{
			if (dir == Up) if (!CollMsn) { oPrint << " " << Up; } else { oPrint << Up << " "; }
			else if (dir == Right)  if (!CollMsn) { oPrint << " " << Right; } else { oPrint << Right << " "; }
			else if (dir == Down)  if (!CollMsn) { oPrint << " " << Down; } else { oPrint << Down << " "; }
			else if (dir == Left)  if (!CollMsn) { oPrint << " " << Left; }	else { oPrint << Left << " "; }

			if (Word.at(n) == '0') dir = nextDir[n % 2][dir];
		}
		oPrint << ";";
	}
	oPrint.close();
}

void FiboWordFracCoord2Coll(int Iter, bool CollMsn, int Line, float Dist, bool xory, string Name)
{
	ofstream oPrint(Name); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		vector<Point> Pt = FiboWordFrac(FiboWord(Iter));
		if (!CollMsn) { oPrint << Line << ","; }
		for (size_t n = 0; n < Pt.size(); ++n)
		{
			if (!CollMsn) { oPrint << " "; if (!xory) { oPrint << Pt[n].x * Dist; } }
			if (!CollMsn) { oPrint << " "; if (xory) { oPrint << Pt[n].y * Dist; } }
			if (CollMsn) { if (!xory) { oPrint << Pt[n].x * Dist; } oPrint << " "; }
			if (CollMsn) { if (xory) { oPrint << Pt[n].y * Dist; } oPrint << " "; }
		}
		oPrint << ";";
	}
	oPrint.close();
}

void Vector2Coll(vector<float> Coll, bool CollMsn, int Line)
{
	ofstream oPrint("Vector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		if (!CollMsn) { oPrint << Line << ","; }
		for (int n = 0; n < Coll.size(); ++n)
		{
			if (!CollMsn) { oPrint << " " << Coll[n]; }
			else { oPrint << Coll[n] << " "; }
		}
		if (!CollMsn) {	oPrint << ";"; }
	}
	oPrint.close();
}

// Imprime x estapas de uma função:

// #####################################################################################################################################
// ####### OPENNN:

// MAKE A SINGLE LINE .csv DATASET FOR OPENNN:
void MakeDataSetFromVector(vector<double> Vector)
{
	ofstream oPrint("DATA.csv"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		for (int n = 0; n < Vector.size(); ++n)
		{
			oPrint << Vector[n] << ";";
		}
	}
	oPrint.close();
}

// MAKES A DATA SET MATRIX:
void MakeDataSetMatrix(vector<double> Vector, int Width)
{
	ofstream oPrint("DATA.csv"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		int Count = 0;
		for (int n = 0; n < Vector.size(); ++n)
		{
			oPrint << Vector[n] << ";";
			++Count;
			if (Count == Width - 1) { oPrint << endl; Count = 0; }
		}
	}
	oPrint.close();
}

// MAKES A DATASET FOR OPENNN THAT CONSIDERS EACH CHANNEL:
// FOR FULL UNDERSTANDING OF THE VALUES, CONSIDER EACH 3 ITENS AS ONE COLOR! For example, 1;0.5;0.5;1;1;1;0.25;0.33;0.5; is a 1x3 image.
void MakeDataSetRGBMatrix(vector<Point3DFlt> Vector, int Width, bool csvORdat)
{
	ofstream oPrint; bool Goodtogo = false;
	if (!csvORdat) { oPrint.open("DATA.csv"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; } else { Goodtogo = true; } }
		else { oPrint.open("DATA.dat"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; } else { Goodtogo = true; }
	}
	if (Goodtogo)
	{
		int Count = 0;
		for (int n = 0; n < Vector.size(); ++n)
		{
			if (!csvORdat) { oPrint << Vector[n].x << ";" << Vector[n].y << ";" << Vector[n].z << ";"; }
			else { oPrint << Vector[n].x << " " << Vector[n].y << " " << Vector[n].z << " "; }
			++Count;
			if (Count == Width) { oPrint << endl; Count = 0; }
		}
	}
	oPrint.close();
}

// MAKES A DATASET IN A SINGLE LINE WITH A TARGET INPUT IN THE BEGINNING:
void MakeDataSetRGBLine(vector<Point3DFlt> Vector, int Target)
{
	ofstream oPrint("DATA.csv"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << Target; for (int n = 0; n < Vector.size(); ++n) { oPrint << "," << Vector[n].x << "," << Vector[n].y << "," << Vector[n].z; } }
	oPrint.close();
}

// MAKES A DATASET FOR AUTOENCODER
void MakeAutoEncoderDataSetRGBLine(vector<Point3DFlt> Vector)
{
	ofstream oPrint("DATA.csv"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		int Count = 0, TotalSize = Vector.size() * 2;
		for (int InOut = 0; InOut < 2; ++InOut)
		{
			for (int n = 0; n < Vector.size(); ++n)
			{
				oPrint << Vector[n].x << "," << Vector[n].y << "," << Vector[n].z;
				if (Count < TotalSize - 1) { oPrint << ","; }
				++Count;
			} 
		}
		oPrint << endl; Count = 0;
		for (int InOut = 0; InOut < 2; ++InOut)
		{
			for (int n = 0; n < Vector.size(); ++n)
			{
				oPrint << Vector[n].x << "," << Vector[n].y << "," << Vector[n].z;
				if (Count < TotalSize - 1) { oPrint << ","; }
				++Count;
			}
		}
	}
	oPrint.close();
}


// ################################################# FIM ####################################################################################

#endif // SCPARSE_
