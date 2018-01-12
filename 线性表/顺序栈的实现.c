#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

typedef struct
{
    char name[15];
    int age;
}DATA;

typedef struct stack
{
    DATA data[SIZE+1]; //数据元素
    int top; //栈顶
}SeqStack;
SeqStack *SeqStackInit()
{
    SeqStack *p;
    if(p=(SeqStack *)malloc(sizeof(SeqStack))) //申请栈内存
    {
        p->top=0; //设置栈顶为0
        return p;//返回指向栈的指针
    }
    return NULL;
}

void SeqStackFree(SeqStack *s) //释放栈所占用空间
{
    if(s)
        free(s);
}
int SeqStackIsEmpty(SeqStack *s) //判断栈是否为空
{
    return(s->top==0);
}
void SeqStackClear(SeqStack *s)  //清空栈
{
    s->top=0;
}
int SeqStackIsFull(SeqStack *s) //判断栈是否已满
{
    return(s->top==SIZE);
}
int SeqStackPush(SeqStack *s,DATA data) //入栈操作
{
     if((s->top+1)>SIZE)
     {
         printf("栈溢出!\n");
         return 0;
     }
     s->data[++s->top]=data;//将元素入栈
     return 1;
}
DATA SeqStackPop(SeqStack *s) //出栈操作
{
     if(s->top==0)
     {
         printf("栈为空！");
         exit(0);
     }
     return (s->data[s->top--]);
}

DATA SeqStackPeek(SeqStack *s) //读栈顶数据
{
     if(s->top==0)
     {
         printf("栈为空！");
         exit(0);
     }
     return (s->data[s->top]);
}



int main()
{
    SeqStack *stack;
    DATA data,data1;
    stack=SeqStackInit();  //初始化栈
    printf("入栈操作：\n");
    printf("输入姓名 年龄进行入栈操作:");
    scanf("%s%d",data.name,&data.age);
    SeqStackPush(stack,data);
    printf("输入姓名 年龄进行入栈操作:");
    scanf("%s%d",data.name,&data.age);
    SeqStackPush(stack,data);
    printf("\n出栈操作：\n按任意键进行出栈操作:");
    getchar();
    data1=SeqStackPop(stack);
    printf("出栈的数据是(%s,%d)\n" ,data1.name,data1.age);
    printf("再按任意键进行出栈操作:");
    getchar();

    data1=SeqStackPop(stack);
    printf("出栈的数据是(%s,%d)\n" ,data1.name,data1.age);
    SeqStackFree(stack); //释放栈所占用的空间
    return 0;
}
