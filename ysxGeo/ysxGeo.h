#pragma once

#ifndef YSXGEO_H
#define YSXGEO_H

// #####################################################################################################################################

// ATENÇÃO: QUASE TODOS OS ANGLES DEVEM SER COLOCADOS COMO RADIANOS, USAR FUNÇÃO "Ang2Rad" SE NÃO SOUBER!!!!!!!
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

// ATENÇÃO: Mudanças de versões, pode ser que esteja errado algo, mas, funções agora são 'FIGURA + QUALIDADE', por exemplo: 'FIGURA = Triangulo', 'QUALIDADE = Lado', resulta em 'TriSide'

// #####################################################################################################################################

// ####### TECHNICALS:
// CONVERSORS:
double Ang2Rad(double a) { return((a / 360) * TAU); }
double Rad2Ang(double r) { return((r / TAU) * 360); }

// PI AND ANGLES:
double PiRatio(double Div) { return (PI / Div); }
double AngRatio(double Div) { return (360.0 / Div); }

// TRIG.:
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
// ####### ANGLES:

double AngAct(double Ang) { return(90 - Ang); } // Acute | "Input" e "Output" em "Graus".
double AngObt(double Ang) { return(180 - Ang); } // Obtuse | "Input" e "Output" em "Graus".
double AngWhl(double Ang) { return(360 - Ang); } // Whole | "Input" e "Output" em "Graus".
double SumIntAngPolygn(double Sides) { return(180 * (Sides - 2)); } // Sum of the internal angles of a Polygon
double PolygnAng(double Sides) { return((180 * (Sides - 2)) / Sides); } // Internal angles of a Polygon
double PolygrmAng(double Sides) { return(((360 * (Sides - 2)) / Sides) - 180); } // 180 - (360 - (((180 * (Sides - 2)) / Sides) * 2)) Before Wolfam Alpha
 // Paralel over Transversal:
Point3D<double> ParaTrans(double Ang) { if (Ang > 360) { Ang = 360; } if (Ang > 180) { Ang = 360 - Ang; } Point3D<double> R = {Ang, 180 - Ang, 180 + Ang }; return(R); }

// #####################################################################################################################################
// ####### TRIG. LAWS:

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

// #####################################################################################################################################

#include "ysxTri.h"

// #####################################################################################################################################
// ####### POLIGONS:

double Perim(double Sides, double Size) { return(Sides * Size); }

// #####################################################################################################################################
// ####### QUADRILATERALS:

double QuadriArBret(double a, double b, double c, double d, double alpha, double gamma)
{ double s = 0.5 * (a + b + c + d); return (sqrt((s - a) * (s - b) * (s - c) * (s - d) - (a * b * c * d * cos2((alpha + gamma) / 2)))); }

// RECTANGLE OF EQUAL AREA AND PERIMETER:
double EqPeriArRect(double Width) { if (Width <= 2) { Width = 2.000000001; } return((2 * Width) / ( Width - 2)); }

// #####################################################################################################################################
// ####### PRISMS:

// ####### CUBOID:
double CuboidVol(double a, double b, double c) { return(a * b * c); }
double CuboidSurf(double a, double b, double c) { return(2 * ((a * b) + (a * c) + (b * c))); }
double CuboidSpcDia(double a, double b, double c) { return(sqrt(a * a + b * b + c * c)); } // Cuboid Space Diagonal sqrt(a^2+b^2+c^2)


// #####################################################################################################################################
// ####### CIRCLES:

// CIRCUNFERENCE AND AREA:
double CircAr(double r) { return (PI * r * r); } // Area
double CircAr(double r, double Rad) { if (Rad > TAU) { Rad = TAU; } return((Rad * r * r) / 2.0); } //  return((PI * r * r) * (Rad / TAU)); }
double Circumf(double r) { return (TAU * r); } // Circumference

// CIRCLE RAY FROM AREA:
double CircAr2r(double AreaC) { return(sqrt(AreaC / PI)); }

// SQUARE ARE FROM CIRCLE AREA:
double CircArSqrAr(double AreaC) { return(pow((CircAr2r(AreaC) * 2), 2)); }

// OVERLAPED SECTOR OF TWO CIRCLES:
double OverlapArea(double Distance, double r)
{
	if (Distance == 0) { return (PI * r * r); }	if (Distance >= 2 * r) { return (0); }
	double HalfAngle = acos(Distance / (2 * r)); double b = TriSide(r, Distance * 0.5); double TriArea = b * Distance * 0.5;
	double AreaSeg = HalfAngle * r * r; return ((AreaSeg - TriArea) * 2);
}

// #####################################################################################################################################
// ####### SPHRES:

// VOLUME AND AREA:
double SphereSurf(double r) { return (4 * PI * pow(r, 2)); }
double SphereVol(double r) { return ((4.0 / 3) * PI * pow(r, 3)); }
double SphericalSegV(double h, double r1, double r2) { return(((PI * h) / 6) * (3 * r1 * r1 + 3 * r2 * r2 + h * h)); }
double SphericalSegA(double R, double h) { return(2 * PI * R * h); }

// #####################################################################################################################################
// ####### CILINDROS:

// VOLUME AND AREA:
double CylinSurf(double r, double h) { return(PI * r * r * h); }
double CylinVol(double r, double h) { return(PI * r * r * h); }
double CylinLatArea(double r, double h) { return(2 * PI * r * h); }

// #####################################################################################################################################
// ####### CONES AND FRUSTRUM (TRONCO):

// VOLUME AND AREA:
double ConeSurf(double lenght, double r) { return(PI * r * (lenght + r)); }
double ConeVol(double r, double h) { return((PI * r * r * h) / 3); }
double FrustrumSurf(double r1, double r2, double s) { return(PI * (r1 + r2) * s); }
double FrustrumVol(double h, double r1, double r2) { return(((PI * h) / 3) * (r1 * r1 + r1 * r2 + r2 * r2)); }

// #####################################################################################################################################
// ####### CLASSES #######

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