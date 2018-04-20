#include <iostream>
#include <string>
#include <vector>

#include "LoadFiles.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char ** argv){

	// Load frames
	string path = "frames";
	if (argc == 2){
		path = string(argv[1]);
	}

	vector<Image> images = Image::loadImages(path, "image");
	cout << "Loaded all files to the RAM." << endl;

	return 0;	

}