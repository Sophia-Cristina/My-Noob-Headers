#pragma once

#ifndef YSXCURL_H
#define YSXCURL_H

#include "curl.h"

// #####################
// ####### By Sophia Cristina
// ####### For CURL lib usage.
// #####################

// #################################################
// REFERENCES:
// #################################################

// This callback returns the website data to a 'std::string':
size_t ysxCURL_WriteToStringCallback(char* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append(ptr, size * nmemb);
    return(size * nmemb);
}


class ysxCURL_HTTP
{
private:

public:
    CURL* curl = nullptr;
    std::string ReadBuffer;

    enum FlgAdrs { fWtostring = 1 };
    /*0000 0000
             |+- Write to 'GetData';
	     +--  
    */
    uint8_t Flags = 0;

    /*GET HTTP/S REQUEST:
    Returns:
     0: Exited successfully and nothing in special;
    -1: if 'res != CURLE_OK';
    -2: Clean 'CURL*' pointer. 'CURL*' should be 'nullptr'.*/
    /*int GetRequest(std::string URL)
    {
		curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, URL.data());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirects if needed

            if (Flags & fWtostring)
	    {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ysxCURL_WriteToStringCallback);
	        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ReadBuffer);
	    }

            CURLcode Result = curl_easy_perform(curl); // The result of a CURL easy handle transfer

            if (Result != CURLE_OK)
            {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(Result) << std::endl;
	        curl_easy_cleanup(curl);		
		return(-1);
            }
        }
	curl_easy_cleanup(curl);
	return(0);
    }

    // GET THE CURL POINTER, BUT YOU MANAGE IT BY YOURSELF:
    int GetRequestCURL(std::string URL)
	{
		if (!curl)
		{
		    curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, URL.data());
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirects if needed

                if (Flags & fWtostring)
	    	    {
				    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ysxCURL_WriteToStringCallback);
		            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ReadBuffer);
		        }

                CURLcode Result = curl_easy_perform(curl); // The result of a CURL easy handle transfer

                if (Result != CURLE_OK)
                {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(Result) << std::endl;
	            	curl_easy_cleanup(curl);		
		    	 	return(-1);
    	        }
    		}
	   	 	curl_easy_cleanup(curl);
		}
	return(0);
    }*/

    // #####################
    ysxCURL_HTTP()
    {
    }
    ~ysxCURL_HTTP()
    {
    }
    // #####################
};

// ###############################################################################################################################################################################

#endif
