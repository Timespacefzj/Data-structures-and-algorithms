#include <stdio.h>
#include <stdlib.h>         //malloc
#include <time.h>             //��ȡϵͳʱ�����ú���
#include <conio.h>            //getch()
#include <windows.h>          //���ù����Ϣ mallco

#define MaxSize 5          /*����ͣ����ջ����*/
#define PRICE 0.05         /*ÿ��ÿ�����շ�ֵ*/
#define BASEPRICE 0.5      //����ͣ����
#define Esc 27             //�˳�ϵͳ
#define Exit 3				//�����Ի�
#define Stop 1				//ͣ��
#define Drive 2				//ȡ��

int jx=0,jy=32;               //ȫ�ֱ�����־��ӡλ��

typedef struct
{
    int hour;
    int minute;
}Time,*PTime;                     /*ʱ����*/

typedef struct             /*����ջԪ�ص����ͼ�������Ϣ���*/
{
    int num ;                 /*���ƺ�*/
    Time arrtime;             /*����ʱ�̻�����ʱ��*/
}CarNode;

typedef struct             /*����ջ,ģ��ͣ����*/
{
    CarNode stack[MaxSize];
    int top;
}SqStackCar;

typedef struct node        /*������н�������*/
{
    int num;                  /*���ƺ�*/
    struct node *next;
}QueueNode;

typedef struct                              /*�������,ģ����*/
{
    QueueNode *front,*rear;
}LinkQueueCar;


 /*��ʼ��ջ*/
