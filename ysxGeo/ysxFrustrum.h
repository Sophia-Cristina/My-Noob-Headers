#pragma once

#ifndef YSXFRUSTRUM_H
#define YSXFRUSTRUM_H

// #####################
// ####### By Sophia Cristina
// ####### Cylinder maths which aren't on other headers
// #####################

// #################################################
// REFERENCES:
// #################################################

// VOLUME AND AREA:
double FrustrumSurf(double r1, double r2, double s) { return(PI * (r1 + r2) * s); }
double FrustrumVol(double h, double r1, double r2) { return(((PI * h) / 3) * (r1 * r1 + r1 * r2 + r2 * r2)); }

// ###############################################################################################################################################################################

#endif