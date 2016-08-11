/*********************************************************************
 * File name: LinkList.c
 * Author: long
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0

typedef int Elemtype;
typedef int Status;

typedef struct LNode    //节点的数据结构
{
    Elemtype data;
    struct LNode *next;
}LNode, *LinkList;

Status InitList(LinkList *L)        //初始化链表
{
    *L = (LinkList)malloc(sizeof(LNode));
    if (!L)
    {
        return ERROR;
    }
    (*L)->data = 0;
    (*L)->next = NULL;
    return OK;
}

Status DestroyList(LinkList *L)     //销毁链表
{
    LNode *temp;
    while (*L)
    {
        temp = (*L)->next;
        free(*L);
        *L = temp;
    }
    return OK;
}

Status ClearList(LinkList *L)   //清空链表
{
    LinkList temp = (*L)->next;
    (*L)->data = 0;
    (*L)->next = NULL;
    DestroyList(&temp);
    return OK;
}

Status IsEmpty(const LinkList L)     //判断链表是否为空
{
    if (L->data == 0 || L->next == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

int GetLength(const LinkList L)   //获得链表的长度
{
    return L->data;
}

Status GetElem(const LinkList L, int i, Elemtype *e)    //获得指定位置的元素
{
    LNode *temp = L->next;
    if (i > 0 && i <= L->data)
    {
        int j;
        for (j = 1; j < i; j++)
        {
            temp = temp->next;
        }
        *e = temp->data;
        return OK;
    }
    return ERROR;
}

int Compare(const Elemtype e1, const Elemtype e2)   //比较两个元素的大小
{
    if (e1 == e2)
    {
        return 0;
    }
    else if (e1 < e2)
    {
        return -1;
    }
    else
        return 1;
}

int FindElem(const LinkList L, Elemtype e, int (*Compare)(Elemtype, Elemtype))  //获得指定元素的位置
{
    int i = 1;
    LNode *temp = L->next;
    while(temp)
    {
        if (!(*Compare)(temp->data, e))
        {
            return i;
        }
        else
        {
            i++;
            temp = temp->next;
        }
    }
    return ERROR;
}

Status PreElem(const LinkList L, Elemtype cur_e, Elemtype *pre_e)   //获得指定元素的前驱元素
{
    LNode *pre = L->next;
    LNode *cur = pre->next;
    while (cur)
    {
        if (!Compare(cur_e, cur->data))
        {
            *pre_e = pre->data;
            return OK;
        }
        else
        {
            pre = cur;
            cur = pre->next;
        }
    }
    return ERROR;
}

Status NextElem(const LinkList L, Elemtype cur_e, Elemtype *next_e)     //获得指定元素的后继元素
{
    LNode *cur = L->next;
    while (cur->next)
    {
        if (!Compare(cur_e, cur->data))
        {
            *next_e = cur->next->data;
            return OK;
        }
        else
        {
            cur = cur->next;
        }
    }
    return ERROR;
}

Status InsertElem(LinkList L, int i, Elemtype e)    //在指定位置插入元素
{
    int j = 1;
    LNode *temp = L, *ielem;
    while (temp && j<i)
    {
        temp = temp->next;
        j++;
    }
    if (j==i)
    {
        ielem=(LNode *)malloc(sizeof(LNode));
        ielem->data = e;
        ielem->next = temp->next;
        temp->next  = ielem;
        (L->data)++;
        return OK;
    }
    return ERROR;
}

Status DeleteElem(LinkList L, int i, Elemtype *e) //删除指定位置的元素
{
    int j = 1;
    LNode *pre = L;
    LNode *del = pre->next;

    while (del && j<i)
    {
        pre = del;
        del = pre->next;
        j++;
    }
    if (del && j==i)
    {
        *e = del->data;
        pre->next = del->next;
        free(del);
        (L->data)--;
        return OK;
    }
    return ERROR;
}

void Visit(Elemtype e)      //访问元素
{
    printf("%d ", e);
}

Status TraverseList(const LinkList L, void (*Visit)(Elemtype))    //遍历链表
{
    if (L == NULL)
    {
        printf("List is not exist, it could be destroyed.\n");
        return ERROR;
    }
    else if (IsEmpty(L))
    {
        printf("List is empty.\n");
        return OK;
    }
    LNode *temp = L->next;
    while (temp)
    {
        Visit(temp->data);
        temp = temp->next;
    }
    return OK;
}

int main(void)      //主函数测试
{
    LinkList L;
    if (InitList(&L))
    {
        int i;
        Elemtype e;
        printf("Initialize success.\n");
        for (i = 0; i < 10; i++)
        {
            InsertElem(L, i+1, i);
        }
        printf("List: ");
        TraverseList(L, Visit);
        printf("\nLength is %d.\n", GetLength(L));
        if (GetElem(L, 1, &e))
        {
            printf("The first element is %d.\n", e);
        }
        else
        {
            printf("Element is not exist.\n");
        }
        if (IsEmpty(L))
        {
            printf("List is empty.\n");
        }
        else
        {
            printf("List is not empty.\n");
        }
        printf("The 1 at %d.\n", FindElem(L, 1, Compare));
        DeleteElem(L, 1, &e);
        printf("Delete first element is %d.\n", e);
        printf("List: ");
        TraverseList(L, Visit);
        printf("\nLength is %d.\n", GetLength(L));
        if (DestroyList(&L))
        {
            printf("Destroy success.\n");
        }
        printf("List: ");
        TraverseList(L, Visit);
    }
   return 0;
}

