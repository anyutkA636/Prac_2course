//3.18. Подсчитать количество натуральных чисел n ( 111 ≤ n ≤ 999 ), в
//записи которых есть две одинаковые цифры. 

#include <stdio.h>
int main(void)
{
int i, n, c, flag;
printf("Enter: ");
if (scanf("%d", &n) == 1) {
    c = 0;
    for (i = 111; i <= n; i++) {
        if (i % 10 == i / 100 || i % 10 == ((i / 10) % 10) || i / 100 == ((i / 10) % 10)) {
            c ++;
            //printf("%d\n", i);
        }
    }
    printf("Answer: %d\n", c);
}
else 
    printf("Invalid_param\n");
return 0;    
}