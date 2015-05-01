#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

class Node {
private:
	vector<Node> children;
	string tag;
	string content;
public:
	string& Node::getTag();
	void Node::setTag(string tag);

	void Node::setContent(string tag);
	string& Node::getContent();

	vector<Node>& Node::getChildren();
	void Node::addChild(Node child);
};

#endif