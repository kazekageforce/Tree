#include "Tree.h"
using namespace std;
#define COUNT 10
#include <iostream>
#include <vector>

Tree::Tree(vector<int> members) {
	for (int data : members) {
		insert(data);
	}
}

Tree::~Tree() {
	head = nullptr;
	tail = nullptr;
}

void Tree::insert(int data) {
	if (head == nullptr) {
		head = new Node(data);
		return;
	}
	if (head->left == nullptr) {
		Node* newNode = new Node(data, head);
		tail = newNode;
		head->left = tail;
		fUp(tail);
		return;
	}
	if (tail->parent->right == nullptr) {
		Node* newNode = new Node(data, tail->parent);
		tail->parent->right = newNode;
		tail = newNode;
		fUp(tail);
		return;
	}
	Node* current = tail->parent;
	while (current->parent != nullptr) {
		if (current == current->parent->left) {
			current = current->parent->right;
			while (current->left != nullptr) {
				current = current->left;
			}
			Node* newNode = new Node(data, current);
			current->left = newNode;
			tail = newNode;
			fUp(tail);
			return;
		}
		current = current->parent;
	}
	while (current->left != nullptr) {
		current = current->left;
	}
	Node* newNode = new Node(data, current);
	current->left = newNode;
	tail = newNode;
	fUp(tail);
}


void Tree::fUp(Node* current) {
	while (current->parent != nullptr && current->data > current->parent->data) {
		Node* tmp = current->parent;

		int temp = current->data;
		current->data = current->parent->data;
		current->parent->data = temp;

		current = tmp;
	}
}


Tree::Node* Tree::search(int data, Node* current) {
	if (current != nullptr && current->data == data) {
		return current;
	}
	else if (current == nullptr) {
		return nullptr;
	}
	Node* tmp = search(data, current->right);
	if (tmp != nullptr) {
		return tmp;
	}
	return search(data, current->left);
}


bool Tree::exist(int data) {
	Node* tmp = search(data, head);
	return tmp != nullptr;
}


void Tree::remove(int data) {
	if (head == nullptr) {
		cout << "Empty." << endl;
	}
	Node* need = search(data, head);
	while (need != nullptr) {
		removeNode(need);
		if (tail == nullptr) {
			break;
		}
		if (tail->parent != nullptr) {
			fUp(need);
			fDown(need);
		}
		need = search(data, head);
	}
}


void Tree::removeNode(Node* need) {
	if (need == nullptr) {
		return;
	}
	need->data = tail->data;
	if (tail == head) {
		head = nullptr;
		tail = nullptr;
		return;
	}
	if (tail->parent->right != nullptr) {
		tail = tail->parent->left;
		tail->parent->right = nullptr;
		return;
	}
	tail->parent->left = nullptr;
	while (tail->parent != nullptr) {
		if (tail == tail->parent->right) {
			tail = tail->parent->left;
			while (tail->left != nullptr) {
				tail = tail->right;
			}
			return;
		}
		tail = tail->parent;
	}
	tail = head;
	while (tail->right != nullptr) {
		tail = tail->right;
	}
}


void Tree::fDown(Node* current) {
	while (current && current->left) {
		Node* max = current->left;
		if (current->right != nullptr) {
			if (current->right->data > max->data) {
				max = current->right;
			}
		}
		Node* tmp = max;
		if (current->data > max->data) {
			break;
		}
		int temp = current->data;
		current->data = max->data;
		max->data = temp;

		current = tmp;
	}
}


void print2DUtil(Tree::Node* root, int space) {
	if (root == nullptr)
		return;
	space += COUNT;
	print2DUtil(root->right, space);
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << "\n";
	print2DUtil(root->left, space);
}

void Tree::print() {
	Node* root = head;
	print2DUtil(root, 0);
}

vector<int> Tree::eraseVec(vector<int> arr, int data) {
	vector<int> tmp;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] != data) {
			tmp.push_back(arr[i]);
		}
	}
	return tmp;
}


int main() {
	cout << "Enter some numbers using enter. " << endl;
	cout << "The size of your tree should be: ";
	int sz;
	cin >> sz;
	cout << "Your numbers are (use 0 if you want to exit): " << endl;
	vector<int> numbers;
	int a;
	while (numbers.size() != sz)
	{
		cin >> a;
		numbers.push_back(a);
		if (a == 0) {
			numbers.pop_back();
			break;
		}
	}
	Tree* tree = new Tree(numbers);
	cout << "Choose the operation." << endl;
	cout << "Press 1 if you want the tree to be shown." << endl;
	cout << "Press 2 if you want to insert some value. " << endl;
	cout << "Press 3 to check the existance of some value." << endl;
	cout << "Press 4 to remove some element." << endl;
	cout << "Press 5 to remove whole tree." << endl;
	cout << "Press 0 to exit." << endl;
	int op;
	while (cin >> op) {
		if (op == 1) {
			cout << "Your tree is: " << endl;
			tree->print();
			cout << endl;
		}
		else if (op == 2) {
			cout << "Please, enter the value you want to push: ";
			int elem;
			cin >> elem;
			numbers.push_back(elem);
			if (numbers.size() <= sz) {
				tree->insert(elem);
			}
			else {
				cout << "The entered size of the tree doesn't allow putting of the new elements." << endl;
			}
		}
		else if (op == 3) {
			cout << "Please, enter the element thats existance you want to check: ";
			int data;
			cin >> data;
			if (tree->exist(data)) {
				cout << "Exists." << endl;
			}
			else {
				cout << "Doesn't exist." << endl;
			}
		}
		else if (op == 4) {
			cout << "Please, enter the element that you want to remove: ";
			int data;
			cin >> data;
			tree->remove(data);
			numbers = tree->eraseVec(numbers, data);
		}
		else if (op == 5) {
			tree->~Tree();
		}
		else if (op == 0) {
			exit(0);
		}
		else {
			cout << "No such operation." << endl;
		}
		cout << endl;
		cout << "Choose the operation." << endl;
		cout << "Press 1 if you want the tree to be shown." << endl;
		cout << "Press 2 if you want to insert some value. " << endl;
		cout << "Press 3 to check the existance of some value." << endl;
		cout << "Press 4 to remove some element." << endl;
		cout << "Press 5 to remove whole tree." << endl;
		cout << "Press 0 to exit." << endl;
	}
}

