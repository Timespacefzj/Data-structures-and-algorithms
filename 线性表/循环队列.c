#include<stdio.h>
#define QueueSize 10		/*定义顺序循环队列的最大容量*/
typedef char DataType;		/*定义顺序循环队列元素的类型为字符类型*/
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
   if(SQ->front==(SQ->rear+1)%QueueSize)  	                  /*在插入新的元素之前，判断队尾指针是否到达数组的最大值，即是否队列已满*/
       return 0;
   SQ->queue[SQ->rear]=e;	/*在队尾插入元素x */
   SQ->rear=(SQ->rear+1)%QueueSize;    	/*队尾指针向后移动一个位置*/
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
       SQ->front=(SQ->front+1)%QueueSize;	/*将队头指针向后移动一个位置，指向新的队头*/
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
        *e=SQ.queue[SQ.front];	/*将队头元素赋值给e，取出队头元素*/
        return 1;
    }
}
void DisplayQueue(SeqQueue SQ)
/*顺序循环队列的显示输出函数。首先判断队列是否为空，输出时还应考虑队头指针和队尾指针值的大小问题*/
{
	int i;
	if(QueueEmpty(SQ))				/*判断顺序循环队列是否为空*/
       return 0;
	if(SQ.front<SQ.rear)
/*如果队头指针值小于队尾指针的值，则把队头指针到队尾指针指向的元素依次输出*/
		for(i=SQ.front;i<SQ.rear;i++)
			printf("%c ",SQ.queue[i]);
	else
/*如果队头指针值大于队尾指针的值，则把队尾指针到队头指针指向的元素依次输出*/
		for(i=SQ.front;i<SQ.rear+QueueSize;i++)
			printf("%c ",SQ.queue[i%QueueSize]);
    printf("\n");
}
void main()
{
	SeqQueue Q;						/*定义一个顺序循环队列*/
	char e;							/*定义一个字符类型变量，用于存放出队列的元素*/
	InitQueue(&Q);						/*初始化顺序循环队列*/
/*将3个元素A，B，C依次进入顺序循环队列*/
	printf("A入队\n");
	EnQueue(&Q,'A');
	printf("B入队\n");
	EnQueue(&Q,'B');
	printf("C入队\n");
	EnQueue(&Q,'C');
/*将顺序循环队列中的元素显示输出*/
	printf("队列中元素：");
	DisplayQueue(Q);
/*将顺序循环队列中的队头元素出队列*/
	printf("队头元素第一次出队\n");
	DeQueue(&Q,&e);
	printf("出队的元素：");
	printf("%c\n",e);
	printf("队头元素第二次出队\n");
	DeQueue(&Q,&e);
	printf("出队的元素：");
	printf("%c\n",e);
/*将顺序循环队列中的元素显示输出*/
	printf("队列中元素：");
	DisplayQueue(Q);
/*将3个元素D，E，F依次进入顺序循环队列*/
	printf("D入队\n");
	EnQueue(&Q,'D');
	printf("E入队\n");
	EnQueue(&Q,'E');
	printf("F入队\n");
	EnQueue(&Q,'F');
/*将顺序循环队列中的元素显示输出*/
	printf("队列中元素：");
	DisplayQueue(Q);
}
