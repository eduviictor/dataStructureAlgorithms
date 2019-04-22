#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void insertionSort(int v[], int n);
void testar(int v[], int n);
int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n;
	double tempo;
	int *v;
	for(n = 100; n <= 2000; n = n + 200){
		tempo = 0;
		for(i = 0; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			insertionSort(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			free(v);
		}
		fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		fprintf(stderr, "%d %.10lf \n", n, tempo/n);
		
	}
	return 0;
}

void testar(int v[], int n){
	int i;
	printf("\n--------\n");
	for(i = 0; i < n; i++){
		printf("%d\n", v[i]);
	}
	printf("\n-------\n");
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = i;
	}
	return v;
}

void insertionSort(int v[], int n){
	int i = 0, j, aux;
	while(i < n){
		j = i;
		while((j > 1) && (v[j] < v[j-1])){							
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