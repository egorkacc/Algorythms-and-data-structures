#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000
#define REQUEST_SIZE 5

typedef struct queue b;

struct queue 
{
    int *max, *data;
    int cap, top1, top2;
};

void push1(b *q, int x);
void push2(b *q, int x);
void enqueue(b *q, int x);

int queueempty(b *q);
int dequeue(b *q);
int pop1(b *q);
int pop2(b *q);

int stackempty1(b *q);
int stackempty2(b *q);

int max(b q);

int main(int argc, char **argv) 
{
    int n;
    scanf("%i", &n);
    
    char str[REQUEST_SIZE];
    
    struct queue q;
    q.data = (int *)malloc(sizeof(int)*SIZE);
    q.max = (int *)malloc(sizeof(int)*SIZE);
    
    q.cap = SIZE;
    q.top1 = 0;
    q.top2 = SIZE - 1;
    
    int i, j;
    int x_str;
    for(i = 0; i < n; i++) 
	{
        scanf("%s", str);
        
        if(!strcmp(str, "EMPTY")) 
		{
            j = queueempty(&q);
            if(j != 1)
                printf("false\n");
            else 
				printf("true\n");
        }
        
        if(!strcmp(str, "ENQ")) 
		{
            scanf("%i", &x_str);
			   
            enqueue(&q, x_str);
        }
        
        if(!strcmp(str, "DEQ")) 
		{
            x_str = dequeue(&q);
            
            printf("%i\n", x_str);                      
        }
        
        if(!strcmp(str,"MAX")) 
		{ 
            j = max(q);
            
            printf("%i\n", j);
        }
    }
        
    free(q.max);
    free(q.data);
    
    return 0;
}

void push1(b *q, int x_str) 
{
    q->data[q->top1] = x_str;
    if(!(q->top1))
        q->max[q->top1] = x_str;   
    else if(q->max[q->top1 - 1] < x_str)
        q->max[q->top1] = x_str;
    else 
		q->max[q->top1] = q->max[q->top1 - 1];
		
    ++(q->top1);
}

void push2(b *q, int x_str)
{
    q->data[q->top2] = x_str;
    
    if(q->top2 == (q->cap - 1))
        q->max[q->top2] = x_str;
    else if(q->max[q->top2 + 1]>x_str)
        q->max[q->top2] = q->max[q->top2 + 1];
    else 
		q->max[q->top2] = x_str;
		
    --(q->top2);
}

void enqueue(b *q, int x_str) 
{
    push1(q, x_str);
}

int queueempty(b *q) 
{
    if(stackempty1(q) && stackempty2(q))
        return 1;
    else 
		return 0;
}

int dequeue(b *q) 
{
    int x_str;
    if(stackempty2(q)) 
        while(!stackempty1(q))
            push2(q, pop1(q));
            
    x_str = pop2(q);
    
    return x_str;
}

int pop1(b *q) 
{
    --(q->top1);
    int x_str = q->data[q->top1];
    
    return x_str;
}

int pop2(b *q) 
{
    ++(q->top2);
    int x_str = q->data[q->top2];
    
    return x_str;
}

int stackempty1(b *q) 
{
    if(!(q->top1))
        return 1;
    else 
		return 0;
}

int stackempty2(b *q) 
{
    if(q->top2 == (q->cap - 1))
        return 1;
    else 
		return 0;
}

int max(b q) 
{
    int x_str;
    
    if(q.top1 && 
		((q.top2 == (q.cap - 1)) ||
			((q.top2 != (q.cap - 1)) && 
				(q.max[q.top1 - 1]> q.max[q.top2 + 1]))))
        return q.max[q.top1 - 1];
    else 
		return q.max[q.top2 + 1];
}
