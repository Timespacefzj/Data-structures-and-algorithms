#include <stdio.h>
#include <string.h>
#define MAXSIZE 100  //定义线性表的最大长度

typedef struct
{
    char key[15];  //结点的关键字
    char name[20];
    int age;
} DATA;    //定义结点类型，可定义为简单类型，也可定义为结构
typedef struct    //定义顺序表结构
{
    DATA ListData[MAXSIZE+1]; //保存顺序表的数组
    int ListLen;              //顺序表已存结点 的数量
}SeqListType;

void SeqListInit(SeqListType *SL); //初始化顺序表
int SeqListLength(SeqListType *SL);  //返回顺序表的元素数量
int SeqListAdd(SeqListType *SL,DATA data); //向顺序表中添加元素
int SeqListInsert(SeqListType *SL,int n,DATA data); //向顺序表中插入元素
int SeqListDelete(SeqListType *SL,int n);  //删除顺序表中的据元素
DATA *SeqListFindByNum(SeqListType *SL,int n);  //根据序号返回元素
int SeqListFindByCont(SeqListType *SL,char *key); //按关键字查找
int SeqListAll(SeqListType *SL);//遍历顺序表中的内容

void SeqListInit(SeqListType *SL) //初始化顺序表
{
    SL->ListLen=0;     //初始化时，设置顺序表长度为0
}
int SeqListLength(SeqListType *SL)  //返回顺序表的元素数量
{
    return (SL->ListLen);
}
int SeqListAdd(SeqListType *SL,DATA data)  //增加元素到顺序表尾部
{
    if(SL->ListLen>=MAXSIZE)  //顺序表已满
    {
        printf("顺序表已满，不能再添加结点了！\n");
        return 0;
    }
    SL->ListData[++SL->ListLen]=data;
    return 1;
}
int SeqListInsert(SeqListType *SL,int n,DATA data)
{
    int i;
    if(SL->ListLen>=MAXSIZE)   //顺序表结点数量已超过最大数量
    {
        printf("顺序表已满，不能插入结点!\n");
        return 0;             //返回0表示插入不成功
    }
    if(n<1 || n>SL->ListLen)  //插入结点序号不正确
    {
        printf("插入元素序号错误，不能插入元素！\n");
        return 0;              //返回0，表示插入不成功
    }
    for(i=SL->ListLen;i>=n;i--)  //将顺序表中的数据向后移动
        SL->ListData[i+1]=SL->ListData[i];
    SL->ListData[n]=data;        //插入结点
    SL->ListLen++;               //顺序表结点数量增加1
    return 1;                   //返回成功插入
}
int SeqListDelete(SeqListType *SL,int n)  //删除顺序表中的数据元素
{
    int i;
    if(n<1 || n>SL->ListLen)  //删除元素序号不正确
    {
        printf("删除结点序号错误，不能删除结点！\n");
        return 0;              //返回0，表示删除不成功
    }
    for(i=n;i<=SL->ListLen;i++)  //将顺序表中的数据向前移动
        SL->ListData[i]=SL->ListData[i+1];
    SL->ListLen--;               //顺序表元素数量减1
    return 1;                   //返回成功删除
}
DATA *SeqListFindByNum(SeqListType *SL,int n)  //根据序号返回数据元素
{
    if(n<1 || n>SL->ListLen)  //元素序号不正确
    {
        printf("结点序号错误，不能返回结点！\n");
        return NULL;              //返回0，表示不成功
    }
    return &(SL->ListData[n]);
}
int SeqListFindByCont(SeqListType *SL,char *key)  //按关键字查询结点
{
    int i;
    for(i=1;i<=SL->ListLen;i++)
        if(strcmp(SL->ListData[i].key,key)==0)  //如果找到所需结点
            return i;        //返回结点序号
    return 0;  //遍历后仍没有找到，则返回0


}


int SeqListAll(SeqListType *SL)  //遍历顺序表中的结点
{
    int i;
    for(i=1;i<=SL->ListLen;i++)
        printf("(%s,%s,%d)\n",SL->ListData[i].key,SL->ListData[i].name,SL->ListData[i].age);
}

void  main()
{
	int i;
    SeqListType SL;         //定义顺序表变量
    DATA data,*data1;       //定义结点保存数据类型变量和指针变量
    char key[15];           //保存关键字

    SeqListInit(&SL);       //初始化顺序表

    do {                    //循环添加结点数据
        printf("输入添加的结点(学号 姓名 年龄)：");
        fflush(stdin);              //清空输入缓冲区
        scanf("%s%s%d",&data.key,&data.name,&data.age);
        if(data.age)                                    //若年龄不为0
        {
            if(!SeqListAdd(&SL,data))                   //若添加结点失败
                break;                                  //退出死循环
        }else   //若年龄为0
            break;          //退出死循环
    }while(1);
    printf("\n顺序表中的结点顺序为：\n");
    SeqListAll(&SL);                     //显示所有结点数据

    fflush(stdin);                       //清空输入缓冲区
    printf("\n要取出结点的序号：");
    scanf("%d",&i);                 //输入结占点序号
    data1=SeqListFindByNum(&SL,i);  //按序号查找结点
    if(data1)                       //若返回的结点指针不为NULL
        printf("第%d个结点为：(%s,%s,%d)\n",i,data1->key,data1->name,data1->age);

    fflush(stdin);                                                             //清空输入缓冲区
    printf("\n要查找结点的关键字：");
    scanf("%s",key);  //输入关键字
    i=SeqListFindByCont(&SL,key);      //按关键字查找 ，返回结点序号
    data1=SeqListFindByNum(&SL,i);     //按序号查询，返回结点指针
    if(data1)                          //若结点指针不为NULL
        printf("第%d个结点为：(%s,%s,%d)\n",i,data1->key,data1->name,data1->age);

	return 0;
}
