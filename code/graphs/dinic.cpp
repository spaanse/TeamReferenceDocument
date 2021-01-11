#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

//10N
struct fgraph{int n,s,t,a;vi d,V;vvi A,C,F;
queue<int>q;fgraph(int _n,int _s,int _t):
d(_n),V(_n),A(_n),C(_n,vi(_n,0)),F(C){
	n=_n;s=_s;t=_t;}
void addedge(int u,int v,int c){C[u][v]+=c;
	A[u].push_back({v});A[v].push_back({u});}
int r(int u,int v){return C[u][v]-F[u][v];}
int bfs(){q.push(s);d.assign(n,-1);d[s]=0;
	while(q.size()){int u=q.front();q.pop();
		for(int v:A[u])if(d[v]<0&&r(u,v)>0){
			d[v]=d[u]+1;q.push(v);}}return d[t];}
int dfs(int u,int c){if(u==t){return c;}
	if(c<=0||V[u]){return 0;}V[u]=2;int f=0;
	for(int v:A[u])if(d[v]>d[u]){
		int nf=dfs(v,min(c-f,C[u][v]));
		F[u][v]+=nf;F[v][u]-=nf;f+=nf;
	}V[u]=f<c;return f;}
int calc(){while(bfs()>=0){
	V.assign(n,0);a+=dfs(s,2e9);}return a;}};

int main(){
	int numNode, numEdge;
	cin >> numNode >> numEdge;
	fgraph flowgraph(numNode,0,numNode-1);
	for (int i = 0; i < numEdge; i++) {
		int from,to,cap;
		cin >> from >> to >> cap;
		flowgraph.addedge(from,to,cap);
	}
	cout << flowgraph.calc() << endl;
	return 0;
}