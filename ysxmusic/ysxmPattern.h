#pragma once
#ifndef PATTMAX2COLL_H
#define PATTMAX2COLL_H

#include <string>
#include <vector>
#include "ysxCImg.h"
#include "ysxmath.h"
#include "ysxmSaveVector.h"

//using namespace std;

// #################################################
// #################################################
// #################################################


// #################################################
// #################################################
// #################################################


// #################################################
// ##################### VELHOS ############################
// #################################################

// ####### FUNÇÕES:
// Fazer uma simples função para o max:
std::vector<float> Fx(float Amp, float Omega, int Samples, float x1, float x2, bool Limit)
{
	if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.
	std::vector<float> y;
	float x;
	for (int xn = 0; xn <= Samples; ++xn)
	{
		float Sample = (xn * 1.0) / Samples;
		x = x1 + ((x2 - x1) * Sample);

		// ####### FORMULA #######
		y.push_back(MiniForm(x, Omega)); // ESCREVA AQUI SUA FUNÇÃO.
		// ####### ####### #######
		y.back() = y.back() * Amp; // Amp

		// Normaliza:
		if (Limit) { if (y.back() > 1.0) { y.back() = 1.0; } if (y.back() < -1.0) { y.back() = -1.0; } }
	}
	return(y);
}

// Usar função(ões) para fazer patterns:
std::vector<float> PatternFx(int COitava, int TOitava, int Size, int Steps, int StepBase, float Turns, float TurnOffSet, float Omega, bool StepMod)
{
	// Matematica:
	COitava *= 12; TOitava *= 12;
	float Delta = TOitava - COitava;
	int StepCount = 0, DivStep = round(Size / Steps);
	float Radians = Turns * Tau;
	std::vector<float> Pattern;
	// Ação:
	for (int n = 0; n < Size; ++n)
	{
		float ndiv = n / (Size - 1.0);
		float x = (ndiv * Radians) + (TurnOffSet * Tau);
		float FormulaResult = ModForm(x, Omega);
		float Nota = (FormulaResult * Delta) + COitava;
		int rNota = round(Nota);
		int Base = (DivStep * StepCount) + StepBase;
		if (!StepMod) { if (n == Base) { Pattern.push_back(rNota); ++StepCount; } else { Pattern.push_back(0); } }
		else
		{
			if (n == Base)
			{
				int Mod = round(ModForm(x, Omega) * (DivStep - 1));
				if (Mod > 0 && Size > Mod + Base) { for (int nm = 0; nm < Mod; ++nm) { Pattern.push_back(0); ++n; } }
				Pattern.push_back(rNota);
				++StepCount;
			}
			else { Pattern.push_back(0); }
		}
	}
	return(Pattern);
}

// Usar função(ões) para fazer patterns de velocity:
std::vector<int> PatternFxVel(int CVel, int TVel, int Size, int Steps, int StepBase, float Turns, float TurnOffSet, float Omega, bool StepMod)
{
	// Matematica:
	if (TVel > 127) { TVel = 127; }
	int Delta = TVel - CVel;
	int StepCount = 0, DivStep = round(Size / Steps);
	float Radians = Turns * Tau;
	std::vector<int> Pattern;
	// Ação:
	for (int n = 0; n < Size; ++n)
	{
		float ndiv = n / (Size - 1.0);
		float x = (ndiv * Radians) + (TurnOffSet * Tau);
		float FormulaResult = ModForm(x, Omega);
		float Nota = (FormulaResult * Delta) + CVel;
		int rNota = round(Nota);
		int Base = (DivStep * StepCount) + StepBase;
		if (!StepMod) {	if (n == Base) { Pattern.push_back(rNota); ++StepCount; } else { Pattern.push_back(0); } }
		else
		{
			if (n == Base)
			{
				int Mod = round(ModForm(x, Omega) * (DivStep - 1));
				if (Mod > 0 && Size > Mod + Base) { for (int nm = 0; nm < Mod; ++nm) { Pattern.push_back(0); ++n; }	}
				Pattern.push_back(rNota);
				++StepCount;
			}
			else { Pattern.push_back(0); }
		}
	}
	return(Pattern);
}

