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
#include "CourseData.h"
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>        // Needed to get the date
#include <filesystem>   // Needed to make dir
#include <sstream>      // Needed for stringstream
#include <nlohmann/json.hpp>    // Needed to read data fetched from online servers
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String

// Needed for Windows Form
using namespace System;
using namespace System::Windows::Forms;

int readCSV(std::vector<CourseData>* courses, std::string fileName);    // Read in data from CSV file
void getData(std::vector<CourseData>* courses, std::vector<int>* courseNums, std::string* auth);
int saveData(std::vector<CourseData>* courses); // Save data as .csv files
void debugPrint(const std::vector<int> courseNums, const std::string auth, std::vector<CourseData>* courses); // Debug test to print data to console

[STAThread]

int main() {
    std::string userName;               // String holding users name
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
    Assessments::UIForm ui(&auth, &userName);
    Application::Run(% ui); // Run UI form

    // Define select form and send course numbers vector address
    Assessments::UISelectCourses select(&auth, &userName, &courseNums);
    Application::Run(% select); // Run select form

    getData(&courses, &courseNums, &auth);

    // Debug: Prints auth and course numbers to console with course data
    debugPrint(courseNums, auth, &courses);

    // Save data as .csv's
    if (saveData(&courses))
        return EXIT_FAILURE;

    // Define Visualization form sending course data vector address
    Assessments::VisualizationForm visualization(&courses);
    Application::Run(% visualization);  // Run Visualization form
}

