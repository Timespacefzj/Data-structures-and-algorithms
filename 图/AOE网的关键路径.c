#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define StackSize 100
#define MaxSize 50              /*最大顶点个数*/
typedef int DataType;           /*栈元素类型定义*/
typedef struct
{
    DataType stack[StackSize];
    int top;
}SeqStack;

/*图的邻接表类型定义*/
typedef char VertexType[4];
typedef int InfoPtr;            /*定义为整型，为了存放权值*/
typedef int VRType;
typedef enum{DG,DN,UG,UN}GraphKind;     /*图的类型：有向图、有向网、无向图和无向网*/
typedef struct ArcNode          /*边结点的类型定义*/
{
    int adjvex;                 /*弧指向的顶点的位置*/
    InfoPtr *info;              /*弧的权值*/
    struct ArcNode *nextarc;    /*指示下一个与该顶点相邻接的顶点*/
}ArcNode;
typedef struct VNode            /*头结点的类型定义*/
{
    VertexType data;            /*用于存储顶点*/
    ArcNode *firstarc;          /*指示第一个与该顶点邻接的顶点*/
}VNode,AdjList[MaxSize];
typedef struct                  /*图的类型定义*/
{
    AdjList vertex;
    int vexnum,arcnum;          /*图的顶点数目与弧的数目*/
    GraphKind kind;             /*图的类型*/
}AdjGraph;


void InitStack(SeqStack *S)
/*将栈初始化为空栈只需要把栈顶指针top置为0*/
{
S->top=0;   /*把栈顶指针置为0*/
}
int StackEmpty(SeqStack S)
/*判断栈是否为空，栈为空返回1，否则返回0*/
{
    if(S.top==0)            /*判断栈顶指针top是否为0*/
        return 1;           /*当栈为空时，返回1；否则返回0*/
    else
        return 0;
}
int GetTop(SeqStack S, DataType *e)
/*取栈顶元素。将栈顶元素值返回给e，并返回1表示成功；否则返回0表示失败。*/
{
   if(S.top<=0)     /*在取栈顶元素之前，判断栈是否为空*/
{
    printf("栈已经空!\n");
    return 0;
}
else
{
    *e=S.stack[S.top-1];    /*在取栈顶元素*/
    return 1;
}
}
int PushStack(SeqStack *S,DataType e)
/*将元素e进栈，元素进栈成功返回1，否则返回0.*/
{
if(S->top>=StackSize)               /*在元素进栈前，判断是否栈已经满*/
{
        printf("栈已满，不能进栈！\n");
        return 0;
}
else
{
        S->stack[S->top]=e;         /*元素e进栈*/
        S->top++;                   /*修改栈顶指针*/
        return 1;
}
}
int PopStack(SeqStack *S,DataType *e)
/*出栈操作。将栈顶元素出栈，并将其赋值给e。出栈成功返回1，否则返回0*/
{
    if(S->top<=0)       /*元素出栈之前，判断栈是否为空*/
    {
        printf("栈已经没有元素，不能出栈!\n");
        return 0;
    }
    else
{
    S->top--;           /*先修改栈顶指针，即出栈*/
        *e=S->stack[S->top];    /*将出栈元素赋值给e*/
        return 1;
    }
}
int StackLength(SeqStack S)
/*求栈的长度，即栈中元素个数，栈顶指针的值就等于栈中元素的个数*/
{
    return S.top;
}
void ClearStack(SeqStack *S)
/*将栈初始化为空栈只需要把栈顶指针top置为0*/
{
S->top=0;   /*把栈顶指针置为0*/
}



