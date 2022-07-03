#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTER_RANGE 26

#define LENGTH 100
#define S_LENGTH 100000
#define MEM_WIDTH 65536

#define KEY(c) (c - 'a')

#define alloc silly_alloc(&Container)
#define my_free(x) silly_free(x, &Container)

#define COMMAND(str) if(!strcmp(command, #str))

typedef char boolean;
typedef struct Trie
{
    int val;
    
    boolean word_end;
	        
    struct Trie *parent;
    struct Trie *arcs[LETTER_RANGE];
} *trie;

typedef struct Trie mem_type;
typedef mem_type *q_type;

typedef struct CB_Queue
{
    q_type *data;
    
    int cap;  
    int count; 
    int head;  
    int tail;
} *cb_queue;

typedef struct MemPage
{
    int top;
    
    mem_type array[MEM_WIDTH];
} *mem_page;

struct MemContainer
{
    int top;
    
    mem_page *pages;
    
    cb_queue Freed;
} Container;

boolean queue_empty(cb_queue q);
boolean map_empty(trie T);
boolean full_page(mem_page page);

mem_page create_mem_page();
mem_type *silly_alloc(struct MemContainer *C);

trie insert_trie(trie T, char *k);
trie init_trie();

q_type dequeue(cb_queue q);

cb_queue init_queue(int nel);

int lookup(trie T, char *k);
int prefix(trie T, char *k);

void silly_free(mem_type *elem, struct MemContainer *Container);
void destroy_container(struct MemContainer *Container);

void init_memory(struct MemContainer *Container);
void descend(trie T, char *k, int *i, trie *x);

void increase_container(struct MemContainer *Container);
void increase_val(trie x);
void decrease_val(trie x);

void delete_trie_node(trie T, char *k);

void enqueue(cb_queue q, q_type x);
void delete_queue(cb_queue q);

void commands(trie T, int n);

int main(int argc, char **argv)
{
    init_memory(&Container);
    trie Root = init_trie();
    
    int n;
    scanf("%i", &n);
    
    commands(Root, n);
    
    destroy_container(&Container);
    
    return 0;
}

boolean queue_empty(cb_queue q)
{
    return !(q->count);
}

boolean map_empty(trie T)
{
    if(T->word_end) 
		return 0;
    
    int i;
    for(i = 0; i < LETTER_RANGE; ++i)
        if (T->arcs[i] != NULL) 
			return 0;
			
    return 1;
}

boolean full_page(mem_page page)
{
    return page->top == MEM_WIDTH;
}

mem_page create_mem_page()
{
    mem_page New = (mem_page)malloc(sizeof(struct MemPage));
    if(New == NULL)
	{
        printf("Out of memory\n");
        
        destroy_container(&Container);
    }
    
    New->top = 0;
    
    return New;
}

mem_type *silly_alloc(struct MemContainer *C)
{
    mem_page last = C->pages[C->top];
    mem_type *ptr = NULL;
    
    if(!full_page(last))
	{
        ptr = last->array + last->top;
        
        ++last->top;
        
        return ptr;
    } 
	else 
	{
        if(!queue_empty(C->Freed))
            return dequeue(C->Freed);
        else 
		{
            increase_container(C);
            
            last = C->pages[C->top];
            ptr = &(last->array[last->top]);
            
            ++(last->top);
            
            return ptr;
        }
    }
}

trie insert_trie(trie T, char *k)
{
    trie x = NULL;
    
    int i;
    descend(T, k, &i, &x);
    
    int len = strlen(k);

    if((i == len) && x->word_end)
	{
        return x;
    }
    
    trie y = NULL;
    for( ; i < len; i++)
	{
        y = init_trie();        
        x->arcs[KEY(k[i])] = y;
        
        y->parent = x;
        x = y;
    }
    
    x->word_end = 1;
    
    increase_val(x);

    return x;
}

trie init_trie()
{
    trie New = alloc; 
    
    memset(New, 0, sizeof(struct Trie));
    
    return New;
}

q_type dequeue(cb_queue q)
{
    if(queue_empty(q))
	{
        delete_queue(q);
        
        printf("!ERROR!\n");
        
        exit(1);
    }
    
    q_type result = q->data[q->head];
    ++q->head;
    
    if(q->head == q->cap)
        q->head = 0;
        
    --(q->count);
    
    return result;
}

