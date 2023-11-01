#pragma once
#include "../setup/header.cpp"
struct pt{ db x=0.0,y=0.0;
bool operator==(pt p){
	return fabs(x-p.x)<EPS &&fabs(y-p.y)<EPS;}
pt& operator+=(pt&p) {
	x+=p.x; y+=p.y; return *this;}
pt& operator-=(pt&p) {
	x-=p.x; y-=p.y; return *this;}
pt& operator*=(db s) {
	x*=s; y*=s; return *this;}
pt operator+(pt r){pt a=*this; return a+=r;}
pt operator-(pt r){pt a=*this; return a-=r;}
pt operator*(db s){pt a=*this; return a*=s;}
db norm(){return hypot(x,y);}
db dist(pt p){return (*this-p).norm();}
pt normalize(){if(norm()<EPS)return pt();
	else return operator*(1.0/norm());}
pt rotate(db r){return 
	{x*cos(r)-y*sin(r),x*sin(r)+y*cos(r)};}
pt mirror(pt p){return *this*2-p;}
pt mid(pt p){return (*this+p)*.5;}
db dot(pt p){return x*p.x+y*p.y;}
db cross(pt p) {return x*p.y-y*p.x;}
db angle(pt p){
	return acos(dot(p)/norm()/p.norm());}
bool col(pt p){return fabs(cross(p))<EPS;}
bool ccw(pt p){return cross(p)>EPS;}};
