#include<stdlib.h>
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int a[10][10],b[10][10],c[10][10]; // variables to store allocated memory
	int a_r,a_c,b_r,b_c, nthreads, tid, chunk =10; //variables to input matrixsize and variables to be used by OpenMP functions
	int i,j; // variables to be used in for loops togenerate matrices
	printf("\nenter rows and columns for matrix one:");
	scanf("%d%d",&a_r,&a_c);
	printf("\nenter rows and columns for matrix two:");
	scanf("%d%d",&b_r,&b_c);
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
	////// initializing second matrix
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
	for(i =0;i<a_r; i++)
	{
		for(j=0;j< b_c; j++)
		{
			c[i][j]=0;
		}
	}
	#pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j)
	{
		tid=omp_get_thread_num();
		if(tid==0)
		{
			nthreads=omp_get_num_threads();
		}
		#pragma omp for schedule (static)
		for(i=0;i<a_r; i++)
		{
			printf("Thread=%d did row=%d\n",tid,i);
			for(j=0;j<a_c; j++)
			{
				c[i][j]=a[i][j]+b[i][j];
			}
		}
	}
	printf("\nAfter addition\n");
	for(i=0;i<a_r;i++)
	{
		for(j=0;j<b_c;j++)
		{
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
}
