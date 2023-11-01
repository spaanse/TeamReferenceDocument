#pragma once
#include <bits/stdc++.h>
using namespace std;
const double EPS=1e-9; const int INF=2e9;
#define TDEF(n0,n1,n2)\
typedef vector<n0> n1;typedef vector<n1> n2;
TDEF(int,vi,vvi);
typedef int64_t ll; TDEF(ll,vl,vvl);
typedef pair<int,int> ii; TDEF(ii,vii,vvii);
typedef double db; TDEF(db,vd,vvd);
typedef complex<double>cpx;TDEF(cpx,vc,vvc);
typedef queue<int> qi; typedef string st;
bool ckmin(int&a,int b){return b<a?a=b,1:0;}
bool ckmax(int&a,int b){return b>a?a=b,1:0;}
#define rep(i,m) for(int i=0;i<m;i++)
int main(){iostream::sync_with_stdio(false);
	cin.tie(0); return 0; }
