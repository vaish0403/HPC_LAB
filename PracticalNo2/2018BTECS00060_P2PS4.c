//2018BTECS00060
//Addition of a scalar and a vector Work Sharing

#include <stdlib.h>  
#include <stdio.h>    
#include <omp.h>      


#define ARRAY_SIZE 8     
#define NUM_THREADS 4    

int main (int argc, char *argv[]) 
{
	int * a;
    int * b;   
    int n = ARRAY_SIZE;                 
	int n_per_thread;                   
	int total_threads = NUM_THREADS;    
	int i;       
    a = (int *) malloc(sizeof(int)*n);
        for(i=0; i<n; i++) {
            a[i] = i;
        }
    b = (int *) malloc(sizeof(int)*n);
        for(i=0; i<n; i++) {
            b[i] = i;
        }
	omp_set_num_threads(total_threads);
	
	
	n_per_thread = n/total_threads;
	#pragma omp parallel for shared(a, b) private(i) schedule(static, n_per_thread)
        for(i=0; i<n; i++) {
		a[i]=a[i]+5;
		printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
        }
	printf("i\tb[i]\t+\tX\t=\ta[i]\n");
        for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, b[i], 5 , a[i]);
        }
	
        // clean up memory
        free(a);  free(b);
	
	return 0;
}
