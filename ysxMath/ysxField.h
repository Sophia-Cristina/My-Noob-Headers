#pragma once

#ifndef YSXFIELD_H
#define YSXFIELD_H

// #####################
// ####### By Sophia Cristina
// ####### Related to "field" ideas of math
// #####################

// #################################################
// REFERENCES:
// [1] https://en.wikipedia.org/wiki/Field_(mathematics)
// [2] https://en.wikiversity.org/wiki/Reed%E2%80%93Solomon_codes_for_coders
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// GALOIS BASE 2, USED IN REED-SOLOMON CODE CORRECTOR [2] (W.I.P):
// It is maybe not optimized, because i took from a tutorial. Maybe later i study it better and optimize.
template<class T_>
class ysxFIELD_GaloisBase2
{
public:

	// #################################################

	std::vector<unsigned char> ExpTable = 
	{
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c,
	0x98, 0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d,
	0x27, 0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23, 0x46,
	0x8c, 0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1, 0x5f,
	0xbe, 0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e, 0x3c, 0x78, 0xf0, 0xfd,
	0xe7, 0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2, 0xd9,
	0xaf, 0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce, 0x81,
	0x1f, 0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc, 0x85,
	0x17, 0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54, 0xa8,
	0x4d, 0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73, 0xe6,
	0xd1, 0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff, 0xe3,
	0xdb, 0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41, 0x82,
	0x19, 0x32, 0x64, 0xc8, 0x8d, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6, 0x51,
	0xa2, 0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12,
	0x24, 0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0xb, 0x16, 0x2c,
	0x58, 0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x1, 0x2,
	0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c, 0x98,
	0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d, 0x27,
	0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23, 0x46, 0x8c,
	0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1, 0x5f, 0xbe,
	0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e, 0x3c, 0x78, 0xf0, 0xfd, 0xe7,
	0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2, 0xd9, 0xaf,
	0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce, 0x81, 0x1f,
	0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc, 0x85, 0x17,
	0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54, 0xa8, 0x4d,
	0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73, 0xe6, 0xd1,
	0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff, 0xe3, 0xdb,
	0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41, 0x82, 0x19,
	0x32, 0x64, 0xc8, 0x8d, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6, 0x51, 0xa2,
	0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12, 0x24,
	0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0xb, 0x16, 0x2c, 0x58,
	0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x1, 0x2
	};

	std::vector<unsigned char> LogTable =
	{
	0x0, 0x0, 0x1, 0x19, 0x2, 0x32, 0x1a, 0xc6, 0x3, 0xdf, 0x33, 0xee, 0x1b, 0x68, 0xc7, 0x4b, 0x4,
	0x64, 0xe0, 0xe, 0x34, 0x8d, 0xef, 0x81, 0x1c, 0xc1, 0x69, 0xf8, 0xc8, 0x8, 0x4c, 0x71, 0x5,
	0x8a, 0x65, 0x2f, 0xe1, 0x24, 0xf, 0x21, 0x35, 0x93, 0x8e, 0xda, 0xf0, 0x12, 0x82, 0x45, 0x1d,
	0xb5, 0xc2, 0x7d, 0x6a, 0x27, 0xf9, 0xb9, 0xc9, 0x9a, 0x9, 0x78, 0x4d, 0xe4, 0x72, 0xa6, 0x6,
	0xbf, 0x8b, 0x62, 0x66, 0xdd, 0x30, 0xfd, 0xe2, 0x98, 0x25, 0xb3, 0x10, 0x91, 0x22, 0x88, 0x36,
	0xd0, 0x94, 0xce, 0x8f, 0x96, 0xdb, 0xbd, 0xf1, 0xd2, 0x13, 0x5c, 0x83, 0x38, 0x46, 0x40, 0x1e,
	0x42, 0xb6, 0xa3, 0xc3, 0x48, 0x7e, 0x6e, 0x6b, 0x3a, 0x28, 0x54, 0xfa, 0x85, 0xba, 0x3d, 0xca,
	0x5e, 0x9b, 0x9f, 0xa, 0x15, 0x79, 0x2b, 0x4e, 0xd4, 0xe5, 0xac, 0x73, 0xf3, 0xa7, 0x57, 0x7,
	0x70, 0xc0, 0xf7, 0x8c, 0x80, 0x63, 0xd, 0x67, 0x4a, 0xde, 0xed, 0x31, 0xc5, 0xfe, 0x18, 0xe3,
	0xa5, 0x99, 0x77, 0x26, 0xb8, 0xb4, 0x7c, 0x11, 0x44, 0x92, 0xd9, 0x23, 0x20, 0x89, 0x2e, 0x37,
	0x3f, 0xd1, 0x5b, 0x95, 0xbc, 0xcf, 0xcd, 0x90, 0x87, 0x97, 0xb2, 0xdc, 0xfc, 0xbe, 0x61, 0xf2,
	0x56, 0xd3, 0xab, 0x14, 0x2a, 0x5d, 0x9e, 0x84, 0x3c, 0x39, 0x53, 0x47, 0x6d, 0x41, 0xa2, 0x1f,
	0x2d, 0x43, 0xd8, 0xb7, 0x7b, 0xa4, 0x76, 0xc4, 0x17, 0x49, 0xec, 0x7f, 0xc, 0x6f, 0xf6, 0x6c,
	0xa1, 0x3b, 0x52, 0x29, 0x9d, 0x55, 0xaa, 0xfb, 0x60, 0x86, 0xb1, 0xbb, 0xcc, 0x3e, 0x5a, 0xcb,
	0x59, 0x5f, 0xb0, 0x9c, 0xa9, 0xa0, 0x51, 0xb, 0xf5, 0x16, 0xeb, 0x7a, 0x75, 0x2c, 0xd7, 0x4f,
	0xae, 0xd5, 0xe9, 0xe6, 0xe7, 0xad, 0xe8, 0x74, 0xd6, 0xf4, 0xea, 0xa8, 0x50, 0x58, 0xaf
	};

