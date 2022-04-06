#pragma once

#include <vector>

#include "CourseData.h"

// Class for computating the calculations of the data
namespace calculations
{
	double calcAvg(std::vector<double>&);								// Calculates the average of a vector of doubles
	double calcMedian(std::vector<double>&);							// Calculates the median of a vector of doubles
	double calcPercentThree(std::vector<double>&);						// Calculates the percent above three of a vector of doubles
	double calcDeviation(std::vector<double>&);							// Calculates the standard deviation of a vector of doubles
	std::vector<double> calcAvg(std::vector<CourseData>&);				// Calculates the average of a vector of CourseData
	std::vector<double> calcMedian(std::vector<CourseData>&);			// Calculates the median of a vector of CourseData
	std::vector<double> calcPercentThree(std::vector<CourseData>&);		// Calculates the percent above three of a vector of CourseData
	std::vector<double> calcDeviation(std::vector<CourseData>&);		// Calculates the standard deviation of a vector of CourseData
	void calcData(std::vector<CourseData>&,				// Calculates the average, 
		std::vector<double>*, std::vector<double>*,						// median, percent above three, 
		std::vector<double>*, std::vector<double>*);	// and standard deviation of a vector of CourseData
	void calcData(CourseData, std::vector<double>*, 
		std::vector<double>*, std::vector<double>*, 
		std::vector<double>*);							// Calculate the data for a single course
};