#include "UIForm.h"

// On enter button click, get authorization key from authKey, and exit form
System::Void Assessments::UIForm::enterBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	// Set auth as what user put in textBox1
	auth = authKey->Text;

	// Temporarily add temp test course number
	courses->push_back(99999);

	// Close form
	this->Close();
}
