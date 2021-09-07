#include <iostream>
#include <string>
using namespace std;

int main() {
	string command = '';
	while (command != 'exit') {
		getLine(cin, command, '(');
		command = toLower(command);
	}
	return 0;
}
