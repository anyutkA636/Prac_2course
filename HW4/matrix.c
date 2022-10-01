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
            printf("%7.3lf",  A[i][j]);
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

//search for the inverse matrix by the Gauss method
double ** dynamic_matrix_inverse(double **A, int M)
{
    int i, j, k, h;
    double coef, tmp;
    double **E = dynamic_array_alloc(M, M); // E is copy of A
    double **C = dynamic_array_alloc(M, M); 
    
    //Copy the matrix A to E, turn C into a single matrix
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            C[i][j] = 0;
            E[i][j] = A[i][j];
        }
        C[i][i] = 1;
    }
    // We bring the matrix to the upper diagonal form
    for (h = 0; h < M; h ++) {
        k = -1;
        //Looking for the first non-zero element in the column
        for (i = h; i < M; i++) 
            if (E[i][h] != 0) {
                k = i;
                break; 
            }
            
        if (k != -1) {
            //Swap the 0 and K lines in C and E
            if (k != h) {
                for (j = 0; j < M; j++) {
                    tmp = E[h][j];
                    E[h][j] = E[k][j];
                    E[k][j] = tmp;
                    tmp = C[h][j];
                    C[h][j] = C[k][j];
                    C[k][j] = tmp;
                }
            }
            
            if (k != -1) {
                for (i = 0; i < M; i++) {  // i = k
                    coef = E[i][h] / E[h][h];
                        for (j = 0; j < M; j++) {
                            if (i != h) {
                               E[i][j] -= E[h][j] * coef;
                               C[i][j] -= C[h][j] * coef;
                            }
                        }
                    }
            }
            
        }
        else {
            printf("There is no inverse matrix.\n");
            dynamic_array_free(E, M);
            dynamic_array_free(C, M);
            return 0;
        }
        
    }
    for (i = 0; i < M; i++) {
        for  (j = 0; j < M; j++) 
            C[i][j] /= E[i][i];
        E[i][i] = 1;
    }

    dynamic_array_free(E, M);
    return C;
}



int main ()
{
    int M, N, task;
    double **A, **B, **C;
    
    printf("Enter '1' - transpose, '2' - inverse matrix\n");
    if (scanf("%d", &task) == 1) {
        
        if (task == 1) {
            printf("Enter M and N: ");
            if ((scanf("%d %d", &M, &N) == 2) && M > 0 && N > 0) {
                A = dynamic_array_alloc(M, N);
                printf("Enter matrix: \n");
                matrix_enter(A, M, N);
                B = dynamic_matrix_transposition(A, M, N);
                printf("The transposed matrix is: \n");
                matrix_print(B, N, M);
                printf("\n");
                dynamic_array_free(B, N);
                dynamic_array_free(A, M);
            }   
            else
                printf("Incorrect_param\n");
        }
        
        else if (task == 2)
        printf("Enter M: ");
        if ((scanf("%d", &M) == 1) && M > 0) {
            A = dynamic_array_alloc(M, M);
            printf("Enter matrix: \n");
            matrix_enter(A, M, M);
            printf("The inverse matrix M*M is: \n");
            C = dynamic_matrix_inverse(A, M);
            matrix_print(C, M, M);
            dynamic_array_free(A, M);
            dynamic_array_free(C, M);
        }
        else
        printf("Incorrect_param\n");
    
    }
    else
        printf("Incorrect_param\n");
  return 0;
}
