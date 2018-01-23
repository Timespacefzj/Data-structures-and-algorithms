#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*һԪ����ʽ������Ͷ���*/

typedef struct polyn
{
	float coef;		/*���һԪ����ʽ��ϵ��*/
    int expn;		/*���һԪ����ʽ��ָ��*/
    struct polyn *next;
}PolyNode, *PLinkList;

void OutPut(PLinkList head)
/*���һԪ����ʽ*/
{
	PolyNode *p=head->next;
	while(p)
	{
		printf("%1.1f",p->coef);
		if(p->expn)
			printf("*x^%d",p->expn);
		if(p->next&&p->next->coef>0)
			printf("+");
		p=p->next;
	}
}

PLinkList CreatePolyn()
/*����һԪ����ʽ��ʹһԪ����ʽ��ָ���ݼ�*/
{
    PolyNode *p,*q,*s;
	PolyNode *head=NULL;
	int expn2;
	float coef2;
	head=(PLinkList)malloc(sizeof(PolyNode));		/*��̬����һ��ͷ���*/
	if(!head)
		return NULL;
	head->coef=0;
	head->expn=0;
	head->next=NULL;
	do
	{
		printf("����ϵ��coef(ϵ����ָ����Ϊ0����)");
		scanf("%f",&coef2);
		printf("����ָ��exp(ϵ����ָ����Ϊ0����)");
		scanf("%d",&expn2);
		if((long)coef2==0&&expn2==0)
			break;
		s=(PolyNode*)malloc(sizeof(PolyNode));
		if(!s)
			return NULL;
		s->expn=expn2;
		s->coef=coef2;
		q=head->next;					/*qָ������ĵ�һ����㣬����β*/
		p=head;						/*pָ��q��ǰ�����*/
		while(q&&expn2<q->expn)			/*���������ָ����qָ��Ľ��ָ���Ƚ�*/
		{
			p=q;
			q=q->next;
		}
		if(q==NULL||expn2>q->expn)		/*qָ��Ҫ�������λ�ã�pָ��Ҫ�������ǰ��*/
		{
			p->next=s;					/*��s�����뵽������*/
			s->next=q;
		}
		else
			q->coef+=coef2;				/*���ָ���������н��ָ����ͬ����ϵ����Ӽ���*/
	} while(1);
	return head;
}
PolyNode *Reverse(PLinkList head)
/*�����ĵ��������ã�ʹһԪ����ʽ��ָ��������ʽ*/
{
	PolyNode *q,*r,*p=NULL;
	q=head->next;
	while(q)
	{
		r=q->next;		/*rָ������Ĵ�������*/
		q->next=p;		/*������������*/
		p=q;			/*pָ������ú�������*/
		q=r;			/*qָ����һ׼�����õĽ��*/
	}
	head->next=p;		/*��ͷ����ָ��ָ���Ѿ����ú������*/
	return head;
}
PolyNode *MultiplyPolyn(PLinkList A,PLinkList B)
/*����ʽ�ĳ˻���*/
{
	PolyNode *pa,*pb,*pc,*u,*head;
	int k,maxExp;
	float coef;
	head=(PLinkList)malloc(sizeof(PolyNode));		/*��̬����ͷ���*/
	if(!head)
		return NULL;
	head->coef=0.0;
	head->expn=0;
	head->next=NULL;
	if(A->next!=NULL&&B->next!=NULL)
		maxExp=A->next->expn+B->next->expn;	/*maxExpΪ��������ָ���ĺ͵����ֵ*/
	else
		return head;
	pc=head;
	B=Reverse(B);							/*ʹ����ʽB��x����ָ��������ʽ*/
	for(k=maxExp;k>=0;k--)					/*����ʽ�ĳ˻�ָ����ΧΪ0-maxExp*/
	{
		pa=A->next;
		while(pa!=NULL&&pa->expn>k)			/*�ҵ�pa��λ��*/
			pa=pa->next;
		pb=B->next;
		while(pb!=NULL&&pa!=NULL&&pa->expn+pb->expn<k)/*�����С��k��ʹpb�Ƶ���һ�����*/
			pb=pb->next;
		coef=0.0;
		while(pa!=NULL&&pb!=NULL)
		{
			if(pa->expn+pb->expn==k)	/*������������ҵ���Ӧ�Ľ�㣬���͵���k������Ӧ��ϵ��*/
			{
				coef+=pa->coef*pb->coef;
				pa=pa->next;
				pb=pb->next;
			}
			else if(pa->expn+pb->expn>k)	/*����ʹ���k����ʹpa�Ƶ���һ�����*/
				pa=pa->next;
			else
				pb=pb->next;			/*�����С��k����ʹpb�Ƶ�����һ�����*/
		}
		if(coef!=0.0)
			/*���ϵ����Ϊ0���������½�㣬����ϵ����ָ���ֱ�ֵ���½�㡣���������뵽������*/
		{
			u=(PolyNode*)malloc(sizeof(PolyNode));
			u->coef=coef;
			u->expn=k;
			u->next=pc->next;
			pc->next=u;
			pc=u;
		}
	}
	B=Reverse(B);			/*��ɶ���ʽ�˻��󣬽�B��x����ָ���ݼ���ʽ*/
	return head;
}

void main()
{
    PLinkList A,B,C;
	A=CreatePolyn();
	printf("A(x)=");
	OutPut(A);
	printf("\n");
	B=CreatePolyn();
	printf("B(x)=");
	OutPut(B);
	printf("\n");
	C=MultiplyPolyn(A,B);
	printf("C(x)=A(x)*B(x)=");
	OutPut(C);				/*������*/
	printf("\n");
}
