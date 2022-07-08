#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 100

#define alloc(n, type) (type *)malloc(n*sizeof(type))

#define COMMAND(str) if(!strcmp(command, #str))

typedef int q_type;
typedef char boolean;

typedef struct CB_Queue
{
    q_type *data;
    
    int cap;  
    int count;
    int head; 
    int tail;  
} cb_queue;

boolean queue_empty(cb_queue *q);

q_type dequeue(cb_queue *q);

void init_queue(cb_queue *q, int nel);
void delete_queue(cb_queue *q);
void enqueue(cb_queue *q, q_type x);

void commands(cb_queue *q);

int main(int argc, char **argv)
{
    cb_queue Q;
    
    int start_size = 4;
    init_queue(&Q, start_size);
    
    commands(&Q);
    
    delete_queue(&Q);
    
    return 0;
}

boolean queue_empty(cb_queue *q)
{
    return !(q->count);
}

q_type dequeue(cb_queue *q)
{
    if(queue_empty(q))
    {
        delete_queue(q);
        
        printf("!ERROR!\n");
        
        exit(1);
    }
    
    q_type result = q->data[q->head];
    ++(q->head);
    
    if(q->head == q->cap)
        q->head = 0;
    
    --(q->count);
    
    return result;
}

void init_queue(cb_queue *q, int nel)
{
    q->data = alloc(nel, q_type);
    q->cap = nel;
    q->count = q->head = q->tail = 0;
}

void delete_queue(cb_queue *q)
{
    free(q->data);
    
    q->cap = q->count = q->head = q->tail = 0;
}

void enqueue(cb_queue *q, q_type x)
{
    if(q->count == q->cap)
    {
        int old_cap = q->cap;
        
        q->cap *= 2;
        q->data = (q_type *)realloc(q->data, sizeof(q_type)*q->cap);
        
        if(q->head)
	{ 
            memcpy(q->data+q->head+old_cap, q->data+q->head, (old_cap-q->head)*sizeof(q_type));
            
            q->head += old_cap;
        }
	else
            q->tail += old_cap;
    }
    
    q->data[q->tail] = x;
    ++(q->tail);
    
    if(q->tail == q->cap)
        q->tail = 0;
    
    ++(q->count);
}

void commands(cb_queue *q)
{
    int m;
    scanf("%i", &m);
    
    char command[LENGTH];
    
    int arg, i;
    for(i = 0; i < m; i++)
    {
        scanf("%s", command);
        
        COMMAND(ENQ)
	{
            scanf("%i", &arg);
            
            enqueue(q, arg);
        }
        
        COMMAND(DEQ)
	{
            printf("%i\n", dequeue(q));
        }
        
        COMMAND(EMPTY)
	{
            printf(queue_empty(q) ? "true\n" : "false\n");
        }
    }
}
