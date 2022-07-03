#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date Date;

struct Date 
{ 
    int Day, Month, Year;
};
    
Date *datesort(Date *source, char d, int nel);
  
int main(int argc, char** argv) 
{
    int n;
    scanf("%i", &n);
    
    Date *a = (Date *)malloc(sizeof(Date)*(n + 1));
  
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%i", &a[i].Year);
        
        scanf("%i", &a[i].Month);
        if(!a[i].Month)
    		scanf("%i", &a[i].Month);
    		
        scanf("%i", &a[i].Day);
        if(!a[i].Day)
    		scanf("%i", &a[i].Day);
	}
/*	
	printf("===================================\n");
	for(i = 0; i < n; i++)
    {
        printf("%i %i", a[i].Month, a[i].Day);
        printf("\n");
	}
	printf("===================================\n");
*/		
	if(n - 1)
	{
		a = datesort(a, 'd', n);
		a = datesort(a, 'm', n);
		a = datesort(a, 'y', n);
	}
    
    for(i = 0; i < n; i++) 
	{
		if((a[i].Month > 9) && (a[i].Day > 9))
        	printf("%i %i %i", a[i].Year, a[i].Month, a[i].Day);
        else if((a[i].Month > 9) && (a[i].Day <= 9))
        	printf("%i %i 0%i", a[i].Year, a[i].Month, a[i].Day);
		else if((a[i].Month <= 9) && (a[i].Day > 9))
        	printf("%i 0%i %i", a[i].Year, a[i].Month, a[i].Day);
        else
        	printf("%i 0%i 0%i", a[i].Year, a[i].Month, a[i].Day);
        printf("\n");
    }
  
    free(a);
    
    return 0;
}
  
Date *datesort(Date *source, char d, int nel)
{
	Date* ans = (Date *)malloc(sizeof(Date)*(nel + 1));
	
    int assist;
    if(d == 'd')
        assist = 32;
    if(d == 'm') 
        assist = 13;
    if(d == 'y') 
        assist = 61;
          
	int cou[assist];	    
    int i;
    
    for(i = 0; i < assist; i++)
        cou[i] = 0;
    
	int k;    
    for(i = 0; i < nel; i++) 
	{
        if(d == 'd')
            k = source[i].Day;
        if(d == 'm')
            k = source[i].Month;    
        if(d == 'y')
            k = source[i].Year - 1970;
        
        ++cou[k];
    } 

    int _assist = assist - 1;
    while(_assist)
	{
        cou[assist - _assist] = cou[assist - _assist] + cou[assist - _assist - 1];
    	--_assist;
    }
    
    for(i = 0; i < nel; i++)
        ans[i] = source[i];
    
	int j = --nel;    
    while(j + 1)
	{
        if(d == 'd')
            k = source[j].Day;
        if(d == 'm')
            k = source[j].Month;    
        if(d == 'y')
            k = source[j].Year - 1970;
            
        i = --cou[k];
        cou[k] = i;
        
        ans[i].Day = source[j].Day;
        ans[i].Month = source[j].Month;
        ans[i].Year = source[j].Year;
        
        --j;
    }
    
    free(source);
    
    return ans;        
}
