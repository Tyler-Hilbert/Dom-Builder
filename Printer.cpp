#include <string>
#include <iostream>

void Printer::print(DomTree &domTree) {
	displayElement(domTree.getRoot(), output, 0);
	displayText.setString(output);

}

void Printer::displayElement(Node &node, string &output, int tabs) {
	for (int i = 0; i < tabs; i++) {
		cout << "\t";
	}
	tabs++;

	cout << node.getTag() << ":" << node.getContent() << "\n";

	for (int i = 0; i < node.getChildren().size(); i++) {
		displayElement(node.getChildren().at(i), output, tabs);
	}
}
