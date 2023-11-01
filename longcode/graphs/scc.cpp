#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
using namespace std;

typedef vector<int>vi;
typedef vector<vi>vvi;
typedef pair<int,int>ii;
typedef vector<ii>vii;
typedef int64_t ll;

struct uf{vi p;uf(int n):p(n,-1){}
int fd(int n){return p[n]<0?n:p[n]=fd(p[n]);}
int sz(int n){return-p[fd(n)];}
bool same(int x,int y){return fd(x)==fd(y);}
void join(int x,int y){x=fd(x);y=fd(y);
	if(x!=y){if(p[x]<p[y])swap(x,y);
	p[y]+=p[x];p[x]=y;}}};

//2ai
// #include "union_find.cpp"
void tarjan(vvi&adj,uf&a,vi&o){
int n=adj.size(),i=n;vi l(n),h(n);
function<void(int,int)>scc=[&](int c,int p){
	if(!l[c]){l[c]=h[c]=i--;for(int t:adj[c]){
		scc(t,c);h[c]=max(h[c],h[t]);}
	(l[c]==h[c])?o.push_back(c):a.join(c,p);
	h[c]=0;}}; for(int c=0;c<n;c++)scc(c,c);}

int main(){
	
	return 0;
}
