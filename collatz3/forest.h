#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
class Table {
public:
	unsigned int *table,size;
	Table(unsigned int size) :size(size){
		table = new unsigned int[size];
	}
	unsigned int& operator[](std::size_t i) { return table[i]; }
	void write() {
		for (std::size_t i = 0; i < size; i++) {
			if (table[i] == 0) printf_s("m");
			else printf_s("%d", table[i]);
			if (i != size - 1) printf_s(" ");
		}
	}
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
	void left_rotate(Node* node, Node** local_root);
	void right_rotate(Node* node, Node** local_root);

	void check_balance(Node* node, TreeAVL* tree);
	void rebalance(Node* node, Node** local_root);

	void remove(Node* node, TreeAVL* tree);

	void insert(Node*node, TreeAVL* tree);
	void insert(Node* node, Node* parent, TreeAVL* tree);
	Node* search(unsigned int value);
public:
	Node * root;
	TreeAVL() {
		root = NULL;
	}
	void add(unsigned int value, unsigned int position);
	unsigned int find_min();
	unsigned int find_max();
};