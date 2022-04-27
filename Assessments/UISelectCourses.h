#pragma once
#include <vector>
#include <string>
#include <cliext/vector>

namespace Assessments {
	// Needed for windows forms
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class UISelectCourses : public System::Windows::Forms::Form {
	public:
		std::string* auth;				// Pointer to given string to store authorisation key
		std::string* userName;			// Pointer to given string to store user name
		std::vector<int>* courseNums;	// Pointer to given vector of ints to store course ids
		cliext::vector<String^> courseNames;	// Vector of strings to store course names

	public:

		   cliext::vector<String^> courseTeachers;	// Vector of strings to store course teacher names

		UISelectCourses(std::string* authIn, std::string* userNameIn, std::vector<int>* courseNumsIn);

	protected:
		~UISelectCourses() {
			if (components)
				delete components;
		}

		// Auto generated code
	private: System::Windows::Forms::CheckedListBox^ addedCourCLB;
	private: System::Windows::Forms::ComboBox^ instructorCombo;
	private: System::Windows::Forms::TextBox^ coursesTextBox;
	private: System::Windows::Forms::Label^ instructorLabel;
	private: System::Windows::Forms::Label^ semesterLabel;
	private: System::Windows::Forms::Label^ coursesLabel;
	private: System::Windows::Forms::Label^ addedCoursesLabel ;
	private: System::Windows::Forms::ComboBox^ semesterCombo;
	private: System::Windows::Forms::Button^ selAllBut;
	private: System::Windows::Forms::Button^ remAllBut;
	private: System::Windows::Forms::Button^ searchBut;
	protected:

	private:
		// Required designer variable.
		System::ComponentModel::Container ^components;

		// DO NOT MODIFY
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UISelectCourses::typeid));
			this->addedCourCLB = (gcnew System::Windows::Forms::CheckedListBox());
			this->instructorCombo = (gcnew System::Windows::Forms::ComboBox());
			this->semesterCombo = (gcnew System::Windows::Forms::ComboBox());
			this->coursesTextBox = (gcnew System::Windows::Forms::TextBox());
			this->instructorLabel = (gcnew System::Windows::Forms::Label());
			this->semesterLabel = (gcnew System::Windows::Forms::Label());
			this->coursesLabel = (gcnew System::Windows::Forms::Label());
			this->addedCoursesLabel  = (gcnew System::Windows::Forms::Label());
			this->selAllBut = (gcnew System::Windows::Forms::Button());
			this->remAllBut = (gcnew System::Windows::Forms::Button());
			this->searchBut = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Added Courses Checked List Box
			// 
			this->addedCourCLB->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->addedCourCLB->CheckOnClick = true;
			this->addedCourCLB->FormattingEnabled = true;
			this->addedCourCLB->Location = System::Drawing::Point(133, 327);
			this->addedCourCLB->Name = L"addedCourCLB";
			this->addedCourCLB->Size = System::Drawing::Size(605, 184);
			this->addedCourCLB->TabIndex = 0;
			this->addedCourCLB->SelectedIndexChanged += gcnew System::EventHandler(this, &UISelectCourses::addedCourCLB_SelectedIndexChanged);
			// 
			// Add Instructor Box 
			// 
			this->instructorCombo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->instructorCombo->DataSource = this->addedCourCLB->CustomTabOffsets;
			this->instructorCombo->FormattingEnabled = true;
			this->instructorCombo->Location = System::Drawing::Point(342, 192);
			this->instructorCombo->MaxLength = 100;
			this->instructorCombo->Name = L"instructorCombo";
			this->instructorCombo->Size = System::Drawing::Size(214, 21);
			this->instructorCombo->TabIndex = 2;
			this->instructorCombo->SelectedIndexChanged += gcnew System::EventHandler(this, &UISelectCourses::instructorCombo_SelectedIndexChanged);
			// 
			// Add Semester Combo Box
			// 
			this->semesterCombo->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->semesterCombo->FormattingEnabled = true;
			this->semesterCombo->Location = System::Drawing::Point(342, 219);
			this->semesterCombo->MaxLength = 100;
			this->semesterCombo->Name = L"semesterCombo";
			this->semesterCombo->Size = System::Drawing::Size(214, 21);
			this->semesterCombo->TabIndex = 3;
			// 
			// Add Courses Text Box 
			// 
			this->coursesTextBox->AcceptsReturn = true;
			this->coursesTextBox->AcceptsTab = true;
			this->coursesTextBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->coursesTextBox->Location = System::Drawing::Point(342, 246);
			this->coursesTextBox->Name = L"coursesTextBox";
			this->coursesTextBox->Size = System::Drawing::Size(214, 20);
			this->coursesTextBox->TabIndex = 4;
			// 
			// Add Instructor Label
			// 
			this->instructorLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->instructorLabel->AutoSize = true;
			this->instructorLabel->BackColor = System::Drawing::Color::White;
			this->instructorLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->instructorLabel->Location = System::Drawing::Point(263, 195);
			this->instructorLabel->Name = L"instructorLabel";
			this->instructorLabel->Size = System::Drawing::Size(73, 13);
			this->instructorLabel->TabIndex = 5;
			this->instructorLabel->Text = L"Add Instructor";
			this->instructorLabel->Click += gcnew System::EventHandler(this, &UISelectCourses::instructorLabel_Click);
			// 
			// Add Semester Label 
			// 
			this->semesterLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->semesterLabel->AutoSize = true;
			this->semesterLabel->BackColor = System::Drawing::Color::White;
			this->semesterLabel->Location = System::Drawing::Point(263, 222);
			this->semesterLabel->Name = L"semesterLabel";
			this->semesterLabel->Size = System::Drawing::Size(73, 13);
			this->semesterLabel->TabIndex = 6;
			this->semesterLabel->Text = L"Add Semester";
			// 
			// Add Courses Label 
			// 
			this->coursesLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->coursesLabel->AutoSize = true;
			this->coursesLabel->BackColor = System::Drawing::Color::White;
			this->coursesLabel->Location = System::Drawing::Point(234, 249);
			this->coursesLabel->Name = L"coursesLabel";
			this->coursesLabel->Size = System::Drawing::Size(102, 13);
			this->coursesLabel->TabIndex = 7;
			this->coursesLabel->Text = L"Add Course Number";
			// 
			// Added Courses Label 
			// 
			this->addedCoursesLabel ->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->addedCoursesLabel ->AutoSize = true;
			this->addedCoursesLabel ->BackColor = System::Drawing::Color::White;
			this->addedCoursesLabel ->Location = System::Drawing::Point(130, 310);
			this->addedCoursesLabel ->Name = L"addedCoursesLabel ";
			this->addedCoursesLabel ->Size = System::Drawing::Size(82, 13);
			this->addedCoursesLabel ->TabIndex = 8;
			this->addedCoursesLabel ->Text = L"Added Courses:";
			this->addedCoursesLabel ->Click += gcnew System::EventHandler(this, &UISelectCourses::addedCoursesLabel_Click);
			// 
			// Select All Button
			// 
			this->selAllBut->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->selAllBut->BackColor = System::Drawing::SystemColors::Control;
			this->selAllBut->Location = System::Drawing::Point(31, 327);
			this->selAllBut->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->selAllBut->Name = L"selAllBut";
			this->selAllBut->Size = System::Drawing::Size(81, 19);
			this->selAllBut->TabIndex = 9;
			this->selAllBut->Text = L"Select All";
			this->selAllBut->UseVisualStyleBackColor = false;
			// 
			// Remove All Button
			// 
			this->remAllBut->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->remAllBut->BackColor = System::Drawing::SystemColors::Control;
			this->remAllBut->Location = System::Drawing::Point(31, 350);
			this->remAllBut->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->remAllBut->Name = L"remAllBut";
			this->remAllBut->Size = System::Drawing::Size(81, 19);
			this->remAllBut->TabIndex = 10;
			this->remAllBut->Text = L"Remove All";
			this->remAllBut->UseVisualStyleBackColor = false;
			// 
			// Search Button
			// 
			this->searchBut->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->searchBut->BackColor = System::Drawing::SystemColors::Control;
			this->searchBut->Location = System::Drawing::Point(26, 474);
			this->searchBut->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->searchBut->Name = L"searchBut";
			this->searchBut->Size = System::Drawing::Size(86, 49);
			this->searchBut->TabIndex = 11;
			this->searchBut->Text = L"Search";
			this->searchBut->UseVisualStyleBackColor = false;
			this->searchBut->Click += gcnew System::EventHandler(this, &UISelectCourses::searchBut_Click);
			// 
			// UISelectCourses
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(881, 538);
			this->Controls->Add(this->searchBut);
			this->Controls->Add(this->remAllBut);
			this->Controls->Add(this->selAllBut);
			this->Controls->Add(this->addedCoursesLabel );
			this->Controls->Add(this->coursesLabel);
			this->Controls->Add(this->semesterLabel);
			this->Controls->Add(this->instructorLabel);
			this->Controls->Add(this->coursesTextBox);
			this->Controls->Add(this->semesterCombo);
			this->Controls->Add(this->instructorCombo);
			this->Controls->Add(this->addedCourCLB);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"UISelectCourses";
			this->Text = L"Course Selection";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking button in UIForm
	private: System::Void addedCoursesLabel_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string test = "test";
	}
private: System::Void searchBut_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void instructorCombo_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	std::string test = "test";
}
private: System::Void addedCourCLB_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	std::string test = "test";
}
private: System::Void instructorLabel_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}