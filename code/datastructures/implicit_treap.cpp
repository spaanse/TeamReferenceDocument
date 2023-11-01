#pragma once
#include "../setup/header.cpp"
struct nd{
int v;int h,s=1,f=0;nd*l,*r=l=0;
nd(int _v){v=_v;h=rand();}};
int sz(nd*n){return n?n->s:0;}
void upd(nd*n){
	if(n)n->s=1+sz(n->l)+sz(n->r);}
nd*cpy(nd*t){
	if(!t){return 0;}nd*c=new nd(*t);
	c->l=cpy(t->l);c->r=cpy(t->r);return c;}
void del(nd*&t){if(!t)return;
	del(t->l);del(t->r);delete t;t=0;}
void ps(nd*t){if(!t||!t->f)return;
	swap(t->l,t->r);t->f=0;
	if(t->l){t->l->f^=1;}if(t->r)t->r->f^=1;}
void spt(nd*t,nd*&l,nd*&r,int k,int d=0){
	if(!t){l=r=0;return;}
	ps(t);int ck=d+sz(t->l);
	if(ck<k){spt(t->r,t->r,r,k,ck+1);l=t;}
	else{spt(t->l,l,t->l,k,d);r=t;}upd(t);}
void cc(nd*&t,nd*l,nd*r){ps(l);ps(r);
	if(!l||!r){t=l?l:r;return;}
	if(l->h>r->h){cc(l->r,l->r,r);t=l;}
	else{cc(r->l,l,r->l);t=r;}upd(t);}	
void ins(nd*&t,nd*n,int k,int d=0){
	if(!t){t=n;upd(t);return;}
	ps(t);int ck=d+sz(t->l);
	if(n->h>t->h)spt(t,n->l,n->r,k,d),t=n;
	else if(k<=ck)ins(t->l,n,k,d);
	else{ins(t->r,n,k,ck+1);}upd(t);}
void rem(nd*&t,nd*&r,int k,int d=0){
	if(!t){return;}ps(t);int ck=d+sz(t->l);
	if(ck==k){r=t;cc(t,t->l,t->r);}
	if(ck>k)rem(t->l,r,k,d);
	if(ck<k){rem(t->r,r,k,ck+1);}upd(t);}
nd*at(nd*t,int k,int d=0){int ck=d+sz(t->l);
	ps(t);if(!t||k==ck)return t;
	if(k<ck)return at(t->l,k,d);
	elsereturn at(t->r,k,ck+1);}
void rev(nd*t,int l,int r){nd*lt,*m,*rt;
	spt(t,lt,rt,r);spt(lt,lt,m,l);
	if(m){m->f^=1;}cc(lt,lt,m);cc(t,lt,rt);}

int test_treap(){
	nd*arr=0;
	for(int i=0;i<20;i++){
		int newVal=rand()%100;
		ins(arr,new nd(newVal),i);
		if(i)cout<<"";
		cout<<newVal;
	}cout<<endl;
	nd*tmp=0;
	rem(arr,tmp,3);delete tmp;
	rem(arr,tmp,5);delete tmp;
	rem(arr,tmp,5);delete tmp;
	for(int i=0;i<17;i++){
		if(i)cout<<"";
		cout<<at(arr,i)->v;
	}cout<<endl;
	rev(arr,5,10);
	for(int i=0;i<17;i++){
		if(i)cout<<"";
		cout<<at(arr,i)->v;
	}cout<<endl;
	nd*arr2=cpy(arr);
	for(int i=0;i<17;i++){
		if(i)cout<<"";
		cout<<at(arr2,i)->v;
	}cout<<endl;
	return 0;
}
