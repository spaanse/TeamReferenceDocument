#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
#include<map>
using namespace std;

typedef vector<int>vi;
typedef vector<vi>vvi;
typedef pair<int,int>ii;
typedef vector<ii>vii;
typedef int64_t ll;
typedef string st;
//625
struct sufAut{
struct nd{nd*p=0;int ln=0,oc=0,ps=1;
	map<char,nd*>t={};}*l,*r=l=new nd;
nd* find(st s){nd*c=r;for(char x:s)if(c){
		c=c->t[x];}return c;}
bool has(st s){return find(s);}
void add(char x){nd*c=new nd{r,l->ln+1,1};
	for(;l&&!l->t[x];l=l->p){l->t[x]=c;}if(l){
		nd*n=l->t[x];if(l->ln+1!=n->ln){
		nd*d=c->p=n->p=new nd(*n);d->ln=l->ln+1;
		for(;l&&l->t[x]==n;l=l->p)l->t[x]=d;
	}else c->p=n;}l=c;}
void add(st s){for(int x:s)add(x);}
vector<nd*>rto(){vector<nd*>a{r};
	for(nd*c:a)for(auto e:c->t){nd*n=e.second;
		if(n&&n->ln==c->ln+1)a.push_back(n);}
	reverse(a.begin(),a.end());return a;}
int nsub(){int a=0;for(nd*c:rto()){
	for(auto e:c->t){nd*n=e.second;if(n)
		c->ps+=n->ps;}a+=c->ps;}return a;}
st lexk(int k){st a;nd*c=r;int kp;while(k--)
	for(auto e:c->t){nd*n=e.second;if(n){
		kp=k;k-=n->ps;if(k<0){c=n;k=kp;
		a.push_back(e.first);break;}}}return a;}
void po(){for(nd*c:rto())
	if(c->p)c->p->oc+=c->oc;}
int fo(st s){return find(s)->ln-s.size();}
int no(st s){return find(s)->oc;}};

// #define pb push_back
// vi fstr(st s){int n=s.size(),i=0;vi a(n);
// 	for(;i<n;i++){a[i]=s[i]-'a';}return a;}
// st tstr(vi s){int n=s.size(),i=0;st a;
// 	for(;i<n;i++){a+=s[i]+'a';}return a;}
// struct sufAut{int nv=26,l=0,n=1;vi ps,ln{0},
// lk{-1},og{0},f{0},cnt;vvi t{vi(nv,-1)};
// int find(vi s){int c=0,i=0;while(c!=-1){
// 		c=t[c][s[i++]];}return(i==n?c:-1);}
// bool has(vi s){return find(s)>=0;}
// vi rtopo(){vi a;for(int i=0;i<n;i++)a[i]=i;
// 	sort(a.begin(),a.end(),[&](int x,int y)
// 		{return ln[x]>ln[y];});return a;}
// void add(int v){int c=n++,p;t.pb(vi(nv,-1));
// 	lk.pb(0);og.pb(1);f.pb(c);ln.pb(ln[l]+1);
// 	for(;l>=0&&t[l][v]<0;l=lk[l])t[l][v]=c;
// 	if(l>=0){if(ln[l]+1!=ln[p=t[l][v]]){
// 		ln.pb(ln[l]+1);og.pb(0);lk.pb(lk[p]);
// 		t.pb(t[p]);f.pb(f[p]);lk[c]=lk[p]=n++;
// 		for(;l>=0&&t[l][v]==p;l=lk[l]){
// 			t[l][v]=n-1;}}else lk[c]=p;}l=c;}
// void add(vi vs){for(int v:vs)add(v);}
// int count(){ps.assign(n,1);int a=0,j;
// 	for(int i:rtopo()){for(j=0;j<nv;j++){
// 		if(t[i][j]>=0)ps[i]+=ps[t[i][j]];}
// 		a+=ps[i];}return a;}
// vi lexk(int k){vi a;int c=0,j,kp;
// 	while(k--)for(j=0;j<nv;j++)if(t[c][j]){
// 		kp=k;k-=ps[t[c][j]];if(k<0){c=t[c][j];
// 			a.push_back(j);k=kp;break;}}return a;}
// void po(){cnt=og;for(int i:rtopo())
// 		if(lk[i]>=0)cnt[lk[i]]+=cnt[i];}
// int no(vi s){return cnt[find(s)];}
// int fo(vi s){return f[find(s)]-s.size();}};

int main(){
	
	return 0;
}