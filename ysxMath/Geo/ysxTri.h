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
	   @				| 'class' 'Triangle' works with '{ a, b, Gamma }'; And I believe all triangle functions I made works like 
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
 * Triangle class now uses only 'rad';

 #################################################
 REFERENCES:
 #################################################*/


// #################################################
// #################################################
// #################################################

// ANGLES:
// Angle by sides, care with div by 0 | Alpha = bc, Beta = ac, Gama = ab
double ysxTRI_Ang(double a, double b, double c) { double d = 2.0 * b * c; if (d == 0) { return(0); } return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / d)); }

// SIZES:
double ysxTRI_Ret2TriRetIso(double a, double b) { return(sqrt((a * a + b * b)) / ROOT2); } // Make an 'a & b' Triangle to an 'a & a' Triangle
double ysxTRI_Side(double hip, double Length) { return(sqrt(hip * hip - Length * Length)); } // Height or Width
double ysxTRI_HghtsS(double a, double Rad) { return(a * sin(Rad)); } // Length * sin().
double ysxTRI_BaseC(double a, double Rad) { return(a * cos(Rad)); } // Length * cos().

// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
// The altitude from, for example, the side of length a
// Altitude of a right triangle is 'h^2 = pq; h = sqrt(pq)", 'h' is altitude and 'p + q' is the 'hipotenuse' divided by the Altitude line.
constexpr double ysxTRI_Alt(double Area, double a) { return(a == 0 ? 0 : (2.0 * Area) / a); }

