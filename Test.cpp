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
	string path = "resources/tests/basic.html"; // TODO: Add error handeling here for empty file
	string in = reader.getFile(path);

	// Create DomTree
	DomTree domTree;
	Node root;
	root.setTag("root");
	domTree.setRoot(root);

	// Parse DomTree
	DomTreeBuilder domBuilder;
	domBuilder.populateDomTreeFromString(domTree, in);

	// Run tests
	Node html = domTree.getRoot().getChildren().at(0);
	printResult(html.getTag().compare("HTML") == 0, 1);

	Node title = html.getChildren().at(0).getChildren().at(0);
	printResult(title.getTag().compare("TITLE") == 0, 2);
	printResult(title.getContent().compare("Your Title Here") == 0, 3);

	Node body = html.getChildren().at(1);
	printResult(body.getChildren().at(0).getChildren().at(2).getContent().compare("second") == 0, 4);
	printResult(body.getChildren().at(0).getContent().compare("third") == 0, 5);
	cout << body.getChildren().at(0).getContent();


	return 0;
}

void printResult(bool res, int num) {
	if (res)
		cout << "Passed test " << to_string(num) << "\n";
	else 
		cout << "Failed test " << to_string(num) << "\n";
}
