#pragma once
#include "../setup/header.cpp"
struct tree{
struct nd{set<int> c;int p=-2,s;};
vector<nd> t; tree(int n){t.resize(n);}
void add(int u,int v){
	t[u].c.insert(v);t[v].c.insert(u);}
void rt(int u,int p=-1){nd&n=t[u];if(n.p-p){
	if(n.p>=0){n.c.insert(n.p);}n.c.erase(p);
	n.p=p;for(int c:n.c)rt(c,u);
	n.s=1;for(int c:n.c)n.s+=t[c].s;}}};
