#pragma once

#ifndef YSXCONST_H
#define YSXCONST_H

#include "ysxDoc.h"

// #####################################################################################################################################

// #####################
// ####### GENERAL CONSTANTS
// #####################

#define FEI 4.6692016 // Feigenbaum constant
#define GAUSS 0.83462684167 // Gauss Constant https://en.wikipedia.org/wiki/Gauss%27s_constant
#define PHI 1.618033988749894
#define EXP 2.718281828459045
#define TAU 6.283185307179586
#define PI 3.141592653589793
#define HPI 1.570796326794897 // Half PI: 1.5707963267948966192313216916398
#define TTAU 4.71238898038469 // 3 / 4 of a TAU: 4.7123889803846898576939650749193
#define ROOTPI 1.7724538509055160272981674833411 // sqrt(Pi)
#define EULERMASCH 0.577215664901533 // 0.577215664901532'86060651209008240243104215933593992
#define PLASTICNUM 1.324717957244746025960908854
#define PLASTICNUMEQ pow((9 + sqrt(69)) / 18.0, 1.0 / 3) + pow((9 - sqrt(69)) / 18.0, 1.0 / 3) // 1.324717957244746025960908854

// #####################
// ####### TABLES
// #####################

// POWERS OF TWO THAT FITS 2 BYTES:
#define TWOPOWERS { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 }

// POPULAR SAMPLE-RATES TABLE:
// https://en.wikipedia.org/wiki/Sampling_(signal_processing)#Sampling_rate
#define SAMPLERATES { 8000, 11025, 16000, 22050, 32000, 44056, 44100, 47250, 48000, 50000, 50400, 64000, 88200, 96000, 176400, 192000, 352800, 2822400, 5644800, 11289600, 22579200 }

// HIGH COMPOSITE NUMBERS:
// https://oeis.org/A002182
#define HIGHCOMPNUMS { 1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, \
45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160 }

// #####################
// ####### RADICALS
// #####################

#define ROOT2 1.414213562373095 // Square root of 2  | 1.4142135623730950488016887242097
#define ROOT3 1.732050807568877 // Square root of 3  | 1.7320508075688772935274463415059
#define ROOT5 2.236067977499790 // Square root of 5  | 2.2360679774997896964091736687313
#define ROOT6 2.449489742783178 // Square root of 6  | 2.4494897427831780981972840747059
#define ROOT7 2.645751311064590 // Square root of 7  | 2.6457513110645905905016157536393
#define ROOT8 2.828427124746190 // Square root of 8  | 2.8284271247461900976033774484194
#define ROOT10 3.162277660168379 // Square root of 10 | 3.1622776601683793319988935444327

#define CUBE2 1.259921049894873 // Cube root of 2  | 1.2599210498948731647672106072782
#define CUBE3 1.442249570307408 // Cube root of 3  | 1.4422495703074083823216383107801
#define CUBE4 1.587401051968199 // Cube root of 3  | 1.5874010519681994747517056392723
#define CUBE5 1.709975946676697 // Cube root of 5  | 1.7099759466766969893531088725439
#define CUBE6 1.817120592832140 // Cube root of 6  | 1.8171205928321396588912117563273
#define CUBE7 1.912931182772389 // Cube root of 7  | 1.9129311827723891011991168395488
#define CUBE9 2.080083823051904 // Cube root of 9  | 2.0800838230519041145300568243579
#define CUBE10 2.154434690031884 // Cube root of 10 | 2.1544346900318837217592935665194

// #####################
// ####### GEOMETRY
// #####################

// #####################
// TRIANGLES:

#define EQUITRIAREA 0.433012701892219 // 0.43301270189221932338186158537647; MULTIPLY BY 'SIDE^2' | Also equal to 'sqrt(3) / 4'

// #####################
// QUADRILATERAL:

// #####################
// CIRCLES:

#define CIRCLESQRAREA 0.785398163397448 // 0.78539816339744830961566084581988; // Area of a circle inside a square of side 1
#define SQRAREACIRCLE 0.214601836602552 // 0.21460183660255169038433915418012; // Area left if you remove a circle from a square of area 1
#define QUARTERCIRCHALFSQR 0.285398163397448 // 0.28539816339744830961566084581988; // Remove a half square from the area of a quarter circle of radius 1;
#define CROSSEDQUARTERCIRCLE 0.570796326794897 // 0.57079632679489661923132169163975; // The area you get when two quarter circles overlap inside a square of radius 1;

