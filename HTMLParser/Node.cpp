#include "Node.h"
#include <string>

using namespace std;

void Node::setTag(string tag) {
	this->tag = tag;
}

string &Node::getTag() {
	return this->tag;
}

void Node::setContent(string content) {
	this->content = content;
}

string& Node::getContent() {
	return content;
}

vector<Node> &Node::getChildren() {
	return this->children;
}

void Node::addChild(Node node) {
	this->children.push_back(node);
}
