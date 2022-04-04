#pragma once
#include <string>

namespace curl {
    // Get data from online servers from given URL
    std::string request(std::string url);
}