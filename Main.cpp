#include <string>
#include <fstream>
#include "DomTree.h"
#include "FileReader.h"
#include "DirBuilder.h"
#include "DomTreeBuilder.h"

using namespace std; 


int main(int argc, const char** argv) {
	// Read page
	FileReader reader;
	string path = "resources/characters.html";
	string in = reader.getFile(path);

	// Create DomTree
	DomTree domTree;
	Node root;
	root.setTag("root");
	domTree.setRoot(root);

	// Parse DomTree
	DomTreeBuilder domBuilder;
	domBuilder.populateDomTreeFromString(domTree, in);

	// Create directories and other files from  the dom tree model
	DirBuilder dirBuilder;
	dirBuilder.create(domTree);

	return 0;
}
