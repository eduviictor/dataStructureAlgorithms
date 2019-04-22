#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef struct tabela{
	int v;
	struct tabela *prox;
}Lista;

int main(void){
    // struct timeval a;
	// struct timeval b;
	unsigned int n = 8, i;
    // double tempo;
    Lista **t;
    
	Lista *v;
	v = (Lista*) malloc(8 * sizeof(Lista));
	t = &v;
    printf("\n%s", t);
	return 0;
}
