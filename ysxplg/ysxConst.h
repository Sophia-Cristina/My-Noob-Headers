#pragma once

#ifndef YSXCONST_H
#define YSXCONST_H

#include "ysxDoc.h"

// #####################################################################################################################################

// ####### Constants:
const double Fei = 4.6692016; // Feigenbaum constant
const double Guass = 0.83462684167; // Gauss Constant https://en.wikipedia.org/wiki/Gauss%27s_constant
const double Phi = 1.618033988749894;
const double Exp = 2.718281828459045;
const double Tau = 6.283185307179586;
const double Pi = 3.141592653589793;
const double RootPi = 1.7724538509055160272981674833411; // sqrt(Pi)
const double EulerMasch = 0.577215664901533; // 0.577215664901532'86060651209008240243104215933593992

// RADICALS:
const double Root2 = 1.414213562373095; // Square root of 2 | 1.4142135623730950488016887242097
const double Root3 = 1.732050807568877; // Square root of 3 | 1.7320508075688772935274463415059
const double Root5 = 2.236067977499790; // Square root of 5 | 2.2360679774997896964091736687313
const double Root6 = 2.449489742783178; // Square root of 6 | 2.4494897427831780981972840747059
const double Root7 = 2.645751311064590; // Square root of 7 | 2.6457513110645905905016157536393
const double Root8 = 2.828427124746190; // Square root of 8 | 2.8284271247461900976033774484194
const double Root10 = 3.162277660168379; // Square root of 10 | 3.1622776601683793319988935444327

const double Cube2 = 1.259921049894873; // Cube root of 2 | 1.2599210498948731647672106072782
const double Cube3 = 1.442249570307408; // Cube root of 3 | 1.4422495703074083823216383107801
const double Cube4 = 1.587401051968199; // Cube root of 3 | 1.5874010519681994747517056392723
const double Cube5 = 1.709975946676697; // Cube root of 5 | 1.7099759466766969893531088725439
const double Cube6 = 1.817120592832140; // Cube root of 6 | 1.8171205928321396588912117563273
const double Cube7 = 1.912931182772389; // Cube root of 7 | 1.9129311827723891011991168395488
const double Cube9 = 2.080083823051904; // Cube root of 8 | 2.0800838230519041145300568243579
const double Cube10 = 2.154434690031884; // Cube root of 10 | 2.1544346900318837217592935665194


// !!!!!!! *** = Ver se é int ou não, peguei de um livro antigo sem especificações !!!!!!!
// ####### Geometry:

// TRIANGLES:
const double EquiTriArea = 0.433012701892219; // 0.43301270189221932338186158537647; MULTIPLY WITH 'SIDE^2' | Also equal to 'sqrt(3) / 4'


// QUADRILATERAL:


// CIRCLES:
const double CircleSqrArea = 0.785398163397448; // 0.78539816339744830961566084581988; // Circle of r = 0.5 | The area of a circle inside a square of sides 1
const double SqrAreaCircle = 0.214601836602552; // 0.21460183660255169038433915418012; // If you remove a circle of r = 0.5 from a square of area 1, you get this area left
// In a square of side 1, 4 quarter circles in the four directions cross each other, the center figure have this area:
const double Center4QuartCircArea = 0.31514674362772; // 0.3151467436277204526267681195873;
const double QuarterCircHalfSqr = 0.285398163397448; // 0.28539816339744830961566084581988; // Remove a half square from the area of a quarter circle of radius 1;
const double CrossedQuarterCircle = 0.570796326794897; // 0.57079632679489661923132169163975; // The area you get when two quarter circles overlap inside a square of radius 1;
// Semi-circle with a retangle tangent to it and a circle tangent to the semi circle:
const double RatioSemiCircTangRecttoTangCirc = 5.828427124746190; // 5,8284271247461900976033774484194

// ####### Não sei ainda:
const int Avogadro = 6022169; // ***
const int Faraday = 9648670; // ***
const int Planck = 66256196; // ***
const int FineStruct = 7297351; // ***

// ####### Eletricidade:
const int ElemCharge = 16021917; // ***

// ####### Physical constants:
// Massa:
const int AtomicMassUnit = 1660531; // ***
const int ElectronRestMass = 9109558; // ***
const int ProtonRestMass = 1672614; // ***
const int NeutronRestMass = 1674920; // ***
const int Charge2MassRtEle = 1758802; // Charge to Mass Ratio for Electron // ***

// Astro:
const int LightSpeed = 299792458; // 299792458 Metres per second
const int EarthRadius = 6371; // 6371km
const int LunarDist = 384402; // 384402km Lunar distance
const int AstroUnit = 149597870700; // "149597870700" Astronomical unit, approximately the distance between the Earth and Sun

// Atmosfera:
const int AtmPress = 101325; // "101325" is theAtmosphere pressure in Pa
const float Gravity = 9.80665; // "9.80665" is the standard acceleration due to gravity
const float GasCnstDryAir = 287.058; // The specific gas constant for dry air is 287.058 J/(kg·K) in SI units. https://en.wikipedia.org/wiki/Density_of_air

// Temperaturas:
const float Kelvin = 273.15; // 273.15

// Peso:

// Atrito:
vector<NameValue> FrictionList()
{
	//vector<NameValue> List{ {"a", 1}, {"b", 3} };
	vector<NameValue> List;
	// https://en.wikipedia.org/wiki/Friction#Approximate_coefficients_of_friction
	NameValue L; L.Name = "Aluminum (Static)"; L.Value = 1.2; List.push_back(L);
	L.Name = "Aluminum (Kinect)"; L.Value = 1.45; List.push_back(L);
	return (List);
}

// Som:
const int ConstSpeedSnd = 343; // 343m/s is a standard aproximation for speed of sound in normal atmosphere

// Som de computador:
// VETOR COM VARIAS CONSTANTES DE SAMPLERATE:
// https://en.wikipedia.org/wiki/Sampling_(signal_processing)#Sampling_rate
const vector<int> SampleRateList
{ 8000, 11025, 16000, 22050, 32000, 44056, 44100, 47250, 48000, 50000, 50400, 64000, 88200, 96000, 176400, 192000, 352800, 2822400, 5644800, 11289600, 22579200 };

// ####### Numbers:
// High Composite Numbers: https://oeis.org/A002182
const vector<int> HighCompNumList
{ 1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720,
45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160 };

// ####### Misc.:
const vector<string> TarotCards {"The Fool", "The Magician", "The High Priestess", "The Empress", "The Emperor", "The  Hierophant", "The  Lovers", "The Chariot", "Strength",
"The Hermit", "Wheel of Fortune", "Justice", "The Hanged Man", "Death", "Temperance", "The Devil", "The Tower", "The Star", "The Moon", "The Sun", "Judgement", "The World"};
// ################################################# FIM ####################################################################################

#endif // SCPARSE_