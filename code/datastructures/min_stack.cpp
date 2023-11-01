#pragma once
#include "../setup/header.cpp"
struct ms{stack<int> s,m;
	int sz(){return s.size();}
	int top(){return s.size()?s.top():INF;}
	int mn(){return s.size()?m.top():INF;}
	void push(int v){ s.push(v);
		m.push(min(m.top(),v));}
	void pop(){s.pop();m.pop();}};
