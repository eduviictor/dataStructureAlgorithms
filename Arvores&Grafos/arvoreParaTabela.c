#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

/*Eduardo Victor*/


struct tnode{
	int v;
	struct tnode *l;
    struct tnode *r; 
};

typedef struct tabela{
	int v;
	struct tabela *prox;
}Hash;

struct tnode *tsearch(struct tnode *R, int v);
struct tnode *newTnode(int v);
int myrand(int min, int max);
void tinsertInterativa(struct tnode **R, int v);
void tprint(struct tnode *R);
void tremove(struct tnode *R);
void inserirHash(int num, int tam, Hash* v);
void copyAndRemove(struct tnode *R, int tam, Hash* v);
void testar(Hash* v, int n);
int hash(int num, int tam);

int main(void){
	struct tnode *R = NULL;
    unsigned int n = 8, i;
    Hash v[8];
    srand(time(NULL));
    for(i = 0; i < n; i++){
		v[i].prox = NULL;
	}
    for(i = 0; i < 15; i++){
        tinsertInterativa(&R, myrand(0, 100));
    }

    tprint(R);
    copyAndRemove(R, n, v);

    testar(v, n);
    R = NULL;
	return 0;
}

void testar(Hash* v, int n){
	Hash* p;
	for(int i = 0; i < n; i++){
		if(v[i].prox != NULL){
			printf("\nPosition: %d", i);
			for(p = v[i].prox; p != NULL; p = p->prox){
				printf("\n%d", p->v);
			}
		}
	
	}
	printf("\n");
}

void copyAndRemove(struct tnode *R, int tam, Hash* v){
    if(R != NULL){
        copyAndRemove(R->l, tam, v);
        R->l = NULL;
        copyAndRemove(R->r, tam, v);
        R->r = NULL;
        if((R->l == NULL) && (R->r == NULL)){
            inserirHash(R->v, tam, v);
            R = NULL;
        }
    }
}

int hash(int num, int tam){
	return num % tam;
}

void inserirHash(int num, int tam, Hash* v){
	int chave = hash(num, tam);
	Hash* new = (Hash*) malloc(sizeof(Hash));
	if(v[chave].prox != NULL){
		Hash* p = (Hash*) malloc(sizeof(Hash));
		for(p->prox = v[chave].prox; p != NULL; p = p->prox){
			if(p->prox == NULL){
				p->prox = new;
				new->prox = NULL;
				new->v = num;
			}
		}
	}else{
		new->prox = NULL;
		new->v = num;
		v[chave].prox = new;
	}

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