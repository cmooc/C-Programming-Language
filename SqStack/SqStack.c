/****************************************************************
 * File name: SqStack.c
 * Author: long
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INIT_SIZE 20        //初始化栈的大小
#define INCREMRNT_SIZE 5    //增量的大小

typedef int SElemType;      //栈元素类型
typedef int Status;

typedef struct
{
    SElemType *base;    //栈底指针
    SElemType *top;     //栈顶指针
    int size;           //栈的大小
}SqStack;

Status InitStack(SqStack *S)        //初始化栈
{
    S->base = (SElemType *)malloc(INIT_SIZE * sizeof(SElemType));
    if (!S->base)
    {
        return ERROR;
    }
    S->top = S->base;
    S->size = INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack *S)     //销毁栈
{
    free(S->base);
    S->base = NULL;
    S->top  = NULL;
    S->size = 0;
    return OK;
}

Status ClearStack(SqStack *S)   //清空栈
{
    S->top = S->base;
    return OK;
}

Status IsEmpty(const SqStack S)       //判断栈是否为空
{
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

int GetLength(const SqStack S)        //获得栈的长度
{
    return S.top - S.base;
}

Status GetTop(const SqStack S, SElemType *e)    //获得栈顶元素
{
    if (!IsEmpty(S))
    {
        *e = *(S.top-1);
    }
    else
        return ERROR;
}

Status Push(SqStack *S, SElemType e)        //入栈
{
    if (GetLength(*S) == S->size)
    {
        S->base = (SElemType *)realloc(S->base, (S->size + INCREMRNT_SIZE) * sizeof (SElemType));
        if (!S->base)
        {
            return ERROR;
        }
        S->top  = S->base + S->size;
        S->size += INCREMRNT_SIZE;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e)    //出栈
{
    if (!IsEmpty(*S))
    {
        *e = *(--S->top);
        return OK;
    }
    return ERROR;
}

void Visit(SElemType e)         //访问元素
{
    printf("%d ", e);
}

Status TraverseStack(SqStack S, void (*Visit)(SElemType))     //遍历栈
{
    if (S.base == NULL)
    {
        printf("Stack is not exist, it could be destroyed.\n");
        return ERROR;
    }
    else if (IsEmpty(S))
    {
        printf("Stack is empty.\n");
        return ERROR;
    }
    else
    {
        while (S.top > S.base)
        {
            Visit(*S.base);
            S.base++;
        }
    }
}

void Test(SqStack S)        //测试函数，加深对指针的理解
{
    printf("\n");
    printf("sizeof(S.base)=%ld.\n", sizeof(S.base));
    printf("sizeof(S.top)=%ld.\n", sizeof(S.top));
    printf("sizeof(int)=%ld.\n", sizeof(int));

    printf("s.top-s.base=%d.\n", S.top-S.base);
    printf("(s.top-s.base)/4=%d.\n", (S.top-S.base)/4);
    printf("(s.top-s.base)/sizeof(int)=%d.\n", (S.top-S.base)/sizeof(int));

    printf("S.base=%p.\n", S.base);
    printf("S.base+sizeof(SElemType)=%p.\n", S.base+sizeof(SElemType));
    printf("S.base+sizeof(int)=%p.\n", S.base+sizeof(int));
    printf("++S.base=%p.\n", ++S.base);
    printf("S.top=%p.\n", S.top);
    printf("S.top+sizeof(SElemType)=%p.\n", S.top+sizeof(SElemType));
    printf("S.top+sizeof(int)=%p.\n", S.top+sizeof(int));
    printf("S.top+1*sizeof(int)=%p.\n", S.top+1*sizeof(int));
    printf("++S.top=%p.\n", ++S.top);
    printf("\n");
}

int main(void)      //主函数测试
{
    SqStack S;
    if (InitStack(&S))
    {
        int i;
        SElemType e;
        printf("Initialize success.\n");
        for (i = 0; i < 20; i++)
        {
            Push(&S, i);
            printf("Push %d.\n", i);
        }
        printf("Stack: ");
        TraverseStack(S, Visit);
        printf("\nLength is %d.\n", GetLength(S));
        //Test(S);
        if (IsEmpty(S))
        {
            printf("Stack is empty.\n");
        }
        else
        {
            printf("Stack is not empty.\n");
        }
        for (i = 0; i < 5; i++)
        {
            Pop(&S, &e);
            printf("Pop %d.\n", e);
        }
        printf("Stack: ");
        TraverseStack(S, Visit);
        printf("\nLength is %d.\n", GetLength(S));
        if (DestroyStack(&S))
        {
            printf("Destroy success.\n");
        }
        printf("Stack: ");
        TraverseStack(S, Visit);
    }
    return 0;
}


