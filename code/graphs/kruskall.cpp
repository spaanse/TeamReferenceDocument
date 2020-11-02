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
// Include Union Find
struct edge{int c,f,t;
	bool operator<(edge &o){return c<o.c;}};
typedef vector<edge> ve;
ve kruskall(int n, ve edges){
	sort(edges.begin(),edges.end());
	uf ts(n); ve mst; mst.reserve(n);
	for (edge e : edges) {
		if (ts.same(e.f,e.t)) continue;
		mst.push_back(e); ts.join(e.f,e.t);}
	return mst;}


int main() {
	
	return 0;
}