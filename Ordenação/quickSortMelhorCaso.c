#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void quickSort(int v[], int s, int e);
int partition(int v[], int s, int e);
void testar(int v[], int n);
void fill(int v[], int s, int e);

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
			v = newv(n);
			fill(v, 0, n-1);
			testar(v, n);
			gettimeofday(&b, NULL);
			quickSort(v, 0, n - 1);
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

void testar(int v[], int n){
	int i;
	printf("\n--------\n");
	for(i = 0; i < n; i++){
		printf("%d\n", v[i]);
	}
	printf("\n-------\n");
}

void quickSort(int v[], int s, int e){
	int p;
	if(s < e){
		p = partition(v, s, e);
		quickSort(v, s, p - 1);
		quickSort(v, p + 1, e);
	}
}

int partition(int v[], int s, int e){
	int l = -1, i, aux;
	for(i = s; i < e; i++){
		if(v[i] < v[e]){
			aux = v[i];
			v[i] = v[l + 1];
			v[l + 1] = aux;
			l++;
		}
	}
	aux = v[e];
	v[e] = v[l + 1];
	v[l + 1] = aux;
	return l + 1;
}

void fill(int v[], int s, int e){
    int m = (s + e)/2;
	if(e-s+1 == 3){
		v[e] = m + 1;
        v[s] = m;
        v[s+1] = m + 2;
	}
	else if(e-s+1 > 3){
        fill(v, s, m-1);
        fill(v, m+1, e);
		v[m] = v[e]; 
        v[e] = m + 1;
	}
}



int *newv(unsigned int n){
	int* v = (int*) malloc(n * sizeof(int));
	return v;
}

int myrand(int min, int max){
	return min + rand() % (max - min + 1); 
}


double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}	