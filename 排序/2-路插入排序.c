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

 void P2_InsertSort(SqList *L)
 { /* 2_·�������� */
   int i,j,first,final;
   RedType *d;
   d=(RedType*)malloc((*L).length*sizeof(RedType)); /* ����L.length����¼����ʱ�ռ� */
   d[0]=(*L).r[1]; /* ��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0]) */
   first=final=0; /* first��final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ�� */
   for(i=2;i<=(*L).length;++i)
   { /* ���ν�L�ĵ�2�������1����¼����d�� */
     if ((*L).r[i].key<d[first].key)
     { /* �����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��) */
       first=(first-1+(*L).length)%(*L).length; /* ��dΪѭ������ */
       d[first]=(*L).r[i];
     }
     else if((*L).r[i].key>d[final].key)
     { /* �����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��) */
       final=final+1;
       d[final]=(*L).r[i];
     }
     else
     { /* �����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��) */
       j=final++; /* �ƶ�d��β��Ԫ���Ա㰴������¼ */
       while((*L).r[i].key<d[j].key)
       {
         d[(j+1)%(*L).length]=d[j];
         j=(j-1+(*L).length)%(*L).length;
       }
       d[j+1]=(*L).r[i];
     }
   }
   for(i=1;i<=(*L).length;i++) /* ��d����L.r */
     (*L).r[i]=d[(i+first-1)%(*L).length]; /* ���Թ�ϵ */
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
   for(i=0;i<N;i++) /* ��l1.r��ֵ */
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ:\n");
   print(l);
   P2_InsertSort(&l);
   printf("2_·���������:\n");
   print(l);
 }
