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
			mergeSort(v, 0, n - 1);
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

void mergeSort(int v[], int s, int e){
	int m;
	if(s < e){
		m = (s + e)/2;
		mergeSort(v, s, m);
		mergeSort(v, m+1, e);
		merge(v, s, m, e);
	}
}

void merge(int v[], int s, int m, int e){
	int i = s, j = m + 1, k = 0;
	int* w = (int*)malloc((e - s + 1) * sizeof(int));
	while(k < (e - s + 1)){
		if((v[i] < v[j]) && ((i <= m) || (j > e))){
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
	while(k < (e - s + 1)){
		v[s + k] = w[k];
		k++;
	}
	free(w);
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = myrand(0, n);
	}
	return v;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	