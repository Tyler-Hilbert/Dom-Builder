#ifndef DOMTREE_H
#define DOMTREE_H

#include "Node.h"


class DomTree {
private:
	Node root;
	Node *current;
public:
	void DomTree::setRoot(Node root);
	Node& DomTree::getRoot();
	bool DomTree::hasRoot();


	void DomTree::addNode(Node node);
	void DomTree::closeNode(string &tag);
};

#endif



