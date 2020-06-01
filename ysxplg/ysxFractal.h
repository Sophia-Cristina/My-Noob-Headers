#pragma once

#ifndef YSXFRACTAL_H
#define YSXFRACTAL_H

using namespace std;

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
