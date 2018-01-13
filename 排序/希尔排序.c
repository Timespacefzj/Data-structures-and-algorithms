#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
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
void ShellInsert(SqList *L,int c)
/*��˳���L����һ��ϣ������c������*/
{
    int i,j;
    DataType t;
    for(i=c+1;i<=L->length;i++)             /*������Ϊc��Ԫ����Ϊһ�������н�������*/
    {
        if(L->data[i].key<L->data[i-c].key)     /*�������С��ǰ�ߣ�����Ҫ�ƶ�Ԫ��*/
        {
            t=L->data[i];
            for(j=i-c;j>0&&t.key<L->data[j].key;j=j-c)
                L->data[j+c]=L->data[j];
            L->data[j+c]=t;             /*���ν�Ԫ�ز��뵽��ȷ��λ��*/
        }
    }
}
void ShellInsertSort(SqList *L,int delta[],int m)
/*ϣ������ÿ�ε����㷨ShellInsert,delta�Ǵ������������*/
{
    int i;
    for(i=0;i<m;i++)            /*����m��ϣ����������*/
    {
        ShellInsert(L,delta[i]);
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
/*˳�������*/
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
    printf("[����ǰ]          ");
    DispList(L,n);
    ShellInsertSort(&L,delta,m);
    printf("[ϣ��������]    ");
    DispList(L,n);
}
