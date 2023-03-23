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
	uint8_t BiggerSide = 'n';

	// This function changes "BiggerSide" value!
	uint8_t GetBiggerSide()
	{
		if (d > c && d > b && d > a) { BiggerSide = 'd'; } else if (c > b && c > a && c > d) { BiggerSide = 'c'; }
		else if (b > c && b > a && b > d) { BiggerSide = 'b'; } else if (a > b && a > c && a > d) { BiggerSide = 'a'; }
		else BiggerSide = 'n';
	}

	// This function calls "GetBiggerSide()" and modify array "Ratios[3]":
	void GetRatios()
	{
		GetBiggerSide();
		if (BiggerSide == 'd') { Ratios[0] = a / d; Ratios[1] = b / d; Ratios[2] = c / d; Ratios[3] = 1; }
		else if (BiggerSide == 'c') { Ratios[0] = a / c; Ratios[1] = b / c; Ratios[2] = 1; Ratios[3] = d / c; }
		else if (BiggerSide == 'b') { Ratios[0] = a / b; Ratios[1] = 1; Ratios[2] = c / b; Ratios[3] = d / b; }
		else if (BiggerSide == 'a') { Ratios[0] = 1; Ratios[1] = b / a; Ratios[2] = c / a; Ratios[3] = d / a; }
		else if (BiggerSide == 'n') { Ratios[0] = 1; Ratios[1] = 1; Ratios[2] = 1; Ratios[3] = 1; }
	};
	// ############################
	double a, b, c, d;
	double Alpha, Beta, Gamma, Delta;
	double Hipo = 0;
	double A, P; // Area and Perimeter
	double Ratios[4]; // Ratio based on the bigger side
	// ############################
	void MakeSquare(double Side)
	{
		a = Side; b = Side; c = Side; d = Side; GetRatios();
		Alpha = PI; Beta = PI; Gamma = PI; Delta = PI;
		A = a * a; P = a * 4;
		Hipo = a * ROOT2;
	}

	void MakeRectangle(double Sidea, double Sideb)
	{
		a = Sidea; b = Sideb; c = Sidea; d = Sideb;
		BiggerSide = 'n';
		Ratios[0] = b > a ? a / b : 1; Ratios[1] = b > a ? 1 : b / a;
		Ratios[2] = Ratios[0]; Ratios[3] = Ratios[1];
		Alpha = PI; Beta = PI; Gamma = PI; Delta = PI;
		A = a * b; P = a * 2 + b * 2;
		Hipo = sqrt(a * a + b * b);
	}
};

// ###############################################################################################################################################################################

#endif