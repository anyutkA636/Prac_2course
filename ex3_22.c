//3.22. Определить, верно ли, что куб суммы цифр натурального числа n равен n^2
// такими числами являются 1 и 27

#include <stdio.h>

int main(void)
{
int n, i, j, sum, sq, cu;
printf("Enter N: ");
if (scanf("%d", &n) == 1) {
    //for (i = 1; i <= 1000; i++) {
    //n = i;
    i = n;
    sum = 0;
    while (n > 0) {
        if (n >= 10 && n % 10 != 0) {
            sum += n % 10;
            n /= 10;
        }
        else if (n % 10 == 0) {
            j = 10;
            while (n / j != 0)  
                j *= 10;
            j /= 10;
            n /= j;
        }
        else if (n < 10) {
            sum += n % 10;
            n = 0;
        }
    }
    sq = i * i;
    cu = sum * sum * sum;
    printf("Is the cube of the sum of digits of a natural number N equal to N^2?\n");
    if (sq == cu)
        printf("Yes, it is\n");
   else
        printf("No, it isn't\n");
    //}
}
else
    printf("Incorrect_param\n");
return 0;
}