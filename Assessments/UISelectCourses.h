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
	private: System::Windows::Forms::Button^ button1;
	public:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
		   cliext::vector<String^> courseTeachers;	// Vector of strings to store course teacher names

		UISelectCourses(std::string* authIn, std::string* userNameIn, std::vector<int>* courseNumsIn);

	protected:
		~UISelectCourses() {
			if (components)
				delete components;
		}

		// Auto generated code
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ comboBox2;
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
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->checkedListBox1->CheckOnClick = true;
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(177, 402);
			this->checkedListBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(805, 242);
			this->checkedListBox1->TabIndex = 0;
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(456, 236);
			this->comboBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBox1->MaxLength = 100;
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(284, 24);
			this->comboBox1->TabIndex = 2;
			// 
			// comboBox2
			// 
			this->comboBox2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(456, 270);
			this->comboBox2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->comboBox2->MaxLength = 100;
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(284, 24);
			this->comboBox2->TabIndex = 3;
			// 
			// textBox1
			// 
			this->textBox1->AcceptsReturn = true;
			this->textBox1->AcceptsTab = true;
			this->textBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBox1->Location = System::Drawing::Point(456, 303);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(284, 22);
			this->textBox1->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Location = System::Drawing::Point(351, 240);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(96, 17);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Add Instructor";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(351, 273);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 17);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Add Semester";
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(312, 306);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(136, 17);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Add Course Number";
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(174, 381);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(109, 17);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Added Courses:";
			this->label4->Click += gcnew System::EventHandler(this, &UISelectCourses::label4_Click);
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->Location = System::Drawing::Point(41, 402);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 23);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Select All";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// button2
			// 
			this->button2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->Location = System::Drawing::Point(41, 431);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(108, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Remove All";
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button3->BackColor = System::Drawing::SystemColors::Control;
			this->button3->Location = System::Drawing::Point(35, 584);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(114, 60);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Search";
			this->button3->UseVisualStyleBackColor = false;
			// 
			// UISelectCourses
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1175, 662);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->checkedListBox1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"UISelectCourses";
			this->Text = L"UISelectCourses";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking button in UIForm
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}