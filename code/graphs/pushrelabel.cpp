#pragma once
#include "../setup/header.cpp"
struct flow{int n,s,t;vi l,x,i;vvi C,F;qi q;
flow(int N):l(N),x(N),i(N),C(N,l),F(C){
	n=N;s=0;t=N-1;l[s]=N;x[s]=2e9;}
void add(int u,int v,int c){C[u][v]+=c;}
void ps(int u,int v){int f;if(l[v]<=l[u]){
	f=min(x[u],F[v][u]+(l[v]<l[u]?C[u][v]:0));
	if(0<f){if(!x[v]&&v!=s&&v!=t)q.push(v);
	F[u][v]+=f;F[v][u]-=f;x[v]+=f;x[u]-=f;}}}
void dc(int u){while(x[u]){if(i[u]<n)
	ps(u,i[u]++);else{l[u]++;i[u]=0;}}i[u]--;}
void calc(){for(int v=0;v<n;v++) ps(s,v);
	for(;q.size();q.pop()) dc(q.front());}};

int test_pr(){
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
