#include "VisualizationForm.h"
#include <msclr/marshal_cppstd.h>   // Needed to convert String to String^

Assessments::VisualizationForm::VisualizationForm(std::vector<CourseData>* in) {
	InitializeComponent();

	// Go through courses vector and add data to textBox1 for each course
	for (int i = 0; i < 1; i++) {	// Replace 1 with (int)in->size() when course data works

		// Add course info and Competencies label
		textBox1->Text += in->at(i).getYear() + " ";
		textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getSemester() + " ");
		textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getCode() + " ");
		textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getName() + " ");
		textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getSection() + " ");
		textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getProf() + " ");
		textBox1->Text += in->at(i).getCourseNum() + ":\r\nCompetencies: ";

		// Loops through comps vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getComps()->size(); j++) {
			textBox1->Text += msclr::interop::marshal_as<String^>(in->at(i).getComps()->at(j) + " / ");
		}
		textBox1->Text += "\r\n";	// Next line

		// Loops through comps vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getData()->size(); j++) {
			textBox1->Text += "Student " + (j + 1) + ": ";
			for (int k = 0; k < (int)in->at(i).getData()->at(j).size(); k++) {
				textBox1->Text += in->at(i).getData()->at(j).at(k) + " ";
			}
			textBox1->Text += "\r\n";	// Next line
		}

		textBox1->Text += "Average: "; // Add average label

		// Loops through average vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getAverage()->size(); j++) {
			textBox1->Text += in->at(i).getAverage()->at(j) + " ";
		}
		textBox1->Text += "\r\n";	// Next line

		textBox1->Text += "Median: "; // Add median label

		// Loops through median vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getMedian()->size(); j++) {
			textBox1->Text += in->at(i).getMedian()->at(j) + " ";
		}
		textBox1->Text += "\r\n";	// Next line

		textBox1->Text += "Percent: ";	// Add percent label

		// Loops through percent vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getPercent()->size(); j++) {
			textBox1->Text += in->at(i).getPercent()->at(j) + "% ";
		}
		textBox1->Text += "\r\n";	// Next line

		textBox1->Text += "Deviation: "; // Add deviation label

		// Loops through deviation vector adding each to text box
		for (int j = 0; j < (int)in->at(i).getDeviation()->size(); j++) {
			textBox1->Text += in->at(i).getDeviation()->at(j) + " ";
		}
		textBox1->Text += "\r\n";	// Next line
	}
}
