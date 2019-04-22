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
	
	unsigned int n;
	n = 3;
	/*for(n = 100; n <= 1000; n = n + 100){
		tempo = 0;
		for(i = 0; i <= n; i++){
			
		}
		printf("%d %.10lf \n", n, tempo/n);
	}*/
	printf("%d\n", (0 + n-1)/2);
	return 0;
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i <= n; i++){
		v[i] = i;
	}
	return v;
}


int buscaBinaria(int v[], int x, int s, int e){
	int m;
	if(s <= e){
		m = ceil((s + e)/2);
		if(v[m] == x)
			return m;
		if(v[m] > x)
			return buscaBinaria(v, x, s, m-1);
		return buscaBinaria(v, x, m+1, e);}
	return -1;
}


