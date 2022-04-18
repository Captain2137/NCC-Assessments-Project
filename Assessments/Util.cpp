#include "Util.h"
#include <curl/curl.h>  // Needed for pulling data from online servers
#include <iostream>
#include <algorithm>
#include <cmath>

double calcAvg(std::vector<int> scores);		// Calculates the average of a vector of doubles
double calcMedian(std::vector<int> scores);		// Calculates the median of a vector of doubles
double calcPercent(std::vector<int> scores);    // Calculates the percent above three of a vector of doubles
double calcDeviation(std::vector<int> scores);  // Calculates the standard deviation of a vector of doubles

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

// Calculates the averages, medians, percents above three, and 
// standard devations in each competency given a 2D vector of courses data
std::vector<std::vector<double>> util::calcData(std::vector<std::vector<int>> courseData) {
	// The number of competencies in the courses
	int compSize = (int)courseData[0].size();
	// The number of students in the course
	int classSize = (int)courseData.size();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<int>> compData(compSize, std::vector<int>(0));
	// 2D vector to hold the calculated data results
	std::vector<std::vector<double>> calcedData(4, std::vector<double>(0));

	// For all comps in the course
	for (int i = 0; i < compSize; i++) {
		// For all students in the comp
		for (int j = 0; j < classSize; j++) {
			// Add the current student's data for the current comp to the 2D vector
			compData[i].push_back(courseData[j][i]);
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the average, median, percent above three, and standard deviation,
		// for the current comp
		double average = calcAvg(compData[i]);
		double median = calcMedian(compData[i]);
		double percentThree = calcPercent(compData[i]);
		double deviation = calcDeviation(compData[i]);
		// Add the average, median, percent above three, and standard deviation
		// for the current comp to the vector of calculated data
		calcedData[0].push_back(average);
		calcedData[1].push_back(median);
		calcedData[2].push_back(percentThree);
		calcedData[3].push_back(deviation);
	}

	// Return the calced data
	return calcedData;
}

// Calculates the average given a vector of doubles
double calcAvg(std::vector<int> scores) {
	int size = (int)scores.size();	// The number of scores in the vector
	double sum = 0;					// The sum of the scores

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		sum += scores[i];
	}

	// Calculate and return the average score
	return sum / size;
}

// Calculates the median given a vector of doubles
double calcMedian(std::vector<int> scores) {
	int middle = (int)scores.size() / 2;		// The middle score if odd number of scores
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
double calcPercent(std::vector<int> scores) {
	int size = (int)scores.size();	// The number of scores in the vector
	int counter = 0;				// The number of scores that are 3 or higher

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
double calcDeviation(std::vector<int> scores) {
	int size = (int)scores.size();		// The number of scores in the vector
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