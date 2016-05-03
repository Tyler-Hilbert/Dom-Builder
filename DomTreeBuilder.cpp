#include "DomTreeBuilder.h"

#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>
#include "Node.h"
#include "DomTree.h"
#include "FileReader.h"
#include "DirBuilder.h"

using namespace std; 

// Populates the passed domTree with the html contents from in
void DomTreeBuilder::populateDomTreeFromString(DomTree &domTree, string &in) {
	// Parse the page
	if (in.empty()) {
		// ToDO: add error handling here
	} else {
		// Check for and loop through tags
		int tagIndex = in.find_first_of('<'); 	
		try {
			do {
				in = in.substr(tagIndex + 1);
				parse(in, domTree);
				tagIndex = in.find_first_of('<');
			} while (tagIndex != -1);
		}
		catch (int e) {
			// TODO:: Improve handling
		}
	}
}

/**
 *  Parses the line string and adds it to the parsed string
 */
void DomTreeBuilder::parse(string &in, DomTree &domTree) {
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
		domTree.closeNode(tag);
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
		domTree.addNode(node);
	}

	in = in.substr(endTagIndex);
}


/**
  * Decodes any character entities
  */
void DomTreeBuilder::decodeHTML(string &line) {
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

