#pragma once

#ifndef YSXCYLINDER_H
#define YSXCYLINDER_H

// #####################
// ####### By Sophia Cristina
// ####### Cylinder maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

// VOLUME AND AREA:
double ysxCYLIN_Surf(double r, double h) { return(TAU * r * h); }
double ysxCYLIN_Vol(double r, double h) { return(PI * r * r * h); }

// ###############################################################################################################################################################################

#endif