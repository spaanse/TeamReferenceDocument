#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <assert.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
//727
template<typename T>struct impl_treap{
struct nd{T v;int h,s=1;bool f=0;
	nd*l=NULL,*r=NULL;
	nd(T _v){v=_v;h=rand();}}*s;
int sz(nd*n){return n?n->s:0;}
void upd(nd*n){
	if(n)n->s=1+sz(n->l)+sz(n->r);}
nd*cpy(nd*t){
	if(!t) {return NULL;} nd*c=new nd(*t);
	c->l=cpy(t->l);c->r=cpy(t->r);return c;}
void del(nd*&t){if(!t)return;
	del(t->l);del(t->r);t=NULL;}
void ps(nd*t){if(!t||!t->f)return;
	swap(t->l,t->r);t->f=0;
	if(t->l){t->l->f^=1;} if(t->r)t->r->f^=1;}
void spt(nd*t,nd*&l,nd*&r,
	 int k,int d=0){if(!t) {l=r=NULL; return;}
	ps(t);int ck=d+sz(t->l);
	if(ck<k) {spt(t->r,t->r,r,k,ck+1);l=t;}
	else{spt(t->l,l,t->l,k,d);r=t;}upd(t);}
void cc(nd*&t,nd*l,nd*r){ps(l);ps(r);
	if(!l||!r) {t=l?l:r;return;}
	if(l->h>r->h) {cc(l->r,l->r,r);t=l;}
	else{cc(r->l,l,r->l);t=r;}upd(t);}	
void ins(nd*&t,nd*n,int k,int d=0){
	if(!t) {t=n;upd(t);return;}
	ps(t);int ck=d+sz(t->l);
	if(n->h>t->h)spt(t,n->l,n->r,k,d),t=n;
	else if(k<=ck)ins(t->l,n,k,d);
	else{ins(t->r,n,k,ck+1);}upd(t);}
void rem(nd*&t, nd*&r,
	int k,int d=0){if(!t)return;
	ps(t);int ck=d+sz(t->l);
	if(ck==k) {r=t;cc(t,t->l,t->r);}
	if(ck>k) rem(t->l,r,k,d);
	if(ck<k) {rem(t->r,r,k,ck+1);} upd(t);}
nd*find(nd*t,int k,int d=0){
	ps(t);int ck=d+sz(t->l);
	if(!t||k==ck)return t;
	if(k<ck)return find(t->l,k,d);
	else    return find(t->r,k,ck+1);}
impl_treap()= default;~impl_treap(){del(s);}
impl_treap(impl_treap<T>&o){s=cpy(o.s);} 
void insert(T v,int i){ins(s,new nd(v),i);}
void remove(int i){nd*del=NULL;
	rem(s,del,i);delete del;}
void reverse(int l,int r){
	nd*lt,*m,*rt=m=lt=NULL;
	spt(s,lt,rt,r);spt(lt,lt,m,l);
	if(m) {m->f^=1;} cc(lt,lt,m);cc(s,lt,rt);}
size_t size(){return sz(s);}
T&operator[](size_t i){
	assert(0<=i&&i<size());
	return find(s,i)->v;}};

int main(){
	impl_treap<int>arr;
	for(int i=0;i<20;i++){
		int newVal=rand()%100;
		arr.insert(newVal,i);
		if (i) cout << " ";
		cout << newVal;
	} cout << endl;
	arr.remove(3);arr.remove(5);arr.remove(5);
	for (int i = 0; i < 17; i++) {
		if (i) cout << " ";
		cout << arr[i];
	} cout << endl;
	arr.reverse(5,10);
	for (int i = 0; i < 17; i++) {
		if (i) cout << " ";
		cout << arr[i];
	} cout << endl;
	impl_treap<int> arr2 = arr;
	for (int i = 0; i < 17; i++) {
		if (i) cout << " ";
		cout << arr2[i];
	} cout << endl;

	return 0;
}
