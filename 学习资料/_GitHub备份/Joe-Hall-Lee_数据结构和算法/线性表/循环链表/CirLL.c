#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "ds_init.h"
#include "ds_delete.h"
#include "ds_search.h"
#include "ds_insert.h"

/***********************************************************/
/*操作                                                     */
/***********************************************************/

/*遍历*/
void ds_traverse(node *pNode) // 遍历，循环链表的遍历最好用 do while 语句 ，因为头节点就有值
{
	node *temp;
	temp = pNode;
	do
	{
		printf("%5d", temp->data);
		temp = temp->next;
	} while (temp != pNode);

	printf("\n");
}

int main()
{
	node *pHead = NULL;
	char opp = 1;
	int find;

	printf("1. 初始化列表\n\n2. 插入结点\n\n3. 删除结点\n\n4.返回结点位置\n\n5. 遍历列表\n\n0. 退出\n\n请选择你的操作：");

	while (opp != '0')
	{
		scanf("%c", &opp);
		switch (opp)
		{
		case '1':
			ds_init(&pHead);
			printf("\n");
			ds_traverse(pHead);

			break;

		case '2':
			printf("输入需要插入结点的位置。");
			scanf_s("%d", &find);
			ds_insert(&pHead, find);
			printf("在位置 %d 插入值后:\n", find);
			ds_traverse(pHead);
			printf("\n");
			break;
		case '3':
			printf("输入需要删除的结点位置。");
			scanf_s("%d", &find);
			printf("删除第%d个结点后:\n", find);
			ds_delete(&pHead, find);
			ds_traverse(pHead);
			printf("\n");
			break;

		case '4':
			printf("你要查找哪个元素的位置？");
			scanf_s("%d", &find);
			printf("元素 %d 所在位置:%d\n", find, ds_search(pHead, find));
			printf("\n");
			break;

		case '5':
			ds_traverse(pHead);
			printf("\n");
			break;
		case '0':
			exit(0);
		}
	}

	return 0;
}