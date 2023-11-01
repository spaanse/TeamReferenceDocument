#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

struct fenwickTree{
	int size;
	vi array;
	fenwickTree(int newSize) {
		size = newSize;
		array.assign(newSize,0);
	}
	void add(int i, int d) {
		i++;
		while (i <= size) {
			array[i] += d;
			// 
			i += (i & -i);
		}
	}
	int query(int i) { 
		int result = 0;
		i++;
		while (i > 0) {
			result += array[i];
			// unset the least significant bit
			i -= (i & -i);
		}
		return result;
	}
	int query(int l, int r) {
		return query(r)-query(l);
	} 
};
//range updates+queries
struct FTRangeUpdate { fenwickTree x0, x1;
	FTRangeUpdate(int _n):x0(_n),x1(_n){}
	void add(int i, int d){x1.add(i,d);}
	void add(int l, int r, int d){
		x0.add(l,d); x0.add(r,-d);
		x1.add(l,-d*(l-1)); x1.add(r,d*(r-1));}
	int query(int i) {
		return i*x0.query(i) + x1.query(i);}
	int query(int l, int r){
		return query(r)-query(l);}};


int main() {
	
	return 0;
}
