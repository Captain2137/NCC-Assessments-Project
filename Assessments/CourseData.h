#pragma once
#include <string>
#include <vector>

// Holds all the data for a course
class CourseData {
public:
    int courseNum;                          // Course number
    std::string name;                       // Name of course
    std::string prof;                       // Professor's name
    std::vector<std::string> comps;         // Courses competencies
    std::vector<double> mastery;            // Points to get mastery in competency
    std::vector<std::vector<double>> data;  // 2D vector to store student data
    std::vector<double> average;            // Averages in each competency
    std::vector<double> median;             // Medians in each competency
    std::vector<double> percent;            // Percent passed in each competency
    std::vector<double> deviation;          // Deviation in each competency

    void calculate();   // Calculate average, median, median, and deviation for course

    void setCourseNum(int courseNumIn) { courseNum = courseNumIn; }             // Sets course number
    void setName(std::string nameIn) { name = nameIn; }                         // Sets course name
    void setProf(std::string profIn) { prof = profIn; }                         // Sets professors name
    void addComps(std::string compsIn) { comps.push_back(compsIn); }            // Adds a competency
    void addMastery(double masteryIn) { mastery.push_back(masteryIn); }         // Adds a mastery
    void addData(std::vector<double> dataIn) { data.push_back(dataIn); }        // Adds new student data
    void addAverage(double averageIn) { average.push_back(averageIn); }         // Adds a average
    void addMedian(double medianIn) { median.push_back(medianIn); }             // Adds a median
    void addPercent(double percentIn) { percent.push_back(percentIn); }         // Adds a percent
    void addDeviation(double deviationIn) { deviation.push_back(deviationIn); } // Adds a deviation
};