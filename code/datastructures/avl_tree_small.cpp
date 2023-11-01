#pragma once
#include "../setup/header.cpp"
namespace avl{typedef int T;
struct nd{T v;nd*l=0,*r=0;int h=1;};
int ht(nd*n){return n?n->h:0;}
int bal(nd*n){return n?ht(n->r)-ht(n->l):0;}
void upd(nd*n){n->h=1+max(ht(n->l),ht(n->r));}
nd *cp(nd*n){return n?
	new nd{n->v,cp(n->l),cp(n->r),n->h}:n;}
void del(nd*&n){
	if(n){del(n->l);del(n->r);delete n;n=0;}}
void rot(nd*&n,nd*&c,nd*&g){if(n&&c&&g){
	swap(n,c);swap(c,g);upd(g);upd(n);}}
void rotL(nd*&n){rot(n,n->r,n->r->l);}
void rotR(nd*&n){rot(n,n->l,n->l->r);}
void fix(nd*&n){if(n){upd(n);
	if(bal(n->l)>0)rotL(n->l);
	if(bal(n->r)<0)rotR(n->r);
	if(bal(n)<-1)rotR(n);
	if(bal(n)>1)rotL(n);}}
void insert(nd*&n,T v){
	if(!n){n=new nd{v};return;}
	insert(v<n->v?n->l:n->r,v);fix(n);}
void rem(nd*&n,T v,nd*&m){if(n){
	if(m||n->v==v)m=n;
	rem((v<n->v?n->l:n->r),v,m);
	if(n->v==v){
		swap(n->v,m->v);swap(*n,*m);swap(n,m);}
	if(n!=m)fix(n);
	else{n=n->l?n->l:n->r;}}}
void rem(nd*n,T v){
	nd*t=0;rem(n,v,t);delete t;}
nd *fd(nd*n,T v,int&idx){while(n&&n->v!=v)
	{n=v<n->v?n->l:n->r;}return n;}
nd *fd(nd*n,T v){int t=0;return fd(n,v,t);}
nd *min(nd*n){return (n&&n->l)?min(n->l):n;}
nd *max(nd*n){return (n&&n->r)?max(n->r):n;}
// restores AVL of a splayed tree
void unsplay(nd*&n) {
	if(!n) return;
	int diff = ht(n->r) - ht(n->l);
	if(diff >  1) {rotL(n); unsplay(n->l);}
	if(diff < -1) {rotR(n); unsplay(n->r);}
	fix(n);}
// puts value v at rt, n->l and n->r AVL
void splay(nd*&n, T v) {
	if(!n||n->v == v) return;
	if(n->v < v) {splay(n->r, v);
		rotL(n); unsplay(n->l);
	} else {splay(n->l, v);
		rotR(n); unsplay(n->r);}}
// combines l,r into l according to set op. b
void setop(nd*&l, nd*&r, char b) {
	if(!l &&  b&1) {l = r; r = 0; return;}
	if(!l && ~b&1) {del(r); return;}
	if(!r && ~b&2) {del(l); return;}
	nd *elem = fd(r, l->v);
	insert(r, l->v); splay(r, l->v);
	setop(l->l, r->l, b);setop(l->r, r->r, b);
	upd(l); unsplay(l);
	if(!(elem ? b&4 : b&2)) rem(l, r->v);
	delete r; r = 0;}
void isct (nd*&l, nd*&r) {setop(l,r,4);}
void merge(nd*&l, nd*&r) {setop(l,r,7);}
void diff (nd*&l, nd*&r) {setop(l,r,3);}
void minus(nd*&l, nd*&r) {setop(l,r,2);}
} using namespace avl;

int test_avl() {
	// int n;
	// cin >> n;
	nd*tree1 = 0, *tree2 = 0;
	// insert(tree1, n);
	for(int i = 0; i < 20; i++) {
		insert(tree1,rand()%100);
		insert(tree2,rand()%100);
	}
	merge(tree1,tree2);
	cout << tree1->v << endl;
	del(tree1);
	del(tree2);
	return 0;
}
