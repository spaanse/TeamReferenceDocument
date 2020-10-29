#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;

namespace avl{
	typedef int T;
	// A node contains an item
	// pointers to the left, right and parent nodes
	// and the depth, balance and size of each subtree
	struct node {
		T item;
		node *lft = NULL, *rgt = NULL, *par = NULL;
		int depth = 1, balance=0, size=1;
	};
	// Recursively removes all nodes from the tree rooted at cur
	void delAll(node *&cur) {
		if (cur) {
			delAll(cur->lft);
			delAll(cur->rgt);
			delete cur;
		}
		cur = NULL;
	}
	// Get's the depth of the node pointed to, or 0 if the pointer is NULL
	int getDepth(node *cur) {
		if (cur) return cur->depth;
		return 0;
	}
	// Get's the size of the node pointed to, or 0 if the pointer is NULL
	int getSize(node *cur) {
		if (cur) return cur->size;
		return 0;
	}
	// Get's the balance of the node pointed to, or 0 if the pointer is NULL
	int getBalance(node *cur) {
		if (cur) return cur->balance;
		return 0;
	}
	// Updates the properties of a node based on the children
	void update(node* cur) {
		int lftDpt = getDepth(cur->lft);
		int rgtDpt = getDepth(cur->rgt);
		cur->depth = 1+max(lftDpt,rgtDpt);
		cur->balance = rgtDpt - lftDpt;
		cur->size = 1 + getSize(cur->lft) + getSize(cur->rgt);
	}
	// Rotates the edge between cur and cld, cur moves down and cld up.
	// Uses pointers passed by reference to simplify the update of the parent
	void rotate(node *&cur, node *&cld) {
		if (not cld) return;
		// a pointer to the pointer cld->lft or cld->rgt
		node **gcl;
		// which is set based on the relation between cur and cld
		if (cld == cur->rgt) gcl = &cld->lft;
		if (cld == cur->lft) gcl = &cld->rgt;
		// update the parent of cld
		cld->par = cur->par;
		// update the parent of cur
		cur->par = cld;
		// update the parent of the grandchild
		if (*gcl) (*gcl)->par = cur;
		// update the child pointers
		swap(cur,cld); swap(cld, *gcl);
		// update the properties of the new root and child
		update(*gcl); update(cur);
	}
	// rotates cur - cur->rgt to the left
	void rotLft(node *&cur) {
		if (cur) rotate(cur,cur->rgt);
	}
	// rotates cur - cur->lft to the right
	void rotRgt(node *&cur) {
		if (cur) rotate(cur,cur->lft);
	}
	// rebalance a node if necessary
	void balance(node *&cur) {
		if (not cur) return;
		update(cur);
		if (cur->balance < -1) {
			if (getBalance(cur->lft) > 0)
				rotLft(cur->lft);
			rotRgt(cur);
		} else if (cur->balance > 1) {
			if (getBalance(cur->rgt) < 0)
				rotRgt(cur->rgt);
			rotLft(cur);
		}
	}
	// insert a value into the AVL tree
	void insert(node *&cur, T value) {
		if (not cur) cur = new node {value};
		if (value < cur->item) insert(cur->lft, value);
		if (value > cur->item) insert(cur->rgt, value);
		if (cur->lft) cur->lft->par = cur;
		if (cur->rgt) cur->rgt->par = cur;
		balance(cur);
	}
	// remove a value from the AVL tree
	// lowest will store the removed node after returning, or NULL if no deletion occured
	void remove(node *&cur, T value, node *&lowest) {
		if (not cur) return;
		if (lowest or cur->item == value) lowest = cur;
		if (cur->item <= value) remove(cur->rgt, value, lowest);
		else                    remove(cur->lft, value, lowest);
		if (cur->item == value) swap(cur->item, lowest->item);
		if (cur == lowest) {
			if (cur->lft) cur = cur->lft;
			else          cur = cur->rgt;
			if (cur) cur->par = lowest->par;
		} else balance(cur);
	}
	// removes a node and frees it's memory
	void remove(node *cur, T value) {
		node *tmp = NULL;
		remove(cur, value, tmp);
		delete tmp;
	}
	// find a value in the tree rooted at cur
	// after returning idx will contain the index of this node
	node* find(node *cur, T value, int &idx) {
		while (cur and cur->item != value)
			if (value < cur->item) {
				cur = cur->lft;
			} else {
				idx += getSize(cur->lft)+1;
				cur = cur->rgt;
			}
		if (cur) idx += getSize(cur->lft);
		return cur;
	}
	// version without the idx variable by reference
	node* find(node*cur,T value){
		int temp=0;
		return find(cur,value,temp);
	}
	// Find the ith largest node, converse of the idx in find
	node* nth(node *cur, int index) {
		while (cur and index != getSize(cur->lft)) {			
			if (index < getSize(cur->lft)){
				cur = cur->lft;
			} else {
				index -= getSize(cur->lft)+1;
				cur = cur->rgt;
			}
		}
		return cur;
	}
	// find the smallest vertex in the tree rooted at cur
	node* smallest(node *cur){
		return nth(cur, 0);
	}
	// find the largest vertex in the tree rooted at cur
	node* largest(node *cur){
		return nth(cur, getSize(cur)-1);
	}
	// find the next largest vertex in the tree of cur
	node* successor(node *cur) {
		if (cur->rgt) {
			cur = cur->rgt;
			return smallest(cur);
		}
		while (cur->par and cur->par->rgt == cur) {
			cur = cur->par;
		}
		return cur->par;
	}
	// find the next smaller vertex in the tree of cur
	node* predecessor(node *cur) {
		if (cur->lft) {
			cur = cur->lft;
			return largest(cur);
		}
		while (cur->par and cur->par->lft == cur) {
			cur = cur->par;
		}
		return cur->par;
	}
	// given a splayed tree (see next function) restores it to an AVL tree
	void unsplay(node *&cur) {
		if (not cur) return;
		int diff = getDepth(cur->rgt) - getDepth(cur->lft);
		if (diff > 1) {
			rotLft(cur);
			unsplay(cur->lft);
		}
		if (diff <-1) {
			rotRgt(cur);
			unsplay(cur->rgt);
		}
		balance(cur);
	}
	// moves the node with value to the root
	// the left and right subtree of the root will be AVL, but the root isn't
	void splay(node *&cur, T value) {
		if (not cur or cur->item == value) return;
		if (cur->item < value) {
			splay(cur->rgt, value);
			rotLft(cur);
			unsplay(cur->lft);
		} else {
			splay(cur->lft, value);
			rotRgt(cur);
			unsplay(cur->rgt);
		}
	}
	// Concatenate an AVL tree, a node and another AVL tree into a combined AVL tree
	// Result will be stored in mid
	void concat(node *&lft, node *&mid, node *&rgt) {
		mid->lft = lft;
		if (lft) lft->par = mid;
		lft = NULL;
		mid->rgt = rgt;
		if (rgt) rgt->par = mid;
		rgt = NULL;
		unsplay(mid);
	}
	// Concatenate two AVL trees into a combined AVL tree
	// result will be stored in lft
	void concat(node *&lft, node*& rgt) {
		if (not rgt) return;
		splay(rgt, smallest(rgt)->item);
		rgt->lft = lft;
		if(lft) lft->par = rgt;
		unsplay(rgt);
		lft = rgt;
		rgt=NULL;
	}
	// Perform a set operation on the trees rooted at lft and rgt
	// b is a bitset that decides which operation
	// b&1 is true if the result should contain a value when only rgt had that value (01)
	// b&2 is true if the result should contain a value when only lft had that value (10)
	// b&4 is true if the result should contain a value when both lft and rgt had that value (11)
	// result, stored in lft, will be an AVL tree with the result of the set operation
	void binop(node *&lft, node *&rgt, char b) {
		if (not lft and b&1) {
			if (b&1) lft = rgt;
			rgt=NULL;
			return;
		}
		if (not lft and not (b&1)) {
			delAll(rgt);
			return;
		}
		if (not rgt and not (b&2)) {
			delAll(lft);
			return;
		}
		node* elem = find(rgt, lft->item);
		insert(rgt, lft->item);
		splay(rgt, lft->item);
		binop(lft->lft,rgt->lft,b);
		binop(lft->rgt,rgt->rgt,b);
		if (lft->lft) lft->lft->par = lft;
		if (lft->rgt) lft->rgt->par = lft;
		unsplay(lft);
		if (not (elem ? b&4 : b&2)) {
			remove(lft,rgt->item);
		}
		delete rgt; rgt = NULL;
	}
	// Define set operations using the function binop
	// intersect: the result only contains a value if both inputs contained it
	void isct (node *&lft, node *&rgt) {binop(lft,rgt,4);}
	// merge: the result contains a value if either input contained it
	void merge(node *&lft, node *&rgt) {binop(lft,rgt,7);}
	// symmetric difference: result contains value if exactly one input contained it
	void sdiff(node *&lft, node *&rgt) {binop(lft,rgt,3);}
	// set minus: result contains all values of lft that were not in rgt
	void minus(node *&lft, node *&rgt) {binop(lft,rgt,2);}
	// other bitsets are unnecessary: 
	//  - binop(lft,rgt,0) returns nothing,
	//  - binop(lft,rgt,1) is equivalent to binop(rgt,lft,2)
	//  - binop(lft,rgt,5) is equivalent to simply returning rgt
	//  - binop(lft,rgt,6) is equivalent to simply returning lft

