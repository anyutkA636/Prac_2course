#include <stdio.h>
#include <stdlib.h>

// allocating memory for an array
double ** dynamic_array_alloc(int M, int N)  
{
    int i;
    double **A = (double **) malloc (M * sizeof(double *));
    for (i = 0; i < M; i++)
        A[i] = (double *) malloc (N * sizeof(double));
    return A;
}

// deleting an array from memory
void dynamic_array_free(double **A, int M)  
{
    int i;
    for (i = 0; i < M; i++)
       free(A[i]);
    free(A);
}

// entering a matrix
void matrix_enter(double **A, int M, int N)  
{
    int i, j;
    for (i = 0; i < M; i++) 
        for (j = 0; j < N; j++) {
            scanf("%lf",  &A[i][j]);
    }
}

// matrix printing
void matrix_print(double **A, int M, int N)  
{
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++)
            printf("%6.2lf",  A[i][j]);
        printf("\n");
    }
}

// matrix transposition
double ** dynamic_matrix_transposition(double **A, int M, int N)
{
    int i, j;
    double **B = dynamic_array_alloc(N, M);
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            B[i][j] = A[j][i];
    return B;
}



int main ()
{
    int M, N;
    double **A, **B;
    printf("Enter M and N: ");
    if (scanf("%d %d", &M, &N) == 2) {
        A = dynamic_array_alloc(M, N);
        printf("Enter matrix: \n");
        matrix_enter(A, M, N);
        B = dynamic_matrix_transposition(A, M, N);

        //matrix_print(A, M, N);
        printf("The transposed matrix is: \n");
        matrix_print(B, N, M);
        dynamic_array_free(A, M);
        dynamic_array_free(B, N);
        
    }
    else
        printf("Incorrect_param\n");
  return 0;
}