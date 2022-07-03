#include <stdlib.h>
#include <stdio.h>
#include "elem.h"

struct Elem *searchlist(struct Elem *list, int k)
{
	struct Elem *elem;
    if(list->value.list && (list->tag == LIST))
	{
        elem = searchlist(list->value.list, k);
        
        if(!elem)  
			searchlist(list->tail, k);
		else 
            return elem;
    }
    
    if(list->tail)
        searchlist(list->tail, k);
    else if(k == list->value.i)
        return list;
}
/*
int main(int argc, char **argv)
{
	struct Elem a, a1, a2;
	
	a.tag = FLOAT;
	a.value.i = 3.1412;
	a.tail = &a1;
	
	a1.tag = FLOAT;
	a1.value.f = 12.434234;
	a1.tail = &a2;
	
	a2.tag = INTEGER;
	a2.value.i = 1;
	a2.tail = 0;
	
	if(searchlist(&a, 1) == &a2)
		printf("c:\n");
	else
		printf(":c\n");
	
	return 0;
}
*/
