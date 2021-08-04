#pragma once
#ifndef SAVEMAX2COLL_H
#define SAVEMAX2COLL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//using namespace std;

// #################################################
// #################################################
// #################################################

// Locais:
std::string VectorFile = "Vector.txt";
std::string BarFile = "Bar.txt";
std::string VelocityFile = "Velocity.txt";

std::string Filename = "OUT.txt";
std::string PlugPath = "C:\\Program Files(x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Plug\\";
std::string FilePath = "C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\";

struct Memo
{
	std::vector<float> MemoMD; std::vector<int> MemoVel; // MD = Nota Midi ou um float; Vel = Velocity;
	std::vector<float> SavedMD; std::vector<int> SavedVel;
};
typedef std::vector<float> PatternMD; typedef std::vector<int> PatternVel;
struct Patterns
{
	std::vector<PatternMD> PatternsMD; std::vector<PatternVel> PatternsVel;
};

// #################################################
// ##################### FUNÇÕES #####################
// #################################################

// Limpa Memoria:
std::vector<float> ClnMemoFlt() { std::vector<float> Clean; return (Clean); }
std::vector<int> ClnMemoInt() { std::vector<int> Clean; return (Clean); }

// #################################################

// Saida para texto:
void MemoOut(Memo Mem)
{
	int MDs = Mem.MemoMD.size(); // s = size
	int Vels = Mem.MemoVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");;
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		for (int n = 0; n < MDs; ++n) { MMD << Mem.MemoMD[n] << " "; }
		for (int n = 0; n < Vels; ++n) {  MVL << Mem.MemoVel[n] << " "; }
	}
	MMD.close(); MVL.close();
}
void MemoOut(Memo Mem, int Index)
{
	int MDs = Mem.MemoMD.size(); // s = size
	int Vels = Mem.MemoVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		MMD << std::to_string(Index) + ","; MVL << std::to_string(Index) + ",";
		for (int n = 0; n < MDs; ++n) { MMD << " " << Mem.MemoMD[n]; } MMD << ";";
		for (int n = 0; n < Vels; ++n) { MVL << " " << Mem.MemoVel[n]; } MVL << ";";
	}
	MMD.close(); MVL.close();
}
void SavedOut(Memo Mem)
{
	int MDs = Mem.SavedMD.size(); // s = size
	int Vels = Mem.SavedVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		for (int n = 0; n < MDs; ++n) { MMD << Mem.SavedMD[n] << " "; }
		for (int n = 0; n < Vels; ++n) { MVL << Mem.SavedVel[n] << " "; };
	}
	MMD.close(); MVL.close();
}
void SavedOut(Memo Mem, int Index)
{
	int MDs = Mem.SavedMD.size(); // s = size
	int Vels = Mem.SavedVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		MMD << std::to_string(Index) + ","; MVL << std::to_string(Index) + ",";
		for (int n = 0; n < MDs; ++n) { MMD << " " << Mem.SavedMD[n]; } MMD << ";";
		for (int n = 0; n < Vels; ++n) { MVL << " " << Mem.SavedVel[n]; } MVL << ";";
	}
	MMD.close(); MVL.close();
}

