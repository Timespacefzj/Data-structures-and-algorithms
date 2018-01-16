#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
/*ͼ���ڽӱ����Ͷ���*/
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define MaxSize 50              /*��󶥵����*/
typedef enum{DG,DN,UG,UN}GraphKind;     /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct ArcNode          /*�߽������Ͷ���*/
{
    int adjvex;                 /*��ָ��Ķ����λ��*/
    InfoPtr *info;              /*�뻡��ص���Ϣ*/
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
/*��������*/
int LocateVertex(AdjGraph G,VertexType v);
void CreateGraph(AdjGraph *G);
void DisplayGraph(AdjGraph G);
void DestroyGraph(AdjGraph *G);

int LocateVertex(AdjGraph G,VertexType v)
/*����ͼ�ж����Ӧ��λ��*/
{
    int i;
    for(i=0;i<G.vexnum;i++)
        if(strcmp(G.vertex[i].data,v)==0)
            return i;
        return -1;
}
void CreateGraph(AdjGraph *G)
/*�����ڽӱ�洢�ṹ����������ͼG*/
{
    int i,j,k;
    VertexType v1,v2;               /*������������v1��v2*/
    ArcNode *p;
    printf("������ͼ�Ķ�����,����(���ŷָ�): ");
    scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
    printf("������%d�������ֵ:\n",G->vexnum);
    for(i=0;i<G->vexnum;i++)            /*������洢��ͷ�����*/
    {
        scanf("%s",G->vertex[i].data);
        G->vertex[i].firstarc=NULL; /*��������Ķ�����Ϊ��*/
    }
    printf("�����뻡β�ͻ�ͷ(�Կո���Ϊ���):\n");
    for(k=0;k<G->arcnum;k++)            /*����������*/
    {
        scanf("%s%s",v1,v2);
        i=LocateVertex(*G,v1);
        j=LocateVertex(*G,v2);
        /*jΪ��ͷiΪ��β�����ڽӱ�*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=NULL;
        p->nextarc=G->vertex[i].firstarc;
        G->vertex[i].firstarc=p;
        /*iΪ��ͷjΪ��β�����ڽӱ�*/
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=i;
        p->info=NULL;
        p->nextarc=G->vertex[j].firstarc;
        G->vertex[j].firstarc=p;
    }
    (*G).kind=UG;
}

void DestroyGraph(AdjGraph *G)
/*��������ͼG*/
{
    int i;
    ArcNode *p,*q;
    for(i=0;i<(*G).vexnum;++i)      /*�ͷ�ͼ�еı߱���*/
    {
        p=G->vertex[i].firstarc;        /*pָ��߱�ĵ�һ�����*/
        if(p!=NULL)                 /*����߱�Ϊ�գ����ͷű߱�Ľ��*/
        {
            q=p->nextarc;
            free(p);
            p=q;
        }
    }
    (*G).vexnum=0;                  /*����������Ϊ0*/
    (*G).arcnum=0;                  /*���ߵ���Ŀ��Ϊ0*/
}

void DisplayGraph(AdjGraph G)
/*���ͼ���ڽӾ���G*/
{
    int i;
    ArcNode *p;
    printf("%d�����㣺\n",G.vexnum);
    for(i=0;i<G.vexnum;i++)
        printf("%s ",G.vertex[i].data);
    printf("\n%d����:\n",2*G.arcnum);
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertex[i].firstarc;
        while(p)
        {
            printf("%s��%s ",G.vertex[i].data,G.vertex[p->adjvex].data);
            p=p->nextarc;
        }
        printf("\n");
    }
}
void main()
{
    AdjGraph G;
    printf("�����ڽӾ��󴴽�����ͼG��\n");
    CreateGraph(&G);
    printf("�������ͼG��");
    DisplayGraph(G);
    DestroyGraph(&G);
}
