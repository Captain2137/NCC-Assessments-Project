#pragma once
#include <string>
#include <vector>

// this is a comet

// Holds all the data for a course
class CourseData {
public:
    int courseNum;                      // Course number
    int year;                           // Year
    std::string semester;               // Semester
    std::string code;                   // Code ex. CSCI
    std::string name;                   // Name of course
    std::string section;                // Section
    std::string prof;                   // Professor's name
    std::vector<std::string> comps;     // Courses competencies
    std::vector<int> mastery;           // Points to get mastery in competency
    std::vector<std::vector<int>> data; // 2D vector to store student data
    std::vector<double> average;        // Averages in each competency
    std::vector<double> median;         // Medians in each competency
    std::vector<double> percent;        // Percent passed in each competency
    std::vector<double> deviation;      // Deviation in each competency

    void calculate();   // Calculate average, median, median, and deviation for course

    void setCourseNum(int courseNumIn) { courseNum = courseNumIn; }             // Sets course number
    void setYear(int yearIn) { year = yearIn; }                                 // Sets year
    void setSemester(std::string semesterIn) { semester = semesterIn; }         // Sets semester
    void setCode(std::string codeIn) { code = codeIn; }                         // Sets code
    void setName(std::string nameIn) { name = nameIn; }                         // Sets course name
    void setSection(std::string sectionIn) { section = sectionIn; }             // Sets section
    void setProf(std::string profIn) { prof = profIn; }                         // Sets professors name
    void addComps(std::string compsIn) { comps.push_back(compsIn); }            // Adds a competency
    void addMastery(int masteryIn) { mastery.push_back(masteryIn); }            // Adds a mastery
    void addData(std::vector<int> dataIn) { data.push_back(dataIn); }           // Adds new student data
    void addAverage(double averageIn) { average.push_back(averageIn); }         // Adds a average
    void addMedian(double medianIn) { median.push_back(medianIn); }             // Adds a median
    void addPercent(double percentIn) { percent.push_back(percentIn); }         // Adds a percent
    void addDeviation(double deviationIn) { deviation.push_back(deviationIn); } // Adds a deviation

    const int* getCourseNum() { return &courseNum; }                    // Returns course number by reference
    const int* getYear() { return &year; }                              // Returns year by reference
    const std::string* getSemester() { return &semester; }              // Returns semester by reference
    const std::string* getCode() { return &code; }                      // Returns code by reference
    const std::string* getName() { return &name; }                      // Returns course name by reference
    const std::string* getSection() { return &section; }                // Returns section by reference
    const std::string* getProf() { return &prof; }                      // Returns professors name by reference
    const std::vector<std::string>* getComps() { return &comps; }       // Returns competencies by reference
    const std::vector<int>* getMastery() { return &mastery; }           // Returns masteries by reference
    const std::vector<std::vector<int>>* getData() { return &data; }    // Returns data by reference
    const std::vector<double>* getAverage() { return &average; }        // Returns averages by reference
    const std::vector<double>* getMedian() { return &median; }          // Returns medians by reference
    const std::vector<double>* getPercent() { return &percent; }        // Returns percents by reference
    const std::vector<double>* getDeviation() { return &deviation; }    // Returns deviations by reference
};