// Print out Vector, 'File' will receive a '+ ".txt"':
void VectorOut(std::vector<int> Vec, bool Coll, int Index, std::string File)
{
	// ARQUIVO:
	File = File + ".txt";
	std::ofstream VEC; VEC.open(FilePath + File);
	if (!VEC.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (Vec.size() > 0)
	{
		if (Coll) { VEC << std::to_string(Index) + ","; } for (int n = 0; n < Vec.size(); ++n) { if (Coll) { VEC << " " << Vec[n]; } else { VEC << Vec[n] << " "; } } VEC << ";";
	}
	VEC.close();
}
// Print out Vector, 'File' will receive a '+ ".txt"':
void VectorOut(std::vector<float> Vec, bool Coll, int Index, std::string File)
{
	// ARQUIVO:
	File = File + ".txt";
	std::ofstream VEC; VEC.open(FilePath + File);
	if (!VEC.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (Vec.size() > 0)
	{
		if (Coll) { VEC << std::to_string(Index) + ","; } for (int n = 0; n < Vec.size(); ++n) { if (Coll) { VEC << " " << Vec[n]; } else { VEC << Vec[n] << " "; } } VEC << ";";
	}
	VEC.close();
}

// Pattern, saida para texto:
void PattOut(Patterns Patt, bool Coll)
{
	int MDs = Patt.PatternsMD.size(); // s = size
	int Vels = Patt.PatternsVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		if (Coll) { MMD << "0,"; MVL << "0,"; }
		for (int n = 0; n < MDs; ++n)
		{
			for (int m = 0; m < Patt.PatternsMD[n].size(); ++m) { if (Coll) { MMD << " " << Patt.PatternsMD[n][m]; } else { MMD << Patt.PatternsMD[n][m] << " "; } }
		}
		MMD << ";";
		for (int n = 0; n < Vels; ++n)
		{
			for (int m = 0; m < Patt.PatternsVel[n].size(); ++m) { if (Coll) { MVL << " " << Patt.PatternsVel[n][m]; } else { MVL << Patt.PatternsVel[n][m] << " "; } }
		}
		MVL << ";";
	}
	MMD.close(); MVL.close();
}
void PattOutIndex(Patterns Patt, bool Coll)
{
	int MDs = Patt.PatternsMD.size(); // s = size
	int Vels = Patt.PatternsVel.size();
	// ARQUIVO:
	std::ofstream MMD; MMD.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Bar.txt");
	if (!MMD.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }
	std::ofstream MVL; MVL.open("C:\\Program Files (x86)\\Cycling '74\\Max519\\patches\\MAXMEU\\Synth\\Poly\\MIDISynth\\Velocity.txt");
	if (!MVL.is_open()) { std::cout << "!!! Arquivo não foi aberto. !!!" << std::endl; }

	if (MDs > 0 && Vels > 0)
	{
		for (int n = 0; n < MDs; ++n)
		{
			if (Coll) { MMD << n << ","; }
			for (int m = 0; m < Patt.PatternsMD[n].size(); ++m) { if (Coll) { MMD << " " << Patt.PatternsMD[n][m]; } else { MMD << Patt.PatternsMD[n][m] << " "; } }
			MMD << ";\n";
		}
		for (int n = 0; n < Vels; ++n)
		{
			if (Coll) { MVL << n << ","; }
			for (int m = 0; m < Patt.PatternsVel[n].size(); ++m) { if (Coll) { MVL << " " << Patt.PatternsVel[n][m]; } else { MVL << Patt.PatternsVel[n][m] << " "; } }
			MVL << ";\n";
		}
	}
	MMD.close(); MVL.close();
}

// #################################################
// ####### SAIDAS:

// LEMBRAR DE ARRUMAR AS FUNÇÕES COM REFERENCIA!!!!!!!
// Salva pattern da memória:
void Memo2Saved(Memo& Mem) { Mem.SavedMD = Mem.MemoMD; Mem.SavedVel = Mem.MemoVel; }

// Coloca pattern salvo na memória
void Saved2Memo(Memo& Mem) { Mem.MemoMD = Mem.SavedMD; Mem.MemoVel = Mem.SavedVel; }

// Salva no Saved um Pattern:
void Patt2Saved(Patterns Patt, Memo& Mem, int Index)
{
	int SizeM = Patt.PatternsMD.size(); int SizeV = Patt.PatternsMD.size();
	if (Index < SizeM && Index >= 0 && SizeM > 0 && Index < SizeV && SizeV > 0)
	{
		Mem.SavedMD = Patt.PatternsMD[Index]; Mem.SavedVel = Patt.PatternsVel[Index];
	}
	else { std::cout << "Numero do indice é diferente do tamanho do vetor\nou pattern esta vazio!\n"; }
}

// Salva no memo um Pattern:
void Patt2Memo(Patterns Patt, Memo& Mem, int Index)
{
	int SizeM = Patt.PatternsMD.size(); int SizeV = Patt.PatternsMD.size();
	if (Index < SizeM && Index >= 0 && SizeM > 0 && Index < SizeV && SizeV > 0)
	{
		Mem.MemoMD = Patt.PatternsMD[Index]; Mem.MemoVel = Patt.PatternsVel[Index];
	}
	else { std::cout << "Numero do indice é diferente do tamanho do vetor\nou pattern esta vazio!\n"; }
}

// Salva memória no pattern, substitui no index, acrescenta index se maior que ultimo número:
void Memo2Patt(Patterns& Patt, Memo Mem, int Index)
{
	if (Index >= 0)
	{
		if (Index < Patt.PatternsMD.size() && Index < Patt.PatternsVel.size())
		{
			Patt.PatternsMD[Index] = Mem.MemoMD; Patt.PatternsVel[Index] = Mem.MemoVel;
		}
		else { Patt.PatternsMD.push_back(Mem.MemoMD); Patt.PatternsVel.push_back(Mem.MemoVel); }
	}
}

// Salva Saved no pattern, substitui no index, acrescenta index se maior que ultimo número:
void Saved2Patt(Patterns& Patt, Memo Mem, int Index)
{
	if (Index >= 0)
	{
		if (Index < Patt.PatternsMD.size() && Index < Patt.PatternsVel.size())
		{
			Patt.PatternsMD[Index] = Mem.SavedMD; Patt.PatternsVel[Index] = Mem.SavedVel;
		}
		else { Patt.PatternsMD.push_back(Mem.SavedMD); Patt.PatternsVel.push_back(Mem.SavedVel); }
	}
}

// Push Back o SavedMD (salvamento atual):
void PushBackSaved(Patterns& Patt, Memo Mem) { Patt.PatternsMD.push_back(Mem.SavedMD); Patt.PatternsVel.push_back(Mem.SavedVel); }

// Push Back o MemoMD (Buffer atual):
void PushBackMemo(Patterns& Patt, Memo Mem) { Patt.PatternsMD.push_back(Mem.MemoMD); Patt.PatternsVel.push_back(Mem.MemoVel); }

// Anexa ultimo Memo nele mesmo:
void AppendMemo2Memo(Memo& Mem)
{
	int OldSize = Mem.MemoMD.size(), OldSizeVel = Mem.MemoVel.size();
	for (int n = 0; n < OldSize; ++n) { Mem.MemoMD.push_back(Mem.MemoMD[n]); }
	for (int n = 0; n < OldSizeVel; ++n) { Mem.MemoVel.push_back(Mem.MemoVel[n]); }
}

// Anexa ultimo Saved nele mesmo:
void AppendSaved2Saved(Memo& Mem)
{
	int OldSize = Mem.SavedMD.size(), OldSizeVel = Mem.SavedVel.size();
	for (int n = 0; n < OldSize; ++n) { Mem.SavedMD.push_back(Mem.SavedMD[n]); }
	for (int n = 0; n < OldSizeVel; ++n) { Mem.SavedVel.push_back(Mem.SavedVel[n]); }
}

// Anexa ultimo Saved no Memo:
void AppendSaved2Memo(Memo& Mem)
{
	for (int n = 0; n < Mem.SavedMD.size(); ++n) { Mem.MemoMD.push_back(Mem.SavedMD[n]); }
	for (int n = 0; n < Mem.SavedVel.size(); ++n) { Mem.MemoVel.push_back(Mem.SavedVel[n]); }
}

// Anexa ultimo Memo no Saved:
void AppendMemo2Saved(Memo& Mem)
{
	for (int n = 0; n < Mem.MemoMD.size(); ++n) { Mem.SavedMD.push_back(Mem.MemoMD[n]); }
	for (int n = 0; n < Mem.MemoVel.size(); ++n) { Mem.SavedVel.push_back(Mem.MemoVel[n]); }
}

// ### TWO MEMOS:
// Anexa Memória (não Saved) do 'Memo 2' para a memória do 'Memo 1':
void AppMem2toMem1(Memo& Mem1, Memo Mem2)
{
	for (int n = 0; n < Mem2.MemoMD.size(); ++n) { Mem1.MemoMD.push_back(Mem2.MemoMD[n]); }
	for (int n = 0; n < Mem2.MemoVel.size(); ++n) { Mem1.MemoVel.push_back(Mem2.MemoVel[n]); }
}

// #################################################
// ####### TÉCNICOS:
// Float to MIDI and MIDI to Float:
std::vector<int> Float2MIDI(std::vector<float> VecFloat, int MaxMIDI) { std::vector<int> V; for (int n = 0; n < VecFloat.size(); ++n) { V.push_back(round(VecFloat[n] * MaxMIDI)); } return(V); }
std::vector<float> MIDI2Float(std::vector<int> VecMIDI, int MaxMIDI) { std::vector<float> V; for (int n = 0; n < VecMIDI.size(); ++n) { V.push_back((1.0 * VecMIDI[n]) / MaxMIDI); } return(V); }

// Faz sair "MemoMD" como int e imprime juntamente o "MemoVel", mude "Filename" de acordo ("OUT.txt" e "Velocity.txt"):
void MIDINotesMIDIVelOut(Memo Mem, int MaxMIDI, bool Coll, int Index)
{ Filename = "Bar"; VectorOut(Float2MIDI(Mem.MemoMD, MaxMIDI), Coll, Index, Filename); Filename = "Velocity"; VectorOut(Mem.MemoVel, Coll, Index, Filename); Filename = "OUT"; }

// #################################################

// #################################################
// #################################################
// #################################################


// #################################################
// #################################################
// #################################################

#endif // SCPARSE_