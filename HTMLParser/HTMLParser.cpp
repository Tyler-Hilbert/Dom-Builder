#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>


using namespace std; 


void parseLine(string &parsed, string &line, bool &inBody, bool &inScript);
void replaceAll(string& str, const string& from, const string& to);
int getTagIndex(string &line);


// vector of all the tags
vector<string> tags = { "<!DOCTYPE", "<!--", "<B", "<EM", "<FORM", "<BR", "<BUTTON", 
						"<HTML", "<HEAD", "<META", "<BODY", "<DIV", "<UL", "<H1", "<LI", "<A", "<SCRIPT", 
						"</HTML", "</HEAD", "</B", "</EM", "</FORM", "</BODY", "</BUTTON", 
						"</DIV", "</UL", "</H1", "</LI", "</A", "</SCRIPT", "<H", "</H", "<IMG", "</IMG", 
						"<SPAN", "</SPAN", "<TITLE", "</TITLE", "<INPUT", "</INPUT", "<SELECT", "</SELECT",
						"<OPTION", "</OPTION", "<TABLE", "</TABLE", "<TR", "</TR", "<TD", "</TD", "<STYLE", "</STYLE",
						"<FONT", "</FONT", "<P", "</P" };


int main(int argc, const char** argv) {
	string parsed = ""; // The parsed html

	string line;
	ifstream myfile("D:\\Documents\\Computer Science\\Cryptology\\decryption.html");

	bool inBody = false;
	bool inScript = false;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			replaceAll(line, "\t", "");
			replaceAll(line, "&nbsp;", "");
			parseLine(parsed, line, inBody, inScript);
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
void parseLine(string &parsed, string &line, bool &inBody, bool &inScript) {
	// Make upper case upperLine
	boost::algorithm::trim(line);
	string upperLine;
	for (int i = 0; i < line.length(); i++) {
		upperLine += toupper(line[i]);
	}
	
	if (inBody) {
		int tagIndex = upperLine.find("</BODY");
		if (tagIndex != -1) {
			line = line.substr(0, tagIndex - 1);
			upperLine = upperLine.substr(0, tagIndex - 1);
			inBody = false;
		}
	} else {
		int tagIndex = upperLine.find("<BODY");
		if (tagIndex != -1) {
			// Get to body tag
			line = line.substr(tagIndex);
			upperLine = upperLine.substr(tagIndex);
			// Remove tag
			int endTagIndex = line.find(">");
			if (endTagIndex == -1) {
				return;
			}
			line = line.substr(endTagIndex + 1);
			upperLine = upperLine.substr(endTagIndex + 1);

			inBody = true;

			parseLine(parsed, line, inBody, inScript);
		}
	}

	
	if (inScript) {
		int tagIndex = upperLine.find("</SCRIPT");
		if (tagIndex != -1) {
			line = line.substr(tagIndex);
			upperLine = upperLine.substr(tagIndex);
			inScript = false;
		}
	} else {
		int tagIndex = upperLine.find("<SCRIPT");

		if (tagIndex != -1) {

 			if (tagIndex != 0) { // Add any html before script tag
				string preScript = line.substr(0, tagIndex - 1);
				parseLine(parsed, preScript, inBody, inScript);
			}

			line = line.substr(tagIndex);
			upperLine = upperLine.substr(tagIndex);


			// Remove tag
			int endTagIndex = line.find(">");
			if (endTagIndex == -1) {
				return;
			}
			line = line.substr(endTagIndex + 1);
			upperLine = upperLine.substr(endTagIndex + 1);

			inScript = true;

			parseLine(parsed, line, inBody, inScript);
		}
	}
	
	if (inBody && !inScript) {
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
				parseLine(parsed, removedTag, inBody, inScript);
			}
		} else if (!line.empty()) {
			parsed += line;
		}
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
