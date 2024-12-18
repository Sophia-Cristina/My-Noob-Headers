#pragma once

#ifndef YSXPRINT_H
#define YSXPRINT_H

#include "ysxText.h"

// #####################
// ####### By Sophia Cristina
// ####### Header made to print useful '.txt' files and to std::cout.
// #####################

// ATTENTION: There is a lot of very old bad code here!

// #####################################################################################################################################
// ##################### COUT #####################

// COUT TEXT:
void ysxCOUT_Text(std::string Filename)
{
	std::string Line; std::ifstream Data(Filename); if (!Data.is_open()) { std::cout << "! NOT OPEN !\n"; }
	else { while (getline(Data, Line)) { std::cout << Line << std::endl; } } Data.close();
}

// COUT VECTOR:
template <class T_> void ysxCOUT_Array(T_* Ini, size_t Size) { for (size_t n = 0; n < Size; ++n) { std::cout << n << ": " << Ini[n] << std::endl; } }
template <class T_> void ysxCOUT_Vector(std::vector<T_> Vec)
{
	for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << std::endl; }
}
template <class T_> void ysxCOUT_Vector(std::vector<Point<T_>> Vec)
{
	for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << std::endl; }
}
template <class T_> void ysxCOUT_Vector(std::vector<Point3D<T_>> Vec)
{
	for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << std::endl; }
}

// COUT VECTOR WITH COLLUMS:
template <class T_> void ysxCOUT_Vector(std::vector<T_> Vec, size_t Cols)
{
	for (size_t n = 0; n < Vec.size(); ++n) { std::cout << n << ": " << Vec[n] << " | "; if (n % Cols == Cols - 1) { std::cout << std::endl; } }
}
template <class T_> void ysxCOUT_Vector(std::vector<Point<T_>> Vec, size_t Cols)
{
	for (size_t n = 0; n < Vec.size(); ++n)
	{
		std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " ";
		if (n % Cols == Cols - 1) { std::cout << std::endl; }
	}
}
template <class T_> void ysxCOUT_Vector(std::vector<Point3D<T_>> Vec, size_t Cols)
{
	for (size_t n = 0; n < Vec.size(); ++n)
	{
		std::cout << n << ".x: " << Vec[n].x << " | .y: " << Vec[n].y << " | .z: " << Vec[n].z << " ";
		if (n % Cols == Cols - 1) { std::cout << std::endl; }
	}
}

// COUT STRING AS UINT:
void ysxCOUT_StringUInt(std::string Str) { uint16_t i; for (size_t n = 0; n < Str.size(); ++n) { i = Str[n]; std::cout << n << ": " << i << std::endl; } }
void ysxCOUT_StringUInt(std::string Str, size_t Cols)
{
	uint16_t i; for (size_t n = 0; n < Str.size(); ++n) { i = Str[n]; std::cout << n << ": " << i << " "; if (n % Cols == Cols - 1) { std::cout << std::endl; } }
}

// #####################################################################################################################################
 
// #####################################################################################################################################
// ##################### TEXTOS #####################

