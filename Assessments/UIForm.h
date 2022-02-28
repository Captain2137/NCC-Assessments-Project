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

	/// <summary>
	/// Summary for UIForm
	/// </summary>
	public ref class UIForm : public System::Windows::Forms::Form {
	public:
		std::vector<int>* courses;	// Pointer to given vector to store course numbers

		// Constructor
		UIForm(std::vector<int>* in) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			courses = in;	// Set courses pointer to given address
		}

		String^ getAuth() { return auth; }	// Return authorisation key

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UIForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// Its here due to an auto code generation problem, move
		String^ auth = "";	// Contains authorisation key

		// Auto generated code
	private: System::Windows::Forms::Button^ enterBtn;
	private: System::Windows::Forms::TextBox^ authKey;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		// DO NOT MODIFY
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->enterBtn = (gcnew System::Windows::Forms::Button());
			this->authKey = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// enterBtn
			// 
			this->enterBtn->Location = System::Drawing::Point(195, 12);
			this->enterBtn->Name = L"enterBtn";
			this->enterBtn->Size = System::Drawing::Size(75, 23);
			this->enterBtn->TabIndex = 0;
			this->enterBtn->Text = L"Enter";
			this->enterBtn->UseVisualStyleBackColor = true;
			this->enterBtn->Click += gcnew System::EventHandler(this, &UIForm::enterBtn_Click);
			// 
			// authKey
			// 
			this->authKey->Location = System::Drawing::Point(12, 12);
			this->authKey->Name = L"authKey";
			this->authKey->Size = System::Drawing::Size(177, 22);
			this->authKey->TabIndex = 1;
			// 
			// UIForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->authKey);
			this->Controls->Add(this->enterBtn);
			this->Name = L"UIForm";
			this->Text = L"UIForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking button in UIForm
	private: System::Void enterBtn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
