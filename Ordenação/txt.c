#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>


int verificaPrimo(int n);
double tvtosec(struct timeval t);

int main(void){
	struct timeval a;
	struct timeval b;
	int i, n;
	double tempo;

	for(i = 1; i <= 10; i++){
		scanf("%d", &n);
		gettimeofday(&a, NULL);
		verificaPrimo(n);
		gettimeofday(&b, NULL);
		tempo = tvtosec(b) - tvtosec(a);
		printf("%d %.20lf\n", n, tempo);
	}
	return 0;
}

int verificaPrimo(int n){
	int i;
	if(n > 1){
		for(i = 2; i < sqrt(n); i++){
			if(n % i == 0){
				return 1;
			}
		}
		return 0;
	}
	return 1;	
}

double tvtosec(struct timeval t){              
	return (double)t.tv_sec + t.tv_usec/(double)1e6;
}




//cc -wall prime.c -o prime
//./prime > out.txt