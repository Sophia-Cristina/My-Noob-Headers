#pragma once

#ifndef YSXINDICATORS_H
#define YSXINDICATORS_H

#include <vector>

// #####################
// ####### By Sophia Cristina
// ####### B. Bollinger, LWMA, EMA, RSI and etc...
// #####################

/*#################################################
REFERENCES:
#################################################*/

// ############################
// ####### AVERAGES
// ############################


// Moving Average vector, 'Prices' is the prices being verified, the user choose between 'close', 'open', 'high' or 'low' values,
// the size of the vector must be equal or bigger than the 'Period', or else, vector returned will be empty:
std::vector<double> ysxTRADE_MovingAvrg(const std::vector<double>& Prices, uint32_t Period)
{
    std::vector<double> Return;
    size_t Size = Prices.size();
    size_t D = Size - Period; // 10 = 100 - 90
    if (Size >= Period && Period > 0)
    {
        for (size_t n = 0; n < D; ++n) // 0 to 9
        {
            double Sum = 0;
            for (size_t m = n; m < Period + n; ++m) { Sum += Prices[m]; } // 0 -> 9 to 90 -> 99
            Sum /= (double)Period;
            Return.push_back(Sum);
        }
    }
    return(Return);
}

/* The Formula for the Linearly Weighted Moving Average (LWMA):
https://www.investopedia.com/terms/l/linearlyweightedmovingaverage.asp
Prices vector is a period for each item | Weight go from high to low | Curve is a exponential function to control the height change ('1' is linear):

* Choose a lookback period. This is how many n values will be calculated into the LWMA.
* Calculate the linear weights for each period. This can be accomplished in a couple of ways.
  The easiest is to assign n as the weight for the first value. For example, if using a 100-period lookback,
  then the first value is multiplied by a weight of 100, the next value is multiplied by a weight of 99.
  A more complex way is to choose a different weight for the most recent value, such as 30.
  Now each value will need to drop by 30/100 so that when n-99 (100th period) is reached the weight is one.
* Multiply the prices for each period by their respective weights, then get the sum total.
* Divide the above by the sum of all the weights.
*/
double ysxTRADE_LWMA(const std::vector<double>& Prices, double HighWeight, double LowWeight, double CurvePower)
{
    double Size = Prices.size();
    double Sum = 0, SumW = 0; // Sum the prices and then get the sum of the Weights
    double Weight, D, Div, Curve;

    if (Size > 0)
    {
        if (CurvePower = 0) { CurvePower = 0.000001; } if (CurvePower < 0) { CurvePower *= -1; }
        if (HighWeight < LowWeight) { double T = HighWeight; HighWeight = LowWeight; LowWeight = T; }
        
        Weight;
        D = HighWeight - LowWeight;
        Div = D / Size;
        Curve;

        for (size_t n = 0; n < Size; ++n)
        {
            Curve = pow(((Size - n) / Size), CurvePower);
            Weight = HighWeight - Curve * D;
            Sum += (Prices[n] * Weight);
            SumW += Weight;
        }
    }
    if (SumW == 0) { SumW = 0.000001; }
    return(Sum / SumW);
}


// #################################################


// ############################
// ####### OVER BUY / SELL INDICATORS
// ############################

// Bollinger Bands have three values, so we need a special struct, you can also use 'Point3D' in 'ysxMath':
struct ysxTRADE_BollingerResult
{
    std::vector<double> Middle;
    std::vector<double> Upper;
    std::vector<double> Lower;
};

ysxTRADE_BollingerResult ysxTRADE_BollingerBands(const std::vector<double>& Prices, uint32_t Period, double Mult = 2.67)
{
    ysxTRADE_BollingerResult BB;
    const size_t Size = Prices.size();
    if (Size < Period || Period == 0) { return(BB); }

    BB.Middle = ysxTRADE_MovingAvrg(Prices, Period);
    const size_t Count = BB.Middle.size();

    BB.Upper.reserve(Count);
    BB.Lower.reserve(Count);

    for (size_t i = 0; i < Count; ++i)
    {
        std::vector<double> Window(Prices.begin() + i, Prices.begin() + i + Period);
        double Std = ysxARITH_StdDev(Window);
        double Mid = BB.Middle[i];

        BB.Upper.push_back(Mid + (Mult * Std));
        BB.Lower.push_back(Mid - (Mult * Std));
    }

    return(BB);
}

std::vector<double> ysxTRADE_RSI(const std::vector<double>& Prices, uint32_t Period)
{
    std::vector<double> RSI;
    const size_t Size = Prices.size();
    if (Size <= Period) { return(RSI); }

    double Gain = 0.0, Loss = 0.0;
    for (size_t i = 1; i <= Period; ++i)
    {
        double Change = Prices[i] - Prices[i - 1];
        if (Change > 0.0) { Gain += Change; }
        else { Loss -= Change; } // make positive
    }

    Gain /= (double)Period;
    Loss /= (double)Period;

    RSI.reserve(Size - Period);

    for (size_t i = Period + 1; i < Size; ++i)
    {
        double Change = Prices[i] - Prices[i - 1];
        double GainCur = (Change > 0.0) ? Change : 0.0;
        double LossCur = (Change < 0.0) ? -Change : 0.0;

        Gain = ((Gain * (Period - 1)) + GainCur) / (double)Period;
        Loss = ((Loss * (Period - 1)) + LossCur) / (double)Period;

        double RS = (Loss == 0.0) ? 100.0 : (Gain / Loss);
        double CurRSI = 100.0 - (100.0 / (1.0 + RS));
        RSI.push_back(CurRSI);
    }
    return(RSI);
}

std::vector<double> ysxTRADE_StochRSI(const std::vector<double>& Prices, uint32_t RSI_Period, uint32_t Stoch_Period)
{
    std::vector<double> RSI = ysxTRADE_RSI(Prices, RSI_Period);
    std::vector<double> StochRSI;

    const size_t Size = RSI.size();
    if (Size < Stoch_Period) { return(StochRSI); }

    StochRSI.reserve(Size - Stoch_Period + 1);

    for (size_t i = 0; i <= Size - Stoch_Period; ++i)
    {
        auto Begin = RSI.begin() + i;
        auto End   = Begin + Stoch_Period;
        double MinRSI = *std::min_element(Begin, End);
        double MaxRSI = *std::max_element(Begin, End);
        double CurRSI = RSI[i + Stoch_Period - 1];

        double Norm = (MaxRSI == MinRSI) ? 0.0 : ((CurRSI - MinRSI) / (MaxRSI - MinRSI));
        StochRSI.push_back(Norm);
    }

    return(StochRSI);
}


// ###############################################################################################################################################################################

#endif
