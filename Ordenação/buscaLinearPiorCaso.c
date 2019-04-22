#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
int buscaLinear(int v[], int n, int x);

int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n, x = 10000;
	double tempo;
	int *v;
	for(n = 100; n <= 10000; n = n + 100){
		tempo = 0;
		for(i = 0; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			buscaLinear(v, n, x);
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
		v[i] = i;
	}
	return v;
}

int buscaLinear(int v[], int n, int x){
	int i;
	for(i = 0; i < n; i++){
		if(v[i] == x){
			return i;
		}
	}
	return -1;
}



int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	