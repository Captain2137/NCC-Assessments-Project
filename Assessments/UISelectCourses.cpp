#include "UISelectCourses.h"
#include "Curl.h"
#include <string>
#include <iostream>
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <nlohmann/json.hpp>    // Needed to read data fetched from online servers

using namespace curl;
using json = nlohmann::json;
// On enter button click, get authorization key from authKey, and exit form
System::Void Assessments::UISelectCourses::enterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	/*
	// Get data from online server
	json j = json::parse(curl::request("https://canvas-prod.ccsnh.edu/api/v1/courses?per_page=100&access_token=" + msclr::interop::marshal_as<std::string>(authKey->Text)));

	// Debug: Print ran json with formating
	std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

	if (j.contains("errors")) {	// If error, print error message(s)
		std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << ", " << j["status"].get<std::string>() << std::endl << std::endl;
	}
	else {	// If success, get course ids
	 // Step through the received data and add each course id to courses
		for (int i = 0; i < j.size(); i++) {
			courses->push_back(j[i]["id"]);
		}
	}
	*/

	// Close form
	this->Close();
}