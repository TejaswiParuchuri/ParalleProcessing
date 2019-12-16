#include<stdlib.h>
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
int a[10][10],b[10][10],c[10][10]; // variables to store allocated memory
int a_r,a_c,b_r,b_c,nthreads,tid,chunk;
int i,j,k; // variables to be used in for loops togenerate matrices
again:
printf("\nenter rows and columns for matrix one:");
scanf("%d%d",&a_r,&a_c);
printf("\nenter rows and columns for matrix two:");
scanf("%d%d",&b_r,&b_c);
if(a_c!=b_r )
/*** Do matrix multiply sharing iterations on outer loop ***/
/*** Display who does which iterations for demonstration purposes ***/
for(i=0;i<a_r; i++)
{
printf("\ncan not multiply");
goto again;
}
printf("Initializing matrices...\n");
printf("Hello\n");
/*** Spawn a parallel region explicitly scoping all variables ***/
//iinitializing first matrix
printf("\nEnter matrix A\n");
for(i=0;i<a_r; i++)
{
for(j=0;j<a_c; j++)
{
printf("A[%d][%d]",i,j);
scanf("%d",&a[i][j]);
printf("\n");
}
}
//// initializing second matrix
printf("\nEnter matrix B\n");
for(i=0;i<b_r; i++)
{
for(j=0;j<b_c; j++)
{
printf("B[%d][%d]",i,j);
scanf("%d",&b[i][j]);
printf("\n");
}
}
/*initialize product matrix */
for(i=0;i<a_r; i++)
{
for(j=0;j< b_c; j++)
{
c[i][j]=0;
}
}
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k)
{
tid=omp_get_thread_num();
if(tid==0)
{
nthreads = omp_get_num_threads();
}
//iinitializing first matrix
#pragma omp for schedule (static)
for(i=0;i<a_r; i++)
{
printf("Thread=%d did row=%d\n",tid,i);
for(j=0;j<a_c; j++)
{
for(k=0;k<b_c; k++)
{
c[i][j]=c[i][j]+a[i][k]*b[k][j];
}
}
}
}
printf("\nAfter multiplication\n");
for(i=0;i<a_r;i++)
{
for(j=0;j<b_c;j++)
{
printf("%d\t",c[i][j]);
}
printf("\n");
}
}
