#include<iostream>
#include<vector>
#include<utility>
#include<tuple>
#include<algorithm>
using namespace std;

typedef vector<int>vi;
typedef vector<vi>vvi;
typedef pair<int,int>ii;
typedef vector<ii>vii;
typedef int64_t ll;

//d4i
struct mod{ ll m=1000000007,v=0;
mod(){}
mod(ll _v){v=_v%m;if(v<0){v+=m;}}
mod(ll _v,ll _m){m=_m;v=_v%m;if(v<0){v+=m;}}
mod(mod&r){v=r.v;m=r.m;}
mod& operator*=(mod r){
	v*=r.v;v%=m;return*this;}
mod& operator+=(mod r){
	v+=r.v;if(v>=m){v-=m;}return*this;}
mod& operator-=(mod r){
	v-=r.v;if(v<0){v+=m;}return*this;}
mod& operator/=(mod r){
	return*this*=r.pow(m-2);}
mod& operator++(){return*this+=1;}
mod& operator--(){return*this-=1;}
mod operator+(mod r){return mod{*this}+=r;}
mod operator-(mod r){return mod{*this}-=r;}
mod operator*(mod r){return mod{*this}*=r;}
mod operator/(mod r){return mod{*this}/=r;}
bool operator==(mod r){return v==r.v;}
bool operator<(mod r){return v<r.v;}
operator ll(){return v;}
operator bool(){return v?1:0;}
mod pow(ll e){ mod a{1,m},b{*this};
	do{if(e&1){a*=b;}b*=b;}
	while(e>>=1);return a;}};


int main(){
	
	return 0;
}