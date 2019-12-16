#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int MAT1[10][10];
int MAT2[10][10];
int MAT3[10][10];

int r1,c1,r2,c2;

struct v{
int i;
int j;};

void *thread_Multiply_Matrix(void *para)
{
int n,sum=0;
struct v *data=para;
for(n=0;n<c1;n++){
sum+=MAT1[data->i][n]*MAT2[n][data->j];
}
MAT3[data->i][data->j]=sum;
pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
pthread_t tid[20];
int iCount,jCount,kCount,i;
printf("Enter Number of Rows For Matrix 1 :");
scanf("%d",&r1);
printf("Enter Number of Columns For Matrix 1 :");
scanf("%d",&c1);
for(iCount=0;iCount<r1;iCount++)
{
for(jCount=0;jCount<c1;jCount++)
{
printf("Enter Mat1[%d][%d] :",iCount,jCount);
scanf("%d",&MAT1[iCount][jCount]);
}
}
printf("\n");
printf("Enter Numer of Rows For Matrix 2 :");
scanf("%d",&r2);
printf("Enter Number of Columns For Matrix 2 :");
scanf("%d",&c2);
for(iCount=0;iCount<r2;iCount++)
{
for(jCount=0;jCount<c2;jCount++)
{
printf("Enter Mat2[%d][%d] :",iCount,jCount);
scanf("%d",&MAT2[iCount][jCount]);
}
}
if(c1!=r2)
{
printf("Multipication of Matrix not Possible !!!");
}
else
{
for(iCount=0;iCount<r1;iCount=iCount+1)
{
for(jCount=0;jCount<c2;jCount=jCount+1)
{
MAT3[iCount][jCount]=0;
}
}
i=0;
for(iCount=0;iCount<r1;iCount=iCount+1)
{
for(jCount=0;jCount<c2;jCount++)
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
for(jCount=0;jCount<c2;jCount++)
{
pthread_join(tid[i++],NULL);
}
}
}

printf("\n Matrix 1 \n");
for(iCount=0;iCount<r1;iCount++)
{
for(jCount=0;jCount<c1;jCount++)
{
	printf("%d \t",MAT1[iCount][jCount]);
}
printf("\n");
}

printf("\n Matrix 2 \n");

for(iCount=0;iCount<r2;iCount++)
{
for(jCount=0;jCount<c2;jCount++)
{
printf("%d \t",MAT2[iCount][jCount]);
}
printf("\n");
}

printf("\n Multipication of Matrix ...\n");

for(iCount=0;iCount<r1;iCount++)
{
for(jCount=0;jCount<c2;jCount++)
{
	printf("%d \t",MAT3[iCount][jCount]);
}
printf("\n");
}
return 0;
}

