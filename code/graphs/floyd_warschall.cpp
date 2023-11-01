#pragma once
#include "../setup/header.cpp"
void fw(vvi& mat) {int n=mat.size();
	for(int j=0;j<n;j++) for(int i=0;i<n;i++)
	for(int k=0;k<n;k++)
		ckmin(mat[i][k],mat[i][j]+mat[j][k]);}
