#pragma once

#ifndef YSXTRI_H
#define YSXTRI_H

// #####################
// ####### By Sophia Cristina
// ####### Triangle maths
// #####################

// #################################################
// REFERENCES:
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// ANGLES:
double TriAng(double Alpha, double Beta) { return(180 - (Alpha + Beta)); } // Retorna angulo restante subtraido de dois valores | "Input" e "Output" em "Graus".
double TriAng(double a, double b, double c) { return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2.0 * b * c))); } // Angulo função de tres medidas | Alpha = bc, Beta = ac, Gama = ab

// SIZES:
double hipo(double a, double b) { return(sqrt(a * a + b * b)); } // Hipotenusa | Se não me engano tem uam formula nativa do c++ para isso
double RetTri2RetIsoTri(double a, double b) { return(sqrt(((a * a) + (b * b))) / sqrt(2)); } // Make an 'a & b' Triangle to an 'a & a' Triangle
double TriSide(double hip, double Length) { return(sqrt((hip * hip) - (Length * Length))); } // Altura ou Base
double TriHghtsS(double a, double Rad) { return(a * sin(Rad)); } // Comprimento * seno(angulo).
double TriBaseC(double a, double Rad) { return(a * cos(Rad)); } // Comprimento * cos(angulo).

// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
// The altitude from, for example, the side of length a
// Altitude of a right triangle is 'h^2 = pq; h = sqrt(pq)", 'h' is altitude and 'p + q' is the 'hipotenuse' divided by the Altitude line.
double TriAlt(double Area, double a) { return((2.0 * Area) / a); }

// PERIMETERS AND AREAS:
double PerimTri(double a, double b, double c) { return(a + b + c); } // Perimetro
double TriAr(double a, double b) { return(0.5 * a * b); } // Area
double TriAr(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double TriArAAS(double b, double Alpha, double Beta) { return((pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * sin(Beta)); } // Area
double TriArASA(double a, double Beta, double Gama) { return((pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * sin(Beta + Gama)); } // Area
double TriArHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

// MEDIANS:
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double MedianSideRelation(double a, double b, double c) { return((3.0 / 4) * (a * a + b * b + c * c)); }
double TriMedian(double a, double b, double c) { return(0.5 * sqrt((2 * pow(b, 2)) + (2 * pow(c, 2)) - pow(a, 2))); }
double TriSideMedian(double a, double b, double c) { return (sqrt((2 * (b * b) + 2 * (c * c) - (a * a)) / 4.0)); } // Formula to 'Median a', to 'Median b', use this input order "b, c, a" and "c, a, b" to 'Median c'

// BISECTORS:
double TriBisAC(double Lgtha, double DegreesBC) { double DgAC = 180 - (90 + DegreesBC), D = 180 - ((180 - (DegreesBC + (DgAC * 0.5)))); return (Lgtha / sin(Ang2Rad(D))); }
double TriBisBC(double Lgthb, double DegreesAC) { double DgBC = 180 - (90 + DegreesAC), D = 180 - ((180 - ((DgBC * 0.5) + DegreesAC))); return (Lgthb / sin(Ang2Rad(D))); }
double TriBisAct(double a, double b, double Ang) // For 'c' shorter than 'b', else, make 'c' the new 'b'
{
	//double c = LawCos(a, b, Ang2Rad(Ang));
	double Rad = Ang2Rad(Ang);
	double Beta = Rad2Ang(LawSinAngle(a, b, Rad));
	if (a < cos(Rad) * b) { Beta = 180 - Beta; }
	double BisAng = 0.5 * (180 - (Ang + Beta));
	double LastAng = (180 - (90 + Ang)) - BisAng;
	double Alt;	if (Ang <= 90) { Alt = b * sin(Rad); } else { Alt = b * sin(Ang2Rad(180 - Ang)); }
	return(Alt / cos(Ang2Rad(LastAng)));
}

// https://en.wikipedia.org/wiki/Bisection:
// If the side lengths of a triangle are 'a,b,c', the semiperimeter 's = (a + b + c) / 2', and A is the angle opposite side 'a',
// then the length of the internal bisector of angle A is: "(2 * sqrt(b * c * s * (s - a))) / (b + c)":
//double LghtBis(double a, double b, double c) { double s = (a + b + c) * 0.5; return((2 * sqrt(b * c * s * (s - a))) / (b + c)); } // Lenght of a bisector
//double PerpBisa(double a, double b, double c, double Area) { return(( 2.0 * a * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double PerpBisb(double a, double b, double c, double Area) { return((2.0 * b * Area) / pow(a, 2) + pow(b, 2) - pow(c, 2)); } // Interior perpendicular bisectors
//double PerpBisc(double a, double b, double c, double Area) { return((2.0 * c * Area) / pow(a, 2) - pow(b, 2) + pow(c, 2)); } // Interior perpendicular bisectors

// CIRCUMCENTER, INRADIUS, INCENTER AND ETC:
double TriCircumR(double a, double b, double c) { return(sqrt((pow(a, 2) * pow(b, 2) * pow(c, 2))/((a + b + c) * (- a + b + c) * (a - b + c) * (a + b - c)))); } // Circumradius
double TriInradius(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c)) / s); } // Inradius
double TriIncenter(double a, double b, double Ang) // Lenght from 'I' to 'B'
{
	double Gamma = Ang2Rad(Ang), c = LawCos(a, b, Gamma), BisL = TriBisAct(a, b, Ang);
	double Beta = LawSinAngle(a, b, Gamma); if (a < cos(Gamma) * b) { Beta = PI - Beta; } double Alpha = PI - (Gamma + Beta);
	double Inc = TriBisAct(BisL, c, Rad2Ang(Alpha * 0.5)); return(Inc);
}

