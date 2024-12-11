#pragma once

#ifndef YSXCIRCLE_H
#define YSXCIRCLE_H

// #####################
// ####### By Sophia Cristina
// ####### Circle maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

// #################################################

// ####### AREA & CIRCUMFERENCE #######
// CIRCUNFERENCE AND AREA:
constexpr double ysxCIRC_Ar(const double r) { return(PI * r * r); } // Area
constexpr double ysxCIRC_Ar(const double r, double Rad) { if (Rad > TAU) { Rad = TAU; } return(Rad * r * r / 2.0); }
constexpr double ysxCIRC_Circumf(const double r) { return(TAU * r); } // Circumference
constexpr double ysxCIRC_CircArSqrAr(const double AreaC) { return(4 * AreaC / PI); } // Square area from circle area

// OVERLAPED SECTOR OF TWO CIRCLES:
double ysxCIRC_OverlapArea(double Distance, const double r)
{
	if (Distance == 0) { return (PI * r * r); }	if (Distance >= 2 * r) { return (0); }
	double HalfAngle = acos(Distance / (2 * r)); double b = ysxTRI_Side(r, Distance * 0.5); double TriArea = b * Distance * 0.5;
	double AreaSeg = HalfAngle * r * r; return ((AreaSeg - TriArea) * 2);
}

// ####### DIAMETER #######

// ####### RADIUS #######
// CIRCULAR SEGMENT ANGLE:
constexpr double ysxCIRC_RadbySeg(const double crd, const double r) { return(r == 0 ? 0 : 2 * asin(crd / 2 * r)); }

// CIRCLE RADIUS BY "...":
double ysxCIRC_Rbycrd(const double crd, const double rad) { double S = sin(rad * 0.5); return(S == 0 ? 0 : crd / (2 * S)); }
double ysxCIRC_RbySeg(const double SegHeight, const double rad) { return(SegHeight / (1 - cos(rad * 0.5))); }
constexpr double ysxCIRC_RbySeg(const double h, const double crd, const double rad) { return(h == 0 ? 0 : (0.125 * (crd * crd + 4 * h * h) / h)); }
double ysxCIRC_RbySecA(const double SecArea, const double rad) { return(rad == 0 ? 0 : sqrt(2 * SecArea / rad)); }
constexpr double ysxCIRC_RbySecP(const double SecPeri, const double rad) { return(SecPeri / (rad + 2)); }
double ysxCIRC_RbyAr(const double Area) { return(sqrt(Area / PI)); }
constexpr double ysxCIRC_RbyPr(const double Peri) { return(Peri / TAU); }

// RADIUS FROM SAGITTA:
constexpr double ysxCIRC_SagittaRad(const double h, const double w) { return(h == 0 ? 0 : w * w / (8 * h) + h * 0.5); }

// ####### ARC #######
// CIRCULAR ARC LENGTH:
constexpr double ysxCIRC_ArcLng(const double r, const double rad) { return(r * rad); }

struct ysxCIRC_Arc { double r, rad, Arc; };

// ####### CHORD #######
// For trig function "crd()", check "ysxGeo.h"!

// Chord lenght:
double ysxCIRC_CrdLenght(const double r, const double rad) { return(2 * r * sin(rad * 0.5)); }
// Chord lenght by Segment height:
double ysxCIRC_CrdLenBySegh(const double r, const double h) { return(2 * sqrt(2 * r * h - h * h)); }

// ####### SECANT #######

// ##################################################################################################

// ####### SEGMENT #######
// CIRCULAR SEGMENT AREA:
double ysxCIRC_SegAr(const double r, const double rad) { return(0.5 * r * r * (rad - sin(rad))); }

// CIRCLE SEGMENT PERIMETER:
constexpr double ysxCIRC_SegPr(const double w, const double r, const double rad) { return(w + r * rad); }

// CIRCLE SEGMENT CHORD:
double ysxCIRC_SegCrd(const double r, const double rad) { return(r * sin(rad * 0.5)); }
double ysxCIRC_SegCrd(const double r, const double h, const double rad) { return(2 * sqrt(h * (2 * r - h))); }

// CIRCLE SEGMENT HEIGHT:
double ysxCIRC_SegHeight(const double r, const double rad) { return(r * (1 - cos(rad * 0.5))); }

// SEG.AREA / CIRCLE.AREA | RATIO:
double ysxCIRC_ArSegAr(const double rad) { return((rad - sin(rad)) / TAU); }

// CIRCLE SEGMENT:
struct ysxCIRC_Seg : public ysxCIRC_Arc
{ double h = 0, w = 0, A_Seg = 0, P_Seg = 0; };

