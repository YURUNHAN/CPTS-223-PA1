#include "AVLTree.h"
#include <vector>
#include <algorithm>

using namespace std;



int main()
{
	// AVLTree<int> *tree = new AVLTree<int>();

	// tree->insert(5);
	// tree->insert(4);
	// tree->insert(3);
	// tree->insert(2);

	// tree->preOrder();

	// cout << "contains 4: " << tree->contains(4) << endl;
	// cout << "contains 1: " << tree->contains(1) << endl;
	// cout << "contains 2: " << tree->contains(2) << endl;
	// cout << "contains 5: " << tree->contains(5) << endl;
	// cout << "contains 20: " << tree->contains(20) << endl;

	// cout << tree->validate() << endl;

	vector<int> oddAscending;
	vector<int> oddDescending;
	vector<int> oddRandom;

	for (int i = 1; i < 100; i += 2)
	{
		oddAscending.push_back(i);
		oddDescending.push_back(i);
		oddRandom.push_back(i);
	}

	reverse(oddDescending.begin(), oddDescending.end());

	random_shuffle(oddRandom.begin(), oddRandom.end());


	AVLTree<int> *treeAscending = new AVLTree<int>();
	AVLTree<int> *treeDescending = new AVLTree<int>();
	AVLTree<int> *treeRandom = new AVLTree<int>();

	for (int i = 0; i < oddAscending.size(); ++i)
	{
		treeAscending->insert(oddAscending[i]);
		treeDescending->insert(oddDescending[i]);
		treeRandom->insert(oddRandom[i]);
	}

	cout << "Height of AVL tree that has odd ascending: " << treeAscending->height() << endl;
	cout << "Height of AVL tree that has odd descending: " << treeDescending->height() << endl;
	cout << "Height of AVL tree that has odd random: " << treeRandom->height() << endl;

	cout << endl;

	cout << "validate of AVL tree that has odd ascending: " << treeAscending->validate() << endl;
	cout << "validate of AVL tree that has odd descending: " << treeDescending->validate() << endl;
	cout << "validate of AVL tree that has odd random: " << treeRandom->validate() << endl;	

	cout << endl;

	for (int i = 1; i <= 100; ++i)
	{
		int found = treeAscending->contains(i);
		cout << "treeAscending contains " << i << ": " << found << endl;
		if (found == 1 && i%2 == 0 || (found == 0 && i%2 == 1) )
		{
			cout << "My implementation of AVL is wrong!\n";
		}
	}

	for (int i = 1; i <= 100; ++i)
	{
		int found = treeDescending->contains(i);
		cout << "treeDescending contains " << i << ": " << found << endl;
		if (found == 1 && i%2 == 0 || (found == 0 && i%2 == 1) )
		{
			cout << "My implementation of AVL is wrong!\n";
		}
	}

	for (int i = 1; i <= 100; ++i)
	{
		int found = treeRandom->contains(i);
		cout << "treeRandom contains " << i << ": " << found << endl;
		if (found == 1 && i%2 == 0 || (found == 0 && i%2 == 1) )
		{
			cout << "My implementation of AVL is wrong!\n";
		}
	}

	delete treeAscending;
	delete treeDescending;
	delete treeRandom;

	return 0;
}