#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
typedef queue<int> qi;

//faL
struct flow{int s=0,t;vi d,V;vvi A,C,F;qi q;
flow(int n):d(n),A(n),C(n,d){t=n-1;V=d;F=C;}
void add(int u,int v,int c){C[u][v]+=c;
	A[u].push_back({v});A[v].push_back({u});}
int r(int u,int v){return C[u][v]-F[u][v];}
int bfs(){q.push(s);d=vi(size(d));d[s]=1;
	while(q.size()){int u=q.front();q.pop();
		for(int v:A[u])if(!d[v]&&r(u,v)>0){
			d[v]=d[u]+1;q.push(v);}}return d[t];}
int dfs(int u,int c){if(u==t){return c;}
	if(c<=0||V[u]){return 0;}V[u]=2;int n,f=0;
	for(int v:A[u])if(d[v]>d[u]){
		n=dfs(v,min(c-f,r(u,v)));F[u][v]+=n;
		F[v][u]-=n;f+=n;}V[u]=f<c;return f;}
int calc(){int a=0;while(bfs()){
	V=vi(size(V));a+=dfs(s,2e9);}return a;}};

int main(){
	int numNode, numEdge;
	cin >> numNode >> numEdge;
	flow flowgraph(numNode);
	for (int i = 0; i < numEdge; i++) {
		int from,to,cap;
		cin >> from >> to >> cap;
		flowgraph.add(from,to,cap);
	}
	cout << flowgraph.calc() << endl;
	return 0;
}