	// #################################################

	// IN GALOIS FIELD, ADD OR SUB ARE EQUAL, JUST A XOR add(x , y) = x XOR y:
	T_ AddSub(T_ x, T_ y) {	return(x ^ y); }
	
	/* GALOIS MULTIPLICATION:
	[2] Galois Field integer multiplication using Russian Peasant Multiplication algorithm (faster than the standard multiplication + modular reduction).
	If prim is 0 and carryless = False, then the function produces the result for a standard integers multiplication (no carry - less arithmetics nor modular reduction). */
	uint64_t MultNoLUT(uint64_t x, uint64_t y, uint16_t prim = 0, uint32_t field_char_full = 256, bool carryless = true)
	{
		uint64_t r = 0;
		while (y) // while y is above 0
		{
			// y is odd, then add the corresponding x to r (the sum of all x's corresponding to odd y's will give the final product).
			// Note that since we're in GF(2), the addition is in fact an XOR (very important because in GF(2) the multiplication and
			// additions are carry-less, thus it changes the result!):
			if (y & 1) { if (carryless) { r ^= x; } else { r += x; } }
			y >>= 1; // equivalent to y / 2
			x <<= 1; // equivalent to x * 2
			if (prim > 0 && x & field_char_full)
			{
				// GF modulo: if x >= 256 then apply modular reduction using the primitive polynomial
				// (we just subtract, but since the primitive number can be above 256 then we directly XOR):
				x = x ^ prim;
			}
		}
		return(r);
	}

	// MULTIPLY:
	// Should be 'ExpTable[(LogTable[x] + LogTable[y]) % 255]' if gf_exp wasn't oversized
	T_ Mult(T_ x, T_ y) { if (y == 0 || x == 0) { return(0); } return(ExpTable[LogTable[x] + LogTable[y]]); }

	// DIVISION:
	T_ Div(T_ x, T_ y) { if (y == 0 || x == 0) { return(0); } return(ExpTable[(LogTable[x] + 255 - LogTable[y]) % 255]); }

	// POWER
	T_ Pow(T_ x, T_ power)
	{
		long long i = LogTable[x];
		i *= power; i %= 255; if (i < 0) { i = i + 255; }
		return(ExpTable[i]);
	}

	// INVERSE
	T_ Inverse(T_ x) { return(ExpTable[255 - LogTable[x]]); } // Inverse(x) == Div(1, x));

	// #################################################

	/* POLYNOMIALS:
	[2] (...) Confusion is the fact that 'x' is still used as the placeholder.
	This 'x' has nothing to do with the 'x' mentioned previously, so don't mix them up. */
	// * Maybe use 'uint16_t';

	// MULT POLY BY SCALAR:
	std::vector<T_> PolyScale(std::vector<T_> p, T_ x)
	{
		std::vector<T_> r(p.size());
		for (size_t i = 0; i < p.size(); ++i) { r[i] = Mult(p[i], x); }
		return(r);
	}

	// "ADDS" TWO POLYNOMIALS (USING EXCLUSIVE-OR, AS USUAL):
	std::vector<T_> PolyAdd(std::vector<T_> p, std::vector<T_> q)
	{
		T_ sp = (T_)p.size(), sq = (T_)q.size(), sr;
		std::vector<T_> r(sp >= sq ? sp : sq); sr = r.size();
		for (T_ i = 0; i < sp; ++i) { r[i + sr - sp] = p[i];	}
		for (T_ i = 0; i < sq; ++i) { r[i + sr - sq] ^= q[i]; }
		return(r);
	}

