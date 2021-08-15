#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
using namespace std;
typedef vector<int>vi;
//355
struct uf{vi p;uf(int n):p(n,-1){}
int fd(int n){return p[n]<0?n:p[n]=fd(p[n]);
}int sz(int n){return-p[fd(n)];}
bool same(int x,int y){return fd(x)==fd(y);}
void join(int x,int y){x=fd(x);y=fd(y);
	if(x==y)return;if(p[x]>p[y])swap(x,y);
	p[x]+=p[y];p[y]=x;}};

int main(){

	return 0;
}
