/*����ͷ�ļ�*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#define QUEUE_MAXSIZE 50
#define MaxSize 50
/*���ĺ����ֵ�������*/
typedef int DataType;
typedef struct ChainTree
{
    struct ChainTree *lchild,*rchild;
    DataType data;
}ChainBinTree,BitNode,*BiTree;

void oper(ChainBinTree *p) //�����������������
{
     printf("%c ",p->data); //�������
     return;
}

void BinTree_Level(ChainBinTree *bt,void (*oper)(ChainBinTree *p)) //�������
{
     ChainBinTree *p;
     ChainBinTree *q[QUEUE_MAXSIZE]; //����һ��˳��ջ
     int head=0,tail=0;//���ס���β���
     if(bt)//������ָ�벻Ϊ��
     {
         tail=(tail+1)%QUEUE_MAXSIZE;//����ѭ�����ж�β���
         q[tail] = bt;//����������ָ�����
     }
     while(head!=tail) //���в�Ϊ�գ�����ѭ��
     {
         head=(head+1)%QUEUE_MAXSIZE; //����ѭ�����еĶ������
         p=q[head]; //��ȡ����Ԫ��
         oper(p);//�������Ԫ��
         if(p->lchild!=NULL) //������������������������ָ�����
         {
             tail=(tail+1)%QUEUE_MAXSIZE;//����ѭ�����еĶ�β���
             q[tail]=p->lchild;//��������ָ�����
         }

         if(p->rchild!=NULL)//���������Һ��ӣ����Һ��ӽ��ָ�����
         {
             tail=(tail+1)%QUEUE_MAXSIZE;//����ѭ�����еĶ�β���
             q[tail]=p->rchild;//��������ָ�����
         }
     }
     return;
}

void BinTree_DLR(ChainBinTree *bt,void (*oper)(ChainBinTree *p))  //�������
{
     if(bt)//����Ϊ�գ���ִ�����²���
     {
         oper(bt); //�����������
         BinTree_DLR(bt->lchild,oper);
         BinTree_DLR(bt->rchild,oper);
     }
     return;
}
void BinTree_LDR(ChainBinTree *bt,void(*oper)(ChainBinTree *p))  //�������
{
     if(bt)//����Ϊ�գ���ִ�����²���
     {
         BinTree_LDR(bt->lchild,oper); //�������������
         oper(bt);//����������
         BinTree_LDR(bt->rchild,oper); //�������������/
     }
     return;
}
void BinTree_LRD(ChainBinTree *bt,void (*oper)(ChainBinTree *p)) //�������
{
     if(bt)
     {
         BinTree_LRD(bt->lchild,oper); //�������������
         BinTree_LRD(bt->rchild,oper); //�������������/
         oper(bt); //����������
     }
     return;
}
void PreOrderTraverse2(BiTree T)
/*��������������ķǵݹ�ʵ��*/
{
    BiTree stack[MaxSize];              /*����һ��ջ�����ڴ�Ž���ָ��*/
    int top;                            /*����ջ��ָ��*/
    BitNode *p;                         /*����һ������ָ��*/
    top=0;                          /*��ʼ��ջ*/
    p=T;
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                  /*���p���գ����ʸ���㣬����������*/
        {
            printf("%2c",p->data);          /*���ʸ����*/
            stack[top++]=p;                 /*��p��ջ*/
            p=p->lchild;                /*����������*/
        }
        if(top>0)                       /*���ջ����*/
        {
            p=stack[--top];                 /*ջ��Ԫ�س�ջ*/
            p=p->rchild;                    /*����������*/
        }
    }
}
void InOrderTraverse2(BiTree T)
/*��������������ķǵݹ�ʵ��*/
{
    BiTree stack[MaxSize];              /*����һ��ջ�����ڴ�Ž���ָ��*/
    int top;                            /*����ջ��ָ��*/
    BitNode *p;                         /*����һ������ָ��*/
    top=0;                          /*��ʼ��ջ*/
    p=T;
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                  /*���p���գ����ʸ���㣬����������*/
        {
            stack[top++]=p;                 /*��p��ջ*/
            p=p->lchild;                /*����������*/
        }
        if(top>0)                       /*���ջ����*/
        {
            p=stack[--top];                 /*ջ��Ԫ�س�ջ*/
            printf("%2c",p->data);          /*���ʸ����*/
            p=p->rchild;                    /*����������*/
        }
    }
}
void PostOrderTraverse2(BiTree T)
/*��������������ķǵݹ�ʵ��*/
{
    BiTree stack[MaxSize];              /*����һ��ջ�����ڴ�Ž���ָ��*/
    int top;                            /*����ջ��ָ��*/
    BitNode *p,*q;                      /*�������ָ��*/
    top=0;                              /*��ʼ��ջ*/
    p=T,q=NULL;                         /*��ʼ������ָ��*/
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                      /*���p���գ����ʸ���㣬����������*/
        {
            stack[top++]=p;                 /*��p��ջ*/
            p=p->lchild;                    /*����������*/
        }
        if(top>0)                           /*���ջ����*/
        {
            p=stack[top-1];                     /*ȡջ��Ԫ��*/
            if(p->rchild==NULL||p->rchild==q)   /*���pû���Һ��ӽ�㣬���Һ��ӽ���Ѿ����ʹ�*/
            {
                printf("%2c",p->data);          /*���ʸ����*/
                q=p;
                p=NULL;
                top--;
            }
            else
                p=p->rchild;
        }
    }
}

