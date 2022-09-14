#include "SortLib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>

// Helper functions:
template <typename T>
void printArr(T* arr, int size){
    for (int j = 0; j < size; j++){
        std::cout << arr[j] << " ";
    }
    std::cout << std::endl;
}

// Will be used to check if -o/-a/-i is given as an argument:
bool checkIfInVector(std::vector<std::string> v, std::string item){
	for (int i = 0; i < v.size(); i++){
		if (v.at(i) == item){
			return true;
		}
	}
	return false;
}

// Functions that return the the argument following -o/-a/-i
std::string getArgument(std::vector<std::string> v, std::string item){
	for (int i = 0; i < v.size()-1; i++){
		if (v.at(i) == item){
			return v.at(i+1);
		}
	}
	return "";
}


int main(int argc, char* argv[]) {
	std::vector<std::string> arguments;

	if (argc < 3) { // must have at least 3 arguments for ./sort -a <algorithm>
		std::cerr << "Usage: " << argv[0] << " -a <algorithm> [-i <infile> -o <outfile> -t]" << std::endl;
        return 1;
	}else{
		for (int i = 1; i < argc; i++){
			arguments.push_back(argv[i]);
			//std::cout << "Arg " << i-1 << ": " << arguments.at(i-1) << std::endl;
		}
	}

	// Parse the arguments
	// You can assume if -a is present, so is the algorithm
	// And if -i is present, so is the filename, and so on

	bool iFileGiven = checkIfInVector(arguments, "-i");
	if (!iFileGiven){
		iFileGiven = checkIfInVector(arguments, "[-i");
	}

	bool oFileGiven = checkIfInVector(arguments, "-o");

	bool wantsTimePrinted = checkIfInVector(arguments, "-t");
	if (!wantsTimePrinted){
		wantsTimePrinted = checkIfInVector(arguments, "-t]");
	}

	// Read the input data
	// If a file was provided with -i, read from the file
	// Else, read from stdin (cin)
	
	int size;
	int* arr;
	if (!iFileGiven){
		std::cin >> size;
		arr = new int[size];
		for (int i = 0; i < size; i++){
			std::cin >> arr[i];
		}
	}else{
		std::string iFileName;
		//std::cout << "the filename is " << arguments.at(3) << std::endl;
		iFileName = getArgument(arguments, "-i");
		if (iFileName.empty()){
			iFileName = getArgument(arguments, "[-i");
		}
		std::fstream file;
		
		try{
			file.open(iFileName);
		}catch(...){
			std::cerr << "Unable to open input file." << std::endl;
			return 1;
		}

		// Read the file and fill up the array:
		file >> size;
		arr = new int[size];
		int index = 0;

		while (!file.eof()){
			file >> arr[index];
			index++;
		}
		file.close();
	}
	// Set up your timer
	// You can use the included "chrono" library from C++11!
	// Hint: The following line of code would give you the current time
	auto start = std::chrono::high_resolution_clock::now();

	// Apply the sorting algorithm based on the given argument
	std::string algo = getArgument(arguments, "-a");

	if (algo == "counting"){
		SortLib::CountingSort(arr, size);

	}else if (algo == "selection"){
		SortLib::SelectionSort(arr, size);

	}else if (algo == "quick"){
		SortLib::QuickSort(arr, size);

	}else{return 1;}

	// Stop your timer and find the difference
	// Hint: The following line can compute the difference of two times in microseconds
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	// Write the output data
	// If a file was provided with -o, write to that file
	// Else, write to stdout (cout)
	if (oFileGiven){
		std::string oFileName = getArgument(arguments, "-o");

		if (oFileName.at(oFileName.size()-1) == ']'){
			oFileName.pop_back();
		}

		std::ofstream output;
		try{
		output.open(oFileName);
		}catch(...){
			std::cerr << "Unable to open output file." << std::endl;
			return 1;
		}
		for (int i = 0; i < size; i++){
			if (i != size-1){
				output << arr[i] << " ";
			}else{
				output << arr[i] << "\n";
			}
		}
		/*if (wantsTimePrinted){
			output << "Elapsed Time: " << duration.count() << std::endl;
		}*/
		output.close();
	}else{
		for (int i = 0; i < size; i++){
			if (i != size-1){
				std::cout << arr[i] << " ";
			}else{
				std::cout << arr[i] << "\n";
			}
		}
	}

	// If -t was set, print the elapsed time as "Elapsed Time: <duration>"
	if (wantsTimePrinted){
		std::cout << "Elapsed Time: " << duration.count() << std::endl;
	}

	// Cleanup; remember to delete your dynamic data array!
	delete [] arr;
	return 0;
}