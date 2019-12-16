#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>
int A[10][10];
int B[10][10];
int C[10][10];
int c1,r1;
void *matrix_tran(void *para) {
long id;
id=(long) para;
int i, j;
for (j = 0; j < c1; j++)
C[j][id] = A[id][j];

pthread_exit(NULL);
}
struct v{
int i;
int j;};
void *thread_Multiply_Matrix(void *para)
{
int n,sum=0;
struct v *data=para;
for(n=0;n<c1;n++){
sum+=A[data->i][n]*C[n][data->j];
}
B[data->i][data->j]=sum;
pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
pthread_t thread[10],tid[20];
int j,iCount,jCount,c,d;
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
for (i = 0; i < r1; i++) {
pthread_create(&thread[i],NULL, matrix_tran,(void *)i);
}
for (i = 0; i < r1; i++)
pthread_join(thread[i], NULL);
for(iCount=0;iCount<r1;iCount=iCount+1)
{
for(jCount=0;jCount<c1;jCount=jCount+1)
{
B[iCount][jCount]=0;
}
}
i=0;
for(iCount=0;iCount<r1;iCount=iCount+1)
{
for(jCount=0;jCount<c1;jCount++)
{
struct v *data=(struct v*)malloc(sizeof(struct v));
data->i=iCount;
data->j=jCount;
pthread_create(&tid[i++],NULL,thread_Multiply_Matrix,(void *)data);
}
}
i=0;
for(iCount=0;iCount<r1;iCount++)
{
for(jCount=0;jCount<c1;jCount++)
{
pthread_join(tid[i++],NULL);
}
}
for(c=0;c<r1;c++){
for(d=0;d<c1;d++){
printf("%d\t",B[c][d]);
}
printf("\n");
}
for ( c = 0 ; c < r1; c++ )
{
for ( d = 0 ; d < c1; d++ )
{
if ( c == d )
{
if ( B[c][d] != 1 )
break;
}
else
if (B[c][d] != 0 ){
break;
}
}
if ( d != r1 )
break;
}
if ( c != r1 )
printf("Matrix is not orthogonal.\n");
else
printf("Matrix is orthogonal.\n");
return 0;
}

