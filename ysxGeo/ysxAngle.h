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
Ang = Degree = 0 to 360;
Rad = Radians = 0 to 2 * PI;
Turn = 0 to 1;*/

// #####################
// ####### ANGLE STUFF:

double RadAct(double Rad) { return(HPI - Rad); } // Acute | In and Out in "Degrees".
double RadObt(double Rad) { return(PI - Rad); } // Obtuse | In and Out in "Degress".
double RadWhl(double Rad) { return(TAU - Rad); } // Whole | In and Out in "Degrees".
double SumIntAngPolygn(double Sides) { return(PI * (Sides - 2)); } // Sum of the internal angles of a Polygon
double PolygnAng(double Sides) { return((PI * (Sides - 2)) / Sides); } // Internal angles of a Polygon
double PolygrmAng(double Sides) { return(((TAU * (Sides - 2)) / Sides) - PI); } // PI - (TAU - (((PI * (Sides - 2)) / Sides) * 2)) Before Wolfam Alpha

// Paralel over Transversal:
Point3D<double> ParaTrans(double Rad) { if (Rad > TAU) { Rad = TAU; } if (Rad > PI) { Rad = TAU - Rad; } Point3D<double> R = { Rad, PI - Rad, PI + Rad }; return(R); }

// #####################
// ####### TRIG. LAWS:

// LAW OF COSINE:
double LawCos(double a, double b, double Rad) { return(sqrt((a * a) + (b * b) - (2 * a * b * cos(Rad)))); } // Retorna tamanho de uma linha usando angulo e dois valores
double LawCosRad(double a, double b, double c) { return (acos((a * a + b * b - c * c) / (2 * a * b))); } // Retorna valor de angulo usando tres valores de linha

// LAW OF SINE:
double LawSinH(double Height, double Rad) { if (sin(Rad) != 0) { return(Height / sin(Rad)); } else { return(0); } } // Height / sin() = Length
double LawSinW(double Width, double Rad) { if (cos(Rad) != 0) { return(Width / cos(Rad)); } else { return(0); } } // Width / cos() = Length
// Input and Return in Radians, find an angle by Law of Sine:
double LawSinRad(double a, double b, double Rad) { double c = LawCos(a, b, Rad); return(asin((sin(Rad) * b) / c)); }
double LawSinRadbc(double b, double c, double Rad) { return(asin((sin(Rad) * b) / c)); }
double LawSinRadSOH(double b, double c) { return(asin(b / c)); } // Law of Sine, but SOHCAHTOA instead of sine function, returns 'Beta' angle

// LAW OF TANGENT:
// The law of tangents states that: (a - b)/(a + b) = tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta)):
double LawTan(double a, double b) { return((a - b) / (a + b)); }
double LawTanRad(double Alpha, double Beta) { return(tan(0.5 * (Alpha - Beta)) / tan(0.5 * (Alpha + Beta))); }
// Wolfram A. gave me this 'b' solution: a * csc(Alpha) * sin(Beta);
double LawTanb(double a, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); }
//double LawTana(double b, double Alpha, double Beta) { return(a * csc(Alpha) * sin(Beta)); } // Não sei solucionar

// LAW OF COTANGENT:
double LawCota(double a, double b, double c, double Alpha) { return(cot(Alpha) / (((a + b + c) * 0.5) - a)); }
double LawCotb(double a, double b, double c, double Beta) { return(cot(Beta) / (((a + b + c) * 0.5) - b)); }
double LawCotc(double a, double b, double c, double Gama) { return(cot(Gama) / (((a + b + c) * 0.5) - c)); }
double Mollweidepos(double a, double b, double c) { return((a + b) / c); } // Based on Law of Cotangent = cos((Alpha - Beta) * 0.5) / sin(Gama * 0.5)
double Mollweideneg(double a, double b, double c) { return((a - b) / c); } // Based on Law of Cotangent = sin((Alpha - Beta) * 0.5) / cos(Gama * 0.5)
double MollweideposRad(double Alpha, double Beta, double Gama) { return(cos((Alpha - Beta) * 0.5) / sin(Gama * 0.5)); } // Based on Law of Cotangent = (a + b) / c
double MollweidenegRad(double Alpha, double Beta, double Gama) { return(sin((Alpha - Beta) * 0.5) / cos(Gama * 0.5)); } // Based on Law of Cotangent = (a - b) / c

// ###################################################################################################################################################



#endif // SCPARSE_