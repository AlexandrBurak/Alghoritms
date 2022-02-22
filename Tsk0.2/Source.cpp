#pragma comment(linker, "/STACK:16777216")
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
	Node* parent;

	Node(long key) {
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(long key, Node* parent) {
		this->key = key;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = parent;
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
		Node* parent = nullptr;
		while (*node_s) {
			Node& node = **node_s;
			if (x < node.key) {
				node_s = &node.left;
				parent = &node;
			}
			else if (x > node.key) {
				node_s = &node.right;
				parent = &node;
			}
			else {
				return;
			}
		}
		*node_s = new Node(x, parent);
	}



	Node* Search(long x) {
		Node** node_s = &this->root;
		while (*node_s) {
			Node& node = **node_s;
			if (x < node.key) {
				node_s = &node.left;
			}
			else if (x > node.key) {
				node_s = &node.right;
			}
			else 
			{
				return *node_s;
			}
		}
		return *node_s;
	}

	Node* SearchMin(Node* from) {
		Node* res = from;
		if (res != nullptr) {
			while (res->left) {
				res = res->left;
			}
			return res;
		}
	}

	

	void TourV(Node* node, vector<long>& vect) {
		if (node == nullptr) {
			return;
		}
		vect.push_back(node->key);
		//cout << node->key << endl;
		TourV(node->left, vect);
		TourV(node->right, vect);
	}


	Node* delete_rec(Node* loc_root, long x) {
		if (loc_root == nullptr) {
			return nullptr;
		}

		if (x < loc_root->key) {
			loc_root->left = delete_rec(loc_root->left, x);
			return loc_root;
		}
		else if (x > loc_root->key) {
			loc_root->right = delete_rec(loc_root->right, x);
			return loc_root;
		}
		if (loc_root->left == nullptr) {
			return loc_root->right;
		}
		else if (loc_root->right == nullptr) {
			return loc_root->left;
		}
		else {
			long min_key = this->SearchMin(loc_root->right)->key;
			loc_root->key = min_key;
			loc_root->right = delete_rec(loc_root->right, min_key);
			return loc_root;
		}

	}
	
	/*
	void Delete(long key) {
		Node* target = this->Search(key);
		if (target == this->root) {
			Node* min_for_target = this->SearchMin(target->right);
			if (target->right == min_for_target) {
				min_for_target->left = target->left;
				min_for_target->parent = nullptr;
				this->root = min_for_target;
				return;
			}
			min_for_target->parent->left = min_for_target->right;
			min_for_target->right->parent = min_for_target->parent;
			min_for_target->parent = target->parent;
			min_for_target->left = target->left;
			min_for_target->right = target->right;
			this->root = min_for_target;
			return;
		}
		if (target->left != nullptr && target->right == nullptr) {
			target->left->parent = target->parent;
			if (target->parent->left == target) {
				target->parent->left = target->left;
			}
			else if (target->parent->right == target) {
				target->parent->right = target->left;
			}
			target = target->left;
			return;
		}
		else if (target->left == nullptr && target->right != nullptr) {
			target->right->parent = target->parent;
			if (target->parent->left == target) {
				target->parent->left = target->right;
			}
			else if (target->parent->right == target) {
				target->parent->right = target->right;
			}
			target = target->right;
			return;
		}
		else if (target->left != nullptr && target->right != nullptr) {
			Node* min_for_target = this->SearchMin(target->right);
			if (target->right == min_for_target) {
				min_for_target->left = target->left;
				min_for_target->parent = target->parent;
				target->left->parent = min_for_target;
				if (target->parent->left == target) {
					target->parent->left = min_for_target;
				}
				else if (target->parent->right == target) {
					target->parent->right = min_for_target;
				}
				target = min_for_target;
				return;
			}
			min_for_target->parent->left = min_for_target->right;
			min_for_target->right->parent = min_for_target->parent;
			min_for_target->parent = target->parent;
			min_for_target->left = target->left;
			min_for_target->right = target->right;
			if (target->parent->left == target) {
				target->parent->left = min_for_target;
			}
			else if (target->parent->right == target) {
				target->parent->right = min_for_target;
			}
			target = min_for_target;
			return;
		}
		if (target->parent->left == target) {
			target->parent->left = nullptr;
			target = nullptr;
			return;
		}
		else if (target->parent->right == target) {
			target->parent->right = nullptr;
			target = nullptr;
			return;
		}
		
	}
	*/

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
	long del_key;
	vector<long> vect;
	vector<long> tour;
	in >> del_key;
	while (!in.eof()) {
		in >> val;
		vect.push_back(val);
	}
	auto res = unique(begin(vect), end(vect));
	vect.erase(res, end(vect));
	Tree* tr = new Tree();
	tr->root = new Node(vect[0]);
	for (int i = 1; i < vect.size(); i++) {
		tr->Add(vect[i]);
	}
	tr->root = tr->delete_rec(tr->root, del_key);
	vect.clear();
	tr->TourV(tr->root, vect);
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