#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
//02k
#define pb push_back
vi reverse(vi in){int n=in.size();vi ans(n);
	for(int i=0;i<n;i++) ans[n-i-1]=in[i];
	return ans;}
vi fromStr(string in){
	int n=in.size(); vi ans(n);
	for (int i=0;i<n;i++) ans[i]=in[i]-'a';
	return ans;}
string toStr(vi in){
	int n=in.size(); string ans;
	for (int i=0;i<n;i++) ans[i]+=in[i]+'a';
	return ans;}
struct sufAut{ int nv=26, l=0, n=1;
vi ln{0},lk{-1},og{0},fo{0},pStart,cnt;
vvi t{vi(nv,-1)};
int find(vi s) { int c=0, i=0;
	while (c!=-1) c=t[c][s[i++]];
	return (i==n?c:-1);}
bool has(vi s) {return find(s)!=-1;}
vi topo() {vi ans;
	for(int i=0;i<n;i++)ans[i]=i;
	sort(ans.begin(),ans.end(),
		[this](int a,int b) -> bool {
		return ln[a] < ln[b];}); return ans;}
void add(int v){
	int c=n++,p; og.pb(1); fo.pb(c);
	ln.pb(ln[l]+1);t.pb(vi(nv,-1));lk.pb(0);
	for(;l!=-1&&t[l][v]==-1;l=lk[l])t[l][v]=c;
	if (l != -1) { p = t[l][v];
		if (ln[l]+1 == ln[p]) lk[c]=p;
		else { ln.pb(ln[l]+1); t.pb(t[p]);
			lk.pb(lk[p]); og.pb(0);fo.pb(fo[p]);
			lk[c] = lk[p] = n++;
			for(;l!=-1&&t[l][v]==p;l=lk[l])
				t[l][v] = n-1;}} l=c;}
void add(vi vs){for (int v:vs) add(v);}
int count(){pStart.assign(n,1); int ans=0,j;
	for (int i:reverse(topo())) {
		for (j=0;j<nv;j++) if(t[i][j]!=-1)
			pStart[i]+=pStart[t[i][j]];
		ans += pStart[i];} return ans;}
vi lexicok(int k) { vi ans; int c=0;
	while (k--){
		for (int j=0;j<nv;j++) if (t[c][j]){
			if (k < pStart[t[c][j]]){ 
				c=t[c][j]; ans.pb(j); break;}
			k -= pStart[t[c][j]]; }}return ans;}
void precomputeOcc() { cnt = og;
	for(int i:reverse(topo()))if (lk[i]!=-1)
		cnt[lk[i]] += cnt[i];}
int numOcc(vi s){return cnt[find(s)];}
int firstOcc(vi s){
	return fo[find(s)]-s.size();}};

int main() {
	
	return 0;
}