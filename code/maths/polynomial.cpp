#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <assert.h>
#include <complex>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;

typedef complex<double> cpx;
typedef vector<cpx> vcpx;
//6E3
// n power of two
void fft(vcpx&a,int n,bool inv=0){
	if(n==1) {return;} a.resize(n);
	cpx wp=exp(2i*acos(-1)/cpx(inv?-n:n)),w=1;
	vcpx o(n/2),e(n/2);
	for(int i=0;i<n/2;i++){
		e[i]=a[2*i];o[i]=a[2*i+1];}
	fft(e,n/2,inv);fft(o,n/2,inv);
	for(int i=0;i<n/2;i++,w*=wp){
		a[i]=e[i]+w*o[i];a[i+n/2]=e[i]-w*o[i];}
	if(inv)for(int i=0;i<n;i++)a[i]/=2;}

#define rep(i,m) for(int i=0;i<m;i++)
//075
template<typename T>
struct pl { typedef vector<T> vT; vT c;
void fix(){while(!c.empty()&&c.back()==T(0))
	c.pop_back();}
pl(initializer_list<T> l):c(l){fix();}
pl(vT l):c(l){fix();} pl(T v){c={v};fix();}
int deg(){return c.size()-1;}
T operator[](int i){
	return (0<=i&&i<(int)c.size())?c[i]:T(0);}
pl operator+(pl r) {
	int d=max(deg(),r.deg())+1; vT a(d);
	rep(i,d){a[i]=(*this)[i]+r[i];} return a;}
pl operator-(pl r) {
	int d=max(deg(),r.deg())+1; vT a(d);
	rep(i,d){a[i]=(*this)[i]-r[i];} return a;}
pl operator*(pl r) { vT a(deg()+r.deg()+1);
	rep(i,deg()+1) rep(j,r.deg()+1){
		a[i+j]+=c[i]*r.c[j];} return a;}
pl operator/(pl r){ pl t=c; vT a;
	while (t.deg()>=r.deg()){
		a.push_back(t.c.back()/r.c.back());
		t = t-r*a.back();}
	reverse(a.begin(), a.end()); return a;}
pl operator%(pl r){return *this-*this/r*r;}
template<typename S>S eval(S x){S b{1},a;
	rep(i,deg()+1){a+=b*c[i];b*=x;} return a;}
pl modxk(int k){ k=min(k,(int)c.size());
	return vT(c.begin(),c.begin()+k);}
pl divxk(int k){ k=min(k,(int)c.size());
	return vT(c.begin()+k,c.end());}
pl mulxk(int k){vT a=c;
	a.insert(a.begin(),k,0);return a;}
pl deriv() {pl a=divxk(1);
	rep(i,deg()){a.c[i]*=i+1;} return a;}
pl intg() {pl a=mulxk(1);
	rep(i,deg()+1) {a.c[i+1]/=i+1;} return a;}
pl inv(int n) {pl a={T(1)/c[0]};
	for(int i=1;i<n;i*=2){
		pl t = (a*modxk(2*i)).divxk(i).modxk(i);
		a = a-(a*t).modxk(i).mulxk(i);}
	return a.modxk(n);}
pl rev(int n,bool f=0){ pl a=c;
	if (f) a.c.resize(max(n,(int)a.c.size()));
	reverse(a.c.begin(),a.c.end());
	return a.modxk(n);}
pl fdiv(pl r){int d=deg()-r.deg()+1;
	if (d<=0){return{};}
	pl a=(rev(d)*r.rev(d).inv(d));
	return a.modxk(d).rev(d,1);}
pl fmod(pl r){return *this-fdiv(r)*r;}
pl fmul(pl r){int d=deg()+r.deg()+1;
	d=2*d-1; while (d&(d-1)) d&=d-1;
	vcpx v1=c,v2=r.c; fft(v1,d);fft(v2,d);
	for (int i=0;i<d;i++) v1[i]*=v2[i];
	fft(v1,d,1);return pl(v1);}};

int main() {
	pl<cpx> a {3,5,2};
	pl<cpx> b {2,-3,1,7};
	pl<cpx> c = b.fmod(a);
	// 6,1,-8,20,37,14
	for (int i = 0; i <= c.deg(); i++) {
		cout << c.c[i] << " ";
	} cout << endl;
	return 0;
}