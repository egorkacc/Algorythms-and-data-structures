#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(int a1, int a2);

void insertion_sort(int *base, int low, int high);

void merge(int *base, int low, int med, int high);
void mergesort_rec(int *base, int low, int high);
void mergesort(int *base, int nel);

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);
    
    int *arr = (int *)malloc(sizeof(int)*n);
    
    int i;
    for(i = 0; i < n; i++) 
		scanf("%i", arr + i);
    
    mergesort(arr, n);
    
    for(i = 0; i < n; i++) 
		printf("%i ", arr[i]);
    
    free(arr);
    
    return 0;
}

int compare(int a1, int a2)
{
    return (abs(a1) > abs(a2));
}

void insertion_sort(int *base, int low, int high)
{
    int elem;           
    int i, loc; 
    for(i = low + 1; i <= high; i++)
	{
        for(elem = base[i], loc = i - 1; (loc >= low) && compare(base[loc], elem); loc--)
            base[loc + 1] = base[loc];   
        
        base[loc + 1] = elem;
    }
}

void merge(int *base, int low, int med, int high)
{
    int count_1 = low;          
    int count_2 = med + 1;   
    int count_t = 0;      
	        
    int *temp = (int *)malloc(sizeof(int)*(high - low + 1));
    
    while(count_t < (high - low + 1))
	{
        if(count_1 <= med && (count_2 > high || !compare(base[count_1], base[count_2])))
            temp[count_t++] = base[count_1++];
        else
            temp[count_t++] = base[count_2++];
    }
    
    memcpy(base + low, temp, sizeof(int)*(high - low + 1));
    
    free(temp);
}


void mergesort_rec(int *base, int low, int high)
{
    if((high - low) > 4)
	{
        int med = (low + high)/2;
        
        mergesort_rec(base, low, med);
        mergesort_rec(base, med + 1, high);
        
        merge(base, low, med, high);
    } 
	else
        insertion_sort(base, low, high);
}

void mergesort(int *base, int nel)
{
    mergesort_rec(base, 0, nel - 1);
}
