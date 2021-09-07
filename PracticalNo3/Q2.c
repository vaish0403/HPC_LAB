//2018BTECS00060
/*	Problem Statement 2 : 
    Write a code in OpenMP for multiplication of 2D Matrix and a 1D vector 
    (Demonstrate the use of different clauses wherever applicable), 
    vary the size of your matrices from 200, 1000, 2000 and 3000 
    and measure the runtime with one thread 
    (Use functions in C in calculate the execution time or use GPROF) For each matrix size,
    change the number of threads from 2,4,8., 
    and plot the speedup versus the number of threads. 
    Explain whether or not the scaling behaviour is as expected.
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//(1xn) * (nxm) = (1xm)  
//size of resultant matrix - 1xm
#define N 10 /* number of rows in matrix A */
#define M 500 /* number of columns in matrix B */

int main (int argc, char *argv[])
{
    int tid, nthreads, i, j, k;
	double time = omp_get_wtime();

    //1d vector - a
    //2d matrix - b
    //resultant 1d vector - c
    int a[N], b[N][M], c[M];
    
    //omp_set_num_threads(10);

    #pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
        }

        //Initialize matrices 
        #pragma omp for
            for (i=0; i<N; i++)
               a[i] = i;
        
        #pragma omp for
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    b[i][j]= i*j;
         
        #pragma omp for
            for (i=0; i<M; i++)
                c[i]= 0;

        #pragma omp for
            for (i=0; i<M; i++)
            {
                printf("Thread=%d did row=%d\n",tid,i);
                for(j=0; j<N; j++)
                {
                    c[i] += a[j] * b[j][i];
                }
            }
     }

    printf("\n1D Vector :\n");
    for (i=0; i<N; i++)
    {
        printf("%d    ", a[i]);
    }
    printf("\n");
    
    printf("\n2D matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%d    ", b[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Resultant vector:\n");
    for (i=0; i<M; i++)
    {
        printf("%d    ", c[i]);
    }
    printf("\n");
    
   
	printf ("\nTime Taken %f Seconds",omp_get_wtime() - time); 
	printf("\nUsing %d Threads",omp_get_max_threads());
  
    return(0);
}
