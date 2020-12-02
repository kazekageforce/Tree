#pragma once
#include <vector>
using namespace std;
class Tree
{
public:
	class Node {
	public:
		int data;
		Node* left, * right, * parent;

		Node(int data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) :
			data(data), parent(parent), left(left), right(right) {};

	};
	Tree(vector<int> members);
	~Tree();
	void print();
	void insert(int data);
	void fUp(Node* current);
	Node* search(int data, Node* current);
	bool exist(int data);
	void remove(int data);
	void removeNode(Node* remnode);
	void fDown(Node* current);
	vector<int> eraseVec(vector<int> arr, int data);
private:
	Node* head = nullptr;
	Node* tail = nullptr;
};
;