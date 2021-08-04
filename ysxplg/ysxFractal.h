#pragma once

#ifndef YSXFRACTAL_H
#define YSXFRACTAL_H

/*
#####################################################################################################################################
#####################################################################################################################################

Fractais e sequencias.

#####################################################################################################################################
#####################################################################################################################################
*/

// #####################################################################################################################################
// MINHA SEQUENCIA BINARIA:
vector<string> BinaryWordsSeq(int Iter) // Sequencia binaria que funciona assim: 0, 1, 00, 01, 10, 11...
{
	string Word;
	vector<string> Words;

	// PREPARA:
	Word.push_back('0');
	Words.push_back(Word);
	Word[0] = '1';
	Words.push_back(Word);
	Word = Words[0];
	int Wordsn = 0;

	// AÇÃO:
	for (int Wordn = 1; Wordn < Iter; ++Wordn)
	{
		bool First = false, Second = false;

		for (int n = 0; n < pow(2, Wordn); ++n)
		{
			Word = Words[Wordsn];
			++Wordsn;
			Word.push_back('0'); Words.push_back(Word);
			Word[Wordn] = '1'; Words.push_back(Word);
		}
	}
	return(Words);
}

// AREA POR ITERAÇÃO DO MEU "BINARY WORD SEQUENCY FRACTAL":
vector<long> BinaryWordSeqArea(int Iter)
{
	if (Iter <= 0) { Iter = 1; }
	long Sum = 0, Area;
	vector<long> Areas;
	for (int n = 1; n <= Iter; ++n)
	{
		Area = n * pow(2, n);
		Sum += Area;
		Areas.push_back(Sum);
	}
	return(Areas);
}

// AREA DE CADA ITERAÇÃO DO MEU "BINARY WORD SEQUENCY FRACTAL":
vector<long> BinaryWordSeqArean(int Iter)
{
	if (Iter <= 0) { Iter = 1; }
	long Area;
	vector<long> Areas;
	for (int n = 1; n <= Iter; ++n)
	{
		Area = n * pow(2, n);
		Areas.push_back(Area);
	}
	return(Areas);
}

// VALOR DA WORD BINARIA:
vector<int> BinaryWordValue(vector<string> Words)
{
	vector<int> V;
	for (int n = 0; n < Words.size(); ++n)
		{
			int Soma = 0;
			for (int m = 0; m < Words[n].size(); ++m)
			{
				if (Words[n][m] == '0') { Soma += - pow(2, Words[n].size() - m); } else { Soma += pow(2, Words[n].size() - m); }
			}
			V.push_back(Soma * 0.5);
		}
	return (V);
}

// MATRIZ DE COORDENADAS DE UM FRACTAL COM TAIS SEQUENCIAS !!! ERRO:
vector<Point> MatrixFractalBinary(vector<string> Words)
{
	// Descobre numero de iterações:
	int Iter, Size = Words.size();
	for (int n = 1; Size == 0; ++n)
	{
		Size -= pow(2, n);
		Iter = n;
	}
	cout << "Iter: " << Iter << endl;

	// Verifica pontuação para devida coordenada:
	vector<int> Scores;
	for (int n = 0; n < Words.size(); ++n)
	{
		int Score = 0;
		for (int m = 0; m < Words[n].size(); ++m)
		{
			if (Words[n][m] == '1') { Score += 1 * pow(10, ((Words.size() - 1) - m)); }
		}
		Scores.push_back(Score);
	}

	// Verifica pontuação de cada coordenada:
	vector<double> CrdTargs;
	vector<Point> Coord;
	for (int n = 0; n < Iter; ++n)
	{
		int Stages = pow(2, n + 1);
		double ThetaDiv = TAU / Stages;
		double ThetaOffset = PI * 0.5;
		for (int Tht = ThetaOffset + ThetaDiv; Tht <= TAU + ThetaOffset; Tht += ThetaDiv) // Qualquer coisa tira o ThetaDiv
		{
			double Bonus = 0;
			// Bonus:
			if (sin(Tht) > 0) { Bonus += 2; }
			if (sin(Tht) < 0) { Bonus += -2; }
			if (cos(Tht) > 0) { Bonus += 2; }
			if (cos(Tht) < 0) { Bonus += -2; }
			// Target:
			CrdTargs.push_back((2 * sin(Tht)) + cos(Tht) + Bonus);
		}
		// Associa pontuação a coordenadas:
		vector<double> Best;
		for (int m = 0; m < Stages; ++m)
		{
			for (int k = 0; k < Stages; ++k)
			{
				double Delta = CrdTargs[k];
				Best.push_back(0);
				for (int l = 0; l < Stages; ++l)
				{
					double ActualDelta = CrdTargs[k] - Scores[l];
					if (ActualDelta < Delta) { Delta = ActualDelta; Best[k] = l; }
				}
			}
		}
		// Adiciona em Coordenada:
		int x, y, r;
		double ThetaDiv2 = ThetaDiv / n;
		for (int Tht = ThetaOffset; Tht <= TAU + ThetaOffset; Tht += ThetaDiv2) // Qualquer coisa tira o ThetaDiv
		{
			r = n;
			Point GetCrd;
			Coord.push_back(GetCrd);
		}
	}

	return(Coord);
}

