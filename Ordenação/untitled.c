#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>

(unsigned int n);

int main(){
	int i;
	int n = 100;
	srand(time(NULL));
	for(i = 0; i < 10; i++){
		printf("%d\n", 3 + (srand() % (n-1) + n));
	}

	return 0;
}

