#pragma once

#ifndef YSXMONEY_H
#define YSXMONEY_H

// ############################################################################################################################################
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// !!!!!!!	
// !!!!!!!	CATALOGO DE MUDANÇAS (MANTENHA EM ORDEM):
// !!!!!!!	* Totally new ideas, ignore this header for now;
// !!!!!!!	* Verify file format
// !!!!!!!	
// ################################################# ANOTAÇÕES E ATENÇÕES #################################################
// ############################################################################################################################################

// ############################################################################################################################################

// ############################
// ####### FUNCTIONS
// ############################

// ############################################################################################################################################
// ############################################################################################################################################
// ############################################################################################################################################

// ############################
// ####### TRADE RELATED
// ############################

// PROFIT FROM AN OPERATION WHICH YOU BUY THEN SELL, OR OTHERWISE:
double ProfitOP(double Price1, double Coins1, double Price2, double Coins2)
{

}

// SINGLE TRADE OPERATION:
struct TradeOP
{
    char Coin1[4], Coin2[4]; // Names
    double Price, Coins; // Strike-Price and the amount of coins paid
    bool SB; // 'S'ell (0) or 'B'uy (1)
};

// VALUES INSIDE 'TradeOP':
void CoutTradeOP(TradeOP OP)
{
    for (short n = 0; n < 4; ++n) { std::cout << OP.Coin1[n]; }
    for (short n = 0; n < 4; ++n) { std::cout << OP.Coin2[n]; }
    std::cout << std::endl;
    std::cout << "PRICE: " << OP.Price << " | COINS: " << OP.Coins << " | ";
    OP.SB ? std::cout << " BUY\n" : std::cout << "SELL\n";
}

// A 'TradeOP' AND PROFIT / LOSS:
struct TradeDone
{
    TradeOP Trade;
    double Gain;
};

// VALUES INSIDE 'TradeDone':
void CoutTradeDone(TradeDone OP)
{
    for (short n = 0; n < 4; ++n) { std::cout << OP.Trade.Coin1[n]; }
    for (short n = 0; n < 4; ++n) { std::cout << OP.Trade.Coin2[n]; }
    std::cout << std::endl;
    std::cout << "PRICE: " << OP.Trade.Price << " | COINS: " << OP.Trade.Coins << " | ";
    OP.Trade.SB ? std::cout << " BUY\n" : std::cout << "SELL\n";
    std::cout << "GAIN: " << OP.Gain << std::endl;
}

/* COLLECTION OF TRADE OPERATIONS, DONE AND TO BE DONE, CALCULATE POSSIBLE GAINS OR AQUIRED GAINS:
IT ALSO CALCULATES TARGET PRICES TO BUY / SELL WITH DESIRED GAINS TO COMPLETE YOUR OPERATIONS.
With 'TradeBook' you can create new 'TradeOP' & 'TradeDone' vectors and maintain the values from a saved file.
Be sure to delete a 'Trades' item after adding it to 'Done' vector.
Whenever a function asks for 'Gain', use '0 < Gain < 1' to chek your possible loss, and '> 1' to check your
possible profit. Not sure why someone would need negative numbers for 'Gain', but it is possible if you want to.*/
class TradeBook
{
public:
    std::vector<TradeOP> Trades; // Trades in progress
    std::vector<TradeDone> Done; // Trades done. It is public, but you shouldn't mess with it too much, some functions use 'push_back' and other are order oriented
    double GainTrade = 0; // Total gain if all trades end up being sucessful
    double GainDone = 0; // Total gain from 'Done' vector
    std::vector<std::vector<double>> Ranges; // Prices you may aim to. Use function