void InitSeqStack(SqStackCar *s)
{
	s->top=-1;
}
/* push��վ���� */
int push(SqStackCar *s,CarNode x)            //����Ԫ��x��ָ��s��ָ��ջ
{
	if(s->top==MaxSize-1)
		return(0);							//���ջ��,����0
	else
	{
		s->stack[++s->top]=x;				//ջ����,���ﳵ����ջ
		return(1);
	}
}
/*ջ��Ԫ�س�ջ*/
CarNode pop(SqStackCar *s)
{
	CarNode x;
	if(s->top<0)
	{
		x.num=0;
	    x.arrtime.hour=0;
		x.arrtime.minute=0;
		return(x);                             //���ջ��,���ؿ�ֵ
	}
	else
	{
		s->top--;
		return(s->stack[s->top+1]);             //ջ����,����ջ��Ԫ��
	}
}
/*��ʼ������*/
void InitLinkQueue(LinkQueueCar *q)
{
	q->front=(QueueNode*)malloc(sizeof(QueueNode));  //����һ���½��,��ͷ���
	if(q->front!=NULL)
	{
		q->rear=q->front;
		q->front->next=NULL;
		q->front->num=0;                       //ͷ����num�������������Ԫ�صĸ���
	}
}
/*���������*/
void EnLinkQueue(LinkQueueCar *q,int x)
{
	QueueNode *p;
	p=(QueueNode*)malloc(sizeof(QueueNode));       //����һ���½��
	p->num=x;
	p->next=NULL;
	q->rear->next=p;                               //�½�������
	q->rear=p;
	q->front->num++;                               //����Ԫ�ظ�����1
}
/*���ݳ�����*/
int DeLinkQueue(LinkQueueCar *q)
{
	QueueNode *p;
	int n;
	if(q->front==q->rear)                          //�ӿշ���0
		return(0);
	else
	{
		p=q->front->next;
		q->front->next=p->next;
		if(p->next==NULL)
			q->rear=q->front;
		n=p->num;
		free(p);
			q->front->num--;
		return(n);                                 //���س��ӵ�������Ϣ
	}
}
/*********************         ��������     ***************************/
//������ͣ��ջ ͣ������ ������Ϣ
//����ֵ����
//���ܣ��Դ���ĳ���������ջ ջ���������
void Arrive(SqStackCar *stop,LinkQueueCar *lq,CarNode x)
{
	int f;
	f=push(stop,x);                                         //��ջ
	if (f==0)              //ջ��
	{
		EnLinkQueue(lq,x.num);               //���
		printstop(1,lq->front->num,0,23);
		printlog(x.arrtime,x.num,1,'B',lq->front->num,0);
	    qingping(0);	printf("���ĳ�ͣ�ڱ��%d�ų�λ��\n",lq->front->num);		//���¶Ի�
	}
	else
	{
		printstop(0,stop->top+1,0,23);
		printlog(x.arrtime,x.num,1,'P',stop->top+1,0);
		qingping(0);    printf("���ĳ�ͣ��ͣ����%d�ų�λ��\n",stop->top+1);			//���¶Ի�
	}
	qingping(1);	printf("�����������");
	getch();
}
/**************************        �����뿪         *************************************/
//������ͣ��ջָ��s1���ݴ�ջָ��s2��ͣ������ָ��p��������Ϣx
//����ֵ����
//���ܣ�����ջ��s1��x����ջ��ջ��û������Ҷ�p�в����ӣ���ӡ�뿪�շ���Ϣ
void Leave(SqStackCar *s1,SqStackCar *s2,LinkQueueCar *p,CarNode x)
{
	double fee=0;
	int position=s1->top+1;                          //�������ڳ�λ
	int n,f=0;
	CarNode y;
	QueueNode *q;
	while((s1->top > -1)&&(f!=1))             //��ջ������δ�ҵ�x
	{
		y=pop(s1);
		if(y.num!=x.num)
		{
		    n=push(s2,y);
			position--;
		}
		else
			f=1;
	}
	if(y.num==x.num)                      //�ҵ�x
	{
		gotoxy(33,17);	printf("%d:%-2d",(x.arrtime.hour-y.arrtime.hour),(x.arrtime.minute-y.arrtime.minute) );
		fee=((x.arrtime.hour-y.arrtime.hour)*60+(x.arrtime.minute-y.arrtime.minute))*PRICE+BASEPRICE;
		gotoxy(48,17);	printf("%2.1fԪ\n",fee);
		qingping(0);	printf("ȷ�����ĳ�����Ϣ");
		qingping(1); printf("�����������");
		getch();
		while(s2->top>-1)
		{   y=pop(s2);
			f=push(s1,y);
		}
		n=DeLinkQueue(p);
		if(n!=0)
		{
			y.num=n;
			y.arrtime=x.arrtime;
			f=push(s1,y);
			printleave(p->front->num+1,position,s1->top+1);                    //��ջ����ji���г�Ա��ջ
			printlog(x.arrtime,x.num,0,'P',position,fee);
			printlog(y.arrtime,y.num,1,'P',s1->top+1,0);
		}
		else
		{
			printleave(0,position,s1->top+2);
			printlog(x.arrtime,x.num,0,'P',position,fee);
		}
	}
	else                               //��ջ����x
	{
		while(s2->top > -1)           //��ԭջ
		{
            y=pop(s2);
	        f=push(s1,y);
		}
		q=p->front;
		f=0;
		position=1;
		while(f==0&&q->next!=NULL)     //���Ӳ�����δ�ҵ�x
		if(q->next->num!=x.num)
		{
			q=q->next;
			position++;
		}
		else                          //�ҵ�x
		{
			q->next=q->next->next;
			p->front->num--;
			if(q->next==NULL)
			p->rear=p->front;
			gotoxy(33,17);	printf("0:0");
			gotoxy(48,17);	printf("0Ԫ");
			qingping(0);		printf("���ĳ�������");
			qingping(1);		printf("�����������");
			getch();
			printleave(-1,position,p->front->num+1);                  //���Ӷ���
			printlog(x.arrtime,x.num,0,'B',position,0);
			f=1;
		}
		if(f==0)                                          //δ�ҵ�x
		{
			qingping(0);		printf("ͣ�����ͱ���Ͼ������ĳ�");
			qingping(1);		printf("�����������");
			getch();
		}
	}
}
/*��ȡϵͳʱ��*/
//����PTime����
PTime get_time()
{
	Time *t;
	time_t timer;
    struct tm *tblock;
	t=(Time*)malloc(sizeof(Time));

    timer=time(NULL);
    tblock=localtime(&timer);
	t->minute=tblock->tm_min;
	t->hour=tblock->tm_hour;
	return t;
}
/*�ƶ����*/
//������ƶ�����x��y����
void gotoxy(int x,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y+3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*��ͼ*/
//����ϵͳ����
void panitPL()
{
	int i,j,x,y,a[2][4]={2,0,0,1,-2,0,0,-1};      //����];
	gotoxy(20,4);
	printf("****************�Ի���****************");
	x=18,y=6;                                      //��ʼ��

	for(i=0;i<2 ;i++)
	{
		for(j=0; j<20; j++)
		{

			x+=a[i][0];	y+=a[i][1];
			gotoxy(x,y);
			printf("�T");
		}
		x+=a[i][0];	y+=a[i][1];
		gotoxy(x,y);
		if(i==0)
		    printf("�[");
		else
			printf("�^");
		for(j=0; j<12; j++)
		{
			x+=a[i][2];   y+=a[i][3];
			gotoxy(x,y);
			printf("�U");
		}
		x+=a[i][2];   y+=a[i][3];
		gotoxy(x,y);
		if(i==0)
			printf("�a");
		else
			printf("�X");

	}
	gotoxy(22,8);
	printf("С�ţ�");
	gotoxy(22,11);
	printf("�˿ͣ�");
	gotoxy(22,14);	printf("*********** ͣ����Ϣ ***********");
	gotoxy(23,15);	printf("���ƺţ�");
	gotoxy(42,15);	printf("ʱ�䣺");
	gotoxy(23,17);	printf("ͣ��ʱ����");
	gotoxy(42,17);	printf("�շѣ�");
}
/*��������*/
//���¶Ի���ǰ��ԭ�Ի����
void qingping(int a)
{
	if(a==0)                      //���С�ŵĶԻ�
	{
		gotoxy(28,8);	printf("                                ");
		gotoxy(28,9);	printf("                                ");
		gotoxy(28,8);
	}
	else if(a==1)                  //��չ˿͵ĶԻ�
	{
		gotoxy(28,11);	printf("                    ");
		gotoxy(28,12);	printf("                    ");
		gotoxy(28,13);	printf("                    ");
		gotoxy(28,11);
	}
	else                           //��ճ�����Ϣ
	{
		gotoxy(31,15);	printf("          ");
		gotoxy(48,15);	printf("          ");
		gotoxy(33,17);	printf("         ");
		gotoxy(48,17);	printf("         ");
		gotoxy(31,15);
	}
}
//�����¼��ƶ�ѡ��
int getkey()
{
	char c;
	int x=28,y=11;
	while(1)
	{
		gotoxy(x,11);	printf("  ");
		gotoxy(x,12);	printf("  ");
		gotoxy(x,13);	printf("  ");
		gotoxy(x,y);	printf(">>");
        c=getch();
		if(c==13) return y-10;			//enter�����ص�ǰѡ��
		if(c!=-32)continue;				//���Ƿ���������´�ѭ��
		c=getch();
		if(c==72) if(y>11) y--;         //��
		if(c==80) if(y<13) y++;         //��
	}
}


//���복����Ϣ
CarNode getcarInfo()
{
	PTime T;
	CarNode x;
	qingping(0);	printf("���������ĳ��ƺ�\n");
	qingping(1);	printf("���������복����Ϣ");
	qingping(2);
	scanf("%d",&(x.num));
	T=get_time();
	x.arrtime=*T;
	gotoxy(48,15);	printf("%d:%d",x.arrtime.hour,x.arrtime.minute);
	getch();
	return x;
}
//��ӡͣ����
void printcar()
{
	gotoxy(0,20);					//�X �[�a�^�T�U
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	printf("                            �����ݷ���  �U  1     2     3     4     5         �U");
	printf("-----------------------------------------------------------------------------�U");
	printf("                              ������                                         �U");
	printf("-----------------------------------------------------------------------------�U");
	printf("  12    11    10    9     8     7     6     5     4     3     2     1        �U");
	printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[      �U");
	printf("              ��                        �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a      �U");
	printf("             ���             ͣ���� �� �U  1     2     3     4     5          �U");
	printf("                                       �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	printf("                     ͣ����������־\n\n");
	printf("  ʱ��     ���ƺ�    ��(1)/��(0)     ��λ(B���Pͣ����)    �շ�(Ԫ)  ");
}
//��ӡ��־��¼
void printlog(Time t,int n,int io,char ab,int po,double f)
{
	jy++;
	gotoxy(jx,jy);
//	printf("  ʱ��     ���ƺ�    ��(1)/��(0)     ��λ(B���Pͣ����)    �շ�(Ԫ)  ");
	if(io==0)
		printf("                                                         /  %2.1f",f);
	gotoxy(jx,jy);
	printf("                   /     %d        /    %c:%d",io,ab,po);
	gotoxy(jx,jy);
	printf("  %d:%d /  %d",t.hour,t.minute,n);
}
void printstop(int a,int num,int x0,int y0)
{
	static char *car="������";
//	int x0=0,y0=23;
	int x=0,y=28;
	if(a==0)
	{
		x=(num+6)*6;
		for(;x0<72;x0++)
		{
			gotoxy(x0,y0);	printf("%s",car);	Sleep(30);
			gotoxy(x0,y0);	printf("      ");
		}
		for(;y0<y;y0++)
		{
			gotoxy(x0,y0);	printf("%s",car);	Sleep(100);
			gotoxy(x0,y0);	printf("      ");
		}
		for(;x0>x;x0--)
		{
			gotoxy(x0,y0);	printf("%s",car);	Sleep(50);
			gotoxy(x0,y0);	printf("      ");
		}
		gotoxy(x,y);
		printf("%s",car);
	}
	else
	{
		x=(12-num)*6;
		y=y-3;
		for(;x0<x;x0++)
		{
			gotoxy(x0,y0);	printf("%s",car);	Sleep(30);
			gotoxy(x0,y0);	printf("      ");
		}
		gotoxy(x,y);
		printf("%s",car);
	}


}
void printleave(int a,int po,int num)
{
	static char *car="������";
	int x0=0,y0=23;
	int x=0,y=28;
	int i;
	if(a==-1)
	{
	    x=(12-po)*6;
		y=y-3;
		gotoxy(x,y);	printf("      ");
		gotoxy(x,y-2);  printf("%s",car);
		Sleep(100);
		if(12>num)
		{
			gotoxy((12-num)*6,y);
			printf("      ");
		}
		gotoxy(x,y);	printf("%s",car);
		for(;x>x0;x--)
		{
			gotoxy(x,y-2);  printf("%s",car);	Sleep(30);
			gotoxy(x,y-2);	printf("      ");
		}
	}
	else
	{
		i=num+1;
		for(;num>po;num--)
		{
			x=(num+6)*6;	y=28;
			for(;x<72;x++)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(30);
				gotoxy(x,y);	printf("      ");
			}
			for(;y>21;y--)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(50);
				gotoxy(x,y);	printf("      ");
			}
			for(;x>(i-num+6)*6;x--)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(30);
				gotoxy(x,y);	printf("      ");
			}
			gotoxy(x,y);	printf("%s",car);
		}
		x=(po+6)*6;	y=28;
	    for(;x<72;x++)
		{
			gotoxy(x,y);	printf("%s",car);	Sleep(30);
			gotoxy(x,y);	printf("      ");
		}
		for(;y>23;y--)
		{
			gotoxy(x,y);	printf("%s",car);	Sleep(50);
			gotoxy(x,y);	printf("      ");
		}
		for(;x>0;x--)
		{
			gotoxy(x,y);	printf("%s",car);	Sleep(30);
			gotoxy(x,y);	printf("      ");
		}
		num++;
		for(;i-num>0;num++)
		{
			x=(i-num+6)*6;	y=21;
			for(;x<72;x++)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(30);
				gotoxy(x,y);	printf("      ");
			}
			for(;y<28;y++)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(50);
				gotoxy(x,y);	printf("      ");
			}
			for(;x>(num-1+6)*6;x--)
			{
				gotoxy(x,y);	printf("%s",car);	Sleep(30);
				gotoxy(x,y);	printf("      ");
			}
			gotoxy(x,y);	printf("%s",car);
		}
		if(a>0)
		{
			x=66;
			y=25;
			gotoxy(x,y);	printf("      ");
			gotoxy(x,y-2);  printf("%s",car);	Sleep(100);
			if(12>a)
			{
				gotoxy((12-a)*6,y);
				printf("      ");
			}
			if(a>1)
			{
			    gotoxy(x,y);	printf("%s",car);
			}
			printstop(0,i-1,x,y-2);
		}
	}
}

