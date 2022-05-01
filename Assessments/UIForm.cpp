#include "Util.h"
#include "UIForm.h"
#include <iostream>
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <nlohmann/json.hpp>		// Needed to read data fetched from online servers

using namespace util;

// On enter button click, get authorization key from authKey, and exit form
System::Void Assessments::UIForm::enterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!authKey->Text->CompareTo("")) {	// Exit if authKey text is empty
		// Message box alerting the user that nothing was inputted.
		MessageBox::Show("Error: Canvas Key was not given.");
		Application::Exit();	// This exits the program entirely
	} else {
		// Set auth as what user put in authKey
		*auth = msclr::interop::marshal_as<std::string>(authKey->Text);

		// Get manageable ids from online server
		nlohmann::json j = nlohmann::json::parse(util::curlRequest(
			"https://canvas.nashuaweb.net/api/v1/manageable_accounts?access_token=" + *auth));
		// Change canvas.nashuaweb.net to canvas-prod.ccsnh.edu in final

		// Debug: Print raw json with formating
		//std::cout << "Raw Json:\n" << j.dump(4) << std::endl << std::endl;

		// If json contains errors, print error to console, inform user, and exit
		if (j.contains("errors")) {
			// Message box alerting the user of error
			MessageBox::Show("Error: " + msclr::interop::marshal_as<String^>(
				j["errors"][0]["message"].get<std::string>()));

			Application::Exit();	// This Exits the Application Entirely
		} else {
			for (int i = 0; i < j.size(); i++) {
				accountIds->push_back(j[i]["id"]);
			}

			this->Close();	// Close form
		}
	}
}