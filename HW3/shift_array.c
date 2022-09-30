// shifting an array 

#include <stdio.h>

void shift(int *arr, int N, int M) // N = len_arr, M = shift_number
{
    int i, j, prev, suc, end;
    M %= N;
    if (M < 0)
        M += N;
    for (i = 0; i < M; i++) {
        end = arr[N - 1];
        prev = arr[0];
        for (j = 0; j < (N - 1); j++) {
            suc = arr[j + 1];
            arr[j + 1] = prev;
            prev = suc;
        }
        arr[0] = end;
    }
}

int main(void)
{
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    int i, M, N = sizeof(A) / sizeof(int);
    
    printf("Enter shift number: \n");
    if (scanf("%d", &M) == 1) {
        shift(A, N, M);
        
        for (i = 0; i < N; ++i)
            printf("%d ", A[i]);
        printf("\n");
    }
    else
        printf("Incorrect_param\n");
    return 0;
}