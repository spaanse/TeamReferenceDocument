#ifndef LINE
#define LINE 

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include "point.cpp"
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

#define EPS 1e-9
#define INF (1<<29)

//4a2
// include point; ax+by=c, a*a+b*b=1
struct line{db a,b,c;
line(pt p1,pt p2) {pt p=(p2-p1).normalize();
	a=-p.y; b=p.x; c=a*p1.x+b*p1.y;}
line(db _a,db _b,db _c){a=_a;b=_b;c=_c;}
bool par(line l){
	return fabs(b*l.a-a*l.b)<EPS;}
bool operator==(line l){
	return par(l)&&fabs(a*c-l.a*l.c)<EPS;}
pt isct(line l){db d=b*l.a-a*l.b;
	return{(b*l.c-c*l.b)/d,-(a*l.c-c*l.a)/d};}
line parr(pt p){return {a,b,a*p.x+b*p.y};}
line perp(pt p){return {-b,a,-b*p.x+a*p.y};}
line rev(){return {-a,-b,-c};}
void left(pt p){
	if(a*p.x+b*p.y<-EPS){a=-a;b=-b;c=-c;}}
line bisect(line l){db d=hypot(a+l.a,b+l.b);
	return {(a+l.a)/d,(b+l.b)/d,(c+l.c)/d};}
pt project(pt p){return isct(perp(p));}
pt mirror(pt p){return project(p)*2-p;}
db dist(pt p){return project(p).dist(p);}
};
line bisect(pt a,pt b){
	return line(a,b).perp((a+b)*.5);}

#endif