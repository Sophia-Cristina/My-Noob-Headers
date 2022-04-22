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
double rect(double x) { x /= TAU; x -= floor(x); return (x < 0.5 ? 1 : -1); }
double rect(double x, double PW) { x /= TAU; x -= floor(x); if (PW < 0)	{ PW *= -1;	} if (PW > 0.98) { PW -= floor(PW); } return (x < PW ? 1 : -1); } // Rectangle wave with Pulse Width (0 to 0.98)
double saw(double x) { x /= TAU; x -= floor(x); x = (x * 2) - 1; return (x); }
double phasor(double x) { x /= TAU; x -= floor(x); return (x); }
double tri(double x) { int f = floor(((2 * x) / TAU) + 0.5); x = (4 / TAU) * (x - PI * f) * pow(-1, f); return (x); }

// #####################################################################################################################################
// TOOLS:
#include "ysxGeo/ysxAngle.h"
// 2D:
#include "ysxGeo/ysxTri.h" // Triangles
#include "ysxGeo/ysxCircle.h"
#include "ysxGeo/ysxCylinder.h"
#include "ysxGeo/ysxQuadri.h" // Quadrilateral
#include "ysxGeo/ysxPolygon.h"
// 3D:
#include "ysxGeo/ysxCuboid.h"
#include "ysxGeo/ysxSphere.h"
#include "ysxGeo/ysxCone.h"
#include "ysxGeo/ysxFrustrum.h"

// ################################################# FIM ####################################################################################

#endif // SCPARSE_