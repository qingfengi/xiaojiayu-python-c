#include <stdio.h>
#define MAX_LENGTH_INSERT_SORT 7

void ISort(int k[], int n)
{
    int i, j, temp;

    for (i = 1; i < n; i++)
    {
        if (k[i] < k[i - 1])
        {
            temp = k[i];

            for (j = i - 1; k[j] > temp; j--)
                k[j + 1] = k[j];

            k[j + 1] = temp;
        }
    }
}

void InsertSort(int k[], int low, int high)
{
    ISort(k + low, high - low + 1);
}

void swap_4(int k[], int low, int high)
{
    int temp;

    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}

int Partition_4(int k[], int low, int high)
{
    int point;

    int m = low + (high - low) / 2;

    if (k[low] > k[high])
        swap_4(k, low, high);
    if (k[m] > k[high])
        swap_4(k, m, high);
    if (k[m] > k[low])
        swap_4(k, m, low);

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

void QSort_4(int k[], int low, int high)
{
    int point;

    if (high - low > MAX_LENGTH_INSERT_SORT)
    {
        point = Partition_4(k, low, high);

        QSort_4(k, low, point - 1);

        QSort_4(k, point + 1, high);
    }
    else
    {
        InsertSort(k, low, high);
    }
}

void QuickSort_4(int k[], int n)
{
    QSort_4(k, 0, n - 1);
}

int main()
{
    int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

    QuickSort_4(a, 10);

    printf("排序后的结果是：");
    for (i = 0; i < 10; i++)
        printf("%d", a[i]);

    printf("\n\n");

    return 0;
}
