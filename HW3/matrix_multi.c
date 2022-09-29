#include <stdio.h>
#include <stdlib.h>


int vvod_arr (int *a, int m, int n)
{
  int i, j;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      {
	printf ("arr[%d][%d] = ", i, j);
	scanf ("%d", &a[i * n + j]);
      }
}

int print_arr (int *a, int m, int n)
{
  int i, j;
  for (i = 0; i < m; i++)
    {
      for (j = 0; j < n; j++)
	  printf ("%3d", a[i * n + j]);
      printf ("\n");
    }
}

int multi (int *A, int *B, int *C, int m, int n, int k)
{
  int i, j, h;
  for(i = 0; i < m; i++)
    for(j = 0; j < k; j++)
    {
        C[i * k + j] = 0;
        for(h = 0; h < n; h++)
            C[i * k + j] += A[i * n + h] * B[h * k + j];
    }
}

int main(int argc, char *argv[])
//int main (void)
{
  int n, m, k;
if (argc < 4) 
   printf("Incorrect_param\n");
else {
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  k = atoi(argv[3]);
  //scanf ("%d", &m);
  //scanf ("%d", &n);
  //scanf ("%d", &k);

  int A_arr[m][n], B_arr[n][k], C_arr[m][k];
  printf ("Enter array A:\n");
  vvod_arr ((int *) A_arr, m, n);
  
  printf ("Enter array B:\n");
  vvod_arr ((int *) B_arr, n, k);
  
  multi ((int *) A_arr, (int*)B_arr, (int*)C_arr, m, n ,k);
  
  //printf("Array A:\n");
  //print_arr((int*)A_arr, m, n);
  //printf("Array B:\n");
  //print_arr((int*)B_arr, n, k);
  
  printf("Array C:\n");
  print_arr((int*)C_arr, m, k);
 }
}
