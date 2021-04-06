#pragma once

#ifndef YSXMUSIC_H
#define YSXMUSIC_H

#include "ysxConst.h";

// #####################################################################################################################################

// ############################
// ####### RELÓGIO / TEMPO:

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
double Tau2Samples(int SampleRate) { return(SampleRate / Tau); } // SamplesRate divided by tau | 44100 / 6.2831 = 7018.7329903525843074077739647279
double Sample_n2Rad(int n, int SampleRate) { return(Tau * (n / SampleRate)); } // If the SampleRate was a table, 'n' would be the index, when 'n = TableSize', the function returns 2*PI
double Rad2Sample_n(double x, int SampleRate) { return((x / Tau) * SampleRate); } // If the SampleRate was a table, the return would be the index, when 'x = 2*PI', the function returns SampleRate (ex.: 2*PI / 2*PI) * 44100)

// ############################
// ####### Notas e Patterns:
// # Frequencias:
//double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, (MIDI - (Temperament * 5.75)) / Temperament) * BaseFreq); } // A3 = 57; C3 = 48;
double MIDItoFreq(int MIDI, int Temperament, double BaseFreq) { return(pow(2.0, ((double)MIDI / Temperament)) * BaseFreq * 0.0185814); } // Modo Reduzido, mas fixo em 'A3 = 57'
double FreqtoMIDI(double Freq, int Temperament, double BaseFreq) { return(69 + 12 * log2(Freq / BaseFreq)); }

// ############################
// ####### ESPECIAL:

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

// ####### ####### ####### ####### ####### #######


class TestMusic
{
public:
	void Test()
	{
		cout << "Digite qual função:\n";
		cout << "| 1 = | 2 =\n";
		cout << "#######\n MISC:\n";
		cout << "770 = BPM2ms | 771 = ms2BPM | 772 = ms2Freq | 773 = Ptrn2ms |\n";
		cout << "774 = Beats in ms | 775 = ms in Beats | 776 = Beats in Time |\n";
		cout << "880(m, s) | 881(h, m, s) = Time in ms |\n";
		int Op; cin >> Op;

		if (Op == 1)
		{
		}
		if (Op == 2)
		{
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