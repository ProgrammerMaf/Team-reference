#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma comment(linker, "/STACK:16000000")

typedef long long ll;
typedef pair<int, int> pii;

const int INF = (int)1e9;
const double EPS = 1e-8;
const double PI = 2 * acos(0.);

const int N = 100500;	//treap
const int M = 20000000;	//memory

struct node {
	node * l;
	node * r;
	bool rev;
	int val;
	int y;
	int cnt;

};

node * memory[M];
int K = 0;

void update(node * t) {
	if (t) {
		if (t -> rev) {
			swap(t -> l, t -> r);
			if (t -> l) {
				(t -> l -> rev) ^= 1;
			}
			if (t -> r) {
				(t -> r -> rev) ^= 1;
			}
			t -> rev = 0;
		}
	}
}

int cnt(node * t) {
	return t ? t -> cnt : 0;
}

void update_cnt(node * t) {
	if (t) {
		t -> cnt = 1 + cnt(t -> l) + cnt(t -> r);
	}
}

void split(node* t, int k, node *& l, node *& r) {
	if (!t)
		return;
	update(t);
	l = r = NULL;
	if (cnt(t -> l) >= k) {
		split(t -> l, k, l, t -> l);
		r = t;
	} else {
		k -= cnt(t -> l);
		--k;
		split(t -> r, k, t -> r, r);
		l = t;
	}
	update_cnt(l);
	update_cnt(r);
}

node * merge(node * l, node * r) {
	if (!l) {
		return r;
	}
	if (!r) {
		return l;
	}
	update(l);
	update(r);
	if (l -> y < r -> y) {
		l -> r = merge(l -> r, r);
		update_cnt(l);
		return l;
	} else {
		r -> l = merge(l, r -> l);
		update_cnt(r);
		return r;	
	}
}

node * build_treap(int *x, int *y, int l, int r) {
	if (l >= r)
		return NULL;
    node * t;
	int mn = l;
	for (int i = l; i < r; ++i) {
		if (y[i] < y[mn]) {
			mn = i;
		}
	}
    t = new node();
    t -> val = x[mn];
    t -> y = y[mn];
    t -> rev = 0;
    t -> l = build_treap(x, y, l, mn);
    t -> r = build_treap(x, y, mn + 1, r);
    update_cnt(t);
    return t;
}

int x[N];
int y[N];

node * build_treap(int *a, int n) {
	for (int i = 0; i < n; ++i) {
		x[i] = a[i];
		y[i] = rand() ^ (int(rand()) << 15);
	}
	return build_treap(0, n);
}

int main() {
	return 0;
}
