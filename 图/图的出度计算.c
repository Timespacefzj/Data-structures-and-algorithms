#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef int DataType;			/*栈中的元素类型定义*/
typedef char VertexType[4];     /*图的邻接表类型定义*/
typedef int InfoPtr;			/*定义为整型，为了存放权值*/
typedef int VRType;
#define MaxSize 50				/*顶点个数最大值*/
typedef enum{DG,DN,UG,UN}GraphKind; 	/*图的类型：有向图、有向网、无向图和无向网*/
typedef struct ArcNode			/*边结点的类型定义*/
{
    int adjvex; 				/*弧指向的顶点的位置*/
	InfoPtr *info;				/*弧的权值*/
	struct ArcNode *nextarc; 	/*指示下一个与该顶点相邻接的顶点*/
}ArcNode;
typedef struct VNode			/*头结点的类型定义*/
{
	VertexType data; 			/*用于存储顶点*/
	ArcNode *firstarc; 			/*指示第一个与该顶点邻接的顶点*/
}VNode,AdjList[MaxSize];
typedef struct					/*图的类型定义*/
{
	AdjList vertex;
	int vexnum,arcnum;			/*图的顶点数目与弧的数目*/
	GraphKind kind; 			/*图的类型*/
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
	CreateGraph(&G);		/*采用邻接表存储结构创建有向图G*/
	DisplayGraph(G);		/*输出有向图G*/
	AllOutDegree(G);		/*有向图G各顶点的出度*/
	MaxOutDegree(G);		/*求有向图G出度最大的顶点*/
	ExistArc(G);			/*判断有向图G中是否存在弧<i,j>*/
	DestroyGraph(&G);		/*销毁图G*/
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
	printf("(1)各顶点的出度:\n");
	for(i=0;i<G.vexnum;i++)
		printf("顶点%s:%d\n",G.vertex[i].data,OutDegree(G,i));
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
	printf("(2)最大出度的顶点是%s,出度为%d\n",G.vertex[maxv].data,maxds);
}
void ZeroOutDegree(AdjGraph G)
{
	int i,x;
	printf("(3)出度为零的顶点:");
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
	printf("(4)是否存在弧<i,j>\n");
	printf("请输入弧的弧头和弧尾:");
	scanf("%s%s%*c",v1,v2);
	i=LocateVertex(G,v1);
	j=LocateVertex(G,v2);
	p=G.vertex[i].firstarc;
	while(p!=NULL && p->adjvex!=j)
		p=p->nextarc;
	if(p==NULL)
		printf("不存在弧<%s,%s>\n",v1,v2);
	else
		printf("存在弧<%s,%s>\n",v1,v2);
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
void CreateGraph(AdjGraph *G)
/*采用邻接表存储结构，创建有向图*/
{
	int i,j,k;
	VertexType v1,v2;					/*定义两个弧v1和v2*/
	ArcNode *p;
	printf("请输入图的顶点数,边数(以逗号分隔): ");
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
	printf("请输入%d个顶点的值:",G->vexnum);
	for(i=0;i<G->vexnum;i++)			/*将顶点存储在头结点中*/
	{
		scanf("%s",G->vertex[i].data);
		G->vertex[i].firstarc=NULL;		/*将相关联的顶点置为空*/
	}
	printf("请输入弧尾和弧头(以空格作为分隔):\n");
	for(k=0;k<G->arcnum;k++)			/*建立边链表*/
	{
		scanf("%s%s%*c",v1,v2);
		i=LocateVertex(*G,v1);
		j=LocateVertex(*G,v2);
		/*j为弧头i为弧尾创建邻接表*/
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		/*将p指向的结点插入到边表中*/
		p->nextarc=G->vertex[i].firstarc;
		G->vertex[i].firstarc=p;
	}
	(*G).kind=DG;
}
void DestroyGraph(AdjGraph *G)
/*销毁图*/
{
	int i;
	ArcNode *p,*q;
	for(i=0;i<G->vexnum;++i)		/*释放网中的边表结点*/
	{
		p=G->vertex[i].firstarc;	/*p指向边表的第一个结点*/
		if(p!=NULL)			/*如果边表不为空，则释放边表的结点*/
		{
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;					/*将顶点数置为0*/
	(*G).arcnum=0;					/*将边的数目置为0*/
}
void DisplayGraph(AdjGraph G)
/*输出图G的各条弧*/
{
	int i;
	ArcNode *p;
	printf("该图中有%d个顶点：",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\n图中共有%d条弧:\n",G.arcnum);
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
