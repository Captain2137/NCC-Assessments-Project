#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include <iostream>

#include "Calculations.h"

// Calculates the average given a vector of doubles
double Calculations::calcAvg(std::vector<double>& scores)
{
	// The average score
	double avgScore = 0;
	// The number of scores in the vector
	int size = scores.size();
	// The sum of the scores
	double sum = 0;

	// For all scores in the vector
	for (int i = 0; i < size; i++)
	{
		sum += scores[i];
	}
	// Calculate the average score
	avgScore = sum / size;

	// Return the average score
	return avgScore;
}

// Calculates the median given a vector of doubles
double Calculations::calcMedian(std::vector<double>& scores) {
	// The median score
	double median = 0;
	// The number of scores in the vector
	int size = scores.size();
	// The middle score if odd number of scores
	int middle = floor(size / 2);
	// Sort the scores in ascending order
	std::sort(scores.begin(), scores.end());

	// If the number of scores is even
	if (middle % 2 == 0) {
		// Calculate the median score
		median = (scores[middle] + scores[middle - 1]) / 2.0;
	}
	// If the number of scores is odd
	else {
		// The middle score is the median score
		median = scores[middle];
	}

	// Return the median score
	return median;
}

// Calculates the number of scores tha are 3 or higher
// given a vector of doubles
double Calculations::calcPercentThree(std::vector<double>& scores) {
	// The percent of scores above 3
	double percentThree = 0;
	// The number of scores in the vector
	int size = scores.size();
	// The number of scores that are 3 or higher
	int counter = 0;

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		// If the score is 3 or higher
		if (scores[i] >= 3) {
			// Add the score to the counter
			counter++;
		}
	}
	// Calculate the percent of scores that are 
	// 3 or higher
	percentThree = counter * 100.0 / size;

	// Return the percent of scores that are 3 or higher
	return percentThree;
}

// Calculates the standard deviation given a vector
// of doubles
double Calculations::calcDeviation(std::vector<double>& scores) {
	// The standard deviation of the scores
	double deviation = 0;
	// The number of scores in the vector
	int size = scores.size();
	// Use the calcAvg function to get the average
	// of the scores
	Calculations c;
	double average = c.calcAvg(scores);
	// The sum of the squares of each deviation
	double sum = 0;

	// For all scores in the vector
	for (int i = 0; i < size; i++) {
		// Calculate the deviation from the average,
		// square it, and add the result to the sum
		sum += pow((scores[i] - average), 2);
	}
	// Calculate the standard deviation
	deviation = sqrt(sum * 1.0 / (size - 1));

	// Return the standard deviation
	return deviation;
}

/*
// Calculates the average in each competency 
// given a vector of CourseData
std::vector<double> Calculations::calcAvg(std::vector<CourseData>& courses)
{
	// The averages
	std::vector<double> averages = {};
	// The sum of the scores
	std::vector<double> sums = {};
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();

	// Inialize the sums and averages arrays to be 0s
	for (int i = 0; i < compSize; i++) {
		sums.push_back(0);
		averages.push_back(0);
	}

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++)
	{
		// The averages of the current course
		std::vector<double> courseAvgs = courses[i].copyAverage();
		// For all competencies in the course
		for (int j = 0; j < compSize; j++) {
			// Add the courses competency average to the sum
			sums[j] += courseAvgs[j];
		}
	}
	
	// For each comptenecy
	for (int i = 0; i < compSize; i++) {
		// Calculate the average of the competency
		averages[i] = sums[i] / courseSize;
	}
	
	// Return the average scores
	return averages;
}
*/

