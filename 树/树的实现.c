//����һ���������ղ�����������Ľ�㣬ͨ������Ҫ�޸ĵĽ��Ԫ��ֵ�޸Ľ��Ԫ��ֵ��������������ָ��
//λ�ò���һ����������������������Ϣ��
//�ڴ������Ĺ����У������˳�򴴽�����ÿ����һ���ַ��������������Ľ�������У�ͬʱ���ý����Ϣ����У� //�Ա��Ժ���Ӻ��ӽ����Ϣ��ÿλһ����������꺢�ӽ�㣬�ͽ���ͷ�����ӣ�Ϊ�˽����Ӻ��ӽ����Ϣ��

/*������Ͷ���*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAXSIZE 100
#define ClearTree InitTree /* ���߲�����ͬ */
#define DestroyTree InitTree /* ���߲�����ͬ */
/* �������Ԫ������ */
typedef char TElemType;
typedef struct
{
    int num;
    TElemType name;
}QElemType;
TElemType Nil=' '; /* �Կո����ʾ�� */

typedef struct QNode
{
    QElemType data;
    struct QNode* next;
}LQNode,*QueuePtr;
/*�������Ͷ���*/
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

/*����˫�ױ�洢��ʾ*/
typedef struct
{
    TElemType data;
    int parent; /* ˫��λ���� */
} PTNode;
typedef struct
{
    PTNode nodes[MAXSIZE];
    int n; /* ����� */
} PTree;


void InitQueue(LinkQueue *LQ)
/*��ʽ���еĳ�ʼ��*/
{
    LQ->front=LQ->rear=(LQNode*)malloc(sizeof(LQNode)); /*Ϊͷ��������ڴ�ռ�*/
    if(LQ->front==NULL)
        exit(-1);
    LQ ->front->next=NULL;  /*��ͷ����ָ������ΪΪ0*/
}
int QueueEmpty(LinkQueue LQ)
/*�ж���ʽ�����Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0*/
{
    if(LQ.front->next==NULL)        /*����ʽ����Ϊ��ʱ������1�����򷵻�0*/
        return 1;
    else
        return 0;
}
int EnQueue(LinkQueue *LQ,QElemType e)
/*��Ԫ��e���뵽��ʽ����LQ�У�����ɹ�����1*/
{
    LQNode *s;
    s=(LQNode*)malloc(sizeof(LQNode));  /*Ϊ��Ҫ��ӵ�Ԫ������һ�����Ŀռ�*/
    if(!s)
        exit(-1);                       /*�������ռ�ʧ�ܣ����˳������ز���-1*/
    s->data=e;                          /*��Ԫ��ֵ��ֵ������������*/
    s->next=NULL;                       /*������ָ������Ϊ��*/
    LQ->rear->next=s;                   /*��ԭ�����еĶ�βָ��ָ��p*/
    LQ->rear=s;                     /*����βָ��ָ��p*/
    return 1;
}
int DeQueue(LinkQueue *LQ,QElemType *e)
/*ɾ����ʽ�����еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0*/
{
    LQNode *s;
    if(LQ->front==LQ->rear)     /*��ɾ��Ԫ��֮ǰ���ж���ʽ�����Ƿ�Ϊ��*/
        return 0;
    else
    {
        s=LQ->front->next;              /*ʹָ��pָ���ͷԪ�ص�ָ��*/
        *e=s->data;                     /*��Ҫɾ���Ķ�ͷԪ�ظ�ֵ��e*/
        LQ->front->next=s->next;            /*ʹͷ����ָ��ָ��ָ��p����һ�����*/
        if(LQ->rear==s) LQ->rear=LQ->front; /*���Ҫɾ���Ľ���Ƕ�β����ʹ��βָ��ָ���ͷָ��*/
            free(s);                        /*�ͷ�ָ��pָ��Ľ��*/
        return 1;
    }
}
int GetHead (LinkQueue LQ,QElemType *e)
/*ȡ��ʽ�����еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ȡԪ�سɹ�����1�����򷵻�0*/
{
    LQNode *s;
    if(LQ.front==LQ.rear)       /*��ȡ��ͷԪ��֮ǰ���ж���ʽ�����Ƿ�Ϊ��*/
        return 0;
    else
    {
        s=LQ.front->next;   /*��ָ��pָ����еĵ�һ��Ԫ�ؼ���ͷԪ��*/
        *e=s->data;         /*����ͷԪ�ظ�ֵ��e��ȡ����ͷԪ��*/
        return 1;
    }
}
void ClearQueue(LinkQueue *LQ)
/*��ն���*/
{
    while(LQ->front!=NULL)
    {
        LQ->rear=LQ->front->next;       /*��βָ��ָ���ͷָ��ָ�����һ�����*/
        free(LQ->front);                /*�ͷŶ�ͷָ��ָ��Ľ��*/
        LQ->front=LQ->rear;         /*��ͷָ��ָ���βָ��*/
    }
}



