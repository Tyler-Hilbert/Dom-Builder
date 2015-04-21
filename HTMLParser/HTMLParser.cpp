#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stack>


using namespace std; 

// Stack of important tags
class tagsList : public stack<string> {
public:
	bool inWritableTag() {
		return (empty() || top() == "<body");
	}
};


void parse(string &parsed, string &line, tagsList &tags);


int main(int argc, const char** argv) {
	ifstream infile("D:\\Documents\\Computer Science\\masonacm.org.htm");

	if (infile) {
		// Read file
		string fileData((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
		infile.close();

		// Parse
		string parsed = "";
		tagsList tags;
		parse(parsed, fileData, tags);

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
void parse(string &parsed, string &in, tagsList &tags) {	
	// Check for tag
	int tagIndex = in.find_first_of('<');

	if (tagIndex != -1) {
		// Add line up to the tag
		string beforeTag = in.substr(0, tagIndex);
		boost::algorithm::trim(beforeTag);
		if (!beforeTag.empty() && tags.inWritableTag()) {
			parsed += beforeTag + "\n";
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

		in = in.substr(endTagIndex + 1);


		// Continue parsing
		parse(parsed, in, tags);
	} 
}


