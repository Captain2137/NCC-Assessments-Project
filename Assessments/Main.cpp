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
// https://github.com/nlohmann/json
//
// Chart Graphics thanks to: (C++ Windows 64 bit)
// https://www.advsofteng.com/download.html
*/

#include "UIForm.h"
#include "UISelectCourses.h"
#include "CourseData.h"
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>                    // Needed to get the date
#include <filesystem>               // Needed to make dir
#include <sstream>                  // Needed for stringstream
#include <nlohmann/json.hpp>        // Needed to read data fetched from online servers
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <chartdirector/chartdir.h> // Needed for graphing library

// Needed for Windows Form
using namespace System;
using namespace System::Windows::Forms;

// Read in data from CSV file
int readCSV(std::vector<CourseData>* courses, const std::string fileName);

// Get course data from online servers
void getData(const std::vector<int>* courseNums, const std::vector<std::string>* courseNames,
    const std::vector<std::string>* courseProfs, std::vector<CourseData>* courses, const std::string* auth);

// Save data as .csv files
int saveData(const std::vector<CourseData>* courses);

// Debug test to print data to console
void debugPrint(const std::vector<int>* accountIds, const std::vector<CourseData>* courses,
    const std::string* auth);

[STAThread]

int main() {
    std::vector<int> accountIds;            // Vector array holding account ids
    std::vector<int> courseNums;            // Vector array holding course numbers
    std::vector<std::string> courseNames;   // Vector array holding course names
    std::vector<std::string> courseProfs;   // Vector array holding course professor names
    std::vector<CourseData> courses;        // Vector array holding course data for each course
    std::string auth;                       // String holding authorization key

    // Set Windows Form Styles
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Define UI form and send course numbers vector address
    Assessments::UIForm ui(&accountIds, &auth);
    Application::Run(% ui); // Run UI form

    // Define select form and send course numbers vector address
    Assessments::UISelectCourses select(&accountIds, &auth, &courseNums, &courseNames, &courseProfs);
    Application::Run(% select); // Run select form

    // Get course data from online servers
    getData(&courseNums, &courseNames, &courseProfs, &courses, &auth);

    // Debug: Prints auth and course numbers to console with course data
    debugPrint(&accountIds, &courses, &auth);

    // Save data as .csv's
    if (saveData(&courses))
        return EXIT_FAILURE;

    // Visualization graphics here

}