void InitTree(PTree *T)
/* ����������������T */
{
    (*T).n=0;
}
void CreateTree(PTree *T)
/* ���������������T */
{
    LinkQueue q;
    QElemType p,qq;
    int i=1,j,l;
    char c[MAXSIZE]; /* ��ʱ��ź��ӽ������ */
    InitQueue(&q); /* ��ʼ������ */
    printf("����������(�ַ���,�ո�Ϊ��): ");
    scanf("%c%*c",&(*T).nodes[0].data); /* ��������Ϊ0��%*c�Ե��س��� */
    if((*T).nodes[0].data!=Nil) /* �ǿ��� */
    {
        (*T).nodes[0].parent=-1; /* �������˫�� */
        qq.name=(*T).nodes[0].data;
        qq.num=0;
        EnQueue(&q,qq); /* �ý����� */
        while(i<MAXSIZE&&!QueueEmpty(q)) /* ����δ���ҶӲ��� */
        {
            DeQueue(&q,&qq); /* ����һ����� */
            printf("�밴����˳��������%c�����к���: ",qq.name);
            gets(c);
            l=strlen(c);
            for(j=0;j<l;j++)
            {
                (*T).nodes[i].data=c[j];
                (*T).nodes[i].parent=qq.num;
                p.name=c[j];
                p.num=i;
                EnQueue(&q,p); /* �ý����� */
                i++;
            }
        }
        if(i>MAXSIZE)
        {
            printf("��������������������.\n");
            exit(-1);
        }
        (*T).n=i;
    }
    else
        (*T).n=0;
}

int TreeEmpty(PTree T)
/* ��ʼ��������T���ڡ������������TΪ�������򷵻�1�����򷵻�0*/
{
    if(T.n)
        return 0;
    else
        return 1;
}

int TreeDepth(PTree T)
/* ��ʼ��������T���ڡ��������������T����� */
{
    int k,m,def,max=0;
    for(k=0;k<T.n;++k)
    {
        def=1; /* ��ʼ����������� */
        m=T.nodes[k].parent;
        while(m!=-1)
        {
            m=T.nodes[m].parent;
            def++;
        }
        if(max<def)
            max=def;
    }
    return max; /* ������ */
}

