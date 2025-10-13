#pragma once

#ifndef YSXBINANCE_H
#define YSXBINANCE_H

//#include "ysxCURL.h" // include by the user, above this header

// #####################
// ####### By Sophia Cristina
// ####### Use Binance API.
// #####################

// #################################################
// REFERENCES:
//
// #################################################


#include <chrono>
#include "../../ysxCryp/ysxCrypto.h"
#include "../../ysxTrade/ysxTrade.h"
#include "../../ysxTrade/ysxIndicators.h"
#define USE_SDL3
#include "../SDL/Graph/ysxSDLTrade.h"


#define BIN_API_TIMESTMP std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define BIN_API_WS "wss://ws-api.binance.com:443/ws-api/v3"
#define BIN_API_WSTEST "wss://testnet.binance.vision/ws-api/v3i"


// #################################################
// FUNCTIONS:
// #################################################

// #################################################
// CLASSES:
// #################################################

// This class is capable to do all the basic calls to Binance API. This class is not to be used for operations, but for connections and basic reponses.
// Create classes that inherit or construct this class inside these to use the resources.
class ysxCURL_BinanceAPI
{
    // Ensure curl is initialized:
    bool EnsureCurl()
    {
        if (!CURLHandle)
        {
            curl_global_init(CURL_GLOBAL_DEFAULT);
            CURLHandle = curl_easy_init();
            if (!CURLHandle) { return(false); }
        }
        return(true);
    }


    // #################################################


public:
    const std::string BaseURL = "https://api.binance.com";  // real base
    CURL* CURLHandle = nullptr;
    std::string APIKey;
    std::string APISecret; // your secret
    std::string Response;

    // Read key and secret key from file (file should have only the keys and no other text and in the same order in separated lines):
    // The strings are public, you can also simple write it directly if you want so.
    bool GetKeySecretTxt(const std::string& FileName)
    {
        std::ifstream File(FileName);
        if (!File.is_open()) { std::cerr << "Could not open file: " << FileName << "\n"; return(false); }
        if (!std::getline(File, APIKey)) { std::cerr << "Could not read API key from file.\n"; return(false); }
        if (!std::getline(File, APISecret)) { std::cerr << "Could not read API secret from file.\n"; return(false); }
        File.close();
        return(true);
    }

    // Generic GET request:
    bool PerformRequest(const std::string& url, struct curl_slist* headers = nullptr)
    {
        if (!EnsureCurl())
        {
            std::cerr << "Failed to init CURL.\n";
            return(false);
        }

        // Reset previous response
        Response.clear();

        curl_easy_setopt(CURLHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(CURLHandle, CURLOPT_WRITEFUNCTION, &ysxCURL_WriteToStringCallback);
        curl_easy_setopt(CURLHandle, CURLOPT_WRITEDATA, &Response);

        if (headers) { curl_easy_setopt(CURLHandle, CURLOPT_HTTPHEADER, headers); }

        CURLcode res = curl_easy_perform(CURLHandle);
        if (res != CURLE_OK)
        {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
            return(false);
        }
        return(true);
    }


    // Base Query string that is used in basically all calls for Binance API:
    std::string GetQueryString()
    {
        long long ts = BIN_API_TIMESTMP;
        std::ostringstream qs;
        qs << "timestamp=" << ts;
        // You can decide the time window that a request is accepted with this command:
        // qs << "&recvWindow=5000";

        std::string queryString = qs.str();

        // Compute signature over queryString using HMAC SHA256 with APISecret:
        std::vector<uint8_t> SecretKey = ysxBYTE_String2UI8Vec(APISecret);
        ysxCRYPT_HMAC HMAC(ysxCRYPT_SHA::Type::tSHA256, SecretKey);
        std::string signature = HMAC.ComputeHex(queryString);
        // Append signature
        queryString += "&signature=" + signature;

        // Full URL
        return(queryString);
    }


    // Get price of a pair (symbol, ex.: 'BTCUSDT'):
    double GetSymbolPrice(const std::string& symbol)
    {
        std::string url = BaseURL + "/api/v3/ticker/price?symbol=" + symbol;
        struct curl_slist* headers = nullptr;
        Response.clear();

        if (!PerformRequest(url, headers)) { std::cerr << "CURL request failed for symbol: " << symbol << "\n"; return(0); }
        if (Response.empty()) { std::cerr << "Empty response for symbol: " << symbol << "\n"; return(0); }

        nlohmann::json j;
        try { j = nlohmann::json::parse(Response); }
        catch (const std::exception& e) { std::cerr << "JSON parse error for " << symbol << ": " << e.what() << "\n"; return(0); }
        if (!j.contains("price")) { std::cerr << "No 'price' in response for " << symbol << ": " << j.dump() << "\n"; return(0); }
        try { return(std::stod(j["price"].get<std::string>())); }
        catch (const std::exception& e) { std::cerr << "Invalid price format for " << symbol << ": " << e.what() << "\n"; return(0); }
    }



    // #################################################

    ysxCURL_BinanceAPI() { }
    ysxCURL_BinanceAPI(const std::string& SetKey, const std::string& SetSecret) { APIKey = SetKey; APISecret = SetSecret; }
    //ysxCURL_BinanceAPI(const std::string& APIKeysFile) { GetKeySecretTxt(APIKeysFile); }

    ~ysxCURL_BinanceAPI()
    {
        if (CURLHandle) { curl_easy_cleanup(CURLHandle); CURLHandle = nullptr; }
        curl_global_cleanup();
    }
};


// #################################################
// #################################################
// #################################################


// Class to deal with balance operations, like, accounting, converstions and etc.
// This class is not about trading or other operations.
class ysxCURL_BinanceAPIBalanceOps
{
public:
    ysxCURL_BinanceAPI BinAPI;
    std::map<std::string, double> Balances;

