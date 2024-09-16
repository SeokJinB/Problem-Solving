#include <iostream>

using namespace std;

class Node
{
public:
	int data;
	Node* left;
	Node* right;

	Node(int data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};

class BinaryTree
{
public:
	Node* root;

	BinaryTree()
	{
		root = nullptr;
	}

	Node* insertion(Node* node, int data)
	{
		if (node == nullptr)
		{
			return new Node(data);
		}

		if (data < node->data)
			node->left = insertion(node->left, data);
		else
			node->right = insertion(node->right, data);

		return node;
	}

	Node* findMin(Node* node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	Node* deletion(Node* node, int data)
	{
		if (node == nullptr)
			return node;

		if (data < node->data)
		{
			node->left = deletion(node->left, data);
		}
		else if (data > node->data)
		{
			node->right = deletion(node->right, data);
		}
		else
		{
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			else if (node->left == nullptr)
			{
				Node* temp = node;
				node = node->right;
				delete temp;
			}
			else if (node->right == nullptr)
			{
				Node* temp = node;
				node = node->left;
				delete temp;
			}
			else
			{
				Node* temp = findMin(node);
				node->data = temp->data;
				node->right = deletion(node->right, temp->data);
			}
		}

		return node;
	}

	void inorderTraversal(Node* node)
	{
		if (node == nullptr)
			return;

		inorderTraversal(node->left);
		cout << node->data << " ";
		inorderTraversal(node->right);
	}

	void preorderTraversal(Node* node)
	{
		if (node == nullptr)
			return;

		cout << node->data << " ";
		preorderTraversal(node->left);
		preorderTraversal(node->right);
	}

	void postorderTraversal(Node* node)
	{
		if (node == nullptr)
			return;

		postorderTraversal(node->left);
		postorderTraversal(node->right);
		cout << node->data << " ";
	}
};

int main()
{
	BinaryTree tree;

	tree.root = tree.insertion(tree.root, 50);
	tree.root = tree.insertion(tree.root, 30);
	tree.root = tree.insertion(tree.root, 20);
	tree.root = tree.insertion(tree.root, 40);
	tree.root = tree.insertion(tree.root, 70);
	tree.root = tree.insertion(tree.root, 60);
	tree.root = tree.insertion(tree.root, 80);

	cout << "Inorder Traversal: ";
	tree.inorderTraversal(tree.root);
	cout << endl;

	cout << "Preorder Traversal: ";
	tree.preorderTraversal(tree.root);
	cout << endl;

	cout << "Postorder Traversal: ";
	tree.postorderTraversal(tree.root);
	cout << endl << endl;

	tree.root = tree.deletion(tree.root, 20);
	cout << "After deleting 20: ";
	tree.inorderTraversal(tree.root);
	cout << endl;

	return 0;
}

