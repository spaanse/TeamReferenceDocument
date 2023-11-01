#pragma once
#include "../setup/header.cpp"
struct uf{vi p;uf(int n):p(n,-1){}
int fd(int n){return p[n]<0?n:p[n]=fd(p[n]);}
int sz(int n){return-p[fd(n)];}
bool same(int x,int y){return fd(x)==fd(y);}
void join(int x,int y){x=fd(x);y=fd(y);
// if(p[x]<p[y])swap(x,y); //O(1) amortized
	if(x!=y){p[y]+=p[x];p[x]=y;}}};
