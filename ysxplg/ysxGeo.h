#pragma once

#ifndef YSXGEO_H
#define YSXGEO_H

#include "ysxConst.h";

using namespace std;

// #####################################################################################################################################

// ATENÇÃO: QUASE TODOS OS ANGULOS DEVEM SER COLOCADOS COMO RADIANOS, USAR FUNÇÃO "Ang2Rad" SE NÃO SOUBER!!!!!!!
// VAI ESTAR ESCRITO NOS INPUTS DAS FUNÇÕES, ANGULO OU RAD.

// ATENÇÃO: Lado "a" de um triangulo sempre sera a linha reta horizontal, e o lado "b" sempre sera a linha da esquerda.

// #####################################################################################################################################

// #####################################################################################################################################
// ############################
// ####### FUNÇÕES #######
// ############################

// ####### TÉCNICOS:
// CONVERSORES:
double Ang2Rad(double a) { return((a / 360) * Tau); }
double Rad2Ang(double r) { return((r / Tau) * 360); }

// PI E ANGULOS:
double PiRatio(double Div) { return (Pi / Div); }
double AngRatio(double Div) { return (360.0 / Div); }

// FUNÇÕES:
double csc(double x) { return(1.0 / sin(x)); }
double sec(double x) { return(1.0 / cos(x)); }
double cot(double x) { return(1.0 / tan(x)); }
double versin(double x) { return(1.0 - cos(x)); }
double exsec(double x) { return((1.0 / cos(x)) - 1.0); }
double excsc(double x) { return(exsec((Pi * 0.5) - x)); }
double crd(double x) { return(2.0 * sin(x * 0.5)); }
double cos2(double x) { return(cos(x) * cos(x)); }
double sin2(double x) { return(sin(x) * sin(x)); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ####### POLIGONOS:
double Perim(double Sides, double Size) { return(Sides * Size); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### ANGULOS:
// #####################
// ####### ANGULOS:
double AngTri(double Alpha, double Beta) { return(180 - (Alpha + Beta)); } // Retorna angulo restante subtraido de dois valores | "Input" e "Output" em "Graus".
double AngTri(double a, double b, double c) { return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2.0 * b * c))); } // Angulo função de tres medidas | Alpha = bc, Beta = ac, Gama = ab
double AngAct(double Ang) { return(90 - Ang); } // Acute | "Input" e "Output" em "Graus".
double AngObt(double Ang) { return(180 - Ang); } // Obtuse | "Input" e "Output" em "Graus".
double AngWhl(double Ang) { return(360 - Ang); } // Whole | "Input" e "Output" em "Graus".
double SumIntAngPolygn(double Sides) { return(180 * (Sides - 2)); } // Sum of the internal angles of a Polygon
double AngPolygn(double Sides) { return((180 * (Sides - 2)) / Sides); } // Internal angles of a Polygon
double AngPolygrm(double Sides) { return(((360 * (Sides - 2)) / Sides) - 180); } // 180 - (360 - (((180 * (Sides - 2)) / Sides) * 2)) Before Wolfam Alpha
// Paralel over Transversal:
Point3DFlt ParaTrans(double Ang) { if (Ang > 360) { Ang = 360; } if (Ang > 180) { Ang = 360 - Ang; } Point3DFlt R = {Ang, 180 - Ang, 180 + Ang }; return(R); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### TRIANGULOS
// #####################

// ####### TAMANHOS:
double hipo(double a, double b) { return(sqrt((a * a) + (b * b))); } // Hipotenusa
double SideTri(double hip, double Length) { return(sqrt((hip * hip) - (Length * Length))); } // Altura ou Base
double HghtTrisS(double a, double Rad) { return(a * sin(Rad)); } // Comprimento * seno(angulo).
double BasTriC(double a, double Rad) { return(a * cos(Rad)); } // Comprimento * cos(angulo).
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double AltTri(double Area, double a) { return((2.0 * Area) / a); } // The altitude from, for example, the side of length a

// ####### LEIS TRIGONOMETRICAS:
// LAW OF COSINE:
double LawCos(double a, double b, double Rad) { return(sqrt(pow(a, 2) + pow(b, 2) - (2 * a * b * cos(Rad)))); } // Retorna tamanho de uma linha usando angulo e dois valores
double LawCosAngle(double a, double b, double c) { return (acos((a * a + b * b - c * c) / (2 * a * b))); } // Retorna valor de angulo usando tres valores de linha

// LAW OF SINE:
double LawSin(double Height, double Rad) { if (sin(Rad) != 0) { return(Height / sin(Rad)); } else { return(0); } } // Altura dividido por seno retorna comprimento
double LawSin0(double Width, double Rad) { if (sin(Rad) != 0) { return(Width / cos(Rad)); } else { return(0); } } // Base dividido por coseno retorna comprimento
// Input and Return in Radians, find an angle by Law of Sine:
double LawSinAngle(double a, double b, double Rad) { double c = LawCos(a, b, Rad);	double Ret = asin((sin(Rad) * b) / c);	return(Ret); }
double LawSinAngle(double a, double b, double c, double Rad) { return(asin((sin(Rad) * b) / c)); }

// LAW OF TANGENT:
// The law of tangents states that: (a - b)/(a + b) = tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta)):
double LawTan(double a, double b) { return((a - b) / (a + b)); }
double LawTanAng(double Alpha, double Beta) { return(tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta))); }
// Wolfram Alpha me deu a solução de b como: a * csc(Alpha) * sin(Beta);
double LawTanb(double a, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); }