// ESPIRAL COM COMBINAÇÕES DA SEQUENCIA BINARIA !!! ERRO:
vector<LinePoint> SpiralFractalBinary(int Iter)
{
	// As primeiras 3 iterações devem ser feitas manualmente, pois um ciclo não se completa e seria chato fazer uma função só para isso
	vector<LinePoint> Coord(2);
	Coord[0].P0.x = 0; Coord[0].P0.y = 0; Coord[0].P1.x = 0; Coord[0].P1.y = 0;
	Coord[1].P0.x = 0; Coord[1].P0.y = 1; Coord[1].P1.x = 0; Coord[1].P1.y = 1;
	cout << "ITER1 DONE!\n\n";
	if (Iter == 1) { return(Coord); }
	LinePoint IniLines;
	IniLines.P0.x = 0; IniLines.P0.y = 2; IniLines.P1.x = 1; IniLines.P1.y = 2;
	Coord.push_back(IniLines);
	IniLines.P0.x = 1; IniLines.P0.y = 1; IniLines.P1.x = 1; IniLines.P1.y = 0;
	Coord.push_back(IniLines);
	IniLines.P0.x = 1; IniLines.P0.y = -1; IniLines.P1.x = 0; IniLines.P1.y = -1;
	Coord.push_back(IniLines);
	IniLines.P0.x = -1; IniLines.P0.y = -1; IniLines.P1.x = -1; IniLines.P1.y = 0;
	Coord.push_back(IniLines);
	cout << "ITER2 DONE!\n\n";
	if (Iter == 2) { return(Coord); }

	// Ação:
	enum { Up, Down, Left, Right };
	int Dir = Right, Crdn = 1;
	int inix = 0, iniy = 1, Top = 1;
	bool Pair = true;
	for (int n = 2; n <= Iter; ++n)
	{
		++Top;
		int x0, x1, y0, y1;
		if (Pair) { x0 = 0; }
		for (int m = 0; m < pow(2, n); ++m)
		{
			//if (m == 0) {  }
			//LinePoint Map;
			
		}
	}
	cout << "ITERn DONE!\n\n";
}
// #####################################################################################################################################

// #####################################################################################################################################
// SEQUENCIA DE LINHAS DE QUADRADOS (Ver no caderno, não é quadrados de potencia):
vector<int> SeqQuadrado(int Iter)
{
	if (Iter < 1) { Iter = 1; }
	vector<int> Ret;
	for (int n = 1; n <= Iter; ++n)
	{
		Ret.push_back((n * 2) - 1);
	}
	return(Ret);
}

vector<Point> SeqQdrdCoord(int Iter)
{
	vector<Point> Points;
	Point Push;
	Push.x = 0; Push.y = 0;
	Points.push_back(Push);
	enum Dir { Up, Left, Down, Right};
	if (Iter > 1)
	{
		for (int n = 2; n <= Iter; ++n)
		{

		}
	}
	return(Points);
}
// #####################################################################################################################################

// #####################################################################################################################################
// FIBONACCI WORD
string FiboWord(int iters)
{
	if (iters < 1) return "0";
	string prev{ "0" }, now{ "01" }, next;
	if (iters == 1) { return (prev); } if (iters == 2) { return (now); }
	for (int n = 2; n < iters; ++n)
	{
		next = now + prev;
		prev = now;
		now = next;
	}
	return now;
}

// FIBONACCI WORD FRACTAL COORDINATES:
vector<Point> FiboWordFrac(string Word)
{
	// https://en.wikipedia.org/wiki/Fibonacci_word_fractal // https://en.wikipedia.org/wiki/Fibonacci_word
	enum { Up, Down, Left, Right }; // https://en.cppreference.com/w/cpp/language/enum // Nesse caso, Up = 0, Down = 1, Left = 2, Right = 3;
	static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
	vector<Point> Coord{ {0, 0} };
	int x = 0, y = 0;
	int dir = Up;

	for (size_t n = 1; n < Word.size(); ++n) // http://www.cplusplus.com/reference/cstring/size_t/
	{
		if (dir == Up) ++y;
		else if (dir == Right) ++x;
		else if (dir == Down) --y;
		else if (dir == Left) --x;

		Coord.push_back({ x, y });

		if (Word.at(n) == '0') dir = nextDir[n % 2][dir];
	}

	return Coord;
}

vector<Point> BentFiboWordFrac(string Word)
{
	// https://en.wikipedia.org/wiki/Fibonacci_word_fractal // https://en.wikipedia.org/wiki/Fibonacci_word
	enum { Up, Down, Left, Right }; // https://en.cppreference.com/w/cpp/language/enum // Nesse caso, Up = 0, Down = 1, Left = 2, Right = 3;
	static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
	vector<Point> Coord{ {0, 0} };
	int x = 0, y = 0;
	int dir = Up;

	for (size_t n = 1; n < Word.size(); ++n) // http://www.cplusplus.com/reference/cstring/size_t/
	{
		if (dir == Up) { ++x; ++y; }
		else if (dir == Right) { --y; ++x; }
		else if (dir == Down) { --x; --y; }
		else if (dir == Left) { --x; ++y; }

		Coord.push_back({ x, y });

		if (Word.at(n) == '0') dir = nextDir[n % 2][dir];
	}

	return Coord;
}
// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_