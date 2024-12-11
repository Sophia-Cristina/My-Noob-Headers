#pragma once

#ifndef YSXTRADINGGRAPHS_H
#define YSXTRADINGGRAPHS_H

// #####################
// ####### By Sophia Cristina
// ####### Candles, lines, renko and etc.
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################

// ############################
// ####### CHART RELATED
// ############################

struct ysxTRADE_Candle
{
	uint64_t High = 0, Open = 0, Close = 0, Low = 0;
}

ysxTRADE_Candle ysxTRADE_GetCandle(std::string CandleString)
{
	return(CandleString); // W.I.P
}

// ############################
// ####### HISTORY RELATED
// ############################


// ############################

//class ysxTRADE_Wallet
//{
//public:
	
//}

// ###############################################################################################################################################################################
#endif