#include <iostream>
#include <math.h>
#include "AVLNode.h"


using namespace std;



template<class T>
class AVLTree
{
private:

	AVLNode<T>* root;

public:
	AVLTree()
	{
		root = NULL;
	}

	AVLTree(T value)
	{
		root = new AVLNode<T>(value);
	}

	AVLNode<T> getRoot()
	{
		return root;
	}

	int height(AVLNode<T> *node)
	{
		if (node == NULL)
			return 0;

		return node->height;
	}

	int height()
	{
		return height(root);
	}

	int getBalance(AVLNode<T> *node)
	{
		if (node == NULL)
			return 0;
		else
			return height(node->left) - height(node->right);
	}

	AVLNode<T>* leftRotate(AVLNode<T>* x)
	{
		AVLNode<T>* y = x->right;
		AVLNode<T>* T2 = y->left;

		y->left = x; 
		x->right = T2; 

		// Update heights 
		x->height = max(height(x->left),    
		                height(x->right)) + 1; 
		y->height = max(height(y->left), 
		                height(y->right)) + 1; 

		return y; 
	}

	AVLNode<T>* rightRotate(AVLNode<T>* y)
	{
		AVLNode<T>* x = y->left;
		AVLNode<T>* T2 = x->right;

		x->right = y; 
		y->left = T2; 

		y->height = max(height(y->left),
		                height(y->right)) + 1; 
		x->height = max(height(x->left),
		                height(x->right)) + 1; 

		// Return new root 
		return x; 
	}


	void insert(T value)
	{
		root = insert(root, value);
	}

	AVLNode<T>* insert(AVLNode<T>* node, T value)
	{
		if (node == NULL)
			return new AVLNode<T>(value);

		if (value < node->data)
		{
			node->left = insert(node->left, value);
		}
		else if (value > node->data)
		{
			node->right = insert(node->right, value);
		}
		else
		{
			// same value not allowed in AVL
			return node;
		}

		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBalance(node);

		// left left
		if (balance > 1 && value < node->left->data)
		{
			return rightRotate(node);
		}

		// right right
		if (balance < -1 && value > node->right->data)
		{
			return leftRotate(node);
		}

		// left right 
		if (balance > 1 && value > node->left->data)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// right left
		if (balance < -1 && value < node->right->data)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	void preOrder()
	{
		preOrder(root);
	}

	void preOrder(AVLNode<T> *node)
	{
		if (node != NULL)
		{
			cout << "node: " << node->data << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	int contains(T value)
	{
		return contains(root, value);
	}

	int contains(AVLNode<T>* node, T value)
	{
		if (node == NULL)
			return 0;

		if (node->data == value)
			return 1;

		if (value < node->data)
		{
			return contains(node->left, value);
		}
		else
		{
			return contains(node->right, value);
		}
	}

	int validate()
	{
		return validate(root);
	}

	int validate(AVLNode<T>* node)
	{
		if (node == NULL)
			return 1;

		int valid = 1;
		if (abs( height(node->left) - height(node->right) ) > 1)
			valid = 0;

		return valid && validate(node->left) && validate(node->right);
	}


	
	~AVLTree()
	{
		if (root != NULL)
			delete root;
	}
	
};