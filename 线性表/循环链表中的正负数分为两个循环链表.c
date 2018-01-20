#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
/*单链表类型定义*/
typedef int DataType;
typedef struct Node
{
    DataType data;
    struct Node *next;
}ListNode,*LinkList;
/*函数声明*/

LinkList CreateCycList()
/*创建循环单链表*/
{
	ListNode *h=NULL,*s=NULL,*t=NULL;
	DataType e;
	int i=1;
	printf("创建一个循环单链表(输入0表示创建链表结束):\n");
	while(1)
	{
		printf("请输入第%d个结点的data域值:",i);
		scanf("%d",&e);
		if(e==0)
			break;
		if(i==1)
		{
			h=(ListNode*)malloc(sizeof(ListNode));
			h->data=e;
			h->next=NULL;
			t=h;
		}
		else
		{
			s=(ListNode*)malloc(sizeof(ListNode));
			s->data=e;
			s->next=NULL;
			t->next=s;
			t=s;
		}
		i++;
	}
	if(t!=NULL)
		t->next=h;
	return h;
}

void Split(LinkList ha,LinkList hb)
/*将一个循环单链表ha构造成两个循环单链表，其中ha中的元素只含正数，hb中的元素只含负数*/
{
	ListNode *ra,*rb,*p=ha->next;
	int v;
	ra=ha;
	ra->next=NULL;
	rb=hb;
	rb->next=NULL;
	while(p!=ha)
	{
		v=p->data;
		if(v>0)/*若元素值大于0，插入到ha中*/
		{
			ra->next=p;
			ra=p;
		}
		else/*若元素值小于0，插入到hb中*/
		{
			rb->next=p;
			rb=p;
		}
		p=p->next;
	}
	ra->next=ha;/*变为循环单链表*/
	rb->next=hb;/*变为循环单链表*/
}

void DispCycList(LinkList h)
/*输出循环单链表*/
{
	ListNode *p=h->next;
	if(p==NULL)
	{
		printf("链表为空!\n");
		return;
	}
	while(p->next!=h)
	{
		printf("%4d",p->data);
		p=p->next;
	}
	printf("%4d",p->data);
	printf("\n");
}

void main()
{
	LinkList ha,hb=NULL;
	ListNode *s,*p;
	ha=CreateCycList();
	p=ha;
	while(p->next!=ha)/*找ha的最后一个结点，p指向该结点*/
		p=p->next;
	/*为ha添加哨兵结点*/
	s=(ListNode*)malloc(sizeof(ListNode));
	s->next=ha;
	ha=s;
	p->next=ha;
    /*创建一个空的循环单链表hb*/
	s=(ListNode*)malloc(sizeof(ListNode));
	s->next=hb;
	hb=s;

	Split(ha,hb);
	printf("输出循环单链表A(正数):\n");
	DispCycList(ha);
	printf("输出循环单链表B(负数):\n");
	DispCycList(hb);
}
