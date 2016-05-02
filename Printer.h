#ifndef PRINTER_H
#define PRINTER_H

#include "DomTree.h"
#include "Node.h"

class Printer {
private:
	void displayElement(Node &node, int tabs);
public:
	void print(DomTree &domTree);
};

#endif
