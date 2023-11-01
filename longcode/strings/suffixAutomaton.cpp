#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef int64_t ll;
typedef string st;
#define pb push_back
//79L
vi fstr (st s) {
	int numNode=s.size (),i=0;
	vi a (numNode);
	for (; i<numNode; i++) {
		a[i]=s[i]-'a';
	}
	return a;
}
st tstr (vi s) {
	int numNode=s.size (),i=0;
	st a;
	for (; i<numNode; i++) {
		a+=s[i]+'a';
	}
	return a;
}

struct newSufAut {
	struct node {
		node* link=0;
		int length=0, original=false, paths=1, count=0;
		map<char,node*> trans={};
	} *last,*root = last = new node;
	node* find(string s) {
		node* current = root;
		for (char c:s) if(current) {
			current = current->trans[c];
		}
		return current;
	}
	bool has(string s) {
		return find(s);
	}
	void add(char c) {
		node* current = new node{root,last->length+1,true};
		for(;last&&!last->trans[c];last=last->link){
			last->trans[c]=current;
		}
		if (last) {
			node* next = last->trans[c];
			if(last->length+1!=next->length) {
				node* clone = new node(*next);
				clone->length = last->length+1;
				current->link = next->link = clone;
				for(; last && last->trans[c] == next; last = last->link) {
					last->trans[c] = clone;
				}
			} else {
				current->link = next;
			}
		}
		last = current;
	}
	void add (string s) {
		for (int c:s) add (c);
	}
	vector<node*> revTopoOrder() {
		vector<node*> ans{root};
		for(node* cur : ans) {
			for (auto elem : cur->trans) {
				node* next = elem.second;
				if (next && next->length == cur->length+1) {
					ans.push_back(next);
				}
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
	int numSubstr () {
		int ans=0;
		for (node* cur:revTopoOrder()) {
			for (auto elem : cur->trans) {
				node* next = elem.second;
				if (next)
					cur->paths+=next->paths;
			}
			ans+=cur->paths;
		}
		return ans;
	}
	string lexicalKth (int k) {
		string ans;
		node* current = root;
		int kp;
		while (k--)
			for (auto elem : current->trans){
			node* next = elem.second;
			if (next) {			
				kp=k;
				k-=next->paths;
				if (k<0) {
					current=next;
					ans.push_back(elem.first);
					k=kp;
					break;
				}
			}
		}
		return ans;
	}
	void precomputeOcc () {
		for (node* cur:revTopoOrder ()) {
			cur->count += cur->original;
			if (cur->link) cur->link->count+=cur->count;
		}
	}
	int numberOcc (string s) {
		return find (s)->count;
	}
	int firstOcc (string s) {
		return find (s)->length-s.size ();
	}
};

int main () {
	return 0;
}
