#pragma once
#include "../setup/header.cpp"
struct mod{ ll m,v; mod(mod&r)=default;
mod(ll w=0,ll n=1e9+7){m=n;v=w%m;v+=v<0?m:0;}
mod& operator*=(mod r){v*=r.v%m;return*this;}
mod& operator+=(mod r){
	v+=r.v;v-=v>=m?m:0;return*this;}
mod& operator-=(mod r){
	v-=r.v;v+=v<0?m:0;return*this;}
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
operator bool(){return v;}
mod pow(ll e){ mod a{1,m},b{*this};
	do{if(e&1){a*=b;}b*=b;}
	while(e>>=1);return a;}};
