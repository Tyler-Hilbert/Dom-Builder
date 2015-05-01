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
#include "Node.h"
#include "DomTree.h"

using namespace std; 


void parse(string &line, DomTree &domTree, int &tagIndex, mutex &mutex); // Parses up to tag
bool nextTagIs(string &in, int &tagIndex, string tag); // Checks if the tag at the given index is the passed tag
void addNode(string &line, DomTree &domTree, mutex &mutex); // Adds parsed html to text string
void decodeHTML(string &line); // Decodes the html character entities
void createGui(DomTree &domTree, mutex &mutex); // Starts the gui thread

bool writable = false;

int main(int argc, const char** argv) {
	DomTree domTree;
	Node root;
	root.setTag("HTML");
	domTree.setRoot(root);

	// Create gui thread
	mutex mutex;
	thread thread(&createGui, ref(domTree), ref(mutex));
	thread.detach();

	// Read page
	Page page;
	string in = page.getPage("http://httpbin.org");

	// Parse the returned page
	if (in.empty()) {
		// ToDO: add error handling here
	} else {
		// Check for and loop through tags
		int tagIndex = in.find_first_of('<'); 	
		try {
			do {
				parse(in, domTree, tagIndex, mutex);
				tagIndex = in.find_first_of('<');
			} while (tagIndex != -1);
		}
		catch (int e) {
			// TODO:: Improve handling
		}
	}

	system("pause");
	return 0;
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parse(string &in, DomTree &domTree, int &tagIndex,  mutex &mutex) {	
	// Add line up to the tag
	string beforeTag = in.substr(0, tagIndex);
	boost::algorithm::trim(beforeTag);
	if (!beforeTag.empty() && writable) { 
		addNode(beforeTag, domTree, mutex);
	}

	// Set if the element is inside a writable element
	if (nextTagIs(in, tagIndex, "<script"))
		writable = false;
	else if (nextTagIs(in, tagIndex, "<style"))
		writable = false;
	else if (nextTagIs(in, tagIndex, "<body"))
		writable = true;

	// Remove tag
	in = in.substr(tagIndex);
	int endTagIndex = in.find_first_of('>');
	if (endTagIndex == -1) {
		return; // TODO: make a better handling
	}

	// Set if the element is inside a writable element
	if (nextTagIs(in, tagIndex, "</script"))
		writable = true;
	else if (nextTagIs(in, tagIndex, "</style"))
		writable = true;
	else if (nextTagIs(in, tagIndex, "</body"))
		writable = false;

	// Update in string
	in = in.substr(endTagIndex + 1);
}

/**
  * Checks if the next tag starting at tagIndex is the passed tag
  */
bool nextTagIs(string &in, int &tagIndex, string tag) {
	return (in.length() >= tagIndex + tag.length() && boost::iequals(in.substr(tagIndex, tag.length()), tag));
}

/**
  *	Adds parsed HTML to the DOMTree
  */
void addNode(string &line, DomTree &domTree, mutex &mutex) {
	decodeHTML(line);
	// Output
	if (!line.empty()) {
		mutex.lock();
		Node node;
		node.setTag("Test"); // TODO: Fix this
		node.setContent(line);
		domTree.addNode(node);
		mutex.unlock();
	}
}

/**
  * Decodes any character entities
  */
void decodeHTML(string &line) {
	int tagIndex = line.find_first_of('&');
	while (tagIndex != -1) {
		if (boost::iequals(line.substr(tagIndex, 5), "&amp;")) {
			line.erase(tagIndex + 1, 4);
		} else if (boost::iequals(line.substr(tagIndex, 4), "&lt;")) {
			line[tagIndex] = '<';
			line.erase(tagIndex + 1, 3);
		} else if (boost::iequals(line.substr(tagIndex, 4), "&gt;")) {
			line[tagIndex] = '>';
			line.erase(tagIndex + 1, 3);
		} else {
			line = line.substr(line.find_first_of(';') + 1); // Remove other entities
		}

		tagIndex = line.find_first_of('&', tagIndex + 1);
	}
}

/**
  * Creates the view, should be called as a thread
  */
void createGui(DomTree &domTree, mutex &mutex) {
	// Display View
	View view(domTree, mutex);
}


