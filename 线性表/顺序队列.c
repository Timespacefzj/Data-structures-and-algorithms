#include <stdio.h>
#define QueueSize 12
typedef char DataType;
typedef struct Squeue{	/*˳��������Ͷ���*/
        DataType queue[QueueSize];
        int front,rear;	/*��ͷָ��Ͷ�βָ��*/
}SeqQueue;

void InitQueue(SeqQueue *SQ)
/*��˳����г�ʼ��Ϊ�ն���ֻ��Ҫ�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0*/
{
    SQ->front=SQ->rear=0;	/*�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0*/
}
int QueueEmpty(SeqQueue SQ)
/*�ж϶����Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0*/
{
   if(SQ.front==SQ.rear)		/*�ж϶�ͷָ��Ͷ�βָ���Ƿ����*/
       return 1;			/*������Ϊ��ʱ������1�����򷵻�0*/
   else
       return 0;
}
int EnQueue(SeqQueue *SQ,DataType e)
/*��Ԫ��x���뵽˳�����SQ�У�����ɹ�����1�����򷵻�0*/
{
   if(SQ->rear==QueueSize)  	/*�ڲ����µ�Ԫ��֮ǰ���ж϶�βָ���Ƿ񵽴���������ֵ�����Ƿ��������*/
       return 0;
   SQ->queue[SQ->rear]=e;	/*�ڶ�β����Ԫ��x */
   SQ->rear=SQ->rear+1;    	/*��βָ������ƶ�һ��λ��*/
   return 1;
}
int DeQueue(SeqQueue *SQ,DataType *e)
/*ɾ��˳������еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0*/
{
   if(SQ->front==SQ->rear)  /*��ɾ��Ԫ��֮ǰ���ж϶����Ƿ�Ϊ��*/
       return 0;
   else
   {
       *e=SQ->queue[SQ->front]; 	/*��Ҫɾ����Ԫ�ظ�ֵ��e*/
       SQ->front=SQ->front+1;	/*����ͷָ������ƶ�һ��λ�ã�ָ���µĶ�ͷ*/
       return 1;
   }
}
int GetHead (SeqQueue SQ,DataType *e)
/*ȡ��ͷԪ�أ�������Ԫ�ظ�ֵ��e��ȡԪ�سɹ�����1�����򷵻�0*/
{
    if(SQ.front==SQ.rear)		/*��ȡ��ͷԪ��֮ǰ���ж�˳��ѭ�������Ƿ�Ϊ��*/
        return 0;
    else
    {
        *e=SCQ.queue[SQ.front];	/*����ͷԪ�ظ�ֵ��e��ȡ����ͷԪ��*/
        return 1;
    }
}
int ClearQueue(SeqQueue *SQ)
/*��ն���*/
{
    SQ->front=SQ->rear=0;     /*����ͷָ��Ͷ�βָ�붼��Ϊ0*/
}
void PrintQueue(SeqQueue SQ)
{
    int cur;
    DataType e;
    printf("��ǰ����Ϊ��\n");
    cur=SQ.front;
    while(cur!=SQ.rear)
    {
        e=SQ.queue[cur++];	/*����ͷԪ�ظ�ֵ��e��ȡ����ͷԪ��*/
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
        printf("��ѡ�������1.���  2.����  3.�˳�\n");
        scanf("%d",&a);
        getchar();
        switch(a)
        {
            case 1:
                if(Q.rear<QueueSize)
                {
                    printf("���������Ԫ�أ�\n");
                    scanf("%c",&e);
                    EnQueue(&Q,e);
                    PrintQueue(Q);
                }
                else
                {
                    printf("����������\n");
                }
                break;
            case 2:
                if(!QueueEmpty(Q))
                {
                    DeQueue(&Q,&e);
                    printf("����Ԫ���ǣ�%c\n",e);
                    PrintQueue(Q);
                }
                break;
            case 3:
            default:
                printf("���������");
                exit(1);
        }

    }
}
