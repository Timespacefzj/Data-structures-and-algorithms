/*包含头文件*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#define QUEUE_MAXSIZE 50
#define MaxSize 50
/*树的孩子兄弟链表定义*/
typedef int DataType;
typedef struct ChainTree
{
    struct ChainTree *lchild,*rchild;
    DataType data;
}ChainBinTree,BitNode,*BiTree;

void oper(ChainBinTree *p) //操作二叉树结点数据
{
     printf("%c ",p->data); //输出数据
     return;
}

void BinTree_Level(ChainBinTree *bt,void (*oper)(ChainBinTree *p)) //按层遍历
{
     ChainBinTree *p;
     ChainBinTree *q[QUEUE_MAXSIZE]; //定义一个顺序栈
     int head=0,tail=0;//队首、队尾序号
     if(bt)//若队首指针不为空
     {
         tail=(tail+1)%QUEUE_MAXSIZE;//计算循环队列队尾序号
         q[tail] = bt;//将二叉树根指针进队
     }
     while(head!=tail) //队列不为空，进行循环
     {
         head=(head+1)%QUEUE_MAXSIZE; //计算循环队列的队首序号
         p=q[head]; //获取队首元素
         oper(p);//处理队首元素
         if(p->lchild!=NULL) //若结点存在左子树，则左子树指针进队
         {
             tail=(tail+1)%QUEUE_MAXSIZE;//计算循环队列的队尾序号
             q[tail]=p->lchild;//将左子树指针进队
         }

         if(p->rchild!=NULL)//若结点存在右孩子，则右孩子结点指针进队
         {
             tail=(tail+1)%QUEUE_MAXSIZE;//计算循环队列的队尾序号
             q[tail]=p->rchild;//将右子树指针进队
         }
     }
     return;
}

