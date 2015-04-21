#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>


using namespace std; 


void parse(string &parsed, string &line);
void replaceAll(string& str, const string& from, const string& to);


int main(int argc, const char** argv) {
	//ifstream infile("D:\\Documents\\Computer Science\\Cryptology\\decryption.html");
	ifstream infile("D:\\Documents\\Computer Science\\static-html.txt");

	if (infile) {
		// Read file
		string fileData((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
		infile.close();

		// Prepare file to parse
		//replaceAll(fileData, "\t", "");
		//replaceAll(fileData, "&nbsp;", "");

		// Parse
		string parsed = "";
		bool inBody = false;
		bool inScript = false;
		parse(parsed, fileData);

		// Output
		cout << parsed;
		system("pause");

		return 0;
	} else {
		cout << "file not found!\n";
		system("pause");
		return -1;
	}
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parse(string &parsed, string &in) {	
	// Check for tag
	int tagIndex = in.find_first_of('<');

	if (tagIndex != -1) {
		// Add line up to the tag
		string beforeTag = in.substr(0, tagIndex);
		boost::algorithm::trim(beforeTag);
		if (!beforeTag.empty()) {
			parsed += beforeTag + "\n";
		}

		// Remove tag
		in = in.substr(tagIndex);
		int endTagIndex = in.find_first_of('>');
		if (endTagIndex == -1) {
			return; // TODO: make a better handling
		}
		in = in.substr(endTagIndex + 1);

		// Continue parsing
		parse(parsed, in);
	} 
}

	

void replaceAll(string& str, const string& from, const string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
