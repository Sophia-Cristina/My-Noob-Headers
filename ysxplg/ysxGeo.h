#pragma once

#ifndef YSXGEO_H
#define YSXGEO_H

#include "ysxConst.h";

// #####################################################################################################################################

// ATENÇÃO: QUASE TODOS OS ANGULOS DEVEM SER COLOCADOS COMO RADIANOS, USAR FUNÇÃO "Ang2Rad" SE NÃO SOUBER!!!!!!!
// VAI ESTAR ESCRITO NOS INPUTS DAS FUNÇÕES, ANGULO / ANG OU RAD.
// SE ESTIVER ESCRITO 'TURN', QUER DIZER QUE UM NUMERO DE '0' À '1' FORMA O PERIMETRO DE UM CIRCULO.

// ATENÇÃO: Lado "a" de um triangulo sempre sera a linha reta horizontal, e o lado "b" sempre sera a linha da esquerda. Veja abaixo.

// ANOTAÇÕES:


// Exemplo de um triangulo no meu header, e outras coisas:
//
// @ = Angulo; # = Area; | = Altura;
//
//       Alpha
//        @					| A 'class' 'Triangulo' funciona fazendo com '{ a, b, Gamma }'; Acredito que todas as funções de triangulo que fiz funciona assim.
//        |##      c		| Como pode ver, 'Gamma' vai ser o angulo mais usado nesse header, por exemplo, a função: LawCos(a, b, Gamma);
//   b    |#### hipotenusa  |
// oposto |######			| Você pode usar a função 'LawSinAngSCT' para pegar angulo com SOHCAHTOA, assim: com '{ b, c }' retorna 'asin(((b / c) * b) / c))'
//        @#######@			| SOH: b / c = sin(Beta) | CAH: a / c = cos(Beta) | TOA = b / a = tang(Beta) |                                    î_ SOH
//    Gamma    a     Beta   | SOH = b / c = 0.469472 = sin(Beta) | Beta = 28°
//         Adjacente		|

//
// Exemplo não-reto:
//
//			  @ Alpha		| Vemos que aqui a ordem mantém independente do triangulo, se quiser um triangulo do outro lado, deve reverter as formulas ou advinhar o valor do lado e / ou angulo.
//           #|#
//       b  ##|##  c
//         ###|###
//  Gamma @###|###@ Beta
//			  a

// #################################################

// ####### GLOSSARIO:
// # GEO SPACE:
// 'Ar = Area';
// 'Peri = Perimeter';
// 'Surf = Surface Area';
// 'Vol = Volume';
// 'Eq & Eql = Equal OR Equilateral OR Something related';
// # FIGURES:
// 'Tri = Triangle';
// 'Rect = Rectangle';
// 'Sqr = Square';
// 'Circ = Circle';
// 'Cicumf & Circum = Circumference';
// 'Cylin = Cylinder';
// 

// ATENÇÃO: Mudanças de versões, pode ser que esteja errado algo, mas, funções agora são 'FIGURA + QUALIDADE', por exemplo: 'FIGURA = Triangulo', 'QUALIDADE = Lado', resulta em 'TriSide'

// #####################################################################################################################################



// #####################################################################################################################################

// #####################################################################################################################################
// ############################
// ####### FUNÇÕES #######
// ############################

// ####### TÉCNICOS:
// CONVERSORES:
double Ang2Rad(double a) { return((a / 360) * TAU); }
double Rad2Ang(double r) { return((r / TAU) * 360); }

// PI E ANGULOS:
double PiRatio(double Div) { return (PI / Div); }
double AngRatio(double Div) { return (360.0 / Div); }

