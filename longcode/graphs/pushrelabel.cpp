#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

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
		label[source] = numNode;
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
		if(label[v]>=label[u]) return;
		int newflow=min(excess[u],
		                capacity[u][v]-flow[u][v]);
		if(!excess[v] and v!=source and v!=sink and newflow>0) {
			q.push(v);
		}
		flow[u][v]+=newflow;
		flow[v][u]-=newflow;
		excess[v]+=newflow;
		excess[u]-=newflow;
	}
	void fix(int u){
		while(excess[u]){
			if(index[u]==(int)adjList[u].size()) {
				label[u]++;
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
	srand(0);
	// int numNode, numEdge;
	// cin >> numNode >> numEdge;
	// fgraph fg(numNode,0,numNode-1);
	// for (int index = 0; index < numEdge; index++) {
	// 	int from,v,cap;
	// 	cin >> from >> v >> cap;
	// 	fg.addedge(from,v,cap);
	// }
	while (true) {
		int numNode = 1000;
		vii edges;
		for (int i = 0; i < numNode-1; i++) {
			for (int j = 1; j < numNode; j++) if (i!=j){
				edges.push_back({i,j});
			}
		}
		random_shuffle(edges.begin(), edges.end());
		int numEdge = 2000;
		fgraph fg(numNode,0,numNode-1);
		for (int i = 0; i < numEdge; i++) {
			fg.addedge(edges[i].first,edges[i].second,rand()%100);
		}
		// fg.addedge(0,1,numNode);
		// for (int i = 2; i < numNode-1; i++) {
		// 	fg.addedge(1,i,1);
		// }
		// for (int i = 2; i < numNode-2; i++) {
		// 	fg.addedge(i,i+1,numNode);
		// }
		// fg.addedge(numNode-2,numNode-1,numNode);
		int flow = fg.calc();
		if (flow == 0) continue;
		cout << fg.calc() << endl;
		
		for(int from=0;from<numNode;from++) {
			for (int v : fg.adjList[from]) {
				assert(fg.capacity[from][v]>=fg.flow[from][v]);
			}
			if (from != 0 && from != numNode-1) {
				assert(fg.excess[from] == 0);
			}
			assert(fg.label[from] < 2*numNode);
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
	}
	return 0;
}