// PERIMETERS AND AREAS:
constexpr double ysxTRI_Perim(double a, double b, double c) { return(a + b + c); } // Perimeter
double ysxTRI_Area(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double ysxTRI_AreaAAS(double b, double Alpha, double Beta) { double S = sin(Beta); return(S == 0 ? 0 : (pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * S); } // Area
double ysxTRI_AreaASA(double a, double Beta, double Gama) { double S = sin(Beta + Gama); return(S == 0 ? 0 : (pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * S); } // Area
double ysxTRI_AreaHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

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
// Bisector (acute):
// For 'c' shorter than 'b', else, make 'c' the new 'b'.
double ysxTRI_BisAct(double a, double b, double Rad)
{
	double Beta = ysxGEO_LawSinRad(a, b, Rad); if (a < cos(Rad) * b) { Beta = PI - Beta; }
	double R = 0.5 * (Beta - Rad);
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
	double B = ysxGEO_LawSinRad(a, b, Rad); if (a < cos(Rad) * b) { B = PI - B; }
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
	double a = 0, b = 0, c = 0;
	double Alpha = 0, Beta = 0, Gamma = 0;

	// Largest side: 'a', 'b', 'c', or 'n' if there is no unique largest side.
	uint8_t BiggerSide = 'n';

	// Height relative to side 'a'.
	// 'a = Base0 + Base1', at the point the height line splits it.
	double Height = 0;
	double Base0 = 0, Base1 = 0;

	// Area and perimeter.
	double Area = 0;
	double Perimeter = 0;

	// Median lengths.
	double Mediana = 0, Medianb = 0, Medianc = 0;

	// Side ratios relative to the largest side.
	double Ratios[3] = { 0, 0, 0 };

  // Coordinates:
	Point<double> Coord[3] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
	Point<double> Mid[3] = { { 0, 0 }, { 0, 0 }, { 0, 0 } }; // Midpoints
	Point<double> Circumcenter = { 0, 0 };

	//enum TriTypeLength { NoTypeLgt, Equilateral, Isoceles, Scalene };
	//enum TriTypeAngle { NoTypeAng, Right, Acute, Obtuse };
	uint16_t TypeLength = 0;
	uint16_t TypeAngle = 0;
	
		// DERIVED GEOMETRY:
	// Angle bisectors from vertices A, B and C.
	double BisA = 0, BisB = 0, BisC = 0;

	// Distances from the incenter to vertices A, B and C.
	double IA = 0, IB = 0, IC = 0;

	// Incenter and incircle.
	double Incircle = 0, Inradius = 0;

	// Perpendicular bisectors.
	double PerpBisAC = 0, PerpBisBC = 0;

	// Circumcircle.
	double Circumcircle = 0, Circumradius = 0;

  // #################################################

  // Utility:
	const double Epsilon = 1e-10;
	bool NearlyEqual(double x, double y) { return(abs(x - y) <= Epsilon); }

	// Law of Cosines: c² = a² + b² - 2ab cos(γ)
	void SetSides() { c = sqrt(a * a + b * b - 2.0 * a * b * cos(Gamma)); }

	// Side classification:
	void SetBiggerSide()
	{
		if (NearlyEqual(a, b) && NearlyEqual(b, c)) { BiggerSide = 'n'; return; }

		if (a > b && a > c) { BiggerSide = 'a'; }
		else if (b > a && b > c) { BiggerSide = 'b'; }
		else if (c > a && c > b) { BiggerSide = 'c'; }
		else { BiggerSide = 'n'; } // There is no unique bigger side.
	}

	void SetRatios()
	{
		SetBiggerSide();
		if (BiggerSide == 'a') { Ratios[0] = 1; Ratios[1] = b / a; Ratios[2] = c / a; }
		else if (BiggerSide == 'b') { Ratios[0] = a / b; Ratios[1] = 1; Ratios[2] = c / b; }
		else if (BiggerSide == 'c') { Ratios[0] = a / c; Ratios[1] = b / c; Ratios[2] = 1; }
		else { Ratios[0] = 1.0; Ratios[1] = 1.0; Ratios[2] = 1; }

		if (NearlyEqual(a, b) && NearlyEqual(b, c)) { TypeLength = 1; }
		else if ( NearlyEqual(a, b) || NearlyEqual(a, c) || NearlyEqual(b, c)) { TypeLength = 2; }
		else { TypeLength = 3; }
	}

	// Angles:
	void SetAngles()
	{
		double CosAlpha = (b * b + c * c - a * a) / (2 * b * c);
		double CosBeta = (a * a + c * c - b * b) / (2 * a * c);
		double CosGamma = (a * a + b * b - c * c) / (2 * a * b);
		Alpha = acos(CosAlpha); Beta = acos(CosBeta); Gamma = acos(CosGamma);
		
		if (NearlyEqual(Alpha, PI * 0.5) || NearlyEqual(Beta, PI * 0.5) || NearlyEqual(Gamma, PI * 0.5)) { TypeAngle = 1; }
		else if (Alpha < PI * 0.5 && Beta < PI * 0.5 && Gamma < PI * 0.5) { TypeAngle = 2; }
		else { TypeAngle = 3; }
	}

	// Angle bisectors:
	void SetBisectors()
	{
		double Numerator = b * c * ((b + c) * (b + c) - a * a);
		BisA = sqrt(std::max(0.0, Numerator)) / (b + c);
		Numerator = a * c * ((a + c) * (a + c) - b * b);
		BisB = sqrt(std::max(0.0, Numerator)) / (a + c);
		Numerator = a * b * ((a + b) * (a + b) - c * c);
		BisC = sqrt(std::max(0.0, Numerator)) / (a + b);
	}

	// Incenter:
	void SetIncenter()
	{
		Inradius = ysxTRI_Inrad(a, b, c);
		IA = Inradius / sin(Gamma * 0.5);
		IB = Inradius / sin(Alpha * 0.5);
		IC = Inradius / sin(Beta * 0.5);
	}

	void SetInradius() { Inradius = ysxTRI_Inrad(a, b, c); }

	// Medians:
	void SetMedians() { Mediana = ysxTRI_SideMedian(a, b, c); Medianb = ysxTRI_SideMedian(b, a, c); Medianc = ysxTRI_SideMedian(c, a, b); }

	// Height and coordinate-system dimensions:
	void SetHeightAndBase()
	{
		Height = b * sin(Gamma);
		double Projection = b * cos(Gamma);
		if (Projection >= 0.0) { Base0 = std::min(c, Projection); Base1 = abs(c - Projection); }
		else { Base0 = abs(Projection); Base1 = c; }
	}

	// Coordinates:
	void SetCoords()
	{
		double Cx = b * cos(Gamma);
		double Cy = b * sin(Gamma);

		Coord[0].x = 0; Coord[0].y = 0;
		Coord[1].x = Cx; Coord[1].y = Cy;
		Coord[2].x = a; Coord[2].y = 0;
	}

	// Midpoints:
	void SetMidpoints()
	{
		SetCoords();
		for (uint8_t i = 0; i < 3; ++i)
		{
			uint8_t Next = (i + 1) % 3;
			Mid[i].x = (Coord[i].x + Coord[Next].x) * 0.5;
			Mid[i].y = (Coord[i].y + Coord[Next].y) * 0.5;
		}
	}

	// Area / perimeter:
	void SetArea() { Area = 0.5 * a * Height; }
	void SetPerimeter() { Perimeter = a + b + c; }

	// Circumcenter:
	void SetCircumcenter()
	{
		double Cx = b * cos(Gamma);
		double Cy = b * sin(Gamma);
		double Ox = c * 0.5;
		double Oy = 0.0;

		if (abs(Cy) > Epsilon) { Oy = (Cx * Cx + Cy * Cy - c * Cx) / (2 * Cy); }
		Circumcenter.x = Ox;
		Circumcenter.y = Oy;
		Circumradius = sqrt(Ox * Ox + Oy * Oy);
		Circumcircle = PI * 2 * Circumradius;
	}

	// Validation:
	bool IsValidTriangle()
	{
		if (a <= 0.0 || b <= 0.0 || c <= 0.0) { return(false); }
		return(a + b > c && a + c > b && b + c > a);
	}
	
	// #################################################

    // Return a string with triangle mathematical informatio0:
    std::string InfoString()
    {
        std::string StringTypeLength = "Unknown";
        if (TypeLength == 1) { StringTypeLength = "Equilateral"; }
        else if (TypeLength == 2) { StringTypeLength = "Isoceles"; }
        else if (TypeLength == 3) { StringTypeLength = "Scalene"; }

        std::string StringTypeAngle = "Unknown";
        if (TypeAngle == 1) { StringTypeAngle = "Right"; }
        else if (TypeAngle == 2) { StringTypeAngle = "Acute"; }
        else if (TypeAngle == 3) { StringTypeAngle = "Obtuse"; }

        std::string Info = "";
        Info += "\n############## TRIANGLE ##############\n\n";
        Info += "Triangle = " + StringTypeLength + " & " + StringTypeAngle + " | Bigger: " + (char)BiggerSide + "\n";
        Info += "*** a: " + std::to_string(a) + " | Alpha: " + std::to_string(Alpha) + " | BisA: " + std::to_string(BisA) + " ***\n";
        Info += "*** b: " + std::to_string(b) + " | Beta: " + std::to_string(Beta) + " | BisB: " + std::to_string(BisB) + " ***\n";
        Info += "*** c: " + std::to_string(c) + " | Gamma: " + std::to_string(Gamma) + " | BisC: " + std::to_string(BisC) + " ***\n\n";
        Info += "# Height: " + std::to_string(Height) + " #\n";
        Info += "# Area: " + std::to_string(Area) + " | Perimeter: " + std::to_string(Perimeter) + " #\n\n";
        Info += "Incenter distances: IA: " + std::to_string(IA) + " | IB: " + std::to_string(IB) + " | IC: " + std::to_string(IC) + " | Inradius: " + std::to_string(Inradius) + "\n";
        Info += " * Incircle Area: " + std::to_string(PI * Inradius * Inradius) + " | Incircle Perimeter: " + std::to_string(PI * 2 * Inradius) + "\n";
        Info += "Circumcenter: x: " + std::to_string(Circumcenter.x) + " | y: " + std::to_string(Circumcenter.y) + " | Circumradius: " + std::to_string(Circumradius) + "\n\n";
        Info += "\n#####################\n\n";
        Info += "Coordinates:\n";
        for (uint8_t i = 0; i < 3; ++i) { Info += "  " + std::to_string(i) + ": { " + std::to_string(Coord[i].x) + ", " + std::to_string(Coord[i].y) + " }\n"; }
        Info += "\nMidpoints:\n";
        for (uint8_t i = 0; i < 3; ++i) { Info += "  " + std::to_string(i) + ": { " + std::to_string(Mid[i].x) + ", " + std::to_string(Mid[i].y) + " }\n"; }
        Info += "\nRatios: a: " + std::to_string(Ratios[0]) + " | b: " + std::to_string(Ratios[1]) + " | c: " + std::to_string(Ratios[2]) + "\n\n";
        Info += "\n############## END TRI INFO ##############\n\n";
        return(Info);
    }
    
  // #################################################
  
  // Recalculate everything:
	void SetAll()
	{
		//if (!IsValidTriangle()) { TypeLength = 0; TypeAngle = 0; return; }
		SetSides();
		std::cout << "SetSides();\n";
		SetRatios();
		std::cout << "SetRatios();\n";
		SetAngles();
		std::cout << "SetAngles();\n";
		SetHeightAndBase();
		std::cout << "SetHeightAndBase();\n";
		SetArea();
		std::cout << "SetArea();\n";
		SetPerimeter();
		std::cout << "SetPerimeter();\n";
		SetBisectors();
		std::cout << "SetBisectors();\n";
		SetInradius();
		std::cout << "SetInradius();\n";
		SetIncenter();
		std::cout << "SetIncenter()\n";
		SetMedians();
		std::cout << "SetMedians();\n";
		SetMidpoints();
		std::cout << "SetMidpoints();\n";
		SetCircumcenter();
		std::cout << "SetCircumcenter();\n";
	}
	
	ysxTRI_Triangle(double a_in, double b_in, double gamma_in)
	{
		if (a_in == 0) { a_in = 0.000001; }
		if (b_in == 0) { b_in = 0.000001; }
		a = a_in; b = b_in; Gamma = gamma_in; SetAll();
	}
	
	// #################################################
	
};

#endif
