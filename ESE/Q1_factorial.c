#include <omp.h>
#include <stdio.h>

int main(void){
	int i,n;
	long long int fac=1;
	printf("\nEnter Number:");
	scanf("%d",&n);
	#pragma omp parallel for shared(n) private(i) reduction(*:fac)
	for(i=1;i<=n;i++)
	{
		fac*=i; 
		printf("multiplication done by %d\n",omp_get_thread_num());
	}
	printf("factorial of %d = %lld\n",n,fac);
	return 0;
}