// Usar função(ões) para fazer patterns de percussão:
std::vector<float> PatternFxFlt(float Cflt, float Tflt, int Size, int Steps, int OffSet, float Turns, float TurnOffSet, float Omega, bool StepMod)
{
	// Matematica:
	float Delta = Tflt - Cflt;
	int StepCount = 0, DivStep = round(Size / Steps);
	float Radians = Turns * Tau;
	std::vector<float> Pattern;
	// Ação:
	for (int n = 0; n < Size; ++n)
	{
		float ndiv = n / (Size - 1.0);
		float x = (ndiv * Radians) + (TurnOffSet * Tau);
		float FormulaResult = ModForm(x, Omega);
		float Nota = (FormulaResult * Delta) + Cflt;
		int rNota = round(Nota);
		int Base = (DivStep * StepCount) + OffSet;
		if (!StepMod) { if (n == Base) { Pattern.push_back(Nota); ++StepCount; } else { Pattern.push_back(0); } }
		else
		{
			if (n == Base)
			{
				int Mod = round(ModForm(x, Omega) * (DivStep - 1));
				if (Mod > 0 && Size > Mod + Base) { for (int nm = 0; nm < Mod; ++nm) { Pattern.push_back(0); ++n; }	}
				Pattern.push_back(Nota);
				++StepCount;
			}
			else { Pattern.push_back(0); }
		}
	}
	return(Pattern);
}

// Somar funções dentro de uma matriz e fazer disso uma só função para o max:

// ####### BMP:
// Formula independente.
std::vector<float> FxBmpSum(CImg<unsigned char> Img, float a, float x1, float x2, float ChaoFreq, float TetoFreq, int Samples, bool DividirSoma)
{
	if (x1 > x2) { int xTemp = x1; x1 = x2; x2 = xTemp; } // Inverte.
	if (ChaoFreq > TetoFreq) { float Temp = ChaoFreq; ChaoFreq = TetoFreq; TetoFreq = Temp; } // Inverte.
	cimg_library::CImg<unsigned char> Imagem(64, Samples, 1, 3, 0);
	int Altura = Img.height(), Largura = Img.width();
	// ##### Começa aqui #####
	// PLOTADORA:
	int Count = 0;
	std::vector<float> y;
	for (int npixy = 0; npixy < Altura; ++npixy)
	{
		for (int npixx = 0; npixx < Largura; ++npixx)
		{
			int npix = npixx + (npixy * Largura);
			Point3D RGB; RGB = BitmapRGB(Img, npixx, npixy);
			float LinRGB = (RGB.x + RGB.y + RGB.z * 1.0) / 765;
			float CF = ((TetoFreq - ChaoFreq) * LinRGB) + ChaoFreq; // Frequencia baseado nos dados da célula atual

			for (int xn = 0; xn < Samples; ++xn)
			{
				float xsum = x1 + x2;
				float xdiv = (xn * 1.0) / (Samples - 1);
				float x = x1 + ((x2 - x1) * xdiv);

				// ####### FORMULA #######
				y.push_back(a * MiniForm(x, CF)); // ESCREVA AQUI SUA FUNÇÃO.
				// ####### ####### #######

				y.back() = y.back() / a; // Normaliza com 'a'
				// Limita 'y':
				if (y.back() > 1.0) { y.back() = 1.0; } if (y.back() < -1.0) { y.back() = -1.0; }

				// Plota na Imagem:
				int yImg = round(64 - (((y.back() + 1) * 0.5) * 64));
				unsigned char color[] = { (((RGB.x * 1.0) / 255) * 200) + 55, (((RGB.y * 1.0) / 255) * 200) + 55, (((RGB.z * 1.0) / 255) * 200) + 55 }; // Cor do gráfico.
				if (yImg < 64 && yImg > 0) { Imagem.draw_point(xn, yImg, color); }
			}
			++Count;
		}
	}
	Imagem.save_bmp("ySPHAx - f(x).bmp");
	return(y);
}

// #################################################
// ##################### NOVOS ############################
// #################################################
// ####### LIVRE:
// Cria pattern manualmente:
void CreatePattern(Memo& Mem, int Steps)
{
	for (int n = 0; n < Steps; ++n)
	{
		float Data;
		std::cout << n << " (Nota): "; std::cin >> Data;
		Mem.MemoMD.push_back(Data);
		std::cout << n << " (Velocity): "; std::cin >> Data;
		Mem.MemoVel.push_back(Data);
	}
}

