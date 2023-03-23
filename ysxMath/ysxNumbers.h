#pragma once

#ifndef YSXNUMBERS_H
#define YSXNUMBERS_H

// #####################
// ####### By Sophia Cristina
// ####### Things related to numbers
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ##############  ##############

// IS IT PRIME?:
bool ysxNUMBR_IsPrime(size_t n) { for (size_t m = 2; m < n - 1; ++m) { if (n % m == 0) { return(false); } } return(true); }

// TRIANGULAR NUMBER:
size_t ysxNUMBR_TriNmbr(size_t n) { return ((n * (n + 1)) / 2); }

// FIBO NUMBER:
size_t ysxNUMBR_GetaFiboNmbr(size_t Fn)
{
	if (Fn < 1) { return(1); } if (Fn == 2) { return(1); }
	size_t One = 1, Two = 1, Actual = 0;
	for (size_t n = 2; n < Fn; ++n)
	{
		Actual = One + Two;
		One = Two; Two = Actual;
	}
	return(Actual);
}
std::vector<size_t> ysxNUMBR_GetaFiboVec(size_t Fn) // VEJA SE TA CERTO, VEJA SE n NÃO DEVERIA SER 2
{
	if (Fn < 1) { std::vector<size_t> A; A.push_back(1); return(A); }
	if (Fn == 2) { std::vector<size_t> A; A.push_back(1); A.push_back(1); return(A); }
	size_t One = 1, Two = 1;
	std::vector<size_t> Actual = { 1, 1 };
	for (size_t n = 2; n < Fn; ++n)
	{
		Actual.push_back(One + Two);
		One = Two; Two = Actual[n];
	}
	return(Actual);
}

// LUCAS NUMBER:
size_t ysxNUMBR_GetaLucasNmbr(size_t Ln)
{
	if (Ln < 1) { return(2); }
	if (Ln == 2) { return(1); }
	size_t One = 2, Two = 1, Actual;
	for (size_t n = 2; n < Ln; ++n)
	{
		Actual = One + Two;
		One = Two; Two = Actual;
	}
	return(Actual);
}
std::vector<size_t> ysxNUMBR_GetaLucasVec(size_t Ln) // VEJA SE TA CERTO, VEJA SE n NÃO DEVERIA SER 2
{
	if (Ln < 1) { std::vector<size_t> A; A.push_back(2); return(A); }
	if (Ln == 2) { std::vector<size_t> A; A.push_back(2); A.push_back(1); return(A); }
	size_t One = 2, Two = 1;
	std::vector<size_t> Actual = { 2, 1 };
	for (size_t n = 2; n < Ln; ++n)
	{
		Actual.push_back(One + Two);
		One = Two; Two = Actual[n];
	}
	return(Actual);
}

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_