// ADJACENT TRIANGLE:
// Suppose two adjacent but non - overlapping triangles share the same side of length f and share the same circumcircle,
// so that the side of length f is a chord of the circumcircle and the triangles have side lengths(a, b, f) and (c, d, f),
// with the two triangles together forming a cyclic quadrilateral with side lengths in sequence(a, b, c, d). Then:
double TriAdj(double a, double b, double c, double d) { return(sqrt((((a * c) + (b * d)) * ((a * d) + (b * c)))/((a * b) + (c * d)))); }

// #################################################
// ############## TRIANGLE ##############
class Triangulo
{
public:
	// ############################
	char Bigger = 'n';
	char GetBigger(double a, double b, double c)
	{ char Ret = 'n'; if (c > b && c > a) { Ret = 'c'; } else if (b > c && b > a) { Ret = 'b'; } else if (a > b && a > c) { Ret = 'a'; } return (Ret); }
	// ############################
	std::vector<double> GetRatios(double a, double b, double c)
	{
		std::vector<double> TRatios(3);
		char Big = GetBigger(a, b, c);
		
		if (Big == 'c') { TRatios[0] = a / c; TRatios[1] = b / c; TRatios[2] = 1; }
		else if (Big == 'b') { TRatios[0] = a / b; TRatios[1] = 1; TRatios[2] = c / b; }
		else if (Big == 'a') { TRatios[0] = 1; TRatios[1] = b / a; TRatios[2] = c / a; }
		else if (Big == 'n') { TRatios[0] = 1; TRatios[1] = 1; TRatios[2] = 1; }
		return(TRatios);
	};
	// ############################
	double a, b, c; // Tamanho
	double Alpha, Beta, Gamma; // Angulos
	double Alt, Base, Base0; // Altura e as duas bases (linha dividida pelo ponto tocado pela altura se o triangulo não for reto), Triangulo -> /_|_\ <- As bases são os '_', a altura é '|'
	double Area, Perimetro;
	double Mediana, Medianb, Medianc; // Angulos
	double Ratios[3]; // Razão baseada no maior valor de um comprimeto de lado
	enum TriLnghtType { NoTypeLgt, Equilateral, Isoceles, Scalene };
	enum TriAngType { NoTypeAng, Right, Acute, Obtuse };
	unsigned char LnghtType = NoTypeLgt, AngType = NoTypeAng; // Make it a single byte with 8 flags, 4 for ang type and 4 for lenght type
	// ############################
	Point<int> Coord[3], Midpoints[3], Circumcenter;
	// ############################
	double BisA, BisB, BisC; // Bisetores
	double IA, IB, IC; // Incenter to 'A' or 'B' or 'C'
	double Incircle, Inradius;
	double PerpBisAC, PerpBisBC; // Bisetores Perpendiculares
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
		std::cout << "# Alt: " << Alt << " | Base: " << Base << " | Base0: " << Base0 << " #\n";
		std::cout << "# Area: " << Area << " | Perimetro: " << Perimetro << " #\n";
		std::cout << "Incenter: IB: " << IB << " | IA: " << IA << " | IC: " << IC << " | Inradius: " << Inradius << std::endl;
		std::cout << "Circumcentro: x: " << Circumcenter.x << " | y: " << Circumcenter.y << std::endl;
		std::cout << "\n#####################\n\n";
		std::cout << "Coordinates x: 0: " << Coord[0].x << " | 1: " << Coord[1].x << " | 2: " << Coord[2].x << std::endl;
		std::cout << "Coordinates y: 0: " << Coord[0].y << " | 1: " << Coord[1].y << " | 2: " << Coord[2].y << std::endl;
		std::cout << "Midpoints x: 0: " << Midpoints[0].x << " | 1: " << Midpoints[1].x << " | 2: " << Midpoints[2].x << std::endl;
		std::cout << "Midpoints y: 0: " << Midpoints[0].y << " | 1: " << Midpoints[1].y << " | 2: " << Midpoints[2].y << std::endl;	
		std::cout << "\n#####################\n\n";
		std::cout << "Ratios: a: " << Ratios[0] << " | b: " << Ratios[1] << " | c: " << Ratios[2] << std::endl;
		std::cout << "\n############## END TRI ##############\n\n";
	}
	// ############################
	Triangulo(double asize, double bsize, double Angle)
	{
		double Rad = Ang2Rad(Angle);
		a = asize; b = bsize; c = LawCos(a, b, Rad);
		// Razões:
		Bigger = GetBigger(a, b, c);
		Ratios[0] = GetRatios(a, b, c)[0]; Ratios[1] = GetRatios(a, b, c)[1]; Ratios[2] = GetRatios(a, b, c)[2];
		if (Bigger == 'n') { LnghtType = Equilateral; }
		else if (Ratios[0] != Ratios[1] && Ratios[0] != Ratios[2] && Ratios[1] != Ratios[2]) { LnghtType = Scalene; }
		else { LnghtType = Isoceles; }
		//if (Ratios[0] == Ratios[1] || Ratios[0] == Ratios[2] || Ratios[1] == Ratios[2]) { LnghtType = Isoceles; }
		// Angulos:
		Beta = Rad2Ang(LawSinAngle(a, b, Rad));
		if (a < cos(Rad) * b) { Beta = 180 - Beta; AngType = Obtuse; }
		Gamma = Angle;
		Alpha = 180 - (Gamma + Beta);

		// Angulos:
		if (Alpha == 90 || Beta == 90 || Gamma == 90) { AngType = Right; }
		if (Alpha < 90 && Beta < 90 && Gamma < 90) { AngType = Acute; }
		if (Alpha > 90 || Beta > 90 || Gamma > 90) { AngType = Obtuse; }

		// Bisetores:
		BisA = TriBisAct(a, b, Gamma); BisB = TriBisAct(b, c, Alpha); BisC = TriBisAct(c, a, Beta);
		if (Angle > 90) { BisA = TriBisAct(b, a, Gamma); BisB = TriBisAct(c, a, Alpha); BisC = TriBisAct(c, b, Beta); }

		// Incenter:
		IB = TriIncenter(a, b, Gamma); IC = TriIncenter(b, c, Alpha); IA = TriIncenter(c, b, Beta); Inradius = TriInradius(a, b, c);

		// Medians:
		Mediana = TriSideMedian(a, b, c); Medianb = TriSideMedian(b, a, c); Medianc = TriSideMedian(c, a, b);

		// Altura e Bases:
		if (Angle <= 90)
		{
			Alt = b * sin(Rad);
			if (a >= b * cos(Rad)) { Base = b * cos(Rad); Base0 = fabs(a - (b * cos(Rad))); }
			else { Base = a; Base0 = fabs(a - (b * cos(Rad))); }
		} // Mudar
		else { Alt = b * sin(Ang2Rad(180 - Angle)); Base = b * cos(Ang2Rad(180 - Angle)); Base0 = a; }
		// Mapear:
		Coord[0].x = 0; Coord[0].y = 0; Coord[1].x = round(a); Coord[1].y = 0; Coord[2].x = round(b * cos(Rad)); Coord[2].y = round(Alt);
		if (Angle > 90) { Coord[0].x = round(b * cos(Ang2Rad(180 - Angle))); Coord[1].x = round(a + (b * cos(Rad))); Coord[2].x = 0; }

		// Midpoints:
		Midpoints[0].x = round(0.5 * (Coord[1].x - Coord[0].x)) + Coord[0].x; Midpoints[0].y = round(0.5 * (Coord[1].y - Coord[0].y)) + Coord[0].y;
		if (Coord[1].x >= Coord[2].x) { Midpoints[1].x = round(0.5 * (Coord[1].x - Coord[2].x)) + Coord[2].x; }
		else { Midpoints[1].x = round(0.5 * (Coord[2].x - Coord[1].x)) + Coord[1].x; }
		if (Coord[1].y >= Coord[2].y) { Midpoints[1].y = round(0.5 * (Coord[1].y - Coord[2].y)) + Coord[2].y; }
		else { Midpoints[1].y = round(0.5 * (Coord[2].y - Coord[1].y)) + Coord[1].y; }
		Midpoints[2].x = round(0.5 * (Coord[2].x - Coord[0].x)); Midpoints[2].y = round(0.5 * (Coord[2].y - Coord[0].y));
		// Circumcentro:
		// Area e perimetro:
		Area = a * Alt * 0.5; Perimetro = a + b + c;
	}
};

#endif // SCPARSE_