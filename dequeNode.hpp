class DequeNode {
	private:
		int value;
		DequeNode* parent;
		DequeNode* jump;
		int depth;
		bool isRoot(DequeNode* u);
	public:
		DequeNode(int x, DequeNode* p, int d);
		void setValue(int x);
		void setParent(DequeNode* parent);
		void setJump(DequeNode* jump);
		void setDepth(int depth);
		int getValue();
		DequeNode* getParent();
		DequeNode* getJump();
		int getDepth();
};

bool DequeNode::isRoot(DequeNode* u) {
	return (u != NULL && u->getParent() == NULL);
}

DequeNode::DequeNode(int x, DequeNode* p, int d) {
    this->setValue(x);
	this->setParent(p);
	this->setDepth(d);
	//if (!isRoot(this)) addLeaf(this); TODO
};

void DequeNode::setValue(int x) {
	this->value = x;
};

void DequeNode::setParent(DequeNode* parent) {
	this->parent = parent;
};

void DequeNode::setJump(DequeNode* jump) {
	this->jump = jump;
};

void DequeNode::setDepth(int depth) {
	this->depth = depth;
};

int DequeNode::getValue() {
	return this->value;
};

DequeNode* DequeNode::getParent() {
	return this->parent;
};

DequeNode* DequeNode::getJump() {
	return this->jump;
};

int DequeNode::getDepth() {
	return this->depth;
};
