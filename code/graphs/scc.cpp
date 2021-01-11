#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

struct uf { vi p; uf(int n) : p(n,-1) {}
	int find(int n){
		return p[n]<0 ? n : p[n] = find(p[n]);}
	int size(int n) {return -p[find(n)];}
	bool same(int x, int y) {
		return find(x)==find(y);}
	void join(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (p[x] > p[y]) swap(x,y);
		p[x] += p[y]; p[y] = x; } };

//69H
// include Union Find or change output type
uf tarjan(vvi& adj) {int n=adj.size(),i=0;
vi v(n),l(n),h(n),s; uf a(n);
function<void(int)> scc=[&](int c){
	l[c]=h[c]=v[c]=++i; s.push_back(c);
	for (int t:adj[c]) {
		if (!h[t]) scc(t);
		if (v[t]) l[c]=min(l[c],l[t]);}
	if (l[c]==h[c]) while(1) {
		int t=s.back();s.pop_back(); v[t]=0;
		if (c!=t) a.join(c,t); else break;}};
for(int c=0;c<n;c++) if(!h[c]) scc(c);
return a;}

int main() {
	
	return 0;
}