// Read in data from CSV file
int readCSV(std::vector<CourseData>* courses, const std::string fileName) {
    try {
        std::ifstream file(fileName);   // Open file

        // Throws errors if reading of file failed
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

        CourseData course;                      // Create course data to store data
        std::vector<double> row;                // Temp to hold row for 2D vector
        std::string line, text;                 // Current line and substring in line

        getline(file, line);                    // Get first line from file
        std::stringstream str(line);            // Get line ready for string segmentation

        std::getline(str, text, ',');           // Get first substring from line till ','
        course.setName(text);                   // Save as the course name

        std::getline(str, text, ',');           // Get second substring from line till ','
        course.setProf(text);                   // Save as the professors name

        std::getline(str, text, ',');           // Get last substring from line till ','
        course.setCourseNum(std::stoi(text));   // Save as the course number

        getline(file, line);                    // Get second line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Get first substring from line till ','

        if (text != "Competencies")             // If first substring is not "Competencies"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as competencies
        while (std::getline(str, text, ',')) {  // Keeps looping till end of list string
            course.addComps(text);
        }

        getline(file, line);                    // Get third line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Get first substring from line till ','

        if (text != "Competency Masteries")     // If first substring is not "Competency Masteries"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as masteries
        while (std::getline(str, text, ',')) {  // Keeps looping till end of list string
            course.addMastery(std::stod(text));
        }

        getline(file, line);                    // Get fourth line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Get first substring from line till ','

        // Keeps reading if line starts with students #
        while (text.find("Student") != std::string::npos) { // End if none found
            row.clear();                        // Empty old row

            // Get the rest of the substrings in line and save them in data
            while (std::getline(str, text, ',')) {  // Keeps looping till end of string
                row.push_back(std::stod(text));     // Add data to row temporarily
            }
            course.addData(row);                // Add row to data

            getline(file, line);                // Get next line from file
            str.clear();                        // Reset stringstream
            str.str(line);                      // Get line ready for string segmentation
            std::getline(str, text, ',');       // Get first substring from line till ','
        }

        if (text != "Average")                  // If first substring is not "Average"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as averages
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addAverage(std::stod(text));
        }

        getline(file, line);                    // Get third from last line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Skip first substring from line till ','

        if (text != "Median")                   // If first substring is not "Median"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as medians
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addMedian(std::stod(text));
        }

        getline(file, line);                    // Get second from last line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Skip first substring from line till ','

        if (text != "Percent")                  // If first substring is not "Percent"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as percents
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addPercent(std::stod(text));
        }

        getline(file, line);                    // Get last line from file
        str.clear();                            // Reset stringstream
        str.str(line);                          // Get line ready for string segmentation
        std::getline(str, text, ',');           // Skip first substring from line till ','

        if (text != "Deviation")                // If first substring is not "Deviation"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as deviations
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addDeviation(std::stod(text));
        }

        file.close();   // Close file when done

        courses->push_back(course); // Add course to the list of courses if successfully read
    } catch (const std::ios_base::failure& e) { // If error happends while opeing file
        std::cout << "Error: " << e.what() << ", reading of file \"" << fileName << "\" failed\n\n";
        return EXIT_FAILURE;
    } catch (const std::invalid_argument& e) {  // If error happends while reading file
        std::cout << "Error: " << e.what() << ", file \"" << fileName << "\" not compatible\n\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) { // If another error happends
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        return EXIT_FAILURE;
    } catch (...) { // If error unknown happends
        std::cout << "Error: Unknown\n\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Get course data from online servers
void getData(const std::vector<int>* courseNums, const std::vector<std::string>* courseNames,
    const std::vector<std::string>* courseProfs, std::vector<CourseData>* courses, const std::string* auth) {
    std::vector<double> row;       // Temp to hold row for 2D vector

    // Go through courses vector and create CourseData class for each
    for (int i = 0; i < (int)courseNums->size(); i++) {
        courses->push_back(CourseData());
        courses->back().setCourseNum(courseNums->at(i));
        courses->back().setName(courseNames->at(i));
        courses->back().setProf(courseProfs->at(i));

        // Get data from online server
        nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net/api/v1/courses/"
            + msclr::interop::marshal_as<std::string>(courseNums->at(i).ToString())
            + "/outcome_rollups?include[]=outcomes&access_token=" + *auth));
        // Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

        // Debug: Print raw json with formating
        //std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

        if (j.contains("errors")) {	// If error, print error message(s)
            std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << std::endl << std::endl;
        } else {
            for (int k = 0; k < j["linked"]["outcomes"].size(); k++) {
                courses->back().addComps(j["linked"]["outcomes"][k]["title"]);
                courses->back().addMastery(j["linked"]["outcomes"][k]["mastery_points"]);
            }

            for (int k = 0; k < j["rollups"].size(); k++) {
                row.clear();
                for (int l = 0; l < j["rollups"][k]["scores"].size(); l++) {
                    row.push_back(j["rollups"][k]["scores"][l]["score"]);
                }
                courses->back().addData(row);
            }

            courses->back().calculate();
        }
    }
}

