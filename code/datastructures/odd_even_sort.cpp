#pragma once
#include "../setup/header.cpp"
void oemerge(vi& v, int l0, int le, int m0, int me, int d=1) {
	oemerge(v, l0,   le, m0,   me, 2*d);
	oemerge(v, l0+d, le, m0+d, me, 2*d);
}

void oesort(vi& v, int l, int r) {
	int m = (l+r) / 2;
	oesort(v, l, m);
	oesort(v, m, r);
	oemerge(v, l, m, r);
	return;
}

int main() {
	
	return 0;
}
