//3_17
#include <stdio.h>
#include <math.h>
int main(void)
{ 
	double a, b, c, d, x1, x2;
	printf("Enter a, b, c:\n");
	if (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
		if (a != 0) {
			d = b*b - 4*a*c;
			if (d == 0) {
				x1 = (-b)/(2*a);
				printf("Answer: %lf\n", x1);
			}
			else if (d > 0) {
				x1 = (-b + sqrt(d))/(2*a);
				x2 = (-b - sqrt(d))/(2*a);
				printf("Answer: %lf, %lf\n", x1, x2);
			}
			else {
				x1 = (-b)/(2*a);
				x2 = sqrt(-d)/(2*a);
				printf("Answer: %lf +- %lf*i\n", x1, x2);
			}
		}
		else
			printf("Not a quadratic equation\n");
	}
	else 
		printf("Incorrect_param");	

return 0;
} 