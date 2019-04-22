#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
int buscaBinaria(int v[], int x, int s, int e);

int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n, x = 2000;
	double tempo;
	int *v;
	for(n = 100; n <= 1000 ; n++){
		tempo = 0;
		for(i = 0; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			buscaBinaria(v, x, 0, n - 1);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
		printf("%d %.10lf \n", n, tempo/n);
		free(v);
	}
	return 0;
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = i;
	}
	return v;
}	
int buscaBinaria(int v[], int x, int s, int e){
	int i, m;
	if(s <= e){
		m = (s + e)/2;
		if(v[m] == x)
			return m;
		if(v[m] > x)
			return buscaBinaria(v, x, s, m-1);
		return buscaBinaria(v, x, m+1, e);}
	return -1;
}



int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	