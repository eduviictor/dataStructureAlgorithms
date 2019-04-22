#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
unsigned int sumx(int *v, unsigned int n, int x);
int *newv(unsigned int n);
int myrand(int min, int max);

int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n;
	double tempo;
	int *v;
	srand(time(NULL));
	for(n = 100; n <= 500; n++){
		tempo = 0;
		for(i = 0; i <= n; i++){
			gettimeofday(&b, NULL);
			v = newv(n);
			sumx(v, n, myrand(3, (n-1)+n));
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
		printf("%d %.10lf \n", n, tempo/n);
		free(v);
	}
	return 0;
}

int *newv(unsigned int n){
	int* v = (int*) malloc(n * sizeof(int));
	while(n--) v[n]=n;
	return v;
}


unsigned int sumx(int *v, unsigned int n, int x){
	unsigned int i, j;
	for(i = 1; i < n-1; i++){
		for(j = i + 1; j <= n; j++){
			if(v[j] + v[i] == x){
				return 0;
			}
		}
	}
	return 1;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}