void BinTree_DLR(ChainBinTree *bt,void (*oper)(ChainBinTree *p))  //先序遍历
{
     if(bt)//树不为空，则执行如下操作
     {
         oper(bt); //处理结点的数据
         BinTree_DLR(bt->lchild,oper);
         BinTree_DLR(bt->rchild,oper);
     }
     return;
}
void BinTree_LDR(ChainBinTree *bt,void(*oper)(ChainBinTree *p))  //中序遍历
{
     if(bt)//树不为空，则执行如下操作
     {
         BinTree_LDR(bt->lchild,oper); //中序遍历左子树
         oper(bt);//处理结点数据
         BinTree_LDR(bt->rchild,oper); //中序遍历右子树/
     }
     return;
}
void BinTree_LRD(ChainBinTree *bt,void (*oper)(ChainBinTree *p)) //后序遍历
{
     if(bt)
     {
         BinTree_LRD(bt->lchild,oper); //后序遍历左子树
         BinTree_LRD(bt->rchild,oper); //后序遍历右子树/
         oper(bt); //处理结点数据
     }
     return;
}
void PreOrderTraverse2(BiTree T)
/*先序遍历二叉树的非递归实现*/
{
    BiTree stack[MaxSize];              /*定义一个栈，用于存放结点的指针*/
    int top;                            /*定义栈顶指针*/
    BitNode *p;                         /*定义一个结点的指针*/
    top=0;                          /*初始化栈*/
    p=T;
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                  /*如果p不空，访问根结点，遍历左子树*/
        {
            printf("%2c",p->data);          /*访问根结点*/
            stack[top++]=p;                 /*将p入栈*/
            p=p->lchild;                /*遍历左子树*/
        }
        if(top>0)                       /*如果栈不空*/
        {
            p=stack[--top];                 /*栈顶元素出栈*/
            p=p->rchild;                    /*遍历右子树*/
        }
    }
}
void InOrderTraverse2(BiTree T)
/*中序遍历二叉树的非递归实现*/
{
    BiTree stack[MaxSize];              /*定义一个栈，用于存放结点的指针*/
    int top;                            /*定义栈顶指针*/
    BitNode *p;                         /*定义一个结点的指针*/
    top=0;                          /*初始化栈*/
    p=T;
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                  /*如果p不空，访问根结点，遍历左子树*/
        {
            stack[top++]=p;                 /*将p入栈*/
            p=p->lchild;                /*遍历左子树*/
        }
        if(top>0)                       /*如果栈不空*/
        {
            p=stack[--top];                 /*栈顶元素出栈*/
            printf("%2c",p->data);          /*访问根结点*/
            p=p->rchild;                    /*遍历右子树*/
        }
    }
}
void PostOrderTraverse2(BiTree T)
/*后序遍历二叉树的非递归实现*/
{
    BiTree stack[MaxSize];              /*定义一个栈，用于存放结点的指针*/
    int top;                            /*定义栈顶指针*/
    BitNode *p,*q;                      /*定义结点的指针*/
    top=0;                              /*初始化栈*/
    p=T,q=NULL;                         /*初始化结点的指针*/
    while(p!=NULL||top>0)
    {
        while(p!=NULL)                      /*如果p不空，访问根结点，遍历左子树*/
        {
            stack[top++]=p;                 /*将p入栈*/
            p=p->lchild;                    /*遍历左子树*/
        }
        if(top>0)                           /*如果栈不空*/
        {
            p=stack[top-1];                     /*取栈顶元素*/
            if(p->rchild==NULL||p->rchild==q)   /*如果p没有右孩子结点，或右孩子结点已经访问过*/
            {
                printf("%2c",p->data);          /*访问根结点*/
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
/*树的初始化*/
{
    *T=0;
}
void DestroyBinTree(BiTree *T)
/*树的销毁操作*/
{
    BiTree p=*T;
    if(p)
    {
        DestroyBinTree(&(p->lchild));/*销毁第一个孩子结点*/
        DestroyBinTree(&(p->rchild));/*销毁兄弟结点*/
        free(p);
        *T = 0;
    }
}
void CreateBinTree(BiTree *T,DataType *e,int *index)
/*创建树操作*/
{
    if(e[*index]==0)
    {
        *T=0;
        (*index)++;
    }
	else
	{
        *T=(BiTree)malloc(sizeof(BitNode));	/*生成结点*/
        (*T)->data=e[*index];
        (*index)++;
        CreateBinTree(&((*T)->lchild),e,index);/*创建第一个孩子结点*/
        CreateBinTree(&((*T)->rchild),e,index);/*创建兄弟结点*/
        return;
    }
}

void DisplayBinTree(DataType *e)
/*输出树的结点*/
{
    printf("%2c",*e);
}

int DepBinTree(BiTree T)
/*求树的深度*/
{
	BitNode *p;
	int k,d=0;
	if(T==NULL)				/*如果是空树，返回0*/
		return 0;
	p=T->lchild;		/*p指向树的第一孩子结点*/
	while(p!=NULL)
	{
		k=DepBinTree(p);		/*求子p树的深度*/
		if(d<k)
			d=k;			/*d保存树的最大深度*/
		p=p->rchild;	/*进入p的下一个结点*/
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
    printf("树的深度是:%2d",DepBinTree(T));
    printf("\n");
    printf("树的按层遍历结果是:\n");
    BinTree_Level(T,oper);
    printf("\n");
	printf("树的递归先根遍历结果是:\n");
	BinTree_DLR(T,oper);
    printf("\n");
    printf("树的非递归先根遍历结果是:\n");
    PreOrderTraverse2(T);
    printf("\n");
    printf("树的递归中根遍历结果是:\n");
    BinTree_LDR(T,oper);
    printf("\n");
    printf("树的非递归中根遍历结果是:\n");
    InOrderTraverse2(T);
    printf("\n");
	printf("树的后根遍历结果是:\n");
    BinTree_LRD(T,oper);
    printf("\n");
    printf("树的非后根遍历结果是:\n");
    PostOrderTraverse2(T);
    printf("\n");
	DestroyBinTree(&T);
}
