#pragma once

#ifndef YSXTIME_H
#define YSXTIME_H

// #####################
// ####### By Sophia Cristina
// ####### Time related things, NOT system clock!
// #####################

/*#################################################
REFERENCES:
#################################################*/


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################
// ############## CONVERTERS ##############

double Time2ms(int Min, int Sec) { return((Sec + (Min * 60)) * 1000); }
double Time2ms(int Hr, int Min, int Sec) { return((Sec + ((Min * 60) + (Hr * 3600))) * 1000); }
double ms2Min(double ms) { return(ms / 60000.0); }
double Dec2Sec(double Dec) { return(Dec * 60); }
void CoutSec2Min(double s) { std::cout << floor(s / 60.0) << ":" << 60 * (s / 60.0 - floor(s / 60.0)) << '\n'; }

// #################################################
// ##############  ##############

/*class A
{
public:

// #################################################

	A()
	{
	}

	~A()
	{
	}
};*/

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_