#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
int coutingSort(int v[], int n);
void testar(int v[], int n);

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
			gettimeofday(&b, NULL);
			v = newv(n);
			*v = coutingSort(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			testar(v, n);
			return 0;
			free(v);
		}
		printf("%d %.10lf \n", n, tempo/n);
		
	}

	return 0;
}

int coutingSort(int v[], int n){
	int i, j, *c, *w;
	c = newv(n);
	for(i = 0; i < n - 1; i++){
		c[i] = 0;
 		for(j = 0; j < n - 1; j++){
			if(v[j] > v[i]){
				c[i] = c[i] + 1;
			}
		}
	}
	w = newv(n);
	for(i = 0; i < n - 1; i++){
		w[c[i] + 1] = v[i];
	}
	testar(w, n);
	return *w;
}


int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = myrand(0, n);
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