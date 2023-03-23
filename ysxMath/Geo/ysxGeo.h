#pragma once

#ifndef YSXGEO_H
#define YSXGEO_H

// #####################################################################################################################################

// ####### GLOSSARIO:
// # GEO SPACE:
// 'A, Ar = Area';
// 'P, Pr, Peri = Perimeter';
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

// ATENÇÃO: Mudanças de versões, pode ser que esteja errado algo, mas, funções agora são 'FIGURA + QUALIDADE', por exemplo: 'FIGURA = Triangulo', 'QUALIDADE = Lado', resulta em 'TriSide'*/

// #####################################################################################################################################

// ####### TECHNICALS:
// CONVERSORS:
constexpr double Ang2Rad(double a) { return((a / 360) * TAU); }
constexpr double Rad2Ang(double r) { return((r / TAU) * 360); }

// PI AND ANGLES:
constexpr double PiRatio(double Div) { return (PI / Div); }
constexpr double AngRatio(double Div) { return (360.0 / Div); }

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
double rect(double x) { x /= TAU; x -= floor(x); return (x < 0.5 ? 1 : -1); }
double rect(double x, double PW) { x /= TAU; x -= floor(x); if (PW < 0)	{ PW *= -1;	} if (PW > 0.98) { PW -= floor(PW); } return (x < PW ? 1 : -1); } // Rectangle wave with Pulse Width (0 to 0.98)
double saw(double x) { x /= TAU; x -= floor(x); x = (x * 2) - 1; return (x); }
double phasor(double x) { x /= TAU; x -= floor(x); return (x); }
double tri(double x) { int f = floor(((2 * x) / TAU) + 0.5); x = (4 / TAU) * (x - PI * f) * pow(-1, f); return (x); }

// #####################################################################################################################################
// TOOLS:
#include "ysxAngle.h"
// 2D:
#include "ysxTri.h" // Triangles
#include "ysxCircle.h"
#include "ysxCylinder.h"
#include "ysxQuadri.h" // Quadrilateral
#include "ysxPolygon.h"
// 3D:
#include "ysxCuboid.h"
#include "ysxSphere.h"
#include "ysxCone.h"
#include "ysxFrustrum.h"

// ################################################# FIM ####################################################################################

#endif // SCPARSE_