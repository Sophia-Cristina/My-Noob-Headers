#pragma once

#ifndef YSXTRADE_H
#define YSXTRADE_H

// #####################
// ####### By Sophia Cristina
// ####### For everything related to trading.
// #####################

/*#################################################
REFERENCES:
#################################################*/


// #################################################

// ############################
// ####### TRADE RELATED
// ############################

class ysxTRADE_Order
{
public:
	std::string Ticker[2]; // 0 = Paid, 1 = Received
	double AmntPaid = 1, AmntReceived = 1; // Avoid division by zero

	// AmntPaid is 3.5 USD, the SOL price is 110, AmntReceived = 3.5 / 110 = 0.0318
	void SetReceivedBuy(double Price) { AmntReceived = AmntPaid / Price; }
	// AmntPaid 0.0318 SOL, SOL price is 120, AmntReceived = 0.0318 * 120 = 3.818
	void SetReceivedSell(double Price) { AmntReceived = AmntPaid * Price; }
	// AmntReceived is 3.5 USD, the SOL price is 110, AmntPaid = 3.5 / 110 = 0.0318
	void SetPaidBuy(double Price) { AmntPaid = AmntReceived / Price; }
	// AmntReceived 0.0318 SOL, SOL price is 120, AmntPaid = 0.0318 * 120 = 3.818
	void SetPaidSell(double Price) { AmntPaid = AmntReceived * Price; }
	// Paid 1.5, received 2.93 JUP, price of JUPSUD = 1.5 / 2.93 = 0.51
	double GetPrice() { return(AmntPaid / AmntReceived); }

	std::string GetSpreadSheetString()
	{
	    //std::string S = Ticker[1] + Ticker[0] + 9 + std::to_string(AmntReceived) + 9 + std::to_string(GetPrice()) + 9 + std::to_string(GetPrice() * 1.05) + 9 + std::to_string(AmntReceived) + '\n';
	}
};

// ############################

double ysxTRADE_Profit(ysxTRADE_Order Order0, ysxTRADE_Order Order1) { return(Order1.AmntReceived - Order0.AmntPaid); };

// ############################
// ####### BANK RELATED
// ############################

// Use an array for a wallet:
struct ysxTRADE_Coins
{
	std::string Ticker = "BTC";
	double BankIni = 0, BankActual = 0;
	double ValueIni = 0, ValueActual = 0;
};

class ysxTRADE_Wallet
{
public:
	std::string WalletName = "USD_Wallet_0";
	std::string WalletTicker = "USD"; // The return currency for this wallet

	// Total wallet value (sum(n, Coins[n].ValueActual)),
	// Make sure that the 'Coins[n].ValueActual' are the value of the coin in terms of 'WalletTicker'
	double WalletValue = 0;

	std::vector<double> ConvValues; // Conversion values, ex.: USDBRL, ConvValues[0] = 4.95

	std::vector<ysxTRADE_Coins> Coins;
	std::vector<ysxTRADE_Order> Orders;

	// In a new order, let's say SOLBTC, 'CoinSellVal' should be SOLUSD value (or any ticker you might want to keep track of), and BTCUSD is the 'CoinBuyVal'.
	void NewOrder(ysxTRADE_Order Order, double CoinSellVal, double CoinBuyVal)
	{
	    Orders.push_back(Order);
	    // BUYING:
	    bool Found = false;
	    for (size_t n = 0; n < Coins.size(); ++n) // Find if the bought coin is on the 'Coins' list
	    {
		if (Coins[n].Ticker.compare(Order.Ticker[1]) == 0)
		{
		    Coins[n].BankActual += Order.AmntReceived;
		    Coins[n].ValueActual = CoinBuyVal;
		    Found = true;
		    break;
		}
	    }
	    if (!Found)
	    {
		ysxTRADE_Coins NewCoin;
		NewCoin.Ticker = Order.Ticker[1];
		NewCoin.BankIni = Order.AmntReceived;
		NewCoin.BankActual = Order.AmntReceived;
		NewCoin.ValueIni = CoinBuyVal;
		NewCoin.ValueActual = CoinBuyVal;
		Coins.push_back(NewCoin);
	    }
	    // SELLING:
	    Found = false;
	    for (size_t n = 0; n < Coins.size(); ++n) // Find if the sold coin is on the 'Coins' list
	    {
		if (Coins[n].Ticker.compare(Order.Ticker[0]) == 0)
		{
		    Coins[n].BankActual -= Order.AmntPaid;
		    Coins[n].ValueActual = CoinSellVal;
		    Found = true;
		    break;
		}
	    }
	    if (!Found)
	    {
		ysxTRADE_Coins NewCoin;
		NewCoin.Ticker = Order.Ticker[0];
		//NewCoin.BankIni = -Order.AmntPaid;
		//NewCoin.BankActual = -Order.AmntPaid;
		NewCoin.BankIni = 0; // I decided that any new coin that is sold should be '0', so, when bought back, would get the correct profit
		NewCoin.BankActual = 0;
		NewCoin.ValueIni = CoinSellVal;
		NewCoin.ValueActual = CoinSellVal;
		Coins.push_back(NewCoin);
	    }
	}