// FUNÇÕES:
double csc(double x) { return(1.0 / sin(x)); }
double sec(double x) { return(1.0 / cos(x)); }
double cot(double x) { return(1.0 / tan(x)); }
double versin(double x) { return(1.0 - cos(x)); }
double exsec(double x) { return((1.0 / cos(x)) - 1.0); }
double excsc(double x) { return(exsec((PI * 0.5) - x)); }
double crd(double x) { return(2.0 * sin(x * 0.5)); }
double cos2(double x) { return(cos(x) * cos(x)); }
double sin2(double x) { return(sin(x) * sin(x)); }
//double rect(double x) { if (sin(x) > 0) { return(1); } else if (sin(x) < 0) { return(-1); } else { return(0); } }
double rect(double x) { x /= TAU; x -= floor(x); return (x < 0.5 ? 1 : -1); }
double rect(double x, double PW) { x /= TAU; x -= floor(x); if (PW < 0)	{ PW *= -1;	} if (PW > 0.98) { PW -= floor(PW); } return (x < PW ? 1 : -1); } // Rectangle wave with Pulse Width (0 to 0.98)
double saw(double x) { x /= TAU; x -= floor(x); x = (x * 2) - 1; return (x); }
double phasor(double x) { x /= TAU; x -= floor(x); return (x); }
double tri(double x) { int f = floor(((2 * x) / TAU) + 0.5); x = (4 / TAU) * (x - PI * f) * pow(-1, f); return (x); }


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### POLIGONOS
// #####################

double Perim(double Sides, double Size) { return(Sides * Size); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### ANGULOS
// #####################

// ####### ANGULOS:
double TriAng(double Alpha, double Beta) { return(180 - (Alpha + Beta)); } // Retorna angulo restante subtraido de dois valores | "Input" e "Output" em "Graus".
double TriAng(double a, double b, double c) { return(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2.0 * b * c))); } // Angulo função de tres medidas | Alpha = bc, Beta = ac, Gama = ab
double AngAct(double Ang) { return(90 - Ang); } // Acute | "Input" e "Output" em "Graus".
double AngObt(double Ang) { return(180 - Ang); } // Obtuse | "Input" e "Output" em "Graus".
double AngWhl(double Ang) { return(360 - Ang); } // Whole | "Input" e "Output" em "Graus".
double SumIntAngPolygn(double Sides) { return(180 * (Sides - 2)); } // Sum of the internal angles of a Polygon
double PolygnAng(double Sides) { return((180 * (Sides - 2)) / Sides); } // Internal angles of a Polygon
double PolygrmAng(double Sides) { return(((360 * (Sides - 2)) / Sides) - 180); } // 180 - (360 - (((180 * (Sides - 2)) / Sides) * 2)) Before Wolfam Alpha
 // Paralel over Transversal:
