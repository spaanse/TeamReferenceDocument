#pragma once
#include "../setup/header.cpp"
// n power of two
void fft(vc&a,int n,bool inv=0){
	if(n==1) {return;} a.resize(n);
	cpx wp=exp(2i*acos(-1)/cpx(inv?-n:n)),w=1;
	vc o(n/2),e(n/2);
	for(int i=0;i<n/2;i++){
		e[i]=a[2*i];o[i]=a[2*i+1];}
	fft(e,n/2,inv);fft(o,n/2,inv);
	for(int i=0;i<n/2;i++,w*=wp){
		a[i]=e[i]+w*o[i];a[i+n/2]=e[i]-w*o[i];}
	if(inv)for(int i=0;i<n;i++)a[i]/=2;}
