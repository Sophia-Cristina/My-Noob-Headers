#pragma once

#ifndef YSXINDICATORS_H
#define YSXINDICATORS_H

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
double ysxTRADE_LWMA(std::vector<double> Prices, double HighWeight, double LowWeight, double CurvePower)
{
    double Size = Prices.size();
    double Sum = 0, SumW = 0; // Sum the prices and then get the sum of the Weights
    double Weight;
    double D;
    double Div;
    double Curve;

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

// ###############################################################################################################################################################################

#endif
