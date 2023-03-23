#pragma once

#ifndef YSXPOLYNOM_H
#define YSXPOLYNOM_H

// #####################
// ####### By Sophia Cristina
// ####### Polynomials.
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################
// #################################################
// #################################################

// #################################################
// ############## QUADRATIC ##############

// QUADRATIC EQUATION:
Point<double> ysxPOLYNOM_QuadraticEq(double a, double b, double c)
{
	Point<double> Root;
	double Delta = b * b - 4 * a * c;
	if (!Delta) { Root.x = -b / (2 * a); Root.y = Root.x; return(Root); }
	Root.x = (-b + sqrt(Delta)) / (2 * a); Root.y = (-b - sqrt(Delta)) / (2 * a);
	return(Root);
}

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_