#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


typedef struct lista{
    int v;
    struct lista *prox;
}Lista;

typedef struct table{
    int elements;
    int size;
    struct lista **l;
}Table;

Lista* searchHash(Table* table, int v);
double tvtosec(struct timeval t);
int calcPosition(int tam, int v);
Lista* newList(int x);
void insertTable(Table* table, Lista* list);
void updateSizeTable(Table* table);
void testTable(Table* table);
void testList(Lista* list);
void freeTable(Table* table);
void freeList(Lista* list);
int myrand(int min, int max);

int main(void){    
    struct timeval a;
	struct timeval b;
    unsigned int n, i, k;
    double tempo;
    srand(time(NULL));
    Table table;
    table.l = malloc(sizeof(Lista*)*1);
    table.size = 1;
    table.elements = 0;
    for(n = 1; n <= 100; n = n + 1){
        
        for(k = 0; k < n; k++){
            insertTable(&table, newList(myrand(0, n)));
        }
		tempo = 0;
        for(i = 0; i <= n; i++){
            int m = myrand(0, n);
       		gettimeofday(&b, NULL);
            searchHash(&table, m);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
        freeTable(&table);
		fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		fprintf(stderr, "%d %.10lf \n", n, tempo/n);
    }
	return 0;
}

Lista* searchHash(Table* table, int v){
    Lista* list;
    for(int i = 0; i < table->size; i++){
        list = table->l[i];
        while(list != NULL){
            if(list->v == v){
                return list;
            }
            list = list->prox;
        }
    }
    return NULL;
}


void testTable(Table* table){
    for(int i = 0; i < table->size; i++){
        printf("\nChave %d: ", i);
        testList(table->l[i]);
    }
}

void testList(Lista* list){
    while(list!=NULL){
        printf("%d ", list->v);
        list = list->prox; 
    }
}


Lista* newList(int x){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->v = x;
    l->prox = NULL;
    return l;
}

void insertTable(Table* table, Lista* list){
    int position;
    if(table->elements > table->size){
        updateSizeTable(table);
    }
    position = calcPosition(table->size,list->v);
    if(table->l[position]==NULL){
        table->l[position] = list;
    }else{
        list->prox=table->l[position];
        table->l[position]=list;
    }
    table->elements++;

}

void updateSizeTable(Table* table){
        
    Table aux;
    int size = table->size * 2;
    aux.l = malloc(sizeof(Lista*)*(size));
    aux.size = size;
    aux.elements = 0;
    Lista* list;

    for(int i = 0; i < aux.size; i++){
        aux.l[i] = NULL;    
    }

    for(int j = 0; j < table->size; j++){
        list = table->l[j];
        while(list != NULL){
            Lista *lista = newList(list->v);
            int x = calcPosition(aux.size, list->v);
            if(aux.l[x] == NULL){
                aux.l[x] = lista;
            }else{
                lista->prox = aux.l[x];
                aux.l[x] = lista;
            }
            list = list->prox;
            aux.elements++;
        }    
    }
    freeTable(table);
    table->size = size;
    table->elements = aux.elements;
    table->l = aux.l;

}


int calcPosition(int tam, int v){
    return v%tam;
}

void freeTable(Table* table){
    for(int i = 0; i < table->size; i++){
        freeList(table->l[i]);
        table->l[i] = NULL;
    }
    table->elements = 0;
}

void freeList(Lista* list){
    Lista* aux;
    while(list != NULL){
        aux = list->prox;
        free(list);
        list = aux; 
    }
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}

double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}