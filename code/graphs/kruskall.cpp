#pragma once
#include "../setup/header.cpp"
#include "../datastructures/union_find.cpp"
typedef tuple<int,int,int> edge;
typedef vector<edge> ve;
void kruskall(int n,ve ed,ve&mst){uf con(n);
	mst.reserve(n); sort(ed.begin(),ed.end());
	for(auto&[c,f,t]:ed)if(!con.same(f,t)){
		mst.push_back({c,f,t}); con.join(f,t);}}
