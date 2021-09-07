#include "dequeNode.hpp"
#include "deque.hpp"

class PersistentDeque {
	private:
		DequeNode* LCA(DequeNode* u, DequeNode* v);
		DequeNode* LevelAncestor(int k, DequeNode* u);
		void addLeaf(DequeNode* u);
		deque swap(deque d);
	public:
		deque deque();
		DequeNode front(deque d);
		DequeNode back(deque d);
		deque pushFront(deque d, int x);
		deque pushBack(deque d, int x);
		DequeNode Kth(deque d, int k)
};

DequeNode* PersistentDeque::LCA(DequeNode* u, DequeNode* v) {
	if (u->getDepth() > v->getDepth()) {
		DequeNode* temp = u;
		u = v;
		v = temp;
	}

	if (u == v) return u;
	while (u->getParent() != v->getParent()) {
		if (u->getJump() != v->getJump()) {
			u = u->getJump();
			v = v->getJump();
		} else {
			u = u->getParent();
			v = v->getParent();
		}
	}
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

	if (!isRoot(v->getJump()) && v->getDepth() - v->getJump()->getDepth() == v->getJump()->getDepth() - v->getJump()->getJump()->getDepth()) {
		u->setJump(v->getJump()->getJump());
	} else {
		u->setJump(v);
	}
};

deque PersistentDeque::swap(deque d) {
	deque swappedDeque = deque();
	swappedDeque.first = d.last;
	swappedDeque.last = d.first;
	return swappedDeque;
};

deque PersistentDeque::deque() {
	deque newDeque = { NULL, NULL };
	return newDeque;
};

DequeNode PersistentDeque::front(deque d) {
	return *(d.first);
};

DequeNode PersistentDeque::back(deque d) {
	return *(d.last);
};

deque PersistentDeque::pushFront(deque d, int x) {
	if (d.first == NULL) {
		DequeNode* u = DequeNode(x, NULL, 1);
		deque newDeque = {u, u};
		return newDeque;
	} else {
		deque newDeque = { DequeNode(x, d.first, d.first->getDepth() + 1), d.last };
		return newDeque;
	}
};

deque PersistentDeque::pushBack(deque d, int x) {
	return swap(pushFront(swap(d), x));
};

DequeNode PersistentDeque::popFront(deque d) {
	DequeNode* mid = LCA(d.first, d.last);

	if (d.first != mid) {
		//adiciona a deque (d.second, d.last) à lista de deques
		return *(d.first);
	} else {
		//adiciona a deque (d.first, d.penultimo) à lista de deques
		return Kth(swap(d), 2)
	}
};

DequeNode PersistentDeque::Kth(deque d, int k) {
	DequeNode* mid = LCA(d.first, d.last);
	int l1 = d.first->getDepth() - mid->getDepth();
	int l2 = d.last->getDepth() - mid->getDepth();

	if (k - 1 <= l1) return *(LevelAncestor(k-1, d.first));
	else return *(LevelAncestor(l2 - (k - 1 - l1), d.last));
};

void PersistentDeque::print(deque d) {
	DequeNode* mid = LCA(d.first, d.last);
	int l1 = d.first->getDepth() - mid->getDepth();
	int l2 = d.last->getDepth() - mid->getDepth();

	if (k - 1 <= l1) return *(LevelAncestor(k-1, d.first));
	else return *(LevelAncestor(l2 - (k - 1 - l1), d.last));
};
