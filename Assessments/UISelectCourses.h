#pragma once
#include <vector>

namespace Assessments {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class UISelectCourses : public System::Windows::Forms::Form {
	public:
		std::vector<int>* courses;	// Pointer to given vector to store course numbers

		UISelectCourses(std::vector<int>* in) {
			InitializeComponent();
			
			courses = in;	// Set courses pointer to given address
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UISelectCourses()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// UISelectCourses
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(493, 393);
			this->Name = L"UISelectCourses";
			this->Text = L"UISelectCourses";
			this->ResumeLayout(false);

		}
#pragma endregion
		// Auto generated code by double clicking button in UIForm
	private: System::Void enterBtn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
