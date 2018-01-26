#include <stdio.h>
#define QueueSize 12
typedef char DataType;
typedef struct Squeue{	/*顺序队列类型定义*/
        DataType queue[QueueSize];
        int front,rear;	/*队头指针和队尾指针*/
}SeqQueue;

void InitQueue(SeqQueue *SQ)
/*将顺序队列初始化为空队列只需要把队头指针和队尾指针同时置为0*/
{
    SQ->front=SQ->rear=0;	/*把队头指针和队尾指针同时置为0*/
}
int QueueEmpty(SeqQueue SQ)
/*判断队列是否为空，队列为空返回1，否则返回0*/
{
   if(SQ.front==SQ.rear)		/*判断队头指针和队尾指针是否相等*/
       return 1;			/*当队列为空时，返回1；否则返回0*/
   else
       return 0;
}
int EnQueue(SeqQueue *SQ,DataType e)
/*将元素x插入到顺序队列SQ中，插入成功返回1，否则返回0*/
{
   if(SQ->rear==QueueSize)  	/*在插入新的元素之前，判断队尾指针是否到达数组的最大值，即是否队列已满*/
       return 0;
   SQ->queue[SQ->rear]=e;	/*在队尾插入元素x */
   SQ->rear=SQ->rear+1;    	/*队尾指针向后移动一个位置*/
   return 1;
}
int DeQueue(SeqQueue *SQ,DataType *e)
/*删除顺序队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0*/
{
   if(SQ->front==SQ->rear)  /*在删除元素之前，判断队列是否为空*/
       return 0;
   else
   {
       *e=SQ->queue[SQ->front]; 	/*将要删除的元素赋值给e*/
       SQ->front=SQ->front+1;	/*将队头指针向后移动一个位置，指向新的队头*/
       return 1;
   }
}
int GetHead (SeqQueue SQ,DataType *e)
/*取队头元素，并将该元素赋值给e，取元素成功返回1，否则返回0*/
{
    if(SQ.front==SQ.rear)		/*在取队头元素之前，判断顺序循环队列是否为空*/
        return 0;
    else
    {
        *e=SCQ.queue[SQ.front];	/*将队头元素赋值给e，取出队头元素*/
        return 1;
    }
}
int ClearQueue(SeqQueue *SQ)
/*清空队列*/
{
    SQ->front=SQ->rear=0;     /*将队头指针和队尾指针都置为0*/
}
void PrintQueue(SeqQueue SQ)
{
    int cur;
    DataType e;
    printf("当前队列为：\n");
    cur=SQ.front;
    while(cur!=SQ.rear)
    {
        e=SQ.queue[cur++];	/*将队头元素赋值给e，取出队头元素*/
        printf("%c ",e);
    }
    printf("\n");
}

void main()
{
    int i,a;
    DataType p[12],e;
    SeqQueue Q;
    InitQueue(&Q);
    while(1)
    {
        printf("请选择操作：1.入队  2.出队  3.退出\n");
        scanf("%d",&a);
        getchar();
        switch(a)
        {
            case 1:
                if(Q.rear<QueueSize)
                {
                    printf("请输入入队元素：\n");
                    scanf("%c",&e);
                    EnQueue(&Q,e);
                    PrintQueue(Q);
                }
                else
                {
                    printf("队列已满！\n");
                }
                break;
            case 2:
                if(!QueueEmpty(Q))
                {
                    DeQueue(&Q,&e);
                    printf("出队元素是：%c\n",e);
                    PrintQueue(Q);
                }
                break;
            case 3:
            default:
                printf("程序结束！");
                exit(1);
        }

    }
}
