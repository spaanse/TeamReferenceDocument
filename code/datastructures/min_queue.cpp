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
template<typename T> struct monStack{
	stack<T> s, m;
	bool size() {return s.size();}
	T top(){return s.top();}
	T min(){return m.top();}
	void push(T v){ s.push(v);
		m.push(m.size() ? min(m.top(),v) : 0);}
	void pop() {s.pop(); m.pop();}};
// queue, but stores value of min element
template<typename T> struct monQueue{
	monStack<T> i,o;
	bool size(){return i.size() + o.size();}
	void fix(){if(!o.size())while(i.size()){
			o.push(i.top()); i.pop();}}
	T front() {fix(); return o.top();}
	T min() { if (!i.size()) return o.min();
		        if (!o.size()) return i.min();
		return min(i.min(), o.min());}
	void push(T v) {i.push(v);}
	void pop() {fix(); o.pop();}};

int main() {
	
	return 0;
}