#pragma once

#ifndef YSXCONE_H
#define YSXCONE_H

// #####################
// ####### By Sophia Cristina
// ####### Cylinder maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

// VOLUME AND AREA:
double ConeSurf(double lenght, double r) { return(PI * r * (lenght + r)); }
double ConeVol(double r, double h) { return((PI * r * r * h) / 3); }

// ###############################################################################################################################################################################

#endif