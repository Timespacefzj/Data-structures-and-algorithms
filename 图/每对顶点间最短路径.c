#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define INFINITY 65535          /*����һ�����޴��ֵ*/
#define MaxSize 50              /*��󶥵����*/
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
typedef enum{DG,DN,UG,UN}GraphKind;     /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef int PathMatrix[MaxSize][MaxSize][MaxSize];  /*����һ���������·������ά����*/
typedef int ShortPathLength[MaxSize][MaxSize];      /*����һ������Ӷ���v������w����̾��������*/
typedef struct
{
    VRType adj;             /*������Ȩͼ����1��ʾ���ڣ�0��ʾ�����ڣ����ڴ�Ȩͼ���洢Ȩֵ*/
    InfoPtr *info;              /*�뻡��ߵ������Ϣ*/
}ArcNode,AdjMatrix[MaxSize][MaxSize];
typedef struct                  /*ͼ�����Ͷ���*/
{
    VertexType vex[MaxSize];    /*���ڴ洢����*/
    AdjMatrix arc;              /*�ڽӾ��󣬴洢�߻򻡵���Ϣ*/
    int vexnum,arcnum;          /*�������ͱߣ���������Ŀ*/
    GraphKind kind;             /*ͼ������*/
}MGraph;
typedef struct                  /*���һ���洢�����С��к�Ȩֵ�����Ͷ���*/
{
    int row;
    int col;
    int weight;
}GNode;

void Floyd(MGraph N,PathMatrix path,ShortPathLength dist)
/*��Floyd�㷨��������N�ĸ�����v��w�����·����
����path[v][w][u]��ʾu�Ǵ�v��w��ǰ������·���ϵĶ���*/
{
    int u,v,w,i;
    for(v=0;v<N.vexnum;v++)                 /*��ʼ������path��dist*/
        for(w=0;w<N.vexnum;w++)
        {
            dist[v][w]=N.arc[v][w].adj;     /*��ʼʱ������v������w�����·��Ϊv��w�Ļ���Ȩֵ*/
            for(u=0;u<N.vexnum;u++)
                path[v][w][u]=0;            /*·�������ʼ��Ϊ��*/
            if(dist[v][w]<INFINITY)          /*���v��w��·��������v��w��·������v��w����*/
            {
                path[v][w][u]=1;
                path[v][w][w]=1;
            }
        }
    for(u=0;u<N.vexnum;u++)
        for(v=0;v<N.vexnum;v++)
            for(w=0;w<N.vexnum;w++)
                if(dist[v][u]<INFINITY&&dist[u][w]<INFINITY&&dist[v][u]+dist[u][w]<dist[v][w])
                /*��v��u��w��һ��·��Ϊ��ǰ��̵�·��*/
                {
                    dist[v][w]=dist[v][u]+dist[u][w];   /*����v��w�����·��*/
                    for(i=0;i<N.vexnum;i++)             /*��v��w��·��������v��u�ʹ�u��w������·��*/
                        path[v][w][i]=path[v][u][i]||path[u][w][i];
                }
}

void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch)
/*�����ڽӾ����ʾ������������N*/
{
    int i,j,k;
    N->vexnum=vnum;
    N->arcnum=arcnum;
    for(i=0;i<vnum;i++)             /*���������㸳ֵ��vex��*/
        strcpy(N->vex[i],ch[i]);
    for(i=0;i<N->vexnum;i++)            /*��ʼ���ڽӾ���*/
        for(j=0;j<N->vexnum;j++)
        {
            N->arc[i][j].adj=INFINITY;
            N->arc[i][j].info=NULL; /*������Ϣ��ʼ��Ϊ��*/
        }
    for(k=0;k<arcnum;k++)
    {
        i=value[k].row;
        j=value[k].col;
        N->arc[i][j].adj=value[k].weight;
    }

    N->kind=DN;                     /*ͼ������Ϊ������*/
}

void DisplayGraph(MGraph N)
/*����ڽӾ���洢��ʾ��ͼN*/
{
    int i,j;
    printf("����������%d������%d����������������: ",N.vexnum,N.arcnum);
    for(i=0;i<N.vexnum;++i)             /*������Ķ���*/
        printf("%s ",N.vex[i]);
    printf("\n������N��:\n");               /*�����N�Ļ�*/
    printf("���i=");
    for(i=0;i<N.vexnum;i++)
        printf("%8d",i);
    printf("\n");
    for(i=0;i<N.vexnum;i++)
    {
        printf("%8d",i);
        for(j=0;j<N.vexnum;j++)
            printf("%8d",N.arc[i][j].adj);
        printf("\n");
    }
}

void main()
{
    int i,j,vnum=6,arcnum=8;
    MGraph N;
    GNode value[]={{0,2,15},{0,4,30},{0,5,100},{1,2,10},
    {2,3,50},{3,5,10},{4,3,20},{5,4,60}};
    VertexType ch[]={"v0","v1","v2","v3","v4","v5"};
    PathMatrix path;                        /*�ö�ά���������·���������Ķ���*/
    ShortPathLength dist;                   /*��һά���������·������*/
    CreateGraph(&N,value,vnum,arcnum,ch); /*����������N*/
    DisplayGraph(N);                        /*���������N*/
    Floyd(N,path,dist);
    for(i=0;i<N.vexnum;i++)
    {
        for(j=i+1;j<N.vexnum;j++)
        printf("%s��%s�����·������Ϊ��%d\n",N.vex[i],N.vex[j],dist[i][j]);
    }
}
