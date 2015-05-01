#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <mutex>
#include "DomTree.h"

class View {
public:
	View(DomTree &domTree, std::mutex &mutex);
};

#endif