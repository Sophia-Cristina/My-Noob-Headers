#pragma once

#ifndef YSXPOLYGON_H
#define YSXPOLYGON_H

// #####################
// ####### By Sophia Cristina
// ####### Polygon maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

constexpr double ysxPOLYGN_Perim(double Sides, double Size) { return(Sides * Size); }
double ysxPOLYGN_Inradius(double Sides, double Size) { return(Size * 0.5 * cot(PI / Sides)); } // Inradius regular polygon

// ###############################################################################################################################################################################

#endif