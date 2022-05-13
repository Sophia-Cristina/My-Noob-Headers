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
double CircAr(double r) { return(PI * r * r); } // Area
double CircAr(double r, double Rad) { if (Rad > TAU) { Rad = TAU; } return(Rad * r * r / 2.0); }
double Circumf(double r) { return(TAU * r); } // Circumference
double CircArSqrAr(double AreaC) { return(4 * AreaC / PI); } // Square area from circle area

// OVERLAPED SECTOR OF TWO CIRCLES:
double OverlapArea(double Distance, double r)
{
	if (Distance == 0) { return (PI * r * r); }	if (Distance >= 2 * r) { return (0); }
	double HalfAngle = acos(Distance / (2 * r)); double b = TriSide(r, Distance * 0.5); double TriArea = b * Distance * 0.5;
	double AreaSeg = HalfAngle * r * r; return ((AreaSeg - TriArea) * 2);
}

// ####### DIAMETER #######

// ####### RADIUS #######
// CIRCULAR SEGMENT ANGLE:
double CircRadbySeg(double crd, double r) { return(2 * asin(crd / 2 * r)); }

// CIRCLE RADIUS BY "...":
double CircRbycrd(double crd, double rad) { return(crd / (2 * sin(rad * 0.5))); }
double CircRbySeg(double SegHeight, double rad) { return(SegHeight / (1 - cos(rad * 0.5))); }
double CircRbySeg(double h, double crd, double rad) { return((0.125 * (crd * crd + 4 * h * h) / h)); }
double CircRbySecA(double SecArea, double rad) { return(sqrt(2 * SecArea / rad)); }
double CircRbySecP(double SecPeri, double rad) { return(SecPeri / (rad + 2)); }
double CircRbyAr(double Area) { return(sqrt(Area / PI)); }
double CircRbyPr(double Peri) { return(Peri / TAU); }

// RADIUS FROM SAGITTA:
double SagittaRad(double h, double w) { return(w * w / (8 * h) + h * 0.5); }

// ####### ARC #######
// CIRCULAR ARC LENGTH:
double CircArcLng(double r, double rad) { return(r * rad); }

struct CircArc { double r, rad, Arc; };

// ####### CHORD #######
// Check lenght in 'ysxGeo.h'.

// ####### SECANT #######

// ##################################################################################################

// ####### SEGMENT #######
// CIRCULAR SEGMENT AREA:
double CircSegAr(double r, double rad) { return(0.5 * r * r * (rad - sin(rad))); }

// CIRCLE SEGMENT PERIMETER:
double CircSegPr(double w, double r, double rad) { return(w + r * rad); }

// CIRCLE SEGMENT CHORD:
double CircSegCrd(double r, double rad) { return(r * sin(rad * 0.5)); }
double CircSegCrd(double r, double h, double rad) { return(2 * sqrt(h * (2 * r - h))); }

// CIRCLE SEGMENT HEIGHT:
double CircSegHeight(double r, double rad) { return(r * (1 - cos(rad * 0.5))); }

// SEG.AREA / CIRCLE.AREA | RATIO:
double CircArSegAr(double rad) { return((rad - sin(rad)) / TAU); }

// CIRCLE SEGMENT:
struct CircSeg : public CircArc
{ double h = 0, w = 0, A_Seg = 0, P_Seg = 0; };

// SEGMENT STRUCT FROM SAGITTA:
CircSeg SagittaSeg(double h, double w)
{
	CircSeg S;
	S.h = h; S.w = w; S.r = w * w / (8 * h) + h * 0.5;
	S.rad = 2 * asin(w / (2 * S.r)); S.Arc = S.rad * S.r;
	S.A_Seg = 0.5 * S.r * S.r * (S.rad - sin(S.rad));
	S.P_Seg = w + S.r * S.rad;
	return(S);
}

// ####### SECTOR #######
// CIRCULAR SECTOR AREA:
double CircSecAr(double r, double rad) { return(r * r * rad * 0.5); }

// CIRCULAR SECTOR:
struct CircSector : public CircSeg
{ double A_Sec, P_Sec; };

CircSector GetCircSec(double rad, double r)
{
	CircSector S;
	S.rad = rad; S.r = r;
	S.Arc = r * rad; S.w = 2 * r * sin(0.5 * rad);
	S.A_Sec = 0.5 * r * r * rad; S.P_Sec = r + r + S.Arc;
	return(S);
}

// GET CIRCLE QUADRANT, SEXTANT OR OCTANT:
CircSector GetCircQuad(double r)
{
	CircSector S;
	S.rad = HPI; S.r = r; S.Arc = r * HPI; S.w = 2 * r * sin(0.5 * HPI);
	S.A_Sec = 0.5 * r * r * HPI; S.P_Sec = r + r + S.Arc;
	return(S);
}
CircSector GetCircSext(double r)
{
	CircSector S;
	S.rad = TPI; S.r = r; S.Arc = r * TPI; S.w = 2 * r * sin(0.5 * TPI);
	S.A_Sec = 0.5 * r * r * TPI; S.P_Sec = r + r + S.Arc;
	return(S);
}
CircSector GetCircOct(double r)
{
	CircSector S;
	S.rad = QPI; S.r = r; S.Arc = r * QPI; S.w = 2 * r * sin(0.5 * QPI);
	S.A_Sec = 0.5 * r * r * QPI; S.P_Sec = r + r + S.Arc;
	return(S);
}

// ####### DEFINITIONS #######

// APOLLONIUS OF PERGA:
void ApollonusCirc()
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
double CircLocusofConst(std::vector<Point<int>> Set, double R, uint32_t m)
{
	double S = 0; uint32_t n = Set.size();
	for (uint32_t i = 1; i < n; ++i) { S += pow(hypot(Set[i].x - Set[i - 1].x, Set[i].y - Set[i - 1].y), 2 * m); }
	if (S > n * pow(R, 2 * m)) { return(S); } else { return(0); }	
}

// #################################################
// ####### CLASS #######
class Circle : public CircSector
{
public:
	double d = 1, A = 0.785398163397448, P = TAU;
	Circle() { r = 0.5; rad = 0; Arc = 0; A_Sec = 0; A_Seg = 0; P_Sec = 0; P_Seg = 0; }
	Circle(double radius) { r = radius; A = PI * r * r; d = r * 2; P = TAU * r; }
	Circle(double radius, double radians)
	{
		r = radius; rad = radians;
		A = PI * r * r; d = r * 2; P = TAU * r;	Arc = r * rad;
		A_Seg = 0.5 * r * r * (rad - sin(rad)); h = r * (1 - cos(rad * 0.5));
		w = r * sin(rad * 0.5); P_Seg = w + Arc;
		A_Sec = r * r * rad * 0.5; P_Sec = 2 * r + Arc;
	}
	~Circle() {}
};

// ###############################################################################################################################################################################

#endif