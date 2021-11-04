#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
typedef queue<int> qi;

//faL
struct flow{int n,s,t;vi l,x,i;vvi C,F;qi q;
flow(int N):l(N),x(N),i(N),C(N,l),F(C){
	n=N;s=0;t=N-1;l[s]=N;x[s]=2e9;}
void ps(int u,int v){if(l[v]>=l[u]) return;
	int f=min(x[u],C[u][v]-F[u][v]);
	if(!x[v]&&v!=s&&v!=t&&0<f)q.push(v);
	F[u][v]+=f;F[v][u]-=f;x[v]+=f;x[u]-=f;}
void fix(int u){while(x[u]){if(i[u]<n)
	ps(u,i[u]++);else{l[u]++;i[u]=0;}}i[u]--;}
void calc(){for(int v=0;v<n;v++) ps(s,v);
	for(;q.size();q.pop())fix(q.front());}};

int main(){
	int numNode, numEdge;
	cin >> numNode >> numEdge;
	flow fg(numNode);
	for (int i = 0; i < numEdge; i++) {
		int fr,to,cap;
		cin >> fr >> to >> cap;
		fg.C[fr][to] += cap;
	}
	fg.calc();
	cout << fg.x[numNode-1] << endl;

	for(int fr=0;fr<numNode;fr++) {
		for (int to=0; to < numNode; to++) {
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
		for (int to; to < numNode; to++) {
			if (fg.C[fr][to]>fg.F[fr][to]
				  &&!vis[to]) {
				q.push(to); vis[to] = true;
			}
		}
	}
	return 0;
}
