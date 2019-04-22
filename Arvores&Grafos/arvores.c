#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

struct tnode{
	int v;
	struct tnode *l;
    struct tnode *r; 
};

struct tnode *tsearch(struct tnode *R, int v);
struct tnode *newTnode(int v);
double tvtosec(struct timeval t);
int myrand(int min, int max);
void tinsertInterativa(struct tnode **R, int v);
void tprint(struct tnode *R);
void tremove(struct tnode *R);

int main(void){
    struct timeval a;
	struct timeval b;
	struct tnode *R = NULL;
    unsigned int n, i, k;
    double tempo;
    srand(time(NULL));
    for(n = 1000; n <= 50000; n = n + 2000){
        // int aux[n];
        for(k = 0; k < n; k++){
            // aux[k] = myrand(0, n);
            tinsertInterativa(&R, k);
        }
		tempo = 0;
        for(i = 0; i <= n; i++){
       		gettimeofday(&b, NULL);
            tsearch(R, 2*n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
        tremove(R);
        R = NULL;
        
		fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		fprintf(stderr, "%d %.10lf \n", n, tempo/n);
    }
	return 0;
}

struct tnode *newTnode(int v){
    struct tnode *n = (struct tnode *) malloc(sizeof(struct tnode));
    n->v = v;
    n->l = NULL;
    n->r = NULL;
    return n;
}

struct tnode *tsearch(struct tnode *R, int v){
    if(R != NULL){
        if(R->v == v){
            return R;
        }
        if(R->v < v){
            return tsearch(R->r , v);
        }
        else{
            return tsearch(R->l, v);
        }
    }
    else{
        return NULL;
    }
}

void tinsertInterativa(struct tnode **R, int v){
    struct tnode *p, *f;
    if(*R == NULL){
        (*R) = newTnode(v);
    }
    else{
        p = (*R);
        while(p != NULL){
            f = p;
            if(p->v < v){
                p = p->r;
            }
            else{
                p = p->l;
            }
        }
        if(f->v < v){
            f->r = newTnode(v);
        }
        else{
            f->l = newTnode(v);
        }
    }
}

void tprint(struct tnode *R){
    if(R != NULL){
        tprint(R->l);
        printf("%p %d %p %p\n", R, R->v, R->l, R->r);
        tprint(R->r);
    }
}

void tremove(struct tnode *R){
    if(R != NULL){
        tremove(R->l);
        tremove(R->r);
        free(R);
    }
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}

double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}