#pragma once

#ifndef YSXTEXT_H
#define YSXTEXT_H

// #####################
// ####### By Sophia Cristina
// ####### Header made to handle text files, not binary
// ####### NOT WORKING YET, I MADE IT RECENTLY
// ####### FUNCTIONS HERE ARE NOW ON ysxMoney.h
// #####################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

class TradeData
{
public:
    std::string Coin1, Coin2;
    double Paid, Received;
};

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################


// ############################
// ####### TÉCNICOS
// ############################

// Load the data to the 'TradeData' vector:
std::vector<TradeData> LoadTradeData(std::string Path)
{
    std::vector<TradeData> Datas;
    bool SC[] = { false, false, false, false }; // 'SC' stands for 'Semi-Colon', what separates the data
    std::string In;
    TradeData Data;
    std::ifstream D = std::ifstream(Path);
    int beg = D.tellg(); D.seekg(0, ios::end); int end = D.tellg(); D.seekg(0, ios::beg);
    if (D.is_open())
    {
        while (!D.eof())
        {
            char c = '!';
            double Value;
            while (c != ';' && !D.eof())
            {
                if (!SC[0]) { D.read(&c, 1); if (c != ' ' && c != ';') { In.push_back(c); } }
                else if (!SC[1]) { D >> Data.Paid; D.read(&c, 1); }
                else if (!SC[2]) { D.read(&c, 1); if (c != ' ' && c != ';') { In.push_back(c); } }
                else if (!SC[3]) { D >> Data.Received; D.read(&c, 1); }
            }
            if (!SC[0]) { SC[0] = true; Data.Coin1 = In; In = std::string(); }
            else if (!SC[1]) { SC[1] = true; }
            else if (!SC[2]) { SC[2] = true; Data.Coin2 = In; In = std::string(); }
            else if (!SC[3]) { SC[0] = false; SC[1] = false; SC[2] = false; }
            Datas.push_back(Data);
        }
    }
    D.close();
    return(Datas);
}

// Get a text with some calculated results from trades:
std::string GetCalcText(std::vector<TradeData> Datas)
{
    std::string S = "";
    std::vector<NameValue> Coins = { {Datas[0].Coin1, -Datas[0].Paid}, {Datas[0].Coin2, Datas[0].Received} };
    int Size = Datas.size();
    if (Size > 0)
    {
        double TotalPaid = 0;
        for (int n = 0; n < Datas.size(); ++n)
        {
            S += "Paid: ";
            S += std::to_string(Datas[n].Paid);
            S += Datas[n].Coin1;
            S += " and received ";
            S += std::to_string(Datas[n].Received) + "\n";
            S += Datas[n].Coin2;
            for (int m = 0; m < Coins.size(); ++m)
            {
                if (Datas[n].Coin1.compare(Coins[m].Name) != 0)
                {
                    Coins.push_back({ Datas[n].Coin1, -Datas[n].Paid });
                }
                else
                {
                    Coins[m].Value -= Datas[n].Paid;
                }
                if (Datas[n].Coin2.compare(Coins[m].Name) != 0)
                {
                    Coins.push_back({ Datas[n].Coin2, Datas[n].Received });
                }
                else
                {
                    Coins[m].Value += Datas[n].Received;
                }
            }            
        }

        
        for (int m = 0; m < Coins.size(); ++m)
        {
            S += "TOTAL '" + Coins[m].Name + "s': " + std::to_string(Coins[m].Value) + "\n";
        }
        //DoMathOrSomething() <- add it later...
    }
    return(S);
}

// Get 'TradeData' coins, add those to a vector, and sum all profits and subtract all payments:
std::vector<NameValue> GetTotalEachCoin(std::vector<TradeData> Datas)
{
    std::string S = "";
    std::vector<NameValue> Coins = { {Datas[0].Coin1, -Datas[0].Paid}, {Datas[0].Coin2, Datas[0].Received} };
    int Size = Datas.size();
    if (Size > 0)
    {
        double TotalPaid = 0;
        for (int n = 0; n < Datas.size(); ++n)
        {
            for (int m = 0; m < Coins.size(); ++m)
            {
                if (Datas[n].Coin1.compare(Coins[m].Name) != 0)
                {
                    Coins.push_back({ Datas[n].Coin1, -Datas[n].Paid });
                }
                else
                {
                    Coins[m].Value -= Datas[n].Paid;
                }
                if (Datas[n].Coin2.compare(Coins[m].Name) != 0)
                {
                    Coins.push_back({ Datas[n].Coin2, Datas[n].Received });
                }
                else
                {
                    Coins[m].Value += Datas[n].Received;
                }
            }
        }
    }
    return(Coins);
}

