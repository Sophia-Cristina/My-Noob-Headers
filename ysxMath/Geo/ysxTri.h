#pragma once

#ifndef YSXTRI_H
#define YSXTRI_H

// #####################
// ####### By Sophia Cristina
// ####### Triangle maths which aren't on other headers
// #####################

/* #################################################
ATTENTION: Side 'a' of a triangle is always the bottom horizontal line (and seem as straight), and 'b' always the line at 'a's' left.

ANNOTATIONS:

@ = Angle; # = Area; | = Height;
	 Alpha
	   @				| 'class' 'Triangle' works with '{ a, b, Gamma }'; And I believe all triangle functions I made works like this.
	   |##    H			| As you can see, 'Gamma' is going to be the most used angle, ex.: LawCos(a, b, Gamma);
  b    |#### hypot		| An useful function on 'ysxAngle.h' is 'LawSinRadSOH' to get an angle by SOHCAHTOA: '{ b, c }' returns 'asin(((b / c) * b) / c))'.
O	   |######			| SOH: b / c = sin(Beta) | CAH: a / c = cos(Beta) | TOA = b / a = tan(Beta) |							  î_ SOH
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

 #################################################
 REFERENCES:
 #################################################*/


// #################################################
// #################################################
// #################################################

// ANGLES:
constexpr double ysxTRI_Ang(double a, double b) { return(PI - (a + b)); } // Return last triangle angle by subtraction
// Angle by sides, care with div by 0 | Alpha = bc, Beta = ac, Gama = ab
double ysxTRI_Ang(double a, double b, double c) { return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2.0 * b * c))); }

// SIZES:
double ysxTRI_Ret2TriRetIso(double a, double b) { return(sqrt(((a * a) + (b * b))) / ROOT2); } // Make an 'a & b' Triangle to an 'a & a' Triangle
double ysxTRI_Side(double hip, double Length) { return(sqrt((hip * hip) - (Length * Length))); } // Height or Width
double ysxTRI_HghtsS(double a, double Rad) { return(a * sin(Rad)); } // Length * sin().
double ysxTRI_BaseC(double a, double Rad) { return(a * cos(Rad)); } // Length * cos().

// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
// The altitude from, for example, the side of length a
// Altitude of a right triangle is 'h^2 = pq; h = sqrt(pq)", 'h' is altitude and 'p + q' is the 'hipotenuse' divided by the Altitude line.
constexpr double ysxTRI_Alt(double Area, double a) { return(a == 0 ? 0 : (2.0 * Area) / a); }

