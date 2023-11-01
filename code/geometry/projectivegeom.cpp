#pragma once
#include "../setup/header.cpp"
#define cm(x,y) x*p.y-y*p.x
#define cp(x,y) x*p.y+y*p.x
template<bool P>
struct ptln{db x=0.0,y=0.0,z=1.0;
typedef ptln<P> pt;typedef ptln<!P> ln;
bool operator==(pt p){
	return fabs(cm(x,z))<EPS &&
	       fabs(cm(y,z))<EPS;}
db dot(ln p){return x*p.x+y*p.y+z*p.z;}
bool on(ln p){return fabs(dot(p))<EPS;}
ln isct(pt p) {
	return{cm(y,z),cm(z,x),cm(x,y)};}
pt operator*(db s){return{x*s,y*s,z*s};}
db mag(){return hypot(x,y);}
db norm(){return mag()/z;}
}; typedef ptln<1> pt;typedef ptln<0> ln;

template<bool P=1>struct tf{
vector<vector<db>> m;
tf(db d=1.){m.assign(3,vector<db>(3,0));
	for(int i=0;i<3;i++)m[i][i]=d;}
tf(initializer_list<db> _m){tf(); int i=0;
	for (db d:_m){m[i/3][i%3]=d;i++;}}
db &operator()(int i,int j){
	return m[i%3][j%3];}
ptln<P> operator*(ptln<P> p){tf<P> c=*this;
	return{c(0,0)*p.x+c(0,1)*p.y+c(0,2)*p.z,
	       c(1,0)*p.x+c(1,1)*p.y+c(1,2)*p.z,
	       c(2,0)*p.x+c(2,1)*p.y+c(2,2)*p.z};}
tf<P> operator*(tf<P> o){tf<P> c=*this,a;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++)
	for(int k=0;k<3;k++)a(i,j)+=c(i,k)*o(k,j);
	return a;}
tf<!P> swap(){ tf<!P> a;tf<P> c=*this;
	for (int i=0;i<3;i++) for(int j=0;j<3;j++)
		a(i,j) =c(i+1,j+2)*c(i+2,j+1)
		         -c(i+1,j+1)*c(i+2,j+2);
	return a;}
}; typedef tf<1> pttf; typedef tf<0> lntf;

pttf mv(pt p){
	return {p.z,0,p.z,p.z,0,p.y,0,0,p.z};}
pttf mid(pt p){ return tf(.5)*mv(p);}
pttf mir(pt p){ return mv(tf(2)*p)*tf(-1);}
pttf rot(db a){db c=cos(a); db s=sin(a);
	return {c,-s,0,s,c,0,0,0,1};}
pttf project(ln l){db a=l.x,b=l.y,c=l.z;
	return {b*b,-a*b,-a*c,-a*b,a*a,-b*c,
		                          0,0,a*a+b*b};}
lntf perp(pt p){
	return {0,-p.z,0,p.z,0,0,-p.y,p.x,0};}
lntf parr(pt p){
	return {p.z,0,0,0,p.z,0,-p.x,-p.y,0};}


// ln bisect(ln l, ln m){
	// return l*m.mag()+m*l.mag();}

int test_proj_geom() {
	ln l {5,3,1};
	pt p {1,0},q{5,3};
	ln m=p.isct(q);
	pt r=l.isct(m);
	cout <<r.x<<" "<<r.y<<" "<< r.z << endl;
	return 0;
}
