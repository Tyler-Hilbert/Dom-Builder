#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <mutex>
#include "DomTree.h"
#include "Node.h"

class View {
private:
	void View::displayElement(Node &node, string &output, int tabs);
public:
	View(DomTree &domTree, std::mutex &mutex);
};

#endif