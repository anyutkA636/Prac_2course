//3.37. Вычислить с точностью eps > 0 значение числа e - предел последовательности { xi }при i → ∞
//xi = (1+1/i)i, i = 1, 2, ...
//Считать, что требуемая точность достигнута, если | xi - xi+1| < eps.

#include <stdio.h>
#include <math.h>
int main(void)
{
int n;
float x1, x2, y, eps;
printf("Enter eps: ");
if (scanf("%f", &eps) == 1) {
	x1 = -1;
	x2 = 1;
	n = 0;
	while ((x2 - x1) >= eps) {
		x1 = x2;
		n += 1;
		y = 1 + (float)1 / n;
		x2 = pow(y, n);
		//printf("x1 %f\n", x1);
		//printf("x2 %f\n", x2);
	}
	printf("Answer: %f\n", x2);
	}
else {
printf("Incorect_param\n");
}
return 0;
}