// PERIMETERS AND AREAS:
constexpr double ysxTRI_Perim(double a, double b, double c) { return(a + b + c); } // Perimeter
constexpr double ysxTRI_Ar(double a, double b) { return(0.5 * a * b); } // Area
double ysxTRI_Ar(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double ysxTRI_ArAAS(double b, double Alpha, double Beta) { double S = sin(Beta); return(S == 0 ? 0 : (pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * S); } // Area
double ysxTRI_ArASA(double a, double Beta, double Gama) { double S = sin(Beta + Gama); return(S == 0 ? 0 : (pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * S); } // Area
double ysxTRI_ArHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

// MEDIANS:
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
constexpr double ysxTRI_MedianSideRelation(double a, double b, double c) { return(0.75 * (a * a + b * b + c * c)); }
double ysxTRI_Median(double a, double b, double c) { return(0.5 * sqrt((2 * pow(b, 2)) + (2 * pow(c, 2)) - pow(a, 2))); }
// Formula to 'Median a'. For 'Median b', use this input order "b, c, a" and "c, a, b" for 'Median c'
double ysxTRI_SideMedian(double a, double b, double c) { return(sqrt((2 * (b * b) + 2 * (c * c) - (a * a)) / 4.0)); }

/* BISECTORS:
Use 'Rad BC'and 'Lgth a' for 'AC' bis.,
use 'Rad AC'and 'Lgth b' for 'BC' bis..*/
double ysxTRI_BisAC(double Lgth, double Rad) { double S = sin(PI - PI - Rad + (PI - HPI + Rad) * 0.5);  return(S == 0 ? 0 : Lgth / S); }
double ysxTRI_BisAct(double a, double b, double Rad) // For 'c' shorter than 'b', else, make 'c' the new 'b'
{
	double Beta = ysxGEO_LawSinRad(a, b, Rad);	if (a < cos(Rad) * b) { Beta = PI - Beta; }
	double R = 0.5 * (Beta - Rad); // Changed in accord to Wolfram A.
	double Alt; if (Rad <= HPI) { Alt = b * sin(Rad); } else { Alt = b * sin(PI - Rad); }
	return(Alt / cos(R));
}

// https://en.wikipedia.org/wiki/Bisection:
// If the side lengths of a triangle are 'a,b,c', the semiperimeter 's = (a + b + c) / 2', and A is the angle opposite side 'a',
// then the length of the internal bisector of angle A is: "(2 * sqrt(b * c * s * (s - a))) / (b + c)":
//double ysxTRI_LghtBis(double a, double b, double c) { double s = (a + b + c) * 0.5; return((2 * sqrt(b * c * s * (s - a))) / (b + c)); } // Lenght of a bisector
//double ysxTRI_PerpBisa(double a, double b, double c, double Area) { return((2.0 * a * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double ysxTRI_PerpBisb(double a, double b, double c, double Area) { return((2.0 * b * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double ysxTRI_PerpBisc(double a, double b, double c, double Area) { return((2.0 * c * Area) / pow(a, 2) - pow(b, 2) + pow(c, 2)); } // Interior perpendicular bisectors

// CIRCUMCENTER, INRADIUS, INCENTER AND ETC, CARE WITH DIV BY 0:
double ysxTRI_CircumR(double a, double b, double c) { return(sqrt((pow(a, 2) * pow(b, 2) * pow(c, 2)) / ((a + b + c) * (- a + b + c) * (a - b + c) * (a + b - c)))); } // Circumradius
double ysxTRI_Inrad(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(((s - a) * (s - b) * (s - c)) / s)); } // Inradius
// double ysxTRI_Inrad(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c)) / s); } // Inradius
double ysxTRI_Incenter(double a, double b, double Rad) // Lenght from 'I' to 'B'
{
	double B = ysxGEO_LawSinRad(a, b, Rad); if (a < cos(Rad) * b) { B = PI - B; };

	return(ysxTRI_BisAct(ysxTRI_BisAct(a, b, Rad), ysxGEO_LawCos(a, b, Rad), PI - (Rad + B) * 0.5));
}

// ADJACENT TRIANGLE, CARE WITH DIV BY 0:
// Suppose two adjacent but non - overlapping triangles share the same side of length f and share the same circumcircle,
// so that the side of length f is a chord of the circumcircle and the triangles have side lengths(a, b, f) and (c, d, f),
// with the two triangles together forming a cyclic quadrilateral with side lengths in sequence(a, b, c, d). Then:
double ysxTRI_Adjcnt(double a, double b, double c, double d) { return(sqrt((((a * c) + (b * d)) * ((a * d) + (b * c))) / ((a * b) + (c * d)))); }

// #################################################
// #################################################
// #################################################

// #####################
// ####### TRIANGLE #######
// #####################

class ysxTRI_Triangle
{
public:
	double a, b, c; // Sides
	uint8_t BiggerSide = 'n';
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
	double Circumcircle, Circumradius;
	//double Centroid, NinePntCircle, EulerLine;
	//double SteinerInellipse, SteinerEllipse; // Talvez uma função
	//double MandartInellipse; // Talvez uma função
	//double ExtouchTri, ExtouchTriArea;
	//double LemoineHex, LemoineHexArea, LemoineHexPerim, LemoineHexIntArea, LemoineHexIntPerim; // https://en.wikipedia.org/wiki/Lemoine_hexagon
	// Every acute triangle has three inscribed squares.
	
	// ############################

	// Eet "BiggerSide" value:
	void SetBiggerSide()
	{
		if (c > b && c > a) { BiggerSide = 'c'; } else if (b > c && b > a) { BiggerSide = 'b'; }
		else if (a > b && a > c) { BiggerSide = 'a'; } else BiggerSide = 'n';
	}

	// This function calls "SetBiggerSide()" and modify array "Ratios[]":
	void SetRatios()
	{
		SetBiggerSide();
		if (BiggerSide == 'c') { Ratios[0] = a / c; Ratios[1] = b / c; Ratios[2] = 1; }
		else if (BiggerSide == 'b') { Ratios[0] = a / b; Ratios[1] = 1; Ratios[2] = c / b; }
		else if (BiggerSide == 'a') { Ratios[0] = 1; Ratios[1] = b / a; Ratios[2] = c / a; }
		else if (BiggerSide == 'n') { Ratios[0] = 1; Ratios[1] = 1; Ratios[2] = 1; LnghtType = Equilateral; }
		if (Ratios[0] != Ratios[1] && Ratios[0] != Ratios[2] && Ratios[1] != Ratios[2]) { LnghtType = Scalene; }
		else if (LnghtType != Equilateral) { LnghtType = Isoceles; }
	};

	// You should change 'Gamma' before using it, and other angles will be changed from 'Gamma'.
	// W.I.P, later to make this function to work with all angles.
	void SetAngles()
	{
		Beta = ysxGEO_LawSinRad(a, b, Gamma); if (a < cos(Gamma) * b) { Beta = PI - Beta; AngType = Obtuse; }
		Alpha = PI - (Gamma + Beta);
		if (Alpha == HPI || Beta == HPI || Gamma == HPI) { AngType = Right; }
		if (Alpha < HPI && Beta < HPI && Gamma < HPI) { AngType = Acute; }
		if (Alpha > HPI || Beta > HPI || Gamma > HPI) { AngType = Obtuse; }
	}

	void SetBisectors()
	{
		if (Gamma > HPI) { BisA = ysxTRI_BisAct(b, a, Gamma); BisB = ysxTRI_BisAct(c, a, Alpha); BisC = ysxTRI_BisAct(c, b, Beta); }
		else { BisA = ysxTRI_BisAct(a, b, Gamma); BisB = ysxTRI_BisAct(b, c, Alpha); BisC = ysxTRI_BisAct(c, a, Beta); }
	}

	void SetInradius() { Inradius = ysxTRI_Inrad(a, b, c); }

	void SetIncenter() { IB = ysxTRI_Incenter(a, b, Gamma); IC = ysxTRI_Incenter(b, c, Alpha); IA = ysxTRI_Incenter(c, b, Beta); }

	void SetMedians()
	{
		Mediana = ysxTRI_SideMedian(a, b, c); Medianb = ysxTRI_SideMedian(b, a, c); Medianc = ysxTRI_SideMedian(c, a, b);
	}

	void SetHeightAndBase()
	{
		if (Gamma <= HPI)
		{
			Height = b * sin(Gamma);
			if (a >= b * cos(Gamma)) { Base = b * cos(Gamma); Base0 = fabs(a - (b * cos(Gamma))); }
			else { Base = a; Base0 = fabs(a - (b * cos(Gamma))); }
		}
		else { Height = b * sin(PI - Gamma); Base = b * cos(PI - Gamma); Base0 = a; }
	}

	void SetCoords()
	{
		Coord[0].x = 0; Coord[0].y = 0; Coord[1].x = round(a); Coord[1].y = 0; Coord[2].x = round(b * cos(Gamma)); Coord[2].y = round(Height);
		if (Gamma > HPI) { Coord[0].x = round(b * cos(PI - Gamma)); Coord[1].x = round(a + (b * cos(Gamma))); Coord[2].x = 0; }
	}

	// This function calls 'SetCoords()':
	void SetMidpoints()
	{
		SetCoords();
		Midpts[0].x = round(0.5 * (Coord[1].x - Coord[0].x)) + Coord[0].x; Midpts[0].y = round(0.5 * (Coord[1].y - Coord[0].y)) + Coord[0].y;
		if (Coord[1].x >= Coord[2].x) { Midpts[1].x = round(0.5 * (Coord[1].x - Coord[2].x)) + Coord[2].x; }
		else { Midpts[1].x = round(0.5 * (Coord[2].x - Coord[1].x)) + Coord[1].x; }
		if (Coord[1].y >= Coord[2].y) { Midpts[1].y = round(0.5 * (Coord[1].y - Coord[2].y)) + Coord[2].y; }
		else { Midpts[1].y = round(0.5 * (Coord[2].y - Coord[1].y)) + Coord[1].y; }
		Midpts[2].x = round(0.5 * (Coord[2].x - Coord[0].x)); Midpts[2].y = round(0.5 * (Coord[2].y - Coord[0].y));
	}

	void SetArea() { A = a * Height * 0.5; }

	void SetPerimeter() { P = a + b + c; }

	void SetAll()
	{
		SetRatios(); // Also get the bigger size
		SetAngles();
		SetBisectors();
		SetIncenter(); SetInradius();
		SetMedians();
		SetHeightAndBase();
		SetMidpoints(); // Also get coordinates
		SetArea(); SetPerimeter();
	}

	// ############################

	void CoutInfo()
	{
		std::cout << "\n############## TRIANGLE ##############\n\n";
		std::string LType, AType;
		if (LnghtType == 1) { LType = "Equilateral"; } else if (LnghtType == 2) { LType = "Isoceles"; } else if (LnghtType == 3) { LType = "Scalene"; }
		if (AngType == 1) { AType = "Right"; } else if (AngType == 2) { AType = "Acute"; } else if (AngType == 3) { AType = "Obtuse"; }
		std::cout << "Tipo triangulo = " << LType << " & " << AType << " | Bigger: " << BiggerSide << '\n';
		std::cout << "*** a: " << a << " | Alpha: " << Alpha << " | BisA: " << BisA << " ***\n";
		std::cout << "*** b: " << b << " | Beta: " << Beta << " | BisB: " << BisB << " ***\n";
		std::cout << "*** c: " << c << " | Gamma: " << Gamma << " | BisC: " << BisC << " ***\n";
		std::cout << "# Height: " << Height << " | Base: " << Base << " | Base0: " << Base0 << " #\n";
		std::cout << "# Area: " << A << " | Perimetro: " << P << " #\n";
		std::cout << "Incenter: IB: " << IB << " | IA: " << IA << " | IC: " << IC << " | Inradius: " << Inradius << '\n';
		std::cout << "Circumcentro: x: " << Circumcenter.x << " | y: " << Circumcenter.y << '\n';
		std::cout << "\n#####################\n\n";
		std::cout << "Coordinates x: 0: " << Coord[0].x << " | 1: " << Coord[1].x << " | 2: " << Coord[2].x << '\n';
		std::cout << "Coordinates y: 0: " << Coord[0].y << " | 1: " << Coord[1].y << " | 2: " << Coord[2].y << '\n';
		std::cout << "Midpts x: 0: " << Midpts[0].x << " | 1: " << Midpts[1].x << " | 2: " << Midpts[2].x << '\n';
		std::cout << "Midpts y: 0: " << Midpts[0].y << " | 1: " << Midpts[1].y << " | 2: " << Midpts[2].y << '\n';
		std::cout << "\n#####################\n\n";
		std::cout << "Ratios: a: " << Ratios[0] << " | b: " << Ratios[1] << " | c: " << Ratios[2] << '\n';
		std::cout << "\n############## END TRI ##############\n\n";
	}
	
	// ############################
	
	ysxTRI_Triangle(double asize, double bsize, double Rad)
	{
		a = asize; b = bsize; c = ysxGEO_LawCos(a, b, Rad);
		Gamma = Rad;
		SetAll();
	}
};

#endif
