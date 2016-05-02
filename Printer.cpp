#include "Printer.h"
#include <string>
#include <iostream>

void Printer::print(DomTree &domTree) {
	displayElement(domTree.getRoot(), 0);
}

void Printer::displayElement(Node &node, int tabs) {
	for (int i = 0; i < tabs; i++) {
		cout << "\t";
	}
	tabs++;

	cout << node.getTag() << ":" << node.getContent() << "\n";

	for (int i = 0; i < node.getChildren().size(); i++) {
		displayElement(node.getChildren().at(i), tabs);
	}
}