// In a square of side 1, four quarter circles in four directions cross each other, the center figure area is:
// 0.3151467436277204526267681195873;
#define CENTER4QUARTCIRCAREA 0.31514674362772
// Semi-circle with a retangle tangent to it and a circle tangent to the semi circle:
// 5.8284271247461900976033774484194
#define RATIOSEMICIRCTANGRECTTOTANGCIRC 5.828427124746190

// #####################
// ####### PHYSICS
// #####################

// #####################
// WEIGHT:

// #####################
// FRICTION:

std::vector<NameValue> FrictionList()
{
	//std::vector<NameValue> List{ {"a", 1}, {"b", 3} };
	std::vector<NameValue> List;
	// https://en.wikipedia.org/wiki/Friction#Approximate_coefficients_of_friction
	NameValue L;
	L.Name = "Aluminum (Static)"; L.Value = 1.2; List.push_back(L);
	L.Name = "Aluminum (Kinect)"; L.Value = 1.45; List.push_back(L);
	return (List);
}

// #####################
// SPEED / ACCELERATION:

// #####################
// SOUND:
#define SPEEDSOUND 343 // 343m/s is a standard aproximation for speed of sound in normal atmosphere

// #####################
// :
#define AVOGADRO 6022169 // * 10^23 | Number of particles that are contained in one mole, exactly
#define FARADAY 96485.333289 // Cmol^-1 | Magnitude of electric charge per mole of electrons
//#define ELEMCHARGE 16021917
#define ATOMICMASSUNIT 1.6605390666 // * 10^-21 mg | dalton or unified atomic mass unit
#define ELECTRONRESTMASS 9.1093837015 // * 10^-31 kg | Mass of a stationary electron, also known as the invariant mass of the electron. It is one of the fundamental constants of physics
#define PROTONRESTMASS 1.67262192369 // * 10^-27 kg
#define NEUTRONRESTMASS 1.67492749804 // * 10^-27 kg

// https://en.wikipedia.org/wiki/Mass-to-charge_ratio
// Some disciplines use the charge-to-mass ratio (Q/m) instead.
// CODATA recommended value for an electron is: (Q/m) = -1.75882001076(53) * 10^11 C*kg^-1
#define C2MASSRATIOELEC -1.75882001076

// A photon's energy is equal to its frequency multiplied by the Planck constant. Due to mass–energy equivalence, the Planck constant also relates mass to frequency.
// 6.62607015 * 10^-34 (J*s || J*Hz^-1) // Exact value
#define PLANCK 6.62607015

// Sommerfeld's constant, A.K.A.: Fine Structure constant.
// Quantifies the strength of the electromagnetic interaction between elementary charged particles.
// 2018 CODATA recommended value is: (e^2) / (4 * PI * Vacuum_permittivity * (PLANK / TAU) * Speed_Light)
// * V. Permittivity is represented by Epsilon_0
// * 'Plank / Tau' is represented by 'h' with vertical line crossed at the top
#define SOMMERFELD 0.0072973525693

// #####################
// ATMOSPHERE:

#define ATMPRESS 101325 // Atmosphere pressure in Pa
#define GRAVITY 9.80665 // Standard acceleration due to gravity
#define GASDRYAIR 287.058 // Gas constant for dry air: 287.058 J/(kg*K); SI units. https://en.wikipedia.org/wiki/Density_of_air

// #####################
// TEMPERATURE:
#define KELVIN 273.15 // 273.15

// #####################
// ####### ASTRONOMY
// #####################

#define LIGHTSPEED 299792458 // Metres per second
#define EARTHRADIUS 6371 // km
#define LUNARDIST 384402 // km | Lunar distance
#define ASTROUNIT 149597870700 // Astronomical unit, approximately the distance between the Earth and Sun

// #####################
// ####### SIGNALS
// #####################


// #####################
// ####### NUMBERS
// #####################


// #####################
// ####### MISC
// #####################

// TAROT MAJOR CARDS:
#define TAROTMAJORS { "The Fool", "The Magician", "The High Priestess", "The Empress", "The Emperor", "The  Hierophant", "The  Lovers", "The Chariot", "Strength", \
"The Hermit", "Wheel of Fortune", "Justice", "The Hanged Man", "Death", "Temperance", "The Devil", "The Tower", "The Star", "The Moon", "The Sun", "Judgement", "The World" }
// ################################################# FIM ####################################################################################

#endif // SCPARSE_