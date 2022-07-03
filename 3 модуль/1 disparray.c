#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST(str) if(!strcmp(command, #str))

#define LENGTH 256

#define hash_table_size sizeof(sizeof(struct Hash_table) + n*sizeof(list))

typedef int (*hash_type)(int, int);

typedef struct Elem 
{   
    int value;
    int index;
    
    struct Elem *next;
} *elem;

typedef struct List
{
    elem Head;
} *list;

typedef struct Hash_table
{
	int nel;
	
    list *table;
    hash_type h;
} *hash_table;

hash_table init_hash_table(int n, hash_type hash_func);

list init_new_list();

elem list_search(elem Head, int index);
elem init_new_elem();
elem scan_elem();

int lookup(elem *T, int index, int nel);
int hash(int i, int m);

void insert_hash_table(elem *T, elem New, int nel);
void insert_beforehead(list L, elem New_elem);
void insert_after(elem *T, elem New_elem);

void delete_from_head(elem T);
void delete_table(elem *table, int len);

void reassign(elem Old, elem New);

void commands(elem *table, int n, int length);

int main(int argc, char **argv)
{
    int request, length;
    scanf("%i %i", &request, &length);
    
    elem *table = (elem *)calloc(length, sizeof(elem));
    
    commands(table, request, length);
    
    delete_table(table, length);
    
    return 0;
}

hash_table init_hash_table(int n, hash_type hash_func)
{
    hash_table New_table = (hash_table)malloc(hash_table_size);
    
    New_table->table = (list  *)(New_table+1);
    New_table->nel = n;
    New_table->h = hash_func;
    
    int i;
    for(i = 0; i < n; i++)
        New_table->table[i]->Head = NULL;
        
    return New_table;
}

list init_new_list()
{
    list New_list = (list)malloc(sizeof(struct List));
    
    New_list->Head = NULL;
    
    return New_list;
}

elem list_search(elem Head, int index)
{
    elem Current = Head;
    
    while(Current && (Current->index != index))
        Current = Current->next;
        
    return Current;
}

elem init_new_elem()
{
    elem New_elem = (elem)malloc(sizeof(struct Elem));
    
    New_elem->next = NULL;
    
    return New_elem;
}

elem scan_elem()
{
    elem New = init_new_elem();
    
    scanf("%i %i", &New->index, &New->value);
    
    return New;
}

int lookup(elem *T, int index, int nel)
{
    int i = hash(index, nel);
    
    elem temp = list_search(T[i], index);
    if(!temp) 
		return 0;
		
    return temp->value;
}

int hash(int i, int m)
{
    return i%m;
}

void insert_hash_table(elem *T, elem New, int nel)
{
    int i = hash(New->index, nel);
    
    elem Temp = list_search(T[i], New->index);
    if(Temp)
	{
        reassign(Temp, New);
        
        return;
    }
    
    insert_after(&T[i], New);
}

void insert_beforehead(list L, elem New_elem)
{
    New_elem->next = L->Head;
    
    L->Head = New_elem->next;
}

void insert_after(elem *T, elem New_elem)
{
    if(!(*T))
	{
        *T = New_elem;
        
        return;
    }
    
    New_elem->next = T[0]->next;
    T[0]->next = New_elem;
}

void delete_from_head(elem T)
{
    if(!T) 
		return;
		
    elem Current = T;
    elem Next = Current->next;
    
    while(Next != NULL)
	{
        free(Current);
        
        Current = Next;
        Next = Current->next;
    }
    
    free(Current);
}


void delete_table(elem *table, int len)
{
    int i;
    for(i = 0; i < len; i++)
        delete_from_head(table[i]);
        
    free(table);
}

void reassign(elem Old, elem New)
{
    Old->value = New->value;
    
    free(New);
}

void commands(elem *table, int n, int length)
{
    char command[LENGTH];

    int idx, N = n;
    for(N; N; N--)
	{
        scanf("%s", command);
        
        REQUEST(ASSIGN)
		{
            elem New = scan_elem();
            
            insert_hash_table(table, New, length);
        }
        
        REQUEST(AT)
		{
            scanf("%i", &idx);
            
            printf("%i\n", lookup(table, idx, length));
        }
    }
}
