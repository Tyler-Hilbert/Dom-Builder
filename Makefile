DEPS = DomTree.cpp FileReader.cpp Main.cpp  Node.cpp DirBuilder.cpp DomTreeBuilder.cpp

Parser: $(DEPS)
	g++ -std=c++11 -o Parser $(DEPS) -I. -g




