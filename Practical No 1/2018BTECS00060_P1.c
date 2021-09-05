//2018BTECS00060

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
// Beginning of parallel region
    #pragma omp parallel
    {
        printf("Hello World, PRN: 2018BTECS00060 from thread = %d\n", omp_get_thread_num());
    }
    return 0;
// Ending of parallel region
}
