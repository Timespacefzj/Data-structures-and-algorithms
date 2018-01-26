#include<stdio.h>
#define QueueSize 10
typedef struct{
	char name[20];
	char sex;  /*�Ա�'F'��ʾŮ�ԣ�'M'��ʾ����*/
}Person;
typedef Person DataType;  /* ��������Ԫ�ص��������͸�ΪPerson */
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

void DancePartner(DataType dancer[],int num)
/*�ṹ����dancer�д���������Ů��num�����������*/
{
	int i;
	DataType p;
	SeqQueue Mdancers,Fdancers;
	InitQueue(&Mdancers);/*��ʿ���г�ʼ��*/
	InitQueue(&Fdancers);/*Ůʿ���г�ʼ��*/
	for(i=0;i<num;i++){/*���ν������������Ա����*/
		p=dancer[i];
		if(p.sex=='F')
			EnQueue(&Fdancers,p);   /*����Ů��*/
		else
			EnQueue(&Mdancers,p);   /*�����ж�*/
	}
	printf("��Գɹ������ֱ���: \n");
	while(!QueueEmpty(Fdancers)&&!QueueEmpty(Mdancers)){
		/*����������Ů�����*/
		DeQueue(&Fdancers,&p);     /*Ůʿ����*/
		printf("%s   ",p.name);/*��ӡ����Ůʿ��*/
		DeQueue(&Mdancers,&p);     /*��ʿ����*/
		printf("%s\n",p.name);    /*��ӡ������ʿ��*/
	}
	if(!QueueEmpty(Fdancers)){ /*���Ůʿʣ����������ͷŮʿ������*/
		printf("����%d��Ůʿ�ȴ���һ������.\n",DancerCount(Fdancers));
		GetHead(Fdancers,&p);  /*ȡ��ͷ*/
		printf("%s ������һ�������ȵõ����. \n",p.name);
	}
	else if(!QueueEmpty(Mdancers)){/*����ж�ʣ����������ͷ������*/
		printf("����%d����ʿ�ȴ���һ������.\n",DancerCount(Mdancers));
		GetHead(Mdancers,&p);
		printf("%s ������һ�������ȵõ����.\n",p.name);
	}
}
int DancerCount(SeqQueue Q)
/*�����еȴ���Ե�����*/
{
	return (Q.rear-Q.front+QueueSize)%QueueSize;
}

void main()
{
	int i,n;
	DataType dancer[30];
	printf("������������Ŷӵ�����:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("����:");
		scanf("%s",dancer[i].name);
		getchar();
		printf("�Ա�:");
		scanf("%c",&dancer[i].sex);
	}
	DancePartner(dancer,n);
}
