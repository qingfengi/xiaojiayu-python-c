#include <stdio.h>

typedef char *String;

void get_next(String T, int *next)
{
	int j = 0;
	int i = 1;
	next[1] = 0;

	while (i < T[0])
	{
		if (0 == j || T[i] == T[j])
		{
			i++;
			j++;
			if (T[i] != T[j])
			{
				next[i] = j;
			}
			else
			{
				next[i] = next[j];
			}
		}
		else
		{
			// j 回溯
			j = next[j];
		}
		// 因为前缀是固定的，后缀是相对的
	}
}

// 返回子串在主串 S 第 pos 个字符之后的位置
// 若不存在，则返回 0
int Index_KMP(String S, String T, int pos)
{
	int i = pos;
	int j = 1;
	int next[255];

	get_next(T, next);

	while (i <= S[0] || j <= T[0])
	{
		if (0 == j || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j > T[0])
	{
		return i - T[0];
	}
}