#pragma once

#ifndef YSXTRI_H
#define YSXTRI_H

// #####################
// ####### By Sophia Cristina
// ####### Triangle maths which aren't on other headers
// #####################

/* #################################################
ATTENTION: Side 'a' of a triangle is always the botom horizontal line (and seem as straight), and 'b' always the line at 'a's' left.

ANNOTATIONS:

@ = Angle; # = Area; | = Height;
	 Alpha
	   @				| 'class' 'Triangle' work with '{ a, b, Gamma }'; And I believe all triangle functions I made works like this.
	   |##    H			| As you can see, 'Gamma' is going to be the most used angle, ex.: LawCos(a, b, Gamma);
  b    |#### hypot		| A useful function on 'ysxAngle.h' is 'LawSinRadSOH' to get an angle by SOHCAHTOA: '{ b, c }' returns 'asin(((b / c) * b) / c))'.
O	   |######			| SOH: b / c = sin(Beta) | CAH: a / c = cos(Beta) | TOA = b / a = tang(Beta) |							  î_ SOH
	   @#######@		| SOH = b / c = 0.469472 = sin(Beta) | Beta = 28° = 0.48869219 rad = (7 * PI) / 45;
Gamma    A     Beta
	   Adjacent

Example not-right:

		  @ Alpha		| We can see that the variables order mantain independent of the triangle type.
		 #|#
	 b  ##|##  c
	   ###|###
Gamma @###|###@ Beta
		  a


#################################################

CHANGES:
 * Function 'hip(,)' removed, use 'cmath' 'hypot' instead;
 * Triangle class now uses only 'rad';
 * To do: prefix 'Tri' to all functions, like namespace;

 #################################################
 REFERENCES:
 #################################################*/


// ###############################################################################################################################################################################

// ANGLES:
double TriAng(double a, double b) { return(PI - (a + b)); } // Return last triangle angle by subtraction
double TriAng(double a, double b, double c) { return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2.0 * b * c))); } // Angulo função de tres medidas | Alpha = bc, Beta = ac, Gama = ab

// SIZES:
double RetTri2RetIsoTri(double a, double b) { return(sqrt(((a * a) + (b * b))) / sqrt(2)); } // Make an 'a & b' Triangle to an 'a & a' Triangle
double TriSide(double hip, double Length) { return(sqrt((hip * hip) - (Length * Length))); } // Height or Width
double TriHghtsS(double a, double Rad) { return(a * sin(Rad)); } // Length * sin().
double TriBaseC(double a, double Rad) { return(a * cos(Rad)); } // Length * cos().

// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
// The altitude from, for example, the side of length a
// Altitude of a right triangle is 'h^2 = pq; h = sqrt(pq)", 'h' is altitude and 'p + q' is the 'hipotenuse' divided by the Altitude line.
double TriAlt(double Area, double a) { return((2.0 * Area) / a); }

