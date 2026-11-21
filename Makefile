CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
LIB      = src/BST.cpp src/AVL.cpp

all: bin/demo bin/testes bin/ex1 bin/ex2 bin/ex3

bin:
	mkdir -p bin

bin/demo: src/main.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/testes: testes/testes.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/ex1: exercicios/ex1_percursos.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/ex2: exercicios/ex2_remocao.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@
bin/ex3: exercicios/ex3_avl_rotacoes.cpp $(LIB) | bin
	$(CXX) $(CXXFLAGS) $^ -o $@

teste: bin/testes
	./bin/testes
clean:
	rm -rf bin
.PHONY: all teste clean