// ####### BATIDA E RITMO:
// Cria compasso com nota em cada beat:
Memo BarBeat(int Beats, int SamplesPerBeat, int OffSet, float Value, float Velocity, float ValRatio, float VelRatio)
{
	Memo M; 
	double Val = Value, Vel = Velocity;
	if (OffSet < 0) { OffSet = 0; } if (OffSet >= SamplesPerBeat) { OffSet = SamplesPerBeat - 1; }
	for (int n = 0; n < Beats; ++n)
	{
		//int Count = 1;
		for (int m = 0; m < SamplesPerBeat; ++m)
		{
			if (m == OffSet)
			{
				M.MemoMD.push_back(Val); M.MemoVel.push_back(Vel);
				Val *= ValRatio; Vel *= VelRatio;
				//Val = Value * ValRatio; Vel = Velocity * VelRatio;
				//ValRatio *= ValRatio * Count; VelRatio *= VelRatio * Count;
			}
			else { M.MemoMD.push_back(0); M.MemoVel.push_back(0); }
		}
	}
	return (M);
}

Memo BarMetre(int Beats, double BasicNote, double Note, int SamplesPerBeat, float Value, float Velocity)
{
	if (BasicNote < 1) { BasicNote = 1; } if (Note < 1) { Note = 1; }
	double NoteBeatRatio = Note / BasicNote;
	int Size = Beats * SamplesPerBeat;
	double SamplesPerNote = SamplesPerBeat / NoteBeatRatio;
	int CountNote = 0;

	Memo M;
	for (int n = 0; n < Size; ++n)
	{
		//std::cout << "SamplesPerNote * CountNote = " << SamplesPerNote * CountNote;
		if (n == round(SamplesPerNote * CountNote)) { M.MemoMD.push_back(Value); M.MemoVel.push_back(Velocity); ++CountNote; }
		else { M.MemoMD.push_back(0); M.MemoVel.push_back(0); }
	}
	return (M);
}

// Cria compasso com nota em divisões de um size total e offset (INUTIL SE TEM BARBEAT):
Memo BeatDivOff(int Beats, int Size, int OffSet, float Value, int Velocity, float ValRatio, float VelRatio)
{
	Memo M;
	float Val = Value; int Vel = Velocity;
	int SamplesPerBeat = Size / Beats;
	if (OffSet < 0) { OffSet = 0; } if (OffSet >= SamplesPerBeat) { OffSet = SamplesPerBeat - 1; }
	for (int n = 0; n < Beats; ++n)
	{
		int Count = 1;
		for (int m = 0; m < SamplesPerBeat; ++m)
		{
			if (m == OffSet)
			{
				M.MemoMD.push_back(Val); M.MemoVel.push_back(Vel);
				Val = Value * ValRatio; Vel = Velocity * VelRatio;
				ValRatio *= ValRatio * Count; VelRatio *= VelRatio * Count;
			}
			else { M.MemoMD.push_back(0); M.MemoVel.push_back(0); }
		}
	}
	return (M);
}

// ####### HARMONIA E MELODIA:
// Notas MIDI são sequenciadas aritiméticamente e aleatóriamente baseadas numa nota inicial:
Memo RandomMelodyArith(int SemiTons, int BeatSize, int Notes, int InitialNote, int MinVel, int MaxVel)
{
	std::vector<int> Pos;
	if (MinVel > MaxVel) { int T = MaxVel; MaxVel = MinVel; MinVel = T; } int DeltaVel = MaxVel - MinVel;
	for (int n = 0; n < Notes; ++n) { Pos.push_back(rand() % BeatSize); }
	int CountPos = 0; Memo Mem; int Note = InitialNote; int UpNoneDown = 1;
	for (int N = 0; N < Notes; ++N)
	{
		for (int n = 0; n < BeatSize; ++n)
		{
			if (n == Pos[CountPos])
			{
				UpNoneDown = rand() % 3; if (UpNoneDown == 0) { Note -= SemiTons; } else if (UpNoneDown == 2) { Note += SemiTons; }
				if (Note > 127) { Note = 127; } if (Note < 0) { Note = 0; } Mem.MemoMD.push_back(Note);
				int RandVel = 0; if (DeltaVel > 0) { RandVel = rand() % DeltaVel + 1; Mem.MemoVel.push_back(MinVel + RandVel); } else { Mem.MemoVel.push_back(MinVel); }
			}
			else { Mem.MemoMD.push_back(0); Mem.MemoVel.push_back(0); } // !!!!!!! ATENÇÃO: Este esta adicionando um "0" a cada vez que não acha nota, fugindo do 'BeatSize'. Verificar outras funções iguais. !!!!!!!
			// CRIE UM Memo SÓ COM ZEROS E MODIFIQUE O Pos, TALVEZ SE FOR A MESMA POSIÇÃO, ADICIONE OU DIMINUA UMA POSIÇÃO
		}
		++CountPos;
	}
	return(Mem);
}