    // SUM ALL GAINS FROM ALL 'Trades', SAVE VALUE ON 'GainTrade':
    // NOTE: It RESETS 'GainTrade' to '0'.
    void PossibleGain(double Gain)
    {
        double Fee = 0; GainTrade = 0;
        for (unsigned int n = 0; n < Trades.size(); ++n)
        {
            if (Trades[n].SB) { Fee = Trades[n].Price * 1.02; } // 1% to BUY and another 1% to re-sell
            else { Fee = Trades[n].Price * 0.98; }
            if (Trades[n].SB) { GainTrade += ((Trades[n].Coins * Fee * Gain) - (Trades[n].Coins * Trades[n].Price)) / (Fee * Gain); }
            else { GainTrade += ((Trades[n].Coins * Trades[n].Price) - (Trades[n].Coins * (Fee / Gain))) / (Fee * Gain); }
        }
    }

    // ADD RANGES IN VECTOR:
    void DoRanges(double Gain1, double Gain2, unsigned char Divisions)
    {
        if (Gain1 > Gain2) { double t = Gain1; Gain1 = Gain2; Gain2 = t; }
        double d = (Gain2 - Gain1) / (double)Divisions;
        double Fee = 0;
        std::vector<std::vector<double>> R;
        for (unsigned int n = 0; n < Trades.size(); ++n)
        {
            std::vector<double> RangeDivs;
            if (Trades[n].SB) { Fee = Trades[n].Price * 1.02; }
            else { Fee = Trades[n].Price * 0.98; }
            for (double x = Gain1; x < Gain2; x += d)
            {
                if (Trades[n].SB) { RangeDivs.push_back(Fee * x); }
                else { RangeDivs.push_back(Fee / x); }
            }
            R.push_back(RangeDivs);
        }
        Ranges = R;
    }

    // SOLVE ALL 'Trade'S INSIDE 'Done' VECTOR:
    void DoAllDoneTrades(double Gain)
    {
        if (Done.size() > 0)
        {
            GainDone = 0;
            double Fee = 0;
            for (unsigned int n = 0; n < Done.size(); ++n)
            {
                if (Done[n].Trade.SB) { Fee = Done[n].Trade.Price * 1.02; }
                else { Fee = Done[n].Trade.Price * 0.98; }
                if (Done[n].Trade.SB)
                {
                    Done[n].Gain = ((Done[n].Trade.Coins * Fee * Gain) - (Done[n].Trade.Coins * Done[n].Trade.Price)) / (Fee * Gain);
                    GainDone += Done[n].Gain;
                }
                else
                {
                    Done[n].Gain = ((Done[n].Trade.Coins * Done[n].Trade.Price) - (Done[n].Trade.Coins * (Fee / Gain))) / (Fee * Gain);
                    GainDone += Done[n].Gain;
                }
            }
        }
    }

    /* SOLVE A TRADE, DELETE IT, ADD AS 'TRADE DONE':
    If you use 'DoAllDoneTrades', it resets 'GainDone', but it counts every item inside 'Done' vector,
    so it makes no difference. However, this means you can simply add a 'TradeOP' inside a item in
    'Done' vector (probably deleting 'TradeOP' item if in a vector), and you don't need to do the calcs,
    because the function is going to do it it for you. This way the computer won't do twice the work.
    The same caution you need to with this function, this won't reset 'GainDone', it is going to sum with
    the value that is already there, so, if you use this function twice for the same trade, the 'GainDone'
    is going to be incorrect (at least for the reason it was designed).
    */
    void DoTrade(unsigned int Index, double Gain)
    {
        if (Index < Trades.size() - 1 && Trades.size() > 0)
        {
            TradeDone D; D.Trade = Trades[Index];
            double Fee, Coins = D.Trade.Coins;
            if (D.Trade.SB) { Fee = D.Trade.Price * 1.02; } else { Fee = D.Trade.Price * 0.98; }
            if (D.Trade.SB)
            {
                D.Gain = ((D.Trade.Coins * Fee * Gain) - (D.Trade.Coins * D.Trade.Price)) / (Fee * Gain);
                GainDone += D.Gain;
            }
            else
            {
                D.Gain = ((D.Trade.Coins * D.Trade.Price) - (D.Trade.Coins * (Fee / Gain))) / (Fee * Gain);
                GainDone += D.Gain;
            }
            Trades.erase(Trades.begin() + Index);
            Done.push_back(D);
        }
    }

