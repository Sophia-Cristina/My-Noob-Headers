#pragma once

#ifndef YSXPRINT_H
#define YSXPRINT_H

#include "ysxmath.h"

// #####################################################################################################################################

// #####################################################################################################################################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### TEXTOS #####################

// PRINT STRING LIKE A TEXT IN A NOTEPAD:
void PrintString(string S)
{
	ofstream oPrint("String.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { oPrint << S; } oPrint.close();
}
void PrintString(char S[])
{
	ofstream oPrint("String.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else { for (int n = 0; n < sizeof(S); ++n) { oPrint << S[n]; } } oPrint.close();
}

// PRINT CHAR AS IT NUMBER VALUE:
void PrintCharAsInt(string File, bool Spaces)
{
	vector<char> V;
	ifstream In(File); if (!In.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		while (!In.eof())
		{
			char C;
			In.read(&C, 1);
			V.push_back(C);
		}
	}
	In.close();
	ofstream oPrint("READ INT.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		if (Spaces) { for (int n = 0; n < V.size() - 1; ++n) { oPrint << (int)V[n] << " "; } }
		else { for (int n = 0; n < V.size() - 1; ++n) { oPrint << (int)V[n]; } }
		
	}
	oPrint.close();
}

// PRINT A VECTOR PLOT MADE WITH ASCII:
void PrintCharPlotter(char C, vector<double> V, int L)
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		double MaxAbs, MinAbs, Max = MaxVec(V), Min = MinVec(V);
		MaxMinVecAbs(V, MaxAbs, MinAbs);

		oPrint << "MAX AND MIN: " << Max << " | " << Min << "\n\n";
		cout << "MAX AND MIN: " << Max << " | " << Min << "\n\n";

		double md = MaxAbs - Max;
		for (int n = 0; n < L; ++n)
		{
			//double ValCeil = (MaxAbs * ((L - n + 1) / (double)L)), ValFloor = (MaxAbs * ((L - n) / (double)L));
			//double ValCeil = (Max * ((L - n + 1) / L)), ValFloor = (Max * ((L - n) / L));
			double ValCeil = (MaxAbs * ((L - n) / (double)L)), ValFloor = (MaxAbs * ((L - 1 - n) / (double)L));

			for (int m = 0; m < V.size(); ++m)
			{
				if (V[m] >= ValFloor - md && V[m] <= ValCeil - md)
				{
					oPrint << C << "|"; cout << C << "|";
				}
				else
				{
					oPrint << "_|"; cout << "_|";
				}
			}
			oPrint << " | " << ValFloor - md << " to " << ValCeil - md << " | ";
			cout << " | " << ValFloor - md << " to " << ValCeil - md << " | ";

			oPrint << endl;
			cout << endl;
		}
	}
	oPrint.close();
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### MÉTRICA #####################
// Print.open("Print.txt");
// if (!Print.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
void PrintMeterSecConvesor(double ms)
{
	ofstream oPrint("PrintMeterSecConvesor.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "ms to kmh: " << ms * 3.6 << " | "; oPrint << "ms to mile: " << ms / 0.44704 << " | ";
		oPrint << "ms to feet per sec: " << ms * 3.28084 << " | "; oPrint << "ms to knot: " << ms * 1.9438444924 << " | ";
	}
	oPrint.close();
}

// #####################################################################################################################################


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### MATEMÁTICAS #####################

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

void SmallEquation(double a, double b, double q)
{
	ofstream oPrint("SimpleEq.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		oPrint << "x =  b / a -> x = " << b << " / " << a << " =\n";
		oPrint << b / a << endl;
		oPrint << " a / b = " << a / b << endl;
		oPrint << "quantia * x = (b / a) * quantia = " << (b / a) * q << endl;
		oPrint << "(a / b) * quantia = " << (a / b) * q << "\n\n";
	}
	oPrint.close();
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### GEOMETRIA #####################

// Imprime Informações que possam ser adiquiridas atravéz de um lado 'a' e outro 'b', e com o 'c' baseado na hipotenusa destes:
void PrtTriInfo(double a, double b, double ang)
{
	ofstream oPrint("Print.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
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
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### VETORES #####################

// ############## PRINT VECTORS:
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
void PrintVector(vector<double> Vec, string FileName)
{
	ofstream oPrint(FileName); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
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

// ############## PLOT VECTOR:
/*void PrintCharPlotter(char C, vector<double> V, int L)
{
	double MaxAbs = MaxVecAbs(V), Max = MaxVec(V), Min = MinVec(V); Min *= -1;

	for (int n = 0; n < L; ++n)
	{
		oPrint
		for (int m = 0; m < V.size(); ++m)
		{

		}
	}
}*/


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### FRACTAIS #####################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### MUSICA #####################

// "Prt" significa "Print"
// Imprime Informações que possam ser adiquiridas atravéz de um BPM:
void PrtBPMInfo(double BPM, double Div, double Div0, double Increment, double Increment0)
{
	ofstream oPrint("BPMInfo.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		double Beatms = BPM2ms(BPM);
		oPrint << "BPM: " << BPM << " | Beat ms: " << Beatms << " | 4/4: " << Beatms * 4 << " | 16 * 4/4: " << 16 * (Beatms * 4) << endl;
		oPrint << "Minutes (4 * 4/4  = pattern Renoise):\n4/4: " << ms2Min(Beatms) * 4 << " | 4 * 4/4: " << 4 * (ms2Min(Beatms) * 4) << endl;
		oPrint << "8 * 4/4: " << 8 * (ms2Min(Beatms) * 4) << " | 16 * 4 / 4: " << 16 * (ms2Min(Beatms) * 4) << endl;
		oPrint << "Seconds:\nBeat: " << Dec2Sec(ms2Min(Beatms) - floor(ms2Min(Beatms))) << " | 4/4: " << Dec2Sec(ms2Min(Beatms * 4) - floor(ms2Min(Beatms * 4))) << endl;
		oPrint << "4 * (4/4) : " << Dec2Sec(ms2Min((Beatms * 4) * 4) - floor(ms2Min((Beatms * 4) * 4)));
		oPrint << " | 8 * (4/4) : " << Dec2Sec(ms2Min((Beatms * 4) * 8) - floor(ms2Min((Beatms * 4) * 8))) << endl;
		oPrint << "16 * 4/4: " << Dec2Sec(ms2Min((Beatms * 4) * 16) - floor(ms2Min((Beatms * 4) * 16))) << endl;
		oPrint << "Freq.: " << ms2Freq(Beatms) << "hz;\n";
		oPrint << "-------\nDivisões:\n";
		for (double n = 1; n <= Div; n += Increment) { double b = Beatms / n;  oPrint << "Beat: " << Beatms << " / " << n << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		oPrint << "!!!!!!!\n";
		for (double m = 1; m < Div0; m += Increment0)
		{
			for (double n = 1; n <= 10; n += Increment)
			{
				double b = (Beatms / n) + (Beatms / m);
				oPrint << "(" << Beatms << " / " << n << ") + Beat / " << m << " = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			oPrint << endl;
		}
		oPrint << "-------\nMultiplicações:\n";
		for (double n = 1; n <= Div; n += Increment) { double b = Beatms * n;  oPrint << "Beat: " << Beatms << " * " << n << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		oPrint << "!!!!!!!\n";
		for (double m = 1; m < Div0; m += Increment0)
		{
			for (double n = 1; n <= 10; n += Increment)
			{
				double b = (Beatms / n) + (Beatms * m);
				oPrint << "(" << Beatms << " / " << n << ") + (Beat * " << m << ") = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			oPrint << endl;
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
		for (int n = 0; n < SampleRateList.size(); ++n) { int Rate = SampleRateList[n]; oPrint << "ms per sample: " << 1000.0 / Rate; ++Count; if (Count >= 5) { oPrint << endl; Count = 0; } }
		for (int n = 0; n < SampleRateList.size(); ++n) { int Rate = SampleRateList[n]; oPrint << "2 * Pi per sample: " << Tau / Rate; ++Count; if (Count >= 5) { oPrint << endl; Count = 0; } }
	}
	oPrint.close();
}

// Print MTOF:
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
			if (MIDI == Temperament * CountOctave) { oPrint << " <- NOTE 'A'!\n"; ++CountOctave; }
			else { oPrint << endl; }
		}
		oPrint << "\n####### FIM! #######";
	}
	oPrint.close();
}

// ##############       ##############
// ############## RENOISE STUFFS ##############
// ##############       ##############

// Print a text which can be copied and pasted on the automation section of Renoise (2.8.0).
// You should normalize it before using. It adds ".txt" after "FileName":
void Vector2RenoiseAuto(vector<double> V, int Type, int LenghtInPatternLines, string FileName)
{
	if (V.size() > 0)
	{
		ofstream oPrint(FileName + ".txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
		else
		{
			// HEADER:
			oPrint << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Envelope doc_version=\"0\">\n";
			// TYPE:
			if (Type < 0) { Type = 0; } if (Type > 2) { Type = 2; }
			if (Type == 0) { oPrint << "  <PlayMode>Linear</PlayMode>\n"; }
			else if (Type == 1) { oPrint << "  <PlayMode>Points</PlayMode>\n"; }
			else { oPrint << "  <PlayMode>Curve</PlayMode>\n"; }
			int Length = LenghtInPatternLines * 256;
			oPrint << "  <Length>" << Length << "</Length>\n";
			oPrint << "  <ValueQuantum>0.0</ValueQuantum>\n  <Polarity>Unipolar</Polarity>\n";

			double Div = (double)Length / V.size();
			//V = NormalizeMod(V);
			int Used = -1;

			oPrint << "  <Points>\n";
			// POINTS START!
			for (int n = 0; n < V.size(); ++n)
			{
				int Index = 0;
				if (Div >= 1)
				{
					Index = round(n * Div);
					oPrint << "    <Point>" << Index << ", " << V[n] << "</Point>\n";
				}
				else if (Div < 1)
				{
					Index = floor(n * Div);
					if (Used != Index)
					{
						Used = Index;
						oPrint << "    <Point>" << Index << ", " << V[n] << "</Point>\n";
					}
				}

			}
			// POINTS END!
			oPrint << "  </Points>\n</Envelope>";
		}
		oPrint.close();
	}
}

// PRINT BLOCKS OF VECTORS:
void Vector2RenoiseAuto(vector<vector<double>> Vv, int Type, int LenghtInPatternLines, string FileName)
{ for (int n = 0; n < Vv.size(); ++n) { Vector2RenoiseAuto(Vv[n], Type, LenghtInPatternLines, FileName + to_string(n)); } }

// ##############       ##############
// ############## COLL: ##############
// ##############       ##############

// FibonacciWord binary into coll:
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

// FibonacciWord steps into coll
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

// Coordinates of FibonacciWord into coll:
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

// Any Vector to coll:
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

// Print Vector of Vectors into 'Line + n':
void VectorofVectors2Coll(vector<vector<float>> Coll, int Line)
{
	ofstream oPrint("Vector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		for (int n = 0; n < Coll.size(); ++n)
		{
			oPrint << Line + n << ",";
			for (int m = 0; m < Coll[n].size(); ++m)
			{
				oPrint << " " << Coll[n][m];
			}
			oPrint << ";";
		}
	}
	oPrint.close();
}

// Imprime x estapas de uma função:

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### CSV #####################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### ESPECIAIS #####################

// PRINT SOMETHING A NUMBER OF TIMES:
void PrintitNtimes()
{
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
	}
	oPrint.close();
}
// PLOT VECTOR WITH '#', SCALE THE SIZE WITH NUMBER OF LINES:
void PrintVectorPlot(vector<float> V, int Lines)
{
	if (Lines < 2) { Lines = 2; }
	ofstream oPrint("PrintVector.txt"); if (!oPrint.is_open()) { cout << "!!! Arquivo não foi aberto. !!!" << endl; }
	else
	{
		float Max, Min; MaxMinVec(V, Max, Min);
		double d = (Max - Min) / Lines;

		for (int n = 0; n < Lines; ++n)
		{
			double Ceil = d * n;       // /_\ // 1 - 0    | A linha que não pode pasar.
			double Room = d * (n + 1); // |_| //   0.5    | O espaço que cada linha ocupa (se 'd' for igual a '0.5')
			double Floor = Max - Room; // ''' // 1 - 0.5  | O ponto que começa a linha inferior, tipo apartamento
			oPrint << Max - d * n << " |";
			for (int m = 0; m < V.size(); ++m) { if (V[m] > Floor && V[m] < Max - Ceil) { oPrint << "#|"; } else { oPrint << "_|"; } }
			oPrint << endl;
		}
	}
	oPrint.close();
}

// #####################################################################################################################################



// ################################################# FIM ####################################################################################

#endif // SCPARSE_