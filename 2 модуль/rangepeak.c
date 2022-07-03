#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20001

void build(int *array, int a, int b, int *t, int assist, int nel);
void update(int *array,  int *t, int a, int b, int i, int new_value, int assist, int nel);

int max1(int *t,  int a,  int b, int assist,  int l,  int r);
int max(int a, int b);
int min(int a, int b);

int is_peak(int *array,  int left, int nel);
int new_peak(int *array, int i, int new_value, int nel);
int new_peak_left(int *array, int i, int new_value, int nel);
int new_peak_right(int *array, int i, int new_value, int nel);

int main(int argc, char **argv) 
{
    int n, i, y, p;
    char str[5];
    int a, b;
    scanf("%i",  &n);
    int *array=(int *)malloc(n*sizeof(int));
    
    for(i = 0; i < n; i++)
        scanf("%i",  &array[i]);
        
    int *t = (int *)malloc(sizeof(int)*(5*n));
    
	for(i = 0; i < 4*n; i++)
        t[i] = 0;
        
    build(array, 0, n - 1, t, 1, n);
	 
    int *r = (int *)malloc(SIZE); 
	scanf("%i",  &y);
	
	int q = 0;     
    for(i = 0; i < y; i++) 
	{        
        scanf("%s %i %i",  str,  &a,  &b);
        
        if(strcmp(str, "PEAK") == 0) 
		{
            r[q] = max1(t, 0, n - 1, 1, a, b);
            
    		++q;
        }            
        else
            update(array, t, 0, n - 1, a, b, 1, n);     
   }
   
    for(i = 0; i < q; i++)
        printf("%i\n", r[i]);
        
	free(array);
	free(t);       
	free(r);
	
    return 0;
}

void build(int *array, int a, int b, int *t, int assist, int nel) 
{
    int center;
    if(a == b)
    t[assist] = is_peak(array, a, nel - 1);        
    else 
	{
            center = (a + b)/2;
            build(array, a, center, t, 2*assist, nel);
            build(array, center + 1, b, t, 2*assist + 1, nel);
            t[assist] = t[2*assist]+t[2*assist + 1];
    }
}

void update(int *array,  int *t, int a, int b, int i, int new_value, int assist, int nel)
{
    int center;
    center = (a + b)/2;
    if(a == b) 
	{
        t[assist - 1] = new_peak(array, i, new_value, nel - 1);
	    t[assist - 2] = new_peak_left(array, i - 1, new_value, nel - 1);
	    t[assist] = new_peak_right(array, i + 1, new_value, nel - 1);
    }
	else 
	{
	    if(i < center)
	        update(array, t, a, center, i, new_value, 2*assist, nel);
	    else 
			update(array, t, center + 1, b, i, new_value, 2*assist + 1, nel);
		t[assist - 1] = t[2*assist] + t[2*assist + 1];
	    t[1] = t[0];
	}
}

int max1(int *t,  int a,  int b, int assist,  int l,  int r) 
{
    int center;
    if((l == a) && (r == b)) 
        return t[assist];
	else 
	{
		center = (a + b)/2;
        if(r <= center)
            max1(t, a, center, 2*assist, l, r);
        else 
		{
            if(l > center)
                max1(t, center+1, b, 2*assist + 1, l, r);    
            else 
				return max1(t, a, center, 2*assist, l, min(r, center)) + (max1(t, center + 1, b, 2*assist + 1, max(l, center + 1),  r));
        }
	}
}

int max(int a, int b) 
{
    return(a > b) ? a : b;
}

int min(int a, int b) 
{
    return(a < b) ? a : b;
}


int is_peak(int *array,  int left, int nel) 
{
	if(!left && !nel)
		return 1;
		
    if(!left && (array[left] > array[left + 1])) 
		return 1;
		
	if(!left && (array[left] <= array[left + 1]))
		return 0;
		
	if((left == nel) && (array[left - 1] > array[left])) 
		return 0;
		
	if((left == nel) && (array[left - 1] <= array[left]))
		return 1;
		
    if((array[left - 1] <= array[left]) && (array[left] >= array[left + 1]))
		return 1;
	else 
		return 0;
}

int new_peak(int *array, int i, int new_value, int nel) 
{
	if(!i && !nel)
		return 1;
		
    if(!i && (new_value > array[i + 1])) 
		return 1;
		
	if(!i && (new_value <= array[i + 1]))
		return 0;
		
	if((i == nel) && (array[i - 1] > new_value)) 
		return 0;
		
	if((i == nel) && (array[i - 1] <= new_value))
		return 1;
		
    if((array[i - 1] <= new_value) && (new_value >= array[i + 1]))
		return 1;
	else 
		return 0;
}

int new_peak_left(int *array, int i, int new_value, int nel) 
{
	if(!i && !nel)
		return 1;
		
    if(!i && (array[i] > new_value)) 
		return 1;
		
	if(!i && (array[i] <= new_value))
		return 0;
		
	if((i == nel) && (array[i - 1] > array[i])) 
		return 0;
		
	if((i == nel) && (array[i - 1] <= array[i]))
		return 1;
		
    if((array[i - 1] <= array[i]) && (array[i] >= new_value))
		return 1;
	else 
		return 0;
}

int new_peak_right(int *array, int i, int new_value, int nel) 
{
	if(!i && !nel)
		return 1;
		
    if(!i && (array[i] > array[i + 1])) 
		return 1;
		
	if(!i && (array[i] <= array[i + 1]))
		return 0;
		
	if((i  ==  nel) && (new_value > array[i])) 
		return 0;
		
	if((i  ==  nel) && (new_value <= array[i]))
		return 1;
		
    if((new_value <= array[i]) && (array[i] >= array[i + 1]))
		return 1;
	else 
		return 0;
}
