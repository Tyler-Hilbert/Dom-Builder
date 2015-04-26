#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stack>
#include "View.h"


using namespace std; 

// Stack of important tags
class tagsList : public stack<string> {
public:
	bool inWritableTag() {
		return (empty() || top() == "<body");
	}
};


void parse(string &line, tagsList &tags, int &tagIndex, string &text);
void print(string &line, string &text);


int main(int argc, const char** argv) {
	ifstream infile("D:\\Documents\\Computer Science\\Web\\tpb.htm");

	if (infile) {
		// Read file
		string in((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
		infile.close();

		// Parse
		tagsList tags;
		string text;
		// Check for tag
		int tagIndex = in.find_first_of('<');
		do {
			parse(in, tags, tagIndex, text);
			tagIndex = in.find_first_of('<');
		} while (tagIndex != -1);


		// Display View
		View view(text);


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
void parse(string &in, tagsList &tags, int &tagIndex, string &text) {	
	// Add line up to the tag
	string beforeTag = in.substr(0, tagIndex);
	boost::algorithm::trim(beforeTag);
	if (!beforeTag.empty() && tags.inWritableTag()) { 
		print(beforeTag, text);
	}

	// Add important tag to stack
	if (boost::iequals(in.substr(tagIndex, 7), "<script"))
		tags.push("<script");
	else if (boost::iequals(in.substr(tagIndex, 6), "<style"))
		tags.push("<style");
	else if (boost::iequals(in.substr(tagIndex, 5), "<body"))
		tags.push("<body");

	// Remove tag
	in = in.substr(tagIndex);
	int endTagIndex = in.find_first_of('>');
	if (endTagIndex == -1) {
		return; // TODO: make a better handling
	}

	// Remove tag from stack
	if (boost::iequals(in.substr(tagIndex, 8), "</script"))
		tags.pop();
	else if (boost::iequals(in.substr(tagIndex, 7), "</style"))
		tags.pop();
	else if (boost::iequals(in.substr(tagIndex, 6), "</body"))
		tags.pop();

	// Update in string
	in = in.substr(endTagIndex + 1);
}

void print(string &line, string &text) {
	// Decode html entities
	int tagIndex = line.find_first_of('&');
	while (tagIndex != -1) {
		line.substr(tagIndex);

		if (boost::iequals(line.substr(0, 5), "amp;")) {
			text += "&";
			line = line.substr(4);
		} else if (boost::iequals(line.substr(tagIndex, 4), "lt;")) {
			text += "<";
			line = line.substr(3);
		} else if (boost::iequals(line.substr(tagIndex, 4), "gt;")) {
			text += ">";
			line = line.substr(3);
		} else {
			line = line.substr(line.find_first_of(';') + 1); // Remove other entities
		}

		tagIndex = line.find_first_of('&');
	}

	// Output
	if (!line.empty()) {
		text = text + line + "\n";
	}
}


