#ifndef WAVLTREE_H
#define WAVLTREE_H

#include <iostream>
using namespace std;

// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file 
template <typename KeyType, typename ValType>
class WAVLTree {
	public:
		// DO NOT MODIFY PUBLIC MEMBERS BELOW THIS LINE
		WAVLTree();
		~WAVLTree();
		void insert(KeyType key, ValType val);
		ValType find(const KeyType& key);
		int getSize();
		int getHeight();
		int getRank(const KeyType& key);
		// DO NOT MODIFY PUBLIC MEMBERS ABOVE THIS LINE

		// define new public members
		void insertWithoutDupl(KeyType key, ValType val);
		void printTree(); //for debug
		void remove(KeyType key); //for BF
		void removeWithDup(KeyType key, ValType val); //for BF
		KeyType findByMaxVal(ValType v); //for FF
		ValType findByMaxKey(KeyType k); //for FF

		WAVLTree(bool using_max_val);

		struct node {
			KeyType key;
			ValType val;
			ValType maxVal; //for FF
			node *left, *right, *parent;
			int rank;

			node(KeyType new_key, ValType new_val, node* new_p)
				:key{ new_key }, val{ new_val }, maxVal{ new_val }, left{ nullptr }, right{ nullptr }, parent{ new_p }, rank{ 1 }{}
		};

	private:
		// define new private members

		node* root;
		bool is_using_max_val;

		void deleteTree(node* r) {
			if (r) {
				deleteTree(r->left);
				deleteTree(r->right);
				delete r;
			}
		}

		int computeHeight(node* n);
		void rebalanceInsert(node* n);
		void rebalanceRemove(node* n);
		int rankDif(node* n);
		void promote(node* n);
		void demote(node* n);
		void rrRotation(node* n);
		void llRotation(node* n);
		void rlRotation(node* n);
		void lrRotation(node* n);
		void printTreeUtil(node* r, int space);
		node* removeUtil(KeyType key, node* n, node*& parentOfRemove);
		node* removeWithDupUtil(KeyType key, ValType val, node* n, node*& parentOfRemove);
		node* minNode(node* n);
		ValType updateMaxVal(node* n); //for BRC
		KeyType findByMaxValUtil(ValType v, node* n);
		ValType findByMaxKeyUtil(KeyType v, node* n);
		int size;
};

// fill in the definitions for each public member function and for any additional public/private members you define

template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::WAVLTree()
{
	root = nullptr;
	is_using_max_val = false;
	size = 0;
}

template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::WAVLTree(bool using_max_val) {
	root = nullptr;
	is_using_max_val = using_max_val;
	size = 0;
}