int ve[MaxSize];                /*ve存放事件最早发生时间*/
int TopologicalOrder(AdjGraph N,SeqStack *T)
/*采用邻接表存储结构的有向网N的拓扑排序，并求各顶点对应事件的最早发生时间ve*/
/*如果N无回路，则用用栈T返回N的一个拓扑序列,并返回1,否则为0*/
{
    int i,k,count=0;
    int indegree[MaxSize];      /*数组indegree存储各顶点的入度*/
    SeqStack S;
    ArcNode *p;
    /*将图中各顶点的入度保存在数组indegree中*/
    for(i=0;i<N.vexnum;i++)     /*将数组indegree赋初值*/
        indegree[i]=0;
    for(i=0;i<N.vexnum;i++)
    {
        p=N.vertex[i].firstarc;
        while(p!=NULL)
        {
            k=p->adjvex;
            indegree[k]++;
            p=p->nextarc;
        }
    }
    InitStack(&S);              /*初始化栈S*/
    printf("拓扑序列：");
    for(i=0;i<N.vexnum;i++)
        if(!indegree[i])        /*将入度为零的顶点入栈*/
            PushStack(&S,i);
        InitStack(T);           /*初始化拓扑序列顶点栈*/
        for(i=0;i<N.vexnum;i++) /*初始化ve*/
            ve[i]=0;
        while(!StackEmpty(S))   /*如果栈S不为空*/
        {
            PopStack(&S,&i);    /*从栈S将已拓扑排序的顶点j弹出*/
            printf("%s ",N.vertex[i].data);
            PushStack(T,i);     /*j号顶点入逆拓扑排序栈T*/
            count++;            /*对入栈T的顶点计数*/
            for(p=N.vertex[i].firstarc;p;p=p->nextarc)  /*处理编号为i的顶点的每个邻接点*/
            {
                k=p->adjvex;            /*顶点序号为k*/
                if(--indegree[k]==0)    /*如果k的入度减1后变为0，则将k入栈S*/
                    PushStack(&S,k);
                if(ve[i]+*(p->info)>ve[k]) /*计算顶点k对应的事件的最早发生时间*/
                    ve[k]=ve[i]+*(p->info);
            }
        }
        if(count<N.vexnum)
        {
            printf("该有向网有回路\n");
            return 0;
        }
        else
            return 1;
}

int CriticalPath(AdjGraph N)
/*输出N的关键路径*/
{
    int vl[MaxSize];                /*事件最晚发生时间*/
    SeqStack T;
    int i,j,k,e,l,dut,value,count,e1[MaxSize],e2[MaxSize];
    ArcNode *p;
    if(!TopologicalOrder(N,&T))     /*如果有环存在，则返回0*/
        return 0;
    value=ve[0];
    for(i=1;i<N.vexnum;i++)
        if(ve[i]>value)
            value=ve[i];            /*value为事件的最早发生时间的最大值*/
        for(i=0;i<N.vexnum;i++)     /*将顶点事件的最晚发生时间初始化*/
            vl[i]=value;
        while(!StackEmpty(T))       /*按逆拓扑排序求各顶点的vl值*/
            for(PopStack(&T,&j),p=N.vertex[j].firstarc;p;p=p->nextarc)
            /*弹出栈T的元素,赋给j,p指向j的后继事件k*/
            {
                k=p->adjvex;
                dut=*(p->info);     /*dut为弧<j,k>的权值*/
                if(vl[k]-dut<vl[j]) /*计算事件j的最迟发生时间*/
                    vl[j]=vl[k]-dut;
            }
        printf("\n事件的最早发生时间和最晚发生时间\ni ve[i] vl[i]\n");
        for(i=0;i<N.vexnum;i++)     /*输出顶点对应的事件的最早发生时间最晚发生时间*/
            printf("%d   %d     %d\n",i,ve[i],vl[i]);
        printf("关键路径为：(");
        for(i=0;i<N.vexnum;i++)     /*输出关键路径经过的顶点*/
            if(ve[i]==vl[i])
                printf("%s ",N.vertex[i].data);
        printf(")\n");
        count=0;
        printf("活动最早开始时间和最晚开始时间\n   弧    e   l   l-e\n");
        for(j=0;j<N.vexnum;j++)     /*求活动的最早开始时间e和最晚开始时间l*/
            for(p=N.vertex[j].firstarc;p;p=p->nextarc)
            {
                k=p->adjvex;
                dut=*(p->info);     /*dut为弧<j,k>的权值*/
                e=ve[j];            /*e就是活动<j,k>的最早开始时间*/
                l=vl[k]-dut;        /*l就是活动<j,k>的最晚开始时间*/
                printf("%s→%s %3d %3d %3d\n",N.vertex[j].data,N.vertex[k].data,e,l,l-e);
                if(e==l)            /*将关键活动保存在数组中*/
                {
                    e1[count]=j;
                    e2[count]=k;
                    count++;
                }
            }
        printf("关键活动为：");
        for(k=0;k<count;k++)        /*输出关键路径*/
        {
            i=e1[k];
            j=e2[k];
            printf("(%s→%s) ",N.vertex[i].data,N.vertex[j].data);
        }
        printf("\n");
    return 1;
}

