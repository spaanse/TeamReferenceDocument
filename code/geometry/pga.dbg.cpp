2b| #include <bits/stdc++.h>
ca| using namespace std;
d4| 
99| typedef vector<int> vi;
dd| typedef vector<vi> vvi;
b0| typedef int64_t ll;
19| typedef vector<ll> vl;
6f| typedef vector<vl> vvl;
92| typedef pair<int,int> ii;
c2| typedef vector<ii> vii;
fd| typedef vector<vii> vvii;
c2| typedef queue<int> qi;
43| typedef double db;
3e| typedef vector<db> vd;
98| typedef vector<db> vvd;
d4| 
0f| template<int p,int q,int r> struct mv{
42| static const int d=p+q+r, e=1<<d;
04| vd c = vd(e); uint i=0,j=0;
cf| db f(uint x, uint y){x&=e-1;uint z=(x&y)>>p;
18| if(z>>q){return 0;}db a=popcount(z)&1?-1:1;
86| while(x>>=1)if(popcount(x&y)&1)a*=-1;
52| return a;}
6a| mv operator~(){mv a(c);for(i=0;i<e;i++){
d3| if(popcount(i)&2)a.c[i]*=-1;}return a;}
f7| //right dual: x !x = I; left dual: !!!x x = I
fe| mv operator!(){mv a;for(i=0;i<e;i++)
b7| { a.c[e-1-i]=c[i]*f(i,~i); } return a;}
17| mv prod(mv&w, auto b){mv a;i=0;
d4| for(;i<e;i++)for(j=0;j<e;j++)if(!b(i,j)){
d4| a.c[i^j]+=f(i,j)*c[i]*w.c[j];}return a;}
28| mv operator*(mv w){return prod(w,
ab| [](int i,int j){return 0;});}
6e| mv operator|(mv w){return prod(w,
03| [](int i,int j){return i&j;});}
b0| mv operator&(mv w){return!!!((!*this)|!w);}
1f| mv operator/(mv w){return prod(w,
65| [](int i,int j){return i&~j&&~i&j;});}
bd| // };
30| void print() {
ce| bool first = true;
f5| for (int i = 0; i < e; i++) {
d5| if (c[i] == 0) continue;
46| if (!first) cout << " + ";
04| if (c[i] == -1) cout << "-";
d0| if (0 < c[i]) cout << "+";
ab| if (c[i] != 1 and c[i] != -1) cout << c[i];
93| // cout << "e";
de| // for (int k = 0; k < d; k++) {
53| // 	if (i & (1<<k)) cout << k;
21| // 	else cout << "_";
52| // }
cc| first = false;
cb| }
48| if (first) cout << "0";
cb| }
d4| 
e5| // a|-b = !(!a /\ !!b)
d4| 
d4| 
6f| // projection: (A . B) B
da| // Transformation: ~R A R
21| };
d4| 
e8| int main() {
d3| for (int i = 0; i < 1<<4; i++) {
1c| mv<3,1,0> v;
58| v.c[i] = 1.0;
b0| v.print();
89| cout << " ";
f4| (v * !v).print();
89| cout << " ";
7a| (!!!v * v).print();
89| cout << " ";
c0| (!!!!v).print();
1f| cout << endl;
d4| 
cb| }
d3| for (int i = 0; i < 1<<4; i++) {
dd| for (int j = 0; j < 1<<4; j++) {
23| mv<3,0,1> v, w;
58| v.c[i] = 1.0;
c9| w.c[j] = 1.0;
9f| (v&w).print();
89| cout << " ";
cb| }
1f| cout << endl;
cb| }
bb| return 0;
cb| }