// Read in data from CSV file
int readCSV(std::vector<CourseData>* courses, std::string fileName) {
    try {
        std::ifstream file(fileName);   // Open file

        // Throws errors if reading of file failed
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

        CourseData course;          // Create course data to store data
        std::vector<double> row;       // Temp to hold row for 2D vector
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
                row.push_back(std::stod(text));     // Add data to row temporarily
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

void getData(std::vector<CourseData>* courses, std::vector<int>* courseNums, std::string* auth) {
    // Go through courses vector and create CourseData class for each
    for (int i = 0; i < (int)courseNums->size(); i++) {
        std::vector<double> row;       // Temp to hold row for 2D vector

        // Get data from online server
        nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net//api/v1/courses/"
            + msclr::interop::marshal_as<std::string>(courseNums->at(i).ToString())
            + "?include[]=term&include[]=sections&include[]=teachers&access_token=" + *auth));
        // Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

        // Debug: Print raw json with formating
        std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

        if (j.contains("errors")) {	// If error, print error message(s)
            std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << std::endl << std::endl;
        } else {	// If success, 
            courses->push_back(CourseData());
            courses->back().setCourseNum(courseNums->at(i));
            courses->back().setCode(j["course_code"]);
            courses->back().setName(j["name"]);
            courses->back().setProf(j["teachers"][0]["display_name"]);
            courses->back().setSemester(j["term"]["name"]);
            courses->back().setYear(std::stoi(j["term"]["start_at"].get<std::string>().substr(0, 4)));
            courses->back().setSection("");

            // Get data from online server
            nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net/api/v1/courses/"
                + msclr::interop::marshal_as<std::string>(courseNums->at(i).ToString())
                + "/outcome_rollups?include[]=outcomes&include[]=users&include[]=outcome_paths&access_token=" + *auth));
            // Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

            // Debug: Print raw json with formating
            std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

            if (j.contains("errors")) {	// If error, print error message(s)
                std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << std::endl << std::endl;
            } else {	// If success, 
                for (int k = 0; k < j["linked"]["outcome_paths"].size(); k++) {
                    courses->back().addComps(j["linked"]["outcome_paths"][k]["parts"][0]["name"]);
                }

                for (int k = 0; k < j["linked"]["outcomes"].size(); k++) {
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
}

// Save data into CSV files
int saveData(std::vector<CourseData>* courses) {
    struct tm newtime;                          // To store time
    char today[9];                              // YY-MM-DD
    time_t now = time(0);                       // Get current time
    localtime_s(&newtime, &now);                // Set time in newtime
    strftime(today, 9, "%y-%m-%d", &newtime);   // Format time to YY-MM-DD
    std::string date = today;                   // Convert to string

    // Made new folder in root directory if does not exist
    std::filesystem::create_directories("CSVs/" + date);

    bool multi = courses->size() > 1;           // Flag if multiple courses
    std::vector<std::vector<double>> totalData;    // 2D vector to store total data
    remove(("CSVs/" + date + "/Aggregate.csv").c_str());  // Delete old file if exists
    std::string fileName;                       // To store file name
    
    try {
        // Go through course data vector and save contents to file
        for (int i = 0; i < (int)courses->size(); i++) {
            // Create and open file following format in folder named after the date:
            // YEAR-SEMESTER-CODE-ID-SECTION-INSTRUCTOR.csv
            fileName = "CSVs/" + date + "/"
                + msclr::interop::marshal_as<std::string>((*courses->at(i).getYear()).ToString())
                + "-" + *courses->at(i).getSemester() + "-" + *courses->at(i).getCode() + "-"
                + msclr::interop::marshal_as<std::string>((*courses->at(i).getCourseNum()).ToString())
                + "-" + *courses->at(i).getSection() + "-" + *courses->at(i).getProf() + ".csv";
            fileName.erase(std::remove(fileName.begin(), fileName.end(), ':'), fileName.end());
            std::ofstream outFile(fileName);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // Save course year, semester, code, name, section, professor's name, and course number to file
            outFile << *courses->at(i).getYear() << ",";
            outFile << *courses->at(i).getSemester() << ",";
            outFile << *courses->at(i).getCode() << ",";
            outFile << *courses->at(i).getName() << ",";
            outFile << *courses->at(i).getSection() << ",";
            outFile << *courses->at(i).getProf() << ",";
            outFile << *courses->at(i).getCourseNum() << "," << std::endl;

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
                // Create and open file Aggregate.csv 
                fileName = "CSVs/" + date + "/Aggregate.csv";
                std::ofstream outFile(fileName, std::ios_base::app);

                // Throws errors if writing of file failed
                outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

                // Save course year, semester, code, name, section, professor's name, and course number to file
                outFile << *courses->at(i).getYear() << ",";
                outFile << *courses->at(i).getSemester() << ",";
                outFile << *courses->at(i).getCode() << ",";
                outFile << *courses->at(i).getName() << ",";
                outFile << *courses->at(i).getSection() << ",";
                outFile << *courses->at(i).getProf() << ",";
                outFile << *courses->at(i).getCourseNum() << "," << std::endl;

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

        if (multi) {    // If multiple courses, print totals to total.csv
            // Open file Aggregate.csv
            fileName = "CSVs/" + date + "/Aggregate.csv";
            std::ofstream outFile(fileName, std::ios_base::app);

            // Throws errors if writing of file failed
            outFile.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::goodbit);

            // The 2D vector of the average, median, percent above three, and standard deviation
            std::vector<std::vector<double>> calcedData = util::calcData(totalData);

            // Save total average contents to file
            outFile << "Aggregate Average,";
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(0).at(i) << ",";
            }
            std::cout << std::endl;

            // Save total median contents to file
            outFile << "\nAggregate Median,";
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(1).at(i) << ",";
            }
            std::cout << std::endl;

            // Save total percent contents to file
            outFile << "\nAggregate Percent,";
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(2).at(i) << ",";
            }
            std::cout << std::endl;

            // Save total deviation contents to file
            outFile << "\nAggregate Deviation,";
            for (int i = 0; i < (int)calcedData[0].size(); i++) {
                outFile << calcedData.at(3).at(i) << ",";
            }
            std::cout << std::endl;

            // Close file when done
            outFile.close();
        }
    } catch (const std::ios_base::failure& e) {
        // If error happends while opeing file
        std::cout << "Error: " << e.what() << ", writing of file \"" << fileName << "\" failed\n\n";
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
        std::cout << *courses->at(i).getYear() << ",";
        std::cout << *courses->at(i).getSemester() << ",";
        std::cout << *courses->at(i).getCode() << ",";
        std::cout << *courses->at(i).getName() << ",";
        std::cout << *courses->at(i).getSection() << ",";
        std::cout << *courses->at(i).getProf() << ",";
        std::cout << *courses->at(i).getCourseNum() << std::endl;

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