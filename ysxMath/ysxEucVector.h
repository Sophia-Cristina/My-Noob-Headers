#pragma once

#ifndef YSXEUCVECTOR_H
#define YSXEUCVECTOR_H

// #####################
// ####### By Sophia Cristina
// ####### Euclidean vector.
// #####################

// !!! EUCVEC IS GOING TO BECOME A CLASS WITH OPERATOR OVERLOAD !!!

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ############## EUCLIDEAN VECTOR ##############

// GET MAGNITUDE:
double ysxEUCVEC_GetMag(Point<double> Vector) { return(hypot(fabs(Vector.x), fabs(Vector.y))); }

// GET RADIAN:
double ysxEUCVEC_GetVecRad(Point<double> Vector)
{
	double ax = fabs(Vector.x), ay = fabs(Vector.y); double Rad = asin(ay / hypot(ax, ay));
	if (Vector.x >= 0 && Vector.y >= 0) { return (Rad); }
	else if (Vector.x < 0 && Vector.y >= 0) { return (PI - Rad); }
	else if (Vector.x < 0 && Vector.y < 0) { return (PI + Rad); }
	return ((PI * 1.5) + ((0.5 * PI) - Rad));
}

// GET RADIAN BETWEEN TWO VECTORS:
template <class T_> double ysxEUCVEC_GetRadBetween(Point<T_> A, Point<T_> B)
{
	double RadA = GetVecRad(A), RadB = GetVecRad(B); if (RadA > RadB) { return(RadA - RadB); } return(RadB - RadA);
}

// SUBTRACT, ADD OR MULTIPLY EUC. VECTOR:
template <class T_> Point<T_> ysxEUCVEC_SubEucVector(Point<T_> A, Point<T_> B) { Point<T_> C = { A.x - B.x, A.y - B.y }; return(C); }
template <class T_> Point<T_> ysxEUCVEC_AddEucVector(Point<T_> A, Point<T_> B) { Point<T_> C = { A.x + B.x, A.y + B.y }; return(C); }
template <class T_> Point<T_> ysxEUCVEC_SclrMulEucVec(Point<T_> A, double ScalarMultiplier) { Point<T_> B = { A.x * ScalarMultiplier, A.y * ScalarMultiplier }; return(B); }

// DOT PRODUCT:
template <class T_> T_ ysxEUCVEC_DotProd(double AMag, double BMag, double Rad) { return(AMag * BMag * cos(Rad)); }
template <class T_> T_ ysxEUCVEC_DotProd(Point<T_> A, Point<T_> B) { return((A.x * B.x) + (A.y * B.y)); }

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_
