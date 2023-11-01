#pragma once
#include "../setup/header.cpp"
#include "../datastructures/union_find.cpp"
void tarjan(vvi&adj,uf&a,vi&o){
int n=adj.size(),i=n;vi l(n),h(n);
function<void(int,int)>scc=[&](int c,int p){
	if(!l[c]){l[c]=h[c]=i--;for(int t:adj[c]){
		scc(t,c);ckmax(h[c],h[t]);}
	(l[c]==h[c])?o.push_back(c):a.join(c,p);
	h[c]=0;}}; for(int c=0;c<n;c++)scc(c,c);}
