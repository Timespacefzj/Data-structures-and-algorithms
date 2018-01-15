int LeafCount(BiTree T)
/*统计二叉树中叶子结点数目*/
{
    if(!T)                                  /*如果是空二叉树，返回0*/
      return 0;
    else
      if(!T->lchild&&!T->rchild)            /*如果左子树和右子树都为空，返回1*/
        return 1;
      else
        return LeafCount(T->lchild)+LeafCount(T->rchild); /*将左子树叶子结点个数与右子树叶子结点个数相加*/
}
int NotLeafCount(BiTree T)
/*统计二叉树中非叶子结点数目*/
{
    if(!T)                                  /*如果是空二叉树，返回0*/
        return 0;
    else if(!T->lchild&&!T->rchild)         /*如果是叶子结点，返回0*/
        return 0;
    else
        return NotLeafCount(T->lchild)+NotLeafCount(T->rchild)+1; /*左右子树的非叶子结点数目加上根结点的个数*/
}
int AllNodes(BiTree T)
/*求二叉树中所有结点的个数*/
{
    if(!T)                         /*如果是空二叉树返回0*/
        return 0;
    else if(!T->lchild&&!T->lchild)/*如果是叶子结点返回1*/
        return 1;
    else                           /*如果是非叶子节点，也不是根节点*/
        return AllNodes(T->lchild)+AllNodes(T->rchild)+1;/*左右子树结点个数加根节点个数*/

}
int BitTreeDepth(BiTree T)
/*计算二叉树的深度*/
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
        /*若左子树相似*/
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
    if(T->lchild!=NULL)/*若T的左子树不为空，则将左右子树交换*/
        Bitree_Swap(T->lchild);
    if(T->rchild!=NULL)/*若T的右子树不为空，则将左右子树交换*/
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
        /*遍历左子树*/
        {
            top++;
            if(top>=StackSize)
                exit(-1);
            s[top]=p;
            p=p->lchild;
        }
        if(top>0)/*若栈不为空*/
        {
            p=s[top];
            if(p->lchild == NULL ||p->rchild==q)/*根节点*/
            {
                if(p==r)/*找到r所指结点，则输出从根节点到r所指结点之间的结点*/
                {
                    for(i=1;i<=top;i++)
                    {
                        printf("%4d",s[i]->data);
                        top=0;
                    }
                }
                else
                {
                    q=p;/*用q保存刚刚遍历过的结点*/
                    top--;
                    p=NULL;
                }
            }
            else
                p=p->rchild;/*遍历右子树*/
        }
    }
}