    // Get account balances from Spot and Futures (USDT AND COIN-CM), mix balances togheter and add to 'Balances' 'std::map':
    bool GetBalance()
    {
        nlohmann::json j;

        // SPOT balance:
        std::string FullURL =  BinAPI.BaseURL + "/api/v3/account?" +  BinAPI.GetQueryString();
        struct curl_slist* Headers = nullptr;
        std::string KeyHdr = "X-MBX-APIKEY: " + BinAPI.APIKey;
        Headers = curl_slist_append(Headers, KeyHdr.c_str());
        bool ok = BinAPI.PerformRequest(FullURL, Headers);
        curl_slist_free_all(Headers);
        if (!ok) { std::cerr << "'GetBalance()' (SPOT) request failed.\n"; return(false); }
        curl_easy_reset(BinAPI.CURLHandle);
        nlohmann::json spot_json = nlohmann::json::parse(BinAPI.Response);
        if (spot_json.is_discarded()) { std::cerr << "Failed to parse SPOT JSON.\n"; return(false); }
        if (spot_json.contains("balances"))
        {
            for (const auto& item : spot_json["balances"])
            {
                j["balances"].push_back(item);
            }
        }
        std::cout << "SPOT RESPONSE:\n" << BinAPI.Response << "\n\n";


        // COIN-CM balance:
        FullURL =  "https://dapi.binance.com/dapi/v1/balance?" +  BinAPI.GetQueryString();
        struct curl_slist* Headersc = nullptr;
        KeyHdr = "X-MBX-APIKEY: " + BinAPI.APIKey;
        Headersc = curl_slist_append(Headersc, KeyHdr.c_str());
        ok = BinAPI.PerformRequest(FullURL, Headersc);
        curl_slist_free_all(Headersc);
        if (!ok) { std::cerr << "'GetBalance()' (COIN-M) request failed.\n"; return(false); }
        curl_easy_reset(BinAPI.CURLHandle);
        nlohmann::json coincm_json = nlohmann::json::parse(BinAPI.Response);
        if (coincm_json.is_discarded()) { std::cerr << "Failed to parse COIN-CM JSON.\n"; return(false); }
        if (coincm_json.is_array())
        {
            for (const auto& item : coincm_json)
            {
                if (item.contains("asset") && item.contains("balance"))
                {
                    nlohmann::json New;
                    New["asset"]  = item["asset"];
                    New["free"]   = item["balance"];
                    New["locked"] = "0";
                    j["balances"].push_back(New);
                }
            }
        }
        std::cout << "COIN-CM RESPONSE:\n" << BinAPI.Response << "\n\n";

        // USDT-M balance:
        FullURL =  "https://fapi.binance.com/fapi/v2/balance?" +  BinAPI.GetQueryString();
        struct curl_slist* Headersu = nullptr;
        KeyHdr = "X-MBX-APIKEY: " + BinAPI.APIKey;
        Headersu = curl_slist_append(Headersu, KeyHdr.c_str());
        ok = BinAPI.PerformRequest(FullURL, Headersu);
        curl_slist_free_all(Headersu);
        if (!ok) { std::cerr << "'GetBalance()' (USDT-M) request failed.\n"; return(false); }
        curl_easy_reset(BinAPI.CURLHandle);
        nlohmann::json usdtm_json = nlohmann::json::parse(BinAPI.Response);
        if (usdtm_json.is_discarded()) { std::cerr << "Failed to parse USDT-M JSON.\n"; return(false); }
        if (usdtm_json.is_array())
        {
            for (const auto& item : usdtm_json)
            {
                if (item.contains("asset") && item.contains("balance"))
                {
                    nlohmann::json New;
                    New["asset"]  = item["asset"];
                    New["free"]   = item["balance"];
                    New["locked"] = "0";
                    j["balances"].push_back(New);
                }
            }
        }
        std::cout << "USDT-M RESPONSE:\n" << BinAPI.Response << "\n\n";



        std::map<std::string, double> GetBalancesMap;

        for (auto& a : j["balances"])
        {
            std::string asset = a.value("asset", "");
            if (asset.empty()) { continue; }

            std::string s_free  = a.value("free", "0.0");
            std::string s_locked = a.value("locked", "0.0");

            double free  = 0.0, locked = 0.0;
            try { free = std::stod(s_free); locked = std::stod(s_locked); } catch (...) { continue; }

            double total = free + locked;
            if (total > 0.0) { GetBalancesMap[asset] = total; }
        }
        Balances = GetBalancesMap;
        return(true);
    }

