#pragma once

#ifndef YSXDOC_H
#define YSXDOC_H

#include <vector>

// #####################################################################################################################################
// ####### STRUCTS #######
// INDEX:
template <class T_> struct NameValue { std::string Name; T_ Value = 0; };
template <class T_> struct NameValueInfo { std::string Name, Info; T_ Value; };

// #####################################################################################################################################
// ####### SORTING FUNCTIONS #######

// ############################
// ####### SORTS
// ############################

// QUICKSORT:
template <class T_>
void QuickSort(std::vector<T_>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } size_t pivot = V[r]; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i] <= pivot) { std::swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
void QuickSortPtx(std::vector<Point<double>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } double pivot = V[r].x; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].x <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPtx(V, l, cnt - 2); QuickSortPtx(V, cnt, r);
}
void QuickSortPty(std::vector<Point<double>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } double pivot = V[r].y; uint32_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].y <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	QuickSortPty(V, l, cnt - 2); QuickSortPty(V, cnt, r);
}

// BUBBLE SORT:
template <class T_>
void BubbleSort(std::vector<T_>& V)
{
	uint32_t N = V.size();
	for (uint32_t i = 0; i < N; ++i)
	{
		uint32_t p = 0; while (p < N - 1 - i) { if (V[p] > V[p + 1]) { T_ t = V[p]; V[p] = V[p + 1]; V[p + 1] = t; } ++p; }
	}
}

// INSERTION SORT:
template <class T_>
void InsertionSort(std::vector<T_>& V)
{
	uint32_t n = V.size(), K, k;
	if (n > 1)
	{
		for (uint32_t h = 1; h < n; ++h) { K = V[h]; k = h - 1; while (k >= 0 && K < V[k]) { V[k + 1] = V[k]; --k; } V[k + 1] = K; }
	}
}

// ############################
// ####### SEARCH
// ############################

// BINARY SEARCH (-1 = NOT FOUND):
// Vector should be sorted already!
/*template <class T_>
uint32_t BinSearch(uint32_t Val, std::vector<T_> V)
{
	uint32_t n = 0, m = V.size();
	while (lo <= hi)
	{
		uint32_t mid = (n + m) / 2;	if (Val == V[mid]) { return(mid); } // found
		if (Val < V[mid]) { m = mid - 1; } else { n = mid + 1; }
	}
	return(-1); // n and m have crossed; key not found
}*/

// #####################################################################################################################################

// #####################################################################################################################################
// #######  #######

// #####################################################################################################################################
// ################################################# FIM ####################################################################################

#endif // SCPARSE_