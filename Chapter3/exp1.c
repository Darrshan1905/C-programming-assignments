#include<stdio.h>

int main() {
	int low, high, mid;
	int arr[5] = {1,2,3,4,5};
	int x = 2;
	low = 0;
	high = 4;
	mid = 0;

	while (low <= high && arr[mid] != x) {
		mid = (low+high)/2;
		if (x < arr[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if(arr[mid] == x)
		printf("At index %d\n", mid);
	else
		printf("Element not found");
	return -1;
}
