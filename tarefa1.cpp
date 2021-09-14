// Matheus Barbosa Silva - NUSP: 11221741
// Tarefa 1 - Deque Persistente

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "persistentDeque.hpp"

using namespace std;
string prompt = ">>>>> ";

void printDequePrompt(int i) {
	cout << prompt << "Deque " << i << ": ";
}

void callPersistentDequeCommand(string command, vector<int> args, PersistentDeque* pd) {
	if (args.size() == 1) {
		if (command == "print") {
			printDequePrompt(args[0]);
			pd->print(pd->getDeque(args[0]));
		} else if (command == "popfront" || command == "popback") {
			deque res;
			if (command == "popfront") res = pd->popFront(pd->getDeque(args[0]));
			else res = pd->popBack(pd->getDeque(args[0]));
			printDequePrompt(pd->getLastDequeIndex());
			pd->print(res);
		} else if (command == "front") {
			int res = pd->front(pd->getDeque(args[0]));
			cout << prompt << "Front (Deque " << pd->getLastDequeIndex() << "): " << res << endl;
		} else {
			int res = pd->back(pd->getDeque(args[0]));
			cout << prompt << "Back (Deque " << pd->getLastDequeIndex() << "): " << res << endl;
		}
	} else if (args.size() == 2) {
		if (command == "kth") {
			int res = pd->Kth(pd->getDeque(args[0]), args[1]);
			cout << prompt << args[1] << "º Elemento da Deque " << args[0] << ": " << res << endl;
		} else {
			deque res;
			if (command == "pushfront") res = pd->pushFront(pd->getDeque(args[0]), args[1]);
			else res = pd->pushBack(pd->getDeque(args[0]), args[1]);
			printDequePrompt(pd->getLastDequeIndex());
			pd->print(res);
		}
	} else {
		pd->Deque();
		cout << prompt << "Deque vazia criada!" << endl;
	}
}

int main() {
	PersistentDeque* persistentDeque = new PersistentDeque();
	string command, arg1, arg2;
	vector<int> args;
	vector<string> twoArgsCommands = { "pushfront", "pushback", "kth" };
	string exit = "exit";

	cout << prompt << "TESTES DE DEQUE PERSISTENTE" << endl;
	cout << " * Insira o comando exit() para terminar a execução." << endl;

	while (getline(cin, command, '(') && command != exit) {
		transform(command.begin(), command.end(), command.begin(), ::tolower);

		if (count(twoArgsCommands.begin(), twoArgsCommands.end(), command)) {
			getline(cin, arg1, ',');
			getline(cin, arg2, ')');
			args.push_back(stoi(arg1));
			args.push_back(stoi(arg2));
			getline(cin, arg1);
		} else if (command != "deque"){
			getline(cin, arg1, ')');
			args.push_back(stoi(arg1));
			getline(cin, arg1);
		} else {
			getline(cin, arg1);
		}

		if (command != exit) callPersistentDequeCommand(command, args, persistentDeque);

		args.clear();
	}

	delete persistentDeque;
	return 0;
}
