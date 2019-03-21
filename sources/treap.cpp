#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdarg>

using namespace std;

#pragma comment (linker, "/STACK:160000000")

typedef long long ll;
typedef pair <int, int> pii;

const int N = 100500;	//treap
const int M = 20000000;	//memory

struct node {
	node * l, * r;
	int x, y;
	int cnt;
	int add;

	node() {
		l = r = 0;
		y = rand();
		add = 0;
		cnt = 1;
	}
};

node memory[M];
int K = 0;

int cnt(node * t) {
	if (t == 0)
		return 0;
	return t -> cnt;
}

void update(node * t) {
	if (t -> l) {
		t -> l -> add += t -> add;
	}
	if (t -> r) {
		t -> r -> add += t -> add;
	}
	t -> x += t -> add;
	t -> add = 0;
}

void update_cnt(node * t) {
	if (t) {
		t -> cnt = 1 + cnt(t -> l) + cnt(t -> r);
	}
}

void split(node * t, node *& l, node *& r, int x) {
	if (!t) {
		l = r = 0;
		return;
	}
	update(t);
	if (x <= t -> x) {
		split(t -> l, l, t -> l, x);
		r = t;
	} else {
		split(t -> r, t -> r, r, x);
		l = t;
	}
	update_cnt(t);
}

node * merge(node * l, node * r) {
	if (l == 0) {
		return r;
	}
	if (r == 0) {
		return l;
	}
	update(l);
	update(r);
	node *t;
	if (l -> y < r -> y) {
		l -> r = merge(l -> r, r);
		t = l;
	} else {
		r -> l = merge(l, r -> l);
		t = r;
	}
	update_cnt(t);
	return t;
}

void print(node * t) {
	if (!t)
		return;
	print(t -> l);
	printf("%d ", t -> x);
	print(t -> r);
}

int main() {
	return 0;
}
