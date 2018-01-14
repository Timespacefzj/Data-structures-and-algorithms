#include<stdio.h>
#define MaxLength 60
typedef struct
{
    char str[MaxLength];
    int length;
}SeqString;
void StrAssign(SeqString *S,char cstr[])
/*���ĸ�ֵ����*/
{
    int i=0;
    for(i=0;cstr[i]!='\0';i++)  /*������cstr�е��ַ���ֵ����S*/
        S->str[i]=cstr[i];
    S->length=i;
}
int StrEmpty(SeqString S)
/*�жϴ��Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0*/
{
    if(S.length==0)         /*�жϴ��ĳ����Ƿ����0*/
        return 1;           /*����Ϊ��ʱ������1�����򷵻�0*/
    else
        return 0;
}
int StrLength(SeqString S)
/*�󴮵ĳ��Ȳ���*/
{
    return S.length;
}
void StrCopy(SeqString *T,SeqString S)
/*���ĸ��Ʋ���.*/
{
    int i;
    for(i=0;i<S.length;i++)     /*����S���ַ���ֵ����T*/
        T->str[i]=S.str[i];
    T->length=S.length;         /*����S�ĳ��ȸ�ֵ����T*/
}
int StrCompare(SeqString S,SeqString T)
/*���ıȽϲ���*/
{
    int i;
    for(i=0;i<S.length&&i<T.length;i++) /*�Ƚ��������е��ַ�*/
        if(S.str[i]!=T.str[i])          /*��������ַ���ͬ���򷵻������ַ��Ĳ�ֵ*/
            return (S.str[i]-T.str[i]);
        return (S.length-T.length);             /*����Ƚ���ϣ������������ĳ��ȵĲ�ֵ*/
}
int StrInsert(SeqString *S,int pos,SeqString T)
/*���Ĳ����������S�е�pos��λ�ò���T��Ϊ�������*/
{
    int i;
    if(pos<0||pos-1>S->length)      /*����λ�ò���ȷ������0*/
    {
        printf("����λ�ò���ȷ");
        return 0;
    }
    if(S->length+T.length<=MaxLength)           /*��һ������������Ӵ��󴮳���MaxLength�����Ӵ�T�����ز��뵽��S��*/
    {
        /*�ڲ����Ӵ�Tǰ����S��pos����ַ�����ƶ�len��λ��*/
        for(i=S->length+T.length-1;i>=pos+T.length-1;i--)
            S->str[i]=S->str[i-T.length];
        /*�������뵽S��*/
        for(i=0;i<T.length;i++)
            S->str[pos+i-1]=T.str[i];
        S->length=S->length+T.length;
        return 1;
    }
    /*�ڶ���������Ӵ�������ȫ���뵽S�У�����S�е��ַ����ᱻ�ص�*/
    else if(pos+T.length<=MaxLength)
    {
        for(i=MaxLength-1;i>T.length+pos-1;i--) /*��S��pos�Ժ���ַ������ƶ�����������*/
            S->str[i]=S->str[i-T.length];
        for(i=0;i<T.length;i++)                 /*��T���뵽S��*/
            S->str[i+pos-1]=T.str[i];
        S->length=MaxLength;
        return 0;
    }
    /*������������Ӵ�T���ܱ���ȫ���뵽S�У�T�н������ַ�������*/
    else
    {
        for(i=0;i<MaxLength-pos;i++)            /*��Tֱ�Ӳ��뵽S�У�����֮ǰ����Ҫ�ƶ�S�е��ַ�*/
            S->str[i+pos-1]=T.str[i];
        S->length=MaxLength;
        return 0;
    }
}
int StrDelete(SeqString *S,int pos,int len)
/*�ڴ�S��ɾ��pos��ʼ��len���ַ�*/
{
    int i;
    if(pos<0||len<0||pos+len-1>S->length)
    {
        printf("ɾ��λ�ò���ȷ������len���Ϸ�");
        return 0;
    }
    else
    {
        for(i=pos+len;i<=S->length-1;i++)
            S->str[i-len]=S->str[i];
        S->length=S->length-len;
        return 1;
    }
}
int StrCat(SeqString *T,SeqString S)
{
    int i,flag;
    if(T->length+S.length<=MaxLength)
    {
        for(i=T->length;i<T->length+S.length;i++)
            T->str[i]=S.str[i-T->length];
        T->length=T->length+S.length;
        flag=1;
    }
    else if(T->length<MaxLength)
    {
        for(i=T->length;i<MaxLength;i++)
            T->str[i]=S.str[i-T->length];
        T->length=MaxLength;
        flag=0;
    }

    return flag;
}
void StrClear(SeqString *S)
{
    S->length=0;
}
int SubString(SeqString *Sub,SeqString S,int pos,int len)
{
    int i;
    if(pos<0||len<0||pos+len-1>S.length)
    {
        printf("����pos��len���Ϸ�");
        return 0;
    }
    else
    {
        for(i=0;i<len;i++)
            Sub->str[i]=S.str[i+pos-1];
        Sub->length=len;
        return 1;
    }
}
int StrReplace(SeqString *S,SeqString T,SeqString V)
{
    int i;
    int flag;
    if(StrEmpty(T))
        return 0;
    i=0;
    do
    {
        i=StrIndex(*S,i,T);
        if(i)
        {
            StrDelete(S,i,StrLength(T));
            flag=StrInsert(S,i,V);
            if(!flag)
                return 0;
            i+=StrLength(V);
        }
    }while(i);
    return 1;
}
int StrIndex(SeqString S,int pos,SeqString T)
{
    int i,j;
    if(StrEmpty(T))
        return 0;
    i=pos;
    j=0;
    while(i<S.length&&j<T.length)
    {
        if(S.str[i]==T.str[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>=T.length)
        return i-j+1;
    else
        return 0;
}

void StrPrint(SeqString S)
{
    int i;
    for(i=0;i<S.length;i++)
    {
        printf("%c",S.str[i]);
    }
    printf("\n");
}
void main()
{
    SeqString S1,S2,Sub;
    char ch[MaxLength];
    printf("�������һ���ַ���:\n");
    gets(ch);
    StrAssign(&S1,ch);
    printf("�����S1��");
    StrPrint(S1);
    printf("������ڶ����ַ���:\n");
    gets(ch);
    StrAssign(&S2,ch);
    printf("�����S2��");
    StrPrint(S2);
    printf("����S2���뵽S1�ĵ�13��λ��:\n");
    StrInsert(&S1,13,S2);
    StrPrint(S1);
    printf("����S1�еĵ�22��λ�����7���ַ�ɾ��:\n");
    StrDelete(&S1,22,7);
    StrPrint(S1);
    printf("����S2�еĵ�6��λ�����4�ַ�ȡ������Sub��:\n");
    SubString(&Sub,S2,6,4);
    StrPrint(Sub);
    printf("����Sub��ֵΪAmerica:\n");
    StrAssign(&Sub,"America");
    printf("����S1�еĴ�S2��Subȡ��:\n");
    StrReplace(&S1,S2,Sub);
    StrPrint(S1);
}
