#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
/*双向链表类型定义*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *prior;
    struct Node *next;
}DListNode,*DLinkList;
/*函数声明*/

void Josephus(DLinkList head,int n,int m,int k)
/*在长度为n的双向循环链表中，从第k个人开始报数，数到m的人出列*/
{
	DListNode *p,*q;
	int i;
	p=head;
	for(i=1;i<k;i++)		/*从第k个人开始报数*/
	{
		q=p;
		p=p->next;
	}
	while(p->next!=p)
	{
		for(i=1;i<m;i++)	/*数到m的人出列*/
		{
			q=p;
			p=p->next;
		}
		q->next=p->next;	/*将p指向的结点删除，即报数为m的人出列*/
		p->next->prior=q;
		printf("%4d",p->data);/*输出被删除的结点*/
		free(p);
		p=q->next;			/*p指向下一个结点，重新开始报数*/
	}
	printf("%4d\n",p->data);
}
DLinkList CreateDCList(int n)
/*创建双向循环链表*/
{
	DLinkList head=NULL;
	DListNode *s,*q;
	int i;
	for(i=1;i<=n;i++)
	{
		s=(DListNode*)malloc(sizeof(DListNode));
		s->data=i;
		s->next=NULL;
		/*将新生成的结点插入到双向循环链表*/
		if(head==NULL)
		{
			head=s;
			s->prior=head;
			s->next=head;
		}
		else
		{
			s->next=q->next;
			q->next=s;
			s->prior=q;
			head->prior=s;
		}
        q=s;						/*q始终指向链表得最后一个结点*/
	}
	return head;
}



void main()
{
	DLinkList h;
	int n,k,m;
	printf("输入环中人的个数n=");
	scanf("%d",&n);
	printf("输入开始报数的序号k=");
	scanf("%d",&k);
	printf("报数为m的人出列m=");
	scanf("%d",&m);
	h=CreateDCList(n);
	Josephus(h,n,m,k);
}
