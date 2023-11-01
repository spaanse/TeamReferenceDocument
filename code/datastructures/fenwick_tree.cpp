#pragma once
#include "../setup/header.cpp"
struct ft{int n;vi a;
	ft(int _n):n(_n),a(vi(n,0)){}
	void add(int i,int d){
		for(i++;i<=n;i+=i&-i)a[i]+=d;}
	int qr(int i){int r;
		for(i++;i>0;i-=i&-i){r+=a[i];}return r;}
	int qr(int l,int r){return qr(r)-qr(l);}};
struct ft_ru{ft x0,x1;
	ft_ru(int _n):x0(_n),x1(_n){}
	void add(int i,int d){x1.add(i,d);}
	void add(int l,int r,int d){
		x0.add(l,d);x0.add(r,-d);
		x1.add(l,-d*(l-1));x1.add(r,d*(r-1));}
	int qr(int i){return i*x0.qr(i)+x1.qr(i);}
	int qr(int l,int r){return qr(r)-qr(l);}};
