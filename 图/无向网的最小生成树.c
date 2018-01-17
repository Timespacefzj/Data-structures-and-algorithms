#include"malloc.h"
#include"stdlib.h"
#include"stdio.h"
#include <string.h>
#define MAX_VERTEX_NUM 20   /*��󶥵����*/
#define MAX_NAME 3           /*�����ַ�������󳤶�+1 */
#define INFINITY 65535        /*65535�����������ֵ*/
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// �ڽӾ�������ݽṹ
typedef struct
{
    VRType adj; // �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ�
    InfoType *info; // �û������Ϣ��ָ��(����)
 }ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// ͼ�����ݽṹ
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];    // ��������
    AdjMatrix arcs;     // �ڽӾ���
    int vexnum;         // ͼ�ĵ�ǰ������
    int arcnum;         // ͼ�ĵ�ǰ����
} MGraph;

// ��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
typedef struct
{
    VertexType adjvex;
    VRType lowcost;
}Closedge[MAX_VERTEX_NUM];


// ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1��
int LocateVex(MGraph G,VertexType u)
{
    int i;
    for(i = 0; i < G.vexnum; ++i)
        if( strcmp(u, G.vexs[i]) == 0)
            return i;
    return -1;
}

// ��������(�ڽӾ���)��ʾ��,����������G��
int CreateAN(MGraph *G)
{
    int i,j,k,w;
    VertexType va,vb;
    printf("������������G�Ķ������ͱ���(�Կո���Ϊ���): ");
    scanf("%d%d%*c",&(*G).vexnum,&(*G).arcnum);
    printf("������%d�������ֵ(ÿ��������ַ���<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
    for(i=0;i<(*G).vexnum;++i) // ���춥������
        scanf("%s",(*G).vexs[i]);
    for(i=0;i<(*G).vexnum;++i) // ��ʼ���ڽӾ���
        for(j=0;j<(*G).vexnum;++j)
        {
            (*G).arcs[i][j].adj=INFINITY; // ����ʼ��Ϊ�����
            (*G).arcs[i][j].info=NULL;
        }
    printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
    for(k=0;k<(*G).arcnum;++k)
    {
        scanf("%s%s%d%*c",va,vb,&w); // %*c�Ե��س���
        i=LocateVex(*G,va);
        j=LocateVex(*G,vb);
        (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; // ����ͼ
    }
    return 1;
}
// ��closedge.lowcost����С��ֵ
int MiniNum(Closedge edge,MGraph G)
{
    int i=0,j,k,min;
    while(!edge[i].lowcost)
        i++;
    min=edge[i].lowcost; // ��һ����Ϊ0��ֵ
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

// ������ķ�㷨�ӵ�u���������������G����С������T,���T�ĸ�����
void PRIM(MGraph G,VertexType u)
{
    int i,j,k;
    Closedge closedge;
    k=LocateVex(G,u);
    for(j=0;j<G.vexnum;++j) // ���������ʼ��
    {
        if(j!=k)
        {
            strcpy(closedge[j].adjvex,u);
            closedge[j].lowcost=G.arcs[k][j].adj;
        }
    }
    closedge[k].lowcost=0; // ��ʼʱ,U={u}
    printf("����ķ�㷨��õ���С�����������ĸ�����Ϊ:\n");
    for(i=1;i<G.vexnum;++i)
    { // ѡ������G.vexnum-1������
        k=MiniNum(closedge,G); // ���T����һ����㣺��K����
        printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); // ����������ı�
        closedge[k].lowcost=0; // ��K���㲢��U��
        for(j=0;j<G.vexnum;++j)
            if(G.arcs[k][j].adj<closedge[j].lowcost)
            {
                // �¶��㲢��U��������ѡ����С��
                strcpy(closedge[j].adjvex,G.vexs[k]);
                closedge[j].lowcost=G.arcs[k][j].adj;
            }
    }
}

//�ÿ�³˹�����㷨����С������
void Kruskal(MGraph G)
{
    int set[MAX_VERTEX_NUM],i,j;
    int a=0,b=0,min=G.arcs[a][b].adj,k=0;
    for(i=0;i<G.vexnum;i++)                  //��ʼʱ��������ֱ����ڲ�ͬ�ļ���
        set[i]=i;
    printf("��³˹�����㷨��õ���С�������ĸ�����Ϊ��\n");
    while(k<G.vexnum-1)                      //����������СȨֵ�ı�
    {
        for(i=0;i<G.vexnum;i++)              //�ھ���������ǲ�����СȨֵ�ı�
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
        min=G.arcs[a][b].adj=INFINITY; //ɾ������������СȨֵ�ıߣ��´β��ٲ���
        if(set[a]!=set[b])            //����ߵ����������ڲ�ͬ�ļ�����
        {
            printf("%s-%s\n",G.vexs[a],G.vexs[b]);//�����СȨֵ�ı�
            k++;
            for(i=0;i<G.vexnum;i++)
            {
                if(set[i]==set[b])    //������b���ڼ��ϲ��붥��a������
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
    printf("ͼ���ڽӾ���Ϊ��\n");
    for(i=0; i<G.vexnum; i++)
    {
        for(j=0; j<G.vexnum; j++)
            printf("%d       ",G.arcs[i][j].adj);
        printf("\n");
    }
    PRIM(G,G.vexs[0]);
    Kruskal(G);
}
