#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	long long i, j;
	long long x, ans = 0;
    scanf("%lli", &x);
    
    if(x < 0)
        x = -x;
        
	int temp = sqrt(x) + 1;    
    long a[temp];
    a[0] = 0;
    a[1] = 0;
    
	for(i = 2; i < temp; i++)
		a[i] = 1;	
	
	for(i = 2; i*i <= temp; i++)
        if(a[i])  
            for(j = i*i; j <= temp; j += i)
                a[j] = 0;
		            
    for(i = 2; i <= sqrt(x); i++)
    	if(a[i] && !(x%i)) 
		{	
            x /= i;
            if((x%i) || (x == i))
	        	ans = x;
	        i = 1;
        }
	
	if(ans)
		printf("%lli\n", ans);
	else if(!ans && x && (x != 1))
	{
		ans = x;
		printf("%lli\n", ans);
	}
	else
		printf("Do not excist");	
	
	return 0;
}

