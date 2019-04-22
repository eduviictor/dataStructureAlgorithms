#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct grafo{
	int v;
	struct grafo *prox;
}Grafo;

double tvtosec(struct timeval t);
int myrand(int min, int max);
void newv(int *v, unsigned int n);
// void inserirLigação(int num, int tam, int destino, Grafo* a);
void testar(Grafo* v, int n);
void testarL(Grafo* v, int n);
// Grafo* buscaGrafo(int num, int n, Grafo* v);
// void hremove(Grafo* v);
void lerArqPraLista();
void lerArqPraMatriz();

int main(void){
	FILE* arq = fopen("grafo.txt", "r");
	
	char *aux;
    char c[100];
    int n = 0, esc;

	while(!feof(arq)){
        aux = fgets(c, 100, arq);
        if(strcmp(aux, "#\n") == 0){
            break;
        }
        else{ 
            n++;
		}
    }
    

	printf("\n1 - Ler arquivo pra lista\n2 - Ler arquivo pra Matriz\n");
	scanf("%d", &esc);
	
	switch(esc){
		case 1:
			
			lerArqPraLista(n);
			
			break;
		case 2:
			lerArqPraMatriz(n);
			break;
		default:
			printf("\nOpção inválida");
			break;
	}
	
	
	return 0;
}

void lerArqPraLista(int n){
	Grafo grafo[n];
	for(int i = 0; i < n; i++){
		grafo[i].prox = NULL;
	}
	FILE *file;
	file = fopen("grafo.txt", "r");
	if(file == NULL){
		printf("Arquivo n�o pode ser aberto!");
		system("pause");
		return;
		}
	else{
		char frase[100], num1S[3], num2S[3];
		int aux = 0, aux2, contS, i = 0, num1, num2, t, index1, index2, j;
		while(fgets(frase, 100, file) != NULL){ /*   */
			for(t = 0; frase[t] != '\0'; t++){
				if(frase[t] == '#'){
					break;
				}
			}
			if(frase[t] == '#'){
				aux = 1;
				continue;
			}
			if(aux == 0){
				grafo[i].v = atoi(frase);
				//printf("\n%s", frase);
				//printf("\n%d", grafo[i].v);
			}
		else if(aux == 1){
				aux2 = 0;
				contS = 0;
				for(j = 0; frase[j] != '\0'; j++){
					if(frase[j] == ' '){
						aux2 = 1;						
						contS = 0;
						continue;
					}
					if(aux2 == 0){
						num1S[contS] = frase[j];
						contS++;
					}
					else if(aux2 == 1){
						num2S[contS] = frase[j];
						contS++;
					}

				}
				num1S[2] = '\0';
				num2S[2] = '\0';

				num1 = atoi(num1S);
				num2 = atoi(num2S);
				// printf("\nS1: %d", num1);	
				// printf("\nS2: %d", num2);
				
				for(int k = 0; k < n; k++){
					if(grafo[k].v == num1){
						index1 = k;
					}
					if(grafo[k].v == num2){
						index2 = k;
					}
				}
				
				Grafo* new = (Grafo*) malloc(sizeof(Grafo));
				if(grafo[index1].prox != NULL){
					Grafo* p = (Grafo*) malloc(sizeof(Grafo));
					for(p->prox = grafo[index1].prox; p != NULL; p = p->prox){
						if(p->prox == NULL){
							p->prox = new;
							new->prox = NULL;
							new->v = index2;
						}
					}
				}else{
					new->prox = NULL;
					new->v = index2;
					grafo[index1].prox = new;
				}
			}
			i++;
		}	
		fclose(file);
		testarL(grafo, n);
	}
}

void lerArqPraMatriz(int n){
	FILE *file;
	file = fopen("grafo.txt", "r");
	if(file == NULL){
		printf("Arquivo n�o pode ser aberto!");
		system("pause");
		return;
		}
	else{
		char frase[100], num1S[3], num2S[3];
		int aux = 0, i = 0, aux2, contS, index1, index2, vetor[n], t, j, num1, num2, matriz[n][n];
		for(int l = 0; l < n; l++){
			for(int c = 0; c < n; c++){
				matriz[l][c] = 0;
			}
		}
		while(fgets(frase, 100, file) != NULL){ /*   */
			for(t = 0; frase[t] != '\0'; t++){
				if(frase[t] == '#'){
					break;
				}
			}
			if(frase[t] == '#'){
				aux = 1;
				continue;
			}
			if(aux == 0){
				vetor[i] = atoi(frase);
			}
		else if(aux == 1){
				aux2 = 0;
				contS = 0;
				for(j = 0; frase[j] != '\0'; j++){
					if(frase[j] == ' '){
						aux2 = 1;						
						contS = 0;
						continue;
					}
					if(aux2 == 0){
						num1S[contS] = frase[j];
						contS++;
					}
					else if(aux2 == 1){
						num2S[contS] = frase[j];
						contS++;
					}

				}
				num1S[2] = '\0';
				num2S[2] = '\0';

				num1 = atoi(num1S);
				num2 = atoi(num2S);

				for(int m = 0; m < n; m++){
					if(vetor[m] == num1){
						index1 = m;
					}
					if(vetor[m] == num2){
						index2 = m;
					}
				}

				matriz[index1][index2] = 1;
			}
			i++;
		}
		printf("\n     ");
		for(int i = 0; i < n; i++){
			printf("%d   ", i);
		}
		printf("\n");
		for(int l = 0; l < n; l++){
			printf("\n%d:", l);
			printf(" | ");
			for(int c = 0; c < n; c++){
				printf("%d", matriz[l][c]);
				printf(" | ");
			}
			printf("\n");
		}
		fclose(file);
	}
}

void hremove(Grafo* v){
	v = NULL;
}

void testar(Grafo* v, int n){
	for(int i = 0; i < n; i++){
		printf("\n%d", v[i].v);
	}
	printf("\n");
}

void testarL(Grafo* v, int n){
	Grafo* p;
	for(int i = 0; i < n; i++){
		if(v[i].prox != NULL){
			printf("\nPosition: %d", i);
			printf("---- %d", v[i].v);
			for(p = v[i].prox; p != NULL; p = p->prox){
				printf("\n%d", p->v);
			}
		}
	}
	printf("\n");
}