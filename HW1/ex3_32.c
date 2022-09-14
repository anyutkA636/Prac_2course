//3.32. Распечатать первые n простых чисел ( p - простое число, если
//p >= 2 и делится только на 1 и на себя).
#include <stdio.h>
int main(void)
{
int i, a, n, count, c;
printf("Enter n: ");
if (scanf("%d", &n) == 1) {
	a = 0;
	count = 0;
	while (count != n) {
		c = 0;
		a += 1;
		for (i = 1; i <= a; i++) {
			if (a % i == 0) {
				c += 1;
				if (c == 3) 
					break;
			}
		}
		if ((c == 2) || (c==1)) {
			count += 1;
			printf("%d\n", a);
		}
	}
}
else 
	printf("Incorect_param\n");
return 0;
}