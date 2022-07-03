#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define out printf
#define SHOW_LIST(n) {\
elem help = Head;\
printf("list:  ");\
    int i;\
for(i = 0; i < n; ++i){\
    printf("[%i] = %i;  ", help->index, help->v);\
    help = help->next;\
}\
putchar('\n');\
}
#else
#define out(...)
#define SHOW_LIST(n)
#endif

#define alloc_elem (struct Elem *)malloc(sizeof(struct Elem))

typedef int val_type;

typedef struct Elem 
{
    struct Elem *prev, *next;
    
    int v;
    int index;
} *elem;

elem init_double_linked_list();

int compare(elem a, elem compared);

void insert_after(elem Current_elem, val_type val);
void insert_before_head(elem Head, val_type val);
void insert_after_tail(elem Head, val_type val);

void delete_elem(elem Elem_to_del);
void delete_tail(elem Head);
void delete_list(elem Head);

void insertion_sort(elem Head, int n);

int main(int argc, char **argv)
{
    elem Head = init_double_linked_list();
    
    int n;
    scanf("%i", &n);
    
    int i, temp;
    if(n) 
		scanf("%i", &Head->v);
		
    for(i = 1; i < n; i++)
	{
        scanf("%i", &temp);
        
        insert_after_tail(Head, temp);
    }
    
    SHOW_LIST(n)
    insertion_sort(Head, n);
    SHOW_LIST(n)
    
    elem help = Head;
    for(i = 0; i < n; i++)
	{
        printf("%i ", help->v);
        
        help = help->next;
    }
    
    putchar('\n');
    
    delete_list(Head);
    
    return 0;
}

elem init_double_linked_list()
{
	
    elem New_Head = alloc_elem;
    New_Head->next = New_Head->prev = New_Head;
    New_Head->index = 0;
    
    return New_Head;
}

int compare(elem a, elem compared)
{
    out("a[%i] = %i, compared = %i\n", a->index, a->v, compared->v);
    
    return a->v > compared->v;
}

void insert_after(elem Current_elem, val_type val)
{
    elem New_elem = alloc_elem;
    New_elem->v = val;
    
    Current_elem->next->prev = New_elem;
    New_elem->next = Current_elem->next; 
    
    Current_elem->next = New_elem;
    New_elem->prev = Current_elem;
    
    New_elem->index = Current_elem->index + 1;
    
    ++(New_elem->next->index);
    
    out("value = %i, index = %i, prev = %i, next = %i\n", New_elem->v, New_elem->index, New_elem->prev->index, New_elem->next->index);
}

void insert_before_head(elem Head, val_type val)
{
    insert_after(Head, Head->v);
    
    Head->v = val;

}

void insert_after_tail(elem Head, val_type val)
{
    elem Tail = alloc_elem;
    
    Tail->v = val;
    Tail->next = Head;
    Tail->prev = Head->prev;
    Tail->prev->next = Tail;
    
    Head->prev = Tail;
    
    Tail->index = Tail->prev->index + 1;
    
    out("value = %i, index = %i, prev = %i, next = %i\n", Tail->v, Tail->index, Tail->prev->index, Tail->next->index);
}

void delete_elem(elem Elem_to_del)
{
    out("delete_elem [%i] = %i\n", Elem_to_del->index, Elem_to_del->v);
    
    Elem_to_del->next->prev = Elem_to_del->prev; 
    Elem_to_del->prev->next = Elem_to_del->next;
    
    --(Elem_to_del->next->index);
    
    free(Elem_to_del);
}

void delete_tail(elem Head)
{
    elem current;
    
    current = Head->prev;
    current->prev->next = Head;
    
    Head->prev = current->prev;
    
    free(current);
}

void delete_list(elem Head)
{
    elem Tail = Head->prev;
    
    while(Tail != Head)
	{
        Tail = Tail->prev;
        
        out("del_ind = %i\n", Tail->next->index);
        
        free(Tail->next);
    }
    
    free(Head);
}

void insertion_sort(elem Head, int n)
{
    elem temp = alloc_elem;  
    elem i, loc;   
    
    int counter = 0;
    int counter2 = 0;
    
    for(i = Head->next; i != Head; counter2++)
	{
		*temp = *i, loc = i->prev;
        while(loc->next != Head && compare(loc, temp))
			loc = loc->prev;
        
        if(loc->next == Head)
            insert_before_head(Head, i->v);
        else
        	insert_after(loc, i->v);  
        
        i = i->next;
        
        delete_elem(i->prev);
        
        SHOW_LIST(n)
    }
    
    free(temp);
}
