#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "DomTree.h"
#include "FileReader.h"
#include "DomTreeBuilder.h"
#include "Node.h"

using namespace std; 

void printResult(bool res, int num);


int main(int argc, const char** argv) {
	cout << "Running test\n";

	// Read page
	FileReader reader;
	string path = "resources/test/basic.html";
	string in = reader.getFile(path);

	// Create DomTree
	DomTree domTree;
	Node root;
	root.setTag("root");
	domTree.setRoot(root);

	// Parse DomTree
	DomTreeBuilder domBuilder;
	domBuilder.populateDomTreeFromString(domTree, in);

	printResult(root.getChildren().at(0).getTag().compare("HTML") == 0, 1);

	return 0;
}

void printResult(bool res, int num) {
	if (res)
		cout << "Passed test " << to_string(num) << "\n";
	else 
		cout << "Failed test " << to_string(num) << "\n";
}