// SEGMENT STRUCT FROM SAGITTA:
ysxCIRC_Seg ysxCIRC_SagittaSeg(const double h, const double w)
{
	ysxCIRC_Seg S;
	S.h = h; S.w = w; S.r = h == 0 ? 0 : w * w / (8 * h) + h * 0.5;
	S.rad = 2 * asin(w / (2 * S.r)); S.Arc = S.rad * S.r;
	S.A_Seg = 0.5 * S.r * S.r * (S.rad - sin(S.rad));
	S.P_Seg = w + S.r * S.rad;
	return(S);
}

// ####### SECTOR #######
// CIRCULAR SECTOR AREA:
constexpr double ysxCIRC_SecAr(const double r, const double rad) { return(r * r * rad * 0.5); }

// CIRCULAR SECTOR:
struct ysxCIRC_Sector : public ysxCIRC_Seg
{ double A_Sec, P_Sec; };

ysxCIRC_Sector GetCircSec(const double rad, const double r)
{
	ysxCIRC_Sector S;
	S.rad = rad; S.r = r;
	S.Arc = r * rad; S.w = 2 * r * sin(0.5 * rad);
	S.A_Sec = 0.5 * r * r * rad; S.P_Sec = r + r + S.Arc;
	return(S);
}

// GET CIRCLE QUADRANT, SEXTANT OR OCTANT:
ysxCIRC_Sector GetCircQuad(const double r)
{
	ysxCIRC_Sector S;
	S.rad = HPI; S.r = r; S.Arc = r * HPI; S.w = 2 * r * sin(0.5 * HPI);
	S.A_Sec = 0.5 * r * r * HPI; S.P_Sec = r + r + S.Arc;
	return(S);
}
ysxCIRC_Sector GetCircSext(const double r)
{
	ysxCIRC_Sector S;
	S.rad = TPI; S.r = r; S.Arc = r * TPI; S.w = 2 * r * sin(0.5 * TPI);
	S.A_Sec = 0.5 * r * r * TPI; S.P_Sec = r + r + S.Arc;
	return(S);
}
ysxCIRC_Sector GetCircOct(const double r)
{
	ysxCIRC_Sector S;
	S.rad = QPI; S.r = r; S.Arc = r * QPI; S.w = 2 * r * sin(0.5 * QPI);
	S.A_Sec = 0.5 * r * r * QPI; S.P_Sec = r + r + S.Arc;
	return(S);
}

// ####### DEFINITIONS #######

// APOLLONIUS OF PERGA:
void ysxCIRC_ApollonusCirc()
{}

/* LOCUS OF CONSTANT SUM:
If the 'sum' of the 'squares' of the 'distances' to the given 'points' is 'constant', then it is a circle.
Vertices 'n' of regular polygon 'P_n';
Sum of the (2m)-th power of distances;
Circumradius 'const R';
This function returns: 'if () { return(S); } else { return(0); }'
Circle and return 'Sum' (center is the centroid of the 'P_n') if 'Sum' is bigger than 'n * R^(2 * m)',
else it returns '0':
*/
double ysxCIRC_LocusofConst(std::vector<Point<int>> Set, const double R, uint32_t m)
{
	double S = 0; uint32_t n = Set.size();
	for (uint32_t i = 1; i < n; ++i) { S += pow(hypot(Set[i].x - Set[i - 1].x, Set[i].y - Set[i - 1].y), 2 * m); }
	if (S > n * pow(R, 2 * m)) { return(S); } else { return(0); }	
}

// #################################################
// ####### CLASS #######
class ysxCIRC_Circle : public ysxCIRC_Sector
{
public:
	double d = 1, A = CIRCSQRAREA, P = TAU;
	ysxCIRC_Circle() { r = 0.5; rad = 0; Arc = 0; A_Sec = 0; A_Seg = 0; P_Sec = 0; P_Seg = 0; }
	ysxCIRC_Circle(const double radius) { r = radius; A = PI * r * r; d = r * 2; P = TAU * r; }
	ysxCIRC_Circle(const double radius, const double radians)
	{
		r = radius; rad = radians;
		A = PI * r * r; d = r * 2; P = TAU * r;	Arc = r * rad;
		A_Seg = 0.5 * r * r * (rad - sin(rad)); h = r * (1 - cos(rad * 0.5));
		w = r * sin(rad * 0.5); P_Seg = w + Arc;
		A_Sec = r * r * rad * 0.5; P_Sec = 2 * r + Arc;
	}
	~ysxCIRC_Circle() {}
};

// ###############################################################################################################################################################################

#endif
