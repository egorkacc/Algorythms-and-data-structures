#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100 
#define MAX_LEN 10

#define even(n) !(n & 1)
#define _size_(of_struct) sizeof(struct of_struct)

#define sum_len sizeof(struct Elem) + (L->levels)*sizeof(elem) + (L->levels)*sizeof(int)
#define alloc_elem_ptr (elem *)malloc(sizeof(elem)*levels)

#define COMMAND(str) if(!strcmp(command, #str))

typedef char boolean;
typedef boolean (*cmp_type)(int, int);

typedef struct Elem
{
	struct Elem **next;
	
	int *span;
    int key;
    
    char value[MAX_LEN];
} *elem;

typedef struct List
{
	cmp_type compare;
    elem Head;
    
    int nel;
    int levels;
    
    void *buffer;
} *list;

list init_list(int nel, cmp_type compare);

elem init_elem(list L);
elem succ(elem x);

elem *skip(list L, int key);
elem lookup(list L, int key);

elem insert(list L, elem x);
elem rank_insert(list L, elem New);

boolean list_empty(elem Head);
boolean compare_min(int a, int b);

int fast_log2(int n);

int rank(list L, int key);

void rank_delete_elem(list L, int key);
void delete_elem(list L, int key);

void delete_list(list L);

void command_centre(list L, int n);

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);
    
    list L = init_list(n, compare_min);
    
    command_centre(L, n);
    
    delete_list(L);
    
    return 0;
}

list init_list(int nel, cmp_type compare)
{
    list New = (list)malloc(sizeof(struct List));
    New->nel = nel;
    New->compare = compare;
    New->levels = fast_log2(nel) + 1;
    
    New->buffer = malloc((New->levels)*(sizeof(elem) + sizeof(int)));
    New->Head = init_elem(New);
    
    return New;
}

elem init_elem(list L)
{
    elem New_list = (elem)calloc(1, sum_len);
    New_list->next = (elem *)(New_list + 1);
    New_list->span = (int *)(New_list->next + L->levels);
    
    return New_list;
}

elem succ(elem x)
{
    return x->next[0];
}

elem *skip(list L, int key) 
{
    elem *p = (elem *)L->buffer;
    elem x = L->Head;
    
    int i;
    for(i = L->levels - 1; i + 1; --i) 
	{
        while((x->next[i] != NULL) && (L->compare(x->next[i]->key, key)))
            x = x->next[i];
            
        p[i] = x;
    }
    
    return p;
}

elem lookup(list L, int key)
{
    elem *p = skip(L, key);
    elem Temp = succ(p[0]);
    
    if(!Temp || (Temp->key != key))
    {
        printf("LOOKUP: The key is not found\n"); //При правильных входных данных сюда не зайдет
        
        return NULL;
    }
    
    return Temp;
}

elem insert(list L, elem x) 
{
    int key = x->key;
    elem *p = skip(L, x->key);
    
    if(p[0]->next[0] && (p[0]->next[0]->key == key))
	{
        printf("INSERT: The elem already exists\n"); //При правильных входных данных сюда не зайдет
        
        return NULL;
    }
    
    printf("%i %s\n", x->key, x->value);
    
    int r = 2*rand();
    
    int i;
    for(i = 0; (i < L->levels) && even(r); i++)
	{
        x->next[i] = p[i]->next[i];
        p[i]->next[i] = x;
        r /= 2;
    }
    
    while(i < L->levels)
	{
        x->next[i] = NULL;
        
        ++i;
    }
    
    return x;
}

elem rank_insert(list L, elem New) 
{
    int key = New->key;
    int m = L->levels;
    
    elem *p = (elem *)L->buffer;
    elem x = L->Head;
    
    int *distances = (int *)(p + m);
    int i = m - 1;
    int counter;

    while((x->next[i] != NULL) && (L->compare(x->next[i]->key, key)))
        x = x->next[i];

    p[i] = x;
    for(i = m - 2; i + 1; i--) 
	{
        counter = 0;
        while((x->next[i] != NULL) && L->compare(x->next[i]->key, key))
		{
            counter += x->span[i];
            
            x = x->next[i];
        }
        
        p[i] = x;
        distances[i + 1] = counter;
    }
    distances[0] = 0;

    for(i = 1; i < m; i++)
        distances[i] += distances[i - 1];

    if (p[0]->next[0] && (p[0]->next[0]->key == key))
	{
        printf("INSERT: The key %i already exists\n", key); //При правильных входных данных сюда не зайдет
        
        free(New);
        
        return p[0]->next[0];
    }
    
    x = New;
    int old_span;
    int r = 2*rand();
    
    for(i = 0; (i < L->levels) && even(r); i++)
	{
        x->next[i] = p[i]->next[i];
        p[i]->next[i] = x;
        
        old_span = p[i]->span[i];
        p[i]->span[i] = distances[i] + 1;
        
        x->span[i] = old_span - distances[i];

        r /= 2;
    }

    while(i < m)
	{
        ++(p[i]->span[i]);
        ++i;
    }
    
    return x;
}

