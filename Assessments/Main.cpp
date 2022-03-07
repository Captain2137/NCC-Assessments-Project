/* Setup thanks to:
// https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-gui
//
// Convert String^ to String thanks to:
// https://stackoverflow.com/questions/946813/c-cli-converting-from-systemstring-to-stdstring
//
// Additional libraries added thanks to:
// https://docs.microsoft.com/en-us/cpp/build/adding-references-in-visual-cpp-projects?view=msvc-170
// https://vcpkg.io/en/getting-started.html
// 
// Curl thanks to: (Windows 64 bit binary)
// https://curl.se/download.html
//
// JSON thanks to:
// https://github.com/open-source-parsers/jsoncpp
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
#include <curl/curl.h>  // Needed for pulling data from online servers
#include <json/json.h>

// Needed for Windows Form
using namespace System;
using namespace System::Windows::Forms;

void debugPrint(const std::vector<int> courseNums, const std::string auth); // Debug test to print data to console
int readCSV(std::vector<CourseData>* courses, std::string fileName);    // Read in data from CSV file
void printCourseData(std::vector<CourseData>* courses); // Debug test to print course data to console
void testCurl(std::string auth);    // Test to see if curl works
void testJSON();    // Test to see if JSON works

[STAThread]

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::vector<int> courseNums;        // Vector array holding course numbers
        std::vector<CourseData> courses;    // Vector array holding course data for each course

        testCurl("");
        testJSON();

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

        std::getline(str, text, ',');       // Get first substring from line till ','
        course.setYear(std::stoi(text));    // Save as the year

        std::getline(str, text, ',');   // Get second substring from line till ','
        course.setSemester(text);       // Save as the semester

        std::getline(str, text, ',');   // Get third substring from line till ','
        course.setCode(text);           // Save as the code

        std::getline(str, text, ',');   // Get forth substring from line till ','
        course.setName(text);           // Save as the course name

        std::getline(str, text, ',');   // Get fith substring from line till ','
        course.setSection(text);        // Save as the section

        std::getline(str, text, ',');   // Get sixth substring from line till ','
        course.setProf(text);           // Save as the professors name

        std::getline(str, text, ',');           // Get last substring from line till ','
        course.setCourseNum(std::stoi(text));   // Save as the course number

        getline(file, line);            // Get second line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Get first substring from line till ','

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

        getline(file, line);            // Get third from last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        // Get the rest of the substrings in line and save them as medians
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addMedian(std::stoi(text));
        }

        getline(file, line);            // Get second from last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        // Get the rest of the substrings in line and save them as percents
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addPercent(std::stod(text));
        }

        getline(file, line);            // Get last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        // Get the rest of the substrings in line and save them as deviations
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addDeviation(std::stod(text));
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
        std::cout << courses->at(i).getYear() << " ";
        std::cout << courses->at(i).getSemester() << " ";
        std::cout << courses->at(i).getCode() << " ";
        std::cout << courses->at(i).getName() << " ";
        std::cout << courses->at(i).getSection() << " ";
        std::cout << courses->at(i).getProf() << " ";
        std::cout << courses->at(i).getCourseNum() << std::endl;

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

        // Print median contents to console
        for (int j = 0; j < (int)courses->at(i).getMedian()->size(); j++) {
            std::cout << courses->at(i).getMedian()->at(j) << " ";
        }
        std::cout << std::endl;

        // Print percent contents to console
        for (int j = 0; j < (int)courses->at(i).getPercent()->size(); j++) {
            std::cout << courses->at(i).getPercent()->at(j) << " ";
        }
        std::cout << std::endl;

        // Print deviation contents to console
        for (int j = 0; j < (int)courses->at(i).getDeviation()->size(); j++) {
            std::cout << courses->at(i).getDeviation()->at(j) << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

// Test to see if curl works
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Test to see if curl works
void testCurl(std::string auth) {
    std::string url = "https://https://canvas-prod.ccsnh.edu/api/v1/courses?access_token=" + auth;

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
}

void testJSON() {
    Json::Value root;
    std::ifstream ifs("withComment.json");

    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        return;
    }
    std::cout << root << std::endl;
}