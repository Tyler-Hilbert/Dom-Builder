#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>
#include <thread>
#include <mutex>
#include "Page.h"
#include "Node.h"
#include "DomTree.h"
#include "FileReader.h"
#include "Printer"

using namespace std; 


void parse(string &line, DomTree &domTree, mutex &mutex); // Parses up to tag
void decodeHTML(string &line); // Decodes the html character entities
void createGui(DomTree &domTree, mutex &mutex); // Starts the gui thread


int main(int argc, const char** argv) {
	mutex mutex;
	DomTree domTree;
	Node root;
	root.setTag("root");
	mutex.lock();
	domTree.setRoot(root);
	mutex.unlock();


	// Read page
	FileReader reader;
	string path = "resources/characters.html";
	string in = reader.getFile(path);



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

	Printer printer(domTree);

	system("pause");
	return 0;
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void parse(string &in, DomTree &domTree, mutex &mutex) {
	// Get tag
	string tag;
	int endTagIndex = in.find_first_of('>');
	int attributeStart = in.find_first_of(' ');
	if (attributeStart != -1 && attributeStart < endTagIndex) {
		tag = (in.substr(0, attributeStart));
	} else {
		tag = (in.substr(0, endTagIndex));
	}

	// Check if opening or closing tag
	if (in.at(0) == '/'){
		tag = tag.substr(1);
		mutex.lock();
		domTree.closeNode(tag);
		mutex.unlock();
	} else {
		Node node;
		node.setTag(tag);

		// Get content for tag
		int nextTag = in.find_first_of('<', endTagIndex);
		if (nextTag != -1) {
			string content = in.substr(endTagIndex + 1, nextTag - endTagIndex - 1);
			decodeHTML(content);
			node.setContent(content);
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
		if (line.substr(tagIndex, 5).compare("&amp;") == 0) { // Verfiy this is correct
			line.erase(tagIndex + 1, 4);
		} else if (line.substr(tagIndex, 4).compare("&lt;") == 0 ) { // verify this
			line[tagIndex] = '<';
			line.erase(tagIndex + 1, 3);
		} else if (line.substr(tagIndex, 4).compare("&gt;") == 0) {
			line[tagIndex] = '>';
			line.erase(tagIndex + 1, 3);
		} else {
			line = line.substr(line.find_first_of(';') + 1); // Remove other entities
		}

		tagIndex = line.find_first_of('&', tagIndex + 1);
	}


	// Remove \r....
	// TODO: This should be replaced with something better
	int index;
	while ((index = line.find("\r")) != -1) {
		line.erase(index, 2);
	}
}

