#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define eat_whitespaces \
{\
    int letter;\
    while((letter = getchar()) == ' '){\
    }\
    ungetc(letter, stdin);\
}

#define LENGTH 100

#define alloc_list (struct Elem *)malloc(sizeof(struct Elem)+LENGTH)


typedef struct Elem 
{
    struct Elem *next;
    
    char *word;
    
    int key;
    int index;
} *elem;

elem init_new_elem();
elem find_tail(elem Head);

int compare(elem a);
int list_len(elem Head);

void add_to_tail(elem Head, elem New_elem);
void add_after(elem Current, elem New_elem);

void read_sentence(elem Head);

void print_list(elem Head);
void delete_list(elem Head);

void swap_head(elem Head);
void swap(elem a);

void bublesort(elem list);

struct Elem *bsort(struct Elem *list);

int main(int argc, char **argv)
{
    elem Head = init_new_elem();
    
    read_sentence(Head);
    
    bsort(Head);
    
    print_list(Head);
    
    delete_list(Head);
    
    return 0;
}

elem init_new_elem()
{
    elem New_elem = alloc_list;
    
    New_elem->next = NULL;
    New_elem->word = (char *)(New_elem + 1);
    New_elem->word[0] = '\0';
    New_elem->index = 0;
    
    return New_elem;
}

elem find_tail(elem Head)
{
    elem Tail = Head;
    
    while(Tail->next != NULL)
        Tail = Tail->next;

    return Tail;
}

int compare(elem a)
{
    return a->next->key < a->key;
}

int list_len(elem Head)
{
    elem Temp = Head;
    
    int counter = 0;
    while(Temp != NULL)
	{
        Temp = Temp->next;
        ++counter;
    }
    
    return counter;
}

void add_to_tail(elem Head, elem New_elem)
{
    elem Temp = Head;
    while(Temp->next != NULL)
        Temp = Temp->next;

    Temp->next = New_elem;
    New_elem->next = NULL;
    New_elem->index = Temp->index + 1;
}

void add_after(elem Current, elem New_elem)
{
    New_elem->next = Current->next;
    Current->next = New_elem;
    New_elem->index = Current->index + 1;
}

void read_sentence(elem Head)
{
	eat_whitespaces;
	
    int letter;
    if((letter = getchar()) == '\n')
        return;
        
    ungetc(letter, stdin);
    
    scanf("%s", Head->word);
    
    Head->key = strlen(Head->word);
    elem Tail = Head;
    elem Temp = NULL;
    
    while((letter = getchar()) != '\n')
	{
        ungetc(letter, stdin);
        
        Temp = init_new_elem();
        scanf(" %s", Temp->word);
        
        add_after(Tail, Temp);
        
        Tail = Temp;
        Tail->key = strlen(Tail->word);
    }
}

void print_list(elem Head)
{
    elem Temp = Head;
    
    while(Temp != NULL)
	{
        printf("%s ", Temp->word);

        Temp = Temp->next;
    }
}

void delete_list(elem Head)
{
    if(Head->next == NULL)
	{

        free(Head);
        
        return;
    }
    
    elem Current = Head;
    elem Next = Current->next;
    
    while(Next != NULL)
	{
        free(Current);
        
        Current = Next;
        Next = Current->next;
    }
    
    putchar('\n');

    free(Current);
}

void swap_head(elem Head)
{
    elem Temp = Head;
    
    Head = Head->next;
    Head->next = Temp;

}

void swap(elem a)
{
	char buff[LENGTH];
    elem b = a->next;
    
    strncpy(buff, a->word, LENGTH);
    strncpy(a->word, b->word, LENGTH);
    strncpy(b->word, buff, LENGTH);
    
    int temp;
    temp = a->key;
    a->key = b->key;
    b->key = temp;
}

void bublesort(elem list)
{
    elem prev, ptr, tmp;
    
    int exit = 0;
    while (!exit)
	{
        tmp = prev = NULL;
        ptr = list;
        
        exit = 1;
        while (ptr->next != NULL)
		{
            elem a = ptr;
            elem b = ptr->next;

            if (compare(ptr))
			{
                exit = 0;
                
                if (prev)
                    prev->next = b;
                else
                    list = b;

                prev = b;
                tmp = b->next;
                
                b->next = a;
                a->next = tmp;

                ptr = a;
            } 
			else 
			{
                prev = ptr;
                ptr = ptr->next;
            }
        }
    }
}

struct Elem *bsort(struct Elem *list)
{
    elem Tail = find_tail(list);
    elem i, bound, prev;
    
    while(Tail != list)
	{
        bound = Tail;
        for(Tail = i = prev = list; i != bound; i = i->next)
		{
            if(compare(i))
			{
                swap(i);
                
                Tail = i;
            }
            
            prev = i;
        }
    }
    
    return list;
}
