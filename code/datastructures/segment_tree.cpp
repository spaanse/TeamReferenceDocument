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
struct segTree{
	struct seg{int v=0, lz=0; int l=0, r=0;};
	vector<seg> s;
	// determine the combine function (sum) here
	seg join(seg a, seg b) {
		return {a.v+b.v,0,a.l,b.r};}
	void propagate(int i) {seg &c = s[i];
		if (c.l+1<c.r){ s[2*i  ].lz += c.lz;
			              s[2*i+1].lz += c.lz;}
		c.v += (c.r - c.l) * c.lz; c.lz = 0;}
	// make a segment tree from an array
	segTree(vi arr) { int n = arr.size(); 
		s.resize(4*n);make(arr,1,0,n);}
	seg make(vi&arr,int i,int l,int r) {
		if (l+1==r){
			return s[i] = {arr[l], 0, l, r};}
		seg lft = make(arr,2*i  , l, (l+r)/2);
		seg rgt = make(arr,2*i+1, (l+r)/2, r);
		return s[i] = join(lft,rgt);}
	// update arr[t] = v
	void update(int t, int v, int i=1) {
		propagate(i);
		if (s[i].l+1 == s[i].r) s[i].v = v;
		else {update(t,v,2*i);update(t,v,2*i+1);
			s[i]=join(s[2*i],s[2*i+1]);}}
	// update arr[t] += d for all t in [l,r)
	void rangeUpd(int l,int r,int d,int i=1) {
		propagate(i);
		if (r<=s[i].l || l>=s[i].r) return;
		if (l<=s[i].l && r>=s[i].r) s[i].lz = d;
		else {rangeUpd(l,r,d,2*i);
			    rangeUpd(l,r,d,2*i+1);}}
	// query the value of range [l,r)
	seg query(int l, int r, int i=1){
		propagate(i);
		if (r<=s[i].l || l>=s[i].r) return {};
		if (l<=s[i].l && r>=s[i].r) return s[i];
		return join(query(l,r,2*i),
			          query(l,r,2*i+1));} };

int main() {
	
	return 0;
}