// PERIMETERS AND AREAS:
double PerimTri(double a, double b, double c) { return(a + b + c); } // Perimeter
double TriAr(double a, double b) { return(0.5 * a * b); } // Area
double TriAr(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double TriArAAS(double b, double Alpha, double Beta) { return((pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * sin(Beta)); } // Area
double TriArASA(double a, double Beta, double Gama) { return((pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * sin(Beta + Gama)); } // Area
double TriArHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

// MEDIANS:
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double MedianSideRelation(double a, double b, double c) { return((3.0 / 4) * (a * a + b * b + c * c)); }
double TriMedian(double a, double b, double c) { return(0.5 * sqrt((2 * pow(b, 2)) + (2 * pow(c, 2)) - pow(a, 2))); }
double TriSideMedian(double a, double b, double c) { return(sqrt((2 * (b * b) + 2 * (c * c) - (a * a)) / 4.0)); } // Formula to 'Median a', to 'Median b', use this input order "b, c, a" and "c, a, b" to 'Median c'

/* BISECTORS:
Use 'Rad BC'and 'Lgth a' for 'AC' bis.,
use 'Rad AC'and 'Lgth b' for 'BC' bis..*/
double TriBisAC(double Lgth, double Rad) { return(Lgth / sin(PI - PI - Rad + (PI - HPI + Rad) * 0.5)); }
double TriBisAct(double a, double b, double Rad) // For 'c' shorter than 'b', else, make 'c' the new 'b'
{
	double Beta = LawSinRad(a, b, Rad);	if (a < cos(Rad) * b) { Beta = PI - Beta; }
	double R = 0.5 * (Beta - Rad); // Changed in accord to Wolfram A.
	double Alt;	if (Rad <= HPI) { Alt = b * sin(Rad); } else { Alt = b * sin(PI - Rad); }
	return(Alt / cos(R));
}

// https://en.wikipedia.org/wiki/Bisection:
// If the side lengths of a triangle are 'a,b,c', the semiperimeter 's = (a + b + c) / 2', and A is the angle opposite side 'a',
// then the length of the internal bisector of angle A is: "(2 * sqrt(b * c * s * (s - a))) / (b + c)":
//double TriLghtBis(double a, double b, double c) { double s = (a + b + c) * 0.5; return((2 * sqrt(b * c * s * (s - a))) / (b + c)); } // Lenght of a bisector
//double TriPerpBisa(double a, double b, double c, double Area) { return((2.0 * a * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double TriPerpBisb(double a, double b, double c, double Area) { return((2.0 * b * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double TriPerpBisc(double a, double b, double c, double Area) { return((2.0 * c * Area) / pow(a, 2) - pow(b, 2) + pow(c, 2)); } // Interior perpendicular bisectors

// CIRCUMCENTER, INRADIUS, INCENTER AND ETC:
double TriCircumR(double a, double b, double c) { return(sqrt((pow(a, 2) * pow(b, 2) * pow(c, 2))/((a + b + c) * (- a + b + c) * (a - b + c) * (a + b - c)))); } // Circumradius
double TriInrad(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c)) / s); } // Inradius
double TriIncenter(double a, double b, double Rad) // Lenght from 'I' to 'B'
{
	double C = Rad, B = LawSinRad(a, b, C); if (a < cos(C) * b) { B = PI - B; };
	return(TriBisAct(TriBisAct(a, b, Rad), LawCos(a, b, C), PI - (C + B) * 0.5));
}

// ADJACENT TRIANGLE:
// Suppose two adjacent but non - overlapping triangles share the same side of length f and share the same circumcircle,
// so that the side of length f is a chord of the circumcircle and the triangles have side lengths(a, b, f) and (c, d, f),
// with the two triangles together forming a cyclic quadrilateral with side lengths in sequence(a, b, c, d). Then:
double TriAdjcnt(double a, double b, double c, double d) { return(sqrt((((a * c) + (b * d)) * ((a * d) + (b * c)))/((a * b) + (c * d)))); }

