#pragma once
#include <string>
#include <vector>

namespace util {
    // Get data from online servers from given URL
    std::string curlRequest(std::string url);

    // Calculates the course data
    std::vector<std::vector<double>> calcData(const std::vector<std::vector<double>>* courseData);
}