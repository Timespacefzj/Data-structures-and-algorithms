#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define StackSize 100
#define MaxSize 50              /*��󶥵����*/
typedef int DataType;           /*ջԪ�����Ͷ���*/
typedef struct
{
    DataType stack[StackSize];
    int top;
}SeqStack;

/*ͼ���ڽӱ����Ͷ���*/
typedef char VertexType[4];
typedef int InfoPtr;            /*����Ϊ���ͣ�Ϊ�˴��Ȩֵ*/
typedef int VRType;
typedef enum{DG,DN,UG,UN}GraphKind;     /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct ArcNode          /*�߽������Ͷ���*/
{
    int adjvex;                 /*��ָ��Ķ����λ��*/
    InfoPtr *info;              /*����Ȩֵ*/
    struct ArcNode *nextarc;    /*ָʾ��һ����ö������ڽӵĶ���*/
}ArcNode;
typedef struct VNode            /*ͷ�������Ͷ���*/
{
    VertexType data;            /*���ڴ洢����*/
    ArcNode *firstarc;          /*ָʾ��һ����ö����ڽӵĶ���*/
}VNode,AdjList[MaxSize];
typedef struct                  /*ͼ�����Ͷ���*/
{
    AdjList vertex;
    int vexnum,arcnum;          /*ͼ�Ķ�����Ŀ�뻡����Ŀ*/
    GraphKind kind;             /*ͼ������*/
}AdjGraph;


void InitStack(SeqStack *S)
/*��ջ��ʼ��Ϊ��ջֻ��Ҫ��ջ��ָ��top��Ϊ0*/
{
S->top=0;   /*��ջ��ָ����Ϊ0*/
}
int StackEmpty(SeqStack S)
/*�ж�ջ�Ƿ�Ϊ�գ�ջΪ�շ���1�����򷵻�0*/
{
    if(S.top==0)            /*�ж�ջ��ָ��top�Ƿ�Ϊ0*/
        return 1;           /*��ջΪ��ʱ������1�����򷵻�0*/
    else
        return 0;
}
int GetTop(SeqStack S, DataType *e)
/*ȡջ��Ԫ�ء���ջ��Ԫ��ֵ���ظ�e��������1��ʾ�ɹ������򷵻�0��ʾʧ�ܡ�*/
{
   if(S.top<=0)     /*��ȡջ��Ԫ��֮ǰ���ж�ջ�Ƿ�Ϊ��*/
{
    printf("ջ�Ѿ���!\n");
    return 0;
}
else
{
    *e=S.stack[S.top-1];    /*��ȡջ��Ԫ��*/
    return 1;
}
}
int PushStack(SeqStack *S,DataType e)
/*��Ԫ��e��ջ��Ԫ�ؽ�ջ�ɹ�����1�����򷵻�0.*/
{
if(S->top>=StackSize)               /*��Ԫ�ؽ�ջǰ���ж��Ƿ�ջ�Ѿ���*/
{
        printf("ջ���������ܽ�ջ��\n");
        return 0;
}
else
{
        S->stack[S->top]=e;         /*Ԫ��e��ջ*/
        S->top++;                   /*�޸�ջ��ָ��*/
        return 1;
}
}
int PopStack(SeqStack *S,DataType *e)
/*��ջ��������ջ��Ԫ�س�ջ�������丳ֵ��e����ջ�ɹ�����1�����򷵻�0*/
{
    if(S->top<=0)       /*Ԫ�س�ջ֮ǰ���ж�ջ�Ƿ�Ϊ��*/
    {
        printf("ջ�Ѿ�û��Ԫ�أ����ܳ�ջ!\n");
        return 0;
    }
    else
{
    S->top--;           /*���޸�ջ��ָ�룬����ջ*/
        *e=S->stack[S->top];    /*����ջԪ�ظ�ֵ��e*/
        return 1;
    }
}
int StackLength(SeqStack S)
/*��ջ�ĳ��ȣ���ջ��Ԫ�ظ�����ջ��ָ���ֵ�͵���ջ��Ԫ�صĸ���*/
{
    return S.top;
}
void ClearStack(SeqStack *S)
/*��ջ��ʼ��Ϊ��ջֻ��Ҫ��ջ��ָ��top��Ϊ0*/
{
S->top=0;   /*��ջ��ָ����Ϊ0*/
}