// #################################################
// ############## TRIANGLE ##############
class Triangle
{
public:
	// ############################
	uint8_t Bigger = 'n';
	uint8_t GetBigger(double a, double b, double c)
	{ uint8_t Ret = 'n'; if (c > b && c > a) { Ret = 'c'; } else if (b > c && b > a) { Ret = 'b'; } else if (a > b && a > c) { Ret = 'a'; } return (Ret); }
	// ############################
	std::vector<double> GetRatios(double a, double b, double c)
	{
		std::vector<double> TRatios(3);
		uint8_t Big = GetBigger(a, b, c);
		
		if (Big == 'c') { TRatios[0] = a / c; TRatios[1] = b / c; TRatios[2] = 1; }
		else if (Big == 'b') { TRatios[0] = a / b; TRatios[1] = 1; TRatios[2] = c / b; }
		else if (Big == 'a') { TRatios[0] = 1; TRatios[1] = b / a; TRatios[2] = c / a; }
		else if (Big == 'n') { TRatios[0] = 1; TRatios[1] = 1; TRatios[2] = 1; }
		return(TRatios);
	};
	// ############################
	double a, b, c; // Sides
	double Alpha, Beta, Gamma; // Angles
	double Height, Base, Base0; // Height and both bases (divided by the height line, if not right-triangle)
	double A, P; // Area and Perimeter
	double Mediana, Medianb, Medianc; // Angles
	double Ratios[3]; // Side ratio, based on the bigger side
	enum TriLnghtType { NoTypeLgt, Equilateral, Isoceles, Scalene };
	enum TriAngType { NoTypeAng, Right, Acute, Obtuse };
	uint8_t LnghtType = NoTypeLgt, AngType = NoTypeAng; // Make it a single byte with 8 flags, 4 for ang type and 4 for lenght type
	// ############################
	Point<int> Coord[3], Midpts[3], Circumcenter;
	// ############################
	double BisA, BisB, BisC; // Bisectors
	double IA, IB, IC; // Incenter to 'A' or 'B' or 'C'
	double Incircle, Inradius;
	double PerpBisAC, PerpBisBC; // Perpendicular Bisectors
	double Circumcircle, Centroid, NinePntCircle, EulerLine;
	double SteinerInellipse, SteinerEllipse; // Talvez uma função
	double MandartInellipse; // Talvez uma função
	double ExtouchTri, ExtouchTriArea;
	double LemoineHex, LemoineHexArea, LemoineHexPerim, LemoineHexIntArea, LemoineHexIntPerim; // https://en.wikipedia.org/wiki/Lemoine_hexagon
	double SplitterA, SplitterB, SplitterC;
	// Every acute triangle has three inscribed squares.
	// ############################
	void CoutInfo()
	{
		std::cout << "\n############## TRIANGLE ##############\n\n";
		std::string LType, AType;
		if (LnghtType == 1) { LType = "Equilateral"; } else if (LnghtType == 2) { LType = "Isoceles"; } else if (LnghtType == 3) { LType = "Scalene"; }
		if (AngType == 1) { AType = "Right"; } else if (AngType == 2) { AType = "Acute"; } else if (AngType == 3) { AType = "Obtuse"; }
		std::cout << "Tipo triangulo = " << LType << " & " << AType << " | Bigger: " << Bigger << std::endl;
		std::cout << "*** a: " << a << " | Alpha: " << Alpha << " | BisA: " << BisA << " ***\n";
		std::cout << "*** b: " << b << " | Beta: " << Beta << " | BisB: " << BisB << " ***\n";
		std::cout << "*** c: " << c << " | Gamma: " << Gamma << " | BisC: " << BisC << " ***\n";
		std::cout << "# Height: " << Height << " | Base: " << Base << " | Base0: " << Base0 << " #\n";
		std::cout << "# Area: " << A << " | Perimetro: " << P << " #\n";
		std::cout << "Incenter: IB: " << IB << " | IA: " << IA << " | IC: " << IC << " | Inradius: " << Inradius << std::endl;
		std::cout << "Circumcentro: x: " << Circumcenter.x << " | y: " << Circumcenter.y << std::endl;
		std::cout << "\n#####################\n\n";
		std::cout << "Coordinates x: 0: " << Coord[0].x << " | 1: " << Coord[1].x << " | 2: " << Coord[2].x << std::endl;
		std::cout << "Coordinates y: 0: " << Coord[0].y << " | 1: " << Coord[1].y << " | 2: " << Coord[2].y << std::endl;
		std::cout << "Midpts x: 0: " << Midpts[0].x << " | 1: " << Midpts[1].x << " | 2: " << Midpts[2].x << std::endl;
		std::cout << "Midpts y: 0: " << Midpts[0].y << " | 1: " << Midpts[1].y << " | 2: " << Midpts[2].y << std::endl;	
		std::cout << "\n#####################\n\n";
		std::cout << "Ratios: a: " << Ratios[0] << " | b: " << Ratios[1] << " | c: " << Ratios[2] << std::endl;
		std::cout << "\n############## END TRI ##############\n\n";
	}
	// ############################
	Triangle(double asize, double bsize, double Rad)
	{
		a = asize; b = bsize; c = LawCos(a, b, Rad);
		// Razões:
		Bigger = GetBigger(a, b, c);
		Ratios[0] = GetRatios(a, b, c)[0]; Ratios[1] = GetRatios(a, b, c)[1]; Ratios[2] = GetRatios(a, b, c)[2];
		if (Bigger == 'n') { LnghtType = Equilateral; }
		else if (Ratios[0] != Ratios[1] && Ratios[0] != Ratios[2] && Ratios[1] != Ratios[2]) { LnghtType = Scalene; }
		else { LnghtType = Isoceles; }
		// Angles:
		Beta = LawSinRad(a, b, Rad); if (a < cos(Rad) * b) { Beta = PI - Beta; AngType = Obtuse; }
		Gamma = Rad;
		Alpha = PI - (Gamma + Beta);
		if (Alpha == HPI || Beta == HPI || Gamma == HPI) { AngType = Right; }
		if (Alpha < HPI && Beta < HPI && Gamma < HPI) { AngType = Acute; }
		if (Alpha > HPI || Beta > HPI || Gamma > HPI) { AngType = Obtuse; }

		// Bisectors:
		BisA = TriBisAct(a, b, Gamma); BisB = TriBisAct(b, c, Alpha); BisC = TriBisAct(c, a, Beta);
		if (Rad > HPI) { BisA = TriBisAct(b, a, Gamma); BisB = TriBisAct(c, a, Alpha); BisC = TriBisAct(c, b, Beta); }
		// Incenter:
		IB = TriIncenter(a, b, Gamma); IC = TriIncenter(b, c, Alpha); IA = TriIncenter(c, b, Beta); Inradius = TriInrad(a, b, c);
		// Medians:
		Mediana = TriSideMedian(a, b, c); Medianb = TriSideMedian(b, a, c); Medianc = TriSideMedian(c, a, b);

		// Height e width:
		if (Rad <= HPI)
		{
			Height = b * sin(Rad);
			if (a >= b * cos(Rad)) { Base = b * cos(Rad); Base0 = fabs(a - (b * cos(Rad))); }
			else { Base = a; Base0 = fabs(a - (b * cos(Rad))); }
		}
		else { Height = b * sin(PI - Rad); Base = b * cos(PI - Rad); Base0 = a; }
		
		// Coordinates:
		Coord[0].x = 0; Coord[0].y = 0; Coord[1].x = round(a); Coord[1].y = 0; Coord[2].x = round(b * cos(Rad)); Coord[2].y = round(Height);
		if (Rad > HPI) { Coord[0].x = round(b * cos(PI - Rad)); Coord[1].x = round(a + (b * cos(Rad))); Coord[2].x = 0; }

		// Midpts:
		Midpts[0].x = round(0.5 * (Coord[1].x - Coord[0].x)) + Coord[0].x; Midpts[0].y = round(0.5 * (Coord[1].y - Coord[0].y)) + Coord[0].y;
		if (Coord[1].x >= Coord[2].x) { Midpts[1].x = round(0.5 * (Coord[1].x - Coord[2].x)) + Coord[2].x; }
		else { Midpts[1].x = round(0.5 * (Coord[2].x - Coord[1].x)) + Coord[1].x; }
		if (Coord[1].y >= Coord[2].y) { Midpts[1].y = round(0.5 * (Coord[1].y - Coord[2].y)) + Coord[2].y; }
		else { Midpts[1].y = round(0.5 * (Coord[2].y - Coord[1].y)) + Coord[1].y; }
		Midpts[2].x = round(0.5 * (Coord[2].x - Coord[0].x)); Midpts[2].y = round(0.5 * (Coord[2].y - Coord[0].y));
		
		// Circumcenter:

		// Area and perimeter:
		A = a * Height * 0.5; P = a + b + c;
	}
};

#endif