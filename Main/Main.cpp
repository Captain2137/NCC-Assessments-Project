// Thanks to: http://y-okamoto-psy1949.la.coocan.jp/VCpp/OnVSCpp2019/en/ for this setup
// Thanks to: https://docs.microsoft.com/en-us/cpp/ide/walkthrough-deploying-your-program-cpp?view=msvc-160

#include "CommandLine.h"
#include "CSV.h"
#include "MainForm.h"

[Main::STAThreadAttribute]

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		Main::MainForm mainForm;
		mainForm.ShowDialog();
		std::string bookstoreCSV = mainForm.getBookstoreCSV();
		std::cout << bookstoreCSV << std::endl;
		CSV csv;
		csv.tokenize(bookstoreCSV);
		std::cin.get();
		return 0;
	}
	else {
		return Main::CommandLine(argc, argv);
	}
}