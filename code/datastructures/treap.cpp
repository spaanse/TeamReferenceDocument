#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <assert.h>
#include <iomanip>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
//727
namespace treap { typedef int T;
struct node{T v; int h, s=1;
	node *p=NULL, *l=NULL, *r=NULL;
	node(T _v){v=_v; h = rand();}};
int h(node* n) {return n->h;}
//a26
// the size of any node pointer
int size(node* n) {return n ? n->s : 0;}
// update parent pointers and size
void update(node*n) { if (!n) return;
	n->p=NULL; n->s=1+size(n->l)+size(n->r);
	if(n->l){n->l->p=n;} if(n->r){n->r->p=n;}}
// deep copy of a tree
node *copy(node*t) {
	if(!t){return NULL;} node *c=new node{*t};
	c->l = copy(t->l); c->r = copy(t->r);
	update(c); return c;}
// deep delete of a tree
void delAll(node*&t) {
	if(t) {delAll(t->l); delAll(t->r);
		delete t; t = NULL;}}
// split all nodes <v into l, all >v into r
void split(node*t, T v, node*&l, node*&r){
	if (!t) {l = r = NULL; return;}
	if (v < t->v){split(t->l,v,l, t->l); r=t;}
	if (v > t->v){split(t->r,v,t->r, r); l=t;}
	if (v == t->v) {l=t->l; r=t->r; delete t;}
	else update(t);}
// given max l<min r combines l,r into t
void concat(node*&t, node*l, node*r) {
	if (!l || !r) {t=l?l:r;update(t); return;}
	if (h(l)>h(r)){concat(l->r, l->r, r);t=l;}
	else          {concat(r->l, l, r->l);t=r;}
	update(t);}
// inserts node n into tree t
void insert(node*&t, node*n) {
	if (!t) {t=n; update(t); return;}
	if(h(n)>h(t)) split(t,n->v,n->l,n->r),t=n;
	else insert(n->v < t->v ? t->l : t->r, n);
	update(t);}
// inserts value v into tree t
void insert(node*&t, T v){
	insert(t, new node{v});}
// cuts value v from tree t, placed in d
void remove(node*&t, T v, node*&d) {
	if (!t) return;
	if (t->v==v) {d=t; concat(t, t->l, t->r);}
	else remove(v<t->v ? t->l : t->r, v, d);
	update(t);}
// removes value v from tree t
void remove(node*&t, T v){
	node*tmp=NULL;remove(t,v,tmp);delete tmp;}
// finds value v in tree t, i becomes its idx
node *find(node*t, T v, int&i) {
	while(t && t->v != v)
		if(v < t->v) t = t->l;
		else {i += size(t->l) + 1; t = t->r;}
	if (t) {i += size(t->l);} return t;}
node *find(node*t, T v) {
	int tmp=0; return find(t,v,tmp);}
// finds the root of the tree containing n
node *root(node*n) {
	while (n->p) {n = n->p;} return n;}
// finds the i-th node in the tree t
node *nth(node*t, int i) {
	while(t && i != size(t->l))
		if(i < size(t->l)) t = t->l;
		else {i -= size(t->l) + 1; t = t->r;}
	return t;}
// finds the smallest/largest node in tree t
node *min(node*t){return nth(t, 0);}
node *max(node*t){return nth(t, size(t)-1);}
// finds the node with idx diff greater
node *skip(node*n, int diff) {
	find(root(n),n->v,diff);
	return nth(root(n),diff);}
// finds the next greater/smaller node
node *succ(node*n) {return skip(n, 1);}
node *pred(node*n) {return skip(n,-1);}
// perform sym. set operation on l,r; res in l
void setop(node*&l,node*&r,char b) {
	if (!l || !r) {l=l?l:r; r=NULL;
		if (!(b&1)){delAll(l);} return;}
	if (h(l) < h(r)) swap(l,r);
	node *lt, *rt = lt = NULL;
	bool fnd=find(r,l->v);split(r,l->v,lt,rt);
	setop(l->l, lt, b); setop(l->r, rt, b);
	if (!(fnd?(b&2):(b&1))) remove(l, l->v);
	r=NULL; update(l);}
// compute sym. diff, isct, union
void diff (node*&l, node*&r) {setop(l,r,1);}
void isct (node*&l, node*&r) {setop(l,r,2);}
void merge(node*&l, node*&r) {setop(l,r,3);}
// compute set minus l\r, result in l
void setmin (node*&l, node*r) {
	if (!l || !r) return;
	node *lt,*rt=lt=NULL; split(l,r->v,lt,rt);
	setmin(lt,r->l); setmin(rt, r->r);
	concat(l,lt,rt); update(l);}
} using namespace treap;

void print(node*t, string prefix="") {
	if (!t) return;
	print(t->l, prefix+"  |");
	cout << prefix << setw(3) << t->v << endl;
	print(t->r, prefix+"  |");
}

void validate(node*t) {
	if (!t) return;
	assert(t->s == 1+size(t->l)+size(t->r));
	if (t->l) { validate(t->l);
		assert(t->l->p == t);
		assert(max(t->l)->v < t->v);
		assert(h(t->l) <= h(t));}
	if (t->r) { validate(t->r);
		assert(t->r->p == t);
		assert(min(t->r)->v > t->v);
		assert(h(t->r) <= h(t));}
}

int main() {
	node *tree1=NULL, *tree2=NULL;
	insert(tree1,1);
	insert(tree1,4);
	insert(tree2,4);
	insert(tree2,2);
	setmin(tree1,tree2);
	print(tree1); cout << endl;
	delAll(tree1);
	delAll(tree2);
	return 0;
}