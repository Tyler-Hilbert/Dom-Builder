#include "Node.h"
#include <string>

using namespace std;

void Node::setParent(Node *parent) {
	this->parent = parent;
}

Node* Node::getParent() {
	return parent;
}

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

Node* Node::addChild(Node node) {
	this->children.push_back(node);
	Node n = this->children.back();
	return &this->children.back();
}
