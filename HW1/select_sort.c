//сортировка выбором, select sort

#include <stdio.h>
int main(void)
{
int i, j, max, n, h;
n = 5;
int arr[] = {8, 4, 230, 3, 80985};
n -= 1;
for (i = n; i >= 1; i--) {
	max = 0;
	for (j = 1; j <= i; j++) {
		if (arr[max] < arr[j]) 
			max = j;
	}
	h = arr[max];
	arr[max] = arr[i];
	arr[i] = h;
}
for (i = 0; i <= n; i++) 
	printf("%d ", arr[i]);
return 0;
}
