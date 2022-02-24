#pragma once
#include <string>
#include <vector>

// Holds all the data for a course
class CourseData {
public:
    int courseNum;                      // Course number
    std::string prof;                   // Professors name
    std::vector<std::string> comps;     // Courses competencies
    std::vector<std::vector<int>> data; // 2D vector to store student data
    std::vector<double> average;        // Averages in each competency
    std::vector<double> percent;        // Percent passed in each competency

    CourseData() {};    // Default constructor

    void setCourseNum(int courseNumIn) { courseNum = courseNumIn; }     // Sets course number
    void setProf(std::string profIn) { prof = profIn; }                 // Sets professors name
    void addComps(std::string compsIn) { comps.push_back(compsIn); }    // Adds a competency
    void addData(std::vector<int> dataIn) { data.push_back(dataIn); }   // Adds new student data
    void addAverage(double averageIn) { average.push_back(averageIn); } // Adds a average
    void addPercent(double percentIn) { percent.push_back(percentIn); } // Adds a percent

    int getCourseNum() { return courseNum; }                    // Returns course number
    std::string getProf() { return prof; }                      // Returns professors name
    std::vector<std::string>* getComps() { return &comps; }     // Returns competencies
    std::vector<std::vector<int>>* getData() { return &data; }  // Returns data
    std::vector<double>* getAverage() { return &average; }      // Returns averages
    std::vector<double>* getPercent() { return &percent; }      // Returns percents
};