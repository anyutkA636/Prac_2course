//3.25. Для данного вещественного положительного числа a найти наименьшее целое
//положительное n такое, что 1 + 1/2 +1/3+ ... + 1/n > a.
#include <stdio.h>
int main(void)
{
float a, s;
int n;
printf("Enter: ");
if (scanf("%f", &a) == 1) {
	s = 1;
	n = 1;
	while (s <= a) {
		n += 1;
		s += (float)1/n;
		//printf("%f\n", s);
	}
	printf("Answer: %d\n", n);
}
else 
	printf("Incorect_param\n");
return 0;
}
