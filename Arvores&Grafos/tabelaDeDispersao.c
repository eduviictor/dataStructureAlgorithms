#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef struct tabela{
	int v;
	struct tabela *prox;
}Hash;


double tvtosec(struct timeval t);
int myrand(int min, int max);
void newv(int *v, unsigned int n);
int hash(int v, int n);
void inserirHash(int num, Hash* v);
void testar(Hash* v, int n);
void testarL(Hash* v, int n);
int numElements(Hash* v);
void verificaHash(Hash* v);
Hash* buscaHash(int num, int n, Hash* v);
Hash redimensiona(Hash* v);
void hremove(Hash* v);

static int contador;

int main(void){
    struct timeval a;
	struct timeval b;
	unsigned int n, i;
    double tempo;
	srand(time(NULL));
	

	for(n = 100; n <= 1000; n = n + 1000){
		Hash v[1];
		contador = 1;
		v[0].prox = NULL;
        for(i = 0; i < 10; i++){
			
            inserirHash(myrand(1, n), v);
			testarL(v, contador);
        }
		return 0;
		tempo = 0;
        for(i = 0; i <= n; i++){
       		gettimeofday(&b, NULL);
            buscaHash(2, 8, v);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
        hremove(v);
		// fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		// fprintf(stderr, "%d %.10lf \n", n, tempo/n);
    }
	
	return 0;
}

// int numElements(Hash* v){
// 	int cont = 0;
// 	for(int i = 0; v[i] != NULL; i++){
// 		cont++;
// 	}
// 	printf("\n%d", cont);
// 	return cont;
// }

void hremove(Hash* v){
	v = NULL;
}

Hash* buscaHash(int num, int n, Hash* v){
	int chave = hash(num, n);
	Hash* p;
	if(v[chave].prox != NULL){
		for(p = v[chave].prox; p != NULL; p = p->prox){
			if(p->v == num){
				return p;
			}
		}
	}
	return NULL;
}

int hash(int num, int tam){
	return num % tam;
}

void testar(Hash* v, int n){
	for(int i = 0; i < n; i++){
		printf("\n%p", v[i].prox);
	}
	printf("\n");
}

void inserirHash(int num, Hash* v){
	
	int tam = contador;
	printf("\nTam: %d", tam);
	int chave = hash(num, tam);
	verificaHash(v);
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

void verificaHash(Hash* v){
	int tam = contador;
	int cont;
	for(int i = 0; i < tam; i++){
		if(v[i].prox != NULL){
			cont = 0;
			Hash* p;
			for(p = v; p->prox != NULL; p = p->prox){
				cont++;
			}
			printf("\nCont: %d", cont);
			printf("\nTam: %d", tam);
			if(cont > tam){
				*v = redimensiona(v);
			}
			
		}
	
	}
	printf("\n----");
	testarL(v, contador);
}

void testarL(Hash* v, int n){
	Hash* p;
	for(int i = 0; i < n; i++){
		printf("\nChave %d: ", i);
		if(v[i].prox != NULL){
			for(p = v[i].prox; p != NULL; p = p->prox){
				printf(" %d", p->v);
			}	
		}
		printf("\n-------------------------------");
	}
	printf("\n");
}

Hash redimensiona(Hash* v){
	contador = contador * 2;
	printf("\nContador: %d", contador);
	int tam = contador;
	Hash new[tam];
	int i;
	for(i = 0; i < tam; i++){
		new[i].prox = NULL;
	}
	Hash* p;
	for(i = 0; i < tam/2; i++){	
		if(v[i].prox != NULL){
			p = v[i].prox;
			while(p != NULL){
				//testarL(v, contador/2);
				inserirHash(p->v, new);
				
				//printf("\nRedimensionei\n");
				p = p->prox;
			}
			testarL(new, contador);
			// for(p = v[i].prox; p != NULL; p = p->prox){
			// 	inserirHash(p->v, tam * 2, new);
			// 	testarL(new, tam * 2);
			// 	printf("\nRedimensionei\n");
			// }
		}
	}
	return *new;
}

//H(v, n) = v % n + 1

void newv(int *v, unsigned int n){
	for(int i = 0; i < n; i++){
		v[i] = 0;
	}
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}

double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	