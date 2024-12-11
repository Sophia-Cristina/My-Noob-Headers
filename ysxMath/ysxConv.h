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
// !!!!!!!
// !!!!!!!	Obs.: Japanese have names for fractions of their measures, so, i won't add those, just divide by '10' (example) or something
// !!!!!!!
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* ;
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################

// #################################################
/* REFERENCES:
GENERAL UNITS:
 [1.1] https://en.wikipedia.org/wiki/Unit_of_volume
ASIA:
 [2.1] https://en.wikipedia.org/wiki/Japanese_units_of_measurement
 [2.2] https://en.wikipedia.org/wiki/Chinese_units_of_measurement
 [2.3]	https://en.wikipedia.org/wiki/Taiwanese_units_of_measurement
 [2.4]	https://en.wikipedia.org/wiki/Korean_units_of_measurement
*/
// #################################################

// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// #################################################
// ####### FUNÇÕES #######
// #################################################
/*TEMPLATE: double something2anything(double Something) { return(); }
Reads as: "Something to Anything";
Ex.: 'kmh2ms()' reads as 'km per hour to meter per seconds'.*/

// #################################################
// ####### LENGTH:
// https://en.wikipedia.org/wiki/Conversion_of_units

// ####### OCIDENT:
constexpr double kmh2ms(double kmh) { return(kmh / 3.6); } // km/h to m/s
constexpr double ms2kmh(double ms) { return(ms * 3.6); } // m/s to km/h
constexpr double foot2m(double foot) { return(foot * 0.3048); } // foot to m
constexpr double m2foot(double m) { return(m / 0.3048); } // m to foot
constexpr double mileh2ms(double mile) { return(mile * 0.44704); } // miles per hour to m/s
constexpr double ms2mileh(double ms) { return(ms / 0.44704); } // miles per hour to m/s
constexpr double mile2km(double mile) { return(mile * 1.609344); } // mile to km
constexpr double km2mile(double km) { return(km / 1.609344); } // km to mile
constexpr double mile2knot(double mile) { return(mile * 0.868976); } // miles to knots
constexpr double knot2mile(double knot) { return(knot / 0.868976); } // knots to miles
constexpr double kmh2knot(double km) { return(km * 1.852); } // km/h to knots
constexpr double knot2kmh(double knot) { return(knot / 1.852); } // knots to km/h
constexpr double mile2fts(double mile) { return(mile * 1.467); } // miles per hour to feet per sec
constexpr double fts2mile(double fts) { return(fts / 1.467); } // feet per sec to mile per hour
constexpr double inch2cm(double inch) { return((inch * 25.4) * 0.1); } // inch to cm
constexpr double cm2inch(double cm) { return((cm * 10) * 0.03937008); } // cm to inch
constexpr double yard2m(double yard) { return(yard * 0.9144); } // yard 2 meters
constexpr double m2yard(double m) { return(m / 0.9144); } // meter 2 yard
constexpr double ms2fts(double ms) { return(ms * 3.28084); } // m/s to feets per sec
constexpr double ms2knot(double ms) { return(ms * 1.9438444924); } // m/s to knot = 1.9438444924406047516198704103672)
constexpr double knot2ms(double knot) { return(knot / 1.9438444924); } // knot to m/s = 1.9438444924406047516198704103672)

// ####### ASIAN:
constexpr double shaku2m(double Shaku) { return(Shaku * (10.0 / 33)); } // Japan -> length derived (but varying) from the Chinese chi, originally based upon the distance measured by a human hand from the tip of the thumb to the tip of the forefinger
constexpr double m2shaku(double m) { return(m / (10.0 / 33)); }
// The Japanese Ken unit is 6 * Shaku or 1 + 9 / 11


// #################################################
// ####### AREA:

// ####### OCIDENT:

// ####### ASIAN:
constexpr double tsubo2sqrm(double Tsubo) { return(Tsubo * (100 / 30.25)); } //  Korea (pyeong) / Japan (Tsubo) -> unit of area and floorspace, equal to a square kan or 36 square Korean feet. The ping and tsubo are its equivalent Taiwanese and Japanese units
constexpr double sqrm2tsubo(double Sqrm) { return(Sqrm / (100 / 30.25)); }


// #################################################
// ####### VOLUME:

// ####### OCIDENT:
constexpr double CubicMeter2Litre(double m3) { return(m3 * 1000); } // 1 m^3 = 1000 Litre
constexpr double Litre2CubicMeter(double L) { return(L / 1000); }
constexpr double Cubiccm2Litre(double cm3) { return(cm3 * 0.001); } // 1 cm^3 = 0.001 Litre
constexpr double Litre2Cubiccm(double L) { return(L / 0.001); }

