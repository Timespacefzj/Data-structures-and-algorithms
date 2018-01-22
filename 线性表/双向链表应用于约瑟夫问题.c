#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
/*˫���������Ͷ���*/
typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node *prior;
    struct Node *next;
}DListNode,*DLinkList;
/*��������*/

void Josephus(DLinkList head,int n,int m,int k)
/*�ڳ���Ϊn��˫��ѭ�������У��ӵ�k���˿�ʼ����������m���˳���*/
{
	DListNode *p,*q;
	int i;
	p=head;
	for(i=1;i<k;i++)		/*�ӵ�k���˿�ʼ����*/
	{
		q=p;
		p=p->next;
	}
	while(p->next!=p)
	{
		for(i=1;i<m;i++)	/*����m���˳���*/
		{
			q=p;
			p=p->next;
		}
		q->next=p->next;	/*��pָ��Ľ��ɾ����������Ϊm���˳���*/
		p->next->prior=q;
		printf("%4d",p->data);/*�����ɾ���Ľ��*/
		free(p);
		p=q->next;			/*pָ����һ����㣬���¿�ʼ����*/
	}
	printf("%4d\n",p->data);
}
DLinkList CreateDCList(int n)
/*����˫��ѭ������*/
{
	DLinkList head=NULL;
	DListNode *s,*q;
	int i;
	for(i=1;i<=n;i++)
	{
		s=(DListNode*)malloc(sizeof(DListNode));
		s->data=i;
		s->next=NULL;
		/*�������ɵĽ����뵽˫��ѭ������*/
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
        q=s;						/*qʼ��ָ����������һ�����*/
	}
	return head;
}



void main()
{
	DLinkList h;
	int n,k,m;
	printf("���뻷���˵ĸ���n=");
	scanf("%d",&n);
	printf("���뿪ʼ���������k=");
	scanf("%d",&k);
	printf("����Ϊm���˳���m=");
	scanf("%d",&m);
	h=CreateDCList(n);
	Josephus(h,n,m,k);
}