cb_queue init_queue(int nel)
{
    cb_queue q = (cb_queue)malloc(sizeof(struct CB_Queue));
    
    q->data = (q_type *)malloc(nel*sizeof(q_type));
    q->cap = nel;
    q->count = q->head = q->tail = 0;
    
    return q;
}

int lookup(trie T, char *k)
{
    trie x = NULL;
    
    int i;
    descend(T, k, &i, &x);
    
    if((i != (int)strlen(k)) || !x->word_end)
	{
        printf("LOOKUP: !ERROR! descend function works incorrectly\n");
        
        return -1;
    }
    
    return x->val;
}

int prefix(trie T, char *k)
{
    trie x = T, y = NULL;
    int i = 0, len = strlen(k);
    while(i < len)
	{
        y = x->arcs[KEY(k[i])];
        
        if(!y) 
			return 0;
			 
        x = y;
        
        ++i;
    }
    
    return x->val;
}

void silly_free(mem_type *elem, struct MemContainer *Container)
{
    enqueue(Container->Freed, elem);
}

void destroy_container(struct MemContainer *Container)
{
    int i;
    for(i = 0; i <= Container->top; i++)
        free(Container->pages[i]);
        
    free(Container->pages);
    
    delete_queue(Container->Freed);
}

void init_memory(struct MemContainer *Container)
{
    Container->Freed = init_queue(MEM_WIDTH);
    
    Container->pages = (mem_page *)malloc(sizeof(mem_page));
    Container->pages[0] = create_mem_page();
    
    Container->top = 0;
}

void descend(trie T, char *k, int *i, trie *x)
{
    *x = T;
    trie y = NULL;
    
    int len = strlen(k);
    
    for(*i = 0; *i < len; (*i)++)
	{
        y = (*x)->arcs[KEY(k[*i])];
        
        if(y == NULL) break;
        	*x = y;
    }
}

void increase_container(struct MemContainer *Container)
{
    ++(Container->top);
    
    Container->pages = (mem_page *)realloc(Container->pages, sizeof(mem_page)*(Container->top + 1));
    Container->pages[Container->top] = create_mem_page();
}

void increase_val(trie x)
{
    trie Temp = x;
    
    while(Temp)
    {
        ++(Temp->val);
        Temp = Temp->parent;
    }
}

void decrease_val(trie x)
{
    trie Temp = x;
    
    while(Temp)
    {
        --(Temp->val);
        Temp = Temp->parent;
    }
}

void delete_trie_node(trie T, char *k)
{
    trie x = NULL;
    
    int i;
    descend(T, k, &i, &x);
    
    int len = strlen(k);
    if((i != len) || !x->word_end)
	{
        printf("DELETE: !ERROR! the word \"%s\" doesn't exist\n", k);
        
        return;
    }
    
    x->word_end = 0;
    
    int j = 0;
    while(x->parent && !x->word_end)
	{
        while(j < LETTER_RANGE && (x->arcs[j] == NULL))
        	++j;
        	
        if(j < LETTER_RANGE) 
			break;
			
        if(x->val > 1)
			break;
			
        trie y = x->parent;
        
        --i;
        
        y->arcs[KEY(k[i])] = NULL;
        
        my_free(x);
        
        x = y;
    }
    
    decrease_val(x);
}

void enqueue(cb_queue q, q_type x)
{
    if(q->count == q->cap)
	{
        int old_cap = q->cap;
        
        q->cap *= 2;
        q->data = (q_type *)realloc(q->data, q->cap*sizeof(q_type));
        
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

void delete_queue(cb_queue q)
{
    free(q->data);
    free(q);
}

void commands(trie T, int n)
{
    char command[LENGTH];
    char buffer[S_LENGTH];
    
    int i;
    for(i = 0; i < n; ++i)
	{
        scanf("%s %s", command, buffer);
        
        COMMAND(INSERT)
		{
            insert_trie(T, buffer);
            
        	continue;
        }
        
        COMMAND(DELETE)
		{
            delete_trie_node(T, buffer);

            continue;
        }
        
        COMMAND(PREFIX)
		{
            printf("%i\n", prefix(T, buffer));
            
            continue;
        }
    }
}
