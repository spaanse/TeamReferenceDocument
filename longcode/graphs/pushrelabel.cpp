#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

//10N
struct flowgraph{
	int numNode,source,sink;
	vi label,excess,index;
	vvi adjList,capacity,flow;
	queue<int> todo;
	flowgraph(int _numNode,int _source,int _sink) {
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
	void addedge(int from,int to,int cap) {
		capacity[from][to]+=cap;
		adjList[from].push_back(to);
		adjList[to].push_back(from);
	}
	void push(int from,int to){
		if(label[to]>=label[from]) return;
		int newflow=min(excess[from],
		                capacity[from][to]-flow[from][to]);
		if(!excess[to] and to!=source and to!=sink and newflow>0) {
			todo.push(to);
		}
		flow[from][to]+=newflow;
		flow[to][from]-=newflow;
		excess[to]+=newflow;
		excess[from]-=newflow;
	}
	void fix(int node){
		while(excess[node]){
			if(index[node]==(int)adjList[node].size()) {
				label[node]++;
				index[node]=0;
			} else {
				push(node,adjList[node][index[node]]);
				if (excess[node]) index[node]++;
			}
		}
	}
	int calculate(){
		for(int to:adjList[source]) {
			push(source,to);
		}
		while (!todo.empty()) {
			fix(todo.front());
			todo.pop();
		}
		return excess[sink];
	}
};

int main(){
	int seed = 0;
	int numNode = 1000;
	int numEdge = 2000;
	while (true) {
		cout << seed << " ";
		srand(seed);
		vii edges;
		for (int i = 0; i < numNode-1; i++) {
			for (int j = 1; j < numNode; j++) if (i!=j){
				edges.push_back({i,j});
			}
		}
		random_shuffle(edges.begin(), edges.end());
		flowgraph fg(numNode,0,numNode-1);
		for (int i = 0; i < numEdge; i++) {
			fg.addedge(edges[i].first,edges[i].second,rand()%100);
		}
		int flow = fg.calculate();
		cout << flow << endl;
		
		for(int from=0;from<numNode;from++) {
			for (int to : fg.adjList[from]) {
				assert(fg.capacity[from][to]>=fg.flow[from][to]);
			}
			if (from != 0 && from != numNode-1) {
				assert(fg.excess[from] == 0);
			}
			assert(fg.label[from] < 2*numNode);
		}

		queue<int> todo;
		todo.push(0);
		vi vis(numNode,false);
		vis[0] = true;
		while (!todo.empty()) {
			int from = todo.front(); todo.pop();
			assert(from != numNode-1);
			for (int to : fg.adjList[from]) {
				if (fg.capacity[from][to]>fg.flow[from][to]
					  &&!vis[to]) {
					todo.push(to); vis[to] = true;
				}
			}
		}
		seed++;
	}
	return 0;
}
