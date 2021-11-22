%%writefile cuda81oti.cu
#include<stdio.h>
#include<cuda.h>
#define row1 2 /* Number of rows of first matrix */
#define col1 3 /* Number of columns of first matrix */
#define row2 3 /* Number of rows of second matrix */
#define col2 2 /* Number of columns of second matrix */
__global__ void matproductsharedmemory(int *l,int *m, int *n)
{
int x=blockIdx.x;
int y=blockIdx.y;
__shared__ int p[col1];
int i;
int k=threadIdx.x;
n[col2*y+x]=0;
p[k]=l[col1*y+k]*m[col2*k+x];
__syncthreads();
for(i=0;i<col1;i++)
n[col2*y+x]=n[col2*y+x]+p[i];
}
int main()
{
int a[row1][col1]={1,2,3,4,5,6};
int b[row2][col2]={1,2,3,4,5,6};
int c[row1][col2];
int *d,*e,*f;
int i,j;
cudaMalloc((void **)&d,row1*col1*sizeof(int));
cudaMalloc((void **)&e,row2*col2*sizeof(int));
cudaMalloc((void **)&f,row1*col2*sizeof(int));
cudaMemcpy(d,a,row1*col1*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(e,b,row2*col2*sizeof(int),cudaMemcpyHostToDevice);
dim3 grid(col2,row1);
/* Here we are defining two dimensional Grid(collection of blocks) structure. Syntax is
dim3 grid(no. of columns,no. of rows) */
matproductsharedmemory<<<grid,col1>>>(d,e,f);
cudaMemcpy(c,f,row1*col2*sizeof(int),cudaMemcpyDeviceToHost);
printf("\n Product of two matrices:\n ");
for(i=0;i<row1;i++)
{
for(j=0;j<col2;j++)
{
printf("%d\t",c[i][j]);
}
printf("\n");
}
cudaFree(d);
cudaFree(e);
cudaFree(f);
return 0;
}
