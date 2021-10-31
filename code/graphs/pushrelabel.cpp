#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
typedef queue<int> qi;

//faL
struct flow{int s,t;vi l,x,i;vvi A,C,F;qi q;
flow(int n):l(n),x(n),i(n),A(n),C(n,l),F(C){
	s=0;t=n-1;l[s]=n;x[s]=2e9;}
void add(int u,int v,int c){C[u][v]+=c;
	A[u].push_back(v);A[v].push_back(u);}
void ps(int u,int v){if(l[v]>=l[u]) return;
	int f=min(x[u],C[u][v]-F[u][v]);
	if(!x[v]&&v!=s&&v!=t&&0<f)q.push(v);
	F[u][v]+=f;F[v][u]-=f;x[v]+=f;x[u]-=f;}
void fix(int u){while(x[u]){
	if(i[u]==(int)A[u].size()){l[u]++;i[u]=0;}
	else ps(u,A[u][i[u]++]);} i[u]--;}
int calc(){for(int v:A[s]) ps(s,v);
	for(;q.size();q.pop())fix(q.front());
	return x[t];}};

int main(){
	int numNode, numEdge;
	cin >> numNode >> numEdge;
	flow fg(numNode);
	for (int i = 0; i < numEdge; i++) {
		int fr,to,cap;
		cin >> fr >> to >> cap;
		fg.add(fr,to,cap);
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
