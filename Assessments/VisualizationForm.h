#pragma once
#include "CourseData.h"
#include <vector>
#include <string>

namespace Assessments {
	// Needed for Windows Form
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class VisualizationForm : public System::Windows::Forms::Form {
	public:
		// Constructor takes in vector of CourseData
		VisualizationForm(std::vector<CourseData>* in);

	protected:
		~VisualizationForm() {	// Deconstructor
			if (components)
				delete components;
		}

		// Auto generated code
	private: System::Windows::Forms::TextBox^ textBox1;

	private:
		System::ComponentModel::Container ^components;	// Required designer variable.

		// DO NOT MODIFY
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(892, 853);
			this->textBox1->TabIndex = 0;
			// 
			// VisualizationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(916, 877);
			this->Controls->Add(this->textBox1);
			this->Name = L"VisualizationForm";
			this->Text = L"VisualizationForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Auto generated code by double clicking item in UIForm
	};
}
