#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int bin_search(int str[], int n, int key)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high)
	{
		mid = low + (key - str[low]) * (high - low) / (str[high] - str[low]); // 插值查找的唯一不同点

		if (str[mid] == key)
			return mid; // 查找成功
		if (str[mid] < key)
			low = mid + 1; // 在后半序列中查找
		if (str[mid] > key)
			high = mid - 1; // 在前半序列中查找
	}

	return -1;
}

int main()
{
	int str[11] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
	int m, addr;

	printf("请输入待查找的关键字: ");
	scanf("%d", &m);

	addr = bin_search(str, 11, m);
	if (-1 != addr)
	{
		printf("查找成功，可喜可贺，可口可乐！关键字 %d 所在的位置是: %d\n", m, addr);
	}
	else
	{
		printf("查找失败！\n");
	}

	return 0;
}
