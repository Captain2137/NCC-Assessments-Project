#include "Util.h"
#include "UIForm.h"
#include <iostream>
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <nlohmann/json.hpp>    // Needed to read data fetched from online servers

using namespace util;

// On enter button click, get authorization key from authKey, and exit form
System::Void Assessments::UIForm::enterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	// Set auth as what user put in textBox1
	*auth = msclr::interop::marshal_as<std::string>(authKey->Text);

	// Get data from online server
	nlohmann::json j = nlohmann::json::parse(util::curlRequest("https://canvas.nashuaweb.net/api/v1/users/self?access_token=" + *auth));
	// Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

	// Debug: Print raw json with formating
	std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

	if (j.contains("errors")) {	// If error, print error message(s)
		std::cout << "Error: " << j["errors"][0]["message"].get<std::string>() << std::endl << std::endl;
	} else {	// If success, get user's name
		*userName = j["name"];
	}

	// Close form
	this->Close();
}