DEPS = DomTree.cpp FileReader.cpp HTMLParser.cpp  Node.cpp DirBuilder.cpp

Parser: $(DEPS)
	g++ -std=c++11 -o Parser $(DEPS) -I. -g




