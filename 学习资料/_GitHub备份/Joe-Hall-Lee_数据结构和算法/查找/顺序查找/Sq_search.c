// 顺序查找，a 为要查找的数组，n 为要查找的数组的长度，key 为要查找的关键字
int Sq_Search(int *a, int n, int key)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		if (a[i] == key)
			return i;
	}
	return 0;
}
