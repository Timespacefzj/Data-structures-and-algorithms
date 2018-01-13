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

void InsertSort(SqList *L)
/*直接插入排序*/
{
    int i,j;
    DataType t;
    for(i=1;i<L->length;i++)        /*前i个元素已经有序，从第i+1个元素开始与前i个有序的关键字比较*/
    {
        t=L->data[i+1];             /*取出第i+1个元素，即待排序的元素*/
        j=i;
        while(j>0&&t.key<L->data[j].key)/*寻找当前元素的合适位置*/
        {
            L->data[j+1]=L->data[j];
            j--;
        }
        L->data[j+1]=t;             /*将当前元素插入合适的位置*/
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
    InsertSort(&L);
    printf("[直接插入排序结果]");
    DispList(L,n);
}
