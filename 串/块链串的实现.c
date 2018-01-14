#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ChunkSize 4
#define stuff '#'
/*���Ľ�����Ͷ���*/
typedef struct Chunk
{
    char ch[ChunkSize];
    struct Chunk *next;
}Chunk;
/*���������Ͷ���*/
typedef struct
{
    Chunk *head;
    Chunk *tail;
    int length;
}LinkString;
void InitString(LinkString *S)
/*��ʼ���ַ���S*/
{
    S->length=0;            /*�����ĳ�����Ϊ0*/
    S->head=S->tail=NULL;   /*������ͷָ���βָ����Ϊ��*/
}
int StrAssign(LinkString *S,char *cstr)
/*����һ����ֵ����cstr�Ĵ�S���ɹ�����1�����򷵻�0*/
{
    int i,j,k,len;
    Chunk *p,*q;
    len=strlen(cstr);                   /*lenΪ�����ĳ��� */
    if(!len)
        return 0;
    S->length=len;
        j=len/ChunkSize;                /*jΪ�����Ľ���� */
    if(len%ChunkSize)
        j++;
    for(i=0;i<j;i++)
    {
        p=(Chunk*)malloc(sizeof(Chunk));    /*��̬����һ�����*/
        if(!p)
            return 0;
        for(k=0;k<ChunkSize&&*cstr;k++) /*���ַ���ctrs�е��ַ���ֵ��������������*/
            *(p->ch+k)=*cstr++;
        if(i==0)                        /*����ǵ�һ�����*/
            S->head=q=p;                /*ͷָ��ָ���һ�����*/
        else
        {
            q->next=p;
            q=p;
        }
        if(!*cstr)                      /*��������һ�������*/
        {
            S->tail=q;                  /*��βָ��ָ�����һ�����*/
            q->next=NULL;               /*��βָ���ָ������Ϊ��*/
            for(;k<ChunkSize;k++)       /*�����һ�������'#'���*/
            *(q->ch+k)=stuff;
        }
    }
    return 1;
}
int StrEmpty(LinkString S)
/*�жϴ��Ƿ�Ϊ�ա����SΪ�մ����򷵻�1�����򷵻�0*/
{
   if(S.length==0)                      /*�����Ϊ�գ�����1 */
     return 1;
   else                             /*������ǿգ�����0 */
     return 0;
 }
int StrLength(LinkString S)
/*�󴮵ĳ��� */
{
    return S.length;
}
int StrCopy(LinkString *T,LinkString S)
/*���ĸ��Ʋ���*/
{
    char *str;
    int flag;
    if(!ToChars(S,&str))        /*����S�е��ַ��������ַ���str��*/
        return 0;
    flag=StrAssign(T,str);      /*���ַ���str���ַ���ֵ����T��*/
    free(str);              /*�ͷ�str�Ŀռ� */
    return flag;
 }
 int ToChars(LinkString S,char **cstr)
