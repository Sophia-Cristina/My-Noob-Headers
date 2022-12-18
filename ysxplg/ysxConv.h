#pragma once

#ifndef YSXCONV_H
#define YSXCONV_H

#include "ysxConst.h"

// #####################
// ####### By Sophia Cristina
// ####### Conversors for important math functions.
// ####### I'll try to gather units from all aroung the world
// #####################

// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	https://en.wikipedia.org/wiki/Japanese_units_of_measurement
// !!!!!!!	https://en.wikipedia.org/wiki/Chinese_units_of_measurement
// !!!!!!!	https://en.wikipedia.org/wiki/Taiwanese_units_of_measurement
// !!!!!!!	https://en.wikipedia.org/wiki/Korean_units_of_measurement
// !!!!!!!
// !!!!!!!	Obs.: Japanese have names for fractions of their measures, so, i won't add those, just divide by '10' (example) or something
// !!!!!!!
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* ;
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################

// #####################################################################################################################################
// ####### DECLARAÇÕES:

// #####################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #################################################
// ####### FUNÇÕES #######
// #################################################
// TEMPLATE: double something2anything(double Something) { return(); }

// #################################################
// ####### LENGTH:
// https://en.wikipedia.org/wiki/Conversion_of_units

// ####### OCIDENT:
double kmh2ms(double kmh) { return(kmh / 3.6); } // km/h to m/s
double ms2kmh(double ms) { return(ms * 3.6); } // m/s to km/h
double foot2m(double foot) { return(foot * 0.3048); } // foot to m
double m2foot(double m) { return(m / 0.3048); } // m to foot
double mileh2ms(double mile) { return(mile * 0.44704); } // miles per hour to m/s
double ms2mileh(double ms) { return(ms / 0.44704); } // miles per hour to m/s
double mile2km(double mile) { return(mile * 1.609344); } // mile to km
double km2mile(double km) { return(km / 1.609344); } // km to mile
double mile2knot(double mile) { return(mile * 0.868976); } // miles to knots
double knot2mile(double knot) { return(knot / 0.868976); } // knots to miles
double kmh2knot(double km) { return(km * 1.852); } // km/h to knots
double knot2kmh(double knot) { return(knot / 1.852); } // knots to km/h
double mile2fts(double mile) { return(mile * 1.467); } // miles per hour to feet per sec
double fts2mile(double fts) { return(fts / 1.467); } // feet per sec to mile per hour
double inch2cm(double inch) { return((inch * 25.4) * 0.1); } // inch to cm
double cm2inch(double cm) { return((cm * 10) * 0.03937008); } // cm to inch
double yard2m(double yard) { return(yard * 0.9144); } // yard 2 meters
double m2yard(double m) { return(m / 0.9144); } // meter 2 yard
double ms2fts(double ms) { return(ms * 3.28084); } // m/s to feets per sec
double ms2knot(double ms) { return(ms * 1.9438444924); } // m/2 to knot (orignally 1.9438444924406047516198704103672, but cut to 'double')
double knot2ms(double knot) { return(knot / 1.9438444924); } // m/2 to knot (orignally 1.9438444924406047516198704103672, but cut to 'double')

// ####### ASIAN:
double shaku2m(double Shaku) { return(Shaku * (10.0 / 33)); } // Japan -> length derived (but varying) from the Chinese chi, originally based upon the distance measured by a human hand from the tip of the thumb to the tip of the forefinger
double m2shaku(double m) { return(m / (10.0 / 33)); }
// The Japanese Ken unit is 6 * Shaku or 1 + 9 / 11


// #################################################
// ####### AREA:

// ####### OCIDENT:

// ####### ASIAN:
double tsubo2sqrm(double Tsubo) { return(Tsubo * (100 / 30.25)); } //  Korea (pyeong) / Japan (Tsubo) -> unit of area and floorspace, equal to a square kan or 36 square Korean feet. The ping and tsubo are its equivalent Taiwanese and Japanese units
double sqrm2tsubo(double Sqrm) { return(Sqrm / (100 / 30.25)); }


// #################################################
// ####### VOLUME:

// ####### OCIDENT:

// ####### ASIAN:
double sho2l(double Sho) { return(Sho * (2401.0 / 1331)); } // Japan -> a Go is 1 / 10 of Sho, Go is a common japanese unit, so i think this comment might be handy.
double l2sho(double l) { return(l / (2401.0 / 1331)); }

// #################################################
// ####### MASS:

// ####### OCIDENT:
double lbs2kg(double lbs) { return(lbs * 0.45359237); } // Pounds to kg
double kg2lbs(double kg) { return(kg / 0.45359237); } // kg to pounds
double oz2g(double oz) { return(oz * 28.349523125); } // oz to grams
double g2oz(double g) { return(g / 28.349523125); } // grams to oz
double g2gr(double g) { return(g / 0.06479891); } // grams to grainss
double gr2g(double g) { return(g * 0.06479891); } // grains to grams

// ####### ASIAN:

double kan2kg(double Kan) { return(Kan * 3.75); }
double kg2kan(double Kg) { return(Kg / 3.75); }

// #################################################
// ####### TEMPERATURE:

// ####### OCIDENT:
double Fahr2Cel(double F) { return((F - 32) * (5.0 / 9)); }
double Cel2Fahr(double C) { return((C * 9.0 / 5) + 32); }

// ####### ASIAN:

// #################################################
// ####### PRESSURE:

// ####### OCIDENT:
double atm2pa(double atm) { return(atm * 101325); }
double pa2atm(double Pa) { return(Pa / 101325); }

// ####### ASIAN:

// #################################################
// ####### SOUND:
// !!! IT NULLS IT IF DB < 0 !!!
// Sound Intensity to Decibels for propper sound intesity level
// https://en.wikipedia.org/wiki/Sound_intensity#Sound_intensity_level:
double SndInt2db(double I) { double Result = 10 * log10(I / 1.0e-12); if (Result < 0) { Result = 0; } return(Result); }
double SndInt2db(double I, double I0) { double Result = 10 * log10(I / I0); if (Result < 0) { Result = 0; } return(Result); }
double SndInt2db(double I, double p, double Watts, double m2) { double Result = 10 * log10(I / ((p * Watts) / m2)); if (Result < 0) { Result = 0; } return(Result); }

// #####################################################################################################################################

// ################################################# FIM ####################################################################################

#endif // SCPARSE_