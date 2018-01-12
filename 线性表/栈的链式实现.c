#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
typedef struct
{
    char name[15];
    int age;
}DataType;
typedef struct node
{
DataType data;
struct node *next;
}LinkStackNode,*LinkStack;
void InitStack(LinkStack *top)
/*初始化链式栈。为头结点动态申请一块内存空间，并将指针域置为NULL*/
{
	if((*top=(LinkStack)malloc(sizeof(LinkStackNode)))==NULL)
	{
		printf("分配结点失败！\n");
		exit(-1);
	}
	(*top)->next=NULL;
}
int StackEmpty(LinkStack top)
/*判断链式栈是否为空。如果链式栈为空，则返回1；否则，返回0*/
{
	if(top->next==NULL)		/*如果头结点的指针域为空*/
		return 1; 			/*则返回1*/
	else					/*如果头结点的指针域不为空*/
		return 0; 			/*则返回0*/
}
int StackLength(LinkStack top)
/*求栈的长度*/
{
	int n=0;				/*n用作计数器*/
	LinkStackNode *p;
	p=top; 				/*从栈顶指针开始*/
	while(p->next!=NULL) 	/*如果栈不为空*/
	{
		p=p->next; 			/*访问下一个结点*/
		n++;				/*计数器加1*/
	}
	return n; 				/*返回栈的长度*/
}
int PushStack(LinkStack top,DataType e)
/*入栈操作。如果入栈操作成功，返回1*/
{
	LinkStackNode *p;
	if((p=(LinkStackNode*)malloc(sizeof(LinkStackNode)))==NULL)	/*动态生成一个新结点*/
	{
		printf("内存分配失败！\n");
		exit(-1);
	}
	p->data=e; 				/*将元素值e存放到新结点数据域*/
	p->next=top->next; 		/*新结点指向原来的栈顶*/
	top->next=p; 			/*新结点成为栈顶*/
	return 1; 				/*返回1表示入栈操作成功*/
}
int PopStack(LinkStack top,DataType *e)
/*出栈操作。出栈操作成功返回1，否则返回0*/
{
	LinkStackNode *p;
	p=top->next; 			/*p指向栈顶结点*/
	if(!p) 					/*如果栈为空*/
	{
		printf("栈为空，不能进行出栈操作！\n");
		return 0; 			/*返回0表示出栈操作失败*/
	}
	top->next=p->next; 		/*删除栈顶结点*/
	free(p); 				/*释放结点所占内存空间*/
	return 1; 				/*返回1表示出栈操作成功*/
}
int GetTop(LinkStack top,DataType *e)
/*取栈顶元素。如果取栈顶元素成功返回1，否则返回0*/
{
	LinkStackNode *p;
	p=top->next;			/*p指向栈顶结点*/
	if(!p) 					/*如果栈不为空*/
	{
		printf("栈已空，不能取栈顶元素！\n");
		return 0; 			/*返回0表示取栈顶元素失败*/
	}
	*e=p->data; 			/*取出栈顶元素赋值给e*/
	return 1; 				/*返回1表示取栈顶元素成功*/
}
void ClearStack(LinkStack top)
/*清空栈。释放链式栈中的每一个结点所占的内存空间*/
{
	LinkStackNode *p,*q;
	p=top; 			/*从栈顶指针开始*/
	while(!p) 			/*如果栈不为空*/
	{
		q=p; 			/*q指向要释放的结点*/
		p=p->next; 		/*p指向下一个结点*/
		free(q); 		/*释放结点*/
	}
}


int main()
{
    LinkStack stack;
    DataType data,data1;
    InitStack(&stack);						/*初始化链栈*/
    printf("入栈操作：\n");
    printf("输入姓名 年龄进行入栈操作:");
    scanf("%s%d",data.name,&data.age);
    PushStack(stack,data);
    printf("输入姓名 年龄进行入栈操作:");
    scanf("%s%d",data.name,&data.age);
    PushStack(stack,data);

    printf("\n出栈操作：\n按任意键进行出栈操作:");
    getchar();
    PopStack(stack,&data1);
    printf("出栈的数据是(%s,%d)\n" ,data1.name,data1.age);
    printf("再按任意键进行出栈操作:");
    getchar();
    PopStack(stack,&data1);
    printf("出栈的数据是(%s,%d)\n" ,data1.name,data1.age);
    ClearStack(stack); //释放栈所占用的空间
    getchar();
    return 0;
}
