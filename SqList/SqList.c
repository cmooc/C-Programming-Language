
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INIT_SIZE 10        //初始的大小
#define INCREMENT_SIZE 5    //每次拓展的大小

typedef int Status;
typedef int Elemtype;

typedef struct
{
	Elemtype *elem;
	int length;
	int size;
}SqList;

Status InitList(SqList *L)
{
	L->elem = (Elemtype *)malloc(INIT_SIZE*sizeof(Elemtype));
	if (!L->elem)
	{
	    return ERROR;
    }
	L->length = 0;
	L->size = INIT_SIZE;
	return OK;
}

Status DestroyList(SqList *L)
{
	free(L->elem);
	L->length = 0;
	L->size = 0;
	return OK;
}

Status ClearList(SqList *L)
{
	L->length = 0;
	return OK;
}

Status IsEmpty(SqList *L)
{
	if (L->length==0)
	{
		return TRUE;
	}
	return FALSE;
}

int getLength(const SqList L)
{
	return L.length;
}

Status GetElem(const SqList L, int i, Elemtype *e)
{
	if (i>0 && i <= L.length)
	{
	    *e = L.elem[i-1];
	    return OK;
    }
    return ERROR;
}

int compare(Elemtype e1, Elemtype e2)
{
    if (e1==e2)
    {
        return 0;
    }
    else if (e1<e2)
    {
        return -1;
    }
    else
        return 1;
}

Status FindElem(const SqList L, Elemtype e, int (*compare)(Elemtype, Elemtype))
{
    int i;
    for (i=0; i<L.length; i++)
    {
        if (!(*compare)(L.elem[i], e))
        {
            return i+1;
        }
    }
    if (i>=L.length)
        return ERROR;
}

Status InsertElem(SqList *L, int i, Elemtype e)
{
    Elemtype *new;
    if (i<1||i>L->length+1)
    {
        return ERROR;
    }
    if (L->length>=L->size)
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

Status DeleteElem(SqList *L, int i, Elemtype *e)
{
    if (i<1||i>L->length)
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

void visit(Elemtype e)
{
    printf("%d ",e);
}

Status TraverseList(const SqList L, void (*visit)(Elemtype))
{
    int i;
    for (i=0;i<L.length;i++)
    {
        visit (L.elem[i]);
    }
    return OK;
}

int main(void)
{
    SqList L;
    if (InitList(&L))
    {
        Elemtype e;
        printf("Init_success.\n");
        int i;
        for (i=0; i<10; i++)
        {
            InsertElem(&L, i+1, i);
        }
        printf("Length is %d.\n", getLength(L));
        if (GetElem(L, 1, &e))
        {
            printf("The first element is %d.\n", e);
        }
        else
        {
            printf("Element is not exist.\n");
        }
        if (IsEmpty(&L))
        {
            printf("List is empty.\n");
        }
        else
        {
            printf("List is not empty.\n");
        }
        printf("The 5 at %d.\n", FindElem(L, 5, *compare));
        DeleteElem(&L, 1, &e);
        printf("Delete first element is %d.\n", e);
        printf("List: ");
        TraverseList(L, visit);
        if (DestroyList(&L))
        {
            printf("Destory success.\n");
        }
    }
    return 0;
}

