#include <stdio.h>
#include <stdlib.h>
#define Maxsize 200
typedef struct
{
    int key;
    /*other fields*/
}Elementtype;
typedef struct
{
    Elementtype elements[Maxsize];
    int n;
}HEAP;
void MaxHeap(HEAP *heap)
{
    heap->n=0;
}
int HeapEmpty(HEAP heap)
{
    return(!heap.n);
}
void Insert(HEAP *heap,Elementtype element)
{
    int i;
    i=heap->n+1;
    while( (i!=1)&&(element.key>heap->elements[i/2].key))
    {
        heap->elements[i]=heap->elements[i/2];
        i/=2;
    }
    heap->elements[i]=element;
    heap->n++;
}
Elementtype DeleteMax(HEAP *heap)
{
    int parent=1,child=2;
    Elementtype element,tmp;
    if(!HeapEmpty(*heap))
    {
        element=heap->elements[1];
        tmp=heap->elements[heap->n--];
        while(child <= heap->n)
        {
            if((child<heap->n)&&(heap->elements[child].key<heap->elements[child+1].key))
                child++;
            if(tmp.key >= heap->elements[child].key)
                break;
            heap->elements[parent]=heap->elements[child];
            parent=child;
            child*=2;
        }
        heap->elements[parent]=tmp;
        return element;
    }
}
int main()
{
    int n,i;
    HEAP h;
    MaxHeap(&h);
    printf("请输入要插入的元素个数：（不超过200）");
    scanf("%d",&n);
    while(n>Maxsize)
    {
        printf("元素个数超出堆的容量！请重新输入：");
        scanf("%d",&n);
    }
    Elementtype a[n+1],x;
    printf("请依次输入每个元素的值：");
    for (i = 1; i <= n; i++)
    {
        scanf("%d",&a[i].key);
        Insert(&h, a[i]);
    }
    while (!HeapEmpty(h))
    {
        x = DeleteMax(&h);
        printf("%d", x.key);
        if (!HeapEmpty(h))
            printf(",");
    }
    printf("\n");
    return 0;
}
