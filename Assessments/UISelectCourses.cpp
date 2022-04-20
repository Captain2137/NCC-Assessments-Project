#include "UISelectCourses.h"
#include "Util.h"
#include <iostream>
#include <nlohmann/json.hpp>    // Needed to read data fetched from online servers
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String

Assessments::UISelectCourses::UISelectCourses(std::string* authIn, std::string* userNameIn, std::vector<int>* courseNumsIn) {
	auth = authIn;				// Set auth pointer to given address
	userName = userNameIn;		// Set userName pointer to given address
	courseNums = courseNumsIn;	// Set courseNums pointer to given address

	// Get data from online server
	nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net/api/v1/accounts/self/courses?per_page=100&include[]=teachers&access_token=" + *auth));
	// Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

	// Debug: Print raw json with formating
	std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

	if (j.contains("errors")) {	// If error, print error message(s)
		std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << std::endl << std::endl;
	} else {	// If success, get course ids
		// Step through the received data and add each course id to courses
		for (int i = 0; i < j.size(); i++) {
			courseNums->push_back(j[i]["id"]);
			courseNames.push_back(msclr::interop::marshal_as<String^>(j[i]["name"].get<std::string>()));
			courseTeachers.push_back(msclr::interop::marshal_as<String^>(j[i]["teachers"][0]["display_name"].get<std::string>()));
		}
	}

	InitializeComponent();
}

System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	std::cout << "Test" << std::endl;

}
