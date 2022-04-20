#pragma once
#include <string>
#include <vector>

namespace util {
    std::string curlRequest(std::string url);   // Get data from online servers from given URL
    std::vector<std::vector<double>> calcData(std::vector<std::vector<int>>);   // Calculates the course data

    /*
    double calcAvg(std::vector<int>);		// Calculates the average of a vector of doubles
    double calcMedian(std::vector<int>);    // Calculates the median of a vector of doubles
    double calcPercent(std::vector<int>);    // Calculates the percent above three of a vector of doubles
    double calcDeviation(std::vector<int>);  // Calculates the standard deviation of a vector of doubles
    */
}