// Notas MIDI baseados num vetor, mudando linearmente:
Memo RandomVecArith(Memo NoteandVel, int Diff, int BeatSize, int Notes, int MinVel, int MaxVel)
{
	std::vector<int> Pos;
	if (MinVel > MaxVel) { int T = MaxVel; MaxVel = MinVel; MinVel = T; } int DeltaVel = MaxVel - MinVel;
	for (int n = 0; n < Notes; ++n) { Pos.push_back(rand() % BeatSize); }
	int CountPos = 0; Memo Mem; int Note = rand() % NoteandVel.MemoMD.size(); int UpNoneDown = 1;
	for (int N = 0; N < Notes; ++N)
	{
		for (int n = 0; n < BeatSize; ++n)
		{
			if (n == Pos[CountPos])
			{
				UpNoneDown = rand() % 3; if (UpNoneDown == 0) { Note -= Diff; } else if (UpNoneDown == 2) { Note += Diff; }
				if (Note > NoteandVel.MemoMD.size()) { Note = NoteandVel.MemoMD.size(); } if (Note < 0) { Note = 0; }
				Mem.MemoMD.push_back(NoteandVel.MemoMD[Note]); Mem.MemoVel.push_back(NoteandVel.MemoVel[Note]);
			}
			else { Mem.MemoMD.push_back(0); Mem.MemoVel.push_back(0); }
		}
		++CountPos;
	}
	return(Mem);
}

// Notas MIDI são sequenciadas geométricamente e aleatóriamente baseadas numa nota inicial:
Memo RandomMelodyGeo(int SemiTons, int BeatSize, int Notes, int InitialNote, int MinVel, int MaxVel)
{
	if (SemiTons == 0) { SemiTons = 1; };
	std::vector<int> Pos;
	if (MinVel > MaxVel) { int T = MaxVel; MaxVel = MinVel; MinVel = T; } int DeltaVel = MaxVel - MinVel;
	for (int n = 0; n < Notes; ++n) { Pos.push_back(rand() % BeatSize); }
	int CountPos = 0; Memo Mem; int Note = InitialNote; int UpNoneDown = 1;
	for (int N = 0; N < Notes; ++N)
	{
		for (int n = 0; n < BeatSize; ++n)
		{
			if (n == Pos[CountPos])
			{
				UpNoneDown = rand() % 3; if (UpNoneDown == 0) { Note /= SemiTons; } else if (UpNoneDown == 2) { Note *= SemiTons; }
				if (Note > 127) { Note = 127; } if (Note < 0) { Note = 0; } Mem.MemoMD.push_back(Note);
				int RandVel = 0; if (DeltaVel > 0) { RandVel = rand() % DeltaVel + 1; Mem.MemoVel.push_back(MinVel + RandVel); }
				else { Mem.MemoVel.push_back(MinVel); }
			}
			else { Mem.MemoMD.push_back(0); Mem.MemoVel.push_back(0); }
		}
		++CountPos;
	}
	return(Mem);
}

