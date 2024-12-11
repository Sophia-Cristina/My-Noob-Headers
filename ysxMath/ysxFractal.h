#pragma once

#ifndef YSXFRACTAL_H
#define YSXFRACTAL_H

/*

LONG TIME I DON'T MESS WITH CODES HERE, THIS NEEDS A BIG CLEAN UP!

#####################################################################################################################################
#####################################################################################################################################

Fractais e sequencias.

#####################################################################################################################################
#####################################################################################################################################
*/

// #####################################################################################################################################
// MINHA SEQUENCIA BINARIA:
std::vector<std::string> ysxFRACTAL_BinaryWordsSeq(int Iter) // Sequencia binaria que funciona assim: 0, 1, 00, 01, 10, 11...
{
	std::string Word;
	std::vector<std::string> Words;

	// PREPARA:
	Word.push_back('0');
	Words.push_back(Word);
	Word[0] = '1';
	Words.push_back(Word);
	Word = Words[0];
	size_t Wordsn = 0;

	// AÇÃO:
	for (size_t Wordn = 1; Wordn < Iter; ++Wordn)
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
std::vector<long> ysxFRACTAL_BinaryWordSeqArea(int Iter)
{
	if (Iter <= 0) { Iter = 1; }
	long Sum = 0, Area;
	std::vector<long> Areas;
	for (int n = 1; n <= Iter; ++n)
	{
		Area = n * pow(2, n);
		Sum += Area;
		Areas.push_back(Sum);
	}
	return(Areas);
}

// AREA DE CADA ITERAÇÃO DO MEU "BINARY WORD SEQUENCY FRACTAL":
std::vector<long> ysxFRACTAL_BinaryWordSeqArean(int Iter)
{
	if (Iter <= 0) { Iter = 1; }
	long Area;
	std::vector<long> Areas;
	for (int n = 1; n <= Iter; ++n)
	{
		Area = n * pow(2, n);
		Areas.push_back(Area);
	}
	return(Areas);
}

// VALOR DA WORD BINARIA:
std::vector<int> ysxFRACTAL_BinaryWordValue(std::vector<std::string> Words)
{
	std::vector<int> V;
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

// MATRIZ DE COORDENADAS DE UM FRACTAL COM TAIS SEQUENCIAS:
//std::vector<Point<int>> ysxFRACTAL_MatrixFractalBinary(std::vector<std::string> Words)
//{
//}

// ESPIRAL COM COMBINAÇÕES DA SEQUENCIA BINARIA !!! ERRO:
//std::vector<LinePoint<int>> ysxFRACTAL_SpiralFractalBinary(int Iter)
//{	
//}
 
// #####################################################################################################################################

// #####################################################################################################################################
// SEQUENCIA DE LINHAS DE QUADRADOS (Ver no caderno, não é quadrados de potencia):
std::vector<int> ysxFRACTAL_SeqQuadrado(int Iter)
{
	if (Iter < 1) { Iter = 1; }
	std::vector<int> Ret;
	for (int n = 1; n <= Iter; ++n)
	{
		Ret.push_back((n * 2) - 1);
	}
	return(Ret);
}

std::vector<Point<int>> ysxFRACTAL_SeqQdrdCoord(int Iter)
{
	std::vector<Point<int>> Points;
	Point<int> Push;
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
std::string ysxFRACTAL_FibonacciWord(int iters)
{
	if (iters < 1) return "0";
	std::string prev{ "0" }, now{ "01" }, next;
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
std::vector<Point<int>> ysxFRACTAL_FiboWordFrac(std::string Word)
{
	// https://en.wikipedia.org/wiki/Fibonacci_word_fractal // https://en.wikipedia.org/wiki/Fibonacci_word
	enum { Up, Down, Left, Right }; // https://en.cppreference.com/w/cpp/language/enum // Nesse caso, Up = 0, Down = 1, Left = 2, Right = 3;
	static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
	std::vector<Point<int>> Coord{ {0, 0} };
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

std::vector<Point<int>> ysxFRACTAL_BentFiboWordFrac(std::string Word)
{
	// https://en.wikipedia.org/wiki/Fibonacci_word_fractal // https://en.wikipedia.org/wiki/Fibonacci_word
	enum { Up, Down, Left, Right }; // https://en.cppreference.com/w/cpp/language/enum // Nesse caso, Up = 0, Down = 1, Left = 2, Right = 3;
	static int nextDir[2][4] = { { Left,  Right, Down,  Up }, { Right, Left,  Up, Down } };
	std::vector<Point<int>> Coord{ {0, 0} };
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