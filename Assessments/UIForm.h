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
			this->enterBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->enterBtn->Location = System::Drawing::Point(603, 351);
			this->enterBtn->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->enterBtn->Name = L"enterBtn";
			this->enterBtn->Size = System::Drawing::Size(149, 44);
			this->enterBtn->TabIndex = 0;
			this->enterBtn->Text = L"Enter";
			this->enterBtn->UseVisualStyleBackColor = true;
			this->enterBtn->Click += gcnew System::EventHandler(this, &UIForm::enterBtn_Click);
			// 
			// authKey
			// 
			this->authKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->authKey->Location = System::Drawing::Point(239, 351);
			this->authKey->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->authKey->Name = L"authKey";
			this->authKey->Size = System::Drawing::Size(360, 44);
			this->authKey->TabIndex = 1;
			this->authKey->TextChanged += gcnew System::EventHandler(this, &UIForm::authKey_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(85, 351);
			this->label1->MinimumSize = System::Drawing::Size(149, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 44);
			this->label1->TabIndex = 2;
			this->label1->Text = L"API Key:";
			this->label1->Click += gcnew System::EventHandler(this, &UIForm::label1_Click);
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(859, 489);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->authKey);
			this->Controls->Add(this->enterBtn);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
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
private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void authKey_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