// Notas MIDI baseados num vetor, mudando exponencialmente:
Memo RandomVecGeo(Memo NoteandVel, double Ratio, int BeatSize, int Notes, int MinVel, int MaxVel)
{
	if (Ratio == 0) { Ratio = 1; };
	std::vector<int> Pos;
	if (MinVel > MaxVel) { int T = MaxVel; MaxVel = MinVel; MinVel = T; } int DeltaVel = MaxVel - MinVel;
	for (int n = 0; n < Notes; ++n) { Pos.push_back(rand() % BeatSize); }
	int CountPos = 0; Memo Mem; int Note = rand() % NoteandVel.MemoMD.size(); int UpNoneDown = 1;
	for (int N = 0; N < Notes; ++N)
	{
		for (int n = 0; n < BeatSize; ++n)
		{
			if (n == Pos[CountPos])
			{
				UpNoneDown = rand() % 3; if (UpNoneDown == 0) { Note = round( Note / Ratio); } else if (UpNoneDown == 2) { Note *= Ratio; }
				if (Note > NoteandVel.MemoMD.size()) { Note = NoteandVel.MemoMD.size(); } if (Note < 0) { Note = 0; }
				Mem.MemoMD.push_back(NoteandVel.MemoMD[Note]); Mem.MemoVel.push_back(NoteandVel.MemoVel[Note]);
			}
			else { Mem.MemoMD.push_back(0); Mem.MemoVel.push_back(0); }
		}
		++CountPos;
	}
	return(Mem);
}

// Notas são escolhidas aleatóriamente de um std::vector<>:
Memo RandomVecNotes(Memo NoteandVel, int BeatSize, int Notes, bool RandVel)
{
	std::vector<int> Pos; for (int n = 0; n < Notes; ++n) { Pos.push_back(rand() % BeatSize); } // Posição no beat
	int CountPos = 0; Memo Mem; // Conta posição e memoria do pattern
	for (int N = 0; N < Notes; ++N)
	{
		for (int n = 0; n < BeatSize; ++n)
		{
			if (n == Pos[CountPos]) { int Rand = rand() % NoteandVel.MemoMD.size(); Mem.MemoMD.push_back(Rand); if (RandVel) { Rand = rand() % NoteandVel.MemoVel.size(); } Mem.MemoVel.push_back(Rand); }
			else { Mem.MemoMD.push_back(0); Mem.MemoVel.push_back(0); }
		}
		++CountPos;
	}
	return(Mem);
}

// ####### ARPEGGIOS:

// Arp. Up or down:
Memo ArpDownorUpArith(int BaseNote, int Notes, int Difference, bool DownorUp, int Vel, int VelDiff, bool VelDownorUp)
{
	Memo M;
	for (int n = 0; n < Notes; ++n)
	{
		if (!DownorUp) { M.MemoMD.push_back(BaseNote - (n * Difference)); if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff)); } else { M.MemoVel.push_back(Vel + (n * VelDiff)); } }
		else { M.MemoMD.push_back(BaseNote + (n * Difference)); if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff)); } else { M.MemoVel.push_back(Vel + (n * VelDiff)); } }
	}
	return (M);
}
Memo ArpDownorUpGeo(int BaseNote, int Notes, double Ratio, bool DownorUp, int Vel, double VelRatio, bool VelDownorUp)
{
	if (Ratio == 0) { Ratio = 1; } if (VelRatio == 0) { VelRatio = 1; }
	Memo M;
	for (int n = 1; n <= Notes; ++n)
	{
		if (!DownorUp) { M.MemoMD.push_back(BaseNote / (n * Ratio)); if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio)); } else { M.MemoVel.push_back(Vel * (n * VelRatio)); } }
		else { M.MemoMD.push_back(BaseNote * (n * Ratio)); if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio)); } else { M.MemoVel.push_back(Vel * (n * VelRatio)); } }
	}
	return (M);
}

// Arp Random:
Memo ArpRandomArith(int BaseNote, int Notes, int Difference, int Vel, int VelDiff)
{
	Memo M; int Note = BaseNote, Velocity = Vel;
	for (int n = 0; n < Notes; ++n)
	{
		int Rand = rand() % 2;
		if (Rand == 0)
		{
			Note -= Difference;	M.MemoMD.push_back(Note);
			int RandVel = rand() % 2; if (RandVel == 0) { Velocity -= VelDiff; M.MemoVel.push_back(Velocity); }	else { Velocity += VelDiff; M.MemoVel.push_back(Velocity); }
		}
		else
		{
			Note += Difference;	M.MemoMD.push_back(Note);
			int RandVel = rand() % 2; if (RandVel == 0) { Velocity -= VelDiff; M.MemoVel.push_back(Velocity); }	else { Velocity += VelDiff; M.MemoVel.push_back(Velocity); }
		}
	}
	return (M);
}
Memo ArpRandomGeo(int BaseNote, int Notes, int Ratio, int Vel, int VelRatio)
{
	if (Ratio == 0) { Ratio = 1; } if (VelRatio == 0) { VelRatio = 1; }
	Memo M; int Note = BaseNote, Velocity = Vel;
	for (int n = 0; n < Notes; ++n)
	{
		int Rand = rand() % 2;
		if (Rand == 0)
		{
			Note /= Ratio;	M.MemoMD.push_back(Note);
			int RandVel = rand() % 2; if (RandVel == 0) { Velocity /= VelRatio; M.MemoVel.push_back(Velocity); } else { Velocity *= VelRatio; M.MemoVel.push_back(Velocity); }
		}
		else
		{
			Note *= Ratio;	M.MemoMD.push_back(Note);
			int RandVel = rand() % 2; if (RandVel == 0) { Velocity /= VelRatio; M.MemoVel.push_back(Velocity); } else { Velocity *= VelRatio; M.MemoVel.push_back(Velocity); }
		}
	}
	return (M);
}

