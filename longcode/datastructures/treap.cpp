#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <assert.h>
#include <iomanip>

using namespace std;

typedef vector<int> vi;
typedef vector <vi> vvi;
typedef pair<int, int> ii;
typedef vector <ii> vii;
typedef int64_t ll;
//727
namespace treap {
    typedef int T;

    struct node {
        T value;
        int hash, size = 1;
        node *p = 0, *l = 0, *r = 0;

        node(T _v) {
            value = _v;
            hash = rand();
        }
    };

    int hash(node *n) { return n->hash; }

    int size(node *n) { return n ? n->size : 0; }

    void update(node *n) {
        if (!n)return;
        n->p = 0;
        n->size = 1 + size(n->l) + size(n->r);
        if (n->l) n->l->p = n;
        if (n->r) n->r->p = n;
    }

    node *copy(node *t) {
        if (!t) { return 0; }
        node *c = new node{*t};
        c->l = copy(t->l);
        c->r = copy(t->r);
        update(c);
        return c;
    }

    void remove(node *&t) {
        if (!t)return;
        remove(t->l);
        remove(t->r);
        delete t;
        t = 0;
    }

    void split(node *t, T value, node *&l, node *&r) {
        if (!t) {
            l = r = 0;
            return;
        }
        if (value < t->value) {
            split(t->l, value, l, t->l);
            r = t;
        }
        if (value > t->value) {
            split(t->r, value, t->r, r);
            l = t;
        }
        if (value == t->value) {
            l = t->l;
            r = t->r;
            delete t;
        }
        else update(t);
    }

    void concat(node *&t, node *l, node *r) {
        if (!l || !r) {
            t = l ? l : r;
        } else if (hash(l) > hash(r)) {
            concat(l->r, l->r, r);
            t = l;
        } else {
            concat(r->l, l, r->l);
            t = r;
        }
        update(t);
    }

    void insert(node *&t, node *n) {
        if (!t) {
            t = n;
        } else if (hash(n) > hash(t)) {
            split(t, n->value, n->l, n->r);
            t = n;
        } else {
            insert(n->value < t->value ? t->l : t->r, n);
        }
        update(t);
    }

    void insert(node *&t, T value) { insert(t, new node{value}); }

    void remove(node *&t, T value, node *&d) {
        if (!t) return;
        if (t->value == value) {
            d = t;
            concat(t, t->l, t->r);
        } else { remove(value < t->value ? t->l : t->r, value, d); }
        update(t);
    }

    void remove(node *&t, T value) {
        node *tmp = 0;
        remove(t, value, tmp);
        delete tmp;
    }

    node *find(node *t, T value, int &i) {
        while (t && t->value != value) {
            if (value < t->value)t = t->l;
            else {
                i += size(t->l) + 1;
                t = t->r;
            }
        }
        if (t) { i += size(t->l); }
        return t;
    }

    node *find(node *t, T value) {
        int tmp = 0;
        return find(t, value, tmp);
    }

    node *root(node *n) {
        while (n->p) { n = n->p; }
        return n;
    }

    node *nth(node *t, int i) {
        while (t && i != size(t->l)) {
            if (i < size(t->l))t = t->l;
            else {
                i -= size(t->l) + 1;
                t = t->r;
            }
        }
        return t;
    }

    node *min(node *t) { return nth(t, 0); }

    node *max(node *t) { return nth(t, size(t) - 1); }

    node *skip(node *n, int d) {
        find(root(n), n->value, d);
        return nth(root(n), d);
    }

    node *succ(node *n) { return skip(n, 1); }

    node *pred(node *n) { return skip(n, -1); }
}
using namespace treap;

// void setop(node*&l,node*&r,char b){
// 	if(!l||!r){l=l?l:r;r=0;
// 		if(!(b&1)){remove(l);}return;}
// 	if(hash(l)<hash(r))swap(l,r);
// 	node*lt,*rt=lt=0;
// 	bool fnd=find(r,l->value);split(r,l->value,lt,rt);
// 	setop(l->l,lt,b);setop(l->r,rt,b);
// 	if(!(fnd?(b&2):(b&1)))remove(l,l->value);
// 	r=0;update(l);}
// void diff(node*&l,node*&r){setop(l,r,1);}
// void isct(node*&l,node*&r){setop(l,r,2);}
// void merge(node*&l,node*&r){setop(l,r,3);}
// void setmin(node*&l,node*r){if(!l||!r)return;
// 	node*lt,*rt=lt=0;split(l,r->value,lt,rt);
// 	setmin(lt,r->l);setmin(rt,r->r);
// 	concat(l,lt,rt);update(l);}

void print(node *t, string prefix = "") {
    if (!t) return;
    print(t->l, prefix + "  |");
    cout << prefix << setw(3) << t->value << endl;
    print(t->r, prefix + "  |");
}

void validate(node *t) {
    if (!t) return;
    assert(t->size == 1 + size(t->l) + size(t->r));
    if (t->l) {
        validate(t->l);
        assert(t->l->p == t);
        assert(max(t->l)->value < t->value);
        assert(treap::hash(t->l) <= treap::hash(t));
    }
    if (t->r) {
        validate(t->r);
        assert(t->r->p == t);
        assert(min(t->r)->value > t->value);
        assert(treap::hash(t->r) <= treap::hash(t));
    }
}

int main() {
    node *tree1 = 0, *tree2 = 0;
    insert(tree1, 1);
    insert(tree1, 4);
    insert(tree2, 4);
    insert(tree2, 2);
    print(tree1);
    cout << endl;
    remove(tree1);
    remove(tree2);
    return 0;
}
