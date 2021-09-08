all: tarefa1

ep1: tarefa1.cpp dequeNode.hpp deque.hpp persistentDeque.hpp
	gpp tarefa1.cpp -o -O3 tarefa1
