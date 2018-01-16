#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef int DataType;			/*ջ�е�Ԫ�����Ͷ���*/
typedef char VertexType[4];     /*ͼ���ڽӱ����Ͷ���*/
typedef int InfoPtr;			/*����Ϊ���ͣ�Ϊ�˴��Ȩֵ*/
typedef int VRType;
#define MaxSize 50				/*����������ֵ*/
typedef enum{DG,DN,UG,UN}GraphKind; 	/*ͼ�����ͣ�����ͼ��������������ͼ��������*/
typedef struct ArcNode			/*�߽������Ͷ���*/
{
    int adjvex; 				/*��ָ��Ķ����λ��*/
	InfoPtr *info;				/*����Ȩֵ*/
	struct ArcNode *nextarc; 	/*ָʾ��һ����ö������ڽӵĶ���*/
}ArcNode;
typedef struct VNode			/*ͷ�������Ͷ���*/
{
	VertexType data; 			/*���ڴ洢����*/
	ArcNode *firstarc; 			/*ָʾ��һ����ö����ڽӵĶ���*/
}VNode,AdjList[MaxSize];
typedef struct					/*ͼ�����Ͷ���*/
{
	AdjList vertex;
	int vexnum,arcnum;			/*ͼ�Ķ�����Ŀ�뻡����Ŀ*/
	GraphKind kind; 			/*ͼ������*/
}AdjGraph;
int LocateVertex(AdjGraph G,VertexType v);
void CreateGraph(AdjGraph *G);
void DisplayGraph(AdjGraph G);
void DestroyGraph(AdjGraph *G);
int OutDegree(AdjGraph G,int v);
void AllOutDegree(AdjGraph G);
void MaxOutDegree(AdjGraph G);
void ZeroOutDegree(AdjGraph G);
void ExistArc(AdjGraph G);
void main()
{
	AdjGraph G;
	CreateGraph(&G);		/*�����ڽӱ�洢�ṹ��������ͼG*/
	DisplayGraph(G);		/*�������ͼG*/
	AllOutDegree(G);		/*����ͼG������ĳ���*/
	MaxOutDegree(G);		/*������ͼG�������Ķ���*/
	ExistArc(G);			/*�ж�����ͼG���Ƿ���ڻ�<i,j>*/
	DestroyGraph(&G);		/*����ͼG*/
}
int OutDegree(AdjGraph G,int v)
{
	ArcNode *p;
	int n=0;
	p=G.vertex[v].firstarc;
	while(p!=NULL)
	{
		n++;
		p=p->nextarc;
	}
	return n;
}
void AllOutDegree(AdjGraph G)
{
	int i;
	printf("(1)������ĳ���:\n");
	for(i=0;i<G.vexnum;i++)
		printf("����%s:%d\n",G.vertex[i].data,OutDegree(G,i));
	printf("\n");
}
void MaxOutDegree(AdjGraph G)
{
	int maxv=0,maxds=0,i,x;
	for(i=0;i<G.vexnum;i++)
	{
		x=OutDegree(G,i);
		if(x>maxds)
		{
			maxds=x;
			maxv=i;
		}
	}
	printf("(2)�����ȵĶ�����%s,����Ϊ%d\n",G.vertex[maxv].data,maxds);
}
void ZeroOutDegree(AdjGraph G)
{
	int i,x;
	printf("(3)����Ϊ��Ķ���:");
	for(i=0;i<G.vexnum;i++)
	{
		x=OutDegree(G,i);
		if(x==0)
			printf("%s\n",G.vertex[i].data);
	}
}
void ExistArc(AdjGraph G)
{
	int i,j;
	VertexType v1,v2;
	ArcNode *p;
	printf("(4)�Ƿ���ڻ�<i,j>\n");
	printf("�����뻡�Ļ�ͷ�ͻ�β:");
	scanf("%s%s%*c",v1,v2);
	i=LocateVertex(G,v1);
	j=LocateVertex(G,v2);
	p=G.vertex[i].firstarc;
	while(p!=NULL && p->adjvex!=j)
		p=p->nextarc;
	if(p==NULL)
		printf("�����ڻ�<%s,%s>\n",v1,v2);
	else
		printf("���ڻ�<%s,%s>\n",v1,v2);
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
void CreateGraph(AdjGraph *G)
/*�����ڽӱ�洢�ṹ����������ͼ*/
{
	int i,j,k;
	VertexType v1,v2;					/*����������v1��v2*/
	ArcNode *p;
	printf("������ͼ�Ķ�����,����(�Զ��ŷָ�): ");
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
	printf("������%d�������ֵ:",G->vexnum);
	for(i=0;i<G->vexnum;i++)			/*������洢��ͷ�����*/
	{
		scanf("%s",G->vertex[i].data);
		G->vertex[i].firstarc=NULL;		/*��������Ķ�����Ϊ��*/
	}
	printf("�����뻡β�ͻ�ͷ(�Կո���Ϊ�ָ�):\n");
	for(k=0;k<G->arcnum;k++)			/*����������*/
	{
		scanf("%s%s%*c",v1,v2);
		i=LocateVertex(*G,v1);
		j=LocateVertex(*G,v2);
		/*jΪ��ͷiΪ��β�����ڽӱ�*/
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		/*��pָ��Ľ����뵽�߱���*/
		p->nextarc=G->vertex[i].firstarc;
		G->vertex[i].firstarc=p;
	}
	(*G).kind=DG;
}
void DestroyGraph(AdjGraph *G)
/*����ͼ*/
{
	int i;
	ArcNode *p,*q;
	for(i=0;i<G->vexnum;++i)		/*�ͷ����еı߱���*/
	{
		p=G->vertex[i].firstarc;	/*pָ��߱�ĵ�һ�����*/
		if(p!=NULL)			/*����߱�Ϊ�գ����ͷű߱�Ľ��*/
		{
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;					/*����������Ϊ0*/
	(*G).arcnum=0;					/*���ߵ���Ŀ��Ϊ0*/
}
void DisplayGraph(AdjGraph G)
/*���ͼG�ĸ�����*/
{
	int i;
	ArcNode *p;
	printf("��ͼ����%d�����㣺",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\nͼ�й���%d����:\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertex[i].firstarc;
		while(p)
		{
			printf("<%s,%s> ",G.vertex[i].data,G.vertex[p->adjvex].data);
			p=p->nextarc;
		}
		printf("\n");
	}
}