/*
// Calculates the median in each competency 
// given a vector of CourseData
std::vector<double> Calculations::calcAvg(std::vector<CourseData>& courses) {
	// The medians
	std::vector<double> averages = {};
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++) {
		// Copy the course data for the current course
		std::vector<std::vector<double>> courseData = courses[i].copyData();
		// The number of students in the current course
		int classSize = courseData.size();
		// For all comps in the vector
		for (int j = 0; j < compSize; j++) {
			// For all students in the comp
			for (int h = 0; h < classSize; h++) {
				// Add the current student's data for the current comp to the 2D vector
				compData[j].push_back(courseData[h][j]);
			}
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the median of the current comp with the calcMedian function
		double average = calcAvg(compData[i]);
		// Add the median to the vector of medians
		averages.push_back(average);
	}

	// Return the median scores
	return averages;
}

// Calculates the median in each competency 
// given a vector of CourseData
std::vector<double> Calculations::calcMedian(std::vector<CourseData>& courses) {
	// The medians
	std::vector<double> medians = {};
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++) {
		// Copy the course data for the current course
		std::vector<std::vector<double>> courseData = courses[i].copyData();
		// The number of students in the current course
		int classSize = courseData.size();
		// For all comps in the vector
		for (int j = 0; j < compSize; j++) {
			// For all students in the comp
			for (int h = 0; h < classSize; h++) {
				// Add the current student's data for the current comp to the 2D vector
				compData[j].push_back(courseData[h][j]);
			}
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the median of the current comp with the calcMedian function
		double median = calcMedian(compData[i]);
		// Add the median to the vector of medians
		medians.push_back(median);
	}

	// Return the median scores
	return medians;
}

// Calculates the percent above three in each competency 
// given a vector of CourseData
std::vector<double> Calculations::calcPercentThree(std::vector<CourseData>& courses) {
	// The percent of scores above 3
	std::vector<double> percentThrees = {};
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++) {
		// Copy the course data for the current course
		std::vector<std::vector<double>> courseData = courses[i].copyData();
		// The number of students in the current course
		int classSize = courseData.size();
		// For all comps in the vector
		for (int j = 0; j < compSize; j++) {
			// For all students in the comp
			for (int h = 0; h < classSize; h++) {
				// Add the current student's data for the current comp to the 2D vector
				compData[j].push_back(courseData[h][j]);
			}
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the percent above three of the current comp with the 
		// calcPercentThree function
		double percentThree = calcPercentThree(compData[i]);
		// Add the percentThree to the vector of percentThrees
		percentThrees.push_back(percentThree);
	}

	// Return the percents of scores that are 3 or higher
	return percentThrees;
}

// Calculates the standard deviations in each competency 
// given a vector of CourseData
std::vector<double> Calculations::calcDeviation(std::vector<CourseData>& courses) {
	// The standard deviations of the scores
	std::vector<double> deviations = {};
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++) {
		// Copy the course data for the current course
		std::vector<std::vector<double>> courseData = courses[i].copyData();
		// The number of students in the current course
		int classSize = courseData.size();
		// For all comps in the vector
		for (int j = 0; j < compSize; j++) {
			// For all students in the comp
			for (int h = 0; h < classSize; h++) {
				// Add the current student's data for the current comp to the 2D vector
				compData[j].push_back(courseData[h][j]);
			}
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the standard deviation of the current comp with the 
		// calcDeviation function
		double deviation = calcDeviation(compData[i]);
		// Add the deviation to the vector of deviations
		deviations.push_back(deviation);
	}

	// Return the standard deviations
	return deviations;
}
*/

// Calculates the averages, medians, percents above three, and 
// standard devations in each competency given a vector of CourseData
void Calculations::calcData(std::vector<CourseData>& courses, 
	std::vector<double>* averages, std::vector<double>* medians, 
	std::vector<double>* percentThrees, std::vector<double>* deviations) {
	// The number of courses in the vector
	int courseSize = courses.size();
	// The number of competencies in the courses
	int compSize = courses[0].getNumComps();
	// 2D vector to hold the data from all classes for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all courses in the vector
	for (int i = 0; i < courseSize; i++) {
		// Copy the course data for the current course
		std::vector<std::vector<double>> courseData = courses[i].copyData();
		// The number of students in the current course
		int classSize = courseData.size();
		// For all comps in the vector
		for (int j = 0; j < compSize; j++) {
			// For all students in the comp
			for (int h = 0; h < classSize; h++) {
				// Add the current student's data for the current comp to the 2D vector
				compData[j].push_back(courseData[h][j]);
			}
		}
	}

	// For all comps in the vector
	for (int i = 0; i < compSize; i++) {
		// Calculate the average, median, percent above three, and standard deviation,
		// for the current comp
		double average = calcAvg(compData[i]);
		double median = calcMedian(compData[i]);
		double percentThree = calcPercentThree(compData[i]);
		double deviation = calcDeviation(compData[i]);
		// Add the average, median, percent above three, and standard deviation
		// for the current comp to their respective vectors
		(*averages).push_back(average);
		(*medians).push_back(median);
		(*percentThrees).push_back(percentThree);
		(*deviations).push_back(deviation);
	}

	// End the function
	return;
}

// Calculates the averages, medians, percents above three, and 
// standard devations in each competency given a CourseData object
void Calculations::calcData(CourseData course, 
	std::vector<double>* averages, std::vector<double>* medians,
	std::vector<double>* percentThrees, std::vector<double>* deviations) {
	// The number of competencies in the courses
	int compSize = course.getNumComps();
	// Copy the course data for the course
	std::vector<std::vector<double>> courseData = course.copyData();
	// The number of students in the course
	int classSize = courseData.size();
	// 2D vector to hold the data from the class for each comp
	std::vector<std::vector<double>> compData(compSize, std::vector<double>(0));

	// For all comps in the course
	for (int i = 0; i < compSize; i++) {
		// For all students in the comp
		for (int j = 0; j < classSize; j++) {
			// Add the current student's data for the current comp to the 2D vector
			compData[i].push_back(courseData[j][i]);
		}
	}

	// For all comps in the course
	for (int i = 0; i < compSize; i++) {
		// Calculate the average, median, percent above three, and standard deviation,
		// for the current comp
		double average = calcAvg(compData[i]);
		double median = calcMedian(compData[i]);
		double percentThree = calcPercentThree(compData[i]);
		double deviation = calcDeviation(compData[i]);
		// Add the average, median, percent above three, and standard deviation
		// for the current comp to their respective vectors
		(*averages).push_back(average);
		(*medians).push_back(median);
		(*percentThrees).push_back(percentThree);
		(*deviations).push_back(deviation);
	}

	// End the function
	return;
}