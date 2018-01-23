#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*一元多项式结点类型定义*/

typedef struct polyn
{
	float coef;		/*存放一元多项式的系数*/
    int expn;		/*存放一元多项式的指数*/
    struct polyn *next;
}PolyNode, *PLinkList;

void OutPut(PLinkList head)
/*输出一元多项式*/
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
/*创建一元多项式，使一元多项式呈指数递减*/
{
    PolyNode *p,*q,*s;
	PolyNode *head=NULL;
	int expn2;
	float coef2;
	head=(PLinkList)malloc(sizeof(PolyNode));		/*动态生成一个头结点*/
	if(!head)
		return NULL;
	head->coef=0;
	head->expn=0;
	head->next=NULL;
	do
	{
		printf("输入系数coef(系数和指数都为0结束)");
		scanf("%f",&coef2);
		printf("输入指数exp(系数和指数都为0结束)");
		scanf("%d",&expn2);
		if((long)coef2==0&&expn2==0)
			break;
		s=(PolyNode*)malloc(sizeof(PolyNode));
		if(!s)
			return NULL;
		s->expn=expn2;
		s->coef=coef2;
		q=head->next;					/*q指向链表的第一个结点，即表尾*/
		p=head;						/*p指向q的前驱结点*/
		while(q&&expn2<q->expn)			/*将新输入的指数与q指向的结点指数比较*/
		{
			p=q;
			q=q->next;
		}
		if(q==NULL||expn2>q->expn)		/*q指向要插入结点的位置，p指向要插入结点的前驱*/
		{
			p->next=s;					/*将s结点插入到链表中*/
			s->next=q;
		}
		else
			q->coef+=coef2;				/*如果指数与链表中结点指数相同，则将系数相加即可*/
	} while(1);
	return head;
}
PolyNode *Reverse(PLinkList head)
/*将生的的链表逆置，使一元多项式呈指数递增形式*/
{
	PolyNode *q,*r,*p=NULL;
	q=head->next;
	while(q)
	{
		r=q->next;		/*r指向链表的待处理结点*/
		q->next=p;		/*将链表结点逆置*/
		p=q;			/*p指向刚逆置后链表结点*/
		q=r;			/*q指向下一准备逆置的结点*/
	}
	head->next=p;		/*将头结点的指针指向已经逆置后的链表*/
	return head;
}
PolyNode *MultiplyPolyn(PLinkList A,PLinkList B)
/*多项式的乘积。*/
{
	PolyNode *pa,*pb,*pc,*u,*head;
	int k,maxExp;
	float coef;
	head=(PLinkList)malloc(sizeof(PolyNode));		/*动态生成头结点*/
	if(!head)
		return NULL;
	head->coef=0.0;
	head->expn=0;
	head->next=NULL;
	if(A->next!=NULL&&B->next!=NULL)
		maxExp=A->next->expn+B->next->expn;	/*maxExp为两个链表指数的和的最大值*/
	else
		return head;
	pc=head;
	B=Reverse(B);							/*使多项式B（x）呈指数递增形式*/
	for(k=maxExp;k>=0;k--)					/*多项式的乘积指数范围为0-maxExp*/
	{
		pa=A->next;
		while(pa!=NULL&&pa->expn>k)			/*找到pa的位置*/
			pa=pa->next;
		pb=B->next;
		while(pb!=NULL&&pa!=NULL&&pa->expn+pb->expn<k)/*如果和小于k，使pb移到下一个结点*/
			pb=pb->next;
		coef=0.0;
		while(pa!=NULL&&pb!=NULL)
		{
			if(pa->expn+pb->expn==k)	/*如果在链表中找到对应的结点，即和等于k，求相应的系数*/
			{
				coef+=pa->coef*pb->coef;
				pa=pa->next;
				pb=pb->next;
			}
			else if(pa->expn+pb->expn>k)	/*如果和大于k，则使pa移到下一个结点*/
				pa=pa->next;
			else
				pb=pb->next;			/*如果和小于k，则使pb移到到下一个结点*/
		}
		if(coef!=0.0)
			/*如果系数不为0，则生成新结点，并将系数和指数分别赋值给新结点。并将结点插入到链表中*/
		{
			u=(PolyNode*)malloc(sizeof(PolyNode));
			u->coef=coef;
			u->expn=k;
			u->next=pc->next;
			pc->next=u;
			pc=u;
		}
	}
	B=Reverse(B);			/*完成多项式乘积后，将B（x）呈指数递减形式*/
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
	OutPut(C);				/*输出结果*/
	printf("\n");
}
