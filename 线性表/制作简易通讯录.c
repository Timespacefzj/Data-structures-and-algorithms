#include <stdio.h>
typedef struct
{
    char key[15];   //关键字(设置姓名为关键字)
    char addr[20];
    char telephone[15];
    char mobile[12];
}DATA;  //数据结点类型

typedef struct Node
{
    DATA data;
    struct Node *next;
}ChainListType;

ChainListType *ChainListAddFirst(ChainListType *head,DATA data)
{
    ChainListType *node,*h;
    if(!(node=(ChainListType *)malloc(sizeof(ChainListType))))
    {
        printf("为保存结点数据申请内存失败！\n");
        return NULL;  //分配内存失败
    }
    node->data=data; //保存数据
    node->next=head;  //指向头指针所指结点
    head=node;        //头指针指向新增结点
    return head;
}

ChainListType *ChainListFind(ChainListType *head,char *key) //按关键字在链表中查找内容
{
    ChainListType *h;
    h=head;       //保存链表头指针
    while(h)      //若结点有效，则进行查找
    {
        if(strcmp(h->data.key,key)==0) //若结点关键字与传入关键字相同
            return h;  //返回该结点指针
        h=h->next; //处理下一结点
    }
    return NULL; //返回空指针
}

int ChainListDelete(ChainListType *head,char *key)
{
    ChainListType *node,*h;
    node=head;   //node保存删除结点的前一结点
    h=head;    //h为移动指针
    while(h)
    {
        if(strcmp(h->data.key,key)==0) //找到关键字，执行删除操作
        {
            node->next=h->next;  //使前一结点指向当前结点的下一结点
            free(h);  //释放内存
            return 1;
        }else{
            node=h;  //指向当前结点
            h=h->next; //指向下一结点
        }
     }
     return 0;//未删除
}

void ChainListAll(ChainListType *head) //遍历链表
{
    ChainListType *h;
    DATA data;
    h=head;
    printf("链表所有数据如下：\n");
    while(h) //循环处理链表每个结点
    {
        data=h->data;//获取结点数据
        printf("姓名:%s\n",data.key);
        printf("地址:%s\n",data.addr);
        printf("电话:%s\n",data.telephone);
        printf("手机:%s\n",data.mobile);
        h=h->next;//处理下一结点
    }
    return;
}

ChainListType *input(ChainListType *head) //向通讯录中输入的信息
{
    DATA data;
    printf("请输入联系人信息\n");
    printf("姓名:");
    scanf("%s",data.key);
    printf("地址:");
    scanf("%s",data.addr);
    printf("电话:");
    scanf("%s",data.telephone);
    printf("手机:");
    scanf("%s",data.mobile);
    return ChainListAddFirst(head,data); //调用添加函数
}

void find(ChainListType *head)
{
    ChainListType *h;
    DATA data;
    char name[15];
    printf("请输入查找姓名:");
    scanf("%s",name);
    h=ChainListFind(head,name);
    if(h)//查找结点指针有效
    {
        data=h->data;//获取结点数据
        printf("姓名:%s\n",data.key);
        printf("地址:%s\n",data.addr);
        printf("电话:%s\n",data.telephone);
        printf("手机:%s\n",data.mobile);
    }
}

void delete(ChainListType *head)
{
    ChainListType *h=head;
    char name[15];
    printf("请输入要删除的姓名:");
    scanf("%s",name);
    ChainListDelete(head,name);
}

int main()
{
    ChainListType *node, *head=NULL;
    int select;//选择菜单的序号
    do{
        printf("\n_____________________\n");
        printf("1.添加联系人\n");
        printf("2.查找联系人\n");
        printf("3.删除联系人\n");
        printf("4.显示所有联系人\n");
        printf("0.退出\n");
        printf("_____________________\n");
        select=getch();
        switch(select)
        {
            case '1':
                printf("\n添加联系人\n");
                head=input(head);
                break;
            case '2':
                 printf("\n查找联系人\n");
                 find(head);
                 break;
           case '3':
                printf("\n删除联系人\n");
                delete(head);
                break;
           case '4':
                printf("\n显示联系人\n");
                ChainListAll(head);
                break;
           case '0':
                return 0;
        }
    }while(select != '0');
}