    std::string BalancesString()
    {
        std::ostringstream Out;
        Out << "##################### BALANCE #####################\n";

        // Fetch conversion rates:
        double USDT_BRL = BinAPI.GetSymbolPrice("USDTBRL");
        double BTC_USDT = BinAPI.GetSymbolPrice("BTCUSDT");
        double SOL_USDT = BinAPI.GetSymbolPrice("SOLUSDT");

        // Calculate total USD and conversions:
        double totalUSD = 0.0;
        for (auto& [asset, qty] : Balances)
        {
            Out << asset << ":\n";
            Out << "Quantity: " << qty << "\n";

            auto GetPair = [&](const std::string& base, const std::string& quote)
            {
                std::string p = base + quote;
                try { return(BinAPI.GetSymbolPrice(p)); }
                catch (...) { return(0.0); }
            };
            double toUSDT, toBRL, toBTC, toSOL;
            if (asset == "USDT" || asset == "USDC") { toUSDT = 1; totalUSD += toUSDT * qty; toBRL = USDT_BRL; toBTC = 1 / BTC_USDT; toSOL = 1 / SOL_USDT; }
            else if (asset == "BRL") { toUSDT = 1 / USDT_BRL; totalUSD += toUSDT * qty; toBRL = 1; toBTC = 1 / (BTC_USDT * USDT_BRL); toSOL = 1 / (SOL_USDT * USDT_BRL); }
            else if (asset == "LDSXP")
            {
                toUSDT = GetPair("SXP", "USDT"); totalUSD += toUSDT * qty;
                toBRL  = (toUSDT > 0.0) ? (toUSDT * USDT_BRL) : 0.0;
                toBTC  = (toUSDT > 0.0) ? (toUSDT / BTC_USDT) : 0.0;
                toSOL  = (toUSDT > 0.0) ? (toUSDT / SOL_USDT) : 0.0;
            }
            else if (asset == "LDTRX")
            {
                toUSDT = GetPair("TRX", "USDT"); totalUSD += toUSDT * qty;
                toBRL  = (toUSDT > 0.0) ? (toUSDT * USDT_BRL) : 0.0;
                toBTC  = (toUSDT > 0.0) ? (toUSDT / BTC_USDT) : 0.0;
                toSOL  = (toUSDT > 0.0) ? (toUSDT / SOL_USDT) : 0.0;
            }
            else if (asset == "NFT") { toUSDT = 0; toBRL = 0; toBTC = 0; toSOL = 0; }
            else
            {
                toUSDT = GetPair(asset, "USDT"); totalUSD += toUSDT * qty;
                toBRL  = (toUSDT > 0.0) ? (toUSDT * USDT_BRL) : 0.0;
                toBTC  = (toUSDT > 0.0) ? (toUSDT / BTC_USDT) : 0.0;
                toSOL  = (toUSDT > 0.0) ? (toUSDT / SOL_USDT) : 0.0;
            }
            Out << asset << "/USDT: " << toUSDT << " | " << toUSDT * qty << "\n";
            Out << asset << "/BRL:  " << toBRL  << " | " << toBRL * qty << "\n";
            Out << asset << "/BTC:  " << toBTC  << " | " << toBTC * qty << "\n";
            Out << asset << "/SOL:  " << toSOL  << " | " << toSOL * qty << "\n";
            Out << "\n#####################\n\n";
        }

        Out << "##################### TOTAL BALANCE #####################\n\n";
        Out << totalUSD << " USD\n";
        Out << totalUSD * USDT_BRL << " BRL\n";
        Out << (totalUSD / BTC_USDT) << " BTC\n";
        Out << (totalUSD / SOL_USDT) << " SOL\n\n#####################\n\n";

        return(Out.str());
    }

