/* Setup thanks to:
// https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-gui
//
// Convert String^ to String thanks to:
// https://stackoverflow.com/questions/946813/c-cli-converting-from-systemstring-to-stdstring
*/

#include "UIForm.h"
#include "VisualizationForm.h"
#include "CommandLine.h"
#include "CourseData.h"
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>  // Needed for stringstream
//#include <curl/curl.h>  // Needed for pulling data from online servers

// Needed for Windows Form
using namespace System;
using namespace System::Windows::Forms;

void debugPrint(const std::vector<int> courseNums, const std::string auth); // Debug test to print data to console
int readCSV(std::vector<CourseData>* courses, std::string fileName);    // Read in data from CSV file
void printCourseData(std::vector<CourseData>* courses); // Debug test to print course data to console
void testCurl(std::string auth);    // Test to see if curl works

[STAThread]

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::vector<int> courseNums;        // Vector array holding course numbers
        std::vector<CourseData> courses;    // Vector array holding course data for each course

        // Read in test CSV
        if (readCSV(&courses, "2022-Spring-CSCI285N-63925-A-Betsy Gamrat.csv") == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }

        // Set Windows Form Styles
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);

        // Define UI form sending course vector address
        Assessments::UIForm ui(&courseNums);
        Application::Run(% ui); // Run UI form

        // Get authorization key from ui and convert it from String^ to String
        std::string auth = msclr::interop::marshal_as< std::string >(ui.getAuth());

        // Go through courses vector and create CourseData class for each
        for (int i = 0; i < (int)courseNums.size(); i++) {
            courses.push_back(CourseData());
            courses.back().setCourseNum(courseNums[i]);
        }

        // Debug: Prints auth and course numbers to console with course data
        debugPrint(courseNums, auth);
        printCourseData(&courses);

        // Define Visualization form sending course vector address
        Assessments::VisualizationForm visualization(&courses);
        Application::Run(% visualization);  // Run Visualization form
    } else {
        // If arguments given, then use command line
        return Main::CommandLine(argc, argv);
    }
}

// Read in data from CSV file
int readCSV(std::vector<CourseData>* courses, std::string fileName) {
    try {
        std::ifstream file(fileName);   // Open file

        // Throws errors if reading of file failed
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

        CourseData course;          // Create course data to store data
        std::vector<int> row;       // Temp to hold row for 2D vector
        std::string line, text;     // Current line and substring in line

        getline(file, line);            // Get first line from file
        std::stringstream str(line);    // Get line ready for string segmentation
        std::getline(str, text, ',');   // Get first substring from line till ','
        course.setProf(text);           // Save as the professors name

        // Get the rest of the substrings in line and save them as competencies
        while (std::getline(str, text, ',')) {  // Keeps looping till end of list string
            course.addComps(text);
        }

        getline(file, line);            // Get second line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Get first substring from line till ','

        // Keeps reading if line starts with students #
        while (text.find("Student") != std::string::npos) { // End if none found
            row.clear();    // Empty old row

            // Get the rest of the substrings in line and save them in data
            while (std::getline(str, text, ',')) {  // Keeps looping till end of string
                row.push_back(std::stoi(text));     // Add data to row temporarily
            }
            course.addData(row);    // Add row to data

            getline(file, line);            // Get next line from file
            str.clear();                    // Reset stringstream
            str.str(line);                  // Get line ready for string segmentation
            std::getline(str, text, ',');   // Get first substring from line till ','
        }

        // Get the rest of the substrings in line and save them as averages
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addAverage(std::stod(text));
        }

        getline(file, line);            // Get last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        // Get the rest of the substrings in line and save them as percents
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addPercent(std::stod(text));
        }

        // Close file when done
        file.close();

        // Add course to the list of courses if successfully read
        courses->push_back(course);
    } catch (const std::ios_base::failure& e) {
        // If error happends while opeing file
        std::cout << "Error: " << e.what() << ", reading of file failed\n";
        return EXIT_FAILURE;
    } catch (const std::invalid_argument& e) {
        // If error happends while reading file
        std::cout << "Error: " << e.what() << ", file not compatible\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        // If another error happends
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        // If error unknown happends
        std::cout << "Error: Unknown\n";
        return EXIT_FAILURE;
    }

    //Debug: Prints course data to comsole
    printCourseData(courses);

    return 0;
}

// Debug test to print course numbers and authorization key to console
void debugPrint(const std::vector<int> courseNums, const std::string auth) {
    // Prints auth and course numbers to console
    std::cout << "Debug: Courses\n";
    std::cout << "Auth key: " << auth << std::endl;
    std::cout << "Courses: ";

    // Go through courses vector and print contents to console
    for (unsigned int i = 0; i < courseNums.size(); i++) {
        std::cout << courseNums[i] << ", ";
    }
    std::cout << std::endl << std::endl;
}

// Debug test to print course data to console
void printCourseData(std::vector<CourseData>* courses) {
    std::cout << "Debug: CourseData\n";
    for (int i = 0; i < (int)courses->size(); i++) {
        std::cout << "Course: " << courses->at(i).getCourseNum() << std::endl;

        // Print comps contents to console
        for (int j = 0; j < (int)courses->at(i).getComps()->size(); j++) {
            std::cout << courses->at(i).getComps()->at(j) << ", ";
        }
        std::cout << std::endl;

        // Print data contents to console
        for (int j = 0; j < (int)courses->at(i).getData()->size(); j++) {
            for (int k = 0; k < (int)courses->at(i).getData()->at(j).size(); k++) {
                std::cout << courses->at(i).getData()->at(j).at(k) << " ";
            }
            std::cout << std::endl;
        }

        // Print average contents to console
        for (int j = 0; j < (int)courses->at(i).getAverage()->size(); j++) {
            std::cout << courses->at(i).getAverage()->at(j) << " ";
        }
        std::cout << std::endl;

        // Print percent contents to console
        for (int j = 0; j < (int)courses->at(i).getPercent()->size(); j++) {
            std::cout << courses->at(i).getPercent()->at(j) << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

// Test to see if curl works
void testCurl(std::string auth) {
    std::string url = "https://https://canvas-prod.ccsnh.edu/api/v1/courses?access_token=" + auth;

    //CURL* curl;
    //curl = curl_easy_init();
    //curl_easy_cleanup(curl);
}
