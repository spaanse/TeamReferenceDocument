#pragma once
#include "../setup/header.cpp"
#include "../geometry/point.cpp"
#include "../geometry/line.cpp"
struct circ{pt c;db r;
circ(pt _c,db _r){c=_c;r=_r;}
circ(pt p1,pt p2,pt p3){
	c=bisect(p1,p2).isct(bisect(p1,p3));
	r=c.dist(p1);}
circ(line l,pt p,pt q){
	pt s=line(p,q).isct(l);
	db d=sqrt(p.dist(s)*q.dist(s));
	line perp=l.perp(s);perp.c+=d;
	c=perp.isct(bisect(p,q));r=c.dist(p);}
circ(line l1,line l2,pt p){
	l1.left(p);l2.left(p);
	line m=l1.bisect(l2).parr(p);
	pt s1=m.isct(l1),s2=m.isct(l2);
	db d=sqrt(p.dist(s1)*p.dist(s2));
	line perp=l1.perp(s1);perp.c+=d;
	c=perp.isct(bisect(s1,s2));r=c.dist(p);}
circ(line l1,line l2,line l3){l1=l1.rev();
	c=l1.bisect(l2).isct(l1.bisect(l3));
	r=l1.dist(c);}
circ(line l,pt p,db _r){r=_r;db d=l.dist(p);
	line m=l.perp(p);m.c+=sqrt((2*r-d)*d);
	l.left(p);l.c+=r;c=l.isct(m);}
circ(pt p,pt q,db _r){r=_r;
	c=(p-q).normalize().rotate(acos(0.0));
	db d=(p-q).norm();d=sqrt(4*r*r-d*d);
	c=bisect(p,q).project(p+c*(d/2));}
circ(line l1,line l2,db _r){r=_r;
	l1.c+=r;l2.c+=r;c=l1.isct(l2);}
db dist(pt p){return p.dist(c)-r;}
db dist(line l){return l.dist(c)-r;}
db perimeter(){return 2*r*acos(-1.0);}
db area(){return r*r*acos(-1.0);}
pt isct(line l){
	db d=dist(l);line m=l.perp(c);
	m.c+=sqrt(r*r*-d*d);return m.isct(l);}
pt isct(circ o){db d=c.dist(o.c);
	line m(c,o.c);m=m.perp(c);
	m.c-=.5*(d*d+r*r*-o.r*o.r)/d;
	return isct(m);}
};
db arclen(db r,db t){return r*t;}
db chordlen(db r,db t){return r*sin(t/2)*2;}
db sectorarea(db r,db t){return.5*t*r*r;}
