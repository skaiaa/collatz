#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
class Table {
public:
	unsigned int *table;
	Table(unsigned int size) {
		table = new unsigned int[size];
	}
	unsigned int& operator[](std::size_t i) { return table[i]; }
	~Table() {
		delete table;
	}
};
class TreeAVL;
class Node {
public:
	Node * parent;
	Node* left;
	Node* right;
	unsigned int value;
	TreeAVL* positions;
	int balance;//(h(Lst)-h(RsT))
	Node() {
		parent = NULL;
		left = NULL;
		right = NULL;
		balance = 0;
		positions = NULL;
	};
	~Node();

};

class TreeAVL {
private:


	void left_rotate(Node* node, Node** local_root) {
		Node* tmp = node->right;
		if (tmp == NULL)return;
		node->right = tmp->left;
		if (tmp->left != NULL)tmp->left->parent = node;
		tmp->parent = node->parent;
		if (node->parent == NULL)*local_root = tmp;
		else if (node == node->parent->left) node->parent->left = tmp;
		else node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}
	void right_rotate(Node* node, Node** local_root) {
		Node* tmp = node->left;
		if (tmp == NULL)return;
		node->left = tmp->right;
		if (tmp->right != NULL)tmp->right->parent = node;
		tmp->parent = node->parent;
		if (node->parent == NULL)*local_root = tmp;
		else if (node == node->parent->right) node->parent->right = tmp;
		else node->parent->left = tmp;
		tmp->right = node;
		node->parent = tmp;
	}
	void rebalance(Node* node,Node** local_root) {
		Node* parent = node->parent;
		if (node->balance < -1 && node->right->balance < 0) {
			left_rotate(node, local_root);
		}
		else if (node->balance < -1 && node->right->balance>0) {
			right_rotate(node->right, local_root);
			left_rotate(node, local_root);
		}
		else if (node->balance > 1 && node->left->balance > 0) {
			right_rotate(node, local_root);

		}
		else if (node->balance > 1 && node->left->balance < 0) {
			left_rotate(node->left, local_root);
			right_rotate(node, local_root);
		}
	}
	int height(Node* node) {
		if (node != NULL) return std::max(height(node->left), height(node->right)) + 1;
		else return 0;
	}
	void check_balance(Node* node,TreeAVL* tree) {
		Node* tmp = node;
		while (tmp != NULL) {
			tmp->balance = height(tmp->left) - height(tmp->right);
			if (abs(tmp->balance) > 1)rebalance(tmp,&(tree->root));
			tmp = tmp->parent;
		}
	}

	void remove(Node* node,TreeAVL* tree) {
		unsigned int value=node->value;//tylko zeby zobaczyc co kasuje
		if (node != NULL) {
			if (node->left == NULL && node->right == NULL) { //lisc
				if (node->parent == NULL) { // root
					delete node;
					tree->root = NULL;
				}
				else {
					if (node->parent->left == node) { //ma rodzica, lewe dziecko
						node->parent->left = NULL;
						delete node;
					}
					else if (node->parent->right == node) { //ma rodzica, prawe dziecko
						node->parent->right = NULL;
						delete node;
					}
				}
			}
			else if (node->left == NULL && node->right != NULL) { //tylko z prawym synem
				if (node->parent != NULL) {
					node->parent->left = node->right;
					node->right->parent = node->parent;
					delete node;
				}
				else {
					tree->root = node->right;
					tree->root->parent = NULL;
					delete node;
					int g = 0;
				}
			}
			else if (node->left != NULL && node->right == NULL) { //tylko z lewym synem
				if (node->parent != NULL) {
					node->parent->right = node->left;
					node->left->parent = node->parent;
					delete node;
				}
				else {
					tree->root = node->left;
					tree->root->parent = NULL;
					delete node;
				}
			}
		}
	}

	void insert(Node*node,TreeAVL* tree) {
		unsigned int value = node->value;
		if (tree->root == NULL) tree->root = node;
		else {
			Node* tmp = tree->root;
			while (tmp != NULL) {
				if (node->value < tmp->value) {
					if (tmp->left != NULL)tmp = tmp->left;
					else {
						node->parent = tmp;
						tmp->left = node;
						break;
					}
				}
				else {
					if (tmp->right != NULL)tmp = tmp->right;
					else {
						node->parent = tmp;
						tmp->right = node;
						break;
					}
				}
			}
			if(node->parent!=NULL)check_balance(node->parent,tree);
		}
	}
	void insert(Node* node, Node* parent,TreeAVL* tree) {
		node->parent = parent;
		if (node->value < parent->value) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		check_balance(node->parent, tree);
	}
public:
	Node * root;
	TreeAVL() {
		root = NULL;
	}
	Node* search(unsigned int value) {
		Node* tmp = root;
		Node* parent=NULL;
		while (tmp != NULL && tmp->value != value) {
			parent = tmp;
			if (value < tmp->value) tmp = tmp->left;
			else tmp = tmp->right;
		}
		return tmp;
	}

	void add(unsigned int value, unsigned int position) {
		Node* tmp = search(value);

		if (tmp == NULL) {
			Node* new_node = new Node;
			new_node->value = value;
			new_node->positions = new TreeAVL;
			new_node->positions->root = new Node;
			new_node->positions->root->value = position;
			insert(new_node,this);
		}
		else {
			Node* new_node = new Node;
			new_node->value = position;
			insert(new_node,tmp->positions);
		}
	}
	unsigned int find_min() { // znajduje index najmniejszego pierwszego w kolejnosci ORAZ usuwa go z drzewa
		Node* big_node = root;
		if (big_node != NULL) {
			while (big_node->left != NULL) big_node = big_node->left;
			Node* index_node = big_node->positions->root;
			while (index_node->left != NULL) index_node = index_node->left;
			unsigned int index= index_node->value;
			remove(index_node,big_node->positions);
			if (big_node->positions->root == NULL)
				remove(big_node,this);
			return index;
		}
		else throw std::invalid_argument("tree doesn't exists!");
	}
	unsigned int find_max() { //znajduje index najwiekszego pierwszego w kolejnosci ORAZ usuwa go z drzewa
		Node* big_node = root;
		if (big_node != NULL) {
			while (big_node->right != NULL) big_node = big_node->right;
			Node* index_node = big_node->positions->root;
			while (index_node->left != NULL) index_node = index_node->left;
			unsigned int index = index_node->value;
			remove(index_node,big_node->positions);
			if (big_node->positions->root == NULL) 
				remove(big_node,this);
			return index;
		}
		else throw std::invalid_argument("tree doesn't exists!");
	}
};