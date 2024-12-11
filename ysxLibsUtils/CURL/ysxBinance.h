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
// #################################################

#define BIN_API_TIMESTMP std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define BIN_API_WS "wss://ws-api.binance.com:443/ws-api/v3"
#define BIN_API_WSTEST "wss://testnet.binance.vision/ws-api/v3i"

// #################################################
// FUNCTIONS:
// #################################################

// MODIFY TO SOMETHING RELEVANT IF NEEDED.
// This callback returns the website data to a 'std::string':
//size_t ysxCURL_WriteToStringCallback(char* ptr, size_t size, size_t nmemb, std::string* data)
//{
//    data->append(ptr, size * nmemb);
//    return(size * nmemb);
//}


// #################################################
// CLASSES:
// #################################################

class ysxCURL_BinanceAPI
{
private:
    std::string URL = "";

public:
    //CURL* curl = nullptr;
    std::string Response;
    const std::string BaseURL = "https://api.binance.com/api/v3";
    const std::string EndPoint = "/account";
	std::string APIKey;
    std::string APISec;
	std::string APIFile;
	//ysxCRYPT_HMACSHA256 HMACSHA256(APISec);

	// ############################
	// ####### UTILS #######
	// ############################

	// Open 'FileName.txt' and get API key and secret:
    void GetKeySecretTxt(const std::string& FileName)
    {
        std::ifstream File(FileName);
        if (File.is_open())
        {
            std::getline(File, APIKey);
            std::getline(File, APISec);
            File.close();
        }
        else
        {
            std::cerr << "Could not find a file called '" << FileName << "'!" << std::endl;
        }
    }

	// Get HMACSHA256 signature:
	//std::string GetHMACSHA256Sig(std::string )
	//{
		//std::string Sig = HMACSHA256.GetHash("timestamp=" + std::to_string(BIN_API_TIMESTMP));
		//return(Sig);
	//}

	// ############################
	// ####### TRADE DATA #######
	// ############################

	// ####### CANDLES:

std::string CandleParse(const std::string Data)
{

}

std::string CandleGetData(CURL* curl, const std::string& Symbol, const std::string Interval)
{
    //URL = https://api.binance.com/api/v3/klines?symbol=+Symbol+&interval=5m&limit=1";
    URL = BaseURL + "/klines?symbol=" + Symbol + "&interval=" + Interval + "&limit=1";
    //URL = BaseURL + "/klines?symbol=SOLUSDT&interval=5m&limit=1";
    
	if (curl) { curl_easy_cleanup(curl); }
        AccessAPI(curl, 7);

	// #######

        // Parse the response and extract the required values
        // Assuming the response is in JSON format
        // You might need to use a JSON library or a custom JSON parser for more complex parsing
        
        // Here's an example of how you can extract the required values using simple string manipulation
        
	//std::cout <<"RESPONSE:\n\n" << Response << "\n\n";
	
	// W.I.P
	std::string Data = "####### " + Symbol + " | " + Interval + " | BINANCE #######\n" + CandleParse(Response) + '\n';

        // Find the opening price
        size_t start = Response.find('[', 0) + 2;
        size_t end = Response.find(',', start);
	Data += "Open: " + Response.substr(start, end - start) + '\n';
        
        // Find the high price
        start = end + 2;
        end = Response.find(',', start) - 1;
	Data += "High: " + Response.substr(start, end - start) + '\n';
        
        // Find the low price
        start = end + 3;
        end = Response.find(',', start) - 1;
	Data += "Low: " + Response.substr(start, end - start) + '\n';
        
        // Find the current price
        start = end + 3;
        end = Response.find(',', start) - 1;
        Data += "Current: " + Response.substr(start, end - start) + '\n';

	Data += "####### ####### ####### ####### ####### ####### #######\n\n";

	return(Data);
}

	// ####### API MAIN FUNCTION #######

    int AccessAPI(CURL* curl, uint8_t Flags)
    {
        if (!curl)
        {
            CURLcode Res;
            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();

            curl_easy_setopt(curl, CURLOPT_URL, URL.data());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ysxCURL_WriteToStringCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &Response);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);

            Res = curl_easy_perform(curl);

            if (Res != CURLE_OK)
            {
                std::cerr << "Error: " << curl_easy_strerror(Res) << "\nif Return=='-1' then 'Res!=CURLE_OK'." << std::endl;
                return -1;
            }
            else
            {
                Response = "####### RESPONSE BEG #######\n\n" + Response + "\n\n####### RESPONSE END #######\n\n";
                curl_easy_cleanup(curl);
            }

            curl_global_cleanup();
            URL = "";
            return 0;
        }
        else
        {
            URL = "";
            std::cout << "if Return='-2' then 'return'. To avoid leaking, 'curl' should be 'nullptr'." << std::endl;
            return -2;
        }
    }

    ysxCURL_BinanceAPI(std::string FileAPIdotTxt, bool CoutKeyAndSecret)
    {
	APIFile = FileAPIdotTxt;
        GetKeySecretTxt(APIFile);
        if (CoutKeyAndSecret)
        {
            std::cout << "API Key: " << APIKey << std::endl;
            std::cout << "API Secret: " << APISec << std::endl;
        }
    }
    ~ysxCURL_BinanceAPI() {}
};


// ###############################################################################################################################################################################

#endif
