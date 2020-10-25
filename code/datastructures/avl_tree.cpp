#include<algorithm>
#include<iostream>
#include<iomanip>
#include<assert.h>
using namespace std;
//b2w
namespace avl {typedef int T;
struct node {T v; int d = 1, s = 1;
	node *p = NULL, *l = NULL, *r = NULL;};
// deep copy of a node
node *copy(node*n) {
	if(!n){return NULL;}node *c=new node{*n};
	if(c->l) {c->l=copy(c->l); c->l->p=c;}
	if(c->r) {c->r=copy(c->r); c->r->p=c;}
	return c;}
// deep delete of a node
void delAll(node*&n) {
	if(n) {delAll(n->l); delAll(n->r);
		delete n; n = NULL;}}
// get depth, size, balance of any node ptr
int depth(node*n) {return n ? n->d : 0;}
int size (node*n) {return n ? n->s : 0;}
int balance(node*n) {
	return n ? size(n->r)-size(n->l) : 0;}
// update size and depth of node n
void update(node*n) {
	n->d = 1 + max(depth(n->l), depth(n->r));
	n->s = 1 + size(n->l) + size(n->r);
	if (n->l){n->l->p=n;}
	if (n->r){n->r->p=n;}}
// move node n down and its child c up
void rotate(node*&n, node*&c) {
	if(!n || !c) return;
	node**g = (c == n->r ? &c->l : &c->r);
	c->p=n->p; swap(n, c); swap(c, *g);
	update(*g); update(n);}
void rotL(node*&n) {if(n) rotate(n, n->r);}
void rotR(node*&n) {if(n) rotate(n, n->l);}
// rebalance n if necessary
void fix(node*&n) {
	if(!n) {return;} update(n);
	if (balance(n->l) > 0) rotL(n->l);
	if (balance(n->r) < 0) rotR(n->r);
	if (balance(n) < -1) rotR(n);
	if (balance(n) >  1) rotL(n);}
// insert a node with value v (and parent p)
void insert(node*&n, T v, node*p=NULL) {
	if(!n) {n = new node {v,1,1,p}; return;}
	insert(v<n->v ? n->l : n->r,v,n); fix(n);}
// remove the node with value v
void remove(node*&n, T v, node*&m) {
	if(!n) {return;} if(m||n->v == v) m = n;
	remove((n->v > v ? n->l : n->r), v, m);
	if(n->v == v){
		swap(n->v,m->v);swap(*n,*m); swap(n,m);}
	if(n != m) fix(n);
	else {n = n->l?n->l:n->r;if(n)n->p=m->p;}}
void remove(node*n, T v) {
	node*t = NULL; remove(n, v, t); delete t;}
// finds node with value v, idx it's index
node *find(node*n, T v, int&idx) {
	while(n && n->v != v)
		if(v < n->v) n = n->l;
		else {idx += size(n->l) + 1; n = n->r;}
	if (n) {idx += size(n->l);} return n;}
node *find(node*n,T v){
	int tmp=0; return find(n,v,tmp);}
node *root(node*n) {
	while (n->p) {n = n->p;} return n;}
// returns the node at the i-th index
node *nth(node*n, int i) {
	while(n && i != size(n->l))
		if(i < size(n->l)) n = n->l;
		else {i -= size(n->l) + 1; n = n->r;}
	return n;}
node *min(node*n){return nth(n, 0);}
node *max(node*n){return nth(n, size(n)-1);}
// if n is kth node returns (k+diff)th node
node *skip(node*n, int diff) {
	find(root(n),n->v,diff);
	return nth(root(n),diff);}
node *succ(node*n) {return skip(n, 1);}
node *pred(node*n) {return skip(n,-1);}
// restores AVL of a splayed tree
void unsplay(node*&n) {
	if(!n) return;
	int diff = depth(n->r) - depth(n->l);
	if(diff >  1) {rotL(n); unsplay(n->l);}
	if(diff < -1) {rotR(n); unsplay(n->r);}
	fix(n);}
// puts value v at root, n->l and n->r AVL
void splay(node*&n, T v) {
	if(!n||n->v == v) return;
	if(n->v < v) {splay(n->r, v);
		rotL(n); unsplay(n->l);
	} else {splay(n->l, v);
		rotR(n); unsplay(n->r);}}
// combines l,r into l according to set op. b
void setop(node*&l, node*&r, char b) {
	if(!l &&  b&1) {l = r; r = NULL; return;}
	if(!l && ~b&1) {delAll(r); return;}
	if(!r && ~b&2) {delAll(l); return;}
	node *elem = find(r, l->v);
	insert(r, l->v); splay(r, l->v);
	setop(l->l, r->l, b);setop(l->r, r->r, b);
	update(l); unsplay(l);
	if(!(elem ? b&4 : b&2)) remove(l, r->v);
	delete r; r = NULL;}
void isct (node*&l, node*&r) {setop(l,r,4);}
void merge(node*&l, node*&r) {setop(l,r,7);}
void diff (node*&l, node*&r) {setop(l,r,3);}
void minus(node*&l, node*&r) {setop(l,r,2);}
} using namespace avl;

int main() {
	// int n;
	// cin >> n;
	node*tree1 = NULL, *tree2 = NULL;
	// insert(tree1, n);
	for(int i = 0; i < 20; i++) {
		insert(tree1,rand()%100);
		insert(tree2,rand()%100);
	}
	merge(tree1,tree2);
	cout << tree1->v << endl;
	delAll(tree1);
	delAll(tree2);
	return 0;
}
