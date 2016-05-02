#include "DirBuilder.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>


// Creates the file structure from the dom tree
void DirBuilder::create(DomTree &domTree) {
	parseElement(domTree.getRoot(), 0);
}

// Parses the individual elements and creates the directory/file if needed.
void DirBuilder::parseElement(Node &node, int tabs) {
	// Create a new folder for each of the characters (They should be the only things in the <li> tags)
	if (node.getTag().compare("li") == 0) {
		// Get character name
		string charName = node.getContent();
		charName.erase(remove(charName.begin(), charName.end(), '\n'), charName.end());
		// trim leading spaces
		size_t startpos = charName.find_first_not_of(" \t");
		if(string::npos != startpos ) {
    		charName = charName.substr( startpos );
		}
		// Replace ' ' with '_'
		replace(charName.begin(), charName.end(), ' ', '_');
		// Add character directory to the front of the path
		string path = "./character/" + charName;
		// Turn into a command to make directory
		string command;
		command = "mkdir " + path;
		// Create directory
		const char * cmd = command.c_str();
		system (cmd);
	}



	for (int i = 0; i < tabs; i++) {
		cout << "\t";
	}
	tabs++;

	cout << node.getTag() << ":" << node.getContent() << "\n";

	for (int i = 0; i < node.getChildren().size(); i++) {
		parseElement(node.getChildren().at(i), tabs);
	}
}