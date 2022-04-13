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
*/

#include "UIForm.h"
#include "UISelectCourses.h"
#include "VisualizationForm.h"
#include "CommandLine.h"
#include "CourseData.h"
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>        // Needed to get the date
#include <filesystem>   // Needed to make dir
#include <sstream>      // Needed for stringstream
#include <nlohmann/json.hpp>    // Needed to read data fetched from online servers
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String

// Needed for Windows Form
using namespace System;
using namespace System::Windows::Forms;

int readCSV(std::vector<CourseData>* courses, std::string fileName);    // Read in data from CSV file
int saveData(std::vector<CourseData>* courses); // Save data as .csv files
void debugPrint(const std::vector<int> courseNums, const std::string auth, std::vector<CourseData>* courses); // Debug test to print data to console

[STAThread]

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::vector<int> courseNums;        // Vector array holding course numbers
        std::vector<CourseData> courses;    // Vector array holding course data for each course
        std::string auth;                   // String holding authorization key

        // Debug: Read in test CSV
        if (readCSV(&courses, "2022-Spring-CSCI285N-63925-A-Betsy Gamrat.csv"))
            return EXIT_FAILURE;

        // Debug: Read in same test CSV for total.csv test
        readCSV(&courses, "2022-Spring-CSCI285N-63925-A-Betsy Gamrat.csv");

        // Set Windows Form Styles
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);

        // Define UI form and send course numbers vector address
        Assessments::UIForm ui(&courseNums);
        Application::Run(% ui); // Run UI form

        // Get authorization key from ui and convert it from String^ to String
        auth = msclr::interop::marshal_as<std::string>(ui.getAuth());

        // Define select form and send course numbers vector address
        Assessments::UISelectCourses select;
        Application::Run(% select); // Run select form

        // Go through courses vector and create CourseData class for each
        //for (int i = 0; i < (int)courseNums.size(); i++) {
        //    courses.push_back(CourseData());
        //    courses.back().setCourseNum(courseNums[i]);
        //}

        // Debug: Prints auth and course numbers to console with course data
        debugPrint(courseNums, auth, &courses);

        // Save data as .csv's
        if (saveData(&courses))
            return EXIT_FAILURE;

        // Define Visualization form sending course data vector address
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

        if (text != "Students") // If first substring is not "Students"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

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

        if (text != "Average")  // If first substring is not "Average"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as averages
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addAverage(std::stod(text));
        }

        getline(file, line);            // Get third from last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        if (text != "Median")   // If first substring is not "Median"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as medians
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addMedian(std::stod(text));
        }

        getline(file, line);            // Get second from last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        if (text != "Percent")  // If first substring is not "Percent"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

        // Get the rest of the substrings in line and save them as percents
        while (std::getline(str, text, ',')) {  // Keeps looping till end of string
            course.addPercent(std::stod(text));
        }

        getline(file, line);            // Get last line from file
        str.clear();                    // Reset stringstream
        str.str(line);                  // Get line ready for string segmentation
        std::getline(str, text, ',');   // Skip first substring from line till ','

        if (text != "Deviation")    // If first substring is not "Deviation"
            throw std::invalid_argument("invalid argument encountered");    // Throw invalid_argument error

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
        std::cout << "Error: " << e.what() << ", reading of file \"" << fileName << "\" failed\n\n";
        return EXIT_FAILURE;
    } catch (const std::invalid_argument& e) {
        // If error happends while reading file
        std::cout << "Error: " << e.what() << ", file \"" << fileName << "\" not compatible\n\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        // If another error happends
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        // If error unknown happends
        std::cout << "Error: Unknown\n\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int saveData(std::vector<CourseData>* courses) {
    struct tm newtime;                          // To store time
    char today[9];                              // MM-DD-YY
    time_t now = time(0);                       // Get current time
    localtime_s(&newtime, &now);                // Set time in newtime
    strftime(today, 9, "%m-%d-%y", &newtime);   // Format time to MM-DD-YY
    std::string date = today;                   // Convert to string

    // Made new folder in root directory if does not exist
    std::filesystem::create_directory(date);

    bool multi = courses->size() > 1;           // Flag if multiple courses
    std::vector<std::vector<int>> totalData;    // 2D vector to store total data
    remove((date + "/Total.csv").c_str());      // Delete old file if exists
    std::string fileName;                       // To store file name
    
    try {
        // Go through course data vector and save contents to file
        for (int i = 0; i < (int)courses->size(); i++) {
            // Create and open file following format in folder named after the date:
            // YEAR-SEMESTER-CODE-ID-SECTION-INSTRUCTOR.csv
            fileName = date + "/"
                + msclr::interop::marshal_as<std::string>(courses->at(i).getYear().ToString())
                + "-" + courses->at(i).getSemester() + "-" + courses->at(i).getCode() + "-"
                + msclr::interop::marshal_as<std::string>(courses->at(i).getCourseNum().ToString())
                + "-" + courses->at(i).getSection() + "-" + courses->at(i).getProf() + ".csv";
            std::ofstream outFile(fileName);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // Save course year, semester, code, name, section, professor's name, and course number to file
            outFile << courses->at(i).getYear() << ",";
            outFile << courses->at(i).getSemester() << ",";
            outFile << courses->at(i).getCode() << ",";
            outFile << courses->at(i).getName() << ",";
            outFile << courses->at(i).getSection() << ",";
            outFile << courses->at(i).getProf() << ",";
            outFile << courses->at(i).getCourseNum() << "," << std::endl;

            // Save comps contents to file
            outFile << "Students,";
            for (int j = 0; j < (int)courses->at(i).getComps()->size(); j++) {
                outFile << courses->at(i).getComps()->at(j) << ",";
            }
            outFile << std::endl;

            // Save data contents to file
            for (int j = 0; j < (int)courses->at(i).getData()->size(); j++) {
                outFile << "Student " << j + 1 << ",";
                for (int k = 0; k < (int)courses->at(i).getData()->at(j).size(); k++) {
                    outFile << courses->at(i).getData()->at(j).at(k) << ",";
                }
                outFile << std::endl;
            }

            // Save average contents to file
            outFile << "Average,";
            for (int j = 0; j < (int)courses->at(i).getAverage()->size(); j++) {
                outFile << courses->at(i).getAverage()->at(j) << ",";
            }

// Save median contents to file
outFile << "\nMedian,";
for (int j = 0; j < (int)courses->at(i).getMedian()->size(); j++) {
    outFile << courses->at(i).getMedian()->at(j) << ",";
}

// Save percent contents to file
outFile << "\nPercent,";
for (int j = 0; j < (int)courses->at(i).getPercent()->size(); j++) {
    outFile << courses->at(i).getPercent()->at(j) << ",";
}

// Save deviation contents to file
outFile << "\nDeviation,";
for (int j = 0; j < (int)courses->at(i).getDeviation()->size(); j++) {
    outFile << courses->at(i).getDeviation()->at(j) << ",";
}

// Close file when done
outFile.close();

if (multi) {    // If multiple courses, print all courses to total.csv
    // Create and open file total.csv 
    fileName = date + "/Total.csv";
    std::ofstream outFile(fileName, std::ios_base::app);

    // Throws errors if writing of file failed
    outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

    // Save course year, semester, code, name, section, professor's name, and course number to file
    outFile << courses->at(i).getYear() << ",";
    outFile << courses->at(i).getSemester() << ",";
    outFile << courses->at(i).getCode() << ",";
    outFile << courses->at(i).getName() << ",";
    outFile << courses->at(i).getSection() << ",";
    outFile << courses->at(i).getProf() << ",";
    outFile << courses->at(i).getCourseNum() << "," << std::endl;

    // Save comps contents to file
    outFile << "Students,";
    for (int j = 0; j < (int)courses->at(i).getComps()->size(); j++) {
        outFile << courses->at(i).getComps()->at(j) << ",";
    }
    outFile << std::endl;

    // Save data contents to file and add line to totalData
    for (int j = 0; j < (int)courses->at(i).getData()->size(); j++) {
        totalData.push_back(courses->at(i).getData()->at(j));

        outFile << "Student " << j + 1 << ",";
        for (int k = 0; k < (int)courses->at(i).getData()->at(j).size(); k++) {
            outFile << courses->at(i).getData()->at(j).at(k) << ",";
        }
        outFile << std::endl;
    }

    // Save average contents to file
    outFile << "Average,";
    for (int j = 0; j < (int)courses->at(i).getAverage()->size(); j++) {
        outFile << courses->at(i).getAverage()->at(j) << ",";
    }

    // Save median contents to file
    outFile << "\nMedian,";
    for (int j = 0; j < (int)courses->at(i).getMedian()->size(); j++) {
        outFile << courses->at(i).getMedian()->at(j) << ",";
    }

    // Save percent contents to file
    outFile << "\nPercent,";
    for (int j = 0; j < (int)courses->at(i).getPercent()->size(); j++) {
        outFile << courses->at(i).getPercent()->at(j) << ",";
    }

    // Save deviation contents to file
    outFile << "\nDeviation,";
    for (int j = 0; j < (int)courses->at(i).getDeviation()->size(); j++) {
        outFile << courses->at(i).getDeviation()->at(j) << ",";
    }
    outFile << std::endl << std::endl;

    // Close file when done
    outFile.close();
}
        }

        if (multi) {// If multiple courses, print totals to total.csv
            // Open file total.csv
            fileName = date + "/Total.csv";
            std::ofstream outFile(fileName, std::ios_base::app);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // The 2D vector of the average, median, percent above three, and standard deviation
            std::vector<std::vector<double>> calcedData = util::calcData(totalData);

            // Save total average contents to file
            outFile << "Total average,";
            for (int i = 0; i < calcedData[0].size(); i++) {
                std::cout << calcedData[0][i] << ",";
                outFile << calcedData[0][i] << ",";
            }
            std::cout << std::endl;

            // Save total median contents to file
            outFile << "\nTotal median,";
            for (int i = 0; i < calcedData[1].size(); i++) {
                std::cout << calcedData[1][i] << ",";
                outFile << calcedData[1][i] << ",";
            }
            std::cout << std::endl;

            // Save total percent contents to file
            outFile << "\nTotal percent,";
            for (int i = 0; i < calcedData[2].size(); i++) {
                std::cout << calcedData[2][i] << ",";
                outFile << calcedData[2][i] << ",";
            }
            std::cout << std::endl;

            // Save total deviation contents to file
            outFile << "\nTotal deviation,";
            for (int i = 0; i < calcedData[3].size(); i++) {
                std::cout << calcedData[3][i] << ",";
                outFile << calcedData[3][i] << ",";
            }
            std::cout << std::endl;

            // Close file when done
            outFile.close();
        }
    } catch (const std::ios_base::failure& e) {
        // If error happends while opeing file
        std::cout << "Error: " << e.what() << ", reading of file \"" << fileName << "\" failed\n\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        // If another error happends
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        // If error unknown happends
        std::cout << "Error: Unknown\n\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Debug test to print course numbers, authorization key, and course data to console
void debugPrint(const std::vector<int> courseNums, const std::string auth, std::vector<CourseData>* courses) {
    // Prints auth and course numbers to console
    std::cout << "Debug: CourseData\n";
    std::cout << "Auth key: " << auth << std::endl;
    std::cout << "Courses: ";

    // Go through course numbers vector and print contents to console
    for (unsigned int i = 0; i < courseNums.size(); i++) {
        std::cout << courseNums[i] << ", ";
    }
    std::cout << std::endl << std::endl;

    // Go through course data vector and print contents to console
    for (int i = 0; i < (int)courses->size(); i++) {
        std::cout << courses->at(i).getYear() << ",";
        std::cout << courses->at(i).getSemester() << ",";
        std::cout << courses->at(i).getCode() << ",";
        std::cout << courses->at(i).getName() << ",";
        std::cout << courses->at(i).getSection() << ",";
        std::cout << courses->at(i).getProf() << ",";
        std::cout << courses->at(i).getCourseNum() << std::endl;

        // Print comps contents to console
        std::cout << "Students,";
        for (int j = 0; j < (int)courses->at(i).getComps()->size(); j++) {
            std::cout << courses->at(i).getComps()->at(j) << ",";
        }
        std::cout << std::endl;

        // Print data contents to console
        for (int j = 0; j < (int)courses->at(i).getData()->size(); j++) {
            std::cout << "Student " << j + 1 << ",";
            for (int k = 0; k < (int)courses->at(i).getData()->at(j).size(); k++) {
                std::cout << courses->at(i).getData()->at(j).at(k) << ",";
            }
            std::cout << std::endl;
        }

        // Print average contents to console
        std::cout << "Average,";
        for (int j = 0; j < (int)courses->at(i).getAverage()->size(); j++) {
            std::cout << courses->at(i).getAverage()->at(j) << ",";
        }

        // Print median contents to console
        std::cout << "\nMedian,";
        for (int j = 0; j < (int)courses->at(i).getMedian()->size(); j++) {
            std::cout << courses->at(i).getMedian()->at(j) << ",";
        }

        // Print percent contents to console
        std::cout << "\nPercent,";
        for (int j = 0; j < (int)courses->at(i).getPercent()->size(); j++) {
            std::cout << courses->at(i).getPercent()->at(j) << ",";
        }

        // Print deviation contents to console
        std::cout << "\nDeviation,";
        for (int j = 0; j < (int)courses->at(i).getDeviation()->size(); j++) {
            std::cout << courses->at(i).getDeviation()->at(j) << ",";
        }
        std::cout << std::endl << std::endl;
    }
}