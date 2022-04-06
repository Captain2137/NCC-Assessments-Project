#pragma once
#include <vector>

namespace Assessments {
	// Needed for windows forms
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class UIForm : public System::Windows::Forms::Form {
	public:
		std::vector<int>* courses;	// Pointer to given vector to store course numbers

		UIForm(std::vector<int>* in) {	// Constructor
			InitializeComponent();

			courses = in;	// Set courses pointer to given address
		}

		String^ getAuth() { return auth; }	// Return authorisation key

	protected:
		~UIForm() {	// Deconstructor
			if (components)
				delete components;
		}

		// Its here due to an auto code generation problem, move after finished
		String^ auth = "";	// Contains authorisation key

		// Auto generated code
	private: System::Windows::Forms::Button^ enterBtn;
	private: System::Windows::Forms::TextBox^ authKey;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UIForm::typeid));
			this->enterBtn = (gcnew System::Windows::Forms::Button());
			this->authKey = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->SuspendLayout();
			// 
			// enterBtn
			// 
			this->enterBtn->Location = System::Drawing::Point(215, 81);
			this->enterBtn->Margin = System::Windows::Forms::Padding(2);
			this->enterBtn->Name = L"enterBtn";
			this->enterBtn->Size = System::Drawing::Size(56, 19);
			this->enterBtn->TabIndex = 0;
			this->enterBtn->Text = L"Enter";
			this->enterBtn->UseVisualStyleBackColor = true;
			this->enterBtn->Click += gcnew System::EventHandler(this, &UIForm::enterBtn_Click);
			// 
			// authKey
			// 
			this->authKey->Location = System::Drawing::Point(77, 81);
			this->authKey->Margin = System::Windows::Forms::Padding(2);
			this->authKey->Name = L"authKey";
			this->authKey->Size = System::Drawing::Size(134, 20);
			this->authKey->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 84);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"API Key:";
			this->label1->Click += gcnew System::EventHandler(this, &UIForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(20, 106);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(51, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Class List";
			this->label2->Click += gcnew System::EventHandler(this, &UIForm::label2_Click);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->IntegralHeight = false;
			this->checkedListBox1->Location = System::Drawing::Point(77, 106);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(120, 96);
			this->checkedListBox1->TabIndex = 4;
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(650, 463);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->authKey);
			this->Controls->Add(this->enterBtn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"UIForm";
			this->Text = L"UIForm";
			this->Load += gcnew System::EventHandler(this, &UIForm::UIForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking button in UIForm
	private: System::Void enterBtn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void UIForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