boolean list_empty(elem Head)
{
    return !(Head->next[0]);
}

boolean compare_min(int a, int b)
{
    return a < b;
}

int fast_log2(int n)
{
    if(n < 1)
	{
        printf("MY_LOG2: The number %u is incorrect\n", n); //При правильных входных данных сюда не зайдет
        
        return -1;
    }
    
    if(n == 1) 
		return 0;
		
    int delta, i;
    delta = i = 16;
    
    int assist;
    while(1)
	{
        delta /= 2;
        assist = n >> i;
        
        if(assist == 1) 
			return i;
			
        if(assist)
            i += delta;
        else
            i -= delta;
    }
    
    return -1;
}

int rank(list L, int key) 
{
    int m = L->levels;
    elem *p = (elem *)L->buffer;
    elem x = L->Head;
    
    int i;
    int counter = 0;
    for(i = m - 1; i + 1; i--)
	{
        while((x->next[i] != NULL) && L->compare(x->next[i]->key, key))
		{
            counter += x->span[i];
            x = x->next[i];
        }
        
        p[i] = x;
	}
	
    if (!(p[0]->next[0]) || (p[0]->next[0]->key != key))
	{
        printf("RANK: The key %i is not found\n", key); //При правильных входных данных сюда не зайдет
        
        return -1;
    }
    
    return counter;
}

void rank_delete_elem(list L, int key)
{

    elem *p = skip(L, key);
    elem x = succ(p[0]);
    
    if (!x || (x->key != key))
    {
        printf("DELETE ELEM: The key is not found.\n"); //При правильных входных данных сюда не зайдет
        
        return;
    }
    
    int m = L->levels;
    
    int i;
    for(i = 0; (i < m) && (p[i]->next[i] == x); i++)
	{
        p[i]->next[i] = x->next[i];
        p[i]->span[i] += x->span[i] - 1;
    }
    
    while(i < m)
	{
        --(p[i]->span[i]);
        
        ++i;
    }
    
    free(x);
}

void delete_elem(list L, int key)
{
    elem *p = skip(L, key);
    elem x = succ(p[0]);
    
    if (!x || (x->key != key))
    {
        printf("DELETE ELEM: The key is not found\n"); //При правильных входных данных сюда не зайдет
        
        return;
    }
    
    int m = L->levels;
    
    int i;
    for(i = 0; (i < m) && (p[i]->next[i] == x); i++)
        p[i]->next[i] = x->next[i];

    free(x);
}

void delete_list(list L)
{
    elem temp = L->Head;
    elem prev = NULL;
    
    while(temp != NULL)
	{
        prev = temp;
        temp = temp->next[0];
        
        free(prev);
    }
    free(L->buffer);
    free(L);
}

void command_centre(list L, int n)
{
    char command[NAME_LEN];
    elem TEMP = NULL;
    
    int arg, i;
    for(i = 0; i < n; i++, TEMP = NULL)
	{
        scanf("%s", command);
        
        COMMAND(INSERT)
		{
            TEMP = init_elem(L);
            
            scanf("%i %s", &TEMP->key, TEMP->value);
            
            rank_insert(L, TEMP);
            
            continue;
        }
        
        COMMAND(LOOKUP)
		{
            scanf("%i", &arg);
            
            TEMP = lookup(L, arg);
            
            printf("%s\n", TEMP->value);
            
			continue;
        }
        
        COMMAND(DELETE)
		{
            scanf("%i", &arg);
            
			rank_delete_elem(L, arg);
            
			continue;
        }
        
        COMMAND(RANK)
		{
            scanf("%i", &arg);
            
            printf("%i\n", rank(L, arg));
        }
    }
}