    // SAME AS 'DoTrade', BUT BETWEEN A RANGE:
    // Also, CHECK 'DoTrade' comment for ! cautions !
    void DoSomeTrades(unsigned int n0, unsigned int n1, double Gain)
    {
        if (n0 > n1) { unsigned int t = n0; n0 = n1; n1 = t; }
        if (n1 < Trades.size() - 1 && Trades.size() > n0)
        {
            double Fee, Coins;
            TradeDone D;
            for (unsigned int n = n0; n <= n1; ++n)
            {
                D.Trade = Trades[n];
                Coins = D.Trade.Coins;
                if (D.Trade.SB) { Fee = D.Trade.Price * 1.02; }
                else { Fee = D.Trade.Price * 0.98; }
                if (D.Trade.SB)
                {
                    D.Gain = ((D.Trade.Coins * Fee * Gain) - (D.Trade.Coins * D.Trade.Price)) / (Fee * Gain);
                    GainDone += D.Gain;
                }
                else
                {
                    D.Gain = ((D.Trade.Coins * D.Trade.Price) - (D.Trade.Coins * (Fee / Gain))) / (Fee * Gain);
                    GainDone += D.Gain;
                }
                Trades.erase(Trades.begin() + n);
                Done.push_back(D);
            }
        }
    }

    /* SAME AS 'DoSomeTrades', BUT ALL TRADES IN VECTOR:
    Also, CHECK 'DoTrade' comment for ! cautions !
    However, this function DOES reset 'GainDone' to '0'!
    REMEMBER, this ERASES all items from the 'TradeOP' vector!
    It becomes a vector with '0' items, not the same number of indexes as before!*/
    void DoAllTrades(double Gain)
    {
        if (Trades.size() > 0)
        {
            double Fee;
            TradeDone D; GainDone = 0;
            for (unsigned int n = 0; n < Trades.size(); ++n)
            {
                D.Trade = Trades[n];
                if (D.Trade.SB) { Fee = D.Trade.Price * 1.02; }
                else { Fee = D.Trade.Price * 0.98; }
                if (D.Trade.SB)
                {
                    D.Gain = ((D.Trade.Coins * Fee * Gain) - (D.Trade.Coins * D.Trade.Price)) / (Fee * Gain);
                    GainDone += D.Gain;
                }
                else
                {
                    D.Gain = ((D.Trade.Coins * D.Trade.Price) - (D.Trade.Coins * (Fee / Gain))) / (Fee * Gain);
                    GainDone += D.Gain;
                }
                Done.push_back(D);
            }
            Trades = std::vector<TradeOP>::vector(); // CLEAN EVERYTHING AT ONCE!
        }
    }
};

// ############################
/*
TRADE BOOK FILE FORMAT:
double GainTrade, GainDone;
unsigned int Size = Size of vector 'Trades';
unsigned int Size = Size of vector 'TradeDone';
All values (TradeOP) from 'Trades' vector;
All values (TradeDone) from 'Done' vector;
---
After loading files, calculate price ranges.
*/

// SAVE TRADEBOOK IN A BINARY FILE, CHECK COMMENT ABOUT FILE FORMAT IN THIS HEADER:
void SaveTradeBook(TradeBook ToSave, std::string Filename)
{
    std::ofstream O(Filename + ".TradeBook", std::ios::binary);
    unsigned int TSize = ToSave.Trades.size();
    unsigned int DSize = ToSave.Done.size();    
    O.write((char*)&ToSave.GainTrade, sizeof(double)); O.write((char*)&ToSave.GainDone, sizeof(double));
    O.write((char*)&TSize, sizeof(TSize)); O.write((char*)&DSize, sizeof(DSize));
    for (unsigned int n = 0; n < TSize; ++n) { O.write((char*)&ToSave.Trades[n], sizeof(TradeOP)); } // Probably better to load 'siezof() * TSize'
    for (unsigned int n = 0; n < DSize; ++n) { O.write((char*)&ToSave.Done[n], sizeof(TradeDone)); }
    O.close();
}

