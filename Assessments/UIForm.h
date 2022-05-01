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
		std::vector<int>* accountIds;	// Pointer to given vector of ints to store account ids
		std::string* auth;				// Pointer to given string to store authorisation key

		UIForm(std::vector<int>* accountIdsIn, std::string* authIn) {	// Constructor
			InitializeComponent();

			accountIds = accountIdsIn;	// Set accountIds pointer to given address
			auth = authIn;				// Set auth pointer to given address
		}

	protected:
		~UIForm() {	// Deconstructor
			if (components)
				delete components;
		}

		// Auto generated code
	private: System::Windows::Forms::Button^ enterBtn;
	private: System::Windows::Forms::TextBox^ authKey;
	private: System::Windows::Forms::Label^ canvasTokenLabel;
	protected:

	private:
		// Required designer variable.
		System::ComponentModel::Container^ components;

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
			this->canvasTokenLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// enterBtn
			// 
			this->enterBtn->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->enterBtn->AutoSize = true;
			this->enterBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->enterBtn->ForeColor = System::Drawing::SystemColors::ControlText;
			this->enterBtn->Location = System::Drawing::Point(489, 283);
			this->enterBtn->Margin = System::Windows::Forms::Padding(2);
			this->enterBtn->MaximumSize = System::Drawing::Size(112, 44);
			this->enterBtn->MinimumSize = System::Drawing::Size(112, 44);
			this->enterBtn->Name = L"enterBtn";
			this->enterBtn->Size = System::Drawing::Size(112, 44);
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
			this->authKey->Location = System::Drawing::Point(243, 283);
			this->authKey->Margin = System::Windows::Forms::Padding(2);
			this->authKey->MaximumSize = System::Drawing::Size(242, 55);
			this->authKey->MinimumSize = System::Drawing::Size(242, 55);
			this->authKey->Name = L"authKey";
			this->authKey->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->authKey->Size = System::Drawing::Size(242, 44);
			this->authKey->TabIndex = 1;
			// 
			// Canvas Token Label 
			// 
			this->canvasTokenLabel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->canvasTokenLabel->AutoSize = true;
			this->canvasTokenLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->canvasTokenLabel->Location = System::Drawing::Point(61, 284);
			this->canvasTokenLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->canvasTokenLabel->MaximumSize = System::Drawing::Size(173, 44);
			this->canvasTokenLabel->MinimumSize = System::Drawing::Size(112, 44);
			this->canvasTokenLabel->Name = L"canvasTokenLabel";
			this->canvasTokenLabel->Size = System::Drawing::Size(173, 44);
			this->canvasTokenLabel->TabIndex = 2;
			this->canvasTokenLabel->Text = L"Canvas Token:";
			this->canvasTokenLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(677, 371);
			this->Controls->Add(this->canvasTokenLabel);
			this->Controls->Add(this->authKey);
			this->Controls->Add(this->enterBtn);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
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