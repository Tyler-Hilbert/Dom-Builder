#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stack>
#include "View.h"
#include <thread>
#include <mutex>
#include "Page.h"

using namespace std; 

// Stack of important tags
class tagsList : public stack<string> {
public:
	bool inWritableTag() {
		return (empty() || top() == "<body");
	}
};


void parse(string &line, tagsList &tags, int &tagIndex, string &text, mutex &mutex); // Parses up to tag
void print(string &line, string &text, mutex &mutex); // Adds parsed html to text string
void createGui(string &text, mutex &mutex); // Starts the gui thread
bool nextTagIs(string &in, int &tagIndex, string tag); // Checks if the tag at the given index is the passed tag

int main(int argc, const char** argv) {
	// Create gui thread
	string text;
	mutex mutex;
	thread thread(&createGui, ref(text), ref(mutex));
	thread.detach();

	// Read page
	Page page;
	string in = page.getPage("http://httpbin.org");

	// Parse the returned page
	if (in.empty()) {
		text = "unable to read url";
	} else {
		tagsList tags;

		int tagIndex = in.find_first_of('<'); 	// Check for tag

		try {
			do {
				parse(in, tags, tagIndex, text, mutex);
				tagIndex = in.find_first_of('<');
			} while (tagIndex != -1);
		}
		catch (int e) {
			text = e;
		}
	}

	system("pause");
	return 0;
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parse(string &in, tagsList &tags, int &tagIndex, string &text, mutex &mutex) {	
	// Add line up to the tag
	string beforeTag = in.substr(0, tagIndex);
	boost::algorithm::trim(beforeTag);
	if (!beforeTag.empty() && tags.inWritableTag()) { 
		print(beforeTag, text, mutex);
	}

	// Add important tag to stack
	if (nextTagIs(in, tagIndex, "<script"))
		tags.push("<script");
	else if (nextTagIs(in, tagIndex, "<style"))
		tags.push("<style");
	else if (nextTagIs(in, tagIndex, "<body"))
		tags.push("<body");

	// Remove tag
	in = in.substr(tagIndex);
	int endTagIndex = in.find_first_of('>');
	if (endTagIndex == -1) {
		return; // TODO: make a better handling
	}

	// Remove tag from stack
	if (nextTagIs(in, tagIndex, "</script"))
		tags.pop();
	else if (nextTagIs(in, tagIndex, "</style"))
		tags.pop();
	else if (nextTagIs(in, tagIndex, "</body"))
		tags.pop();

	// Update in string
	in = in.substr(endTagIndex + 1);
}

/**
  *	Adds parsed HTML to the text string
  */
void print(string &line, string &text, mutex &mutex) {
	// Decode html entities
	int tagIndex = line.find_first_of('&');
	while (tagIndex != -1) {
		line.substr(tagIndex);

		if (boost::iequals(line.substr(0, 5), "amp;")) {
			mutex.lock();
			text += "&";
			mutex.unlock();
			line = line.substr(4);
		} else if (boost::iequals(line.substr(tagIndex, 4), "lt;")) {
			mutex.lock();
			text += "<";
			mutex.unlock();
			line = line.substr(3);
		} else if (boost::iequals(line.substr(tagIndex, 4), "gt;")) {
			mutex.lock();
			text += ">";
			mutex.unlock();
			line = line.substr(3);
		} else {
			line = line.substr(line.find_first_of(';') + 1); // Remove other entities
		}

		tagIndex = line.find_first_of('&');
	}

	// Output
	if (!line.empty()) {
		mutex.lock();
		text = text + line + "\n";
		mutex.unlock();
	}
}

/**
  * Creates the view, should be called as a thread
  */
void createGui(string &text, mutex &mutex) {
	// Display View
	View view(text, mutex);
}

/**
  * Checks if the next tag starting at tagIndex is the passed tag
  */
bool nextTagIs(string &in, int &tagIndex, string tag) {
	return (in.length() >= tagIndex + tag.length() && boost::iequals(in.substr(tagIndex, tag.length()), tag));
}