template <typename KeyType, typename ValType>
WAVLTree<KeyType, ValType>::~WAVLTree()
{
	deleteTree(root);
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::insertWithoutDupl(KeyType key, ValType val)
{
	if (!root) {
		root = new node(key, val, nullptr);
		size++;
	}
	else {
		node* t = root;
		while (t->key != key) {
			if (key < t->key) {
				if (!t->left) {
					t->left = new node(key, val, t);
					size++;
				}
				t = t->left;
			}
			else if (key > t->key) {
				if (!t->right) {
					t->right = new node(key, val, t);
					size++;
				}
				t = t->right;
			}
		}
		t->val = val;
		rebalanceInsert(t);
	}
	if (is_using_max_val) {
		updateMaxVal(root);
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::insert(KeyType key, ValType val)
{
	if (!root) {
		root = new node(key, val, nullptr);
		size++;
	}else {
		node* t = root;
		while (t) {
			if (key <= t->key) {
				if (!t->left) {
					t->left = new node(key, val, t);
					size++;
					t = t->left;
					break;
				}
				t = t->left;
			}
			else if (key > t->key) {
				if (!t->right) {
					t->right = new node(key, val, t);
					size++;
					t = t->right;
					break;
				}
				t = t->right;
			}
		}
		rebalanceInsert(t);
	}
	if (is_using_max_val) {
		updateMaxVal(root);
	}
}



template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::find(const KeyType& key)
{
	node* t = root;
	while (t) {
		if (key < t->key) {
			t = t->left;
		}
		else if (key > t->key) {
			t = t->right;
		}
		else {
			return t->val;
		}
	}
	return -1;
}
template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getSize()
{
	return size; 
}

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getHeight()
{
	return computeHeight(root);
}

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::getRank(const KeyType& key)
{
	node* t = root;
	while (t) {
		if (key < t->key) {
			t = t->left;
		}
		else if (key > t->key) {
			t = t->right;
		}
		else {
			return t->rank;
		}
	}
	return -1;
}

// add definitions for any public/private members if needed

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::computeHeight(node* n) {
	if (!n) {
		return 0;
	}
	else {
		int l = computeHeight(n->left);
		int r = computeHeight(n->right);

		if (l > r) {
			return l + 1;
		}
		else {
			return r + 1;
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::rebalanceInsert(node* n) {
	if (n == root) {
		return;
	}
	if (rankDif(n) == 1) {
		return;
	}
	else if (rankDif(n) == 0) {
		node* p = n->parent;
		if (p->left == n && ((p->right==nullptr && p->rank==1) || rankDif(p->right)==1)) {
			//Case 1a
			promote(p);
			rebalanceInsert(p);
		}
		else if (p->right == n && ((p->left == nullptr && p->rank == 1) || rankDif(p->left) == 1)) {
			//Case 1a mirrored
			promote(p);
			rebalanceInsert(p);
		}
		else if (p->left == n && ((p->right == nullptr && p->rank == 2) || rankDif(p->right) == 2)) {
			//Case 2
			if ((n->left == nullptr && n->rank == 1) || rankDif(n->left) == 1) {
				//Case 2a
				llRotation(n);
				demote(p);
				return;
			}
			else if ((n->right == nullptr && n->rank == 1) || rankDif(n->right) == 1) {
				//Case 2b
				node* t = n->right;
				lrRotation(n);
				demote(p);
				demote(n);
				promote(t);
				return;
			}
		}
		else if (p->right == n && ((p->left == nullptr && p->rank == 2) || rankDif(p->left) == 2)) {
			//Case 2 mirrored
			if ((n->right == nullptr && n->rank == 1) || rankDif(n->right) == 1) {
				//Case 2a
				rrRotation(n);
				demote(p);
				return;
			}
			else if ((n->left == nullptr && n->rank == 1) || rankDif(n->left) == 1) {
				//Case 2b
				node* t = n->left;
				rlRotation(n);
				demote(p);
				demote(n);
				promote(t);
				return;
			}
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::rebalanceRemove(node* n) {
	if (!n) {
		return;
	}
	node* s = n->left;
	node* q = n->right;
	if (s == nullptr && q == nullptr && n->rank == 2) {
		demote(n);
		rebalanceRemove(n->parent);
		return;
	}
	else if (rankDif(s) == 2 && ((q == nullptr && n->rank == 3) || rankDif(q) == 3)) {
		//Case 1a
		demote(n);
		rebalanceRemove(n->parent);
		return;
	}
	else if (rankDif(q) == 2 && ((s == nullptr && n->rank == 3) || rankDif(s) == 3)) {
		//Case 1a mirrored
		demote(n);
		rebalanceRemove(n->parent);
		return;
	}
	else if (rankDif(s) == 1 && ((q == nullptr && n->rank == 3) || rankDif(q) == 3)) {
		//Case 2
		if ((s->left == nullptr && s->rank == 2) || rankDif(s->left) == 2) {
			if (rankDif(s->right) == 2) {
				//Case 2a
				demote(n);
				demote(s);
				rebalanceRemove(n->parent);
				return;
			}
			else if (rankDif(s->right) == 1) {
				//Case 2b'
				lrRotation(s);
				demote(s);
				demote(n);
				demote(n);
				promote(s->right);
				promote(s->right);
				return;
			}
		}
		else if ((s->left == nullptr && s->rank == 1) || rankDif(s->left) == 1) {
			//Case 2b
			llRotation(s);
			promote(s);
			demote(n);
			return;
		}

	}
	else if (rankDif(q) == 1 && ((s == nullptr && n->rank == 3) || rankDif(s) == 3)) {
		//Case 2 mirrored
		if ((q->right == nullptr && q->rank == 2) || rankDif(q->right) == 2) {
			if (rankDif(q->left) == 2) {
				//Case 2a
				demote(n);
				demote(q);
				rebalanceRemove(n->parent);
				return;
			}
			else if (rankDif(q->left) == 1) {
				//Case 2b'
				rlRotation(q);
				demote(q);
				demote(n);
				demote(n);
				promote(q->left);
				promote(q->left);
				return;
			}
		}
		else if ((q->right == nullptr && q->rank == 1) || rankDif(q->left) == 1) {
			//Case 2b
			rrRotation(q);
			promote(q);
			demote(n);
			return;
		}
	}
}

template <typename KeyType, typename ValType>
int WAVLTree<KeyType, ValType>::rankDif(node* n) {
	if (n == root) {
		return -1;
	}
	if (n == nullptr) {
		return -1;
	}
	return n->parent->rank - n->rank;
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::promote(node* n) {
	if (n == nullptr) {
		return;
	}
	n->rank++;
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::demote(node* n) {
	if (n == nullptr) {
		return;
	}
	n->rank--;
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::rrRotation(node* n) {
	node* p = n->parent;
	node* t = n->right;

	if (root == p) {
		root = n;
	}

	p->right = n->left;

	if (p->right) {
		p->right->parent = p;
	}

	n->left = p;
	n->parent = p->parent;
	p->parent = n;

	if (n->parent) {
		if (n->parent->left == p) {
			n->parent->left = n;
		}
		else if (n->parent->right == p) {
			n->parent->right = n;
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::llRotation(node* n) {
	node* p = n->parent;
	node* t = n->left;

	if (root == p) {
		root = n;
	}

	p->left = n->right;
	if (p->left) {
		p->left->parent = p;
	}

	n->right = p;
	n->parent = p->parent;
	p->parent = n;

	if (n->parent) {
		if (n->parent->left == p) {
			n->parent->left = n;
		}
		else if (n->parent->right == p) {
			n->parent->right = n;
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::rlRotation(node* n) {
	node* p = n->parent;
	node* t = n->left;

	if (root == p) {
		root = t;
	}

	p->right = t->left;
	if (p->right) {
		p->right->parent = p;
	}

	n->left = t->right;
	if (n->left) {
		n->left->parent = n;
	}

	t->left = p;
	t->right = n;
	t->parent = p->parent;
	p->parent = t;
	n->parent = t;

	if (t->parent) {
		if (t->parent->left == p) {
			t->parent->left = t;
		}
		else if (t->parent->right == p) {
			t->parent->right = t;
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::lrRotation(node* n) {
	node* p = n->parent;
	node* t = n->right;

	if (root == p) {
		root = t;
	}

	p->left = t->right;
	if (p->left) {
		p->left->parent = p;
	}

	n->right = t->left;
	if (n->right) {
		n->right->parent = n;
	}

	t->right = p;
	t->left = n;
	t->parent = p->parent;
	p->parent = t;
	n->parent = t;

	if (t->parent) {
		if (t->parent->left == p) {
			t->parent->left = t;
		}
		else if (t->parent->right == p) {
			t->parent->right = t;
		}
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::remove(KeyType key) {
	node* parentOfRemove = nullptr;
	root = removeUtil(key, root, parentOfRemove);
	if (root) {
		root->parent = nullptr;
	}
	rebalanceRemove(parentOfRemove);
	if (is_using_max_val) {
		updateMaxVal(root);
	}
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::removeWithDup(KeyType key, ValType val) {
	node* parentOfRemove = nullptr;
	root = removeWithDupUtil(key, val, root, parentOfRemove);
	if (root) {
		root->parent = nullptr;
	}
	rebalanceRemove(parentOfRemove);
	if (is_using_max_val) {
		updateMaxVal(root);
	}
}

template <typename KeyType, typename ValType>
struct WAVLTree<KeyType, ValType>::node* WAVLTree<KeyType, ValType>::removeUtil(KeyType key, node* n, node*& parentOfRemove) {
	if (n == nullptr) {
		return n;
	}
	if (key < n->key) {
		n->left = removeUtil(key, n->left, parentOfRemove);
		if (n->left) {
			n->left->parent = n;
		}
	}
	else if (key > n->key) {
		n->right = removeUtil(key, n->right, parentOfRemove);
		if (n->right) {
			n->right->parent = n;
		}
	}
	else {
		if (n->left == nullptr) {
			node* temp = n->right;
			parentOfRemove = n->parent;
			delete(n);
			size--;
			return temp;
		}
		else if (n->right == nullptr) {
			node* temp = n->left;
			parentOfRemove = n->parent;
			delete(n);
			size--;
			return temp;
		}
		node* temp = minNode(n->right);
		n->key = temp->key;
		n->val = temp->val;
		n->right = removeUtil(temp->key, n->right, parentOfRemove);
		if (n->right) {
			n->right->parent = n;
		}
	}
	return n;
}

template <typename KeyType, typename ValType>
struct WAVLTree<KeyType, ValType>::node* WAVLTree<KeyType, ValType>::removeWithDupUtil(KeyType key, ValType val, node* n, node*& parentOfRemove) {
	if (n == nullptr) {
		return n;
	}
	if (key < n->key) {
		n->left = removeWithDupUtil(key, val, n->left, parentOfRemove);
		if (n->left) {
			n->left->parent = n;
		}
	}
	else if (key > n->key) {
		n->right = removeWithDupUtil(key, val, n->right, parentOfRemove);
		if (n->right) {
			n->right->parent = n;
		}
	}
	else if (key == n->key && val != n->val) {
		n->left = removeWithDupUtil(key, val, n->left, parentOfRemove);
		if (n->left) {
			n->left->parent = n;
		}
	}
	else {
		if (n->left == nullptr) {
			node* temp = n->right;
			parentOfRemove = n->parent;
			delete(n);
			size--;
			return temp;
		}
		else if (n->right == nullptr) {
			node* temp = n->left;
			parentOfRemove = n->parent;
			delete(n);
			size--;
			return temp;
		}
		node* temp = minNode(n->right);
		n->key = temp->key;
		n->val = temp->val;
		n->right = removeWithDupUtil(temp->key, temp->val, n->right, parentOfRemove);
		if (n->right) {
			n->right->parent = n;
		}
	}
	return n;
}

template <typename KeyType, typename ValType>
struct WAVLTree<KeyType, ValType>::node* WAVLTree<KeyType, ValType>::minNode(node* n) {
	node* t = n;
	while (t && t->left != nullptr) {
		t = t->left;
	}
	return t;
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::printTree() {
	printTreeUtil(root, 0);
}

template <typename KeyType, typename ValType>
void WAVLTree<KeyType, ValType>::printTreeUtil(node* r, int space) {
	// Base case  
	if (r == nullptr)
		return;

	// Increase distance between levels  
	space += 10;

	// Process right child first  
	printTreeUtil(r->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	if (is_using_max_val) {
		cout << r->key << "-" << r->rank << "-" << r->val << ":" << r->maxVal << "\n";
	}
	else {
		cout << r->key << "-" << r->rank << "-" << r->val;
		if (r->left) {
			cout << " " << r->left->val;
		}
		if (r->right) {
			cout << " " << r->right->val;
		}
		if (r->parent) {
			cout << " " << r->parent->val;
		}
		cout << "\n";
	}

	// Process left child  
	printTreeUtil(r->left, space);
}

template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::updateMaxVal(node* n) {
	if (n == nullptr) {
		return -1;
	}
	ValType max;
	ValType l = updateMaxVal(n->left);
	ValType r = updateMaxVal(n->right);
	if (l >= r) {
		max = l;
	}
	else {
		max = r;
	}
	if (max > n->val) {
		n->maxVal = max;
	}
	else {
		n->maxVal = n->val;
	}
	return n->maxVal;
}

template <typename KeyType, typename ValType>
KeyType WAVLTree<KeyType, ValType>::findByMaxVal(ValType v) {
	//Run time: O(logN)
	return findByMaxValUtil(v, root);
}

template <typename KeyType, typename ValType>
KeyType WAVLTree<KeyType, ValType>::findByMaxValUtil(ValType v, node* n) {
	//Run time: O(logN)
	//not traversing the whole tree because it only takes 1 operation
	//to know if the left subtree or the right subtree has node
	//that fit the item by looking at the maxVal(BRC)
	//The maximun nodes that this function will traverse is 2logN
	//when it goes right for every recursion.
	if (!n) {
		return -1;
	}
	if (!n->left && !n->right) {
		if (v <= n->val) {
			return n->key;
		}
		else if (v < n->val + 1e-4) {
			return n->key;
		}
		return -1;
	}
	if (v > n->maxVal + 1e-4) {
		return -1;
	}
	
	KeyType l = findByMaxValUtil(v, n->left);
	if (l != -1) {
		return l;
	}
	else if (v <= n->val || v < n->val + 1e-4) {
		return n->key;
	}
	//Only happen when the two conditions above are false
	//this means only happen when there is no desired bin
	//neither at the left subtree nor at the current node
	//then we check the right subtree
	KeyType r = findByMaxValUtil(v, n->right);
	if (r != -1) {
		return r;
	}
	return -1;
}

template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::findByMaxKey(KeyType v) {
	//Run time: O(logN)
	return findByMaxKeyUtil(v, root);
}

template <typename KeyType, typename ValType>
ValType WAVLTree<KeyType, ValType>::findByMaxKeyUtil(KeyType v, node* n) {
	//Run time: O(logN)
	//this function is just similar to find
	if (!n) {
		return -1;
	}
	if (!n->left && !n->right) {
		if (v <= n->key) {
			return n->val;
		}
		else if (v < n->key + 1e-4) {
			return n->val;
		}
		return -1;
	}
	if (v > n->key && v > n->key + 1e-4) {
		return findByMaxKeyUtil(v, n->right);
	}
	else if (v <= n->key || v < n->key + 1e-4) {
		ValType l = findByMaxKeyUtil(v, n->left);
		if (l != -1) {
			return l;
		}
		return n->val;
	}
	return -1;
}
#endif /* WAVLTREE_H */
