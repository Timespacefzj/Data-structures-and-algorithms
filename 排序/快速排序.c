#include<stdio.h>
#define MAXSIZE 20 /* һ������ʾ����С˳������󳤶� */
#define N 8
 typedef int InfoType; /* ������������������� */
 typedef int KeyType; /* ����ؼ�������Ϊ���� */
 typedef struct
 {
   KeyType key; /* �ؼ����� */
   InfoType otherinfo; /* ������������������������ж��� */
 }RedType; /* ��¼���� */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]���û������ڱ���Ԫ */
   int length; /* ˳����� */
 }SqList; /* ˳������� */
 void QuickSort(SqList *L)
 { /* ��˳���L���������� */
   QSort(L,1,(*L).length);
 }

 void QSort(SqList *L,int low,int high)
 { /* ��˳���L�е�������L.r[low..high]�����������㷨10.7 */
   int pivotloc;
   if(low<high)
   { /* ���ȴ���1 */
     pivotloc=Partition(L,low,high); /* ��L.r[low..high]һ��Ϊ�� */
     QSort(L,low,pivotloc-1); /* �Ե��ӱ�ݹ�����pivotloc������λ�� */
     QSort(L,pivotloc+1,high); /* �Ը��ӱ�ݹ����� */
   }
 }
 int Partition(SqList *L,int low,int high)
 { /* ����˳���L���ӱ�L.r[low..high]�ļ�¼��ʹ�����¼��λ�� */
   /* ������������λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)������ */
   RedType t;
   KeyType pivotkey;
   pivotkey=(*L).r[low].key; /* ���ӱ�ĵ�һ����¼�������¼ */
   while(low<high)
   { /* �ӱ�����˽�������м�ɨ�� */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     t=(*L).r[low]; /* ���������¼С�ļ�¼�������Ͷ� */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     t=(*L).r[low]; /* ���������¼��ļ�¼�������߶� */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
   }
   return low; /* ������������λ�� */
 }

void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ:\n");
   print(l);
   QuickSort(&l);
   printf("�����:\n");
   print(l);
 }
