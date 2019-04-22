#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void quickSort(int v[], int s, int e);
int partition(int v[], int s, int e);
void bbsort(int v[], int n);

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
		for(i = 1; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			bbsort(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			free(v);
		}
		printf("%d %.10lf \n", n, tempo/n);
		
	}
	return 0;
}

void bbsort(int v[], int n){
	int i, j, aux;
	for(i = 0; i < n - 1; i++){
		for(j = 0; j < n - i; j++){
			if(v[j] > v[j + 1]){
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
		}
	}
}

int *newv(unsigned int n){
	int i, j = n;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i > n; i++){
		v[i] = j;
		j--;
	}
	return v;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	