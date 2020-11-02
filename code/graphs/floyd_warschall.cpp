#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
using namespace std;

bool ckmax(int&a,int b){return b>a?a=b,1:0;}
bool ckmin(int&a,int b){return b<a?a=b,1:0;}

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
//360
//bool ckmin(int&a,int b){return b<a?a=b,1:0;}
void fw(vvi& mat) {int n=mat.size();
	for(int j=0;j<n;j++) for(int i=0;i<n;i++)
	for(int k=0;k<n;k++)
		ckmin(mat[i][k],mat[i][j]+mat[j][k]);}

int main() {
	
	return 0;
}