// Arp. Sine:
Memo ArpSineDownorUpArith(int BaseNote, int Notes, double Omega, int Difference, bool DownorUp, int Vel, int VelDiff, bool VelDownorUp)
{
	Memo M;
	for (int n = 0; n < Notes; ++n)
	{
		double Sine = ((sin(Tau * Omega * (n / (Notes - 1.0)))) + 1) * 0.5;
		if (!DownorUp)
		{
			M.MemoMD.push_back(BaseNote - (n * Difference + Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff + Sine)); }
			else { M.MemoVel.push_back(Vel + (n * VelDiff + Sine)); }
		}
		else
		{
			M.MemoMD.push_back(BaseNote + (n * Difference + Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff + Sine)); }
			else { M.MemoVel.push_back(Vel + (n * VelDiff + Sine)); }
		}
	}
	return (M);
}
Memo ArpSineGeo(int BaseNote, int Notes, double Omega, double Ratio, bool DownorUp, int Vel, double VelRatio, bool VelDownorUp)
{
	if (Ratio == 0) { Ratio = 1; } if (VelRatio == 0) { VelRatio = 1; }
	Memo M;
	for (int n = 0; n < Notes; ++n)
	{
		double Sine = (sin(Tau * Omega * (n / (Notes - 1.0))) + 1) * 0.5; if (Sine == 0) { Sine = 0.000000001; }
		if (!DownorUp)
		{
			M.MemoMD.push_back(BaseNote / (n * Ratio * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio * Sine)); }
			else { M.MemoVel.push_back(Vel * (n * VelRatio * Sine)); }
		}
		else
		{
			M.MemoMD.push_back(BaseNote + (n * Ratio * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio * Sine)); }
			else { M.MemoVel.push_back(Vel * (n * VelRatio * Sine)); }
		}
	}
	return (M);
}
Memo ArpSineArith(int BaseNote, int Notes, double Omega, int Difference, bool DownorUp, int Vel, int VelDiff, bool VelDownorUp)
{
	Memo M;
	for (int n = 0; n < Notes; ++n)
	{
		double Sine = ((sin(Tau * Omega * (n / (Notes - 1.0)))) + 1) * 0.5;
		if (!DownorUp)
		{
			M.MemoMD.push_back(BaseNote - (n * Difference * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff * Sine)); }
			else { M.MemoVel.push_back(Vel + (n * VelDiff * Sine)); }
		}
		else
		{
			M.MemoMD.push_back(BaseNote + (n * Difference * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel - (n * VelDiff * Sine)); }
			else { M.MemoVel.push_back(Vel + (n * VelDiff * Sine)); }
		}
	}
	return (M);
}
/*Memo ArpSineGeo(int BaseNote, int Notes, double Omega, double Ratio, bool DownorUp, int Vel, double VelRatio, bool VelDownorUp)
{
	if (Ratio == 0) { Ratio = 1; } if (VelRatio == 0) { VelRatio = 1; }
	Memo M;
	for (int n = 0; n < Notes; ++n)
	{
		double Sine = (sin(Tau * Omega * (n / (Notes - 1.0))) + 1) * 0.5; if (Sine == 0) { Sine = 0.000000001; }
		if (!DownorUp)
		{
			M.MemoMD.push_back(BaseNote / (n * Ratio * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio * Sine)); }
			else { M.MemoVel.push_back(Vel * (n * VelRatio * Sine)); }
		}
		else
		{
			M.MemoMD.push_back(BaseNote * (n * Ratio * Sine));
			if (!VelDownorUp) { M.MemoVel.push_back(Vel / (n * VelRatio * Sine)); }
			else { M.MemoVel.push_back(Vel * (n * VelRatio * Sine)); }
		}
	}
	return (M);
}*/ // Identico ao ArpSineDownorUpGeo, agora renomeado com o mesmo nome