	// prints the tree rooted at cur
	void print(node *cur, string prefix="") {
		if (not cur) return;
		if (cur->lft) print(cur->lft, prefix+"   |");
		cout << prefix << setw(3) << cur->item << "|" << endl;
		if (cur->rgt) print(cur->rgt, prefix+"   |");
	}
	// asserts that all (AVL) properties hold for the tree rooted at cur
	void validate(node *cur) {
		if (not cur) return;
		assert(cur->balance == getDepth(cur->rgt) - getDepth(cur->lft));
		assert(cur->depth == 1+max(getDepth(cur->lft), getDepth(cur->rgt)));
		assert(cur->size == 1+getSize(cur->lft)+getSize(cur->rgt));
		assert(abs(cur->balance) <= 1);
		if (cur->lft) {
			assert(cur->lft->par == cur);
			validate(cur->lft);
			assert(largest(cur)->item < cur->item);
		}
		if (cur->rgt) {
			assert(cur->rgt->par == cur);
			validate(cur->rgt);
			assert(smallest(cur)->item > cur->item);
		}
	}
}

int main() {
	avl::node *tree1 = NULL, *tree2 = NULL;
	for (int i = 0; i < 40; i++) {
		avl::insert(tree1,rand() % 100);
		avl::insert(tree2,rand() % 100);
	}
	avl::print(tree1);
	cout << endl;
	avl::print(tree2);
	avl::validate(tree1);
	avl::validate(tree2);
	avl::binop(tree1, tree2, 7);
	cout << endl;
	avl::print(tree1);
	avl::validate(tree1);
	avl::delAll(tree1);
	avl::delAll(tree2);
	return 0;
}