// PRINT STRING LIKE A TEXT IN A NOTEPAD:
void ysxPRNTTXT_String(std::string S) { std::ofstream O("String.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; } else { O << S; } O.close(); }
void ysxPRNTTXT_String(std::string S, std::string File) { std::ofstream O(File); if (!O.is_open()) { std::cerr << "File error" << std::endl; } else { O << S; } O.close(); }
void ysxPRNTTXT_String(char * S, size_t Size)
{
	std::ofstream O("String.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else { for (int n = 0; n < Size; ++n) { O << S[n]; } } O.close();
}

// PRINT CHAR AS IT NUMBER VALUE (MAKE IT WITHOUT PUSH BACK):
void ysxPRNTTXT_CharAsInt(std::string S, std::string outFile, bool Spaces = 1)
{
	std::ofstream O(outFile);
	if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		for (size_t n = 0; n < S.size(); ++n) { O << (short)S[n]; if (Spaces) { O << " "; } }
	}
	O.close();
}
void ysxPRNTTXT_CharAsIntFromFile(std::string inFile, std::string outFile, bool Spaces = 1)
{
	std::ifstream In(inFile); std::ofstream O(outFile);
	if (!In.is_open() && !O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{ 
		while (!In.eof()) { uint8_t C; In.read((char*)&C, 1); O << (short)C; if (Spaces) { O << " "; } }
	}
	In.close(); O.close();
}

// PRINT A VECTOR PLOT MADE WITH ASCII:
void ysxPRNTTXT_CharPlotter(char C, std::vector<double> V, size_t L)
{
	std::ofstream O("PrintVector.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		double MaxAbs, MinAbs, Max = ysxVEC_MaxVec(V), Min = ysxVEC_MinVec(V);
		ysxVEC_MaxMinVecAbs(V, MaxAbs, MinAbs);

		O << "MAX AND MIN: " << Max << " | " << Min << "\n\n";
		std::cout << "MAX AND MIN: " << Max << " | " << Min << "\n\n";

		double md = MaxAbs - Max;
		for (uint64_t n = 0; n < L; ++n)
		{
			//double ValCeil = (MaxAbs * ((L - n + 1) / (double)L)), ValFloor = (MaxAbs * ((L - n) / (double)L));
			//double ValCeil = (Max * ((L - n + 1) / L)), ValFloor = (Max * ((L - n) / L));
			double ValCeil = (MaxAbs * ((L - n) / (double)L)), ValFloor = (MaxAbs * (((double)L - 1 - n) / L));

			for (uint64_t m = 0; m < V.size(); ++m)
			{
				if (V[m] >= ValFloor - md && V[m] <= ValCeil - md) { O << C << "|"; std::cout << C << "|"; }
				else { O << "_|"; std::cout << "_|"; }
			}
			O << " | " << ValFloor - md << " to " << ValCeil - md << " | ";
			std::cout << " | " << ValFloor - md << " to " << ValCeil - md << " | ";

			O << std::endl;
			std::cout << std::endl;
		}
	}
	O.close();
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### METRICS #####################

void ysxPRNTTXT_MeterSecConvesor(double ms)
{
	std::ofstream O("PrintMeterSecConversor.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "ms to kmh: " << ms * 3.6 << " | "; O << "ms to mile: " << ms / 0.44704 << " |\n";
		O << "ms to feet per sec: " << ms * 3.28084 << " | "; O << "ms to knot: " << ms * 1.9438444924 << " | ";
	}
	O.close();
}

// #####################################################################################################################################
// ##################### MATHS #####################

/* PRINT:
 'n^From, ..., n^To; From^n, ..., To^n;'
 'n-root(from), ..., n-root(To); From-root(n), ..., To-root(n);'*/
void ysxPRNTTXT_PowRoot(double x, int From, int To)
{
	if (From > To) { int Tmp = From; From = To; To = Tmp; }
	std::ofstream O("PowerRoot.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "#####################\n";
		std::vector<double> pn = ysxVEC_PowerOfn<double>(x, From, To);
		for (size_t n = 0; n < pn.size(); ++n) { O << x << "^" << From + n << " = " << pn[n] << std::endl; }
		O << "#####################\n";
		pn = ysxVEC_PowerByn<double>(x, From, To);
		for (size_t n = 0; n < pn.size(); ++n) { O << From + n << "^" << x << " = " << pn[n] << std::endl;	}
		
		O << "#####################\n";
		std::vector<double> rn = ysxVEC_nRootOfm<double>(x, From, To);
		for (size_t n = 0; n < pn.size(); ++n)	{ O << x << "-root(" << From + n << ") = " << rn[n] << std::endl; }
		O << "#####################\n";
		rn = ysxVEC_mRootOfn<double>(x, From, To);
		for (size_t n = 0; n < pn.size(); ++n) { O << From + n << "-root(" << x << ") = " << rn[n] << std::endl; }
	}
	O.close();
}

// ####### MULTIPLICATIONS AND DIVISIONS #######

void ysxPRNTTXT_Mult(double x, double Ini, double End, double Inc)
{
	std::ofstream O("PrintMult.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "####### MULTIPLICATIONS:\n\n";
		for (double a = Ini; a <= End; a += Inc) { O << x << " * " << a << " = " << x * a << std::endl; }
		O << "####### END!\n";
	}
	O.close();
}
void ysxPRNTTXT_Div(double x, double Ini, double End, double Inc)
{
	std::ofstream O("Div.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "####### DIVISIONS:\n\n";
		for (double a = Ini; a <= End; a += Inc)
		{
			O << x << " / " << a << " = " << x / a << '\n';
			O << a << " / " << x << " = " << a / x << '\n';
		}
		O << "####### END!\n";
	}
	O.close();
}

void ysxPRNTTXT_SmallEq(double a, double b, double c)
{
	std::ofstream O("!SimpleEq.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "x =  b / a -> x = " << b << " / " << a << " =\n";
		O << b / a << '\n';
		O << " a / b = " << a / b << '\n';
		O << "c * x = c * b / a = " << c * b / a << '\n';
		O << "c * a / b = " << c * a / b << "\n\n";
	}
	O.close();
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### GEOMETRIA #####################

// Imprime Informa��es que possam ser adiquiridas atrav�z de um lado 'a' e outro 'b', e com o 'c' baseado na hipotenusa destes:
void ysxPRNTTXT_TriInfo(double a, double b, double ang)
{
	std::ofstream O("Print.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		ysxTRI_Triangle Tri(a, b, ang);
		O << "0: NoTypeLgt; 1: Equilateral; 2: Isoceles; 3: Scalene;\n";
		O << "0: NoTypeAng; 1: Right; 2: Acute; 3: Obtuse;\n";
		O << "Tipo triangulo = " << (int)Tri.LnghtType << " & " << (int)Tri.AngType << std::endl;
		O << "a: " << Tri.a << " | Alpha: " << Tri.Alpha << " | BisA: " << Tri.BisA << std::endl;
		O << "b: " << Tri.b << " | Beta: " << Tri.Beta << " | BisB: " << Tri.BisB << std::endl;
		O << "c: " << Tri.c << " | Gamma: " << Tri.Gamma << " | BisC: " << Tri.BisC << std::endl;
		O << "Alt: " << Tri.Height << " | Base: " << Tri.Base << " | Base0: " << Tri.Base0 << std::endl;
		O << "Circumcentro: x: " << Tri.Circumcenter.x << " | y: " << Tri.Circumcenter.y << std::endl;
	}
	O.close();
}

// #####################################################################################################################################

// ##################### FRACTAIS #####################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### VETORES #####################

// ############## PRINT VECTORS:
template <class T_>
void ysxPRNTTXT_Vector(std::vector<T_> Vec)
{
	std::ofstream O("PrintVector.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else { O << "VECTOR: \n\n"; for (int n = 0; n < Vec.size(); ++n) { O << n << ": " << Vec[n] << std::endl; } } O.close();
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### MUSIC #####################

/*Print information from a given BPM.
It have two numbers for division and multiplication, each number begins at '1' and end at "< End".
Each loop the numbers are incremented by "+= Inc".*/
void ysxPRNTTXT_BPMInfo(double BPM, double End0, double End1, double Inc0, double Inc1)
{
	std::ofstream O("BPMInfo.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		double Beatms = BPM2ms(BPM);
		O << "BPM: " << BPM << " | Beat ms: " << Beatms << " | 4/4: " << Beatms * 4 << " | 16 * 4/4: " << 16 * (Beatms * 4) << std::endl;
		O << "Minutes (4 * 4/4  = pattern Renoise):\n4/4: " << ms2Min(Beatms) * 4 << " | 4 * 4/4: " << 4 * (ms2Min(Beatms) * 4) << std::endl;
		O << "8 * 4/4: " << 8 * (ms2Min(Beatms) * 4) << " | 16 * 4 / 4: " << 16 * (ms2Min(Beatms) * 4) << std::endl;
		O << "Seconds:\nBeat: " << Dec2Sec(ms2Min(Beatms) - floor(ms2Min(Beatms))) << " | 4/4: " << Dec2Sec(ms2Min(Beatms * 4) - floor(ms2Min(Beatms * 4))) << std::endl;
		O << "4 * (4/4) : " << Dec2Sec(ms2Min((Beatms * 4) * 4) - floor(ms2Min((Beatms * 4) * 4)));
		O << " | 8 * (4/4) : " << Dec2Sec(ms2Min((Beatms * 4) * 8) - floor(ms2Min((Beatms * 4) * 8))) << std::endl;
		O << "16 * 4/4: " << Dec2Sec(ms2Min((Beatms * 4) * 16) - floor(ms2Min((Beatms * 4) * 16))) << std::endl;
		O << "Freq.: " << ms2Freq(Beatms) << "hz;\n";
		O << "\n\n---------------------\n\nDivisions:\n";
		for (double x = 1; x <= End0; x += Inc0) { double b = Beatms / x;  O << "Beat: " << Beatms << " / " << x << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		O << "!!!!!!!\n";
		for (double y = 1; y < End1; y += Inc1)
		{
			for (double x = 1; x < End0; x += Inc0)
			{
				double b = (Beatms / x) + (Beatms / y);
				O << "(" << Beatms << " / " << x << ") + Beat / " << y << " = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			O << std::endl;
		}
		O << "\n\n---------------------\n\nMultiplications:\n";
		for (double x = 1; x <= End0; x += Inc0) { double b = Beatms * x;  O << "Beat: " << Beatms << " * " << x << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		O << "!!!!!!!\n";
		for (double y = 1; y < End1; y += Inc1)
		{
			for (double x = 1; x < End0; x += Inc0)
			{
				double b = (Beatms / x) + (Beatms * y);
				O << "(" << Beatms << " / " << x << ") + (Beat * " << y << ") = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			O << std::endl;
		}
	}
	O.close();
}

// Imprime Informa��es que possam ser adiquiridas atrav�z de milisegundos:
void ysxPRNTTXT_PrtmsInfo(double ms, double Div, double Div0, double Inc, double Inc0)
{
	std::ofstream O("PrtmsInfo.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "ms as minutes: " << ms2Min(ms) << " | ms as BPM: " << ms2BPM(ms) << " | ms as freq.: " << ms2Freq(ms) << std::endl;
		O << "4 beats (ms): " << ms * 4 << " | 4 * 4/4: " << 4 * ms * 4 << " | 16 * 4 / 4: " << 16 * ms * 4 << std::endl;
		O << "Minutes (4 * 4/4  = pattern Renoise):\n4/4: " << ms2Min(ms) * 4 << " | 4 * 4/4: " << 4 * (ms2Min(ms) * 4) << std::endl;
		O << "8 * 4/4: " << 8 * (ms2Min(ms) * 4) << " | 16 * 4 / 4: " << 16 * (ms2Min(ms) * 4) << std::endl;
		O << "Freq.: " << ms2Freq(ms) << "hz;\n";
		O << "-------\nDivisions:\n";
		for (double n = 1; n <= Div; n += Inc) { double b = ms / n;  O << "Beat: " << ms << " / " << n << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		O << "!!!!!!!\n";
		for (double m = 1; m < Div0; m += Inc0)
		{
			for (double n = 1; n <= 10; n += Inc)
			{
				double b = (ms / n) + (ms / m);
				O << "(" << ms << " / " << n << ") + Beat / " << m << " = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			O << std::endl;
		}
		O << "-------\nMultiplications:\n";
		for (double n = 1; n <= Div; n += Inc) { double b = ms * n;  O << "Beat: " << ms << " * " << n << " = " << b << " || " << ms2Freq(b) << "hz;\n"; }
		O << "!!!!!!!\n";
		for (double m = 1; m < Div0; m += Inc0)
		{
			for (double n = 1; n <= 10; n += Inc)
			{
				double b = (ms / n) + (ms * m);
				O << "(" << ms << " / " << n << ") + (Beat * " << m << ") = " << b << " || " << ms2Freq(b) << "hz;\n";
			}
			O << std::endl;
		}
	}
	O.close();
}

// Imprime informa��es sobre sample rate:
void ysxPRNTTXT_SampleRateInfo()
{
	std::ofstream O("SampleRateInfo.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		unsigned int List[21] = YSXTABLE_SAMPLERATES;
		int Count = 0;
		for (int n = 0; n < 21; ++n) { int Rate = List[n]; O << "hz: " << Rate; ++Count; if (Count >= 5) { O << std::endl; Count = 0; } }
		for (int n = 0; n < 21; ++n) { int Rate = List[n]; O << "ms per sample: " << 1000.0 / Rate; ++Count; if (Count >= 5) { O << std::endl; Count = 0; } }
		for (int n = 0; n < 21; ++n) { int Rate = List[n]; O << "2 * Pi per sample: " << TAU / Rate; ++Count; if (Count >= 5) { O << std::endl; Count = 0; } }
	}
	O.close();
}

// Print MTOF:
void ysxPRNTTXT_MtoF(int MIDImin, int MIDImax, int Temperament, double BaseFreq)
{
	std::ofstream O("MtoFPrint.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		O << "####### MIDI to Frequency #######\n\n";
		O << "Temperament: " << Temperament << " | Base Freq.: " << BaseFreq << "\n\n";
		uint8_t Oct = 0;
		for (int MIDI = MIDImin; MIDI <= MIDImax; ++MIDI)
		{
			O << "MIDI: " << MIDI << " | FREQ.: " << ysxMUS_MIDItoFreq(MIDI, Temperament, BaseFreq);
			if (MIDI == Temperament * Oct) { O << " <- NOTE 'A'!\n"; ++Oct; }
			else { O << std::endl; }
		}
		O << "\n####### FIM! #######";
	}
	O.close();
}

// ##############				 ##############
// ############## RENOISE STUFFS ##############
// ##############				 ##############

// Print a text which can be copied and pasted on the automation section of Renoise (2.8.0).
// You should normalize it before using. It adds ".txt" after "FileName":
void ysxPRNTTXT_Vec2RenoiseAuto(std::vector<double> V, int Type, int LenghtInPatternLines, std::string FileName)
{
	if (V.size() > 0)
	{
		std::ofstream O(FileName + ".txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
		else
		{
			// HEADER:
			O << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Envelope doc_version=\"0\">\n";
			// TYPE:
			if (Type < 0) { Type = 0; } if (Type > 2) { Type = 2; }
			if (Type == 0) { O << "  <PlayMode>Linear</PlayMode>\n"; }
			else if (Type == 1) { O << "  <PlayMode>Points</PlayMode>\n"; }
			else { O << "  <PlayMode>Curve</PlayMode>\n"; }
			int Length = LenghtInPatternLines * 256;
			O << "  <Length>" << Length << "</Length>\n";
			O << "  <ValueQuantum>0.0</ValueQuantum>\n  <Polarity>Unipolar</Polarity>\n";

			double Div = (double)Length / V.size();
			//V = NormalizeMod(V);
			int Used = -1;

			O << "  <Points>\n";
			// POINTS START!
			for (int n = 0; n < V.size(); ++n)
			{
				int Index = 0;
				if (Div >= 1)
				{
					Index = round(n * Div);
					O << "    <Point>" << Index << ", " << V[n] << "</Point>\n";
				}
				else if (Div < 1)
				{
					Index = floor(n * Div);
					if (Used != Index)
					{
						Used = Index;
						O << "    <Point>" << Index << ", " << V[n] << "</Point>\n";
					}
				}

			}
			// POINTS END!
			O << "  </Points>\n</Envelope>";
		}
		O.close();
	}
}

// PRINT BLOCKS OF VECTORS:
void ysxPRNTTXT_Vec2RenoiseAuto(std::vector<std::vector<double>> Vv, int Type, int LenghtInPatternLines, std::string FileName)
{ for (int n = 0; n < Vv.size(); ++n) { ysxPRNTTXT_Vec2RenoiseAuto(Vv[n], Type, LenghtInPatternLines, FileName + std::to_string(n)); } }

// ##############       ##############
// ############## COLL: ##############
// ##############       ##############

// FibonacciWord binary into coll:
void FiboWord2Coll(int Iter, bool CollMsn, int Line)
{
	std::ofstream O("FiboWord.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		std::string Word = ysxFRACTAL_FibonacciWord(Iter);
		if (!CollMsn) { O << Line << ","; }
		for (int n = 0; n < Word.size(); ++n)
		{
			if (!CollMsn) { O << " " << Word[n]; } else { O << Word[n] << " "; }
		}
		if (!CollMsn) { O << ";"; }
	}
	O.close();
}

// FibonacciWord steps into coll
void FiboWordFrac2Coll(int Iter, bool CollMsn, int Line)
{
	std::ofstream O("FiboFrac.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		enum { Up, Down, Left, Right };
		static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
		int dir = Up;
		std::string Word = ysxFRACTAL_FibonacciWord(Iter);
		if (!CollMsn) { O << Line << ","; }
		for (size_t n = 1; n < Word.size(); ++n)
		{
			if (dir == Up) if (!CollMsn) { O << " " << Up; } else { O << Up << " "; }
			else if (dir == Right)  if (!CollMsn) { O << " " << Right; } else { O << Right << " "; }
			else if (dir == Down)  if (!CollMsn) { O << " " << Down; } else { O << Down << " "; }
			else if (dir == Left)  if (!CollMsn) { O << " " << Left; }	else { O << Left << " "; }

			if (Word.at(n) == '0') dir = nextDir[n % 2][dir];
		}
		O << ";";
	}
	O.close();
}

// Coordinates of FibonacciWord into coll:
void FiboWordFracCoord2Coll(int Iter, bool CollMsn, int Line, float Dist, bool xory, std::string Name)
{
	std::ofstream O(Name); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		std::vector<Point<int>> Pt = ysxFRACTAL_FiboWordFrac(ysxFRACTAL_FibonacciWord(Iter));
		if (!CollMsn) { O << Line << ","; }
		for (size_t n = 0; n < Pt.size(); ++n)
		{
			if (!CollMsn) { O << " "; if (!xory) { O << Pt[n].x * Dist; } }
			if (!CollMsn) { O << " "; if (xory) { O << Pt[n].y * Dist; } }
			if (CollMsn) { if (!xory) { O << Pt[n].x * Dist; } O << " "; }
			if (CollMsn) { if (xory) { O << Pt[n].y * Dist; } O << " "; }
		}
		O << ";";
	}
	O.close();
}

// Any Vector to coll:
void Vec2Coll(std::vector<float> Coll, bool CollMsn, int Line)
{
	std::ofstream O("Vector.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		if (!CollMsn) { O << Line << ","; }
		for (int n = 0; n < Coll.size(); ++n)
		{
			if (!CollMsn) { O << " " << Coll[n]; }
			else { O << Coll[n] << " "; }
		}
		if (!CollMsn) {	O << ";"; }
	}
	O.close();
}

// Print Vector of Vectors into 'Line + n':
void ysxPRNTTXT_VecOfVec2Coll(std::vector<std::vector<float>> Coll, int Line)
{
	std::ofstream O("Vector.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		for (int n = 0; n < Coll.size(); ++n)
		{
			O << Line + n << ",";
			for (int m = 0; m < Coll[n].size(); ++m)
			{
				O << " " << Coll[n][m];
			}
			O << ";";
		}
	}
	O.close();
}

// Imprime x estapas de uma fun��o:

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### CSV #####################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ##################### SPECIALS #####################

// PLOT VECTOR WITH '#', SCALE THE SIZE WITH NUMBER OF LINES:
void ysxPRNTTXT_VecPlot(std::vector<float> V, int Lines)
{
	if (Lines < 2) { Lines = 2; }
	std::ofstream O("PrintVector.txt"); if (!O.is_open()) { std::cerr << "File error" << std::endl; }
	else
	{
		float Max, Min; ysxVEC_MaxMinVec(V, Max, Min);
		double d = (Max - Min) / Lines;

		for (int n = 0; n < Lines; ++n)
		{
			double Ceil = d * n;       // /_\ // 1 - 0    | A linha que n�o pode pasar.
			double Room = d * (n + 1); // |_| //   0.5    | O espa�o que cada linha ocupa (se 'd' for igual a '0.5')
			double Floor = Max - Room; // ''' // 1 - 0.5  | O ponto que come�a a linha inferior, tipo apartamento
			O << Max - d * n << " |";
			for (int m = 0; m < V.size(); ++m) { if (V[m] > Floor && V[m] < Max - Ceil) { O << "#|"; } else { O << "_|"; } }
			O << std::endl;
		}
	}
	O.close();
}

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