// Find in a 'NameValue' if there is certain coin with same 'Name', then convert it and change name to the converted coin:
void ConvertAllCoinsType(std::vector<NameValue>& Coins, std::string Name, double Convert, std::string NewName)
{
    for (int n = 0; n < Coins.size(); ++n)
    {
        if (Coins[n].Name.compare(Name) == 0) { Coins[n].Value *= Convert; Coins[n].Name = NewName; }
    }
}

// Get sum of values from a vector of 'NameValue':
// *ATTENTION*: it will sum different coins values as the same if you haven't converted those.
double SumAllCoinsValues(std::vector<NameValue> Coins) { double T = 0; for (int n = 0; n < Coins.size(); ++n) { T += Coins[n].Value; } return(T); }

// Get coin names:
std::vector<std::string> GetCoinNames(std::vector<NameValue> Coins) { std::vector<std::string> S; for (int n = 0; n < Coins.size(); ++n) { S.push_back(Coins[n].Name); } return(S); }

// Join equal coins (given a name) on same vector, those are going to be in the last index:
std::vector<NameValue> JoinCoinsType(std::vector<NameValue> Coins, std::string Name)
{
    std::vector<NameValue> V;
    NameValue Coin = { Name, 0 };
    for (int n = 0; n < Coins.size(); ++n)
    {
        if (Coins[n].Name.compare(Name) == 0) { Coin.Value += Coins[n].Value; } else { V.push_back(Coins[n]); }
    }
    V.push_back(Coin);
    return(V);
}

std::vector<NameValue> JoinCoins(std::vector<NameValue> Coins)
{
    std::string S = "";
    std::vector<NameValue> NewCoins = { {Coins[0].Name, Coins[0].Value} };
    int Size = Coins.size();
    if (Size > 0)
    {
        double TotalPaid = 0;
        for (int n = 0; n < Coins.size(); ++n)
        {
            for (int m = 0; m < Coins.size(); ++m)
            {
                if (Coins[n].Name.compare(NewCoins[m].Name) != 0)
                {
                    NewCoins.push_back({ Coins[n].Name, Coins[n].Value });
                }
                else
                {
                    NewCoins[m].Value += Coins[n].Value;
                }
            }
        }
    }
    return(Coins);
}


// ############################
// ####### CHART FUNCTIONS
// ############################

// The Formula for the Linearly Weighted Moving Average (LWMA):
// https://www.investopedia.com/terms/l/linearlyweightedmovingaverage.asp
// Prices vectos is a period for each item | Weight go from high to low | Curve is a exponential function to control the height change ('1' is linear):
/*
* Choose a lookback period. This is how many n values will be calculated into the LWMA.
* Calculate the linear weights for each period. This can be accomplished in a couple of ways.
  The easiest is to assign n as the weight for the first value. For example, if using a 100-period lookback,
  then the first value is multiplied by a weight of 100, the next value is multiplied by a weight of 99.
  A more complex way is to choose a different weight for the most recent value, such as 30.
  Now each value will need to drop by 30/100 so that when n-99 (100th period) is reached the weight is one.
* Multiply the prices for each period by their respective weights, then get the sum total.
* Divide the above by the sum of all the weights.
*/
double LWMA(vector<double> Prices, double HighWeight, double LowWeight, double CurvePower)
{
    double Size = Prices.size();
    double Sum = 0, SumW = 0; // Sum the prices and then get the sum of the Weights
    if (Size > 0)
    {
        if (CurvePower <= 0) { CurvePower = 0.000001; }
        if (HighWeight < LowWeight) { double T = HighWeight; HighWeight = LowWeight; LowWeight = T; }
        
        double Weight;
        double D = HighWeight - LowWeight;
        double Div = D / Size;
        double Curve;

        for (int n = 0; n < Size; ++n)
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

// ############################
// ####### BBBB
// ############################


// #####################################################################################################################################
// #####################################################################################################################################
// #####################################################################################################################################

// ############################
// ####### CCCC
// ############################

// ############################

// ############################


// ############################




// #####################################################################################################################################



// ################################################# FIM ####################################################################################

#endif // SCPARSE_
