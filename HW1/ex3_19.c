//3_19
#include <stdio.h>
int main()
{
int n, a, d1, d2, d3, c;
printf("Enter n:\n");
	if (scanf("%d", &n) == 1) {
		c = 0;
		for (a = 100; a <= n; a++) {
			d3 = a % 10;
			d2 = (a % 100) / 10;
			d1 = a / 100;
			//printf("%d %d %d\n", d1, d2, d3);
			if (d1 != d2) {
				if (d1 != d3) {
					if (d2 != d3) 
						c += 1;
	
				}
			}
		}
	printf("%d", c);
	}
	else 
		printf("Incorrect_param");	
return 0;
}