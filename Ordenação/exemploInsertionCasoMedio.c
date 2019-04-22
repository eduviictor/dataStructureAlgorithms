#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void insertionSort(int original[], int length);
void insertionSortJP(int v[], int n);
int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n;
	double tempo;
	int *v;
	srand(time(NULL));
	for(n = 100; n <= 1000; n = n + 100){
		tempo = 0;
		for(i = 0; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			insertionSortJP(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			free(v);
		}
		printf("%d %.10lf \n", n, tempo/n);
		
	}
	return 0;
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = myrand(0, n);
	}
	return v;
}

/*void insertionSort(int original[], int length) {
	int i, j, atual;
	for (i = 1; i < length; i++) {
		atual = original[i];
		for (j = i - 1; (j >= 0) && (atual < original[j]); j--) {						
        	original[j+1] = original[j];												
        }
		original[j+1] = atual;
	}
}*/




void insertionSortJP(int v[], int n){
	int i = 0, j, aux;
	while(i <= n){
		j = i;
		while((j > 1) && (v[j] < v[j-1])){							/*Melhor Caso: T(n): C1 + nC2 + (n-1)(C3 + C4 + C10)*/
			aux = v[j];	
			v[j] = v[j-1];
			v[j-1] = aux;
			j--;
		}
		i++;
	}
}



int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}