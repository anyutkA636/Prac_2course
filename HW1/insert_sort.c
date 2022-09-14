//сортировка вставками, insert sort

#include <stdio.h>
int main(void)
{
int i, j, key, n, h;
n = 5;
int arr[] = {8, 4, 230, 3, 80985};
	n -= 1;
for (j = 1; j <= n; j++) {
	key = arr[j];
	i = j - 1;
	while ((i >= 0) && (arr[i] > key)) {
		arr[i + 1] = arr[i];
		i -= 1;
	}
	arr[i + 1] = key;
}
for (i = 0; i <= n; i++) 
	printf("%d ", arr[i]);
return 0;
}