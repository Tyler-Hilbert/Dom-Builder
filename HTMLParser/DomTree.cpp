#include "DomTree.h"

void DomTree::setRoot(Node root) {
	this->root = root;
}

void DomTree::addNode(Node node) {
	this->root.addChild(node);
}

Node& DomTree::getRoot() {
	return root;
}