#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#define MaxSize 100
/*�������������Ͷ���*/
typedef char DataType;
typedef enum {Link,Thread}PointerTag;
typedef struct Node/*�������*/
{
    DataType data;
    struct Node *lchild, *rchild;                   /*���Һ�������*/
    PointerTag ltag,rtag;                           /*������־��*/
}BiThrNode;
typedef BiThrNode *BiThrTree;                       /*����������*/
/*��������*/
void CreateBitTree2(BiThrTree *T,char str[]);           /*��������������*/
void InThreading(BiThrTree p);                      /*����������������*/
int InOrderThreading(BiThrTree *Thrt,BiThrTree T);      /*ͨ���������������T��ʹT������������Thrt��ָ��ͷ����ָ��*/
int InOrderTraverse(BiThrTree T,int (* visit)(BiThrTree e));        /*�����������������*/
int Print(BiThrTree T);                             /*��ӡ�������еĽ�㼰������־*/
BiThrNode *FindPoint(BiThrTree T,DataType e);       /*�������������в��ҽ��Ϊe��ָ��*/
BiThrNode *InOrderPre(BiThrNode *p);                /*������������������������ǰ��*/
BiThrNode *InOrderPost(BiThrNode *p);               /*��������������������������*/
BiThrTree pre;                                      /*preʼ��ָ���Ѿ��������Ľ��*/
void DestroyBitTree(BiThrTree *T);/*��������������*/
void main()
/*���Գ���*/
{
    DataType ch;
    BiThrTree T,Thrt;
    BiThrNode *p,*pre,*post;
    CreateBitTree2(&T,"(A(B(D,E(H)),C(F(,I),G)))");
    printf("��������������Ľ�㡢ǰ���������Ϣ��\n");
    InOrderThreading(&Thrt,T);
    printf("����   ǰ����־   ���  ��̱�־\n");
    InOrderTraverse(Thrt,Print);
    printf("������Ҫ�����ĸ�����ǰ���ͺ��:");
    ch=getchar();
    p=FindPoint(Thrt,ch);
    pre=InOrderPre(p);
    printf("Ԫ��%c������ֱ��ǰ��Ԫ����:%c\n",ch,pre->data);
    post=InOrderPost(p);
    printf("Ԫ��%c������ֱ�Ӻ��Ԫ����:%c\n",ch,post->data);
    DestroyBitTree(&Thrt);
}
int Print(BiThrTree T)
/*��ӡ�����������еĽ�㼰����*/
{
    static int k=1;
    printf("%2d\t%s\t  %2c\t  %s\t\n",k++,T->ltag==0?"Link":"Thread",
                          T->data,
                          T->rtag==1?"Thread":"Link");
    return 1;
}
void DestroyBitTree(BiThrTree *T)
/*���ٶ�����*/
{
    if(*T)                          /*����Ƿǿն�����*/
    {
        if((*T)->lchild)
            DestroyBitTree(&((*T)->lchild));
        if((*T)->rchild)
            DestroyBitTree(&((*T)->rchild));
        free(*T);
        *T=NULL;
    }
}
void CreateBitTree2(BiThrTree *T,char str[])
/*��������Ƕ�׵��ַ���������������*/
{
    char ch;
    BiThrTree stack[MaxSize];           /*����ջ�����ڴ��ָ��������н���ָ��*/
    int top=-1;                         /*��ʼ��ջ��ָ��*/
    int flag,k;
    BiThrNode *p;
    *T=NULL,k=0;
    ch=str[k];
    while(ch!='\0')                     /*����ַ���û�н���*/
    {
        switch(ch)
        {
        case '(':
            stack[++top]=p;
            flag=1;
            break;
        case ')':
            top--;
            break;
        case ',':
            flag=2;
            break;
        default:
            p=(BiThrTree)malloc(sizeof(BiThrNode));
            p->data=ch;
            p->lchild=NULL;
            p->rchild=NULL;

            if(*T==NULL)                    /*����ǵ�һ����㣬��ʾ�Ǹ����*/
                *T=p;
            else
            {
                switch(flag)
                {
                case 1:
                    stack[top]->lchild=p;
                    break;
                case 2:
                    stack[top]->rchild=p;
                    break;
                }
                if(stack[top]->lchild)
                    stack[top]->ltag=Link;
                if(stack[top]->rchild)
                    stack[top]->rtag=Link;
            }

        }
        ch=str[++k];
    }
}
BiThrNode *FindPoint(BiThrTree T,DataType e)
/*�����������������������Ԫ��ֵΪe�Ľ���ָ�롣*/
{
    BiThrTree p;
    p=T->lchild;                            /*pָ������*/
    while(p!=T)                         /*������ǿն�����*/
    {
        while(p->ltag==Link)
            p=p->lchild;
        if(p->data==e)                      /*�ҵ���㣬����ָ��*/
            return p;
        while(p->rtag==Thread&&p->rchild!=T)    /*���ʺ�̽��*/
        {
            p=p->rchild;
            if(p->data==e)                  /*�ҵ���㣬����ָ��*/
                return p;
        }
        p=p->rchild;
    }
    return NULL;
}
BiThrNode *InOrderPre(BiThrNode *p)
/*���������������ҽ��*p��ֱ��ǰ��*/
{
    BiThrNode *pre;
    if (p->ltag==Thread)        /*���p�ı�־��ltagΪ��������p����������㼴Ϊǰ��*/
        return p->lchild;
    else
{
        pre=p->lchild;          /*����p�����ӵ������¶˽��*/
        while (pre->rtag==Link) /*�������ǿ�ʱ�����������²���*/
            pre=pre->rchild;
         return pre;                /*pre���������¶˽��*/
    }
}
BiThrNode *InOrderPost(BiThrNode *p)
/*�������������в��ҽ��*p��ֱ�Ӻ��*/
{
    BiThrNode *pre;
    if (p->rtag==Thread)        /*���p�ı�־��ltagΪ��������p����������㼴Ϊ���*/
        return p->rchild;
    else
    {
        pre=p->rchild;          /*����p���Һ��ӵ������¶˽��*/
        while (pre->ltag==Link) /*�������ǿ�ʱ�����������²���*/
            pre=pre->lchild;
        return pre;             /*pre���������¶˽��*/
    }
}
int InOrderTraverse(BiThrTree T,int (* visit)(BiThrTree e))
/*�����������������������visit�Ǻ���ָ�룬ָ����ʽ��ĺ���ʵ��*/
{
    BiThrTree p;
    p=T->lchild;                            /*pָ������*/
    while(p!=T)                         /*�������������ʱ��p==T*/
    {
        while(p->ltag==Link)
            p=p->lchild;
        if(!visit(p))                           /*��ӡ*/
            return 0;
        while(p->rtag==Thread&&p->rchild!=T)    /*���ʺ�̽��*/
        {
            p=p->rchild;
            visit(p);
        }
        p=p->rchild;
    }
    return 1;
}
BiThrTree pre;                      /*preʼ��ָ���Ѿ��������Ľ��*/
int InOrderThreading(BiThrTree *Thrt,BiThrTree T)
/*ͨ���������������T��ʹT������������Thrt��ָ��ͷ����ָ��*/
{

    if(!(*Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) /*Ϊͷ�������ڴ浥Ԫ*/
        exit(-1);
    /*��ͷ���������*/
    (*Thrt)->ltag=Link;             /*�޸�ǰ��������־*/
    (*Thrt)->rtag=Thread;           /*�޸ĺ��������־*/
    (*Thrt)->rchild=*Thrt;              /*��ͷ����rchildָ��ָ���Լ�*/
    if(!T)                          /*���������Ϊ�գ���lchildָ��ָ���Լ�*/
        (*Thrt)->lchild=*Thrt;
    else
    {
        (*Thrt)->lchild=T;          /*��ͷ������ָ��ָ������*/
        pre=*Thrt;                  /*��preָ���Ѿ��������Ľ��*/
        InThreading(T);             /*���������������������*/
        /*�����һ�����������*/
        pre->rchild=*Thrt;          /*�����һ��������ָ��ָ��ͷ���*/
        pre->rtag=Thread;           /*�޸����һ������rtag��־��*/
        (*Thrt)->rchild=pre;            /*��ͷ����rchildָ��ָ�����һ�����*/
    }
    return 1;
}
void InThreading(BiThrTree p)
/*������������������*/
{
    if(p)
    {
        InThreading(p->lchild);     /*������������*/
        if(!p->lchild)              /*ǰ��������*/
        {
            p->ltag=Thread;
            p->lchild=pre;
        }
        if(!pre->rchild)                /*���������*/
        {
            pre->rtag=Thread;
            pre->rchild=p;
        }
        pre=p;                      /*preָ��Ľ����������ϣ�ʹpָ��Ľ���Ϊǰ��*/
        InThreading(p->rchild);         /*������������*/
    }
}
