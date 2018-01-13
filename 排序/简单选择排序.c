#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
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
void SelectSort(SqList *L,int n)
/*简单选择排序*/
{
    int i,j,k;
    DataType t;
    /*将第i个元素的关键字与后面[i+1...n]个元素的关键字比较，将关键字最小的的元素放在第i个位置*/
    for(i=1;i<=n-1;i++)
    {
        j=i;
        for(k=i+1;k<=n;k++) /*关键字最小的元素的序号为j*/
            if(L->data[k].key<L->data[j].key)
                j=k;
        if(j!=i)            /*如果序号i不等于j，则需要将序号i和序号j的元素交换*/
        {
            t=L->data[i];
            L->data[i]=L->data[j];
            L->data[j]=t;
        }
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
/*输出表中的元素*/
{
    int i;
    for(i=1;i<=n;i++)
        printf("%4d",L.data[i].key);
    printf("\n");
}
void main()
{
    DataType a[]={69,62,50,58,42,42,27,53};
    SqList L;
    int n=sizeof(a)/sizeof(a[0]);
    InitSeqList(&L,a,n);
    printf("[排序前]          ");
    DispList(L,n);
    SelectSort(&L,n);
    printf("[简单选择排序结果]");
    DispList(L,n);
}