TElemType Root(PTree T)
/* ��ʼ��������T���ڡ��������������T�ĸ� */
{
    int i;
    for(i=0;i<T.n;i++)
        if(T.nodes[i].parent<0)
            return T.nodes[i].data;
    return Nil;
}
TElemType Value(PTree T,int i)
/* ��ʼ��������T���ڣ�i����T�н�����š�������������ص�i������ֵ */
{
    if(i<T.n)
        return T.nodes[i].data;
    else
        return Nil;
}
int Assign(PTree *T,TElemType cur_e,TElemType value)
/* ��ʼ��������T���ڣ�cur_e����T�н���ֵ�������������cur_eΪvalue */
{
    int j;
    for(j=0;j<(*T).n;j++)
    {
        if((*T).nodes[j].data==cur_e)
        {
            (*T).nodes[j].data=value;
            return 1;
        }
    }
    return 0;
}
TElemType Parent(PTree T,TElemType cur_e)
{ /* ��ʼ��������T���ڣ�cur_e��T��ĳ����� */
/* �����������cur_e��T�ķǸ���㣬�򷵻�����˫�ף�������ֵΪ���գ�*/
    int j;
    for(j=1;j<T.n;j++) /* ��������Ϊ0 */
        if(T.nodes[j].data==cur_e)
            return T.nodes[T.nodes[j].parent].data;
    return Nil;
}
TElemType LeftChild(PTree T,TElemType cur_e)
{ /* ��ʼ��������T���ڣ�cur_e��T��ĳ����� */
    /* �����������cur_e��T�ķ�Ҷ�ӽ�㣬�򷵻����������ӣ����򷵻أ��գ�*/
    int i,j;
    for(i=0;i<T.n;i++)
        if(T.nodes[i].data==cur_e) /* �ҵ�cur_e�������Ϊi */
            break;
    for(j=i+1;j<T.n;j++) /* �������Ĺ��캯�������ӵ���ţ���˫�׵���� */
        if(T.nodes[j].parent==i) /* �������Ĺ��캯����������(����)����ţ��������ӵ���� */
            return T.nodes[j].data;
    return Nil;
}
TElemType RightSibling(PTree T,TElemType cur_e)
/* ��ʼ��������T���ڣ�cur_e��T��ĳ����� */
    /* �����������cur_e����(��һ��)�ֵܣ��򷵻��������ֵܣ����򷵻أ��գ�*/
{
    int i;
    for(i=0;i<T.n;i++)
        if(T.nodes[i].data==cur_e) /* �ҵ�cur_e�������Ϊi */
            break;
    if(T.nodes[i+1].parent==T.nodes[i].parent)
        /* �������Ĺ��캯������cur_e�����ֵܵĻ������ֵܽ������ */
        return T.nodes[i+1].data;
    return Nil;
}
void Print(PTree T)
/* �����T */
{
    int i;
    printf("������=%d\n",T.n);
    printf(" ��� ˫��\n");
    for(i=0;i<T.n;i++)
    {
        printf("    %c",Value(T,i)); /* ��� */
        if(T.nodes[i].parent>=0) /* ��˫�� */
            printf("    %c",Value(T,T.nodes[i].parent)); /* ˫�� */
        printf("\n");
    }
}
int InsertChild(PTree *T,TElemType p,int i,PTree c)
/* ��ʼ��������T���ڣ�p��T��ĳ����㣬1��i��p��ָ���Ķ�+1���ǿ���c��T���ཻ */
/* �������������cΪT��p���ĵ�i������ */
{
    int j,k,l,f=1,n=0; /* �轻����־f�ĳ�ֵΪ1��p�ĺ�����n�ĳ�ֵΪ0 */
    PTNode t;
    if(!TreeEmpty(*T)) /* T���� */
    {
        for(j=0;j<(*T).n;j++) /* ��T����p����� */
            if((*T).nodes[j].data==p) /* p�����Ϊj */
                break;
            l=j+1; /* ���c��p�ĵ�1�������������j+1�� */
            if(i>1) /* c����p�ĵ�1������ */
            {
                for(k=j+1;k<(*T).n;k++) /* ��j+1��ʼ��p��ǰi-1������ */
                    if((*T).nodes[k].parent==j) /* ��ǰ�����p�ĺ��� */
                    {
                        n++; /* ��������1 */
                        if(n==i-1) /* �ҵ�p�ĵ�i-1�����ӣ������Ϊk1 */
                            break;
                    }
                    l=k+1; /* c����k+1�� */
            } /* p�����Ϊj��c����l�� */
            if(l<(*T).n) /* �����l������� */
                for(k=(*T).n-1;k>=l;k--) /* ���ν����l�Ժ�Ľ�������c.n��λ�� */
                {
                    (*T).nodes[k+c.n]=(*T).nodes[k];
                    if((*T).nodes[k].parent>=l)
                        (*T).nodes[k+c.n].parent+=c.n;
                }
                for(k=0;k<c.n;k++)
                {
                    (*T).nodes[l+k].data=c.nodes[k].data; /* ���ν���c�����н����ڴ˴� */
                    (*T).nodes[l+k].parent=c.nodes[k].parent+l;
                }
                (*T).nodes[l].parent=j; /* ��c�ĸ�����˫��Ϊp */
                (*T).n+=c.n; /* ��T�Ľ������c.n�� */
                while(f)
                { /* �Ӳ����֮�󣬽�����԰��������� */
                    f=0; /* ������־��0 */
                    for(j=l;j<(*T).n-1;j++)
                        if((*T).nodes[j].parent>(*T).nodes[j+1].parent)
                        {/* ������j��˫�����ڽ��j+1��˫��֮��(��û�а���������)�����������*/
                            t=(*T).nodes[j];
                            (*T).nodes[j]=(*T).nodes[j+1];
                            (*T).nodes[j+1]=t;
                            f=1; /* ������־��1 */
                            for(k=j;k<(*T).n;k++) /* �ı�˫����� */
                                if((*T).nodes[k].parent==j)
                                    (*T).nodes[k].parent++; /* ˫����Ÿ�Ϊj+1 */
                                else if((*T).nodes[k].parent==j+1)
                                    (*T).nodes[k].parent--; /* ˫����Ÿ�Ϊj */
                        }
                }
                return 1;
    }
    else /* ��T������ */
        return 0;
}
void TraverseTree(PTree T,void(*Visit)(TElemType))
/* ��ʼ������������T����,Visit�ǶԽ�������Ӧ�ú��� */
/* ������������������T,��ÿ�������ú���Visitһ���ҽ�һ�� */
{
    int i;
    for(i=0;i<T.n;i++)
        Visit(T.nodes[i].data);
    printf("\n");
}
void vi(TElemType c)
{
    printf("%c ",c);
}

void main()
{
    int i;
    PTree T,p;
    TElemType e,e1;
    InitTree(&T);
    CreateTree(&T);
    printf("������T��,���շ�? %d(1:�� 0:��) ����Ϊ%c �������Ϊ%d\n",
    TreeEmpty(T),Root(T),TreeDepth(T));
    printf("���������T:\n");
    TraverseTree(T,vi);
    printf("��������޸ĵĽ���ֵ ��ֵ: ");
    scanf("%c%*c%c%*c",&e,&e1);
    Assign(&T,e,e1);
    printf("��������޸ĺ����T:\n");
    TraverseTree(T,vi);
    printf("%c��˫����%c,������%c,��һ���ֵ���%c\n",e1,Parent(T,e1),LeftChild(T,e1),RightSibling(T,e1));
    printf("������p:\n");
    InitTree(&p);
    CreateTree(&p);
    printf("���������p:\n");
    TraverseTree(p,vi);
    printf("����p�嵽��T�У�������T��p��˫�׽�� �������: ");
    scanf("%c%d%*c",&e,&i);
    InsertChild(&T,e,i,p);
    Print(T);
}
