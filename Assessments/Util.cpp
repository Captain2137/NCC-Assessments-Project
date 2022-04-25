#include "Util.h"
#include <curl/curl.h>  // Needed for pulling data from online servers
#include <iostream>
#include <algorithm>
#include <cmath>

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
std::vector<std::vector<double>> util::calcData(std::vector<std::vector<double>> courseData) {
	
	/*
	// The number of competencies in the courses
	int compSize = (int)courseData[0].size();
	*/
	
	// The number of students in the course
	int classSize = (int)courseData.size();
	// The largest number of comps in a course
	int largestCompSize = 0;
	// Vector to hold the number of comps for each student
	std::vector<int> compSizes(classSize, 0);
	// 2D vector to hold the calculated data results
	std::vector<std::vector<double>> calcedData(4, std::vector<double>(0));

	// For all students in the course
	for (int i = 0; i < classSize; i++) {
		// The number of comps the current student has
		compSizes[i] = (int)courseData[i].size();
		// If the current student's course has more comps than the current largest number of comps
		if (compSizes[i] > largestCompSize) {
			// Set the largest number of comps to the current course's number of comps
			largestCompSize = compSizes[i];
		}
	}

	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(largestCompSize, std::vector<double>(0));

	// For all students in the course
	for (int i = 0; i < classSize; i++) {
		// For all comps in the current student's course
		for (int j = 0; j < compSizes[i]; j++) {
			// Add the current student's data for the current comp to the 2D vector
			compData[j].push_back(courseData[i][j]);
		}
	}

	/*
	// For all comps in the course
	for (int i = 0; i < compSize; i++) {
		// For all students in the comp
		for (int j = 0; j < classSize; j++) {
			// Add the current student's data for the current comp to the 2D vector
			compData[i].push_back(courseData[j][i]);
		}
	}*/

	/*
	// For all comps in the vector
	for (int i = 0; i < largestCompSize; i++) {
		// Add the average, median, percent above three, and standard deviation
		// for the current comp to the vector of calculated data
		calcedData[0].push_back(calcAvg(compData[i]));
		calcedData[1].push_back(calcMedian(compData[i]));
		calcedData[2].push_back(calcPercent(compData[i]));
		calcedData[3].push_back(calcDeviation(compData[i]));
	}*/

	// For all comps in the vector
	for (int i = 0; i < largestCompSize; i++) {
		int size = (int)compData[i].size();	// The number of scores in the vector
		double sumAvg = 0;	// The sum of the scores
		int middle = (int)compData[i].size() / 2;	// The middle score if odd number of scores
		int counter = 0;	// The number of scores that are 3 or higher
		double average = 0;	// The average of the scores
		double sumDev = 0;	// The sum of the squares of each deviation

		std::sort(compData[i].begin(), compData[i].end());	// Sort the scores in ascending order

		// For all scores in the vector
		for (int j = 0; j < size; j++) {
			// Add the current data to the sum
			sumAvg += compData[i][j];

			// If the score is 3 or higher
			if (compData[i][j] >= 3) {
				// Add 1 to the counter
				counter++;
			}
		}

		// Calculates the average
		average = sumAvg / size;
		// Add the current average to the vector of calced data
		calcedData[0].push_back(average);

		// For all scores in the vector
		for (int j = 0; j < size; j++) {
			// Calculate the deviation from the average,
			// square it, and add the result to the sum
			sumDev += pow((compData[i][j] - average), 2);
		}

		// If the number of scores is even
		if (middle % 2 == 0) {
			// Calculate the median score and add to the vector
			calcedData[1].push_back((compData[i][middle] + compData[i][middle - 1]) / 2);
		}

		// If the number of scores is odd
		else {
			// The middle score is the median score, add to the vector
			calcedData[1].push_back(compData[i][middle]);
		}

		// Calculate the percent of scores 3 or higher and add to the vector
		calcedData[2].push_back(counter * 100.0 / size);

		// Calculate the standard deviation and add to the vector
		calcedData[3].push_back(sqrt((double)sumDev / (size - 1)));
	}

	// Return the calced data
	return calcedData;
}

/*
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
}*/