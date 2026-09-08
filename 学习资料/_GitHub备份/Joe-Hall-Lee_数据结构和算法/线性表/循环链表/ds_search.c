#include "ds_search.h"
/* 返回结点所在的位置 */

int ds_search(node *pNode, int elem)
{
	node *target;
	int i = 1;

	for (target = pNode; target->data != elem && target->next != pNode; ++i)
	{
		target = target->next;
	}

	if (target->data != elem && target->next == pNode) /* 表中不存在该元素 */
	{
		return 0;
	}
	else
		return i;
}