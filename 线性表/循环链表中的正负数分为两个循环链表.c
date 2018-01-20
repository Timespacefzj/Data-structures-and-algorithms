#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
/*���������Ͷ���*/
typedef int DataType;
typedef struct Node
{
    DataType data;
    struct Node *next;
}ListNode,*LinkList;
/*��������*/

LinkList CreateCycList()
/*����ѭ��������*/
{
	ListNode *h=NULL,*s=NULL,*t=NULL;
	DataType e;
	int i=1;
	printf("����һ��ѭ��������(����0��ʾ�����������):\n");
	while(1)
	{
		printf("�������%d������data��ֵ:",i);
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
/*��һ��ѭ��������ha���������ѭ������������ha�е�Ԫ��ֻ��������hb�е�Ԫ��ֻ������*/
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
		if(v>0)/*��Ԫ��ֵ����0�����뵽ha��*/
		{
			ra->next=p;
			ra=p;
		}
		else/*��Ԫ��ֵС��0�����뵽hb��*/
		{
			rb->next=p;
			rb=p;
		}
		p=p->next;
	}
	ra->next=ha;/*��Ϊѭ��������*/
	rb->next=hb;/*��Ϊѭ��������*/
}

void DispCycList(LinkList h)
/*���ѭ��������*/
{
	ListNode *p=h->next;
	if(p==NULL)
	{
		printf("����Ϊ��!\n");
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
	while(p->next!=ha)/*��ha�����һ����㣬pָ��ý��*/
		p=p->next;
	/*Ϊha����ڱ����*/
	s=(ListNode*)malloc(sizeof(ListNode));
	s->next=ha;
	ha=s;
	p->next=ha;
    /*����һ���յ�ѭ��������hb*/
	s=(ListNode*)malloc(sizeof(ListNode));
	s->next=hb;
	hb=s;

	Split(ha,hb);
	printf("���ѭ��������A(����):\n");
	DispCycList(ha);
	printf("���ѭ��������B(����):\n");
	DispCycList(hb);
}