// SAME AS 'SaveTradeBook', BUT VECTOR:
void SaveTradeBooks(std::vector<TradeBook> ToSave, std::string Filename)
{
    std::ofstream O(Filename + ".TradeBook", std::ios::binary);
    for (int TB = 0; TB < ToSave.size(); ++TB)
    {
        unsigned int TSize = ToSave[TB].Trades.size();
        unsigned int DSize = ToSave[TB].Done.size();
        O.write((char*)&ToSave[TB].GainTrade, sizeof(double)); O.write((char*)&ToSave[TB].GainDone, sizeof(double));
        O.write((char*)&TSize, sizeof(TSize)); O.write((char*)&DSize, sizeof(DSize));
        for (unsigned int n = 0; n < TSize; ++n) { O.write((char*)&ToSave[TB].Trades[n], sizeof(TradeOP)); }
        for (unsigned int n = 0; n < DSize; ++n) { O.write((char*)&ToSave[TB].Done[n], sizeof(TradeDone)); }
    }
    O.close();
}

// APPEND TRADEBOOK AT THE END OF A FILE:
void AppendTradeBook(TradeBook ToSave, std::string Filename)
{
    std::fstream F(Filename + "TradeBook", std::ios::binary);
    if (F.is_open())
    {
        F.seekp(0, std::ios::end);
        unsigned int TSize = ToSave.Trades.size();
        unsigned int DSize = ToSave.Done.size();
        F.write((char*)&ToSave.GainTrade, sizeof(double)); F.write((char*)&ToSave.GainDone, sizeof(double));
        F.write((char*)&TSize, sizeof(TSize)); F.write((char*)&DSize, sizeof(DSize));
        for (unsigned int n = 0; n < TSize; ++n) { F.write((char*)&ToSave.Trades[n], sizeof(TradeOP)); }
        for (unsigned int n = 0; n < DSize; ++n) { F.write((char*)&ToSave.Done[n], sizeof(TradeDone)); }
    }
    else { std::cout << "Error opening file!\n"; }
    F.close();
}

// SAME AS 'AppendTradeBook', BUT VECTOR:
void AppendTradeBooks(std::vector<TradeBook> ToSave, std::string Filename)
{
    std::fstream F(Filename + "TradeBook", std::ios::binary);
    if (F.is_open())
    {
        F.seekp(0, std::ios::end);
        for (int TB = 0; TB < ToSave.size(); ++TB)
        {
            unsigned int TSize = ToSave[TB].Trades.size();
            unsigned int DSize = ToSave[TB].Done.size();
            F.write((char*)&ToSave[TB].GainTrade, sizeof(double)); F.write((char*)&ToSave[TB].GainDone, sizeof(double));
            F.write((char*)&TSize, sizeof(TSize)); F.write((char*)&DSize, sizeof(DSize));
            for (unsigned int n = 0; n < TSize; ++n) { F.write((char*)&ToSave[TB].Trades[n], sizeof(TradeOP)); }
            for (unsigned int n = 0; n < DSize; ++n) { F.write((char*)&ToSave[TB].Done[n], sizeof(TradeDone)); }
        }
    }
    else { std::cout << "Error opening file!\n"; }
    F.close();
}