    // Candle / Kline fetcher similarly: GET /api/v3/klines with symbol, interval, etc. This will be made in another class.


    // #################################################

    ysxCURL_BinanceAPIBalanceOps() { }
    ysxCURL_BinanceAPIBalanceOps(const std::string& SetKey, const std::string& SetSecret) { BinAPI.APIKey = SetKey; BinAPI.APISecret = SetSecret; }
    ysxCURL_BinanceAPIBalanceOps(const std::string& APIKeysFile) { BinAPI.GetKeySecretTxt(APIKeysFile); }
    //ysxCURL_BinanceAPIBalanceOps(ysxCURL_BinanceAPI BinanceAPIClass) { BinAPI = BinanceAPIClass; }

    ~ysxCURL_BinanceAPIBalanceOps()
    {
        if (BinAPI.CURLHandle) { curl_easy_cleanup(BinAPI.CURLHandle); BinAPI.CURLHandle = nullptr; }
        curl_global_cleanup();
    }
};


// #################################################
// #################################################
// #################################################


// This class deals with candles in all ways possible, it can gather candles, plot images of it, and also process indicators:
class ysxCURL_BinanceAPICandles
{
public:
    ysxCURL_BinanceAPI BinAPI;
    // You shouldn't edit this object, since functions overwrite it. However, this is the object you check after using a function:
    std::vector<ysxTRADE_Candle> Candles;
    std::vector<double> Prices, Volumes;
    std::vector<std::vector<double>> IndicatorsLine; // Indicators that are lines and usually plotted over the candles (ex.: MA and Bollinger)
    std::vector<std::vector<double>> IndicatorsIsolated; // Indicators that have their own drawings that does not match the graphs (ex.: RSI and MACD)


    // #################################################