int ve[MaxSize];                /*ve����¼����緢��ʱ��*/
int TopologicalOrder(AdjGraph N,SeqStack *T)
/*�����ڽӱ�洢�ṹ��������N���������򣬲���������Ӧ�¼������緢��ʱ��ve*/
/*���N�޻�·��������ջT����N��һ����������,������1,����Ϊ0*/
{
    int i,k,count=0;
    int indegree[MaxSize];      /*����indegree�洢����������*/
    SeqStack S;
    ArcNode *p;
    /*��ͼ�и��������ȱ���������indegree��*/
    for(i=0;i<N.vexnum;i++)     /*������indegree����ֵ*/
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
    InitStack(&S);              /*��ʼ��ջS*/
    printf("�������У�");
    for(i=0;i<N.vexnum;i++)
        if(!indegree[i])        /*�����Ϊ��Ķ�����ջ*/
            PushStack(&S,i);
        InitStack(T);           /*��ʼ���������ж���ջ*/
        for(i=0;i<N.vexnum;i++) /*��ʼ��ve*/
            ve[i]=0;
        while(!StackEmpty(S))   /*���ջS��Ϊ��*/
        {
            PopStack(&S,&i);    /*��ջS������������Ķ���j����*/
            printf("%s ",N.vertex[i].data);
            PushStack(T,i);     /*j�Ŷ���������������ջT*/
            count++;            /*����ջT�Ķ������*/
            for(p=N.vertex[i].firstarc;p;p=p->nextarc)  /*������Ϊi�Ķ����ÿ���ڽӵ�*/
            {
                k=p->adjvex;            /*�������Ϊk*/
                if(--indegree[k]==0)    /*���k����ȼ�1���Ϊ0����k��ջS*/
                    PushStack(&S,k);
                if(ve[i]+*(p->info)>ve[k]) /*���㶥��k��Ӧ���¼������緢��ʱ��*/
                    ve[k]=ve[i]+*(p->info);
            }
        }
        if(count<N.vexnum)
        {
            printf("���������л�·\n");
            return 0;
        }
        else
            return 1;
}

int CriticalPath(AdjGraph N)
/*���N�Ĺؼ�·��*/
{
    int vl[MaxSize];                /*�¼�������ʱ��*/
    SeqStack T;
    int i,j,k,e,l,dut,value,count,e1[MaxSize],e2[MaxSize];
    ArcNode *p;
    if(!TopologicalOrder(N,&T))     /*����л����ڣ��򷵻�0*/
        return 0;
    value=ve[0];
    for(i=1;i<N.vexnum;i++)
        if(ve[i]>value)
            value=ve[i];            /*valueΪ�¼������緢��ʱ������ֵ*/
        for(i=0;i<N.vexnum;i++)     /*�������¼���������ʱ���ʼ��*/
            vl[i]=value;
        while(!StackEmpty(T))       /*��������������������vlֵ*/
            for(PopStack(&T,&j),p=N.vertex[j].firstarc;p;p=p->nextarc)
            /*����ջT��Ԫ��,����j,pָ��j�ĺ���¼�k*/
            {
                k=p->adjvex;
                dut=*(p->info);     /*dutΪ��<j,k>��Ȩֵ*/
                if(vl[k]-dut<vl[j]) /*�����¼�j����ٷ���ʱ��*/
                    vl[j]=vl[k]-dut;
            }
        printf("\n�¼������緢��ʱ���������ʱ��\ni ve[i] vl[i]\n");
        for(i=0;i<N.vexnum;i++)     /*��������Ӧ���¼������緢��ʱ��������ʱ��*/
            printf("%d   %d     %d\n",i,ve[i],vl[i]);
        printf("�ؼ�·��Ϊ��(");
        for(i=0;i<N.vexnum;i++)     /*����ؼ�·�������Ķ���*/
            if(ve[i]==vl[i])
                printf("%s ",N.vertex[i].data);
        printf(")\n");
        count=0;
        printf("����翪ʼʱ�������ʼʱ��\n   ��    e   l   l-e\n");
        for(j=0;j<N.vexnum;j++)     /*�������翪ʼʱ��e������ʼʱ��l*/
            for(p=N.vertex[j].firstarc;p;p=p->nextarc)
            {
                k=p->adjvex;
                dut=*(p->info);     /*dutΪ��<j,k>��Ȩֵ*/
                e=ve[j];            /*e���ǻ<j,k>�����翪ʼʱ��*/
                l=vl[k]-dut;        /*l���ǻ<j,k>������ʼʱ��*/
                printf("%s��%s %3d %3d %3d\n",N.vertex[j].data,N.vertex[k].data,e,l,l-e);
                if(e==l)            /*���ؼ��������������*/
                {
                    e1[count]=j;
                    e2[count]=k;
                    count++;
                }
            }
        printf("�ؼ��Ϊ��");
        for(k=0;k<count;k++)        /*����ؼ�·��*/
        {
            i=e1[k];
            j=e2[k];
            printf("(%s��%s) ",N.vertex[i].data,N.vertex[j].data);
        }
        printf("\n");
    return 1;
}