// LOAD TRADEBOOK IN A BINARY FILE, CHECK COMMENT ABOUT FILE FORMAT IN THIS HEADER:
std::vector<TradeBook> LoadTradeBooks(std::string Filename)
{
    std::ifstream I(Filename + ".TradeBook", std::ios::binary);
    std::vector<TradeBook> TBs;
    if (I.is_open())
    {
        while (!I.eof())
        {
            TradeBook TB;
            double Dbl; unsigned int Int;
            I.read((char*)&Dbl, sizeof(double));
            TB.GainTrade = Dbl;
            I.read((char*)&Dbl, sizeof(double));
            TB.GainDone = Dbl;
            I.read((char*)&Int, sizeof(int));
            TB.Trades = std::vector<TradeOP>::vector(Int);
            I.read((char*)&Int, sizeof(int));
            TB.Done = std::vector<TradeDone>::vector(Int);
            if (TB.Trades.size() > 0) { I.read((char*)&TB.Trades[0], sizeof(TradeOP) * TB.Trades.size()); }
            if (TB.Done.size() > 0) { I.read((char*)&TB.Done[0], sizeof(TradeDone) * TB.Done.size()); }
            TBs.push_back(TB);
        }
    }
    else { std::cout << "Error opening file!\n"; }
    I.close();
    return(TBs);
}
// ############################################################################################################################################

// ############################
// ####### TÉCNICOS
// ############################


/*
// Find in a 'NameValue' if there is certain coin with same 'Name', then convert it and change name to the converted coin:
void ConvertAllTrade[n].CoinsType(std::vector<NameValue>& Trade[n].Coins, std::string Name, double Convert, std::string NewName)
{
    for (int n = 0; n < Trade[n].Coins.size(); ++n)
    {
        if (Trade[n].Coins[n].Name.compare(Name) == 0) { Trade[n].Coins[n].Value *= Convert; Trade[n].Coins[n].Name = NewName; }
    }
}

// Get sum of values from a vector of 'NameValue':
// *ATTENTION*: it will sum different coins values as the same if you haven't converted those.
double SumAllTrade[n].CoinsValues(std::vector<NameValue> Trade[n].Coins) { double T = 0; for (int n = 0; n < Trade[n].Coins.size(); ++n) { T += Trade[n].Coins[n].Value; } return(T); }

// Get coin names:
std::vector<std::string> GetCoinNames(std::vector<NameValue> Trade[n].Coins) { std::vector<std::string> S; for (int n = 0; n < Trade[n].Coins.size(); ++n) { S.push_back(Trade[n].Coins[n].Name); } return(S); }

// Join equal coins (given a name) on same vector, those are going to be in the last index:
std::vector<NameValue> JoinTrade[n].CoinsType(std::vector<NameValue> Trade[n].Coins, std::string Name)
{
    std::vector<NameValue> V;
    NameValue Coin = { Name, 0 };
    for (int n = 0; n < Trade[n].Coins.size(); ++n)
    {
        if (Trade[n].Coins[n].Name.compare(Name) == 0) { Coin.Value += Trade[n].Coins[n].Value; } else { V.push_back(Trade[n].Coins[n]); }
    }
    V.push_back(Coin);
    return(V);
}

std::vector<NameValue> JoinTrade[n].Coins(std::vector<NameValue> Trade[n].Coins)
{
    std::string S = "";
    std::vector<NameValue> NewTrade[n].Coins = { {Trade[n].Coins[0].Name, Trade[n].Coins[0].Value} };
    int Size = Trade[n].Coins.size();
    if (Size > 0)
    {
        double TotalPaid = 0;
        for (int n = 0; n < Trade[n].Coins.size(); ++n)
        {
            for (int m = 0; m < Trade[n].Coins.size(); ++m)
            {
                if (Trade[n].Coins[n].Name.compare(NewTrade[n].Coins[m].Name) != 0)
                {
                    NewTrade[n].Coins.push_back({ Trade[n].Coins[n].Name, Trade[n].Coins[n].Value });
                }
                else
                {
                    NewTrade[n].Coins[m].Value += Trade[n].Coins[n].Value;
                }
            }
        }
    }
    return(Trade[n].Coins);
}
*/

// ############################
// ####### CHART FUNCTIONS
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
double LWMA(std::vector<double> Prices, double HighWeight, double LowWeight, double CurvePower)
{
    double Size = Prices.size();
    double Sum = 0, SumW = 0; // Sum the prices and then get the sum of the Weights
    if (Size > 0)
    {
        if (CurvePower = 0) { CurvePower = 0.000001; } if (CurvePower < 0) { CurvePower *= -1; }
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