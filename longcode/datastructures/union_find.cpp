#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;
typedef vector<int> vi;

struct UnionFind {
	// parent[i] < 0 if i is the root of it's component
	//  then -parent[i] is the size of the component
	// otherwise parent[i] is the index of the current parent of i
	vi parent;
	UnionFind(int size) {
		// all components are their own root and have size 1
		parent.assign(size, -1);
	}
	// find the root of the component containing cur
	int find(int cur){
		if (parent[cur] < 0) {
			// is the root of it's component
			return cur;
		} else {
			// update the parent pointer and return the component root
			parent[cur] = find(parent[cur]);
			return parent[cur];
		}
	}
	// find the size of the component containing cur
	int size(int cur) {
		return -parent[find(cur)];
	}
	// determine if two indices belong to the same component
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	// combine the components containing x and y into one
	void join(int x, int y) {
		// find the respective roots
		x = find(x);
		y = find(y);
		if (x == y) {
			return; // already in the same component
		}
		// make the larger component the parent of the smaller
		// therefore swap x,y if needed so x is the largest component of the two
		if (parent[x] > parent[y]) swap(x,y);
		// update the size of component x
		parent[x] += parent[y];
		// and set y's parent to x
		parent[y] = x;
	} 
};

int main() {

	return 0;
}