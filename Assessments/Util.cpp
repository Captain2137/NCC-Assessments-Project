#include "Util.h"
#include <curl/curl.h>  // Needed for pulling data from online servers
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace util;

// Saves data fetched by curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Get data from online servers from given URL
std::string util::curlRequest(std::string url) {
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

std::vector<std::vector<double>> util::calc(std::vector<std::vector<int>> data) {
	int size;
	int sum;
	std::vector<int> temp;
	std::vector<std::vector<double>> results;

	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.at(i).size(); j++) {

		}
	}

	return results;
}

// Calculates the average given a vector of doubles
double util::calcAvg(std::vector<int> scores) {
	int size = scores.size();	// The number of scores in the vector
	double sum = 0;				// The sum of the scores

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		sum += scores[i];
		std::cout << scores[i] << " ";
	}

	std::cout << "  Sum: " << sum << "   Size: " << size << std::endl << std::endl;

	// Calculate and return the average score
	return sum / size;
}

// Calculates the median given a vector of doubles
double util::calcMedian(std::vector<int> scores) {
	int middle = scores.size() / 2;				// The middle score if odd number of scores
	std::sort(scores.begin(), scores.end());	// Sort the scores in ascending order

	// If the number of scores is even
	if (middle % 2 == 0) {
		// Calculate the median score
		return (scores[middle] + scores[middle - 1]) / 2.0;
	}

	// If the number of scores is odd
	else {
		// The middle score is the median score
		return scores[middle];
	}
}

// Calculates the number of scores tha are 3 or higher given a vector of doubles
double util::calcPercent(std::vector<int> scores) {
	int size = scores.size();	// The number of scores in the vector
	int counter = 0;			// The number of scores that are 3 or higher

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		// If the score is 3 or higher
		if (scores[i] >= 3) {
			// Add the score to the counter
			counter++;
		}
	}
	// Calculate and return the percent of scores that are 3 or higher
	return counter * 100.0 / size;
}

// Calculates the standard deviation given a vector of doubles
double util::calcDeviation(std::vector<int> scores) {
	int size = scores.size();			// The number of scores in the vector
	double average = calcAvg(scores);	// Use the calcAvg function to get the average of the scores
	double sum = 0;						// The sum of the squares of each deviation

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		// Calculate the deviation from the average,
		// square it, and add the result to the sum
		sum += pow((scores[i] - average), 2);
	}

	// Calculate and return the standard deviation
	return sqrt((double)sum / (size - 1));
}