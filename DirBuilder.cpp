#include "DirBuilder.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


// Creates the file structure from the dom tree
void DirBuilder::create(DomTree &domTree) {
	parseElement(domTree.getRoot(), 0);
}

// Parses the individual elements and creates the directory/file if needed.
void DirBuilder::parseElement(Node &node, int tabs) {
	// Create a new folder for each of the characters (They should be the only things in the <li> tags)
	if (node.getTag().compare("li") == 0) {
		string dirName;
		dirName = "character/" + node.getContent();
		string command;
		command = "mkdir " + dirName;
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
