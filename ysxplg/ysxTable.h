#pragma once

#ifndef YSXTABLE_H
#define YSXTABLE_H

#include "ysxDoc.h"

// #####################################################################################################################################

// POWERS OF TWO THAT FITS 2 BYTES:
#define TWOPOWERS16B { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 }

// POPULAR SAMPLE-RATES TABLE:
// https://en.wikipedia.org/wiki/Sampling_(signal_processing)#Sampling_rate
#define SAMPLERATES { 8000, 11025, 16000, 22050, 32000, 44056, 44100, 47250, 48000, 50000, 50400, 64000, 88200, 96000, 176400, 192000, 352800, 2822400, 5644800, 11289600, 22579200 }

// HIGH COMPOSITE NUMBERS:
// https://oeis.org/A002182
#define HIGHCOMPNUMS { 1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, \
45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160 }

// FRICTION:
// https://en.wikipedia.org/wiki/Friction#Approximate_coefficients_of_friction
std::vector<NameValue<double>> FrictionList()
{
	std::vector<NameValue<double>> List = { { "Aluminum (Static)", 1.2 }, { "Aluminum (Kinect)", 1.45 } };
	return(List);
}

// ####### MISC #######

// TAROT MAJOR CARDS:
#define TAROTMAJORS { "The Fool", "The Magician", "The High Priestess", "The Empress", "The Emperor", "The  Hierophant", "The  Lovers", "The Chariot", "Strength", \
"The Hermit", "Wheel of Fortune", "Justice", "The Hanged Man", "Death", "Temperance", "The Devil", "The Tower", "The Star", "The Moon", "The Sun", "Judgement", "The World" }

// ################################################# FIM ####################################################################################

#endif