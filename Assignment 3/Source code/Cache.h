#ifndef CACHE_H
#define CACHE_H

#include "main.h"


class ReplacementPolicy {
	protected:
	public:
	ReplacementPolicy(){}
	virtual ~ReplacementPolicy(){}
	virtual void insert(Elem* e) = 0;
	virtual void access(int addr) = 0;
	virtual void remove() = 0; 
	virtual Elem* top() = 0;
	virtual void print() = 0;
	virtual int getSize() = 0;
};

class SearchEngine {
	public:
	SearchEngine(){}
	virtual ~SearchEngine(){}
	virtual Elem* search(int key) = 0; 
	virtual void addNode(Elem *key) = 0;
	virtual	void removeNode(int key) = 0;
	virtual void print() = 0;
};


class NodeR{
	public:
	Elem *data;
	NodeR *next;
	NodeR *prev;

	NodeR(Elem *data){
		this->data = data;
		this->next = NULL;
		this->prev = NULL;
	}
	~NodeR(){
		//delete data;
	}
};

// FIFO Imlement
class Queue{
	public:
	NodeR *head;
	NodeR *tail;
	int size;

	Queue(){
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}

	~Queue(){
		this->clear();
	}

	void push(Elem *item){
		NodeR *temp = new NodeR(item);
		if(this->size == 0){
			this->head = temp;
			this->tail = temp;
		}
		else if(this->size > 0){
			this->tail->next = temp;
			temp->prev = this->tail;
			this->tail = temp;
		}
		this->size++;
	}
	void pop(){
		if(this->size == 0) return;
		else if(this->size == 1){
			delete this->head;
			this->head = NULL;
			this->tail = NULL;
			this->size = 0;
		}
		else if(this->size > 1){
			NodeR *temp = this->head;
			this->head = this->head->next;
			this->head->prev = NULL;
			delete temp;
			this->size--;
		}
	}
	Elem* top(){
		if(this->size > 0) return this->head->data;
		return NULL;
	}
	void clear(){
		NodeR *temp = this->head;
		while(temp != NULL){
			this->head = this->head->next;
			delete temp;
			temp = this->head;
		}
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}

};
class FIFO : public ReplacementPolicy {
	Queue *q;
	int count;
	public:
	FIFO(){
		q = new Queue();
		this->count = 0;
	}
	~FIFO(){
		//delete Elem*
		NodeR *temp = q->head;
		while(temp != NULL){
			delete temp->data;
			temp = temp->next;
		}
		//

		delete q;
	}
	void insert(Elem* e){
		q->push(e);
		count++;
	}
	void access(int addr){}
	void remove(){
		q->pop();
		count--;
	}
	Elem *top(){
		return q->top();
	}
	void print(){
		NodeR *temp = q->head;
		while(temp != NULL){
			temp->data->print();
			temp = temp->next;
		}
	}
	int getSize(){
		return this->count;
	}
};

// MRU Implement
class SelfListMRU{
	public:
	NodeR *head;
	NodeR *tail;
	int size;

