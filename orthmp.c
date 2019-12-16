#include<stdlib.h>
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
int a[10][10],b[10][10],c[10][10]; // variables to store allocated memory
int a_r,a_c, nthreads, tid; //variables to input matrixsize and variables to be used by OpenMP functions
int i,j,k; // variables to be used in for loops togenerate matrices
printf("\nenter rows and columns for matrix one:");
scanf("%d%d",&a_r,&a_c);
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
// initializing second matrix
for(i=0;i<a_r; i++)
{
for(j=0;j<a_c; j++)
{
b[i][j]=0;
}
}
//*initialize product matrix */
for(i=0;i<a_r; i++)
{
for(j=0;j< a_c; j++)
{
c[i][j]=0;
}
}
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
{
tid=omp_get_thread_num();
if(tid==0)
{
nthreads = omp_get_num_threads();
}
//iinitializing first matrix
#pragma omp for schedule(static)
for(i=0;i<a_r;i++)
{
printf("Thread=%d did row=%d\n",tid,i);
for(j=0;j<a_c;j++)
{
b[j][i]=a[i][j];
}
}
#pragma omp for schedule(static)
for(i=0;i<a_r; i++)
{
printf("Thread=%d did row=%d\n",tid,i);
for(j=0;j<a_c; j++)
{
for(k=0;k<a_c; k++)
{
c[i][j]=c[i][j]+a[i][k]*b[k][j];
}
}
}
}
printf("\nAfter multiplication\n");
for(i=0;i<a_r;i++)
{
for(j=0;j<a_c;j++)
{
printf("%d\t",c[i][j]);
}
printf("\n");
}
for ( i = 0 ; i< a_r; i++ )
{
for ( j= 0 ; j< a_c; j++ )
{
if ( i== j)
{
if ( c[i][j] != 1 )
break;
}
else
{
if (c[i][j] != 0 )
break;
}
}
if ( j!= a_r )
break;
}
if ( i != a_r )
printf("Matrix is not orthogonal.\n");
else
printf("Matrix is orthogonal.\n");
return 0;
}
