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
    struct tnode *p;
    unsigned int h;
};

struct tnode *tsearch(struct tnode *R, int v);
struct tnode *newTnode(int v);
double tvtosec(struct timeval t);
int myrand(int min, int max);
void tinsertInterativa(struct tnode **R, int v);
void tinsertInterativaBalanceada(struct tnode **R, int v);
void tprint(struct tnode *R);
int max(int n1, int n2);
void re(struct tnode *x);
void updated(struct tnode *n);

int main(void){
    struct tnode *R = NULL;
    for(int i = 0; i < 10; i++){
        tinsertInterativaBalanceada(&R, i);
    }
    tprint(R);
    
	return 0;
}

struct tnode *newTnode(int v){
    struct tnode *n = (struct tnode *) malloc(sizeof(struct tnode));
    n->v = v;
    n->l = NULL;
    n->r = NULL;
    n->p = NULL;
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
            if(p->v == v){
                return;
            }
            else if(p->v < v){
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

void tinsertInterativaBalanceada(struct tnode **R, int v){
    struct tnode *w = newTnode(v);
    struct tnode *p, *f;
    
    if(*R == NULL){
        *R = w;
    }
    else{
        p = *R;
        while(p != NULL){
            f = p;
            if(p->v > w->v){
                p = p->l;
            }
            else{
                p = p->r;
            }
        }

        w->p = f;
        
        if(w->v < f->v){
            f->l = w;
            
        }
        else{
            f->r = w;
        }
        updated(f);
    }
}



void updated(struct tnode *n){
    unsigned int h = max(n->r->h, n->l->h) + 1;
    if(n->h != h){
        if((n->r->h - n->l->h) >= 2){
            re(n);
        }
        n->h = h;
        if(n->p != NULL){
            updated(n->p);
        }
    }
}

int max(int n1, int n2){
    if(n1 > n2){
        return n1;
    }else{
        return n2;
    }
}

void re/*C1*/(struct tnode *x){
    struct tnode *y = x->r;
    struct tnode *b = y->l;
    if(x->p != NULL){
        if(x->p->r == x){
            x->p->r = y;
        }
        else{
            x->p->l = y;
        }
    }
    y->p = x->p;
    x->p = y;
    y->l = x;
    if(b != NULL){
        b->p = x;
        x->l = b;
    }
}

/*debug gdb
    gcc -g gdb ...
    gdb nomeArquivo
    run
*/



void tprint(struct tnode *R){
    if(R != NULL){
        tprint(R->l);
        printf("%p %d %p %p %p\n", R, R->v, R->l, R->r, R->p);
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




// void tinsertInterativaBalanceada(struct tnode **R, int v){
//     struct tnode *w = newTnode(v);
//     struct tnode *p, *f;
    
//     if(*R == NULL){
//         *R = w;
//     }
//     else{
//         f = p;
//         p = *R;
        
//         while(p != NULL){
//             if(p->v > w->v){
//                 p = p->l;
//             }
//             else{
//                 p = p->r;
//             }
//         }
//         w->p = f;
        
//         if(w->v < f->v){
//             f->l = w;
            
//         }
//         else{
//             f->r = w;
//         }
//         //updated(f);
//     }
// }