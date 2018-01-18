#include<iostream>
#include<iomanip>
#include<malloc.h>
#include<string.h>
using namespace std;
#define MaxListSize 20
#define EQUAL 1

typedef struct STU{
  char stuno [10];
  char name [10];
  float score;
  int age;
}ElemType;
class List
{private:
  //线性表的数组表示
  ElemType elem[MaxListSize];
  int length;
  int MaxSize;
 public:
  //输入学生数据
  void init(List **L,int ms);
  //删除所有学生数据
  void DestroyList(List &L){free(&L);}
  //将顺序表置为空表
  void ClearList(){length=0;}
  //判断顺序表是否为空表
  bool ListEmpty()
   {return length==0;}
  //判断顺序表是否为满
  bool ListFull()
   {return length==MaxSize;}
  //删除某个学生数据
  bool ListDelete(int,ElemType &e);
  //遍历顺序表
  void ListTraverse();
  //返回顺序表的长度
  int ListLength();
  //学生数据查询
  void GetElem(int,ElemType *);
  //修改学生数据
  bool UpdateList(ElemType& e,ElemType);
  //添加学生数据
  bool ListInsert(int,ElemType &);
  //对学生数据按升序或降序输出
  void printlist(int);
  bool EqualList(ElemType *,ElemType *);
  bool Less_EqualList(ElemType *,ElemType *);
  bool LocateElem(ElemType ,int);
};

void List::init(List **L,int ms)
{*L=(List *)malloc(sizeof(List));
 (*L)->length=0;
 (*L)->MaxSize=ms;
}
int List::ListLength()
{return length;}

bool List::ListDelete(int mark,ElemType &e)
{int i,j;
 if(ListEmpty()) return false;
 if(mark>0) {  //删除表头元素
    e=elem[0];
    for(i=1; i<length; i++)
     elem[i-1]=elem[i];}
 else   //删除表尾元素
   if(mark<0) e=elem[length-1];
   else {  //删除值为e的元素
    for(i=0;i<length;i++)
     if(strcmp(elem[i].name,e.name)==0) break;
     if(i>=length) return false;
     else e=elem[i];
     for(j=i+1;j<length;j++)
      elem[j-1]=elem[j];}
 length--;
 return true;
}
void List::ListTraverse()
{for(int i=0;i<length;i++)
   {cout<<setw(8)<<elem[i].name;
    cout<<setw(10)<<elem[i].stuno;
    cout<<setw(9)<<elem[i].age;
    cout<<setw(8)<<elem[i].score<<endl;}
}
void List::GetElem(int i,ElemType *e)
{*e=elem[i];}

bool List::EqualList(ElemType *e1,ElemType *e2)
{ if (strcmp(e1->name,e2->name))
    return false;
  if (strcmp(e1->stuno,e2->stuno))
    return false;
  if (e1->age!=e2->age)
    return false;
  if (e1->score!=e2->score)
    return false;
  return true;
}
bool List::Less_EqualList(ElemType *e1,ElemType *e2)
{ if(strcmp(e1->name,e2->name)<=0) return true;
  else return false;
}
bool List::LocateElem(ElemType e,int type)
{ int i;
  switch (type)
    { case EQUAL:
    for(i=0;i<length;i++)
      if(EqualList(&elem[i],&e))
        return true;
    break;
      default:break;}
  return false;
}
//修改学生数据
bool List::UpdateList(ElemType& e,ElemType e1)
{for(int i=0;i<length;i++)
   if(strcmp(elem[i].name,e.name)==0) {
     elem[i]=e1;return true;}
 return false;
}
bool List::ListInsert(int i,ElemType &e)
{ElemType *p,*q;
 if(i<1||i>length+1) return false;
 q=&elem[i-1];
 for(p=&elem[length-1];p>=q;--p)
   *(p+1)=*p;
 *q=e;
 ++length;
 return true;
}
//对学生成绩按升序或降序输出
void List::printlist(int mark)
{int* b=new int[length];
 int i,k;
 cout<<"    姓名     学号      成绩\n";
 if(mark!=0){
  for(i=0; i<length;i++) b[i]=i;
  for(i=0; i<length;i++) {k=i;
   for(int j=i+1;j<length;j++) {
    if(mark==1&&elem[b[j]].score<elem[b[k]].score) k=j;
    if(mark==-1&&elem[b[k]].score<elem[b[j]].score) k=j;}
    if(k!=i) {int x=b[i];b[i]=b[k];b[k]=x;}}
  for(int i=0;i<length;i++)
  {cout<<setw(8)<<elem[b[i]].name;
   cout<<setw(10)<<elem[b[i]].stuno;
   cout<<setw(9)<<elem[b[i]].age;
   cout<<setw(8)<<elem[b[i]].score<<endl;}}
 else {
  for(i=0;i<length;i++)
   {cout<<setw(8)<<elem[i].name;
    cout<<setw(10)<<elem[i].stuno;
    cout<<setw(9)<<elem[i].age;
    cout<<setw(8)<<elem[i].score<<endl;}}
}

int main()
{ cout<<"linelist1m.cpp运行结果:\n";
  ElemType e,e1,e2,e3,e4,e5,e6;
  List *La,*Lb,*Lc;
  int k;
  cout<<"首先调用插入函数.\n";
  La->init(&La,4);
  strcpy(e1.name,"stu1");
  strcpy(e1.stuno,"100001");
  e1.age=22;
  e1.score=88;
  La->ListInsert(1,e1);
  strcpy(e2.name,"stu2");
  strcpy(e2.stuno,"100002");
  e2.age=21;
  e2.score=79;
  La->ListInsert(2,e2);
  strcpy(e3.name,"stu3");
  strcpy(e3.stuno,"100003");
  e3.age=19;
  e3.score=87;
  La->ListInsert(3,e3);
  La->printlist(0);
  cout<<"表La长:"<<La->ListLength()<<endl;
  cin.get();

  Lb->init(&Lb,4);
  strcpy(e4.name,"zmofun");
  strcpy(e4.stuno,"100001");
  e4.age=20;
  e4.score=94;
  Lb->ListInsert(1,e4);
  strcpy(e5.name,"bobjin");
  strcpy(e5.stuno,"100002");
  e5.age=23;
  e5.score=69;
  Lb->ListInsert(2,e5);
  strcpy(e6.name,"stu1");
  strcpy(e6.stuno,"100001");
  e6.age=22;
  e6.score=88;
  Lb->ListInsert(3,e6);
  Lb->printlist(0);
  cout<<"表Lb长:"<<Lb->ListLength()<<endl;
  cin.get();

  k=Lc->ListDelete(-1,e6);
  if(k==0) cout<<"删除失败!\n";
  else cout<<"删除成功!\n";
  cout<<"输出表Lc:\n";
  Lc->printlist(0);
  cin.get();
  cout<<"按成绩升序输出表Lc\n";
  Lc->printlist(1);cin.get();
  cout<<"按成绩降序输出表Lc\n";
  Lc->printlist(-1);cin.get();
  return 0;
}
