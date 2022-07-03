#include <stdlib.h>
#include <stdio.h>

void bubblesort(unsigned long nel, 
    int (*compare)(unsigned long i, unsigned long j), 
    void (*swap)(unsigned long i, unsigned long j));

int compare(unsigned long i, unsigned long j);
void swap(unsigned long i, unsigned long j);

int *array;
/*
int main(int argc, char **argv)
{
	int i, n;
	scanf("%i", &n);

	array = (int *)malloc(sizeof(int)*n);
	
	for(i = 0; i < n; i++) 
		scanf("%i", array + i);

	bubblesort(n, compare, swap);
	
	for(i = 0; i < n; i++) 
		printf("%i ", array[i]);

	free(array);
	
	return 0;
}
*/
void bubblesort(unsigned long nel, 
    int (*compare)(unsigned long i, unsigned long j), 
    void (*swap)(unsigned long i, unsigned long j)) 
{ 
    int left = 0, right = nel - 1, swapped = 1,
        new_left = left,
        new_right = right,
        i, j;
        
    while(swapped)
    {
    	swapped = 0;
    	
    	for(i = left; i < right; i++)
    		if(compare(i, i + 1))
    		{
    			swap(i, i + 1);
                swapped = 1;
                new_right = i;
    		}
        right = new_right;
        
    	if(!swapped) 
			break;
    	swapped = 0;

    	for(i = right; i > left; i--)
    	{
    		if(compare(i - 1, i))
    		{
    			swap(i - 1, i);
    			swapped = 1;
                new_left = i;
    		}
    	}
    	left = new_left;
    }
}

int compare(unsigned long i, unsigned long j)
{
	if(array[i] < array[j])
		return -1;
	else if(array[i] == array[j]) 
		return 0;
	else
		return 1;
}

void swap(unsigned long i, unsigned long j)
{
	int t = array[i];
	array[i] = array[j];
	array[j] = t;
}
