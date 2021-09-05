//2018BTECS00060
//Addition of 2 vectors SPMD

#include <stdlib.h>  
#include <stdio.h>    
#include <omp.h>      
#define ARRAY_SIZE 8     
#define NUM_THREADS 4    

int main (int argc, char *argv[]) 
{
	int * a;
	int * b; 
	int * c;
        
    int n = ARRAY_SIZE;                                   
	int total_threads = NUM_THREADS;    
	int i;       
    a = (int *) malloc(sizeof(int)*n);
	b = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);
    for(i=0; i<n; i++) {
        a[i] = i;
    }
    for(i=0; i<n; i++) {
        b[i] = i;
    }   
	omp_set_num_threads(total_threads);
	#pragma omp parallel
	{
		int id,i,Nthrds,istart,iend;
		id=omp_get_thread_num();
		Nthrds=omp_get_num_threads();
		istart=id*n/Nthrds;
		iend=(id+1)*n/Nthrds;
		if(id==Nthrds-1)iend=n;
		for(i=istart;i<iend;i++)
		{
			c[i]=b[i]+a[i];
		}
	} 
	printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");
        for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
        }
    free(a);  free(b); free(c);
	
	return 0;
}

