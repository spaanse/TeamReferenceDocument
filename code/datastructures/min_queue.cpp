#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <stack>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
//5ih
// stack, but stores value of min element
struct ms{stack<int> s,m;
	int sz(){return s.sz();}
	int top(){return s.sz()?s.top():2e9;}
	int mn(){return s.sz()?m.top():2e9;}
	void push(int v){ s.push(v);
		m.push(min(m.top(),v));}
	void pop(){s.pop();m.pop();}};
// queue, but stores value of min element
struct mq{ms i,o;
	int sz(){return i.sz()+o.sz();}
	void fix(){if(!o.sz())while(i.sz()){
			o.push(i.top()); i.pop();}}
	int front() {fix(); return o.top();}
	int mn(){return min(i.mn(), o.mn());}
	void push(int v){i.push(v);}
	void pop(){fix(); o.pop();}};

int main() {
	
	return 0;
}