// LAW OF COTANGENT:
double LawCota(double a, double b, double c, double Alpha) { return(cot(Alpha) / (((a + b + c) * 0.5) - a)); }
double LawCotb(double a, double b, double c, double Beta) { return(cot(Beta) / (((a + b + c) * 0.5) - b)); }
double LawCotc(double a, double b, double c, double Gama) { return(cot(Gama) / (((a + b + c) * 0.5) - c)); }
double Mollweidepos(double a, double b, double c) { return((a + b) / c); } // Based on Law of Cotangent = cos((Alpha - Beta) * 0.5) / sin(Gama * 0.5)
double Mollweideneg(double a, double b, double c) { return((a - b) / c); } // Based on Law of Cotangent = sin((Alpha - Beta) * 0.5) / cos(Gama * 0.5)
double MollweideposAng(double Alpha, double Beta, double Gama) { return(cos((Alpha - Beta) * 0.5) / sin(Gama * 0.5)); } // Based on Law of Cotangent = (a + b) / c
double MollweidenegAng(double Alpha, double Beta, double Gama) { return(sin((Alpha - Beta) * 0.5) / cos(Gama * 0.5)); } // Based on Law of Cotangent = (a - b) / c

// ####### PERIMETROS E AREAS:
double PerimTri(double a, double b, double c) { return(a + b + c); } // Perimetro
double AreaTri(double a, double b) { return(0.5 * a * b); } // Area
double AreaTri(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double AreaTriAAS(double b, double Alpha, double Beta) { return((pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * sin(Beta)); } // Area
double AreaTriASA(double a, double Beta, double Gama) { return((pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * sin(Beta + Gama)); } // Area
double AreaTriHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

// ####### MÉDIAS:
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double MedianSideRelation(double a, double b, double c) { return((3.0 / 4) * (pow(a, 2) + pow(b, 2) + pow(c, 2))); }
double MedianTri(double a, double b, double c) { return(0.5 * sqrt((2 * pow(b, 2)) + (2 * pow(c, 2)) - pow(a, 2))); }
double Median(double a, double b, double c) // Formula to 'Median a', to 'Median b', use this input order "b, c, a" and "c, a, b" to 'Median c'
{ return (sqrt((2 * (b * b) + 2 * (c * c) - (a * a)) / 4.0)); }

// ####### BISETORES:
double LgthBisAC(double Lgtha, double DegreesBC) { double DgAC = 180 - (90 + DegreesBC), D = 180 - ((180 - (DegreesBC + (DgAC * 0.5)))); return (Lgtha / sin(Ang2Rad(D))); }
double LgthBisBC(double Lgthb, double DegreesAC) { double DgBC = 180 - (90 + DegreesAC), D = 180 - ((180 - ((DgBC * 0.5) + DegreesAC))); return (Lgthb / sin(Ang2Rad(D))); }
double LgthBisAct(double a, double b, double Ang) // For 'c' shorter than 'b', else, make 'c' the new 'b'
{
	//double c = LawCos(a, b, Ang2Rad(Ang));
	double Rad = Ang2Rad(Ang);
	double Beta = Rad2Ang(LawSinAngle(a, b, Rad));
	if (a < cos(Rad) * b) { Beta = 180 - Beta; }
	double BisAng = 0.5 * (180 - (Ang + Beta));
	double LastAng = (180 - (90 + Ang)) - BisAng;
	double Alt;	if (Ang <= 90) { Alt = b * sin(Rad); }	else { Alt = b * sin(Ang2Rad(180 - Ang)); }
	return(Alt / cos(Ang2Rad(LastAng)));
}

// ####### CIRCUMCENTER, INRADIUS, INCENTER E ETC:
double TriCircumR(double a, double b, double c) { return(sqrt((pow(a, 2) * pow(b, 2) * pow(c, 2))/((a + b + c) * (- a + b + c) * (a - b + c) * (a + b - c)))); } // Circumradius
double TriInradius(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c)) / s); } // Inradius
double TriIncenter(double a, double b, double Ang) // Lenght from 'I' to 'B'
{
	double Gamma = Ang2Rad(Ang), c = LawCos(a, b, Gamma), BisL = LgthBisAct(a, b, Ang);
	double Beta = LawSinAngle(a, b, Gamma); if (a < cos(Gamma) * b) { Beta = Pi - Beta; } double Alpha = Pi - (Gamma + Beta);
	double Inc = LgthBisAct(BisL, c, Rad2Ang(Alpha * 0.5)); return(Inc);
}

