#ifndef _DOM_TREE_BUILDER_H
#define _DOM_TREE_BUILDER_H

#include "DomTree.h"
#include <string>

// This is the class that will parse an html string and populate the DOM Tree from its contents
class DomTreeBuilder {
public:
	void populateDomTreeFromString(DomTree &domTree, string &in);

private:
	void parse(string &line, DomTree &domTree); // Parses up to tag
	void decodeHTML(string &line); // Decodes the html character entities
};
#endif