#ifndef DIR_BUILDER_H
#define DIR_BUILDER_H

#include <string>

#include "DomTree.h"
#include "Node.h"

using namespace std;

// Turns the Dom Tree into the file structure and creates dirs/files
class DirBuilder {
private:
	void parseElement(Node &node, int tabs);

	string m_character; // The character's name that is being parsed
	string m_color; // The color of the character that is being parsed
public:
	void create(DomTree &domTree);
};

#endif
