#pragma once
#include <string>
#include <vector>

namespace util {
    std::string curlRequest(std::string url);   // Get data from online servers from given URL
    std::vector<std::vector<double>> calcData(std::vector<std::vector<int>>);   // Calculates the course data
}