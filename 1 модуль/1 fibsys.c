#include <stdio.h>

int main(int argc, char **argv) // доработать для больших
{
	unsigned char i, c;
	unsigned long long x;
	long q;
	unsigned char a[500] = {};
    unsigned long f[200] = {};
    
    scanf ("%llu", &x);
    
    if (!x)
		printf("%i ", 0);
	if (x == 1)
		printf("%i ", 1);
		
	q = c = i = 0;
	
	a[0] = 2;
    a[1] = 2;
		
	f[0] = 1;
	f[1] = 1;
	      
	for (i = 2; i <= x; i++) 
	{
		f[i] = 0;
		f[i] = f[i - 1] + f[i - 2];
		c = i;
		if (f[i] > x)
			break;
	}
	
    for (i = 0; i < c; i++)
        a[i] = 0;
        
	for (i = c; i; i--) 
	{
		a[i] = 0;
        q = x - f[i];
		if (q > -1) 
		{
			a[i] = 1;
			x -= f[i];
		}
		if (!x)
			break;
	}
		
	if (!a[c]) 
	{
        for (i = c - 1; i; i--) 
	        printf("%i", a[i]);
	}
	
	if (a[c] == 1) 
	{
        for (i = c; i; i--) 
	        printf("%i", a[i]);
	}
	
	return 0;	
}
