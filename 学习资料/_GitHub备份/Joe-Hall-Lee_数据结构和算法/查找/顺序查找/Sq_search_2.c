// 顺序查找优化方案，a 为要查找的数组，n 为要查找的数组的长度，key 为要查找的关键字
int Sq_search(int *a, int n, int key)
{
	int i = n;
	a[0] = key;
	while (a[i] != key)
		i--;

	return i;
}
