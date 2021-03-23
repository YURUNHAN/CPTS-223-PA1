#include <stdlib.h>

using namespace std;


template<class T>
class AVLNode
{
public:
	T data;
	AVLNode<T> *left;
	AVLNode<T> *right;
	int height;

	AVLNode(T pdata)
	{
		data = pdata;
		left = NULL;
		right = NULL;
		height = 1;
	}

	~AVLNode()
	{
		if (left != NULL) {
			delete left;
			left = NULL;
		}

		if (right != NULL) {
			delete right;
			right = NULL;
		}
	}
};