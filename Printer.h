#ifndef VIEW_H
#define VIEW_H

#include "DomTree.h"
#include "Node.h"

class View {
private:
	void Printer::displayElement(Node &node, string &output, int tabs);
public:
	Printer::print(DomTree &domTree);
};

#endif
