#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

double tvtosec(struct timeval t);
int *newv(unsigned int n);
int myrand(int min, int max);
void testar(int v[], int n);
bool sorted(int v[], int n);
void bogoSort(int v[], int n);
void shuffle(int v[], int n);

int main(/*int argc, char **argv*/){
	/*double p = atof(argv[1]);*/
	struct timeval a;
	struct timeval b;
	unsigned int i, n;
	double tempo;
	int *v;
	srand(time(NULL));
	for(n = 3; n <= 10; n++){
		tempo = 0;
		for(i = 1; i <= n; i++){
			v = newv(n);
			gettimeofday(&b, NULL);
			bogoSort(v, n);
			gettimeofday(&a, NULL);
			tempo += tvtosec(a) - tvtosec(b);
			free(v);
		}
		fprintf(stdout, "%d %.10lf \n", n, tempo/n);
		fprintf(stderr, "%d %.10lf \n", n, tempo/n);	
	}
	return 0;
}

void bogoSort(int v[], int n){
    while(sorted(v, n) != true){
        shuffle(v, n);
    }

}
bool sorted(int v[], int n){
    for(int i = 0; i < n - 1; i++){
        if(v[i] > v[i + 1]){
            return false;
        }
    }
    return true;
}
void shuffle(int v[], int n){
    for(int i = 0; i < n; i++){
        int j = myrand(0, n - 1);
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

int *newv(unsigned int n){
	int i;
	int* v = (int*) malloc(n * sizeof(int));
	for(i = 0; i < n; i++){
		v[i] = myrand(0, 100);
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
