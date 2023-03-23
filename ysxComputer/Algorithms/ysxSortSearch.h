#pragma once

#ifndef YSXSORTSEARCH_H
#define YSXSORTSEARCH_H

// #####################
// ####### By Sophia Cristina
// ####### Sort and search algorithms.
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ##############  ##############


// #################################################
// ############## SORTS  ##############

// QUICKSORT:
template <class T_>
void ysxSORT_QuickSort(std::vector<T_>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } size_t pivot = V[r]; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i] <= pivot) { std::swap(V[cnt], V[i]); ++cnt; } }
	QuickSort(V, l, cnt - 2); QuickSort(V, cnt, r);
}
template <class T_> void ysxSORT_QuickSortPtx(std::vector<Point<T_>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } T_ pivot = V[r].x; size_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].x <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	ysxSORT_QuickSortPtx(V, l, cnt - 2); ysxSORT_QuickSortPtx(V, cnt, r);
}
template <class T_> void ysxSORT_QuickSortPty(std::vector<Point<T_>>& V, uint32_t l, uint32_t r)
{
	if (l >= r) { return; } T_ pivot = V[r].y; uint32_t cnt = l;
	for (size_t i = l; i <= r; ++i) { if (V[i].y <= pivot) { std::swap(V[cnt].x, V[i].x); std::swap(V[cnt].y, V[i].y); ++cnt; } }
	ysxSORT_QuickSortPty(V, l, cnt - 2); ysxSORT_QuickSortPty(V, cnt, r);
}

// BUBBLE SORT:
template <class T_>
void ysxSORT_BubbleSort(std::vector<T_>& V)
{
	uint32_t N = V.size();
	for (uint32_t i = 0; i < N; ++i)
	{
		uint32_t p = 0; while (p < N - 1 - i) { if (V[p] > V[p + 1]) { T_ t = V[p]; V[p] = V[p + 1]; V[p + 1] = t; } ++p; }
	}
}

// INSERTION SORT:
template <class T_>
void ysxSORT_InsertionSort(std::vector<T_>& V)
{
	uint32_t n = V.size(), K, k;
	if (n > 1)
	{
		for (uint32_t h = 1; h < n; ++h) { K = V[h]; k = h - 1; while (k >= 0 && K < V[k]) { V[k + 1] = V[k]; --k; } V[k + 1] = K; }
	}
}

// #################################################
// ############## SEARCH ##############

// BINARY SEARCH (-1 = NOT FOUND):
// Vector should be sorted already!
/*template <class T_>
int32_t ysxSORT_BinSearch(uint32_t Val, std::vector<T_> V)
{
	uint32_t n = 0, m = V.size();
	while (lo <= hi)
	{
		uint32_t mid = (n + m) / 2; if (Val == V[mid]) { return(mid); } // found
		if (Val < V[mid]) { m = mid - 1; } else { n = mid + 1; }
	}
	return(-1); // n and m have crossed; key not found
}*/


// #################################################
// #################################################
// #################################################

#endif // SCPARSE_