#pragma once

#ifndef YSXQUADRI_H
#define YSXQUADRI_H

// #####################
// ####### By Sophia Cristina
// ####### Quadrilateral maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

double ysxQUADRI_ArBret(double a, double b, double c, double d, double alpha, double gamma)
{ double s = 0.5 * (a + b + c + d); return (sqrt((s - a) * (s - b) * (s - c) * (s - d) - (a * b * c * d * cos2((alpha + gamma) / 2)))); }

// RECTANGLE OF EQUAL AREA AND PERIMETER:
double ysxQUADRI_EqPeriArRect(double Width) { if (Width <= 2) { Width = 2.000000001; } return((2 * Width) / ( Width - 2)); }

// #################################################

class ysxQUADRI_Quadrilateral // W.I.P
{
public:
	// ############################
	char Bigger = 'n';
	char GetBigger(double a, double b, double c, double d)
	{
		char Ret = 'n'; if (d > c && d > b && d > a) { Ret = 'd'; } else if (c > b && c > a && c > d) { Ret = 'c'; }
		else if (b > c && b > a && b > d) { Ret = 'b'; } else if (a > b && a > c && a > d) { Ret = 'a'; } return (Ret);
	}
	// ############################
	double a, b, c, d;
	double Alpha, Beta, Gamma, Delta;
	double A, P; // Area and Perimeter
	double Ratios[4]; // Razão baseada no maior valor de um comprimeto de lado
};

// ###############################################################################################################################################################################

#endif