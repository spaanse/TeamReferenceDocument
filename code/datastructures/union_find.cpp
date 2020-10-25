#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
//355
struct uf { vi p; uf(int n) : p(n,-1) {}
	int find(int n){
		return p[n]<0 ? n : p[n] = find(p[n]);}
	int size(int n) {return -p[find(n)];}
	bool same(int x, int y) {
		return find(x)==find(y);}
	void join(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (p[x] > p[y]) swap(x,y);
		p[x] += p[y]; p[y] = x; } };

int main() {

	return 0;
}