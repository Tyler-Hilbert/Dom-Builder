#include "FileReader.h"
#include <iostream>
#include <fstream>

string FileReader::getFile(string &path) {
	string line;
	string contents;
	ifstream myfile(path);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			contents.append(line + '\n');
		}
		myfile.close();
	}

	return contents;
}