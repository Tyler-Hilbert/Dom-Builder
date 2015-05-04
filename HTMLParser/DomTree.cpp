#include "DomTree.h"

void DomTree::setRoot(Node root) {
	this->root = root;
	current = &this->root;
}

void DomTree::addNode(Node node) {
	node.setParent(current);
	current = current->addChild(node);
}

void DomTree::closeNode() {
	current = current->getParent();
}

Node& DomTree::getRoot() {
	return root;
}

bool DomTree::hasRoot() {
	return !root.getTag().empty();
}