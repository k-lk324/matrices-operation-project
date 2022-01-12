#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10

void sum_matrix(int matrix1, int matrix2, int matrix3, int m, int n);
void substraction_matrix(int matrix1, int matrix2, int matrix4, int m, int n);
void multiplication_matrix(int matrix1, int matrix2, int matrix5, int m, int n);

int main(void)
{
	int matrix1[ROWS][COLS], matrix2[ROWS][COLS], matrix3[ROWS][COLS];
 	int i,j;
 	int M=2, N=2, K=2, L=2;
 	int a,b;
 	
 	
	srand(time(NULL));
	
	 /*ÔÕ×ÁÉÁ ÁÑ×ÉÊÏÐÏÉÇÓÇ ÓÔÏÉ×ÅÉÙÍ*/
	 
	for(i=0; i<M; i++)
	 	for(j=0; j<N; j++)
		 	matrix1[i][j]=rand()%5;	
		 	
	for(i=0; i<K; i++)
	 	for(j=0; j<L; j++)
		 	matrix2[i][j]=rand()%5;
	
	
	
	sum_matrix( matrix1,  matrix2,  matrix3, M, N);
	substraction_matrix( matrix1,  matrix2,  matrix4, M, N);
	multiplication_matrix( matrix1,  matrix2,  matrix5, M, N);

	
	printf("Matrix of sum:\n");
		for(i=0; i<M; i++)
    	{
	 		for(j=0; j<N; j++)
	 			printf(" %2d", matrix3[i][j]);
	 	printf("\n");
		}
	printf("\n");
	printf("Matrix of substraction:\n");
		for(i=0; i<M; i++)
    	{	
		 	for(j=0; j<N; j++)
	 			printf(" %2d", matrix4[i][j]);
	 		printf("\n");
		}
		
		
	ptintf("\n");
	printf("Matrix of multiplication:\n");
		for(i=0; i<M; i++)
    	{
		 	for(j=0; j<L; j++)
	 			printf(" %2d", matrix5[i][j]);
	 		printf("\n");
		}
		
		
	printf("\n");
	printf("Inverse matrix A");
	for(i=0; i<M; i++)
    	{	
		 	for(j=0; j<N; j++)
		 		matrix6[i][j]=matrix1[j][i];
		
		}
		for(i=0; i<M; i++)
    	{	
		 	for(j=0; j<N; j++)
		 		printf(" %2d", matrix6[i][j]);
	 		printf("\n");
		}
}

void sum_matrix(int matrix1, int matrix2, int matrix3, int m, int n)
{
	int i,j;
	
	for(i=0; i<m; i++)
    	{
	 		for(j=0; j<n; j++)
	 		{
		 		matrix3[i][j]=matrix1[i][j]+matrix2[i][j];
			}
		}
	
	
}

void substraction_matrix(int matrix1, int matrix2, int matrix4, int m, int n)
{
	int i,j;
	
	for(i=0; i<m; i++)
    	{
	 		for(j=0; j<n; j++)
	 		{
		 		matrix3[i][j]=matrix1[i][j]-matrix2[i][j];
			}
		}
	
	
}

void multiplication_matrix(int matrix1, int matrix2, int matrix5, int m, int n)
{
	int i,j,a;
	
	for(i=0; i<M; i++)
		{
			for(j=0; j<L; j++)
			{
				for(a=0; a<K; a++)
				{
					sum+=matrix1[i][a]*matrix2[a][j];
				}
				matrix5[i][j]=sum;
				sum=0;		
			}
		}
	

}
