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
//43c
struct ft{ int n; vi a;
	ft(int _n) : n(_n),a(vi(n,0)){}
	void add(int i, int d) {
		for(i++;i<=n;i+=i&-i) a[i] += d;}
	int qry(int i){ int r;
		for(i++;i>0;i-=i&-i){r+=a[i];}return r;}
	int qry(int l, int r){
		return qry(r)-qry(l);} };
//range updates+queries
struct ft_ru { ft x0, x1;
	ft_ru(int _n):x0(_n),x1(_n){}
	void add(int i, int d){x1.add(i,d);}
	void add(int l, int r, int d){
		x0.add(l,d); x0.add(r,-d);
		x1.add(l,-d*(l-1)); x1.add(r,d*(r-1));}
	int qry(int i) {
		return i*x0.qry(i) + x1.qry(i);}
	int qry(int l, int r){
		return qry(r)-qry(l);}};


int main() {
	
	return 0;
}
