/*******************************************************
 * File Name:SqList.c  线性表---顺序存储结构
 * Author:long
********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INIT_SIZE       10  //初始的大小
#define INCREMENT_SIZE  5   //每次拓展的大小

typedef int Status;
typedef int Elemtype;   //表中存储数据的类型

typedef struct
{
	Elemtype *elem;
	int      length;     //当前长度
	int      size;       //当前表的最大长度
}SqList;

Status InitList(SqList *L)  //初始化一个表
{
	L->elem = (Elemtype *)malloc(INIT_SIZE*sizeof(Elemtype));
	if (!L->elem)
	{
	    return ERROR;
    }
	L->length = 0;
	L->size   = INIT_SIZE;
	return OK;
}

Status DestroyList(SqList *L)   //销毁一个表
{
	free(L->elem);
    L->elem   = NULL;
	L->length = 0;
	L->size   = 0;
	return OK;
}

Status ClearList(SqList *L)     //清空一个表
{
	L->length = 0;
	return OK;
}

Status IsEmpty(const SqList L)       //判断表是否为空
{
	if (L.length == 0)
	{
		return TRUE;
	}
	return FALSE;
}

int GetLength(const SqList L)   //获得表当前的长度
{
	return L.length;
}

Status GetElem(const SqList L, int i, Elemtype *e)  //获取指定位置的元素
{
	if (i > 0 && i <= L.length)
	{
	    *e = L.elem[i-1];
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

Status FindElem(const SqList L, Elemtype e, int (*Compare)(Elemtype, Elemtype))     //寻找指定元素在表中的位置
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (!(*Compare)(L.elem[i], e))
        {
            return i+1;
        }
    }
    if (i >= L.length)
        return ERROR;
}

Status InsertElem(SqList *L, int i, Elemtype e)     //在指定位置插入指定元素
{
    Elemtype *new;
    if (i < 1 || i > L->length+1)
    {
        return ERROR;
    }
    if (L->length >= L->size)
    {
        new=(Elemtype *)realloc(L->elem, (L->size + INCREMENT_SIZE)*sizeof(Elemtype));
        if (!new)
        {
            return ERROR;
        }
        L->elem = new;
        L->size += INCREMENT_SIZE;
    }

    Elemtype *p = &L->elem[i-1];
    Elemtype *q = &L->elem[L->length-1];
    for (; q>=p; q--)
    {
        *(q+1)= *q;
    }
    *p=e;
    ++L->length;
    return OK;
}

Status DeleteElem(SqList *L, int i, Elemtype *e)    //删除指定位置的元素并返回
{
    if (i < 1 || i > L->length)
    {
        return ERROR;
    }
    Elemtype *p= &L->elem[i-1];
    *e=*p;
    for (; p< &L->elem[L->length]; p++)
    {
        *p=*(p+1);
    }
    --L->length;
    return OK;
}

void Visit(const Elemtype e)      //访问指定元素
{
    printf("%d ", e);
}

Status TraverseList(const SqList L, void (*visit)(Elemtype))    //遍历表
{
    int i;
    if (L.elem == NULL)
    {
        printf("List is not exist, it could be destroyed.\n");
        return ERROR;
    }
    else if (IsEmpty(L))
    {
        printf("List is empty.\n");
        return OK;
    }
    for (i = 0; i  <L.length;i++)
    {
        Visit (L.elem[i]);
    }
    return OK;
}

int main(void)          //主函数测试
{
    SqList L;
    if (InitList(&L))
    {
        Elemtype e;
        printf("Initialize success.\n");
        int i;

        for (i = 0; i < 10; i++)
        {
            InsertElem(&L, i+1, i);
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
        DeleteElem(&L, 1, &e);
        printf("Delete first element is %d.\n", e);
        printf("List: ");
        TraverseList(L, Visit);
        printf("\nLength is %d.\n", GetLength(L));
        if (DestroyList(&L))
        {
            printf("Destory success.\n");
        }
        printf("List: ");
        TraverseList(L, Visit);
    }
    return 0;
}

