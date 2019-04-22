#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
int *countingSort(int v[], int n);
void testar(int v[], int n);
int *zeros(unsigned int n);

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
		for(i = 1; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			v = countingSort(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			free(v);
		}
		fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		fprintf(stderr, "%d %.10lf \n", n, tempo/n);	
	}
	return 0;
}

int *countingSort(int v[], int n){
	int i, j, *c, *w;
	c = zeros(n);
	for(i = 0; i < n; i++){
 		for(j = 0; j < n; j++){
			if(v[j] < v[i]){
				c[i] = c[i] + 1;
			}
		}
	}
	w = zeros(n);
	for(i = 0; i < n; i++){
		w[c[i]] = v[i];
	}
	return w;
}

int *zeros(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = 0;
	}
	return v;
}


int *newv(unsigned int n){
	int i, j = n;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = j;
		j--;
	}
	return v;
}

void testar(int v[], int n){
	int i;
	printf("\nTESTE\n");
	for(i = 0; i < n; i++){
		printf("%d\n", v[i]);
	}
	printf("\nFIMTESTE\n");
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	