#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>


using namespace std; 


void parseLine(string &parsed, string &line);
void replaceAll(string& str, const string& from, const string& to);
int getTagIndex(string &line);

// vector of all the tags
vector<string> tags = { "<!DOCTYPE", "<!--", "<B", "<EM", "<FORM", "<BR", "<BUTTON", 
						"<HTML", "<HEAD", "<META", "<BODY", "<DIV", "<UL", "<H1", "<LI", "<A", "<SCRIPT", 
						"</HTML", "</HEAD", "</B", "</EM", "/FORM", "</BODY", "</BUTTON", 
						"</DIV", "</UL", "</H1", "</LI", "</A", "</SCRIPT", "<H", "</H", "<IMG", "</IMG", 
						"<SPAN", "</SPAN", "<TITLE", "</TITLE"};


int main(int argc, const char** argv) {
	string parsed = ""; // The parsed html

	string line;
	ifstream myfile("D:\\Documents\\Computer Science\\Cryptology\\index.html");

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			replaceAll(line, "\t", "");
			parseLine(parsed, line);
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
		system("pause");
		return 0;
	}

	cout << parsed;

	system("pause");
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parseLine(string &parsed, string &line) {
	// Make upper case upperLine
	boost::algorithm::trim(line);
	string upperLine;
	for (int i = 0; i < line.length(); i++) {
		upperLine += toupper(line[i]);
	}

	// Check for tag
	int tagIndex = getTagIndex(upperLine);

	if (tagIndex != -1) {
		// Add line up to the tag
		if (tagIndex != 0) {
			parsed += line.substr(0, tagIndex) + "\n";
		}

		// Remove tag
		string removedTag = line.substr(tagIndex);
		int endTagIndex = removedTag.find(">");
		if (endTagIndex == -1) {
			return;
		}
		removedTag = removedTag.substr(endTagIndex + 1);

		// Check for more tags in line
		if (removedTag.size() != 0) {
			parseLine(parsed, removedTag);
		}
	} else if (!line.empty()) {
		parsed += line + "\n";
	}
}

/**
 *  returns the index of the lowest tag in the string
 */
int getTagIndex(string &line) {
	int lowIndex = -1; // The first index of a tag found
	for (int i = 0; i < tags.size(); i++) {
		int tagIndex = line.find(tags[i]);
		if (tagIndex != -1 && (lowIndex == -1 || tagIndex < lowIndex)) {
			lowIndex = tagIndex;
		}
	}

	return lowIndex;
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
