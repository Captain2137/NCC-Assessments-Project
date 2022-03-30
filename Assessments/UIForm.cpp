#include "Curl.h"
#include "UIForm.h"
#include <string>
#include <iostream>
#include <msclr/marshal_cppstd.h>   // Needed to convert String^ to String
#include <json/json.h>  // Needed to read data fetched from online servers

using namespace Curl;

// On enter button click, get authorization key from authKey, and exit form
System::Void Assessments::UIForm::enterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	// Set auth as what user put in textBox1
	auth = authKey->Text;

	std::string rawJson = Curl::request("https://canvas-prod.ccsnh.edu/api/v1/courses?per_page=100&access_token=" + msclr::interop::marshal_as<std::string>(authKey->Text));

    JSONCPP_STRING errs;
    Json::Value root;

    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> const reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root, &errs)) {
        std::cout << errs << std::endl;
        return;
    }

    try {
        //Json::Value id = root["id"];
        //std::cout << id;


        for (int i = 0; i < root.size(); i++) {
            courses->push_back(root[i]["id"].asInt());
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl << std::endl;
    }

	// Close form
	this->Close();
}
