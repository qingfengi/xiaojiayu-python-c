#include <stdio.h>
#include <stdlib.h>

// 链表存储结构
typedef struct LinkList
{
    int data;
    struct LinkList *next;
} node;
/** \brief 创建初始化循环链表
 *
 * \param 链表 L
 * \param 链表的长度 n
 * \return 第一个结点的地址
 *
 */
node *CreateList(node *head, int n)
{
    node *rear;     // 尾结点
    node *p, *temp; // 临时结点
    int i = 1;
    // 创建一个结点
    if (head == NULL)
        head = (node *)malloc(sizeof(node));
    if (!head)
        exit(0);

    p = head;
    while (i <= n)
    {
        // 创建一个结点
        temp = (node *)malloc(sizeof(node));
        if (!temp)
            exit(0);

        temp->data = i;
        p->next = temp;
        p = temp;
        i++;
    }
    // 尾结点指向第一个结点，构成循环链表
    rear = p;
    rear->next = head->next;

    return rear->next;
}
/** \brief 打印输出循环链表
 *
 * \param 第一个结点的地址
 * \return 无
 *
 */
void print(node *pHead)
{
    node *temp;
    temp = pHead;

    while (1)
    {
        printf("%3d", temp->data);
        temp = temp->next;
        if (temp == pHead) // 再次到达第一个结点的位置
            break;
    }
}

int main()
{
    int n; // 存放阶数
    node *L = NULL;
    node *pHead; // 第一个结点
    int count = 1;

    printf("请输入拉丁方阵的阶数 n = ");
    scanf_s("%d", &n);

    pHead = CreateList(L, n);
    while (count <= n)
    {
        print(pHead);
        printf("\n");
        pHead = pHead->next;
        count++;
    }

    return 0;
}