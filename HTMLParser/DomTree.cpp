#include "DomTree.h"
#include <boost/algorithm/string.hpp>

void DomTree::setRoot(Node root) {
	this->root = root;
	current = &this->root;
}

void DomTree::addNode(Node node) {
	node.setParent(current);
	current = current->addChild(node);
}

void DomTree::closeNode(string &tag) {
	// TODO: add error handling for bad html closing tag
	bool found = false;
	do {
		if (boost::iequals(current->getTag(), tag)) {
			found = true;
		}
		current = current->getParent();
	} while (!found);
}

Node& DomTree::getRoot() {
	return root;
}

bool DomTree::hasRoot() {
	return !root.getTag().empty();
}