#pragma once

#ifndef YSXMATH_H
#define YSXMATH_H

/*#####################
####### By Sophia Cristina
####### Header made to deal with technical aspects of math stuffs.
####### It also contain some math formulaes...
####### But you should check below some internal includes.
#####################*/

#include <string>
#include <iomanip>
#include <fstream>

// MATEMATICAS:
#include <utility> // Things like 'std::pair'.
#include <math.h> // #include <cmath>
#include <functional> // Objects specifically designed to be used with a syntax similar to that of functions
#include <algorithm> // Collection of functions especially designed to be used on ranges of elements
#include <complex>

// CONTAINERS:
#include <array> // Fixed-size sequence containers
#include <deque> // Double ended queue deque (usually pronounced like "deck") is an irregular
				 // acronym of double - ended queue. Double - ended queues are sequence
				 // containers with dynamic sizes that can be expanded or contracted on both
				 // ends (either its front or its back).
#include <forward_list> // Sequence containers that allow constant time insert and erase
					    // operations anywhere within the sequence.
#include <list> // Sequence containers that allow constant time insert and erase operations
				// anywhere within the sequence, and iteration in both directions.
#include <map> // Associative containers that store elements formed by a combination of a key
			   // value and a mapped value, following a specific order.
			   // Multimaps, where multiple elements can have equivalent keys.
#include <queue> // A type of container adaptor, specifically designed to operate in a FIFO
				 // context (first-in first-out), where elements are inserted into one end
				 // of the container and extracted from the other.
				 // Priority queues are specifically designed such that its first element is
				 // always the greatest of the elements it contains, according to some strict
				 // weak ordering criterion.
#include <set> // Store unique elements following a specific order.
			   // Multsets, where multiple elements can have equivalent values.
#include <stack> // A type of container adaptor, specifically designed to operate in a LIFO
				 // context(last - in first - out), where elements are insertedand extracted
				 // only from one end of the container.
#include <unordered_map> // Associative containers that store elements formed by the
						 // combination of a key value and a mapped value, and which allows
						 // for fast retrieval of individual elements based on their keys.
						 // Multimaps, much like unordered_map containers, but
						 // allowing different elements to have equivalent keys.
#include <unordered_set> // Store unique elements in no particular order, and which allow
						 // for fast retrieval of individual elements based on their value.
						 // Multisets, much like unordered_set containers, but allowing
						 // different elements to have equivalent values.
#include <vector> // Sequence containers representing arrays that can change in size

// ############################################################################################################################################
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// CHANGES (KEEP ORDER):
// * Function 'IsNumber' was called 'IsNmbr';
// * 'Str2cArray' is now 'Str2cPt' and 'Str2ucPt' in 'ysxBytes.h';
// * Starting to replace 'for' loops with 'int' or something, to 'size_t';
// * Adding templates to this header and sub-headers. W.I.P;
// * Removed Forward Declarations;
// ################################################# ANOTATIONS AND ALTERATIONS #################################################
// ############################################################################################################################################

// #####################################################################################################################################
// ############## TOOLS ##############

// DECLARE OBJECTOS QUE SERÃO USADOS EM TODOS OS HEADERS AQUI!

// ####### STRUCTS:
template <class T_> struct Point { T_ x, y; }; // Coordinates 2D
template <class T_> struct Point3D { T_ x, y, z; }; // Coordinates 3D
template <class T_> struct LinePoint { Point<T_> P0, P1; }; // In my opinion, easier to make lines
template <class T_> struct LinePoint3D { Point3D<T_> P0, P1; }; // In my opinion, easier to make lines
template <class T_, class T__> struct IdxVal { T_ i; T__ v; }; // Index and Value, maybe use 'map<,>' instead if you need a container

// #####################################################################################################################################

// IS INTEGER?:
bool IsInt(double x) { if (1.0 == x / round(x)) { return (true); } else { return (false); } }

// GET DECIMALS (x - floor(x)):
double GetDec(double x) { return(x - floor(x)); }

// #####################################################################################################################################

#include "ysxMath/ysxConst.h"
#include "ysxMath/ysxTable.h" // Const tables
#include "ysxMath/ysxConv.h" // Conversors
#include "ysxMath/ysxVector.h" // std::vector
#include "ysxMath/ysxNumbers.h" // Things related to number and its study
#include "ysxMath/ysxTime.h" // Time things, but NOT system clock
#include "ysxMath/ysxArith.h" // Arithmetic
#include "ysxMath/ysxEucVector.h" // Euclidean Vector
#include "ysxMath/ysxPolyNom.h" // Polynomials
#include "ysxMath/Geo/ysxGeo.h" // Geometry
#include "ysxMath/ysxCalc.h" // Calculus
#include "ysxMath/Physics/ysxPhys.h" // Physics
#include "ysxMath/ysxField.h" // Field arithmetics
#include "ysxMech/ysxEngn.h" // Engineering stuffs
#include "ysxElec/ysxElectr.h" // Some trigonomotry in 'ysxGeo.h'. Also #include 'ysxBytes.h' and 'ysxSignal.h'.
#include "ysxMusic/ysxMusic.h"
#include "ysxMusic/ysxSynth.h"
#include "ysxMath/ysxMoney.h" // Things about money and related to economy and etc...
#include "ysxMath/ysxFractal.h"

// #####################################################################################################################################

// ############################
// ############################
// ############################

// ############## TO REMOVE ##############

// COLLATZ CONJECTURE:
// Creates a vector with each iteration process until the number reaches 1
std::vector<int> CollatzConj(int n)
{
	std::vector<int> V;
	if (n < 1) { V.push_back(1); return(V); }
	else
	{
		int v = n;
		while (v != 1)
		{
			if (v % 2 == 0) { v /= 2; V.push_back(v); }
			else { v = v * 3 + 1; V.push_back(v); }
		}
	}
	return(V);
}

// ############################
// ####### COMBINATORICS:
// PERMUTATIONS WITHOUT REPETITION:
long long BinomialCoff(int n, int k) { n = abs(n); k = abs(k); long Fct = (n - k) + 1; for (long long a = Fct + 1; a <= n; ++a) { Fct *= a; } return(Fct / ysxARITH_Fact(k)); }

// COMBINATION:

// PERMUTATIONS WITHOUT REPETITION:
//long long PermNoRep(int n, int r) { n = abs(n); r = abs(r); long fn = Fact(n), fnr = Fact(n - r), Ret = fn / fnr; cout << "fn: " << fn << " | fnr: " << fnr << std::endl;
//cout << "Ret: " << Ret << std::endl; return(Ret); }

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_