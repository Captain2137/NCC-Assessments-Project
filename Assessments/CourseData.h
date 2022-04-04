#pragma once
#include <string>
#include <vector>

// Holds all the data for a course
class CourseData {
public:
    int courseNum;                      // Course number
    int year;                           // Year
    std::string semester;               // Semester
    std::string code;                   // Code ex. CSCI
    std::string name;                   // Name of course
    std::string section;                // Section
    std::string prof;                   // Professors name
    std::vector<std::string> comps;     // Courses competencies
    std::vector<std::vector<int>> data; // 2D vector to store student data
    std::vector<double> average;        // Averages in each competency
    std::vector<int> median;            // Medians in each competency
    std::vector<double> percent;        // Percent passed in each competency
    std::vector<double> deviation;      // Deviation in each competency

    void setCourseNum(int courseNumIn) { courseNum = courseNumIn; }             // Sets course number
    void setYear(int yearIn) { year = yearIn; }                                 // Sets year
    void setSemester(std::string semesterIn) { semester = semesterIn; }         // Sets semester
    void setCode(std::string codeIn) { code = codeIn; }                         // Sets code
    void setName(std::string nameIn) { name = nameIn; }                         // Sets course name
    void setSection(std::string sectionIn) { section = sectionIn; }             // Sets section
    void setProf(std::string profIn) { prof = profIn; }                         // Sets professors name
    void addComps(std::string compsIn) { comps.push_back(compsIn); }            // Adds a competency
    void addData(std::vector<int> dataIn) { data.push_back(dataIn); }           // Adds new student data
    void addAverage(double averageIn) { average.push_back(averageIn); }         // Adds a average
    void addMedian(int medianIn) { median.push_back(medianIn); }                // Adds a median
    void addPercent(double percentIn) { percent.push_back(percentIn); }         // Adds a percent
    void addDeviation(double deviationIn) { deviation.push_back(deviationIn); } // Adds a deviation

    void calculate();   // Calculate average, median, percent, and deviation from data

    int getCourseNum() { return courseNum; }                    // Returns course number
    int getYear() { return year; }                              // Returns year
    std::string getSemester() { return semester; }              // Returns semester
    std::string getCode() { return code; }                      // Returns code
    std::string getName() { return name; }                      // Returns course name
    std::string getSection() { return section; }                // Returns section
    std::string getProf() { return prof; }                      // Returns professors name
    std::vector<std::string>* getComps() { return &comps; }     // Returns competencies
    std::vector<std::vector<int>>* getData() { return &data; }  // Returns data
    std::vector<double>* getAverage() { return &average; }      // Returns averages
    std::vector<int>* getMedian() { return &median; }           // Returns medians
    std::vector<double>* getPercent() { return &percent; }      // Returns percents
    std::vector<double>* getDeviation() { return &deviation; }  // Returns deviations
};