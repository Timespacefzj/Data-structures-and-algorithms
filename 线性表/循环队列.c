#include<stdio.h>
#define QueueSize 10		/*����˳��ѭ�����е��������*/
typedef char DataType;		/*����˳��ѭ������Ԫ�ص�����Ϊ�ַ�����*/
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
   if(SQ->front==(SQ->rear+1)%QueueSize)  	                  /*�ڲ����µ�Ԫ��֮ǰ���ж϶�βָ���Ƿ񵽴���������ֵ�����Ƿ��������*/
       return 0;
   SQ->queue[SQ->rear]=e;	/*�ڶ�β����Ԫ��x */
   SQ->rear=(SQ->rear+1)%QueueSize;    	/*��βָ������ƶ�һ��λ��*/
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
       SQ->front=(SQ->front+1)%QueueSize;	/*����ͷָ������ƶ�һ��λ�ã�ָ���µĶ�ͷ*/
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
        *e=SQ.queue[SQ.front];	/*����ͷԪ�ظ�ֵ��e��ȡ����ͷԪ��*/
        return 1;
    }
}
void DisplayQueue(SeqQueue SQ)
/*˳��ѭ�����е���ʾ��������������ж϶����Ƿ�Ϊ�գ����ʱ��Ӧ���Ƕ�ͷָ��Ͷ�βָ��ֵ�Ĵ�С����*/
{
	int i;
	if(QueueEmpty(SQ))				/*�ж�˳��ѭ�������Ƿ�Ϊ��*/
       return 0;
	if(SQ.front<SQ.rear)
/*�����ͷָ��ֵС�ڶ�βָ���ֵ����Ѷ�ͷָ�뵽��βָ��ָ���Ԫ���������*/
		for(i=SQ.front;i<SQ.rear;i++)
			printf("%c ",SQ.queue[i]);
	else
/*�����ͷָ��ֵ���ڶ�βָ���ֵ����Ѷ�βָ�뵽��ͷָ��ָ���Ԫ���������*/
		for(i=SQ.front;i<SQ.rear+QueueSize;i++)
			printf("%c ",SQ.queue[i%QueueSize]);
    printf("\n");
}
void main()
{
	SeqQueue Q;						/*����һ��˳��ѭ������*/
	char e;							/*����һ���ַ����ͱ��������ڴ�ų����е�Ԫ��*/
	InitQueue(&Q);						/*��ʼ��˳��ѭ������*/
/*��3��Ԫ��A��B��C���ν���˳��ѭ������*/
	printf("A���\n");
	EnQueue(&Q,'A');
	printf("B���\n");
	EnQueue(&Q,'B');
	printf("C���\n");
	EnQueue(&Q,'C');
/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
/*��˳��ѭ�������еĶ�ͷԪ�س�����*/
	printf("��ͷԪ�ص�һ�γ���\n");
	DeQueue(&Q,&e);
	printf("���ӵ�Ԫ�أ�");
	printf("%c\n",e);
	printf("��ͷԪ�صڶ��γ���\n");
	DeQueue(&Q,&e);
	printf("���ӵ�Ԫ�أ�");
	printf("%c\n",e);
/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
/*��3��Ԫ��D��E��F���ν���˳��ѭ������*/
	printf("D���\n");
	EnQueue(&Q,'D');
	printf("E���\n");
	EnQueue(&Q,'E');
	printf("F���\n");
	EnQueue(&Q,'F');
/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
}