/*����ת������������S������ת��Ϊ�ַ���������S�е��ַ�������cstr���ɹ�����1�����򷵻�0*/
{
    Chunk *p=S.head;            /*��pָ��S�еĵ�1�����*/
    int i;
    char *q;
    *cstr=(char*)malloc((S.length+1)*sizeof(char));
    if(!cstr||!S.length)
        return 0;
        q=*cstr;                    /*��qָ��cstr */
    while(p) /*����û���� */
    {
        for(i=0;i<ChunkSize;i++)
        if(p->ch[i]!=stuff)     /*�����ǰ�ַ��������������ַ�'#'����S���ַ���ֵ��q*/
        *q++=(p->ch[i]);
        p=p->next;
    }
    (*cstr)[S.length]=0;             /*���ַ�����ĩβ��ӽ�����־*/
    return 1;
}
int StrCompare(LinkString S,LinkString T)
/*���ıȽϲ�������S��ֵ����T���򷵻���ֵ����S��ֵ����T���򷵻�0����S��ֵС��T���򷵻ظ�ֵ*/
{
    char *p,*q;
    int flag;
    if(!ToChars(S,&p))          /*����Sת��Ϊ�ַ���p*/
        return 0;
    if(!ToChars(T,&q))          /*����Tת��Ϊ�ַ���q*/
        return 0;
    for(;*p!='\0'&&*q!='\0';)
        if(*p==*q)
        {
            p++;
            q++;
        }
        else
            flag=*p-*q;
    free(p);                    /*�ͷ�p�Ŀռ� */
    free(q);                    /*�ͷ�q�Ŀռ�*/
    if(*p=='\0'||*q=='\0')
        return S.length-T.length;
    else
        return flag;
}
int StrConcat(LinkString *T,LinkString S)
/*�������Ӳ���������S�����ڴ�T��β��*/
{
    int flag1,flag2;
    LinkString S1,S2;
    InitString(&S1);
    InitString(&S2);
    flag1=StrCopy(&S1,*T);          /*����T�����ݿ�����S1��*/
    flag2=StrCopy(&S2,S);               /*����S�����ݿ�����S2��*/
    if(flag1==0||flag2==0)          /*�����һ�����������ɹ����򷵻�0*/
        return 0;
    T->head=S1.head;                /*�޸Ĵ�T��ͷָ��*/
    S1.tail->next=S2.head;          /*����S1��S2��β����*/
    T->tail=S2.tail;                    /*�޸Ĵ�T��βָ��*/
    T->length=S.length+T->length;       /*�޸Ĵ�T�ĳ���*/
    return 1;
}
int StrInsert(LinkString *S, int pos,LinkString T)
/*���Ĳ���������ڴ�S�ĵ�pos��λ�ò��봮T*/
{
    char *t1,*s1;
    int i,j;
    int flag;
    if(pos<1||pos>S->length+1)      /*�������λ�ò��Ϸ�*/
        return 0;
    if(!ToChars(*S,&s1))                /*����Sת��Ϊ�ַ���s1*/
        return 0;
    if(!ToChars(T,&t1))             /*����Tת��Ϊ�ַ���t1*/
        return 0;
    j=strlen(s1);                   /*jΪ�ַ���s1�ĳ���*/
    s1=(char*)realloc(s1,(j+strlen(t1)+1)*sizeof(char));     /*Ϊs1���·���ռ�*/
    for(i=j;i>=pos-1;i--)
        s1[i+strlen(t1)]=s1[i];             /*���ַ���s1�еĵ�pos�Ժ���ַ�����ƶ�strlen(t1)��λ��*/
    for(i=0;i<(int)strlen(t1);i++)      /*���ַ���s1�в���t1*/
        s1[pos+i-1]=t1[i];
    InitString(S);                  /*�ͷ�S��ԭ�д洢�ռ�*/
    flag=StrAssign(S,s1);           /*��s1���ɴ�S*/
    free(t1);
    free(s1);
    return flag;
}
int StrDelete(LinkString *S,int pos,int len)
/*����ɾ������������S�еĵ�pos���ַ��𳤶�Ϊlen���Ӵ�ɾ��*/
{
    char *str;
    int i;
    int flag;
    if(pos<1||pos>S->length-len+1||len<0)   /*�������Ϸ�*/
        return 0;
    if(!ToChars(*S,&str))                   /*����Sת��Ϊ�ַ���str*/
        return 0;
    for(i=pos+len-1;i<=(int)strlen(str);i++)        /*���ַ����е�pos���ַ���ĳ���Ϊlen���Ӵ�ɾ��*/
        str[i-len]=str[i];
    InitString(S);                      /*�ͷ�S��ԭ�д洢�ռ�*/
    flag=StrAssign(S,str);                   /*���ַ���strת��Ϊ��S*/
    free(str);
    return flag;
}
int SubString(LinkString *Sub, LinkString S,int pos,int len)
/*ȡ�Ӵ���������Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���*/
{
    char *t,*str;
    int flag;
    if(pos<1||pos>S.length||len<0||len>S.length-pos+1)  /*�������Ϸ�*/
        return 0;
    if(!ToChars(S,&str))            /*����Sת��Ϊ�ַ���str*/
        return 0;
    t=str+pos-1;                /*tָ���ַ���str�е�pos���ַ�*/
    t[len]='\0';                    /* ��Sub��������Ϊ'\0'*/
    flag=StrAssign(Sub,t);      /*���ַ���tת��ΪSub */
    free(str);
    return flag;
}
void ClearString(LinkString *S)
/*��մ������������Ŀռ��ͷ�*/
{
    Chunk *p,*q;
    p=S->head;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    S->head=S->tail=NULL;
    S->length=0;
}

void StrPrint(LinkString S)
/*���������*/
{
    int i=0,j;
    Chunk *h;
    h=S.head;                       /*hָ���һ�����*/
    while(i<S.length)
    {
        for(j=0;j<ChunkSize;j++)    /*������е�ÿһ���ַ�*/
            if(*(h->ch+j)!=stuff)
            {
                printf("%c",*(h->ch+j));
                i++;
            }
            h=h->next;              /*hָ����һ�����*/
    }
    printf("\n");
}

void main()
{
    int i,j;
    int flag;
    LinkString S1,S2,S3,Sub;
    char *str1="Welcome to";
    char *str2=" Data Structure";
    char *str3="Computer Architecture";
    printf("���ĳ�ʼ���͸�ֵ����:\n");
    InitString(&S1);                    /*��S1��S2��S3�ĳ�ʼ��*/
    InitString(&S2);
    InitString(&S3);
    InitString(&Sub);
    StrAssign(&S1,str1);                /*��S1��S2��S3�ĸ�ֵ����*/
    StrAssign(&S2,str2);
    StrAssign(&S3,str3);
    printf("��S1��ֵ��:");
    StrPrint(S1);
    printf("��S2��ֵ��:");
    StrPrint(S2);
    printf("��S3��ֵ��:");
    StrPrint(S3);
    printf("����S2�����ڴ�S1��ĩβ:\n");
    StrConcat(&S1,S2);                  /*����S2�����ڴ�S1��ĩβ*/
    printf("S1��:");
    StrPrint(S1);
    printf("����S1�ĵ�12��λ�ú��14���ַ�ɾ��:\n");
    StrDelete(&S1,12,14);               /*����S1�еĵ�12��λ�ú��14���ַ�ɾ��*/
    printf("S1��:");
    StrPrint(S1);
    printf("����S2���뵽��S1�еĵ�12���ַ���:\n");
    StrInsert(&S1,12,S3);               /*����S3���뵽��S1�ĵ�12���ַ���*/
    printf("S1��:");
    StrPrint(S1);
    printf("����S1�еĵ�12���ַ����8���ַ�ȡ������ֵ����Sub:\n");
    SubString(&Sub,S1,12,8);            /*����S1�еĵ�12��λ�ú��8���ַ�ȡ����ֵ��Sub*/
    printf("Sub��:");
    StrPrint(Sub);
}

