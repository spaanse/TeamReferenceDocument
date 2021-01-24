#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

//10N
struct fgraph{int n;vi l,x,i;vvi A,C,F;
queue<int>q; fgraph(int _n):l(_n),x(l),i(l),
A(_n),C(_n,l),F(C){	n=_n;l[0]=2*n;x[0]=2e9;}
void addedge(int u,int v,int c){C[u][v]+=c;
	A[u].push_back({v});A[v].push_back({u});}
void ps(int u,int v){int f=x[u];
	f=min(f,(l[u]&1?0:C[u][v])-F[u][v]);
	if(l[u]<(l[v]|1)||f<=0)return;
	if(!x[v]&&v!=0&&v!=n-1)q.push(v);
	F[u][v]+=f;F[v][u]-=f;x[v]+=f;x[u]-=f;}
void fix(int u){while(x[u]){
	if(i[u]==(int)A[u].size()){l[u]++;i[u]=0;}
	else ps(u,A[u][i[u]++]);} i[u]--;}
int calc(){for(int v:A[0]) ps(0,v);
	for(;q.size();q.pop())fix(q.front());
	return x[n-1];}};

int main(){
	int numNode, numEdge;
	cin >> numNode >> numEdge;
	fgraph fg(numNode);
	for (int i = 0; i < numEdge; i++) {
		int fr,to,cap;
		cin >> fr >> to >> cap;
		fg.addedge(fr,to,cap);
	}
	cout << fg.calc() << endl;

	for(int fr=0;fr<numNode;fr++) {
		for (int to : fg.A[fr]) {
			assert(fg.C[fr][to]>=fg.F[fr][to]);
		}
		if (fr != 0 && fr != numNode-1) {
			assert(fg.x[fr] == 0);
		}
		assert(fg.l[fr] < 2*numNode);
	}

	queue<int> q;
	q.push(0);
	vi vis(numNode,false);
	vis[0] = true;
	while (!q.empty()) {
		int fr = q.front(); q.pop();
		assert(fr != numNode-1);
		for (int to : fg.A[fr]) {
			if (fg.C[fr][to]>fg.F[fr][to]
				  &&!vis[to]) {
				q.push(to); vis[to] = true;
			}
		}
	}
	return 0;
}