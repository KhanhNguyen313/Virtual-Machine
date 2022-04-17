#ifndef CACHE_H
#define CACHE_H

#include "main.h"


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

class AVL
{
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

	Elem *containNode(Node *node, int addr)
	{
		if(node == NULL) return NULL;
		if(addr < node->data->addr) return containNode(node->left, addr);
		if(addr > node->data->addr) return containNode(node->right, addr);
		return node->data;
	}

	void addNode(Elem *key)
	{
		root = this->insert(root, key);
	}
	void removeNode(int key)
	{
		root = this->deleteNode(root, key);
	}
	void clean()
	{
		cleanNode(root);
	}
	Elem *contain(int addr)
	{
		return containNode(root, addr);
	}
	void preorderRec(Node *node)
	{
		if(node == NULL) return;
		node->data->print();
		preorderRec(node->left);
		preorderRec(node->right);
	}
	void preorder()
	{
		preorderRec(root);
	}
	void inorderRec(Node *node)
	{
		if(node == NULL) return;
		inorderRec(node->left);
		node->data->print();
		inorderRec(node->right);
	}
	void inorder()
	{
		inorderRec(root);
	}

};

class Cache {
		
	public:
		AVL AVLTree;
		queue<Elem *> recentUse;

		Cache(int s) {}
		~Cache() {
			while(!recentUse.empty())
			{
				delete recentUse.front();
				recentUse.pop();
			}
		}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
};


#endif