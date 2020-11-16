#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <iomanip>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

//70b
struct mat { typedef double T;
typedef vector<T>vT; typedef vector<vT>vvT;
vvT m; int R,C;
T& operator()(int r, int c){return m[r][c];}
mat(vvT o){m=o; R=m.size(); C=m[0].size();}
mat(int r,int c,T d=1):m(r,vT(c,0)){R=r;C=c;
	for (int i=0;i<min(r,c);i++)m[i][i]=d;}
mat& operator+=(mat&o) {
	for(int r=0;r<R;r++) for(int c=0;c<C;c++)
		{m[r][c] += o(r,c);} return *this;}
mat& operator-=(mat&o){
	for(int r=0;r<R;r++) for(int c=0;c<C;c++)
		{m[r][c] -= o(r,c);} return *this;}
mat& operator*=(T k) {
	for(int r=0;r<R;r++) for(int c=0;c<C;c++)
		{m[r][c] *= k;} return *this;}
mat operator*(mat&o){mat a(R,o.C,0);
	for(int i=0,j,k;i<R;i++)for(j=0;j<o.C;j++)
	for(k=0;k<C;k++)a(i,j)+=m[i][k]*o(k,j);
	return a;}
mat& operator*=(mat&o){
	m=operator*(o).m;return *this;}
mat ldu(vi&p,int&d) {mat a=*this; int k,i,j;
	for(k=0;k<min(R,C);k++){ d*=a(k,k);i=k;
		while(i<R && fabs(a(i,k))<1e-9) i++;
		assert(i!=R); if(i!=k){ d*=-1;
			swap(a.m[i],a.m[j]);swap(p[i],p[j]);}
		for(i=k+1;i<R;i++) a(i,k)/=a(k,k);
		for(j=k+1;j<C;j++) a(k,j)/=a(k,k);
		for(i=k+1;i<R;i++) for(j=k+1;j<C;j++)
			a(i,j)-=a(i,k)*a(k,j)*a(k,k);}
	return a;}
T det(){vi p(R);int d=1;ldu(p,d);return d;}
mat operator/(mat o){ //o*a=m
	int i,j,k;vi p(R); for(i=0;i<R;i++)p[i]=i;
	mat c=o.ldu(p,i),a(R,C);
	for(i=0;i<R;i++) a.m[i]=m[p[i]];
	for(j=0;j<C;j++){
		for(i=0;i<R;i++) for(k=0;k<i;k++)
			a(i,j)-=c(i,k)*a(k,j);
		for(i=0;i<R;i++) a(i,j)/=c(i,i);
		for(i=R-1;i>=0;i--) for(k=R-1;k>i;k--)
			a(i,j)-=c(i,k)*a(k,j);} return a;}
mat inv(){mat i(R,C);return i/(*this);}
mat transpose(){mat a(C,R); int i,j;
	for(i=0;i<R;i++)for(j=0;j<C;j++){
		a(j,i)=m[i][j];} return a;}};
mat operator+(mat l,mat&r){return l+=r;}
mat operator-(mat l,mat&r){return l-=r;}
mat operator*(mat l,double k){return l*=k;}

void print(mat t) {
	for (int i = 0; i < t.R; i++) {
		for (int j = 0; j < t.C; j++) {
			cout << t(i,j) << " ";
		} cout << fixed << setw(5) << endl;
	} cout << fixed << setw(5) << endl;
}

int main() {
	mat A(3,3);
	A(0,0) =  4; A(0,1) = -3; A(0,2) =  5;
	A(1,0) =  1; A(1,1) =  0; A(1,2) =  3;
	A(2,0) = -1; A(2,1) =  5; A(2,2) =  2;
	print(A.inv());
	mat B(3,1);
	B(0,0) =  3;// B(0,1) =  7; B(0,2) = -1;
	B(1,0) =  2;// B(1,1) = -2; B(1,2) =  5;
	B(2,0) = -7;// B(2,1) =  9; B(2,2) =  8;
	B = B/A;
	print(B);
	B = A*B;
	print(B);
	return 0;
}