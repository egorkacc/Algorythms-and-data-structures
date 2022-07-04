#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100

#define LOOP -1

int compare(const void *a, const void *b);

size_t howManyA(const char *str);

void countA(char *str, size_t nel);
void swap(void *base, size_t i, size_t j, size_t width);

void hsort(void *base, size_t nel, size_t width,
    int (*compare)(const void *a, const void *b));
    
void buildHeap(void *base, size_t nel, size_t width,
    int (*compare)(const void *, const void *));
    
void heapify(void *base, size_t i, size_t nel, size_t width,
    int (*compare)(const void *, const void *));

void countA(char *str, size_t nel);

int main(int argc, char **argv)
{
    size_t number;     
    scanf("%zi", &number);
    
    char *superstr = (char *)malloc(number*MAX_LINES); 

    size_t i;
    for (i = 0; i < number; i++)
        scanf("%s", superstr + i*MAX_LINES);

    hsort(superstr, number, MAX_LINES, compare);
    
    for (i = 0; i < number; i++)
        printf("%s\n", superstr + i*MAX_LINES);

    free(superstr);
    
    return 0;
}

void hsort(void *base, size_t nel, size_t width,
    int (*compare)(const void *, const void *))
{
    if(nel < 2) 
		return;
    
    buildHeap(base, nel, width, compare);
    
    size_t i;
    for(i = nel - 1; i ; i--)
	{
        swap(base, 0, i, width); 
        
        heapify(base, 0, i, width, compare); 
    }   
}

void buildHeap(void *base, size_t nel, size_t width,
    int (*compare)(const void *, const void *))
{
    size_t i = (nel/2 - 1);
    while(LOOP) 
	{
        heapify(base, i, nel, width, compare);
        
        if(!i)
			break;
			
        --i;
    }
}

void heapify(void *base, size_t i, size_t nel, size_t width,
    int (*compare)(const void *, const void *))
{
    size_t left, right, old_root;
    while(LOOP)
    {
        left = 2*i + 1;    
        right = left + 1;   
        old_root = i;
        
        if (left < nel && (compare((char *)base + i*width, (char *)base + left*width) == 1))
            i = left;

        if (right < nel && (compare((char *)base + i*width, (char *)base + right*width) == 1))
            i = right;
        
        if (i == old_root)
            break;     

        swap(base, i, old_root, width);
    }
}

int compare(const void *a, const void *b)
{
    const char *str_a = a;
    const char *str_b = b;
    
    size_t counter_a = howManyA(str_a);
    size_t counter_b = howManyA(str_b);

    if(counter_a == counter_b) 
		return 0;
	
	if(counter_a < counter_b)
		return 1;
	else
		return -1;
}

size_t howManyA(const char *str)
{
    size_t counter = 0;
    size_t i = 0;

    while(str[i])
        if(str[i++] == 'a')
            ++counter;
        
    return counter;
}

void swap(void *base, size_t i, size_t j, size_t width)
{
    void *buff = malloc(width);
    
    memcpy(buff, (char *)base + i*width, width);
    memcpy((char *)base + i*width, (char *)base + j*width, width);
    memcpy((char *)base + j*width, buff, width);
    
    free(buff);
}

void countA(char *str, size_t nel)
{
    size_t i;
    for(i = 0; i < nel; i += MAX_LINES)
	{
        *(str + i) = howManyA(str + i);
        
        printf("%i %s\n", str[i], str + i);
    }
}
