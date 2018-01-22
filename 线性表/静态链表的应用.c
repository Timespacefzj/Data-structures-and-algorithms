#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define ListSize 100
/*��̬�������Ͷ���*/
typedef int DataType;
typedef struct
{
    DataType data;
    int cur;
}SListNode;
typedef struct
{
	SListNode list[ListSize];
	int av;
}SLinkList;

void InitSList(SLinkList *L)
/*��̬�����ʼ��*/
{
    int i;
    for(i=0;i<ListSize;i++)
    (*L).list[i].cur=i+1;
    (*L).list[ListSize-1].cur=0;
    (*L).av=1;
}

void InsertSList(SLinkList *L,int i,DataType e)
/*�������*/
{
    int j,k,x;
    k=(*L).av;
    (*L).av=(*L).list[k].cur;
    (*L).list[k].data=e;
    j=(*L).list[0].cur;
    for(x=1;x<i-1;x++)
    j=(*L).list[j].cur;
    (*L).list[k].cur=(*L).list[j].cur;
    (*L).list[j].cur=k;
}
void DeleteSList(SLinkList *L,int i,DataType*e)
/*ɾ������*/
{
    int j,k,x;
    j=(*L).list[0].cur;
    for(x=1;x<i-1;x++)
    j=(*L).list[j].cur;
    k=(*L).list[j].cur;
    (*L).list[j].cur=(*L).list[k].cur;
    (*L).list[k].cur=(*L).av;
    *e=(*L).list[k].data;
    (*L).av=k;
}



void PrintDList(SLinkList L,int n)
/*�����̬�����е�����Ԫ��*/
{
	int j,k;
	k=L.list[0].cur;
	for(j=1;j<=n;j++)
	{
		printf("%4d",L.list[k].data);
		k=L.list[k].cur;
	}
	printf("\n");
}

void main()
{
    SLinkList L;
    int i,num;
	int pos;
	int e;
	DataType a[]={20,15,-82,37,52,8,-90};
	num=sizeof(a)/sizeof(a[0]);
	InitSList(&L);
	for(i=1;i<=num;i++)
		InsertSList(&L,i,a[i-1]);
    printf("��̬�����е�Ԫ��:");
	PrintDList(L,num);
	printf("������Ҫ�����Ԫ�ؼ�λ��:");
	scanf("%d",&e);
	getchar();
	scanf("%d",&pos);
	getchar();
	InsertSList(&L,pos,e);
	printf("����Ԫ�غ�,��̬�����е�Ԫ��:");
	PrintDList(L,num+1);
	printf("������Ҫɾ��Ԫ�ص�λ��:");
	scanf("%d",&pos);
	getchar();
	DeleteSList(&L,pos,&e);
	printf("Ԫ��%d�ѱ�ɾ����\n",e);
	printf("ɾ��Ԫ�غ�,��̬�����е�Ԫ��:");
	PrintDList(L,num);
}
