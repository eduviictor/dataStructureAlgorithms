#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int *zeros(unsigned int n);
int myrand(int min, int max);
int *distributionSort(int v[], int n);
int min(int v[], int n);
int max(int v[], int n);
void testar(int v[], int n);
int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n;
	double tempo;
	int *v;
	srand(time(NULL));
	for(n = 100; n <= 2000; n = n + 200){
		tempo = 0;
		for(i = 0; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			v = distributionSort(v, n);
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

int *distributionSort(int v[], int n){
	int maior = max(v, n);
	int i, k = maior + 1;
	int *w = zeros(k);
	int *y = zeros(n);
	for(i = 0; i < n; i++){
		w[v[i]]++;
	}
	for(i = 1; i < k; i++){
		w[i] += w[i - 1];
	}
	for(i = 0; i < n; i++){
		y[w[v[i]] - 1] = v[i];
		w[v[i]]--;
	}
	return y;
}

int max(int v[], int n){
	int i, maior = v[0];
	for(i = 0; i < n; i++){
		if(v[i] > maior){
			maior = v[i];
		}
	}
	return maior;
}

int min(int v[], int n){
	int i, menor = v[0];
	for(i = 0; i < n; i++){
		if(v[i] < menor){
			menor = v[i];
		}
	}
	return menor;
}


int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = myrand(0, n);
	}
	return v;
}

int *zeros(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = 0;
	}
	return v;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	