void InitBinTree(BiTree *T)
/*���ĳ�ʼ��*/
{
    *T=0;
}
void DestroyBinTree(BiTree *T)
/*�������ٲ���*/
{
    BiTree p=*T;
    if(p)
    {
        DestroyBinTree(&(p->lchild));/*���ٵ�һ�����ӽ��*/
        DestroyBinTree(&(p->rchild));/*�����ֵܽ��*/
        free(p);
        *T = 0;
    }
}
void CreateBinTree(BiTree *T,DataType *e,int *index)
/*����������*/
{
    if(e[*index]==0)
    {
        *T=0;
        (*index)++;
    }
	else
	{
        *T=(BiTree)malloc(sizeof(BitNode));	/*���ɽ��*/
        (*T)->data=e[*index];
        (*index)++;
        CreateBinTree(&((*T)->lchild),e,index);/*������һ�����ӽ��*/
        CreateBinTree(&((*T)->rchild),e,index);/*�����ֵܽ��*/
        return;
    }
}

void DisplayBinTree(DataType *e)
/*������Ľ��*/
{
    printf("%2c",*e);
}

int DepBinTree(BiTree T)
/*���������*/
{
	BitNode *p;
	int k,d=0;
	if(T==NULL)				/*����ǿ���������0*/
		return 0;
	p=T->lchild;		/*pָ�����ĵ�һ���ӽ��*/
	while(p!=NULL)
	{
		k=DepBinTree(p);		/*����p�������*/
		if(d<k)
			d=k;			/*d��������������*/
		p=p->rchild;	/*����p����һ�����*/
	}
	return d+1;

}


void main()
{
    int test[] = {'A','B','E',0,'F','H',0,'I',0,'J',0,0,0,'C',0,'D','G',0,0,0,0};
    int h=0;
    BiTree T;
    InitBinTree(&T);
    CreateBinTree(&T,test,&h);
    printf("���������:%2d",DepBinTree(T));
    printf("\n");
    printf("���İ�����������:\n");
    BinTree_Level(T,oper);
    printf("\n");
	printf("���ĵݹ��ȸ����������:\n");
	BinTree_DLR(T,oper);
    printf("\n");
    printf("���ķǵݹ��ȸ����������:\n");
    PreOrderTraverse2(T);
    printf("\n");
    printf("���ĵݹ��и����������:\n");
    BinTree_LDR(T,oper);
    printf("\n");
    printf("���ķǵݹ��и����������:\n");
    InOrderTraverse2(T);
    printf("\n");
	printf("���ĺ�����������:\n");
    BinTree_LRD(T,oper);
    printf("\n");
    printf("���ķǺ�����������:\n");
    PostOrderTraverse2(T);
    printf("\n");
	DestroyBinTree(&T);
}
