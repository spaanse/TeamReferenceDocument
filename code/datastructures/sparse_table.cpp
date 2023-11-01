#pragma once
#include "../setup/header.cpp"
struct sp_table{ vvi t;
sp_table(vi a) { int n=a.size();
	t.assign(log2(n)+2,a);
	for(int i=0,p=1;p<n;i++,p*=2)
		for(int j=0;j+p<n;j++)
			t[i+1][j]=min(t[i][j],t[i][j+p]);}
int query(int l, int r){
	int d=r-l,i=0,p=1; while(d>>=1)i++,p*=2;
	return min(t[i][l],t[i][r-p]);}};

int test_sparse_table() {
	sp_table table({5,3,8,7,5,2,2,1,9,6});
	cout << table.query(0,4) << endl; //3
	cout << table.query(0,10) << endl; //1
	cout << table.query(1,2) << endl; //3
	return 0;
}