// ####### USA:
constexpr double CupUS2Litre(double Cups) { return(Cups / (25.0 / 6)); }
constexpr double Litre2CupUS(double L) { return(L * 25.0 / 6); }
constexpr double FluidOnceUS2Litre(double floz) { return(floz * 0.0295735295625); }
constexpr double Litre2FluidOnceUS(double L) { return(L / 0.0295735295625); }
constexpr double ShotGlassUS2Litre(double n) { return(n * 0.04436029434375); }
constexpr double Litre2ShotGlassUS(double L) { return(L / 0.04436029434375); }
constexpr double GallonUS2Litre(double G) { return(G * 3.785411784); }
constexpr double Litre2GallonUS(double L) { return(L / 3.785411784); }
constexpr double BoardFoot2Litre(double BF) { return(BF * 2.359737); }
constexpr double Litre2BoardFoot(double L) { return(L / 2.359737); }
constexpr double Cord2Litre(double Cord) { return(Cord * 3620); }
constexpr double Litre2Cord(double L) { return(L / 3620); }
constexpr double CubicYard2Litre(double yd3) { return(yd3 * 764.5549); }
constexpr double Litre2CubicYard(double L) { return(L / 764.5549); }

// ####### EUROPE:
constexpr double FluidOnceImpr2Litre(double floz) { return(floz * 0.0284130625); }
constexpr double Litre2FluidOnceImpr(double L) { return(L / 0.0284130625); }
constexpr double ImprQuart2Litre(double Quart) { return(Quart * 1.1365225); }
constexpr double Litre2ImprQuart(double L) { return(L / 1.1365225); }
constexpr double GallonImpr2Litre(double G) { return(G * 4.54609); }
constexpr double Litre2GallonImpr(double L) { return(L / 4.54609); }
constexpr double Bushel2Litre(double Bushel) { return(Bushel * 36.36872); }
constexpr double Litre2Bushel(double L) { return(L / 36.36872); }
constexpr double ShotGlassUK2Litre(double n) { return(n * 0.035); }
constexpr double Litre2ShotGlassUK(double L) { return(L / 0.035); }

constexpr double Pint2Litre(double P) { return(P * 0.473176473); }
constexpr double Litre2Pint(double L) { return(L / 0.473176473); }
constexpr double Gill2Litre(double G) { return(G * 0.1420653125); }
constexpr double Litre2Gill(double L) { return(L / 0.1420653125); }
constexpr double Barrels2Litre(double B) { return(B * 158.987294928); }
constexpr double Litre2Barrels(double L) { return(L / 158.987294928); }
constexpr double Hoppus2CubicMeter(double hft) { return(hft * 27.74); }
constexpr double CubicMeter2Hoppus(double m3) { return(m3 / 27.74); }

// ####### ASIAN:
constexpr double sho2l(double Sho) { return(Sho * (2401.0 / 1331)); } // Japan -> a Go is 1 / 10 of Sho, Go is a common japanese unit, so i think this comment might be handy.
constexpr double l2sho(double l) { return(l / (2401.0 / 1331)); }
constexpr double CupJP2Litre(double Cups) { return(Cups * 0.2); }
constexpr double Litre2CupJP(double L) { return(L / 0.2); }

// #################################################
// ####### MASS:

// ####### OCIDENT:
constexpr double lbs2kg(double lbs) { return(lbs * 0.45359237); } // Pounds to kg
constexpr double kg2lbs(double kg) { return(kg / 0.45359237); } // kg to pounds
constexpr double oz2g(double oz) { return(oz * 28.349523125); } // oz to grams
constexpr double g2oz(double g) { return(g / 28.349523125); } // grams to oz
constexpr double g2gr(double g) { return(g / 0.06479891); } // grams to grains
constexpr double gr2g(double g) { return(g * 0.06479891); } // grains to grams

// ####### ASIAN:

constexpr double kan2kg(double Kan) { return(Kan * 3.75); }
constexpr double kg2kan(double Kg) { return(Kg / 3.75); }

// #################################################
// ####### TEMPERATURE:

// ####### OCIDENT:
constexpr double Fahr2Cel(double F) { return((F - 32) * (5.0 / 9)); }
constexpr double Cel2Fahr(double C) { return((C * 9.0 / 5) + 32); }

// ####### ASIAN:

// #################################################
// ####### PRESSURE:

// ####### OCIDENT:
constexpr double atm2pa(double atm) { return(atm * 101325); }
constexpr double pa2atm(double Pa) { return(Pa / 101325); }

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