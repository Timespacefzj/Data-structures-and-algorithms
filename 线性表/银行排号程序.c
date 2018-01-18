#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUEUEMAX 15
typedef struct
{
    int num; //�˿ͱ��
    long time;//�������ʱ��
}DATA;
typedef struct
{
    DATA data[QUEUEMAX]; //��������
    int head; //��ͷ
    int tail; //��β
}CycQueue;
CycQueue *CycQueueInit()
{
    CycQueue *q;
    if(q=(CycQueue *)malloc(sizeof(CycQueue))) //���뱣����е��ڴ�
    {
        q->head = 0;//���ö�ͷ
        q->tail = 0;//���ö�β
        return q;
    }else
        return NULL; //���ؿ�
}
void CycQueueFree(CycQueue *q) //�ͷŶ���
{
    if (q!=NULL)
        free(q);
}
int CycQueueIsEmpty(CycQueue *q)  //�����Ƿ�Ϊ��
{
    return (q->head==q->tail);
}
int CycQueueIsFull(CycQueue *q)//�����Ƿ�����
{
    return ((q->tail+1)%QUEUEMAX==q->head);
}
int CycQueueIn(CycQueue *q,DATA data)//��Ӻ���
{
    if((q->tail+1)%QUEUEMAX == q->head )
    {
        printf("����������\n");
        return 0;
    }else{
        q->tail=(q->tail+1)%QUEUEMAX;//����β���
        q->data[q->tail]=data;
        return 1;
    }
}
DATA *CycQueueOut(CycQueue *q)//ѭ�����еĳ��Ӻ���
{
    if(q->head==q->tail) //����Ϊ��
    {
        printf("�����ѿգ�\n");
        return NULL;
    }else{
        q->head=(q->head+1)%QUEUEMAX;
        return &(q->data[q->head]);
    }
}
int CycQueueLen(CycQueue *q) //��ȡ���г���
{
    int n;
    n=q->tail-q->head;
    if(n<0)
        n=QUEUEMAX+n;
    return n;
}
DATA *CycQueuePeek(CycQueue *q) //��ȡ�Ӷ��е�1��λ�õ�����
{
    if(q->head==q->tail)
    {
        printf("�����Ѿ�Ϊ��!\n");
        return NULL;
    }else{
        return &(q->data[(q->head+1)%QUEUEMAX]);
    }
}

int num;//�˿����
void add(CycQueue *q) //�����˿�����
{
    DATA data;
    if(!CycQueueIsFull(q)) //�������δ��
    {
        data.num=++num;
        data.time=time(NULL);
        CycQueueIn(q,data);
    }
    else
        printf("\n�Ŷӵ���̫�࣬���Ժ����Ŷ�!\n");
}
void next(CycQueue *q) //֪ͨ��һ�˿�׼��
{
    DATA *data;
    if(!CycQueueIsEmpty(q)) //�����в�Ϊ��
    {
        data=CycQueueOut(q); //ȡ����ͷ��������
        printf("\n����Ϊ%d�Ĺ˿Ͱ���ҵ��!\n",data->num);
    }
    if(!CycQueueIsEmpty(q)) //�����в�Ϊ��
    {
        data=CycQueuePeek(q);//ȡ������ָ��λ�õ�����
        printf("����Ϊ%d�Ĺ˿�׼�������Ͻ�Ϊ����ҵ��!\n",data->num);
    }
}
int main()
{
    CycQueue *queue1;
    int i,n;
    char select;
    num=0;//�˿����
    queue1=CycQueueInit(); //��ʼ������
    if(queue1==NULL)
    {
        printf("��������ʱ����\n");
        getch();
        return 0;
    }
    do{
        printf("\n��ѡ��������:\n");
        printf("1.�µ��˿�\n");
        printf("2.��һ���˿�\n");
        printf("0.�˳�\n") ;
        fflush(stdin);
        select=getch();
        switch(select)
        {
            case '1':
                add(queue1);
                printf("\n���ڹ���%dλ�˿��ڵȺ�!\n",CycQueueLen(queue1));
                break;
            case '2':
                next(queue1);
                printf("\n���ڹ���%dλ�˿��ڵȺ�!\n",CycQueueLen(queue1));
                break;
            case '0':
                break;
        }
    }while(select!='0');
    CycQueueFree(queue1); //�ͷŶ���
    getch();
    return 0;
}
