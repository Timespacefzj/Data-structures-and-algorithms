#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUEUEMAX 15
typedef struct
{
    int num; //顾客编号
    long time;//进入队列时间
}DATA;
typedef struct
{
    DATA data[QUEUEMAX]; //队列数组
    int head; //队头
    int tail; //队尾
}CycQueue;
CycQueue *CycQueueInit()
{
    CycQueue *q;
    if(q=(CycQueue *)malloc(sizeof(CycQueue))) //申请保存队列的内存
    {
        q->head = 0;//设置队头
        q->tail = 0;//设置队尾
        return q;
    }else
        return NULL; //返回空
}
void CycQueueFree(CycQueue *q) //释放队列
{
    if (q!=NULL)
        free(q);
}
int CycQueueIsEmpty(CycQueue *q)  //队列是否为空
{
    return (q->head==q->tail);
}
int CycQueueIsFull(CycQueue *q)//队列是否已满
{
    return ((q->tail+1)%QUEUEMAX==q->head);
}
int CycQueueIn(CycQueue *q,DATA data)//入队函数
{
    if((q->tail+1)%QUEUEMAX == q->head )
    {
        printf("队列已满！\n");
        return 0;
    }else{
        q->tail=(q->tail+1)%QUEUEMAX;//求列尾序号
        q->data[q->tail]=data;
        return 1;
    }
}
DATA *CycQueueOut(CycQueue *q)//循环队列的出队函数
{
    if(q->head==q->tail) //队列为空
    {
        printf("队列已空！\n");
        return NULL;
    }else{
        q->head=(q->head+1)%QUEUEMAX;
        return &(q->data[q->head]);
    }
}
int CycQueueLen(CycQueue *q) //获取队列长度
{
    int n;
    n=q->tail-q->head;
    if(n<0)
        n=QUEUEMAX+n;
    return n;
}
DATA *CycQueuePeek(CycQueue *q) //获取队定中第1个位置的数据
{
    if(q->head==q->tail)
    {
        printf("队列已经为空!\n");
        return NULL;
    }else{
        return &(q->data[(q->head+1)%QUEUEMAX]);
    }
}

int num;//顾客序号
void add(CycQueue *q) //新增顾客排列
{
    DATA data;
    if(!CycQueueIsFull(q)) //如果队列未满
    {
        data.num=++num;
        data.time=time(NULL);
        CycQueueIn(q,data);
    }
    else
        printf("\n排队的人太多，请稍候再排队!\n");
}
void next(CycQueue *q) //通知下一顾客准备
{
    DATA *data;
    if(!CycQueueIsEmpty(q)) //若队列不为空
    {
        data=CycQueueOut(q); //取队列头部的数据
        printf("\n请编号为%d的顾客办理业务!\n",data->num);
    }
    if(!CycQueueIsEmpty(q)) //若队列不为空
    {
        data=CycQueuePeek(q);//取队列中指定位置的数据
        printf("请编号为%d的顾客准备，马上将为您理业务!\n",data->num);
    }
}
int main()
{
    CycQueue *queue1;
    int i,n;
    char select;
    num=0;//顾客序号
    queue1=CycQueueInit(); //初始化队列
    if(queue1==NULL)
    {
        printf("创建队列时出错！\n");
        getch();
        return 0;
    }
    do{
        printf("\n请选择具体操作:\n");
        printf("1.新到顾客\n");
        printf("2.下一个顾客\n");
        printf("0.退出\n") ;
        fflush(stdin);
        select=getch();
        switch(select)
        {
            case '1':
                add(queue1);
                printf("\n现在共有%d位顾客在等候!\n",CycQueueLen(queue1));
                break;
            case '2':
                next(queue1);
                printf("\n现在共有%d位顾客在等候!\n",CycQueueLen(queue1));
                break;
            case '0':
                break;
        }
    }while(select!='0');
    CycQueueFree(queue1); //释放队列
    getch();
    return 0;
}
