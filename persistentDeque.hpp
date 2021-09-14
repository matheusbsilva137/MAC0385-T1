// Matheus Barbosa Silva - NUSP: 11221741
// Tarefa 1 - Deque Persistente

#include <vector>
#include "deque.hpp"

using namespace std;

class PersistentDeque {
	private:
		vector<deque> dequeList;
		vector<DequeNode*> dequeNodeList;
		DequeNode* LCA(DequeNode* u, DequeNode* v);
		DequeNode* LevelAncestor(int k, DequeNode* u);
		void addLeaf(DequeNode* u);
		deque swap(deque d);
		void printRecursive(deque d);
	public:
		~PersistentDeque();
		deque Deque();
		deque getDeque(int i);
		int front(deque d);
		int back(deque d);
		deque pushFront(deque d, int x);
		deque pushBack(deque d, int x);
		deque popFront(deque d);
		deque popBack(deque d);
		int Kth(deque d, int k);
		void print(deque d);
		int getLastDequeIndex();
};

PersistentDeque::~PersistentDeque() {
	for (int i = 0; i < dequeNodeList.size(); i++) delete dequeNodeList[i];
};

DequeNode* PersistentDeque::LCA(DequeNode* u, DequeNode* v) {
	if (u->getDepth() > v->getDepth()) {
		DequeNode* temp = u;
		u = v;
		v = temp;
	}
	v = LevelAncestor(v->getDepth() - u->getDepth(), v);

	if (u == v) return u;
	while (u->getParent() != v->getParent() && !u->isRoot() && !v->isRoot()) {
		if (u->getJump() != v->getJump()) {
			u = u->getJump();
			v = v->getJump();
		} else {
			u = u->getParent();
			v = v->getParent();
		}
	}
	if (u->isRoot()) return u;
	if (v->isRoot()) return v;
	return u->getParent();
};

DequeNode* PersistentDeque::LevelAncestor(int k, DequeNode* u) {
	int y = u->getDepth() - k;
	while (u->getDepth() != y) {
		if (u->getJump()->getDepth() >= y) {
			u = u->getJump();
		} else {
			u = u->getParent();
		}
	}
	return u;
};

void PersistentDeque::addLeaf(DequeNode* u) {
	DequeNode* v = u->getParent();

	if (v->getJump() != NULL && !v->getJump()->isRoot() && v->getDepth() - v->getJump()->getDepth() == v->getJump()->getDepth() - v->getJump()->getJump()->getDepth()) {
		u->setJump(v->getJump()->getJump());
	} else {
		u->setJump(v);
	}
};

deque PersistentDeque::swap(deque d) {
	deque swappedDeque = { d.last, d.first };
	return swappedDeque;
};

deque PersistentDeque::Deque() {
	deque emptyDeque = { NULL, NULL };
	dequeList.push_back(emptyDeque);
	return emptyDeque;
};

deque PersistentDeque::getDeque(int i) {
	return dequeList[i];
};

int PersistentDeque::front(deque d) {
	return d.first->getValue();
};

int PersistentDeque::back(deque d) {
	return d.last->getValue();
};

deque PersistentDeque::pushFront(deque d, int x) {
	if (d.first == NULL) {
		DequeNode* u = new DequeNode(x, NULL, 1);
		dequeNodeList.push_back(u);

		deque newDeque = { u, u };
		dequeList.push_back(newDeque);
		return newDeque;
	} else {
		DequeNode* u = new DequeNode(x, d.first, d.first->getDepth() + 1);
		dequeNodeList.push_back(u);

		addLeaf(u);
		deque newDeque = { u, d.last };
		dequeList.push_back(newDeque);
		return newDeque;
	}
};

deque PersistentDeque::pushBack(deque d, int x) {
	deque res = swap(pushFront(swap(d), x));
	dequeList.back() = res;
	return res;
};

deque PersistentDeque::popFront(deque d) {
	if (d.first == d.last) return Deque();

	DequeNode* mid = LCA(d.first, d.last);
	if (d.first != mid) {
		deque newDeque = { d.first->getParent(), d.last };
		dequeList.push_back(newDeque);
		return newDeque;
	} else {
		DequeNode* second = LevelAncestor(d.last->getDepth() - d.first->getDepth() - 1, d.last);
		deque newDeque = { second, d.last };
		dequeList.push_back(newDeque);
		return newDeque;
	}
};

deque PersistentDeque::popBack(deque d) {
	deque res = swap(popFront(swap(d)));
	dequeList.back() = res;
	return res;
};

int PersistentDeque::Kth(deque d, int k) {
	DequeNode* mid = LCA(d.first, d.last);
	int l1 = d.first->getDepth() - mid->getDepth();
	int l2 = d.last->getDepth() - mid->getDepth();

	if (k - 1 <= l1) return LevelAncestor(k-1, d.first)->getValue();
	else return LevelAncestor(l2 - (k - 1 - l1), d.last)->getValue();
};

void PersistentDeque::printRecursive(deque d) {
	if (d.first == d.last) {
		if (d.first != NULL) cout << d.first->getValue();
		else cout << "(VAZIA)";
	} else {
		DequeNode* mid = LCA(d.first, d.last);
		cout << d.first->getValue() << " ";

		if (d.first != mid) {
			deque nextDeque = { d.first->getParent(), d.last };
			printRecursive(nextDeque);
		} else {
			DequeNode* u = d.last;
			vector<int> values;
			while (u != mid) {
				values.push_back(u->getValue());
				u = u->getParent();
			}

			for (int i = values.size() - 1; i >= 0; i--) cout << values[i] << " ";
		}
	}
};

void PersistentDeque::print(deque d) {
	printRecursive(d);
	cout << endl;
};

int PersistentDeque::getLastDequeIndex() {
	return dequeList.size() - 1;
};
