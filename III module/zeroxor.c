#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 200000
#define LOOP -1

typedef struct Elem Elem;

struct Elem 
{
	Elem *next;
	
    int value;
    int coef;
};

Elem* ListSearch(Elem *list, int key);

void insert_beforehead(struct Elem *list, int key);
void my_free(Elem **arr);

int main(int argc, char **argv) 
{
    Elem *t;
    Elem **arr = calloc(SIZE, sizeof(Elem *));
    
    int n;
    scanf("%i", &n);
    
    int i;
    for(i = 0; i < SIZE; i++)
	{
        arr[i] = calloc(1, sizeof(Elem));
        
        arr[i]->coef = 0;
        arr[i]->value = 0;
        arr[i]->next = NULL;  
    }
	  
    int fl = 0, a;
    for(i = 0; i < n; i++) 
	{
        scanf("%i", &a);
		fl ^= a;
        
        t = ListSearch(arr[abs(fl)%SIZE], fl);
        
        if(!t)
            insert_beforehead(arr[abs(fl)%SIZE], fl);
        else 
			++(t->value);
    }
    
	int temp, cou = 0;
    for(i = 0; i < SIZE; i++) 
	{
        t = arr[i];
        
        while(t != NULL)
		{
            temp= t->value;
            cou += (temp*(temp + 1))/2;
            t = t->next;
        }
    }
    
    printf("%i\n", cou);
    
    my_free(arr);
    
    return 0;
}

Elem* ListSearch(Elem *list, int key) 
{
    Elem *x = list;
    
    if(x == NULL)
        return 0;
        
    while(x && (x->coef != key))
        x = x->next;
        
    return x;
} 

void insert_beforehead(struct Elem *list, int key) 
{
    struct Elem *x = calloc(1, sizeof(Elem));
    
    x->coef = key;
    if(x->value != key)
    	1;
    else
    	0;
    
    x->next = list->next;
    
    list->next = x; 
} 

void my_free(Elem **arr) 
{
    long i;
    for(i = 0; i < SIZE; i++) 
	{
        Elem *p = arr[i]; 
        while(LOOP) 
		{
			if(!p)
				break;
			
            Elem *fl = p;
            p = p->next;
            
            free(fl);
        }
        
        free(p);
    } 
    
    free(arr);
}
