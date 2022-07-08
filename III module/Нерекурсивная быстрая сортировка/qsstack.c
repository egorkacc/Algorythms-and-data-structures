#include <stdio.h>
#include <stdlib.h>

typedef struct stack st;
typedef struct Task t;

struct Task
{ 
    int low, high; 
};

struct stack
{
    struct Task *data;
    int cap, top;
};

t pop(st *s);

void quicksort(int *arr, int n);

void swap(int *a, int *b);
void initstack (st *s, int n);
void push(st *s, int left, int right);

int stackempty(st *s);

int main(int argc, char **argv) 
{
    int n;
    scanf("%i", &n);
    
    int *arr = (int *)malloc(sizeof(int)*(n + 1));
    
    int i;
    for(i = 0; i < n; i++)
        scanf("%i", &arr[i]);
        
    quicksort(arr, n);
    
    for(i = 0; i < n; i++)
        printf("%i ", arr[i]);
    printf("\n");
    
    free(arr);
    
    return 0;
}

t pop(st *s) 
{
    t x;
    --(s->top);
    
    x = s->data[s->top]; 
    
    return x;
}

void quicksort(int *arr, int n) 
{
    int left, right, mid, assist;
    
    st s;
    initstack(&s, 5000);
    
    push(&s, 0, n - 1);
    
    while (!(stackempty(&s)))
    {
        t temp = pop(&s);
        while(temp.high > temp.low)
	{
            mid = (temp.low + temp.high)/2;
            left = temp.low;
            right = temp.high;
            
            assist = arr[mid];
            
            while(left < right)
	    {
                while(assist > arr[left]) 
                    ++left;
                    
                while(assist < arr[right])
                    --right;
                    
                if(right > (left - 1))
		{
                    swap(&arr[right], &arr[left]);
                    
                    ++left;
                    --right;
                }
            } 
			 
            if(left <= (mid - 1)) 
	    {
                if(left < temp.high)
                    push(&s, left, temp.high);
                    
                temp.high = right;
            }
            else
	    {
                if(right > temp.low)
                    push(&s, temp.low, right);
                    
                temp.low = left;    
            }   
        } 
    }
	 
    free(s.data);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initstack (st *s, int n) 
{
    s->cap = n;
    s->top = 0;
    s->data = (struct Task *)malloc((sizeof(struct Task))*(n + 1));
}

void push(st *s, int left, int right) 
{
    s->data[s->top].low = left;
    s->data[s->top].high = right;
    ++(s->top);
}

int stackempty(st *s) 
{
    if(!s->top)  
        return 1;
    else 
	return 0;       
}
