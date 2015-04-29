#include "Page.h"
#include <SFML/Network.hpp>
#include <string>

using namespace std;


string Page::getPage(const string &url) {
	sf::Http http(url);
	sf::Http::Request request;


	sf::Http::Response response = http.sendRequest(request);
	return response.getBody();
}
