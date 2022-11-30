#include "Header.h"

int main() {
	Aggressor aggr;
	aggr.generateInputData("Input.txt");
	std::vector<Aggressor> fileData = aggr.extractData("Input.txt");
	aggr.proccessOutputData(fileData, "Output.txt");
	std::cout << "Done";
}