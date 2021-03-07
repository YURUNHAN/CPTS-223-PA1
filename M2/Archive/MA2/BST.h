#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <queue>
#include <limits>
using namespace std;

/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node
{
public:
    T value;
    Node* left;
    Node* right;

    Node(T val)
    {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node()
    {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST
{

protected:
    Node<T>* _root;         // Root of the tree nodes

    /* Add new T val to the tree */
    void addHelper(Node<T>* root, T val)
    {
        if (root->value > val)
        {
            if (!root->left)
            {
                root->left = new Node<T>(val);
            }
            else
            {
                addHelper(root->left, val);
            }
        }
        else
        {
            if (!root->right)
            {
                root->right = new Node<T>(val);
            }
            else
            {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T>* root)
    {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T>* root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
        }
    }

    /* Return height of tree (root == nullptr -> 0) */
    int heightHelper(Node<T>* root)
    {
        if (!root)
        {
            return -1;
        }
        else
        {
            return 1 + max(heightHelper(root->left), heightHelper(root->right));
        }
    }

    /* Delete a given <T> value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value)
    {
        if (!current) return false;
        if (current->value == value)
        {
            if (current->left == nullptr || current->right == nullptr)
            {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent)
                {
                    if (parent->left == current)
                    {
                        parent->left = temp;
                    }
                    else
                    {
                        parent->right = temp;
                    }
                }
                else
                {
                    this->_root = temp;
                }
            }
            else
            {
                Node<T>* validSubs = current->right;
                while (validSubs->left)
                {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
            deleteValueHelper(current, current->right, value);
    }


    /* helper method of printMaxPath */
    void printMaxPathHelper(Node<T>* root, int & curHeight, int & maxHeight,
        vector<T> & stack, vector<T> & maxStack)
    {
        if (root)
        {
            // current node is non-empty, visit each of its subtree
            stack.push_back(root->value);
            curHeight++;
            printMaxPathHelper(root->left, curHeight, maxHeight, stack, maxStack);
            printMaxPathHelper(root->right, curHeight, maxHeight, stack, maxStack);
            curHeight--;
            stack.pop_back();
        }
        else
        {
            // current node is null, update the max height and max stack
            if (curHeight > maxHeight)
            {
                maxHeight = curHeight;
                maxStack = stack;
            }
        }
    }
    /* help method of contains */
    bool containsHelper(Node<T>* root, T value)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->value == value)
        {
            return true;
        }
        else if (root->value > value)
        {
            return containsHelper(root->left, value);
        }
        else
        {
            return containsHelper(root->right, value);
        }
    }

    /* help method of destructor */
    void destroyHelper(Node<T>* root)
    {
        if (root)
        {
            destroyHelper(root->left);
            destroyHelper(root->right);
            delete root;
        }
    }
    /********************************* PUBLIC API *****************************/
public:

    BST() : _root(nullptr) {}               // Basic initialization constructor

    /**
     * Destructor - Needs to free *all* nodes in the tree
     * TODO: Implement Destructor
     */
    ~BST()
    {
        destroyHelper(_root);
    }

    /* Public API */
    void add(T val)
    {
        if (this->_root)
        {
            this->addHelper(this->_root, val);
        }
        else
        {
            this->_root = new Node<T>(val);
        }
    }

    void print()
    {
        printInOrderHelper(this->_root);
    }

    /**
     * Print the nodes level by level, starting from the root
     * TODO: Implement printLevelOrder
     */
    void printLevelOrder()
    {
        Node<T> * cur;
        int level;

        // contains the node
        queue<Node<T> * > qValue;

        // contains the level of cooresponding node
        queue<int> qLevel;

        // enqueue first node
        qValue.push(_root);
        qLevel.push(0);
        int curLevel = 0;
        while (!qValue.empty())
        {
            cur = qValue.front();
            level = qLevel.front();

            // if current level less than this level
            // display a new line character
            if (curLevel < level)
            {
                curLevel = level;
                cout << endl;
            }

            // show current node
            cout << cur->value << ' ';

            // remove this node
            qValue.pop();
            qLevel.pop();

            // enqueue left child
            if (cur->left)
            {
                qValue.push(cur->left);
                qLevel.push(level + 1);
            }
            // enqueue right child
            if (cur->right)
            {
                qValue.push(cur->right);
                qLevel.push(level + 1);
            }
        }

        cout << endl;
    }

    int nodesCount()
    {
        return nodesCountHelper(this->_root);
    }

    int height()
    {
        return heightHelper(this->_root);
    }

    /**
     * Print the maximum path in this tree
     * TODO: Implement printMaxPath
     */
    void printMaxPath()
    {
        vector<T> stack;
        vector<T> maxStack;
        int curHeight = 0;
        int maxHeight = -1;
        printMaxPathHelper(_root, curHeight, maxHeight, stack, maxStack);
        for (int i = 0; i < (int)maxStack.size(); i++)
        {
            cout << maxStack[i] << ' ';
        }
    }

    bool deleteValue(T value)
    {
        return this->deleteValueHelper(nullptr, this->_root, value);
    }

    /**
     * Find if the BST contains the value
     * TODO: Implement contains
     */
    bool contains(T value)
    {
        return containsHelper(_root, value);
    }


};

#endif

