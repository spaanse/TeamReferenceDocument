#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

ll numPush, maxPush=0;
//10N
struct fgraph{
	int numNode,source,sink;
	vi label,excess,index;
	vvi adjList,capacity,flow;
	queue<int>q;
	fgraph(int _numNode,int _source,int _sink) {
		numNode = _numNode;
		source = _source;
		sink = _sink;
		label.assign(numNode,0);
		label[source] = 2*numNode;
		excess.assign(numNode,0);
		excess[source] = 2e9;
		index.assign(numNode,0);
		adjList.resize(numNode);
		capacity.assign(numNode,vi(numNode,0));
		flow.assign(numNode,vi(numNode,0));
	}
	void addedge(int u,int v,int c) {
		capacity[u][v]+=c;
		adjList[u].push_back({v});
		adjList[v].push_back({u});
	}
	void push(int u,int v){
		if (label[u] < (label[v]|1)) return;
		int maxflow = -flow[u][v];
		if (!(label[u]&1)) maxflow += capacity[u][v];
		int newflow = min(excess[u], maxflow);
		if (newflow <= 0) return;
		if(!excess[v] and v!=source and v!=sink) {
			q.push(v);
			numPush++;
		}
		// cerr << "push " << newflow << " units from " << u << " to " << v << endl;
		flow[u][v]+=newflow;
		flow[v][u]-=newflow;
		excess[v]+=newflow;
		excess[u]-=newflow;
	}
	void fix(int u){
		while(excess[u]){
			if(index[u]==(int)adjList[u].size()) {
				label[u]++;
				// cerr << "relabel " << u << " to " << (label[u]>>1) << " phase " << (label[u]&1?"flat":"down") << endl;
				index[u]=0;
			} else {
				push(u,adjList[u][index[u]]);
				index[u]++;
			}
		}
		index[u]--;
	}
	int calc(){
		for(int v:adjList[source]) {
			push(source,v);
		}
		while (!q.empty()) {
			fix(q.front());
			q.pop();
		}
		return excess[sink];
	}
};

int main(){
	int numNode = 1000;
	numNode = (((numNode-1)/2)*2)+1;
	// int numEdge = numNode-1;
	
	fgraph fg(numNode,0,numNode-1);
	int chainLen = numNode/3;

	for (int i = chainLen-1; i >= 0; i--) {
		fg.addedge(chainLen+i,chainLen+i+1,chainLen-i);
	}

	for (int i = chainLen-1; i >= 0; i--) {
		fg.addedge(i,i+1,numNode);
	}

	numPush = 0;
	int flow = fg.calc();
	maxPush = max(maxPush, numPush);
	if (numPush >= maxPush-numNode) {
		cerr << flow << " " << numPush << endl;
	}
	// if (flow == 0) continue;
	// cout << flow << endl;
	
	for(int from=0;from<numNode;from++) {
		for (int v : fg.adjList[from]) {
			assert(fg.capacity[from][v]>=fg.flow[from][v]);
		}
		if (from != 0 && from != numNode-1) {
			assert(fg.excess[from] == 0);
		}
		assert(fg.label[from] < 4*numNode);
	}

	queue<int> q;
	q.push(0);
	vi vis(numNode,false);
	vis[0] = true;
	while (!q.empty()) {
		int from = q.front(); q.pop();
		assert(from != numNode-1);
		for (int v : fg.adjList[from]) {
			if (fg.capacity[from][v]>fg.flow[from][v]
				  &&!vis[v]) {
				q.push(v); vis[v] = true;
			}
		}
	}
	return 0;
}