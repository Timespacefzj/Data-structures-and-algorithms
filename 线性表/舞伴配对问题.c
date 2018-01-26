#include<stdio.h>
#define QueueSize 10
typedef struct{
	char name[20];
	char sex;  /*性别，'F'表示女性，'M'表示男性*/
}Person;
typedef Person DataType;  /* 将队列中元素的数据类型改为Person */
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

void DancePartner(DataType dancer[],int num)
/*结构数组dancer中存放跳舞的男女，num是跳舞的人数*/
{
	int i;
	DataType p;
	SeqQueue Mdancers,Fdancers;
	InitQueue(&Mdancers);/*男士队列初始化*/
	InitQueue(&Fdancers);/*女士队列初始化*/
	for(i=0;i<num;i++){/*依次将跳舞者依其性别入队*/
		p=dancer[i];
		if(p.sex=='F')
			EnQueue(&Fdancers,p);   /*排入女队*/
		else
			EnQueue(&Mdancers,p);   /*排入男队*/
	}
	printf("配对成功的舞伴分别是: \n");
	while(!QueueEmpty(Fdancers)&&!QueueEmpty(Mdancers)){
		/*依次输入男女舞伴名*/
		DeQueue(&Fdancers,&p);     /*女士出队*/
		printf("%s   ",p.name);/*打印出队女士名*/
		DeQueue(&Mdancers,&p);     /*男士出队*/
		printf("%s\n",p.name);    /*打印出队男士名*/
	}
	if(!QueueEmpty(Fdancers)){ /*输出女士剩余人数及队头女士的名字*/
		printf("还有%d名女士等待下一轮舞曲.\n",DancerCount(Fdancers));
		GetHead(Fdancers,&p);  /*取队头*/
		printf("%s 将在下一轮中最先得到舞伴. \n",p.name);
	}
	else if(!QueueEmpty(Mdancers)){/*输出男队剩余人数及队头者名字*/
		printf("还有%d名男士等待下一轮舞曲.\n",DancerCount(Mdancers));
		GetHead(Mdancers,&p);
		printf("%s 将在下一轮中最先得到舞伴.\n",p.name);
	}
}
int DancerCount(SeqQueue Q)
/*队列中等待配对的人数*/
{
	return (Q.rear-Q.front+QueueSize)%QueueSize;
}

void main()
{
	int i,n;
	DataType dancer[30];
	printf("请输入舞池中排队的人数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("姓名:");
		scanf("%s",dancer[i].name);
		getchar();
		printf("性别:");
		scanf("%c",&dancer[i].sex);
	}
	DancePartner(dancer,n);
}