// ####### OPERAÇÕES COM ZEROS:


// Insere zeros aleatóriamente por um pattern:
void InsertRandomZeros(Memo& NoteandVel, int Zeros)
{
	std::cout << "####### InsertRandomZero:\n\n";
	if (Zeros < 1) { Zeros = 1; }
	for (int Z = 0; Z < Zeros; ++Z)
	{
		std::cout << "Z: " << Z << endl;
		int Rand = rand() % NoteandVel.MemoMD.size(); std::cout << "Rand: " << Rand << " | Size: " << NoteandVel.MemoMD.size() << endl;
		std::vector<float> N; std::vector<int> V;
		for (int n = 0; n < NoteandVel.MemoMD.size(); ++n)
		{
			N.push_back(NoteandVel.MemoMD[n]); V.push_back(NoteandVel.MemoVel[n]); if (n == Rand) { N.push_back(0); V.push_back(0); }
		}
		NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
	}
}

// Insere zeros no fim ou no começo:
void InsertZerosBeginorEnd(Memo& NoteandVel, int Zeros, bool BeginEnd)
{
	std::vector<float> N; std::vector<int> V;
	if (!BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
	for (int n = 0; n < NoteandVel.MemoMD.size(); ++n) { N.push_back(NoteandVel.MemoMD[n]); V.push_back(NoteandVel.MemoVel[n]); }
	if (BeginEnd) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
	NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
}

// Isere zeros a cada termo:
void InsertZerosBetweenTerms(Memo& NoteandVel, int Zeros, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<float> N; std::vector<int> V;
	for (int n = 0; n < NoteandVel.MemoMD.size(); ++n)
	{
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
		N.push_back(NoteandVel.MemoMD[n]); V.push_back(NoteandVel.MemoVel[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
	}
	NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
}
void InsertZerosBetweenTermsExpo(Memo& NoteandVel, int Zeros, double InitialPower, bool BeforeAfter, bool BeforeAndAfter)
{
	std::vector<float> N; std::vector<int> V;
	for (int n = 0; n < NoteandVel.MemoMD.size(); ++n)
	{
		double Zr = pow(Zeros, (n + InitialPower));
		if (BeforeAndAfter) { BeforeAfter = false; }
		if (!BeforeAfter) { for (int Z = 0; Z < Zr; ++Z) { N.push_back(0); V.push_back(0); } }
		N.push_back(NoteandVel.MemoMD[n]); V.push_back(NoteandVel.MemoVel[n]);
		if (BeforeAndAfter) { BeforeAfter = true; }
		if (BeforeAfter) { for (int Z = 0; Z < Zr; ++Z) { N.push_back(0); V.push_back(0); } }
	}
	NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
}

// Isere zeros em um termo:
void InsertZerosatTerm(Memo& NoteandVel, int Zeros, int at, bool BeforeAfter)
{
	std::vector<float> N; std::vector<int> V;
	for (int n = 0; n < NoteandVel.MemoMD.size(); ++n)
	{
		if (!BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
		N.push_back(NoteandVel.MemoMD[n]); V.push_back(NoteandVel.MemoVel[n]);
		if (BeforeAfter && n == at) { for (int Z = 0; Z < Zeros; ++Z) { N.push_back(0); V.push_back(0); } }
	}
	NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
}

// Deleta zeros:
void DeleteZeros(Memo& NoteandVel)
{
	std::vector<float> N; std::vector<int> V;
	for (int n = 0; n < NoteandVel.MemoMD.size(); ++n) { if (NoteandVel.MemoMD[n] != 0) { N.push_back(NoteandVel.MemoMD[n]); } if (NoteandVel.MemoVel[n] != 0) { V.push_back(NoteandVel.MemoVel[n]); } }
	NoteandVel.MemoMD = N; NoteandVel.MemoVel = V;
}

// #################################################
// #################################################
// #################################################

#endif