	// MULTIPLY TWO POLYNOMIALS:
	std::vector<T_> PolyMult(std::vector<T_> p, std::vector<T_> q)
	{
		// Pre - allocate the result array
		T_ sp = p.size(), sq = q.size(), sr;
		std::vector<T_> r(sp + sq - 1); sr = r.size();
		// Compute the polynomial multiplication(just like the outer product of two vectors,
		// we multiply each coefficients of p with all coefficients of q)
		for (T_ j = 0; j < sq; ++j)
		{
			for (T_ i = 0; i < sp; ++i)
			{
				r[i + j] ^= Mult(p[i], q[j]); // equivalent to : r[i + j] = gf_add(r[i + j], gf_mul(p[i], q[j]));
			}
		}		
		// -- you can see it's your usual polynomial multiplication
		return(r);
	}

	/* DIVIDE TWO POLYNOMIALS:
	Doesn't work with standard polynomials outside of this galois field, see the Wikipedia article for generic algorithm
	CAUTION: this function expects polynomials to follow the opposite convention at decoding:
	The terms must go from the biggest to lowest degree(while most other functions here expect
	a list from lowest to biggest degree), eg:
	1 + 2x + 5x^2 = { 5, 2, 1 }; NOT { 1, 2, 5 }
	RETURN: .x = quotients; .y = remainders;
	*/
	//Point<std::vector<T_>> PolyDiv(std::vector<T_> dividend, std::vector<T_> divisor)
	std::vector<T_> PolyDiv(std::vector<T_> dividend, std::vector<T_> divisor)
	{
		T_ sdivd = dividend.size(), sdivr = divisor.size(); // SizeDIVidenD and SizeDIVsoR
		std::vector<T_> msg_out = dividend; // Copy the dividend
		//normalizer = divisor[0] // precomputing for performance
		T_ coef;
		for (T_ i = 0; i < sdivd - (sdivr - 1); ++i)
		{
			//msg_out[i] /= normalizer // for general polynomial division(when polynomials are non - monic), the usual way of using
									   // synthetic division is to divide the divisor g(x) with its leading coefficient, but not needed here
			coef = msg_out[i]; // precaching
			if (coef != 0) // log(0) is undefined, so we need to avoid that case explicitly(and it's also a good optimization)
			{
				// in synthetic division, we always skip the first coefficient of the divisior, because it's only used to normalize the dividend coefficient:
				for (T_ j = 1; j < sdivr; ++j)
				{
					// log(0) is undefined
					if (divisor[j] != 0) { msg_out[i + j] ^= Mult(divisor[j], coef); }  // equivalent to the more mathematically correct
				}
			}
		}
		// (but xoring directly is faster): msg_out[i + j] += -divisor[j] * coef
		/*
		Point<std::vector<T_>> R;
		{
			// The resulting msg_out contains both the quotient and the remainder, the remainder being the size of the divisor
			// (the remainder has necessarily the same degree as the divisor -- not length but degree == length-1 -- since it's
			// what we couldn't divide from the dividend), so we compute the index where this separation is, and return the quotient and remainder.
			//T_ separator = sdivr - 1;
			T_ separator = -(sdivr - 1);
			//T_ separator = sdivd - (sdivr - 1);
			// msg_out[:separator], msg_out[separator:]
			std::vector<T_> quotient; // It must have a better way to do this... :s
			std::vector<T_> remainder;
			for (T_ n = 0; n < msg_out.size(); ++n)
			{
				if (n < separator) { remainder.push_back(msg_out[n]); }
				else { quotient.push_back(msg_out[n]); }
			}
			R.x = quotient;
			R.y = remainder;
		}*/
		{
			size_t Separator = sdivd - (sdivr - 1);
			memmove(&msg_out[0], &msg_out[Separator], (msg_out.size() - Separator) * sizeof(T_));
			//newp->length = newp->length - Separator;
		}
		return(msg_out); // return quotient, remainder.
	}

	// EVALUATE POLYNOMIAL:
	// Horner's method is used to avoid explicitly calculating powers of x. Horner's method works by factorizing
	// consecutively the terms, so that we always deal with x^1, iteratively, avoiding the computation of higher degree terms:
	// '01 x^4 + 0f x^3 + 36 x^2 + 78 x + 40 = (((01 x + 0f) x + 36) x + 78) x + 40'
	T_ PolyEval(std::vector<T_> poly, T_ x)
	{ T_ y = poly[0]; for (T_ i = 1; i < poly.size(); ++i) { y = Mult(y, x) ^ poly[i]; } return(y); }

	// #################################################

	// prim is the primitive (binary) polynomial. Since it's a polynomial in the binary sense,
	// it's only in fact a single galois field value between 0 and 255, and not a list of gf values.
	ysxFIELD_GaloisBase2(uint16_t prim = 0x11d)
	{
	}

	~ysxFIELD_GaloisBase2()
	{
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_