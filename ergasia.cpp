#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10

 int main(void)
 {
 	int array1[ROWS][COLS], array2[ROWS][COLS], array3[ROWS][COLS],array4[ROWS][COLS], array5[ROWS][COLS];
 	int i,j,a;
 	int M, N, K, L;
 	int sum=0;
 	
 	printf ("Enter the rows and columns of matrix A(M,N):");
 	scanf("%d, %d", &M,& N);
 	
 	printf ("Enter the rows and columns of matrix B(K,L):");
 	scanf("%d, %d", &K, &L);
	 
	 srand(time(NULL));
	
	 
	 
	 for(i=0; i<M; i++)
	 	for(j=0; j<N; j++)
		 	array1[i][j]=rand()%5;	
		 	
		 
	 for(i=0; i<K; i++)
	 	for(j=0; j<L; j++)
		 	array2[i][j]=rand()%5;
 	
 	printf("matrix A:\n");
 	for(i=0; i<M; i++)
    {
	 	for(j=0; j<N; j++)
	 		printf(" %2d", array1[i][j]);
	 	printf("\n");
	}
	
	printf("matrix B:\n");
 	for(i=0; i<K; i++)
    {
	 	for(j=0; j<L; j++)
	 		printf(" %2d", array2[i][j]);
	 	printf("\n");
	}
	
	if(M==K && N==L)
	{

 	for(i=0; i<M; i++)
    {
	 	for(j=0; j<N; j++)
	 	{
		 	array3[i][j]=array1[i][j]+ array2[i][j];
		}
	}
	
	for(i=0; i<M; i++)
    {
	 	for(j=0; j<N; j++)
	 	{
		 	array4[i][j]=array1[i][j]- array2[i][j];
		}
	}
	
	printf("matrix of sum:\n");
	for(i=0; i<M; i++)
    {
	 	for(j=0; j<N; j++)
	 		printf(" %2d", array3[i][j]);
	 	printf("\n");
	}
	
	printf("matrix of substraction:\n");
	for(i=0; i<M; i++)
    {
	 	for(j=0; j<N; j++)
	 		printf(" %2d", array4[i][j]);
	 	printf("\n");
	}
	}
	
	
	
	
	if(N==K)
	{
	
	for(i=0; i<M; i++)
	{
		for(j=0; j<L; j++)
		{
			for(a=0; a<K; a++)
			{
				sum+=array1[i][a]*array2[a][j];
			}
		array5[i][j]=sum;
		sum=0;		
		}
	}
	

	printf("matrix of multiplication:\n");
	for(i=0; i<M; i++)
    {
	 	for(j=0; j<L; j++)
	 		printf(" %2d", array5[i][j]);
	 	printf("\n");
	}

 }
 	
	 return 0;
 		
 }
