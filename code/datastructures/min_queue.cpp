#pragma once
#include "../setup/header.cpp"
#include "../datastructures/min_stack.cpp"
struct mq{ms i,o;
	int sz(){return i.sz()+o.sz();}
	void fix(){if(!o.sz())while(i.sz()){
			o.push(i.top()); i.pop();}}
	int front() {fix(); return o.top();}
	int mn(){return min(i.mn(), o.mn());}
	void push(int v){i.push(v);}
	void pop(){fix(); o.pop();}};
