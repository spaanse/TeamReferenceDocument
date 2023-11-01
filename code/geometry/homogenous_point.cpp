#pragma once
#include "../setup/header.cpp"
#define cm(x,y) x*p.y-y*p.x
#define cp(x,y) x*p.y+y*p.x
struct A;struct B;template<class A,class B>
struct ptln{db x=0.0,y=0.0,z=1.0;
typedef ptln<A,B> pt;typedef ptln<B,A> ln;
bool operator==(pt p){
	return fabs(cm(x,z))<EPS &&
	       fabs(cm(y,z))<EPS;}
db dot(ln p){return x*p.x+y*p.y+z*p.z;}
bool on(ln p){return fabs(dot(p))<EPS;}
ln isct(pt p) {
	return{cm(y,z),cm(z,x),cm(x,y)};}
pt operator+(pt p){
	return {x+p.x,y+p.y,z+p.z};}
pt operator-(pt p){return *this+p*-1;}
pt operator*(db s){return {x*s,y*s,z*s};}
pt operator/(db s){return *this*(1./s);}
db mag(){return hypot(x,y);}
db norm(){return mag()/z;}
};typedef ptln<A,B> pt;typedef ptln<B,A> ln;

pt mid(pt p,pt q){return p*q.z+q*p.z;}
ln bisect(ln l, ln m){
	return l*m.mag()+m*l.mag();}
ln perp(pt p,ln l){
	return p.isct({l.x,l.y,0});}
pt project(pt p,ln l){
	return l.isct(perp(p,l));}


// struct pt : bs {void fix(){x/=z;y/=z;z=1.;}
// pt(bs b){x=b.x;y=b.y;z=b.z;}
// pt(db a,db b){x=a;y=b;z=1.;}
// pt(db a,db b,db c){x=a;y=b;z=c;}
// pt& operator+=(pt p) {fix();p.fix();
// 	x+=p.x; y+=p.y; return *this;}
// pt& operator-=(pt p) {fix();p.fix();
// 	x-=p.x; y-=p.y; return *this;}
// pt& operator*=(db s){x*=s;y*=s;return*this;}
// pt& operator/=(db s){x/=s;y/=s;return*this;}
// pt operator+(pt r){pt a=*this; return a+=r;}
// pt operator-(pt r){pt a=*this; return a-=r;}
// pt operator*(db s){pt a=*this; return a*=s;}
// pt operator/(db s){pt a=*this; return a/=s;}
// };//
// struct line : bs {
// line(bs b){x=b.x;y=b.y;z=b.z;}
// line(db a,db b,db c){x=a;y=b;z=c;}
// };//

int test_hom_point() {
	ln l {5,3,1};
	pt p {1,0},q{5,3};
	ln m=p.isct(q);
	pt r=l.isct(m);
	cout << r.x<<" "<<r.y<<" "<<r.z<<endl;
	return 0;
}
