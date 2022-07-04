#include <stdlib.h>
#include <stdio.h>

unsigned long *fib;
int *array;

unsigned long make_fib_array(unsigned long nel);
unsigned long len_fib_array(unsigned long nel);

int compare(unsigned long i, unsigned long j);

void swap(unsigned long i, unsigned long j);

void shellsort(unsigned long,
    int (*)(unsigned long, unsigned long),
    void (*)(unsigned long, unsigned long));
/*
int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);

    array = (int*)malloc(sizeof(int)*n);
    
    int i;
    for(i = 0; i < n; i++) 
		scanf("%i", array + i);

    shellsort(n, compare, swap);
    
    for(i = 0; i < n; i++) 
		printf("%i ", array[i]);
		
    printf("\n");

    free(array);
    
    return 0;
}
*/
unsigned long make_fib_array(unsigned long nel)
{
    unsigned long i;
    unsigned long len = len_fib_array(nel);
    
    fib = (unsigned long *)malloc(sizeof(unsigned long)*(len + 2));
    fib[0] = 1; 
    fib[1] = 2;
    
    for(i = 1; i < (len - 1); i++)
        fib[i + 1] = fib[i] + fib[i - 1];

    return len; 
}

unsigned long len_fib_array(unsigned long nel)
{
    unsigned long fib1 = 1, fib2 = 2, temp, i;
    
    if (nel < 4) 
		return nel;
    
    for (i = 1; fib2 < nel; i++)
	{
        temp = fib2;
        fib2 += fib1;
        fib1 = temp;
    }
    
    return i;
}

int compare(unsigned long i, unsigned long j)
{
    if (array[i] == array[j]) 
		return 0;
	else if(array[i] < array[j])
		return -1;
	else
		return 1;
}

void swap(unsigned long i, unsigned long j)
{
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
}

void shellsort(unsigned long nel, int (*compare)(unsigned long i, unsigned long j),
    void (*swap)(unsigned long i, unsigned long j))
{

    unsigned long i, d, loc;
    unsigned long j;
    j = make_fib_array(nel);       
    for( ; j; j--)
	{
        d = fib[j - 1];
        
        for(i = d; i < nel; i++)
            for(loc = i - d; (compare(loc + d, loc) == -1); loc -= d)
			{
                swap(loc + d, loc);
                
                if(loc < d)
					break;
            }
    }
    
    free(fib);
}
