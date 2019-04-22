#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void mergeSort(int v[], int s, int e);
void merge(int v[], int s, int m, int e);

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
			gettimeofday(&b, NULL);
			v = newv(n);
			mergeSort(v, 1, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
		}
		printf("%d %.10lf \n", n, tempo/n);
		free(v);
	}
	return 0;
}


void mergeSort(int v[], int s, int e){
	int m;
	if(s < e){
		m = (s + e)/2;
		mergeSort(v, s, m);x	x	
		mergeSort(v, m+1, e);
		merge(v, s, m, e);
	}
}

void merge(int v[], int s, int m, int e){
	int w[e - s + 1], i = s, j = m + 1, k = 1;
	while(k <= (e - s + 1)){
		if(((v[i] < v[j]) && (i <= m)) || (j > e)){
			w[k] = v[i];
			i++;
		}
		else{
			w[k] = v[j];
			j++;
		}
		k++;
	}
	k = 0;
	while(k <= e - s + 1){
		v[s + k - 1] = w[k];
		k++;
	}
}

int *newv(unsigned int n){
	int* v = (int*) malloc(n * sizeof(int));
	while(n--) v[n]=n;
	return v;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	