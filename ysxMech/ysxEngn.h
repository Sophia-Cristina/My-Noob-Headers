#pragma once

#ifndef YSXENGN_H
#define YSXENGN_H

// #####################
// ####### By Sophia Cristina
// #######
// ####### For whatever kind of engineering but electrical engineering.
// #####################

// #################################################
// REFERENCES:
// [1] HYDRAULIC DESIGN OF HIGHWAY CULVERTS
// #################################################


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################
// ############## HYDRAULICS ##############

// ####### HIGHWAY CULVERTS:

/* HEADLOSS GRATE CURVERT:
Types:
0: 2.42 Sharp-edged rectangular bars;
1: 1.83 Rectangular with semi-circular upstream face;
2: 1.79 Circular bars;
3: 1.67 Rectangular bars with semi-circular upstream and downstream face
W: Max cross-sect width of the bars facing the flow, 'ft' or 'm';
X: Min clear spacing between bars, 'ft' or 'm';
Vu: Approach velocity, 'ft/s' or 'm/s';
g: Accel. gravity;
Rad: Angle of the grate with respect to the horizontal;*/
double ysxENGN_HeadlossGrateCulvert(uint8_t Type, double W, double X, double Rad, double Vu, double g)
{
 double K = 2.42;
 if (Type == 1) { K = 1.83; } else if (Type == 2) { K = 1.79; }
 else if (Type == 3) { K = 1.67; }
 return(K * (W / X) * ((Vu * Vu) / (2 * g)) * sin(Rad));
}

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_