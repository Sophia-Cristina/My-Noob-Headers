#pragma once

#ifndef YSXANGLE_H
#define YSXANGLE_H

// #####################
// ####### By Sophia Cristina
// ####### Angle maths
// #####################

// #################################################
// REFERENCES:
// #################################################

/* ROTATIONS:
Ang = Angle = radians are used by standard inside processes and as return value;
Degree = 0 to 360;
Rad = Radians = 0 to 2 * PI;
Turn = 0 to 1;*/

// #####################
// ####### ANGLE STUFF:

constexpr double ysxGEO_RadAct(double Rad) { return(HPI - Rad); } // Acute
constexpr double ysxGEO_RadObt(double Rad) { return(PI - Rad); } // Obtuse
constexpr double ysxGEO_RadWhl(double Rad) { return(TAU - Rad); } // Whole
constexpr double ysxGEO_SumIntAngPolygn(double Sides) { return(PI * (Sides - 2)); } // Sum of the internal angles of a Polygon
constexpr double ysxGEO_PolygnAng(double Sides) { return(Sides == 0 ? 0 : (PI * (Sides - 2)) / Sides); } // Internal angles of a Polygon
constexpr double ysxGEO_PolygrmAng(double Sides) { return(Sides == 0 ? 0 : ((TAU * (Sides - 2)) / Sides) - PI); } // PI - (TAU - (((PI * (Sides - 2)) / Sides) * 2)) Before Wolfam Alpha

// Paralel over Transversal:
Point3D<double> ysxGEO_ParaTrans(double Rad) { if (Rad > TAU) { Rad = TAU; } if (Rad > PI) { Rad = TAU - Rad; } Point3D<double> R = { Rad, PI - Rad, PI + Rad }; return(R); }

// #####################
// ####### TRIG. LAWS:

// LAW OF COSINE:
double ysxGEO_LawCos(double a, double b, double Rad) { return(sqrt(a * a + b * b - 2 * a * b * cos(Rad))); } // Retorna tamanho de uma linha usando angulo e dois valores
 // Return angle. DON'T USE 'a = 0' or 'b = 0'!
double ysxGEO_LawCosRad(double a, double b, double c) { return (acos((a * a + b * b - c * c) / (2 * a * b))); }

// LAW OF SINE:
double ysxGEO_LawSinH(double Height, double Rad) { if (sin(Rad) != 0) { return(Height / sin(Rad)); } else { return(0); } } // Height / sin() = Length
double ysxGEO_LawSinW(double Width, double Rad) { if (cos(Rad) != 0) { return(Width / cos(Rad)); } else { return(0); } } // Width / cos() = Length
// Input and Return in Radians, find an angle by Law of Sine:
double ysxGEO_LawSinRad(double a, double b, double Rad) { double c = ysxGEO_LawCos(a, b, Rad); return(c == 0 ? 0 : asin((sin(Rad) * b) / c)); }
double ysxGEO_LawSinRadbc(double b, double c, double Rad) { return(c == 0 ? 0 : asin((sin(Rad) * b) / c)); }
double ysxGEO_LawSinRadSOH(double b, double c) { return(asin(b / c)); } // Law of Sine, but SOHCAHTOA instead of sine function, returns 'Beta' angle

// LAW OF TANGENT:
// Care with div by 0! The law of tangents states that: (a - b)/(a + b) = tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta)):
constexpr double ysxGEO_LawTan(double a, double b) { return((a - b) / (a + b)); }
double ysxGEO_LawTanRad(double Alpha, double Beta) { return(tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta))); }
// Wolfram A. gave me this 'b' solution: a * csc(Alpha) * sin(Beta);
double ysxGEO_LawTanb(double a, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); }
//double LawTana(double b, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); } // Não sei solucionar

// LAW OF COTANGENT (CARE WITH DIV BY 0):
double ysxGEO_LawCota(double a, double b, double c, double Alpha) { return(cot(Alpha) / (((a + b + c) * 0.5) - a)); }
double ysxGEO_LawCotb(double a, double b, double c, double Beta) { return(cot(Beta) / (((a + b + c) * 0.5) - b)); }
double ysxGEO_LawCotc(double a, double b, double c, double Gama) { return(cot(Gama) / (((a + b + c) * 0.5) - c)); }
constexpr double ysxGEO_Mollweidepos(double a, double b, double c) { return((a + b) / c); } // Based on Law of Cotangent = cos((Alpha - Beta) * 0.5) / sin(Gama * 0.5)
constexpr double ysxGEO_Mollweideneg(double a, double b, double c) { return((a - b) / c); } // Based on Law of Cotangent = sin((Alpha - Beta) * 0.5) / cos(Gama * 0.5)
 // Based on Law of Cotangent = (a + b) / c
double ysxGEO_MollweideposRad(double Alpha, double Beta, double Gama) { double S = sin(Gama * 0.5);  return(S == 0 ? 0 : cos((Alpha - Beta) * 0.5) / S); }
// Based on Law of Cotangent = (a - b) / c
double ysxGEO_MollweidenegRad(double Alpha, double Beta, double Gama) { double C = cos(Gama * 0.5);  return(C == 0 ? 0 : sin((Alpha - Beta) * 0.5) / C); }

// ###################################################################################################################################################

#endif // SCPARSE_
