#pragma once

#ifndef YSXSPHERE_H
#define YSXSPHERE_H

// #####################
// ####### By Sophia Cristina
// ####### Sphere maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

// VOLUME AND AREA:
double ysxSPHERE_Surf(double r) { return(4 * PI * pow(r, 2)); }
double ysxSPHERE_Vol(double r) { return((4.0 / 3) * PI * pow(r, 3)); }
constexpr double ysxSPHERE_SphericalSegV(double h, double r1, double r2) { return(((PI * h) / 6) * (3 * r1 * r1 + 3 * r2 * r2 + h * h)); }
constexpr double ysxSPHERE_SphericalSegA(double R, double h) { return(2 * PI * R * h); }

class ysxSPHERE_Sphere
{
public:

};

// ###############################################################################################################################################################################

#endif
