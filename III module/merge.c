#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int *heap;
    int count, cap;
};

void InitPrioritiQueue(struct queue *q, int size_r);
void Insert(struct queue *q, int ptr);

void swap(struct queue *q, int i, int j);

int Heapify(struct queue *base, int i, int n, int ptr);
int ExtractMax(struct queue *q);

int main(int argc, char **argv) 
{
    int k;
    scanf("%i", &k);
	int n[k];
	
	int i;
	int size_r = 0;
    for(i = 0; i < k; i++)
	{
        scanf("%i", &n[i]);
        
        size_r += n[i];
    }

    struct queue *q = (struct queue *)malloc(sizeof(struct queue)*size_r);
    InitPrioritiQueue(q, size_r);

	int num;
    for(i = 0; i < size_r; i++)
	{
        scanf("%i", &num);
        
        Insert(q, num);
    }
    
    for(i = 0; i < size_r; i++)
        printf("%i ", ExtractMax(q));

    free(q->heap);
    free(q);

    return 0;
}

void InitPrioritiQueue(struct queue *q, int size_r)
{
    q->heap = (int *)malloc(sizeof(int)*size_r);
    
    q->cap = size_r;
    q->count = 0;
}

void Insert(struct queue *q, int ptr)
{
    int i = q->count;
    
    if(i == q->cap)
        printf("Out of space :c");
        
    i = (q->count)++;
    q->heap[i] = ptr;
    
    while(i && (q->heap[i] < q->heap[(i - 1)/2]))
	{
        int swp = q->heap[i];
        q->heap[i] = q->heap[(i - 1)/2];
        q->heap[(i - 1)/2] = swp;
        
        i = (i - 1)/2 ;
    }
}

void swap(struct queue *q, int i, int j) 
{
    int temp = q->heap[i];
    q->heap[i] = q->heap[j];
    q->heap[j] = temp;
}

int compare(int a, int b)
{
	if(a < b)
		return -1;
    if(a == b) 
		return 0;
	else
		return 1;
}

int Heapify(struct queue *base,int i, int n, int ptr)
{
    while(i < n/2)
	{
        int l = 2*i + 1;
        int r = l + 1;
        
        if(!(compare(r, n) >= 0) && !(compare(base->heap[r], base->heap[l]) >= 0))
            l = r;
            
        if(!(compare(base->heap[i], base->heap[l]) > 0))
            return ptr;
            
        swap(base, i, l);
        
        i = l;
    }
    return ptr;
}
