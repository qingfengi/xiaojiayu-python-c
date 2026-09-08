#include <stdio.h>

void BubbleSort_2(int k[], int n)
{
	int i, j, temp, count1 = 0, count2 = 0, flag;

	flag = 1;
	for (i = 0; i < n - 1 && flag; i++)
	{
		for (j = n - 1; j > i; j--)
		{
			count1++;
			flag = 0;
			if (k[j - 1] > k[j])
			{
				count2++;
				temp = k[j - 1];
				k[j - 1] = k[j];
				k[j] = temp;
				flag = 1;
			}
		}
	}

	printf("总共进行了 %d 次比较，进行了 %d 次移动！", count1, count2);
}

int main()
{
	int i, a[10] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};

	BubbleSort_2(a, 10);

	printf("排序后的结果是：");
	for (i = 0; i < 10; i++)
		printf("%d", a[i]);

	printf("\n\n");

	return 0;
}