int LocateVertex(AdjGraph G,VertexType v)
/*返回图中顶点对应的位置*/
{
    int i;
    for(i=0;i<G.vexnum;i++)
        if(strcmp(G.vertex[i].data,v)==0)
            return i;
        return -1;
}
void CreateGraph(AdjGraph *N)
/*采用邻接表存储结构，创建有向网N*/
{
    int i,j,k,w;
    VertexType v1,v2;                   /*定义两个弧v1和v2*/
    ArcNode *p;
    printf("请输入图的顶点数,边数(以逗号分隔): ");
    scanf("%d,%d",&(*N).vexnum,&(*N).arcnum);
    printf("请输入%d个顶点的值:",N->vexnum);
    for(i=0;i<N->vexnum;i++)            /*将顶点存储在头结点中*/
    {
        scanf("%s",N->vertex[i].data);
        N->vertex[i].firstarc=NULL;     /*将相关联的顶点置为空*/
    }
    printf("请输入弧尾、弧头和权值(以空格作为分隔):\n");
    for(k=0;k<N->arcnum;k++)            /*建立边链表*/
    {
        scanf("%s%s%*c%d",v1,v2,&w);
        i=LocateVertex(*N,v1);
        j=LocateVertex(*N,v2);
        /*j为弧头i为弧尾创建邻接表*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
        *(p->info)=w;
        /*将p指向的结点插入到边表中*/
        p->nextarc=N->vertex[i].firstarc;
        N->vertex[i].firstarc=p;
    }
    (*N).kind=DN;
}

void DisplayGraph(AdjGraph N)
/*网的邻接矩阵N的输出*/
{
    int i;
    ArcNode *p;
    printf("该网中有%d个顶点：",N.vexnum);
    for(i=0;i<N.vexnum;i++)
        printf("%s ",N.vertex[i].data);
    printf("\n网中共有%d条弧:\n",N.arcnum);
    for(i=0;i<N.vexnum;i++)
    {
        p=N.vertex[i].firstarc;
        while(p)
        {
            printf("<%s,%s,%d> ",N.vertex[i].data,N.vertex[p->adjvex].data,*(p->info));
            p=p->nextarc;
        }
        printf("\n");
    }
}

void DestroyGraph(AdjGraph *N)
/*销毁无向图G*/
{
    int i;
    ArcNode *p,*q;
    for(i=0;i<N->vexnum;++i)        /*释放网中的边表结点*/
    {
        p=N->vertex[i].firstarc;    /*p指向边表的第一个结点*/
        if(p!=NULL)                 /*如果边表不为空，则释放边表的结点*/
        {
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    (*N).vexnum=0;                  /*将顶点数置为0*/
    (*N).arcnum=0;                  /*将边的数目置为0*/
}

void main()
{
    AdjGraph N;
    CreateGraph(&N);        /*采用邻接表存储结构创建有向网N*/
    DisplayGraph(N);        /*输出有向网N*/
    CriticalPath(N);        /*求网N的关键路径*/
    DestroyGraph(&N);       /*销毁网N*/
}
