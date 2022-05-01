#include "UISelectCourses.h"
#include "Util.h"
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>		// Needed to read data fetched from online servers
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String

Assessments::UISelectCourses::UISelectCourses(const std::vector<int>* accountIds, const std::string* auth,
    std::vector<int>* courseNumsIn, std::vector<std::string>* courseNamesIn, std::vector<std::string>* courseProfsIn) {
	courseNums = courseNumsIn;	    // Set courseNums pointer to given address
    courseNames = courseNamesIn;	// Set courseNames pointer to given address
    courseProfs = courseProfsIn;	// Set courseProfs pointer to given address

    for (int i = 0; i < accountIds->size(); i++) {	// Go through each id
        // Get data from online server
        nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net/api/v1/accounts/"
            + msclr::interop::marshal_as<std::string>(accountIds->at(i).ToString())
            + "/courses?per_page=100&include[]=teachers&access_token=" + *auth));
        // Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

        // Debug: Print raw json with formating
        //std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

        if (j.contains("errors")) {	// If error, print error message
            // Message box alerting the user of error
            MessageBox::Show("Error: " + msclr::interop::marshal_as<String^>(
                j["errors"][0]["message"].get<std::string>()));

            Application::Exit();	// This Exits the Application Entirely
        } else {
            // Step through the received data and add data
            for (int k = 0; k < j.size(); k++) {
                // Dont add duplicate ids
                if (std::find(courseNums->begin(), courseNums->end(), j[k]["id"]) == courseNums->end()) {
                    courseNums->push_back(j[k]["id"]);
                    courseNames->push_back(j[k]["name"]);
                    courseProfs->push_back(j[k]["teachers"][0]["display_name"]);
                }
            }
        }
    }

    InitializeComponent();
}