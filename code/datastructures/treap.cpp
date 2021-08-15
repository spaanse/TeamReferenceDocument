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
namespace treap{typedef int T;
struct nd{T v;int h,s=1;nd*p=0,*l=0,*r=0;
	nd(T _v){v=_v;h=rand();}};
int h(nd*n){return n->h;}
int sz(nd*n){return n?n->s:0;}
void upd(nd*n){if(!n)return;
	n->p=0;n->s=1+sz(n->l)+sz(n->r);
	if(n->l){n->l->p=n;}if(n->r){n->r->p=n;}}
nd*copy(nd*t){if(!t){return 0;}
	nd*c=new nd{*t};c->l=copy(t->l);
	c->r=copy(t->r);upd(c);return c;}
void del(nd*&t){if(!t)return;
	del(t->l);del(t->r);delete t;t=0;}
void split(nd*t,T v,nd*&l,nd*&r){
	if(!t){l=r=0;return;}
	if(v<t->v){split(t->l,v,l,t->l);r=t;}
	if(v>t->v){split(t->r,v,t->r,r);l=t;}
	if(v==t->v){l=t->l;r=t->r;delete t;}
	else upd(t);}
void concat(nd*&t,nd*l,nd*r){
	if(!l||!r){t=l?l:r;upd(t);return;}
	if(h(l)>h(r)){concat(l->r,l->r,r);t=l;}
	else{concat(r->l,l,r->l);t=r;}upd(t);}
void ins(nd*&t,nd*n){
	if(!t){t=n;upd(t);return;}
	if(h(n)>h(t))split(t,n->v,n->l,n->r),t=n;
	else{ins(n->v<t->v?t->l:t->r,n);}upd(t);}
void ins(nd*&t,T v){ins(t,new nd{v});}
void rem(nd*&t,T v,nd*&d){if(!t)return;
	if(t->v==v){d=t;concat(t,t->l,t->r);}
	else{rem(v<t->v?t->l:t->r,v,d);}upd(t);}
void rem(nd*&t,T v){
	nd*tmp=0;rem(t,v,tmp);delete tmp;}
nd*find(nd*t,T v,int&i){while(t&&t->v!=v){
	if(v<t->v)t=t->l;
	else{i+=sz(t->l)+1;t=t->r;}}
	if(t){i+=sz(t->l);}return t;}
nd*find(nd*t,T v){
	int tmp=0;return find(t,v,tmp);}
nd*root(nd*n){while(n->p){n=n->p;}return n;}
nd*nth(nd*t,int i){while(t&&i!=sz(t->l)){
	if(i<sz(t->l))t=t->l;
	else{i-=sz(t->l)+1;t=t->r;}}return t;}
nd*min(nd*t){return nth(t,0);}
nd*max(nd*t){return nth(t,sz(t)-1);}
nd*skip(nd*n,int d){find(root(n),n->v,d);
	return nth(root(n),d);}
nd*succ(nd*n){return skip(n,1);}
nd*pred(nd*n){return skip(n,-1);}
}using namespace treap;

// void setop(nd*&l,nd*&r,char b){
// 	if(!l||!r){l=l?l:r;r=0;
// 		if(!(b&1)){del(l);}return;}
// 	if(h(l)<h(r))swap(l,r);
// 	nd*lt,*rt=lt=0;
// 	bool fnd=find(r,l->v);split(r,l->v,lt,rt);
// 	setop(l->l,lt,b);setop(l->r,rt,b);
// 	if(!(fnd?(b&2):(b&1)))rem(l,l->v);
// 	r=0;upd(l);}
// void diff(nd*&l,nd*&r){setop(l,r,1);}
// void isct(nd*&l,nd*&r){setop(l,r,2);}
// void merge(nd*&l,nd*&r){setop(l,r,3);}
// void setmin(nd*&l,nd*r){if(!l||!r)return;
// 	nd*lt,*rt=lt=0;split(l,r->v,lt,rt);
// 	setmin(lt,r->l);setmin(rt,r->r);
// 	concat(l,lt,rt);upd(l);}

void print(nd*t, string prefix="") {
	if (!t) return;
	print(t->l, prefix+"  |");
	cout << prefix << setw(3) << t->v << endl;
	print(t->r, prefix+"  |");
}

void validate(nd*t) {
	if (!t) return;
	assert(t->s == 1+sz(t->l)+sz(t->r));
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
	nd *tree1=0, *tree2=0;
	ins(tree1,1);
	ins(tree1,4);
	ins(tree2,4);
	ins(tree2,2);
	print(tree1); cout << endl;
	del(tree1);
	del(tree2);
	return 0;
}
