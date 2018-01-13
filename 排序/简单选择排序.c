#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
typedef int KeyType;
typedef struct /*����Ԫ�����Ͷ���*/
{
    KeyType key;/*�ؼ���*/
}DataType;
typedef struct /*˳������Ͷ���*/
 {
    DataType data[MaxSize];
    int length;
}SqList;
void SelectSort(SqList *L,int n)
/*��ѡ������*/
{
    int i,j,k;
    DataType t;
    /*����i��Ԫ�صĹؼ��������[i+1...n]��Ԫ�صĹؼ��ֱȽϣ����ؼ�����С�ĵ�Ԫ�ط��ڵ�i��λ��*/
    for(i=1;i<=n-1;i++)
    {
        j=i;
        for(k=i+1;k<=n;k++) /*�ؼ�����С��Ԫ�ص����Ϊj*/
            if(L->data[k].key<L->data[j].key)
                j=k;
        if(j!=i)            /*������i������j������Ҫ�����i�����j��Ԫ�ؽ���*/
        {
            t=L->data[i];
            L->data[i]=L->data[j];
            L->data[j]=t;
        }
    }
}

void InitSeqList(SqList *L,DataType a[],int n)
/*˳���ĳ�ʼ��*/
{
    int i;
    for(i=1;i<=n;i++)
    {
        L->data[i]=a[i-1];
    }
    L->length=n;

}
void DispList(SqList L,int n)
/*������е�Ԫ��*/
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
    printf("[����ǰ]          ");
    DispList(L,n);
    SelectSort(&L,n);
    printf("[��ѡ��������]");
    DispList(L,n);
}
