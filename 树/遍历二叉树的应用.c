int LeafCount(BiTree T)
/*ͳ�ƶ�������Ҷ�ӽ����Ŀ*/
{
    if(!T)                                  /*����ǿն�����������0*/
      return 0;
    else
      if(!T->lchild&&!T->rchild)            /*�������������������Ϊ�գ�����1*/
        return 1;
      else
        return LeafCount(T->lchild)+LeafCount(T->rchild); /*��������Ҷ�ӽ�������������Ҷ�ӽ��������*/
}
int NotLeafCount(BiTree T)
/*ͳ�ƶ������з�Ҷ�ӽ����Ŀ*/
{
    if(!T)                                  /*����ǿն�����������0*/
        return 0;
    else if(!T->lchild&&!T->rchild)         /*�����Ҷ�ӽ�㣬����0*/
        return 0;
    else
        return NotLeafCount(T->lchild)+NotLeafCount(T->rchild)+1; /*���������ķ�Ҷ�ӽ����Ŀ���ϸ����ĸ���*/
}
int AllNodes(BiTree T)
/*������������н��ĸ���*/
{
    if(!T)                         /*����ǿն���������0*/
        return 0;
    else if(!T->lchild&&!T->lchild)/*�����Ҷ�ӽ�㷵��1*/
        return 1;
    else                           /*����Ƿ�Ҷ�ӽڵ㣬Ҳ���Ǹ��ڵ�*/
        return AllNodes(T->lchild)+AllNodes(T->rchild)+1;/*���������������Ӹ��ڵ����*/

}
int BitTreeDepth(BiTree T)
/*��������������*/
{
    if(T == NULL)
        return 0;
    return
        BitTreeDepth(T->lchild)>BitTreeDepth(T->rchild)?1+BitTreeDepth(T->lchild):1+BitTreeDepth(T->rchild);
}
void MaxMinLeaf(BitTree T,int *max,int *min)
{
    int m1,m2,n1,n2;
    if(T==NULL)
    {
        *max=0;
        *min=0;
    }
    else
    {
        MaxMinLeaf(T->lchild,m1,n1);
        MaxMinLeaf(T->rchild,m2,n2);
        *max=(m1>m2?m1:m2)+1;
        *min=(m1<m2?m1:m2)+1;
    }
}
int BiTree_Like(BiTree t1,BiTree t2)
{
    if(t1==NULL && t2==NULL)
        return 1;
    if((t1!=NULL && t2==NULL)||(t1==NULL && t2!=NULL))
        return 0;
    if(BiTree_Like(t1->rchild,t2->rchild))
        /*������������*/
        return (BiTree_Like(t1->rchild,t2->rchild))
    else
        return 0;
}
void Bitree_Swap(BiTree T)
{
    BiTree p;
    if(!T=NULL)
        if(T->lchild!=NULL||T->rchild!=NULL)
    {
        p=T->rchild;
        T->lchild=T->rchild;
        T->rchild=p;
    }
    if(T->lchild!=NULL)/*��T����������Ϊ�գ���������������*/
        Bitree_Swap(T->lchild);
    if(T->rchild!=NULL)/*��T����������Ϊ�գ���������������*/
        Bitree_Swap(T->rchild);
}
void path(BiTree root,BitNode *r)
{
    BitNode *p,*q;
    int i ,top=0;
    BitNode *s[StackSize];
    q=NULl;
    p=root;
    while(p!=NULL||top!=0)
    {
        while(p!NULL)
        /*����������*/
        {
            top++;
            if(top>=StackSize)
                exit(-1);
            s[top]=p;
            p=p->lchild;
        }
        if(top>0)/*��ջ��Ϊ��*/
        {
            p=s[top];
            if(p->lchild == NULL ||p->rchild==q)/*���ڵ�*/
            {
                if(p==r)/*�ҵ�r��ָ��㣬������Ӹ��ڵ㵽r��ָ���֮��Ľ��*/
                {
                    for(i=1;i<=top;i++)
                    {
                        printf("%4d",s[i]->data);
                        top=0;
                    }
                }
                else
                {
                    q=p;/*��q����ոձ������Ľ��*/
                    top--;
                    p=NULL;
                }
            }
            else
                p=p->rchild;/*����������*/
        }
    }
}
