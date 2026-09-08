#include <stdio.h>

void swap_3(int k[], int low, int high)
{
    int temp;

    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}

int Partition_3(int k[], int low, int high)
{
    int point;

    int m = low + (high - low) / 2;

    if (k[low] > k[high])
        swap_3(k, low, high);
    if (k[m] > k[high])
        swap_3(k, m, high);
    if (k[m] > k[low])
        swap_3(k, m, low);

    point = k[low];

    while (low < high)
    {
        while (low < high && k[high] >= point)
            high--;
        k[low] = k[high];

        while (low < high && k[low] <= point)
            low++;
        k[high] = k[low];
    }

    k[low] = point;

    return low;
}

void QSort_3(int k[], int low, int high)
{
    int point;

    if (low < high)
    {
        point = Partition_3(k, low, high);

        QSort_3(k, low, point - 1);

        QSort_3(k, point + 1, high);
    }
}

void QuickSort_3(int k[], int n)
{
    QSort_3(k, 0, n - 1);
}

int main()
{
    int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

    QuickSort_3(a, 10);

    printf("排序后的结果是：");
    for (i = 0; i < 10; i++)
        printf("%d", a[i]);

    printf("\n\n");

    return 0;
}