// ADJACENT TRIANGLE:
// Suppose two adjacent but non - overlapping triangles share the same side of length f and share the same circumcircle,
// so that the side of length f is a chord of the circumcircle and the triangles have side lengths(a, b, f) and (c, d, f),
// with the two triangles together forming a cyclic quadrilateral with side lengths in sequence(a, b, c, d). Then:
double AdjTri(double a, double b, double c, double d) { return(sqrt((((a * c) + (b * d)) * ((a * d) + (b * c)))/((a * b) + (c * d)))); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### QUADRILATEROS
// #####################

double QuadriAreaBret(double s, double a, double b, double c, double d, double alpha, double gamma) { return (sqrt((s - a) * (s - b) * (s - c) * (s - d) - (a * b * c * d * cos2((alpha + gamma) / 2)))); }
double QuadriAreaBret(double a, double b, double c, double d, double alpha, double gamma) { double s = 0.5 * (a + b + c + d); return (sqrt((s - a) * (s - b) * (s - c) * (s - d) - (a * b * c * d * cos2((alpha + gamma) / 2)))); }
double EqualPeriAreaRect(double Width) { if (Width <= 2) { Width = 2.000000001; } return((2 * Width) / ( Width - 2)); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### CIRCULOS
// #####################

// ####### CIRCUNFERENCIA E AREA:
double ArCirc(double r) { return (Pi * r * r); } // Area
double ArCirc(double r, double Rad) { if (Rad > Tau) { Rad = Tau; } return((Pi * r * r) * (Rad / Tau)); }
double Circumf(double r) { return (Pi * 2 * r); } // Circumferencia

// RAIO DO CIRCULO ATRAVEZ DA AREA:
double ArCirc2r(double AreaC) { return(sqrt(AreaC / Pi)); }

// AREA DO QUADRADO ATRAVEZ DA AREA DO CIRCULO:
double ArCircQdr(double AreaC) { return(pow((ArCirc2r(AreaC) * 2), 2)); }

// AREA DO SETOR SOBREPOSTO DE DOIS CIRCULOS:
double OverlapArea(double Distance, double r)
{
	if (Distance == 0) { return (Pi * r * r); }	if (Distance >= 2 * r) { return (0); }
	double HalfAngle = acos(Distance / (2 * r)); double b = SideTri(r, Distance * 0.5); double TriArea = b * Distance * 0.5;
	double AreaSeg = HalfAngle * r * r; return ((AreaSeg - TriArea) * 2);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### ESFERAS
// #####################

// VOLUME ESFERA:
double VolSphr(double r) { return ((4.0 / 3) * Pi * pow(r, 3)); }

// SUPERFICIE ESFERA:
double SrfSphr(double r) { return (4 * Pi * pow(r, 2)); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### CILINDROS
// #####################

// VOLUME CILINDRO:
double CylinVol(double r, double h) { return(Pi * r * r * h); }

// ####### ####### ####### ####### ####### #######
// ############################
// ####### CLASSES #######
// ############################

// ####### ####### ####### ####### ####### #######
// ####### TRIANGULO:
class Triangulo
{
public:
	// ############################
	char Bigger = 'n';
	char GetBigger(double a, double b, double c)
	{ char Ret = 'n'; if (c > b && c > a) { Ret = 'c'; } else if (b > c && b > a) { Ret = 'b'; } else if (a > b && a > c) { Ret = 'a'; } return (Ret); }
	// ############################
	vector<double> GetRatios(double a, double b, double c)
	{
		vector<double> TRatios(3);
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
	double Alt, Base, Base0; // Altura e as duas bases que se ligam até a altura se o triangulo não for reto
	double Area, Perimetro;
	double Mediana, Medianb, Medianc; // Angulos
	double Ratios[3]; // Razão baseada no maior valor de um comprimeto de lado
	enum TriLnghtType { NoTypeLgt, Equilateral, Isoceles, Scalene };
	enum TriAngType { NoTypeAng, Right, Acute, Obtuse };
	char LnghtType = NoTypeLgt, AngType = NoTypeAng;
	Triangulo(double asize, double bsize, double Angle); //  ####### CONTRUCTOR #######
	// ############################
	Point Coord[3], Midpoints[3], Circumcenter;
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
		cout << "\n#####################\n\n";
		cout << "0: NoTypeLgt; 1: Equilateral; 2: Isoceles; 3: Scalene;\n";
		cout << "0: NoTypeAng; 1: Right; 2: Acute; 3: Obtuse;\n";
		cout << "Tipo triangulo = " << (int)LnghtType << " & " << (int)AngType << " | Bigger: " << Bigger << endl;
		cout << "*** a: " << a << " | Alpha: " << Alpha << " | BisA: " << BisA << " ***\n";
		cout << "*** b: " << b << " | Beta: " << Beta << " | BisB: " << BisB << " ***\n";
		cout << "*** c: " << c << " | Gamma: " << Gamma << " | BisC: " << BisC << " ***\n";
		cout << "# Alt: " << Alt << " | Base: " << Base << " | Base0: " << Base0 << " #\n";
		cout << "# Area: " << Area << " | Perimetro: " << Perimetro << " #\n";
		cout << "Incenter: IB: " << IB << " | IA: " << IA << " | IC: " << IC << " | Inradius: " << Inradius << endl;
		cout << "Circumcentro: x: " << Circumcenter.x << " | y: " << Circumcenter.y << endl;
		cout << "\n#####################\n\n";
	}
	// ############################
};

// ####### TRIANGULO | CONSTR.:
Triangulo::Triangulo(double asize, double bsize, double Angle)
{
	double Rad = Ang2Rad(Angle);
	a = asize; b = bsize; c = LawCos(a, b, Rad);
	// Razões:
	Bigger = GetBigger(a, b, c);
	Ratios[0] = GetRatios(a, b, c)[0];
	Ratios[1] = GetRatios(a, b, c)[1];
	Ratios[2] = GetRatios(a, b, c)[2];
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
	BisA = LgthBisAct(a, b, Gamma);
	BisB = LgthBisAct(b, c, Alpha);
	BisC = LgthBisAct(c, a, Beta);
	if (Angle > 90)
	{
		BisA = LgthBisAct(b, a, Gamma);
		BisB = LgthBisAct(c, a, Alpha);
		BisC = LgthBisAct(c, b, Beta);
	}

	// Incenter:
	IB = TriIncenter(a, b, Gamma);
	IC = TriIncenter(b, c, Alpha);
	IA = TriIncenter(c, b, Beta);
	Inradius = TriInradius(a, b, c);

	// Medians:
	Mediana = Median(a, b, c); Medianb = Median(b, a, c); Medianc = Median(c, a, b);

	// Altura e Bases:
	if (Angle <= 90)
	{
		Alt = b * sin(Rad);
		if (a >= b * cos(Rad)) { Base = b * cos(Rad); Base0 = fabs(a - (b * cos(Rad))); }
		else { Base = a; Base0 = fabs(a - (b * cos(Rad))); }
	} // Mudar
	else
	{
		Alt = b * sin(Ang2Rad(180 - Angle));
		Base = b * cos(Ang2Rad(180 - Angle)); Base0 = a;
	}
	// Mapear:
	Coord[0].x = 0; Coord[0].y = 0; Coord[1].x = round(a); Coord[1].y = 0; Coord[2].x = round(b * cos(Rad)); Coord[2].y = round(Alt);
	if (Angle > 90)	{ Coord[0].x = round(b * cos(Ang2Rad(180 - Angle))); Coord[1].x = round(a + (b * cos(Rad))); Coord[2].x = 0; }

	// Midpoints:
	Midpoints[0].x = round(0.5 * (Coord[1].x - Coord[0].x)); Midpoints[0].y = round(0.5 * (Coord[1].y - Coord[0].y));
	if (Coord[1].x >= Coord[2].x) { Midpoints[1].x = round(0.5 * (Coord[1].x - Coord[2].x)); } else { Midpoints[1].x = round(0.5 * (Coord[2].x - Coord[1].x)); }
	if (Coord[2].y >= Coord[2].y) { Midpoints[1].y = round(0.5 * (Coord[1].y - Coord[2].y)); } else { Midpoints[1].y = round(0.5 * (Coord[2].y - Coord[1].y)); }
	Midpoints[2].x = round(0.5 * (Coord[2].x - Coord[0].x)); Midpoints[2].y = round(0.5 * (Coord[2].y - Coord[0].y));
	// Circumcentro:
	// Area e perimetro:
	Area = a * Alt * 0.5; Perimetro = a + b + c;
}

// ####### ####### ####### ####### ####### #######
// ####### QUADRILATERO:
class Quadrilateral
{
public:
	// ############################
	char Bigger = 'n';
	char GetBigger(double a, double b, double c, double d)
	{ char Ret = 'n'; if (d > c && d > b && d > a) { Ret = 'd'; } else if (c > b && c > a && c > d) { Ret = 'c'; } else if (b > c && b > a && b > d) { Ret = 'b'; } else if (a > b && a > c && a > d) { Ret = 'a'; } return (Ret); }
	// ############################
	double a, b, c, d;
	double Alpha, Beta, Gamma, Delta;
	double Area, Perimeter;
	double Ratios[4]; // Razão baseada no maior valor de um comprimeto de lado

};

// ####### ####### ####### ####### ####### #######


// ####### ####### ####### ####### ####### #######

// ####### ####### ####### ####### ####### #######

class TestGeo
{
	public: 
		void Test()
		{
			cout << "Digite qual função:\n";
			cout << "| 1 = Hipotenusa | 2 = Angulos Tri. | 3 = Lado Tri. | 4 = Altura Tri. |\n";
			cout << "| 5 = Area Circ., 6 = Area -> Raio, 7 = Area_Circ -> Diam -> Qdr |\n";
			cout << "| 8 = Volume Cilindro Regular | 9 = Volume esfera |\n";
			cout << "| 10 = Superficie Esfera | 11 = Circumferencia Circulo |\n";
			cout << "| 12 = Alt. Tri. Sen | 13 = Law of sines |\n";
			cout << "| 14 = Law of cosines. | 15 = Perim. Tri. | 16 = Ang2Rad | 17 = Rad2Ang |\n";
			cout << "| 18 e 19 = Tamanho da linha de um angulo bisetor num triangulo reto |\n";
			cout << "| 20 = LghtBis | 21, 22 e 13 = Perpendicular Bis. a, b ou c |\n";
			cout << "| 24 = LawTan | 25 = LawTanAng | 26 = LawTanb |\n";
			cout << "| 27 = LawCota | 28 = LawCotb | 29 = LawCotc |\n";
			cout << "| 30 = Mollweidepos | 31 = Mollweideneg |\n";
			cout << "| 32 = MollweideposAng | 33 = MollweidenegAng |\n";
			cout << "| 34 = Circumcenter | 35 = Inradius | 36 = Adjacent Tri. |\n";
			cout << "| 37, 38 = Intrn Ang. Polygn or Polygrm |\n";

			int Op; cin >> Op;
	
			if (Op == 1) { cout << "hipo(a, b);\n"; double Opa, Opb; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << hipo(Opa, Opb) << endl; }
			if (Op == 2) { cout << "AngTri(a, b);\n"; double Opa, Opb; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << AngTri(Opa, Opb) << endl; }
			if (Op == 3) { cout << "SideTri(Hip, b);\n"; double Opa, Opb; cout << "Hip: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << SideTri(Opa, Opb) << endl; }
			if (Op == 4) { cout << "AltTri(Area, a);\n"; double Opa, Opb; cout << "Area: "; cin >> Opa; cout << "a: "; cin >> Opb; cout << "RETORNO: " << AltTri(Opa, Opb) << endl; }
			if (Op == 5) { cout << "ArCirc(Raio);\n"; double Opa; cout << "Raio: "; cin >> Opa; cout << "RETORNO: " << ArCirc(Opa) << endl; }
			if (Op == 6) { cout << "ArCirc2r(AreaCirculo);\n"; double Opa; cout << "Area: "; cin >> Opa; cout << "RETORNO: " << ArCirc2r(Opa) << endl; }
			if (Op == 7) { cout << "ArCircQdr(AreaCirculo);\n"; double Opa; cout << "Area: "; cin >> Opa; cout << "RETORNO: " << ArCircQdr(Opa) << endl; }
			if (Op == 8) { cout << "CylinVol(r, h);\n"; double Opr, Oph; cout << "r: "; cin >> Opr; cout << "h: "; cin >> Oph; cout << "RETORNO: " << CylinVol(Opr, Oph) << endl; }
			if (Op == 9) { cout << "VolSphr(Raio);\n"; double Opa; cout << "Raio: "; cin >> Opa; cout << "RETORNO: " << VolSphr(Opa) << endl; }
			if (Op == 10) { cout << "SrfSphr(Raio);\n"; double Opa; cout << "Raio: "; cin >> Opa; cout << "RETORNO: " << SrfSphr(Opa) << endl; }
			if (Op == 11) { cout << "Circumf(Raio);\n"; double Opa; cout << "Raio: "; cin >> Opa; cout << "RETORNO: " << Circumf(Opa) << endl; }
			if (Op == 12)
			{ 
				cout << "HghtTrisS(a, Rad);\n"; double Opa, Opan; cout << "a: "; cin >> Opa; cout << "Angulo: "; cin >> Opan;
				cout << "RETORNO: " << HghtTrisS(Opa, Opan) << endl;
			}
			if (Op == 13)
			{
				cout << "LawSin(h, Rad);\n"; double Opa, Opan; cout << "heigth: "; cin >> Opa; cout << "Angulo: "; cin >> Opan;
				cout << "RETORNO: " << LawSin(Opa, Opan) << endl;
			}
			if (Op == 14)
			{
				cout << "LawCos(a, b, Rad);\n"; double Opa, Opb, Opan;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "Angulo: "; cin >> Opan;
				cout << "RETORNO: " << LawCos(Opa, Opb, Opan) << endl;
			}
			if (Op == 15)
			{
				cout << "PerimTri(a, b, c);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "RETORNO: " << PerimTri(Opa, Opb, Opc) << endl;
			}
			if (Op == 16) { cout << "Ang2Rad(n);\n"; double Opa; cout << "n: "; cin >> Opa; cout << "RETORNO: " << Ang2Rad(Opa) << endl; }
			if (Op == 17) { cout << "Rad2Ang(n);\n"; double Opa; cout << "n: "; cin >> Opa; cout << "RETORNO: " << Rad2Ang(Opa) << endl; }
			if (Op == 18)
			{
				cout << "LgthBisAC(Alt, AngBC);\n"; double Opa, Opabc; cout << "Altura: "; cin >> Opa; cout << "Angulo: "; cin >> Opabc;
				cout << "RETORNO: " << LgthBisAC(Opa, Opabc) << endl;
			}
			if (Op == 19)
			{
				cout << "LgthBisBC(Base, AngAC);\n"; double Opb, Opaac; cout << "Base: "; cin >> Opb; cout << "Angulo: "; cin >> Opaac;
				cout << "RETORNO: " << LgthBisBC(Opb, Opaac) << endl;
			}
			if (Op == 20)
			{
				cout << "LghtBisAct(a, b, Rad);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "Rad: "; cin >> Opc;
				cout << "RETORNO: " << LgthBisAct(Opa, Opb, Opc) << endl;
			}
			if (Op == 21)
			{
				//cout << "PerpBisa(a, b, c, Area);\n"; double Opa, Opb, Opc, Opar;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				//cout << "Area: "; cin >> Opar; cout << "RETORNO: " << PerpBisa(Opa, Opb, Opc, Opar) << endl;
			}
			if (Op == 22)
			{
				//cout << "PerpBisb(a, b, c, Area);\n"; double Opa, Opb, Opc, Opar;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				//cout << "Area: "; cin >> Opar; cout << "RETORNO: " << PerpBisb(Opa, Opb, Opc, Opar) << endl;
			}
			if (Op == 23)
			{
				//cout << "PerpBisc(a, b, c, Area);\n"; double Opa, Opb, Opc, Opar;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				//cout << "Area: "; cin >> Opar; cout << "RETORNO: " << PerpBisc(Opa, Opb, Opc, Opar) << endl;
			}
			if (Op == 24) { cout << "LawTan(a, b);\n"; double Opa, Opb; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "RETORNO: " << LawTan(Opa, Opb) << endl; }
			if (Op == 25)
			{
				cout << "LawTanAng(Alpha, Beta);\n"; double Opa, Opb; cout << "Alpha: "; cin >> Opa; cout << "Beta: "; cin >> Opb; cout << "RETORNO: " << LawTanAng(Opa, Opb) << endl;
			}
			if (Op == 26)
			{
				cout << "LawTanb(a, Alpha, Beta);\n"; double Opal, Opa, Opb; cout << "a: "; cin >> Opa; cout << "Alpha: "; cin >> Opal; cout << "Beta: "; cin >> Opb;
				cout << "RETORNO: " << LawTanb(Opa, Opal, Opb) << endl;
			}
			if (Op == 27)
			{
				cout << "LawCota(a, b, c, Alpha);\n"; double Opal, Opa, Opb, Opc; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "Alpha: "; cin >> Opal;	cout << "RETORNO: " << LawCota(Opa, Opb, Opc, Opal) << endl;
			}
			if (Op == 28)
			{
				cout << "LawCotb(a, b, c, Beta);\n"; double Opbt, Opa, Opb, Opc; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "Alpha: "; cin >> Opbt;	cout << "RETORNO: " << LawCotb(Opa, Opb, Opc, Opbt) << endl;
			}
			if (Op == 29)
			{
				cout << "LawCotc(a, b, c, Beta);\n"; double Opgm, Opa, Opb, Opc; cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "Gama: "; cin >> Opgm;	cout << "RETORNO: " << LawCotc(Opa, Opb, Opc, Opgm) << endl;
			}
			if (Op == 30)
			{
				cout << "Mollweidepos(a, b, c);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "RETORNO: " << Mollweidepos(Opa, Opb, Opc) << endl;
			}
			if (Op == 31)
			{
				cout << "Mollweideneg(a, b, c);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "RETORNO: " << Mollweideneg(Opa, Opb, Opc) << endl;
			}
			if (Op == 32)
			{
				cout << "MollweideposAng(Alpha, Beta, Gama);\n"; double Opa, Opb, Opg;	cout << "Alpha: "; cin >> Opa; cout << "Beta: "; cin >> Opb; cout << "Gama: "; cin >> Opg;
				cout << "RETORNO: " << MollweideposAng(Opa, Opb, Opg) << endl;
			}
			if (Op == 33)
			{
				cout << "MollweidenegAng(Alpha, Beta, Gama);\n"; double Opa, Opb, Opg;	cout << "Alpha: "; cin >> Opa; cout << "Beta: "; cin >> Opb; cout << "Gama: "; cin >> Opg;
				cout << "RETORNO: " << MollweidenegAng(Opa, Opb, Opg) << endl;
			}
			if (Op == 34)
			{
				cout << "TriCircumR(a, b, c);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "RETORNO: " << TriCircumR(Opa, Opb, Opc) << endl;
			}
			if (Op == 35)
			{
				cout << "TriInradius(a, b, c);\n"; double Opa, Opb, Opc;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "RETORNO: " << TriInradius(Opa, Opb, Opc) << endl;
			}
			if (Op == 36)
			{
				cout << "AdjTri(a, b, c, d);\n"; double Opa, Opb, Opc, Opd;	cout << "a: "; cin >> Opa; cout << "b: "; cin >> Opb; cout << "c: "; cin >> Opc;
				cout << "d: "; cin >> Opd; cout << "RETORNO: " << AdjTri(Opa, Opb, Opc, Opd) << endl;
			}
			if (Op == 37) { cout << "AngPolygn(Sides);\n"; double s; cout << "Sides: "; cin >> s; cout << "RETORNO: " << AngPolygn(s) << endl; }
			if (Op == 38) { cout << "AngPolygrm(Sides);\n"; double s; cout << "Sides: "; cin >> s; cout << "RETORNO: " << AngPolygrm(s) << endl; }
		}
};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_
