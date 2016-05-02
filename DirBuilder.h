#ifndef DIR_BUILDER_H
#define DIR_BUILDER_H

#include "DomTree.h"
#include "Node.h"

// Turns the Dom Tree into the file structure and creates dirs/files
class DirBuilder {
private:
	void parseElement(Node &node, int tabs);
public:
	void create(DomTree &domTree);
};

#endif
