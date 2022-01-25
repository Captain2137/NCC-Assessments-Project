#include "CSV.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<iterator>
#include<regex>
#include<boost/tokenizer.hpp>
#include<string>

CSV::CSV() {
}

CSV::CSV(const CSV& orig) {
}

void CSV::tokenize(std::string filename) {
	std::ifstream infile(filename);
	std::string line;
	while (getline(infile, line)) {
		std::cout << "line: " << line << std::endl;
		std::vector<std::string> row;
		if (line.length() > 0) {
			boost::tokenizer<boost::escaped_list_separator<char> > tok(line);
			int tokenNumber = 0;
			for (boost::tokenizer<boost::escaped_list_separator<char>>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
				row.push_back(*beg);
				if ((*beg).length() > 0) {
					std::cout << tokenNumber << ": " << *beg << std::endl;
				}
				tokenNumber++;
			    std::cout << std::endl;
			}
			tokenRows.push_back(row);
		}
	}
}

CSV::~CSV() {
}

