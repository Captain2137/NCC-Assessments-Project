#include "Curl.h"
#include <curl/curl.h>  // Needed for pulling data from online servers
#include <iostream>

using namespace curl;

// Saves data fetched by curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Get data from online servers from given URL
std::string curl::request(std::string url) {
    CURL* curl;             // Start curl
    CURLcode res;           // To store curl result code
    int httpCode = 0;       // To store HTTP code
    std::string readBuffer; // To store received data

    curl = curl_easy_init();    // Initialise curl

    if (curl) { // If initialisation successful
        //std::cout << "Debug: Curl\n";
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); // Print debug info

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Don't verify certificate
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());   // Set URL
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);   // Set callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Save received data to readBuffer string

        res = curl_easy_perform(curl);  // Run curl and save result code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode); // Get HTTP code
        curl_easy_cleanup(curl);    // Clear up curl

        // Debug: Print HTTP code, curl result, readBuffer contents
        std::cout << "HTTP Code: " << httpCode << ", Curl result: " << curl_easy_strerror(res) << std::endl;

        return readBuffer;
    } else {    // If initialisation failed
        std::cout << "Error: Curl initialisation failed\n\n";
        return "";
    }
}