//пузырькова сортировка, bubble sort

#include <stdio.h>
int main(void)
{
int i, j, b, n = 5;
n -= 1;
int arr[] = {8, 4, 0, 3, 5};
for (i = n; i != 1; i--) {
	for (j = 0; j <= i - 1 ; j++) {
		if (arr[j] > arr[j + 1]) {
			b = arr[j + 1];
			arr[j + 1] = arr[j];
			arr[j] = b;
		}
	}
}
for (i = 0; i <= n; i++) {
printf("%d ", arr[i]);
}
return 0;
}