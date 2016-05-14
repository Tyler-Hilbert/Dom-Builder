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
	Node *parent;
public:
	void setParent(Node *parent);
	Node* getParent();

	string& getTag();
	void setTag(string tag);

	void setContent(string tag);
	string& getContent();

	vector<Node>& getChildren();
	Node* addChild(Node child);
};

#endif
