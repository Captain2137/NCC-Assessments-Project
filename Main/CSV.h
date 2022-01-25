#pragma once

#include<string>
#include<vector>

class CSV
{
public:
    CSV();
    CSV(const CSV&);
    void tokenize(std::string);

    virtual ~CSV();
private:
    std::vector<std::vector<std::string>> tokenRows;
};