	// #################################################
	// #################################################
	// #################################################5

	void SetWalletValue()
	{
	    WalletValue = 0;
	    for (size_t n = 0; n < Coins.size(); ++n)
	    {
		WalletValue += Coins[n].BankActual * Coins[n].ValueActual;
	    }
	}

	// #################################################
	// #################################################
	// #################################################

	void CoutCoins(size_t Start, size_t End)
	{
	    if (End > Coins.size()) { End = Coins.size(); }
	    if (Size > End) { size_t t = Size; Size = End; End = t; }
	    for (size_t n = Start; n < End; ++n)
	    {
		std::cout << "####### n: " << n << " << " | " << Coins[n].Ticker << " #######\n";
		std::cout << "INITIAL BANK: " << Coins[n].BankIni << " | ACTUAL BANK: " << Coins[n].BankActual << '\n';
		std::cout << "INITIAL VALUE: " << Coins[n].ValueIni << " | ACTUAL VALUE: " << Coins[n].ValueActual << '\n';
		std::cout << "####### ####### #######\n\n";
	    }
	}

	void CoutOrders(size_t Start, size_t End)
	{
	    if (End > Coins.size()) { End = Orders.size(); }
	    if (Size > End) { size_t t = Size; Size = End; End = t; }
	    for (size_t n = Start; n < End; ++n)
	    {
		std::cout << "####### n: " << n << " << " | " << Orders[n].Ticker[1] << Orders[n].Ticker[0] << " #######\n";
		std::cout << "AMOUNT PAID: " << Orders[n].AmntPaid << " | AMOUNT RECEIVED: " << Orders[n].AmntReceived << '\n';
		std::cout << "####### ####### #######\n\n";
	    }
	}

};


void ysxTRADE_SaveWallet(ysxTRADE_Wallet Wallet, std::string File = "Wallet.dat")
{
	std::ofstream O(File, std::ios::binary);
	if (!O.is_open()) { std::cerr << "Couldn't create file!" << std::endl; }
	else
	{
		// File header is the list sizes:
		uint32_t Size = (uint32_t)Wallet.WalletName.size();
		O.write((char*)&Size, 4);
		uint8_t SizeT = (uint8_t)Wallet.WalletTicker.size();
		O.write((char*)&SizeT, 1);
		Size = Wallet.ConvValues.size();
		O.write((char*)&Size, 4);
		Size = Wallet.Coins.size();
		O.write((char*)&Size, 4);
		Size = Wallet.Orders.size();
		O.write((char*)&Size, 4);

		// DATA:
		O.write((char*)&Wallet.WalletName[0], Wallet.WalletName.size());
		O.write((char*)&Wallet.WalletTicker[0], Wallet.WalletTicker.size());
		O.write((char*)&Wallet.WalletValue, sizeof(double));
		O.write((char*)&Wallet.ConvValues[0], sizeof(double) * Wallet.ConvValues.size());
		for (size_t n = 0; n < Wallet.Coins.size(); ++n)
		{
		    SizeT = (uint8_t)Wallet.Coins[n].Ticker.size();
		    O.write((char*)&SizeT, 1);
		    O.write((char*)&Wallet.Coins[n].Ticker[0], Wallet.Coins[n].Ticker.size());
		    O.write((char*)&Wallet.Coins[n].BankIni, sizeof(double));
		    O.write((char*)&Wallet.Coins[n].BankActual, sizeof(double));
		    O.write((char*)&Wallet.Coins[n].ValueIni, sizeof(double));
		    O.write((char*)&Wallet.Coins[n].ValueActual, sizeof(double));
		}
		for (size_t n = 0; n < Wallet.Orders.size(); ++n)
		{
		    SizeT = (uint8_t)Wallet.Orders[n].Ticker[0].size();
		    O.write((char*)&SizeT, 1);
		    O.write((char*)&Wallet.Orders[n].Ticker[0][0], Wallet.Orders[n].Ticker[0].size());
		    SizeT = (uint8_t)Wallet.Orders[n].Ticker[1].size();
		    O.write((char*)&SizeT, 1);
		    O.write((char*)&Wallet.Orders[n].Ticker[1][0], Wallet.Orders[n].Ticker[1].size());
		    O.write((char*)&Wallet.Orders[n].AmntPaid, sizeof(double));
		    O.write((char*)&Wallet.Orders[n].AmntReceived, sizeof(double));
		}
	}
}