// Save data as .csv files
int saveData(const std::vector<CourseData>* courses) {
    struct tm newtime;                          // To store time
    char today[9];                              // YY-MM-DD
    time_t now = time(0);                       // Get current time
    localtime_s(&newtime, &now);                // Set time in newtime
    strftime(today, 9, "%y-%m-%d", &newtime);   // Format time to YY-MM-DD
    std::string date = today;                   // Convert to string

    // Made new folder in root directory if does not exist
    std::filesystem::create_directories("CSVs/" + date);

    bool multi = courses->size() > 1;                       // Flag if multiple courses
    std::vector<std::vector<double>> totalData;             // 2D vector to store total data
    remove(("CSVs/" + date + "/Aggregate.csv").c_str());    // Delete old file if exists
    std::string fileName;                                   // To store file name
    
    try {
        // Go through course data vector and save contents to file
        for (int i = 0; i < (int)courses->size(); i++) {
            // Create and open file in format (NAME INSTRUCTOR ID.csv) in folder named after the date:
            fileName = "CSVs/" + date + "/" + courses->at(i).name + " " + courses->at(i).prof + " "
                + msclr::interop::marshal_as<std::string>(courses->at(i).courseNum.ToString()) + ".csv";
            fileName.erase(std::remove(fileName.begin(), fileName.end(), ':'), fileName.end());
            std::ofstream outFile(fileName);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // Save course name, professor's name, and course number to file
            outFile << courses->at(i).name << ",";
            outFile << courses->at(i).prof << ",";
            outFile << courses->at(i).courseNum << ",";

            outFile << "\nCompetencies,";   // Save comps contents to file
            for (int j = 0; j < (int)courses->at(i).comps.size(); j++) {
                outFile << courses->at(i).comps.at(j) << ",";
            }

            outFile << "\nCompetency Masteries,";   // Print mastery contents to file
            for (int j = 0; j < (int)courses->at(i).mastery.size(); j++) {
                outFile << courses->at(i).mastery.at(j) << ",";
            }

            // Save data contents to file
            for (int j = 0; j < (int)courses->at(i).data.size(); j++) {
                outFile << "\nStudent " << j + 1 << ",";
                for (int k = 0; k < (int)courses->at(i).data.at(j).size(); k++) {
                    outFile << courses->at(i).data.at(j).at(k) << ",";
                }
            }

            outFile << "\nAverage,";    // Save average contents to file
            for (int j = 0; j < (int)courses->at(i).average.size(); j++) {
                outFile << courses->at(i).average.at(j) << ",";
            }

            outFile << "\nMedian,";     // Save median contents to file
            for (int j = 0; j < (int)courses->at(i).median.size(); j++) {
                outFile << courses->at(i).median.at(j) << ",";
            }

            outFile << "\nPercent,";    // Save percent contents to file
            for (int j = 0; j < (int)courses->at(i).percent.size(); j++) {
                outFile << courses->at(i).percent.at(j) << ",";
            }

            outFile << "\nDeviation,";  // Save deviation contents to file
            for (int j = 0; j < (int)courses->at(i).deviation.size(); j++) {
                outFile << courses->at(i).deviation.at(j) << ",";
            }

            outFile.close();    // Close file when done

            if (multi) {    // If multiple courses, print all courses to total.csv
                fileName = "CSVs/" + date + "/Aggregate.csv";   // Create and open file Aggregate.csv
                std::ofstream outFile(fileName, std::ios_base::app);

                // Throws errors if writing of file failed
                outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

                // Save course name, professor's name, and course number to file
                outFile << courses->at(i).name << ",";
                outFile << courses->at(i).prof << ",";
                outFile << courses->at(i).courseNum << ",";

                outFile << "\nCompetencies,";   // Save comps contents to file
                for (int j = 0; j < (int)courses->at(i).comps.size(); j++) {
                    outFile << courses->at(i).comps.at(j) << ",";
                }

                outFile << "\nCompetency Masteries,";   // Print mastery contents to file
                for (int j = 0; j < (int)courses->at(i).mastery.size(); j++) {
                    outFile << courses->at(i).mastery.at(j) << ",";
                }

                // Save data contents to file and add line to totalData
                for (int j = 0; j < (int)courses->at(i).data.size(); j++) {
                    totalData.push_back(courses->at(i).data.at(j));

                    outFile << "\nStudent " << j + 1 << ",";
                    for (int k = 0; k < (int)courses->at(i).data.at(j).size(); k++) {
                        outFile << courses->at(i).data.at(j).at(k) << ",";
                    }
                }

                outFile << "\nAverage,";    // Save average contents to file
                for (int j = 0; j < (int)courses->at(i).average.size(); j++) {
                    outFile << courses->at(i).average.at(j) << ",";
                }

                outFile << "\nMedian,";     // Save median contents to file
                for (int j = 0; j < (int)courses->at(i).median.size(); j++) {
                    outFile << courses->at(i).median.at(j) << ",";
                }

                outFile << "\nPercent,";    // Save percent contents to file
                for (int j = 0; j < (int)courses->at(i).percent.size(); j++) {
                    outFile << courses->at(i).percent.at(j) << ",";
                }

                outFile << "\nDeviation,";  // Save deviation contents to file
                for (int j = 0; j < (int)courses->at(i).deviation.size(); j++) {
                    outFile << courses->at(i).deviation.at(j) << ",";
                }
                outFile << std::endl << std::endl;

                outFile.close();    // Close file when done
            }
        }

        if (multi) {    // If multiple courses, print totals to total.csv
            fileName = "CSVs/" + date + "/Aggregate.csv";   // Open file Aggregate.csv
            std::ofstream outFile(fileName, std::ios_base::app);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // The 2D vector of the average, median, percent above three, and standard deviation
            std::vector<std::vector<double>> calcedData = util::calcData(&totalData);

            outFile << "Aggregate Average,";        // Save total average contents to file
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(0).at(i) << ",";
            }

            outFile << "\nAggregate Median,";       // Save total median contents to file
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(1).at(i) << ",";
            }

            outFile << "\nAggregate Percent,";      // Save total percent contents to file
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(2).at(i) << ",";
            }

            outFile << "\nAggregate Deviation,";    // Save total deviation contents to file
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(3).at(i) << ",";
            }

            outFile.close();    // Close file when done
        }
    } catch (const std::ios_base::failure& e) { // If error happends while opeing file
        std::cout << "Error: " << e.what() << ", writing of file \"" << fileName << "\" failed\n\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) { // If another error happends
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        return EXIT_FAILURE;
    } catch (...) { // If error unknown happends
        std::cout << "Error: Unknown\n\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Debug test to print data to console
void debugPrint(const std::vector<int>* accountIds, const std::vector<CourseData>* courses,
    const std::string* auth) {
    // Go through account ids vector and print contents to console
    std::cout << "Debug: CourseData\nManageable account ids: ";
    for (unsigned int i = 0; i < accountIds->size(); i++) {
        std::cout << accountIds->at(i) << ", ";
    }

    // Prints auth and course numbers to console
    std::cout << "\nAuth key: " << *auth << "\nCourse ids: ";
    for (unsigned int i = 0; i < courses->size(); i++) {
        std::cout << courses->at(i).courseNum << ", ";
    }
    std::cout << std::endl << std::endl;

    // Go through course data vector and print contents to console
    for (int i = 0; i < (int)courses->size(); i++) {
        std::cout << courses->at(i).name << ",";
        std::cout << courses->at(i).prof << ",";
        std::cout << courses->at(i).courseNum;

        std::cout << "\nCompetencies,"; // Print comps contents to console
        for (int j = 0; j < (int)courses->at(i).comps.size(); j++) {
            std::cout << courses->at(i).comps.at(j) << ",";
        }

        std::cout << "\nCompetency Masteries,"; // Print mastery contents to console
        for (int j = 0; j < (int)courses->at(i).mastery.size(); j++) {
            std::cout << courses->at(i).mastery.at(j) << ",";
        }

        // Print data contents to console
        for (int j = 0; j < (int)courses->at(i).data.size(); j++) {
            std::cout << "\nStudent " << j + 1 << ",";
            for (int k = 0; k < (int)courses->at(i).data.at(j).size(); k++) {
                std::cout << courses->at(i).data.at(j).at(k) << ",";
            }
        }

        std::cout << "\nAverage,";  // Print average contents to console
        for (int j = 0; j < (int)courses->at(i).average.size(); j++) {
            std::cout << courses->at(i).average.at(j) << ",";
        }

        std::cout << "\nMedian,";   // Print median contents to console
        for (int j = 0; j < (int)courses->at(i).median.size(); j++) {
            std::cout << courses->at(i).median.at(j) << ",";
        }

        std::cout << "\nPercent,";  // Print percent contents to console
        for (int j = 0; j < (int)courses->at(i).percent.size(); j++) {
            std::cout << courses->at(i).percent.at(j) << ",";
        }

        std::cout << "\nDeviation,";    // Print deviation contents to console
        for (int j = 0; j < (int)courses->at(i).deviation.size(); j++) {
            std::cout << courses->at(i).deviation.at(j) << ",";
        }
        std::cout << std::endl << std::endl;
    }
}