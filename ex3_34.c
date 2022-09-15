//3.34. Распечатать первые n чисел Фибоначчи ( f0 = 1; f1 = 1; fk+1 = fk-1+ fk;
//k = 1, 2, 3,...) 

#include <stdio.h>

int n;

int fib(int n) {
    if (n == 1 || n == 2) 
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main(void) 
{
printf("Enter N: ");
if (scanf("%d", &n) == 1) 
    for (int i = 1; i <= n; i++)
        printf("%d\n", fib(i));
else
    printf("Incorrect_param\n");
return 0;  
}