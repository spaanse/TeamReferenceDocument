#pragma once
#include "../setup/header.cpp"
struct tree{
struct nd{set<int> c;int p=-1,s=1;};
vector<nd> t; tree(int n){t.resize(n+1);}
void add(int u,int v){
	t[u].c.insert(v);t[v].c.insert(u);}
void rt(int u,int p=0){nd&n=t[u];if(n.p-p){
	if(p>0){n.s-=t[p].s;}swap(n.p,p);
	if(p>0){rt(p,u);n.c.insert(p);}
	n.c.erase(n.p);
	if(p<0){n.s=1;
		for(int c:n.c){rt(c,u);n.s+=t[c].s;}}

}}};
