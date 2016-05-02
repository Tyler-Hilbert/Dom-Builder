#ifndef DOMTREE_H
#define DOMTREE_H

#include "Node.h"


class DomTree {
private:
	Node root;
	Node *current;
public:
	void setRoot(Node root);
	Node& getRoot();
	bool hasRoot();


	void addNode(Node node);
	void closeNode(string &tag);
};

#endif



