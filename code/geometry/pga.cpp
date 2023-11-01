#pragma once
#include "../setup/header.cpp"
template<int p,int q,int r>
struct ga{static const int d=p+q+r, e=1<<d;
struct mv {vd c = vd(e); uint i=0,j=0;
db f(uint x, uint y){x&=e-1;uint z=(x&y)>>p;
	if(z>>q){return 0;}db a=popcount(z)&1?-1:1;
	while(x>>=1)if(popcount(x&y)&1)a*=-1;
	return a;}
mv operator~(){mv a(c);for(i=0;i<e;i++){
	if(popcount(i)&2)a.c[i]*=-1;}return a;}
//right dual: x !x = I; left dual: !!!x x = I
mv operator!(){mv a;for(i=0;i<e;i++)
	{ a.c[e-1-i]=c[i]*f(i,~i); } return a;}
mv prod(mv&w, auto b){mv a;i=0;
	for(;i<e;i++)for(j=0;j<e;j++)if(!b(i,j)){
		a.c[i^j]+=f(i,j)*c[i]*w.c[j];}return a;}
mv operator*(mv w){return prod(w,
	[](int i,int j){return 0;});}
mv operator|(mv w){return prod(w,
	[](int i,int j){return i&j;});}
mv operator&(mv w){return!!!((!*this)|!w);}
mv operator/(mv w){return prod(w,
	[](int i,int j){return i&~j&&~i&j;});}
friend ostream& operator<<(ostream& o,mv v){
	int i=0,j=0,k;for(i=0;i<e;i++)if(v.c[i]){
		if(0<v.c[i]&&j++){o<<"+";}o<<v.c[i]<<"e";
		for(k=0;k<d;k++)if(i&(1<<k))o<<k;}
	if(!j){o<<"0";}return o;}};
template<int g> struct gr : mv {
gr<g> operator~(){return{mv::operator~()};}
gr<d-g> operator!(){return{mv::operator!()};}
template<int h>gr<g+h> operator|(gr<h>w){
	return {mv::operator|(w)};}
template<int h>gr<g+h-d> operator&(gr<h>w){
	return {mv::operator&(w)};}
template<int h>gr<abs(g-h)>operator/(gr<h>w)
	{return {mv::operator/(w)};}};};

using pga = ga<3,1,0>;
using scalar = pga::gr<0>;
using point = pga::gr<1>;
using line = pga::gr<2>;
using plane = pga::gr<3>;
using volume = pga::gr<4>;

int test_pga() {
	point v;
	v.c[1] = 1.0;
	plane w = !v;
	cout << w << endl;
	// for (int i = 0; i < 1<<4; i++) {
	// 	// mv<3,1,0> v;
	// 	// v.c[i] = 1.0;
	// 	// v.print();
	// 	cout << " ";
	// 	// (v * !v).print();
	// 	cout << " ";
	// 	// (!!!v * v).print();
	// 	cout << " ";
	// 	// (!!!!v).print();
	// 	cout << endl;

	// }
	// for (int i = 0; i < 1<<4; i++) {
	// 	for (int j = 0; j < 1<<4; j++) {
	// 		mv<3,0,1> v, w;
	// 		v.c[i] = 1.0;
	// 		w.c[j] = 1.0;
	// 		// (v&w).print();
	// 		cout << " ";
	// 	}
	// 	cout << endl;
	// }
	// return 0;
}
