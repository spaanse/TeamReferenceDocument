#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;

#define INF (1<<29)

bool ckmax(int&a,int b){return b>a?a=b,1:0;}
bool ckmin(int&a,int b){return b<a?a=b,1:0;}

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef int64_t ll;
//eJa
//bool ckmin(int&a,int b){return b<a?a=b,1:0;}
vi dijkstra(vvii adj, int s){
	priority_queue<ii,vii,greater<ii>> t;
	vi p(adj.size(),-1), d(adj.size(),INF);
	d[s]=0;t.push({0,s});
	while (!t.empty()) {
		int v,dv; tie(dv,v) = t.top(); t.pop();
		if (d[v]==dv) for (ii e:adj[v]) {
			int w,dw; tie(w,dw) = e; dw+=dv;
			if(ckmin(d[w],dw)) {
				p[w]=v;t.push({dw,w}); }}}
	return d;}

int main() {
	vvii adjList(6);
	adjList[0].push_back({1,7});
	adjList[0].push_back({2,9});
	adjList[0].push_back({5,14});
	adjList[1].push_back({0,7});
	adjList[1].push_back({2,10});
	adjList[1].push_back({3,15});
	adjList[2].push_back({0,9});
	adjList[2].push_back({1,10});
	adjList[2].push_back({3,11});
	adjList[2].push_back({5,2});
	adjList[3].push_back({1,15});
	adjList[3].push_back({2,11});
	adjList[3].push_back({4,6});
	adjList[4].push_back({3,6});
	adjList[4].push_back({5,9});
	adjList[5].push_back({0,14});
	adjList[5].push_back({2,2});
	adjList[5].push_back({4,9});
	vi dist = dijkstra(adjList,0);
	for (int i = 0; i < 6; i++) {
		cout << dist[i] << " ";
	} cout << endl;
	return 0;
}