#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build (int *array, int a, int b, int *temp, int assist);
void update (int *temp, int a, int b, int i, int new, int assist);

int max1 (int *temp, int a, int b, int assist, int l, int r);
int max (int a, int b);
int min (int a, int b);

int main(int argc, char **argv) 
{
    int n, y;
    scanf("%i",  &n);
    int *array = (int *)malloc(sizeof(int)*n);
    
    char str[4];
    int a, b;
    
    int i;
    for(i = 0; i < n; i++)
        scanf("%i",  &array[i]);
        
    int *temp = (int *)malloc(sizeof(int)*(4*n));
    
    build(array, 0, n - 1, temp, 1);
	 
    scanf("%i",  &y);
    
    int *r = (int *)malloc(sizeof(int)*(y + 1));
    
    int q = 0;
    for(i = 0; i < y; i++) 
	{        
        scanf("%s %i %i",  str,  &a,  &b);
        
        if(!strcmp(str, "MAX")) 
		{
            *(r + q) = max1(temp, 0, n - 1, 1, a, b);
            
            ++q;
        }            
        else 
			update(temp, 0, n - 1, a, b, 1);
    }
    for(i = 0; i < q; i++)
        printf("%i\n",  r[i]);
	
    
	free(array);
	free(temp);       
	free(r);
	
    return 0;
}

void build(int *array, int a, int b, int *temp, int assist) 
{
    int mid;
    
    if(a == b)
        temp[assist] = array[b];
    else 
	{
        mid = (a + b)/2;
        build(array, a, mid, temp, 2*assist);
        build(array, mid + 1, b, temp, 2*assist + 1);
        temp[assist] = max(temp[2*assist], temp[2*assist + 1]);
    }
}

void update(int *temp, int a, int b, int i, int new, int assist) 
{
    int mid;
    
    if(a == b)
        temp[assist] = new;
    else
	{
        mid = (a + b)/2;
        if(i <= mid)
            update(temp, a, mid, i, new, 2*assist);
        else
			update(temp, mid + 1, b, i, new, 2*assist + 1);
			
        temp[assist] = max(temp[2*assist], temp[2*assist + 1]);
    }       
}

int max1(int *temp, int a, int b, int assist, int l, int r) 
{
    int mid;
    if((l == a) && (r == b))
        return temp[assist];
    else 
	{
		mid = (a + b)/2;
	    if(r <= mid)
	        max1(temp, a, mid, 2*assist, l, r);
	    else 
		{
            if(l > mid)
                max1(temp, mid + 1, b, 2*assist + 1, l, r);    
            else 
				return max((max1(temp, a, mid, 2*assist, l, min(r, mid))),
					(max1(temp, mid + 1, b, 2*assist + 1, max(l, mid + 1), r)));
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