Point3D<double> ParaTrans(double Ang) { if (Ang > 360) { Ang = 360; } if (Ang > 180) { Ang = 360 - Ang; } Point3D<double> R = {Ang, 180 - Ang, 180 + Ang }; return(R); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### TRIANGULOS
// #####################

// ####### TAMANHOS:
double hipo(double a, double b) { return(sqrt(a * a + b * b)); } // Hipotenusa | Se não me engano tem uam formula nativa do c++ para isso
double RetTri2RetIsoTri(double a, double b) { return(sqrt(((a * a) + (b * b))) / sqrt(2)); } // Make an 'a & b' Triangle to an 'a & a' Triangle
double TriSide(double hip, double Length) { return(sqrt((hip * hip) - (Length * Length))); } // Altura ou Base
double TriHghtsS(double a, double Rad) { return(a * sin(Rad)); } // Comprimento * seno(angulo).
double TriBaseC(double a, double Rad) { return(a * cos(Rad)); } // Comprimento * cos(angulo).
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double TriAlt(double Area, double a) { return((2.0 * Area) / a); } // The altitude from, for example, the side of length a
// Altitude of a right triangle is 'h^2 = pq; h = sqrt(pq)", 'h' is altitude and 'p + q' is the 'hipotenuse' divided by the Altitude line.

// ####### LEIS TRIGONOMETRICAS:
// LAW OF COSINE:
double LawCos(double a, double b, double Rad) { return(sqrt((a * a) + (b * b) - (2 * a * b * cos(Rad)))); } // Retorna tamanho de uma linha usando angulo e dois valores
double LawCosAngle(double a, double b, double c) { return (acos((a * a + b * b - c * c) / (2 * a * b))); } // Retorna valor de angulo usando tres valores de linha

// LAW OF SINE:
double LawSin(double Height, double Rad) { if (sin(Rad) != 0) { return(Height / sin(Rad)); } else { return(0); } } // Altura dividido por seno retorna comprimento
double LawSin0(double Width, double Rad) { if (sin(Rad) != 0) { return(Width / cos(Rad)); } else { return(0); } } // Base dividido por coseno retorna comprimento
// Input and Return in Radians, find an angle by Law of Sine:
double LawSinAngle(double a, double b, double Rad) { double c = LawCos(a, b, Rad); return(asin((sin(Rad) * b) / c)); }
double LawSinAnglebc(double b, double c, double Rad) { return(asin((sin(Rad) * b) / c)); } // When you know c, you just need b and c
double LawSinAngSCT(double b, double c) { return(asin(b / c)); } // Law of Sine, but SOHCAHTOA instead of sine function, returns 'Beta' angle

// LAW OF TANGENT:
// The law of tangents states that: (a - b)/(a + b) = tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta)):
double LawTan(double a, double b) { return((a - b) / (a + b)); }
double LawTanAng(double Alpha, double Beta) { return(tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta))); }
// Wolfram Alpha me deu a solução de b como: a * csc(Alpha) * sin(Beta);
double LawTanb(double a, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); }
//double LawTana(double b, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); } // Não sei solucionar

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
double TriAr(double a, double b) { return(0.5 * a * b); } // Area
double TriAr(double a, double b, double Rad) { return(0.5 * a * b * sin(Rad)); } // Area
double TriArAAS(double b, double Alpha, double Beta) { return((pow(b, 2) * sin(Alpha) * sin(Alpha + Beta)) / 2.0 * sin(Beta)); } // Area
double TriArASA(double a, double Beta, double Gama) { return((pow(a, 2) * sin(Beta) * sin(Gama)) / 2.0 * sin(Beta + Gama)); } // Area
double TriArHeron(double a, double b, double c) { double s = (a + b + c) * 0.5; return(sqrt(s * (s - a) * (s - b) * (s - c))); } // Area

// ####### MÉDIAS:
// https://en.wikipedia.org/wiki/Triangle#Medians,_angle_bisectors,_perpendicular_side_bisectors,_and_altitudes:
double MedianSideRelation(double a, double b, double c) { return((3.0 / 4) * (a * a + b * b + c * c)); }
double TriMedian(double a, double b, double c) { return(0.5 * sqrt((2 * pow(b, 2)) + (2 * pow(c, 2)) - pow(a, 2))); }
double TriSideMedian(double a, double b, double c) { return (sqrt((2 * (b * b) + 2 * (c * c) - (a * a)) / 4.0)); } // Formula to 'Median a', to 'Median b', use this input order "b, c, a" and "c, a, b" to 'Median c'

// ####### BISETORES:
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

// ####### CIRCUMCENTER, INRADIUS, INCENTER E ETC:
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

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### QUADRILATEROS
// #####################

double QuadriArBret(double a, double b, double c, double d, double alpha, double gamma)
{ double s = 0.5 * (a + b + c + d); return (sqrt((s - a) * (s - b) * (s - c) * (s - d) - (a * b * c * d * cos2((alpha + gamma) / 2)))); }

