#include <stdio.h>
#include <pthread.h>
int A[10][10];
int B[10][10];
int C[10][10];
int c1,r1;
void *matrix_add(void *para) {
long id;
id=(long) para;
int i, j;
for (j = 0; j < c1; j++)
C[id][j] = A[id][j]+B[id][j];
pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
pthread_t thread[10];
int j;
long i;
printf("\nEnter no.of rows");
scanf("%d",&r1);
printf("\nEnter no.of columns");
scanf("%d",&c1);
printf("\nEnter matrix A\n");
for(i=0;i<r1;i++)
{
for(j=0;j<c1;j++)
{
printf("Enter A[%ld][%d] :",i,j);
scanf("%d",&A[i][j]);
}
}
printf("\nEnter matrix B\n");
for(i=0;i<r1;i++)
{
for(j=0;j<c1;j++)
{
printf("Enter B[%ld][%d] :",i,j);
scanf("%d",&B[i][j]);
}
}
for (i = 0; i < r1; i++) {
pthread_create(&thread[i],NULL, matrix_add,(void *)i);
}
for (i = 0; i < r1; i++)
pthread_join(thread[i], NULL);
printf("\nMatrix A\n");
for(i=0;i<r1;i++)
{
for(j=0;j<c1;j++)
{
printf("%d\t",A[i][j]);
}
printf("\n");
}
printf("\nMatrix B\n");
for(i=0;i<r1;i++)
{
for(j=0;j<c1;j++)
{
printf("%d\t",B[i][j]);
}
printf("\n");
}
printf("\nAddition of two matrices is\n");
for (i = 0; i < r1; i++){
for (j = 0; j < c1; j++){
printf("%d\t", C[i][j]);
}
printf("\n");
}
return 0;
}