// ATTENTION: This function does not validate the quality of the file (ex.: corrupted).
// Bugs may happen if the file was saved incorrectly or you are loading the wrong file!
ysxTRADE_Wallet ysxTRADE_LoadWallet(std::string File = "Wallet.dat")
{
	std::ifstream I(File, std::ios::binary);
	ysxTRADE_Wallet Wallet;
	if (!I.is_open()) { std::cerr << "Couldn't create file!" << std::endl; }
	else
	{
		// File header is the list sizes:
		uint32_t NameSize; I.read((char*)&NameSize, 4);
		Wallet.WalletName.resize(NameSize, 'a');
		uint8_t TickerSize; I.read((char*)&TickerSize, 1);
		Wallet.WalletTicker.resize(TickerSize, 'a');
		uint32_t ConvValSize; I.read((char*)&ConvValSize, 4);
		Wallet.ConvValues = std::vector<double>::vector(ConvValSize);
		uint32_t CoinsSize; I.read((char*)&CoinsSize, 4);
		Wallet.Coins = std::vector<ysxTRADE_Coins>::vector(CoinsSize);
		uint32_t OrdersSize; I.read((char*)&OrdersSize, 4);
		Wallet.Orders = std::vector<ysxTRADE_Order>::vector(OrdersSize);

		// DATA:
		I.read((char*)&Wallet.WalletName[0], NameSize);
		I.read((char*)&Wallet.WalletTicker[0], TickerSize);
		I.read((char*)&Wallet.WalletValue, sizeof(double));
		I.read((char*)&Wallet.ConvValues[0], ConvValSize * sizeof(double));

		uint8_t S = 0;
		for (size_t n = 0; n < CoinsSize; ++n)
		{
		    I.read((char*)&S, 1);
		    Wallet.Coins[n].Ticker.resize(S, 'a');
		    I.read((char*)&Wallet.Coins[n].Ticker[0], S);
		    I.read((char*)&Wallet.Coins[n].BankIni, sizeof(double));
		    I.read((char*)&Wallet.Coins[n].BankActual, sizeof(double));
		    I.read((char*)&Wallet.Coins[n].ValueIni, sizeof(double));
		    I.read((char*)&Wallet.Coins[n].ValueActual, sizeof(double));
		}
		for (size_t n = 0; n < OrdersSize; ++n)
		{
		    I.read((char*)&S, 1);
		    Wallet.Orders[n].Ticker[0].resize(S, 'a');
		    I.read((char*)&Wallet.Orders[n].Ticker[0][0], S);
		    I.read((char*)&S, 1);
		    Wallet.Orders[n].Ticker[1].resize(S, 'a');
		    I.read((char*)&Wallet.Orders[n].Ticker[1][0], S);
		    I.read((char*)&Wallet.Orders[n].AmntPaid, sizeof(double));
		    I.read((char*)&Wallet.Orders[n].AmntReceived, sizeof(double));
		}
	}
	return(Wallet);
}

// ###############################################################################################################################################################################
#endif