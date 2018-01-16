#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 65535          /*����һ�����޴��ֵ*/
#define MaxSize 50              /*��󶥵����*/
typedef enum{DG,DN,UG,UN}GraphKind;     /*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct
{
    VRType adj;                 /*������Ȩͼ����1��ʾ���ڣ�0��ʾ�����ڣ����ڴ�Ȩͼ���洢Ȩֵ*/
    InfoPtr *info;              /*�뻡��ߵ������Ϣ*/
}ArcNode,AdjMatrix[MaxSize][MaxSize];
typedef struct                  /*ͼ�����Ͷ���*/
{
    VertexType vex[MaxSize];    /*���ڴ洢����*/
    AdjMatrix arc;              /*�ڽӾ��󣬴洢�߻򻡵���Ϣ*/
    int vexnum,arcnum;          /*�������ͱߣ���������Ŀ*/
    GraphKind kind;             /*ͼ������*/
}MGraph;
void CreateGraph(MGraph *N);
int LocateVertex(MGraph N,VertexType v);
void DestroyGraph(MGraph *N);
void DisplayGraph(MGraph N);

void CreateGraph(MGraph *N)
/*�����ڽӾ����ʾ������������N*/
{
    int i,j,k,w,InfoFlag,len;
    char s[MaxSize];
    VertexType v1,v2;
    printf("������������N�Ķ�����,����,������Ϣ(��:1,��:0): ");
    scanf("%d,%d,%d",&(*N).vexnum,&(*N).arcnum,&InfoFlag);
    printf("������%d�������ֵ(<%d���ַ�):\n",N->vexnum,MaxSize);
    for(i=0;i<N->vexnum;++i)        /*����һ�����飬���ڱ������ĸ�������*/
        scanf("%s",N->vex[i]);
    for(i=0;i<N->vexnum;i++)        /*��ʼ���ڽӾ���*/
        for(j=0;j<N->vexnum;j++)
        {
            N->arc[i][j].adj=INFINITY;
            N->arc[i][j].info=NULL; /*������Ϣ��ʼ��Ϊ��*/
        }
        printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",N->arcnum);
        for(k=0;k<N->arcnum;k++)
        {
            scanf("%s%s%d",v1,v2,&w);   /*������������ͻ���Ȩֵ*/
            i=LocateVertex(*N,v1);
            j=LocateVertex(*N,v2);
            N->arc[i][j].adj=w;
            if(InfoFlag)                /*���������������Ϣ*/
            {
                printf("�����뻡�������Ϣ: ");
                gets(s);
                len=strlen(s);
                if(len)
                {
                    N->arc[i][j].info=(char*)malloc((len+1)*sizeof(char)); /* ���� */
                    strcpy(N->arc[i][j].info,s);
                }
            }
        }
        N->kind=DN;                     /*ͼ������Ϊ������*/
}
int LocateVertex(MGraph N,VertexType v)
/*�ڶ��������в��Ҷ���v���ҵ���������������ţ����򷵻�-1*/
{
    int i;
    for(i=0;i<N.vexnum;++i)
        if(strcmp(N.vex[i],v)==0)
            return i;
        return -1;
}

void DestroyGraph(MGraph *N)
/*������N*/
{
    int i,j;
    for(i=0;i<N->vexnum;i++)                /*�ͷŻ��������Ϣ*/
        for(j=0;j<N->vexnum;j++)
            if(N->arc[i][j].adj!=INFINITY)  /*������ڻ�*/
                if(N->arc[i][j].info!=NULL) /*������������Ϣ���ͷŸ���Ϣ��ռ�ÿռ�*/
                {
                    free(N->arc[i][j].info);
                    N->arc[i][j].info=NULL;
                }
    N->vexnum=0; /*�����Ķ�������Ϊ0*/
    N->arcnum=0; /*�����Ļ�����Ŀ��Ϊ0*/
}



void DisplayGraph(MGraph N)
/*����ڽӾ���洢��ʾ��ͼG*/
{
    int i,j;
    printf("����������%d������%d����������������: ",N.vexnum,N.arcnum);
    for(i=0;i<N.vexnum;++i)             /*������Ķ���*/
        printf("%s ",N.vex[i]);
    printf("\n������N��:\n");           /*�����N�Ļ�*/
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

    MGraph N;
    printf("����һ������\n");
    CreateGraph(&N);
    printf("������Ķ���ͻ���\n");
    DisplayGraph(N);
    printf("��������\n");
    DestroyGraph(&N);
}
