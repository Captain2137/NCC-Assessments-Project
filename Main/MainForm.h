#pragma once

#include <iostream>
#include <string>

namespace Main {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	public: 
		std::string getBookstoreCSV() {
			// Thanks to: https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-system-string-to-standard-string?view=msvc-160
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(this->openFileDialogTestCsv->FileName)).ToPointer();
			std::string str = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			return str;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialogTestCsv;
	private: System::Windows::Forms::Button^ btnSelectFile;


	private: String^ bookstoreCSV; // Thanks to: https://stackoverflow.com/a/50283183

	protected:

	protected:

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
			this->openFileDialogTestCsv = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnSelectFile = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialogTestCsv
			// 
			this->openFileDialogTestCsv->DefaultExt = L"csv";
			this->openFileDialogTestCsv->InitialDirectory = L"\\%USERPROFILE%\\Downloads";
			this->openFileDialogTestCsv->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::openFileDialogBookstore_FileOk);
			// 
			// btnSelectFile
			// 
			this->btnSelectFile->Location = System::Drawing::Point(13, 13);
			this->btnSelectFile->Name = L"btnSelectFile";
			this->btnSelectFile->Size = System::Drawing::Size(259, 23);
			this->btnSelectFile->TabIndex = 0;
			this->btnSelectFile->Text = L"Select Test .csv File";
			this->btnSelectFile->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btnSelectFile->UseVisualStyleBackColor = true;
			this->btnSelectFile->Click += gcnew System::EventHandler(this, &MainForm::btnBookstore_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btnSelectFile);
			this->Name = L"MainForm";
			this->Text = L"Assessments";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void openFileDialogBookstore_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	}

	private: System::Void btnBookstore_Click(System::Object^ sender, System::EventArgs^ e) {
		this->openFileDialogTestCsv->ShowDialog();

	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
