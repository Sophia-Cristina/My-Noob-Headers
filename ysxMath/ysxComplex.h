#pragma once

#ifndef YSXCOMPLEX_H
#define YSXCOMPLEX_H

#include "ysxConst.h"

// #####################
// ####### By Sophia Cristina
// ####### Anything related to complex numbers!
// #####################

// #####################################################################################################################################

// ############################
// ####### BASICS:

// GET MAGNITUDE VECTOR:
std::vector<double> ysxCOMPLX_GetMagnitude(std::vector<std::complex<double>>& V)
{
	uint32_t Size = V.size();
	std::vector<double> Mag(Size);
	for (size_t n = 0; n < Size; ++n) { Mag[n] = sqrt(V[n].real() * V[n].real() + V[n].imag() * V[n].imag()); }
	return(Mag);
}

// CONVERT REAL SIGNAL TO COMPLEX SIGNAL:
std::vector<std::complex<double>> ysxCOMPLX_Real2Complex(const std::vector<double>& V)
{
    size_t Size = V.size();
    std::vector<std::complex<double>> CompV(Size);
    for (size_t n = 0; n < Size; ++n) { CompV[n] = std::complex<double>(V[n], 0.0); }
    return(CompV);
}
// #####################################################################################################################################

#endif // SCPARSE_
