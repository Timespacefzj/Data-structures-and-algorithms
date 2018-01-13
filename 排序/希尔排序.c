#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef int KeyType;
typedef struct /*数据元素类型定义*/
 {
    KeyType key;/*关键字*/
}DataType;
typedef struct /*顺序表类型定义*/
 {
    DataType data[MaxSize];
    int length;
}SqList;
void ShellInsert(SqList *L,int c)
/*对顺序表L进行一次希尔排序，c是增量*/
{
    int i,j;
    DataType t;
    for(i=c+1;i<=L->length;i++)             /*将距离为c的元素作为一个子序列进行排序*/
    {
        if(L->data[i].key<L->data[i-c].key)     /*如果后者小于前者，则需要移动元素*/
        {
            t=L->data[i];
            for(j=i-c;j>0&&t.key<L->data[j].key;j=j-c)
                L->data[j+c]=L->data[j];
            L->data[j+c]=t;             /*依次将元素插入到正确的位置*/
        }
    }
}
void ShellInsertSort(SqList *L,int delta[],int m)
/*希尔排序，每次调用算法ShellInsert,delta是存放增量的数组*/
{
    int i;
    for(i=0;i<m;i++)            /*进行m次希尔插入排序*/
    {
        ShellInsert(L,delta[i]);
    }
}
void InitSeqList(SqList *L,DataType a[],int n)
/*顺序表的初始化*/
{
    int i;
    for(i=1;i<=n;i++)
    {
        L->data[i]=a[i-1];
    }
    L->length=n;
}
void DispList(SqList L,int n)
/*顺序表的输出*/
{
    int i;
    for(i=1;i<=n;i++)
        printf("%4d",L.data[i].key);
    printf("\n");
}

void main()
{
    DataType a[]={78,29,45,10,80,21,55,3,60,32};
    int delta[]={5,3,1};
    int n=10,m=3;
    SqList L;
    InitSeqList(&L,a,n);
    printf("[排序前]          ");
    DispList(L,n);
    ShellInsertSort(&L,delta,m);
    printf("[希尔排序结果]    ");
    DispList(L,n);
}
