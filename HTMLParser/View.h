#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <mutex>

class View {
public:
	View(std::string &text, std::mutex &mutex);
};

#endif