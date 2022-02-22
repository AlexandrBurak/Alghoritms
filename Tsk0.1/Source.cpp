#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

class Node {
public:
	long key;
	Node* left;
	Node* right;

	Node(long key) {
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
	}
	
	Node(long key, Node* left, Node* right) {
		this->key = key;
		this->left = left;
		this->right = right;
	}
};

class Tree {
public:
	Node* root;
	Tree() {
		this->root = nullptr;
	}

	Tree(long key) {
		Node* nt = new Node(key);
		this->root = nt;
	}

	void Destroy(Node* node) {
		if (node) {
			Destroy(node->left);
			Destroy(node->right);
			delete[] node;
		}
	}

	void Add(long x) {
		Node** node_s = &this->root;
		while (*node_s) {
			Node& node = **node_s;
			if (x < node.key) {
				node_s = &node.left;
			}
			else if (x > node.key) {
				node_s = &node.right;
			}
			else {
				return;
			}
		}
		*node_s = new Node(x);
	}

	void Tour(Node* node, vector<long>& vect) {
		if (node == nullptr) {
			return;
		}
		vect.push_back(node->key);
		Tour(node->left, vect);
		Tour(node->right, vect);
	}

	~Tree() {
		Destroy(this->root);
	}
};

int main() {
	ifstream in;
	ofstream out;
	in.open("input.txt");
	out.open("output.txt");
	long val;
	vector<long> vect;
	while (!in.eof()) {
		in >> val;
		vect.push_back(val);
	}

	auto res = unique(begin(vect), end(vect));
	vect.erase(res, end(vect));
	Tree* tr = new Tree();
	for (long obj : vect) {
		tr->Add(obj);
	}
	vect.clear();
	tr->Tour(tr->root, vect);
	for (int i = 0; i < vect.size(); i++) {
		if (i == vect.size() - 1) {
			out << vect[i];
			break;
		}
		out << vect[i] << endl;
	}

	
	in.close();
	out.close();

	return 0;
}