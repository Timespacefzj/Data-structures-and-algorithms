#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef int DataType;   /*元素类型定义为整型*/
typedef struct Node     /*单链表类型定义*/
{
    DataType data;
    struct Node *next;
}ListNode,*LinkList;

void InitList(LinkList *h)
/*单链表的初始化*/
{
if((*h=(LinkList)malloc(sizeof(ListNode)))==NULL)       /*为头结点分配一个存储空间*/
exit(-1);
(*h)->next=NULL;                /*将单链表的头结点指针域置为空*/
}
int ListEmpty(LinkList h)
/*判断单链表是否为空*/
{
    if(h->next==NULL)           /*如果链表为空*/
        return 1;               /*返回1*/
    else                        /*否则*/
        return 0;               /*返回0*/
}
ListNode *Get(LinkList h,int i)
/*查找单链表中第i个结点。查找成功返回该结点的指针，否则返回NUL*/
{
ListNode *p;
int j;
if(ListEmpty(h))        /*查找第i个元素之前，判断链表是否为空*/
    return NULL;
   if(i<1)              /*判断该序号是否合法*/
        return NULL;
    j=0;
p=h;
while(p->next!=NULL&&j<i)
{
    p=p->next;
    j++;
}
if(j==i)            /*如果找到第i个结点*/
    return p;       /*返回指针p*/
else;               /*否则*/
    return NULL ;/*返回NULL*/
}
ListNode *LocateElem(LinkList h,DataType e)
/*查找线性表中元素值为e的元素，查找成功返回对应元素的结点指针，否则返回NULL */
{
ListNode *p;
p=h->next;      /*指针p指向第一个结点*/
while(p)
{
    if(p->data!=e)  /*如果当前元素值与e不相等*/
        p=p->next;  /*则继续查找*/
    else            /*否则*/
        break;      /*退出循环，停止查找*/
}
return p;           /*返回结点的指针*/
}
int LocatePos(LinkList h,DataType e)
/*查找线性表中元素值为e的元素，查找成功返回对应元素的序号，否则返回0*/
{
ListNode *p;
int i;
if(ListEmpty(h))        /*查找第i个元素之前，判断链表是否为空*/
    return 0;
p=h->next;      /*从第一个结点开始查找*/
i=1;
while(p)
{
    if(p->data==e)  /*找到与e相等的元素*/
        return i;   /*返回该序号*/
    else            /*否则*/
    {
        p=p->next; /*继续查找*/
        i++;
    }
}
if(!p)              /*如果没有找到与e相等的元素，返回0，表示失败*/
    return 0;
}
int InsertList(LinkList h,int i,DataType e)
/*在单链表中第i个位置插入值e的结点。插入成功返回1，失败返回0*/
{
ListNode *p,*pre;
int j;
pre=h;          /*指针p指向头结点*/
j=0;
while(pre->next!=NULL&&j<i-1)/*找到第i-1个结点，即第i个结点的前驱结点*/
{
    pre=pre->next;
    j++;
}
if(j!=i-1)                  /*如果没找到，说明插入位置错误*/
{
    printf("插入位置错");
    return 0;
}
/*新生成一个结点，并将e赋值给该结点的数据域*/
if((p=(ListNode*)malloc(sizeof(ListNode)))==NULL)
    exit(-1);
p->data=e;
/*插入结点操作*/
p->next=pre->next;
pre->next=p;
return 1;
}
int DeleteList(LinkList h,int i,DataType *e)
/*删除单链表中的第i个位置的结点。删除成功返回1，失败返回0*/
{
ListNode *pre,*p;
int j;
    pre=h;
    j=0;
    while(pre->next!=NULL&&pre->next->next!=NULL&&j<i-1)/*在寻找的过程中确保被删除结点存在*/
    {
        pre=pre->next;
        j++;
    }
    if(j!=i-1)              /*如果没找到要删除的结点位置，说明删除位置错误*/
    {
        printf("删除位置错误");
        return 0;
}
    p=pre->next;
*e=p->data;
/*将前驱结点的指针域指向要删除结点的下一个结点，也就是将p指向的结点与单链表断开*/
    pre->next=p->next;
    free(p);                /*释放p指向的结点*/
    return 1;
}
int ListLength(LinkList h)
/*求线性表的表长*/
{
    ListNode *p;
    int count=0;
    p=h;
    while(p->next!=NULL)
    {
        p=p->next;
        count++;
    }
    return count;
}
void DestroyList(LinkList h)
/*销毁链表*/
{
    ListNode *p,*q;
    p=h;
    while(p!=NULL)
{
    q=p;
        p=p->next;
        free(q);
    }
}



void CreateList(LinkList L,DataType a[],int n)
/*创建单链表*/
{
    int i;
    for(i=1;i<=n;i++)
        InsertList(L,i,a[i-1]);
}

void InsertSort(LinkList L)
/*链式存储结构下的插入排序*/
{
    ListNode *p=L->next,*pre,*q;
    L->next=NULL;           /*初始时，已排序链表为空*/
    while(p!=NULL)          /*p是指向待排序的结点*/
    {
        if(L->next==NULL)   /*如果*p是第一个结点，则插入到L，并令已排序的最后一个结点的指针域为空*/
        {
            L->next=p;
            p=p->next;
            L->next->next=NULL;
        }
        else                /*p指向待排序的结点，在L指向的已经排好序的链表中查找插入位置*/
        {
            pre=L;
            q=L->next;
            while(q!=NULL&&q->data<p->data) /*在q指向的有序表中寻找插入位置*/
            {
                pre=q;
                q=q->next;
            }
            q=p->next;                      /*q指向p的下一个结点，保存待排序的指针位置*/
            p->next=pre->next;              /*将结点*p插入到结点*pre的后面*/
            pre->next=p;
            p=q;                            /*p指向下一个待排序的结点*/
        }
    }
}
void main()
{
    LinkList L,p;
    int n=8;
    DataType a[]={76,55,10,21,65,90,5,38};
    InitList(&L);
    CreateList(L,a,n);
    printf("排序前的元素序列：\n");
    for(p=L->next;p!=NULL;p=p->next)
        printf("%4d ",p->data);
    printf("\n");
    InsertSort(L);
    printf("排序后的元素序列：\n");
    for(p=L->next;p!=NULL;p=p->next)
        printf("%4d ",p->data);
    printf("\n");
}
