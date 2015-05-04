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


void parse(string &line, DomTree &domTree, mutex &mutex); // Parses up to tag
void decodeHTML(string &line); // Decodes the html character entities
void createGui(DomTree &domTree, mutex &mutex); // Starts the gui thread

bool writable = false;

int main(int argc, const char** argv) {
	mutex mutex;
	DomTree domTree;
	Node root;
	root.setTag("root");
	mutex.lock();
	domTree.setRoot(root);
	mutex.unlock();

	cout << "test 1\n";

	// Create gui thread
	
	thread thread(&createGui, ref(domTree), ref(mutex));
	thread.detach();

	cout << "test 2\n";

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
				in = in.substr(tagIndex + 1);
				parse(in, domTree, mutex);
				tagIndex = in.find_first_of('<');
			} while (tagIndex != -1);
		}
		catch (int e) {
			// TODO:: Improve handling
		}
	}


	cout << "test 3\n";

	system("pause");
	return 0;
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parse(string &in, DomTree &domTree, mutex &mutex) {
	// Get tag
	int endTagIndex = in.find_first_of('>');
	int attributeStart = in.find_first_of(' ');

	// Check if opening or closing tag
	if (in.at(0) == '/'){
		mutex.lock();
		domTree.closeNode();
		mutex.unlock();
	} else {
		Node node;
		// Check if tag has attributes
		if (attributeStart != -1 && attributeStart < endTagIndex) {
			node.setTag(in.substr(0, attributeStart));
		} else {
			node.setTag(in.substr(0, endTagIndex));
		}

		mutex.lock();
		domTree.addNode(node);
		mutex.unlock();
	}

	in = in.substr(endTagIndex);
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