int LocateVertex(AdjGraph G,VertexType v)
/*����ͼ�ж����Ӧ��λ��*/
{
    int i;
    for(i=0;i<G.vexnum;i++)
        if(strcmp(G.vertex[i].data,v)==0)
            return i;
        return -1;
}
void CreateGraph(AdjGraph *N)
/*�����ڽӱ�洢�ṹ������������N*/
{
    int i,j,k,w;
    VertexType v1,v2;                   /*����������v1��v2*/
    ArcNode *p;
    printf("������ͼ�Ķ�����,����(�Զ��ŷָ�): ");
    scanf("%d,%d",&(*N).vexnum,&(*N).arcnum);
    printf("������%d�������ֵ:",N->vexnum);
    for(i=0;i<N->vexnum;i++)            /*������洢��ͷ�����*/
    {
        scanf("%s",N->vertex[i].data);
        N->vertex[i].firstarc=NULL;     /*��������Ķ�����Ϊ��*/
    }
    printf("�����뻡β����ͷ��Ȩֵ(�Կո���Ϊ�ָ�):\n");
    for(k=0;k<N->arcnum;k++)            /*����������*/
    {
        scanf("%s%s%*c%d",v1,v2,&w);
        i=LocateVertex(*N,v1);
        j=LocateVertex(*N,v2);
        /*jΪ��ͷiΪ��β�����ڽӱ�*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
        *(p->info)=w;
        /*��pָ��Ľ����뵽�߱���*/
        p->nextarc=N->vertex[i].firstarc;
        N->vertex[i].firstarc=p;
    }
    (*N).kind=DN;
}

void DisplayGraph(AdjGraph N)
/*�����ڽӾ���N�����*/
{
    int i;
    ArcNode *p;
    printf("��������%d�����㣺",N.vexnum);
    for(i=0;i<N.vexnum;i++)
        printf("%s ",N.vertex[i].data);
    printf("\n���й���%d����:\n",N.arcnum);
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
/*��������ͼG*/
{
    int i;
    ArcNode *p,*q;
    for(i=0;i<N->vexnum;++i)        /*�ͷ����еı߱���*/
    {
        p=N->vertex[i].firstarc;    /*pָ��߱�ĵ�һ�����*/
        if(p!=NULL)                 /*����߱�Ϊ�գ����ͷű߱�Ľ��*/
        {
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    (*N).vexnum=0;                  /*����������Ϊ0*/
    (*N).arcnum=0;                  /*���ߵ���Ŀ��Ϊ0*/
}

void main()
{
    AdjGraph N;
    CreateGraph(&N);        /*�����ڽӱ�洢�ṹ����������N*/
    DisplayGraph(N);        /*���������N*/
    CriticalPath(N);        /*����N�Ĺؼ�·��*/
    DestroyGraph(&N);       /*������N*/
}