// RECTANGLE OF EQUAL AREA AND PERIMETER:
double EqPeriArRect(double Width) { if (Width <= 2) { Width = 2.000000001; } return((2 * Width) / ( Width - 2)); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #####################
// ####### PRISMAS
// #####################

// ####### CUBOID:
double CuboidVol(double a, double b, double c) { return(a * b * c); }
double CuboidSurf(double a, double b, double c) { return(2 * ((a * b) + (a * c) + (b * c))); }
double CuboidSpcDia(double a, double b, double c) { return(sqrt(a * a + b * b + c * c)); } // Cuboid Space Diagonal sqrt(a^2+b^2+c^2)


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// !!!!!!! LEMBRAR QUE NO MAX TEM VARIAS FORMULAS DE AREA E VOLUME !!!!!!!
// #####################
// ####### CIRCULOS
// #####################

// ####### CIRCUNFERENCIA E AREA:
double CircAr(double r) { return (PI * r * r); } // Area
double CircAr(double r, double Rad) { if (Rad > TAU) { Rad = TAU; } return((Rad * r * r) / 2.0); } //  return((PI * r * r) * (Rad / TAU)); }
double Circumf(double r) { return (TAU * r); } // Circumferencia

// RAIO DO CIRCULO ATRAVEZ DA AREA:
double CircAr2r(double AreaC) { return(sqrt(AreaC / PI)); }

// AREA DO QUADRADO ATRAVEZ DA AREA DO CIRCULO:
double CircArSqrAr(double AreaC) { return(pow((CircAr2r(AreaC) * 2), 2)); }

// AREA DO SETOR SOBREPOSTO DE DOIS CIRCULOS:
double OverlapArea(double Distance, double r)
{
	if (Distance == 0) { return (PI * r * r); }	if (Distance >= 2 * r) { return (0); }
	double HalfAngle = acos(Distance / (2 * r)); double b = TriSide(r, Distance * 0.5); double TriArea = b * Distance * 0.5;
	double AreaSeg = HalfAngle * r * r; return ((AreaSeg - TriArea) * 2);
}

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### ESFERAS
// #####################

// VOLUME E AREA:
double SphereSurf(double r) { return (4 * PI * pow(r, 2)); }
double SphereVol(double r) { return ((4.0 / 3) * PI * pow(r, 3)); }
double SphericalSegV(double h, double r1, double r2) { return(((PI * h) / 6) * (3 * r1 * r1 + 3 * r2 * r2 + h * h)); }
double SphericalSegA(double R, double h) { return(2 * PI * R * h); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### CILINDROS
// #####################

// VOLUME E AREA:
double CylinSurf(double r, double h) { return(PI * r * r * h); }
double CylinVol(double r, double h) { return(PI * r * r * h); }
double CylinLatArea(double r, double h) { return(2 * PI * r * h); }

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################
// #####################
// ####### CONES E FRUSTRUM (TRONCO)
// #####################

// VOLUME E AREA:
double ConeSurf(double lenght, double r) { return(PI * r * (lenght + r)); }
double ConeVol(double r, double h) { return((PI * r * r * h) / 3); }
double FrustrumSurf(double r1, double r2, double s) { return(PI * (r1 + r2) * s); }
double FrustrumVol(double h, double r1, double r2) { return(((PI * h) / 3) * (r1 * r1 + r1 * r2 + r2 * r2)); }

// ####### ####### ####### ####### ####### #######
// ####### ####### ####### ####### ####### #######
// ####### ####### ####### ####### ####### #######
// ####### ####### ####### ####### ####### #######
// ####### ####### ####### ####### ####### #######
// ####### ####### ####### ####### ####### #######
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
	char LnghtType = NoTypeLgt, AngType = NoTypeAng;
	Triangulo(double asize, double bsize, double Angle); //  ####### CONTRUCTOR #######
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
	BisA = TriBisAct(a, b, Gamma);
	BisB = TriBisAct(b, c, Alpha);
	BisC = TriBisAct(c, a, Beta);
	if (Angle > 90)
	{
		BisA = TriBisAct(b, a, Gamma);
		BisB = TriBisAct(c, a, Alpha);
		BisC = TriBisAct(c, b, Beta);
	}

	// Incenter:
	IB = TriIncenter(a, b, Gamma);
	IC = TriIncenter(b, c, Alpha);
	IA = TriIncenter(c, b, Beta);
	Inradius = TriInradius(a, b, c);

	// Medians:
	Mediana = TriSideMedian(a, b, c); Medianb = TriSideMedian(b, a, c); Medianc = TriSideMedian(c, a, b);

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

// ####### ####### ####### ####### ####### #######
// ####### QUADRILATERO:
class Quadrilateral
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
	double Area, Perimeter;
	double Ratios[4]; // Razão baseada no maior valor de um comprimeto de lado

};

// ################################################# FIM ####################################################################################

#endif // SCPARSE_