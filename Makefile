DEPS = DomTree.cpp FileReader.cpp Node.cpp DirBuilder.cpp DomTreeBuilder.cpp Main.cpp
TEST_DEPS = DomTree.cpp FileReader.cpp Node.cpp DomTreeBuilder.cpp Test.cpp

all: Parser Test

Parser: $(DEPS)
	g++ -std=c++11 -o Parser $(DEPS) -I. -g

Test: $(TEST_DEPS) 
	g++ -std=c++11 -o Test $(TEST_DEPS) -I. -g
