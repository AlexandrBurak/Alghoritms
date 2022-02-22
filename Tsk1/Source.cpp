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
	int childs = 0;
	bool label;

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
	/*int Binary_Trees<NODETYPE>::CheakPeaks(PNode T, int& count)
{
	int l=0, r=0;
	if (T==0) return 0;
	else
	{
	  l=CheakPeaks(T->Left, count);
	  r=CheakPeaks(T->Rigth, count);
	  if (l!=r)
	  {
		  T->Label=true;
		  count++;
	  }
	  return l+r+1;
	}
}*/
	int Counter(Node* node, int& count) {
		int l = 0, r = 0;
		if (node == nullptr)
		{
			return 0;
		}
		else
		{
			l = Counter(node->left, count);
			r = Counter(node->right, count);
			if (l != r)
			{
				node->label = true;
				count++;
			}
			return l + r + 1;
		}
	}

	void Tour(Node* node) {
		if (node == nullptr) {
			return;
		}
		int count = 0;
		node->childs = this->Counter(node, count) - 1;
		Tour(node->left);
		Tour(node->right);
	}


	void TourV(Node* node, vector<long>& vect) {
		if (node == nullptr) {
			return;
		}

		vect.push_back(node->key);
		TourV(node->left, vect);
		TourV(node->right, vect);
	}

	void AddDiffChilds(Node* node, vector<long>& vect) {
		if (node == nullptr || node->label == false) {
			return;
		}

		vect.push_back(node->key);
		AddDiffChilds(node->left, vect);
		AddDiffChilds(node->right, vect);
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


	~Tree() {
		Destroy(this->root);
	}
};

int main() {
	ifstream in;
	ofstream out;
	in.open("in.txt");
	out.open("out.txt");
	long val;
	vector<long> vect;
	vector<long> tour;
	while (!in.eof()) {
		in >> val;
		vect.push_back(val);
	}
	auto res = unique(begin(vect), end(vect));
	vect.erase(res, end(vect));
	Tree* tr = new Tree();
	tr->root = new Node(vect[0]);
	for (int i = 1; i < vect.size(); ++i) {
		tr->Add(vect[i]);
	}
	tr->Tour(tr->root);
	vect.clear();
	tr->AddDiffChilds(tr->root, vect);
	if (vect.size() == 0 || vect.size() % 2 == 0) {
		vect.clear();
		tr->TourV(tr->root, vect);
		for (int i = 0; i < vect.size(); ++i) {
			out << vect[i] << endl;
		}
		in.close();
		out.close();
		return 0;
	}
	sort(vect.begin(), vect.end());
	long del_key = vect[vect.size() / 2];
	tr->root = tr->delete_rec(tr->root, del_key);
	vect.clear();
	tr->TourV(tr->root, vect);
	for (int i = 0; i < vect.size(); ++i) {
		out << vect[i] << endl;
	}
	in.close();
	out.close();

	return 0;
}