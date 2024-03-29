#pragma once
#include "../setup/header.cpp"
namespace avl{typedef int T;
struct nd{T v;nd*p=0,*l=0,*r=0;int d=1,s=1;};
int ht(nd*n){return n?n->d:0;}
int sz(nd*n){return n?n->s:0;}
void upd(nd*n){n->s=1+sz(n->l)+sz(n->r);
	n->d=1+max(ht(n->l),ht(n->r));
	if(n->l){n->l->p=n;} if(n->r){n->r->p=n;}}
nd *cp(nd*n){if(!n)return n;nd *c=new nd{*n};
	if(c->l){c->l=cp(c->l);}
	if(c->r){c->r=cp(c->r);}
	upd(c);return c;}
void del(nd*&n){
	if(n){del(n->l);del(n->r);delete n;n=0;}}
int bal(nd*n){return n?sz(n->r)-sz(n->l):0;}
void rotate(nd*&n,nd*&c){if(n&&c){
	nd**g=(c==n->r?&c->l:&c->r);c->p=n->p;
	swap(n,c);swap(c,*g);upd(*g);upd(n);}}
void rotL(nd*&n){if(n)rotate(n,n->r);}
void rotR(nd*&n){if(n)rotate(n,n->l);}
void fix(nd*&n){if(n){upd(n);
	if(bal(n->l)>0)rotL(n->l);
	if(bal(n->r)<0)rotR(n->r);
	if(bal(n)<-1)rotR(n);
	if(bal(n)>1)rotL(n);}}
void insert(nd*&n,T v,nd*p=0){
	if(!n){n=new nd{v,p};return;}
	insert(v<n->v?n->l:n->r,v,n);fix(n);}
void rem(nd*&n,T v,nd*&m){if(n){
	if(m||n->v==v)m=n;
	rem((n->v>v?n->l:n->r),v,m);
	if(n->v==v){
		swap(n->v,m->v);swap(*n,*m);swap(n,m);}
	if(n!=m)fix(n);
	else{n=n->l?n->l:n->r;if(n)n->p=m->p;}}}
void rem(nd*n,T v){
	nd*t=0;rem(n,v,t);delete t;}
nd *fd(nd*n,T v,int&idx){
	while(n&&n->v!=v){if(v<n->v)n=n->l;
		else{idx+=sz(n->l)+1;n=n->r;}}
	if(n){idx+=sz(n->l);}return n;}
nd *fd(nd*n,T v){int t=0;return fd(n,v,t);}
nd *rt(nd*n){while(n->p){n=n->p;}return n;}
nd *nth(nd*n,int i){
	while(n&&i!=sz(n->l))if(i<sz(n->l))n=n->l;
		else{i-=sz(n->l)+1;n=n->r;}	return n;}
nd *min(nd*n){return nth(n,0);}
nd *max(nd*n){return nth(n,sz(n)-1);}
nd *skip(nd*n,int diff){fd(rt(n),n->v,diff);
	return nth(rt(n),diff);}
nd *succ(nd*n){return skip(n,1);}
nd *pred(nd*n){return skip(n,-1);}
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

void test_avl() {
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
}