void main(void)
{
	int i,a;
	char c;
	SqStackCar s1,s2;                            //ͣ��ջ���ݴ�ջ
	LinkQueueCar p;                              //����
	InitSeqStack(&s1);
	InitSeqStack(&s2);
	InitLinkQueue(&p);
	printf("                                 ͣ��������ϵͳ\n\n");
	printf("*************************         ��ӭ����        ***************************\n");
	printf("      �շѱ�׼��������0.5Ԫ��ÿ������ȡ0.05Ԫ���շѾ�ȷ��0.1Ԫ\n");
	printf("      PS:���ƺ��ɰ������������");
	panitPL();
	printcar();		gotoxy(0,-3);
	c=0;               //���ܰ���
	while(1)          //��ESC�˳�ϵͳ
	{
		for(i=2;i>-1 ;i--)                           //��ʼ���Ի���
			qingping(i);
		printf("��ESC�˳�ϵͳ,��������ʼ�Ի�");
		c=getch();
		if(c==Esc)
		{
			qingping(0);
			break;
		}

		while(1)
		{
			qingping(2);
			gotoxy(28,8);	printf("��ӭ����ͣ���������ǹ���ԱС�š�");
			gotoxy(28,9);	printf("����������ѡ����Ҫ�ķ���        ");
			gotoxy(28,11);	printf("   1.��Ҫͣ��");
			gotoxy(28,12);	printf("   2.��Ҫȡ��");
			gotoxy(28,13);	printf("   3.�����Ի�");                       //��ӡ�Ի������
			a=getkey();
			if(a==Exit)
			{
				printf("��������");
				break;
			}
			switch(a)
			{
			case Stop:                                  //ͣ��
				Arrive(&s1,&p,getcarInfo() );
				break;
			case Drive:									//ȡ��
				Leave(&s1,&s2,&p,getcarInfo() );
				break;
			}
		}


	}
}