	SelfListMRU(){
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	~SelfListMRU(){
		this->clear();
	}

	void push(Elem *item){
		NodeR *temp = new NodeR(item);
		if(this->size == 0){
			this->head = temp;
			this->tail = temp;
		}
		else if(this->size >= 1){
			temp->next = this->head;
			this->head->prev = temp;
			this->head = temp;
		}
		this->size++;
	}
	void pop(){
		if(this->size == 0) return;
		else if(this->size == 1){
			delete this->head;
			this->head = NULL;
			this->tail = NULL;
			this->size = 0;
		}
		else if(this->size > 1){
			NodeR *temp = this->head;
			this->head = this->head->next;
			this->head->prev = NULL;
			delete temp;
			this->size--;
		}
	}
	Elem* top(){
		if(this->size > 0) return this->head->data;
		return NULL;
	}
	void access(int addr){
		NodeR *temp = this->head;
		while(temp != NULL){
			if(temp->data->addr == addr){
				if(temp->prev != NULL){
					temp->prev->next = temp->next;
					if(temp->next != NULL) temp->next->prev = temp->prev;
					else{
						this->tail = temp->prev;
					}
					temp->next = this->head;
					this->head->prev = temp;
					this->head = temp;
					this->head->prev = NULL;
				}
				break;
			}
			temp = temp->next;
		}
	}
	void clear(){
		NodeR *temp = this->head;
		while(temp != NULL){
			this->head = this->head->next;
			delete temp;
			temp = this->head;
		}
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
};
class MRU : public ReplacementPolicy {
	SelfListMRU *selfList;
	int count = 0;
	public:
	MRU(){
		this->selfList = new SelfListMRU();
		this->count = 0;
	}
	~MRU(){
		//delete Elem*
		NodeR *temp = selfList->head;
		while(temp != NULL){
			delete temp->data;
			temp = temp->next;
		}
		//

		delete selfList;
	}

	void insert(Elem* e){
		selfList->push(e);
		count++;
	}
	void access(int addr){
		selfList->access(addr);
	}
	void remove(){
		selfList->pop();
		count--;
	}
	Elem *top(){
		return selfList->top();
	}
	void print(){
		NodeR *temp = selfList->head;
		while(temp != NULL){
			temp->data->print();
			temp = temp->next;
		}
	}
	int getSize(){
		return this->count;
	}
};

// LRU Implement
class SelfListLRU{
	public:
	NodeR *head;
	NodeR *tail;
	int size;

	SelfListLRU(){
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
	~SelfListLRU(){
		this->clear();
	}

	void push(Elem *item){
		NodeR *temp = new NodeR(item);
		if(this->size == 0){
			this->head = temp;
			this->tail = temp;
		}
		else if(this->size > 0){
			temp->next = this->head;
			this->head->prev = temp;
			this->head = temp;
		}
		this->size++;
	}
	void pop(){
		if(this->size == 0){return;}
		else if(this->size == 1){
			delete this->tail;
			this->head = NULL;
			this->tail = NULL;
			this->size = 0;
		}
		else if(this->size > 1){
			NodeR *temp = this->tail;
			this->tail = this->tail->prev;
			this->tail->next = NULL;
			delete temp;
			this->size--;
		}
	}
	Elem* top(){
		if(this->size > 0) {
			return this->tail->data;
		}
		return NULL;
	}
	void access(int addr){
		NodeR *temp = this->head;
		while(temp != NULL){
			if(temp->data->addr == addr){
				if(temp->prev != NULL){
					temp->prev->next = temp->next;
					if(temp->next != NULL) temp->next->prev = temp->prev;
					else{
						this->tail = temp->prev;
					}
					temp->next = this->head;
					this->head->prev = temp;
					this->head = temp;
					this->head->prev = NULL;
				}
				break;
			}
			temp = temp->next;
		}
	}
	void clear(){
		NodeR *temp = this->head;
		while(temp != NULL){
			this->head = this->head->next;
			delete temp;
			temp = this->head;
		}
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
	}
};
class LRU: public MRU {
	SelfListLRU *selfList;
	int count = 0;
	public:
	LRU(){
		this->selfList = new SelfListLRU();
		this->count = 0;
	}
	~LRU(){
		//delete Elem*
		NodeR *temp = selfList->head;
		while(temp != NULL){
			delete temp->data;
			temp = temp->next;
		}
		//

		delete selfList;
	}

	void insert(Elem* e){
		selfList->push(e);
		count = selfList->size;
	}
	void access(int addr){
		selfList->access(addr);
	}
	void remove(){
		selfList->pop();
		count = selfList->size;
	}
	Elem *top(){
		return selfList->top();
	}
	void print(){
		NodeR *temp = selfList->head;
		while(temp != NULL){
			temp->data->print();
			temp = temp->next;
		}
	}
	int getSize(){
		return this->count;
	}
};

// LFU Implement
class nodeLFU{
	public:
	int freq;
	Elem *data;

	nodeLFU(Elem* data){
		this->data = data;
		this->freq = 1;
	}
	~nodeLFU(){
		//delete data;
	}
};

class heapLFU{
	public:
	nodeLFU **heap;
	int size;

	heapLFU(){
		heap = new nodeLFU*[MAXSIZE];
		for(int i = 0; i < MAXSIZE; i++) heap[i] = NULL;
		size = 0;
	}
	~heapLFU(){
		for(int i = 0; i < MAXSIZE; i++){
			if(heap[i] != NULL) delete heap[i];
		}
		delete[] heap;
	}

	void push(Elem * e){
		nodeLFU *temp = new nodeLFU(e);
		heap[this->size] = temp;
		this->size++;
		reheapUp(this->size - 1);
	}
	void pop(){
		delete heap[0];
		heap[0] = heap[this->size - 1];
		heap[this->size - 1] = NULL;
		this->size--;
		reheapDown(0);
	}
	Elem *top(){
		if(size > 0) return heap[0]->data;
		return NULL;
	}
	void reheapUp(int index){
		if(index <= 0 || index >= this->size) return;
		int parent = (index - 1) / 2;
		if(heap[index]->freq < heap[parent]->freq){
			nodeLFU *temp = heap[index];
			heap[index] = heap[parent];
			heap[parent] = temp;
			reheapUp(parent);
		}
	}
	void reheapDown(int index){
		if(index < 0 || index >= this->size) return;
		int left = 2 * index + 1;
		if(left < this->size){
			int right = 2 * index + 2;
			if(right < this->size){
				if(heap[left]->freq <= heap[right]->freq){
					if(heap[index]->freq >= heap[left]->freq){
						nodeLFU *temp = heap[index];
						heap[index] = heap[left];
						heap[left] = temp;
						reheapDown(left);
					}
				}
				else{
					if(heap[index]->freq >= heap[right]->freq){
						nodeLFU *temp = heap[index];
						heap[index] = heap[right];
						heap[right] = temp;
						reheapDown(right);
					}
				}
			} 
			else{
				if(heap[index]->freq >= heap[left]->freq){
					nodeLFU *temp = heap[index];
					heap[index] = heap[left];
					heap[left] = temp;
				}
			}
		}
	}
	
};
class LFU: public ReplacementPolicy {
	heapLFU *hp;
	int count;
	public:
	LFU(){
		hp = new heapLFU();
		count = 0;
	}
	~LFU(){
		//delete Elem*
		for(int i=0; i<hp->size; i++){
			delete hp->heap[i]->data;
		}
		//

		delete hp;
	}

	void insert(Elem* e){
		hp->push(e);
		this->count++;
	}
	void access(int addr){
		for(int i = 0; i < hp->size; i++){
			if(hp->heap[i]->data->addr == addr){
				hp->heap[i]->freq++;
				hp->reheapDown(i);
				break;
			} 
		}
	}
	void remove(){
		hp->pop();
		this->count--;
	}
	Elem *top(){
		return hp->top();
	}
	void print(){
		for(int i = 0; i < hp->size; i++){
			hp->heap[i]->data->print();
		}
	}
	int getSize(){
		return this->count;
	}
};

//DBHashing Implement
class DBHashing: public SearchEngine {
	int (*h1)(int);
	int (*h2)(int);
	Elem **hashTable;
	int *state; //0=NULL; 1=NON_EMPTY; 2:DELETED
	int size;
	public:
	DBHashing(int (*h1)(int),int (*h2)(int),int s){
		this->h1 = h1;
		this->h2 = h2;
		this->size = s;
		hashTable = new Elem*[s];
		state = new int[s];
		for(int i = 0; i < s; i++) state[i] = 0;
	}
	~DBHashing(){
		delete[] hashTable;
		delete[] state;
	}

	int hp(int key, int i){
		return ((h1(key) + i * h2(key)) % this->size);
	}
	void addNode(Elem *key){
		int i = 0;
		while((state[hp(key->addr, i)] == 1) && (i < (2 * this->size))){
			i++;
		}
		if(i >= 2 * this->size){
			for(int j = 0; j < this->size; j += 3){
				if(state[j] != 1){
					hashTable[j] = key;
					state[j] = 1;
					return;
				}
			}
		}
		hashTable[hp(key->addr, i)] = key; 
		state[hp(key->addr, i)] = 1;
	}
	void removeNode(int key){
		int i = 0;
		while((state[hp(key, i)] != 0) && (i < 2 * this->size)){
			if(state[hp(key, i)] == 1){
				if(hashTable[hp(key, i)]->addr == key){
					state[hp(key, i)] = 2;
					break;
				}
			}
			i++; 
		}
		if(i >= 2 * this->size){
			for(int j = 0; j < this->size; j += 1){
				if(state[j] == 1){
					if(hashTable[j]->addr == key){
						state[j] = 2;
						break;
					}
				}
			}
		}
	}
	void print(){
		cout << "Prime memory:\n";
		for(int i=0; i<this->size; i++){
			if(state[i] == 1){
				hashTable[i]->print();
			}
		}
	}
	Elem *search(int key) {
		int i = 0;
		while(state[hp(key, i)] != 0){
			if(state[hp(key, i)] == 1){
				if(hashTable[hp(key, i)]->addr == key){
					return hashTable[hp(key, i)];
				}
			}
			i++;
			if(hp(key, 0) == hp(key, i)) break;
		}
		return NULL;
	}
};

// AVL implement 
class Node
{
	public:
	Elem *data;
	int height;
	Node *left;
	Node *right;

	Node(Elem *data)
	{
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->height = 1;
	}
};
class AVL : public SearchEngine {
	Node *root;
	public:
		AVL() 
		{
			root = NULL;
		}
		~AVL() 
		{
			this->clean();
		}

		int getHeight(Node *node)
		{
			if(node == NULL) return 0;
			return node->height;
		}

		int getMax(int a, int b)
		{
			return a > b ? a : b;
		}

		Node *LLCase(Node *node)
		{
			Node *t1 = node->left;
			Node *t2 = t1->right;
			t1->right = node;
			node->left = t2;
			node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
			t1->height = getMax(getHeight(t1->left), getHeight(t1->right)) + 1; 
			return t1;
		}

		Node *RRCase(Node *node)
		{
			Node *t1 = node->right;
			Node *t2 = t1->left;
			t1->left = node;
			node->right = t2;
			node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
			t1->height = getMax(getHeight(t1->left), getHeight(t1->right)) + 1; 
			return t1;
		}

		Node *LRCase(Node *node)
		{
			node->left = RRCase(node->left);
			return LLCase(node);
		} 

		Node *RLCase(Node *node)
		{
			node->right = LLCase(node->right);
			return RRCase(node);
		}

		int getBalence(Node *node)
		{
			if(node == NULL) return 0;
			return getHeight(node->left) - getHeight(node->right);
		}

		Node *insert(Node *node, Elem *key)
		{
			if(node == NULL)
			{
				return new Node(key);
			}
			if(key->addr < node->data->addr) node->left = insert(node->left, key);
			else if(key->addr > node->data->addr) node->right = insert(node->right, key);

			//Equal key ???
			else return node;

			node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;

			int balance = getBalence(node);
			if(balance > 1 && key->addr < node->left->data->addr)
			{
				return LLCase(node);
			}
			if(balance < -1 && key->addr > node->right->data->addr)
			{
				return RRCase(node);
			}
			if(balance > 1 && key->addr > node->left->data->addr)
			{
				return LRCase(node);
			}
			if(balance < -1 && key->addr < node->right->data->addr)
			{
				return RLCase(node);
			}
			return node;
		}

		Node *getMinNode(Node *node)
		{
			Node *temp = node;
			while(temp->left != NULL) temp = temp->left;
			return temp;
		}

		Node *deleteNode(Node *node, int key)
		{
			if(node == NULL) return node;
			if(key < node->data->addr) node->left = deleteNode(node->left, key);
			else if(key > node->data->addr) node->right = deleteNode(node->right, key);
			else
			{
				if(node->left == NULL || node->right == NULL)
				{
					Node *temp = node->left ? node->left : node->right;
					if(temp == NULL)
					{
						temp = node;
						node = NULL;
					}
					else 
					{
						node->data = temp->data;
						node->height = temp->height;
						node->left = NULL;
						node->right = NULL;
						//*node = *temp;
					}
					delete temp;
				}
				else
				{
					Node *temp = getMinNode(node->right);
					node->data = temp->data;
					node->right = deleteNode(node->right, temp->data->addr);
				}
			}

			if(node == NULL) return node;
			node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
			int balance = getBalence(node);
			if(balance > 1 && getBalence(node->left) >= 0)
			{
				return LLCase(node);
			}
			if(balance > 1 && getBalence(node->left) < 0)
			{
				return LRCase(node);
			}
			if(balance < -1 && getBalence(node->right) <= 0)
			{
				return RRCase(node);
			}
			if(balance < -1 && getBalence(node->right) > 0)
			{
				return RLCase(node);
			}
			
			return node;
		}

		void cleanNode(Node *node)
		{
			if(node != NULL)
			{
				cleanNode(node->left);
				cleanNode(node->right);
				delete node;
			}
			node = NULL;
		}
		void clean()
		{
			cleanNode(root);
		}

		void addNode(Elem *key)
		{
			root = this->insert(root, key);
		}

		void removeNode(int key)
		{
			root = this->deleteNode(root, key);
		}

		void preorderRec(Node *node)
		{
			if(node == NULL) return;
			node->data->print();
			preorderRec(node->left);
			preorderRec(node->right);
		}

		void inorderRec(Node *node)
		{
			if(node == NULL) return;
			inorderRec(node->left);
			node->data->print();
			inorderRec(node->right);
		}

		void print() 
		{
			cout << "Print AVL in inorder:\n";
			inorderRec(root);
			cout << "Print AVL in preorder:\n";
			preorderRec(root);
		}

		Elem *containNode(Node *node, int addr)
		{
			if(node == NULL) return NULL;
			if(addr < node->data->addr) return containNode(node->left, addr);
			if(addr > node->data->addr) return containNode(node->right, addr);
			return node->data;
		}
		Elem* search(int key)
		{
			Elem *temp = containNode(root, key);
			return temp;
		}
};

#endif