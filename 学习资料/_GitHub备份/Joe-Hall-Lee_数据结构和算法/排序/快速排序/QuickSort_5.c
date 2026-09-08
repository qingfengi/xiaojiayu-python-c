#include <stdio.h>
#define MAX_LENGTH_INSERT_SORT 7

void ISort5(int k[], int n)
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

void InsertSort5(int k[], int low, int high)
{
    ISort5(k + low, high - low + 1);
}

void swap_5(int k[], int low, int high)
{
    int temp;

    temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}

int Partition_5(int k[], int low, int high)
{
    int point;

    int m = low + (high - low) / 2;

    if (k[low] > k[high])
        swap_5(k, low, high);
    if (k[m] > k[high])
        swap_5(k, m, high);
    if (k[m] > k[low])
        swap_5(k, m, low);

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

void QSort_5(int k[], int low, int high)
{
    int point;

    if (high - low > MAX_LENGTH_INSERT_SORT)
    {
        while (low < high)
        {
            point = Partition_5(k, low, high);

            if (point - low < high - point)
            {
                QSort_5(k, low, point - 1);

                low = point + 1;
            }
            else
            {
                QSort_5(k, point + 1, high);

                high = point - 1;
            }
        }
    }
    else
    {
        InsertSort5(k, low, high);
    }
}

void QuickSort_5(int k[], int n)
{
    QSort_5(k, 0, n - 1);
}

int main()
{
    int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

    QuickSort_5(a, 10);

    printf("排序后的结果是：");
    for (i = 0; i < 10; i++)
        printf("%d", a[i]);

    printf("\n\n");

    return 0;
}
