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

struct ysxTRADE_Op { std::string Pair = "BTCBRL"; double Amount1, Price1, Price2, Amount2; };

double ysxTRADE_Profit(ysxTRADE_Op Op) { return((Op.Price2 / Op.Price1) * Op.Amount2); }

class ysxTRADE_Book
{
public:
    std::vector<ysxTRADE_Op> Operations;
    double TotalProfit = 0;
    double InitialBank = 0;
    double Bank = 0;
    double PercentProfit = 0;
    uint64_t LastOpIndex = 0; // Last operation index
    
    // GET 'Bank / InitialBank' AND ADD TO 'PercentProfit', THIS FUNCTION IS ALWAYS USED WHEN BANK IS CHANGED:
    void GetPercentProfit() { PercentProfit = InitialBank == 0 ? Bank : Bank / InitialBank; }

    // PUSH BACK NEW OPERATION ON THE 'Operations' VECTOR:
    void InsertOperation(std::string Pair, double Amount1, double Price1, double Price2, double Amount2)
    {
        Operations.push_back({Pair, Amount1, Price1, Price2, Amount2});
    }

    // GET TOTAL PROFIT, YOU SHOULD ADD TO BANK MANUALY, TAKE THAT IN MIND TO NOT ADD TWICE TO THE BANK:
    double GetTotalProfit()
    {
        TotalProfit = 0;
        for (size_t n = 0; n < Operations.size(); ++n)
        {
            TotalProfit += ysxTRADE_Profit(Operations[n]);
        }
    }
    
    // GET PROFIT SINCE THE LAST OPERATION CALCULATED AND ADD TO BANK, SET 'LastOpIndex' IF YOU WANT TO START FROM SOMEWHERE ELSE:
    double GetProfit()
    {
        size_t n;
        double Prof;
        for (n = LastOpIndex; n < Operations.size(); ++n)
        {
            Prof = ysxTRADE_Profit(Operations[n]);
            TotalProfit += Prof; Bank += Prof;            
        }
        LastOpIndex = n;
        GetPercentProfit();
    }

    // GET TOTAL PROFIT, ADD TO BANK AND CLEAN OPERATIONS AND TOTAL:
    double GetTotalAddBankCleanOp()
    {
        TotalProfit = 0;
        LastOpIndex = 0;
        for (size_t n = 0; n < Operations.size(); ++n)
        {
            TotalProfit += ysxTRADE_Profit(Operations[n]);
        }
        Bank += TotalProfit;
        GetPercentProfit();
        TotalProfit = 0;
        Operations = std::vector<ysxTRADE_Op>::vector();
    }

    // CLEAN OPERATIONS VECTOR:
    void CleanOps() { Operations = std::vector<ysxTRADE_Op>::vector(); LastOpIndex = 0; }

    // CLEAN OPERATIONS VECTOR AND TOTAL PROFIT:
    void CleanOpsAndTotal() { Operations = std::vector<ysxTRADE_Op>::vector(); LastOpIndex = 0; TotalProfit = 0; }

    // SAVE BOOK, OVERWRITE EXISTING FILE!
    void SaveBook(std::string File)
    {
        std::ofstream O(File, std::ios::binary);
        if (O.is_open())
        {
            O.write((char*)&TotalProfit, sizeof(double));
            O.write((char*)&InitialBank, sizeof(double));
            O.write((char*)&Bank, sizeof(double));
            O.write((char*)&PercentProfit, sizeof(double));
            O.write((char*)&LastOpIndex, sizeof(uint64_t));
            size_t LastOpIndex = 0; // Last operation index
            for (size_t n = 0; n < Operations.size(); ++n)
            {
                O.write((char*)&Operations[n], sizeof(ysxTRADE_Op));
            }
        }
        else { std::cerr << "Error creating save file!\n\n"; }
    }

    // LOAD BOOK, OVERWRITE OBJECTS INSIDE CLASS!
    void LoadBook(std::string File)
    {
        std::ifstream I(File, std::ios::binary);
        if (I.is_open())
        {
            ysxTRADE_Op Op;
            Operations = std::vector<ysxTRADE_Op>::vector();
            I.read((char*)&TotalProfit, sizeof(double));
            I.read((char*)&InitialBank, sizeof(double));
            I.read((char*)&Bank, sizeof(double));
            I.read((char*)&PercentProfit, sizeof(double));
            I.read((char*)&LastOpIndex, sizeof(uint64_t));
            while (!I.eof())
            {
                I.read((char*)&Op, sizeof(ysxTRADE_Op));
                Operations.push_back(Op);
            }
        }
        else { std::cerr << "Error opening file! Is the file name correct?\n\n"; }
    }
};

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