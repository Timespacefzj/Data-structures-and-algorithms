 #define LT(a,b) ((a)<(b))
 #define N 8
 #define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */

 typedef int InfoType; /* 定义其它数据项的类型 */
 typedef int KeyType; /* 定义关键字类型为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
   int length; /* 顺序表长度 */
 }SqList; /* 顺序表类型 */

 void BinInsertSort(SqList *L)
/*折半插入排序*/
{
    int i,j,mid,low,high;
    RedType t;
    for(i=1;i<L->length;i++)        /*前i个元素已经有序，从第i+1个元素开始与前i个的有序的关键字比较*/
    {
        t=L->r[i+1];             /*取出第i+1个元素，即待排序的元素*/
        low=1,high=i;
        while(low<=high)            /*利用折半查找思想寻找当前元素的合适位置*/
        {
            mid=(low+high)/2;
            if(L->r[mid].key>t.key)
                high=mid-1;
            else
                low=mid+1;
        }
        for(j=i;j>=low;j--)     /*移动元素，空出要插入的位置*/
            L->r[j+1]=L->r[j];
        L->r[low]=t;         /*将当前元素插入合适的位置*/
    }
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
   for(i=0;i<N;i++) /* 给l1.r赋值 */
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   BinInsertSort(&l);
   printf("折半插入排序后:\n");
   print(l);
 }
