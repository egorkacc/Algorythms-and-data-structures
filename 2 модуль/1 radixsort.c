#include <stdio.h>
#include <malloc.h>

#define SIZE 256

typedef union Int32 
{
	unsigned char bytes[4];
	
    int elem;
} _int32;

int key(int index, int order);

void dispersion_sort(int order);
void radix_sort();

int arrsize;
_int32 *arr;

int main(int argc, char **argv)
{
    scanf("%i", &arrsize);
    
    arr = (_int32 *)malloc(sizeof(_int32)*arrsize);
    
    int i;
    for(i = 0; i < arrsize; i++) 
		scanf("%i", &arr[i].elem);
		
    radix_sort();
    
    for(i = 0; i < arrsize; i++) 
		printf("%i ", arr[i].elem);
		
    free(arr);
    
    return 0;
}

int key(int index, int order)
{
    int k = arr[index].bytes[order];
    
    if(order < 3)
        return k;
    else if(k < 128)
    	return k + 128;
    else
    	return k - 128;
}

void dispersion_sort(int order)
{
    int counter[SIZE];
    
    int i;
    for(i = 0; i < SIZE; i++) 
		counter[i] = 0;
		
	int k;
    for(i = 0; i < arrsize; i++)
	{
        k = key(i, order);
        
        ++counter[k];
    }
    
    for(i = 1; i < SIZE; i++)
        counter[i] += counter[i - 1];

    int temp[arrsize];
    for(i = arrsize - 1; i + 1; i--)
    {
        k = key(i, order);
        
        temp[--counter[k]] = arr[i].elem;
    }
    
    for(i = 0; i < arrsize; i++)
        arr[i].elem = temp[i];
}

void radix_sort()
{
    int i;
    for(i = 0; i < 4; i++)
        dispersion_sort(i);
}
