
//2018BTECS00060

//Analyse and implement a Parallel code for below programs using OpenMP considering synchronization requirements. 
//Fibonacci Computation (Using Dynamic Programming)


#include<stdio.h>
#include<omp.h>

int fib(int n)
{
    /* Declare an array to store Fibonacci numbers. */
    int f[n+2]; // 1 extra to handle case, n = 0
    int i;
    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = 0;
    f[1] = 1;
    #pragma omp ordered
        for (i = 2; i <= n; i++)
        {
            f[i] = f[i-1] + f[i-2];
        }
     return f[n];
}

int main ()
{
    // int n = 9;
	int n;
    printf("Enter a number : ");
    scanf("%d",&n);
    printf("%dth fibonacci number is : %d\n", n, fib(n));
    // getchar();
    return 0;
}
