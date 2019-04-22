#include <stdio.h>
#include <stdlib.h>

struct lnode{
	int v;
	struct lnode *n;
}

int main(){
	struct lnode *l;
	struct lnode a, b, c;

	a.v = 1;
	a.n = &b;
	b.v = 2;
	b.n = &c;
	l = &a;
	c.v = 3;
	c.n = NULL;

	return 0;
}