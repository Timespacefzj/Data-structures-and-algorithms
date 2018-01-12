#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    char key[15];	//关键字
    char name[20];
    int age;
}DATA; 	//数据结点类型
typedef struct Node
{
    DATA data;
    struct Node *next;
}ChainListType;
ChainListType *ChainListAddEnd(ChainListType *head,DATA data);
//添加结点到链表末尾
ChainListType *ChainListAddFirst(ChainListType *head,DATA data);
//添加结点到链表首部
ChainListType *ChainListFind(ChainListType *head,char *key);
//按关键字在链表中查找内容
ChainListType *ChainListInsert(ChainListType *head,char *findkey,DATA data);
//插入结点到链表指定位置
int ChainListDelete(ChainListType *head,char *key);
//删除指定关键字的结点
int ChainListLength(ChainListType *head);
//获取链表结点数量


ChainListType *ChainListAddEnd(ChainListType *head,DATA data)  //添加结点到链表结尾
{
    ChainListType *node,*h;
    if(!(node=(ChainListType *)malloc(sizeof(ChainListType))))
    {
        printf("为保存结点数据申请内存失败！\n");
        return NULL;  //分配内存失败
    }
    node->data=data; //保存数据
    node->next=NULL;  //设置结点指针为空，即为表尾
    if(head==NULL)  //是头指针
    {
        head=node;
        return head;
    }
    h=head;
    while(h->next!=NULL) //查找链表的末尾
        h=h->next ;
    h->next=node;
    return head;
}
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
ChainListType *ChainListInsert(ChainListType *head,char *findkey,DATA data)  //插入结点到链表指定位置
{
    ChainListType *node,*node1;
    if(!(node=(ChainListType *)malloc(sizeof(ChainListType)))) //分配保存结点的内容
    {
        printf("为保存结点数据申请内存失败！\n");
        return 0;  //分配内存失败
    }
    node->data=data;  //保存结点中的数据
    node1=ChainListFind(head,findkey);
    if(node1)  //若找到要插入的结点
    {
        node->next=node1->next;  //新插入结点指向关键结点的下一结点
        node1->next=node;    //设置关键结点指向新插入结点
    }else{
        free(node);//释放内存
        printf("未找到插入位置！\n");
    }
    return head;//返回头指针
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
int ChainListLength(ChainListType *head)//获取链表结点数量
{
    ChainListType *h;
    int i=0;
    h=head;
    while(h)      //遍历整个链表
    {
        i++; //累加结点数量
        h=h->next;//处理下一结点
    }
    return i;//返回结点数量
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
        printf("(%s,%s,%d)\n",data.key,data.name,data.age);
        h=h->next;//处理下一结点
    }
    return;
}
int main()
{
    ChainListType *node, *head=NULL;
    DATA data;
    char key[15],findkey[15];

    printf("输入链表中的数据，包括关键字、姓名、年龄，关键字输入0，则退出：\n");
    do{
        fflush(stdin);  //清空输入缓冲区
        scanf("%s",data.key);
        if(strcmp(data.key,"0")==0) break; //若输入0，则退出
        scanf("%s%d",data.name,&data.age);
        head=ChainListAddEnd(head,data);//在链表尾部添加结点数据
    }while(1);

    printf("该链表共有%d个结点。\n",ChainListLength(head)); //返回结点数量
    ChainListAll(head); //显示所有结点

    printf("\n插入结点，输入插入位置的关键字：") ;
    scanf("%s",&findkey);//输入插入位置关键字
    printf("输入插入结点的数据(关键字 姓名 年龄):");
    scanf("%s%s%d",data.key,data.name,&data.age);//输入插入结点数据
    head=ChainListInsert(head,findkey,data);//调用插入函数

    ChainListAll(head); //显示所有结点

    printf("\n在链表中查找，输入查找关键字:");
    fflush(stdin);//清空输入缓冲区
    scanf("%s",key);//输入查找关键字
    node=ChainListFind(head,key);//调用查找函数，返回结点指针
    if(node)//若返回结点指针有效
    {
        data=node->data;//获取结点的数据
        printf("关键字%s对应的结点数据为(%s,%s,%d)\n" ,key,data.key,data.name,data.age);
    }else//若结点指针无效
        printf("在链表中未找到关键字为%s的结点！\n",key);

    printf("\n在链表中删除结点，输入要删除的关键字:");
    fflush(stdin);//清空输入缓冲区
    scanf("%s",key);//输入删除结点关键字
    ChainListDelete(head,key); //调用删除结点函数
    ChainListAll(head); //显示所有结点

    return 0;
}
