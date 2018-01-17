#include"malloc.h"
#include"stdlib.h"
#include"stdio.h"
#include <string.h>
#define MAX_VERTEX_NUM 20   /*最大顶点个数*/
#define MAX_NAME 3           /*顶点字符串的最大长度+1 */
#define INFINITY 65535        /*65535代表整型最大值*/
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// 邻接矩阵的数据结构
typedef struct
{
    VRType adj; // 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否；
    InfoType *info; // 该弧相关信息的指针(可无)
 }ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的数据结构
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];    // 顶点向量
    AdjMatrix arcs;     // 邻接矩阵
    int vexnum;         // 图的当前顶点数
    int arcnum;         // 图的当前弧数
} MGraph;

// 记录从顶点集U到V-U的代价最小的边的辅助数组定义
typedef struct
{
    VertexType adjvex;
    VRType lowcost;
}Closedge[MAX_VERTEX_NUM];


// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。
int LocateVex(MGraph G,VertexType u)
{
    int i;
    for(i = 0; i < G.vexnum; ++i)
        if( strcmp(u, G.vexs[i]) == 0)
            return i;
    return -1;
}

// 采用数组(邻接矩阵)表示法,构造无向网G。
int CreateAN(MGraph *G)
{
    int i,j,k,w;
    VertexType va,vb;
    printf("请输入无向网G的顶点数和边数(以空格作为间隔): ");
    scanf("%d%d%*c",&(*G).vexnum,&(*G).arcnum);
    printf("请输入%d个顶点的值(每个顶点的字符数<%d个字符):\n",(*G).vexnum,MAX_NAME);
    for(i=0;i<(*G).vexnum;++i) // 构造顶点向量
        scanf("%s",(*G).vexs[i]);
    for(i=0;i<(*G).vexnum;++i) // 初始化邻接矩阵
        for(j=0;j<(*G).vexnum;++j)
        {
            (*G).arcs[i][j].adj=INFINITY; // 网初始化为无穷大
            (*G).arcs[i][j].info=NULL;
        }
    printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
    for(k=0;k<(*G).arcnum;++k)
    {
        scanf("%s%s%d%*c",va,vb,&w); // %*c吃掉回车符
        i=LocateVex(*G,va);
        j=LocateVex(*G,vb);
        (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; // 无向图
    }
    return 1;
}
// 求closedge.lowcost的最小正值
int MiniNum(Closedge edge,MGraph G)
{
    int i=0,j,k,min;
    while(!edge[i].lowcost)
        i++;
    min=edge[i].lowcost; // 第一个不为0的值
    k=i;
    for(j=i+1;j<G.vexnum;j++)
        if(edge[j].lowcost>0)
            if(min>edge[j].lowcost)
            {
                min=edge[j].lowcost;
                k=j;
            }
    return k;
}

// 用普里姆算法从第u个顶点出发构造网G的最小生成树T,输出T的各条边
void PRIM(MGraph G,VertexType u)
{
    int i,j,k;
    Closedge closedge;
    k=LocateVex(G,u);
    for(j=0;j<G.vexnum;++j) // 辅助数组初始化
    {
        if(j!=k)
        {
            strcpy(closedge[j].adjvex,u);
            closedge[j].lowcost=G.arcs[k][j].adj;
        }
    }
    closedge[k].lowcost=0; // 初始时,U={u}
    printf("普里姆算法求得的最小代价生成树的各条边为:\n");
    for(i=1;i<G.vexnum;++i)
    { // 选择其余G.vexnum-1个顶点
        k=MiniNum(closedge,G); // 求出T的下一个结点：第K顶点
        printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); // 输出生成树的边
        closedge[k].lowcost=0; // 第K顶点并入U集
        for(j=0;j<G.vexnum;++j)
            if(G.arcs[k][j].adj<closedge[j].lowcost)
            {
                // 新顶点并入U集后重新选择最小边
                strcpy(closedge[j].adjvex,G.vexs[k]);
                closedge[j].lowcost=G.arcs[k][j].adj;
            }
    }
}

//用克鲁斯卡尔算法求最小生成树
void Kruskal(MGraph G)
{
    int set[MAX_VERTEX_NUM],i,j;
    int a=0,b=0,min=G.arcs[a][b].adj,k=0;
    for(i=0;i<G.vexnum;i++)                  //初始时，各顶点分别属于不同的集合
        set[i]=i;
    printf("克鲁斯卡尔算法求得的最小生成树的各条边为：\n");
    while(k<G.vexnum-1)                      //查找所有最小权值的边
    {
        for(i=0;i<G.vexnum;i++)              //在矩阵的上三角查找最小权值的边
        {
            for(j=i+1;j<G.vexnum;j++)
            {
                if(G.arcs[i][j].adj<min)
                {
                    min=G.arcs[i][j].adj;
                    a=i;
                    b=j;
                }
            }
        }
        min=G.arcs[a][b].adj=INFINITY; //删除上三角中最小权值的边，下次不再查找
        if(set[a]!=set[b])            //如果边的两个顶点在不同的集合上
        {
            printf("%s-%s\n",G.vexs[a],G.vexs[b]);//输出最小权值的边
            k++;
            for(i=0;i<G.vexnum;i++)
            {
                if(set[i]==set[b])    //将顶点b所在集合并入顶点a集合中
                set[i]=set[a];
            }
        }
    }
}

void main()
{
    int i,j;
    MGraph G;
    CreateAN(&G);
    printf("图的邻接矩阵为：\n");
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
            printf("%d       ",G.arcs[i][j].adj);
        printf("\n");
    }
    PRIM(G,G.vexs[0]);
    Kruskal(G);
}
