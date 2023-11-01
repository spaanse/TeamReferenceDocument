#pragma once
#include "../setup/header.cpp"
struct segTree{
struct seg{int v=0,lz=0;int l=0,r=0;};
vector<seg>s;
seg join(seg a,seg b){
	return{a.v+b.v,0,a.l,b.r};}
void ps(int i){seg&c=s[i];
	if(c.l+1<c.r){s[2*i].lz+=c.lz;
		s[2*i+1].lz+=c.lz;}
	c.v+=(c.r-c.l)*c.lz;c.lz=0;}
segTree(vi arr){int n=arr.size();
	s.resize(4*n);make(arr,1,0,n);}
seg make(vi&arr,int i,int l,int r){
	if(l+1==r){return s[i]={arr[l],0,l,r};}
	seg lft=make(arr,2*i,l,(l+r)/2);
	seg rgt=make(arr,2*i+1,(l+r)/2,r);
	return s[i]=join(lft,rgt);}
void upd(int t,int v,int i=1){ps(i);
	if(s[i].l+1==s[i].r)s[i].v=v;
	else{upd(t,v,2*i);upd(t,v,2*i+1);
		s[i]=join(s[2*i],s[2*i+1]);}}
void rup(int l,int r,int d,int i=1){
	ps(i);if(r<=s[i].l||l>=s[i].r)return;
	if(l<=s[i].l&&r>=s[i].r)s[i].lz=d;
	else{rup(l,r,d,2*i);rup(l,r,d,2*i+1);}}
seg qry(int l,int r,int i=1){ps(i);
	if(r<=s[i].l||l>=s[i].r)return{};
	if(l<=s[i].l&&r>=s[i].r)return s[i];
	return join(qry(l,r,2*i),
		qry(l,r,2*i+1));}};
