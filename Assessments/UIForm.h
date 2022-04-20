#pragma once
#include <vector>
#include <string>

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
		std::string* auth;		// Pointer to given string to store authorisation key
		std::string* userName;	// Pointer to given string to store user name

		UIForm(std::string* authIn, std::string* userNameIn) {	// Constructor
			InitializeComponent();

			auth = authIn;			// Set auth pointer to given address
			userName = userNameIn;	// Set userName pointer to given address
		}

	protected:
		~UIForm() {	// Deconstructor
			if (components)
				delete components;
		}

		// Auto generated code
	private: System::Windows::Forms::Button^ enterBtn;
	private: System::Windows::Forms::TextBox^ authKey;
	private: System::Windows::Forms::Label^ label1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UIForm::typeid));
			this->enterBtn = (gcnew System::Windows::Forms::Button());
			this->authKey = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// enterBtn
			// 
			this->enterBtn->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->enterBtn->AutoSize = true;
			this->enterBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->enterBtn->ForeColor = System::Drawing::SystemColors::ControlText;
			this->enterBtn->Location = System::Drawing::Point(611, 354);
			this->enterBtn->Margin = System::Windows::Forms::Padding(2);
			this->enterBtn->MaximumSize = System::Drawing::Size(140, 55);
			this->enterBtn->MinimumSize = System::Drawing::Size(140, 55);
			this->enterBtn->Name = L"enterBtn";
			this->enterBtn->Size = System::Drawing::Size(140, 55);
			this->enterBtn->TabIndex = 0;
			this->enterBtn->Text = L"Enter";
			this->enterBtn->UseVisualStyleBackColor = true;
			this->enterBtn->Click += gcnew System::EventHandler(this, &UIForm::enterBtn_Click);
			// 
			// authKey
			// 
			this->authKey->AcceptsReturn = true;
			this->authKey->AcceptsTab = true;
			this->authKey->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->authKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24));
			this->authKey->ForeColor = System::Drawing::Color::Black;
			this->authKey->Location = System::Drawing::Point(304, 354);
			this->authKey->Margin = System::Windows::Forms::Padding(2);
			this->authKey->MaximumSize = System::Drawing::Size(302, 55);
			this->authKey->MinimumSize = System::Drawing::Size(302, 55);
			this->authKey->Name = L"authKey";
			this->authKey->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->authKey->Size = System::Drawing::Size(302, 53);
			this->authKey->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(76, 355);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->MaximumSize = System::Drawing::Size(216, 55);
			this->label1->MinimumSize = System::Drawing::Size(140, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(214, 55);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Canvas Token:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(846, 464);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->authKey);
			this->Controls->Add(this->enterBtn);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"UIForm";
			this->Text = L"Canvas Token Form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking button in UIForm
	private: System::Void enterBtn_Click(System::Object^ sender, System::EventArgs^ e);

};
}