    /* Get a vector of candles, it uses the class object 'Candles':
    Usage: Get 1000 candles of 5 minutes for SOLUSDT: '.GetCandles("SOLUSDT", "5m", 1000)'.
    Just use 'limit = 1' for a single candle, however, the API have a resquest for 'ticker'.
    CandlePriceType: 0 = Open; 1 = High; 2 = Low; 3 = Close; this will be the value inserted on the 'Prices' vector, the candles will have ALL values anyway if you need.*/
    bool GetCandles(const std::string& symbol, const std::string& interval, std::size_t limit, uint8_t CandlePriceType = 3)
    {
        std::string BaseURL = "https://api.binance.com";
        std::string Endpoint = "/api/v3/klines";
        std::string FullURL = BaseURL + Endpoint + "?symbol=" + symbol + "&interval=" + interval + "&limit=" + std::to_string(limit);
        if (!BinAPI.PerformRequest(FullURL)) { std::cerr << "Failed to fetch candles for " << symbol << " (" << interval << ")\n"; return(false); }
        curl_easy_reset(BinAPI.CURLHandle);

        try
        {
            nlohmann::json j = nlohmann::json::parse(BinAPI.Response);
            if (!j.is_array()) { std::cerr << "Unexpected JSON format for kline data.\n"; return(false); }
            std::vector<ysxTRADE_Candle> OutCandles;
            OutCandles.reserve(j.size());
            std::vector<double> PricesTmp, VolTmp;

            /* Return JSON:
             1 499040000000,     //  0 Open time
             "0.01634790",       //  1 Open
             "0.80000000",       //  2 High
             "0.01575800",       //  3 Low
             "0.01577100",       //  4 Close
             "148976.11427815",  //  5 Volume
             1499644799999,      //  6 Close time
             "2434.19055334",    //  7 Quote asset volume
             308,                //  8 Number of trades
             "1756.87402397",    //  9 Taker buy base asset volume
             "28.46694368",      // 10 Taker buy quote asset volume
             "17928899.62484339" // 11 Ignore
            */
            for (const auto& item : j)
            {
                ysxTRADE_Candle c;
                c.Open = std::stod(item[1].get<std::string>());
                c.High = std::stod(item[2].get<std::string>());
                c.Low = std::stod(item[3].get<std::string>());
                c.Close = std::stod(item[4].get<std::string>());
                c.Volume = std::stod(item[5].get<std::string>());
                OutCandles.push_back(c);
                VolTmp.push_back(c.Volume);
                switch (CandlePriceType)
                {
                    case 0:
                        PricesTmp.push_back(c.Open);
                        break;
                    case 1:
                        PricesTmp.push_back(c.High);
                        break;
                    case 2:
                        PricesTmp.push_back(c.Low);
                        break;
                    case 3:
                        PricesTmp.push_back(c.Close);
                        break;
                    default:
                        PricesTmp.push_back(c.Close);
                        break;
                }
            }
            Prices = PricesTmp;
            Volumes = VolTmp;
            Candles = OutCandles;
        }
        catch (const std::exception& e) { std::cerr << "JSON parse error in GetCandles(): " << e.what() << '\n'; return(false); }
        return(true);
    }


    // #################################################


    // Save binary file with candle information, so you can study / process a chart from a specific request:
    void CandlesSave(const std::string FileName = "Candles.sav")
    {
        std::ofstream O(FileName, std::ios::binary);
        if (!O.is_open()) { std::cerr << "Couldn't create file (" << FileName << ")!" << std::endl; }
        else
        {
            uint32_t Size = Candles.size(); O.write((char*)&Size, 4);
            for (size_t n = 0; n < Size; ++n) { O.write((char*)&Candles[n], sizeof(ysxTRADE_Candle)); }

        }
        O.close();
    }

    void CandlesLoad(const std::string FileName = "Candles.sav")
    {
        std::ifstream I(FileName, std::ios::binary);
        if (!I.is_open()) { std::cerr << "Couldn't open file (" << FileName << ")!" << std::endl; }
        else
        {
            uint32_t Size = 0; I.read((char*)&Size, 4);
            std::vector<ysxTRADE_Candle> Load;
            for (size_t n = 0; n < Size; ++n) { ysxTRADE_Candle c; I.read((char*)&c, sizeof(ysxTRADE_Candle)); Load.push_back(c); }
            Candles = Load;
        }
        I.close();
    }


    // #################################################

    ysxCURL_BinanceAPICandles() { }
    ysxCURL_BinanceAPICandles(const std::string& SetKey, const std::string& SetSecret) { BinAPI.APIKey = SetKey; BinAPI.APISecret = SetSecret; }
    ysxCURL_BinanceAPICandles(const std::string& APIKeysFile) { BinAPI.GetKeySecretTxt(APIKeysFile); }
    //ysxCURL_BinanceAPICandles(const ysxCURL_BinanceAPI& BinanceAPIClass) { BinAPI = BinanceAPIClass; }

    ~ysxCURL_BinanceAPICandles()
    {
        if (BinAPI.CURLHandle) { curl_easy_cleanup(BinAPI.CURLHandle); BinAPI.CURLHandle = nullptr; }
        curl_global_cleanup();
    }
};


// ###############################################################################################################################################################################

#endif

